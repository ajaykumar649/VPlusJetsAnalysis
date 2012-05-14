void plotATGCHistos() {

  TFile* f[6];
  string fnames[6] = { "Histograms_ratio_aTGC_LambdaZ-0.6.root",
		       "Histograms_ratio_aTGC_LambdaZ-0.4.root",
		       "Histograms_ratio_aTGC_LambdaZ-0.2.root",
		       "Histograms_ratio_aTGC_LambdaZ0.2.root",
		       "Histograms_ratio_aTGC_LambdaZ0.4.root",
		       "Histograms_ratio_aTGC_LambdaZ0.6.root"};

  string hnames[7] = {"HadronicWpT-0.6_ratio",
		     "HadronicWpT-0.4_ratio",
		     "HadronicWpT-0.2_ratio",
		     "HadronicWpT0.0_ratio",
		     "HadronicWpT0.2_ratio",
		     "HadronicWpT0.4_ratio",
		     "HadronicWpT0.6_ratio"};

 TH1D* h1[7];
 TH1D* h2[7];
 TH1D* h3[7];
 TH1D* h4[7];
 TH1D* h5[7];
 TH1D* h6[7];

 for (int i=0; i<6; ++i) {
   f[i] = TFile::Open(fnames[i].c_str());
 }

 for (int i=0; i<7; ++i) {
   h1[i] = (TH1D*) f[0]->Get(hnames[i].c_str());
   h2[i] = (TH1D*) f[1]->Get(hnames[i].c_str());
   h3[i] = (TH1D*) f[2]->Get(hnames[i].c_str());
   h4[i] = (TH1D*) f[3]->Get(hnames[i].c_str());
   h5[i] = (TH1D*) f[4]->Get(hnames[i].c_str());
   h6[i] = (TH1D*) f[5]->Get(hnames[i].c_str());
 }


 gStyle->SetOptStat(0);
 TCanvas* c1 = new TCanvas("dijetPt1", "-0.6", 10,10, 500, 500);
 h1[0]->Draw("e");
 for (int i=1; i<7; ++i) h1[i]->Draw("esame");
 TLegend* lg = GetLegend(h1, -0.6);
 lg->Draw();
 c1->SaveAs("atgcRatio_m06.png");



 TCanvas* c2 = new TCanvas("dijetPt2", "-0.4", 10,10, 500, 500);
 h2[0]->Draw("e");
 for (int i=1; i<7; ++i) h2[i]->Draw("esame");
 TLegend* lg = GetLegend(h2, -0.4);
 lg->Draw();
 c2->SaveAs("atgcRatio_m04.png");



 TCanvas* c3 = new TCanvas("dijetPt3", "-0.2", 10,10, 500, 500);
 h3[0]->Draw("e");
 for (int i=1; i<7; ++i) h3[i]->Draw("esame");
 TLegend* lg = GetLegend(h3, -0.2);
 lg->Draw();
 c3->SaveAs("atgcRatio_m02.png");


 TCanvas* c4 = new TCanvas("dijetPt4", "0.2", 10,10, 500, 500);
 h4[0]->Draw("e");
 for (int i=1; i<7; ++i) h4[i]->Draw("esame");
 TLegend* lg = GetLegend(h4, 0.2);
 lg->Draw();
 c4->SaveAs("atgcRatio_02.png");

 TCanvas* c5 = new TCanvas("dijetPt5", "0.4", 10,10, 500, 500);
 h5[0]->Draw("e");
 for (int i=1; i<7; ++i) h5[i]->Draw("esame");
 TLegend* lg = GetLegend(h5, 0.4);
 lg->Draw();
 c5->SaveAs("atgcRatio_04.png");

 TCanvas* c6 = new TCanvas("dijetPt6", "0.6", 10,10, 500, 500);
 h6[0]->Draw("e");
 for (int i=1; i<7; ++i) h6[i]->Draw("esame");
 TLegend* lg = GetLegend(h6, 0.6);
 lg->Draw();
 c6->SaveAs("atgcRatio_06.png");

}



TLegend* GetLegend(TH1* h[7], float lambdaZ)
{
  float  legX0=0.18, legX1=0.45, legY0=0.52, legY1=0.88;
  TLegend * Leg = new TLegend( legX0, legY0, legX1, legY1);
  Leg->SetFillColor(0);
  Leg->SetFillStyle(0);
  Leg->SetTextSize(0.05);
  h[0]->GetYaxis()->SetTitle("#sigma/#sigma_{SM}");
  h[0]->GetYaxis()->SetTitleOffset(1.);
  h[0]->GetXaxis()->SetTitle("Dijet p_{T} (GeV)");
  char temp[50];
  sprintf(temp, "#Lambda_{Z} = %.1f", lambdaZ);
  Leg->SetHeader(temp);
  Leg->AddEntry(h[0],  "#Delta#kappa_{#gamma} = -0.6",  "PL");
  Leg->AddEntry(h[1],  "#Delta#kappa_{#gamma} = -0.4",  "PL");
  Leg->AddEntry(h[2],  "#Delta#kappa_{#gamma} = -0.2",  "PL");
  Leg->AddEntry(h[3],  "#Delta#kappa_{#gamma} = 0.0",  "PL");
  Leg->AddEntry(h[4],  "#Delta#kappa_{#gamma} = 0.2",  "PL");
  Leg->AddEntry(h[5],  "#Delta#kappa_{#gamma} = 0.4",  "PL");
  Leg->AddEntry(h[6],  "#Delta#kappa_{#gamma} = 0.6",  "PL");

  Leg->SetFillColor(0);

  return Leg;
}
