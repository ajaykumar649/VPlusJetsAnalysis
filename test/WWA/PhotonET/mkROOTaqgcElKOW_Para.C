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
void mkROOTaqgcElKOW_Para(){


  //////////////////////////////////////
  // Set MC normalization scale factors:
  const double intLUMI = 19166;

  // PT dependent k-factor included (same for WWA,WZA aQGC)
  const double WWA_scale     =  2.1* 0.01362 * intLUMI/198777;
  const double WWA2_scale    =  2.1* 0.01409 * intLUMI/199183;

  const double KOW_m2m5_scale     = 2.1* 0.03938 * intLUMI/86722;
  const double KOW_m1m5_scale     = 2.1* 0.027463 * intLUMI/150688;
  const double KOW_m05m5_scale     = 2.1* 0.02447 * intLUMI/197899;
  const double KOW_p05m5_scale     = 2.1* 0.024626 * intLUMI/192046;
  const double KOW_p2m5_scale     = 2.1* 0.0402575 * intLUMI/184145;
  const double KOW_p1m5_scale     = 2.1* 0.027794 * intLUMI/276250;


  ///////////////////////////////////////////////////////////////////////////////////
  // Specify what kinematical distribution to observe, as well as histogram settings:
  // 
  plotVar_t pv = {"Photon_Et[iPhoton12]",30,450,10,3,"Photon ET (GeV)"};
  if ( !strlen(pv.plotvar) ) break;
  std::cout << TString(pv.plotvar) << "\t"<<pv.MINRange<<"\t" << pv.MAXRange<<"\t" << pv.NBINS<<"\tTHE CUT " << endl;


  ////////////////////////////////
  // Specify event selection cuts:
  TCut the_cutKfac("effwt*puwt*(iPhoton12>-1 && i12Jet1>-1 && i12Jet2>-1 && abs(W_electron_eta)<2.5 && W_electron_pt>30 && event_met_pfmet>35. && W_mt>30 && abs(Photon_Eta[iPhoton12])<1.4442 && Photon_Et[iPhoton12]>30.&& Photon_dRlep[iPhoton12] > 0.5 && JetPFCor_dRpho12[i12Jet1]>0.5 && JetPFCor_dRpho12[i12Jet2]>0.5 && abs(JetPFCor_dphiMET[i12Jet1])>0.4 && abs(JetPFCor_dphiMET[i12Jet2])>0.4 && JetPFCor_bDiscriminatorCSV[i12Jet1]<0.679 && JetPFCor_bDiscriminatorCSV[i12Jet2]<0.679 && abs(JetPFCor_Eta[i12Jet1]-JetPFCor_Eta[i12Jet2])<1.4 && c2jMass12>70. && c2jMass12<100. && abs(91.1876-massla)>10. &&((i12Jet3>-1)? JetPFCor_dRpho12[i12Jet3]>0.5: 1 )&&((i12Jet4>-1)? JetPFCor_dRpho12[i12Jet4]>0.5: 1 ))");
//mva2jWWAelA1>0.2

  ///////////////////////////
  // Create output ROOT file:
  TFile f("para_el_K0W_WWA_PhotonEt.root", "RECREATE");


  //////////////////////////////////////////////////
  // Create file pointers for each sample ROOT file:
  TFile *wwaShape_file,*wwa2Shape_file;

  TFile *KOW_m2m5_file,*KOW_m1m5_file,*KOW_m05m5_file,*KOW_p05m5_file,*KOW_p2m5_file,*KOW_p1m5_file;


  //////////////////////////////
  // Open each sample ROOT file:
  wwaShape_file = new TFile("InData_New/RD_el_qq_wpwma_wp_qq_wm_lvl.root");
  wwa2Shape_file = new TFile("InData_New/RD_el_qq_wpwma_wp_lvl_wm_qq.root");

  KOW_m2m5_file = new TFile("InData_New/RD_el_K0W_m2m5MG_CMSSW532.root");
  KOW_m1m5_file = new TFile("InData_New/RD_el_K0W_m1m5MG_CMSSW532.root");
  KOW_m05m5_file = new TFile("InData_New/RD_el_K0W_m05m5MG_CMSSW532.root");
  KOW_p05m5_file = new TFile("InData_New/RD_el_K0W_p05m5MG_CMSSW532.root");
  KOW_p2m5_file = new TFile("InData_New/RD_el_K0W_p2m5MG_CMSSW532.root");
  KOW_p1m5_file = new TFile("InData_New/RD_el_K0W_p1m5MG_CMSSW532.root");


  ///////////////////////////////////////////////////
  // Retrieve ROOT tree with kinematic distributions:
  TTree* treewwa    = (TTree*)    wwaShape_file->Get("WJet");
  TTree* treewwa2    = (TTree*)    wwa2Shape_file->Get("WJet");

  TTree* treeKOW_m2m5 = (TTree*) KOW_m2m5_file->Get("WJet");
  TTree* treeKOW_m1m5 = (TTree*) KOW_m1m5_file->Get("WJet");
  TTree* treeKOW_m05m5 = (TTree*) KOW_m05m5_file->Get("WJet");
  TTree* treeKOW_p05m5 = (TTree*) KOW_p05m5_file->Get("WJet");
  TTree* treeKOW_p1m5 = (TTree*) KOW_p1m5_file->Get("WJet");
  TTree* treeKOW_p2m5 = (TTree*) KOW_p2m5_file->Get("WJet");


  ////////////////////////////////////////////////////////////
  // Create kinematic-distribution histograms for each sample:
  TH1* th1wwa = new TH1D("th1wwa", "th1wwa", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1wwa2 = new TH1D("th1wwa2", "th1wwa2", pv.NBINS, pv.MINRange, pv.MAXRange);

  TH1* signal_K0W_20 = new TH1D("signal_K0W_20","signal_K0W_20",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_K0W_10 = new TH1D("signal_K0W_10","signal_K0W_10",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_K0W_5 = new TH1D("signal_K0W_5","signal_K0W_5",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_K0W_m5 = new TH1D("signal_K0W_m5","signal_K0W_-5",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_K0W_m10 = new TH1D("signal_K0W_m10","signal_K0W_-10",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_K0W_m20 = new TH1D("signal_K0W_m20","signal_K0W_-20",pv.NBINS, pv.MINRange, pv.MAXRange);


  /////////////////////////////////////////////////////////////////////////
  // Specify histograms to store Sum of Squares of Weights for each sample:
  th1wwa->Sumw2();
  th1wwa2->Sumw2();
/*
  signal_K0W_20->Sumw2();
  signal_K0W_10->Sumw2();
  signal_K0W_5->Sumw2();
  signal_K0W_m5->Sumw2();
  signal_K0W_m10->Sumw2();
  signal_K0W_m20->Sumw2();
*/

  ///////////////////////////////////////////////////////////////////////////////////
  // Fill kinematical distribution for each sample according to event selection cuts:
  std::cout<<"Fill SM WWA Histogram..."<<std::endl;
  treewwa->Draw(TString(pv.plotvar)+TString(">>th1wwa"), the_cutKfac, "goff");
  th1wwa->AddBinContent(pv.NBINS,th1wwa->GetBinContent(pv.NBINS+1));th1wwa->SetBinContent(pv.NBINS+1,0.);
  treewwa2->Draw(TString(pv.plotvar)+TString(">>th1wwa2"), the_cutKfac, "goff");
  th1wwa2->AddBinContent(pv.NBINS,th1wwa2->GetBinContent(pv.NBINS+1));th1wwa2->SetBinContent(pv.NBINS+1,0.);


  std::cout<<"Fill aQGC_1 WWA Histogram..."<<std::endl;
  treeKOW_p2m5->Draw(TString(pv.plotvar)+TString(">>signal_K0W_20"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_2 WWA Histogram..."<<std::endl;
  treeKOW_p1m5->Draw(TString(pv.plotvar)+TString(">>signal_K0W_10"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_3 WWA Histogram..."<<std::endl;
  treeKOW_p05m5->Draw(TString(pv.plotvar)+TString(">>signal_K0W_5"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_4 WWA Histogram..."<<std::endl;
  treeKOW_m05m5->Draw(TString(pv.plotvar)+TString(">>signal_K0W_m5"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_5 WWA Histogram..."<<std::endl;
  treeKOW_m1m5->Draw(TString(pv.plotvar)+TString(">>signal_K0W_m10"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_6 WWA Histogram..."<<std::endl;
  treeKOW_m2m5->Draw(TString(pv.plotvar)+TString(">>signal_K0W_m20"), the_cutKfac, "goff");

  signal_K0W_20->AddBinContent(pv.NBINS,signal_K0W_20->GetBinContent(pv.NBINS+1));signal_K0W_20->SetBinContent(pv.NBINS+1,0.);
  signal_K0W_10->AddBinContent(pv.NBINS,signal_K0W_10->GetBinContent(pv.NBINS+1));signal_K0W_10->SetBinContent(pv.NBINS+1,0.);
  signal_K0W_5->AddBinContent(pv.NBINS,signal_K0W_5->GetBinContent(pv.NBINS+1));signal_K0W_5->SetBinContent(pv.NBINS+1,0.);
  signal_K0W_m5->AddBinContent(pv.NBINS,signal_K0W_m5->GetBinContent(pv.NBINS+1));signal_K0W_m5->SetBinContent(pv.NBINS+1,0.);
  signal_K0W_m10->AddBinContent(pv.NBINS,signal_K0W_m10->GetBinContent(pv.NBINS+1));signal_K0W_m10->SetBinContent(pv.NBINS+1,0.);
  signal_K0W_m20->AddBinContent(pv.NBINS,signal_K0W_m20->GetBinContent(pv.NBINS+1));signal_K0W_m20->SetBinContent(pv.NBINS+1,0.);


  /////////////////////////
  // Normalize each sample:
  std::cout<<"\nScale Histograms..."<<std::endl;
  th1wwa->Scale(WWA_scale);
  th1wwa2->Scale(WWA2_scale);

  signal_K0W_20->Scale(KOW_p2m5_scale);
  signal_K0W_10->Scale(KOW_p1m5_scale);
  signal_K0W_5->Scale(KOW_p05m5_scale);
  signal_K0W_m5->Scale(KOW_m05m5_scale);
  signal_K0W_m10->Scale(KOW_m1m5_scale);
  signal_K0W_m20->Scale(KOW_m2m5_scale);


  ///////////////////////////
  // Combine certain samples:
  th1wwa->Add(th1wwa2,1);

  signal_K0W_20->Divide(th1wwa);
  signal_K0W_10->Divide(th1wwa);
  signal_K0W_5->Divide(th1wwa);
  signal_K0W_m5->Divide(th1wwa);
  signal_K0W_m10->Divide(th1wwa);
  signal_K0W_m20->Divide(th1wwa);


  ///////////////////////////
  //Fill Parabolic Histogram:
  TH1* bin_1 = new TH1D("bin_1","bin_1",41, -20.5E-6, 20.5E-6);
  TH1* bin_2 = new TH1D("bin_2","bin_2",41, -20.5E-6, 20.5E-6);
  TH1* bin_3 = new TH1D("bin_3","bin_3",41, -20.5E-6, 20.5E-6);
  TH1* bin_4 = new TH1D("bin_4","bin_4",41, -20.5E-6, 20.5E-6);
  TH1* bin_5 = new TH1D("bin_5","bin_5",41, -20.5E-6, 20.5E-6);
  TH1* bin_6 = new TH1D("bin_6","bin_6",41, -20.5E-6, 20.5E-6);
  TH1* bin_7 = new TH1D("bin_7","bin_7",41, -20.5E-6, 20.5E-6);
  TH1* bin_8 = new TH1D("bin_8","bin_8",41, -20.5E-6, 20.5E-6);
  TH1* bin_9 = new TH1D("bin_9","bin_9",41, -20.5E-6, 20.5E-6);
  TH1* bin_10 = new TH1D("bin_10","bin_10",41, -20.5E-6, 20.5E-6);


  bin_1->SetBinContent(1,signal_K0W_m20->GetBinContent(1));
  bin_1->SetBinContent(11,signal_K0W_m10->GetBinContent(1));
  bin_1->SetBinContent(16,signal_K0W_m5->GetBinContent(1));
  bin_1->SetBinContent(21,1);
  bin_1->SetBinContent(26,signal_K0W_5->GetBinContent(1));
  bin_1->SetBinContent(31,signal_K0W_10->GetBinContent(1));
  bin_1->SetBinContent(41,signal_K0W_20->GetBinContent(1));

  bin_2->SetBinContent(1,signal_K0W_m20->GetBinContent(2));
  bin_2->SetBinContent(11,signal_K0W_m10->GetBinContent(2));
  bin_2->SetBinContent(16,signal_K0W_m5->GetBinContent(2));
  bin_2->SetBinContent(21,1);
  bin_2->SetBinContent(26,signal_K0W_5->GetBinContent(2));
  bin_2->SetBinContent(31,signal_K0W_10->GetBinContent(2));
  bin_2->SetBinContent(41,signal_K0W_20->GetBinContent(2));

  bin_3->SetBinContent(1,signal_K0W_m20->GetBinContent(3));
  bin_3->SetBinContent(11,signal_K0W_m10->GetBinContent(3));
  bin_3->SetBinContent(16,signal_K0W_m5->GetBinContent(3));
  bin_3->SetBinContent(21,1);
  bin_3->SetBinContent(26,signal_K0W_5->GetBinContent(3));
  bin_3->SetBinContent(31,signal_K0W_10->GetBinContent(3));
  bin_3->SetBinContent(41,signal_K0W_20->GetBinContent(3));

  bin_4->SetBinContent(1,signal_K0W_m20->GetBinContent(4));
  bin_4->SetBinContent(11,signal_K0W_m10->GetBinContent(4));
  bin_4->SetBinContent(16,signal_K0W_m5->GetBinContent(4));
  bin_4->SetBinContent(21,1);
  bin_4->SetBinContent(26,signal_K0W_5->GetBinContent(4));
  bin_4->SetBinContent(31,signal_K0W_10->GetBinContent(4));
  bin_4->SetBinContent(41,signal_K0W_20->GetBinContent(4));

  bin_5->SetBinContent(1,signal_K0W_m20->GetBinContent(5));
  bin_5->SetBinContent(11,signal_K0W_m10->GetBinContent(5));
  bin_5->SetBinContent(16,signal_K0W_m5->GetBinContent(5));
  bin_5->SetBinContent(21,1);
  bin_5->SetBinContent(26,signal_K0W_5->GetBinContent(5));
  bin_5->SetBinContent(31,signal_K0W_10->GetBinContent(5));
  bin_5->SetBinContent(41,signal_K0W_20->GetBinContent(5));

  bin_6->SetBinContent(1,signal_K0W_m20->GetBinContent(6));
  bin_6->SetBinContent(11,signal_K0W_m10->GetBinContent(6));
  bin_6->SetBinContent(16,signal_K0W_m5->GetBinContent(6));
  bin_6->SetBinContent(21,1);
  bin_6->SetBinContent(26,signal_K0W_5->GetBinContent(6));
  bin_6->SetBinContent(31,signal_K0W_10->GetBinContent(6));
  bin_6->SetBinContent(41,signal_K0W_20->GetBinContent(6));

  bin_7->SetBinContent(1,signal_K0W_m20->GetBinContent(7));
  bin_7->SetBinContent(11,signal_K0W_m10->GetBinContent(7));
  bin_7->SetBinContent(16,signal_K0W_m5->GetBinContent(7));
  bin_7->SetBinContent(21,1);
  bin_7->SetBinContent(26,signal_K0W_5->GetBinContent(7));
  bin_7->SetBinContent(31,signal_K0W_10->GetBinContent(7));
  bin_7->SetBinContent(41,signal_K0W_20->GetBinContent(7));

  bin_8->SetBinContent(1,signal_K0W_m20->GetBinContent(8));
  bin_8->SetBinContent(11,signal_K0W_m10->GetBinContent(8));
  bin_8->SetBinContent(16,signal_K0W_m5->GetBinContent(8));
  bin_8->SetBinContent(21,1);
  bin_8->SetBinContent(26,signal_K0W_5->GetBinContent(8));
  bin_8->SetBinContent(31,signal_K0W_10->GetBinContent(8));
  bin_8->SetBinContent(41,signal_K0W_20->GetBinContent(8));

  bin_9->SetBinContent(1,signal_K0W_m20->GetBinContent(9));
  bin_9->SetBinContent(11,signal_K0W_m10->GetBinContent(9));
  bin_9->SetBinContent(16,signal_K0W_m5->GetBinContent(9));
  bin_9->SetBinContent(21,1);
  bin_9->SetBinContent(26,signal_K0W_5->GetBinContent(9));
  bin_9->SetBinContent(31,signal_K0W_10->GetBinContent(9));
  bin_9->SetBinContent(41,signal_K0W_20->GetBinContent(9));

  bin_10->SetBinContent(1,signal_K0W_m20->GetBinContent(10));
  bin_10->SetBinContent(11,signal_K0W_m10->GetBinContent(10));
  bin_10->SetBinContent(16,signal_K0W_m5->GetBinContent(10));
  bin_10->SetBinContent(21,1);
  bin_10->SetBinContent(26,signal_K0W_5->GetBinContent(10));
  bin_10->SetBinContent(31,signal_K0W_10->GetBinContent(10));
  bin_10->SetBinContent(41,signal_K0W_20->GetBinContent(10));


  ////////////////
  // Fit function:
  Char_t para_fit[] = "[0]+[1]*x+[2]*x^2";
  Char_t fitopt[] = "QMR";
  Double_t xmin = -20.5E-6;
  Double_t xmax = 20.5E-6;
  Double_t p[3][10];
  TF1 *pfit = new TF1("pfit",para_fit,xmin,xmax);
//  pfit->SetParLimits(1,0.0,1E15);
//  pfit->FixParameter(0,0.0);


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

     value = p[0][j-1]+p[1][j-1]*(20E-6)+p[2][j-1]*pow(20E-6,2);
     test->SetBinContent(j,value);

     test2->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-20E-6)+p[2][j-1]*pow(-20E-6,2));

  }

//  test->SetBinContent(8,1+p[0][7]*(20E-6)+p[1][7]*pow(20E-6,2));
//  test2->SetBinContent(8,1+p[0][7]*(-20E-6)+p[1][7]*pow(-20E-6,2));

  TH1D* test_r = (TH1D*)test->Clone("test_r");
  TH1D* test2_r = (TH1D*)test2->Clone("test2_r");

  test_r->Divide(signal_K0W_20);
  test2_r->Divide(signal_K0W_m20);

  test->Multiply(th1wwa);
  test2->Multiply(th1wwa);
  test->Add(th1wwa,-1);
  test2->Add(th1wwa,-1);


  /////////////////////
  // Simulate new aQGC:
  TH1* signal_K0W_m17 = new TH1D("signal_K0W_m17","signal_K0W_-17",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_K0W_m16 = new TH1D("signal_K0W_m16","signal_K0W_-16",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_K0W_m15 = new TH1D("signal_K0W_m15","signal_K0W_-15",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_K0W_m14 = new TH1D("signal_K0W_m14","signal_K0W_-14",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_K0W_m13 = new TH1D("signal_K0W_m13","signal_K0W_-13",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_K0W_m12 = new TH1D("signal_K0W_m12","signal_K0W_-12",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_K0W_m11 = new TH1D("signal_K0W_m11","signal_K0W_-11",pv.NBINS,pv.MINRange,pv.MAXRange);

  TH1* signal_K0W_17 = new TH1D("signal_K0W_17","signal_K0W_17",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_K0W_16 = new TH1D("signal_K0W_16","signal_K0W_16",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_K0W_15 = new TH1D("signal_K0W_15","signal_K0W_15",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_K0W_14 = new TH1D("signal_K0W_14","signal_K0W_14",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_K0W_13 = new TH1D("signal_K0W_13","signal_K0W_13",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_K0W_12 = new TH1D("signal_K0W_12","signal_K0W_12",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_K0W_11 = new TH1D("signal_K0W_11","signal_K0W_11",pv.NBINS,pv.MINRange,pv.MAXRange);

  signal_K0W_m17->Sumw2();
  signal_K0W_m16->Sumw2();
  signal_K0W_m15->Sumw2();
  signal_K0W_m14->Sumw2();
  signal_K0W_m13->Sumw2();
  signal_K0W_m12->Sumw2();
  signal_K0W_m11->Sumw2();

  signal_K0W_17->Sumw2();
  signal_K0W_16->Sumw2();
  signal_K0W_15->Sumw2();
  signal_K0W_14->Sumw2();
  signal_K0W_13->Sumw2();
  signal_K0W_12->Sumw2();
  signal_K0W_11->Sumw2();


  for(Int_t j=1;j<=pv.NBINS;j++){

     Double_t bincent;
     TAxis* xaxis = test->GetXaxis();
     bincent = xaxis->GetBinCenter(j);

     signal_K0W_m20->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-20.E-6)+p[2][j-1]*pow(-20.E-6,2));
     signal_K0W_m17->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-17.E-6)+p[2][j-1]*pow(-17.E-6,2));
     signal_K0W_m16->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-16.E-6)+p[2][j-1]*pow(-16.E-6,2));
     signal_K0W_m15->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-15.E-6)+p[2][j-1]*pow(-15.E-6,2));
     signal_K0W_m14->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-14.E-6)+p[2][j-1]*pow(-14.E-6,2));
     signal_K0W_m13->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-13.E-6)+p[2][j-1]*pow(-13.E-6,2));
     signal_K0W_m12->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-12.E-6)+p[2][j-1]*pow(-12.E-6,2));
     signal_K0W_m11->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-11.E-6)+p[2][j-1]*pow(-11.E-6,2));
     signal_K0W_m10->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-10.E-6)+p[2][j-1]*pow(-10.E-6,2));
     signal_K0W_m5->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-5.E-6)+p[2][j-1]*pow(-5.E-6,2));

     signal_K0W_20->SetBinContent(j,p[0][j-1]+p[1][j-1]*(20.E-6)+p[2][j-1]*pow(20.E-6,2));
     signal_K0W_17->SetBinContent(j,p[0][j-1]+p[1][j-1]*(17.E-6)+p[2][j-1]*pow(17.E-6,2));
     signal_K0W_16->SetBinContent(j,p[0][j-1]+p[1][j-1]*(16.E-6)+p[2][j-1]*pow(16.E-6,2));
     signal_K0W_15->SetBinContent(j,p[0][j-1]+p[1][j-1]*(15.E-6)+p[2][j-1]*pow(15.E-6,2));
     signal_K0W_14->SetBinContent(j,p[0][j-1]+p[1][j-1]*(14.E-6)+p[2][j-1]*pow(14.E-6,2));
     signal_K0W_13->SetBinContent(j,p[0][j-1]+p[1][j-1]*(13.E-6)+p[2][j-1]*pow(13.E-6,2));
     signal_K0W_12->SetBinContent(j,p[0][j-1]+p[1][j-1]*(12.E-6)+p[2][j-1]*pow(12.E-6,2));
     signal_K0W_11->SetBinContent(j,p[0][j-1]+p[1][j-1]*(11.E-6)+p[2][j-1]*pow(11.E-6,2));
     signal_K0W_10->SetBinContent(j,p[0][j-1]+p[1][j-1]*(10.E-6)+p[2][j-1]*pow(10.E-6,2));
     signal_K0W_5->SetBinContent(j,p[0][j-1]+p[1][j-1]*(5.E-6)+p[2][j-1]*pow(5.E-6,2));

  }
/*
  signal_K0W_m20->SetBinContent(8,1+p[0][7]*(-20.E-6)+p[1][7]*pow(-20.E-6,2));
  signal_K0W_m17->SetBinContent(8,1+p[0][7]*(-17.E-6)+p[1][7]*pow(-17.E-6,2));
  signal_K0W_m16->SetBinContent(8,1+p[0][7]*(-16.E-6)+p[1][7]*pow(-16.E-6,2));
  signal_K0W_m15->SetBinContent(8,1+p[0][7]*(-15.E-6)+p[1][7]*pow(-15.E-6,2));
  signal_K0W_m14->SetBinContent(8,1+p[0][7]*(-14.E-6)+p[1][7]*pow(-14.E-6,2));
  signal_K0W_m13->SetBinContent(8,1+p[0][7]*(-13.E-6)+p[1][7]*pow(-13.E-6,2));
  signal_K0W_m12->SetBinContent(8,1+p[0][7]*(-12.E-6)+p[1][7]*pow(-12.E-6,2));
  signal_K0W_m11->SetBinContent(8,1+p[0][7]*(-11.E-6)+p[1][7]*pow(-11.E-6,2));
  signal_K0W_m10->SetBinContent(8,1+p[0][7]*(-10.E-6)+p[1][7]*pow(-10.E-6,2));
  signal_K0W_m5->SetBinContent(8,1+p[0][7]*(-5.E-6)+p[1][7]*pow(-5.E-6,2));


  signal_K0W_20->SetBinContent(8,1+p[0][7]*(20.E-6)+p[1][7]*pow(20.E-6,2));
  signal_K0W_17->SetBinContent(8,1+p[0][7]*(17.E-6)+p[1][7]*pow(17.E-6,2));
  signal_K0W_16->SetBinContent(8,1+p[0][7]*(16.E-6)+p[1][7]*pow(16.E-6,2));
  signal_K0W_15->SetBinContent(8,1+p[0][7]*(15.E-6)+p[1][7]*pow(15.E-6,2));
  signal_K0W_14->SetBinContent(8,1+p[0][7]*(14.E-6)+p[1][7]*pow(14.E-6,2));
  signal_K0W_13->SetBinContent(8,1+p[0][7]*(13.E-6)+p[1][7]*pow(13.E-6,2));
  signal_K0W_12->SetBinContent(8,1+p[0][7]*(12.E-6)+p[1][7]*pow(12.E-6,2));
  signal_K0W_11->SetBinContent(8,1+p[0][7]*(11.E-6)+p[1][7]*pow(11.E-6,2));
  signal_K0W_10->SetBinContent(8,1+p[0][7]*(10.E-6)+p[1][7]*pow(10.E-6,2));
  signal_K0W_5->SetBinContent(8,1+p[0][7]*(5.E-6)+p[1][7]*pow(5.E-6,2));
*/
  signal_K0W_m20->Multiply(th1wwa);
  signal_K0W_m17->Multiply(th1wwa);
  signal_K0W_m16->Multiply(th1wwa);
  signal_K0W_m15->Multiply(th1wwa);
  signal_K0W_m14->Multiply(th1wwa);
  signal_K0W_m13->Multiply(th1wwa);
  signal_K0W_m12->Multiply(th1wwa);
  signal_K0W_m11->Multiply(th1wwa);
  signal_K0W_m10->Multiply(th1wwa);
  signal_K0W_m5->Multiply(th1wwa);

  signal_K0W_20->Multiply(th1wwa);
  signal_K0W_17->Multiply(th1wwa);
  signal_K0W_16->Multiply(th1wwa);
  signal_K0W_15->Multiply(th1wwa);
  signal_K0W_14->Multiply(th1wwa);
  signal_K0W_13->Multiply(th1wwa);
  signal_K0W_12->Multiply(th1wwa);
  signal_K0W_11->Multiply(th1wwa);
  signal_K0W_10->Multiply(th1wwa);
  signal_K0W_5->Multiply(th1wwa);

  signal_K0W_m20->Add(th1wwa,-1);
  signal_K0W_m17->Add(th1wwa,-1);
  signal_K0W_m16->Add(th1wwa,-1);
  signal_K0W_m15->Add(th1wwa,-1);
  signal_K0W_m14->Add(th1wwa,-1);
  signal_K0W_m13->Add(th1wwa,-1);
  signal_K0W_m12->Add(th1wwa,-1);
  signal_K0W_m11->Add(th1wwa,-1);
  signal_K0W_m10->Add(th1wwa,-1);
  signal_K0W_m5->Add(th1wwa,-1);

  signal_K0W_20->Add(th1wwa,-1);
  signal_K0W_17->Add(th1wwa,-1);
  signal_K0W_16->Add(th1wwa,-1);
  signal_K0W_15->Add(th1wwa,-1);
  signal_K0W_14->Add(th1wwa,-1);
  signal_K0W_13->Add(th1wwa,-1);
  signal_K0W_12->Add(th1wwa,-1);
  signal_K0W_11->Add(th1wwa,-1);
  signal_K0W_10->Add(th1wwa,-1);
  signal_K0W_5->Add(th1wwa,-1);


  signal_K0W_m20->Scale(1.185/2.1);
  signal_K0W_m17->Scale(1.185/2.1);
  signal_K0W_m16->Scale(1.185/2.1);
  signal_K0W_m15->Scale(1.185/2.1);
  signal_K0W_m14->Scale(1.185/2.1);
  signal_K0W_m13->Scale(1.185/2.1);
  signal_K0W_m12->Scale(1.185/2.1);
  signal_K0W_m11->Scale(1.185/2.1);
  signal_K0W_m10->Scale(1.185/2.1);
  signal_K0W_m5->Scale(1.185/2.1);

  signal_K0W_20->Scale(1.185/2.1);
  signal_K0W_17->Scale(1.185/2.1);
  signal_K0W_16->Scale(1.185/2.1);
  signal_K0W_15->Scale(1.185/2.1);
  signal_K0W_14->Scale(1.185/2.1);
  signal_K0W_13->Scale(1.185/2.1);
  signal_K0W_12->Scale(1.185/2.1);
  signal_K0W_11->Scale(1.185/2.1);
  signal_K0W_10->Scale(1.185/2.1);
  signal_K0W_5->Scale(1.185/2.1);


/*  // Adding 35% Signal K-factor Systematic uncertainty
  for(int hi=1;hi<=pv.NBINS;hi++){

     fperr = pow(signal_K0W_m20->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_K0W_m20->GetBinContent(hi),2);
     signal_K0W_m20->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_K0W_m17->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_K0W_m17->GetBinContent(hi),2);
     signal_K0W_m17->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_K0W_m16->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_K0W_m16->GetBinContent(hi),2);
     signal_K0W_m16->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_K0W_m15->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_K0W_m15->GetBinContent(hi),2);
     signal_K0W_m15->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_K0W_m14->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_K0W_m14->GetBinContent(hi),2);
     signal_K0W_m14->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_K0W_m13->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_K0W_m13->GetBinContent(hi),2);
     signal_K0W_m13->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_K0W_m12->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_K0W_m12->GetBinContent(hi),2);
     signal_K0W_m12->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_K0W_m11->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_K0W_m11->GetBinContent(hi),2);
     signal_K0W_m11->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_K0W_m10->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_K0W_m10->GetBinContent(hi),2);
     signal_K0W_m10->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_K0W_m5->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_K0W_m5->GetBinContent(hi),2);
     signal_K0W_m5->SetBinError(hi,sqrt(fperr));


     fperr = pow(signal_K0W_20->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_K0W_20->GetBinContent(hi),2);
     signal_K0W_20->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_K0W_17->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_K0W_17->GetBinContent(hi),2);
     signal_K0W_17->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_K0W_16->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_K0W_16->GetBinContent(hi),2);
     signal_K0W_16->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_K0W_15->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_K0W_15->GetBinContent(hi),2);
     signal_K0W_15->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_K0W_14->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_K0W_14->GetBinContent(hi),2);
     signal_K0W_14->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_K0W_13->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_K0W_13->GetBinContent(hi),2);
     signal_K0W_13->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_K0W_12->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_K0W_12->GetBinContent(hi),2);
     signal_K0W_12->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_K0W_11->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_K0W_11->GetBinContent(hi),2);
     signal_K0W_11->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_K0W_10->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_K0W_10->GetBinContent(hi),2);
     signal_K0W_10->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_K0W_5->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_K0W_5->GetBinContent(hi),2);
     signal_K0W_5->SetBinError(hi,sqrt(fperr));

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

  signal_K0W_20->SetYTitle(tmpc);
  signal_K0W_20->GetXaxis()->SetTitle(pv.xlabel);
  signal_K0W_20->GetYaxis()->CenterTitle(true);

  signal_K0W_10->SetYTitle(tmpc);
  signal_K0W_10->GetXaxis()->SetTitle(pv.xlabel);
  signal_K0W_10->GetYaxis()->CenterTitle(true);

  signal_K0W_5->SetYTitle(tmpc);
  signal_K0W_5->GetXaxis()->SetTitle(pv.xlabel);
  signal_K0W_5->GetYaxis()->CenterTitle(true);

  signal_K0W_m5->SetYTitle(tmpc);
  signal_K0W_m5->GetXaxis()->SetTitle(pv.xlabel);
  signal_K0W_m5->GetYaxis()->CenterTitle(true);

  signal_K0W_m10->SetYTitle(tmpc);
  signal_K0W_m10->GetXaxis()->SetTitle(pv.xlabel);
  signal_K0W_m10->GetYaxis()->CenterTitle(true);

  signal_K0W_m20->SetYTitle(tmpc);
  signal_K0W_m20->GetXaxis()->SetTitle(pv.xlabel);
  signal_K0W_m20->GetYaxis()->CenterTitle(true);


  //////////////////////////////////////////////////////////
  // Save Observed Data, Background (+ SM WWA), Background +
  // Uncertainty, Background - Uncertainty, Anomalous Signal
  // histograms to output ROOT file:
  std::cout<<"Save Histograms..."<<std::endl;
  f.cd();
  signal_K0W_20->Write();
  signal_K0W_10->Write();
  signal_K0W_5->Write();
  signal_K0W_m5->Write();
  signal_K0W_m10->Write();
  signal_K0W_m20->Write();

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

  signal_K0W_17->Write();
  signal_K0W_16->Write();
  signal_K0W_15->Write();
  signal_K0W_14->Write();
  signal_K0W_13->Write();
  signal_K0W_12->Write();
  signal_K0W_11->Write();

  signal_K0W_m17->Write();
  signal_K0W_m16->Write();
  signal_K0W_m15->Write();
  signal_K0W_m14->Write();
  signal_K0W_m13->Write();
  signal_K0W_m12->Write();
  signal_K0W_m11->Write();

  //For conveners
//  th1wwa->Write();

  //

}// End Main function
