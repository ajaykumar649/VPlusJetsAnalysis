/*
makeLimitFile

Some important constants are set at the top of the file.
*/
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include "TFile.h"
#include "TDirectory.h"
#include "TString.h"
#include "TPRegexp.h"
#include "TObjArray.h"
#include "TObjString.h"

#include "RooWorkspace.h"
#include "RooAbsData.h"
#include "RooAbsPdf.h"
#include "RooProdPdf.h"
#include "RooRealVar.h"
#include "RooConstVar.h"

#include "card.h"
#include "hwwinputs.h"
#include "hwwutils.h"

using namespace std;

const char *wkspacename = "w_mWW";

//================================================================================

bool issignal(const TString& procname)
{
  bool issignal = procname.Contains("ignal")
#ifdef ISHWW
    || (procname.Contains("HWW")
	|| procname.Contains("ggH")
	|| procname.Contains("qq") )
#endif //ISHWW
    ;

  return issignal;
}

//================================================================================

bool getYield(RooWorkspace*w, 
	      const TString& procname,
	      const TString& channelindicator,
	      double& yield)
{
  yield = 0;

  RooRealVar * pdfint = w->var("n_"+procname+channelindicator);

  if (!pdfint) {
    cerr << "can't find integral for " << procname << endl;
    return false;
  }
  yield = pdfint->getValV();

  //pdfint->Print();

  return true;
}

//================================================================================

bool getConstraint(RooWorkspace*w, const TString& procname, double& constraint)
{
  constraint = 0.;

  if (w->pdf(procname+"_const")) {
    RooArgList l;
    w->pdf(procname+"_const")->treeNodeServerList(&l);

    //l.Print("v");

  // "at this point l has a list of 4 objects that are the constraint.
  // I can't guarantee the order of the items in the list, but you
  // are looking for the two RooConstVar variables.  One will have a
  // value of 1.0 the other will have the constraint value.  So something like this."

    for (int i = 0; i < l.getSize(); ++i) {
      if (l.at(i)->IsA() == TClass::GetClass("RooConstVar"))
	constraint += ((RooConstVar*)(l.at(i)))->getVal();
    }
    //cout << constraint << '\n';

    return true;
  }
  return false;
}

//================================================================================

Card *
makeDataCardContent(TFile *fp,
		    int massgev,
		    bool isinterp,
		    int ichan)
{
  Card *card;

  TString channame(channames[ichan]);

  char elormu = channame[ELORMUCHAR];
  //TString trigsyst   = "CMS_trigger_"+TString(elormu);
  TString leptsyst   = "CMS_eff_"+TString(elormu);

  RooWorkspace *w = (RooWorkspace *)gDirectory->Get(wkspacename);

  //w->Print();

  // The dataset

  if (!w->data("data_obs")) {
    cerr << "Couldn't find data_obs in workspace" << endl;
    exit(-1);
  }

  card = new Card(-1,"data_obs",channame,"",false);

  cout<<endl;

  // PDFs
  RooArgSet pdfs = w->allPdfs();
  TIterator* pdfit = pdfs.createIterator();

  RooArgSet params = w->allVars();
  TIterator* parit = params.createIterator();

  for(RooAbsPdf* pdf = 0;
      (pdf=(RooAbsPdf*)pdfit->Next());){

    //pdf->Print();

    TString pdfname(pdf->GetName());

    // look for a matching "n_pdf" variable.
    bool isaprocess=false;
    parit->Reset();
    for(RooRealVar* param = 0;
	(param=(RooRealVar*)parit->Next());){
    
      if (TString(param->GetName()).BeginsWith("n_"+pdfname)) {
	isaprocess=true;
	break;
      }
    }

    if (!isaprocess) continue;

    if (pdfname.EndsWith("Down")) continue; // skip the "Down"s, expect a matching "Up"

    // tokenize the pdf name to determine
    // 1. process name
    // 2. any systematic applied
    //
    TString procname(""),systname("");

    if (pdfname.EndsWith("Up")) { // This is a histogram with a systematic applied
      procname = TString(pdfname(0,pdfname.First('_')));
      systname = TString(pdfname(pdfname.First('_')+1,pdfname.Length()-pdfname.First('_')-3));
    } else
      procname = pdfname;

    double yield=0;
    if (getYield(w,procname,elormu=='e' ? "_el":"_mu",yield)) {
      cout<<"Read process="<<setw(10)<<procname<<", channel="<<channame<<", mass="<<massgev;
      if (isinterp) cout << " (interpolated)";
      if (systname.Length()) cout << ", systname = " << systname;
      
      card->addProcessChannel(yield,procname,channame,systname,issignal(procname));
    } else
      continue;

    if( issignal(procname) ) {

      // insert signal lumi and xsec systematics now

#ifdef ISHWW

      card->addSystematic("lumi_8TeV",procname,channame,1+siglumiunc);

      card->addSystematic(leptsyst,procname,channame,
			  1+sqrt(siglepteffunc*siglepteffunc + sigtrigeffunc*sigtrigeffunc));

      TString signalsyst = Form("CMS_%s_eff_sig_%dTeV", channame.Data(),beamcomenergytev);
      card->addSystematic(signalsyst,procname,channame,
#ifdef SEVENTEV
			  1.0 + (massgev < 500 ? sigselefferrpctlomass : sigselefferrpcthimass)/100.
#else
			  1.0 + (sigselefferrpct8tev)/100.
#endif
			    );

      // down/up pairs to put in card
      pair<double,double> pdfunc,scaleunc0,scaleunc1,scaleunc2,scaleunc3,ueps0,ueps1; 
    
      makeTheoretUncert4Sig(massgev,procname,pdfunc,scaleunc0,scaleunc1,scaleunc2,scaleunc3,ueps0,ueps1);

      if (procname.Contains("qq") ) { // VBF process
	
	card->addSystematic("pdf_qqbar",procname,channame,pdfunc.second);
	card->addSystematic("QCDscale_qqH",procname,channame,scaleunc0.second);

      } else { // default gg fusion

	card->addSystematic("pdf_gg",procname,channame,pdfunc.second);

	if (ichan & 1) { // odd channel, 3jet bin
	  card->addSystematic("QCDscale_ggH1in",procname,channame,scaleunc2.second);
	  card->addSystematic("QCDscale_ggH2in",procname,channame,scaleunc3.second);
	  card->addSystematic("UEPS",procname,channame,ueps1.second);
	} else { // even channel, 2jet bin
	  card->addSystematic("QCDscale_ggH",procname,channame,scaleunc0.second);
	  card->addSystematic("QCDscale_ggH1in",procname,channame,scaleunc1.second);
	  card->addSystematic("UEPS",procname,channame,ueps0.second);
	}
      }
#endif //ISHWW

    } else {  // background

      double constraint=0.;
      if (getConstraint(w,procname,constraint)) {
	// background from MC, add MC-based uncertainties
	
	card->addSystematic(procname+"_constraint",procname,channame,constraint);
	if (!procname.EqualTo("WpJ")) {
	  card->addSystematic(leptsyst,procname,channame,
			      1+sqrt(siglepteffunc*siglepteffunc + sigtrigeffunc*sigtrigeffunc));
	  card->addSystematic("lumi_8TeV",procname,channame,1+siglumiunc);
	}
      }
    }
    cout<<endl;
  }

  parit->Reset();
  for(RooRealVar* param = 0;
      (param=(RooRealVar*)parit->Next());){
    
    if (TString(param->GetName()).Contains("WpJ") &&
	!TString(param->GetName()).Contains("_nrm") &&
	!param->isConstant()) {
      //param->Print();
      card->addModelParam(param->GetName(),"flatParam");
    }
  }

  return card;

}                                                           // makeDataCardContent

