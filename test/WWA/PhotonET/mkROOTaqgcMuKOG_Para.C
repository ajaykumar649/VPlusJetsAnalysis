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

  const double KOG_m5m5_scale     = 2.1*0.0470065 * intLUMI/194029;
  const double KOG_m2m5_scale     = 2.1*0.0249555 * intLUMI/195494;
  const double KOG_m3m5_scale     = 2.1*0.0302425 * intLUMI/196004;
  const double KOG_p5m5_scale     = 2.1*0.046106 * intLUMI/184331;
  const double KOG_p2m5_scale     = 2.1*0.0245765 * intLUMI/197493;
  const double KOG_p3m5_scale     = 2.1*0.029646 * intLUMI/139920;


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

  TFile *KOG_m5m5_file,*KOG_m3m5_file,*KOG_m2m5_file,*KOG_p2m5_file,*KOG_p3m5_file,*KOG_p5m5_file;


  //////////////////////////////
  // Open each sample ROOT file:
  wwaShape_file = new TFile("InData_New/RD_mu_qq_wpwma_wp_qq_wm_lvl.root");
  wwa2Shape_file = new TFile("InData_New/RD_mu_qq_wpwma_wp_lvl_wm_qq.root");

  KOG_m5m5_file = new TFile("InData_New/RD_mu_KOG_m5m5MG_CMSSW532.root");
  KOG_m3m5_file = new TFile("InData_New/RD_mu_KOG_m3m5MG_CMSSW532.root");
  KOG_m2m5_file = new TFile("InData_New/RD_mu_KOG_m2m5MG_CMSSW532.root");
  KOG_p2m5_file = new TFile("InData_New/RD_mu_KOG_p2m5MG_CMSSW532.root");
  KOG_p3m5_file = new TFile("InData_New/RD_mu_KOG_p3m5MG_CMSSW532.root");
  KOG_p5m5_file = new TFile("InData_New/RD_mu_KOG_p5m5MG_CMSSW532.root");


  ///////////////////////////////////////////////////
  // Retrieve ROOT tree with kinematic distributions:
  TTree* treewwa    = (TTree*)    wwaShape_file->Get("WJet");
  TTree* treewwa2    = (TTree*)    wwa2Shape_file->Get("WJet");

  TTree* treeKOG_m5m5 = (TTree*) KOG_m5m5_file->Get("WJet");
  TTree* treeKOG_m3m5 = (TTree*) KOG_m3m5_file->Get("WJet");
  TTree* treeKOG_m2m5 = (TTree*) KOG_m2m5_file->Get("WJet");
  TTree* treeKOG_p2m5 = (TTree*) KOG_p2m5_file->Get("WJet");
  TTree* treeKOG_p3m5 = (TTree*) KOG_p3m5_file->Get("WJet");
  TTree* treeKOG_p5m5 = (TTree*) KOG_p5m5_file->Get("WJet");


  ////////////////////////////////////////////////////////////
  // Create kinematic-distribution histograms for each sample:
  TH1* th1wwa = new TH1D("th1wwa", "th1wwa", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1wwa2 = new TH1D("th1wwa2", "th1wwa2", pv.NBINS, pv.MINRange, pv.MAXRange);

  TH1* signal_a0w_50 = new TH1D("signal_a0w_50","signal_a0w_5",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_a0w_30 = new TH1D("signal_a0w_30","signal_a0w_3",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_a0w_20 = new TH1D("signal_a0w_20","signal_a0w_2",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_a0w_m20 = new TH1D("signal_a0w_m20","signal_a0w_-2",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_a0w_m30 = new TH1D("signal_a0w_m30","signal_a0w_-3",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_a0w_m50 = new TH1D("signal_a0w_m50","signal_a0w_-5",pv.NBINS, pv.MINRange, pv.MAXRange);


  /////////////////////////////////////////////////////////////////////////
  // Specify histograms to store Sum of Squares of Weights for each sample:
  th1wwa->Sumw2();
  th1wwa2->Sumw2();
/*
  signal_a0w_5->Sumw2();
  signal_a0w_3->Sumw2();
  signal_a0w_2->Sumw2();
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
  treeKOG_p5m5->Draw(TString(pv.plotvar)+TString(">>signal_a0w_m50"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_2 WWA Histogram..."<<std::endl;
  treeKOG_p3m5->Draw(TString(pv.plotvar)+TString(">>signal_a0w_m30"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_3 WWA Histogram..."<<std::endl;
  treeKOG_p2m5->Draw(TString(pv.plotvar)+TString(">>signal_a0w_m20"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_4 WWA Histogram..."<<std::endl;
  treeKOG_m2m5->Draw(TString(pv.plotvar)+TString(">>signal_a0w_20"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_5 WWA Histogram..."<<std::endl;
  treeKOG_m3m5->Draw(TString(pv.plotvar)+TString(">>signal_a0w_30"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_6 WWA Histogram..."<<std::endl;
  treeKOG_m5m5->Draw(TString(pv.plotvar)+TString(">>signal_a0w_50"), the_cutKfac, "goff");

  signal_a0w_50->AddBinContent(pv.NBINS,signal_a0w_50->GetBinContent(pv.NBINS+1));signal_a0w_50->SetBinContent(pv.NBINS+1,0.);
  signal_a0w_30->AddBinContent(pv.NBINS,signal_a0w_30->GetBinContent(pv.NBINS+1));signal_a0w_30->SetBinContent(pv.NBINS+1,0.);
  signal_a0w_20->AddBinContent(pv.NBINS,signal_a0w_20->GetBinContent(pv.NBINS+1));signal_a0w_20->SetBinContent(pv.NBINS+1,0.);
  signal_a0w_m20->AddBinContent(pv.NBINS,signal_a0w_m20->GetBinContent(pv.NBINS+1));signal_a0w_m20->SetBinContent(pv.NBINS+1,0.);
  signal_a0w_m30->AddBinContent(pv.NBINS,signal_a0w_m30->GetBinContent(pv.NBINS+1));signal_a0w_m30->SetBinContent(pv.NBINS+1,0.);
  signal_a0w_m50->AddBinContent(pv.NBINS,signal_a0w_m50->GetBinContent(pv.NBINS+1));signal_a0w_m50->SetBinContent(pv.NBINS+1,0.);


  /////////////////////////
  // Normalize each sample:
  std::cout<<"\nScale Histograms..."<<std::endl;
  th1wwa->Scale(WWA_scale);
  th1wwa2->Scale(WWA2_scale);

  signal_a0w_50->Scale(KOG_p5m5_scale);
  signal_a0w_30->Scale(KOG_p3m5_scale);
  signal_a0w_20->Scale(KOG_p2m5_scale);
  signal_a0w_m20->Scale(KOG_m2m5_scale);
  signal_a0w_m30->Scale(KOG_m3m5_scale);
  signal_a0w_m50->Scale(KOG_m5m5_scale);


  ///////////////////////////
  // Combine certain samples:
  th1wwa->Add(th1wwa2,1);

  signal_a0w_50->Divide(th1wwa);
  signal_a0w_30->Divide(th1wwa);
  signal_a0w_20->Divide(th1wwa);
  signal_a0w_m20->Divide(th1wwa);
  signal_a0w_m30->Divide(th1wwa);
  signal_a0w_m50->Divide(th1wwa);


  ///////////////////////////
  //Fill Parabolic Histogram:
  TH1* bin_1 = new TH1D("bin_1","bin_1",11, -5.5E-5, 5.5E-5);
  TH1* bin_2 = new TH1D("bin_2","bin_2",11, -5.5E-5, 5.5E-5);
  TH1* bin_3 = new TH1D("bin_3","bin_3",11, -5.5E-5, 5.5E-5);
  TH1* bin_4 = new TH1D("bin_4","bin_4",11, -5.5E-5, 5.5E-5);
  TH1* bin_5 = new TH1D("bin_5","bin_5",11, -5.5E-5, 5.5E-5);
  TH1* bin_6 = new TH1D("bin_6","bin_6",11, -5.5E-5, 5.5E-5);
  TH1* bin_7 = new TH1D("bin_7","bin_7",11, -5.5E-5, 5.5E-5);
  TH1* bin_8 = new TH1D("bin_8","bin_8",11, -5.5E-5, 5.5E-5);
  TH1* bin_9 = new TH1D("bin_9","bin_9",11, -5.5E-5, 5.5E-5);
  TH1* bin_10 = new TH1D("bin_10","bin_10",11, -5.5E-5, 5.5E-5);


  bin_1->SetBinContent(1,signal_a0w_m50->GetBinContent(1));
  bin_1->SetBinContent(3,signal_a0w_m30->GetBinContent(1));
  bin_1->SetBinContent(4,signal_a0w_m20->GetBinContent(1));
  bin_1->SetBinContent(6,1);
  bin_1->SetBinContent(8,signal_a0w_20->GetBinContent(1));
  bin_1->SetBinContent(9,signal_a0w_30->GetBinContent(1));
  bin_1->SetBinContent(11,signal_a0w_50->GetBinContent(1));

  bin_2->SetBinContent(1,signal_a0w_m50->GetBinContent(2));
  bin_2->SetBinContent(3,signal_a0w_m30->GetBinContent(2));
  bin_2->SetBinContent(4,signal_a0w_m20->GetBinContent(2));
  bin_2->SetBinContent(6,1);
  bin_2->SetBinContent(8,signal_a0w_20->GetBinContent(2));
  bin_2->SetBinContent(9,signal_a0w_30->GetBinContent(2));
  bin_2->SetBinContent(11,signal_a0w_50->GetBinContent(2));

  bin_3->SetBinContent(1,signal_a0w_m50->GetBinContent(3));
  bin_3->SetBinContent(3,signal_a0w_m30->GetBinContent(3));
  bin_3->SetBinContent(4,signal_a0w_m20->GetBinContent(3));
  bin_3->SetBinContent(6,1);
  bin_3->SetBinContent(8,signal_a0w_20->GetBinContent(3));
  bin_3->SetBinContent(9,signal_a0w_30->GetBinContent(3));
  bin_3->SetBinContent(11,signal_a0w_50->GetBinContent(3));

  bin_4->SetBinContent(1,signal_a0w_m50->GetBinContent(4));
  bin_4->SetBinContent(3,signal_a0w_m30->GetBinContent(4));
  bin_4->SetBinContent(4,signal_a0w_m20->GetBinContent(4));
  bin_4->SetBinContent(6,1);
  bin_4->SetBinContent(8,signal_a0w_20->GetBinContent(4));
  bin_4->SetBinContent(9,signal_a0w_30->GetBinContent(4));
  bin_4->SetBinContent(11,signal_a0w_50->GetBinContent(4));

  bin_5->SetBinContent(1,signal_a0w_m50->GetBinContent(5));
  bin_5->SetBinContent(3,signal_a0w_m30->GetBinContent(5));
  bin_5->SetBinContent(4,signal_a0w_m20->GetBinContent(5));
  bin_5->SetBinContent(6,1);
  bin_5->SetBinContent(8,signal_a0w_20->GetBinContent(5));
  bin_5->SetBinContent(9,signal_a0w_30->GetBinContent(5));
  bin_5->SetBinContent(11,signal_a0w_50->GetBinContent(5));

  bin_6->SetBinContent(1,signal_a0w_m50->GetBinContent(6));
  bin_6->SetBinContent(3,signal_a0w_m30->GetBinContent(6));
  bin_6->SetBinContent(4,signal_a0w_m20->GetBinContent(6));
  bin_6->SetBinContent(6,1);
  bin_6->SetBinContent(8,signal_a0w_20->GetBinContent(6));
  bin_6->SetBinContent(9,signal_a0w_30->GetBinContent(6));
  bin_6->SetBinContent(11,signal_a0w_50->GetBinContent(6));

  bin_7->SetBinContent(1,signal_a0w_m50->GetBinContent(7));
  bin_7->SetBinContent(3,signal_a0w_m30->GetBinContent(7));
  bin_7->SetBinContent(4,signal_a0w_m20->GetBinContent(7));
  bin_7->SetBinContent(6,1);
  bin_7->SetBinContent(8,signal_a0w_20->GetBinContent(7));
  bin_7->SetBinContent(9,signal_a0w_30->GetBinContent(7));
  bin_7->SetBinContent(11,signal_a0w_50->GetBinContent(7));

  bin_8->SetBinContent(1,signal_a0w_m50->GetBinContent(8));
  bin_8->SetBinContent(3,signal_a0w_m30->GetBinContent(8));
  bin_8->SetBinContent(4,signal_a0w_m20->GetBinContent(8));
  bin_8->SetBinContent(6,1);
  bin_8->SetBinContent(8,signal_a0w_20->GetBinContent(8));
  bin_8->SetBinContent(9,signal_a0w_30->GetBinContent(8));
  bin_8->SetBinContent(11,signal_a0w_50->GetBinContent(8));

  bin_9->SetBinContent(1,signal_a0w_m50->GetBinContent(9));
  bin_9->SetBinContent(3,signal_a0w_m30->GetBinContent(9));
  bin_9->SetBinContent(4,signal_a0w_m20->GetBinContent(9));
  bin_9->SetBinContent(6,1);
  bin_9->SetBinContent(8,signal_a0w_20->GetBinContent(9));
  bin_9->SetBinContent(9,signal_a0w_30->GetBinContent(9));
  bin_9->SetBinContent(11,signal_a0w_50->GetBinContent(9));

  bin_10->SetBinContent(1,signal_a0w_m50->GetBinContent(10));
  bin_10->SetBinContent(3,signal_a0w_m30->GetBinContent(10));
  bin_10->SetBinContent(4,signal_a0w_m20->GetBinContent(10));
  bin_10->SetBinContent(6,1);
  bin_10->SetBinContent(8,signal_a0w_20->GetBinContent(10));
  bin_10->SetBinContent(9,signal_a0w_30->GetBinContent(10));
  bin_10->SetBinContent(11,signal_a0w_50->GetBinContent(10));


  ////////////////
  // Fit function:
  Char_t para_fit[] = "[0]+[1]*x+[2]*x^2";
  Char_t fitopt[] = "QMR";
  Double_t xmin = -5E-5;
  Double_t xmax = 5E-5;
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

     value = p[0][j-1]+p[1][j-1]*(5E-5)+p[2][j-1]*pow(5E-5,2);
     test->SetBinContent(j,value);

     test2->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-5E-5)+p[2][j-1]*pow(-5E-5,2));

  }

//  test->SetBinContent(10,1+p[0][9]*(5E-5)+p[1][9]*pow(5E-5,2));
//  test2->SetBinContent(10,1+p[0][9]*(-5E-5)+p[1][9]*pow(-5E-5,2));

  TH1D* test_r = (TH1D*)test->Clone("test_r");
  TH1D* test2_r = (TH1D*)test2->Clone("test2_r");

  test_r->Divide(signal_a0w_50);
  test2_r->Divide(signal_a0w_m50);

  test->Multiply(th1wwa);
  test2->Multiply(th1wwa);
  test->Add(th1wwa,-1);
  test2->Add(th1wwa,-1);


  /////////////////////
  // Simulate new aQGC:
  TH1* signal_a0w_16 = new TH1D("signal_a0w_16","signal_a0w_1p6",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_18 = new TH1D("signal_a0w_18","signal_a0w_1p8",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_22 = new TH1D("signal_a0w_22","signal_a0w_2p2",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_24 = new TH1D("signal_a0w_24","signal_a0w_2p4",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_26 = new TH1D("signal_a0w_26","signal_a0w_2p6",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_28 = new TH1D("signal_a0w_28","signal_a0w_2p8",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_32 = new TH1D("signal_a0w_32","signal_a0w_3p2",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_34 = new TH1D("signal_a0w_34","signal_a0w_3p4",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_36 = new TH1D("signal_a0w_36","signal_a0w_3p6",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_38 = new TH1D("signal_a0w_38","signal_a0w_3p8",pv.NBINS,pv.MINRange,pv.MAXRange);

  TH1* signal_a0w_m16 = new TH1D("signal_a0w_m16","signal_a0w_-1p6",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_m18 = new TH1D("signal_a0w_m18","signal_a0w_-1p8",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_m22 = new TH1D("signal_a0w_m22","signal_a0w_-2p2",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_m24 = new TH1D("signal_a0w_m24","signal_a0w_-2p4",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_m26 = new TH1D("signal_a0w_m26","signal_a0w_-2p6",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_m28 = new TH1D("signal_a0w_m28","signal_a0w_-2p8",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_m32 = new TH1D("signal_a0w_m32","signal_a0w_-3p2",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_m34 = new TH1D("signal_a0w_m34","signal_a0w_-3p4",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_m36 = new TH1D("signal_a0w_m36","signal_a0w_-3p6",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_a0w_m38 = new TH1D("signal_a0w_m38","signal_a0w_-3p8",pv.NBINS,pv.MINRange,pv.MAXRange);

  signal_a0w_16->Sumw2();
  signal_a0w_18->Sumw2();
  signal_a0w_22->Sumw2();
  signal_a0w_24->Sumw2();
  signal_a0w_26->Sumw2();
  signal_a0w_28->Sumw2();
  signal_a0w_32->Sumw2();
  signal_a0w_34->Sumw2();
  signal_a0w_36->Sumw2();
  signal_a0w_38->Sumw2();
  signal_a0w_m16->Sumw2();
  signal_a0w_m18->Sumw2();
  signal_a0w_m22->Sumw2();
  signal_a0w_m24->Sumw2();
  signal_a0w_m26->Sumw2();
  signal_a0w_m28->Sumw2();
  signal_a0w_m32->Sumw2();
  signal_a0w_m34->Sumw2();
  signal_a0w_m36->Sumw2();
  signal_a0w_m38->Sumw2();


  for(Int_t j=1;j<=pv.NBINS;j++){

     Double_t bincent;
     TAxis* xaxis = test->GetXaxis();
     bincent = xaxis->GetBinCenter(j);

     signal_a0w_m50->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-5.E-5)+p[2][j-1]*pow(-5.E-5,2));
     signal_a0w_m30->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-3.E-5)+p[2][j-1]*pow(-3.E-5,2));
     signal_a0w_m20->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-2.E-5)+p[2][j-1]*pow(-2.E-5,2));

     signal_a0w_m28->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-2.8E-5)+p[2][j-1]*pow(-2.8E-5,2));
     signal_a0w_m26->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-2.6E-5)+p[2][j-1]*pow(-2.6E-5,2));
     signal_a0w_m24->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-2.4E-5)+p[2][j-1]*pow(-2.4E-5,2));
     signal_a0w_m22->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-2.2E-5)+p[2][j-1]*pow(-2.2E-5,2));
     signal_a0w_m16->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-1.6E-5)+p[2][j-1]*pow(-1.6E-5,2));
     signal_a0w_m18->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-1.8E-5)+p[2][j-1]*pow(-1.8E-5,2));
     signal_a0w_m32->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-3.2E-5)+p[2][j-1]*pow(-3.2E-5,2));
     signal_a0w_m34->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-3.4E-5)+p[2][j-1]*pow(-3.4E-5,2));
     signal_a0w_m36->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-3.6E-5)+p[2][j-1]*pow(-3.6E-5,2));
     signal_a0w_m38->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-3.8E-5)+p[2][j-1]*pow(-3.8E-5,2));

     signal_a0w_50->SetBinContent(j,p[0][j-1]+p[1][j-1]*(5.E-5)+p[2][j-1]*pow(5.E-5,2));
     signal_a0w_30->SetBinContent(j,p[0][j-1]+p[1][j-1]*(3.E-5)+p[2][j-1]*pow(3.E-5,2));
     signal_a0w_20->SetBinContent(j,p[0][j-1]+p[1][j-1]*(2.E-5)+p[2][j-1]*pow(2.E-5,2));

     signal_a0w_28->SetBinContent(j,p[0][j-1]+p[1][j-1]*(2.8E-5)+p[2][j-1]*pow(2.8E-5,2));
     signal_a0w_26->SetBinContent(j,p[0][j-1]+p[1][j-1]*(2.6E-5)+p[2][j-1]*pow(2.6E-5,2));
     signal_a0w_24->SetBinContent(j,p[0][j-1]+p[1][j-1]*(2.4E-5)+p[2][j-1]*pow(2.4E-5,2));
     signal_a0w_22->SetBinContent(j,p[0][j-1]+p[1][j-1]*(2.2E-5)+p[2][j-1]*pow(2.2E-5,2));
     signal_a0w_18->SetBinContent(j,p[0][j-1]+p[1][j-1]*(1.8E-5)+p[2][j-1]*pow(1.8E-5,2));
     signal_a0w_16->SetBinContent(j,p[0][j-1]+p[1][j-1]*(1.6E-5)+p[2][j-1]*pow(1.6E-5,2));
     signal_a0w_32->SetBinContent(j,p[0][j-1]+p[1][j-1]*(3.2E-5)+p[2][j-1]*pow(3.2E-5,2));
     signal_a0w_34->SetBinContent(j,p[0][j-1]+p[1][j-1]*(3.4E-5)+p[2][j-1]*pow(3.4E-5,2));
     signal_a0w_36->SetBinContent(j,p[0][j-1]+p[1][j-1]*(3.6E-5)+p[2][j-1]*pow(3.6E-5,2));
     signal_a0w_38->SetBinContent(j,p[0][j-1]+p[1][j-1]*(3.8E-5)+p[2][j-1]*pow(3.8E-5,2));

  }
/*
  signal_a0w_m50->SetBinContent(10,1+p[0][9]*(-5.E-5)+p[1][9]*pow(-5.E-5,2));
  signal_a0w_m30->SetBinContent(10,1+p[0][9]*(-3.E-5)+p[1][9]*pow(-3.E-5,2));
  signal_a0w_m20->SetBinContent(10,1+p[0][9]*(-2.E-5)+p[1][9]*pow(-2.E-5,2));

  signal_a0w_m28->SetBinContent(10,1+p[0][9]*(-2.8E-5)+p[1][9]*pow(-2.8E-5,2));
  signal_a0w_m26->SetBinContent(10,1+p[0][9]*(-2.6E-5)+p[1][9]*pow(-2.6E-5,2));
  signal_a0w_m24->SetBinContent(10,1+p[0][9]*(-2.4E-5)+p[1][9]*pow(-2.4E-5,2));
  signal_a0w_m22->SetBinContent(10,1+p[0][9]*(-2.2E-5)+p[1][9]*pow(-2.2E-5,2));
  signal_a0w_m18->SetBinContent(10,1+p[0][9]*(-1.8E-5)+p[1][9]*pow(-1.8E-5,2));
  signal_a0w_m16->SetBinContent(10,1+p[0][9]*(-1.6E-5)+p[1][9]*pow(-1.6E-5,2));
  signal_a0w_m32->SetBinContent(10,1+p[0][9]*(-3.2E-5)+p[1][9]*pow(-3.2E-5,2));
  signal_a0w_m34->SetBinContent(10,1+p[0][9]*(-3.4E-5)+p[1][9]*pow(-3.4E-5,2));
  signal_a0w_m36->SetBinContent(10,1+p[0][9]*(-3.6E-5)+p[1][9]*pow(-3.6E-5,2));
  signal_a0w_m38->SetBinContent(10,1+p[0][9]*(-3.8E-5)+p[1][9]*pow(-3.8E-5,2));

  signal_a0w_50->SetBinContent(10,1+p[0][9]*(5.E-5)+p[1][9]*pow(5.E-5,2));
  signal_a0w_30->SetBinContent(10,1+p[0][9]*(3.E-5)+p[1][9]*pow(3.E-5,2));
  signal_a0w_20->SetBinContent(10,1+p[0][9]*(2.E-5)+p[1][9]*pow(2.E-5,2));

  signal_a0w_28->SetBinContent(10,1+p[0][9]*(2.8E-5)+p[1][9]*pow(2.8E-5,2));
  signal_a0w_26->SetBinContent(10,1+p[0][9]*(2.6E-5)+p[1][9]*pow(2.6E-5,2));
  signal_a0w_24->SetBinContent(10,1+p[0][9]*(2.4E-5)+p[1][9]*pow(2.4E-5,2));
  signal_a0w_22->SetBinContent(10,1+p[0][9]*(2.2E-5)+p[1][9]*pow(2.2E-5,2));
  signal_a0w_18->SetBinContent(10,1+p[0][9]*(1.8E-5)+p[1][9]*pow(1.8E-5,2));
  signal_a0w_16->SetBinContent(10,1+p[0][9]*(1.6E-5)+p[1][9]*pow(1.6E-5,2));
  signal_a0w_32->SetBinContent(10,1+p[0][9]*(3.2E-5)+p[1][9]*pow(3.2E-5,2));
  signal_a0w_34->SetBinContent(10,1+p[0][9]*(3.4E-5)+p[1][9]*pow(3.4E-5,2));
  signal_a0w_36->SetBinContent(10,1+p[0][9]*(3.6E-5)+p[1][9]*pow(3.6E-5,2));
  signal_a0w_38->SetBinContent(10,1+p[0][9]*(3.8E-5)+p[1][9]*pow(3.8E-5,2));
*/
  signal_a0w_m50->Multiply(th1wwa);
  signal_a0w_m30->Multiply(th1wwa);
  signal_a0w_m20->Multiply(th1wwa);

  signal_a0w_m28->Multiply(th1wwa);
  signal_a0w_m26->Multiply(th1wwa);
  signal_a0w_m24->Multiply(th1wwa);
  signal_a0w_m22->Multiply(th1wwa);
  signal_a0w_m18->Multiply(th1wwa);
  signal_a0w_m16->Multiply(th1wwa);
  signal_a0w_m32->Multiply(th1wwa);
  signal_a0w_m34->Multiply(th1wwa);
  signal_a0w_m36->Multiply(th1wwa);
  signal_a0w_m38->Multiply(th1wwa);

  signal_a0w_50->Multiply(th1wwa);
  signal_a0w_30->Multiply(th1wwa);
  signal_a0w_20->Multiply(th1wwa);

  signal_a0w_28->Multiply(th1wwa);
  signal_a0w_26->Multiply(th1wwa);
  signal_a0w_24->Multiply(th1wwa);
  signal_a0w_22->Multiply(th1wwa);
  signal_a0w_18->Multiply(th1wwa);
  signal_a0w_16->Multiply(th1wwa);
  signal_a0w_32->Multiply(th1wwa);
  signal_a0w_34->Multiply(th1wwa);
  signal_a0w_36->Multiply(th1wwa);
  signal_a0w_38->Multiply(th1wwa);

  //For conveners:
  TH1D *signal_a0w_m30_pT = (TH1D*)signal_a0w_m30->Clone("signal_a0w_m30_pT");
  signal_a0w_m30_pT->Scale(1.185/2.1);
  //

  signal_a0w_m50->Add(th1wwa,-1);
  signal_a0w_m30->Add(th1wwa,-1);
  signal_a0w_m20->Add(th1wwa,-1);

  signal_a0w_m28->Add(th1wwa,-1);
  signal_a0w_m26->Add(th1wwa,-1);
  signal_a0w_m24->Add(th1wwa,-1);
  signal_a0w_m22->Add(th1wwa,-1);
  signal_a0w_m18->Add(th1wwa,-1);
  signal_a0w_m16->Add(th1wwa,-1);
  signal_a0w_m32->Add(th1wwa,-1);
  signal_a0w_m34->Add(th1wwa,-1);
  signal_a0w_m36->Add(th1wwa,-1);
  signal_a0w_m38->Add(th1wwa,-1);

  signal_a0w_50->Add(th1wwa,-1);
  signal_a0w_30->Add(th1wwa,-1);
  signal_a0w_20->Add(th1wwa,-1);

  signal_a0w_28->Add(th1wwa,-1);
  signal_a0w_26->Add(th1wwa,-1);
  signal_a0w_24->Add(th1wwa,-1);
  signal_a0w_22->Add(th1wwa,-1);
  signal_a0w_18->Add(th1wwa,-1);
  signal_a0w_16->Add(th1wwa,-1);
  signal_a0w_32->Add(th1wwa,-1);
  signal_a0w_34->Add(th1wwa,-1);
  signal_a0w_36->Add(th1wwa,-1);
  signal_a0w_38->Add(th1wwa,-1);


  signal_a0w_m50->Scale(1.185/2.1);
  signal_a0w_m30->Scale(1.185/2.1);
  signal_a0w_m20->Scale(1.185/2.1);

  signal_a0w_m28->Scale(1.185/2.1);
  signal_a0w_m26->Scale(1.185/2.1);
  signal_a0w_m24->Scale(1.185/2.1);
  signal_a0w_m22->Scale(1.185/2.1);
  signal_a0w_m18->Scale(1.185/2.1);
  signal_a0w_m16->Scale(1.185/2.1);
  signal_a0w_m32->Scale(1.185/2.1);
  signal_a0w_m34->Scale(1.185/2.1);
  signal_a0w_m36->Scale(1.185/2.1);
  signal_a0w_m38->Scale(1.185/2.1);

  signal_a0w_50->Scale(1.185/2.1);
  signal_a0w_30->Scale(1.185/2.1);
  signal_a0w_20->Scale(1.185/2.1);

  signal_a0w_28->Scale(1.185/2.1);
  signal_a0w_26->Scale(1.185/2.1);
  signal_a0w_24->Scale(1.185/2.1);
  signal_a0w_22->Scale(1.185/2.1);
  signal_a0w_18->Scale(1.185/2.1);
  signal_a0w_16->Scale(1.185/2.1);
  signal_a0w_32->Scale(1.185/2.1);
  signal_a0w_34->Scale(1.185/2.1);
  signal_a0w_36->Scale(1.185/2.1);
  signal_a0w_38->Scale(1.185/2.1);


/*
  signal_a0w_16->Sumw2();
  signal_a0w_18->Sumw2();
  signal_a0w_20->Sumw2();
  signal_a0w_22->Sumw2();
  signal_a0w_24->Sumw2();
  signal_a0w_26->Sumw2();
  signal_a0w_28->Sumw2();
  signal_a0w_30->Sumw2();
  signal_a0w_32->Sumw2();
  signal_a0w_34->Sumw2();
  signal_a0w_36->Sumw2();
  signal_a0w_38->Sumw2();
  signal_a0w_50->Sumw2();

  signal_a0w_m16->Sumw2();
  signal_a0w_m18->Sumw2();
  signal_a0w_m20->Sumw2();
  signal_a0w_m22->Sumw2();
  signal_a0w_m24->Sumw2();
  signal_a0w_m26->Sumw2();
  signal_a0w_m28->Sumw2();
  signal_a0w_m30->Sumw2();
  signal_a0w_m32->Sumw2();
  signal_a0w_m34->Sumw2();
  signal_a0w_m36->Sumw2();
  signal_a0w_m38->Sumw2();
  signal_a0w_m50->Sumw2();
*/
/*  // Adding 28% Signal K-factor Systematic uncertainty
  for(int hi=1;hi<=pv.NBINS;hi++){

     fperr = pow(signal_a0w_m16->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m16->GetBinContent(hi),2);
     signal_a0w_m16->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m18->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m18->GetBinContent(hi),2);
     signal_a0w_m18->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m20->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m20->GetBinContent(hi),2);
     signal_a0w_m20->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m22->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m22->GetBinContent(hi),2);
     signal_a0w_m22->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m24->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m24->GetBinContent(hi),2);
     signal_a0w_m24->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m26->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m26->GetBinContent(hi),2);
     signal_a0w_m26->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m28->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m28->GetBinContent(hi),2);
     signal_a0w_m28->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m30->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m30->GetBinContent(hi),2);
     signal_a0w_m30->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m32->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m32->GetBinContent(hi),2);
     signal_a0w_m32->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m34->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m34->GetBinContent(hi),2);
     signal_a0w_m34->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m36->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m36->GetBinContent(hi),2);
     signal_a0w_m36->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m38->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m38->GetBinContent(hi),2);
     signal_a0w_m38->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_m50->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_m50->GetBinContent(hi),2);
     signal_a0w_m50->SetBinError(hi,sqrt(fperr));


     fperr = pow(signal_a0w_16->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_16->GetBinContent(hi),2);
     signal_a0w_16->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_18->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_18->GetBinContent(hi),2);
     signal_a0w_18->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_20->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_20->GetBinContent(hi),2);
     signal_a0w_20->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_22->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_22->GetBinContent(hi),2);
     signal_a0w_22->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_24->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_24->GetBinContent(hi),2);
     signal_a0w_24->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_26->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_26->GetBinContent(hi),2);
     signal_a0w_26->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_28->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_28->GetBinContent(hi),2);
     signal_a0w_28->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_30->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_30->GetBinContent(hi),2);
     signal_a0w_30->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_32->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_32->GetBinContent(hi),2);
     signal_a0w_32->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_34->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_34->GetBinContent(hi),2);
     signal_a0w_34->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_36->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_36->GetBinContent(hi),2);
     signal_a0w_36->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_38->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_38->GetBinContent(hi),2);
     signal_a0w_38->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_a0w_50->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_a0w_50->GetBinContent(hi),2);
     signal_a0w_50->SetBinError(hi,sqrt(fperr));

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

  signal_a0w_50->SetYTitle(tmpc);
  signal_a0w_50->GetXaxis()->SetTitle(pv.xlabel);
  signal_a0w_50->GetYaxis()->CenterTitle(true);

  signal_a0w_30->SetYTitle(tmpc);
  signal_a0w_30->GetXaxis()->SetTitle(pv.xlabel);
  signal_a0w_30->GetYaxis()->CenterTitle(true);

  signal_a0w_20->SetYTitle(tmpc);
  signal_a0w_20->GetXaxis()->SetTitle(pv.xlabel);
  signal_a0w_20->GetYaxis()->CenterTitle(true);

  signal_a0w_m20->SetYTitle(tmpc);
  signal_a0w_m20->GetXaxis()->SetTitle(pv.xlabel);
  signal_a0w_m20->GetYaxis()->CenterTitle(true);

  signal_a0w_m30->SetYTitle(tmpc);
  signal_a0w_m30->GetXaxis()->SetTitle(pv.xlabel);
  signal_a0w_m30->GetYaxis()->CenterTitle(true);

  signal_a0w_m50->SetYTitle(tmpc);
  signal_a0w_m50->GetXaxis()->SetTitle(pv.xlabel);
  signal_a0w_m50->GetYaxis()->CenterTitle(true);


  ////////////////////////////////////////////////////////
  // Save Anomalous Signal histograms to output ROOT file:
  std::cout<<"Save Histograms...\n"<<std::endl;
  f.cd();
  signal_a0w_50->Write();
  signal_a0w_30->Write();
  signal_a0w_20->Write();
  signal_a0w_m20->Write();
  signal_a0w_m30->Write();
  signal_a0w_m50->Write();

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

  signal_a0w_m28->Write();
  signal_a0w_m26->Write();
  signal_a0w_m24->Write();
  signal_a0w_m22->Write();
  signal_a0w_m18->Write();
  signal_a0w_m16->Write();
  signal_a0w_m32->Write();
  signal_a0w_m34->Write();
  signal_a0w_m36->Write();
  signal_a0w_m38->Write();

  signal_a0w_28->Write();
  signal_a0w_26->Write();
  signal_a0w_24->Write();
  signal_a0w_22->Write();
  signal_a0w_18->Write();
  signal_a0w_16->Write();
  signal_a0w_32->Write();
  signal_a0w_34->Write();
  signal_a0w_36->Write();
  signal_a0w_38->Write();
/*
  //For conveners
  signal_a0w_m30_pT->Write();
  th1wwa->Write();
*/
  //

}// End Main function
