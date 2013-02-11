

const double intLUMI = 1.;
//const double WJets_scale   = 37509.0* intLUMI/18353019;
const double WJets_scale   = 3.32283007705589037e-05 * intLUMI;
const double W4Jets_scale  = 214.0 * intLUMI/12842803;
const double WW_scale      = 57.1097   * intLUMI/9450414;
const double WZ_scale      = 32.3161  * intLUMI/10000267;

const double ZJets_scale   = 3503.71  * intLUMI/30209426;
const double ttbar_scale   = 225.197 * intLUMI/6893735;

const double SToppS_scale  = 1.76 * intLUMI/ 139974;
const double SToppT_scale  = 30.7 * intLUMI/1935066;
const double SToppTW_scale = 11.1 * intLUMI/ 493458;
const double STopS_scale   = 3.79 * intLUMI/ 259960;
const double STopT_scale   = 56.4 * intLUMI/3758221;
const double STopTW_scale  = 11.1 * intLUMI/ 497657;




bool domu=true;
float yRatioMin = 0.;
float yRatioMax = 2.6,

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
TH1* systUp;
TH1* systDown;
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

bool saveDataCards_ = true;
TF1 *gaus2;


//////---------- channel: 0==muon dijet, 1== electron dijet
/////                     2==muon  boosted,   3== electron boosted
void makeATGCLimitDataCards(int channel=0) {


//   const Int_t bins = 8; 
//   const Float_t dm_min = 200.; 
//   const Float_t dm_max = 600.;

  Int_t bins = 8; 
  Float_t dm_min = 100.; 
  Float_t dm_max = 300.;
  if(channel>1) { bins = 8; dm_min = 200.; dm_max = 600.; }


  domu = true;
  if(channel==1 || channel==3) domu = false;

 
  TString outfile = (domu?TString("mu_"):TString("el_"))+ 
    (channel<2?TString("dijet"):TString("boosted"));
  outputForLimit = TFile::Open(outfile+".root", "recreate");




  char* cutsDijet = "(W_pt<200.) && (dijetPt>70.) && (abs(JetPFCor_Eta[0])<2.4) && (abs(JetPFCor_Eta[1])<2.4) && (abs(JetPFCor_Eta[0]-JetPFCor_Eta[1])<1.5) &&(abs(JetPFCor_dphiMET[0])>0.4) &&(W_mt>30.) &&(JetPFCor_Pt[0]>40.) &&(JetPFCor_Pt[1]>35.) &&(JetPFCor_Pt[2]<30.) &&(JetPFCor_bDiscriminatorCSV[0]<0.244) &&(JetPFCor_bDiscriminatorCSV[1]<0.244) && (Mass2j_PFCor>70. && Mass2j_PFCor<100.)";



 char* cutsMerged = "(W_pt>200.) && (GroomedJet_CA8_pt[0]>200.) &&(abs(GroomedJet_CA8_eta[0])<2.4) &&(JetPFCor_bDiscriminatorCSV[0]<0.244) &&(GroomedJet_numberbjets <1) &&(GroomedJet_CA8_deltaphi_METca8jet[0] > 2.0) && (GroomedJet_CA8_tau2tau1[0]<0.55) && (GroomedJet_CA8_deltaR_lca8jet[0]>1.57) && (GroomedJet_CA8_deltaphi_Vca8jet[0]>2.0) && (GroomedJet_CA8_mass[0]>70. && GroomedJet_CA8_mass[0]<100.)";


  TString lepton_cut = "(event_met_pfmet >30) && (W_electron_pt>35.) &&";
  if(channel==0) lepton_cut = "(event_met_pfmet >25) && (W_muon_pt>25.) &&";
  if(channel==1) lepton_cut = "(event_met_pfmet >30) && (W_electron_pt>30.) &&";
  if(channel==2) lepton_cut = "(event_met_pfmet >50) && (W_muon_pt>30.) &&";
  if(channel==3) lepton_cut = "(event_met_pfmet >70) && (W_electron_pt>35.) &&";


  TString jet_cut = TString(cutsDijet);
  if(channel>1) jet_cut = TString(cutsMerged);

  TCut the_cut( TString("(effwt*puwt)*(") + lepton_cut + jet_cut + TString(")") );

  char* observable = "dijetPt";
  char* xtitle = "p_{T}^{jj} [GeV]"; 
  if(channel>1) { 
    observable = "GroomedJet_CA8_pt[0]";
    xtitle = "p_{T}^{j} [GeV]";
  }

  InstantiateTrees();



  th1data  = new TH1D("th1data",  "th1data",  bins, dm_min, dm_max);
  th1data->Sumw2();
  th1data->SetMarkerStyle(20);
  th1data->SetMarkerSize(1.25);
  th1data->SetLineWidth(2);
  th1data->SetMinimum(0.0);
  treedata->Draw(TString(observable)+TString(">>th1data"), the_cut, "goff");

  // ------- Get WW/WZ ------- 
    th1ww = new TH1D("th1ww", "th1ww", bins, dm_min, dm_max);
    th1wz = new TH1D("th1wz", "th1wz", bins, dm_min, dm_max);
    th1ww->Sumw2();
    th1wz->Sumw2();
    treeww->Draw(TString(observable)+TString(">>th1ww"), the_cut, "goff");
    treewz->Draw(TString(observable)+TString(">>th1wz"), the_cut, "goff");


    // ------- Get WJets ------- 
    th1wjets  = new TH1D("th1wjets",  "th1wjets", bins, dm_min, dm_max);
    th1wjets->Sumw2();
    treewj->Draw(TString(observable)+TString(">>th1wjets"), the_cut, "goff");


    // ------- Get ttbar ------- 
    th1Top = new TH1D("th1Top", "th1Top", bins, dm_min, dm_max);
    th1Top->Sumw2();
    treettb->Draw(TString(observable)+TString(">>th1Top"), the_cut, "goff");

    // ------- Get QCD ------- 
    th1qcd = new TH1D("th1qcd", "th1qcd", bins, dm_min, dm_max);
    th1qcd->Sumw2();
    treeqcd->Draw(TString(observable)+TString(">>th1qcd"), the_cut, "goff");

    // ------- Get Z+Jets ------- 
    th1zjets = new TH1D("th1zjets", "th1zjets", bins, dm_min, dm_max);
    th1zjets->Sumw2();
    treezj->Draw(TString(observable)+TString(">>th1zjets"), the_cut, "goff");


    // ------- Get Single top ------- 
    th1stops = new TH1D("th1stops", "th1stops", bins, dm_min, dm_max);
    th1stopt = new TH1D("th1stopt", "th1stopt", bins, dm_min, dm_max);
    th1stoptw = new TH1D("th1stoptw", "th1stoptw", bins, dm_min, dm_max);
    th1stops->Sumw2();
    th1stopt->Sumw2();
    th1stoptw->Sumw2();

    treests->Draw(TString(observable)+TString(">>th1stops"), the_cut, "goff");
    treestt->Draw(TString(observable)+TString(">>th1stopt"), the_cut, "goff");
    treestw->Draw(TString(observable)+TString(">>th1stoptw"), the_cut, "goff");
 
    th1stopps = new TH1D("th1stopps", "th1stopps", bins, dm_min, dm_max);
    th1stoppt = new TH1D("th1stoppt", "th1stoppt", bins, dm_min, dm_max);
    th1stopptw = new TH1D("th1stopptw", "th1stopptw", bins, dm_min, dm_max);
    th1stopps->Sumw2();
    th1stoppt->Sumw2();
    th1stopptw->Sumw2();
    tree64->Draw(TString(observable)+TString(">>th1stopps"), the_cut, "goff");
    tree65->Draw(TString(observable)+TString(">>th1stoppt"), the_cut, "goff");
    tree66->Draw(TString(observable)+TString(">>th1stopptw"), the_cut, "goff");


    // Scale the histos
    ScaleHistos();


    // ---- Make smooth W+jets shape ----------
    TH1D* th1wjetsclone = th1wjets->Clone("th1wjetsclone");
    TF1 *gaus = new TF1("gaus","gaus",dm_min, dm_max);
    th1wjets->Fit(gaus,"I0","");
    th1wjets->Add(gaus);
    th1wjets->Add(th1wjetsclone, -1.);
    delete th1wjetsclone;


    // ---- Make smooth diboson shape ----------
    TH1D* th1wwclone = th1ww->Clone("th1wwclone");
    gaus2 = new TF1("gaus2","gaus",dm_min, dm_max);
    th1ww->Fit(gaus2,"I0","");
    th1ww->Add(gaus2);
    th1ww->Add(th1wwclone, -1.);
    delete th1wwclone;



//     // ---- Make smooth ttbar shape ----------
//     TH1D* th1Topclone = th1Top->Clone("th1Topclone");
//     TF1 *gaus3 = new TF1("gaus3","gaus",dm_min, dm_max);
//     th1Top->Fit(gaus3,"I0","");
//     th1Top->Add(gaus3);
//     th1Top->Add(th1Topclone, -1.);
//     delete th1Topclone;




//     // ---- Make smooth Z+jets shape ----------
//     TH1D* th1zjetsclone = th1zjets->Clone("th1zjetsclone");
//     TF1 *gaus4 = new TF1("gaus4","gaus",dm_min, dm_max);
//     th1zjets->Fit(gaus4,"I0","");
//     th1zjets->Add(gaus4);
//     th1zjets->Add(th1zjetsclone, -1.);
//     delete th1zjetsclone;


    /////////////////////
    SetupEmptyHistogram(bins, dm_min, dm_max, xtitle);
    SumAllBackgrounds();
    /////////////////////

    double overflow = th1wjets->GetBinContent(bins+1);
    overflow += gaus2->Integral(dm_max, dm_max + 400.);
    overflow += th1zjets->GetBinContent(bins+1);
    overflow += th1qcd->GetBinContent(bins+1);
    overflow += th1Top->GetBinContent(bins+1);
    cout << "---------- overflow for bkg = " << overflow << endl;

    //Get signal histogram
    signalForDisplay = GetSignalHistogram(0.05, 0.0, 0.0, "signalForDisplay", dm_max, overflow);

    // ratio histogram for aTGC display
    signalRatioForDisplay = 
      (TH1D*) signalForDisplay->Clone("signaRatiolForDisplay");
    signalRatioForDisplay->Divide(th1tot);
    for(int j=1; j<signalRatioForDisplay->GetNbinsX()+1; ++j) {
      double entry = signalRatioForDisplay->GetBinContent(j);
      if() signalRatioForDisplay->SetBinContent(j, 1.+entry);
    }
   


    //-------- Add overflow bin ----------------
//     double lastbin = th1ww->GetBinContent(bins-1);
//     double overflow = th1ww->GetBinContent(bins);
//     th1ww->SetBinContent(bins-1, lastbin+overflow);
//     lastbin = th1wjets->GetBinContent(bins-1);
//     overflow = th1wjets->GetBinContent(bins);
//     th1wjets->SetBinContent(bins-1, lastbin+overflow);
//     lastbin = th1data->GetBinContent(bins-1);
//     overflow = th1data->GetBinContent(bins);
//     th1data->SetBinContent(bins-1, lastbin+overflow);



    // Compose the stack
    THStack* hs = new THStack("hs","MC contribution");
    hs->Add(th1zjets);
    hs->Add(th1qcd);
    hs->Add(th1Top);
    hs->Add(th1wjets);
    hs->Add(th1ww);
    hs->Add(signalForDisplay);



    // Stack for systematics Up
    TF1* formScaleUp = new TF1("formScaleUp", "1.0+0.3*log(x/5)", dm_min, dm_max);
    TF1* formScaleDown = new TF1("formScaleDown", "1.0-0.15*log(x/5)", dm_min, dm_max);

    systUp = (TH1D*) th1wjets->Clone("systUp");
    systUp->Multiply(formScaleUp);
    systUp->Add(th1zjets);
    systUp->Add(th1qcd);
    systUp->Add(th1Top);
    systUp->Add(th1ww);
    systUp->SetFillColor(0);
    systUp->SetLineStyle(2);
    systUp->SetLineColor(2);
    systUp->SetLineWidth(3);


    hhratioUp    = (TH1F*) th1data->Clone("hhratioUp")  ;
    hhratioUp->GetYaxis()->SetRangeUser(yRatioMin, yRatioMax);
    hhratioUp->Divide(systUp);
    hhratioUp->SetLineStyle(2);
    hhratioUp->SetLineColor(2);
    hhratioUp->SetLineWidth(3);


    // Stack for systematics Down
    TH1D* systDown = (TH1D*) th1wjets->Clone("systDown");
    systDown->Multiply(formScaleDown);
    systDown->Add(th1zjets);
    systDown->Add(th1qcd);
    systDown->Add(th1Top);
    systDown->Add(th1ww);
    systDown->SetFillColor(0);
    systDown->SetLineWidth(3);
    systDown->SetLineStyle(2);
    systDown->SetLineColor(2);
    TH1F* hhratioDown    = (TH1F*) th1data->Clone("hhratioDown")  ;
    hhratioDown->GetYaxis()->SetRangeUser(yRatioMin, yRatioMax);
    hhratioDown->Divide(systDown);
    hhratioDown->SetLineStyle(2);
    hhratioDown->SetLineColor(2);
    hhratioDown->SetLineWidth(3);


    ///////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////
    /////  ad hoc thing for the 500 range: remove 0 entry points by hand

//     for(int j=1; j<hhratio->GetNbinsX()+1; ++j) {
//       double x = hhratio->GetBinCenter(j);
//       if(x>400 || (channel>0 && x>350) ) { 
// 	hhratio->SetBinContent(j, 0.); 
// 	hhratio->SetBinError(j, 0.);
// 	th1data->SetBinContent(j, 0.); 
// 	th1data->SetBinError(j, 0.);
// 	hhratioUp->SetBinContent(j, 0.); 
// 	hhratioUp->SetBinError(j, 0.);
// 	hhratioDown->SetBinContent(j, 0.); 
// 	hhratioDown->SetBinError(j, 0.);
//       }
//     }
   
//     //////////////////
    /////////////////////////////////////////
    ///////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////


    // ------- Setup the canvas ------- 
    gStyle->SetOptStat(0);
    // gStyle->SetPadTopMargin(0.1);
    gStyle->SetPadLeftMargin(0.15);
    // gStyle->SetPadRightMargin(0.2);
    gStyle->SetPadBottomMargin(0.3);


    TCanvas* c1 = new TCanvas("dijetPt", "dijetPt", 10,10, 500, 500);
    TPad *d1, *d2;
    c1->Divide(1,2,0,0);
    d1 = (TPad*)c1->GetPad(1);
    d1->SetPad(0.01,0.30,0.95,0.99);
    d2 = (TPad*)c1->GetPad(2);
    d2->SetPad(0.01,0.02,0.95,0.30);

    d1->cd();
    gPad->SetBottomMargin(0.005);
    gPad->SetTopMargin(0.1);
    gPad->SetRightMargin(0.04);
    // gPad->SetLeftMargin(0.14);


    // Draw it all
    double ymax= 5000000.;
    double ymin= 0.8;
    if(channel>1) ymax= 30000.;


    th1totempty->GetYaxis()->SetRangeUser(ymin, ymax);
    th1data->GetYaxis()->SetRangeUser(ymin, ymax);
    th1totempty->Draw();
    th1data->Draw("esame");
    hs->Draw("samehist");
    // systUp->Draw("samehist");
    // systDown->Draw("samehist");
    //th1tot->Draw("e3same");
    th1data->Draw("esame");
    cmspre(); 
    // Set up the legend
    TLegend* Leg = GetLegend(channel);   
    Leg->Draw();  
    d1->SetLogy();
    gPad->RedrawAxis();


    d2->cd();
    // gPad->SetLeftMargin(0.14);
    gPad->SetTopMargin(0.02);
    gPad->SetRightMargin(0.04);
    // gPad->SetRightMargin(0.05);
    gPad->SetFrameBorderSize(0);
    //gPad->SetBottomMargin(0.3);
    gPad->SetTickx();

    th1emptyclone->Draw();
    hhratio->Draw("esame");
    hhratioUp->Draw("hist lsame");
    hhratioDown->Draw("hist lsame");
    // signalRatioForDisplay->Draw("hist same");
    TLine *line; line = new TLine(dm_min,1.0,dm_max,1.0);
    line->SetLineStyle(1);
    line->SetLineWidth(1);
    line->SetLineColor(1);
    line->Draw();
    //d2->SetLogy();
    //d2->SetGridy();
    c1->Print(TString("OutDir/")+outfile+TString("_dijetPt.png"));
    //gPad->WaitPrimitive();
    c1->Modified();
    c1->Update();
    c1->SaveAs(TString("OutDir/")+outfile+TString("_dijetPt.pdf")); 
    c1->SaveAs(TString("OutDir/")+outfile+TString("_dijetPt.root")); 

   


    ///// -------------------------------//////

    if(saveDataCards_) {
      outputForLimit->cd();
      th1data->SetName("data_obs");
      th1data->Write("data_obs");
      th1tot->SetName("background");
      th1tot->Write("background");
      char* tempname = "background_backshapeUp";
      if(channel==0) tempname = "background_mudijet_backshapeUp";
      if(channel==1) tempname = "background_eldijet_backshapeUp";
      if(channel==2) tempname = "background_muboosted_backshapeUp";
      if(channel==3) tempname = "background_elboosted_backshapeUp";
      systUp->SetName(tempname);
      systUp->Write(tempname);
      tempname = "background_backshapeDown";
      if(channel==0) tempname = "background_mudijet_backshapeDown";
      if(channel==1) tempname = "background_eldijet_backshapeDown";
      if(channel==2) tempname = "background_muboosted_backshapeDown";
      if(channel==3) tempname = "background_elboosted_backshapeDown";
      systDown->SetName(tempname);
      systDown->Write(tempname);


//       char mysighistname[100];
//       for (float m=-0.1; m<0.1005; m += 0.005) {
// 	for (float n=0.3; n>-0.302; n -= 0.02) {
// 	  for (float q=0.6; q>-0.605; q -= 0.05) {
// 	  // if( fabs(m) > 0.1 && fabs(n) > 0.2) continue;
// 	  sprintf(mysighistname, 
// 		  "signal_lambdaZ_%0.3f_deltaKappaGamma_%0.3f_deltaG1_%0.3f", 
// 		  m+0.00001, n+0.00001, q+0.00001);
// 	  TH1D* stackhist = GetSignalHistogram(m+0.00001, n+0.00001, 
// 					       q+0.00001, mysighistname, 
// 					       dm_max, overflow);
// 	  outputForLimit->cd();
// 	  stackhist->Write(); 
// 	  delete stackhist;
// 	  }
// 	}
//       }


      char mysighistname[100];
      for (float m=-0.1; m<0.1005; m += 0.005) {
	for (float n=0.3; n>-0.302; n -= 0.02) {
	  sprintf(mysighistname, 
		  "signal_lambdaZ_%0.3f_deltaKappaGamma_%0.3f", 
		  m+0.00001, n+0.00001);
	  TH1D* stackhist = GetSignalHistogram(m, n, 
					       0.0, mysighistname, 
					       dm_max, overflow);
	  outputForLimit->cd();
	  stackhist->Write(); 
	  delete stackhist;
	}
      }
 


      for (float m=-0.1; m<0.1005; m += 0.005) {
	for (float n=0.6; n>-0.605; n -= 0.05) {
	  sprintf(mysighistname, 
		  "signal_lambdaZ_%0.3f_deltaG1_%0.3f", 
		  m+0.00001, n+0.00001);
	  TH1D* stackhist = GetSignalHistogram(m, 0.0, 
					       n, mysighistname, 
					       dm_max, overflow);
	  outputForLimit->cd();
	  stackhist->Write(); 
	  delete stackhist;
	}
      }
 


      outputForLimit->Close();

    } ///// close if saveDataCards_

}