//================================================================================

void
makeDataCardFiles(char *rootfn,
		  char *nametag)
{
  int imass,ichan=-1;
  bool isinterp=false;

  TString cfgtag(nametag);

  // get mass and channel from root filename, assuming a predefined format
  //
  TObjArray *subStrL = TPRegexp(perlrecapturefmt).MatchS(rootfn);

//   TString subStr;
//   for (Int_t i = 0; i < subStrL->GetLast()+1; i++) {
//     subStr = ((TObjString *)subStrL->At(i))->GetString();
//     cout << "\"" << subStr << "\" ";
//   }

  if ((subStrL->GetEntriesFast()!=5)) {
    cerr << "root filename doesn't match expected format, " << TString(rootfn) << endl;
    exit(-1);
  }

  int massgev  = ((TObjString *)subStrL->At(2))->GetString().Atoi();
  TString flav = ((TObjString *)subStrL->At(3))->GetString();
  int njets    = ((TObjString *)subStrL->At(4))->GetString().Atoi();

  cout<<"MH="<<massgev<<"GeV "<<flav<<" "<<njets<<"jets"<<endl;

  for (imass=0; imass<NUMMASSPTS; imass++) {
    int mass = masspts[imass];
    if (mass == massgev) break;
  }

#ifdef DO_INTERP
  if (imass==NUMMASSPTS) {
    for (imass=0; ; imass++) {
      int mass = interpolatedmasspts[imass];
      if (mass == massgev) break;
      if (mass < 0) break;
    }
    isinterp = (mass > 0);
  }
#endif

  if (!isinterp && imass >= NUMMASSPTS) {
    cerr << "Unknown mass read, M= " << massgev << endl;
    exit(-1);
  }
  flav.ToLower();
  if (flav == "muon") ichan=1;          // hwwmunu2j
  else if (flav == "electron") ichan=0; // hwwelnu2j
  else {
    cerr << "Unknown flavor " << flav << endl;
    exit(-1);
  }
  cout << "cfgtag = " << cfgtag << endl;

#ifdef ISHWW
  // needed for theoretical uncertainties
  readHxsTable   (Form("ggHtable%dtev.txt",beamcomenergytev));
  readHxsTable   (Form("vbfHtable%dtev.txt",beamcomenergytev)); // , scalefrom7to8tev);
  readJetBinErrTable("jetbinerrtable.txt");
#endif //ISHWW
  
  TString fname = TString(rootfn);
  TFile *fp = new TFile(fname.Data());

  if (fp->IsZombie()) {
    cerr << "Couldn't find root input file " << fname << ", skipping..." << endl;
    exit(-1);
  }

  cout << "Reading root input file " << fname << endl;
    
  Card *card = makeDataCardContent(fp,massgev,isinterp,ichan);

  card->addShapesFile(ShapesFile_t("*","*",fname,
				   TString(wkspacename)+":$PROCESS",
				   TString(wkspacename)+":$PROCESS_$SYSTEMATIC")
		      );
  TString dcardname = Form("./datacard_%dTeV_%s_%s-M=%d.txt", beamcomenergytev,
			   //outdir.Data(),
			   channames[ichan],cfgtag.Data(),massgev);

  card->Print(dcardname);

  delete card;

}                                                             // makeDataCardFiles

#ifdef MAIN
//================================================================================

#define DEBUG 1

int main(int argc, char* argv[]) {
  if (argc != 3) {
    printf("Usage: %s rootfile nametag\n",argv[0]);
    return 1;
  }
#ifdef DEBUG
  for (int i=0; i<argc; i++) printf("%s ", argv[i]);
  printf ("\n");
#endif

  makeDataCardFiles(argv[1], argv[2]);

  return 0;
}
#endif //MAIN
