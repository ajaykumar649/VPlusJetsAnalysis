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
void mkROOTaqgcElKCW_Para(){


  //////////////////////////////////////
  // Set MC normalization scale factors:
  const double intLUMI = 19166;

  // PT dependent k-factor included (same for WWA aQGC)
  const double WWA_scale     =  2.1*0.01362 * intLUMI/198777;
  const double WWA2_scale    =  2.1*0.01409 * intLUMI/199183;

  const double KCW_m3m5_scale     = 2.1*0.0361451 * intLUMI/201394;
  const double KCW_m2m5_scale     = 2.1*0.0288621 * intLUMI/75392;
  const double KCW_m1m5_scale     = 2.1*0.0246930 * intLUMI/137697;
  const double KCW_p3m5_scale     = 2.1*0.0370699 * intLUMI/114393;
  const double KCW_p1m5_scale     = 2.1*0.0250635 * intLUMI/197530;


  ///////////////////////////////////////////////////////////////////////////////////
  // Specify what kinematical distribution to observe, as well as histogram settings:
  // 
//  plotVar_t pv = {"masslvjja",700,1040,10,3,"M_{l#nujj#gamma} (GeV/c^{2})"};
  plotVar_t pv = {"Photon_Et[iPhoton12]",30,450,10,3,"Photon ET (GeV)"};
  if ( !strlen(pv.plotvar) ) break;
  std::cout << TString(pv.plotvar) << "\t"<<pv.MINRange<<"\t" << pv.MAXRange<<"\t" << pv.NBINS<<"\tTHE CUT " << endl;


  ////////////////////////////////
  // Specify event selection cuts:
  TCut the_cutKfac("effwt*puwt*(iPhoton12>-1 && i12Jet1>-1 && i12Jet2>-1 && abs(W_electron_eta)<2.5 && W_electron_pt>30 && event_met_pfmet>35. && W_mt>30 && abs(Photon_Eta[iPhoton12])<1.4442 && Photon_Et[iPhoton12]>30.&& Photon_dRlep[iPhoton12] > 0.5 && JetPFCor_dRpho12[i12Jet1]>0.5 && JetPFCor_dRpho12[i12Jet2]>0.5 && abs(JetPFCor_dphiMET[i12Jet1])>0.4 && abs(JetPFCor_dphiMET[i12Jet2])>0.4 && JetPFCor_bDiscriminatorCSV[i12Jet1]<0.679 && JetPFCor_bDiscriminatorCSV[i12Jet2]<0.679 && abs(JetPFCor_Eta[i12Jet1]-JetPFCor_Eta[i12Jet2])<1.4 && c2jMass12>70. && c2jMass12<100. && abs(91.1876-massla)>10. &&((i12Jet3>-1)? JetPFCor_dRpho12[i12Jet3]>0.5: 1 )&&((i12Jet4>-1)? JetPFCor_dRpho12[i12Jet4]>0.5: 1 ))");
//mva2jWWAelA1>0.2

  ///////////////////////////
  // Create output ROOT file:
  TFile f("para_el_KCW_WWA_PhotonEt.root", "RECREATE");


  //////////////////////////////////////////////////
  // Create file pointers for each sample ROOT file:
  TFile *wwaShape_file,*wwa2Shape_file;

  TFile *KCW_m3m5_file,*KCW_m2m5_file,*KCW_m1m5_file,*KCW_p1m5_file,*KCW_p3m5_file;


  //////////////////////////////
  // Open each sample ROOT file:
  wwaShape_file = new TFile("InData_New/RD_el_qq_wpwma_wp_qq_wm_lvl.root");
  wwa2Shape_file = new TFile("InData_New/RD_el_qq_wpwma_wp_lvl_wm_qq.root");

  KCW_m3m5_file = new TFile("InData_aQGC/RD_el_kCW_m3m5wwza_CMSSW532.root.root");
  KCW_m2m5_file = new TFile("InData_aQGC/RD_el_kCW_m2m5wwza_CMSSW532.root.root");
  KCW_m1m5_file = new TFile("InData_aQGC/RD_el_kCW_m1m5wwza_CMSSW532.root.root");
  KCW_p1m5_file = new TFile("InData_aQGC/RD_el_kCW_p1m5wwza_CMSSW532.root.root");
  KCW_p3m5_file = new TFile("InData_aQGC/RD_el_kCW_p3m5wwza_CMSSW532.root.root");


  ///////////////////////////////////////////////////
  // Retrieve ROOT tree with kinematic distributions:
  TTree* treewwa    = (TTree*)    wwaShape_file->Get("WJet");
  TTree* treewwa2    = (TTree*)    wwa2Shape_file->Get("WJet");

  TTree* treeKCW_m3m5 = (TTree*) KCW_m3m5_file->Get("WJet");
  TTree* treeKCW_m2m5 = (TTree*) KCW_m2m5_file->Get("WJet");
  TTree* treeKCW_m1m5 = (TTree*) KCW_m1m5_file->Get("WJet");
  TTree* treeKCW_p1m5 = (TTree*) KCW_p1m5_file->Get("WJet");
  TTree* treeKCW_p3m5 = (TTree*) KCW_p3m5_file->Get("WJet");


  ////////////////////////////////////////////////////////////
  // Create kinematic-distribution histograms for each sample:
  TH1* th1wwa = new TH1D("th1wwa", "th1wwa", pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* th1wwa2 = new TH1D("th1wwa2", "th1wwa2", pv.NBINS, pv.MINRange, pv.MAXRange);

  TH1* signal_KCW_30 = new TH1D("signal_KCW_30","signal_KCW_3",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_KCW_20 = new TH1D("signal_KCW_20","signal_KCW_2",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_KCW_10 = new TH1D("signal_KCW_10","signal_KCW_1",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_KCW_m10 = new TH1D("signal_KCW_m10","signal_KCW_-1",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_KCW_m20 = new TH1D("signal_KCW_m20","signal_KCW_-2",pv.NBINS, pv.MINRange, pv.MAXRange);
  TH1* signal_KCW_m30 = new TH1D("signal_KCW_m30","signal_KCW_-3",pv.NBINS, pv.MINRange, pv.MAXRange);


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
  treeKCW_p3m5->Draw(TString(pv.plotvar)+TString(">>signal_KCW_30"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_3 WWA Histogram..."<<std::endl;
  treeKCW_p1m5->Draw(TString(pv.plotvar)+TString(">>signal_KCW_10"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_4 WWA Histogram..."<<std::endl;
  treeKCW_m1m5->Draw(TString(pv.plotvar)+TString(">>signal_KCW_m10"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_5 WWA Histogram..."<<std::endl;
  treeKCW_m2m5->Draw(TString(pv.plotvar)+TString(">>signal_KCW_m20"), the_cutKfac, "goff");

  std::cout<<"Fill aQGC_6 WWA Histogram..."<<std::endl;
  treeKCW_m3m5->Draw(TString(pv.plotvar)+TString(">>signal_KCW_m30"), the_cutKfac, "goff");

  signal_KCW_30->AddBinContent(pv.NBINS,signal_KCW_30->GetBinContent(pv.NBINS+1));signal_KCW_30->SetBinContent(pv.NBINS+1,0.);
  signal_KCW_10->AddBinContent(pv.NBINS,signal_KCW_10->GetBinContent(pv.NBINS+1));signal_KCW_10->SetBinContent(pv.NBINS+1,0.);
  signal_KCW_m10->AddBinContent(pv.NBINS,signal_KCW_m10->GetBinContent(pv.NBINS+1));signal_KCW_m10->SetBinContent(pv.NBINS+1,0.);
  signal_KCW_m20->AddBinContent(pv.NBINS,signal_KCW_m20->GetBinContent(pv.NBINS+1));signal_KCW_m20->SetBinContent(pv.NBINS+1,0.);
  signal_KCW_m30->AddBinContent(pv.NBINS,signal_KCW_m30->GetBinContent(pv.NBINS+1));signal_KCW_m30->SetBinContent(pv.NBINS+1,0.);


  /////////////////////////
  // Normalize each sample:
  std::cout<<"\nScale Histograms..."<<std::endl;
  th1wwa->Scale(WWA_scale);
  th1wwa2->Scale(WWA2_scale);

  signal_KCW_30->Scale(KCW_p3m5_scale);
  signal_KCW_10->Scale(KCW_p1m5_scale);
  signal_KCW_m10->Scale(KCW_m1m5_scale);
  signal_KCW_m20->Scale(KCW_m2m5_scale);
  signal_KCW_m30->Scale(KCW_m3m5_scale);


  ///////////////////////////
  // Combine certain samples:
  th1wwa->Add(th1wwa2,1);

  signal_KCW_30->Divide(th1wwa);
  signal_KCW_10->Divide(th1wwa);
  signal_KCW_m10->Divide(th1wwa);
  signal_KCW_m20->Divide(th1wwa);
  signal_KCW_m30->Divide(th1wwa);


  ///////////////////////////
  //Fill Parabolic Histogram:
  TH1* bin_1 = new TH1D("bin_1","bin_1",7, -3.5E-5, 3.5E-5);
  TH1* bin_2 = new TH1D("bin_2","bin_2",7, -3.5E-5, 3.5E-5);
  TH1* bin_3 = new TH1D("bin_3","bin_3",7, -3.5E-5, 3.5E-5);
  TH1* bin_4 = new TH1D("bin_4","bin_4",7, -3.5E-5, 3.5E-5);
  TH1* bin_5 = new TH1D("bin_5","bin_5",7, -3.5E-5, 3.5E-5);
  TH1* bin_6 = new TH1D("bin_6","bin_6",7, -3.5E-5, 3.5E-5);
  TH1* bin_7 = new TH1D("bin_7","bin_7",7, -3.5E-5, 3.5E-5);
  TH1* bin_8 = new TH1D("bin_8","bin_8",7, -3.5E-5, 3.5E-5);
  TH1* bin_9 = new TH1D("bin_9","bin_9",7, -3.5E-5, 3.5E-5);
  TH1* bin_10 = new TH1D("bin_10","bin_10",7, -3.5E-5, 3.5E-5);


  bin_1->SetBinContent(1,signal_KCW_m30->GetBinContent(1));
  bin_1->SetBinContent(2,signal_KCW_m20->GetBinContent(1));
  bin_1->SetBinContent(3,signal_KCW_m10->GetBinContent(1));
  bin_1->SetBinContent(4,1);
  bin_1->SetBinContent(5,signal_KCW_10->GetBinContent(1));
  bin_1->SetBinContent(7,signal_KCW_30->GetBinContent(1));

  bin_2->SetBinContent(1,signal_KCW_m30->GetBinContent(2));
  bin_2->SetBinContent(2,signal_KCW_m20->GetBinContent(2));
  bin_2->SetBinContent(3,signal_KCW_m10->GetBinContent(2));
  bin_2->SetBinContent(4,1);
  bin_2->SetBinContent(5,signal_KCW_10->GetBinContent(2));
  bin_2->SetBinContent(7,signal_KCW_30->GetBinContent(2));

  bin_3->SetBinContent(1,signal_KCW_m30->GetBinContent(3));
  bin_3->SetBinContent(2,signal_KCW_m20->GetBinContent(3));
  bin_3->SetBinContent(3,signal_KCW_m10->GetBinContent(3));
  bin_3->SetBinContent(4,1);
  bin_3->SetBinContent(5,signal_KCW_10->GetBinContent(3));
  bin_3->SetBinContent(7,signal_KCW_30->GetBinContent(3));

  bin_4->SetBinContent(1,signal_KCW_m30->GetBinContent(4));
  bin_4->SetBinContent(2,signal_KCW_m20->GetBinContent(4));
  bin_4->SetBinContent(3,signal_KCW_m10->GetBinContent(4));
  bin_4->SetBinContent(4,1);
  bin_4->SetBinContent(5,signal_KCW_10->GetBinContent(4));
  bin_4->SetBinContent(7,signal_KCW_30->GetBinContent(4));

  bin_5->SetBinContent(1,signal_KCW_m30->GetBinContent(5));
  bin_5->SetBinContent(2,signal_KCW_m20->GetBinContent(5));
  bin_5->SetBinContent(3,signal_KCW_m10->GetBinContent(5));
  bin_5->SetBinContent(4,1);
  bin_5->SetBinContent(5,signal_KCW_10->GetBinContent(5));
  bin_5->SetBinContent(7,signal_KCW_30->GetBinContent(5));

  bin_6->SetBinContent(1,signal_KCW_m30->GetBinContent(6));
  bin_6->SetBinContent(2,signal_KCW_m20->GetBinContent(6));
  bin_6->SetBinContent(3,signal_KCW_m10->GetBinContent(6));
  bin_6->SetBinContent(4,1);
  bin_6->SetBinContent(5,signal_KCW_10->GetBinContent(6));
  bin_6->SetBinContent(7,signal_KCW_30->GetBinContent(6));

  bin_7->SetBinContent(1,signal_KCW_m30->GetBinContent(7));
  bin_7->SetBinContent(2,signal_KCW_m20->GetBinContent(7));
  bin_7->SetBinContent(3,signal_KCW_m10->GetBinContent(7));
  bin_7->SetBinContent(4,1);
  bin_7->SetBinContent(5,signal_KCW_10->GetBinContent(7));
  bin_7->SetBinContent(7,signal_KCW_30->GetBinContent(7));

  bin_8->SetBinContent(1,signal_KCW_m30->GetBinContent(8));
  bin_8->SetBinContent(2,signal_KCW_m20->GetBinContent(8));
  bin_8->SetBinContent(3,signal_KCW_m10->GetBinContent(8));
  bin_8->SetBinContent(4,1);
  bin_8->SetBinContent(5,signal_KCW_10->GetBinContent(8));
  bin_8->SetBinContent(7,signal_KCW_30->GetBinContent(8));

  bin_9->SetBinContent(1,signal_KCW_m30->GetBinContent(9));
  bin_9->SetBinContent(2,signal_KCW_m20->GetBinContent(9));
  bin_9->SetBinContent(3,signal_KCW_m10->GetBinContent(9));
  bin_9->SetBinContent(4,1);
  bin_9->SetBinContent(5,signal_KCW_10->GetBinContent(9));
  bin_9->SetBinContent(7,signal_KCW_30->GetBinContent(9));

  bin_10->SetBinContent(1,signal_KCW_m30->GetBinContent(10));
  bin_10->SetBinContent(2,signal_KCW_m20->GetBinContent(10));
  bin_10->SetBinContent(3,signal_KCW_m10->GetBinContent(10));
  bin_10->SetBinContent(4,1);
  bin_10->SetBinContent(5,signal_KCW_10->GetBinContent(10));
  bin_10->SetBinContent(7,signal_KCW_30->GetBinContent(10));


  ////////////////
  // Fit function:
  Char_t para_fit[] = "[0]+[1]*x+[2]*x^2";
  Char_t fitopt[] = "QMR";
  Double_t xmin = -3E-5;
  Double_t xmax = 3E-5;
  Double_t p[3][10];
  TF1 *pfit = new TF1("pfit",para_fit,xmin,xmax);


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


  ////////////////
  // Closure test:
  // ratio = 1 + (pt[0][0]+pt[0][1]*pt+pt[0][2]*pt^2)*KOW + (pt[1][0]+pt[1][1]*pt+[1][2]*pt^2)*KOW^2
  TH1* test = new TH1D("test","Test aQGC Photon ET",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* test2 = new TH1D("test2","Test aQGC Photon ET",pv.NBINS,pv.MINRange,pv.MAXRange);

  for(Int_t j=1;j<=pv.NBINS;j++){

     Double_t value,bincent;
     TAxis* xaxis = test->GetXaxis();
     bincent = xaxis->GetBinCenter(j);

     value = p[0][j-1]+p[1][j-1]*(3E-5)+p[2][j-1]*pow(3E-5,2);
     test->SetBinContent(j,value);

     test2->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-3E-5)+p[2][j-1]*pow(-3E-5,2));

  }


  TH1D* test_r = (TH1D*)test->Clone("test_r");
  TH1D* test2_r = (TH1D*)test2->Clone("test2_r");

  test_r->Divide(signal_KCW_30);
  test2_r->Divide(signal_KCW_m30);

  test->Multiply(th1wwa);
  test2->Multiply(th1wwa);
  test->Add(th1wwa,-1);
  test2->Add(th1wwa,-1);


  /////////////////////
  // Simulate new aQGC:
  TH1* signal_KCW_2 = new TH1D("signal_KCW_2","signal_KCW_0p2",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_KCW_5 = new TH1D("signal_KCW_5","signal_KCW_0p5",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_KCW_8 = new TH1D("signal_KCW_8","signal_KCW_0p8",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_KCW_12 = new TH1D("signal_KCW_12","signal_KCW_1p2",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_KCW_15 = new TH1D("signal_KCW_15","signal_KCW_1p5",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_KCW_18 = new TH1D("signal_KCW_18","signal_KCW_1p8",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_KCW_22 = new TH1D("signal_KCW_22","signal_KCW_2p2",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_KCW_25 = new TH1D("signal_KCW_25","signal_KCW_2p5",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_KCW_28 = new TH1D("signal_KCW_28","signal_KCW_2p8",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_KCW_32 = new TH1D("signal_KCW_32","signal_KCW_3p2",pv.NBINS,pv.MINRange,pv.MAXRange);

  TH1* signal_KCW_m2 = new TH1D("signal_KCW_m2","signal_KCW_-0p2",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_KCW_m5 = new TH1D("signal_KCW_m5","signal_KCW_-0p5",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_KCW_m8 = new TH1D("signal_KCW_m8","signal_KCW_-0p8",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_KCW_m12 = new TH1D("signal_KCW_m12","signal_KCW_-1p2",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_KCW_m15 = new TH1D("signal_KCW_m15","signal_KCW_-1p5",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_KCW_m18 = new TH1D("signal_KCW_m18","signal_KCW_-1p8",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_KCW_m22 = new TH1D("signal_KCW_m22","signal_KCW_-2p2",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_KCW_m25 = new TH1D("signal_KCW_m25","signal_KCW_-2p5",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_KCW_m28 = new TH1D("signal_KCW_m28","signal_KCW_-2p8",pv.NBINS,pv.MINRange,pv.MAXRange);
  TH1* signal_KCW_m32 = new TH1D("signal_KCW_m32","signal_KCW_-3p2",pv.NBINS,pv.MINRange,pv.MAXRange);

  signal_KCW_2->Sumw2();
  signal_KCW_5->Sumw2();
  signal_KCW_8->Sumw2();
  signal_KCW_12->Sumw2();
  signal_KCW_15->Sumw2();
  signal_KCW_18->Sumw2();
  signal_KCW_22->Sumw2();
  signal_KCW_25->Sumw2();
  signal_KCW_28->Sumw2();
  signal_KCW_32->Sumw2();
  signal_KCW_m2->Sumw2();
  signal_KCW_m5->Sumw2();
  signal_KCW_m8->Sumw2();
  signal_KCW_m12->Sumw2();
  signal_KCW_m15->Sumw2();
  signal_KCW_m18->Sumw2();
  signal_KCW_m22->Sumw2();
  signal_KCW_m25->Sumw2();
  signal_KCW_m28->Sumw2();
  signal_KCW_m32->Sumw2();


  for(Int_t j=1;j<=pv.NBINS;j++){

     Double_t bincent;
     TAxis* xaxis = test->GetXaxis();
     bincent = xaxis->GetBinCenter(j);

     signal_KCW_m30->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-3.E-5)+p[2][j-1]*pow(-3.E-5,2));
     signal_KCW_m20->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-2.E-5)+p[2][j-1]*pow(-2.E-5,2));
     signal_KCW_m10->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-1.E-5)+p[2][j-1]*pow(-1.E-5,2));

     signal_KCW_m18->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-1.8E-5)+p[2][j-1]*pow(-1.8E-5,2));
     signal_KCW_m15->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-1.5E-5)+p[2][j-1]*pow(-1.5E-5,2));
     signal_KCW_m12->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-1.2E-5)+p[2][j-1]*pow(-1.2E-5,2));
     signal_KCW_m8->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-0.8E-5)+p[2][j-1]*pow(-0.8E-5,2));
     signal_KCW_m2->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-0.2E-5)+p[2][j-1]*pow(-0.2E-5,2));
     signal_KCW_m5->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-0.5E-5)+p[2][j-1]*pow(-0.5E-5,2));
     signal_KCW_m22->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-2.2E-5)+p[2][j-1]*pow(-2.2E-5,2));
     signal_KCW_m25->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-2.5E-5)+p[2][j-1]*pow(-2.5E-5,2));
     signal_KCW_m28->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-2.8E-5)+p[2][j-1]*pow(-2.8E-5,2));
     signal_KCW_m32->SetBinContent(j,p[0][j-1]+p[1][j-1]*(-3.2E-5)+p[2][j-1]*pow(-3.2E-5,2));

     signal_KCW_30->SetBinContent(j,p[0][j-1]+p[1][j-1]*(3.E-5)+p[2][j-1]*pow(3.E-5,2));
     signal_KCW_20->SetBinContent(j,p[0][j-1]+p[1][j-1]*(2.E-5)+p[2][j-1]*pow(2.E-5,2));
     signal_KCW_10->SetBinContent(j,p[0][j-1]+p[1][j-1]*(1.E-5)+p[2][j-1]*pow(1.E-5,2));

     signal_KCW_18->SetBinContent(j,p[0][j-1]+p[1][j-1]*(1.8E-5)+p[2][j-1]*pow(1.8E-5,2));
     signal_KCW_15->SetBinContent(j,p[0][j-1]+p[1][j-1]*(1.5E-5)+p[2][j-1]*pow(1.5E-5,2));
     signal_KCW_12->SetBinContent(j,p[0][j-1]+p[1][j-1]*(1.2E-5)+p[2][j-1]*pow(1.2E-5,2));
     signal_KCW_8->SetBinContent(j,p[0][j-1]+p[1][j-1]*(0.8E-5)+p[2][j-1]*pow(0.8E-5,2));
     signal_KCW_5->SetBinContent(j,p[0][j-1]+p[1][j-1]*(0.5E-5)+p[2][j-1]*pow(0.5E-5,2));
     signal_KCW_2->SetBinContent(j,p[0][j-1]+p[1][j-1]*(0.2E-5)+p[2][j-1]*pow(0.2E-5,2));
     signal_KCW_22->SetBinContent(j,p[0][j-1]+p[1][j-1]*(2.2E-5)+p[2][j-1]*pow(2.2E-5,2));
     signal_KCW_25->SetBinContent(j,p[0][j-1]+p[1][j-1]*(2.5E-5)+p[2][j-1]*pow(2.5E-5,2));
     signal_KCW_28->SetBinContent(j,p[0][j-1]+p[1][j-1]*(2.8E-5)+p[2][j-1]*pow(2.8E-5,2));
     signal_KCW_32->SetBinContent(j,p[0][j-1]+p[1][j-1]*(3.2E-5)+p[2][j-1]*pow(3.2E-5,2));

  }


  signal_KCW_m30->Multiply(th1wwa);
  signal_KCW_m20->Multiply(th1wwa);
  signal_KCW_m10->Multiply(th1wwa);

  signal_KCW_m18->Multiply(th1wwa);
  signal_KCW_m15->Multiply(th1wwa);
  signal_KCW_m12->Multiply(th1wwa);
  signal_KCW_m8->Multiply(th1wwa);
  signal_KCW_m5->Multiply(th1wwa);
  signal_KCW_m2->Multiply(th1wwa);
  signal_KCW_m22->Multiply(th1wwa);
  signal_KCW_m25->Multiply(th1wwa);
  signal_KCW_m28->Multiply(th1wwa);
  signal_KCW_m32->Multiply(th1wwa);

  signal_KCW_30->Multiply(th1wwa);
  signal_KCW_20->Multiply(th1wwa);
  signal_KCW_10->Multiply(th1wwa);

  signal_KCW_18->Multiply(th1wwa);
  signal_KCW_15->Multiply(th1wwa);
  signal_KCW_12->Multiply(th1wwa);
  signal_KCW_8->Multiply(th1wwa);
  signal_KCW_5->Multiply(th1wwa);
  signal_KCW_2->Multiply(th1wwa);
  signal_KCW_22->Multiply(th1wwa);
  signal_KCW_25->Multiply(th1wwa);
  signal_KCW_28->Multiply(th1wwa);
  signal_KCW_32->Multiply(th1wwa);


  signal_KCW_m30->Add(th1wwa,-1);
  signal_KCW_m20->Add(th1wwa,-1);
  signal_KCW_m10->Add(th1wwa,-1);

  signal_KCW_m18->Add(th1wwa,-1);
  signal_KCW_m15->Add(th1wwa,-1);
  signal_KCW_m12->Add(th1wwa,-1);
  signal_KCW_m8->Add(th1wwa,-1);
  signal_KCW_m5->Add(th1wwa,-1);
  signal_KCW_m2->Add(th1wwa,-1);
  signal_KCW_m22->Add(th1wwa,-1);
  signal_KCW_m25->Add(th1wwa,-1);
  signal_KCW_m28->Add(th1wwa,-1);
  signal_KCW_m32->Add(th1wwa,-1);

  signal_KCW_30->Add(th1wwa,-1);
  signal_KCW_20->Add(th1wwa,-1);
  signal_KCW_10->Add(th1wwa,-1);

  signal_KCW_18->Add(th1wwa,-1);
  signal_KCW_15->Add(th1wwa,-1);
  signal_KCW_12->Add(th1wwa,-1);
  signal_KCW_8->Add(th1wwa,-1);
  signal_KCW_5->Add(th1wwa,-1);
  signal_KCW_2->Add(th1wwa,-1);
  signal_KCW_22->Add(th1wwa,-1);
  signal_KCW_25->Add(th1wwa,-1);
  signal_KCW_28->Add(th1wwa,-1);
  signal_KCW_32->Add(th1wwa,-1);


  signal_KCW_m30->Scale(1.185/2.1);
  signal_KCW_m20->Scale(1.185/2.1);
  signal_KCW_m10->Scale(1.185/2.1);

  signal_KCW_m18->Scale(1.185/2.1);
  signal_KCW_m15->Scale(1.185/2.1);
  signal_KCW_m12->Scale(1.185/2.1);
  signal_KCW_m8->Scale(1.185/2.1);
  signal_KCW_m5->Scale(1.185/2.1);
  signal_KCW_m2->Scale(1.185/2.1);
  signal_KCW_m22->Scale(1.185/2.1);
  signal_KCW_m25->Scale(1.185/2.1);
  signal_KCW_m28->Scale(1.185/2.1);
  signal_KCW_m32->Scale(1.185/2.1);

  signal_KCW_30->Scale(1.185/2.1);
  signal_KCW_20->Scale(1.185/2.1);
  signal_KCW_10->Scale(1.185/2.1);

  signal_KCW_18->Scale(1.185/2.1);
  signal_KCW_15->Scale(1.185/2.1);
  signal_KCW_12->Scale(1.185/2.1);
  signal_KCW_8->Scale(1.185/2.1);
  signal_KCW_5->Scale(1.185/2.1);
  signal_KCW_2->Scale(1.185/2.1);
  signal_KCW_22->Scale(1.185/2.1);
  signal_KCW_25->Scale(1.185/2.1);
  signal_KCW_28->Scale(1.185/2.1);
  signal_KCW_32->Scale(1.185/2.1);


  ////////////////////////
  // Set histogram labels:
  const double BINWIDTH = ((pv.MAXRange-pv.MINRange)/pv.NBINS);
  char tmpc[100];    sprintf(tmpc,"Events / %.1f GeV",BINWIDTH);
  if (pv.slog==1)    sprintf(tmpc,"Events / %.1f",BINWIDTH);
  if (pv.slog==2)    sprintf(tmpc,"Events / %.2f",BINWIDTH);
  if (pv.slog==3)    sprintf(tmpc,"Events / %.0f GeV",BINWIDTH);
  if (pv.slog==6)    sprintf(tmpc,"Events / %.2f rad",BINWIDTH);

  signal_KCW_30->SetYTitle(tmpc);
  signal_KCW_30->GetXaxis()->SetTitle(pv.xlabel);
  signal_KCW_30->GetYaxis()->CenterTitle(true);

  signal_KCW_20->SetYTitle(tmpc);
  signal_KCW_20->GetXaxis()->SetTitle(pv.xlabel);
  signal_KCW_20->GetYaxis()->CenterTitle(true);

  signal_KCW_10->SetYTitle(tmpc);
  signal_KCW_10->GetXaxis()->SetTitle(pv.xlabel);
  signal_KCW_10->GetYaxis()->CenterTitle(true);

  signal_KCW_m10->SetYTitle(tmpc);
  signal_KCW_m10->GetXaxis()->SetTitle(pv.xlabel);
  signal_KCW_m10->GetYaxis()->CenterTitle(true);

  signal_KCW_m20->SetYTitle(tmpc);
  signal_KCW_m20->GetXaxis()->SetTitle(pv.xlabel);
  signal_KCW_m20->GetYaxis()->CenterTitle(true);

  signal_KCW_m30->SetYTitle(tmpc);
  signal_KCW_m30->GetXaxis()->SetTitle(pv.xlabel);
  signal_KCW_m30->GetYaxis()->CenterTitle(true);


  ////////////////////////////////////////////////////////
  // Save Anomalous Signal histograms to output ROOT file:
  std::cout<<"Save Histograms...\n"<<std::endl;
  f.cd();
  signal_KCW_30->Write();
  signal_KCW_20->Write();
  signal_KCW_10->Write();
  signal_KCW_m10->Write();
  signal_KCW_m20->Write();
  signal_KCW_m30->Write();

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

  signal_KCW_m18->Write();
  signal_KCW_m15->Write();
  signal_KCW_m12->Write();
  signal_KCW_m8->Write();
  signal_KCW_m5->Write();
  signal_KCW_m2->Write();
  signal_KCW_m22->Write();
  signal_KCW_m25->Write();
  signal_KCW_m28->Write();
  signal_KCW_m32->Write();

  signal_KCW_18->Write();
  signal_KCW_15->Write();
  signal_KCW_12->Write();
  signal_KCW_8->Write();
  signal_KCW_5->Write();
  signal_KCW_2->Write();
  signal_KCW_22->Write();
  signal_KCW_25->Write();
  signal_KCW_28->Write();
  signal_KCW_32->Write();

}// End Main function
