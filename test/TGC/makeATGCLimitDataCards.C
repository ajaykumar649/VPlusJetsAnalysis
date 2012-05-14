

const double intLUMI = 1.;
const double WJets_scale   = 31500.* intLUMI/80754279;
const double W4Jets_scale  = 172.6 * intLUMI/5000700;
const double WW_scale      = 43.   * intLUMI/4225913;
const double WZ_scale      = 18.   * intLUMI/4265239;

const double QCD_scale     = 296600000 *	0.0002855 * intLUMI/25080241 ;
const double ZJets_scale   = 3048  * intLUMI/34689542;
const double ttbar_scale   = 157.5 * intLUMI/3573410;
const double SToppS_scale  = 1.44  * intLUMI/117647;
const double SToppT_scale  = 22.65 * intLUMI/1899460;
const double SToppTW_scale = 7.87  * intLUMI/322638;
const double STopS_scale   = 3.19  * intLUMI/259572;
const double STopT_scale   = 41.92 * intLUMI/3891502;
const double STopTW_scale  = 7.87  * intLUMI/812544;

const string variable = "sqrt((px5+px6)*(px5+px6)+(py5+py6)*(py5+py6))";
const string plotname = "HadronicWpT";
const string axis_label = "p_{T}^{jj} [GeV]";
const Int_t bins = 14; 
const Float_t dm_min = 50.; 
const Float_t dm_max = 400.;

// const Int_t bins = 8; 
// const Float_t dm_min = 200.; 
// const Float_t dm_max = 400.;

bool domu=true;


////////// ALL input files ///////////
TFile* fin2;
TFile* wwShape_file;
TFile* wzShape_file;
TFile* wjetsShape_file;
TFile* ttbar_file;
TFile* qcd_file1;
TFile* zjets_file;
TFile* stops_file;
TFile* stopt_file;
TFile* stoptW_file;
TFile* stopps_file;
TFile* stoppt_file;
TFile* stopptW_file;
TFile* sigLambdaZ;
TFile* outputForLimit;

////////// ALL input trees ///////////
TTree* treedata;
TTree* treeww;
TTree* treewz;
TTree* treewj;
TTree* treettb;
TTree* treeqcd;
TTree* treezj;
TTree* treests;
TTree* treestt;
TTree* treestw;
TTree* tree64;
TTree* tree65;
TTree* tree66;



////////// ALL histograms ///////////
TH1* th1data;
TH1* th1ww;
TH1* th1wz;
TH1* th1wjets;
TH1* th1Top;
TH1* th1qcd;
TH1* th1zjets;
TH1* th1stops;
TH1* th1stopt;
TH1* th1stoptw;
TH1* th1stopps;
TH1* th1stoppt;
TH1* th1stopptw;
TH1D *th1tot;
TH1D* th1totClone;
TH1* th1totempty;
TH1D* th1emptyclone;
TH1F* hhratio;
TH1* signalForDisplay;
TH1* signalRatioForDisplay;



