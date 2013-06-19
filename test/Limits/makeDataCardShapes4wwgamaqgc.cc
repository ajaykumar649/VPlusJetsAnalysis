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
		    const TString& signame,
		    bool doshape)
{
  Card *card;

  TH1 *datahist;

  std::map<TString,TH1 *> backhists;

  TString channame(channames[ichan]);

  char elormu = channame[ELORMUCHAR];
  TString trigsyst    = "CMS_trig_"+TString(elormu);
  TString leptsyst    = "CMS_eff_"+TString(elormu);
  TString Wgamjetsyst = "Wgamjet_"+TString(elormu);

  datahist = (TH1 *)fp->Get(dataobjname);
  if (!datahist) {
    cerr << "Fatal: Couldn't get data histogram from file for channel " << ichan << endl;
    exit(-1);
  }
  for (int i=0; i<NUMBAKPROC; i++) {
    TH1 *backhist = (TH1 *)fp->Get(bakprochistonames[i][1]);
    if (!backhist) {
      cerr << "Warning: Couldn't get background histogram "<<bakprochistonames[i][1]<<" from file "<<fp->GetName() << endl;
    } else
      backhists[bakprochistonames[i][0]] = backhist;
  }
#if 0
  backhist = (TH1 *)fp->Get(bkgdobjname);
  if (!backhist) {
    cerr << "Fatal: Couldn't get background histogram from file for channel " << ichan << endl;
    exit(-1);
  }

  TString shapesystname = Form("%s_backshape",channames[ichan]);

  TH1 *shapehist = (TH1 *)fp->Get("background_"+shapesystname+"Up");
  if (!shapehist) {
    cerr << "Fatal: Couldn't get background shapeUp histogram from file for channel " << ichan << endl;
    exit(-1);
  }
#endif
  TH1 *sighist = (TH1 *)fp->Get(signame);

  if (!sighist) {
    cerr<<"Fatal: Couldn't get signal histogram "<<signame<<" from file for channel "<<channame<<endl;
    exit(-1);
  }

  if (doshape) {
    card = new Card(-1,dataobjname,channame,"",false);
    card->addProcessChannel(sighist->Integral(),"signal",channame,"",true);

    std::map<TString,TH1 *>::const_iterator it;
    for (it=backhists.begin(); it!=backhists.end(); it++)
      card->addProcessChannel(it->second->Integral(),it->first,channame,"",false);
  }
  else {
    // cut-and-count
    int lobin = datahist->FindFixBin(photonptmingev);
    int hibin = datahist->GetNbinsX()+1;

    //cout << lobin<<"-"<<hibin<<endl;

    card = new Card(datahist->Integral(lobin,hibin),
		    dataobjname,channame,"",false);

    card->addProcessChannel(sighist->Integral(lobin,hibin),"signal",channame,"",true);

    std::map<TString,TH1 *>::const_iterator it;
    for (it=backhists.begin(); it!=backhists.end(); it++) {
      TH1 *backhist = it->second;
      double nombakrate =  backhist->Integral( lobin, hibin );
      card->addProcessChannel(nombakrate, it->first,channame,"",false);
#if 0
      // convert shape histo to a normal systematic
      double hibakrate  = shapehist->Integral(shapehist->FindFixBin(photonptmingev),shapehist->GetNbinsX()+1);
      //card->addSystematic("backshape", bkgdobjname,channame, 1+((hibakrate-nombakrate)/nombakrate));
#endif
    }
  }

  // (non-shape) Systematics:
  card->addSystematic(leptsyst,   "signal",channame,1+lepteff_unc);
  card->addSystematic(trigsyst,   "signal",channame,1+trigeff_unc);
  card->addSystematic("MET",      "signal",channame,1+met_unc);
  card->addSystematic("lumi_8TeV","signal",channame,1+lumi_unc);
  card->addSystematic("PDF",      "signal",channame,1+pdf_unc);
  card->addSystematic("Scale",    "signal",channame,1+scale_unc);
  card->addSystematic("JER",      "signal",channame,1+jer_unc);
  card->addSystematic("JES",      "signal",channame,1+jes_unc);
  card->addSystematic("PHES",     "signal",channame,1+phes_unc);
  card->addSystematic("antibtag", "signal",channame,1+antibtag_unc);
  card->addSystematic("pileup",   "signal",channame,1+pileup_unc);

  /* DISABLE if no MVA applied, or otherwise not relevant:
   */
//  card->addSystematic("mvaseleff_"+channame,"signal",channame,1+sigmvaseleffunc);

  card->addSystematic("lumi_8TeV",zgamjet,channame,1+lumi_unc);
  card->addSystematic("lumi_8TeV",ttbgam, channame,1+lumi_unc);
  card->addSystematic("lumi_8TeV",sngltop,channame,1+lumi_unc);
  card->addSystematic("lumi_8TeV",wwgamsm,channame,1+lumi_unc);
  card->addSystematic("lumi_8TeV",wzgamsm,channame,1+lumi_unc);

  card->addSystematic("PDF",      wwgamsm,channame,1+pdf_unc);
  card->addSystematic("PDF",      wzgamsm,channame,1+pdf_unc);

  card->addSystematic("Scale",    wwgamsm,channame,1+scale_unc);
  card->addSystematic("Scale",    wzgamsm,channame,1+scale_unc);

  card->addSystematic(Wgamjetsyst, wgamjet,channame,1+wgamjet_unc[ichan]);
  card->addSystematic("FakePhUnc",fkphoton,channame,1+fkphoton_unc);
  card->addSystematic("Zgamjunc",  zgamjet,channame,1+zgamjet_unc);
  card->addSystematic("ttbgamunc",  ttbgam,channame,1+ttbgam_unc);

  if (!ichan)
    card->addSystematic("QCDunc_e",    qcd,channame,1+qcd_e_unc);

  return card;
}                                                           // makeDataCardContent

