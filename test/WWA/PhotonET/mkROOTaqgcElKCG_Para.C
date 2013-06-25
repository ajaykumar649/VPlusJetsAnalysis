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
void mkROOTaqgcElKCG_Para(){


  //////////////////////////////////////
  // Set MC normalization scale factors:
  const double intLUMI = 19166;

  const double WWA_scale     = 2.1*0.01362 * intLUMI/198777;
  const double WWA2_scale    = 2.1*0.01409 * intLUMI/199183;

  const double KCG_p8m5_scale     = 2.1*0.043602 * intLUMI/172326 ;
  const double KCG_p5m5_scale     = 2.1*0.029437 * intLUMI/115605;
  const double KCG_p3m5_scale     = 2.1*0.0236905 * intLUMI/199484;
  const double KCG_m3m5_scale     = 2.1*0.024164 * intLUMI/193989;
  const double KCG_m5m5_scale     = 2.1*0.030337 * intLUMI/94299;
  const double KCG_m8m5_scale     = 2.1*0.045029 * intLUMI/197270;


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
  TFile f("para_el_aCW_WWA_PhotonEt.root", "RECREATE");


  //////////////////////////////////////////////////
  // Create file pointers for each sample ROOT file:
  TFile *wwaShape_file,*wwa2Shape_file;

  TFile *KCG_m8m5_file,*KCG_m5m5_file,*KCG_m3m5_file,*KCG_p3m5_file,*KCG_p5m5_file,*KCG_p8m5_file;


  //////////////////////////////
  // Open each sample ROOT file:
  wwaShape_file = new TFile("InData_New/RD_el_qq_wpwma_wp_qq_wm_lvl.root");
  wwa2Shape_file = new TFile("InData_New/RD_el_qq_wpwma_wp_lvl_wm_qq.root");

  KCG_m8m5_file = new TFile("InData_New/RD_el_KCG_m8m5MG_CMSSW532.root");
  KCG_m5m5_file = new TFile("InData_New/RD_el_KCG_m5m5MG_CMSSW532.root");
  KCG_m3m5_file = new TFile("InData_New/RD_el_KCG_m3m5MG_CMSSW532.root");
  KCG_p3m5_file = new TFile("InData_New/RD_el_KCG_p3m5MG_CMSSW532.root");
  KCG_p5m5_file = new TFile("InData_New/RD_el_KCG_p5m5MG_CMSSW532.root");
  KCG_p8m5_file = new TFile("InData_New/RD_el_KCG_p8m5MG_CMSSW532.root");


  ///////////////////////////////////////////////////
  // Retrieve ROOT tree with kinematic distributions:
  TTree* treewwa    = (TTree*)    wwaShape_file->Get("WJet");
  TTree* treewwa2    = (TTree*)    wwa2Shape_file->Get("WJet");

  TTree* treeKCG_m8m5 = (TTree*) KCG_m8m5_file->Get("WJet");
  TTree* treeKCG_m5m5 = (TTree*) KCG_m5m5_file->Get("WJet");
  TTree* treeKCG_m3m5 = (TTree*) KCG_m3m5_file->Get("WJet");
  TTree* treeKCG_p3m5 = (TTree*) KCG_p3m5_file->Get("WJet");
  TTree* treeKCG_p5m5 = (TTree*) KCG_p5m5_file->Get("WJet");
  TTree* treeKCG_p8m5 = (TTree*) KCG_p8m5_file->Get("WJet");


  ////////////////////////////////////////////////////////////
  // Create kinematic-distribution histograms for each sample:
  TH1* th1wwa = new TH1D("th1wwa", "th1wwa", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1wwa2 = new TH1D("th1wwa2", "th1wwa2", pv.NBINS, pv.MINRange, pv.MAXRange);

  TH1* signal_aCw_80 = new TH1D("signal_aCw_80","signal_aCw_80",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_aCw_50 = new TH1D("signal_aCw_50","signal_aCw_50",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_aCw_30 = new TH1D("signal_aCw_30","signal_aCw_30",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_aCw_m30 = new TH1D("signal_aCw_m30","signal_aCw_-30",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_aCw_m50 = new TH1D("signal_aCw_m50","signal_aCw_-50",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_aCw_m80 = new TH1D("signal_aCw_m80","signal_aCw_-80",pv.NBINS, pv.MINRange, pv.MAXRange);


  /////////////////////////////////////////////////////////////////////////
  // Specify histograms to store Sum of Squares of Weights for each sample:
  th1wwa->Sumw2();
  th1wwa2->Sumw2();

  ///////////////////////////////////////////////////////////////////////////////////
  // Fill kinematical distribution for each sample according to event selection cuts:
  std::cout<<"Fill SM WWA Histogram..."<<std::endl;
  treewwa->Draw(TString(pv.plotvar)+TString(">>th1wwa"), the_cutKfac, "goff");
  th1wwa->AddBinContent(pv.NBINS,th1wwa->GetBinContent(pv.NBINS+1));th1wwa->SetBinContent(pv.NBINS+1,0.);
  treewwa2->Draw(TString(pv.plotvar)+TString(">>th1wwa2"), the_cutKfac, "goff");
  th1wwa2->AddBinContent(pv.NBINS,th1wwa2->GetBinContent(pv.NBINS+1));th1wwa2->SetBinContent(pv.NBINS+1,0.);


  std::cout<<"Fill aQGC_1 WWA Histogram..."<<std::endl;
  treeKCG_p8m5->Draw(TString(pv.plotvar)+TString(">>signal_aCw_m80"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_2 WWA Histogram..."<<std::endl;
  treeKCG_p5m5->Draw(TString(pv.plotvar)+TString(">>signal_aCw_m50"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_3 WWA Histogram..."<<std::endl;
  treeKCG_p3m5->Draw(TString(pv.plotvar)+TString(">>signal_aCw_m30"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_4 WWA Histogram..."<<std::endl;
  treeKCG_m3m5->Draw(TString(pv.plotvar)+TString(">>signal_aCw_30"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_5 WWA Histogram..."<<std::endl;
  treeKCG_m5m5->Draw(TString(pv.plotvar)+TString(">>signal_aCw_50"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_6 WWA Histogram..."<<std::endl;
  treeKCG_m8m5->Draw(TString(pv.plotvar)+TString(">>signal_aCw_80"), the_cutKfac, "goff");

  signal_aCw_m80->AddBinContent(pv.NBINS,signal_aCw_m80->GetBinContent(pv.NBINS+1));signal_aCw_m80->SetBinContent(pv.NBINS+1,0.);
  signal_aCw_m50->AddBinContent(pv.NBINS,signal_aCw_m50->GetBinContent(pv.NBINS+1));signal_aCw_m50->SetBinContent(pv.NBINS+1,0.);
  signal_aCw_m30->AddBinContent(pv.NBINS,signal_aCw_m30->GetBinContent(pv.NBINS+1));signal_aCw_m30->SetBinContent(pv.NBINS+1,0.);
  signal_aCw_30->AddBinContent(pv.NBINS,signal_aCw_30->GetBinContent(pv.NBINS+1));signal_aCw_30->SetBinContent(pv.NBINS+1,0.);
  signal_aCw_50->AddBinContent(pv.NBINS,signal_aCw_50->GetBinContent(pv.NBINS+1));signal_aCw_50->SetBinContent(pv.NBINS+1,0.);
  signal_aCw_80->AddBinContent(pv.NBINS,signal_aCw_80->GetBinContent(pv.NBINS+1));signal_aCw_80->SetBinContent(pv.NBINS+1,0.);


  /////////////////////////
  // Normalize each sample:
  std::cout<<"\nScale Histograms..."<<std::endl;
  th1wwa->Scale(WWA_scale);
  th1wwa2->Scale(WWA2_scale);

  signal_aCw_80->Scale(KCG_p8m5_scale);
  signal_aCw_50->Scale(KCG_p5m5_scale);
  signal_aCw_30->Scale(KCG_p3m5_scale);
  signal_aCw_m30->Scale(KCG_m3m5_scale);
  signal_aCw_m50->Scale(KCG_m5m5_scale);
  signal_aCw_m80->Scale(KCG_m8m5_scale);


  ///////////////////////////
  // Combine certain samples:
  th1wwa->Add(th1wwa2,1);

  signal_aCw_80->Divide(th1wwa);
  signal_aCw_50->Divide(th1wwa);
  signal_aCw_30->Divide(th1wwa);
  signal_aCw_m30->Divide(th1wwa);
  signal_aCw_m50->Divide(th1wwa);
  signal_aCw_m80->Divide(th1wwa);

  ///////////////////////////
  //Fill Parabolic Histogram:
  TH1* bin_1 = new TH1D("bin_1","bin_1",17, -8.5E-5, 8.5E-5);
  TH1* bin_2 = new TH1D("bin_2","bin_2",17, -8.5E-5, 8.5E-5);
  TH1* bin_3 = new TH1D("bin_3","bin_3",17, -8.5E-5, 8.5E-5);
  TH1* bin_4 = new TH1D("bin_4","bin_4",17, -8.5E-5, 8.5E-5);
  TH1* bin_5 = new TH1D("bin_5","bin_5",17, -8.5E-5, 8.5E-5);
  TH1* bin_6 = new TH1D("bin_6","bin_6",17, -8.5E-5, 8.5E-5);
  TH1* bin_7 = new TH1D("bin_7","bin_7",17, -8.5E-5, 8.5E-5);
  TH1* bin_8 = new TH1D("bin_8","bin_8",17, -8.5E-5, 8.5E-5);
  TH1* bin_9 = new TH1D("bin_9","bin_9",17, -8.5E-5, 8.5E-5);
  TH1* bin_10 = new TH1D("bin_10","bin_10",17, -8.5E-5, 8.5E-5);


  bin_1->SetBinContent(1,signal_aCw_m80->GetBinContent(1));
  bin_1->SetBinContent(4,signal_aCw_m50->GetBinContent(1));
  bin_1->SetBinContent(6,signal_aCw_m30->GetBinContent(1));
  bin_1->SetBinContent(9,1);
  bin_1->SetBinContent(12,signal_aCw_30->GetBinContent(1));
  bin_1->SetBinContent(14,signal_aCw_50->GetBinContent(1));
  bin_1->SetBinContent(17,signal_aCw_80->GetBinContent(1));

  bin_2->SetBinContent(1,signal_aCw_m80->GetBinContent(2));
  bin_2->SetBinContent(4,signal_aCw_m50->GetBinContent(2));
  bin_2->SetBinContent(6,signal_aCw_m30->GetBinContent(2));
  bin_2->SetBinContent(9,1);
  bin_2->SetBinContent(12,signal_aCw_30->GetBinContent(2));
  bin_2->SetBinContent(14,signal_aCw_50->GetBinContent(2));
  bin_2->SetBinContent(17,signal_aCw_80->GetBinContent(2));

  bin_3->SetBinContent(1,signal_aCw_m80->GetBinContent(3));
  bin_3->SetBinContent(4,signal_aCw_m50->GetBinContent(3));
  bin_3->SetBinContent(6,signal_aCw_m30->GetBinContent(3));
  bin_3->SetBinContent(9,1);
  bin_3->SetBinContent(12,signal_aCw_30->GetBinContent(3));
  bin_3->SetBinContent(14,signal_aCw_50->GetBinContent(3));
  bin_3->SetBinContent(17,signal_aCw_80->GetBinContent(3));

  bin_4->SetBinContent(1,signal_aCw_m80->GetBinContent(4));
  bin_4->SetBinContent(4,signal_aCw_m50->GetBinContent(4));
  bin_4->SetBinContent(6,signal_aCw_m30->GetBinContent(4));
  bin_4->SetBinContent(9,1);
  bin_4->SetBinContent(12,signal_aCw_30->GetBinContent(4));
  bin_4->SetBinContent(14,signal_aCw_50->GetBinContent(4));
  bin_4->SetBinContent(17,signal_aCw_80->GetBinContent(4));

  bin_5->SetBinContent(1,signal_aCw_m80->GetBinContent(5));
  bin_5->SetBinContent(4,signal_aCw_m50->GetBinContent(5));
  bin_5->SetBinContent(6,signal_aCw_m30->GetBinContent(5));
  bin_5->SetBinContent(9,1);
  bin_5->SetBinContent(12,signal_aCw_30->GetBinContent(5));
  bin_5->SetBinContent(14,signal_aCw_50->GetBinContent(5));
  bin_5->SetBinContent(17,signal_aCw_80->GetBinContent(5));

  bin_6->SetBinContent(1,signal_aCw_m80->GetBinContent(6));
  bin_6->SetBinContent(4,signal_aCw_m50->GetBinContent(6));
  bin_6->SetBinContent(6,signal_aCw_m30->GetBinContent(6));
  bin_6->SetBinContent(9,1);
  bin_6->SetBinContent(12,signal_aCw_30->GetBinContent(6));
  bin_6->SetBinContent(14,signal_aCw_50->GetBinContent(6));
  bin_6->SetBinContent(17,signal_aCw_80->GetBinContent(6));

  bin_7->SetBinContent(1,signal_aCw_m80->GetBinContent(7));
  bin_7->SetBinContent(4,signal_aCw_m50->GetBinContent(7));
  bin_7->SetBinContent(6,signal_aCw_m30->GetBinContent(7));
  bin_7->SetBinContent(9,1);
  bin_7->SetBinContent(12,signal_aCw_30->GetBinContent(7));
  bin_7->SetBinContent(14,signal_aCw_50->GetBinContent(7));
  bin_7->SetBinContent(17,signal_aCw_80->GetBinContent(7));

  bin_8->SetBinContent(1,signal_aCw_m80->GetBinContent(8));
  bin_8->SetBinContent(4,signal_aCw_m50->GetBinContent(8));
  bin_8->SetBinContent(6,signal_aCw_m30->GetBinContent(8));
  bin_8->SetBinContent(9,1);
  bin_8->SetBinContent(12,signal_aCw_30->GetBinContent(8));
  bin_8->SetBinContent(14,signal_aCw_50->GetBinContent(8));
  bin_8->SetBinContent(17,signal_aCw_80->GetBinContent(8));

  bin_9->SetBinContent(1,signal_aCw_m80->GetBinContent(9));
  bin_9->SetBinContent(4,signal_aCw_m50->GetBinContent(9));
  bin_9->SetBinContent(6,signal_aCw_m30->GetBinContent(9));
  bin_9->SetBinContent(9,1);
  bin_9->SetBinContent(12,signal_aCw_30->GetBinContent(9));
  bin_9->SetBinContent(14,signal_aCw_50->GetBinContent(9));
  bin_9->SetBinContent(17,signal_aCw_80->GetBinContent(9));

  bin_10->SetBinContent(1,signal_aCw_m80->GetBinContent(10));
  bin_10->SetBinContent(4,signal_aCw_m50->GetBinContent(10));
  bin_10->SetBinContent(6,signal_aCw_m30->GetBinContent(10));
  bin_10->SetBinContent(9,1);
  bin_10->SetBinContent(12,signal_aCw_30->GetBinContent(10));
  bin_10->SetBinContent(14,signal_aCw_50->GetBinContent(10));
  bin_10->SetBinContent(17,signal_aCw_80->GetBinContent(10));


  ////////////////
  // Fit function:
  Char_t para_fit[] = "[0]+[1]*x+[2]*x^2";
  Char_t fitopt[] = "QMR";
  Double_t xmin = -8E-5;
  Double_t xmax = 8E-5;
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
  Double_t xmax = 1050;//275;
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

     value = p[0][j-1]+p[1][j-1]*(8E-5)+p[2][j-1]*pow(8E-5,2);
     test->SetBinContent(j,value);

     test2->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-8E-5)+p[2][j-1]*pow(-8E-5,2));

  }

//  test->SetBinContent(8,1+p[0][7]*(8E-5)+p[1][7]*pow(8E-5,2));
//  test2->SetBinContent(8,1+p[0][7]*(-8E-5)+p[1][7]*pow(-8E-5,2));

  TH1D* test_r = (TH1D*)test->Clone("test_r");
  TH1D* test2_r = (TH1D*)test2->Clone("test2_r");

  test_r->Divide(signal_aCw_80);
  test2_r->Divide(signal_aCw_m80);

  test->Multiply(th1wwa);
  test2->Multiply(th1wwa);
  test->Add(th1wwa,-1);
  test2->Add(th1wwa,-1);


  /////////////////////
  // Simulate new aQGC:
  TH1* signal_aCw_26 = new TH1D("signal_aCw_26","signal_aCw_2p6",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_aCw_28 = new TH1D("signal_aCw_28","signal_aCw_2p8",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_aCw_32 = new TH1D("signal_aCw_32","signal_aCw_3p2",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_aCw_34 = new TH1D("signal_aCw_34","signal_aCw_3p4",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_aCw_36 = new TH1D("signal_aCw_36","signal_aCw_3p6",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_aCw_38 = new TH1D("signal_aCw_38","signal_aCw_3p8",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_aCw_40 = new TH1D("signal_aCw_40","signal_aCw_4p0",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_aCw_42 = new TH1D("signal_aCw_42","signal_aCw_4p2",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_aCw_44 = new TH1D("signal_aCw_44","signal_aCw_4p4",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_aCw_46 = new TH1D("signal_aCw_46","signal_aCw_4p6",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_aCw_48 = new TH1D("signal_aCw_48","signal_aCw_4p8",pv.NBINS,pv.MINRange,pv.MAXRange);

  TH1* signal_aCw_m26 = new TH1D("signal_aCw_m26","signal_aCw_-2p6",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_aCw_m28 = new TH1D("signal_aCw_m28","signal_aCw_-2p8",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_aCw_m32 = new TH1D("signal_aCw_m32","signal_aCw_-3p2",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_aCw_m34 = new TH1D("signal_aCw_m34","signal_aCw_-3p4",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_aCw_m36 = new TH1D("signal_aCw_m36","signal_aCw_-3p6",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_aCw_m38 = new TH1D("signal_aCw_m38","signal_aCw_-3p8",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_aCw_m40 = new TH1D("signal_aCw_m40","signal_aCw_-4p0",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_aCw_m42 = new TH1D("signal_aCw_m42","signal_aCw_-4p2",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_aCw_m44 = new TH1D("signal_aCw_m44","signal_aCw_-4p4",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_aCw_m46 = new TH1D("signal_aCw_m46","signal_aCw_-4p6",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_aCw_m48 = new TH1D("signal_aCw_m48","signal_aCw_-4p8",pv.NBINS,pv.MINRange,pv.MAXRange);


  signal_aCw_26->Sumw2();
  signal_aCw_28->Sumw2();
  signal_aCw_32->Sumw2();
  signal_aCw_34->Sumw2();
  signal_aCw_36->Sumw2();
  signal_aCw_38->Sumw2();
  signal_aCw_40->Sumw2();
  signal_aCw_42->Sumw2();
  signal_aCw_44->Sumw2();
  signal_aCw_46->Sumw2();
  signal_aCw_48->Sumw2();
  signal_aCw_m26->Sumw2();
  signal_aCw_m28->Sumw2();
  signal_aCw_m32->Sumw2();
  signal_aCw_m34->Sumw2();
  signal_aCw_m36->Sumw2();
  signal_aCw_m38->Sumw2();
  signal_aCw_m40->Sumw2();
  signal_aCw_m42->Sumw2();
  signal_aCw_m44->Sumw2();
  signal_aCw_m46->Sumw2();
  signal_aCw_m48->Sumw2();


  for(Int_t j=1;j<=pv.NBINS;j++){

     Double_t bincent;
     TAxis* xaxis = test->GetXaxis();
     bincent = xaxis->GetBinCenter(j);

     signal_aCw_m50->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-5.E-5)+p[2][j-1]*pow(-5.E-5,2));
     signal_aCw_m30->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-3.E-5)+p[2][j-1]*pow(-3.E-5,2));
     signal_aCw_m80->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-8.E-5)+p[2][j-1]*pow(-8.E-5,2));

     signal_aCw_m38->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-3.8E-5)+p[2][j-1]*pow(-3.8E-5,2));
     signal_aCw_m36->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-3.6E-5)+p[2][j-1]*pow(-3.6E-5,2));
     signal_aCw_m34->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-3.4E-5)+p[2][j-1]*pow(-3.4E-5,2));
     signal_aCw_m32->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-3.2E-5)+p[2][j-1]*pow(-3.2E-5,2));
     signal_aCw_m28->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-2.8E-5)+p[2][j-1]*pow(-2.8E-5,2));
     signal_aCw_m26->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-2.6E-5)+p[2][j-1]*pow(-2.6E-5,2));
     signal_aCw_m40->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-4.E-5)+p[2][j-1]*pow(-4.E-5,2));
     signal_aCw_m42->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-4.2E-5)+p[2][j-1]*pow(-4.2E-5,2));
     signal_aCw_m44->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-4.4E-5)+p[2][j-1]*pow(-4.4E-5,2));
     signal_aCw_m46->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-4.6E-5)+p[2][j-1]*pow(-4.6E-5,2));
     signal_aCw_m48->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-4.8E-5)+p[2][j-1]*pow(-4.8E-5,2));

     signal_aCw_50->SetBinContent(j,p[0][j-1]+p[1][j-1]*(5.E-5)+p[2][j-1]*pow(5.E-5,2));
     signal_aCw_30->SetBinContent(j,p[0][j-1]+p[1][j-1]*(3.E-5)+p[2][j-1]*pow(3.E-5,2));
     signal_aCw_80->SetBinContent(j,p[0][j-1]+p[1][j-1]*(8.E-5)+p[2][j-1]*pow(8.E-5,2));

     signal_aCw_38->SetBinContent(j,p[0][j-1]+p[1][j-1]*(3.8E-5)+p[2][j-1]*pow(3.8E-5,2));
     signal_aCw_36->SetBinContent(j,p[0][j-1]+p[1][j-1]*(3.6E-5)+p[2][j-1]*pow(3.6E-5,2));
     signal_aCw_34->SetBinContent(j,p[0][j-1]+p[1][j-1]*(3.4E-5)+p[2][j-1]*pow(3.4E-5,2));
     signal_aCw_32->SetBinContent(j,p[0][j-1]+p[1][j-1]*(3.2E-5)+p[2][j-1]*pow(3.2E-5,2));
     signal_aCw_28->SetBinContent(j,p[0][j-1]+p[1][j-1]*(2.8E-5)+p[2][j-1]*pow(2.8E-5,2));
     signal_aCw_26->SetBinContent(j,p[0][j-1]+p[1][j-1]*(2.6E-5)+p[2][j-1]*pow(2.6E-5,2));
     signal_aCw_40->SetBinContent(j,p[0][j-1]+p[1][j-1]*(4.E-5)+p[2][j-1]*pow(4.E-5,2));
     signal_aCw_42->SetBinContent(j,p[0][j-1]+p[1][j-1]*(4.2E-5)+p[2][j-1]*pow(4.2E-5,2));
     signal_aCw_44->SetBinContent(j,p[0][j-1]+p[1][j-1]*(4.4E-5)+p[2][j-1]*pow(4.4E-5,2));
     signal_aCw_46->SetBinContent(j,p[0][j-1]+p[1][j-1]*(4.6E-5)+p[2][j-1]*pow(4.6E-5,2));
     signal_aCw_48->SetBinContent(j,p[0][j-1]+p[1][j-1]*(4.8E-5)+p[2][j-1]*pow(4.8E-5,2));

  }
/*
  signal_aCw_m50->SetBinContent(8,1+p[0][7]*(-5.E-5)+p[1][7]*pow(-5.E-5,2));
  signal_aCw_m30->SetBinContent(8,1+p[0][7]*(-3.E-5)+p[1][7]*pow(-3.E-5,2));
  signal_aCw_m80->SetBinContent(8,1+p[0][7]*(-8.E-5)+p[1][7]*pow(-8.E-5,2));

  signal_aCw_m38->SetBinContent(8,1+p[0][7]*(-3.8E-5)+p[1][7]*pow(-3.8E-5,2));
  signal_aCw_m36->SetBinContent(8,1+p[0][7]*(-3.6E-5)+p[1][7]*pow(-3.6E-5,2));
  signal_aCw_m34->SetBinContent(8,1+p[0][7]*(-3.4E-5)+p[1][7]*pow(-3.4E-5,2));
  signal_aCw_m32->SetBinContent(8,1+p[0][7]*(-3.2E-5)+p[1][7]*pow(-3.2E-5,2));
  signal_aCw_m28->SetBinContent(8,1+p[0][7]*(-2.8E-5)+p[1][7]*pow(-2.8E-5,2));
  signal_aCw_m26->SetBinContent(8,1+p[0][7]*(-2.6E-5)+p[1][7]*pow(-2.6E-5,2));
  signal_aCw_m40->SetBinContent(8,1+p[0][7]*(-4.E-5)+p[1][7]*pow(-4.E-5,2));
  signal_aCw_m42->SetBinContent(8,1+p[0][7]*(-4.2E-5)+p[1][7]*pow(-4.2E-5,2));
  signal_aCw_m44->SetBinContent(8,1+p[0][7]*(-4.4E-5)+p[1][7]*pow(-4.4E-5,2));
  signal_aCw_m46->SetBinContent(8,1+p[0][7]*(-4.6E-5)+p[1][7]*pow(-4.6E-5,2));
  signal_aCw_m48->SetBinContent(8,1+p[0][7]*(-4.8E-5)+p[1][7]*pow(-4.8E-5,2));

  signal_aCw_50->SetBinContent(8,1+p[0][7]*(5.E-5)+p[1][7]*pow(5.E-5,2));
  signal_aCw_30->SetBinContent(8,1+p[0][7]*(3.E-5)+p[1][7]*pow(3.E-5,2));
  signal_aCw_80->SetBinContent(8,1+p[0][7]*(8.E-5)+p[1][7]*pow(8.E-5,2));

  signal_aCw_38->SetBinContent(8,1+p[0][7]*(3.8E-5)+p[1][7]*pow(3.8E-5,2));
  signal_aCw_36->SetBinContent(8,1+p[0][7]*(3.6E-5)+p[1][7]*pow(3.6E-5,2));
  signal_aCw_34->SetBinContent(8,1+p[0][7]*(3.4E-5)+p[1][7]*pow(3.4E-5,2));
  signal_aCw_32->SetBinContent(8,1+p[0][7]*(3.2E-5)+p[1][7]*pow(3.2E-5,2));
  signal_aCw_28->SetBinContent(8,1+p[0][7]*(2.8E-5)+p[1][7]*pow(2.8E-5,2));
  signal_aCw_26->SetBinContent(8,1+p[0][7]*(2.6E-5)+p[1][7]*pow(2.6E-5,2));
  signal_aCw_40->SetBinContent(8,1+p[0][7]*(4.E-5)+p[1][7]*pow(4.E-5,2));
  signal_aCw_42->SetBinContent(8,1+p[0][7]*(4.2E-5)+p[1][7]*pow(4.2E-5,2));
  signal_aCw_44->SetBinContent(8,1+p[0][7]*(4.4E-5)+p[1][7]*pow(4.4E-5,2));
  signal_aCw_46->SetBinContent(8,1+p[0][7]*(4.6E-5)+p[1][7]*pow(4.6E-5,2));
  signal_aCw_48->SetBinContent(8,1+p[0][7]*(4.8E-5)+p[1][7]*pow(4.8E-5,2));
*/
  signal_aCw_m50->Multiply(th1wwa);
  signal_aCw_m30->Multiply(th1wwa);
  signal_aCw_m80->Multiply(th1wwa);

  signal_aCw_m38->Multiply(th1wwa);
  signal_aCw_m36->Multiply(th1wwa);
  signal_aCw_m34->Multiply(th1wwa);
  signal_aCw_m32->Multiply(th1wwa);
  signal_aCw_m28->Multiply(th1wwa);
  signal_aCw_m26->Multiply(th1wwa);
  signal_aCw_m40->Multiply(th1wwa);
  signal_aCw_m42->Multiply(th1wwa);
  signal_aCw_m44->Multiply(th1wwa);
  signal_aCw_m46->Multiply(th1wwa);
  signal_aCw_m48->Multiply(th1wwa);

  signal_aCw_50->Multiply(th1wwa);
  signal_aCw_30->Multiply(th1wwa);
  signal_aCw_80->Multiply(th1wwa);

  signal_aCw_38->Multiply(th1wwa);
  signal_aCw_36->Multiply(th1wwa);
  signal_aCw_34->Multiply(th1wwa);
  signal_aCw_32->Multiply(th1wwa);
  signal_aCw_28->Multiply(th1wwa);
  signal_aCw_26->Multiply(th1wwa);
  signal_aCw_40->Multiply(th1wwa);
  signal_aCw_42->Multiply(th1wwa);
  signal_aCw_44->Multiply(th1wwa);
  signal_aCw_46->Multiply(th1wwa);
  signal_aCw_48->Multiply(th1wwa);

  signal_aCw_m50->Add(th1wwa,-1);
  signal_aCw_m30->Add(th1wwa,-1);
  signal_aCw_m80->Add(th1wwa,-1);

  signal_aCw_m38->Add(th1wwa,-1);
  signal_aCw_m36->Add(th1wwa,-1);
  signal_aCw_m34->Add(th1wwa,-1);
  signal_aCw_m32->Add(th1wwa,-1);
  signal_aCw_m28->Add(th1wwa,-1);
  signal_aCw_m26->Add(th1wwa,-1);
  signal_aCw_m40->Add(th1wwa,-1);
  signal_aCw_m42->Add(th1wwa,-1);
  signal_aCw_m44->Add(th1wwa,-1);
  signal_aCw_m46->Add(th1wwa,-1);
  signal_aCw_m48->Add(th1wwa,-1);

  signal_aCw_50->Add(th1wwa,-1);
  signal_aCw_30->Add(th1wwa,-1);
  signal_aCw_80->Add(th1wwa,-1);

  signal_aCw_38->Add(th1wwa,-1);
  signal_aCw_36->Add(th1wwa,-1);
  signal_aCw_34->Add(th1wwa,-1);
  signal_aCw_32->Add(th1wwa,-1);
  signal_aCw_28->Add(th1wwa,-1);
  signal_aCw_26->Add(th1wwa,-1);
  signal_aCw_40->Add(th1wwa,-1);
  signal_aCw_42->Add(th1wwa,-1);
  signal_aCw_44->Add(th1wwa,-1);
  signal_aCw_46->Add(th1wwa,-1);
  signal_aCw_48->Add(th1wwa,-1);


  signal_aCw_m50->Scale(1.185/2.1);
  signal_aCw_m30->Scale(1.185/2.1);
  signal_aCw_m80->Scale(1.185/2.1);

  signal_aCw_m38->Scale(1.185/2.1);
  signal_aCw_m36->Scale(1.185/2.1);
  signal_aCw_m34->Scale(1.185/2.1);
  signal_aCw_m32->Scale(1.185/2.1);
  signal_aCw_m28->Scale(1.185/2.1);
  signal_aCw_m26->Scale(1.185/2.1);
  signal_aCw_m40->Scale(1.185/2.1);
  signal_aCw_m42->Scale(1.185/2.1);
  signal_aCw_m44->Scale(1.185/2.1);
  signal_aCw_m46->Scale(1.185/2.1);
  signal_aCw_m48->Scale(1.185/2.1);

  signal_aCw_50->Scale(1.185/2.1);
  signal_aCw_30->Scale(1.185/2.1);
  signal_aCw_80->Scale(1.185/2.1);

  signal_aCw_38->Scale(1.185/2.1);
  signal_aCw_36->Scale(1.185/2.1);
  signal_aCw_34->Scale(1.185/2.1);
  signal_aCw_32->Scale(1.185/2.1);
  signal_aCw_28->Scale(1.185/2.1);
  signal_aCw_26->Scale(1.185/2.1);
  signal_aCw_40->Scale(1.185/2.1);
  signal_aCw_42->Scale(1.185/2.1);
  signal_aCw_44->Scale(1.185/2.1);
  signal_aCw_46->Scale(1.185/2.1);
  signal_aCw_48->Scale(1.185/2.1);

/*
  signal_aCw_26->Sumw2();
  signal_aCw_28->Sumw2();
  signal_aCw_30->Sumw2();
  signal_aCw_32->Sumw2();
  signal_aCw_34->Sumw2();
  signal_aCw_36->Sumw2();
  signal_aCw_38->Sumw2();
  signal_aCw_40->Sumw2();
  signal_aCw_42->Sumw2();
  signal_aCw_44->Sumw2();
  signal_aCw_46->Sumw2();
  signal_aCw_48->Sumw2();
  signal_aCw_50->Sumw2();
  signal_aCw_80->Sumw2();

  signal_aCw_m26->Sumw2();
  signal_aCw_m28->Sumw2();
  signal_aCw_m30->Sumw2();
  signal_aCw_m32->Sumw2();
  signal_aCw_m34->Sumw2();
  signal_aCw_m36->Sumw2();
  signal_aCw_m38->Sumw2();
  signal_aCw_m40->Sumw2();
  signal_aCw_m42->Sumw2();
  signal_aCw_m44->Sumw2();
  signal_aCw_m46->Sumw2();
  signal_aCw_m48->Sumw2();
  signal_aCw_m50->Sumw2();
  signal_aCw_m80->Sumw2();
*/
/*  // Adding 35% Signal K-factor Systematic uncertainty
  for(int hi=1;hi<=pv.NBINS;hi++){

     fperr = pow(signal_aCw_m26->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_m26->GetBinContent(hi),2);
     signal_aCw_m26->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_m28->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_m28->GetBinContent(hi),2);
     signal_aCw_m28->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_m30->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_m30->GetBinContent(hi),2);
     signal_aCw_m30->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_m32->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_m32->GetBinContent(hi),2);
     signal_aCw_m32->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_m34->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_m34->GetBinContent(hi),2);
     signal_aCw_m34->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_m36->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_m36->GetBinContent(hi),2);
     signal_aCw_m36->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_m38->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_m38->GetBinContent(hi),2);
     signal_aCw_m38->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_m40->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_m40->GetBinContent(hi),2);
     signal_aCw_m40->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_m42->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_m42->GetBinContent(hi),2);
     signal_aCw_m42->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_m44->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_m44->GetBinContent(hi),2);
     signal_aCw_m44->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_m46->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_m46->GetBinContent(hi),2);
     signal_aCw_m46->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_m48->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_m48->GetBinContent(hi),2);
     signal_aCw_m48->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_m50->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_m50->GetBinContent(hi),2);
     signal_aCw_m50->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_m80->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_m80->GetBinContent(hi),2);
     signal_aCw_m80->SetBinError(hi,sqrt(fperr));


     fperr = pow(signal_aCw_26->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_26->GetBinContent(hi),2);
     signal_aCw_26->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_28->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_28->GetBinContent(hi),2);
     signal_aCw_28->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_30->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_30->GetBinContent(hi),2);
     signal_aCw_30->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_32->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_32->GetBinContent(hi),2);
     signal_aCw_32->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_34->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_34->GetBinContent(hi),2);
     signal_aCw_34->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_36->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_36->GetBinContent(hi),2);
     signal_aCw_36->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_38->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_38->GetBinContent(hi),2);
     signal_aCw_38->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_40->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_40->GetBinContent(hi),2);
     signal_aCw_40->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_42->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_42->GetBinContent(hi),2);
     signal_aCw_42->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_44->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_44->GetBinContent(hi),2);
     signal_aCw_44->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_46->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_46->GetBinContent(hi),2);
     signal_aCw_46->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_48->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_48->GetBinContent(hi),2);
     signal_aCw_48->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_50->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_50->GetBinContent(hi),2);
     signal_aCw_50->SetBinError(hi,sqrt(fperr));

     fperr = pow(signal_aCw_80->GetBinError(hi),2);
     fperr += pow(0.28,2)*pow(signal_aCw_80->GetBinContent(hi),2);
     signal_aCw_80->SetBinError(hi,sqrt(fperr));

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

  signal_aCw_80->SetYTitle(tmpc);
  signal_aCw_80->GetXaxis()->SetTitle(pv.xlabel);
  signal_aCw_80->GetYaxis()->CenterTitle(true);

  signal_aCw_50->SetYTitle(tmpc);
  signal_aCw_50->GetXaxis()->SetTitle(pv.xlabel);
  signal_aCw_50->GetYaxis()->CenterTitle(true);

  signal_aCw_30->SetYTitle(tmpc);
  signal_aCw_30->GetXaxis()->SetTitle(pv.xlabel);
  signal_aCw_30->GetYaxis()->CenterTitle(true);

  signal_aCw_m30->SetYTitle(tmpc);
  signal_aCw_m30->GetXaxis()->SetTitle(pv.xlabel);
  signal_aCw_m30->GetYaxis()->CenterTitle(true);

  signal_aCw_m50->SetYTitle(tmpc);
  signal_aCw_m50->GetXaxis()->SetTitle(pv.xlabel);
  signal_aCw_m50->GetYaxis()->CenterTitle(true);

  signal_aCw_m80->SetYTitle(tmpc);
  signal_aCw_m80->GetXaxis()->SetTitle(pv.xlabel);
  signal_aCw_m80->GetYaxis()->CenterTitle(true);


  //////////////////////////////////////////////////////////
  // Save Observed Data, Background (+ SM WWA), Background +
  // Uncertainty, Background - Uncertainty, Anomalous Signal
  // histograms to output ROOT file:
  std::cout<<"Save Histograms..."<<std::endl;
  f.cd();
  signal_aCw_80->Write();
  signal_aCw_50->Write();
  signal_aCw_30->Write();
  signal_aCw_m30->Write();
  signal_aCw_m50->Write();
  signal_aCw_m80->Write();

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

  signal_aCw_m38->Write();
  signal_aCw_m36->Write();
  signal_aCw_m34->Write();
  signal_aCw_m32->Write();
  signal_aCw_m28->Write();
  signal_aCw_m26->Write();
  signal_aCw_m40->Write();
  signal_aCw_m42->Write();
  signal_aCw_m44->Write();
  signal_aCw_m46->Write();
  signal_aCw_m48->Write();

  signal_aCw_38->Write();
  signal_aCw_36->Write();
  signal_aCw_34->Write();
  signal_aCw_32->Write();
  signal_aCw_28->Write();
  signal_aCw_26->Write();
  signal_aCw_40->Write();
  signal_aCw_42->Write();
  signal_aCw_44->Write();
  signal_aCw_46->Write();
  signal_aCw_48->Write();


  //For conveners
//  th1wwa->Write();

  //
}// End Main function