//////---------- channel: 0==muon no btag, 1== electron no btag
/////                     2==muon  btag,   3== electron btag
void makeATGCLimitDataCards(int channel=0) {

  domu = true;
  if(channel==1 || channel==3) domu = false;

 
  TString outfile = (domu?TString("mu_"):TString("el_"))+ 
    (channel<2?TString("noBtag"):TString("btag"));
  outputForLimit = TFile::Open(outfile+".root", "recreate");


  TString lepton_cut = "(W_mt>50.) && (event_met_pfmet >30) && (W_electron_pt>35.) && ((W_electron_trackiso+W_electron_hcaliso+W_electron_ecaliso-event_RhoForLeptonIsolation*3.141592653589*0.09)/W_electron_pt<0.05) && ( (abs(W_electron_eta)<1.5 && abs(W_electron_deltaphi_in)<0.03 && abs(W_electron_deltaeta_in)<0.004) || (abs(W_electron_eta)>1.5 && abs(W_electron_deltaphi_in)<0.02 && abs(W_electron_deltaeta_in)<0.005))";

  if(domu) lepton_cut = "(W_mt>30.) && (event_met_pfmet >25) && (W_muon_pt>25.) && (abs(W_muon_eta)<2.1) && (abs(W_muon_d0bsp)<0.02) && ((W_muon_trackiso+W_muon_hcaliso+W_muon_ecaliso-event_RhoForLeptonIsolation*3.141592653589*0.09)/W_muon_pt<0.1)";

  TString jet_cut = "&& (JetPFCor_Pt[1]>35.) && (abs(JetPFCor_Eta[0]-JetPFCor_Eta[1])<1.5) && (abs(JetPFCor_dphiMET[0])>0.4) && (JetPFCor_Pt[2]<30) && (Mass2j_PFCor>75. && Mass2j_PFCor<95.)";
  TString bTagCut = "&& (JetPFCor_bDiscriminator[0]<1.74) && (JetPFCor_bDiscriminator[1]<1.74)";
  if(channel>1) 
    bTagCut = "&& ((JetPFCor_bDiscriminator[0]>1.74) || (JetPFCor_bDiscriminator[1]>1.74))";

  TCut the_cut( TString("effwt*(") + lepton_cut + jet_cut + bTagCut + TString(")") );


  InstantiateTrees();

  th1data  = new TH1D("th1data",  "th1data",  bins, dm_min, dm_max);
  th1data->Sumw2();
  th1data->SetMarkerStyle(20);
  th1data->SetMarkerSize(1.25);
  th1data->SetLineWidth(2);
  th1data->SetMinimum(0.0);
  treedata->Draw("dijetPt>>th1data", the_cut, "goff");

  // ------- Get WW/WZ ------- 
    th1ww = new TH1D("th1ww", "th1ww", bins, dm_min, dm_max);
    th1wz = new TH1D("th1wz", "th1wz", bins, dm_min, dm_max);
    th1ww->Sumw2();
    th1wz->Sumw2();
    treeww->Draw("dijetPt>>th1ww", the_cut, "goff");
    treewz->Draw("dijetPt>>th1wz", the_cut, "goff");


    // ------- Get WJets ------- 
    th1wjets  = new TH1D("th1wjets",  "th1wjets", bins, dm_min, dm_max);
    th1wjets->Sumw2();
    treewj->Draw("dijetPt>>th1wjets", the_cut, "goff");


    // ------- Get ttbar ------- 
    th1Top = new TH1D("th1Top", "th1Top", bins, dm_min, dm_max);
    th1Top->Sumw2();
    treettb->Draw("dijetPt>>th1Top", the_cut, "goff");

    // ------- Get QCD ------- 
    th1qcd = new TH1D("th1qcd", "th1qcd", bins, dm_min, dm_max);
    th1qcd->Sumw2();
    treeqcd->Draw("dijetPt>>th1qcd", the_cut, "goff");

    // ------- Get Z+Jets ------- 
    th1zjets = new TH1D("th1zjets", "th1zjets", bins, dm_min, dm_max);
    th1zjets->Sumw2();
    treezj->Draw("dijetPt>>th1zjets", the_cut, "goff");


    // ------- Get Single top ------- 
    th1stops = new TH1D("th1stops", "th1stops", bins, dm_min, dm_max);
    th1stopt = new TH1D("th1stopt", "th1stopt", bins, dm_min, dm_max);
    th1stoptw = new TH1D("th1stoptw", "th1stoptw", bins, dm_min, dm_max);
    th1stops->Sumw2();
    th1stopt->Sumw2();
    th1stoptw->Sumw2();

    treests->Draw("dijetPt>>th1stops", the_cut, "goff");
    treestt->Draw("dijetPt>>th1stopt", the_cut, "goff");
    treestw->Draw("dijetPt>>th1stoptw", the_cut, "goff");
 
    th1stopps = new TH1D("th1stopps", "th1stopps", bins, dm_min, dm_max);
    th1stoppt = new TH1D("th1stoppt", "th1stoppt", bins, dm_min, dm_max);
    th1stopptw = new TH1D("th1stopptw", "th1stopptw", bins, dm_min, dm_max);
    th1stopps->Sumw2();
    th1stoppt->Sumw2();
    th1stopptw->Sumw2();
    tree64->Draw("dijetPt>>th1stopps", the_cut, "goff");
    tree65->Draw("dijetPt>>th1stoppt", the_cut, "goff");
    tree66->Draw("dijetPt>>th1stopptw", the_cut, "goff");


    // Scale the histos
    ScaleHistos();
    SetupEmptyHistogram();

    //Get signal histogram
    signalForDisplay = GetSignalHistogram(0.4, 0.0, "signalForDisplay");

    // ratio histogram for aTGC display
    signalRatioForDisplay = 
      (TH1D*) signalForDisplay->Clone("signaRatiolForDisplay");
    signalRatioForDisplay->Divide(th1tot);
    for(int j=0; j<signalRatioForDisplay->GetNbinsX(); ++j) {
      double entry = signalRatioForDisplay->GetBinContent(j);
      signalRatioForDisplay->SetBinContent(j, 1.+entry);
    }
    signalRatioForDisplay->Smooth(10);


    // Compose the stack
    THStack* hs = new THStack("hs","MC contribution");
    hs->Add(th1zjets);
    hs->Add(th1qcd);
    hs->Add(th1Top);
    hs->Add(th1wjets);
    hs->Add(th1ww);
    hs->Add(signalForDisplay);

    // ------- Setup the canvas ------- 
    gStyle->SetOptStat(0);
    // gStyle->SetPadTopMargin(0.1);

    TCanvas* c1 = new TCanvas("dijetPt", "dijetPt", 10,10, 500, 500);
    TPad *d1, *d2;
    c1->Divide(1,2,0,0);
    d1 = (TPad*)c1->GetPad(1);
    d1->SetPad(0.01,0.30,0.95,0.99);
    d2 = (TPad*)c1->GetPad(2);
    d2->SetPad(0.01,0.02,0.95,0.30);

    d1->cd();
    gPad->SetBottomMargin(0.0);
    gPad->SetTopMargin(0.1);
    gPad->SetRightMargin(0.05);
    gPad->SetLeftMargin(0.14);


    // Draw it all
    double ymax= 500000.;
    th1totempty->GetYaxis()->SetRangeUser(0.12, ymax);
    th1data->GetYaxis()->SetRangeUser(0.12, ymax);
    th1totempty->Draw();
    th1data->Draw("esame");
    hs->Draw("samehist");
    //th1tot->Draw("e3same");
    th1data->Draw("esame");
    cmspre(); 
    // Set up the legend
    TLegend* Leg = GetLegend();   
    Leg->Draw();  
    d1->SetLogy();
    gPad->RedrawAxis();


    d2->cd();
    gPad->SetLeftMargin(0.14);
    gPad->SetTopMargin(0);
    gPad->SetRightMargin(0.05);
    gPad->SetFrameBorderSize(0);
    gPad->SetBottomMargin(0.3);
    gPad->SetTickx();

    th1emptyclone->Draw();
    hhratio->Draw("esame");
    signalRatioForDisplay->Draw("hist same");
    TLine *line; line = new TLine(dm_min,1.0,dm_max,1.0);
    line->SetLineStyle(1);
    line->SetLineWidth(1);
    line->SetLineColor(1);
    line->Draw();
    d2->SetLogy();
    d2->SetGridy();
    c1->Print(TString("OutDir/")+outfile+TString("_dijetPt.png"));
    //gPad->WaitPrimitive();
    c1->Modified();
    c1->Update();
    c1->SaveAs(TString("OutDir/")+outfile+TString("_dijetPt.pdf")); 

   
    ///// -------------------------------//////
    outputForLimit->cd();
    th1data->SetName("data_obs");
    th1data->Write("data_obs");
    th1tot->SetName("background");
    th1tot->Write("background");
    char mysighistname[100];
    for (float m=-0.4; m<0.41; m += 0.04) {
      for (float n=0.6; n>-0.1; n -= 0.2) {
	sprintf(mysighistname, "signal_lambdaZ_%0.2f_deltaKappaGamma_%0.1f", m, n);
	TH1D* stackhist = GetSignalHistogram(m, n, mysighistname);
	outputForLimit->cd();
	stackhist->Write(); 
	delete stackhist;
      }
    }

    /// now fill histograms for lambdaZ = +- 0.6
    for (float n=0.6; n>-0.1; n -= 0.2) {
      sprintf(mysighistname, "signal_lambdaZ_%0.2f_deltaKappaGamma_%0.1f", 0.6, n);
      TH1D* stackhist = GetSignalHistogram(0.6, n, mysighistname);
      outputForLimit->cd();
      stackhist->Write(); 
      delete stackhist;

      sprintf(mysighistname, "signal_lambdaZ_%0.2f_deltaKappaGamma_%0.1f", -0.6, n);
      TH1D* stackhist = GetSignalHistogram(-0.6, n, mysighistname);
      outputForLimit->cd();
      stackhist->Write(); 
      delete stackhist;
    }

    outputForLimit->Close();
}







