/*//////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

Channel: WW+gamma semileptonic Muon channel (W -> uv, W -> jj, gamma)

Usage: Reads in multiple ROOT files (RD Trees) representing data, MC
       signal, and background.  The background normalization is done
       using theoretical cross sections, observed luminosity, and
       sample sizes (user can also add K-factors, etc.).  User
       specifies kinematical distribution to observe, as well as
       histogram range and binning.  User can also specify the
       Systematic/Statistical uncertainty.

Output: ROOT file containing 1D histograms for:
	(1) Observed data (data_obs)
	(2) SM backgrounds + SM signal (background)
	(3) Background + uncertainty (background_mudijet_backshapeUp)
	(4) Background - uncertainty (background_mudijet_backshapeDown)
	(5-?) Anomalous signal - SM signal (signal_??)

Syntax: root -l -b -q mkROOTaqgc.C

///////////////////////////////////////////////////////////////////////
*//////////////////////////////////////////////////////////////////////


/////////////////////
// Load header files:
#include <iostream>
#include "TLatex.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH1F.h"
#include "THStack.h"
#include "TString.h"
#include "TLegend.h"
#include "TLine.h"
#include "TPad.h"
#include "TCanvas.h"


///////////////////////////////////////////
// Define Type to store histogram settings:
struct plotVar_t {
  char* plotvar;
  double MINRange;
  double MAXRange;
  int    NBINS;
  int    slog;
  char* xlabel;
};