void InstantiateTrees() {

 if (domu) {
    fin2            = new TFile("InData/RD_WmunuJets_DataAll_GoldenJSON_19p3invfb.root", "read");
    wwShape_file    = new TFile("InData/RD_mu_WW_CMSSW532.root", "READ");
    wzShape_file    = new TFile("InData/RD_mu_WZ_CMSSW532.root", "READ");
    wjetsShape_file = new TFile("InData/RD_mu_WpJ_CMSSW532.root", "READ");
    wjetsShapeUp_file = new TFile("InData/RD_mu_WpJscaleup_CMSSW532.root", "READ");
    wjetsShapeDown_file = new TFile("InData/RD_mu_WpJscaledown_CMSSW532.root", "READ");
    ttbar_file      = new TFile("InData/RD_mu_TTbar_CMSSW532.root", "READ");
    qcd_file1       = new TFile("InData/RD_mu_WpJ_CMSSW532.root", "READ");
    zjets_file      = new TFile("InData/RD_mu_ZpJ_CMSSW532.root", "READ");
    stops_file      = new TFile("InData/RD_mu_STopS_T_CMSSW532.root", "READ");
    stopt_file      = new TFile("InData/RD_mu_STopT_T_CMSSW532.root", "READ");
    stoptW_file     = new TFile("InData/RD_mu_STopTW_T_CMSSW532.root", "READ");
    stopps_file =  new TFile("InData/RD_mu_STopS_Tbar_CMSSW532.root", "READ");
    stoppt_file =  new TFile("InData/RD_mu_STopT_Tbar_CMSSW532.root", "READ");
    stopptW_file =  new TFile("InData/RD_mu_STopTW_Tbar_CMSSW532.root", "READ");
  } else { // electrons

   fin2            = new TFile("InData/RD_WenuJets_DataAllSingleElectronTrigger_GoldenJSON_19p2invfb.root", "READ");
    wwShape_file    = new TFile("InData/RD_el_WW_CMSSW532.root", "READ");
    wzShape_file    = new TFile("InData/RD_el_WZ_CMSSW532.root", "READ");
    wjetsShape_file = new TFile("InData/RD_el_WpJ_CMSSW532.root", "READ");
    wjetsShapeUp_file = new TFile("InData/RD_el_WpJscaleup_CMSSW532.root", "READ");
    wjetsShapeDown_file = new TFile("InData/RD_el_WpJscaledown_CMSSW532.root", "READ");
    ttbar_file      = new TFile("InData/RD_el_TTbar_CMSSW532.root", "READ");
    qcd_file1       = new TFile("InQCD/RDQCD_WenuJets_Isog0p3NoElMVA_19p2invfb.root", "READ");
    zjets_file      = new TFile("InData/RD_el_ZpJ_CMSSW532.root", "READ");
    stops_file      = new TFile("InData/RD_el_STopS_T_CMSSW532.root", "READ");
    stopt_file      = new TFile("InData/RD_el_STopT_T_CMSSW532.root", "READ");
    stoptW_file     = new TFile("InData/RD_el_STopTW_T_CMSSW532.root", "READ");
    stopps_file =  new TFile("InData/RD_el_STopS_Tbar_CMSSW532.root", "READ");
    stoppt_file =  new TFile("InData/RD_el_STopT_Tbar_CMSSW532.root", "READ");
    stopptW_file =  new TFile("InData/RD_el_STopTW_Tbar_CMSSW532.root", "READ");
 }


  treedata = (TTree*) fin2->Get("WJet");
  double nData = treedata->GetEntries();
  std::cout << "ndata =" << nData <<std::endl;

  //// ------------ Get all trees
  treeww    = (TTree*)    wwShape_file->Get("WJet");
  treewz    = (TTree*)    wzShape_file->Get("WJet");
  treewj    = (TTree*)    wjetsShape_file->Get("WJet");
  treewjUp  = (TTree*)    wjetsShapeUp_file->Get("WJet");
  treewjDown = (TTree*)    wjetsShapeDown_file->Get("WJet");
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
  treewjUp->SetAlias("dijetPt", dijetPt);
  treewjDown->SetAlias("dijetPt", dijetPt);
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
    qcd_scale = 0.0 ;//muon
  else
    qcd_scale = 0.04; //electron


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
}



  // Sum all the backgrounds