void InstantiateTrees() {

 if (domu) {
    fin2            = new TFile("InData/RD_WmunuJets_DataAll_GoldenJSON_4p7invfb.root", "read");
    wwShape_file    = new TFile("InData/RD_mu_WW_CMSSW428.root", "READ");
    wzShape_file    = new TFile("InData/RD_mu_WZ_CMSSW428.root", "READ");
    wjetsShape_file = new TFile("InData/RD_mu_WpJ_CMSSW428.root", "READ");
    ttbar_file      = new TFile("InData/RD_mu_TTbar_CMSSW428.root", "READ");
    qcd_file1       = new TFile("InData/RDQCD_WmunuJets_DataAll_GoldenJSON_2p1invfb.root", "READ");
    zjets_file      = new TFile("InData/RD_mu_ZpJ_CMSSW428.root", "READ");
    stops_file      = new TFile("InData/RD_mu_STopS_T_CMSSW428.root", "READ");
    stopt_file      = new TFile("InData/RD_mu_STopT_T_CMSSW428.root", "READ");
    stoptW_file     = new TFile("InData/RD_mu_STopTW_T_CMSSW428.root", "READ");
    stopps_file =  new TFile("InData/RD_mu_STopS_Tbar_CMSSW428.root", "READ");
    stoppt_file =  new TFile("InData/RD_mu_STopT_Tbar_CMSSW428.root", "READ");
    stopptW_file =  new TFile("InData/RD_mu_STopTW_Tbar_CMSSW428.root", "READ");
  } else { // electrons

    fin2            = new TFile("InData/RD_WenuJets_DataAllSingleElectronTrigger_GoldenJSON_4p7invfb.root", "READ");
    wwShape_file    = new TFile("InData/RD_el_WW_CMSSW428.root", "READ");
    wzShape_file    = new TFile("InData/RD_el_WZ_CMSSW428.root", "READ");
    wjetsShape_file = new TFile("InData/RD_el_WpJ_CMSSW428.root", "READ");
    ttbar_file      = new TFile("InData/RD_el_TTbar_CMSSW428.root", "READ");
    qcd_file1       = new TFile("InData/RDQCD_WenuJets_DataAll_GoldenJSON_2p1invfb.root", "READ");
    zjets_file      = new TFile("InData/RD_el_ZpJ_CMSSW428.root", "READ");
    stops_file      = new TFile("InData/RD_el_STopS_T_CMSSW428.root", "READ");
    stopt_file      = new TFile("InData/RD_el_STopT_T_CMSSW428.root", "READ");
    stoptW_file     = new TFile("InData/RD_el_STopTW_T_CMSSW428.root", "READ");
    stopps_file =  new TFile("InData/RD_el_STopS_Tbar_CMSSW428.root", "READ");
    stoppt_file =  new TFile("InData/RD_el_STopT_Tbar_CMSSW428.root", "READ");
    stopptW_file =  new TFile("InData/RD_el_STopTW_Tbar_CMSSW428.root", "READ");
 }


  treedata = (TTree*) fin2->Get("WJet");
  double nData = treedata->GetEntries();
  std::cout << "ndata =" << nData <<std::endl;

  //// ------------ Get all trees
  treeww    = (TTree*)    wwShape_file->Get("WJet");
  treewz    = (TTree*)    wzShape_file->Get("WJet");
  treewj    = (TTree*)    wjetsShape_file->Get("WJet");
  treettb   = (TTree*)    ttbar_file->Get("WJet");
  treeqcd   = (TTree*)    qcd_file1->Get("WJet");
  treezj    = (TTree*)    zjets_file->Get("WJet");
  treests   = (TTree*)    stops_file->Get("WJet");
  treestt   = (TTree*)    stopt_file->Get("WJet");
  treestw   = (TTree*)    stoptW_file->Get("WJet");
  tree64    = (TTree*)    stopps_file->Get("WJet");
  tree65    = (TTree*)    stoppt_file->Get("WJet");
  tree66    = (TTree*)    stopptW_file->Get("WJet");

  //// ------------ Create a tree branch for dijet pt
  const char* dijetPt = "sqrt(JetPFCor_Pt[0]*JetPFCor_Pt[0]+JetPFCor_Pt[1]*JetPFCor_Pt[1]+2*JetPFCor_Pt[0]*JetPFCor_Pt[1]*cos(JetPFCor_Phi[0]-JetPFCor_Phi[1]))";
  treedata->SetAlias("dijetPt", dijetPt);
  treeww->SetAlias("dijetPt", dijetPt);
  treewz->SetAlias("dijetPt", dijetPt);
  treewj->SetAlias("dijetPt", dijetPt);
  treettb->SetAlias("dijetPt", dijetPt);
  treeqcd->SetAlias("dijetPt", dijetPt);
  treezj->SetAlias("dijetPt", dijetPt);
  treests->SetAlias("dijetPt", dijetPt);
  treestt->SetAlias("dijetPt", dijetPt);
  treestw->SetAlias("dijetPt", dijetPt);
  tree64->SetAlias("dijetPt", dijetPt);
  tree65->SetAlias("dijetPt", dijetPt);
  tree66->SetAlias("dijetPt", dijetPt);
}







