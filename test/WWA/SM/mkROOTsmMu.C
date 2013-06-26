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

Syntax: root -l -b -q mkROOTsm.C

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
void mkROOTsmMu(){


  //////////////////////////////////////
  // Set MC normalization scale factors:
  const double intLUMI = 19297;

// WA+jets norm - data driven : 1.09896 +- 0.091
  const double WAJets_scale = 1.09896 * 9.37246 * intLUMI/1049473;
  const double WAJetsPT100_scale = 1.09896 * 0.423028445 *intLUMI/369309; // V
  const double ZAJets_scale  = 0.63196 * intLUMI/979207;
  const double ZZ_scale      = 8.059 * intLUMI/9702850;

  const double ttbarA_scale  = 1.44 * intLUMI/604113;
  const double SToppS_scale  = 1.75776  * intLUMI/139974;
  const double SToppT_scale  = 30.0042  * intLUMI/1935066;
  const double SToppTW_scale = 11.1773  * intLUMI/493458;
  const double STopS_scale   = 3.89394  * intLUMI/259960;
  const double STopT_scale   = 55.531  * intLUMI/3758221;
  const double STopTW_scale  = 11.1773  * intLUMI/497657;

  // PT dependent k-factor included (same for WWA,WZA aQGC)
  const double WWA_scale     =  2.1* 0.01362 * intLUMI/198777;
  const double WWA2_scale    =  2.1* 0.01409 * intLUMI/199183;
  const double WZA_scale     =  2.1* 0.00578008 * intLUMI/497450;


  ///////////////////////////////////////////////////////////////////////////////////
  // Specify what kinematical distribution to observe, as well as histogram settings:
  plotVar_t pv = {"Photon_Et[iPhoton12]",30,450,10,3,"Photon ET (GeV)"};
  if ( !strlen(pv.plotvar) ) break;
  std::cout << TString(pv.plotvar) << "\t"<<pv.MINRange<<"\t" << pv.MAXRange<<"\t" << pv.NBINS<<"\tTHE CUT " << endl;


  ////////////////////////////////
  // Specify event selection cuts:
  TCut the_cut("effwt*puwt*(iPhoton12>-1&&Photon_Et[iPhoton12]>30.&&Photon_dRlep[iPhoton12]>0.5&&i12Jet2>-1&&i12Jet1>-1&&JetPFCor_dRpho12[i12Jet1]>0.5&&JetPFCor_dRpho12[i12Jet2]>0.5&&abs(W_muon_eta)<2.1&&abs(JetPFCor_dphiMET[i12Jet1])>0.4&& abs(JetPFCor_dphiMET[i12Jet2])>0.4&&JetPFCor_bDiscriminatorCSV[i12Jet1]<0.679&&JetPFCor_bDiscriminatorCSV[i12Jet2]<0.679&&abs(JetPFCor_Eta[i12Jet1]-JetPFCor_Eta[i12Jet2])<1.4&&abs(Photon_Eta[iPhoton12])<1.44421&&W_muon_pt>25&&event_met_pfmet>35.&&c2jMass12>70.&&c2jMass12<100.&&W_mt>30.&&abs(W_muon_dz000)<0.02&&abs(W_muon_dzPV)<0.5&&((i12Jet3>-1)? JetPFCor_dRpho12[i12Jet3]>0.5: 1 )&&((i12Jet4>-1)? JetPFCor_dRpho12[i12Jet4]>0.5: 1 ))");
//mva2jWWAmuA1>0.32
  TCut the_cutPlj("effwt*puwt*(iPhoton12plj>-1&&Photon_Et[iPhoton12plj]>30.&&Photon_dRlep[iPhoton12plj]>0.5&&i12Jet2plj>-1&&i12Jet1plj>-1&&JetPFCor_dRpho12plj[i12Jet1plj]>0.5&&JetPFCor_dRpho12plj[i12Jet2plj]>0.5&&abs(W_muon_eta)<2.1&&abs(JetPFCor_dphiMET[i12Jet1plj])>0.4&& abs(JetPFCor_dphiMET[i12Jet2plj])>0.4&&JetPFCor_bDiscriminatorCSV[i12Jet1plj]<0.679&&JetPFCor_bDiscriminatorCSV[i12Jet2plj]<0.679&&abs(JetPFCor_Eta[i12Jet1plj]-JetPFCor_Eta[i12Jet2plj])<1.4&&abs(Photon_Eta[iPhoton12plj])<1.44421&&W_muon_pt>25&&event_met_pfmet>35.&&c2jMass12plj>70.&&c2jMass12plj<100.&&W_mt>30.&&abs(W_muon_dz000)<0.02&&abs(W_muon_dzPV)<0.5&&((i12Jet3plj>-1)? JetPFCor_dRpho12plj[i12Jet3plj]>0.5: 1 )&&((i12Jet4plj>-1)? JetPFCor_dRpho12plj[i12Jet4plj]>0.5: 1 ))");


  TCut WA23Jcut(TString(the_cut)+TString("*((W_Photon_pt_gen>115)? 0. : 1.) "));
  TCut WA23JPT100cut(TString(the_cut)+TString("*((W_Photon_pt_gen>115)? 1. : 0.) "));

  //////////////////////////////////////////////////////////////////
  // Specify Fake-Photon contribution function (fake rate function):
  TCut fkPhoton_cut(TString(the_cutPlj)+TString("*(0.01373795 + 308.9628/(Photon_Et[(iPhoton12plj>-1)? iPhoton12plj : 0]^2.29711))"));
  TCut fkPhoton_cutUp(TString(fkPhoton_cut)+TString("*(1+((Photon_Et[(iPhoton12plj>-1)? iPhoton12plj : 0]<50.)? 0.12 : ((Photon_Et[(iPhoton12plj>-1)? iPhoton12plj : 0]<75.)? 0.14 : ((Photon_Et[(iPhoton12plj>-1)? iPhoton12plj : 0]<90.)? 0.23 : ((Photon_Et[(iPhoton12plj>-1)? iPhoton12plj : 0]<135.)? 0.22 : 0.39)))))"));
  TCut fkPhoton_cutDown(TString(fkPhoton_cut)+TString("*(1-((Photon_Et[(iPhoton12plj>-1)? iPhoton12plj : 0]<50.)? 0.12 : ((Photon_Et[(iPhoton12plj>-1)? iPhoton12plj : 0]<75.)? 0.14 : ((Photon_Et[(iPhoton12plj>-1)? iPhoton12plj : 0]<90.)? 0.23 : ((Photon_Et[(iPhoton12plj>-1)? iPhoton12plj : 0]<135.)? 0.22 : 0.39)))))"));


  ///////////////////////////
  // Create output ROOT file:
  TFile f("mu_WWA_WZA_PhotonEt.root", "RECREATE");


  //////////////////////////////////////////////////
  // Create file pointers for each sample ROOT file:
  TFile *fin2,*wwaShape_file,*wwa2Shape_file,*wzaShape_file,*zzShape_file,*wajetsShape_file,*wajetsPT100Shape_file,*ttbara_file,*zajets_file,*stops_file,*stopt_file,*stoptW_file,*stopps_file,*stoppt_file,*stopptW_file;


  //////////////////////////////
  // Open each sample ROOT file:
  fin2 = new TFile("InData_New/RD_WmunuJets_DataAll_GoldenJSON_19p3invfb.root");
  wwaShape_file = new TFile("InData_New/RD_mu_qq_wpwma_wp_qq_wm_lvl.root");
  wwa2Shape_file = new TFile("InData_New/RD_mu_qq_wpwma_wp_lvl_wm_qq.root");
  wzaShape_file = new TFile("InData_New/RD_mu_WZA_CMSSW532.root");
  zzShape_file = new TFile("InData_New/RD_mu_ZZ_CMSSW532.root");
  wajetsShape_file = new TFile("InData_New/RD_mu_WGp23J_CMSSW532.root");
  wajetsPT100Shape_file = new TFile("InData_New/RD_mu_WGp23J_PT100_CMSSW532.root");
  ttbara_file = new TFile("InData_New/RD_mu_TTbarGpJets_CMSSW532.root");
  zajets_file = new TFile("InData_New/RD_mu_ZAp23J_CMSSW532.root");
  stops_file = new TFile("InData_New/RD_mu_STopS_T_CMSSW532.root");
  stopt_file = new TFile("InData_New/RD_mu_STopT_T_CMSSW532.root");
  stoptW_file = new TFile("InData_New/RD_mu_STopTW_T_CMSSW532.root");
  stopps_file =  new TFile("InData_New/RD_mu_STopS_Tbar_CMSSW532.root");
  stoppt_file =  new TFile("InData_New/RD_mu_STopT_Tbar_CMSSW532.root");
  stopptW_file =  new TFile("InData_New/RD_mu_STopTW_Tbar_CMSSW532.root");


  ///////////////////////////////////////////////////
  // Retrieve ROOT tree with kinematic distributions:
  TTree* treedata = (TTree*) fin2->Get("WJet");
  TTree* treewwa    = (TTree*)    wwaShape_file->Get("WJet");
  TTree* treewwa2    = (TTree*)    wwa2Shape_file->Get("WJet");
  TTree* treewza    = (TTree*)    wzaShape_file->Get("WJet");
  TTree* treezz    = (TTree*)    zzShape_file->Get("WJet");
  TTree* treewaj    = (TTree*) wajetsShape_file->Get("WJet");
  TTree* treewajPT100    = (TTree*) wajetsPT100Shape_file->Get("WJet");
  TTree* treettba   = (TTree*)      ttbara_file->Get("WJet");
  TTree* treezaj    = (TTree*)      zajets_file->Get("WJet");
  TTree* treests   = (TTree*)      stops_file->Get("WJet");
  TTree* treestt   = (TTree*)      stopt_file->Get("WJet");
  TTree* treestw   = (TTree*)     stoptW_file->Get("WJet");
  TTree* tree64 = (TTree*) stopps_file->Get("WJet");
  TTree* tree65 = (TTree*) stoppt_file->Get("WJet");
  TTree* tree66 = (TTree*) stopptW_file->Get("WJet");


  ////////////////////////////////////////////////////////////
  // Create kinematic-distribution histograms for each sample:
  TH1* data_obs  = new TH1D("data_obs",  "data_obs",  pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1fkdata  = new TH1D("th1fkdata",  "th1fkdata",  pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1fkdataUp  = new TH1D("th1fkdataUp",  "th1fkdataUp",  pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1fkdataDown  = new TH1D("th1fkdataDown",  "th1fkdataDown",  pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1wwa = new TH1D("th1wwa", "th1wwa", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1wwa2 = new TH1D("th1wwa2", "th1wwa2", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1wza = new TH1D("th1wza", "th1wza", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1zz = new TH1D("th1zz", "th1zz", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1wajets  = new TH1D("th1wajets",  "th1wajets",  pv.NBINS ,pv.MINRange,pv.MAXRange);
  TH1* th1wajetsPT100  = new TH1D("th1wajetsPT100",  "th1wajetsPT100",  pv.NBINS ,pv.MINRange,pv.MAXRange);
  TH1* th1Top = new TH1D("th1Top", "th1Top", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1zajets = new TH1D("th1zajets", "th1zajets", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1stops = new TH1D("th1stops", "th1stops", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1stopt = new TH1D("th1stopt", "th1stopt", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1stoptw = new TH1D("th1stoptw", "th1stoptw", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1stopps = new TH1D("th1stopps", "th1stopps", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1stoppt = new TH1D("th1stoppt", "th1stoppt", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1stopptw = new TH1D("th1stopptw", "th1stopptw", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1stop = new TH1D("th1stop", "th1stop", pv.NBINS, pv.MINRange, pv.MAXRange);


  /////////////////////////////////////////////////////////////////////////
  // Specify histograms to store Sum of Squares of Weights for each sample:
  data_obs->Sumw2();
  th1fkdata->Sumw2();
  th1fkdataUp->Sumw2();
  th1fkdataDown->Sumw2();
  th1wwa->Sumw2();
  th1wwa2->Sumw2();
  th1wza->Sumw2();
  th1zz->Sumw2();
  th1wajets->Sumw2();
  th1wajetsPT100->Sumw2();
  th1zajets->Sumw2();
  th1Top->Sumw2();
  th1stops->Sumw2();
  th1stopt->Sumw2();
  th1stoptw->Sumw2();
  th1stopps->Sumw2();
  th1stoppt->Sumw2();
  th1stopptw->Sumw2();


  ///////////////////////////////////////////////////////////////////////////////////
  // Fill kinematical distribution for each sample according to event selection cuts:
  std::cout<<"\nFill Data Histogram..."<<std::endl;
  treedata->Draw(TString(pv.plotvar)+TString(">>data_obs"), the_cut, "goff");
  data_obs->AddBinContent(pv.NBINS,data_obs->GetBinContent(pv.NBINS+1));data_obs->SetBinContent(pv.NBINS+1,0.);

  std::cout<<"Fill Fake Photon Histogram..."<<std::endl;
  treedata->Draw(TString("Photon_Et[iPhoton12plj]>>th1fkdata"), fkPhoton_cut, "goff");
  th1fkdata->AddBinContent(pv.NBINS,th1fkdata->GetBinContent(pv.NBINS+1));th1fkdata->SetBinContent(pv.NBINS+1,0.);

  treedata->Draw(TString("Photon_Et[iPhoton12plj]>>th1fkdataUp"), fkPhoton_cutUp, "goff");
  th1fkdataUp->AddBinContent(pv.NBINS,th1fkdataUp->GetBinContent(pv.NBINS+1));th1fkdataUp->SetBinContent(pv.NBINS+1,0.);

  treedata->Draw(TString("Photon_Et[iPhoton12plj]>>th1fkdataDown"), fkPhoton_cutDown, "goff");
  th1fkdataDown->AddBinContent(pv.NBINS,th1fkdataDown->GetBinContent(pv.NBINS+1));th1fkdataDown->SetBinContent(pv.NBINS+1,0.);

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
  treewaj->Draw(TString(pv.plotvar)+TString(">>th1wajets"), WA23Jcut, "goff");
  th1wajets->AddBinContent(pv.NBINS,th1wajets->GetBinContent(pv.NBINS+1));th1wajets->SetBinContent(pv.NBINS+1,0.);

  treewajPT100->Draw(TString(pv.plotvar)+TString(">>th1wajetsPT100"), WA23JPT100cut, "goff");
  th1wajetsPT100->AddBinContent(pv.NBINS,th1wajetsPT100->GetBinContent(pv.NBINS+1));th1wajetsPT100->SetBinContent(pv.NBINS+1,0.);

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
  th1wajetsPT100->Scale(WAJetsPT100_scale);
  th1wwa->Scale(WWA_scale);
  th1wwa2->Scale(WWA2_scale);
  th1wza->Scale(WZA_scale);
  th1zz->Scale(ZZ_scale);
  th1zajets->Scale(ZAJets_scale);


  ///////////////////////////
  // Combine certain samples:
  th1stop->Add(th1stopptw,1);
  th1stop->Add(th1stoppt,1);
  th1stop->Add(th1stopps,1);
  th1stop->Add(th1stoptw,1);
  th1stop->Add(th1stopt,1);
  th1stop->Add(th1stops,1);

  th1wwa->Add(th1wwa2,1);
  th1wajets->Add(th1wajetsPT100,1);

/*
std::cout << "\nSample Contribution:" << std::endl;
std::cout << "WWA: " << th1wwa->Integral() << std::endl;
std::cout << "Top: " << th1Top->Integral() << std::endl;
std::cout << "Single Top: " << th1stop->Integral() << std::endl;
std::cout << "WA+Jets: " << th1wajets->Integral() << std::endl;
std::cout << "ZA+Jets: " << th1zajets->Integral() << std::endl;
std::cout << "WZA: " << th1wza->Integral() << std::endl;
std::cout << "ZZ: " << th1zz->Integral() << std::endl;
std::cout << "Fake Photons: " << th1fkdata->Integral() << std::endl;
std::cout << "Data: " << data_obs->Integral() << std::endl;

std::cout << "\nSample Contribution:" << std::endl;
std::cout << "Top: " << th1Top->GetBinError(1) << std::endl;
std::cout << "WA+Jets: " << th1wajets->GetBinError(1) << std::endl;
std::cout << "ZA+Jets: " << th1zajets->GetBinError(1) << std::endl;
std::cout << "WZA: " << th1wza->GetBinError(1) << std::endl;
std::cout << "ZZ: " << th1zz->GetBinError(1) << std::endl;
std::cout << "Fake Photons: " << th1fkdata->GetBinError(1) << std::endl;
std::cout << "Data: " << data_obs->GetBinError(1) << std::endl;
*/


  ///////////////////////////////////////////////////////////////
  // Combine SM WVA samples for Signal:
  TH1D *signal_SM = (TH1D*)th1wwa->Clone("signal_SM");
  signal_SM->Add(th1wza,1);


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


  //////////////////////////////////////////////////////////
  // Save Observed Data, Background (+ SM WWA), Background +
  // Uncertainty, Background - Uncertainty, Anomalous Signal
  // histograms to output ROOT file:
  std::cout<<"Save Histograms..."<<std::endl;
  f.cd();
  data_obs->Write();
  th1fkdata->Write();
  th1fkdataUp->Write();
  th1fkdataDown->Write();
  th1Top->Write();
  th1stop->Write();
  th1wajets->Write();
  th1zz->Write();
  th1zajets->Write();
  signal_SM->Write();

}// End Main function
