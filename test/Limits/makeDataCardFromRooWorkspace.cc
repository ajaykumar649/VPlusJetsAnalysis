/*
makeLimitFile

Some important constants are set at the top of the file.
*/
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include "TFile.h"
#include "TDirectory.h"
#include "TString.h"

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

bool getYield(RooWorkspace*w, const TString& procname, double& yield)
{
  yield = 0;

  RooRealVar * pdfint = w->var("n_"+procname);

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
		    int imass,
		    bool isinterp,
		    int ichan)
{
  Card *card;

  TString channame(channames[ichan]);
  int massgev=isinterp ? interpolatedmasspts[imass] : masspts[imass];

  char elormu = channame[ELORMUCHAR];
  //TString trigsyst   = "CMS_trigger_"+TString(elormu);
  TString leptsyst   = "CMS_eff_"+TString(elormu);

  RooWorkspace *w = (RooWorkspace *)gDirectory->Get("w");

  //w->Print();

  // The dataset

  if (!w->data("data_obs")) {
    cerr << "Couldn't find data_obs in workspace" << endl;
    exit(-1);
  }

  card = new Card(-1,"data_obs","",channame,false);

  cout<<endl;

  // PDFs
  RooArgSet pdfs = w->allPdfs();
  TIterator* pit = pdfs.createIterator();
  

  for(RooAbsPdf* pdf = 0;
      (pdf=(RooAbsPdf*)pit->Next());){

    if (pdf->IsA() == RooProdPdf::Class()) {
      //pdf->Print();

      TString pdfname(pdf->GetName());

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
      if (getYield(w,procname,yield)) {
	cout<<"Read process="<<setw(10)<<procname<<", channel="<<channame<<", mass="<<massgev;
	if (isinterp) cout << " (interpolated)";
	if (systname.Length()) cout << ", systname = " << systname;

	card->addProcessChannel(yield,procname,systname,ichan,0,1,issignal(procname));
      } else
	continue;

      if( issignal(procname) ) {

	// insert signal lumi and xsec systematics now

#ifdef ISHWW

	card->addSystematic("lumi_8TeV",procname,0,1+siglumiunc);

	card->addSystematic(leptsyst,procname,0,
			    1+sqrt(siglepteffunc*siglepteffunc + sigtrigeffunc*sigtrigeffunc));

	TString signalsyst = Form("CMS_%s_eff_sig_%dTeV", channame.Data(),beamcomenergytev);
	card->addSystematic(signalsyst,procname,0,
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

	  card->addSystematic("pdf_qqbar",procname,0,pdfunc.second);
	  card->addSystematic("QCDscale_qqH",procname,0,scaleunc0.second);

	} else { // default gg fusion

	  card->addSystematic("pdf_gg",procname,0,pdfunc.second);

	  if (ichan & 1) { // odd channel, 3jet bin
	    card->addSystematic("QCDscale_ggH1in",procname,0,scaleunc2.second);
	    card->addSystematic("QCDscale_ggH2in",procname,0,scaleunc3.second);
	    card->addSystematic("UEPS",procname,0,ueps1.second);
	  } else { // even channel, 2jet bin
	    card->addSystematic("QCDscale_ggH",procname,0,scaleunc0.second);
	    card->addSystematic("QCDscale_ggH1in",procname,0,scaleunc1.second);
	    card->addSystematic("UEPS",procname,0,ueps0.second);
	  }
	}
#endif //ISHWW

      } else {  // background

	double constraint=0.;
	if (getConstraint(w,procname,constraint)) {
	  // background from MC, add MC-based uncertainties

	  card->addSystematic(procname+"_xs_unc",procname,0,constraint);
	  card->addSystematic(leptsyst,procname,0,
			      1+sqrt(siglepteffunc*siglepteffunc + sigtrigeffunc*sigtrigeffunc));
	  card->addSystematic("lumi_8TeV",procname,0,1+siglumiunc);
	}
      }
      cout<<endl;
    }
  }

  RooArgSet params = w->allVars();
  pit = params.createIterator();
  for(RooRealVar* param = 0;
      (param=(RooRealVar*)pit->Next());){
    
    if (TString(param->GetName()).Contains("WpJ") &&!param->isConstant()) {
      //param->Print();
      card->addModelParam(param->GetName(),"flatParam");
    }
  }

  return card;

}                                                           // makeDataCardContent

//================================================================================

void
makeDataCardFiles(int imass, bool isinterp, char*nametag)
{
  TString cfgtag(nametag);

  int massgev=isinterp ? interpolatedmasspts[imass] : masspts[imass];

  cout << "cfgtag = " << cfgtag << endl;

#ifdef ISHWW
  // needed for theoretical uncertainties
  readHxsTable   (Form("ggHtable%dtev.txt",beamcomenergytev));
  readHxsTable   (Form("vbfHtable%dtev.txt",beamcomenergytev)); // , scalefrom7to8tev);
  readJetBinErrTable("jetbinerrtable.txt");
#endif //ISHWW

  
  for (int ichan=0; ichan<NUMCHAN; ichan++) {
    TString fname = TString(dir) + "/" + Form(inputfilesfmtstr[ichan],massgev);
    cout << "Reading files from directory: " << dir << endl;
    TFile *fp = new TFile(fname.Data());

    if (fp->IsZombie()) {
      cerr << "Couldn't find root input file " << fname << ", skipping..." << endl;
      continue;
    }

    cout << "Reading root input file " << fname << endl;
    
    Card *card = makeDataCardContent(fp,imass,isinterp,ichan);

    card->addShapeFiles(ShapeFiles_t("*","*",fname,
				     "w:$PROCESS",
				     "w:$PROCESS_$SYSTEMATIC")
		      );
    TString dcardname = Form("./datacard_%dTeV_%s_%s-M=%d.txt", beamcomenergytev,
			     //outdir.Data(),
			     channames[ichan],cfgtag.Data(),massgev);

    card->Print(dcardname);

    delete card;

  } // channel loop
}                                                             // makeDataCardFiles

#ifdef MAIN
//================================================================================

#define DEBUG 1

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Usage: %s nametag\n",argv[0]);
    return 1;
  }
#ifdef DEBUG
  for (int i=0; i<argc; i++) printf("%s ", argv[i]);
  printf ("\n");
#endif

  //int imass=11;
  for (int imass=0; imass<NUMMASSPTS; imass++) {
    makeDataCardFiles(imass, false, argv[1]);
  }
#ifdef DO_INTERP
  for (int imass=0; ; imass++) {
    int mass = interpolatedmasspts[imass];
    if (mass < 0) break;
    makeDataCardFiles(imass, true, argv[1]);
  }
#endif

  return 0;
}
#endif //MAIN
