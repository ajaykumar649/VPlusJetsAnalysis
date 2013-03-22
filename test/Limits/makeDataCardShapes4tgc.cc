/*
makeLimitFile

Some important constants are set at the top of the file.
*/
#include <assert.h>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "TFile.h"
#include "TH1.h"
#include "TF1.h"
#include "TDirectory.h"
#include "TObjString.h"
#include "TObjArray.h"
#include "TKey.h"
#include "TClass.h"

using namespace std;

#include "dcutils.C"

#include "atgcinputs.h"


//================================================================================

bool calcEstimatedLimit(const CardData_t& card)
{
  double totback = 0.0, totsig=0.0;

  std::map<TString,int>::const_iterator it;
  for (it= card.pname2index.begin(); it != card.pname2index.end(); it++)  {
    const ProcData_t& pd = card.processes[it->second];
    std::map<TString,double>::const_iterator itchan;
    if (pd.procindex > 0) { // background
      for (itchan = pd.channels.begin(); itchan != pd.channels.end(); itchan++)
	totback += itchan->second;
    } else {
      for (itchan = pd.channels.begin(); itchan != pd.channels.end(); itchan++) {
	if (itchan->second < 0.005) {
	  cerr << "signal contribution for channel " << itchan->first << " is too small, skipping" << endl;
	  return false;
	}
	totsig += itchan->second;
      }
    }
  }

  double estlimit = 1.92 * sqrt(totback)/totsig;

  printf("%7.1f %7.2f %5.2f %5.2f\n", 
	 totback,totsig,estlimit,estlimit*3);

  return (true);
}                                                            // calcEstimatedLimit

//================================================================================

CardData_t 
makeNewCard(TH1           *inhist,
	    const TString& procname,
	    const TString& systname,
	    const int      ichan,
	    const int      nchan,
	    bool           doshape
	    )
{
  CardData_t card;

  card.nbackproc = 0;
  card.nsigproc  = 0;

  //cout << "\tmake new card ";

  // cannot start a new card with a systematic histo
  assert(!systname.Length());

  const pair<double,double> zeropair(0.0,0.0);

  char elormu = channames[ichan][0];
  TString trigsyst   = "CMS_trigger_"+TString(elormu);
  TString leptsyst   = "CMS_eff_"+TString(elormu);
  TString sigXSsyst  = "sigUncXS";

  card.systematics[trigsyst]       = "lnN"; // common across same-flavor channels
  card.systematics[leptsyst]       = "lnN"; // common across same-flavor channels
  card.systematics["lumi"]         = "lnN"; // common across channels
  card.systematics[sigXSsyst]      = "lnN";

  ProcData_t pd;

  pair<TString,double> channel;

  pd.name        = procname;
  channel.first  = channames[ichan];

  if (doshape)
    channel.second = inhist->Integral(); // the yield for this channel
  else
    channel.second = inhist->Integral(inhist->FindFixBin(dijetptmingev),
				      inhist->GetNbinsX()+1);

  pd.channels.insert(channel);

  if( procname.Contains("data") ) {
    card.data = pd; // done.
  } else {

    if( procname.Contains("ignal") ) {                              // signal

      card.nsigproc++;

      pd.procindex = 1-card.nsigproc; /* process index for signal processes required to be distinct,
					 as well as 0 or negative */

      // insert signal lumi and xsec systematics now

      pair<double,double> lumipair(0.0, 1+siglumiunc);

      pd.systrates["lumi"].resize(nchan,lumipair);
      pd.systrates[trigsyst].resize(nchan,zeropair);
      pd.systrates[trigsyst][ichan].second = 1+sigtrigeffunc;
      pd.systrates[leptsyst].resize(nchan,zeropair);
      pd.systrates[leptsyst][ichan].second = 1+siglepteffunc;
      pd.systrates[sigXSsyst].resize(nchan,zeropair);
      pd.systrates[sigXSsyst][ichan].second = 1+signal_xs_unc;

    } else {                                                        //background
      card.nbackproc++;
      pd.procindex = card.nbackproc;
    }

    card.processes.push_back(pd);
    card.pname2index[procname]= 0;

  } // else not data

  return card;
}                                                                   // makeNewCard

//================================================================================

