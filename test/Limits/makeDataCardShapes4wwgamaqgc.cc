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
#include "wwgamaqgcinputs.h"


//================================================================================

Card *
makeDataCardContent(TFile *fp,
		    int ichan,
		    const TString& signame)
{
  Card *card;

  TH1 *datahist;
  TH1 *backhist;
  TH1 *shapehist;

  TString channame(channames[ichan]);

  char elormu = channame[ELORMUCHAR];
  TString leptsyst   = "CMS_eff_"+TString(elormu);

  datahist = (TH1 *)fp->Get(dataobjname); // only to see if it's there
  if (!datahist) {
    cerr << "Couldn't get data histogram from file for channel " << ichan << endl;
    exit(-1);
  }

  backhist = (TH1 *)fp->Get(bkgdobjname);
  if (!backhist) {
    cerr << "Couldn't get background histogram from file for channel " << ichan << endl;
    exit(-1);
  }

  TString shapesystname = Form("%s_backshape",channames[ichan]);

  shapehist = (TH1 *)fp->Get("background_"+shapesystname+"Up");
  if (!shapehist) {
    cerr << "Couldn't get background shapeUp histogram from file for channel " << ichan << endl;
    exit(-1);
  }

  TH1 *sighist = (TH1 *)fp->Get(signame);

  if (!sighist) {
    cerr<<"Couldn't get signal histogram "<<signame<<" from file for channel "<<channame<<endl;
    exit(-1);
  }

  card = new Card(-1,dataobjname,channame,"",false);

  card->addProcessChannel(sighist->Integral(),"signal",channame,"",ichan,0,1,true);
  card->addProcessChannel(backhist->Integral(),bkgdobjname,channame,shapesystname,ichan,0,1,false);

  // (non-shape) Systematics:
  card->addSystematic(leptsyst,"signal",0,
		      1+sqrt(lepteff_unc*lepteff_unc + trigeff_unc*trigeff_unc));
  card->addSystematic("MET",      "signal",0,1+met_unc);
  card->addSystematic("lumi_8TeV","signal",0,1+lumi_unc);
  card->addSystematic("PDF",      "signal",0,1+pdf_unc);
  card->addSystematic("Scale",    "signal",0,1+scale_unc);
  card->addSystematic("JER",      "signal",0,1+jer_unc);
  card->addSystematic("JES",      "signal",0,1+jes_unc);
  card->addSystematic("antibtag", "signal",0,1+antibtag_unc);
  card->addSystematic("pileup",   "signal",0,1+pileup_unc);
  card->addSystematic("mvaseleff_"+channame,"signal",0,1+sigmvaseleffunc);

#if 0 // now data-driven
  card->addSystematic(leptsyst,bkgdobjname,0,
		      1+sqrt(lepteff_unc*lepteff_unc + trigeff_unc*trigeff_unc));
  card->addSystematic("MET",      bkgdobjname,0,1+met_unc);
  card->addSystematic("lumi_8TeV",bkgdobjname,0,1+lumi_unc);
  card->addSystematic("PDF",      bkgdobjname,0,1+pdf_unc);
  card->addSystematic("Scale",    bkgdobjname,0,1+scale_unc);
  card->addSystematic("JER",      bkgdobjname,0,1+jer_unc);
  card->addSystematic("JES",      bkgdobjname,0,1+jes_unc);
  card->addSystematic("antibtag", bkgdobjname,0,1+antibtag_unc);
  card->addSystematic("pileup",   bkgdobjname,0,1+pileup_unc);
#endif

  return card;
}                                                           // makeDataCardContent

//================================================================================