///////////////////////
// Begin Main function:
void mkROOTaqgcElKOG(){


  //////////////////////////////////////
  // Set MC normalization scale factors:
  const double intLUMI = 19297;

// WA+jets norm - data driven : 1.045 +- 0.086
  const double WAJets_scale  = 1.045 * 9.37246 * intLUMI/1049473;
  const double ZAJets_scale  = 0.63196 * intLUMI/979207;
  const double ZZ_scale      = 8.059 * intLUMI/9702850;

  const double ttbarA_scale  = 1.44 * intLUMI/604113;
  const double SToppS_scale  = 1.75776  * intLUMI/139974;
  const double SToppT_scale  = 30.0042  * intLUMI/1935066;
  const double SToppTW_scale = 11.1773  * intLUMI/493458;
  const double STopS_scale   = 3.89394  * intLUMI/259960;
  const double STopT_scale   = 55.531  * intLUMI/3758221;
  const double STopTW_scale  = 11.1773  * intLUMI/497657;

  const double WWA_scale     = 1.5 * 0.01362 * intLUMI/198777;
  const double WWA2_scale    = 1.5 * 0.01409 * intLUMI/199183;
  const double WZA_scale     = 1.5 * 0.00578008 * intLUMI/497450;

  const double KOG_m5m5_scale     = 1.5 * 0.0470065 * intLUMI/194029;
  const double KOG_m2m5_scale     = 1.5 * 0.0249555 * intLUMI/195494;
  const double KOG_m3m5_scale     = 1.5 * 0.0302425 * intLUMI/196004;
  const double KOG_p5m5_scale     = 1.5 * 0.046106 * intLUMI/184331;
  const double KOG_p2m5_scale     = 1.5 * 0.0245765 * intLUMI/197493;
  const double KOG_p3m5_scale     = 1.5 * 0.029646 * intLUMI/139920;


  ///////////////////////////////////////////////////////////////////////////////////
  // Specify what kinematical distribution to observe, as well as histogram settings:
  // 
  plotVar_t pv = {"Photon_Et[iPhoton11]",45,325,7,3,"Photon E_{T} (GeV)"};
  if ( !strlen(pv.plotvar) ) break;
  std::cout << TString(pv.plotvar) << "\t"<<pv.MINRange<<"\t" << pv.MAXRange<<"\t" << pv.NBINS<<"\tTHE CUT " << endl;


  ////////////////////////////////
  // Specify event selection cuts:
  TCut the_cut("effwt*puwt*(iPhoton11>-1 && i11Jet1>-1 && i11Jet2>-1 && i11Jet3<0 && abs(W_electron_eta)<2.5 && W_electron_pt>30 && event_met_pfmet>30. && W_mt>30 && abs(Photon_Eta[iPhoton11])<1.44421 && Photon_Et[iPhoton11]>30. && JetPFCor_dRpho11[i11Jet1]>0.5 && JetPFCor_dRpho11[i11Jet2]>0.5 && abs(JetPFCor_dphiMET[i11Jet1])>0.4 && abs(JetPFCor_dphiMET[i11Jet2])>0.4 && JetPFCor_bDiscriminatorCSV[i11Jet1]<0.679 && JetPFCor_bDiscriminatorCSV[i11Jet2]<0.679 && abs(JetPFCor_Eta[i11Jet1]-JetPFCor_Eta[i11Jet2])<1.4 && c2jMass11>72. && c2jMass11<98. && abs(91.1876-massla)>10. &&ggdevt==2&&mva2jWWAelA>0.1)");
 // ! no need for extra PUwt stat err. sumw2 is enough

  //////////////////////////////////////////////////////////////////
  // Specify Fake-Photon contribution function (fake rate function):
  TCut fkPhoton_cut(TString(the_cut)+TString("*(1./(1.+1./(0.0345868+1.44022E04/(Photon_Et[(iPhoton11>-1)? iPhoton11 : 0]^2.89994))))"));


  ///////////////////////////
  // Create output ROOT file:
  TFile f("el_a0W_WWA_PhotonEt_MVA01.root", "RECREATE");


  //////////////////////////////////////////////////
  // Create file pointers for each sample ROOT file:
  TFile *fin2,*fqcd,*wwaShape_file,*wwa2Shape_file,*wzaShape_file,*zzShape_file,*wajetsShape_file,*ttbara_file,*zajets_file,*stops_file,*stopt_file,*stoptW_file,*stopps_file,*stoppt_file,*stopptW_file;

  TFile *KOG_m5m5_file,*KOG_m3m5_file,*KOG_m2m5_file,*KOG_p2m5_file,*KOG_p3m5_file,*KOG_p5m5_file;


  //////////////////////////////
  // Open each sample ROOT file:
  fin2 = new TFile("InData/RD_WenuJets_DataAllSingleElectronTrigger_GoldenJSON_19p2invfb.root");
  fqcd = new TFile("InData/RDQCD_WenuJets_DataAll_GoldenJSON_19p2invfb.root");
  wwaShape_file = new TFile("InData/RD_el_qq_wpwma_wp_qq_wm_lvl.root");
  wwa2Shape_file = new TFile("InData/RD_el_qq_wpwma_wp_lvl_wm_qq.root");
  wzaShape_file = new TFile("InData/RD_el_WZA_CMSSW532.root");
  zzShape_file = new TFile("InData/RD_el_ZZ_CMSSW532.root");
  wajetsShape_file = new TFile("InData/RD_el_WAp23Jets.root");
  ttbara_file = new TFile("InData/RD_el_TTbarAJets.root");
  zajets_file = new TFile("InData/RD_el_ZAp23J_CMSSW532.root");
  stops_file = new TFile("InData/RD_el_STopS_T_CMSSW532.root");
  stopt_file = new TFile("InData/RD_el_STopT_T_CMSSW532.root");
  stoptW_file = new TFile("InData/RD_el_STopTW_T_CMSSW532.root");
  stopps_file =  new TFile("InData/RD_el_STopS_Tbar_CMSSW532.root");
  stoppt_file =  new TFile("InData/RD_el_STopT_Tbar_CMSSW532.root");
  stopptW_file =  new TFile("InData/RD_el_STopTW_Tbar_CMSSW532.root");

  KOG_m5m5_file = new TFile("InData/RD_el_KOG_m5m5MG_CMSSW532.root");
  KOG_m3m5_file = new TFile("InData/RD_el_KOG_m3m5MG_CMSSW532.root");
  KOG_m2m5_file = new TFile("InData/RD_el_KOG_m2m5MG_CMSSW532.root");
  KOG_p2m5_file = new TFile("InData/RD_el_KOG_p2m5MG_CMSSW532.root");
  KOG_p3m5_file = new TFile("InData/RD_el_KOG_p3m5MG_CMSSW532.root");
  KOG_p5m5_file = new TFile("InData/RD_el_KOG_p5m5MG_CMSSW532.root");


  ///////////////////////////////////////////////////
  // Retrieve ROOT tree with kinematic distributions:
  TTree* treedata = (TTree*) fin2->Get("WJet");
  TTree* treeqcd = (TTree*) fqcd->Get("WJet");
  TTree* treewwa    = (TTree*)    wwaShape_file->Get("WJet");
  TTree* treewwa2    = (TTree*)    wwa2Shape_file->Get("WJet");
  TTree* treewza    = (TTree*)    wzaShape_file->Get("WJet");
  TTree* treezz    = (TTree*)    zzShape_file->Get("WJet");
  TTree* treewaj    = (TTree*) wajetsShape_file->Get("WJet");
  TTree* treettba   = (TTree*)      ttbara_file->Get("WJet");
  TTree* treezaj    = (TTree*)      zajets_file->Get("WJet");
  TTree* treests   = (TTree*)      stops_file->Get("WJet");
  TTree* treestt   = (TTree*)      stopt_file->Get("WJet");
  TTree* treestw   = (TTree*)     stoptW_file->Get("WJet");
  TTree* tree64 = (TTree*) stopps_file->Get("WJet");
  TTree* tree65 = (TTree*) stoppt_file->Get("WJet");
  TTree* tree66 = (TTree*) stopptW_file->Get("WJet");

  TTree* treeKOG_m5m5 = (TTree*) KOG_m5m5_file->Get("WJet");
  TTree* treeKOG_m3m5 = (TTree*) KOG_m3m5_file->Get("WJet");
  TTree* treeKOG_m2m5 = (TTree*) KOG_m2m5_file->Get("WJet");
  TTree* treeKOG_p2m5 = (TTree*) KOG_p2m5_file->Get("WJet");
  TTree* treeKOG_p3m5 = (TTree*) KOG_p3m5_file->Get("WJet");
  TTree* treeKOG_p5m5 = (TTree*) KOG_p5m5_file->Get("WJet");


  ////////////////////////////////////////////////////////////
  // Create kinematic-distribution histograms for each sample:
  TH1* data_obs  = new TH1D("data_obs",  "data_obs",  pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1fkdata  = new TH1D("th1fkdata",  "th1fkdata",  pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1qcd  = new TH1D("th1qcd",  "th1qcd",  pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1wwa = new TH1D("th1wwa", "th1wwa", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1wwa2 = new TH1D("th1wwa2", "th1wwa2", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1wza = new TH1D("th1wza", "th1wza", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1zz = new TH1D("th1zz", "th1zz", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1wajets  = new TH1D("th1wajets",  "th1wajets",  pv.NBINS ,pv.MINRange,pv.MAXRange);
  TH1* th1Top = new TH1D("th1Top", "th1Top", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1zajets = new TH1D("th1zajets", "th1zajets", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1stops = new TH1D("th1stops", "th1stops", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1stopt = new TH1D("th1stopt", "th1stopt", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1stoptw = new TH1D("th1stoptw", "th1stoptw", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1stopps = new TH1D("th1stopps", "th1stopps", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1stoppt = new TH1D("th1stoppt", "th1stoppt", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1stopptw = new TH1D("th1stopptw", "th1stopptw", pv.NBINS, pv.MINRange, pv.MAXRange);

  TH1* signal_a0w_5 = new TH1D("signal_a0w_5","signal_a0w_5",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_a0w_3 = new TH1D("signal_a0w_3","signal_a0w_3",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_a0w_2 = new TH1D("signal_a0w_2","signal_a0w_2",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_a0w_m2 = new TH1D("signal_a0w_m2","signal_a0w_-2",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_a0w_m3 = new TH1D("signal_a0w_m3","signal_a0w_-3",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_a0w_m5 = new TH1D("signal_a0w_m5","signal_a0w_-5",pv.NBINS, pv.MINRange, pv.MAXRange);


  /////////////////////////////////////////////////////////////////////////
  // Specify histograms to store Sum of Squares of Weights for each sample:
  data_obs->Sumw2();
  th1fkdata->Sumw2();
  th1qcd->Sumw2();
  th1wwa->Sumw2();
  th1wwa2->Sumw2();
  th1wza->Sumw2();
  th1zz->Sumw2();
  th1wajets->Sumw2();
  th1zajets->Sumw2();
  th1Top->Sumw2();
  th1stops->Sumw2();
  th1stopt->Sumw2();
  th1stoptw->Sumw2();
  th1stopps->Sumw2();
  th1stoppt->Sumw2();
  th1stopptw->Sumw2();

  signal_a0w_5->Sumw2();
  signal_a0w_3->Sumw2();
  signal_a0w_2->Sumw2();
  signal_a0w_m2->Sumw2();
  signal_a0w_m3->Sumw2();
  signal_a0w_m5->Sumw2();


  ///////////////////////////////////////////////////////////////////////////////////
  // Fill kinematical distribution for each sample according to event selection cuts:
  std::cout<<"\nFill Data Histogram..."<<std::endl;
  treedata->Draw(TString(pv.plotvar)+TString(">>data_obs"), the_cut, "goff");
  data_obs->AddBinContent(pv.NBINS,data_obs->GetBinContent(pv.NBINS+1));data_obs->SetBinContent(pv.NBINS+1,0.);
  data_obs->SetBinError(pv.NBINS,data_obs->GetBinContent(pv.NBINS));

  std::cout<<"Fill Fake Photon Histogram..."<<std::endl;
  treedata->Draw(TString(pv.plotvar)+TString(">>th1fkdata"), fkPhoton_cut, "goff");
  th1fkdata->AddBinContent(pv.NBINS,th1fkdata->GetBinContent(pv.NBINS+1));th1fkdata->SetBinContent(pv.NBINS+1,0.);

  std::cout<<"Fill QCD Histogram..."<<std::endl;
  treeqcd->Draw(TString(pv.plotvar)+TString(">>th1qcd"), fkPhoton_cut, "goff");
  th1qcd->AddBinContent(pv.NBINS,th1qcd->GetBinContent(pv.NBINS+1));th1qcd->SetBinContent(pv.NBINS+1,0.);

  std::cout<<"Fill SM WWA Histogram..."<<std::endl;
  treewwa->Draw(TString(pv.plotvar)+TString(">>th1wwa"), the_cut, "goff");
  th1wwa->AddBinContent(pv.NBINS,th1wwa->GetBinContent(pv.NBINS+1));th1wwa->SetBinContent(pv.NBINS+1,0.);
  treewwa2->Draw(TString(pv.plotvar)+TString(">>th1wwa2"), the_cut, "goff");
  th1wwa2->AddBinContent(pv.NBINS,th1wwa2->GetBinContent(pv.NBINS+1));th1wwa2->SetBinContent(pv.NBINS+1,0.);

  std::cout<<"Fill WZA Histogram..."<<std::endl;
  treewza->Draw(TString(pv.plotvar)+TString(">>th1wza"), the_cut, "goff");
  th1wza->AddBinContent(pv.NBINS,th1wza->GetBinContent(pv.NBINS+1));th1wza->SetBinContent(pv.NBINS+1,0.);

  std::cout<<"Fill ZZ Histogram..."<<std::endl;
  treezz->Draw(TString(pv.plotvar)+TString(">>th1zz"), the_cut, "goff");
  th1zz->AddBinContent(pv.NBINS,th1zz->GetBinContent(pv.NBINS+1));th1zz->SetBinContent(pv.NBINS+1,0.);

  std::cout<<"Fill WA+Jets Histogram..."<<std::endl;
  treewaj->Draw(TString(pv.plotvar)+TString(">>th1wajets"), the_cut, "goff");
  th1wajets->AddBinContent(pv.NBINS,th1wajets->GetBinContent(pv.NBINS+1));th1wajets->SetBinContent(pv.NBINS+1,0.);

  std::cout<<"Fill ttbar+A Histogram..."<<std::endl;
  treettba->Draw(TString(pv.plotvar)+TString(">>th1Top"), the_cut, "goff");
  th1Top->AddBinContent(pv.NBINS,th1Top->GetBinContent(pv.NBINS+1));th1Top->SetBinContent(pv.NBINS+1,0.);

  std::cout<<"Fill ZA+Jets Histogram..."<<std::endl;
  treezaj->Draw(TString(pv.plotvar)+TString(">>th1zajets"), the_cut, "goff");
  th1zajets->AddBinContent(pv.NBINS,th1zajets->GetBinContent(pv.NBINS+1));th1zajets->SetBinContent(pv.NBINS+1,0.);

  std::cout<<"Fill STopS Histogram..."<<std::endl;
  treests->Draw(TString(pv.plotvar)+TString(">>th1stops"), the_cut, "goff");
  th1stops->AddBinContent(pv.NBINS,th1stops->GetBinContent(pv.NBINS+1));th1stops->SetBinContent(pv.NBINS+1,0.);

  std::cout<<"Fill STopT Histogram..."<<std::endl;
  treestt->Draw(TString(pv.plotvar)+TString(">>th1stopt"), the_cut, "goff");
  th1stopt->AddBinContent(pv.NBINS,th1stopt->GetBinContent(pv.NBINS+1));th1stopt->SetBinContent(pv.NBINS+1,0.);

  std::cout<<"Fill STopTW Histogram..."<<std::endl;
  treestw->Draw(TString(pv.plotvar)+TString(">>th1stoptw"), the_cut, "goff");
  th1stoptw->AddBinContent(pv.NBINS,th1stoptw->GetBinContent(pv.NBINS+1));th1stoptw->SetBinContent(pv.NBINS+1,0.);

  std::cout<<"Fill STopPS Histogram..."<<std::endl;
  tree64->Draw(TString(pv.plotvar)+TString(">>th1stopps"), the_cut, "goff");
  th1stopps->AddBinContent(pv.NBINS,th1stopps->GetBinContent(pv.NBINS+1));th1stopps->SetBinContent(pv.NBINS+1,0.);

  std::cout<<"Fill STopPT Histogram..."<<std::endl;
  tree65->Draw(TString(pv.plotvar)+TString(">>th1stoppt"), the_cut, "goff");
  th1stoppt->AddBinContent(pv.NBINS,th1stoppt->GetBinContent(pv.NBINS+1));th1stoppt->SetBinContent(pv.NBINS+1,0.);

  std::cout<<"Fill STopPTW Histogram..."<<std::endl;
  tree66->Draw(TString(pv.plotvar)+TString(">>th1stopptw"), the_cut, "goff");
  th1stopptw->AddBinContent(pv.NBINS,th1stopptw->GetBinContent(pv.NBINS+1));th1stopptw->SetBinContent(pv.NBINS+1,0.);


  std::cout<<"Fill aQGC_1 WWA Histogram..."<<std::endl;
  treeKOG_p5m5->Draw(TString(pv.plotvar)+TString(">>signal_a0w_m5"), the_cut, "goff");

  std::cout<<"Fill aQGC_2 WWA Histogram..."<<std::endl;
  treeKOG_p3m5->Draw(TString(pv.plotvar)+TString(">>signal_a0w_m3"), the_cut, "goff");

  std::cout<<"Fill aQGC_3 WWA Histogram..."<<std::endl;
  treeKOG_p2m5->Draw(TString(pv.plotvar)+TString(">>signal_a0w_m2"), the_cut, "goff");

  std::cout<<"Fill aQGC_4 WWA Histogram..."<<std::endl;
  treeKOG_m2m5->Draw(TString(pv.plotvar)+TString(">>signal_a0w_2"), the_cut, "goff");

  std::cout<<"Fill aQGC_5 WWA Histogram..."<<std::endl;
  treeKOG_m3m5->Draw(TString(pv.plotvar)+TString(">>signal_a0w_3"), the_cut, "goff");

  std::cout<<"Fill aQGC_6 WWA Histogram..."<<std::endl;
  treeKOG_m5m5->Draw(TString(pv.plotvar)+TString(">>signal_a0w_5"), the_cut, "goff");

  signal_a0w_5->AddBinContent(pv.NBINS,signal_a0w_5->GetBinContent(pv.NBINS+1));signal_a0w_5->SetBinContent(pv.NBINS+1,0.);
  signal_a0w_3->AddBinContent(pv.NBINS,signal_a0w_3->GetBinContent(pv.NBINS+1));signal_a0w_3->SetBinContent(pv.NBINS+1,0.);
  signal_a0w_2->AddBinContent(pv.NBINS,signal_a0w_2->GetBinContent(pv.NBINS+1));signal_a0w_2->SetBinContent(pv.NBINS+1,0.);
  signal_a0w_m2->AddBinContent(pv.NBINS,signal_a0w_m2->GetBinContent(pv.NBINS+1));signal_a0w_m2->SetBinContent(pv.NBINS+1,0.);
  signal_a0w_m3->AddBinContent(pv.NBINS,signal_a0w_m3->GetBinContent(pv.NBINS+1));signal_a0w_m3->SetBinContent(pv.NBINS+1,0.);
  signal_a0w_m5->AddBinContent(pv.NBINS,signal_a0w_m5->GetBinContent(pv.NBINS+1));signal_a0w_m5->SetBinContent(pv.NBINS+1,0.);


  ///////////////////////////////////////////////////////////////////////////
  // Set uncertainty in each bin of kinematical distribution for each sample:
    float fperr = 0.;
 // adding 10% sys on photon fakerate 
    for(int hi=1;hi<=pv.NBINS;hi++) {
        fperr = (th1fkdata->GetBinError(hi))*(th1fkdata->GetBinError(hi));
        fperr + = 0.01*(th1fkdata->GetBinContent(hi))*(th1fkdata->GetBinContent(hi));
        th1fkdata->SetBinError(hi,sqrt(fperr));
    }

 // adding 50% sys on QCD
    for(int hi=1;hi<=pv.NBINS;hi++) {
        fperr = (th1qcd->GetBinError(hi))*(th1qcd->GetBinError(hi));
        fperr + = 0.25*(th1qcd->GetBinContent(hi))*(th1qcd->GetBinContent(hi));
        th1qcd->SetBinError(hi,sqrt(fperr));
    }

//  Adding Normalization uncertainty to WA+jets
    for(int hi=1;hi<=pv.NBINS;hi++) {
        fperr = (th1wajets->GetBinError(hi))*(th1wajets->GetBinError(hi));
        fperr + = 0.086*0.086*(th1wajets->GetBinContent(hi))*(th1wajets->GetBinContent(hi));
        th1wajets->SetBinError(hi,sqrt(fperr));
    }


  /////////////////////////
  // Normalize each sample:
  std::cout<<"\nScale Histograms..."<<std::endl;
  th1Top->Scale(ttbarA_scale);
  th1stops->Scale(STopS_scale);
  th1stopt->Scale(STopT_scale);
  th1stoptw->Scale(STopTW_scale);
  th1stopps->Scale(SToppS_scale);
  th1stoppt->Scale(SToppT_scale);
  th1stopptw->Scale(SToppTW_scale);
  th1wajets->Scale(WAJets_scale);
  th1wwa->Scale(WWA_scale);
  th1wwa2->Scale(WWA2_scale);
  th1wza->Scale(WZA_scale);
  th1zz->Scale(ZZ_scale);
  th1zajets->Scale(ZAJets_scale);

  signal_a0w_5->Scale(KOG_p5m5_scale);
  signal_a0w_3->Scale(KOG_p3m5_scale);
  signal_a0w_2->Scale(KOG_p2m5_scale);
  signal_a0w_m2->Scale(KOG_m2m5_scale);
  signal_a0w_m3->Scale(KOG_m3m5_scale);
  signal_a0w_m5->Scale(KOG_m5m5_scale);


  ///////////////////////////
  // Combine certain samples:
  th1Top->Add(th1stopptw,1);
  th1Top->Add(th1stoppt,1);
  th1Top->Add(th1stopps,1);
  th1Top->Add(th1stoptw,1);
  th1Top->Add(th1stopt,1);
  th1Top->Add(th1stops,1);
  th1wwa->Add(th1wwa2,1);


  ///////////////////////////////////////////
  // Subtract SM signal from Anomalous signal 
  // (extracts anomalous contribution):
  signal_a0w_5->Add(th1wwa,-1);
  signal_a0w_3->Add(th1wwa,-1);
  signal_a0w_2->Add(th1wwa,-1);
  signal_a0w_m2->Add(th1wwa,-1);
  signal_a0w_m3->Add(th1wwa,-1);
  signal_a0w_m5->Add(th1wwa,-1);


  ////////////////////////////////////////////////////////
  // Combine SM WWA+WZA samples after extracting anomalous
  // contribution because Anomalous samples were only
  // generated for WWA:
  th1wwa->Add(th1wza,1);


  ///////////////////////////////////////////
  // Combine all background + SM WWA samples:
  TH1D *background = (TH1D*)th1wajets->Clone("background");
  background->Reset();
  background->Add(th1fkdata,1);
  background->Add(th1Top,1);
  background->Add(th1wajets,1);
  background->Add(th1zajets,1);
  background->Add(th1zz,1);
  background->Add(th1wwa,1);

  float qcd_scale=0;
   if(th1qcd->Integral()>0 ){
   qcd_scale = 0.0637*background->Integral()/th1qcd->Integral();
   th1qcd->Scale(qcd_scale);
   background->Add(th1qcd,1);
  }


  ////////////////////////////////////////////////
  // Create Background +/- Uncertainty histograms:
  std::cout<<"Set error..."<<std::endl;
  TH1D *background_mudijet_backshapeUp = (TH1D*)background->Clone("background_eldijet_backshapeUp");
  TH1D *background_mudijet_backshapeDown = (TH1D*)background->Clone("background_eldijet_backshapeDown");
  background_mudijet_backshapeUp->Reset();
  background_mudijet_backshapeDown->Reset();

//  Double_t change;
  for(int ibin=1;ibin<=pv.NBINS+1;ibin++){


     //////////////////////////////////////////////////////
     // Instead use pre-existing Control Plot uncertainties
     background_mudijet_backshapeUp->SetBinContent(ibin,background->GetBinContent(ibin)+background->GetBinError(ibin));
     background_mudijet_backshapeDown->SetBinContent(ibin,background->GetBinContent(ibin)-background->GetBinError(ibin));

  }


  ////////////////////////
  // Set histogram labels:
  const double BINWIDTH = ((pv.MAXRange-pv.MINRange)/pv.NBINS);
  char tmpc[100];    sprintf(tmpc,"Events / %.1f GeV",BINWIDTH);
  if (pv.slog==1)    sprintf(tmpc,"Events / %.1f",BINWIDTH);
  if (pv.slog==2)    sprintf(tmpc,"Events / %.2f",BINWIDTH);
  if (pv.slog==3)    sprintf(tmpc,"Events / %.0f GeV",BINWIDTH);
  if (pv.slog==6)    sprintf(tmpc,"Events / %.2f rad",BINWIDTH);

  data_obs->SetYTitle(tmpc);
  data_obs->GetXaxis()->SetTitle(pv.xlabel);
  data_obs->GetYaxis()->CenterTitle(true);

  background->SetYTitle(tmpc);
  background->GetXaxis()->SetTitle(pv.xlabel);
  background->GetYaxis()->CenterTitle(true);

  background_mudijet_backshapeUp->SetYTitle(tmpc);
  background_mudijet_backshapeUp->GetXaxis()->SetTitle(pv.xlabel);
  background_mudijet_backshapeUp->GetYaxis()->CenterTitle(true);

  background_mudijet_backshapeDown->SetYTitle(tmpc);
  background_mudijet_backshapeDown->GetXaxis()->SetTitle(pv.xlabel);
  background_mudijet_backshapeDown->GetYaxis()->CenterTitle(true);

  signal_a0w_5->SetYTitle(tmpc);
  signal_a0w_5->GetXaxis()->SetTitle(pv.xlabel);
  signal_a0w_5->GetYaxis()->CenterTitle(true);

  signal_a0w_3->SetYTitle(tmpc);
  signal_a0w_3->GetXaxis()->SetTitle(pv.xlabel);
  signal_a0w_3->GetYaxis()->CenterTitle(true);

  signal_a0w_2->SetYTitle(tmpc);
  signal_a0w_2->GetXaxis()->SetTitle(pv.xlabel);
  signal_a0w_2->GetYaxis()->CenterTitle(true);

  signal_a0w_m2->SetYTitle(tmpc);
  signal_a0w_m2->GetXaxis()->SetTitle(pv.xlabel);
  signal_a0w_m2->GetYaxis()->CenterTitle(true);

  signal_a0w_m3->SetYTitle(tmpc);
  signal_a0w_m3->GetXaxis()->SetTitle(pv.xlabel);
  signal_a0w_m3->GetYaxis()->CenterTitle(true);

  signal_a0w_m5->SetYTitle(tmpc);
  signal_a0w_m5->GetXaxis()->SetTitle(pv.xlabel);
  signal_a0w_m5->GetYaxis()->CenterTitle(true);


  //////////////////////////////////////////////////////////
  // Save Observed Data, Background (+ SM WWA), Background +
  // Uncertainty, Background - Uncertainty, Anomalous Signal
  // histograms to output ROOT file:
  std::cout<<"Save Histograms..."<<std::endl;
  f.cd();
  data_obs->Write();
  background->Write();
  background_mudijet_backshapeUp->Write();
  background_mudijet_backshapeDown->Write();
  signal_a0w_5->Write();
  signal_a0w_3->Write();
  signal_a0w_2->Write();
  signal_a0w_m2->Write();
  signal_a0w_m3->Write();
  signal_a0w_m5->Write();

}// End Main function