void
addToCard(CardData_t&    card,
	  TH1           *inhist,   // input histogram
	  const TString& procname, // process name 
	  const TString& systname, // name of (shape) systematic applied
	  const int      ichan,    // channel index
	  const int      nchan,    // number of channels in card
	  bool           doshape=true
	  )
{
  //cout << "\tadd to card ";

  // With each input histogram one must:
  // 1. If a new process, update the process info in the card: "card.processes", "card.pname2index",
  // 2. Update new channel information "card.processes[procindex].channels" (channel name/rate pairs)
  // 3. Update the systematics information as necessary:
  //    if systname.length, add shape systematic information to
  //    card.systematics (if new systematic), card.processes[procindex].systrates[systname][ichan]
  // 
  pair<TString,double> channel;

  const pair<double,double> zeropair(0.0,0.0);

  TString channame(channames[ichan]);

  channel.first  = channame;

  if (doshape)
    channel.second = inhist->Integral(); // the yield for this channel
  else
    channel.second = inhist->Integral(inhist->FindFixBin(dijetptmingev),
				      inhist->GetNbinsX()+1);

  char elormu = channame[0];
  TString trigsyst   = "CMS_trigger_"+TString(elormu);
  TString leptsyst   = "CMS_eff_"+TString(elormu);
  TString sigXSsyst  = "sigUncXS";

  card.systematics[trigsyst]     = "lnN"; // common across same-flavor channels
  card.systematics[leptsyst]     = "lnN"; // common across same-flavor channels
  card.systematics[sigXSsyst]    = "lnN";

  if( procname.Contains("data") )         // data observation

    if (!card.data.name.Length()) {             // first channel of data encountered
      ProcData_t pd;
      pd.name = procname;
      pd.channels.insert(channel);
      card.data = pd;
    }else{                                      // another channel for data, possibly
      assert(!card.data.name.CompareTo(procname)); // must be the same
      card.data.channels.insert(channel);
    }

  else if( procname.Contains("ignal") ) { // signal expectation

    assert(!systname.Length());     // shape based systematics for signal not implemented yet

    pair<double,double> lumipair(0.0, 1+siglumiunc);

    map<TString,int>::iterator pit;
    pit = card.pname2index.find(procname);
    if (pit == card.pname2index.end()) {    // new signal process, first channel encountered
      card.nsigproc++;

      ProcData_t pd;
      pd.name      = procname;
      pd.procindex = 1-card.nsigproc; /* process index for signal processes required to be distinct,
					 as well as 0 or negative */

      pd.channels.insert(channel);

      pd.systrates["lumi"].resize(nchan,lumipair);
      pd.systrates[trigsyst].resize(nchan,zeropair);
      pd.systrates[trigsyst][ichan].second = 1.0+sigtrigeffunc;
      pd.systrates[leptsyst].resize(nchan,zeropair);
      pd.systrates[leptsyst][ichan].second = 1+siglepteffunc;
      pd.systrates[sigXSsyst].resize(nchan,zeropair);
      pd.systrates[sigXSsyst][ichan].second = 1+signal_xs_unc;

      // put new signal in front, have to adjust the mapped indices for all the rest.
      // This maintains the proper ordering of processes in the datacard (for LandS)
      //
      for (pit = card.pname2index.begin(); pit != card.pname2index.end(); pit++)
	pit->second++;

      card.processes.push_front(pd);

      card.pname2index[pd.name] = 0;

    } else {                                // another channel for signal, presumably
      ProcData_t& pd = card.processes[pit->second];
      assert(pd.name.Length());             // process should exist here
      assert(!pd.name.CompareTo(procname)); // must be the same
      pd.channels.insert(channel);

      // has this signal systematic been initialized for this process?
      map<TString,vector<pair<double,double> > >::const_iterator rit = pd.systrates.find(trigsyst);
      if (rit == pd.systrates.end()) { //  no
	pd.systrates[trigsyst].resize(nchan,zeropair);
      }
      pd.systrates[trigsyst][ichan].second   = 1.0 + sigtrigeffunc;

      // has this signal systematic been initialized for this process?
      rit = pd.systrates.find(leptsyst);
      if (rit == pd.systrates.end()) { //  no
	pd.systrates[leptsyst].resize(nchan,zeropair);
      }
      pd.systrates[leptsyst][ichan].second   = 1.0 + siglepteffunc;

      // has this signal systematic been initialized for this process?
      rit = pd.systrates.find(sigXSsyst);
      if (rit == pd.systrates.end()) { //  no
	pd.systrates[sigXSsyst].resize(nchan,zeropair);
      }
      pd.systrates[sigXSsyst][ichan].second   = 1.0 + signal_xs_unc;
    }

  } else {                               // background process

    map<TString,int>::iterator pit;
    pit = card.pname2index.find(procname);
    if (pit == card.pname2index.end()) {    // first channel of this background process encountered

      assert(!systname.Length()); // cannot encounter systematic histo before nominal histo

      card.nbackproc++;

      ProcData_t pd;
      pd.name = procname;
      pd.procindex = card.nbackproc;
      pd.channels.insert(channel);

      card.pname2index[pd.name] = (int)card.processes.size();
      card.processes.push_back(pd);

    } else {                                /* either another channel, or a shape
					       systematic for an existing channel */
      ProcData_t& pd = card.processes[pit->second];

      if (systname.Length()) {
	if (doshape) {
	  // a shape-based limit, all channels get a factor of 0.0
	  card.systematics[systname] = "shape";
	  pd.systrates[systname].resize(nchan,zeropair);
	  pd.systrates[systname][ichan].second = 1.0; // except the current channel
	} else {
	  // convert shape histo to a normal systematic
	  std::map<TString,double>::const_iterator itchan;
	  itchan = pd.channels.find(channame);
	  assert(itchan != pd.channels.end());
	  double nomrate = itchan->second;
	  card.systematics[systname] = "lnN";
	  pd.systrates[systname].resize(nchan,zeropair);
	  pd.systrates[systname][ichan].second = 1+((channel.second-nomrate)/nomrate);
	}
      }
      else {
	assert(pd.name.Length());             // process should exist here
	assert(!pd.name.CompareTo(procname)); // and be named the same
	pd.channels.insert(channel);
      }
    }
  }
}                                                                     // addToCard

