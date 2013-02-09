////////////////////////
///// Load Header Files:
#define kanamuon_photon_cxx
#include "kanamuon_photon.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <TMath.h>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>

#include "Resolution.h"
#include "EffTableReader.h"
#include "EffTableLoader.h"

#include "PhysicsTools/KinFitter/interface/TFitConstraintMGaus.h"
#include "PhysicsTools/KinFitter/interface/TFitConstraintM.h"
#include "PhysicsTools/KinFitter/interface/TFitConstraintEp.h"
#include "PhysicsTools/KinFitter/interface/TFitParticleEtEtaPhi.h"
#include "PhysicsTools/KinFitter/interface/TFitParticleCart.h"
#include "PhysicsTools/KinFitter/interface/TKinFitter.h"

#include "ElectroWeakAnalysis/VPlusJets/interface/AngularVars.h"
#include "ElectroWeakAnalysis/VPlusJets/interface/QGLikelihoodCalculator.h"
#include "ElectroWeakAnalysis/VPlusJets/interface/METzCalculator.h"

//////////////////////////
///// Load MVA Ouput Code:
#include "ClassifierOut/TMVAClassification_WWA_nJ2_mu_BDT.class.C"

/////////////////////////////////////////
///// Specify Location of Merged Ntuples:
const TString inDataDir  = "/eos/uscms/store/user/lnujj/Moriond2013/MergedNtuples/";
const TString inDataDir2 = "/eos/uscms/store/user/jfaulkn3/MergedNTuples/MC/";
const TString inDataDir3 = "/eos/uscms/store/user/jfaulkn3/MergedNTuples/Data2012/";
const TString inQCDDir   = "/eos/uscms/store/user/lnujj/Moriond2013/MergedNtuples/";

//////////////////////////////////////////////
///// Specify Location of Store Reduced Trees:
//const TString outDataDir   = "/eos/uscms/store/user/jfaulkn3/ReducedTrees/";
const TString outDataDir   = "/uscms_data/d3/jfaulkn3/ReducedTrees/";

/////////////////////////////////////////////////////////
///// Specify Location of Efficiency Tables:
const std::string fDir   = "EffTable2012/";


////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
///// Function to determine if "a" is greater than "b":
bool large(const double &a, const double &b)
{

   return a > b;
}// End Function "large"