void
makeDataCardFiles() // int argc, char*argv[])
{
  TString fname;
  TFile *fp = NULL;

  for (int ichan=0; ichan<NUMCHAN; ichan++) {
    
    // loop through objects in the input root file and find histograms
    // that are shape inputs into the limit setting data card
    //
    for (int i=0; i<NUMA0WPTS; i++) {
      if (strlen(a0winputfiles[ichan])) {
	fname = TString(dir)+"/"+TString(a0winputfiles[ichan]); // TString(argv[ichan+1]);
	fp = new TFile(fname);
      }

      if (!fp) continue;
      if (fp->IsZombie()) {
	cerr << "Couldn't open file " << fname << endl;
	exit(-1);
      }

      cout << "Reading root input file " << fname << endl;

      int a0w = a0W_points[i];
      TString signame = Form(signalfmtstr,"a0w",(a0w<0?"m":""),abs(a0w));
      Card *card = makeDataCardContent(fp,ichan,signame);

      card->addShapeFiles(ShapeFiles_t("data_obs",channames[ichan],fname,"data_obs"));
      card->addShapeFiles(ShapeFiles_t("signal",channames[ichan],fname,signame));
      card->addShapeFiles(ShapeFiles_t("background",channames[ichan],fname,
				       "background","$PROCESS_$SYSTEMATIC"));

      TString cfgtag = Form("wwgamaqgc_%s_a0w:%de-5",channames[ichan],a0w);

      TString dcardname("./datacard_"+cfgtag+".txt");
      
      card->Print(dcardname);
      
      delete card;
      
    } // a0w loop
    
    // loop through objects in the input root file and find histograms
    // that are shape inputs into the limit setting data card
    //
    for (int i=0; i<NUMACWPTS; i++) {
      if (strlen(aCwinputfiles[ichan])) {
	fname = TString(dir)+"/"+TString(aCwinputfiles[ichan]); // TString(argv[ichan+1]);
	fp = new TFile(fname);
      }

      if (!fp) continue;
      if (fp->IsZombie()) {
	cerr << "Couldn't open file " << fname << endl;
	exit(-1);
      }

      cout << "Reading root input file " << fname << endl;

      int aCw = aCW_points[i];
      TString signame = Form(signalfmtstr,"aCw",(aCw<0?"m":""),abs(aCw));
      Card *card = makeDataCardContent(fp,ichan,signame);

      card->addShapeFiles(ShapeFiles_t("data_obs",channames[ichan],fname,"data_obs"));
      card->addShapeFiles(ShapeFiles_t("signal",channames[ichan],fname,signame));
      card->addShapeFiles(ShapeFiles_t("background",channames[ichan],fname,
				       "background","$PROCESS_$SYSTEMATIC"));

      TString cfgtag = Form("wwgamaqgc_%s_aCw:%de-5",channames[ichan],aCw);

      TString dcardname("./datacard_"+cfgtag+".txt");
      
      card->Print(dcardname);
      
      delete card;
      
    } // aCw loop
    
    // loop through objects in the input root file and find histograms
    // that are shape inputs into the limit setting data card
    //
    for (int i=0; i<NUMLT0PTS; i++) {
      if (strlen(lt0inputfiles[ichan])) {
	fname = TString(dir)+"/"+TString(lt0inputfiles[ichan]); // TString(argv[ichan+1]);
	fp = new TFile(fname);
      }

      if (!fp) continue;
      if (fp->IsZombie()) {
	cerr << "Couldn't open file " << fname << endl;
	exit(-1);
      }

      cout << "Reading root input file " << fname << endl;

      int lt0 = lt0_points[i];
      TString signame = Form(signalfmtstr,"lt0",(lt0<0?"m":""),abs(lt0));
      Card *card = makeDataCardContent(fp,ichan,signame);

      card->addShapeFiles(ShapeFiles_t("data_obs",channames[ichan],fname,"data_obs"));
      card->addShapeFiles(ShapeFiles_t("signal",channames[ichan],fname,signame));
      card->addShapeFiles(ShapeFiles_t("background",channames[ichan],fname,
				       "background","$PROCESS_$SYSTEMATIC"));

      TString cfgtag = Form("wwgamaqgc_%s_lt0:%de-11",channames[ichan],lt0);

      TString dcardname("./datacard_"+cfgtag+".txt");
      
      card->Print(dcardname);
      
      delete card;
      
    } // lt0 loop

  } // channel loop
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
  makeDataCardFiles();
  return 0;
}
#endif
