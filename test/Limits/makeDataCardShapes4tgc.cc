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

#include "card.h"
#include "atgcinputs.h"


//================================================================================
#if 0
bool calcEstimatedLimit(const Card& card)
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
#endif

//================================================================================

Card *
makeDataCardContent(TFile *fp,
		    const TString& channame,
		    const TString& signame)
{
  Card *card;

  TH1 *datahist;
  TH1 *backhist;
  TH1 *shapehist;

  char elormu = channame[ELORMUCHAR];
  TString leptsyst   = "CMS_eff_"+TString(elormu);
  TString trigsyst   = "CMS_trigger_"+TString(elormu);
  TString sigXSsyst  = "sigUncXS";

  datahist = (TH1 *)fp->Get(dataobjname);
  if (!datahist) {
    cerr << "Couldn't get data histogram from file for channel " << channame << endl;
    exit(-1);
  }

  backhist = (TH1 *)fp->Get(bkgdobjname);
  if (!backhist) {
    cerr << "Couldn't get background histogram from file for channel " << channame << endl;
    exit(-1);
  }

  TString shapesystname = Form("%s_backshape",channame.Data());

  shapehist = (TH1 *)fp->Get("background_"+shapesystname+"Up");
  if (!shapehist) {
    cerr << "Couldn't get background shapeUp histogram from file for channel " << channame << endl;
    exit(-1);
  }

  TH1 *sighist = (TH1 *)fp->Get(signame);

  if (!sighist) {
    cerr<<"Couldn't get signal histogram "<<signame<<" from file for channel "<<channame<<endl;
    //exit(-1);
    return NULL;
  }

  card = new Card(-1,dataobjname,channame,"",false);
  card->addProcessChannel(sighist->Integral(),"signal",channame,"",true);
  card->addProcessChannel(backhist->Integral(),bkgdobjname,channame,shapesystname,false);

  // (non-shape) Systematics:
  card->addSystematic(leptsyst,"signal",channame,1+siglepteffunc);
  card->addSystematic(trigsyst,"signal",channame,1+sigtrigeffunc);
  card->addSystematic("lumi_8TeV","signal",channame,1+siglumiunc);
  card->addSystematic("sigXSsyst","signal",channame,1+signal_xs_unc);

  return card;
}                                                           // makeDataCardContent

//================================================================================