//================================================================================

void
makeDataCardFiles(bool doshape) // int argc, char*argv[])
{
  TFile *fps[NUMCHAN];

  TString fnames[NUMCHAN];

#if 0
  if (argc != NUMCHAN+1) {
    cerr << "Need " << NUMCHAN << " input root files, one for each channel" << endl;
    exit(-1);
  }
#endif

  for (int ichan=0; ichan<NUMCHAN; ichan++) {
    fnames[ichan] = TString(dir)+"/"+TString(inputfiles[ichan]); // TString(argv[ichan+1]);
    fps[ichan] = new TFile(fnames[ichan]);
    if (fps[ichan]->IsZombie()) {
      cerr << "Couldn't open file " << fnames[ichan] << endl;
      exit(-1);
    }
  }

  TH1 *datahists[NUMCHAN];
  TH1 *backhists[NUMCHAN];
  TH1 *shapehists[NUMCHAN];

  for (int ichan=0; ichan<NUMCHAN; ichan++) {
    datahists[ichan] = (TH1 *)fps[ichan]->Get("data_obs");
    if (!datahists[ichan]) {
      cerr << "Couldn't get data histogram from file for channel " << ichan << endl;
      exit(-1);
    }
    backhists[ichan] = (TH1 *)fps[ichan]->Get("background");
    if (!backhists[ichan]) {
      cerr << "Couldn't get background histogram from file for channel " << ichan << endl;
      exit(-1);
    }

    shapehists[ichan] = (TH1 *)fps[ichan]->Get(Form("background_%s_backshapeUp",channames[ichan]));
    if (!shapehists[ichan]) {
      cerr << "Couldn't get background shapeUp histogram from file for channel " << ichan << endl;
      exit(-1);
    }
  }

  // loop through objects in the input root file and find histograms
  // that are shape inputs into the limit setting data card
  //
  for (float lambdaz=LAMBDAZ_MIN; lambdaz<=LAMBDAZ_MAX; lambdaz+= LAMBDAZ_INC) {
    for (float deltaKappaGamma=dKG_MIN; deltaKappaGamma<=dKG_MAX; deltaKappaGamma += dKG_INC) {

      TString cfgtag = Form(signalfmtstr,lambdaz+LAMBDAZ_INC/100.,deltaKappaGamma+dKG_INC/100.);
      TString signame = "signal_"+cfgtag;

      CardData_t card = makeNewCard(datahists[0],"data","",0,NUMCHAN,doshape);

      for (int ichan=0; ichan<NUMCHAN; ichan++) {
	TH1 *sighist = (TH1 *)fps[ichan]->Get(signame);

	TString channame(channames[ichan]);

	if (!sighist) {
	  cerr<<"Couldn't get signal histogram "<<signame<<" from file for channel "<<channame<<endl;
	  //exit(-1);
	  goto nextone;
	}

	if (doshape) {
	  // assumes the channel filenames are in the same order as the channels!!
	  card.shapespecs.push_back(ShapeFiles_t("signal",channame,fnames[ichan],signame));
	  card.shapespecs.push_back(ShapeFiles_t("data_obs",channame,fnames[ichan],"data_obs"));
	  card.shapespecs.push_back(ShapeFiles_t("background",channame,fnames[ichan],
						 "background","background_$SYSTEMATIC"));
	}

	if (ichan)
	  addToCard(card,datahists[ichan],"data","",ichan,NUMCHAN,doshape);

	addToCard(card,backhists[ichan],"background","",ichan,NUMCHAN,doshape);
	addToCard(card,shapehists[ichan],"background",
		  Form("%s_backshape",channame.Data()),ichan,NUMCHAN,doshape);
	addToCard(card,sighist,"signal","",ichan,NUMCHAN,doshape);

      } // channel loop

      //if (calcEstimatedLimit(card))
      {
	cfgtag = Form("lz%.3f_dkg%.2f",lambdaz+LAMBDAZ_INC/100.,deltaKappaGamma+dKG_INC/100.);
	fmtDataCardFile(0,card,cfgtag);
      }
    nextone:
      ;
    } // dKG loop
  } // lambdaz loop

}                                                             // makeDataCardFiles

#ifdef MAIN
//================================================================================

#define DEBUG 1

int main(int argc, char* argv[]) {

#if 0
  if (argc<2) {
    printf("Usage: %s [do-cut-and-count]\n",argv[0]);
    return 1;
  }
#endif
#ifdef DEBUG
  for (int i=0; i<argc; i++) printf("%s ", argv[i]);
  printf ("\n");
#endif

  // exactly one arg is nominal,
  // more than one means suppress shape info in the card
  // for a cut-and-count limit
  //
  makeDataCardFiles(argc <= 1);
  return 0;
}
#endif
