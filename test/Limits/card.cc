#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "card.h"

using namespace std;

//================================================================================

Card::Card(double         procchanyield,
	   const TString& procname,
	   const TString& channame,
	   const TString& systname,
	   const bool     issignal
	   )
{
  nbackproc_ = 0;
  nsigproc_  = 0;

  cout << "\tmake new card with process "<<procname<<", channel "<<channame<<endl;

  ProcData_t pd;

  pair<TString,double> channel;

  pd.name          = procname;
  channel.first    = channame;
  channel.second   = procchanyield; // the yield for this channel

  pd.channels.insert(channel);

  if( procname.Contains("data") ) {
    data_ = pd; // done.
  } else {

    if( issignal) {

      assert(!systname.Length());     // don't expect to encounter shape systematic first.

      nsigproc_++;
      pd.procindex = 1-nsigproc_; /* process index for signal processes required to be distinct,
				    as well as 0 or negative */
    } else {                                                        //background
      nbackproc_++;
      pd.procindex = nbackproc_;
    }
      
    processes_.push_back(pd);
    pname2index_[procname]= 0;

  } // else not data

}                                                                   // Card::Card

//================================================================================

void
Card::addProcessChannel(double         procchanyield,// process/channel yield
			const TString& procname,     // process name 
			const TString& channame,     // name of channel
			const TString& systname,     // name of (shape) systematic applied
			const bool     issignal
			)
{
  cout<<"\tadd to card "<<procname<<" "<<channame<<" "<<systname<<endl;;

  // With each input histogram one must:
  // 1. If a new process, update the process info in the card: "card.processes", "card.pname2index_",
  // 2. Update new channel information "processes[procindex].channels" (channel name/rate pairs)
  // 3. Update the systematics information as necessary:
  //    if systname.length, add shape systematic information to
  //    systematics (if new systematic), processes[procindex].systrates[systname+":"+channame]
  // 
  pair<TString,double> channel;

  const pair<double,double> zeropair(0.0,0.0);

  channel.first  = channame;
  channel.second = procchanyield;
  
  if( procname.Contains("data") )                             // *** DATA OBSERVATION ***

    if (!data_.name.Length()) {             // first channel of data encountered
      ProcData_t pd;
      pd.name = procname;
      pd.channels.insert(channel);
      data_ = pd;
    }else{                                      // another channel for data, possibly
      assert(!data_.name.CompareTo(procname)); // must be the same
      data_.channels.insert(channel);
    }

  else if( issignal ) {                                      // *** SIGNAL EXPECTATION ***

    map<TString,int>::iterator pit;
    pit = pname2index_.find(procname);
    if (pit == pname2index_.end()) {    // new signal process, first channel encountered
      nsigproc_++;

      assert(!systname.Length());     // don't expect to encounter shape systematic first

      ProcData_t pd;
      pd.name      = procname;
      pd.procindex = 1-nsigproc_; /* process index for signal processes required to be distinct,
					 as well as 0 or negative */

      pd.channels.insert(channel);

      // put new signal in front, have to adjust the mapped indices for all the rest.
      // This maintains the proper ordering of processes in the datacard (for LandS)
      //
      for (pit = pname2index_.begin(); pit != pname2index_.end(); pit++)
	pit->second++;

      processes_.push_front(pd);

      pname2index_[pd.name] = 0;

    } else {                        // another channel for signal, or a shape systematic

      ProcData_t& pd = processes_[pit->second];
      assert(pd.name.Length());             // process should exist here
      assert(!pd.name.CompareTo(procname)); // must be the same

      if (systname.Length()) {
	systematics_[systname] = "shape1";

	pd.systrates[systname+":"+channame].second = 1.0;  // except the current channel

      } else {

	pd.channels.insert(channel);

      } // nominal signal histo
    } // signal histo for another channel, or systematic

  } else {                                                  // *** BACKGROUND PROCESS ***

    map<TString,int>::iterator pit;
    pit = pname2index_.find(procname);
    if (pit == pname2index_.end()) {    // first channel of this background process encountered
      nbackproc_++;

      ProcData_t pd;
      pd.name = procname;
      pd.procindex = nbackproc_;

      if (systname.Length()) {               // a shape-based limit
	systematics_[systname] = "shape1";
	pd.systrates[systname+":"+channame].second = 1.0;
      }

      pd.channels.insert(channel);

      pname2index_[pd.name] = (int)processes_.size();
      processes_.push_back(pd);

    } else {                                /* either another channel, or a shape
					       systematic for an existing channel */
      ProcData_t& pd = processes_[pit->second];

      if (systname.Length()) {              // a shape-based limit
	systematics_[systname] = "shape1";
	pd.systrates[systname+":"+channame].second = 1.0;
      }
      else {
	assert(pd.name.Length());             // process should exist here
	assert(!pd.name.CompareTo(procname)); // and be named the same
	pd.channels.insert(channel);
      }
    }
  }
}                                                       // Card::addProcessChannel

//================================================================================

