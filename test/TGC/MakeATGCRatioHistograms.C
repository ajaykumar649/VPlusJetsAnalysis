{
  char* dir = "/uscms_data/d2/andersj/Wjj/2012/data/Moriond2013/ReducedTrees/";
  TFile* fSM = new TFile((dir + string("Lambda00_Kappa00_G00.root")).c_str());
  TFile* f_L01K00G00 = new TFile((dir + string("Lambda01_Kappa00_G00.root")).c_str());
  TFile* f_L03K00G00 = new TFile((dir + string("Lambda03_Kappa00_G00.root")).c_str());
  TFile* f_L05K00G00 = new TFile((dir + string("Lambda05_Kappa00_G00.root")).c_str());
  TFile* f_L07K00G00 = new TFile((dir + string("Lambda07_Kappa00_G00.root")).c_str());
  TFile* f_L09K00G00 = new TFile((dir + string("Lambda09_Kappa00_G00.root")).c_str());
  TFile* f_L11K00G00 = new TFile((dir + string("Lambda11_Kappa00_G00.root")).c_str());
  TFile* f_L00K11G00 = new TFile((dir + string("Lambda00_Kappa11_G00.root")).c_str());
  TFile* f_L00K16G00 = new TFile((dir + string("Lambda00_Kappa16_G00.root")).c_str());
  TFile* f_L00K20G00 = new TFile((dir + string("Lambda00_Kappa20_G00.root")).c_str());
  TFile* f_L00K00G11 = new TFile((dir + string("Lambda00_Kappa00_G11.root")).c_str());
  TFile* f_L00K00G40 = new TFile((dir + string("Lambda00_Kappa00_G40.root")).c_str());
  TFile* f_L00K00G60 = new TFile((dir + string("Lambda00_Kappa00_G60.root")).c_str());


  TTree* trSM = (TTree*) fSM->Get("WJet");
  TTree* tr_L01K00G00 = (TTree*) f_L01K00G00->Get("WJet");
  TTree* tr_L03K00G00 = (TTree*) f_L03K00G00->Get("WJet");
  TTree* tr_L05K00G00 = (TTree*) f_L05K00G00->Get("WJet");
  TTree* tr_L07K00G00 = (TTree*) f_L07K00G00->Get("WJet");
  TTree* tr_L09K00G00 = (TTree*) f_L09K00G00->Get("WJet");
  TTree* tr_L11K00G00 = (TTree*) f_L11K00G00->Get("WJet");
  TTree* tr_L00K11G00 = (TTree*) f_L00K11G00->Get("WJet");
  TTree* tr_L00K16G00 = (TTree*) f_L00K16G00->Get("WJet");
  TTree* tr_L00K20G00 = (TTree*) f_L00K20G00->Get("WJet");
  TTree* tr_L00K00G11 = (TTree*) f_L00K00G11->Get("WJet");
  TTree* tr_L00K00G40 = (TTree*) f_L00K00G40->Get("WJet");
  TTree* tr_L00K00G60 = (TTree*) f_L00K00G60->Get("WJet");


  char* dijetPt = "sqrt(JetPFCor_Pt[0]**2+JetPFCor_Pt[1]**2+2*JetPFCor_Pt[0]*JetPFCor_Pt[1]*cos(JetPFCor_Phi[0]-JetPFCor_Phi[1]))";
  trSM->SetAlias("dijetPt", dijetPt);
  tr_L01K00G00->SetAlias("dijetPt", dijetPt);
  tr_L03K00G00->SetAlias("dijetPt", dijetPt);
  tr_L05K00G00->SetAlias("dijetPt", dijetPt);
  tr_L07K00G00->SetAlias("dijetPt", dijetPt);
  tr_L09K00G00->SetAlias("dijetPt", dijetPt);
  tr_L11K00G00->SetAlias("dijetPt", dijetPt);
  tr_L00K11G00->SetAlias("dijetPt", dijetPt);
  tr_L00K16G00->SetAlias("dijetPt", dijetPt);
  tr_L00K20G00->SetAlias("dijetPt", dijetPt);
  tr_L00K00G11->SetAlias("dijetPt", dijetPt);
  tr_L00K00G40->SetAlias("dijetPt", dijetPt);
  tr_L00K00G60->SetAlias("dijetPt", dijetPt);


  char* cutsNoBoost = "(effwt*puwt)*((W_pt<200.) && (dijetPt>70.) &&(abs(JetPFCor_Eta[0])<2.4) &&(abs(JetPFCor_Eta[1])<2.4) &&(abs(JetPFCor_Eta[0]-JetPFCor_Eta[1])<1.5) &&(abs(JetPFCor_dphiMET[0])>0.4) &&(event_met_pfmet>25) &&(W_mt>30.) &&(JetPFCor_Pt[0]>40.) &&(JetPFCor_Pt[1]>35.) &&(JetPFCor_Pt[2]<30.) &&(JetPFCor_bDiscriminatorCSV[0]<0.244) &&(JetPFCor_bDiscriminatorCSV[1]<0.244))";

 char* cutsBoosted = "(effwt*puwt)*((W_pt>200.) &&(event_met_pfmet>65) &&(W_mt>30.) &&(GroomedJet_CA8_pt[0] > 200) &&(abs(GroomedJet_CA8_eta[0])<2.4) &&(JetPFCor_bDiscriminatorCSV[0]<0.244) &&(JetPFCor_bDiscriminatorCSV[1]<0.244) &&(ggdboostedWevt == 1) &&(event_metMVA_met > 65) &&(GroomedJet_numberbjets <1) &&(GroomedJet_CA8_deltaphi_METca8jet > 2.0))";

  ///// ----- Create all the histograms ----------
 double xbins[] = {100., 120., 140., 160., 200., 300., 400., 600.};
  TH1D* hSMNoBoost = new TH1D("hSMNoBoost", "", sizeof(xbins)/ sizeof(xbins[0])-1, xbins);
  hSMNoBoost->Sumw2();
  hSMNoBoost->SetLineWidth(2);
  hSMNoBoost->GetXaxis()->SetTitle("dijet p_{T} (GeV)");
  hSMNoBoost->GetYaxis()->SetTitle("Ratio over SM");


  TH1D* h_L01K00G00_NoBoost = hSMNoBoost->Clone("h_L01K00G00_NoBoost");
  TH1D* h_L03K00G00_NoBoost = hSMNoBoost->Clone("h_L03K00G00_NoBoost");
  TH1D* h_L05K00G00_NoBoost = hSMNoBoost->Clone("h_L05K00G00_NoBoost");
  TH1D* h_L07K00G00_NoBoost = hSMNoBoost->Clone("h_L07K00G00_NoBoost");
  TH1D* h_L09K00G00_NoBoost = hSMNoBoost->Clone("h_L09K00G00_NoBoost");
  TH1D* h_L11K00G00_NoBoost = hSMNoBoost->Clone("h_L11K00G00_NoBoost");
  TH1D* h_L00K11G00_NoBoost = hSMNoBoost->Clone("h_L00K11G00_NoBoost");
  TH1D* h_L00K16G00_NoBoost = hSMNoBoost->Clone("h_L00K16G00_NoBoost");
  TH1D* h_L00K20G00_NoBoost = hSMNoBoost->Clone("h_L00K20G00_NoBoost");
  TH1D* h_L00K00G11_NoBoost = hSMNoBoost->Clone("h_L00K00G11_NoBoost");
  TH1D* h_L00K00G40_NoBoost = hSMNoBoost->Clone("h_L00K00G40_NoBoost");
  TH1D* h_L00K00G60_NoBoost = hSMNoBoost->Clone("h_L00K00G60_NoBoost");

  TH1D* hSMBoosted = hSMNoBoost->Clone("hSMBoosted");
  TH1D* h_L01K00G00_Boosted = hSMNoBoost->Clone("h_L01K00G00_Boosted");
  TH1D* h_L03K00G00_Boosted = hSMNoBoost->Clone("h_L03K00G00_Boosted");
  TH1D* h_L05K00G00_Boosted = hSMNoBoost->Clone("h_L05K00G00_Boosted");
  TH1D* h_L07K00G00_Boosted = hSMNoBoost->Clone("h_L07K00G00_Boosted");
  TH1D* h_L09K00G00_Boosted = hSMNoBoost->Clone("h_L09K00G00_Boosted");
  TH1D* h_L11K00G00_Boosted = hSMNoBoost->Clone("h_L11K00G00_Boosted");
  TH1D* h_L00K11G00_Boosted = hSMNoBoost->Clone("h_L00K11G00_Boosted");
  TH1D* h_L00K16G00_Boosted = hSMNoBoost->Clone("h_L00K16G00_Boosted");
  TH1D* h_L00K20G00_Boosted = hSMNoBoost->Clone("h_L00K20G00_Boosted");
  TH1D* h_L00K00G11_Boosted = hSMNoBoost->Clone("h_L00K00G11_Boosted");
  TH1D* h_L00K00G40_Boosted = hSMNoBoost->Clone("h_L00K00G40_Boosted");
  TH1D* h_L00K00G60_Boosted = hSMNoBoost->Clone("h_L00K00G60_Boosted");

  ///// ----- fill the unboosted histograms -----------
  trSM->Draw("dijetPt>>hSMNoBoost", cutsNoBoost,"goff");
  tr_L01K00G00->Draw("dijetPt>>h_L01K00G00_NoBoost", cutsNoBoost,"goff");
  tr_L03K00G00->Draw("dijetPt>>h_L03K00G00_NoBoost", cutsNoBoost,"goff");
  tr_L05K00G00->Draw("dijetPt>>h_L05K00G00_NoBoost", cutsNoBoost,"goff");
  tr_L07K00G00->Draw("dijetPt>>h_L07K00G00_NoBoost", cutsNoBoost,"goff");
  tr_L09K00G00->Draw("dijetPt>>h_L09K00G00_NoBoost", cutsNoBoost,"goff");
  tr_L11K00G00->Draw("dijetPt>>h_L11K00G00_NoBoost", cutsNoBoost,"goff");
  tr_L00K11G00->Draw("dijetPt>>h_L00K11G00_NoBoost", cutsNoBoost,"goff");
  tr_L00K16G00->Draw("dijetPt>>h_L00K16G00_NoBoost", cutsNoBoost,"goff");
  tr_L00K20G00->Draw("dijetPt>>h_L00K20G00_NoBoost", cutsNoBoost,"goff");
  tr_L00K00G11->Draw("dijetPt>>h_L00K00G11_NoBoost", cutsNoBoost,"goff");
  tr_L00K00G40->Draw("dijetPt>>h_L00K00G40_NoBoost", cutsNoBoost,"goff");
  tr_L00K00G60->Draw("dijetPt>>h_L00K00G60_NoBoost", cutsNoBoost,"goff");

  ///// ----- now fill the boosted histograms -----------
  trSM->Draw("dijetPt>>hSMBoosted", cutsBoosted,"goff");
  tr_L01K00G00->Draw("dijetPt>>h_L01K00G00_Boosted", cutsBoosted,"goff");
  tr_L03K00G00->Draw("dijetPt>>h_L03K00G00_Boosted", cutsBoosted,"goff");
  tr_L05K00G00->Draw("dijetPt>>h_L05K00G00_Boosted", cutsBoosted,"goff");
  tr_L07K00G00->Draw("dijetPt>>h_L07K00G00_Boosted", cutsBoosted,"goff");
  tr_L09K00G00->Draw("dijetPt>>h_L09K00G00_Boosted", cutsBoosted,"goff");
  tr_L11K00G00->Draw("dijetPt>>h_L11K00G00_Boosted", cutsBoosted,"goff");
  tr_L00K11G00->Draw("dijetPt>>h_L00K11G00_Boosted", cutsBoosted,"goff");
  tr_L00K16G00->Draw("dijetPt>>h_L00K16G00_Boosted", cutsBoosted,"goff");
  tr_L00K20G00->Draw("dijetPt>>h_L00K20G00_Boosted", cutsBoosted,"goff");
  tr_L00K00G11->Draw("dijetPt>>h_L00K00G11_Boosted", cutsBoosted,"goff");
  tr_L00K00G40->Draw("dijetPt>>h_L00K00G40_Boosted", cutsBoosted,"goff");
  tr_L00K00G60->Draw("dijetPt>>h_L00K00G60_Boosted", cutsBoosted,"goff");


  // --- normalization scales ------ 
  const double SM_scale   = 2.729 / 149395; // SM: lambda=0, dkappa=0, dg1=0
  const double L01K00G00_scale = 2.730 / 90562;
  const double L03K00G00_scale = 2.736 / 136932;
  const double L05K00G00_scale = 2.760 / 137481;
  const double L07K00G00_scale = 2.793 / 146345;
  const double L09K00G00_scale = 2.830 / 136427;
  const double L11K00G00_scale = 2.890 / 138886;

  const double L00K11G00_scale = 2.760 / 130403;
  const double L00K16G00_scale = 2.848 / 139865;
  const double L00K20G00_scale = 2.947 / 129415;

  const double L00K00G11_scale = 2.729 / 129386;
  const double L00K00G40_scale = 2.792 / 124954;
  const double L00K00G60_scale = 2.940 / 127922;

  hSMNoBoost->Scale(SM_scale);
  h_L01K00G00_NoBoost->Scale(L01K00G00_scale);
  h_L03K00G00_NoBoost->Scale(L03K00G00_scale);
  h_L05K00G00_NoBoost->Scale(L05K00G00_scale);
  h_L07K00G00_NoBoost->Scale(L07K00G00_scale);
  h_L09K00G00_NoBoost->Scale(L09K00G00_scale);
  h_L11K00G00_NoBoost->Scale(L11K00G00_scale);
  h_L00K11G00_NoBoost->Scale(L00K11G00_scale);
  h_L00K16G00_NoBoost->Scale(L00K16G00_scale);
  h_L00K20G00_NoBoost->Scale(L00K20G00_scale);
  h_L00K00G11_NoBoost->Scale(L00K00G11_scale);
  h_L00K00G40_NoBoost->Scale(L00K00G40_scale);
  h_L00K00G60_NoBoost->Scale(L00K00G60_scale);


  hSMBoosted->Scale(SM_scale);
  h_L01K00G00_Boosted->Scale(L01K00G00_scale);
  h_L03K00G00_Boosted->Scale(L03K00G00_scale);
  h_L05K00G00_Boosted->Scale(L05K00G00_scale);
  h_L07K00G00_Boosted->Scale(L07K00G00_scale);
  h_L09K00G00_Boosted->Scale(L09K00G00_scale);
  h_L11K00G00_Boosted->Scale(L11K00G00_scale);
  h_L00K11G00_Boosted->Scale(L00K11G00_scale);
  h_L00K16G00_Boosted->Scale(L00K16G00_scale);
  h_L00K20G00_Boosted->Scale(L00K20G00_scale);
  h_L00K00G11_Boosted->Scale(L00K00G11_scale);
  h_L00K00G40_Boosted->Scale(L00K00G40_scale);
  h_L00K00G60_Boosted->Scale(L00K00G60_scale);




  //----- combine boosted & unboosted histograms ------
  TH1D* hSM = hSMNoBoost->Clone("hSM");
  TH1D* h_L01K00G00 = h_L01K00G00_NoBoost->Clone("h_L01K00G00");
  TH1D* h_L03K00G00 = h_L03K00G00_NoBoost->Clone("h_L03K00G00");
  TH1D* h_L05K00G00 = h_L05K00G00_NoBoost->Clone("h_L05K00G00");
  TH1D* h_L07K00G00 = h_L07K00G00_NoBoost->Clone("h_L07K00G00");
  TH1D* h_L09K00G00 = h_L09K00G00_NoBoost->Clone("h_L09K00G00");
  TH1D* h_L11K00G00 = h_L11K00G00_NoBoost->Clone("h_L11K00G00");
  TH1D* h_L00K11G00 = h_L00K11G00_NoBoost->Clone("h_L00K11G00");
  TH1D* h_L00K16G00 = h_L00K16G00_NoBoost->Clone("h_L00K16G00");
  TH1D* h_L00K20G00 = h_L00K20G00_NoBoost->Clone("h_L00K20G00");
  TH1D* h_L00K00G11 = h_L00K00G11_NoBoost->Clone("h_L00K00G11");
  TH1D* h_L00K00G40 = h_L00K00G40_NoBoost->Clone("h_L00K00G40");
  TH1D* h_L00K00G60 = h_L00K00G60_NoBoost->Clone("h_L00K00G60");
  hSM->Add(hSMBoosted);
  h_L01K00G00->Add(h_L01K00G00_Boosted);
  h_L03K00G00->Add(h_L03K00G00_Boosted);
  h_L05K00G00->Add(h_L05K00G00_Boosted);
  h_L07K00G00->Add(h_L07K00G00_Boosted);
  h_L09K00G00->Add(h_L09K00G00_Boosted);
  h_L11K00G00->Add(h_L11K00G00_Boosted);
  h_L00K11G00->Add(h_L00K11G00_Boosted);
  h_L00K16G00->Add(h_L00K16G00_Boosted);
  h_L00K20G00->Add(h_L00K20G00_Boosted);
  h_L00K00G11->Add(h_L00K00G11_Boosted);
  h_L00K00G40->Add(h_L00K00G40_Boosted);
  h_L00K00G60->Add(h_L00K00G60_Boosted);



  // --- divide aTGC histograms by the SM histogram ------ 
  h_L01K00G00_NoBoost->Divide(hSMNoBoost);
  h_L03K00G00_NoBoost->Divide(hSMNoBoost);
  h_L05K00G00_NoBoost->Divide(hSMNoBoost);
  h_L07K00G00_NoBoost->Divide(hSMNoBoost);
  h_L09K00G00_NoBoost->Divide(hSMNoBoost);
  h_L11K00G00_NoBoost->Divide(hSMNoBoost);
  h_L00K11G00_NoBoost->Divide(hSMNoBoost);
  h_L00K16G00_NoBoost->Divide(hSMNoBoost);
  h_L00K20G00_NoBoost->Divide(hSMNoBoost);
  h_L00K00G11_NoBoost->Divide(hSMNoBoost);
  h_L00K00G40_NoBoost->Divide(hSMNoBoost);
  h_L00K00G60_NoBoost->Divide(hSMNoBoost);

  h_L01K00G00_Boosted->Divide(hSMBoosted);
  h_L03K00G00_Boosted->Divide(hSMBoosted);
  h_L05K00G00_Boosted->Divide(hSMBoosted);
  h_L07K00G00_Boosted->Divide(hSMBoosted);
  h_L09K00G00_Boosted->Divide(hSMBoosted);
  h_L11K00G00_Boosted->Divide(hSMBoosted);
  h_L00K11G00_Boosted->Divide(hSMBoosted);
  h_L00K16G00_Boosted->Divide(hSMBoosted);
  h_L00K20G00_Boosted->Divide(hSMBoosted);
  h_L00K00G11_Boosted->Divide(hSMBoosted);
  h_L00K00G40_Boosted->Divide(hSMBoosted);
  h_L00K00G60_Boosted->Divide(hSMBoosted);

  h_L01K00G00->Divide(hSM);
  h_L03K00G00->Divide(hSM);
  h_L05K00G00->Divide(hSM);
  h_L07K00G00->Divide(hSM);
  h_L09K00G00->Divide(hSM);
  h_L11K00G00->Divide(hSM);
  h_L00K11G00->Divide(hSM);
  h_L00K16G00->Divide(hSM);
  h_L00K20G00->Divide(hSM);
  h_L00K00G11->Divide(hSM);
  h_L00K00G40->Divide(hSM);
  h_L00K00G60->Divide(hSM);


  // --- plot histograms ------ 
  gROOT->ProcessLine(".L ~/tdrstyle.C");
  setTDRStyle();
  tdrStyle->SetErrorX(0.5);
  tdrStyle->SetPadLeftMargin(0.18);
  tdrStyle->SetPadRightMargin(0.08);
  tdrStyle->SetLegendBorderSize(0);
  tdrStyle->SetTitleYOffset(1.3);
  tdrStyle->SetOptStat(0); 
  tdrStyle->SetOptFit(0); 


  // --- Plot non-boosted events ------ 
  TCanvas* can00 = new TCanvas("can00","",500,500);
  h_L01K00G00_NoBoost->GetYaxis()->SetRangeUser(0.3, 80);
  h_L01K00G00_NoBoost->GetXaxis()->SetMoreLogLabels();
  h_L01K00G00_NoBoost->GetXaxis()->SetNoExponent();
  h_L05K00G00_NoBoost->SetLineColor(4);
  h_L05K00G00_NoBoost->SetMarkerColor(4);
  h_L11K00G00_NoBoost->SetLineColor(2);
  h_L11K00G00_NoBoost->SetMarkerColor(2);
  h_L00K11G00_NoBoost->SetMarkerStyle(22);
  h_L00K16G00_NoBoost->SetMarkerStyle(22);
  h_L00K11G00_NoBoost->SetMarkerSize(1.3);
  h_L00K16G00_NoBoost->SetMarkerSize(1.3);
  h_L00K11G00_NoBoost->SetLineStyle(2);
  h_L00K16G00_NoBoost->SetLineStyle(2);
  h_L00K11G00_NoBoost->SetLineColor(4);
  h_L00K11G00_NoBoost->SetMarkerColor(4);
  h_L00K16G00_NoBoost->SetLineColor(2);
  h_L00K16G00_NoBoost->SetMarkerColor(2);
  h_L00K00G40_NoBoost->SetMarkerStyle(21);
  h_L00K00G60_NoBoost->SetMarkerStyle(21);
  h_L00K00G40_NoBoost->SetLineStyle(3);
  h_L00K00G60_NoBoost->SetLineStyle(3);
  h_L00K00G40_NoBoost->SetLineColor(4);
  h_L00K00G40_NoBoost->SetMarkerColor(4);
  h_L00K00G60_NoBoost->SetLineColor(2);
  h_L00K00G60_NoBoost->SetMarkerColor(2);
  h_L01K00G00_NoBoost->Draw();
  h_L05K00G00_NoBoost->Draw("same");
  h_L11K00G00_NoBoost->Draw("same");
  h_L00K11G00_NoBoost->Draw("same");
  h_L00K16G00_NoBoost->Draw("same");
  h_L00K00G40_NoBoost->Draw("same");
  h_L00K00G60_NoBoost->Draw("same");
  TLegend* legend = new TLegend(0.24,0.55,0.64,0.9);
  legend->SetFillColor(0);
  legend->AddEntry(h_L01K00G00_NoBoost, "#lambda = 0.01", "PL");  
  legend->AddEntry(h_L05K00G00_NoBoost, "#lambda = 0.05", "PL");  
  legend->AddEntry(h_L11K00G00_NoBoost, "#lambda = 0.11", "PL");  
  legend->AddEntry(h_L00K11G00_NoBoost, "#Delta#kappa = 0.11", "PL");  
  legend->AddEntry(h_L00K16G00_NoBoost, "#Delta#kappa = 0.16", "PL");  
  legend->AddEntry(h_L00K00G40_NoBoost, "#Deltag_{1} = 0.40", "PL");  
  legend->AddEntry(h_L00K00G60_NoBoost, "#Deltag_{1} = 0.60", "PL");  
  legend->Draw();
  can00->SetLogx(1);
  can00->SetLogy(1);
  can00->SaveAs("Fig_aTGC_NoBoost.png");
  can00->SaveAs("Fig_aTGC_NoBoost.pdf");




  // --- Plot boosted events ------ 
  TCanvas* can11 = new TCanvas("can11","",500,500);
  h_L01K00G00_Boosted->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
  h_L01K00G00_Boosted->GetYaxis()->SetRangeUser(0.3, 500);
  h_L01K00G00_Boosted->GetXaxis()->SetMoreLogLabels();
  h_L01K00G00_Boosted->GetXaxis()->SetNoExponent();
  h_L05K00G00_Boosted->SetLineColor(4);
  h_L05K00G00_Boosted->SetMarkerColor(4);
  h_L11K00G00_Boosted->SetLineColor(2);
  h_L11K00G00_Boosted->SetMarkerColor(2);
  h_L00K11G00_Boosted->SetMarkerStyle(22);
  h_L00K16G00_Boosted->SetMarkerStyle(22);
  h_L00K11G00_Boosted->SetMarkerSize(1.3);
  h_L00K16G00_Boosted->SetMarkerSize(1.3);
  h_L00K11G00_Boosted->SetLineStyle(2);
  h_L00K16G00_Boosted->SetLineStyle(2);
  h_L00K11G00_Boosted->SetLineColor(4);
  h_L00K11G00_Boosted->SetMarkerColor(4);
  h_L00K16G00_Boosted->SetLineColor(2);
  h_L00K16G00_Boosted->SetMarkerColor(2);
  h_L00K00G40_Boosted->SetMarkerStyle(21);
  h_L00K00G60_Boosted->SetMarkerStyle(21);
  h_L00K00G40_Boosted->SetLineStyle(3);
  h_L00K00G60_Boosted->SetLineStyle(3);
  h_L00K00G40_Boosted->SetLineColor(4);
  h_L00K00G40_Boosted->SetMarkerColor(4);
  h_L00K00G60_Boosted->SetLineColor(2);
  h_L00K00G60_Boosted->SetMarkerColor(2);
  h_L01K00G00_Boosted->Draw();
  h_L05K00G00_Boosted->Draw("same");
  h_L11K00G00_Boosted->Draw("same");
  h_L00K11G00_Boosted->Draw("same");
  h_L00K16G00_Boosted->Draw("same");
  h_L00K00G40_Boosted->Draw("same");
  h_L00K00G60_Boosted->Draw("same");
  TLegend* legend = new TLegend(0.24,0.55,0.64,0.9);
  legend->SetFillColor(0);
  legend->AddEntry(h_L01K00G00_Boosted, "#lambda = 0.01", "PL");  
  legend->AddEntry(h_L05K00G00_Boosted, "#lambda = 0.05", "PL");  
  legend->AddEntry(h_L11K00G00_Boosted, "#lambda = 0.11", "PL");  
  legend->AddEntry(h_L00K11G00_Boosted, "#Delta#kappa = 0.11", "PL");  
  legend->AddEntry(h_L00K16G00_Boosted, "#Delta#kappa = 0.16", "PL");  
  legend->AddEntry(h_L00K00G40_Boosted, "#Deltag_{1} = 0.40", "PL");  
  legend->AddEntry(h_L00K00G60_Boosted, "#Deltag_{1} = 0.60", "PL");  
  legend->Draw();
  can11->SetLogx(1);
  can11->SetLogy(1);
  can11->SaveAs("Fig_aTGC_Boosted.png");
  can11->SaveAs("Fig_aTGC_Boosted.pdf");




  ///---- combine the boosted & unboosted events ----
  TCanvas* can22 = new TCanvas("can22","",500,500);
  h_L01K00G00->GetXaxis()->SetTitle("Hadronic W p_{T} (GeV)");
  h_L01K00G00->GetYaxis()->SetRangeUser(0.3, 90);
  h_L01K00G00->GetXaxis()->SetMoreLogLabels();
  h_L01K00G00->GetXaxis()->SetNoExponent();

  h_L05K00G00->SetLineColor(4);
  h_L05K00G00->SetMarkerColor(4);
  h_L11K00G00->SetLineColor(2);
  h_L11K00G00->SetMarkerColor(2);
  h_L00K11G00->SetMarkerStyle(22);
  h_L00K16G00->SetMarkerStyle(22);
  h_L00K11G00->SetMarkerSize(1.3);
  h_L00K16G00->SetMarkerSize(1.3);
  h_L00K11G00->SetLineStyle(2);
  h_L00K16G00->SetLineStyle(2);
  h_L00K11G00->SetLineColor(4);
  h_L00K11G00->SetMarkerColor(4);
  h_L00K16G00->SetLineColor(2);
  h_L00K16G00->SetMarkerColor(2);
  h_L00K00G40->SetMarkerStyle(21);
  h_L00K00G60->SetMarkerStyle(21);
  h_L00K00G40->SetLineStyle(3);
  h_L00K00G60->SetLineStyle(3);
  h_L00K00G40->SetLineColor(4);
  h_L00K00G40->SetMarkerColor(4);
  h_L00K00G60->SetLineColor(2);
  h_L00K00G60->SetMarkerColor(2);


 // --- Fit to a quadratic function ------ 
 // TF1 *func = new TF1("func", "[0]+[1]*x*x", 100., 500.);
  TF1 *func = new TF1("func", "pol2", 100., 500.);
  func->SetLineWidth(3);
  func->SetLineColor(1);
  h_L01K00G00->Fit("func","I","");
  h_L03K00G00->Fit("func","I0","");
  func->SetLineColor(4);
  h_L05K00G00->Fit("func","I","same");
  h_L07K00G00->Fit("func","I0","");
  h_L09K00G00->Fit("func","I0","");
  func->SetLineColor(2);
  h_L11K00G00->Fit("func","I","same");
  func->SetLineStyle(2);
  func->SetLineColor(4);
  h_L00K11G00->Fit("func","I","same");
  func->SetLineColor(2);
  h_L00K16G00->Fit("func","I","same");
  h_L00K20G00->Fit("func","I0","");
  h_L00K00G11->Fit("func","I0",""); //-- looks pretty flat ---
  func->SetLineStyle(3);
  func->SetLineColor(4);
  h_L00K00G40->Fit("func","I","same");
  func->SetLineColor(2);
  h_L00K00G60->Fit("func","I","same");
  TLegend* legend = new TLegend(0.24,0.55,0.64,0.9);
  legend->SetFillColor(0);
  legend->AddEntry(h_L01K00G00, "#lambda = 0.01", "PL");  
  legend->AddEntry(h_L05K00G00, "#lambda = 0.05", "PL");  
  legend->AddEntry(h_L11K00G00, "#lambda = 0.11", "PL");  
  legend->AddEntry(h_L00K11G00, "#Delta#kappa = 0.11", "PL");  
  legend->AddEntry(h_L00K16G00, "#Delta#kappa = 0.16", "PL");  
  legend->AddEntry(h_L00K00G40, "#Deltag_{1} = 0.40", "PL");  
  legend->AddEntry(h_L00K00G60, "#Deltag_{1} = 0.60", "PL");  
  legend->Draw();
  can22->SetLogx(1);
  can22->SetLogy(1);
  can22->SaveAs("Fig_aTGC.png");
  can22->SaveAs("Fig_aTGC.pdf");


  //------- Read C0, C1, C2 for all points -----------
  const int numLambdaBins = 6;
  const int numKappaBins = 3;
  const int numG1Bins = 3;

  TF1 fit_L[numLambdaBins];
  TF1 fit_K[numKappaBins];
  TF1 fit_G1[numG1Bins];
  fit_L[0] = h_L01K00G00->GetFunction("func");
  fit_L[1] = h_L03K00G00->GetFunction("func");
  fit_L[2] = h_L05K00G00->GetFunction("func");
  fit_L[3] = h_L07K00G00->GetFunction("func");
  fit_L[4] = h_L09K00G00->GetFunction("func");
  fit_L[5] = h_L11K00G00->GetFunction("func");
  fit_K[0] = h_L00K11G00->GetFunction("func");
  fit_K[1] = h_L00K16G00->GetFunction("func");
  fit_K[2] = h_L00K20G00->GetFunction("func");
  fit_G1[0] = h_L00K00G11->GetFunction("func");
  fit_G1[1] = h_L00K00G40->GetFunction("func");
  fit_G1[2] = h_L00K00G60->GetFunction("func");

  //------- Lambda values and errors ---------
  float Lambda[] = {0.01, 0.03, 0.05, 0.07, 0.09, 0.11};
  float errLambda[] = {0., 0., 0., 0., 0., 0.};
  float L_C0val[numLambdaBins];
  float L_C0err[numLambdaBins];
  float L_C1val[numLambdaBins];
  float L_C1err[numLambdaBins];
  float L_C2val[numLambdaBins];
  float L_C2err[numLambdaBins];

  for(int i=0; i<numLambdaBins; ++i) {
    L_C0val[i] = fit_L[i]->GetParameter(0);
    L_C0err[i] = fit_L[i]->GetParError(0);
    L_C1val[i] = fit_L[i]->GetParameter(1);
    L_C1err[i] = fit_L[i]->GetParError(1);
    L_C2val[i] = fit_L[i]->GetParameter(2);
    L_C2err[i] = fit_L[i]->GetParError(2);
  }

  //------- Kappa values and errors ---------
  float Kappa[] = {0.11, 0.16, 0.20};
  float errKappa[] = {0., 0., 0.};
  float K_C0val[numKappaBins];
  float K_C0err[numKappaBins];
  float K_C1val[numKappaBins];
  float K_C1err[numKappaBins];
  float K_C2val[numKappaBins];
  float K_C2err[numKappaBins];

  for(int i=0; i<numKappaBins; ++i) {
    K_C0val[i] = fit_K[i]->GetParameter(0);
    K_C0err[i] = fit_K[i]->GetParError(0);
    K_C1val[i] = fit_K[i]->GetParameter(1);
    K_C1err[i] = fit_K[i]->GetParError(1);
    K_C2val[i] = fit_K[i]->GetParameter(2);
    K_C2err[i] = fit_K[i]->GetParError(2);
  }

  //------- G1 values and errors ---------
  float G1[] = {0.11, 0.40, 0.60};
  float errG1[] = {0., 0., 0.};
  float G1_C0val[numG1Bins];
  float G1_C0err[numG1Bins];
  float G1_C1val[numG1Bins];
  float G1_C1err[numG1Bins];
  float G1_C2val[numG1Bins];
  float G1_C2err[numG1Bins];

  for(int i=0; i<numG1Bins; ++i) {
    G1_C0val[i] = fit_G1[i]->GetParameter(0);
    G1_C0err[i] = fit_G1[i]->GetParError(0);
    G1_C1val[i] = fit_G1[i]->GetParameter(1);
    G1_C1err[i] = fit_G1[i]->GetParError(1);
    G1_C2val[i] = fit_G1[i]->GetParameter(2);
    G1_C2err[i] = fit_G1[i]->GetParError(2);
  }

  //------- Graph of Lambda C0, C1, C2 ---------
  cout << "=============================================" << endl;
  cout << "------ Graph of Lambda ------" << endl;
  cout << "=============================================" << endl;

  TGraphErrors* grLC0 = new TGraphErrors( numLambdaBins, Lambda, L_C0val, errLambda, L_C0err);
  TGraphErrors* grLC1 = new TGraphErrors( numLambdaBins, Lambda, L_C1val, errLambda, L_C1err);
  grLC1->SetMarkerStyle(4);
  TGraphErrors* grLC2 = new TGraphErrors( numLambdaBins, Lambda, L_C2val, errLambda, L_C2err);
  grLC2->SetMarkerStyle(22);


  TCanvas* can33 = new TCanvas("can33","",500,500);
  grLC0->GetYaxis()->SetRangeUser(5e-09, 50.);
  grLC0->GetXaxis()->SetTitle("#lambda");
  grLC0->GetYaxis()->SetTitle("C_{i}");
  grLC0->Draw("ap");
  grLC0->Fit("pol2","","");
  grLC1->Draw("p");
  //grLC1->Fit("pol2","","");
  grLC2->Draw("p");
  grLC2->Fit("pol2","","");
  TLegend* legend = new TLegend(0.7,0.16,0.88,0.35);
  legend->SetFillColor(0);
  legend->AddEntry(grLC0, "C0", "P");  
  legend->AddEntry(grLC1, "C1", "P");  
  legend->AddEntry(grLC2, "C2", "P");  
  legend->Draw();
  can33->SetLogy(1);
  can33->SaveAs("Fig_lambda.png");
  can33->SaveAs("Fig_lambda.pdf");


  //------- Graph of Kappa C0, C1, C2 ---------
  cout << "=============================================" << endl;
  cout << "------ Graph of Kappa C0, C1, C2 ------" << endl;
  cout << "=============================================" << endl;

  TGraphErrors* grKC0 = new TGraphErrors( numKappaBins, Kappa, K_C0val, errKappa, K_C0err);
  TGraphErrors* grKC1 = new TGraphErrors( numKappaBins, Kappa, K_C1val, errKappa, K_C1err);
  grKC1->SetMarkerStyle(4);
  TGraphErrors* grKC2 = new TGraphErrors( numKappaBins, Kappa, K_C2val, errKappa, K_C2err);
  grKC2->SetMarkerStyle(22);

  TCanvas* can44 = new TCanvas("can44","",500,500);
  grKC0->GetYaxis()->SetRangeUser(5e-09, 50.);
  grKC0->GetXaxis()->SetTitle("#Delta_{#kappa}");
  grKC0->GetYaxis()->SetTitle("C_{i}'");
  grKC0->Draw("ap");
  grKC0->Fit("pol2","","");
  grKC1->Draw("p");
  grKC1->Fit("pol2","","");
  grKC2->Draw("p");
  grKC2->Fit("pol2","","");
  TLegend* legend = new TLegend(0.7,0.16,0.88,0.35);
  legend->SetFillColor(0);
  legend->AddEntry(grKC0, "C0'", "P");  
  legend->AddEntry(grKC1, "C1'", "P");  
  legend->AddEntry(grKC2, "C2'", "P");  
  legend->Draw();
  can44->SetLogy(1);
  can44->SaveAs("Fig_kappa.png");
  can44->SaveAs("Fig_kappa.pdf");


  //------- Graph of G1 C0, C1, C2 ---------
  cout << "=============================================" << endl;
  cout << "------ Graph of G1 C0, C1, C2 ------" << endl;
  cout << "=============================================" << endl;

  TGraphErrors* grG1C0 = new TGraphErrors( numG1Bins, G1, G1_C0val, errG1, G1_C0err);
  TGraphErrors* grG1C1 = new TGraphErrors( numG1Bins, G1, G1_C1val, errG1, G1_C1err);
  grG1C1->SetMarkerStyle(4);
  TGraphErrors* grG1C2 = new TGraphErrors( numG1Bins, G1, G1_C2val, errG1, G1_C2err);
  grG1C2->SetMarkerStyle(22);

  TCanvas* can55 = new TCanvas("can55","",500,500);
  grG1C0->GetYaxis()->SetRangeUser(5e-09, 50.);
  grG1C0->GetXaxis()->SetTitle("#Delta_{g1}");
  grG1C0->GetYaxis()->SetTitle("C_{i}''");
  grG1C0->Draw("ap");
  grG1C0->Fit("pol2","","");
  grG1C1->Draw("p");
  grG1C1->Fit("pol2","","");
  grG1C2->Draw("p");
  grG1C2->Fit("pol2","","");
  TLegend* legend = new TLegend(0.7,0.16,0.88,0.35);
  legend->SetFillColor(0);
  legend->AddEntry(grG1C0, "C0''", "P");  
  legend->AddEntry(grG1C1, "C1''", "P");  
  legend->AddEntry(grG1C2, "C2''", "P");  
  legend->Draw();
  can55->SetLogy(1);
  can55->SaveAs("Fig_g1.png");
  can55->SaveAs("Fig_g1.pdf");


//   cout << "p0 = " << fit_L01K00G00_C0 << " +- " << fit_L01K00G00_C0err << endl;
//   cout << "p1 = " << fit_L01K00G00_C1 << " +- " << fit_L01K00G00_C0err << endl;
//   cout << "p2 = " << fit_L01K00G00_C2 << " +- " << fit_L01K00G00_C2err << endl;



}
