void makeATGCGraph2() {

  float x7[7]= {-0.6, -0.4, -0.2, 0.0, 0.2, 0.4, 0.6};
  float errx7[7] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  float Lambda_Z_m06_val[7] = {2009.016, 1960.101, 1928.489, 1915.580, 1920.435, 1943.721, 1986.124};
  float Lambda_Z_m06_err[7] = { 1.385, 1.351, 1.372, 1.355, 1.343, 1.350, 1.372 };
  GetCrossSectionChange(Lambda_Z_m06_val, Lambda_Z_m06_err);

  float Lambda_Z_m04_val[7] = {1417.959, 1369.149, 1340.213, 1326.794, 1331.933, 1354.890, 1394.851};
  float Lambda_Z_m04_err[7] = {1.024, 0.946, 0.991, 0.958, 1.004, 0.968, 0.972};

  GetCrossSectionChange(Lambda_Z_m04_val, Lambda_Z_m04_err);

  float Lambda_Z_m02_val[7] = {1053.221, 1004.695, 974.390, 960.664, 965.478, 987.523, 1026.728 };
  float Lambda_Z_m02_err[7] = {0.733, 0.737, 0.729, 0.725, 0.733, 0.774, 0.724};
  GetCrossSectionChange(Lambda_Z_m02_val, Lambda_Z_m02_err);

  float Lambda_Z_m0_val[7] = {952.089, 901.500, 870.836, 856.199, 861.957, 883.845, 923.050 };
  float Lambda_Z_m0_err[7] = {0.800, 0.856, 1.296, 1.045, 1.225, 0.856, 0.820 };
  GetCrossSectionChange(Lambda_Z_m0_val, Lambda_Z_m0_err);

  float Lambda_Z_02_val[7] = {1111.790, 1063.428, 1030.739, 1016.994, 1020.137, 1041.589, 1080.398};
  float Lambda_Z_02_err[7] = {0.791, 0.817, 0.773, 0.757, 0.798, 0.742, 0.796};
  GetCrossSectionChange(Lambda_Z_02_val, Lambda_Z_02_err);

  float Lambda_Z_04_val[7] = {1535.021, 1484.369, 1453.069, 1439.129, 1442.755, 1462.876, 1502.613};
  float Lambda_Z_04_err[7] = {1.040, 1.037, 1.009, 1.028, 1.035, 1.006, 1.017};
  GetCrossSectionChange(Lambda_Z_04_val, Lambda_Z_04_err);

  float Lambda_Z_06_val[7] = {2172.604, 2122.149, 2088.321, 2072.907, 2074.902, 2097.831, 2138.094};
  float Lambda_Z_06_err[7] = {1.492, 1.432, 1.451, 1.443, 1.448, 1.436, 1.431};
  GetCrossSectionChange(Lambda_Z_06_val, Lambda_Z_06_err);




  TGraphErrors* Lambda_Z_m06 = new TGraphErrors(7, x7, Lambda_Z_m06_val, 
						 errx7, Lambda_Z_m06_err);
  Lambda_Z_m06->SetMarkerStyle(4);
  Lambda_Z_m06->SetLineStyle(2);
  Lambda_Z_m06->SetLineWidth(2);

  TGraphErrors* Lambda_Z_m04 = new TGraphErrors(7, x7, Lambda_Z_m04_val, 
						 errx7, Lambda_Z_m04_err);
  Lambda_Z_m04->SetMarkerColor(2);
  Lambda_Z_m04->SetLineColor(2);
  Lambda_Z_m04->SetMarkerStyle(4);
  Lambda_Z_m04->SetLineStyle(2);
  Lambda_Z_m04->SetLineWidth(2);

  TGraphErrors* Lambda_Z_m02 = new TGraphErrors(7, x7, Lambda_Z_m02_val, 
						 errx7, Lambda_Z_m02_err);
  Lambda_Z_m02->SetMarkerColor(4);
  Lambda_Z_m02->SetLineColor(4);
  Lambda_Z_m02->SetMarkerStyle(4);
  Lambda_Z_m02->SetLineStyle(2);
  Lambda_Z_m02->SetLineWidth(2);

  TGraphErrors* Lambda_Z_m0 = new TGraphErrors(7, x7, Lambda_Z_m0_val, 
						 errx7, Lambda_Z_m0_err);
  Lambda_Z_m0->SetMarkerColor(3);
  Lambda_Z_m0->SetLineColor(3);
  Lambda_Z_m0->SetLineWidth(2);


  TGraphErrors* Lambda_Z_02 = new TGraphErrors(7, x7, Lambda_Z_02_val, 
						 errx7, Lambda_Z_02_err);
  Lambda_Z_02->SetMarkerColor(4);
  Lambda_Z_02->SetLineColor(4);
  Lambda_Z_02->SetLineWidth(2);


  TGraphErrors* Lambda_Z_04 = new TGraphErrors(7, x7, Lambda_Z_04_val, 
						 errx7, Lambda_Z_04_err);
  Lambda_Z_04->SetMarkerColor(2);
  Lambda_Z_04->SetLineColor(2);
  Lambda_Z_04->SetLineWidth(2);


  TGraphErrors* Lambda_Z_06 = new TGraphErrors(7, x7, Lambda_Z_06_val, 
						 errx7, Lambda_Z_06_err);
  Lambda_Z_06->GetXaxis()->SetTitle("#Delta#kappa_{#gamma}");
  Lambda_Z_06->GetYaxis()->SetTitle("Cross section ratio (#sigma/#sigma_{SM})");
  Lambda_Z_06->GetYaxis()->SetRangeUser(0., 3.7);
  Lambda_Z_06->SetLineWidth(2);




  gStyle->SetPadLeftMargin(0.18);
  /////////////////////////////////////////////////////////
  TCanvas *can_atgc_xsec  = new TCanvas("can_atgc_xsec",
					    "",500, 500);
  Lambda_Z_06->Draw("apl");
  Lambda_Z_04->Draw("plsame");
  Lambda_Z_02->Draw("plsame");
  Lambda_Z_m0->Draw("plsame");
  Lambda_Z_m02->Draw("plsame");
  Lambda_Z_m04->Draw("plsame");
  Lambda_Z_m06->Draw("plsame");
  TLegend* legend2 = new TLegend(0.35,0.77,0.6,0.92);
  legend2->AddEntry( Lambda_Z_06, "#lambda_{Z} = 0.6", "lpe");  
  legend2->AddEntry( Lambda_Z_04, "#lambda_{Z} = 0.4", "lpe");  
  legend2->AddEntry( Lambda_Z_02, "#lambda_{Z} = 0.2", "lpe");  
  legend2->AddEntry( Lambda_Z_m0, "#lambda_{Z} = 0.0", "lpe");  
  legend2->SetFillColor(0);
  legend2->Draw();
  TLegend* legend3 = new TLegend(0.6,0.77,0.8,0.92);
  legend3->AddEntry( Lambda_Z_m06, "#lambda_{Z} = -0.6", "lp");  
  legend3->AddEntry( Lambda_Z_m04, "#lambda_{Z} = -0.4", "lp");  
  legend3->AddEntry( Lambda_Z_m02, "#lambda_{Z} = -0.2", "lp");  
  legend3->SetFillColor(0);
  legend3->Draw();
  cmsPrelim();
  can_atgc_xsec->SaveAs("atgc_xsec2.png");
}





////CMS Preliminary label and lumu -- upper left corner
void cmsPrelim()
{
   TLatex latex;
   latex.SetNDC();
   latex.SetTextSize(0.04);

   latex.SetTextAlign(11); // align left
   latex.DrawLatex(0.65,0.96,"CMS preliminary");
}





void GetCrossSectionChange(float y[], float yerr[]) {
  const float xsec0 = 871.;  // +- 1.045 fb
  int N = 7;

  for (int i=0; i< N; ++i) {
    y[i] = y[i]/xsec0;
    yerr[i] /= xsec0;
  }

}