void SumAllBackgrounds() {
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
  hhratio->GetYaxis()->SetRangeUser(yRatioMin, yRatioMax);
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
    if(th1data->GetBinContent(i)<0.1) hhratio->SetBinError(i,0.0);
  }
}





TLegend* GetLegend(int channel)
{
  // float  legX0=0.5, legX1=0.89, legY0=0.41, legY1=0.86;
  float  legX0=0.68, legX1=0.93, legY0=0.45, legY1=0.88;
  if(channel > 1) legY0=0.52; 
  TLegend * Leg = new TLegend( legX0, legY0, legX1, legY1);
  Leg->SetFillColor(0);
  Leg->SetFillStyle(0);
  Leg->SetTextSize(0.05);
  Leg->AddEntry(th1data,  "Data",  "PLE");
  Leg->AddEntry(th1ww,  "WW+WZ ",  "f");
  Leg->AddEntry(th1wjets,  "W+jets",  "f");
  Leg->AddEntry(th1Top,  "top",  "f");
  if(channel != 2) Leg->AddEntry(th1qcd,  "Multijet",  "f");
  Leg->AddEntry(th1zjets,  "Z+Jets",  "f");
  Leg->AddEntry(systUp,  "Shape error",  "f");
  Leg->AddEntry(signalForDisplay,  "#lambda_{Z}=0.05",  "l");
  // Leg->AddEntry(th1tot,  "MC Uncertainty",  "f");
  Leg->SetFillColor(0);

  return Leg;
}


