

void comparePythiaMCFMWW() {

 TFile* pythia_file = new TFile("~/nobackup/WjjTrees/Full2011DataFall11MC/ReducedTree_PAT/RD_mu_WW_CMSSW428.root", "READ");

 TTree* pythia_tree = (TTree*) pythia_file->Get("WJet");
 const char* dijetPt = "sqrt(JetPFCor_Pt[0]*JetPFCor_Pt[0]+JetPFCor_Pt[1]*JetPFCor_Pt[1]+2*JetPFCor_Pt[0]*JetPFCor_Pt[1]*cos(JetPFCor_Phi[0]-JetPFCor_Phi[1]))";

pythia_tree->SetAlias("dijetPt", dijetPt);


const string var3 = "sqrt((px5+px6)*(px5+px6)+(py5+py6)*(py5+py6))";
const string histName3 = "Dijet_pT";
const string title3 = "Dijet W P_{T} [GeV]";



 TFile* mcfm_file = TFile::Open( "dcap://cmsdca1.fnal.gov:24140/pnfs/fnal.gov/usr/cms/WAX/11/store/user/lnujj/MCFM_WW_aTGC/Grid2D_LambdaZ_KappaGamma/LambdaZ_0.0_dKgamma_0.0.root", "read");

 TTree* mcfm_tree = (TTree*)mcfm_file ->Get("h300");

 Int_t bins = 14; 
 Float_t dm_min = 50.; 
 Float_t dm_max = 400.;
 TH1D* pythia_hist_dijetpt = new TH1D("pythia_hist_dijetpt", "", bins, dm_min, dm_max);
 pythia_hist_dijetpt->Sumw2();
 pythia_hist_dijetpt->SetLineWidth(2);
 pythia_tree->Draw( "dijetPt>>pythia_hist_dijetpt", "ggdevt==2||ggdevt==3", "goff");
 pythia_hist_dijetpt->Scale(1./pythia_hist_dijetpt->Integral() );
 pythia_hist_dijetpt->GetXaxis()->SetTitle("Dijet p_{T} (GeV)");
pythia_hist_dijetpt->GetYaxis()->SetTitle("Fraction of events");


 TH1D* pythia_hist_dummy = pythia_hist_dijetpt->Clone("pythia_hist_dummy");
 pythia_hist_dummy->Smooth(5);
pythia_hist_dummy ->SetLineColor(2);
pythia_hist_dummy ->SetMarkerColor(2);
pythia_hist_dummy->SetLineWidth(2);

 TH1D* mcfm_hist_dijetpt = new TH1D("mcfm_hist_dijetpt", "", bins, dm_min, dm_max);
 mcfm_hist_dijetpt->Sumw2();
 mcfm_hist_dijetpt->SetLineColor(2);
 mcfm_hist_dijetpt->SetMarkerColor(2);
 mcfm_hist_dijetpt->SetLineWidth(2);
 mcfm_tree->Draw( TString(var3)+TString(">>mcfm_hist_dijetpt"), "", "goff");
 mcfm_hist_dijetpt->Scale(1./mcfm_hist_dijetpt->Integral() );
 //pythia_hist_dummy->Divide(mcfm_hist_dijetpt);

 gStyle->SetOptStat(0);
 gStyle->SetPadTopMargin(0.05);
 gStyle->SetPadBottomMargin(0.13);
 gStyle->SetPadLeftMargin(0.16);
 //gStyle->SetPadRightMargin(0.28);

 TCanvas* c1 = new TCanvas("can1_dijetpt", "dijetpt", 500, 500);
 pythia_hist_dijetpt->Draw("pe");
 //mcfm_hist_dijetpt->Draw("same chist");
 pythia_hist_dummy->Draw("same chist");
 Double_t x1=0.7, y1=0.49;
  Double_t  x2=x1+0.2, y2=y1+0.42;
 TLegend* l = new TLegend( x1, y1, x2, y2 );
 l->AddEntry(pythia_hist_dijetpt, "Pythia", "lp");
 l->AddEntry(mcfm_hist_dijetpt, "MCFM", "lp");
 l->SetFillColor(0);
 l->Draw();
 c1->Print("Pythia_mcfm_dijetpt.png"); 
  
}