void
Card::addSystematic(const TString& systname,
		    const TString& procname,
		    const TString& channame,
		    const double   unc,
		    const TString& pdf)
{
  cout<<"\taddSystematic "<<systname<<" to "<<procname<<endl;

  assert( !procname.Contains("data") );

  const pair<double,double> zeropair(0.0,0.0);

  std::map<TString,TString>::const_iterator sit = systematics_.find(systname);
  if (sit == systematics_.end())
    systematics_[systname] = pdf;

  std::map<TString,int>::const_iterator pit = pname2index_.find(procname);
  assert(pit != pname2index_.end());

  int index = pit->second;
  ProcData_t& pd = processes_[index];

  pd.systrates[systname+":"+channame].second = unc;
}                                                           // Card::addSystematic

//================================================================================

void
Card::addSyst2ShapeFile(const TString& procname,
			const TString& histname)
{
  size_t i;
  for (i=0; i<shapespecs_.size(); i++)
    if (shapespecs_[i].process == procname) {
      shapespecs_[i].histo_with_syst = histname;
      break;
    }
  assert(i<shapespecs_.size());
}                                                       // Card::addSyst2ShapeFile

//================================================================================

void
Card::addModelParam(const TString& paramname,
		    const TString& paramtype)
{
  ModelParam_t mp;
  mp.name = paramname;
  mp.type = paramtype;
  modelparams_.push_back(mp);
}                                                           // Card::addModelParam

//================================================================================

