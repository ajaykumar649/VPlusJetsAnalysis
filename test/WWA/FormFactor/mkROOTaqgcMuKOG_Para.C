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
void mkROOTaqgcMuKOG_Para(){


  //////////////////////////////////////
  // Set MC normalization scale factors:
  const double intLUMI = 19297;

  // PT dependent k-factor included (same for WWA aQGC)
  const double WWA_scale     =  2.1*0.01362 * intLUMI/198777;
  const double WWA2_scale    =  2.1*0.01409 * intLUMI/199183;

  const double KOG_m140m5_scale     = 2.1*.036492 * intLUMI/199579;
  const double KOG_m100m5_scale     = 2.1*.02848 * intLUMI/199186;
  const double KOG_m80m5_scale     =  2.1*.025543 * intLUMI/197579;
  const double KOG_p80m5_scale     =  2.1*.027179 * intLUMI/199532;
  const double KOG_p100m5_scale     = 2.1*.030548 * intLUMI/199529;
  const double KOG_p140m5_scale     = 2.1*.0393085 * intLUMI/199534;


  ///////////////////////////////////////////////////////////////////////////////////
  // Specify what kinematical distribution to observe, as well as histogram settings:
  // 
//  plotVar_t pv = {"masslvjja",700,1040,10,3,"M_{l#nujj#gamma} (GeV/c^{2})"};
  plotVar_t pv = {"Photon_Et[iPhoton12]",30,450,10,3,"Photon ET (GeV)"};
  if ( !strlen(pv.plotvar) ) break;
  std::cout << TString(pv.plotvar) << "\t"<<pv.MINRange<<"\t" << pv.MAXRange<<"\t" << pv.NBINS<<"\tTHE CUT " << endl;


  ////////////////////////////////
  // Specify event selection cuts:
  TCut the_cutKfac("effwt*puwt*(iPhoton12>-1&&Photon_Et[iPhoton12]>30.&&Photon_dRlep[iPhoton12]>0.5&&i12Jet2>-1&&i12Jet1>-1&&JetPFCor_dRpho12[i12Jet1]>0.5&&JetPFCor_dRpho12[i12Jet2]>0.5&&abs(W_muon_eta)<2.1&&abs(JetPFCor_dphiMET[i12Jet1])>0.4&& abs(JetPFCor_dphiMET[i12Jet2])>0.4&&JetPFCor_bDiscriminatorCSV[i12Jet1]<0.679&&JetPFCor_bDiscriminatorCSV[i12Jet2]<0.679&&abs(JetPFCor_Eta[i12Jet1]-JetPFCor_Eta[i12Jet2])<1.4&&abs(Photon_Eta[iPhoton12])<1.44421&&W_muon_pt>25&&event_met_pfmet>35.&&c2jMass12>70.&&c2jMass12<100.&&W_mt>30.&&abs(W_muon_dz000)<0.02&&abs(W_muon_dzPV)<0.5&&((i12Jet3>-1)? JetPFCor_dRpho12[i12Jet3]>0.5: 1 )&&((i12Jet4>-1)? JetPFCor_dRpho12[i12Jet4]>0.5: 1 ))");
//mva2jWWAmuA1>0.32


  ///////////////////////////
  // Create output ROOT file:
  TFile f("para_mu_a0W_WWA_PhotonEt.root", "RECREATE");


  //////////////////////////////////////////////////
  // Create file pointers for each sample ROOT file:
  TFile *wwaShape_file,*wwa2Shape_file;

  TFile *KOG_m140m5_file,*KOG_m100m5_file,*KOG_m80m5_file,*KOG_p80m5_file,*KOG_p100m5_file,*KOG_p140m5_file;

  //////////////////////////////
  // Open each sample ROOT file:
  wwaShape_file = new TFile("InData_New/RD_mu_qq_wpwma_wp_qq_wm_lvl.root");
  wwa2Shape_file = new TFile("InData_New/RD_mu_qq_wpwma_wp_lvl_wm_qq.root");

  KOG_m140m5_file = new TFile("InData_New/RD_mu_a0W_m140m5FF500n2_CMSSW532.root");
  KOG_m100m5_file = new TFile("InData_New/RD_mu_a0W_m100m5FF500n2_CMSSW532.root");
  KOG_m80m5_file = new TFile("InData_New/RD_mu_a0W_m80m5FF500n2_CMSSW532.root");
  KOG_p80m5_file = new TFile("InData_New/RD_mu_a0W_p80m5FF500n2_CMSSW532.root");
  KOG_p100m5_file = new TFile("InData_New/RD_mu_a0W_p100m5FF500n2_CMSSW532.root");
  KOG_p140m5_file = new TFile("InData_New/RD_mu_a0W_p140m5FF500n2_CMSSW532.root");


  ///////////////////////////////////////////////////
  // Retrieve ROOT tree with kinematic distributions:
  TTree* treewwa    = (TTree*)    wwaShape_file->Get("WJet");
  TTree* treewwa2    = (TTree*)    wwa2Shape_file->Get("WJet");

  TTree* treeKOG_m140m5 = (TTree*) KOG_m140m5_file->Get("WJet");
  TTree* treeKOG_m100m5 = (TTree*) KOG_m100m5_file->Get("WJet");
  TTree* treeKOG_m80m5 = (TTree*) KOG_m80m5_file->Get("WJet");
  TTree* treeKOG_p80m5 = (TTree*) KOG_p80m5_file->Get("WJet");
  TTree* treeKOG_p100m5 = (TTree*) KOG_p100m5_file->Get("WJet");
  TTree* treeKOG_p140m5 = (TTree*) KOG_p140m5_file->Get("WJet");


  ////////////////////////////////////////////////////////////
  // Create kinematic-distribution histograms for each sample:
  TH1* th1wwa = new TH1D("th1wwa", "th1wwa", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1wwa2 = new TH1D("th1wwa2", "th1wwa2", pv.NBINS, pv.MINRange, pv.MAXRange);

  TH1* signal_a0w_140 = new TH1D("signal_a0w_140","signal_a0w_14",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_a0w_100 = new TH1D("signal_a0w_100","signal_a0w_10",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_a0w_80 = new TH1D("signal_a0w_80","signal_a0w_8",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_a0w_m80 = new TH1D("signal_a0w_m80","signal_a0w_-8",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_a0w_m100 = new TH1D("signal_a0w_m100","signal_a0w_-10",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_a0w_m140 = new TH1D("signal_a0w_m140","signal_a0w_-14",pv.NBINS, pv.MINRange, pv.MAXRange);


  /////////////////////////////////////////////////////////////////////////
  // Specify histograms to store Sum of Squares of Weights for each sample:
  th1wwa->Sumw2();
  th1wwa2->Sumw2();
/*
  signal_a0w_14->Sumw2();
  signal_a0w_10->Sumw2();
  signal_a0w_8->Sumw2();
  signal_a0w_m2->Sumw2();
  signal_a0w_m3->Sumw2();
  signal_a0w_m5->Sumw2();
*/

  ///////////////////////////////////////////////////////////////////////////////////
  // Fill kinematical distribution for each sample according to event selection cuts:
  std::cout<<"Fill SM WWA Histogram..."<<std::endl;
  treewwa->Draw(TString(pv.plotvar)+TString(">>th1wwa"), the_cutKfac, "goff");
  th1wwa->AddBinContent(pv.NBINS,th1wwa->GetBinContent(pv.NBINS+1));th1wwa->SetBinContent(pv.NBINS+1,0.);
  treewwa2->Draw(TString(pv.plotvar)+TString(">>th1wwa2"), the_cutKfac, "goff");
  th1wwa2->AddBinContent(pv.NBINS,th1wwa2->GetBinContent(pv.NBINS+1));th1wwa2->SetBinContent(pv.NBINS+1,0.);


  std::cout<<"Fill aQGC_1 WWA Histogram..."<<std::endl;
  treeKOG_p140m5->Draw(TString(pv.plotvar)+TString(">>signal_a0w_140"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_2 WWA Histogram..."<<std::endl;
  treeKOG_p100m5->Draw(TString(pv.plotvar)+TString(">>signal_a0w_100"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_3 WWA Histogram..."<<std::endl;
  treeKOG_p80m5->Draw(TString(pv.plotvar)+TString(">>signal_a0w_80"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_4 WWA Histogram..."<<std::endl;
  treeKOG_m80m5->Draw(TString(pv.plotvar)+TString(">>signal_a0w_m80"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_5 WWA Histogram..."<<std::endl;
  treeKOG_m100m5->Draw(TString(pv.plotvar)+TString(">>signal_a0w_m100"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_6 WWA Histogram..."<<std::endl;
  treeKOG_m140m5->Draw(TString(pv.plotvar)+TString(">>signal_a0w_m140"), the_cutKfac, "goff");

  signal_a0w_140->AddBinContent(pv.NBINS,signal_a0w_140->GetBinContent(pv.NBINS+1));signal_a0w_140->SetBinContent(pv.NBINS+1,0.);
  signal_a0w_100->AddBinContent(pv.NBINS,signal_a0w_100->GetBinContent(pv.NBINS+1));signal_a0w_100->SetBinContent(pv.NBINS+1,0.);
  signal_a0w_80->AddBinContent(pv.NBINS,signal_a0w_80->GetBinContent(pv.NBINS+1));signal_a0w_80->SetBinContent(pv.NBINS+1,0.);
  signal_a0w_m80->AddBinContent(pv.NBINS,signal_a0w_m80->GetBinContent(pv.NBINS+1));signal_a0w_m80->SetBinContent(pv.NBINS+1,0.);
  signal_a0w_m100->AddBinContent(pv.NBINS,signal_a0w_m100->GetBinContent(pv.NBINS+1));signal_a0w_m100->SetBinContent(pv.NBINS+1,0.);
  signal_a0w_m140->AddBinContent(pv.NBINS,signal_a0w_m140->GetBinContent(pv.NBINS+1));signal_a0w_m140->SetBinContent(pv.NBINS+1,0.);


  /////////////////////////
  // Normalize each sample:
  std::cout<<"\nScale Histograms..."<<std::endl;
  th1wwa->Scale(WWA_scale);
  th1wwa2->Scale(WWA2_scale);

  signal_a0w_140->Scale(KOG_p140m5_scale);
  signal_a0w_100->Scale(KOG_p100m5_scale);
  signal_a0w_80->Scale(KOG_p80m5_scale);
  signal_a0w_m80->Scale(KOG_m80m5_scale);
  signal_a0w_m100->Scale(KOG_m100m5_scale);
  signal_a0w_m140->Scale(KOG_m140m5_scale);


  ///////////////////////////
  // Combine certain samples:
  th1wwa->Add(th1wwa2,1);

  signal_a0w_140->Divide(th1wwa);
  signal_a0w_100->Divide(th1wwa);
  signal_a0w_80->Divide(th1wwa);
  signal_a0w_m80->Divide(th1wwa);
  signal_a0w_m100->Divide(th1wwa);
  signal_a0w_m140->Divide(th1wwa);


  ///////////////////////////
  //Fill Parabolic Histogram:
  TH1* bin_1 = new TH1D("bin_1","bin_1",281,-140.5E-5,140.5E-5);
  TH1* bin_2 = new TH1D("bin_2","bin_2",281,-140.5E-5,140.5E-5);
  TH1* bin_3 = new TH1D("bin_3","bin_3",281,-140.5E-5,140.5E-5);
  TH1* bin_4 = new TH1D("bin_4","bin_4",281,-140.5E-5,140.5E-5);
  TH1* bin_5 = new TH1D("bin_5","bin_5",281,-140.5E-5,140.5E-5);
  TH1* bin_6 = new TH1D("bin_6","bin_6",281,-140.5E-5,140.5E-5);
  TH1* bin_7 = new TH1D("bin_7","bin_7",281,-140.5E-5,140.5E-5);
  TH1* bin_8 = new TH1D("bin_8","bin_8",281,-140.5E-5,140.5E-5);
  TH1* bin_9 = new TH1D("bin_9","bin_9",281,-140.5E-5,140.5E-5);
  TH1* bin_10 = new TH1D("bin_10","bin_10",281,-140.5E-5,140.5E-5);


  bin_1->SetBinContent(1,signal_a0w_m140->GetBinContent(1));
  bin_1->SetBinContent(41,signal_a0w_m100->GetBinContent(1));
  bin_1->SetBinContent(61,signal_a0w_m80->GetBinContent(1));
  bin_1->SetBinContent(141,1);
  bin_1->SetBinContent(221,signal_a0w_80->GetBinContent(1));
  bin_1->SetBinContent(241,signal_a0w_100->GetBinContent(1));
  bin_1->SetBinContent(281,signal_a0w_140->GetBinContent(1));

  bin_2->SetBinContent(1,signal_a0w_m140->GetBinContent(2));
  bin_2->SetBinContent(41,signal_a0w_m100->GetBinContent(2));
  bin_2->SetBinContent(61,signal_a0w_m80->GetBinContent(2));
  bin_2->SetBinContent(141,1);
  bin_2->SetBinContent(221,signal_a0w_80->GetBinContent(2));
  bin_2->SetBinContent(241,signal_a0w_100->GetBinContent(2));
  bin_2->SetBinContent(281,signal_a0w_140->GetBinContent(2));

  bin_3->SetBinContent(1,signal_a0w_m140->GetBinContent(3));
  bin_3->SetBinContent(41,signal_a0w_m100->GetBinContent(3));
  bin_3->SetBinContent(61,signal_a0w_m80->GetBinContent(3));
  bin_3->SetBinContent(141,1);
  bin_3->SetBinContent(221,signal_a0w_80->GetBinContent(3));
  bin_3->SetBinContent(241,signal_a0w_100->GetBinContent(3));
  bin_3->SetBinContent(281,signal_a0w_140->GetBinContent(3));

  bin_4->SetBinContent(1,signal_a0w_m140->GetBinContent(4));
  bin_4->SetBinContent(41,signal_a0w_m100->GetBinContent(4));
  bin_4->SetBinContent(61,signal_a0w_m80->GetBinContent(4));
  bin_4->SetBinContent(141,1);
  bin_4->SetBinContent(221,signal_a0w_80->GetBinContent(4));
  bin_4->SetBinContent(241,signal_a0w_100->GetBinContent(4));
  bin_4->SetBinContent(281,signal_a0w_140->GetBinContent(4));

  bin_5->SetBinContent(1,signal_a0w_m140->GetBinContent(5));
  bin_5->SetBinContent(41,signal_a0w_m100->GetBinContent(5));
  bin_5->SetBinContent(61,signal_a0w_m80->GetBinContent(5));
  bin_5->SetBinContent(141,1);
  bin_5->SetBinContent(221,signal_a0w_80->GetBinContent(5));
  bin_5->SetBinContent(241,signal_a0w_100->GetBinContent(5));
  bin_5->SetBinContent(281,signal_a0w_140->GetBinContent(5));

  bin_6->SetBinContent(1,signal_a0w_m140->GetBinContent(6));
  bin_6->SetBinContent(41,signal_a0w_m100->GetBinContent(6));
  bin_6->SetBinContent(61,signal_a0w_m80->GetBinContent(6));
  bin_6->SetBinContent(141,1);
  bin_6->SetBinContent(221,signal_a0w_80->GetBinContent(6));
  bin_6->SetBinContent(241,signal_a0w_100->GetBinContent(6));
  bin_6->SetBinContent(281,signal_a0w_140->GetBinContent(6));

  bin_7->SetBinContent(1,signal_a0w_m140->GetBinContent(7));
  bin_7->SetBinContent(41,signal_a0w_m100->GetBinContent(7));
  bin_7->SetBinContent(61,signal_a0w_m80->GetBinContent(7));
  bin_7->SetBinContent(141,1);
  bin_7->SetBinContent(221,signal_a0w_80->GetBinContent(7));
  bin_7->SetBinContent(241,signal_a0w_100->GetBinContent(7));
  bin_7->SetBinContent(281,signal_a0w_140->GetBinContent(7));

  bin_8->SetBinContent(1,signal_a0w_m140->GetBinContent(8));
  bin_8->SetBinContent(41,signal_a0w_m100->GetBinContent(8));
  bin_8->SetBinContent(61,signal_a0w_m80->GetBinContent(8));
  bin_8->SetBinContent(141,1);
  bin_8->SetBinContent(221,signal_a0w_80->GetBinContent(8));
  bin_8->SetBinContent(241,signal_a0w_100->GetBinContent(8));
  bin_8->SetBinContent(281,signal_a0w_140->GetBinContent(8));

  bin_9->SetBinContent(1,signal_a0w_m140->GetBinContent(9));
  bin_9->SetBinContent(41,signal_a0w_m100->GetBinContent(9));
  bin_9->SetBinContent(61,signal_a0w_m80->GetBinContent(9));
  bin_9->SetBinContent(141,1);
  bin_9->SetBinContent(221,signal_a0w_80->GetBinContent(9));
  bin_9->SetBinContent(241,signal_a0w_100->GetBinContent(9));
  bin_9->SetBinContent(281,signal_a0w_140->GetBinContent(9));

  bin_10->SetBinContent(1,signal_a0w_m140->GetBinContent(10));
  bin_10->SetBinContent(41,signal_a0w_m100->GetBinContent(10));
  bin_10->SetBinContent(61,signal_a0w_m80->GetBinContent(10));
  bin_10->SetBinContent(141,1);
  bin_10->SetBinContent(221,signal_a0w_80->GetBinContent(10));
  bin_10->SetBinContent(241,signal_a0w_100->GetBinContent(10));
  bin_10->SetBinContent(281,signal_a0w_140->GetBinContent(10));


  ////////////////
  // Fit function:
  Char_t para_fit[] = "[0]+[1]*x+[2]*x^2";
  Char_t fitopt[] = "QMR";
  Double_t xmin = -140E-5;
  Double_t xmax = 140E-5;
  Double_t p[3][10];
  TF1 *pfit = new TF1("pfit",para_fit,xmin,xmax);
//  pfit->SetParLimits(1,0.0,1E15);
//  pfit->FixParameter(0,0.0);
//  pfit->SetParameters(10,10);


  /////////////////
  // Fit histogram:
  bin_1->Fit(pfit,fitopt,"sames",xmin,xmax);
  p[0][0] = pfit->GetParameter(0);
  p[1][0] = pfit->GetParameter(1);
  p[2][0] = pfit->GetParameter(2);

  bin_2->Fit(pfit,fitopt,"sames",xmin,xmax);
  p[0][1] = pfit->GetParameter(0);
  p[1][1] = pfit->GetParameter(1);
  p[2][1] = pfit->GetParameter(2);

  bin_3->Fit(pfit,fitopt,"sames",xmin,xmax);
  p[0][2] = pfit->GetParameter(0);
  p[1][2] = pfit->GetParameter(1);
  p[2][2] = pfit->GetParameter(2);

  bin_4->Fit(pfit,fitopt,"sames",xmin,xmax);
  p[0][3] = pfit->GetParameter(0);
  p[1][3] = pfit->GetParameter(1);
  p[2][3] = pfit->GetParameter(2);

  bin_5->Fit(pfit,fitopt,"sames",xmin,xmax);
  p[0][4] = pfit->GetParameter(0);
  p[1][4] = pfit->GetParameter(1);
  p[2][4] = pfit->GetParameter(2);

  bin_6->Fit(pfit,fitopt,"sames",xmin,xmax);
  p[0][5] = pfit->GetParameter(0);
  p[1][5] = pfit->GetParameter(1);
  p[2][5] = pfit->GetParameter(2);

  bin_7->Fit(pfit,fitopt,"sames",xmin,xmax);
  p[0][6] = pfit->GetParameter(0);
  p[1][6] = pfit->GetParameter(1);
  p[2][6] = pfit->GetParameter(2);

  bin_8->Fit(pfit,fitopt,"sames",xmin,xmax);
  p[0][7] = pfit->GetParameter(0);
  p[1][7] = pfit->GetParameter(1);
  p[2][7] = pfit->GetParameter(2);

  bin_9->Fit(pfit,fitopt,"sames",xmin,xmax);
  p[0][8] = pfit->GetParameter(0);
  p[1][8] = pfit->GetParameter(1);
  p[2][8] = pfit->GetParameter(2);

  bin_10->Fit(pfit,fitopt,"sames",xmin,xmax);
  p[0][9] = pfit->GetParameter(0);
  p[1][9] = pfit->GetParameter(1);
  p[2][9] = pfit->GetParameter(2);


  /////////////////////////////
  // Fill parameter histograms:
  TH1* p0 = new TH1D("p0","Parameter 0",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* p1 = new TH1D("p1","Parameter 1",pv.NBINS,pv.MINRange,pv.MAXRange);

  for(Int_t i=1;i<=pv.NBINS;i++){
     p0->SetBinContent(i,p[0][i-1]);
     p1->SetBinContent(i,p[1][i-1]);
  }

/*
  ///////////////////
  // Fit pT-function:
  Char_t pt_fit[] = "[0]+[1]*x+[2]*x^2";
  Char_t fitopt[] = "QMR";
  Double_t xmin = 150;//45;
  Double_t xmax =1050;// 275;
  Double_t pt[2][3];
  TF1 *ptfit = new TF1("ptfit",pt_fit,xmin,xmax);

  p0->Fit(ptfit,fitopt,"sames",xmin,xmax);
  pt[0][0] = ptfit->GetParameter(0);
  pt[0][1] = ptfit->GetParameter(1);
  pt[0][2] = ptfit->GetParameter(2);

  p1->Fit(ptfit,fitopt,"sames",xmin,xmax);
  pt[1][0] = ptfit->GetParameter(0);
  pt[1][1] = ptfit->GetParameter(1);
  pt[1][2] = ptfit->GetParameter(2);
*/

  ////////////////
  // Closure test:
  // ratio = 1 + (pt[0][0]+pt[0][1]*pt+pt[0][2]*pt^2)*KOW + (pt[1][0]+pt[1][1]*pt+[1][2]*pt^2)*KOW^2
  TH1* test = new TH1D("test","Test aQGC Photon ET",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* test2 = new TH1D("test2","Test aQGC Photon ET",pv.NBINS,pv.MINRange,pv.MAXRange);

  for(Int_t j=1;j<=pv.NBINS;j++){

     Double_t value,bincent;
     TAxis* xaxis = test->GetXaxis();
     bincent = xaxis->GetBinCenter(j);

/*     value = p[0][j-1]+p[1][j-1]*(5E-5)+p[2][j-1]*pow(5E-5,2);
     test->SetBinContent(j,value);

     test2->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-5E-5)+p[2][j-1]*pow(-5E-5,2));

  }

  test->SetBinContent(10,1+p[0][9]*(5E-5)+p[1][9]*pow(5E-5,2));
  test2->SetBinContent(10,1+p[0][9]*(-5E-5)+p[1][9]*pow(-5E-5,2));
*/

     value = p[0][j-1]+p[1][j-1]*(140E-5)+p[2][j-1]*pow(140E-5,2);
     test->SetBinContent(j,value);

     test2->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-140E-5)+p[2][j-1]*pow(-140E-5,2));

  }

//  test->SetBinContent(10,1+p[0][9]*(5E-5)+p[1][9]*pow(5E-5,2));
//  test2->SetBinContent(10,1+p[0][9]*(-5E-5)+p[1][9]*pow(-5E-5,2));

  TH1D* test_r = (TH1D*)test->Clone("test_r");
  TH1D* test2_r = (TH1D*)test2->Clone("test2_r");

  test_r->Divide(signal_a0w_140);
  test2_r->Divide(signal_a0w_m140);

  test->Multiply(th1wwa);
  test2->Multiply(th1wwa);
  test->Add(th1wwa,-1);
  test2->Add(th1wwa,-1);


  /////////////////////
  // Simulate new aQGC:
  TH1* signal_a0w_150 = new TH1D("signal_a0w_150","signal_a0w_150",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_153 = new TH1D("signal_a0w_153","signal_a0w_153",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_156 = new TH1D("signal_a0w_156","signal_a0w_156",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_159 = new TH1D("signal_a0w_159","signal_a0w_159",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_162 = new TH1D("signal_a0w_162","signal_a0w_162",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_165 = new TH1D("signal_a0w_165","signal_a0w_165",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_168 = new TH1D("signal_a0w_168","signal_a0w_168",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_171 = new TH1D("signal_a0w_171","signal_a0w_171",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_174 = new TH1D("signal_a0w_174","signal_a0w_174",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_177 = new TH1D("signal_a0w_177","signal_a0w_177",pv.NBINS,pv.MINRange,pv.MAXRange);

  TH1* signal_a0w_m150 = new TH1D("signal_a0w_m150","signal_a0w_-150",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_m153 = new TH1D("signal_a0w_m153","signal_a0w_-153",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_m156 = new TH1D("signal_a0w_m156","signal_a0w_-156",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_m159 = new TH1D("signal_a0w_m159","signal_a0w_-159",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_m162 = new TH1D("signal_a0w_m162","signal_a0w_-162",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_m165 = new TH1D("signal_a0w_m165","signal_a0w_-165",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_m168 = new TH1D("signal_a0w_m168","signal_a0w_-168",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_m171 = new TH1D("signal_a0w_m171","signal_a0w_-171",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_m174 = new TH1D("signal_a0w_m174","signal_a0w_-174",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_m177 = new TH1D("signal_a0w_m177","signal_a0w_-177",pv.NBINS,pv.MINRange,pv.MAXRange);

  signal_a0w_150->Sumw2();
  signal_a0w_153->Sumw2();
  signal_a0w_156->Sumw2();
  signal_a0w_159->Sumw2();
  signal_a0w_162->Sumw2();
  signal_a0w_165->Sumw2();
  signal_a0w_168->Sumw2();
  signal_a0w_171->Sumw2();
  signal_a0w_174->Sumw2();
  signal_a0w_177->Sumw2();
  signal_a0w_m150->Sumw2();
  signal_a0w_m153->Sumw2();
  signal_a0w_m156->Sumw2();
  signal_a0w_m159->Sumw2();
  signal_a0w_m162->Sumw2();
  signal_a0w_m165->Sumw2();
  signal_a0w_m168->Sumw2();
  signal_a0w_m171->Sumw2();
  signal_a0w_m174->Sumw2();
  signal_a0w_m177->Sumw2();


  for(Int_t j=1;j<=pv.NBINS;j++){

     Double_t bincent;
     TAxis* xaxis = test->GetXaxis();
     bincent = xaxis->GetBinCenter(j);

     signal_a0w_m140->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-140E-5)+p[2][j-1]*pow(-140E-5,2));
     signal_a0w_m100->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-100E-5)+p[2][j-1]*pow(-100E-5,2));
     signal_a0w_m80->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-80E-5)+p[2][j-1]*pow(-80E-5,2));

     signal_a0w_m165->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-165E-5)+p[2][j-1]*pow(-165E-5,2));
     signal_a0w_m162->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-162E-5)+p[2][j-1]*pow(-162E-5,2));
     signal_a0w_m159->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-159E-5)+p[2][j-1]*pow(-159E-5,2));
     signal_a0w_m156->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-156E-5)+p[2][j-1]*pow(-156E-5,2));
     signal_a0w_m150->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-150E-5)+p[2][j-1]*pow(-150E-5,2));
     signal_a0w_m153->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-153E-5)+p[2][j-1]*pow(-153E-5,2));
     signal_a0w_m168->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-168E-5)+p[2][j-1]*pow(-168E-5,2));
     signal_a0w_m171->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-171E-5)+p[2][j-1]*pow(-171E-5,2));
     signal_a0w_m174->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-174E-5)+p[2][j-1]*pow(-174E-5,2));
     signal_a0w_m177->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-177E-5)+p[2][j-1]*pow(-177E-5,2));

     signal_a0w_140->SetBinContent(j,p[0][j-1]+p[1][j-1]*(140E-5)+p[2][j-1]*pow(140E-5,2));
     signal_a0w_100->SetBinContent(j,p[0][j-1]+p[1][j-1]*(100E-5)+p[2][j-1]*pow(100E-5,2));
     signal_a0w_80->SetBinContent(j,p[0][j-1]+p[1][j-1]*(80E-5)+p[2][j-1]*pow(80E-5,2));

     signal_a0w_165->SetBinContent(j,p[0][j-1]+p[1][j-1]*(165E-5)+p[2][j-1]*pow(165E-5,2));
     signal_a0w_162->SetBinContent(j,p[0][j-1]+p[1][j-1]*(162E-5)+p[2][j-1]*pow(162E-5,2));
     signal_a0w_159->SetBinContent(j,p[0][j-1]+p[1][j-1]*(159E-5)+p[2][j-1]*pow(159E-5,2));
     signal_a0w_156->SetBinContent(j,p[0][j-1]+p[1][j-1]*(156E-5)+p[2][j-1]*pow(156E-5,2));
     signal_a0w_153->SetBinContent(j,p[0][j-1]+p[1][j-1]*(153E-5)+p[2][j-1]*pow(153E-5,2));
     signal_a0w_150->SetBinContent(j,p[0][j-1]+p[1][j-1]*(150E-5)+p[2][j-1]*pow(150E-5,2));
     signal_a0w_168->SetBinContent(j,p[0][j-1]+p[1][j-1]*(168E-5)+p[2][j-1]*pow(168E-5,2));
     signal_a0w_171->SetBinContent(j,p[0][j-1]+p[1][j-1]*(171E-5)+p[2][j-1]*pow(171E-5,2));
     signal_a0w_174->SetBinContent(j,p[0][j-1]+p[1][j-1]*(174E-5)+p[2][j-1]*pow(174E-5,2));
     signal_a0w_177->SetBinContent(j,p[0][j-1]+p[1][j-1]*(177E-5)+p[2][j-1]*pow(177E-5,2));

  }
/*
  signal_a0w_m140->SetBinContent(10,1+p[0][9]*(-140E-5)+p[1][9]*pow(-140E-5,2));
  signal_a0w_m100->SetBinContent(10,1+p[0][9]*(-100E-5)+p[1][9]*pow(-100E-5,2));
  signal_a0w_m80->SetBinContent(10,1+p[0][9]*(-80E-5)+p[1][9]*pow(-80E-5,2));

  signal_a0w_m165->SetBinContent(10,1+p[0][9]*(-165E-5)+p[1][9]*pow(-165E-5,2));
  signal_a0w_m162->SetBinContent(10,1+p[0][9]*(-162E-5)+p[1][9]*pow(-162E-5,2));
  signal_a0w_m159->SetBinContent(10,1+p[0][9]*(-159E-5)+p[1][9]*pow(-159E-5,2));
  signal_a0w_m156->SetBinContent(10,1+p[0][9]*(-156E-5)+p[1][9]*pow(-156E-5,2));
  signal_a0w_m153->SetBinContent(10,1+p[0][9]*(-153E-5)+p[1][9]*pow(-153E-5,2));
  signal_a0w_m150->SetBinContent(10,1+p[0][9]*(-150E-5)+p[1][9]*pow(-150E-5,2));
  signal_a0w_m168->SetBinContent(10,1+p[0][9]*(-168E-5)+p[1][9]*pow(-168E-5,2));
  signal_a0w_m171->SetBinContent(10,1+p[0][9]*(-171E-5)+p[1][9]*pow(-171E-5,2));
  signal_a0w_m174->SetBinContent(10,1+p[0][9]*(-174E-5)+p[1][9]*pow(-174E-5,2));
  signal_a0w_m177->SetBinContent(10,1+p[0][9]*(-177E-5)+p[1][9]*pow(-177E-5,2));

  signal_a0w_140->SetBinContent(10,1+p[0][9]*(140E-5)+p[1][9]*pow(140E-5,2));
  signal_a0w_100->SetBinContent(10,1+p[0][9]*(100E-5)+p[1][9]*pow(100E-5,2));
  signal_a0w_80->SetBinContent(10,1+p[0][9]*(80E-5)+p[1][9]*pow(80E-5,2));

  signal_a0w_165->SetBinContent(10,1+p[0][9]*(165E-5)+p[1][9]*pow(165E-5,2));
  signal_a0w_162->SetBinContent(10,1+p[0][9]*(162E-5)+p[1][9]*pow(162E-5,2));
  signal_a0w_159->SetBinContent(10,1+p[0][9]*(159E-5)+p[1][9]*pow(159E-5,2));
  signal_a0w_156->SetBinContent(10,1+p[0][9]*(156E-5)+p[1][9]*pow(156E-5,2));
  signal_a0w_153->SetBinContent(10,1+p[0][9]*(153E-5)+p[1][9]*pow(153E-5,2));
  signal_a0w_150->SetBinContent(10,1+p[0][9]*(150E-5)+p[1][9]*pow(150E-5,2));
  signal_a0w_168->SetBinContent(10,1+p[0][9]*(168E-5)+p[1][9]*pow(168E-5,2));
  signal_a0w_171->SetBinContent(10,1+p[0][9]*(171E-5)+p[1][9]*pow(171E-5,2));
  signal_a0w_174->SetBinContent(10,1+p[0][9]*(174E-5)+p[1][9]*pow(174E-5,2));
  signal_a0w_177->SetBinContent(10,1+p[0][9]*(177E-5)+p[1][9]*pow(177E-5,2));
*/
  signal_a0w_m140->Multiply(th1wwa);
  signal_a0w_m100->Multiply(th1wwa);
  signal_a0w_m80->Multiply(th1wwa);

  signal_a0w_m165->Multiply(th1wwa);
  signal_a0w_m162->Multiply(th1wwa);
  signal_a0w_m159->Multiply(th1wwa);
  signal_a0w_m156->Multiply(th1wwa);
  signal_a0w_m153->Multiply(th1wwa);
  signal_a0w_m150->Multiply(th1wwa);
  signal_a0w_m168->Multiply(th1wwa);
  signal_a0w_m171->Multiply(th1wwa);
  signal_a0w_m174->Multiply(th1wwa);
  signal_a0w_m177->Multiply(th1wwa);

  signal_a0w_140->Multiply(th1wwa);
  signal_a0w_100->Multiply(th1wwa);
  signal_a0w_80->Multiply(th1wwa);

  signal_a0w_165->Multiply(th1wwa);
  signal_a0w_162->Multiply(th1wwa);
  signal_a0w_159->Multiply(th1wwa);
  signal_a0w_156->Multiply(th1wwa);
  signal_a0w_153->Multiply(th1wwa);
  signal_a0w_150->Multiply(th1wwa);
  signal_a0w_168->Multiply(th1wwa);
  signal_a0w_171->Multiply(th1wwa);
  signal_a0w_174->Multiply(th1wwa);
  signal_a0w_177->Multiply(th1wwa);

  //For conveners:
  TH1D *signal_a0w_m165_pT = (TH1D*)signal_a0w_m165->Clone("signal_a0w_m165_pT");
//  signal_a0w_m100_pT->Scale(1.185/2.1);
  signal_a0w_m165_pT->Divide(th1wwa);


  signal_a0w_m140->Add(th1wwa,-1);
  signal_a0w_m100->Add(th1wwa,-1);
  signal_a0w_m80->Add(th1wwa,-1);

  signal_a0w_m165->Add(th1wwa,-1);
  signal_a0w_m162->Add(th1wwa,-1);
  signal_a0w_m159->Add(th1wwa,-1);
  signal_a0w_m156->Add(th1wwa,-1);
  signal_a0w_m153->Add(th1wwa,-1);
  signal_a0w_m150->Add(th1wwa,-1);
  signal_a0w_m168->Add(th1wwa,-1);
  signal_a0w_m171->Add(th1wwa,-1);
  signal_a0w_m174->Add(th1wwa,-1);
  signal_a0w_m177->Add(th1wwa,-1);

  signal_a0w_140->Add(th1wwa,-1);
  signal_a0w_100->Add(th1wwa,-1);
  signal_a0w_80->Add(th1wwa,-1);

  signal_a0w_165->Add(th1wwa,-1);
  signal_a0w_162->Add(th1wwa,-1);
  signal_a0w_159->Add(th1wwa,-1);
  signal_a0w_156->Add(th1wwa,-1);
  signal_a0w_153->Add(th1wwa,-1);
  signal_a0w_150->Add(th1wwa,-1);
  signal_a0w_168->Add(th1wwa,-1);
  signal_a0w_171->Add(th1wwa,-1);
  signal_a0w_174->Add(th1wwa,-1);
  signal_a0w_177->Add(th1wwa,-1);


  signal_a0w_m140->Scale(1.185/2.1);
  signal_a0w_m100->Scale(1.185/2.1);
  signal_a0w_m80->Scale(1.185/2.1);

  signal_a0w_m165->Scale(1.185/2.1);
  signal_a0w_m162->Scale(1.185/2.1);
  signal_a0w_m159->Scale(1.185/2.1);
  signal_a0w_m156->Scale(1.185/2.1);
  signal_a0w_m153->Scale(1.185/2.1);
  signal_a0w_m150->Scale(1.185/2.1);
  signal_a0w_m168->Scale(1.185/2.1);
  signal_a0w_m171->Scale(1.185/2.1);
  signal_a0w_m174->Scale(1.185/2.1);
  signal_a0w_m177->Scale(1.185/2.1);

  signal_a0w_140->Scale(1.185/2.1);
  signal_a0w_100->Scale(1.185/2.1);
  signal_a0w_80->Scale(1.185/2.1);

  signal_a0w_165->Scale(1.185/2.1);
  signal_a0w_162->Scale(1.185/2.1);
  signal_a0w_159->Scale(1.185/2.1);
  signal_a0w_156->Scale(1.185/2.1);
  signal_a0w_153->Scale(1.185/2.1);
  signal_a0w_150->Scale(1.185/2.1);
  signal_a0w_168->Scale(1.185/2.1);
  signal_a0w_171->Scale(1.185/2.1);
  signal_a0w_174->Scale(1.185/2.1);
  signal_a0w_177->Scale(1.185/2.1);


/*
  signal_a0w_150->Sumw2();
  signal_a0w_153->Sumw2();
  signal_a0w_80->Sumw2();
  signal_a0w_156->Sumw2();
  signal_a0w_159->Sumw2();
  signal_a0w_162->Sumw2();
  signal_a0w_165->Sumw2();
  signal_a0w_100->Sumw2();
  signal_a0w_168->Sumw2();
  signal_a0w_171->Sumw2();
  signal_a0w_174->Sumw2();
  signal_a0w_177->Sumw2();
  signal_a0w_140->Sumw2();

  signal_a0w_m150->Sumw2();
  signal_a0w_m153->Sumw2();
  signal_a0w_m80->Sumw2();
  signal_a0w_m156->Sumw2();
  signal_a0w_m159->Sumw2();
  signal_a0w_m162->Sumw2();
  signal_a0w_m165->Sumw2();
  signal_a0w_m100->Sumw2();
  signal_a0w_m168->Sumw2();
  signal_a0w_m171->Sumw2();
  signal_a0w_m174->Sumw2();
  signal_a0w_m177->Sumw2();
  signal_a0w_m140->Sumw2();
*/
/*  // Adding 28% Signal K-factor Systematic uncertainty
  for(int hi=1;hi<=pv.NBINS;hi++){

     fperr = pow(signal_a0w_m150->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m150->GetBinContent(hi),2);
     signal_a0w_m150->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m153->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m153->GetBinContent(hi),2);
     signal_a0w_m153->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m80->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m80->GetBinContent(hi),2);
     signal_a0w_m80->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m156->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m156->GetBinContent(hi),2);
     signal_a0w_m156->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m159->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m159->GetBinContent(hi),2);
     signal_a0w_m159->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m162->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m162->GetBinContent(hi),2);
     signal_a0w_m162->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m165->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m165->GetBinContent(hi),2);
     signal_a0w_m165->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m100->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m100->GetBinContent(hi),2);
     signal_a0w_m100->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m168->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m168->GetBinContent(hi),2);
     signal_a0w_m168->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m171->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m171->GetBinContent(hi),2);
     signal_a0w_m171->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m174->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m174->GetBinContent(hi),2);
     signal_a0w_m174->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m177->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m177->GetBinContent(hi),2);
     signal_a0w_m177->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m140->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m140->GetBinContent(hi),2);
     signal_a0w_m140->SetBinError(hi,sqrt(fperr));


     fperr = pow(signal_a0w_150->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_150->GetBinContent(hi),2);
     signal_a0w_150->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_153->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_153->GetBinContent(hi),2);
     signal_a0w_153->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_80->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_80->GetBinContent(hi),2);
     signal_a0w_80->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_156->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_156->GetBinContent(hi),2);
     signal_a0w_156->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_159->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_159->GetBinContent(hi),2);
     signal_a0w_159->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_162->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_162->GetBinContent(hi),2);
     signal_a0w_162->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_165->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_165->GetBinContent(hi),2);
     signal_a0w_165->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_100->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_100->GetBinContent(hi),2);
     signal_a0w_100->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_168->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_168->GetBinContent(hi),2);
     signal_a0w_168->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_171->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_171->GetBinContent(hi),2);
     signal_a0w_171->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_174->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_174->GetBinContent(hi),2);
     signal_a0w_174->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_177->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_177->GetBinContent(hi),2);
     signal_a0w_177->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_140->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_140->GetBinContent(hi),2);
     signal_a0w_140->SetBinError(hi,sqrt(fperr));

  }
*/

  ////////////////////////
  // Set histogram labels:
  const double BINWIDTH = ((pv.MAXRange-pv.MINRange)/pv.NBINS);
  char tmpc[100];    sprintf(tmpc,"Events / %.1f GeV",BINWIDTH);
  if (pv.slog==1)    sprintf(tmpc,"Events / %.1f",BINWIDTH);
  if (pv.slog==2)    sprintf(tmpc,"Events / %.2f",BINWIDTH);
  if (pv.slog==3)    sprintf(tmpc,"Events / %.0f GeV",BINWIDTH);
  if (pv.slog==6)    sprintf(tmpc,"Events / %.2f rad",BINWIDTH);

  signal_a0w_140->SetYTitle(tmpc);
  signal_a0w_140->GetXaxis()->SetTitle(pv.xlabel);
  signal_a0w_140->GetYaxis()->CenterTitle(true);

  signal_a0w_100->SetYTitle(tmpc);
  signal_a0w_100->GetXaxis()->SetTitle(pv.xlabel);
  signal_a0w_100->GetYaxis()->CenterTitle(true);

  signal_a0w_80->SetYTitle(tmpc);
  signal_a0w_80->GetXaxis()->SetTitle(pv.xlabel);
  signal_a0w_80->GetYaxis()->CenterTitle(true);

  signal_a0w_m80->SetYTitle(tmpc);
  signal_a0w_m80->GetXaxis()->SetTitle(pv.xlabel);
  signal_a0w_m80->GetYaxis()->CenterTitle(true);

  signal_a0w_m100->SetYTitle(tmpc);
  signal_a0w_m100->GetXaxis()->SetTitle(pv.xlabel);
  signal_a0w_m100->GetYaxis()->CenterTitle(true);

  signal_a0w_m140->SetYTitle(tmpc);
  signal_a0w_m140->GetXaxis()->SetTitle(pv.xlabel);
  signal_a0w_m140->GetYaxis()->CenterTitle(true);


  ////////////////////////////////////////////////////////
  // Save Anomalous Signal histograms to output ROOT file:
  std::cout<<"Save Histograms...\n"<<std::endl;
  f.cd();
  signal_a0w_140->Write();
  signal_a0w_100->Write();
  signal_a0w_80->Write();
  signal_a0w_m80->Write();
  signal_a0w_m100->Write();
  signal_a0w_m140->Write();

  bin_1->Write();
  bin_2->Write();
  bin_3->Write();
  bin_4->Write();
  bin_5->Write();
  bin_6->Write();
  bin_7->Write();
  bin_8->Write();
  bin_9->Write();
  bin_10->Write();

  p0->Write();
  p1->Write();
  test->Write();
  test2->Write();
  test_r->Write();
  test2_r->Write();

  signal_a0w_m165->Write();
  signal_a0w_m162->Write();
  signal_a0w_m159->Write();
  signal_a0w_m156->Write();
  signal_a0w_m153->Write();
  signal_a0w_m150->Write();
  signal_a0w_m168->Write();
  signal_a0w_m171->Write();
  signal_a0w_m174->Write();
  signal_a0w_m177->Write();

  signal_a0w_165->Write();
  signal_a0w_162->Write();
  signal_a0w_159->Write();
  signal_a0w_156->Write();
  signal_a0w_153->Write();
  signal_a0w_150->Write();
  signal_a0w_168->Write();
  signal_a0w_171->Write();
  signal_a0w_174->Write();
  signal_a0w_177->Write();

  //For conveners
//  signal_a0w_m165_pT->Write();
//  th1wwa->Write();

}// End Main function