void ScaleHistos()
{
  th1Top->Scale(ttbar_scale);
  th1Top->SetFillColor(kGreen+2);
  th1Top->SetLineColor(kGreen+2);
  th1Top->SetLineWidth(0);
  th1stops->Scale(STopS_scale);
  th1stops->SetFillColor(7);
  th1stops->SetLineWidth(2);
  th1stopt->Scale(STopT_scale);
  th1stopt->SetFillColor(13);
  th1stopt->SetLineWidth(2);
  th1stoptw->Scale(STopTW_scale);
  th1stoptw->SetFillColor(9);
  th1stoptw->SetLineWidth(2);
  th1wjets->Scale(WJets_scale);
  th1wjets->SetFillColor(kRed);
  th1wjets->SetLineColor(kRed);
  th1wjets->SetLineWidth(0);
  th1ww->Scale(WW_scale);
  th1ww->SetFillColor(kAzure+8);
  th1ww->SetLineColor(kAzure+8);
  th1ww->SetLineWidth(0);
  th1wz->Scale(WZ_scale);
  th1wz->SetFillColor(11);
  th1wz->SetLineWidth(0);
  // th1qcd->Scale(QCD_scale);
  
  th1qcd->SetFillColor(kGray+1);
  th1qcd->SetLineColor(kGray+1);
  th1qcd->SetLineWidth(0);
  th1zjets->Scale(ZJets_scale);
  th1zjets->SetFillColor(kYellow);
  th1zjets->SetLineColor(kYellow);
  th1zjets->SetLineWidth(0);
  std::cout << " qcd " << th1qcd->Integral()   << std::endl;
  std::cout << "tt "   << th1Top->Integral()   << std::endl;
  std::cout << "ww "   << th1ww->Integral()    << std::endl;
  std::cout << "wz "   << th1wz->Integral()    << std::endl;
  std::cout << "z "    << th1zjets->Integral() << std::endl;
  
  double den_qcd = 
    th1Top->Integral()+
    th1stops->Integral()+
    th1stopt->Integral()+
    th1stoptw->Integral()+
    th1wjets->Integral()+
    th1ww->Integral()+
    th1wz->Integral()+
    th1zjets->Integral();

  double qcd_scale;

  if (domu)
    qcd_scale = 0.002 ;//muon
  else
    qcd_scale = 0.062; //electron

  // qcd_scale = 0.001; //electron

  std::cout << " qcd_scale  " << qcd_scale <<std::endl;
  th1qcd->Scale(qcd_scale*den_qcd/th1qcd->Integral()); 

  double den = 
    th1Top->Integral()+
    th1stops->Integral()+
    th1stopt->Integral()+
    th1stoptw->Integral()+
    th1wjets->Integral()+
    th1ww->Integral()+
    th1wz->Integral()+
    th1zjets->Integral()+
    th1qcd->Integral();

  std::cout << "den = " <<den <<std::endl;
  std::cout <<" data " <<  th1data->Integral() << std::endl;

  th1qcd->Scale   (th1data->Integral()/den); std::cout <<"qcd "   << th1qcd->Integral()   << std::endl;
  th1Top->Scale   (th1data->Integral()/den); std::cout <<"tt "    << th1Top->Integral()   << std::endl;
  th1stops->Scale (th1data->Integral()/den); std::cout <<"stops " << th1stops->Integral() << std::endl;
  th1stopt->Scale (th1data->Integral()/den); std::cout <<"stopt " << th1stopt->Integral() << std::endl;
  th1stoptw->Scale(th1data->Integral()/den); std::cout <<"stoptw "<< th1stoptw->Integral()<< std::endl;
  th1wjets->Scale (th1data->Integral()/den); std::cout <<"wjets " << th1wjets->Integral() << std::endl;
  th1ww->Scale    (th1data->Integral()/den); std::cout <<"ww "    << th1ww->Integral()    << std::endl;
  th1wz->Scale    (th1data->Integral()/den); std::cout << "wz "   << th1wz->Integral()    << std::endl;
  th1zjets->Scale (th1data->Integral()/den); std::cout << "z "    << th1zjets->Integral() << std::endl;

  double den2 =
    th1Top->Integral()+
    th1stops->Integral()+
    th1stopt->Integral()+
    th1stoptw->Integral()+
    th1wjets->Integral()+
    th1ww->Integral()+
    th1wz->Integral()+
    th1zjets->Integral()+
    th1qcd->Integral();

  std::cout << "den2 " << den2 << std::endl;

  th1Top->Add(th1stoptw,1);
  th1Top->Add(th1stopt,1);
  th1Top->Add(th1stops,1);
  th1ww->Add(th1wz,1);


  // Sum all the backgrounds
  th1tot = (TH1D*)th1wjets->Clone("th1tot");
  th1tot->Reset();
  th1tot->Add(th1ww,1);
  th1tot->Add(th1qcd,1);
  th1tot->Add(th1Top,1);
  th1tot->Add(th1wjets,1);
  th1tot->Add(th1zjets,1);
  th1tot->SetFillStyle(3013);
  th1tot->SetFillColor(11);
  th1tot->SetLineColor(11);
  th1tot->SetMarkerStyle(0);
  th1tot->SetMinimum(0.0);

  th1totClone = ( TH1D*) th1tot->Clone("th1totClone");
  th1totClone->SetMarkerStyle(0);
  th1totClone->SetFillStyle(3003);
  th1totClone->SetFillColor(11);
  th1totClone->SetLineColor(0);

  double binErr(0.0);
  for(int i=0; i<th1totClone->GetNbinsX(); ++i) {
    binErr = sqrt((th1ww->GetBinError(i))**2 +
		  (th1qcd->GetBinError(i))**2 +
		  (th1Top->GetBinError(i))**2 +
		  (th1wjets->GetBinError(i))**2 +
		  (th1zjets->GetBinError(i))**2);
    th1totClone->SetBinError(i, binErr);
  }

  hhratio    = (TH1F*) th1data->Clone("hhratio")  ;
  hhratio->Sumw2();
  hhratio->SetMarkerSize(1.25);
  hhratio->GetYaxis()->SetRangeUser(0.33, 15.);
  hhratio->Divide(th1tot);
  double binError(0.0), mcbinentry(0.0), mcerror(0.0);
  for(int i=0; i<hhratio->GetNbinsX(); ++i) {
    binError = hhratio->GetBinError(i);
    mcerror = th1tot->GetBinError(i);
    mcbinentry = th1tot->GetBinContent(i);
    if(mcbinentry>0.) mcerror /= mcbinentry;
    else mcerror = 0.0;
    binError = sqrt(binError**2 + mcerror**2);
    hhratio->SetBinError(i, binError);
  }
}