// see documentation for higgs combine tool, data card file specification
// https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideHiggsAnalysisCombinedLimit
//
void Card::Print(const TString& dcardname)
{
  using namespace std;

  assert(processes_.size());

  int nbins= processes_[0].channels.size();
  int jmax = processes_.size()-1;


#if 0
  TString outdir;
  if (shapesfile.Contains("/"))
    outdir=shapesfile(0,shapesfile.Last('/'));
  else
    outdir=TString(".");
#endif

  cout << "Writing "<<dcardname<<endl;

  FILE* dcFile=fopen(dcardname.Data(),"wt");
  //FILE* dcFile=stdout;

  assert (dcFile);

  fprintf(dcFile,"imax %d  # number of channels\n",nbins);
  fprintf(dcFile,"jmax %d  # number of processes-1\n",jmax);
  fprintf(dcFile,"kmax *  # number of nuisance parameters\n");

  fprintf(dcFile,"--------------------\n");

  // these are the data loops
  fprintf(dcFile,"bin                                ");
  for (map<TString,double>::const_iterator it=data_.channels.begin();
       it != data_.channels.end();
       it++) {
    fprintf(dcFile,"%15s",it->first.Data());
  }
  fprintf(dcFile,"\nobservation                        ");
  for (map<TString,double>::const_iterator it=data_.channels.begin();
       it != data_.channels.end();
       it++) {
    //fprintf(dcFile,"%15d",(int)it->second);
    fprintf(dcFile,"%15.5f",it->second);
  }
  
  fprintf(dcFile,"\n--------------------\n");

  if (shapespecs_.size()) {
    for (size_t i = 0; i < shapespecs_.size(); i++)
      fprintf(dcFile,"shapes %s %s %s %s %s\n",
	      shapespecs_[i].process.Data(),
	      shapespecs_[i].channel.Data(),
	      shapespecs_[i].file.Data(),
	      shapespecs_[i].histo.Data(),
	      shapespecs_[i].histo_with_syst.Data());

    fprintf(dcFile,"--------------------\n");
  }

  /****************************************
   * YIELDS PER BIN/PROCESS
   ****************************************/

  //--------------------------------------------------------------------------------
#ifdef PROC_MAJOR_CHAN_MINOR_ORDERING

  // Example:
  //--------------------
  //bin           chan1    chan2    chan1   chan2   chan1    chan2
  //process       Signal   Signal   WJets   WJets     WW       WW
  //process         0        0        1       1        2        2  
  //--------------------

  // these are the signal and background loops
  fprintf(dcFile,"bin                                ");
  for (int j=0; j<=jmax; j++)
    for (map<TString,double>::const_iterator it=processes_[j].channels.begin();
	 it != processes_[j].channels.end();
	 it++)
      fprintf(dcFile,"%15s",it->first.Data());
  fprintf(dcFile,"\n");
  
  fprintf(dcFile,"process                            ");
  for (int j=0; j<=jmax; j++)
    for (int k=0; k<nbins; k++)
      fprintf(dcFile,"%15s",processes_[j].name.Data());
  fprintf(dcFile,"\n");

  fprintf(dcFile,"process                            ");
  for (int j=0; j<=jmax; j++)
    for (int k=0; k<nbins; k++)
      fprintf(dcFile,"%15d",processes_[j].procindex);
  fprintf(dcFile,"\n");

  fprintf(dcFile,"rate                               ");
  for (int j=0; j<=jmax; j++) 
    for (map<TString,double>::const_iterator it=processes_[j].channels.begin();
	 it != processes_[j].channels.end();
	 it++)
      fprintf(dcFile,"%15.2f",max(it->second,0.001));
  fprintf(dcFile,"\n");

  fprintf(dcFile,"--------------------\n");

  /****************************************
   * SYSTEMATICS
   ****************************************/

  map<TString,TString>::const_iterator sit;
  for (sit  = systematics_.begin();
       sit != systematics_.end();
       sit++) {
    const TString& name = sit->first;
    const TString& pdf  = sit->second;
    fprintf(dcFile,"%-32s %5s",name.Data(),pdf.Data());
    for (int j=0; j<=jmax; j++) {
      const ProcData_t& pd = processes_[j];
      map<TString,double>::const_iterator chit;
      for (chit  = pd.channels.begin();
	   chit != pd.channels.end();
	   chit++) {
	TString srchstr = name+":"+chit->first;
	map<TString,pair<double,double> >::const_iterator rit = pd.systrates.find(srchstr);
	if (rit == pd.systrates.end()) {
	  fprintf(dcFile,"        -      ");
	} else {
	  pair<double,double> rate = rit->second;
	  if (rate.second == 0.0)        // expect the UP (second) to contain single-sided error values
	    fprintf(dcFile,"        -      ");
	  else if (rate.first == 0.0)
	    fprintf(dcFile,"  %10.4g   ",rate.second);
	  else
	    fprintf(dcFile," %g/%g ",rate.first,rate.second);
	}
      }
    }
    fprintf(dcFile,"\n");
  }

  //--------------------------------------------------------------------------------
#else // CHAN_MAJOR_PROC_MINOR_ORDERING

  // all processes must have the same channels!

  // Example:
  //--------------------
  //bin           chan1    chan1    chan1   chan2    chan2    chan2
  //process       Signal   WJets      WW    Signal   WJets      WW
  //process         0        1         2      0        1         2  
  //--------------------

  // these are the signal and background loops
  fprintf(dcFile,"bin                                ");
  for (map<TString,double>::const_iterator it=processes_[0].channels.begin();
       it != processes_[0].channels.end();
       it++)
    for (int j=0; j<=jmax; j++)
      fprintf(dcFile,"%15s",it->first.Data());
  fprintf(dcFile,"\n");
  
  fprintf(dcFile,"process                            ");
  for (int k=0; k<nbins; k++)
    for (int j=0; j<=jmax; j++)
      fprintf(dcFile,"%15s",processes_[j].name.Data());
  fprintf(dcFile,"\n");

  fprintf(dcFile,"process                            ");
  for (int k=0; k<nbins; k++)
    for (int j=0; j<=jmax; j++)
      fprintf(dcFile,"%15d",processes_[j].procindex);
  fprintf(dcFile,"\n");

  fprintf(dcFile,"rate                               ");
  for (map<TString,double>::const_iterator chit=processes_[0].channels.begin();
       chit != processes_[0].channels.end();
       chit++) {
    TString channame = chit->first;
    for (int j=0; j<=jmax; j++) {
      map<TString,double>::const_iterator it=processes_[j].channels.find(channame);
      if (it==processes_[j].channels.end()) {
	cerr << "couldn't find channel " << channame << " for process " << j << endl;
	exit(-1);
      }
      fprintf(dcFile,"%15.2f",max(it->second,0.001));
    }
  }
  fprintf(dcFile,"\n");

  fprintf(dcFile,"--------------------\n");

  /****************************************
   * SYSTEMATICS
   ****************************************/

  map<TString,TString>::const_iterator sit;
  for (sit  = systematics_.begin();
       sit != systematics_.end();
       sit++) {
    const TString& name = sit->first;
    const TString& pdf  = sit->second;
    fprintf(dcFile,"%-32s %5s",name.Data(),pdf.Data());
    map<TString,double>::const_iterator chit;
    for (chit  = data_.channels.begin();
	 chit != data_.channels.end();
	 chit++) {
      for (int j=0; j<=jmax; j++) {
	const ProcData_t& pd = processes_[j];

	TString srchstr = name+":"+chit->first;
	map<TString,pair<double,double> >::const_iterator rit = pd.systrates.find(srchstr);
	if (rit == pd.systrates.end()) {
	  fprintf(dcFile,"        -      ");
	} else {
	  pair<double,double> rate = rit->second;
	  if (rate.second == 0.0)        // expect the UP (second) to contain single-sided error values
	    fprintf(dcFile,"        -      ");
	  else if (rate.first == 0.0)
	    fprintf(dcFile,"  %10.4g   ",rate.second);
	  else
	    fprintf(dcFile," %g/%g ",rate.first,rate.second);
	}
      } // proc loop
    } // chan loop

    fprintf(dcFile,"\n");

  } // syst loop

#endif

  fprintf(dcFile,"\n");
  for (size_t i=0; i<modelparams_.size(); i++) {
    fprintf(dcFile,"%-32s %s\n",modelparams_[i].name.Data(),modelparams_[i].type.Data());
  }

  fclose(dcFile);
}                                                               // Card::Print