void SetupEmptyHistogram(int bins, double dm_min, double dm_max, char* xtitle)
{
  th1totempty = new TH1D("th1totempty", "th1totempty", bins, dm_min, dm_max);
  char tmpc[100];    sprintf(tmpc,"Events / %d GeV", (int) (dm_max-dm_min)/bins);
  th1totempty->SetYTitle(tmpc);
  th1totempty->GetYaxis()->SetTitleOffset(1);
  th1totempty->GetYaxis()->SetLabelOffset(0.01);
  th1totempty->GetYaxis()->SetLabelSize(0.08);
  th1totempty->GetYaxis()->SetTitleSize(0.08);

  int maxbin = th1data->GetMaximumBin();
  float maxval = th1data->GetBinContent(maxbin);
  std::cout << "maxval " <<maxval <<std::endl;
  th1totempty->SetMaximum(1.2*maxval);
  th1totempty->SetMinimum(0.0);


  th1emptyclone = new TH1D("th1emptyclone", "th1emptyclone", bins, dm_min, dm_max);
  th1emptyclone->GetYaxis()->SetRangeUser(yRatioMin, yRatioMax);
  th1emptyclone->GetXaxis()->SetTitle(xtitle);
  th1emptyclone->GetXaxis()->SetTitleOffset(0.9);
  th1emptyclone->GetXaxis()->SetTitleSize(0.15);
  th1emptyclone->GetXaxis()->SetLabelSize(0.15);
  th1emptyclone->SetYTitle("Data/MC  ");
  th1emptyclone->GetYaxis()->SetTitleSize(0.2);
  th1emptyclone->GetXaxis()->SetNdivisions(505);
  th1emptyclone->GetYaxis()->SetNdivisions(505);
  th1emptyclone->GetYaxis()->SetTitleOffset(0.3);
  th1emptyclone->GetYaxis()->CenterTitle(true);
  th1emptyclone->GetYaxis()->SetLabelSize(0.2);
  th1emptyclone->GetXaxis()->SetLabelSize(0.2);
  th1emptyclone->GetXaxis()->SetTitleSize(0.2);
  th1emptyclone->GetYaxis()->SetMoreLogLabels();
  th1emptyclone->GetYaxis()->SetNoExponent();
}