void
makeDataCardFiles(bool doshape) // int argc, char*argv[])
{
  TFile *fp;

  TString fname;

#if 0
  if (argc != NUMCHAN+1) {
    cerr << "Need " << NUMCHAN << " input root files, one for each channel" << endl;
    exit(-1);
  }
#endif

  for (int ichan=0; ichan<NUMCHAN; ichan++) {
    fname = TString(dir)+"/"+TString(inputfiles[ichan]); // TString(argv[ichan+1]);
    fp = new TFile(fname);

    TString channame(channames[ichan]);

    if (fp->IsZombie()) {
      cerr << "Couldn't open file " << fname << endl;
      exit(-1);
    }

    cout << "Reading root input file " << fname << endl;

    // loop through objects in the input root file and find histograms
    // that are shape inputs into the limit setting data card
    //
    for (float lambdaz=LAMBDAZ_MIN;
	 lambdaz<=LAMBDAZ_MAX+LAMBDAZ_INC/1000;
	 lambdaz+= LAMBDAZ_INC) {

      //float deltaKappaGamma=0;
      for (float deltaKappaGamma=dKG_MIN;
	   deltaKappaGamma<=dKG_MAX+dKG_INC/1000;
	   deltaKappaGamma += dKG_INC) {

	//+INC/1000 to avoid truncation
	TString cfgtag = Form(signalfmtstr_lzvsdkg,
			      lambdaz+LAMBDAZ_INC/1000.,
			      deltaKappaGamma+dKG_INC/1000.);
	TString signame = "signal_"+cfgtag;

	Card *card = makeDataCardContent(fp,channame,signame);

	//if (calcEstimatedLimit(card))
	if (card)
	{
	  // assumes the channel filenames are in the same order as the channels!!
	  card->addShapesFile(ShapesFile_t("data_obs",channame,fname,"data_obs"));
	  card->addShapesFile(ShapesFile_t("signal",channame,fname,signame));
	  card->addShapesFile(ShapesFile_t("background",channame,fname,
					   "background","background_$SYSTEMATIC"));

	  //+INC/1000 to avoid truncation
	  cfgtag = Form("lz_%.3f_dkg_%.2f_%s",
			lambdaz+LAMBDAZ_INC/1000.,
			deltaKappaGamma+dKG_INC/1000.,
			channame.Data());
	  TString dcardname("./datacard_"+cfgtag+".txt");
	  card->Print(dcardname);
	}
      } // dKG loop

      for (float deltaG1=dg1_MIN;
	   deltaG1<=dg1_MAX+dg1_INC/1000;
	   deltaG1 += dg1_INC) {

	//+INC/1000 to avoid truncation
	TString cfgtag = Form(signalfmtstr_lzvsdg1,
			      lambdaz+LAMBDAZ_INC/1000.,
			      deltaG1+dg1_INC/1000.);
	TString signame = "signal_"+cfgtag;
	
	Card *card = makeDataCardContent(fp,channame,signame);

	//if (calcEstimatedLimit(card))
	if (card)
	{
	  // assumes the channel filenames are in the same order as the channels!!
	  card->addShapesFile(ShapesFile_t("data_obs",channame,fname,"data_obs"));
	  card->addShapesFile(ShapesFile_t("signal",channame,fname,signame));
	  card->addShapesFile(ShapesFile_t("background",channame,fname,
					   "background","background_$SYSTEMATIC"));
	  //+INC/1000 to avoid truncation
	  cfgtag = Form("lz_%.3f_dg1_%.3f_%s",
			lambdaz+LAMBDAZ_INC/1000.,
			deltaG1+dg1_INC/1000.,
			channame.Data());
	  TString dcardname("./datacard_"+cfgtag+".txt");
	  card->Print(dcardname);
	}
      } // dg1 loop
    } // lambdaz loop


    for (float deltaKappaGamma=dKG_MIN;
	 deltaKappaGamma<=dKG_MAX+dKG_INC/1000;
	 deltaKappaGamma += dKG_INC)
    { 
      for (float deltaG1=dg1_MIN;
	   deltaG1<=dg1_MAX+dg1_INC/1000;
	   deltaG1 += dg1_INC) { 
	//+INC/1000 to avoid truncation
	TString cfgtag = Form(signalfmtstr_dkgvsdg1,
			      deltaKappaGamma+dKG_INC/1000.,
			      deltaG1+dg1_INC/1000.
			      );
	TString signame = "signal_"+cfgtag;

	Card *card = makeDataCardContent(fp,channame,signame);

	//if (calcEstimatedLimit(card))
	if (card)
	{
	  // assumes the channel filenames are in the same order as the channels!!
	  card->addShapesFile(ShapesFile_t("data_obs",channame,fname,"data_obs"));
	  card->addShapesFile(ShapesFile_t("signal",channame,fname,signame));
	  card->addShapesFile(ShapesFile_t("background",channame,fname,
					   "background","background_$SYSTEMATIC"));

	  //+INC/1000 to avoid truncation
	  cfgtag = Form("dkg_%.2f_dg1_%.3f_%s",
			deltaKappaGamma+dKG_INC/1000.,
			deltaG1+dg1_INC/1000.,
			channame.Data());
	  TString dcardname("./datacard_"+cfgtag+".txt");
	  card->Print(dcardname);
	}
      } // dg1 loop
    } // dKG loop
  } // channel loop

}                                                             // makeDataCardFiles

//================================================================================

#ifdef MAIN
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
