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
#include <climits>
#include <stdio.h>
#include <stdlib.h>
#include "TFile.h"
#include "TH1.h"
#include "TF1.h"
#include "TDirectory.h"
#include "TObjString.h"
#include "TPRegexp.h"
#include "TObjArray.h"
#include "TKey.h"
#include "TClass.h"

using namespace std;

#include "card.h"
#include "hwwinputs.h"
//#include "hwwinputs_rectcut2.h"
#include "hwwutils.h"
//#include "mjjinputs.h"

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

int
tokNameGetInfo(const TString& hname,
	       TString& prefix,
	       TString& procname,
	       TString& systname)
{

  // use "strtok" because I can stop tokenizing in mid-string
  //x
  TObjArray *tokens = hname.Tokenize("_");

  int ntok= tokens->GetEntriesFast();
  assert(ntok>=2);

  prefix = ((TObjString *)(*tokens)[0])->GetString();
  procname = ((TObjString *)(*tokens)[1])->GetString();

  if (ntok==3 && hname.Contains("Up")) { // This is a histogram with a systematic applied
    systname = ((TObjString *)(*tokens)[2])->GetString().Chop().Chop();
  } else if (ntok == 4 && hname.Contains("Up")) {
    systname =
      ((TObjString *)(*tokens)[2])->GetString() + "_" +
      ((TObjString *)(*tokens)[3])->GetString().Chop().Chop();
  }

  cout<<"Read process="<<setw(10)<<procname;
  if (systname.Length()) cout << ", systname = " << systname;

  return 1;
}                                                                // tokNameGetInfo

//================================================================================

void addSystematics(int                massgev,
		    Card              *card,
		    const TString&     procname,
		    const TString&     channame,
		    int                ichanref)
{
  char elormu = channame[ELORMUCHAR];
  //TString trigsyst   = "CMS_trigger_"+TString(elormu);
  TString leptsyst   = "CMS_eff_"+TString(elormu);

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

      if (channame.Contains("3j")) { //3jet bin
	//card->addSystematic("QCDscale_ggH1in",procname,channame,scaleunc2.second);
	//card->addSystematic("QCDscale_ggH2in",procname,channame,scaleunc3.second);
	card->addSystematic("UEPS",procname,channame,ueps1.second);
      } else { // even channel, 2jet bin
	//card->addSystematic("QCDscale_ggH",procname,channame,scaleunc0.second);
	//card->addSystematic("QCDscale_ggH1in",procname,channame,scaleunc1.second);
	card->addSystematic("UEPS",procname,channame,ueps0.second);
      }
    }
#endif //ISHWW

  } else {  // background

    TString bckgrdsyst = Form("CMS_%s_norm_back_%dTeV",channame.Data(),beamcomenergytev);
    
    int imass2use = findMasspt2use(massgev);
    int index     = imass2use*NUMCHAN+ichanref;

    card->addSystematic(bckgrdsyst,procname,channame,1.01); // backnormerr[index]);
  }
  cout<<endl;
}                                                                // addSystematics

//================================================================================

Card *
makeDataCardContent(const TString& fname,
		    TFile *fp, 
		    int massgev,
		    bool isinterp,
		    int ichan)
{
  Card *card = NULL;

  TString channame = channames[ichan];

  TIter nextkey( gDirectory->GetListOfKeys() );
  TKey *key;

  // loop through objects in the input root file and find histograms
  // that are shape inputs into the limit setting data card
  //
  while ( (key = (TKey*)nextkey())) {

    TObject *obj = key->ReadObj();

    if ( !obj->IsA()->InheritsFrom( "TH1" ) )
      continue;

    TH1 *h1 = (TH1*)obj;
    TString hname(h1->GetName());

    if (hname.EndsWith("Down")) continue; // skip the "Down"s, expect a matching "Up"

    // tokenize the histo name to determine
    // 1. process name
    // 2. any systematic applied
    //
    TString prefix(""), procname(""),systname("");

    if (!tokNameGetInfo(hname, prefix, procname,systname)) {
      cout << "...skipping."  << endl;
      continue;
    }

    double yield = h1->Integral(); // the yield for this channel

    // insert into existing cards data map:

    if (!card) {
      card  = new Card(yield,procname,channame,systname,issignal(procname));

    } else {                                                 // existing masspoint

      card->addProcessChannel(yield,procname,channame,systname,issignal(procname));

    } // existing masspoint

    if (procname.Contains("data"))
      card->addShapesFile(ShapesFile_t("data_obs",channame,fname,hname));
    else {
      addSystematics(massgev,card,procname,channame,ichan);

      if (!systname.Length())
	card->addShapesFile(ShapesFile_t(procname,channame,fname,
					 prefix+"_$PROCESS",prefix+"_$PROCESS_$SYSTEMATIC"));

    }

    cout  << endl;
  } // key loop

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

  TString infname=TString(rootfn);
  TFile *fp = new TFile(infname);
  
  if (fp->IsZombie()) {
    cerr << "Couldn't open file " << infname << endl;
    exit(-1);
  }

  Card *card = makeDataCardContent(infname,fp,massgev,isinterp,ichan);

  TString dcardname = Form("./datacard_%dTeV_%s_%s-M=%d.txt", beamcomenergytev,
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

  //hwwshapes(argv[1],"hww-histo-shapes-TH1.root");

  makeDataCardFiles(argv[1], argv[2]);
  return 0;
}
#endif //MAIN