TLegend* GetLegend()
{
  // float  legX0=0.5, legX1=0.89, legY0=0.41, legY1=0.86;
  float  legX0=0.45, legX1=0.92, legY0=0.52, legY1=0.88;
  TLegend * Leg = new TLegend( legX0, legY0, legX1, legY1);
  Leg->SetFillColor(0);
  Leg->SetFillStyle(0);
  Leg->SetTextSize(0.05);
  Leg->AddEntry(th1data,  "Data",  "PLE");
  Leg->AddEntry(th1ww,  "WW+WZ ",  "f");
  Leg->AddEntry(th1wjets,  "W+jets",  "f");
  Leg->AddEntry(th1Top,  "top",  "f");
  Leg->AddEntry(th1qcd,  "QCD",  "f");
  Leg->AddEntry(th1zjets,  "Z+Jets",  "f");
  Leg->AddEntry(signalForDisplay,  "aTGC: #Lambda_{Z}=0.4, #Delta#kappa_{#gamma}=0.0",  "l");
  // Leg->AddEntry(th1tot,  "MC Uncertainty",  "f");
  Leg->SetFillColor(0);

  return Leg;
}


void SetupEmptyHistogram()
{
  th1totempty = new TH1D("th1totempty", "th1totempty", bins, dm_min, dm_max);
  char tmpc[100];    sprintf(tmpc,"Events / %d GeV", (int) (dm_max-dm_min)/bins);
  th1totempty->SetYTitle(tmpc);
  th1totempty->GetYaxis()->SetTitleOffset(1.2);
  th1totempty->GetYaxis()->SetLabelOffset(0.01);
  th1totempty->GetYaxis()->SetLabelSize(0.06);
  int maxbin = th1data->GetMaximumBin();
  float maxval = th1data->GetBinContent(maxbin);
  std::cout << "maxval " <<maxval <<std::endl;
  th1totempty->SetMaximum(1.2*maxval);
  th1totempty->SetMinimum(0.0);


  th1emptyclone = new TH1D("th1emptyclone", "th1emptyclone", bins, dm_min, dm_max);
  th1emptyclone->GetYaxis()->SetRangeUser(0.33,15.);
  th1emptyclone->GetXaxis()->SetTitle("p_{T}^{jj} [GeV]");
  th1emptyclone->GetXaxis()->SetTitleOffset(0.9);
  th1emptyclone->GetXaxis()->SetTitleSize(0.15);
  th1emptyclone->GetXaxis()->SetLabelSize(0.15);
  th1emptyclone->SetYTitle("Data/MC");
  th1emptyclone->GetYaxis()->SetTitleSize(0.15);
  th1emptyclone->GetXaxis()->SetNdivisions(505);
  th1emptyclone->GetYaxis()->SetNdivisions(505);
  th1emptyclone->GetYaxis()->SetTitleOffset(0.5);
  th1emptyclone->GetYaxis()->CenterTitle(true);
  th1emptyclone->GetYaxis()->SetLabelSize(0.12);
  th1emptyclone->GetYaxis()->SetMoreLogLabels();
  th1emptyclone->GetYaxis()->SetNoExponent();
}