//------- Get signal histogram -------
TH1D* GetSignalHistogram(float lambdaZ, float dkappaGamma, float deltaG1, 
			 char* histName, double dm_max, double baseline_overflow) {

  //---- first we clone the diboson histogram  
  TH1D* newsighist = (TH1D*) th1ww->Clone(histName);

  // --- now define the enhancement ratio function 
  double lambdaZC0 = 0.937435 - 5.57827*lambdaZ + 129.292*lambdaZ*lambdaZ;
  double lambdaZC1 = 0.0;
  double lambdaZC2 = 0.0000015989 - 0.000145525*lambdaZ + 
    0.00689186*lambdaZ*lambdaZ;

  double kappaGC0 = 2.88936 - 29.3189*dkappaGamma + 
    97.749*dkappaGamma*dkappaGamma;
  double kappaGC1 = 0.0;
  double kappaGC2 = 0.0000795061e - 0.00120206*dkappaGamma + 
    0.00844054*dkappaGamma*dkappaGamma;

  double g1C0 =  0.949535 -  0.264428*deltaG1  +  1.17098*deltaG1*deltaG1;
  double g1C1 =  0.0;
  double g1C2 =  0.000000285246 - 0.00000118628*deltaG1  +  
    0.0000660855 *deltaG1*deltaG1;


  TF1* sigratio = 
    new TF1("sigratio",
	    "([0]+[1]*x+[2]*x*x)*([3]+[4]*x+[5]*x*x)*([6]+[7]*x+[8]*x*x)", 
	    50., 1500.);

  if(fabs(lambdaZ)>0.00001) 
    sigratio->SetParameter(0, lambdaZC0); 
  else sigratio->SetParameter(0, 1.0);
  sigratio->SetParameter(1, lambdaZC1);
  sigratio->SetParameter(2, lambdaZC2);

 
  if(fabs(dkappaGamma)>0.00001)
    sigratio->SetParameter(3, kappaGC0);
  else sigratio->SetParameter(3, 1.0);
  sigratio->SetParameter(4, kappaGC1);
  sigratio->SetParameter(5, kappaGC2);


  if(fabs(deltaG1)>0.00001) 
    sigratio->SetParameter(6, g1C0);
  else sigratio->SetParameter(6, 1.0);
  sigratio->SetParameter(7, g1C1);
  sigratio->SetParameter(8, g1C2);


//   TCanvas* c5 = new TCanvas("c5", "", 500, 500);
//   sigratio->Draw();

  // ---- multiply the diboson histogram with enhancement function
  newsighist->Multiply(sigratio);

  // ----- need to subtract the diboson contribution 
  newsighist->Add(th1ww, -1.);

  //    newsighist->Smooth(10);


  newsighist->SetLineWidth(2);
  newsighist->SetLineColor(1);
  newsighist->SetFillColor(0);


  //-------- Add overflow bin ----------------
  int nBinsTot = newsighist->GetNbinsX();
  double lastbin = newsighist->GetBinContent(nBinsTot);
  TF1 *fSignal = new TF1 ("fSignal", "gaus2*sigratio");
  double overflow = fSignal->Integral(dm_max, dm_max + 400.);

  overflow -= baseline_overflow;

  //cout << "last bin = " << lastbin << ", overflow = " << overflow << endl;

  newsighist->SetBinContent(nBinsTot, lastbin+overflow);
  newsighist->SetBinError(nBinsTot, sqrt(lastbin+overflow));

  return newsighist;
}




void cmspre()
{
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.05);

  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.85,0.93,"#sqrt{s} = 8 TeV");
  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.65,0.93,Form("#scale[0.5]{#lower[-0.15]{#it{#int}}}#it{L} dt = %0.1f#kern[0.2]{fb}^{-1}", 19.3));
  latex.SetTextAlign(11); // align left
//  latex.DrawLatex(0.15,0.93,"CMS,  #sqrt{s} = 7 TeV");//preliminary 2011");
  latex.DrawLatex(0.15,0.93,"CMS");

}