////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
///// Function to Specify Sample to Run Over:
void kanamuon_photon::myana(double myflag, bool isQCD, int runflag)
{

   //////////////////////////////////////////////////////////////////////
   /////Prepare the histogram for the cut-flow control : 8 presel + 7 sel
   const int n_step = 15;
   TH1F* h_events          = new TH1F("h_events", "h_events", n_step, 0, n_step);
   TH1F* h_events_weighted = new TH1F("h_events_weighted", "h_events_weighted", n_step, 0, n_step);

   ///////////////////////////////
   ///// Specify Event Categories:
   string step_names[n_step] = {
      "all",
      "no scraping",
      "HBHE noise filter",
      "good PV",
      "tight lepton",
      "loose ele veto",
      "loose mu veto",
      "loose jets",
      "P_{T}(WJ1) > 30", 
      "P_{T}(WJ2) > 30",
      "M_{T}(W^{lep}) > 30",
      "tighter lepton",
      "#Delta#eta(W^{had}) < 1.5",
      "#Delta#phi(WJ1,MET) > 0.4",
      "P_{T}(W^{had}) > 40"};

   /////////////////////////////////////////////////
   ///// Label Event Categories in Event Histograms:
   for ( int istep = 0; istep < n_step; istep++ ) {
      h_events -> GetXaxis() -> SetBinLabel( istep + 1, step_names[istep].c_str() );
      h_events_weighted -> GetXaxis() -> SetBinLabel( istep + 1, step_names[istep].c_str() );
   }

   ///////////////////////////////////////
   ///// Run over specified Merged Ntuple:
   TChain * myChain;

   ////////////////
   ///// 2012 data:
   if (myflag == 20120000 || myflag == -100){
      myChain = new TChain("WJet");  

      if ( !isQCD ) {
         InitCounters( inDataDir + "WmunuJets_DataAllSingleMuonTrigger_GoldenJSON_15p7invfb.root", h_events, h_events_weighted);
         myChain->Add(                    inDataDir + "WmunuJets_DataAllSingleMuonTrigger_GoldenJSON_15p7invfb.root");
         Init(myChain);Loop( h_events, h_events_weighted, 20120000,runflag, outDataDir + "RD_WmunuJets_DataAll_GoldenJSON_15p7invfb");
      } else {
         InitCounters( inDataDir + "QCDmu.root", h_events, h_events_weighted);
         myChain->Add(                    inQCDDir +     "QCDmu.root");
         Init(myChain);Loop( h_events, h_events_weighted, 20120000,runflag, outDataDir + "RDQCD_WmunuJets_DataAll_GoldenJSON_0p7invfb", isQCD);
      }
   }

   if (myflag == 20120001 || myflag == -100){
      myChain = new TChain("WJet");  

      if ( !isQCD ) {
         InitCounters( inDataDir + "WmunuJets_DataAllSingleMuonTrigger_GoldenJSON_5p3invfb.root", h_events, h_events_weighted);
         myChain->Add(                    inDataDir + "WmunuJets_DataAllSingleMuonTrigger_GoldenJSON_5p3invfb.root");
         Init(myChain);Loop( h_events, h_events_weighted, 20120001,runflag, outDataDir + "RD_WmunuJets_DataAll_GoldenJSON_5p3invfb");
      } else {
         InitCounters( inDataDir + "QCDmu.root", h_events, h_events_weighted);
         myChain->Add(                    inQCDDir +     "QCDmu.root");
         Init(myChain);Loop( h_events, h_events_weighted, 20120001,runflag, outDataDir + "RDQCD_WmunuJets_DataAll_GoldenJSON_0p7invfb", isQCD);
      }
   }

   if (myflag == 20120002 || myflag == -100){
      myChain = new TChain("WJet");

      if ( !isQCD ) {
         InitCounters( inDataDir + "WmunuJets_DataAllSingleMuonTrigger_GoldenJSON_18p764invfb.root", h_events, h_events_weighted);
         myChain->Add(                    inDataDir + "WmunuJets_DataAllSingleMuonTrigger_GoldenJSON_18p764invfb.root");
         Init(myChain);Loop( h_events, h_events_weighted, 20120002,runflag, outDataDir + "RD_WmunuJets_DataAll_GoldenJSON_18p764invfb");
      } else {
         InitCounters( inDataDir + "QCDmu.root", h_events, h_events_weighted);
         myChain->Add(                    inQCDDir +     "QCDmu.root");
         Init(myChain);Loop( h_events, h_events_weighted, 20120002,runflag, outDataDir + "RDQCD_WmunuJets_DataAll_GoldenJSON_18p764invfb", isQCD);
      }
   }

   if (myflag == 20120003 || myflag == -100){
      myChain = new TChain("WJet");

      if ( !isQCD ) {
         InitCounters( inDataDir3 + "WmunuJets_DataAllSingleMuonTrigger_GoldenJSON_19p3invfb.root", h_events, h_events_weighted);
         myChain->Add( inDataDir3 + "WmunuJets_DataAllSingleMuonTrigger_GoldenJSON_19p3invfb.root");
         Init(myChain);Loop( h_events, h_events_weighted, 20120003,runflag, outDataDir + "RD_WmunuJets_DataAll_GoldenJSON_19p3invfb");
      } else {
         InitCounters( inDataDir3 + "QCDmu.root", h_events, h_events_weighted);
         myChain->Add(                    inQCDDir +     "QCDmu.root");
         Init(myChain);Loop( h_events, h_events_weighted, 20120003,runflag, outDataDir + "RDQCD_WmunuJets_DataAll_GoldenJSON_19p3invfb", isQCD);
      }
   }

   /////////////////////////////////
   ///// General Background Samples:
   if ( !isQCD ) {
      if (myflag == 20121002 || myflag == -200){
         InitCounters( inDataDir + "mu_STopS_Tbar_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_STopS_Tbar_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121002,runflag, outDataDir + "RD_mu_STopS_Tbar_CMSSW532");
      }
      if (myflag == 20121003 || myflag == -200){
         InitCounters( inDataDir + "mu_STopS_T_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_STopS_T_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121003,runflag, outDataDir + "RD_mu_STopS_T_CMSSW532");
      }
      if (myflag == 20121004 || myflag == -200){
         InitCounters( inDataDir + "mu_STopT_Tbar_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_STopT_Tbar_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121004,runflag, outDataDir + "RD_mu_STopT_Tbar_CMSSW532");
      }
      if (myflag == 20121005 || myflag == -200){
         InitCounters( inDataDir + "mu_STopT_T_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_STopT_T_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121005,runflag, outDataDir + "RD_mu_STopT_T_CMSSW532");
      }
      if (myflag == 20121006 || myflag == -200){
         InitCounters( inDataDir + "mu_STopTW_Tbar_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_STopTW_Tbar_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121006,runflag, outDataDir + "RD_mu_STopTW_Tbar_CMSSW532");
      }
      if (myflag == 20121007 || myflag == -200){
         InitCounters( inDataDir + "mu_STopTW_T_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_STopTW_T_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121007,runflag, outDataDir + "RD_mu_STopTW_T_CMSSW532");
      }
      if (myflag == 20121008 || myflag == -200){
         InitCounters( inDataDir + "mu_TTbar_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_TTbar_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121008,runflag, outDataDir + "RD_mu_TTbar_CMSSW532");
      }
      if (myflag == 20121108 || myflag == -200){
         InitCounters( inDataDir + "crabmerge_MC_Wmunu_TTbar.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "crabmerge_MC_Wmunu_TTbar.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121108,runflag, outDataDir + "RD_mu_TTbar_CMSSW532");
      }
      if (myflag == 20121009 || myflag == -500){
         InitCounters( inDataDir + "mu_WpJ_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WpJ_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121009,runflag, outDataDir + "RD_mu_WpJ_CMSSW532");
      }
      if (myflag == 20121015 || myflag == -200){
         InitCounters( inDataDir + "mu_WW_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WW_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121015,runflag, outDataDir + "RD_mu_WW_CMSSW532");
      }
      if (myflag == 20121016 || myflag == -200){
         InitCounters( inDataDir + "mu_WZ_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WZ_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121016,runflag, outDataDir + "RD_mu_WZ_CMSSW532");
      }
      if (myflag == 20121017 || myflag == -200){
         InitCounters( inDataDir + "mu_ZpJ_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_ZpJ_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121017,runflag, outDataDir + "RD_mu_ZpJ_CMSSW532");
      }
      if (myflag == 20121020 || myflag == -200){
         InitCounters( inDataDir + "mu_ZZ_CMSSW532.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");
         myChain->Add(                    inDataDir + "mu_ZZ_CMSSW532.root");
         Init(myChain);Loop(  h_events, h_events_weighted,20121020,runflag, outDataDir + "RD_mu_ZZ_CMSSW532");
      }
      if (myflag == 20121021 || myflag == -200){
         InitCounters( inDataDir + "mu_WpJ_PT100_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WpJ_PT100_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121021,runflag, outDataDir + "RD_mu_WpJPt100_CMSSW532");
      }
      if (myflag == 20121022 || myflag == -200){
         InitCounters( inDataDir + "mu_W3Jets_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_W3Jets_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121022,runflag, outDataDir + "RD_mu_W3Jets_CMSSW532");
      }
      if (myflag == 20121023 || myflag == -200){
         InitCounters( inDataDir + "mu_W4Jets_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_W4Jets_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121023,runflag, outDataDir + "RD_mu_W4Jets_CMSSW532");
      }
      if (myflag == 20121024 || myflag == -200){
         InitCounters( inDataDir + "mu_ttZ_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_ttZ_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121024,runflag, outDataDir + "RD_mu_ttZ_CMSSW532");
      }
      if (myflag == 20121025 || myflag == -200){
         InitCounters( inDataDir + "mu_ttHbbMH125_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_ttHbbMH125_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121025,runflag, outDataDir + "RD_mu_ttHbbMH125_CMSSW532");
      }
      if (myflag == 20121026 || myflag == -200){
         InitCounters( inDataDir + "mu_ttHinclusivedecayMH125_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_ttHinclusivedecayMH125_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121026,runflag, outDataDir + "RD_mu_ttHinclusivedecayMH125_CMSSW532");
      }
      if (myflag == 20121027 || myflag == -200){
         InitCounters( inDataDir + "mu_ttW_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_ttW_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121027,runflag, outDataDir + "RD_mu_ttW_CMSSW532");
      }
      if (myflag == 20121028 || myflag == -200){
         InitCounters( inDataDir2 + "mu_qq_wpwma_wp_qq_wm_lvl.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add( inDataDir2 + "mu_qq_wpwma_wp_qq_wm_lvl.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121028,runflag, outDataDir + "RD_mu_qq_wpwma_wp_qq_wm_lvl");
      }
      if (myflag == 20121030 || myflag == -500){
         InitCounters( inDataDir + "mu_WGpJ_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WGpJ_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121030,runflag, outDataDir + "RD_mu_WGpJ_CMSSW532");
      }
      if (myflag == 20121029 || myflag == -500){
         InitCounters( inDataDir2 + "mu_qq_wpwma_wp_lvl_wm_qq.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add( inDataDir2 + "mu_qq_wpwma_wp_lvl_wm_qq.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121029,runflag, outDataDir + "RD_mu_qq_wpwma_wp_lvl_wm_qq");
      }
      if (myflag == 20121031 || myflag == -500){
         InitCounters( inDataDir2 + "mu_wwa_lvlva_CMSSW532.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add( inDataDir2 + "mu_wwa_lvlva_CMSSW532.root");
         Init(myChain);Loop( h_events, h_events_weighted, 20121031,runflag, outDataDir + "RD_mu_qq_wpwma_wp_lvl_wm_lvl");
      }
      if (myflag == 20121032 || myflag == -500){
         InitCounters( inDataDir2 + "mu_WAp23Jets.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");
         myChain->Add( inDataDir2 + "mu_WAp23Jets.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121032,runflag, outDataDir + "RD_mu_WGp23J_CMSSW532");
      }
      if (myflag == 20121033 || myflag == -500){
         InitCounters( inDataDir2 + "mu_TTbarAJets.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");
         myChain->Add( inDataDir2 + "mu_TTbarAJets.root");      
         Init(myChain);Loop( h_events, h_events_weighted, 20121033,runflag, outDataDir + "RD_mu_TTbarGpJets_CMSSW532");
      }

   }

}// End Function "myana"



////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
///// Function to Loop over all events in Sample:
void kanamuon_photon::Loop(TH1F* h_events, TH1F* h_events_weighted, int wda, int runflag, const char *outfilename, bool isQCD)
{
   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntries();

   /////////////////////////
   // Output Root File Here:
   char rootfn[200]; 
   if (runflag ==0 ) {sprintf(rootfn, "%s.root",outfilename);}
   else {             sprintf(rootfn, "%s-VS-%i.root",outfilename,runflag);}
   TFile fresults= TFile(rootfn,"RECREATE");

   TTree *newtree = fChain->CloneTree();

   ////////////////////////////////////////////////////////////////
   // Indices: Generated Good Event, # Jets in Event, Good isolated Photon, Good isolated Jet, Photon isolation, Dijet mass, jet four-momentum vectors:
   Int_t   ggdevt   =0,   evtNJ     =0, iPhoton12 = -1, iPhoton11 = -1;
   Int_t i11Jet1=-1, i11Jet2=-1, i11Jet3=-1, i11Jet4=-1, i11Jet5=-1, i11Jet6=-1;
   Int_t i12Jet1=-1, i12Jet2=-1, i12Jet3=-1, i12Jet4=-1, i12Jet5=-1, i12Jet6=-1;
   Float_t         Photon_dRlep[10]={99.};   //[NumPhotons]
   Float_t         JetPFCor_dRpho11[6] = {99.};   
   Float_t         JetPFCor_dRpho12[6] = {99.};   
   Float_t         c2jMass12,c2jMass11;
   TLorentzVector p4j1,p4j2,c2j;

   TBranch *branch_iPhoton12= newtree->Branch("iPhoton12",    &iPhoton12,     "iPhoton12/I");
   TBranch *branch_iPhoton11= newtree->Branch("iPhoton11",    &iPhoton11,     "iPhoton12/I");
   TBranch *branch_i11Jet1= newtree->Branch("i11Jet1",    &i11Jet1,     "i11Jet1/I");
   TBranch *branch_i11Jet2= newtree->Branch("i11Jet2",    &i11Jet2,     "i11Jet2/I");
   TBranch *branch_i11Jet3= newtree->Branch("i11Jet3",    &i11Jet3,     "i11Jet3/I");
   TBranch *branch_i11Jet4= newtree->Branch("i11Jet4",    &i11Jet4,     "i11Jet4/I");
   TBranch *branch_i11Jet5= newtree->Branch("i11Jet5",    &i11Jet5,     "i11Jet5/I");
   TBranch *branch_i11Jet6= newtree->Branch("i11Jet6",    &i11Jet6,     "i11Jet6/I");
   TBranch *branch_i12Jet1= newtree->Branch("i12Jet1",    &i12Jet1,     "i12Jet1/I");
   TBranch *branch_i12Jet2= newtree->Branch("i12Jet2",    &i12Jet2,     "i12Jet2/I");
   TBranch *branch_i12Jet3= newtree->Branch("i12Jet3",    &i12Jet3,     "i12Jet3/I");
   TBranch *branch_i12Jet4= newtree->Branch("i12Jet4",    &i12Jet4,     "i12Jet4/I");
   TBranch *branch_i12Jet5= newtree->Branch("i12Jet5",    &i12Jet5,     "i12Jet5/I");
   TBranch *branch_i12Jet6= newtree->Branch("i12Jet6",    &i12Jet6,     "i12Jet6/I");
   TBranch *branch_c2jMass11= newtree->Branch("c2jMass11",    &c2jMass11,     "c2jMass11/F");
   TBranch *branch_c2jMass12= newtree->Branch("c2jMass12",    &c2jMass12,     "c2jMass12/F");
   TBranch *branch_Photon_dRlep= newtree->Branch("Photon_dRlep",    &Photon_dRlep,     "Photon_dRlep[NumPhotons]/F");
   TBranch *branch_JetPFCor_dRpho11 = newtree->Branch("JetPFCor_dRpho11",    &JetPFCor_dRpho11,     "JetPFCor_dRpho11[6]/F");
   TBranch *branch_JetPFCor_dRpho12 = newtree->Branch("JetPFCor_dRpho12",    &JetPFCor_dRpho12,     "JetPFCor_dRpho12[6]/F");
   TBranch *branch_ggdevt= newtree->Branch("ggdevt",    &ggdevt,     "ggdevt/I");
   TBranch *branch_evtNJ = newtree->Branch("evtNJ",     &evtNJ,      "evtNJ/I");

   ////////////////////////////////////////////////////
   // Kinematic fit to muon/neutrino/jet momentum/mass:
   Float_t fit_mu_px=0,   fit_mu_py =0,   fit_mu_pz=0,   fit_mu_e=0;
   Float_t fit_nv_px=0,   fit_nv_py =0,   fit_nv_pz=0,   fit_nv_e=0;
   Float_t fit_aj_px=0,   fit_aj_py =0,   fit_aj_pz=0,   fit_aj_e=0;
   Float_t fit_bj_px=0,   fit_bj_py =0,   fit_bj_pz=0,   fit_bj_e=0;
   Float_t fit_mlvjj=0,   fit_chi2  =999;  
   Int_t   fit_NDF  =999, fit_status=999;
   Float_t fit_mlv  =0,   fit_mjj   =0;

   TBranch *branch_mu_px = newtree->Branch("fit_mu_px", &fit_mu_px,  "fit_mu_px/F");
   TBranch *branch_mu_py = newtree->Branch("fit_mu_py", &fit_mu_py,  "fit_mu_py/F");
   TBranch *branch_mu_pz = newtree->Branch("fit_mu_pz", &fit_mu_pz,  "fit_mu_pz/F");
   TBranch *branch_mu_e  = newtree->Branch("fit_mu_e",  &fit_mu_e,   "fit_mu_e/F");

   TBranch *branch_nv_px = newtree->Branch("fit_nv_px", &fit_nv_px,  "fit_nv_px/F");
   TBranch *branch_nv_py = newtree->Branch("fit_nv_py", &fit_nv_py,  "fit_nv_py/F");
   TBranch *branch_nv_pz = newtree->Branch("fit_nv_pz", &fit_nv_pz,  "fit_nv_pz/F");
   TBranch *branch_nv_e  = newtree->Branch("fit_nv_e",  &fit_nv_e,   "fit_nv_e/F");

   TBranch *branch_aj_px = newtree->Branch("fit_aj_px", &fit_aj_px,  "fit_aj_px/F");
   TBranch *branch_aj_py = newtree->Branch("fit_aj_py", &fit_aj_py,  "fit_aj_py/F");
   TBranch *branch_aj_pz = newtree->Branch("fit_aj_pz", &fit_aj_pz,  "fit_aj_pz/F");
   TBranch *branch_aj_e  = newtree->Branch("fit_aj_e",  &fit_aj_e,   "fit_aj_e/F");

   TBranch *branch_bj_px = newtree->Branch("fit_bj_px", &fit_bj_px,  "fit_bj_px/F");
   TBranch *branch_bj_py = newtree->Branch("fit_bj_py", &fit_bj_py,  "fit_bj_py/F");
   TBranch *branch_bj_pz = newtree->Branch("fit_bj_pz", &fit_bj_pz,  "fit_bj_pz/F");
   TBranch *branch_bj_e  = newtree->Branch("fit_bj_e",  &fit_bj_e,   "fit_bj_e/F");

   TBranch *branch_mlvjj = newtree->Branch("fit_mlvjj", &fit_mlvjj,  "fit_mlvjj/F");
   TBranch *branch_mlv   = newtree->Branch("fit_mlv",   &fit_mlv,    "fit_mlv/F");
   TBranch *branch_mjj   = newtree->Branch("fit_mjj",   &fit_mjj,    "fit_mjj/F");
   TBranch *branch_chi2  = newtree->Branch("fit_chi2",  &fit_chi2,   "fit_chi2/F");
   TBranch *branch_NDF   = newtree->Branch("fit_NDF",   &fit_NDF,    "fit_NDF/I");
   TBranch *branch_status= newtree->Branch("fit_status",&fit_status, "fit_status/I");

   ///////////////////////////////////////////////////////////////////
   // Decay Angles, four-body/three-body/two-body mass/pt, pt:pt/pt:m ratios:
   Float_t ang_ha   = 999, ang_hb = 999, ang_hs = 999, ang_phi = 999, ang_phia = 999, ang_phib = 999, ang_lva = 999, ang_jja = 999;
   Float_t masslvjj =-999, ptlvjj =-999,  ylvjj = -999,philvjj = -999,masslvjja =-999, ptlvjja =-999, masslva =-999, masslv=-999;
   Float_t rat_mpt_wwa =-999, rat_ptpt_amu =-999, rat_ptpt_aj1 =-999, rat_ptpt_aj2 =-999, rat_ptpt_av =-999;
   TBranch * branch_mpt_wwa = newtree->Branch("rat_mpt_wwa",  &rat_mpt_wwa,  "rat_mpt_wwa/F");
   TBranch * branch_ptpt_amu = newtree->Branch("rat_ptpt_amu",  &rat_ptpt_amu,  "rat_ptpt_amu/F");
   TBranch * branch_ptpt_aj1 = newtree->Branch("rat_ptpt_aj1",  &rat_ptpt_aj1,  "rat_ptpt_aj1/F");
   TBranch * branch_ptpt_aj2 = newtree->Branch("rat_ptpt_aj2",  &rat_ptpt_aj2,  "rat_ptpt_aj2/F");
   TBranch * branch_ptpt_av = newtree->Branch("rat_ptpt_av",  &rat_ptpt_av,  "rat_ptpt_av/F");
   TBranch * branch_ha   =  newtree->Branch("ang_ha",   &ang_ha,    "anig_ha/F");
   TBranch * branch_hb   =  newtree->Branch("ang_hb",   &ang_hb,    "ang_hb/F");
   TBranch * branch_hs   =  newtree->Branch("ang_hs",   &ang_hs,    "ang_hs/F");
   TBranch * branch_phi  =  newtree->Branch("ang_phi",  &ang_phi,   "ang_phi/F");
   TBranch * branch_phia =  newtree->Branch("ang_phia", &ang_phia,  "ang_phia/F");
   TBranch * branch_phib =  newtree->Branch("ang_phib", &ang_phib,  "ang_phib/F");
   TBranch * branch_lva = newtree->Branch("ang_lva", &ang_lva, "ang_lva/F");
   TBranch * branch_jja = newtree->Branch("ang_jja", &ang_jja, "ang_jja/F");
   TBranch * branch_orgm =  newtree->Branch("masslvjj", &masslvjj,  "masslvjj/F");
   TBranch * branch_orgma =  newtree->Branch("masslvjja", &masslvjja,  "masslvjja/F");
   TBranch * branch_orgmlva =  newtree->Branch("masslva", &masslva,  "masslva/F");
   TBranch * branch_orgmlv = newtree->Branch("masslv", &masslv, "masslv/F");
   TBranch * branch_orgpt=  newtree->Branch("ptlvjj",   &ptlvjj,    "ptlvjj/F");
   TBranch * branch_orgpta = newtree->Branch("ptlvjja", &ptlvjja, "ptlvjja/F");
   TBranch * branch_orgy =  newtree->Branch("ylvjj",    &ylvjj,     "ylvjj/F");
   TBranch * branch_orgph=  newtree->Branch("philvjj",  &philvjj,   "philvjj/F");

   //////////////
   // MVA output:
   Float_t mva2jWWAmu = 999;
   TBranch * branch_2jWWAmu   =  newtree->Branch("mva2jWWAmu",   &mva2jWWAmu,    "mva2jWWAmu/F");

   //////////////////////////////
   // Efficiencies/Pilup weights:
   Float_t effwt = 1.0, puwt = 1.0, puwt_up = 1.0, puwt_down = 1.0;
   TBranch * branch_effwt          =  newtree->Branch("effwt",       &effwt,        "effwt/F");
   TBranch * branch_puwt           =  newtree->Branch("puwt",        &puwt,         "puwt/F");
   TBranch * branch_puwt_up        =  newtree->Branch("puwt_up",     &puwt_up,      "puwt_up/F");
   TBranch * branch_puwt_down      =  newtree->Branch("puwt_down",   &puwt_down,    "puwt_down/F");

   ///////////////
   // Quark-Gluon:
   Float_t qgld_Spring11[6]={-1,-1,-1,-1,-1,-1}; 
   Float_t qgld_Summer11[6]={-1,-1,-1,-1,-1,-1};
   Float_t qgld_Summer11CHS[6]={-1,-1,-1,-1,-1,-1};

   TBranch * branch_qgld_Spring11     =  newtree->Branch("qgld_Spring11",     qgld_Spring11,        "qgld_Spring11[6]/F");
   TBranch * branch_qgld_Summer11     =  newtree->Branch("qgld_Summer11",     qgld_Summer11,        "qgld_Summer11[6]/F");
   TBranch * branch_qgld_Summer11CHS  =  newtree->Branch("qgld_Summer11CHS",  qgld_Summer11CHS,     "qgld_Summer11CHS[6]/F");

   ////////////////////
   // For MVA analysis:
   const char* inputVarsPho[] = { "W_pt", "sqrt((JetPFCor_Eta[i11Jet1]-JetPFCor_Eta[i11Jet2])**2+(abs(abs(abs(JetPFCor_Phi[i11Jet1]-JetPFCor_Phi[i11Jet2])-TMath::Pi())-TMath::Pi()))**2)","JetPFCor_Pt[i11Jet1]", "JetPFCor_Pt[i11Jet2]", "ptlvjja" , "c2jMass11"};
   std::vector<std::string> inputVarsMVApho;
   for (int i=0; i<6; ++i) inputVarsMVApho.push_back( inputVarsPho[i] );
   ReadMVA2jWWAmu mvaReader2jWWAmu( inputVarsMVApho );

   /////////////////////////////
   // For Efficiency Correction:
   EffTableLoader muIDEff(            fDir + "scaleFactor-Run2012ABC-RecoToIso.txt");
   EffTableLoader muHLTEff(           fDir + "efficiency-Run2012ABC-IsoToIsoMuHLT.txt");

   ////////////////////////
   // Pile up Re-weighting:
   // S7 MC PU True profile - hardcoded, wow
   // https://twiki.cern.ch/twiki/bin/viewauth/CMS/PileupMCReweightingUtilities
   TFile *dataFile_      = new TFile( "Data190389-206102_PileupHistogram.root" );
   TH1F* PU_intended = new TH1F(  *(static_cast<TH1F*>(dataFile_->Get( "pileup" )->Clone() )) );
   TH1F* PU_generated = new TH1F("PU_generated","Generated pileup distribution (i.e., MC)",60,0.,60);
   Double_t Summer2012[60] = {
      //Pile Up For S10
      2.560E-06,
      5.239E-06,
      1.420E-05,
      5.005E-05,
      1.001E-04,
      2.705E-04,
      1.999E-03,
      6.097E-03,
      1.046E-02,
      1.383E-02,
      1.685E-02,
      2.055E-02,
      2.572E-02,
      3.262E-02,
      4.121E-02,
      4.977E-02,
      5.539E-02,
      5.725E-02,
      5.607E-02,
      5.312E-02,
      5.008E-02,
      4.763E-02,
      4.558E-02,
      4.363E-02,
      4.159E-02,
      3.933E-02,
      3.681E-02,
      3.406E-02,
      3.116E-02,
      2.818E-02,
      2.519E-02,
      2.226E-02,
      1.946E-02,
      1.682E-02,
      1.437E-02,
      1.215E-02,
      1.016E-02,
      8.400E-03,
      6.873E-03,
      5.564E-03,
      4.457E-03,
      3.533E-03,
      2.772E-03,
      2.154E-03,
      1.656E-03,
      1.261E-03,
      9.513E-04,
      7.107E-04,
      5.259E-04,
      3.856E-04,
      2.801E-04,
      2.017E-04,
      1.439E-04,
      1.017E-04,
      7.126E-05,
      4.948E-05,
      3.405E-05,
      2.322E-05,
      1.570E-05,
      5.005E-06
   };   
   for (int i=1;i<=60;i++)  {
      PU_generated->SetBinContent(i,Summer2012[i-1]);
   }
   PU_intended->Scale( 1.0/ PU_intended->Integral() );
   PU_generated->Scale( 1.0/ PU_generated->Integral() );

   TH1F *weights_ = new TH1F( *(PU_intended)) ;

   weights_->Divide(PU_generated);

   ///////////////////
   // Parameter Setup:
   const double Jpt = 30;    // Jet pt threshold

   ////////////////////////
   // Loop over all events:
   Long64_t nbytes = 0, nb = 0;

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      nb = newtree->GetEntry(jentry);   nbytes += nb;

      ////////////////////////////////
      // Save variable initialization:
      ggdevt    = 0;
      evtNJ     = 0;

      fit_mu_px = 0; fit_mu_py = 0; fit_mu_pz = 0;  fit_mu_e  = 0; 
      fit_nv_px = 0; fit_nv_py = 0; fit_nv_pz = 0;  fit_nv_e  = 0; 
      fit_aj_px = 0; fit_aj_py = 0; fit_aj_pz = 0;  fit_aj_e  = 0; 
      fit_bj_px = 0; fit_bj_py = 0; fit_bj_pz = 0;  fit_bj_e  = 0; 
      fit_mlvjj = 0; fit_chi2  =999;fit_NDF   =999; fit_status=999;
      fit_mlv   = 0; fit_mjj   = 0;

      ang_ha  = 999; ang_hb    =999;ang_hs    =999; ang_phi   =999; 
      ang_phia= 999; ang_phib  =999; ang_lva = 999; ang_jja = 999;
      masslvjj=-999; masslvjja =-999; masslv=-999; masslva =-999; ptlvjj    =-999; ptlvjja = -999; ylvjj   =-999;philvjj   =-999;
      rat_mpt_wwa =-999; rat_ptpt_amu =-999; rat_ptpt_aj1 =-999; rat_ptpt_aj2 =-999; rat_ptpt_av =-999;

      mva2jWWAmu = 999;

      effwt = 1.0; puwt = 1.0; puwt_up = 1.0; puwt_down = 1.0;
      qgld_Spring11[0]= -1;       qgld_Spring11[1]= -1;       qgld_Spring11[2]= -1;       qgld_Spring11[3]= -1;       qgld_Spring11[4]= -1;       qgld_Spring11[5]= -1;
      qgld_Summer11[0]= -1;       qgld_Summer11[1]= -1;       qgld_Summer11[2]= -1;       qgld_Summer11[3]= -1;       qgld_Summer11[4]= -1;       qgld_Summer11[5]= -1;
      qgld_Summer11CHS[0]= -1;    qgld_Summer11CHS[1]= -1;    qgld_Summer11CHS[2]= -1;    qgld_Summer11CHS[3]= -1;    qgld_Summer11CHS[4]= -1;    qgld_Summer11CHS[5]= -1;

      ///////////////
      // Photon loop:
      iPhoton12=-1;iPhoton11=-1;
      for(int ipho=NumPhotons-1; ipho>=0;ipho--){
         Photon_dRlep[ipho]=dRCalc(Photon_Eta[ipho],Photon_Phi[ipho],W_muon_eta,W_muon_phi);
         if(Photon_Id2012[ipho]>0&&Photon_dRlep[ipho]>0.5)iPhoton12=ipho;
         if(Photon_Id2011[ipho]>0&&Photon_dRlep[ipho]>0.5)iPhoton11=ipho;
      }

      ////////////
      // Jet Loop:
      c2jMass11=-1.;c2jMass12=-1.;
      double jess=-1,dijetpt=-1;
      i11Jet1=-1;i11Jet2=-1;i12Jet1=-1;i12Jet2=-1;i11Jet3=-1;i12Jet3=-1;i11Jet4=-1;i12Jet4=-1;i11Jet5=-1;i12Jet5=-1;i11Jet6=-1;i12Jet6=-1;

      if(iPhoton11>=0 && iPhoton12>=0){

         for(int ij=0; ij<10;ij++){
            if(iPhoton11>-1) JetPFCor_dRpho11[ij]=dRCalc(Photon_Eta[iPhoton11],Photon_Phi[iPhoton11],JetPFCor_Eta[ij],JetPFCor_Phi[ij]);
            if(iPhoton12>-1) JetPFCor_dRpho12[ij]=dRCalc(Photon_Eta[iPhoton12],Photon_Phi[iPhoton12],JetPFCor_Eta[ij],JetPFCor_Phi[ij]);
         }

         ///////////////
         ///// First Jet
         for(int ij=9; ij>=0;ij--){
            if(JetPFCor_Pt[ij]>30&&JetPFCor_dRpho11[ij]>0.5) i11Jet1=ij;
            if(JetPFCor_Pt[ij]>30&&JetPFCor_dRpho12[ij]>0.5) i12Jet1=ij;
         }

         ////////////////
         ///// Second Jet
         for(int ij=9; ij>=0;ij--){
            if(JetPFCor_Pt[ij]>30.&&JetPFCor_dRpho11[ij]>0.5&&i11Jet1>-1&&ij>i11Jet1) i11Jet2=ij;
            if(JetPFCor_Pt[ij]>30.&&JetPFCor_dRpho12[ij]>0.5&&i12Jet1>-1&&ij>i12Jet1) i12Jet2=ij;
         }

         ///////////////
         ///// Third Jet
         for(int ij=9; ij>=0;ij--){
            if(JetPFCor_Pt[ij]>30.&&JetPFCor_dRpho11[ij]>0.5&&i11Jet2>-1&&ij>i11Jet2) i11Jet3=ij;
            if(JetPFCor_Pt[ij]>30.&&JetPFCor_dRpho12[ij]>0.5&&i12Jet2>-1&&ij>i12Jet2) i12Jet3=ij;
         }

         ////////////////
         ///// Fourth Jet
         for(int ij=9; ij>=0;ij--){
            if(JetPFCor_Pt[ij]>30.&&JetPFCor_dRpho11[ij]>0.5&&i11Jet3>-1&&ij>i11Jet3) i11Jet4=ij;
            if(JetPFCor_Pt[ij]>30.&&JetPFCor_dRpho12[ij]>0.5&&i12Jet3>-1&&ij>i12Jet3) i12Jet4=ij;
         }

         ///////////////
         ///// Fifth Jet
         for(int ij=9; ij>=0;ij--){
            if(JetPFCor_Pt[ij]>30.&&JetPFCor_dRpho11[ij]>0.5&&i11Jet4>-1&&ij>i11Jet4) i11Jet5=ij;
            if(JetPFCor_Pt[ij]>30.&&JetPFCor_dRpho12[ij]>0.5&&i12Jet4>-1&&ij>i12Jet4) i12Jet5=ij;
         }

         ///////////////
         ///// Sixth Jet
         for(int ij=9; ij>=0;ij--){
            if(JetPFCor_Pt[ij]>30.&&JetPFCor_dRpho11[ij]>0.5&&i11Jet5>-1&&ij>i11Jet5) i11Jet6=ij;
            if(JetPFCor_Pt[ij]>30.&&JetPFCor_dRpho12[ij]>0.5&&i12Jet5>-1&&ij>i12Jet5) i12Jet6=ij;
         }

         ////////////////////////////
         // Cut variable definitions:
         if( i11Jet2>-1 ) {

            jess    = 1.00; // control the jet energy scale
            dijetpt = sqrt(JetPFCor_Pt[/*0*/i11Jet1]*JetPFCor_Pt[/*0*/i11Jet1]+
               JetPFCor_Pt[/*1*/i11Jet2]*JetPFCor_Pt[/*1*/i11Jet2]+
               2*JetPFCor_Pt[/*0*/i11Jet1]*JetPFCor_Pt[/*1*/i11Jet2]*cos(JetPFCor_Phi[/*0*/i11Jet1]-JetPFCor_Phi[/*1*/i11Jet2]));

            p4j1.SetPxPyPzE( JetPFCor_Px[i11Jet1], JetPFCor_Py[i11Jet1], JetPFCor_Pz[i11Jet1], JetPFCor_E[i11Jet1] );
            p4j2.SetPxPyPzE( JetPFCor_Px[i11Jet2], JetPFCor_Py[i11Jet2], JetPFCor_Pz[i11Jet2], JetPFCor_E[i11Jet2] );
            c2j =  p4j1 + p4j2;
            c2jMass11 =  c2j.M();

         }

         if( i12Jet2>-1 ) {
            p4j1.SetPxPyPzE( JetPFCor_Px[i12Jet1], JetPFCor_Py[i12Jet1], JetPFCor_Pz[i12Jet1], JetPFCor_E[i12Jet1] );
            p4j2.SetPxPyPzE( JetPFCor_Px[i12Jet2], JetPFCor_Py[i12Jet2], JetPFCor_Pz[i12Jet2], JetPFCor_E[i12Jet2] );
            c2j =  p4j1 + p4j2;
            c2jMass12 =  c2j.M();
         }

      }


      ////////////////////////
      // Calculate efficiency:
      effwt =
         muIDEff.GetEfficiency(W_muon_pt, W_muon_eta) *
         muHLTEff.GetEfficiency(W_muon_pt, W_muon_eta);

         //////////////////////////////////////////////////////////
         // Add Photon ID efficiency scale factor (2011 Medium ID):
         if(Photon_Et[iPhoton11]<20.){

            if(fabs(Photon_Eta[iPhoton11])<1.4442){
               effwt = 1.0022*effwt;
            }else{
               effwt = 1.0189*effwt;
            }

         }else if(Photon_Et[iPhoton11]>20. && Photon_Et[iPhoton11]<30.){

            if(fabs(Photon_Eta[iPhoton11])<0.8){
               effwt = 0.9854*effwt;
            }else if(fabs(Photon_Eta[iPhoton11])>0.8 && fabs(Photon_Eta[iPhoton11])<1.4442){
               effwt = 0.9876*effwt;
            }else if(fabs(Photon_Eta[iPhoton11])>1.4442 && fabs(Photon_Eta[iPhoton11])<2.0){
               effwt = 1.0155*effwt;
            }else{
               effwt = 1.0056*effwt;
            }

         }else if(Photon_Et[iPhoton11]>30. && Photon_Et[iPhoton11]<40.){

            if(fabs(Photon_Eta[iPhoton11])<0.8){
               effwt = 0.9834*effwt;
            }else if(fabs(Photon_Eta[iPhoton11])>0.8 && fabs(Photon_Eta[iPhoton11])<1.4442){
               effwt = 0.9932*effwt;
            }else if(fabs(Photon_Eta[iPhoton11])>1.4442 && fabs(Photon_Eta[iPhoton11])<2.0){
               effwt = 1.0048*effwt;
            }else{
               effwt = 1.0108*effwt;
            }

         }else if(Photon_Et[iPhoton11]>40. && Photon_Et[iPhoton11]<50.){

            if(fabs(Photon_Eta[iPhoton11])<0.8){
               effwt = 0.9853*effwt;
            }else if(fabs(Photon_Eta[iPhoton11])>0.8 && fabs(Photon_Eta[iPhoton11])<1.4442){
               effwt = 0.9914*effwt;
            }else if(fabs(Photon_Eta[iPhoton11])>1.4442 && fabs(Photon_Eta[iPhoton11])<2.0){
               effwt = 1.0013*effwt;
            }else{
               effwt = 1.0057*effwt;
            }

         }else{

            if(fabs(Photon_Eta[iPhoton11])<0.8){
               effwt = 0.9847*effwt;
            }else if(fabs(Photon_Eta[iPhoton11])>0.8 && fabs(Photon_Eta[iPhoton11])<1.4442){
               effwt = 0.9941*effwt;
            }else if(fabs(Photon_Eta[iPhoton11])>1.4442 && fabs(Photon_Eta[iPhoton11])<2.0){
               effwt = 1.0033*effwt;
            }else{
               effwt = 1.0106*effwt;
            }

         }

      ////////////////////////
      // Pile up Re-weighting:
      if (wda>20120999) {
         puwt      =    weights_->GetBinContent(int(event_mcPU_trueInteractions+0.01)+1);
         puwt_up   = puwt;
         puwt_down = puwt;
      } else {effwt=1.0;puwt=1.0;puwt_up=1.0;puwt_down=1.0;} // if data, always put 1 as the weighting factor

      ///////////////////////////////////////////////////
      // Good Event Selection Requirement for all events:
      int istep = 8; //starting selection step after preselection
      bool  isgengdevt = 0;

      if( i11Jet2>0){

         if (JetPFCor_Pt[/*0*/i11Jet1]>Jpt 
          && JetPFCor_Pt[/*1*/i11Jet2]>Jpt 
          && W_mt>30. //Move to MVA MET Later
          && W_muon_pt>25.
          && fabs(W_muon_dz000)<0.02
          && fabs(W_muon_dzPV)<0.5
          && fabs(W_muon_eta)<2.1 //Fix the Muon Eta Range to 2.1
            ) {isgengdevt = 1;}

         if (JetPFCor_Pt[/*0*/i11Jet1]>Jpt ) {
            h_events          -> Fill ( istep ); 
            h_events_weighted -> Fill ( istep, effwt*puwt ); 
            istep++;

            if ( JetPFCor_Pt[/*1*/i11Jet2]>Jpt ) {
               h_events          -> Fill ( istep ); 
               h_events_weighted -> Fill ( istep, effwt*puwt ); 
               istep++;

               if ( W_mt>30. ) {
                  h_events          -> Fill ( istep ); 
                  h_events_weighted -> Fill ( istep, effwt*puwt ); 
                  istep++;

                  if ( W_muon_pt>30. 
                        && fabs(W_muon_dz000)<0.02
                        && fabs(W_muon_dzPV)<0.5
                        && fabs(W_muon_eta)<2.1
                     ) { 
                     h_events          -> Fill ( istep ); 
                     h_events_weighted -> Fill ( istep, effwt*puwt ); 
                     istep++;
                  }
               }
            }
         }
      }

      //////////////////////////////////////////////////////////
      // Event Selection Requirement for Standard vs QCD events:
      if ( !isQCD ) {
         //keep muons with iso<0.20(loose=0.20;tight=0.12) && event_met_pfmet>25.
         if ( !(event_met_pfmet>25.0) ) {isgengdevt=0;}
      } else {
         //keep muons with iso>0.20 (loose=0.20;tight=0.12)
         //if ( !(muoniso>0.12)         ) {isgengdevt=0;}
      }


      ///////////////////////////
      // Fill lepton information:
      TLorentzVector  mup, nvp;
      mup.SetPtEtaPhiE(W_muon_pt, W_muon_eta, W_muon_phi, W_muon_e);
      nvp.SetPxPyPzE(event_met_pfmet * cos(event_met_pfmetPhi), event_met_pfmet * sin(event_met_pfmetPhi), W_pzNu1, sqrt(event_met_pfmet*event_met_pfmet + W_pzNu1*W_pzNu1));

      TLorentzVector b_metpt;
      b_metpt.SetPxPyPzE(event_met_pfmet * cos(event_met_pfmetPhi), event_met_pfmet * sin(event_met_pfmetPhi), 0, sqrt(event_met_pfmet*event_met_pfmet) );

      METzCalculator b_metpz;
      b_metpz.SetMET(b_metpt);
      b_metpz.SetLepton(mup);
      b_metpz.SetLeptonType("muon");
      double b_nvpz = b_metpz.Calculate(); // Default one

      TLorentzVector b_nvp;
      b_nvp.SetPxPyPzE(b_metpt.Px(), b_metpt.Py(), b_nvpz, sqrt(b_metpt.Px()*b_metpt.Px() + b_metpt.Py()*b_metpt.Py() + b_nvpz*b_nvpz) );

      if (b_metpz.IsComplex()) {// if this is a complix, change MET

         double nu_pt1 = b_metpz.getPtneutrino(1);
         double nu_pt2 = b_metpz.getPtneutrino(2);

         TLorentzVector tmpp1; 
         tmpp1.SetPxPyPzE(nu_pt1 * cos(event_met_pfmetPhi), nu_pt1 * sin(event_met_pfmetPhi), b_nvpz, sqrt(nu_pt1*nu_pt1 + b_nvpz*b_nvpz) );

         TLorentzVector tmpp2; 
         tmpp2.SetPxPyPzE(nu_pt2 * cos(event_met_pfmetPhi), nu_pt2 * sin(event_met_pfmetPhi), b_nvpz, sqrt(nu_pt2*nu_pt2 + b_nvpz*b_nvpz) );
         b_nvp = tmpp1;

         if ( fabs((mup+tmpp1).M()-80.4) > fabs((mup+tmpp2).M()-80.4) )	{b_nvp = tmpp2;}

      }

      ///////////////////////
      // 2 jet event for Mjj:
      if (isgengdevt 
       && fabs(JetPFCor_Eta[i11Jet1]-JetPFCor_Eta[i11Jet2])<1.5
         ){ 

         h_events -> Fill ( istep );  
         h_events_weighted -> Fill ( istep, effwt*puwt );  
         istep++; 

         if ( fabs(JetPFCor_dphiMET[i11Jet1])>0.4 ) { 

            h_events          -> Fill ( istep );  
            h_events_weighted -> Fill ( istep, effwt*puwt );  
            istep++; 

            if ( dijetpt>40.){ 

               h_events          -> Fill ( istep );  
               h_events_weighted -> Fill ( istep, effwt*puwt );  
               istep++; 

               if ( JetPFCor_Pt[i11Jet2] > Jpt && JetPFCor_Pt[i11Jet3] < Jpt ) {evtNJ = 2;} 
               if ( JetPFCor_Pt[i11Jet3] > Jpt && JetPFCor_Pt[i11Jet4] < Jpt ) {evtNJ = 3;} 

            } 
         } 
      } 

      /////////////////////////////
      // 2 and 3 jet event for Hww:
      if (isgengdevt) { ggdevt = 4;// Do the kinematic fit for all event!!!

         if ( JetPFCor_Pt[i11Jet2] > Jpt && JetPFCor_Pt[i11Jet3] < Jpt ) {ggdevt = 2;}
         if ( JetPFCor_Pt[i11Jet3] > Jpt && JetPFCor_Pt[i11Jet4] < Jpt ) {ggdevt = 3;}

         int Aj = 0, Bj = 1; Aj = i11Jet1, Bj = i11Jet2;
         TLorentzVector ajp, bjp, ap; 

         ajp.SetPtEtaPhiE(jess * JetPFCor_Pt[Aj], JetPFCor_Eta[Aj], JetPFCor_Phi[Aj], jess * JetPFCor_E[Aj]  );
         bjp.SetPtEtaPhiE(jess * JetPFCor_Pt[Bj], JetPFCor_Eta[Bj], JetPFCor_Phi[Bj], jess * JetPFCor_E[Bj]  );
         ap.SetPtEtaPhiE(Photon_Et[iPhoton11], Photon_Eta[iPhoton11], Photon_Phi[iPhoton11], Photon_E[iPhoton11]  );

         ////////////////////
         // Do kinematic fit:
         TLorentzVector fit_mup(0,0,0,0), fit_nvp(0,0,0,0), fit_ajp(0,0,0,0), fit_bjp(0,0,0,0) ;
         doKinematicFit( 1, mup, b_nvp, ajp, bjp,  fit_mup, fit_nvp, fit_ajp, fit_bjp, fit_chi2, fit_NDF, fit_status);
         fit_mu_px = fit_mup.Px(); fit_mu_py = fit_mup.Py(); fit_mu_pz = fit_mup.Pz(); fit_mu_e = fit_mup.E(); 
         fit_nv_px = fit_nvp.Px(); fit_nv_py = fit_nvp.Py(); fit_nv_pz = fit_nvp.Pz(); fit_nv_e = fit_nvp.E(); 
         fit_aj_px = fit_ajp.Px(); fit_aj_py = fit_ajp.Py(); fit_aj_pz = fit_ajp.Pz(); fit_aj_e = fit_ajp.E(); 
         fit_bj_px = fit_bjp.Px(); fit_bj_py = fit_bjp.Py(); fit_bj_pz = fit_bjp.Pz(); fit_bj_e = fit_bjp.E(); 
         fit_mlvjj = (fit_mup+fit_nvp+fit_ajp+fit_bjp).M();
         fit_mlv   = (fit_mup+fit_nvp).M();
         fit_mjj   = (fit_ajp+fit_bjp).M(); 

         ////////////////////////
         // Create distributions:
         masslvjj = (mup+b_nvp+ajp+bjp).M();
         masslvjja = (mup+b_nvp+ajp+bjp+ap).M();
         masslva = (mup+b_nvp+ap).M();
         masslv = (mup+b_nvp).M();

         ptlvjj   = (mup+b_nvp+ajp+bjp).Pt();
         ptlvjja  = (mup+b_nvp+ajp+bjp+ap).Pt();

         ylvjj    = (mup+b_nvp+ajp+bjp).Rapidity();
         philvjj  = (mup+b_nvp+ajp+bjp).Phi();

         rat_mpt_wwa = masslvjja/ptlvjja;
         rat_ptpt_amu = ap.Pt()/mup.Pt();
         rat_ptpt_av = ap.Pt()/b_nvp.Pt();
         rat_ptpt_aj1 = ap.Pt()/ajp.Pt();
         rat_ptpt_aj2 = ap.Pt()/bjp.Pt();

         double a_costheta1, a_costheta2, a_phi, a_costhetastar, a_phistar1, a_phistar2;
         double cos_Wlv_a_phi3, cos_Wjj_a_phi3;

         if (W_muon_charge < 0){
            calculateAngles(mup, b_nvp, ajp, bjp, a_costheta1, a_costheta2, a_phi, a_costhetastar, a_phistar1, a_phistar2);
         }
         else{
            calculateAngles(b_nvp, mup, ajp, bjp, a_costheta1, a_costheta2, a_phi, a_costhetastar, a_phistar1, a_phistar2);
         }

         gammaCalcAngles(ap, mup, b_nvp, cos_Wlv_a_phi3);
         gammaCalcAngles(ap, ajp, bjp, cos_Wjj_a_phi3);

         ang_ha = a_costheta1; ang_hb = fabs(a_costheta2); ang_hs = a_costhetastar;  ang_phi = a_phi; ang_phia = a_phistar1; ang_phib = a_phistar2;
         ang_lva = cos_Wlv_a_phi3; ang_jja = cos_Wjj_a_phi3;

         float dRjj=0.;
         if(i11Jet1>-1&&i11Jet2>-1){
           dRjj=fabs(fabs(fabs(JetPFCor_Phi[i11Jet1]-JetPFCor_Phi[i11Jet2])-TMath::Pi())-TMath::Pi());
           dRjj*=dRjj;
           dRjj+=(JetPFCor_Eta[i11Jet1]-JetPFCor_Eta[i11Jet2])*(JetPFCor_Eta[i11Jet1]-JetPFCor_Eta[i11Jet2]);
         }

         ///////////////////////////////
         // Fill the trained MVA output:
         std::vector<double> mvaInputValPho;
         mvaInputValPho.push_back( W_pt );
         mvaInputValPho.push_back( sqrt(dRjj) );
         if(i11Jet1>-1){
           mvaInputValPho.push_back( JetPFCor_Pt[i11Jet1] );
         }else{ mvaInputValPho.push_back(0.);}
         if(i11Jet2>-1){
           mvaInputValPho.push_back( JetPFCor_Pt[i11Jet2] );
         }else{ mvaInputValPho.push_back(0.);}
         mvaInputValPho.push_back(ptlvjja);
         mvaInputValPho.push_back(c2jMass11);
         mva2jWWAmu = (float) mvaReader2jWWAmu.GetMvaValue( mvaInputValPho );

      }

      /////////////////
      // Fill Branches:
      branch_ggdevt->Fill();
      branch_evtNJ ->Fill();

      branch_iPhoton12->Fill();
      branch_iPhoton11->Fill();
      branch_i11Jet1->Fill();
      branch_i11Jet2->Fill();
      branch_i11Jet3->Fill();
      branch_i11Jet4->Fill();
      branch_i11Jet5->Fill();
      branch_i11Jet6->Fill();
      branch_i12Jet1->Fill();
      branch_i12Jet2->Fill();
      branch_i12Jet3->Fill();
      branch_i12Jet4->Fill();
      branch_i12Jet5->Fill();
      branch_i12Jet6->Fill();
      branch_c2jMass11->Fill();
      branch_c2jMass12->Fill();

      branch_Photon_dRlep->Fill();
      branch_JetPFCor_dRpho11->Fill();
      branch_JetPFCor_dRpho12->Fill();

      branch_mu_px->Fill();
      branch_mu_py->Fill();
      branch_mu_pz->Fill();
      branch_mu_e ->Fill();

      branch_nv_px->Fill();
      branch_nv_py->Fill();
      branch_nv_pz->Fill();
      branch_nv_e ->Fill();

      branch_aj_px->Fill();
      branch_aj_py->Fill();
      branch_aj_pz->Fill();
      branch_aj_e ->Fill();

      branch_bj_px->Fill();
      branch_bj_py->Fill();
      branch_bj_pz->Fill();
      branch_bj_e ->Fill();

      branch_mlvjj->Fill();
      branch_mlv  ->Fill();
      branch_mjj  ->Fill();
      branch_chi2 ->Fill();
      branch_NDF  ->Fill();
      branch_status->Fill();

      branch_ha->Fill();   
      branch_hb->Fill();   
      branch_hs->Fill();  
      branch_phi->Fill(); 
      branch_phia->Fill();
      branch_phib->Fill();
      branch_lva->Fill();
      branch_jja->Fill();
      branch_orgm->Fill();
      branch_orgma->Fill();
      branch_orgmlva->Fill();
      branch_orgmlv->Fill();
      branch_orgpt->Fill();
      branch_orgpta->Fill();
      branch_orgy->Fill();
      branch_orgph->Fill();
      branch_mpt_wwa->Fill();
      branch_ptpt_amu->Fill();
      branch_ptpt_av->Fill();
      branch_ptpt_aj1->Fill();
      branch_ptpt_aj2->Fill();

      branch_2jWWAmu->Fill();

      branch_effwt->Fill();
      branch_puwt->Fill();
      branch_puwt_up->Fill();
      branch_puwt_down->Fill();

      branch_qgld_Spring11->Fill();
      branch_qgld_Summer11->Fill();
      branch_qgld_Summer11CHS->Fill();

   } // end event loop

   fresults.cd();
   newtree->Write("WJet",TObject::kOverwrite);
   h_events->Write();
   h_events_weighted->Write();

   delete newtree;
   fresults.Close();
   std::cout <<  wda << " Finish :: " << outfilename << "    "<< nentries  << std::endl;

}// End Function "Loop"



////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
///// Function to get angle separation in Phi:
double kanamuon_photon::getDeltaPhi(double phi1, double phi2  )
{
   const double PI = 3.14159265;
   double result = phi1 - phi2;

   if(result > PI)
   {result = result - 2 * PI;}

   if(result <= (-1 * PI))
   {result = result + 2 * PI;}

   result = TMath::Abs(result);
   return result;

}// End Function "getDeltaPhi"



////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
///// Function to do Kinematical fit over distributions:
bool kanamuon_photon::doKinematicFit(Int_t                 fflage,
      const TLorentzVector     mup, 
      const TLorentzVector     nvp, 
      const TLorentzVector     ajp, 
      const TLorentzVector     bjp, 
      TLorentzVector     & fit_mup, 
      TLorentzVector     & fit_nvp,
      TLorentzVector     & fit_ajp, 
      TLorentzVector     & fit_bjp, 
      Float_t            & fit_chi2,
      Int_t              & fit_NDF, 
      Int_t              & fit_status)
{

   bool OK                     = false;
   Resolution* resolution      = new Resolution();

   TMatrixD m1(3,3);
   TMatrixD m2(3,3);
   TMatrixD m3(3,3);
   TMatrixD m4(3,3);
   m1.Zero();
   m2.Zero();
   m3.Zero();
   m4.Zero();

   double etRes, etaRes, phiRes;
   // lepton resolution
   const std::string& leptonName = "muon";  const TLorentzVector lepton   = mup;
   if(leptonName == "electron") {
      OK = resolution->electronResolution(lepton.Et(), lepton.Eta(), etRes, etaRes, phiRes);
      if(!OK) return OK;
   } else {
      OK = resolution->muonResolution(    lepton.Et(), lepton.Eta(), etRes, etaRes, phiRes);
      if(!OK) return OK;
   }
   m1(0,0) = resolution->square(etRes);
   m1(1,1) = resolution->square(etaRes);
   m1(2,2) = resolution->square(phiRes);
   // MET resolution
   OK = resolution->PFMETResolution(     nvp.Et(),            etRes, etaRes, phiRes);
   if(!OK) return OK;
   m2(0,0) = resolution->square(etRes);
   m2(1,1) = 0.01; // resolution->square(etaRes)
   m2(2,2) = resolution->square(phiRes);
   // Leading Jet resolution
   OK = resolution->udscPFJetResolution( ajp.Et(), ajp.Eta(), etRes, etaRes, phiRes);
   if(!OK) return OK;
   m3(0,0) = resolution->square(etRes);
   m3(1,1) = resolution->square(etaRes);
   m3(2,2) = resolution->square(phiRes);
   // Leading Jet resolution
   OK = resolution->udscPFJetResolution( bjp.Et(), bjp.Eta(), etRes, etaRes, phiRes);
   if(!OK) return OK;
   m4(0,0) = resolution->square(etRes);
   m4(1,1) = resolution->square(etaRes);
   m4(2,2) = resolution->square(phiRes);

   TLorentzVector tmp_mup = mup;
   TLorentzVector tmp_nvp = nvp;
   TLorentzVector tmp_ajp = ajp;
   TLorentzVector tmp_bjp = bjp;

   // Fit Particle
   TFitParticleEtEtaPhi* particle1 = new TFitParticleEtEtaPhi( "Lepton",   "Lepton",   &tmp_mup,    &m1 );
   TFitParticleEtEtaPhi* particle2 = new TFitParticleEtEtaPhi( "Neutrino", "Neutrino", &tmp_nvp,    &m2 );
   TFitParticleEtEtaPhi* particle3 = new TFitParticleEtEtaPhi( "Jeta",     "Jeta",     &tmp_ajp,    &m3 );
   TFitParticleEtEtaPhi* particle4 = new TFitParticleEtEtaPhi( "Jetb",     "Jetb",     &tmp_bjp,    &m4 );

   // Constraint
   TFitConstraintMGaus* mCons1 = new TFitConstraintMGaus( "W1MassConstraint", "W1Mass-Constraint", 0, 0 , 80.399, 2.085);
   mCons1->addParticles1( particle1, particle2 );

   TFitConstraintMGaus* mCons2 = new TFitConstraintMGaus( "W2MassConstraint", "W2Mass-Constraint", 0, 0 , 80.399, 2.085);
   mCons2->addParticles1( particle3, particle4 );

   TFitConstraintEp *pxCons = new TFitConstraintEp( "PxConstraint", "Px-Constraint", 0, TFitConstraintEp::pX , (mup+nvp+ajp+bjp).Px() );
   pxCons->addParticles( particle1, particle2, particle3, particle4 );

   TFitConstraintEp *pyCons = new TFitConstraintEp( "PyConstraint", "Py-Constraint", 0, TFitConstraintEp::pY , (mup+nvp+ajp+bjp).Py() );
   pyCons->addParticles( particle1, particle2, particle3, particle4 );

   //Definition of the fitter
   TKinFitter* fitter = new TKinFitter("fitter", "fitter");
   if        (fflage == 1 ){
      fitter->addMeasParticle( particle1 );
      fitter->addMeasParticle( particle2 );
      fitter->addMeasParticle( particle3 );
      fitter->addMeasParticle( particle4 );
      fitter->addConstraint( mCons1 );
      fitter->addConstraint( mCons2 );
   }else   if(fflage == 2 ){
      fitter->addMeasParticle( particle1 );
      fitter->addMeasParticle( particle2 );
      fitter->addMeasParticle( particle3 );
      fitter->addMeasParticle( particle4 );
      fitter->addConstraint( pxCons );
      fitter->addConstraint( pyCons );
      fitter->addConstraint( mCons1 );
      fitter->addConstraint( mCons2 );
   }else   if(fflage == 3 ){
      fitter->addMeasParticle( particle3 );
      fitter->addMeasParticle( particle4 );
      fitter->addConstraint( mCons2 );
   }else {return false;}

   //Set convergence criteria
   fitter->setMaxNbIter( 50 );
   fitter->setMaxDeltaS( 1e-2 );
   fitter->setMaxF( 1e-1 );
   fitter->setVerbosity(1);
   fitter->fit();

   //Return the kinematic fit results
   fit_status   = fitter->getStatus();
   fit_chi2     = fitter->getS();
   fit_NDF      = fitter->getNDF();
   fit_mup      = *(particle1->getCurr4Vec()); 
   fit_nvp      = *(particle2->getCurr4Vec()); 
   fit_ajp      = *(particle3->getCurr4Vec()); 
   fit_bjp      = *(particle4->getCurr4Vec()); 

   if(fitter->getStatus() == 0) { OK = true;  } else { OK = false;  }
   delete resolution;
   delete particle1;
   delete particle2;
   delete particle3;
   delete particle4;
   delete mCons1;
   delete mCons2;
   delete pxCons;
   delete pyCons;
   delete fitter;

   return OK;

}// End Function "doKinematicFit"



////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
///// Function to get angular separation between photon and decay planes:
void kanamuon_photon::gammaCalcAngles(TLorentzVector& thep4gamma, TLorentzVector& thep4M11, TLorentzVector& thep4M12, double& cosine_gamma_vs_decayplane_phi){

   TVector3 gamma_p3 = TVector3( thep4gamma.X(), thep4gamma.Y(), thep4gamma.Z());
   TVector3 M11_p3 = TVector3( thep4M11.X(), thep4M11.Y(), thep4M11.Z());
   TVector3 M12_p3 = TVector3( thep4M12.X(), thep4M12.Y(), thep4M12.Z());

   TVector3 norm = M11_p3.Cross(M12_p3);

   double dotproduct = norm.Dot(gamma_p3);
   cosine_gamma_vs_decayplane_phi = dotproduct/(norm.Mag()*gamma_p3.Mag());

}// End Function "gammaCalcAngles"



////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
///// Function to get decay angles:
void kanamuon_photon::calculateAngles(TLorentzVector& thep4M11, TLorentzVector& thep4M12, TLorentzVector& thep4M21, TLorentzVector& thep4M22, double& costheta1, double& costheta2, double& phi, double& costhetastar, double& phistar1, double& phistar2){


   TLorentzVector thep4H = thep4M11 + thep4M12 + thep4M21 + thep4M22;
   TLorentzVector thep4Z1 = thep4M11 + thep4M12;
   TLorentzVector thep4Z2 = thep4M21 + thep4M22;

   double norm;

   TVector3 boostX = -(thep4H.BoostVector());
   TLorentzVector thep4Z1inXFrame( thep4Z1 );
   TLorentzVector thep4Z2inXFrame( thep4Z2 );      
   thep4Z1inXFrame.Boost( boostX );
   thep4Z2inXFrame.Boost( boostX );
   TVector3 theZ1X_p3 = TVector3( thep4Z1inXFrame.X(), thep4Z1inXFrame.Y(), thep4Z1inXFrame.Z() );
   TVector3 theZ2X_p3 = TVector3( thep4Z2inXFrame.X(), thep4Z2inXFrame.Y(), thep4Z2inXFrame.Z() );

   ///////////////////////////////////////////////
   // check for z1/z2 convention, redefine all 4 vectors with convention
   /////////////////////////////////////////////// 
   TLorentzVector p4H, p4Z1, p4M11, p4M12, p4Z2, p4M21, p4M22;
   p4Z1 = thep4Z1; p4M11 = thep4M11; p4M12 = thep4M12;
   p4Z2 = thep4Z2; p4M21 = thep4M21; p4M22 = thep4M22;
   costhetastar = theZ1X_p3.CosTheta();

   // now helicity angles................................
   // ...................................................
   TVector3 boostZ1 = -(p4Z1.BoostVector());
   TLorentzVector p4Z2Z1(p4Z2);
   p4Z2Z1.Boost(boostZ1);
   //find the decay axis
   TVector3 unitx_1( -p4Z2Z1.X(), -p4Z2Z1.Y(), -p4Z2Z1.Z() );
   norm = 1/(unitx_1.Mag());
   unitx_1*=norm;
   //boost daughters of z2
   TLorentzVector p4M21Z1(p4M21);
   TLorentzVector p4M22Z1(p4M22);
   p4M21Z1.Boost(boostZ1);
   p4M22Z1.Boost(boostZ1);
   //create z and y axes
   TVector3 p4M21Z1_p3( p4M21Z1.X(), p4M21Z1.Y(), p4M21Z1.Z() );
   TVector3 p4M22Z1_p3( p4M22Z1.X(), p4M22Z1.Y(), p4M22Z1.Z() );
   TVector3 unitz_1 = p4M21Z1_p3.Cross( p4M22Z1_p3 );
   norm = 1/(unitz_1.Mag());
   unitz_1 *= norm;
   TVector3 unity_1 = unitz_1.Cross(unitx_1);

   //caculate theta1
   TLorentzVector p4M11Z1(p4M11);
   p4M11Z1.Boost(boostZ1);
   TVector3 p3M11( p4M11Z1.X(), p4M11Z1.Y(), p4M11Z1.Z() );
   TVector3 unitM11 = p3M11.Unit();
   double x_m11 = unitM11.Dot(unitx_1); double y_m11 = unitM11.Dot(unity_1); double z_m11 = unitM11.Dot(unitz_1);
   TVector3 M11_Z1frame(y_m11, z_m11, x_m11);
   costheta1 = M11_Z1frame.CosTheta();

   //////-----------------------old way of calculating phi---------------/////////
   phi = M11_Z1frame.Phi();

   //set axes for other system
   TVector3 boostZ2 = -(p4Z2.BoostVector());
   TLorentzVector p4Z1Z2(p4Z1);
   p4Z1Z2.Boost(boostZ2);
   TVector3 unitx_2( -p4Z1Z2.X(), -p4Z1Z2.Y(), -p4Z1Z2.Z() );
   norm = 1/(unitx_2.Mag());
   unitx_2*=norm;
   //boost daughters of z2
   TLorentzVector p4M11Z2(p4M11);
   TLorentzVector p4M12Z2(p4M12);
   p4M11Z2.Boost(boostZ2);
   p4M12Z2.Boost(boostZ2);
   TVector3 p4M11Z2_p3( p4M11Z2.X(), p4M11Z2.Y(), p4M11Z2.Z() );
   TVector3 p4M12Z2_p3( p4M12Z2.X(), p4M12Z2.Y(), p4M12Z2.Z() );
   TVector3 unitz_2 = p4M11Z2_p3.Cross( p4M12Z2_p3 );
   norm = 1/(unitz_2.Mag());
   unitz_2*=norm;
   TVector3 unity_2 = unitz_2.Cross(unitx_2);
   //calcuate theta2
   TLorentzVector p4M21Z2(p4M21);
   p4M21Z2.Boost(boostZ2);
   TVector3 p3M21( p4M21Z2.X(), p4M21Z2.Y(), p4M21Z2.Z() );
   TVector3 unitM21 = p3M21.Unit();
   double x_m21 = unitM21.Dot(unitx_2); double y_m21 = unitM21.Dot(unity_2); double z_m21 = unitM21.Dot(unitz_2);
   TVector3 M21_Z2frame(y_m21, z_m21, x_m21);
   costheta2 = M21_Z2frame.CosTheta();

   // calculate phi
   //calculating phi_n
   TLorentzVector n_p4Z1inXFrame( p4Z1 );
   TLorentzVector n_p4M11inXFrame( p4M11 );
   n_p4Z1inXFrame.Boost( boostX );
   n_p4M11inXFrame.Boost( boostX );        
   TVector3 n_p4Z1inXFrame_unit = n_p4Z1inXFrame.Vect().Unit();
   TVector3 n_p4M11inXFrame_unit = n_p4M11inXFrame.Vect().Unit();  
   TVector3 n_unitz_1( n_p4Z1inXFrame_unit );
   //// y-axis is defined by neg lepton cross z-axis
   //// the subtle part is here...
   TVector3 n_unity_1 = n_unitz_1.Cross( n_p4M11inXFrame_unit );
   TVector3 n_unitx_1 = n_unity_1.Cross( n_unitz_1 );

   TLorentzVector n_p4M21inXFrame( p4M21 );
   n_p4M21inXFrame.Boost( boostX );
   TVector3 n_p4M21inXFrame_unit = n_p4M21inXFrame.Vect().Unit();
   //rotate into other plane
   TVector3 n_p4M21inXFrame_unitprime( n_p4M21inXFrame_unit.Dot(n_unitx_1), n_p4M21inXFrame_unit.Dot(n_unity_1), n_p4M21inXFrame_unit.Dot(n_unitz_1) );

   /// and then calculate phistar1
   TVector3 n_p4PartoninXFrame_unit( 0.0, 0.0, 1.0 );
   TVector3 n_p4PartoninXFrame_unitprime( n_p4PartoninXFrame_unit.Dot(n_unitx_1), n_p4PartoninXFrame_unit.Dot(n_unity_1), n_p4PartoninXFrame_unit.Dot(n_unitz_1) );
   // negative sign is for arrow convention in paper
   phistar1 = (n_p4PartoninXFrame_unitprime.Phi());

   // and the calculate phistar2
   TLorentzVector n_p4Z2inXFrame( p4Z2 );
   n_p4Z2inXFrame.Boost( boostX );
   TVector3 n_p4Z2inXFrame_unit = n_p4Z2inXFrame.Vect().Unit();
   TVector3 n_unitz_2( n_p4Z2inXFrame_unit );

   //// y-axis is defined by neg lepton cross z-axis
   //// the subtle part is here...
   TVector3 n_unity_2 = n_unitz_2.Cross( n_p4M21inXFrame_unit );
   TVector3 n_unitx_2 = n_unity_2.Cross( n_unitz_2 );
   TVector3 n_p4PartoninZ2PlaneFrame_unitprime( n_p4PartoninXFrame_unit.Dot(n_unitx_2), n_p4PartoninXFrame_unit.Dot(n_unity_2), n_p4PartoninXFrame_unit.Dot(n_unitz_2) );
   phistar2 = (n_p4PartoninZ2PlaneFrame_unitprime.Phi());

}// End Function "calculateAngles"


////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
// function used to fill the counters with preselction level cuts
void kanamuon_photon::InitCounters( const char* input_file_name, TH1F* h_events, TH1F* h_events_weighted)
{
   TFile* f = new TFile(input_file_name, "READ");
   std::vector<float> events;

   //get the counters from the FNAL NT
   events.push_back(((TH1F*) f->Get("AllEventsStep/totalEvents"))->GetEntries());
   events.push_back(((TH1F*) f->Get("noscrapingStep/totalEvents"))->GetEntries());
   events.push_back(((TH1F*) f->Get("HBHENoiseStep/totalEvents"))->GetEntries());
   events.push_back(((TH1F*) f->Get("primaryVertexStep/totalEvents"))->GetEntries());
   events.push_back(((TH1F*) f->Get("tightLeptonStep/totalEvents"))->GetEntries());
   events.push_back(((TH1F*) f->Get("looseElectronStep/totalEvents"))->GetEntries());
   events.push_back(((TH1F*) f->Get("looseMuonStep/totalEvents"))->GetEntries());
   events.push_back(((TH1F*) f->Get("RequireTwoJetsORboostedVStep/totalEvents"))->GetEntries());


   //put the counters in the counter histos
   for ( unsigned int istep = 0; istep < events.size(); istep++ ) {
      h_events -> SetBinContent( istep + 1, events[istep] );
      h_events_weighted -> SetBinContent( istep + 1, events[istep] );
   }
   f -> Close();

}// End Function "InitCounters"