//================================================================================

void makeCards4SM(const char *parfiles[],
		  int ichan,
		  bool doshape)
{
  TString fname;
  TFile *fp = NULL;
  TString channame(channames[ichan]);

  // loop through objects in the input root file and find histograms
  // that are shape inputs into the limit setting data card
  //
  if (strlen(parfiles[ichan])) {
    fname = TString(dir)+"/"+TString(parfiles[ichan]); // TString(argv[ichan+1]);
    fp = new TFile(fname);
  }

  if (!fp) return;
  if (fp->IsZombie()) {
    cerr << "Fatal: Couldn't open file " << fname << endl;
    exit(-1);
  }

  cout << "Reading root input file " << fname << endl;

  Card *card = makeDataCardContent(fp,ichan,SMsigfmtstr,doshape);
    
  if (doshape) {
    card->addShapeFiles(ShapeFiles_t("data_obs",channame,fname,"data_obs"));
    card->addShapeFiles(ShapeFiles_t("signal",channame,fname,SMsigfmtstr));

    for (int i=0; i<NUMBAKPROC; i++) {
      TH1 *backhist = (TH1 *)fp->Get(bakprochistonames[i][1]);
      if (backhist)
	card->addShapeFiles(ShapeFiles_t(bakprochistonames[i][0],channame,fname,
					 bakprochistonames[i][1]));
    }
  }

  TString cfgtag = Form("wwgamaqgc_%s_SM",channame.Data());

  TString dcardname("./datacard_"+cfgtag+".txt");
  
  card->Print(dcardname);
      
  delete card;
}                                                                  // makeCards4SM

//================================================================================

void makeCards4param(const char *parname,
		     const char *parfiles[],
		     int  npts,
		     const int parpts[],
		     int ichan,
		     bool doshape)
{
  TString fname;
  TFile *fp = NULL;
  TString channame(channames[ichan]);

  if (strlen(parfiles[ichan])) {
    fname = TString(dir)+"/"+TString(parfiles[ichan]);
    fp = new TFile(fname);

    if (fp->IsZombie()) {
      cerr << "Fatal: Couldn't open file " << fname << endl;
      exit(-1);
    }
  } else
    return;

  cout << "Reading root input file " << fname << endl;

  for (int i=0; i<npts; i++) {
    // loop through objects in the input root file and find histograms
    // that are shape inputs into the limit setting data card
    //
    int parval = parpts[i];
    TString signame = Form(signalfmtstr,parname,(parval<0?"m":""),abs(parval));
    Card *card = makeDataCardContent(fp,ichan,signame,doshape);
    
    if (doshape) {
      card->addShapeFiles(ShapeFiles_t("data_obs",channame,fname,"data_obs"));
      card->addShapeFiles(ShapeFiles_t("signal",channame,fname,signame));

      for (int i=0; i<NUMBAKPROC; i++) {
	TH1 *backhist = (TH1 *)fp->Get(bakprochistonames[i][1]);
	if (backhist)
	  card->addShapeFiles(ShapeFiles_t(bakprochistonames[i][0],channame,fname,
					   bakprochistonames[i][1]));
      }
    }

    TString cfgtag = Form("wwgamaqgc_%s_%s:%d",channame.Data(),parname,parval);

    TString dcardname("./datacard_"+cfgtag+".txt");
      
    card->Print(dcardname);
      
    delete card;
      
  } // parval loop
}                                                               // makeCards4param

//================================================================================

void
makeDataCardFiles(bool doshape)
{
  for (int ichan=0; ichan<NUMCHAN; ichan++) {
    
    makeCards4param("a0w",a0winputfiles,NUMA0WPTS,a0W_points,ichan,doshape);
//    makeCards4param("aCw",aCwinputfiles,NUMACWPTS,aCW_points,ichan,doshape);
//    makeCards4param("lt0",lt0inputfiles,NUMLT0PTS,lt0_points,ichan,doshape);
//    makeCards4param("K0W",K0Winputfiles,NUMK0WPTS,K0W_points,ichan,doshape);

//    makeCards4SM(SMinputfiles,ichan,doshape);

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
  makeDataCardFiles(argc <= 1);
  return 0;
}
#endif
