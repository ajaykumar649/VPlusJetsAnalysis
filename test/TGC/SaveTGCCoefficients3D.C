void SaveTGCCoefficients3D(){
   
   TFile fout( "ATGC_shape_coefficients.root", "recreate");

   ////// ---- first process lambda:dkappa combination --------
   TFile fin("root_kappa-lambda.root");
   TTree* tr = (TTree*) fin.Get("tree"); 
   TProfile2D* p0_lambda_dkg = new TProfile2D("p0_lambda_dkg","", 61, -0.0305, 0.0305, 31, -0.155, 0.155);
   SetTitles(p0_lambda_dkg, "lambda", "dkg", "p0");
   TProfile2D* p1_lambda_dkg = (TProfile2D*) p0_lambda_dkg->Clone("p1_lambda_dkg");
   TProfile2D* p2_lambda_dkg = (TProfile2D*) p0_lambda_dkg->Clone("p2_lambda_dkg");
   TProfile2D* p3_lambda_dkg = (TProfile2D*) p0_lambda_dkg->Clone("p3_lambda_dkg");
   TProfile2D* p4_lambda_dkg = (TProfile2D*) p0_lambda_dkg->Clone("p4_lambda_dkg");
   TProfile2D* p5_lambda_dkg = (TProfile2D*) p0_lambda_dkg->Clone("p5_lambda_dkg");
   TProfile2D* p6_lambda_dkg = (TProfile2D*) p0_lambda_dkg->Clone("p6_lambda_dkg");

//    TProfile2D p1_lambda_dkg("p1_lambda_dkg","", 55, -0.55, 0.55, 55, -0.55, 0.55, 100, -0.003, 0.0003);
//    SetTitles(p1_lambda_dkg, "lambda", "dkg", "p1");
//    TProfile2D p2_lambda_dkg("p2_lambda_dkg","", 55, -0.55, 0.55, 55, -0.55, 0.55, 100, -3.0e-06, 0.2e-03);
//    SetTitles(p2_lambda_dkg, "lambda", "dkg", "p2");
//    TProfile2D p3_lambda_dkg("p3_lambda_dkg","", 55, -0.55, 0.55, 55, -0.55, 0.55, 100, -2.0e-06, 0.1e-06);
//    SetTitles(p3_lambda_dkg, "lambda", "dkg", "p3");
//    TProfile2D p4_lambda_dkg("p4_lambda_dkg","", 55, -0.55, 0.55, 55, -0.55, 0.55, 100, -1.0e-09, 25.0e-09);
//    SetTitles(p4_lambda_dkg, "lambda", "dkg", "p4");
//    TProfile2D p5_lambda_dkg("p5_lambda_dkg","", 55, -0.55, 0.55, 55, -0.55, 0.55, 100, -26.0e-12, 1.0e-12);
//    SetTitles(p5_lambda_dkg, "lambda", "dkg", "p5");
//    TProfile2D p6_lambda_dkg("p6_lambda_dkg","", 55, -0.55, 0.55, 55, -0.55, 0.55, 100, -4.0e-15, 13.0e-15);
//    SetTitles(p6_lambda_dkg, "lambda", "dkg", "p6");

   tr->Draw("p0:dkappa:lambda>>p0_lambda_dkg","","goff");
   tr->Draw("p1:dkappa:lambda>>p1_lambda_dkg","","goff");
   tr->Draw("p2:dkappa:lambda>>p2_lambda_dkg","","goff");
   tr->Draw("p3:dkappa:lambda>>p3_lambda_dkg","","goff");
   tr->Draw("p4:dkappa:lambda>>p4_lambda_dkg","","goff");
   tr->Draw("p5:dkappa:lambda>>p5_lambda_dkg","","goff");
   tr->Draw("p6:dkappa:lambda>>p6_lambda_dkg","","goff");



   ////// ---- second process lambda:dg1 combination --------
   TFile fin2("root_lambda-g1.root");
   TTree* tr2 = (TTree*) fin2.Get("tree"); 
   TProfile2D* p0_lambda_dg1 = new TProfile2D("p0_lambda_dg1","", 61, -0.0305, 0.0305, 101, -0.101, 0.101);
   SetTitles(p0_lambda_dg1, "lambda", "dg1", "p0");
   TProfile2D* p1_lambda_dg1 = (TProfile2D*) p0_lambda_dg1->Clone("p1_lambda_dg1");
   TProfile2D* p2_lambda_dg1 = (TProfile2D*) p0_lambda_dg1->Clone("p2_lambda_dg1");
   TProfile2D* p3_lambda_dg1 = (TProfile2D*) p0_lambda_dg1->Clone("p3_lambda_dg1");
   TProfile2D* p4_lambda_dg1 = (TProfile2D*) p0_lambda_dg1->Clone("p4_lambda_dg1");
   TProfile2D* p5_lambda_dg1 = (TProfile2D*) p0_lambda_dg1->Clone("p5_lambda_dg1");
   TProfile2D* p6_lambda_dg1 = (TProfile2D*) p0_lambda_dg1->Clone("p6_lambda_dg1");

//    TProfile2D p1_lambda_dg1("p1_lambda_dg1","", 55, -0.55, 0.55, 55, -0.55, 0.55, 100, -0.005, 0.0013);
//    SetTitles(p1_lambda_dg1, "lambda", "dg1", "p1");
//    TProfile2D p2_lambda_dg1("p2_lambda_dg1","", 55, -0.55, 0.55, 55, -0.55, 0.55, 100, -0.02e-03, 0.35e-03);
//    SetTitles(p2_lambda_dg1, "lambda", "dg1", "p2");
//    TProfile2D p3_lambda_dg1("p3_lambda_dg1","", 55, -0.55, 0.55, 55, -0.55, 0.55, 100, -2.5e-06, 0.7e-06);
//    SetTitles(p3_lambda_dg1, "lambda", "dg1", "p3");
//    TProfile2D p4_lambda_dg1("p4_lambda_dg1","", 55, -0.55, 0.55, 55, -0.55, 0.55, 100, -1.0e-09, 36.0e-09);
//    SetTitles(p4_lambda_dg1, "lambda", "dg1", "p4");
//    TProfile2D p5_lambda_dg1("p5_lambda_dg1","", 55, -0.55, 0.55, 55, -0.55, 0.55, 100, -70.0e-12, 2.0e-12);
//    SetTitles(p5_lambda_dg1, "lambda", "dg1", "p5");
//    TProfile2D p6_lambda_dg1("p6_lambda_dg1","", 55, -0.55, 0.55, 55, -0.55, 0.55, 100, -30.0e-15, 70.0e-15);
//    SetTitles(p6_lambda_dg1, "lambda", "dg1", "p6");

   tr2->Draw("p0:dg1:lambda>>p0_lambda_dg1","","goff");
   tr2->Draw("p1:dg1:lambda>>p1_lambda_dg1","","goff");
   tr2->Draw("p2:dg1:lambda>>p2_lambda_dg1","","goff");
   tr2->Draw("p3:dg1:lambda>>p3_lambda_dg1","","goff");
   tr2->Draw("p4:dg1:lambda>>p4_lambda_dg1","","goff");
   tr2->Draw("p5:dg1:lambda>>p5_lambda_dg1","","goff");
   tr2->Draw("p6:dg1:lambda>>p6_lambda_dg1","","goff");


   ////// ---- third process dkg:dg1 combination --------
   TFile fin3("root_kappa-g1.root");
   TTree* tr3 = (TTree*) fin3.Get("tree"); 
   TProfile2D* p0_dkg_dg1 = new TProfile2D("p0_dkg_dg1","", 31, -0.155, 0.155, 101, -0.101, 0.101);
   SetTitles(p0_dkg_dg1, "dkg", "dg1", "p0");
   TProfile2D* p1_dkg_dg1 = (TProfile2D*) p0_dkg_dg1->Clone("p1_dkg_dg1");
   TProfile2D* p2_dkg_dg1 = (TProfile2D*) p0_dkg_dg1->Clone("p2_dkg_dg1");
   TProfile2D* p3_dkg_dg1 = (TProfile2D*) p0_dkg_dg1->Clone("p3_dkg_dg1");
   TProfile2D* p4_dkg_dg1 = (TProfile2D*) p0_dkg_dg1->Clone("p4_dkg_dg1");
   TProfile2D* p5_dkg_dg1 = (TProfile2D*) p0_dkg_dg1->Clone("p5_dkg_dg1");
   TProfile2D* p6_dkg_dg1 = (TProfile2D*) p0_dkg_dg1->Clone("p6_dkg_dg1");

   tr3->Draw("p0:dg1:dkappa>>p0_dkg_dg1","","goff");
   tr3->Draw("p1:dg1:dkappa>>p1_dkg_dg1","","goff");
   tr3->Draw("p2:dg1:dkappa>>p2_dkg_dg1","","goff");
   tr3->Draw("p3:dg1:dkappa>>p3_dkg_dg1","","goff");
   tr3->Draw("p4:dg1:dkappa>>p4_dkg_dg1","","goff");
   tr3->Draw("p5:dg1:dkappa>>p5_dkg_dg1","","goff");
   tr3->Draw("p6:dg1:dkappa>>p6_dkg_dg1","","goff");



   /////----- Let's save all histograms in the output file ----
   fout.cd();
   p0_lambda_dkg->Write();
   p1_lambda_dkg->Write();
   p2_lambda_dkg->Write();
   p3_lambda_dkg->Write();
   p4_lambda_dkg->Write();
   p5_lambda_dkg->Write();
   p6_lambda_dkg->Write();

   p0_lambda_dg1->Write();
   p1_lambda_dg1->Write();
   p2_lambda_dg1->Write();
   p3_lambda_dg1->Write();
   p4_lambda_dg1->Write();
   p5_lambda_dg1->Write();
   p6_lambda_dg1->Write();

   p0_dkg_dg1->Write();
   p1_dkg_dg1->Write();
   p2_dkg_dg1->Write();
   p3_dkg_dg1->Write();
   p4_dkg_dg1->Write();
   p5_dkg_dg1->Write();
   p6_dkg_dg1->Write();

   fout.Close();
}

void SetTitles(TProfile2D* hist, char* xtit, char* ytit, char* ztit) {
   hist->GetXaxis()->SetTitle(xtit);
   hist->GetYaxis()->SetTitle(ytit);
   hist->GetZaxis()->SetTitle(ztit);
}