//------- Get signal histogram -------
TH1D* GetSignalHistogram(float lambdaZ, float dkappaGamma, char* histName) {

  char names[100];
  sprintf(names, "Histograms_ratio_aTGC_LambdaZ%.2f.root", lambdaZ);
  TFile* sigFile = TFile::Open(names, "read");
  sprintf(names, "HadronicWpT%.1f_ratio", dkappaGamma);
  TH1D* sigratio = (TH1D*) sigFile->Get(names);
  TH1D* newsighist = (TH1D*) th1ww->Clone(histName);
  newsighist->Multiply(sigratio);
  newsighist->Add(th1ww, -1.);
  newsighist->Smooth(10);
  newsighist->SetLineWidth(2);
  newsighist->SetLineColor(1);
  newsighist->SetFillColor(0);

  return newsighist;
}




void cmspre()
{
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.05);

  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.85,0.93,"#sqrt{s} = 7 TeV");
  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.65,0.93,Form("#scale[0.5]{#lower[-0.15]{#it{#int}}}#it{L} dt = %0.1f#kern[0.2]{fb}^{-1}", 5.0));
  latex.SetTextAlign(11); // align left
//  latex.DrawLatex(0.15,0.93,"CMS,  #sqrt{s} = 7 TeV");//preliminary 2011");
  latex.DrawLatex(0.15,0.93,"CMS");

}
