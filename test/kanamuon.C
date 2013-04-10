#define kanamuon_cxx
#include "kanamuon.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <TMath.h>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <TMap.h>
#include "LOTable.h"

#include "Resolution.h"
#include "PhysicsTools/KinFitter/interface/TFitConstraintMGaus.h"
#include "PhysicsTools/KinFitter/interface/TFitConstraintM.h"
#include "PhysicsTools/KinFitter/interface/TFitConstraintEp.h"
#include "PhysicsTools/KinFitter/interface/TFitParticleEtEtaPhi.h"
#include "PhysicsTools/KinFitter/interface/TFitParticleCart.h"
#include "PhysicsTools/KinFitter/interface/TKinFitter.h"

#include "ElectroWeakAnalysis/VPlusJets/interface/AngularVars.h"

#include "ElectroWeakAnalysis/VPlusJets/interface/METzCalculator.h"

#include "ClassifierOut/TMVAClassification_170_nJ2_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_180_nJ2_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_190_nJ2_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_200_nJ2_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_250_nJ2_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_300_nJ2_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_350_nJ2_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_400_nJ2_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_450_nJ2_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_500_nJ2_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_550_nJ2_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_600_nJ2_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_400_nJ2_mu_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_400_nJ2_mu_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_400_nJ2_mu_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_450_nJ2_mu_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_450_nJ2_mu_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_450_nJ2_mu_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_500_nJ2_mu_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_500_nJ2_mu_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_500_nJ2_mu_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_550_nJ2_mu_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_550_nJ2_mu_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_550_nJ2_mu_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_600_nJ2_mu_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_600_nJ2_mu_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_600_nJ2_mu_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_700_nJ2_mu_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_700_nJ2_mu_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_700_nJ2_mu_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_800_nJ2_mu_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_800_nJ2_mu_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_800_nJ2_mu_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_900_nJ2_mu_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_900_nJ2_mu_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_900_nJ2_mu_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_1000_nJ2_mu_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_1000_nJ2_mu_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_1000_nJ2_mu_interferenceup_Likelihood.class.C"

#include "ClassifierOut/TMVAClassification_170_nJ3_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_180_nJ3_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_190_nJ3_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_200_nJ3_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_250_nJ3_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_300_nJ3_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_350_nJ3_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_400_nJ3_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_450_nJ3_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_500_nJ3_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_550_nJ3_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_600_nJ3_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_400_nJ3_mu_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_400_nJ3_mu_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_400_nJ3_mu_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_450_nJ3_mu_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_450_nJ3_mu_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_450_nJ3_mu_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_500_nJ3_mu_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_500_nJ3_mu_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_500_nJ3_mu_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_550_nJ3_mu_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_550_nJ3_mu_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_550_nJ3_mu_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_600_nJ3_mu_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_600_nJ3_mu_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_600_nJ3_mu_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_700_nJ3_mu_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_700_nJ3_mu_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_700_nJ3_mu_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_800_nJ3_mu_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_800_nJ3_mu_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_800_nJ3_mu_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_900_nJ3_mu_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_900_nJ3_mu_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_900_nJ3_mu_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_1000_nJ3_mu_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_1000_nJ3_mu_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_1000_nJ3_mu_interferenceup_Likelihood.class.C"

#include "ClassifierOut/TMVAClassification_noqg_nJ2_mu_BDT.class.C"
#include "ClassifierOut/TMVAClassification_noqg_nJ3_mu_BDT.class.C"
#include "ClassifierOut/TMVAClassification_withqg_nJ2_mu_BDT.class.C"
#include "ClassifierOut/TMVAClassification_withqg_nJ3_mu_BDT.class.C"

#include "ClassifierOut/TMVAClassification_170_VBF_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_180_VBF_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_190_VBF_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_200_VBF_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_250_VBF_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_300_VBF_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_350_VBF_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_400_VBF_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_450_VBF_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_500_VBF_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_550_VBF_mu_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_600_VBF_mu_Likelihood.class.C"

#include "EffTableReader.h"
#include "EffTableLoader.h"

//#include "PhysicsTools/Utilities/interface/Lumi3DReWeighting.h"

#include "ElectroWeakAnalysis/VPlusJets/interface/QGLikelihoodCalculator.h"
#include "MMozer/powhegweight/interface/pwhg_wrapper.h"

//const TString inDataDir  = "/eos/uscms/store/user/jdamgov/lnujj/ICHEP12v3/Ntuples/";
//const TString inDataDir  = "/eos/uscms/store/user/pdudero/lnujj/ICHEP12/MergedNtuples/";
//const TString inDataDir  = "/eos/uscms/store/user/lnujj/ICHEP12/MergedNtuples/";
// const TString inDataDir  = "/eos/uscms/store/user/smpjs/ntran/WWlnujj_53x/";
//const TString inDataDir  = "/eos/uscms/store/user/lnujj/HCP2012/MergedNtuples/";
//const TString inDataDir  = "/eos/uscms/store/user/lnujj/HCP2012METfix/MergedNtuples/";
//const TString inDataDir  = "/uscmst1b_scratch/lpc1/3DayLifetime/weizountuple/";
//const TString inDataDir  = "/eos/uscms/store/user/lnujj/Moriond2013/MergedNtuples/";
//const TString inDataDir  = "/eos/uscms/store/user/lnujj/Moriond2013/MergedNtuples_v1/";
//const TString inDataDir  = "/eos/uscms/store/user/lnujj/Moriond2013/MergedNtuples_v2_nojetnum/";
const TString inDataDir  = "/uscmst1b_scratch/lpc1/3DayLifetime/weizou/Ntuple_2013_3_18/";
//const TString inDataDir  = "/uscms_data/d3/weizou/test/CopySample/";
//const TString inDataDir  = "/uscmst1b_scratch/lpc1/3DayLifetime/weizou/DataSample_2013_1_25/";
//const TString inDataDir  = "/uscmst1b_scratch/lpc1/3DayLifetime/jdamgov/HCPlnjj/MergedNtuples/";
//const TString inDataDir  = "/uscmst1b_scratch/lpc1/3DayLifetime/weizountuple/";
//const TString inQCDDir   = "/eos/uscms/store/user/lnujj/ICHEP12/MergedNtuples/";
// const TString inQCDDir   = "/uscms_data/d3/weizou/MakeNtuple/CMSSW_5_3_2_patch4/src/ElectroWeakAnalysis/VPlusJets/test/";
//const TString inQCDDir   = "/eos/uscms/store/user/lnujj/HCP2012/MergedNtuples/";
const TString inQCDDir   = "/eos/uscms/store/user/lnujj/HCP2012METfix/MergedNtuples_v1/";
//const TString outDataDir = "/eos/uscms/store/user/lnujj/postICHEP12/RDtreesPU5p2/";
//const TString outDataDir = "/eos/uscms/store/user/smpjs/weizou/HCP2012/RDtreesPUCMSSW532/";
//const TString outDataDir   = "/uscms_data/d3/weizou/MakeNtuple/CMSSW_5_3_2_patch4/src/ElectroWeakAnalysis/VPlusJets/test/";
//const TString outDataDir   = "/uscmst1b_scratch/lpc1/3DayLifetime/weizou/ttHsample_New_v14/";
//const TString outDataDir   = "/uscmst1b_scratch/lpc1/3DayLifetime/weizou/BoostedWSample_v2/";
//const TString outDataDir   = "/uscmst1b_scratch/lpc1/3DayLifetime/weizou/EWKW2jetsSample_2013_3_15/";
const TString outDataDir   = "/uscmst1b_scratch/lpc1/3DayLifetime/weizou/EWKW2jetsSample_2013_3_23/";
//const TString outDataDir   = "/eos/uscms/store/user/lnujj/HCP2012/ReducedTrees/";
//const std::string fDir   = "EffTableDir/";
const std::string fDir   = "EffTable2012/";
const std::string fInterferenceDir   = "InterferenceTable2012/";

bool large(const double &a, const double &b)
{

   return a > b;
}

struct sortPt
{
   bool operator()(TLorentzVector* s1, TLorentzVector* s2) const
   {
      return s1->Pt() >= s2->Pt();
   }
} mysortPt;

void kanamuon::myana(double myflag, bool isQCD, int runflag)
{
   //Prepare the histogram for the cut-flow control : 8 presel + 7 sel
   const int n_step = 15;
   TH1F* h_events          = new TH1F("h_events", "h_events", n_step, 0, n_step);
   TH1F* h_events_weighted = new TH1F("h_events_weighted", "h_events_weighted", n_step, 0, n_step);

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

   for ( int istep = 0; istep < n_step; istep++ ) {
      h_events -> GetXaxis() -> SetBinLabel( istep + 1, step_names[istep].c_str() );
      h_events_weighted -> GetXaxis() -> SetBinLabel( istep + 1, step_names[istep].c_str() );
   }

   TChain * myChain;

   // 2011 data
   if (myflag == 20120000 || myflag == -100){
      myChain = new TChain("WJet");  
      if ( !isQCD ) {
         //InitCounters( inDataDir + "WmunuJets_DataAllSingleMuonTrigger_GoldenJSON_15p7invfb.root", h_events, h_events_weighted);
         //myChain->Add(                    inDataDir + "WmunuJets_DataAllSingleMuonTrigger_GoldenJSON_15p7invfb.root");
         //InitCounters( inDataDir + "WmunuJets_DataAllSingleMuonTrigger_GoldenJSON_9p9invfb.root", h_events, h_events_weighted);
         //myChain->Add(                    inDataDir + "WmunuJets_DataAllSingleMuonTrigger_GoldenJSON_9p9invfb.root");
         //Init(myChain);Loop( h_events, h_events_weighted, 20120000,runflag, outDataDir + "RD_WmunuJets_DataAll_GoldenJSON_9p9invfb");
         //InitCounters( inDataDir + "WmunuJets_DataAllSingleMuonTrigger_GoldenJSON_18p764invfb.root", h_events, h_events_weighted);
         //myChain->Add(                    inDataDir + "WmunuJets_DataAllSingleMuonTrigger_GoldenJSON_18p764invfb.root");
         /*InitCounters( inDataDir + "WmunuJets_DataAllSingleMuonTrigger_GoldenJSON_19p3invfb_pt1.root", h_events, h_events_weighted);
         myChain->Add(                    inDataDir + "WmunuJets_DataAllSingleMuonTrigger_GoldenJSON_19p3invfb_pt1.root");
         Init(myChain);Loop( h_events, h_events_weighted, 20120000,runflag, outDataDir + "RD_WmunuJets_DataAll_GoldenJSON_19p3invfb_pt1");
         */
         InitCounters( inDataDir + "WmunuJets_DataAllSingleMuonTrigger_GoldenJSON_19p3invfb_pt2.root", h_events, h_events_weighted);
         myChain->Add(                    inDataDir + "WmunuJets_DataAllSingleMuonTrigger_GoldenJSON_19p3invfb_pt2.root");
         Init(myChain);Loop( h_events, h_events_weighted, 20120000,runflag, outDataDir + "RD_WmunuJets_DataAll_GoldenJSON_19p3invfb_pt2");
         /*InitCounters( inDataDir + "WmunuJets_DataAllSingleMuonTrigger_GoldenJSON_12p5invfb.root", h_events, h_events_weighted);
         myChain->Add(                    inDataDir + "WmunuJets_DataAllSingleMuonTrigger_GoldenJSON_12p5invfb.root");
         Init(myChain);Loop( h_events, h_events_weighted, 20120000,runflag, outDataDir + "RD_WmunuJets_DataAll_GoldenJSON_12p5invfb");
         */
      } else {
         InitCounters( inDataDir + "QCDmu.root", h_events, h_events_weighted);
         myChain->Add(                    inQCDDir +     "QCDmu.root");
         Init(myChain);Loop( h_events, h_events_weighted, 20110000,runflag, outDataDir + "RDQCD_WmunuJets_DataAll_GoldenJSON_0p7invfb", isQCD);
      }
   }

   if ( !isQCD ) {
      // General Background Samples
      if (myflag == 20111002 || myflag == -200){
         InitCounters( inDataDir + "mu_STopS_Tbar_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_STopS_Tbar_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111002,runflag, outDataDir + "RD_mu_STopS_Tbar_CMSSW428");
      }
      if (myflag == 20121002 || myflag == -200){
         InitCounters( inDataDir + "mu_STopS_Tbar_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_STopS_Tbar_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121002,runflag, outDataDir + "RD_mu_STopS_Tbar_CMSSW532");
      }
      if (myflag == 20111003 || myflag == -200){
         InitCounters( inDataDir + "mu_STopS_T_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_STopS_T_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111003,runflag, outDataDir + "RD_mu_STopS_T_CMSSW428");
      }
      if (myflag == 20121003 || myflag == -200){
         InitCounters( inDataDir + "mu_STopS_T_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_STopS_T_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121003,runflag, outDataDir + "RD_mu_STopS_T_CMSSW532");
      }
      if (myflag == 20111004 || myflag == -200){
         InitCounters( inDataDir + "mu_STopT_Tbar_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_STopT_Tbar_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111004,runflag, outDataDir + "RD_mu_STopT_Tbar_CMSSW428");
      }
      if (myflag == 20121004 || myflag == -200){
         InitCounters( inDataDir + "mu_STopT_Tbar_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_STopT_Tbar_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121004,runflag, outDataDir + "RD_mu_STopT_Tbar_CMSSW532");
      }
      if (myflag == 20111005 || myflag == -200){
         InitCounters( inDataDir + "mu_STopT_T_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_STopT_T_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111005,runflag, outDataDir + "RD_mu_STopT_T_CMSSW428");
      }
      if (myflag == 20121005 || myflag == -200){
         InitCounters( inDataDir + "mu_STopT_T_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_STopT_T_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121005,runflag, outDataDir + "RD_mu_STopT_T_CMSSW532");
      }
      if (myflag == 20111006 || myflag == -200){
         InitCounters( inDataDir + "mu_STopTW_Tbar_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_STopTW_Tbar_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111006,runflag, outDataDir + "RD_mu_STopTW_Tbar_CMSSW428");
      }
      if (myflag == 20121006 || myflag == -200){
         InitCounters( inDataDir + "mu_STopTW_Tbar_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_STopTW_Tbar_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121006,runflag, outDataDir + "RD_mu_STopTW_Tbar_CMSSW532");
      }
      if (myflag == 20111007 || myflag == -200){
         InitCounters( inDataDir + "mu_STopTW_T_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_STopTW_T_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111007,runflag, outDataDir + "RD_mu_STopTW_T_CMSSW428");
      }
      if (myflag == 20121007 || myflag == -200){
         InitCounters( inDataDir + "mu_STopTW_T_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_STopTW_T_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121007,runflag, outDataDir + "RD_mu_STopTW_T_CMSSW532");
      }
      if (myflag == 20111008 || myflag == -200){
         InitCounters( inDataDir + "mu_TTbar_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_TTbar_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111008,runflag, outDataDir + "RD_mu_TTbar_CMSSW428");
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
      if (myflag == 20111009 || myflag == -500){
         InitCounters( inDataDir + "mu_WpJ_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WpJ_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111009,runflag, outDataDir + "RD_mu_WpJ_CMSSW428");
      }
      /*if (myflag == 20121009 || myflag == -500){
         //InitCounters( inDataDir + "mu_WpJ_CMSSW532.root", h_events, h_events_weighted);             
         InitCounters( inDataDir + "mu_WJets_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WJets_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121009,runflag, outDataDir + "RD_mu_WpJ_CMSSW532");
      }*/
      if (myflag == 201210091 || myflag == -500){
         /*InitCounters( inDataDir + "mu_WJets_CMSSW532_pt1.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WJets_CMSSW532_pt1.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 201210091,runflag, outDataDir + "RD_mu_WJets_CMSSW532_pt1");
         */
         InitCounters( inDataDir + "mu_WJets_CMSSW532_pt1_v2.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WJets_CMSSW532_pt1_v2.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 201210091,runflag, outDataDir + "RD_mu_WJets_CMSSW532_pt1_v2");
      }
      if (myflag == 201210092 || myflag == -500){
         /*InitCounters( inDataDir + "mu_WJets_CMSSW532_pt2.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WJets_CMSSW532_pt2.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 201210092,runflag, outDataDir + "RD_mu_WJets_CMSSW532_pt2");
         */
         InitCounters( inDataDir + "mu_WJets_CMSSW532_pt2_v2.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WJets_CMSSW532_pt2_v2.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 201210092,runflag, outDataDir + "RD_mu_WJets_CMSSW532_pt2_v2");
      }
      if (myflag == 20111010 || myflag == -200){
         InitCounters( inDataDir + "mu_WpJmatchingdown_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WpJmatchingdown_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111010,runflag, outDataDir + "RD_mu_WpJmatchingdown_CMSSW428");
      }
      if (myflag == 20111011 || myflag == -200){
         InitCounters( inDataDir + "mu_WpJmatchingup_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WpJmatchingup_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111011,runflag, outDataDir + "RD_mu_WpJmatchingup_CMSSW428");
      }
      if (myflag == 20111012 || myflag == -200){
         InitCounters( inDataDir + "mu_WpJscaledown_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WpJscaledown_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111012,runflag, outDataDir + "RD_mu_WpJscaledown_CMSSW428");
      }
      if (myflag == 20111013 || myflag == -200){
         InitCounters( inDataDir + "mu_WpJscaleup_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WpJscaleup_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111013,runflag, outDataDir + "RD_mu_WpJscaleup_CMSSW428");
      }
      if (myflag == 20111014 || myflag ==  999){ // set 999 not run!!
         InitCounters( inDataDir + "mu_WpJsherpa_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WpJsherpa_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111014,runflag, outDataDir + "RD_mu_WpJsherpa_CMSSW428");
      }
      if (myflag == 20111015 || myflag == -200){
         InitCounters( inDataDir + "mu_WW_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WW_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111015,runflag, outDataDir + "RD_mu_WW_CMSSW428");
      }
      if (myflag == 20121015 || myflag == -200){
         InitCounters( inDataDir + "mu_WW_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WW_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121015,runflag, outDataDir + "RD_mu_WW_CMSSW532");
      }
      if (myflag == 20111016 || myflag == -200){
         InitCounters( inDataDir + "mu_WZ_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WZ_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111016,runflag, outDataDir + "RD_mu_WZ_CMSSW428");
      }
      if (myflag == 20121016 || myflag == -200){
         InitCounters( inDataDir + "mu_WZ_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WZ_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121016,runflag, outDataDir + "RD_mu_WZ_CMSSW532");
      }
      if (myflag == 20111017 || myflag == -200){
         InitCounters( inDataDir + "mu_ZpJ_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_ZpJ_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111017,runflag, outDataDir + "RD_mu_ZpJ_CMSSW428");
      }
      if (myflag == 20121017 || myflag == -200){
         InitCounters( inDataDir + "mu_ZpJ_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_ZpJ_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121017,runflag, outDataDir + "RD_mu_ZpJ_CMSSW532");
      }
      if (myflag == 20111018 || myflag ==  999){ // set 999 not run!!
         InitCounters( inDataDir + "mu_QCDMu_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_QCDMu_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111018,runflag, outDataDir + "RD_mu_QCDMu_CMSSW428");
      }
      if (myflag == 20111019 || myflag ==  999){ // set 999 not run!!
         InitCounters( inDataDir + "mu_TTbar_powheg_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_TTbar_powheg_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111019,runflag, outDataDir + "RD_mu_TTbar_powheg_CMSSW428");
      }
      if (myflag == 20111020 || myflag == -200){
         InitCounters( inDataDir + "mu_ZZ_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_ZZ_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111020,runflag, outDataDir + "RD_mu_ZZ_CMSSW428");
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
         InitCounters( inDataDir + "mu_W4Jets_CMSSW532_old.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_W4Jets_CMSSW532_old.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121023,runflag, outDataDir + "RD_mu_W4Jets_CMSSW532_old");
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
         InitCounters( inDataDir + "mu_WpJ_PT100Herwing_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WpJ_PT100Herwing_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121028,runflag, outDataDir + "RD_mu_WJets_herwig_CMSSW532");
      }
      if (myflag == 20121029 || myflag == -200){
         InitCounters( inDataDir + "mu_WpJ_PT100madgraph_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WpJ_PT100madgraph_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121029,runflag, outDataDir + "RD_mu_WJets_madgraph_CMSSW532");
      }
      if (myflag == 20121030 || myflag == -200){
         InitCounters( inDataDir + "mu_W2Jets_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_W2Jets_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121030,runflag, outDataDir + "RD_mu_W2Jets_CMSSW532");
      }
      if (myflag == 20121031 || myflag == -200){
         InitCounters( inDataDir + "mu_W1Jets_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_W1Jets_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121031,runflag, outDataDir + "RD_mu_W1Jets_CMSSW532");
      }
      if (myflag == 20121032 || myflag == -200){
         /*InitCounters( inDataDir + "mu_EWKW2Jets_CMSSW532.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_EWKW2Jets_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121032,runflag, outDataDir + "RD_mu_EWKW2Jets_CMSSW532");
         */
         InitCounters( inDataDir + "mu_EWKW2Jets_CMSSW532_v2.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_EWKW2Jets_CMSSW532_v2.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121032,runflag, outDataDir + "RD_mu_EWKW2Jets_CMSSW532_v2");
      }

      // Higgs Signal Samples
      if (myflag == 20112150 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH150_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH150_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112150,runflag, outDataDir + "RD_mu_HWWMH150_CMSSW428");
      }
      if (myflag == 20112160 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH160_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH160_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112160,runflag, outDataDir + "RD_mu_HWWMH160_CMSSW428");
      }
      if (myflag == 20112170 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH170_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH170_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112170,runflag, outDataDir + "RD_mu_HWWMH170_CMSSW428");
      }
      if (myflag == 20122125 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH125_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH125_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122125,runflag, outDataDir + "RD_mu_HWWMH125_CMSSW532_private");
      }
      if (myflag == 20122140 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH140_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH140_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122140,runflag, outDataDir + "RD_mu_HWWMH140_CMSSW532_private");
      }
      if (myflag == 20122160 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH160_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH160_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122160,runflag, outDataDir + "RD_mu_HWWMH160_CMSSW532_private");
      }
      if (myflag == 20122170 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH170_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH170_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122170,runflag, outDataDir + "RD_mu_HWWMH170_CMSSW532_private");
      }
      if (myflag == 20112180 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH180_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH180_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112180,runflag, outDataDir + "RD_mu_HWWMH180_CMSSW428");
      }
      if (myflag == 20122180 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH180_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH180_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122180,runflag, outDataDir + "RD_mu_HWWMH180_CMSSW532_private");
      }
      if (myflag == 20112190 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH190_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH190_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112190,runflag, outDataDir + "RD_mu_HWWMH190_CMSSW428");
      }
      if (myflag == 20122190 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH190_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH190_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122190,runflag, outDataDir + "RD_mu_HWWMH190_CMSSW532_private");
      }
      if (myflag == 20112200 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH200_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH200_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112200,runflag, outDataDir + "RD_mu_HWWMH200_CMSSW428");
      }
      if (myflag == 20122200 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH200_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH200_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122200,runflag, outDataDir + "RD_mu_HWWMH200_CMSSW532_private");
      }
      if (myflag == 20112250 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH250_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH250_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112250,runflag, outDataDir + "RD_mu_HWWMH250_CMSSW428");
      }
      if (myflag == 20122250 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH250_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH250_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122250,runflag, outDataDir + "RD_mu_HWWMH250_CMSSW532_private");
      }
      if (myflag == 20112300 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH300_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH300_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112300,runflag, outDataDir + "RD_mu_HWWMH300_CMSSW428");
      }
      if (myflag == 20122300 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH300_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH300_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122300,runflag, outDataDir + "RD_mu_HWWMH300_CMSSW532_private");
      }
      if (myflag == 20112350 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH350_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH350_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112350,runflag, outDataDir + "RD_mu_HWWMH350_CMSSW428");
      }
      if (myflag == 20122350 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH350_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH350_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122350,runflag, outDataDir + "RD_mu_HWWMH350_CMSSW532_private");
      }
      /*if (myflag == 20122350 || myflag == -300){
        InitCounters( inDataDir + "mu_HWWMH350_CMSSW532_private.root", h_events, h_events_weighted);             
        myChain = new TChain("WJet");  
        myChain->Add(                    inDataDir + "mu_HWWMH350_CMSSW532_private.root"); 
        Init(myChain);Loop( h_events, h_events_weighted, 20122350,runflag, outDataDir + "RD_mu_HWWMH350_CMSSW532_private");
        }
       */
      if (myflag == 20112400 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH400_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH400_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112400,runflag, outDataDir + "RD_mu_HWWMH400_CMSSW428");
      }
      if (myflag == 20122400 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH400_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH400_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122400,runflag, outDataDir + "RD_mu_HWWMH400_CMSSW532_private");
      }
      if (myflag == 20112450 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH450_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH450_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112450,runflag, outDataDir + "RD_mu_HWWMH450_CMSSW428");
      }
      if (myflag == 20122450 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH450_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH450_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122450,runflag, outDataDir + "RD_mu_HWWMH450_CMSSW532_private");
      }
      if (myflag == 20112500 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH500_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH500_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112500,runflag, outDataDir + "RD_mu_HWWMH500_CMSSW428");
      }
      if (myflag == 20122500 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH500_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH500_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122500,runflag, outDataDir + "RD_mu_HWWMH500_CMSSW532_private");
      }
      if (myflag == 20112550 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH550_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH550_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112550,runflag, outDataDir + "RD_mu_HWWMH550_CMSSW428");
      }
      if (myflag == 20122550 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH550_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH550_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122550,runflag, outDataDir + "RD_mu_HWWMH550_CMSSW532_private");
      }
      if (myflag == 20112600 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH600_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH600_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112600,runflag, outDataDir + "RD_mu_HWWMH600_CMSSW428");
      }
      /*if (myflag == 20122600 || myflag == -300){
        InitCounters( inDataDir + "crabmerge_MC_Wmunu_ggH600.root", h_events, h_events_weighted);             
        myChain = new TChain("WJet");  
        myChain->Add(                    inDataDir + "crabmerge_MC_Wmunu_ggH600.root"); 
        Init(myChain);Loop( h_events, h_events_weighted, 20122600,runflag, outDataDir + "RD_mu_HWWMH600_CMSSW532_private");
        }*/
      if (myflag == 20122600 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH600_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");
         myChain->Add(                    inDataDir + "mu_HWWMH600_CMSSW532_private.root");
         Init(myChain);Loop( h_events, h_events_weighted, 20122600,runflag, outDataDir + "RD_mu_HWWMH600_CMSSW532_private");
      }
      /*if (myflag == 20122700 || myflag == -300){
        InitCounters( inDataDir + "mu_HWWMH700_CMSSW532_private.root", h_events, h_events_weighted);             
        myChain = new TChain("WJet");  
        myChain->Add(                    inDataDir + "mu_HWWMH700_CMSSW532_private.root"); 
        Init(myChain);Loop( h_events, h_events_weighted, 20122700,runflag, outDataDir + "RD_mu_HWWMH700_CMSSW532_private");
        }*/
      if (myflag == 20122700 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH700_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH700_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122700,runflag, outDataDir + "RD_mu_HWWMH700_CMSSW532_private");
      }
      /*if (myflag == 20122800 || myflag == -300){
        InitCounters( inDataDir + "mu_HWWMH800_CMSSW532_private.root", h_events, h_events_weighted);             
        myChain = new TChain("WJet");  
        myChain->Add(                    inDataDir + "mu_HWWMH800_CMSSW532_private.root"); 
        Init(myChain);Loop( h_events, h_events_weighted, 20122800,runflag, outDataDir + "RD_mu_HWWMH800_CMSSW532_private");
        }
       */
      if (myflag == 20122800 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH800_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH800_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122800,runflag, outDataDir + "RD_mu_HWWMH800_CMSSW532_private");
      }
      /*if (myflag == 20122900 || myflag == -300){
        InitCounters( inDataDir + "mu_HWWMH900_CMSSW532_private.root", h_events, h_events_weighted);             
        myChain = new TChain("WJet");  
        myChain->Add(                    inDataDir + "mu_HWWMH900_CMSSW532_private.root"); 
        Init(myChain);Loop( h_events, h_events_weighted, 20122900,runflag, outDataDir + "RD_mu_HWWMH900_CMSSW532_private");
        }
       */
      if (myflag == 20122900 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH900_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH900_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122900,runflag, outDataDir + "RD_mu_HWWMH900_CMSSW532_private");
      }
      /*if (myflag == 201221000 || myflag == -300){
        InitCounters( inDataDir + "mu_HWWMH1000_CMSSW532_private.root", h_events, h_events_weighted);             
        myChain = new TChain("WJet");  
        myChain->Add(                    inDataDir + "mu_HWWMH1000_CMSSW532_private.root"); 
        Init(myChain);Loop( h_events, h_events_weighted, 201221000,runflag, outDataDir + "RD_mu_HWWMH1000_CMSSW532_private");
        }
       */
      if (myflag == 201221000 || myflag == -300){
         InitCounters( inDataDir + "mu_HWWMH1000_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWMH1000_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 201221000,runflag, outDataDir + "RD_mu_HWWMH1000_CMSSW532_private");
      }

      // VBF Higgs MC Signal
      if (myflag == 20123125 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH125_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH125_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123125,runflag, outDataDir + "RD_mu_VBFHWWMH125_CMSSW532_private");
      }
      if (myflag == 20113150 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH150_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH150_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113150,runflag, outDataDir + "RD_mu_VBFHWWMH150_CMSSW428");
      }
      if (myflag == 20113160 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH160_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH160_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113160,runflag, outDataDir + "RD_mu_VBFHWWMH160_CMSSW428");
      }
      if (myflag == 20113170 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH170_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH170_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113170,runflag, outDataDir + "RD_mu_VBFHWWMH170_CMSSW428");
      }
      if (myflag == 20123170 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH170_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH170_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123170,runflag, outDataDir + "RD_mu_VBFHWWMH170_CMSSW532_private");
      }
      if (myflag == 20113180 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH180_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH180_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113180,runflag, outDataDir + "RD_mu_VBFHWWMH180_CMSSW428");
      }
      if (myflag == 20123180 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH180_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH180_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123180,runflag, outDataDir + "RD_mu_VBFHWWMH180_CMSSW532_private");
      }
      if (myflag == 20113190 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH190_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH190_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113190,runflag, outDataDir + "RD_mu_VBFHWWMH190_CMSSW428");
      }
      if (myflag == 20123190 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH190_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH190_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123190,runflag, outDataDir + "RD_mu_VBFHWWMH190_CMSSW532_private");
      }
      if (myflag == 20113200 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH200_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH200_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113200,runflag, outDataDir + "RD_mu_VBFHWWMH200_CMSSW428");
      }
      if (myflag == 20123200 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH200_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH200_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123200,runflag, outDataDir + "RD_mu_VBFHWWMH200_CMSSW532_private");
      }
      if (myflag == 20113250 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH250_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH250_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113250,runflag, outDataDir + "RD_mu_VBFHWWMH250_CMSSW428");
      }
      if (myflag == 20123250 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH250_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH250_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123250,runflag, outDataDir + "RD_mu_VBFHWWMH250_CMSSW532_private");
      }
      if (myflag == 20113300 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH300_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH300_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113300,runflag, outDataDir + "RD_mu_VBFHWWMH300_CMSSW428");
      }
      if (myflag == 20123300 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH300_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH300_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123300,runflag, outDataDir + "RD_mu_VBFHWWMH300_CMSSW532_private");
      }
      if (myflag == 20113350 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH350_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH350_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113350,runflag, outDataDir + "RD_mu_VBFHWWMH350_CMSSW428");
      }
      if (myflag == 20123350 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH350_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH350_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123350,runflag, outDataDir + "RD_mu_VBFHWWMH350_CMSSW532_private");
      }
      if (myflag == 20113400 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH400_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH400_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113400,runflag, outDataDir + "RD_mu_VBFHWWMH400_CMSSW428");
      }
      if (myflag == 20123400 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH400_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH400_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123400,runflag, outDataDir + "RD_mu_VBFHWWMH400_CMSSW532_private");
      }
      if (myflag == 20113450 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH450_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH450_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113450,runflag, outDataDir + "RD_mu_VBFHWWMH450_CMSSW428");
      }
      if (myflag == 20123450 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH450_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH450_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123450,runflag, outDataDir + "RD_mu_VBFHWWMH450_CMSSW532_private");
      }
      if (myflag == 20113500 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH500_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH500_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113500,runflag, outDataDir + "RD_mu_VBFHWWMH500_CMSSW428");
      }
      if (myflag == 20123500 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH500_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH500_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123500,runflag, outDataDir + "RD_mu_VBFHWWMH500_CMSSW532_private");
      }
      if (myflag == 20113550 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH550_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH550_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113550,runflag, outDataDir + "RD_mu_VBFHWWMH550_CMSSW428");
      }
      if (myflag == 20123550 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH550_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH550_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123550,runflag, outDataDir + "RD_mu_VBFHWWMH550_CMSSW532_private");
      }
      if (myflag == 20113600 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH600_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH600_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113600,runflag, outDataDir + "RD_mu_VBFHWWMH600_CMSSW428");
      }
      if (myflag == 20123600 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH600_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH600_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123600,runflag, outDataDir + "RD_mu_VBFHWWMH600_CMSSW532_private");
      }
      if (myflag == 20123700 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH700_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH700_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123700,runflag, outDataDir + "RD_mu_VBFHWWMH700_CMSSW532_private");
      }
      if (myflag == 20123800 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH800_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH800_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123800,runflag, outDataDir + "RD_mu_VBFHWWMH800_CMSSW532_private");
      }
      if (myflag == 20123900 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH900_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH900_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123900,runflag, outDataDir + "RD_mu_VBFHWWMH900_CMSSW532_private");
      }
      if (myflag == 201231000 || myflag == -300){
         InitCounters( inDataDir + "mu_VBFHWWMH1000_CMSSW532_private.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBFHWWMH1000_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 201231000,runflag, outDataDir + "RD_mu_VBFHWWMH1000_CMSSW532_private");
      }


      // HTauTau MC Signal
      if (myflag == 20114150 || myflag == -400){
         InitCounters( inDataDir + "mu_HWWTauNuMH150_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWTauNuMH150_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114150,runflag, outDataDir + "RD_mu_HWWTauNuMH150_CMSSW428");
      }
      if (myflag == 20114160 || myflag == -400){
         InitCounters( inDataDir + "mu_HWWTauNuMH160_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWTauNuMH160_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114160,runflag, outDataDir + "RD_mu_HWWTauNuMH160_CMSSW428");
      }
      if (myflag == 20114170 || myflag == -400){
         InitCounters( inDataDir + "mu_HWWTauNuMH170_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWTauNuMH170_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114170,runflag, outDataDir + "RD_mu_HWWTauNuMH170_CMSSW428");
      }
      if (myflag == 20114180 || myflag == -400){
         InitCounters( inDataDir + "mu_HWWTauNuMH180_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWTauNuMH180_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114180,runflag, outDataDir + "RD_mu_HWWTauNuMH180_CMSSW428");
      }
      if (myflag == 20114190 || myflag == -400){
         InitCounters( inDataDir + "mu_HWWTauNuMH190_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWTauNuMH190_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114190,runflag, outDataDir + "RD_mu_HWWTauNuMH190_CMSSW428");
      }
      if (myflag == 20114200 || myflag == -400){
         InitCounters( inDataDir + "mu_HWWTauNuMH200_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWTauNuMH200_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114200,runflag, outDataDir + "RD_mu_HWWTauNuMH200_CMSSW428");
      }
      if (myflag == 20114250 || myflag == -400){
         InitCounters( inDataDir + "mu_HWWTauNuMH250_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWTauNuMH250_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114250,runflag, outDataDir + "RD_mu_HWWTauNuMH250_CMSSW428");
      }
      if (myflag == 20114300 || myflag == -400){
         InitCounters( inDataDir + "mu_HWWTauNuMH300_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWTauNuMH300_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114300,runflag, outDataDir + "RD_mu_HWWTauNuMH300_CMSSW428");
      }
      if (myflag == 20114350 || myflag == -400){
         InitCounters( inDataDir + "mu_HWWTauNuMH350_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWTauNuMH350_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114350,runflag, outDataDir + "RD_mu_HWWTauNuMH350_CMSSW428");
      }
      if (myflag == 20114400 || myflag == -400){
         InitCounters( inDataDir + "mu_HWWTauNuMH400_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWTauNuMH400_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114400,runflag, outDataDir + "RD_mu_HWWTauNuMH400_CMSSW428");
      }
      if (myflag == 20114450 || myflag == -400){
         InitCounters( inDataDir + "mu_HWWTauNuMH450_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWTauNuMH450_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114450,runflag, outDataDir + "RD_mu_HWWTauNuMH450_CMSSW428");
      }
      if (myflag == 20114500 || myflag == -400){
         InitCounters( inDataDir + "mu_HWWTauNuMH500_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWTauNuMH500_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114500,runflag, outDataDir + "RD_mu_HWWTauNuMH500_CMSSW428");
      }
      if (myflag == 20114550 || myflag == -400){
         InitCounters( inDataDir + "mu_HWWTauNuMH550_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWTauNuMH550_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114550,runflag, outDataDir + "RD_mu_HWWTauNuMH550_CMSSW428");
      }
      if (myflag == 20114600 || myflag == -400){
         InitCounters( inDataDir + "mu_HWWTauNuMH600_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_HWWTauNuMH600_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114600,runflag, outDataDir + "RD_mu_HWWTauNuMH600_CMSSW428");
      }

      // VBF Background samples generated by Qiang and Andre
      if (myflag == 20115001 || myflag == -400){
         InitCounters( inDataDir + "mu_VBF_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_VBF_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20115001,runflag, outDataDir + "RD_mu_VBF_CMSSW428");
      }

      //new physics samples for the Mjj analysis
      if (myflag == 20115002 || myflag == -400){
         InitCounters( inDataDir + "mu_ZprimeMadGraph_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_ZprimeMadGraph_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20115002,runflag, outDataDir + "RD_mu_ZprimeMadGraph_CMSSW428");
      }
      if (myflag == 20115003 || myflag == -400){
         InitCounters( inDataDir + "mu_TechnicolorPythia_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_TechnicolorPythia_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20115003,runflag, outDataDir + "RD_mu_TechnicolorPythia_CMSSW428");
      }
      if (myflag == 20115004 || myflag == -400){
         InitCounters( inDataDir + "mu_WH150qq_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WH150qq_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20115004,runflag, outDataDir + "RD_mu_WH150qq_CMSSW428");
      }
      if (myflag == 20115005 || myflag == -400){
         InitCounters( inDataDir + "mu_WpJ100KCrossCheck_CMSSW428.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "mu_WpJ100KCrossCheck_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20115005,runflag, outDataDir + "RD_mu_WpJ100KCrossCheck_CMSSW428");
      }
   }

}

void kanamuon::Loop(TH1F* h_events, TH1F* h_events_weighted, int wda, int runflag, const char *outfilename, bool isQCD)
{
   if (fChain == 0) return;
   //Long64_t nentries = fChain->GetEntries();
   // Out Put File Here
   char rootfn[200]; 
   if (runflag ==0 ) {sprintf(rootfn, "%s.root",outfilename);}
   else {             sprintf(rootfn, "%s-VS-%i.root",outfilename,runflag);}
   TFile fresults= TFile(rootfn,"RECREATE");
   // Disable some variables never used to reduce the size of file
   fChain->SetBranchStatus("JetPFCor_etaetaMoment",    0);
   fChain->SetBranchStatus("JetPFCor_phiphiMoment",    0);
   fChain->SetBranchStatus("JetPFCor_etaphiMoment",    0);
   fChain->SetBranchStatus("JetPFCor_maxDistance",    0);
   fChain->SetBranchStatus("JetPFCor_nConstituents",    0);
   fChain->SetBranchStatus("JetPFCor_ChargedHadronEnergy",    0);
   fChain->SetBranchStatus("JetPFCor_ChargedHadronEnergyFrac",    0);
   fChain->SetBranchStatus("JetPFCor_NeutralHadronEnergy",    0);
   fChain->SetBranchStatus("JetPFCor_NeutralHadronEnergyFrac",    0);
   fChain->SetBranchStatus("JetPFCor_ChargedEmEnergy",    0);
   fChain->SetBranchStatus("JetPFCor_ChargedEmEnergyFrac",    0);
   fChain->SetBranchStatus("JetPFCor_ChargedMuEnergy",    0);
   fChain->SetBranchStatus("JetPFCor_ChargedMuEnergyFrac",    0);
   fChain->SetBranchStatus("JetPFCor_NeutralEmEnergy",    0);
   fChain->SetBranchStatus("JetPFCor_NeutralEmEnergyFrac",    0);
   //fChain->SetBranchStatus("JetPFCor_ChargedMultiplicity",    0);
   //fChain->SetBranchStatus("JetPFCor_NeutralMultiplicity",    0);
   fChain->SetBranchStatus("JetPFCor_MuonMultiplicity",    0);
   fChain->SetBranchStatus("JetPFCor_PhotonEnergy",    0);
   fChain->SetBranchStatus("JetPFCor_PhotonEnergyFraction",    0);
   fChain->SetBranchStatus("JetPFCor_ElectronEnergy",    0);
   fChain->SetBranchStatus("JetPFCor_ElectronEnergyFraction",    0);
   fChain->SetBranchStatus("JetPFCor_MuonEnergy",    0);
   fChain->SetBranchStatus("JetPFCor_MuonEnergyFraction",    0);
   fChain->SetBranchStatus("JetPFCor_HFHadronEnergy",    0);
   fChain->SetBranchStatus("JetPFCor_HFHadronEnergyFraction",    0);
   fChain->SetBranchStatus("JetPFCor_HFEMEnergy",    0);
   fChain->SetBranchStatus("JetPFCor_HFEMEnergyFraction",    0);
   fChain->SetBranchStatus("JetPFCor_ChargedHadronMultiplicity",    0);
   fChain->SetBranchStatus("JetPFCor_NeutralHadronMultiplicity",    0);
   fChain->SetBranchStatus("JetPFCor_PhotonMultiplicity",    0);
   fChain->SetBranchStatus("JetPFCor_ElectronMultiplicity",    0);
   fChain->SetBranchStatus("JetPFCor_HFHadronMultiplicity",    0);
   fChain->SetBranchStatus("JetPFCor_HFEMMultiplicity",    0);
   fChain->SetBranchStatus("JetPFCor_SumPtCands",    0);
   fChain->SetBranchStatus("JetPFCor_SumPt2Cands",    0);
   fChain->SetBranchStatus("JetPFCor_rmsCands",    0);
   // Drop most of VBF
   fChain->SetBranchStatus("*VBFTag*",    0);
   fChain->SetBranchStatus("JetPFCorVBFTag_Pt",    1);
   fChain->SetBranchStatus("JetPFCorVBFTag_Eta",    1);
   fChain->SetBranchStatus("JetPFCorVBFTag_Phi",    1);
   fChain->SetBranchStatus("JetPFCorVBFTag_E",    1);
   fChain->SetBranchStatus("JetPFCorVBFTag_bDiscriminator",    1);
   fChain->SetBranchStatus("JetPFCorVBFTag_bDiscriminatorCSV",    1);
   fChain->SetBranchStatus("numPFCorVBFTagJets",    1);
   // Drop gen jet information
   fChain->SetBranchStatus("*Gen*",    0);
   //fChain->SetBranchStatus("W_H_*",    0);  
   fChain->SetBranchStatus("W_Parton_*",    0);  
   fChain->SetBranchStatus("W_Lepton_*",    0);  
   fChain->SetBranchStatus("W_Met_*",    0);
   fChain->SetBranchStatus("W_tParton_*",    0);
   fChain->SetBranchStatus("W_tLepton_*",    0);
   fChain->SetBranchStatus("W_tMet_*",    0);
   fChain->SetBranchStatus("W_tb_*",    0);
   fChain->SetBranchStatus("W_tbbar_*",    0);
   fChain->SetBranchStatus("W_Hb_*",    0);
   fChain->SetBranchStatus("W_Hbbar_*",    0);
   fChain->SetBranchStatus("W_TagQuark_*",    0);

   //Drop Some Groomed information
   fChain->SetBranchStatus("GroomedJet_*_pt_uncorr" , 0);
   fChain->SetBranchStatus("GroomedJet_*_tau1" , 0);
   fChain->SetBranchStatus("GroomedJet_*_tau2" , 0);
   fChain->SetBranchStatus("GroomedJet_*_tau3" , 0);
   fChain->SetBranchStatus("GroomedJet_*_tau4" , 0);
   fChain->SetBranchStatus("GroomedJet_*_pt_*_uncorr" , 0);
   fChain->SetBranchStatus("GroomedJet_*_area", 0);
   fChain->SetBranchStatus("GroomedJet_*_area_tr", 0);
   fChain->SetBranchStatus("GroomedJet_*_area_ft", 0);
   fChain->SetBranchStatus("GroomedJet_*_area_pr", 0);
   fChain->SetBranchStatus("GroomedJet_*_jetcharge", 0); //This may be useful later
   fChain->SetBranchStatus("GroomedJet_*_constituents0_eta", 0);
   fChain->SetBranchStatus("GroomedJet_*_constituents0_phi", 0);
   fChain->SetBranchStatus("GroomedJet_*_constituents0_e", 0);
   fChain->SetBranchStatus("GroomedJet_*_nconstituents0", 0);
   fChain->SetBranchStatus("GroomedJet_*_constituents0pr_eta", 0);
   fChain->SetBranchStatus("GroomedJet_*_constituents0pr_phi", 0);
   fChain->SetBranchStatus("GroomedJet_*_constituents0pr_e", 0);
   fChain->SetBranchStatus("GroomedJet_*_nconstituents0pr", 0);

   //TTree *newtree = fChain->CloneTree();
   TTree *newtree = fChain->CopyTree("numPFCorJets+numPFCorVBFTagJets>=2");
   Long64_t nentries = newtree->GetEntries();
   char textfn[100]; 
   sprintf(textfn,"%s.txt", rootfn);
   FILE *textfile = fopen(textfn,"w");

   Int_t   ggdevt   =0,   evtNJ     =0;
   Int_t   ggdevtinclusive   =0; //For inclusive Jet Bin

   TBranch *branch_ggdevt= newtree->Branch("ggdevt",    &ggdevt,     "ggdevt/I");
   TBranch *branch_evtNJ = newtree->Branch("evtNJ",     &evtNJ,      "evtNJ/I");
   TBranch *branch_ggdevtinclusive = newtree->Branch("ggdevtinclusive", &ggdevtinclusive, "ggdevtinclusive/I");

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

   Float_t TopWm=0,   TopWm5j=0;
   Float_t Tchi2=999, Tchi25j=999;
   TBranch *branch_TopWm   = newtree->Branch("TopWm",       &TopWm,      "TopWm/F");
   TBranch *branch_TopWm5j = newtree->Branch("TopWm5j",     &TopWm5j,    "TopWm5j/F");
   TBranch *branch_Tchi2   = newtree->Branch("Tchi2",       &Tchi2,      "Tchi2/F");
   TBranch *branch_Tchi25j = newtree->Branch("Tchi25j",     &Tchi25j,    "Tchi25j/F");

   Float_t ang_ha   = 999, ang_hb = 999, ang_hs = 999, ang_phi = 999, ang_phia = 999, ang_phib = 999;
   Float_t masslvjj =-999, ptlvjj =-999,  ylvjj = -999,philvjj = -999;
   TBranch * branch_ha   =  newtree->Branch("ang_ha",   &ang_ha,    "ang_ha/F");
   TBranch * branch_hb   =  newtree->Branch("ang_hb",   &ang_hb,    "ang_hb/F");
   TBranch * branch_hs   =  newtree->Branch("ang_hs",   &ang_hs,    "ang_hs/F");
   TBranch * branch_phi  =  newtree->Branch("ang_phi",  &ang_phi,   "ang_phi/F");
   TBranch * branch_phia =  newtree->Branch("ang_phia", &ang_phia,  "ang_phia/F");
   TBranch * branch_phib =  newtree->Branch("ang_phib", &ang_phib,  "ang_phib/F");
   TBranch * branch_orgm =  newtree->Branch("masslvjj", &masslvjj,  "masslvjj/F");
   TBranch * branch_orgpt=  newtree->Branch("ptlvjj",   &ptlvjj,    "ptlvjj/F");
   TBranch * branch_orgy =  newtree->Branch("ylvjj",    &ylvjj,     "ylvjj/F");
   TBranch * branch_orgph=  newtree->Branch("philvjj",  &philvjj,   "philvjj/F");

   Float_t mva2j160mu = 999, mva2j170mu = 999, mva2j180mu = 999, mva2j190mu = 999, mva2j200mu = 999, mva2j250mu = 999, mva2j300mu = 999, mva2j350mu = 999, mva2j400mu = 999, mva2j450mu = 999, mva2j500mu = 999, mva2j550mu = 999, mva2j600mu = 999;
   Float_t mva2j400interferencenominalmu = 999, mva2j450interferencenominalmu = 999, mva2j500interferencenominalmu = 999, mva2j550interferencenominalmu = 999, mva2j600interferencenominalmu = 999, mva2j700interferencenominalmu = 999, mva2j800interferencenominalmu = 999, mva2j900interferencenominalmu = 999, mva2j1000interferencenominalmu = 999;
   Float_t mva2j400interferencedownmu = 999, mva2j450interferencedownmu = 999, mva2j500interferencedownmu = 999, mva2j550interferencedownmu = 999, mva2j600interferencedownmu = 999, mva2j700interferencedownmu = 999, mva2j800interferencedownmu = 999, mva2j900interferencedownmu = 999, mva2j1000interferencedownmu = 999;
   Float_t mva2j400interferenceupmu = 999, mva2j450interferenceupmu = 999, mva2j500interferenceupmu = 999, mva2j550interferenceupmu = 999, mva2j600interferenceupmu = 999, mva2j700interferenceupmu = 999, mva2j800interferenceupmu = 999, mva2j900interferenceupmu = 999, mva2j1000interferenceupmu = 999;

   Float_t mva3j160mu = 999, mva3j170mu = 999, mva3j180mu = 999, mva3j190mu = 999, mva3j200mu = 999, mva3j250mu = 999, mva3j300mu = 999, mva3j350mu = 999, mva3j400mu = 999, mva3j450mu = 999, mva3j500mu = 999, mva3j550mu = 999, mva3j600mu = 999;
   Float_t mva3j400interferencenominalmu = 999, mva3j450interferencenominalmu = 999, mva3j500interferencenominalmu = 999, mva3j550interferencenominalmu = 999, mva3j600interferencenominalmu = 999, mva3j700interferencenominalmu = 999, mva3j800interferencenominalmu = 999, mva3j900interferencenominalmu = 999, mva3j1000interferencenominalmu = 999;
   Float_t mva3j400interferencedownmu = 999, mva3j450interferencedownmu = 999, mva3j500interferencedownmu = 999, mva3j550interferencedownmu = 999, mva3j600interferencedownmu = 999, mva3j700interferencedownmu = 999, mva3j800interferencedownmu = 999, mva3j900interferencedownmu = 999, mva3j1000interferencedownmu = 999;
   Float_t mva3j400interferenceupmu = 999, mva3j450interferenceupmu = 999, mva3j500interferenceupmu = 999, mva3j550interferenceupmu = 999, mva3j600interferenceupmu = 999, mva3j700interferenceupmu = 999, mva3j800interferenceupmu = 999, mva3j900interferenceupmu = 999, mva3j1000interferenceupmu = 999;
   Float_t mva2jdibosonmu = 999,mva3jdibosonmu = 999, mva2jdibnoqgmu = 999,mva3jdibnoqgmu = 999;
   Float_t mvavbf160mu = 999, mvavbf170mu = 999, mvavbf180mu = 999, mvavbf190mu = 999, mvavbf200mu = 999, mvavbf250mu = 999, mvavbf300mu = 999, mvavbf350mu = 999, mvavbf400mu = 999, mvavbf450mu = 999, mvavbf500mu = 999, mvavbf550mu = 999, mvavbf600mu = 999;

   TBranch * branch_2j160mu   =  newtree->Branch("mva2j160mu",   &mva2j160mu,    "mva2j160mu/F");
   TBranch * branch_2j170mu   =  newtree->Branch("mva2j170mu",   &mva2j170mu,    "mva2j170mu/F");
   TBranch * branch_2j180mu   =  newtree->Branch("mva2j180mu",   &mva2j180mu,    "mva2j180mu/F");
   TBranch * branch_2j190mu   =  newtree->Branch("mva2j190mu",   &mva2j190mu,    "mva2j190mu/F");
   TBranch * branch_2j200mu   =  newtree->Branch("mva2j200mu",   &mva2j200mu,    "mva2j200mu/F");
   TBranch * branch_2j250mu   =  newtree->Branch("mva2j250mu",   &mva2j250mu,    "mva2j250mu/F");
   TBranch * branch_2j300mu   =  newtree->Branch("mva2j300mu",   &mva2j300mu,    "mva2j300mu/F");
   TBranch * branch_2j350mu   =  newtree->Branch("mva2j350mu",   &mva2j350mu,    "mva2j350mu/F");
   TBranch * branch_2j400mu   =  newtree->Branch("mva2j400mu",   &mva2j400mu,    "mva2j400mu/F");
   TBranch * branch_2j450mu   =  newtree->Branch("mva2j450mu",   &mva2j450mu,    "mva2j450mu/F");
   TBranch * branch_2j500mu   =  newtree->Branch("mva2j500mu",   &mva2j500mu,    "mva2j500mu/F");
   TBranch * branch_2j550mu   =  newtree->Branch("mva2j550mu",   &mva2j550mu,    "mva2j550mu/F");
   TBranch * branch_2j600mu   =  newtree->Branch("mva2j600mu",   &mva2j600mu,    "mva2j600mu/F");
   TBranch * branch_2j400interferencenominalmu   =  newtree->Branch("mva2j400interferencenominalmu",   &mva2j400interferencenominalmu,    "mva2j400interferencenominalmu/F");
   TBranch * branch_2j450interferencenominalmu   =  newtree->Branch("mva2j450interferencenominalmu",   &mva2j450interferencenominalmu,    "mva2j450interferencenominalmu/F");
   TBranch * branch_2j500interferencenominalmu   =  newtree->Branch("mva2j500interferencenominalmu",   &mva2j500interferencenominalmu,    "mva2j500interferencenominalmu/F");
   TBranch * branch_2j550interferencenominalmu   =  newtree->Branch("mva2j550interferencenominalmu",   &mva2j550interferencenominalmu,    "mva2j550interferencenominalmu/F");
   TBranch * branch_2j600interferencenominalmu   =  newtree->Branch("mva2j600interferencenominalmu",   &mva2j600interferencenominalmu,    "mva2j600interferencenominalmu/F");
   TBranch * branch_2j700interferencenominalmu   =  newtree->Branch("mva2j700interferencenominalmu",   &mva2j700interferencenominalmu,    "mva2j700interferencenominalmu/F");
   TBranch * branch_2j800interferencenominalmu   =  newtree->Branch("mva2j800interferencenominalmu",   &mva2j800interferencenominalmu,    "mva2j800interferencenominalmu/F");
   TBranch * branch_2j900interferencenominalmu   =  newtree->Branch("mva2j900interferencenominalmu",   &mva2j900interferencenominalmu,    "mva2j900interferencenominalmu/F");
   TBranch * branch_2j1000interferencenominalmu   =  newtree->Branch("mva2j1000interferencenominalmu",   &mva2j1000interferencenominalmu,    "mva2j1000interferencenominalmu/F");
   TBranch * branch_2j400interferenceupmu   =  newtree->Branch("mva2j400interferenceupmu",   &mva2j400interferenceupmu,    "mva2j400interferenceupmu/F");
   TBranch * branch_2j450interferenceupmu   =  newtree->Branch("mva2j450interferenceupmu",   &mva2j450interferenceupmu,    "mva2j450interferenceupmu/F");
   TBranch * branch_2j500interferenceupmu   =  newtree->Branch("mva2j500interferenceupmu",   &mva2j500interferenceupmu,    "mva2j500interferenceupmu/F");
   TBranch * branch_2j550interferenceupmu   =  newtree->Branch("mva2j550interferenceupmu",   &mva2j550interferenceupmu,    "mva2j550interferenceupmu/F");
   TBranch * branch_2j600interferenceupmu   =  newtree->Branch("mva2j600interferenceupmu",   &mva2j600interferenceupmu,    "mva2j600interferenceupmu/F");
   TBranch * branch_2j700interferenceupmu   =  newtree->Branch("mva2j700interferenceupmu",   &mva2j700interferenceupmu,    "mva2j700interferenceupmu/F");
   TBranch * branch_2j800interferenceupmu   =  newtree->Branch("mva2j800interferenceupmu",   &mva2j800interferenceupmu,    "mva2j800interferenceupmu/F");
   TBranch * branch_2j900interferenceupmu   =  newtree->Branch("mva2j900interferenceupmu",   &mva2j900interferenceupmu,    "mva2j900interferenceupmu/F");
   TBranch * branch_2j1000interferenceupmu   =  newtree->Branch("mva2j1000interferenceupmu",   &mva2j1000interferenceupmu,    "mva2j1000interferenceupmu/F");
   TBranch * branch_2j400interferencedownmu   =  newtree->Branch("mva2j400interferencedownmu",   &mva2j400interferencedownmu,    "mva2j400interferencedownmu/F");
   TBranch * branch_2j450interferencedownmu   =  newtree->Branch("mva2j450interferencedownmu",   &mva2j450interferencedownmu,    "mva2j450interferencedownmu/F");
   TBranch * branch_2j500interferencedownmu   =  newtree->Branch("mva2j500interferencedownmu",   &mva2j500interferencedownmu,    "mva2j500interferencedownmu/F");
   TBranch * branch_2j550interferencedownmu   =  newtree->Branch("mva2j550interferencedownmu",   &mva2j550interferencedownmu,    "mva2j550interferencedownmu/F");
   TBranch * branch_2j600interferencedownmu   =  newtree->Branch("mva2j600interferencedownmu",   &mva2j600interferencedownmu,    "mva2j600interferencedownmu/F");
   TBranch * branch_2j700interferencedownmu   =  newtree->Branch("mva2j700interferencedownmu",   &mva2j700interferencedownmu,    "mva2j700interferencedownmu/F");
   TBranch * branch_2j800interferencedownmu   =  newtree->Branch("mva2j800interferencedownmu",   &mva2j800interferencedownmu,    "mva2j800interferencedownmu/F");
   TBranch * branch_2j900interferencedownmu   =  newtree->Branch("mva2j900interferencedownmu",   &mva2j900interferencedownmu,    "mva2j900interferencedownmu/F");
   TBranch * branch_2j1000interferencedownmu   =  newtree->Branch("mva2j1000interferencedownmu",   &mva2j1000interferencedownmu,    "mva2j1000interferencedownmu/F");

   TBranch * branch_3j160mu   =  newtree->Branch("mva3j160mu",   &mva3j160mu,    "mva3j160mu/F");
   TBranch * branch_3j170mu   =  newtree->Branch("mva3j170mu",   &mva3j170mu,    "mva3j170mu/F");
   TBranch * branch_3j180mu   =  newtree->Branch("mva3j180mu",   &mva3j180mu,    "mva3j180mu/F");
   TBranch * branch_3j190mu   =  newtree->Branch("mva3j190mu",   &mva3j190mu,    "mva3j190mu/F");
   TBranch * branch_3j200mu   =  newtree->Branch("mva3j200mu",   &mva3j200mu,    "mva3j200mu/F");
   TBranch * branch_3j250mu   =  newtree->Branch("mva3j250mu",   &mva3j250mu,    "mva3j250mu/F");
   TBranch * branch_3j300mu   =  newtree->Branch("mva3j300mu",   &mva3j300mu,    "mva3j300mu/F");
   TBranch * branch_3j350mu   =  newtree->Branch("mva3j350mu",   &mva3j350mu,    "mva3j350mu/F");
   TBranch * branch_3j400mu   =  newtree->Branch("mva3j400mu",   &mva3j400mu,    "mva3j400mu/F");
   TBranch * branch_3j450mu   =  newtree->Branch("mva3j450mu",   &mva3j450mu,    "mva3j450mu/F");
   TBranch * branch_3j500mu   =  newtree->Branch("mva3j500mu",   &mva3j500mu,    "mva3j500mu/F");
   TBranch * branch_3j550mu   =  newtree->Branch("mva3j550mu",   &mva3j550mu,    "mva3j550mu/F");
   TBranch * branch_3j600mu   =  newtree->Branch("mva3j600mu",   &mva3j600mu,    "mva3j600mu/F");
   TBranch * branch_3j400interferencenominalmu   =  newtree->Branch("mva3j400interferencenominalmu",   &mva3j400interferencenominalmu,    "mva3j400interferencenominalmu/F");
   TBranch * branch_3j450interferencenominalmu   =  newtree->Branch("mva3j450interferencenominalmu",   &mva3j450interferencenominalmu,    "mva3j450interferencenominalmu/F");
   TBranch * branch_3j500interferencenominalmu   =  newtree->Branch("mva3j500interferencenominalmu",   &mva3j500interferencenominalmu,    "mva3j500interferencenominalmu/F");
   TBranch * branch_3j550interferencenominalmu   =  newtree->Branch("mva3j550interferencenominalmu",   &mva3j550interferencenominalmu,    "mva3j550interferencenominalmu/F");
   TBranch * branch_3j600interferencenominalmu   =  newtree->Branch("mva3j600interferencenominalmu",   &mva3j600interferencenominalmu,    "mva3j600interferencenominalmu/F");
   TBranch * branch_3j700interferencenominalmu   =  newtree->Branch("mva3j700interferencenominalmu",   &mva3j700interferencenominalmu,    "mva3j700interferencenominalmu/F");
   TBranch * branch_3j800interferencenominalmu   =  newtree->Branch("mva3j800interferencenominalmu",   &mva3j800interferencenominalmu,    "mva3j800interferencenominalmu/F");
   TBranch * branch_3j900interferencenominalmu   =  newtree->Branch("mva3j900interferencenominalmu",   &mva3j900interferencenominalmu,    "mva3j900interferencenominalmu/F");
   TBranch * branch_3j1000interferencenominalmu   =  newtree->Branch("mva3j1000interferencenominalmu",   &mva3j1000interferencenominalmu,    "mva3j1000interferencenominalmu/F");
   TBranch * branch_3j400interferenceupmu   =  newtree->Branch("mva3j400interferenceupmu",   &mva3j400interferenceupmu,    "mva3j400interferenceupmu/F");
   TBranch * branch_3j450interferenceupmu   =  newtree->Branch("mva3j450interferenceupmu",   &mva3j450interferenceupmu,    "mva3j450interferenceupmu/F");
   TBranch * branch_3j500interferenceupmu   =  newtree->Branch("mva3j500interferenceupmu",   &mva3j500interferenceupmu,    "mva3j500interferenceupmu/F");
   TBranch * branch_3j550interferenceupmu   =  newtree->Branch("mva3j550interferenceupmu",   &mva3j550interferenceupmu,    "mva3j550interferenceupmu/F");
   TBranch * branch_3j600interferenceupmu   =  newtree->Branch("mva3j600interferenceupmu",   &mva3j600interferenceupmu,    "mva3j600interferenceupmu/F");
   TBranch * branch_3j700interferenceupmu   =  newtree->Branch("mva3j700interferenceupmu",   &mva3j700interferenceupmu,    "mva3j700interferenceupmu/F");
   TBranch * branch_3j800interferenceupmu   =  newtree->Branch("mva3j800interferenceupmu",   &mva3j800interferenceupmu,    "mva3j800interferenceupmu/F");
   TBranch * branch_3j900interferenceupmu   =  newtree->Branch("mva3j900interferenceupmu",   &mva3j900interferenceupmu,    "mva3j900interferenceupmu/F");
   TBranch * branch_3j1000interferenceupmu   =  newtree->Branch("mva3j1000interferenceupmu",   &mva3j1000interferenceupmu,    "mva3j1000interferenceupmu/F");
   TBranch * branch_3j400interferencedownmu   =  newtree->Branch("mva3j400interferencedownmu",   &mva3j400interferencedownmu,    "mva3j400interferencedownmu/F");
   TBranch * branch_3j450interferencedownmu   =  newtree->Branch("mva3j450interferencedownmu",   &mva3j450interferencedownmu,    "mva3j450interferencedownmu/F");
   TBranch * branch_3j500interferencedownmu   =  newtree->Branch("mva3j500interferencedownmu",   &mva3j500interferencedownmu,    "mva3j500interferencedownmu/F");
   TBranch * branch_3j550interferencedownmu   =  newtree->Branch("mva3j550interferencedownmu",   &mva3j550interferencedownmu,    "mva3j550interferencedownmu/F");
   TBranch * branch_3j600interferencedownmu   =  newtree->Branch("mva3j600interferencedownmu",   &mva3j600interferencedownmu,    "mva3j600interferencedownmu/F");
   TBranch * branch_3j700interferencedownmu   =  newtree->Branch("mva3j700interferencedownmu",   &mva3j700interferencedownmu,    "mva3j700interferencedownmu/F");
   TBranch * branch_3j800interferencedownmu   =  newtree->Branch("mva3j800interferencedownmu",   &mva3j800interferencedownmu,    "mva3j800interferencedownmu/F");
   TBranch * branch_3j900interferencedownmu   =  newtree->Branch("mva3j900interferencedownmu",   &mva3j900interferencedownmu,    "mva3j900interferencedownmu/F");
   TBranch * branch_3j1000interferencedownmu   =  newtree->Branch("mva3j1000interferencedownmu",   &mva3j1000interferencedownmu,    "mva3j1000interferencedownmu/F");

   TBranch * branch_2jdibosonmu   =  newtree->Branch("mva2jdibosonmu",   &mva2jdibosonmu,    "mva2jdibosonmu/F");
   TBranch * branch_3jdibosonmu   =  newtree->Branch("mva3jdibosonmu",   &mva3jdibosonmu,    "mva3jdibosonmu/F");
   TBranch * branch_2jdibnoqgmu   =  newtree->Branch("mva2jdibnoqgmu",   &mva2jdibnoqgmu,    "mva2jdibnoqgmu/F");
   TBranch * branch_3jdibnoqgmu   =  newtree->Branch("mva3jdibnoqgmu",   &mva3jdibnoqgmu,    "mva3jdibnoqgmu/F");

   TBranch * branch_vbf160mu   =  newtree->Branch("mvavbf160mu",   &mvavbf160mu,    "mvavbf160mu/F");
   TBranch * branch_vbf170mu   =  newtree->Branch("mvavbf170mu",   &mvavbf170mu,    "mvavbf170mu/F");
   TBranch * branch_vbf180mu   =  newtree->Branch("mvavbf180mu",   &mvavbf180mu,    "mvavbf180mu/F");
   TBranch * branch_vbf190mu   =  newtree->Branch("mvavbf190mu",   &mvavbf190mu,    "mvavbf190mu/F");
   TBranch * branch_vbf200mu   =  newtree->Branch("mvavbf200mu",   &mvavbf200mu,    "mvavbf200mu/F");
   TBranch * branch_vbf250mu   =  newtree->Branch("mvavbf250mu",   &mvavbf250mu,    "mvavbf250mu/F");
   TBranch * branch_vbf300mu   =  newtree->Branch("mvavbf300mu",   &mvavbf300mu,    "mvavbf300mu/F");
   TBranch * branch_vbf350mu   =  newtree->Branch("mvavbf350mu",   &mvavbf350mu,    "mvavbf350mu/F");
   TBranch * branch_vbf400mu   =  newtree->Branch("mvavbf400mu",   &mvavbf400mu,    "mvavbf400mu/F");
   TBranch * branch_vbf450mu   =  newtree->Branch("mvavbf450mu",   &mvavbf450mu,    "mvavbf450mu/F");
   TBranch * branch_vbf500mu   =  newtree->Branch("mvavbf500mu",   &mvavbf500mu,    "mvavbf500mu/F");
   TBranch * branch_vbf550mu   =  newtree->Branch("mvavbf550mu",   &mvavbf550mu,    "mvavbf550mu/F");
   TBranch * branch_vbf600mu   =  newtree->Branch("mvavbf600mu",   &mvavbf600mu,    "mvavbf600mu/F");

   Float_t effwt = 1.0, puwt = 1.0, puwt_up = 1.0, puwt_down = 1.0;
   TBranch * branch_effwt          =  newtree->Branch("effwt",       &effwt,        "effwt/F");
   TBranch * branch_puwt           =  newtree->Branch("puwt",        &puwt,         "puwt/F");
   TBranch * branch_puwt_up        =  newtree->Branch("puwt_up",     &puwt_up,      "puwt_up/F");
   TBranch * branch_puwt_down      =  newtree->Branch("puwt_down",   &puwt_down,    "puwt_down/F");

   //Interference Effect Correction
   Float_t  interferencewtggH400 = 1.0, interferencewtggH450 = 1.0, interferencewtggH500 = 1.0, interferencewtggH550 = 1.0, interferencewtggH600 = 1.0, interferencewtggH700 = 1.0, interferencewtggH800 = 1.0, interferencewtggH900 = 1.0, interferencewtggH1000 = 1.0;
   Float_t interferencewt_upggH400 = 1.0, interferencewt_upggH450 = 1.0, interferencewt_upggH500 = 1.0, interferencewt_upggH550 = 1.0, interferencewt_upggH600 = 1.0, interferencewt_upggH700 = 1.0, interferencewt_upggH800 = 1.0, interferencewt_upggH900 = 1.0, interferencewt_upggH1000 = 1.0;
   Float_t interferencewt_downggH400 = 1.0, interferencewt_downggH450 = 1.0, interferencewt_downggH500 = 1.0, interferencewt_downggH550 = 1.0, interferencewt_downggH600 = 1.0, interferencewt_downggH700 = 1.0, interferencewt_downggH800 = 1.0, interferencewt_downggH900 = 1.0, interferencewt_downggH1000 = 1.0;

   TBranch *branch_interferencewtggH400 = newtree->Branch("interferencewtggH400",&interferencewtggH400,"interferencewtggH400/F");
   TBranch *branch_interferencewtggH450 = newtree->Branch("interferencewtggH450",&interferencewtggH450,"interferencewtggH450/F");
   TBranch *branch_interferencewtggH500 = newtree->Branch("interferencewtggH500",&interferencewtggH500,"interferencewtggH500/F");
   TBranch *branch_interferencewtggH550 = newtree->Branch("interferencewtggH550",&interferencewtggH550,"interferencewtggH550/F");
   TBranch *branch_interferencewtggH600 = newtree->Branch("interferencewtggH600",&interferencewtggH600,"interferencewtggH600/F");
   TBranch *branch_interferencewtggH700 = newtree->Branch("interferencewtggH700",&interferencewtggH700,"interferencewtggH700/F");
   TBranch *branch_interferencewtggH800 = newtree->Branch("interferencewtggH800",&interferencewtggH800,"interferencewtggH800/F");
   TBranch *branch_interferencewtggH900 = newtree->Branch("interferencewtggH900",&interferencewtggH900,"interferencewtggH900/F");
   TBranch *branch_interferencewtggH1000 = newtree->Branch("interferencewtggH1000",&interferencewtggH1000,"interferencewtggH1000/F");

   TBranch *branch_interferencewt_upggH400 = newtree->Branch("interferencewt_upggH400",&interferencewt_upggH400,"interferencewt_upggH400/F");
   TBranch *branch_interferencewt_upggH450 = newtree->Branch("interferencewt_upggH450",&interferencewt_upggH450,"interferencewt_upggH450/F");
   TBranch *branch_interferencewt_upggH500 = newtree->Branch("interferencewt_upggH500",&interferencewt_upggH500,"interferencewt_upggH500/F");
   TBranch *branch_interferencewt_upggH550 = newtree->Branch("interferencewt_upggH550",&interferencewt_upggH550,"interferencewt_upggH550/F");
   TBranch *branch_interferencewt_upggH600 = newtree->Branch("interferencewt_upggH600",&interferencewt_upggH600,"interferencewt_upggH600/F");
   TBranch *branch_interferencewt_upggH700 = newtree->Branch("interferencewt_upggH700",&interferencewt_upggH700,"interferencewt_upggH700/F");
   TBranch *branch_interferencewt_upggH800 = newtree->Branch("interferencewt_upggH800",&interferencewt_upggH800,"interferencewt_upggH800/F");
   TBranch *branch_interferencewt_upggH900 = newtree->Branch("interferencewt_upggH900",&interferencewt_upggH900,"interferencewt_upggH900/F");
   TBranch *branch_interferencewt_upggH1000 = newtree->Branch("interferencewt_upggH1000",&interferencewt_upggH1000,"interferencewt_upggH1000/F");

   TBranch *branch_interferencewt_downggH400 = newtree->Branch("interferencewt_downggH400",&interferencewt_downggH400,"interferencewt_downggH400/F");
   TBranch *branch_interferencewt_downggH450 = newtree->Branch("interferencewt_downggH450",&interferencewt_downggH450,"interferencewt_downggH450/F");
   TBranch *branch_interferencewt_downggH500 = newtree->Branch("interferencewt_downggH500",&interferencewt_downggH500,"interferencewt_downggH500/F");
   TBranch *branch_interferencewt_downggH550 = newtree->Branch("interferencewt_downggH550",&interferencewt_downggH550,"interferencewt_downggH550/F");
   TBranch *branch_interferencewt_downggH600 = newtree->Branch("interferencewt_downggH600",&interferencewt_downggH600,"interferencewt_downggH600/F");
   TBranch *branch_interferencewt_downggH700 = newtree->Branch("interferencewt_downggH700",&interferencewt_downggH700,"interferencewt_downggH700/F");
   TBranch *branch_interferencewt_downggH800 = newtree->Branch("interferencewt_downggH800",&interferencewt_downggH800,"interferencewt_downggH800/F");
   TBranch *branch_interferencewt_downggH900 = newtree->Branch("interferencewt_downggH900",&interferencewt_downggH900,"interferencewt_downggH900/F");
   TBranch *branch_interferencewt_downggH1000 = newtree->Branch("interferencewt_downggH1000",&interferencewt_downggH1000,"interferencewt_downggH1000/F");

   //Complex Pole Weight
   Float_t complexpolewtggH180 = 1.0, complexpolewtggH190 = 1.0, complexpolewtggH200 = 1.0, complexpolewtggH250 = 1.0, complexpolewtggH300 = 1.0, complexpolewtggH350 = 1.0, complexpolewtggH400 = 1.0, complexpolewtggH450 = 1.0, complexpolewtggH500 = 1.0, complexpolewtggH550 = 1.0, complexpolewtggH600 = 1.0, complexpolewtggH700 = 1.0, complexpolewtggH800 = 1.0, complexpolewtggH900 = 1.0, complexpolewtggH1000 = 1.0;
   TBranch *branch_complexpolewtggH180 = newtree->Branch("complexpolewtggH180",&complexpolewtggH180,"complexpolewtggH180/F");
   TBranch *branch_complexpolewtggH190 = newtree->Branch("complexpolewtggH190",&complexpolewtggH190,"complexpolewtggH190/F");
   TBranch *branch_complexpolewtggH200 = newtree->Branch("complexpolewtggH200",&complexpolewtggH200,"complexpolewtggH200/F");
   TBranch *branch_complexpolewtggH250 = newtree->Branch("complexpolewtggH250",&complexpolewtggH250,"complexpolewtggH250/F");
   TBranch *branch_complexpolewtggH300 = newtree->Branch("complexpolewtggH300",&complexpolewtggH300,"complexpolewtggH300/F");
   TBranch *branch_complexpolewtggH350 = newtree->Branch("complexpolewtggH350",&complexpolewtggH350,"complexpolewtggH350/F");
   TBranch *branch_complexpolewtggH400 = newtree->Branch("complexpolewtggH400",&complexpolewtggH400,"complexpolewtggH400/F");
   TBranch *branch_complexpolewtggH450 = newtree->Branch("complexpolewtggH450",&complexpolewtggH450,"complexpolewtggH450/F");
   TBranch *branch_complexpolewtggH500 = newtree->Branch("complexpolewtggH500",&complexpolewtggH500,"complexpolewtggH500/F");
   TBranch *branch_complexpolewtggH550 = newtree->Branch("complexpolewtggH550",&complexpolewtggH550,"complexpolewtggH550/F");
   TBranch *branch_complexpolewtggH600 = newtree->Branch("complexpolewtggH600",&complexpolewtggH600,"complexpolewtggH600/F");
   TBranch *branch_complexpolewtggH700 = newtree->Branch("complexpolewtggH700",&complexpolewtggH700,"complexpolewtggH700/F");
   TBranch *branch_complexpolewtggH800 = newtree->Branch("complexpolewtggH800",&complexpolewtggH800,"complexpolewtggH800/F");
   TBranch *branch_complexpolewtggH900 = newtree->Branch("complexpolewtggH900",&complexpolewtggH900,"complexpolewtggH900/F");
   TBranch *branch_complexpolewtggH1000 = newtree->Branch("complexpolewtggH1000",&complexpolewtggH1000,"complexpolewtggH1000/F");

   //Average Complex Pole Weight
   Float_t avecomplexpolewtggH180 = 1.0, avecomplexpolewtggH190 = 1.0, avecomplexpolewtggH200 = 1.0, avecomplexpolewtggH250 = 1.0, avecomplexpolewtggH300 = 1.0, avecomplexpolewtggH350 = 1.0, avecomplexpolewtggH400 = 1.0, avecomplexpolewtggH450 = 1.0, avecomplexpolewtggH500 = 1.0, avecomplexpolewtggH550 = 1.0, avecomplexpolewtggH600 = 1.0, avecomplexpolewtggH700 = 1.0, avecomplexpolewtggH800 = 1.0, avecomplexpolewtggH900 = 1.0, avecomplexpolewtggH1000 = 1.0;
   TBranch *branch_avecomplexpolewtggH180 = newtree->Branch("avecomplexpolewtggH180",&avecomplexpolewtggH180,"avecomplexpolewtggH180/F");
   TBranch *branch_avecomplexpolewtggH190 = newtree->Branch("avecomplexpolewtggH190",&avecomplexpolewtggH190,"avecomplexpolewtggH190/F");
   TBranch *branch_avecomplexpolewtggH200 = newtree->Branch("avecomplexpolewtggH200",&avecomplexpolewtggH200,"avecomplexpolewtggH200/F");
   TBranch *branch_avecomplexpolewtggH250 = newtree->Branch("avecomplexpolewtggH250",&avecomplexpolewtggH250,"avecomplexpolewtggH250/F");
   TBranch *branch_avecomplexpolewtggH300 = newtree->Branch("avecomplexpolewtggH300",&avecomplexpolewtggH300,"avecomplexpolewtggH300/F");
   TBranch *branch_avecomplexpolewtggH350 = newtree->Branch("avecomplexpolewtggH350",&avecomplexpolewtggH350,"avecomplexpolewtggH350/F");
   TBranch *branch_avecomplexpolewtggH400 = newtree->Branch("avecomplexpolewtggH400",&avecomplexpolewtggH400,"avecomplexpolewtggH400/F");
   TBranch *branch_avecomplexpolewtggH450 = newtree->Branch("avecomplexpolewtggH450",&avecomplexpolewtggH450,"avecomplexpolewtggH450/F");
   TBranch *branch_avecomplexpolewtggH500 = newtree->Branch("avecomplexpolewtggH500",&avecomplexpolewtggH500,"avecomplexpolewtggH500/F");
   TBranch *branch_avecomplexpolewtggH550 = newtree->Branch("avecomplexpolewtggH550",&avecomplexpolewtggH550,"avecomplexpolewtggH550/F");
   TBranch *branch_avecomplexpolewtggH600 = newtree->Branch("avecomplexpolewtggH600",&avecomplexpolewtggH600,"avecomplexpolewtggH600/F");
   TBranch *branch_avecomplexpolewtggH700 = newtree->Branch("avecomplexpolewtggH700",&avecomplexpolewtggH700,"avecomplexpolewtggH700/F");
   TBranch *branch_avecomplexpolewtggH800 = newtree->Branch("avecomplexpolewtggH800",&avecomplexpolewtggH800,"avecomplexpolewtggH800/F");
   TBranch *branch_avecomplexpolewtggH900 = newtree->Branch("avecomplexpolewtggH900",&avecomplexpolewtggH900,"avecomplexpolewtggH900/F");
   TBranch *branch_avecomplexpolewtggH1000 = newtree->Branch("avecomplexpolewtggH1000",&avecomplexpolewtggH1000,"avecomplexpolewtggH1000/F");

   Float_t qgld_Spring11[6]={-1,-1,-1,-1,-1,-1}; 
   Float_t qgld_Summer11[6]={-1,-1,-1,-1,-1,-1};
   Float_t qgld_Summer11CHS[6]={-1,-1,-1,-1,-1,-1};

   TBranch * branch_qgld_Spring11     =  newtree->Branch("qgld_Spring11",     qgld_Spring11,        "qgld_Spring11[6]/F");
   TBranch * branch_qgld_Summer11     =  newtree->Branch("qgld_Summer11",     qgld_Summer11,        "qgld_Summer11[6]/F");
   TBranch * branch_qgld_Summer11CHS  =  newtree->Branch("qgld_Summer11CHS",  qgld_Summer11CHS,     "qgld_Summer11CHS[6]/F");

   //Event Flag for Boosted W Analysis
   Int_t isgengdboostedWevt = 0;
   TBranch *branch_isgengdboostedWevt = newtree->Branch("isgengdboostedWevt", &isgengdboostedWevt, "isgengdboostedWevt/I");

   Int_t   ggdboostedWevt =0;
   TBranch *branch_ggdboostedWevt = newtree->Branch("ggdboostedWevt", &ggdboostedWevt, "ggdboostedWevt/I"); 

   Int_t   GroomedJet_numberbjets_csvl = 0;
   TBranch *branch_GroomedJet_numberbjets_csvl = newtree->Branch("GroomedJet_numberbjets_csvl", &GroomedJet_numberbjets_csvl,"GroomedJet_numberbjets_csvl/I");

   Int_t   GroomedJet_numberbjets_csvm = 0;
   TBranch *branch_GroomedJet_numberbjets_csvm = newtree->Branch("GroomedJet_numberbjets_csvm", &GroomedJet_numberbjets_csvm,"GroomedJet_numberbjets_csvm/I");

   Int_t   GroomedJet_numberbjets_ssvhem = 0;
   TBranch *branch_GroomedJet_numberbjets_ssvhem = newtree->Branch("GroomedJet_numberbjets_ssvhem", &GroomedJet_numberbjets_ssvhem,"GroomedJet_numberbjets_ssvhem/I");

   Int_t   GroomedJet_numberbjets_csvl_veto = 0;
   TBranch *branch_GroomedJet_numberbjets_csvl_veto = newtree->Branch("GroomedJet_numberbjets_csvl_veto", &GroomedJet_numberbjets_csvl_veto,"GroomedJet_numberbjets_csvl_veto/I");

   Int_t   GroomedJet_numberbjets_csvm_veto = 0;
   TBranch *branch_GroomedJet_numberbjets_csvm_veto = newtree->Branch("GroomedJet_numberbjets_csvm_veto", &GroomedJet_numberbjets_csvm_veto,"GroomedJet_numberbjets_csvm_veto/I");

   Int_t   GroomedJet_numberbjets_ssvhem_veto = 0;
   TBranch *branch_GroomedJet_numberbjets_ssvhem_veto = newtree->Branch("GroomedJet_numberbjets_ssvhem_veto", &GroomedJet_numberbjets_ssvhem_veto,"GroomedJet_numberbjets_ssvhem_veto/I");

   Int_t   GroomedJet_numberjets = 0;
   TBranch *branch_GroomedJet_numberjets = newtree->Branch("GroomedJet_numberjets", &GroomedJet_numberjets,"GroomedJet_numberjets/I");

   //lepton, MET angular information
   Float_t GroomedJet_CA8_deltaR_lca8jet = -999, GroomedJet_CA8_deltaphi_METca8jet = -999, GroomedJet_CA8_deltaphi_Vca8jet = -999;
   TBranch *branch_GroomedJet_CA8_deltaR_lca8jet = newtree->Branch("GroomedJet_CA8_deltaR_lca8jet", &GroomedJet_CA8_deltaR_lca8jet, "GroomedJet_CA8_deltaR_lca8jet/F");
   TBranch *branch_GroomedJet_CA8_deltaphi_METca8jet = newtree->Branch("GroomedJet_CA8_deltaphi_METca8jet", &GroomedJet_CA8_deltaphi_METca8jet,"GroomedJet_CA8_deltaphi_METca8jet/F");
   TBranch *branch_GroomedJet_CA8_deltaphi_Vca8jet = newtree->Branch("GroomedJet_CA8_deltaphi_Vca8jet", &GroomedJet_CA8_deltaphi_Vca8jet, "GroomedJet_CA8_deltaphi_Vca8jet/F");

   //Some More Variables To be Added in the Reduced Tree Or used in the TMVA Training
   Float_t GroomedJet_CA8_rcores01 = -1, GroomedJet_CA8_rcores02 = -1, GroomedJet_CA8_rcores03 = -1, GroomedJet_CA8_rcores04 = -1;
   Float_t GroomedJet_CA8_rcores05 = -1, GroomedJet_CA8_rcores06 = -1, GroomedJet_CA8_rcores07 = -1, GroomedJet_CA8_rcores08 = -1;
   Float_t GroomedJet_CA8_rcores09 = -1, GroomedJet_CA8_rcores10 = -1, GroomedJet_CA8_rcores11 = -1;

   TBranch *branch_GroomedJet_CA8_rcores01 = newtree->Branch("GroomedJet_CA8_rcores01", &GroomedJet_CA8_rcores01, "GroomedJet_CA8_rcores01/F");
   TBranch *branch_GroomedJet_CA8_rcores02 = newtree->Branch("GroomedJet_CA8_rcores02", &GroomedJet_CA8_rcores02, "GroomedJet_CA8_rcores02/F");
   TBranch *branch_GroomedJet_CA8_rcores03 = newtree->Branch("GroomedJet_CA8_rcores03", &GroomedJet_CA8_rcores03, "GroomedJet_CA8_rcores03/F");
   TBranch *branch_GroomedJet_CA8_rcores04 = newtree->Branch("GroomedJet_CA8_rcores04", &GroomedJet_CA8_rcores04, "GroomedJet_CA8_rcores04/F");
   TBranch *branch_GroomedJet_CA8_rcores05 = newtree->Branch("GroomedJet_CA8_rcores05", &GroomedJet_CA8_rcores05, "GroomedJet_CA8_rcores05/F");
   TBranch *branch_GroomedJet_CA8_rcores06 = newtree->Branch("GroomedJet_CA8_rcores06", &GroomedJet_CA8_rcores06, "GroomedJet_CA8_rcores06/F");
   TBranch *branch_GroomedJet_CA8_rcores07 = newtree->Branch("GroomedJet_CA8_rcores07", &GroomedJet_CA8_rcores07, "GroomedJet_CA8_rcores07/F");
   TBranch *branch_GroomedJet_CA8_rcores08 = newtree->Branch("GroomedJet_CA8_rcores08", &GroomedJet_CA8_rcores08, "GroomedJet_CA8_rcores08/F");
   TBranch *branch_GroomedJet_CA8_rcores09 = newtree->Branch("GroomedJet_CA8_rcores09", &GroomedJet_CA8_rcores09, "GroomedJet_CA8_rcores09/F");
   TBranch *branch_GroomedJet_CA8_rcores10 = newtree->Branch("GroomedJet_CA8_rcores10", &GroomedJet_CA8_rcores10, "GroomedJet_CA8_rcores10/F");
   TBranch *branch_GroomedJet_CA8_rcores11 = newtree->Branch("GroomedJet_CA8_rcores11", &GroomedJet_CA8_rcores11, "GroomedJet_CA8_rcores11/F");

   Float_t GroomedJet_CA8_ptcores01 = -1, GroomedJet_CA8_ptcores02 = -1, GroomedJet_CA8_ptcores03 = -1, GroomedJet_CA8_ptcores04 = -1;
   Float_t GroomedJet_CA8_ptcores05 = -1, GroomedJet_CA8_ptcores06 = -1, GroomedJet_CA8_ptcores07 = -1, GroomedJet_CA8_ptcores08 = -1;
   Float_t GroomedJet_CA8_ptcores09 = -1, GroomedJet_CA8_ptcores10 = -1, GroomedJet_CA8_ptcores11 = -1;

   TBranch *branch_GroomedJet_CA8_ptcores01 = newtree->Branch("GroomedJet_CA8_ptcores01", &GroomedJet_CA8_ptcores01, "GroomedJet_CA8_ptcores01/F");
   TBranch *branch_GroomedJet_CA8_ptcores02 = newtree->Branch("GroomedJet_CA8_ptcores02", &GroomedJet_CA8_ptcores02, "GroomedJet_CA8_ptcores02/F");
   TBranch *branch_GroomedJet_CA8_ptcores03 = newtree->Branch("GroomedJet_CA8_ptcores03", &GroomedJet_CA8_ptcores03, "GroomedJet_CA8_ptcores03/F");
   TBranch *branch_GroomedJet_CA8_ptcores04 = newtree->Branch("GroomedJet_CA8_ptcores04", &GroomedJet_CA8_ptcores04, "GroomedJet_CA8_ptcores04/F");
   TBranch *branch_GroomedJet_CA8_ptcores05 = newtree->Branch("GroomedJet_CA8_ptcores05", &GroomedJet_CA8_ptcores05, "GroomedJet_CA8_ptcores05/F");
   TBranch *branch_GroomedJet_CA8_ptcores06 = newtree->Branch("GroomedJet_CA8_ptcores06", &GroomedJet_CA8_ptcores06, "GroomedJet_CA8_ptcores06/F");
   TBranch *branch_GroomedJet_CA8_ptcores07 = newtree->Branch("GroomedJet_CA8_ptcores07", &GroomedJet_CA8_ptcores07, "GroomedJet_CA8_ptcores07/F");
   TBranch *branch_GroomedJet_CA8_ptcores08 = newtree->Branch("GroomedJet_CA8_ptcores08", &GroomedJet_CA8_ptcores08, "GroomedJet_CA8_ptcores08/F");
   TBranch *branch_GroomedJet_CA8_ptcores09 = newtree->Branch("GroomedJet_CA8_ptcores09", &GroomedJet_CA8_ptcores09, "GroomedJet_CA8_ptcores09/F");
   TBranch *branch_GroomedJet_CA8_ptcores10 = newtree->Branch("GroomedJet_CA8_ptcores10", &GroomedJet_CA8_ptcores10, "GroomedJet_CA8_ptcores10/F");
   TBranch *branch_GroomedJet_CA8_ptcores11 = newtree->Branch("GroomedJet_CA8_ptcores11", &GroomedJet_CA8_ptcores11, "GroomedJet_CA8_ptcores11/F");

   Float_t GroomedJet_CA8_planarflow01 = -1, GroomedJet_CA8_planarflow02 = -1, GroomedJet_CA8_planarflow03 = -1, GroomedJet_CA8_planarflow04 = -1;
   Float_t GroomedJet_CA8_planarflow05 = -1, GroomedJet_CA8_planarflow06 = -1, GroomedJet_CA8_planarflow07 = -1, GroomedJet_CA8_planarflow08 = -1;
   Float_t GroomedJet_CA8_planarflow09 = -1, GroomedJet_CA8_planarflow10 = -1, GroomedJet_CA8_planarflow11 = -1;

   TBranch *branch_GroomedJet_CA8_planarflow01 = newtree->Branch("GroomedJet_CA8_planarflow01", &GroomedJet_CA8_planarflow01, "GroomedJet_CA8_planarflow01/F");
   TBranch *branch_GroomedJet_CA8_planarflow02 = newtree->Branch("GroomedJet_CA8_planarflow02", &GroomedJet_CA8_planarflow02, "GroomedJet_CA8_planarflow02/F");
   TBranch *branch_GroomedJet_CA8_planarflow03 = newtree->Branch("GroomedJet_CA8_planarflow03", &GroomedJet_CA8_planarflow03, "GroomedJet_CA8_planarflow03/F");
   TBranch *branch_GroomedJet_CA8_planarflow04 = newtree->Branch("GroomedJet_CA8_planarflow04", &GroomedJet_CA8_planarflow04, "GroomedJet_CA8_planarflow04/F");
   TBranch *branch_GroomedJet_CA8_planarflow05 = newtree->Branch("GroomedJet_CA8_planarflow05", &GroomedJet_CA8_planarflow05, "GroomedJet_CA8_planarflow05/F");
   TBranch *branch_GroomedJet_CA8_planarflow06 = newtree->Branch("GroomedJet_CA8_planarflow06", &GroomedJet_CA8_planarflow06, "GroomedJet_CA8_planarflow06/F");
   TBranch *branch_GroomedJet_CA8_planarflow07 = newtree->Branch("GroomedJet_CA8_planarflow07", &GroomedJet_CA8_planarflow07, "GroomedJet_CA8_planarflow07/F");
   TBranch *branch_GroomedJet_CA8_planarflow08 = newtree->Branch("GroomedJet_CA8_planarflow08", &GroomedJet_CA8_planarflow08, "GroomedJet_CA8_planarflow08/F");
   TBranch *branch_GroomedJet_CA8_planarflow09 = newtree->Branch("GroomedJet_CA8_planarflow09", &GroomedJet_CA8_planarflow09, "GroomedJet_CA8_planarflow09/F");
   TBranch *branch_GroomedJet_CA8_planarflow10 = newtree->Branch("GroomedJet_CA8_planarflow10", &GroomedJet_CA8_planarflow10, "GroomedJet_CA8_planarflow10/F");
   TBranch *branch_GroomedJet_CA8_planarflow11 = newtree->Branch("GroomedJet_CA8_planarflow11", &GroomedJet_CA8_planarflow11, "GroomedJet_CA8_planarflow11/F");

   Float_t GroomedJet_CA8_mass_sensi_tr = -1, GroomedJet_CA8_mass_sensi_ft = -1, GroomedJet_CA8_mass_sensi_pr = -1;
   TBranch *branch_GroomedJet_CA8_mass_sensi_tr = newtree->Branch("GroomedJet_CA8_mass_sensi_tr", &GroomedJet_CA8_mass_sensi_tr, "GroomedJet_CA8_mass_sensi_tr/F");
   TBranch *branch_GroomedJet_CA8_mass_sensi_ft = newtree->Branch("GroomedJet_CA8_mass_sensi_ft", &GroomedJet_CA8_mass_sensi_ft, "GroomedJet_CA8_mass_sensi_ft/F");
   TBranch *branch_GroomedJet_CA8_mass_sensi_pr = newtree->Branch("GroomedJet_CA8_mass_sensi_pr", &GroomedJet_CA8_mass_sensi_pr, "GroomedJet_CA8_mass_sensi_pr/F");

   Float_t GroomedJet_CA8_qjetmassvolatility = -1;
   TBranch *branch_GroomedJet_CA8_qjetmassvolatility = newtree->Branch("GroomedJet_CA8_qjetmassvolatility", &GroomedJet_CA8_qjetmassvolatility, "GroomedJet_CA8_qjetmassvolatility/F");

   Float_t GroomedJet_CA8_prsubjet1ptoverjetpt = -1, GroomedJet_CA8_prsubjet2ptoverjetpt = -1;
   Float_t GroomedJet_CA8_prsubjet1subjet2_deltaR = -1;

   TBranch *branch_GroomedJet_CA8_prsubjet1ptoverjetpt = newtree->Branch("GroomedJet_CA8_prsubjet1ptoverjetpt", &GroomedJet_CA8_prsubjet1ptoverjetpt, "GroomedJet_CA8_prsubjet1ptoverjetpt/F");
   TBranch *branch_GroomedJet_CA8_prsubjet2ptoverjetpt = newtree->Branch("GroomedJet_CA8_prsubjet2ptoverjetpt", &GroomedJet_CA8_prsubjet2ptoverjetpt, "GroomedJet_CA8_prsubjet2ptoverjetpt/F");
   TBranch *branch_GroomedJet_CA8_prsubjet1subjet2_deltaR = newtree->Branch("GroomedJet_CA8_prsubjet1subjet2_deltaR", &GroomedJet_CA8_prsubjet1subjet2_deltaR, "GroomedJet_CA8_prsubjet1subjet2_deltaR/F");

   Float_t boostedW_lvj_e=-999,   boostedW_lvj_pt=-999,   boostedW_lvj_eta=-999,   boostedW_lvj_phi=-999,   boostedW_lvj_m=-999,   boostedW_lvj_y=-999;
   TBranch *branch_boostedW_lvj_e    = newtree->Branch("boostedW_lvj_e",    &boostedW_lvj_e,     "boostedW_lvj_e/F");
   TBranch *branch_boostedW_lvj_pt   = newtree->Branch("boostedW_lvj_pt",   &boostedW_lvj_pt,    "boostedW_lvj_pt/F");
   TBranch *branch_boostedW_lvj_eta  = newtree->Branch("boostedW_lvj_eta",  &boostedW_lvj_eta,   "boostedW_lvj_eta/F");
   TBranch *branch_boostedW_lvj_phi  = newtree->Branch("boostedW_lvj_phi",  &boostedW_lvj_phi,   "boostedW_lvj_phi/F");
   TBranch *branch_boostedW_lvj_m    = newtree->Branch("boostedW_lvj_m",    &boostedW_lvj_m,     "boostedW_lvj_m/F");
   TBranch *branch_boostedW_lvj_y    = newtree->Branch("boostedW_lvj_y",    &boostedW_lvj_y,     "boostedW_lvj_y/F");

   Float_t boostedW_wjj_ang_ha   = 999, boostedW_wjj_ang_hb = 999, boostedW_wjj_ang_hs = 999, boostedW_wjj_ang_phi = 999, boostedW_wjj_ang_phia = 999, boostedW_wjj_ang_phib = 999;

   TBranch * branch_boostedW_wjj_ang_ha   = newtree->Branch("boostedW_wjj_ang_ha",   &boostedW_wjj_ang_ha,    "boostedW_wjj_ang_ha/F");
   TBranch * branch_boostedW_wjj_ang_hb   = newtree->Branch("boostedW_wjj_ang_hb",   &boostedW_wjj_ang_hb,    "boostedW_wjj_ang_hb/F");
   TBranch * branch_boostedW_wjj_ang_hs   = newtree->Branch("boostedW_wjj_ang_hs",   &boostedW_wjj_ang_hs,    "boostedW_wjj_ang_hs/F");
   TBranch * branch_boostedW_wjj_ang_phi  = newtree->Branch("boostedW_wjj_ang_phi",  &boostedW_wjj_ang_phi,   "boostedW_wjj_ang_phi/F");
   TBranch * branch_boostedW_wjj_ang_phia = newtree->Branch("boostedW_wjj_ang_phia", &boostedW_wjj_ang_phia,  "boostedW_wjj_ang_phia/F");
   TBranch * branch_boostedW_wjj_ang_phib = newtree->Branch("boostedW_wjj_ang_phib", &boostedW_wjj_ang_phib,  "boostedW_wjj_ang_phib/F");

   //Event Flag for Boosted W Analysis With AK7
   Int_t   ggdboostedWevt_ak7 =0;
   TBranch *branch_ggdboostedWevt_ak7 = newtree->Branch("ggdboostedWevt_ak7", &ggdboostedWevt_ak7, "ggdboostedWevt_ak7/I"); 

   Int_t   GroomedJet_numberbjets_csvl_ak7 = 0;
   TBranch *branch_GroomedJet_numberbjets_csvl_ak7 = newtree->Branch("GroomedJet_numberbjets_csvl_ak7", &GroomedJet_numberbjets_csvl_ak7,"GroomedJet_numberbjets_csvl_ak7/I");

   Int_t   GroomedJet_numberbjets_csvm_ak7 = 0;
   TBranch *branch_GroomedJet_numberbjets_csvm_ak7 = newtree->Branch("GroomedJet_numberbjets_csvm_ak7", &GroomedJet_numberbjets_csvm_ak7,"GroomedJet_numberbjets_csvm_ak7/I");

   Int_t   GroomedJet_numberbjets_ssvhem_ak7 = 0;
   TBranch *branch_GroomedJet_numberbjets_ssvhem_ak7 = newtree->Branch("GroomedJet_numberbjets_ssvhem_ak7", &GroomedJet_numberbjets_ssvhem_ak7,"GroomedJet_numberbjets_ssvhem_ak7/I");

   Int_t   GroomedJet_numberbjets_csvl_veto_ak7 = 0;
   TBranch *branch_GroomedJet_numberbjets_csvl_veto_ak7 = newtree->Branch("GroomedJet_numberbjets_csvl_veto_ak7", &GroomedJet_numberbjets_csvl_veto_ak7,"GroomedJet_numberbjets_csvl_veto_ak7/I");

   Int_t   GroomedJet_numberbjets_csvm_veto_ak7 = 0;
   TBranch *branch_GroomedJet_numberbjets_csvm_veto_ak7 = newtree->Branch("GroomedJet_numberbjets_csvm_veto_ak7", &GroomedJet_numberbjets_csvm_veto_ak7,"GroomedJet_numberbjets_csvm_veto_ak7/I");

   Int_t   GroomedJet_numberbjets_ssvhem_veto_ak7 = 0;
   TBranch *branch_GroomedJet_numberbjets_ssvhem_veto_ak7 = newtree->Branch("GroomedJet_numberbjets_ssvhem_veto_ak7", &GroomedJet_numberbjets_ssvhem_veto_ak7,"GroomedJet_numberbjets_ssvhem_veto_ak7/I");

   Int_t   GroomedJet_numberjets_ak7 = 0;
   TBranch *branch_GroomedJet_numberjets_ak7 = newtree->Branch("GroomedJet_numberjets_ak7", &GroomedJet_numberjets_ak7,"GroomedJet_numberjets_ak7/I");

   //lepton, MET angular information
   Float_t GroomedJet_AK7_deltaR_lak7jet = -999, GroomedJet_AK7_deltaphi_METak7jet = -999, GroomedJet_AK7_deltaphi_Vak7jet = -999;
   TBranch *branch_GroomedJet_AK7_deltaR_lak7jet = newtree->Branch("GroomedJet_AK7_deltaR_lak7jet", &GroomedJet_AK7_deltaR_lak7jet, "GroomedJet_AK7_deltaR_lak7jet/F");
   TBranch *branch_GroomedJet_AK7_deltaphi_METak7jet = newtree->Branch("GroomedJet_AK7_deltaphi_METak7jet", &GroomedJet_AK7_deltaphi_METak7jet,"GroomedJet_AK7_deltaphi_METak7jet/F");
   TBranch *branch_GroomedJet_AK7_deltaphi_Vak7jet = newtree->Branch("GroomedJet_AK7_deltaphi_Vak7jet", &GroomedJet_AK7_deltaphi_Vak7jet, "GroomedJet_AK7_deltaphi_Vak7jet/F");

   //Some More Variables To be Added in the Reduced Tree Or used in the TMVA Training
   Float_t GroomedJet_AK7_rcores01 = -1, GroomedJet_AK7_rcores02 = -1, GroomedJet_AK7_rcores03 = -1, GroomedJet_AK7_rcores04 = -1;
   Float_t GroomedJet_AK7_rcores05 = -1, GroomedJet_AK7_rcores06 = -1, GroomedJet_AK7_rcores07 = -1, GroomedJet_AK7_rcores08 = -1;
   Float_t GroomedJet_AK7_rcores09 = -1, GroomedJet_AK7_rcores10 = -1, GroomedJet_AK7_rcores11 = -1;

   TBranch *branch_GroomedJet_AK7_rcores01 = newtree->Branch("GroomedJet_AK7_rcores01", &GroomedJet_AK7_rcores01, "GroomedJet_AK7_rcores01/F");
   TBranch *branch_GroomedJet_AK7_rcores02 = newtree->Branch("GroomedJet_AK7_rcores02", &GroomedJet_AK7_rcores02, "GroomedJet_AK7_rcores02/F");
   TBranch *branch_GroomedJet_AK7_rcores03 = newtree->Branch("GroomedJet_AK7_rcores03", &GroomedJet_AK7_rcores03, "GroomedJet_AK7_rcores03/F");
   TBranch *branch_GroomedJet_AK7_rcores04 = newtree->Branch("GroomedJet_AK7_rcores04", &GroomedJet_AK7_rcores04, "GroomedJet_AK7_rcores04/F");
   TBranch *branch_GroomedJet_AK7_rcores05 = newtree->Branch("GroomedJet_AK7_rcores05", &GroomedJet_AK7_rcores05, "GroomedJet_AK7_rcores05/F");
   TBranch *branch_GroomedJet_AK7_rcores06 = newtree->Branch("GroomedJet_AK7_rcores06", &GroomedJet_AK7_rcores06, "GroomedJet_AK7_rcores06/F");
   TBranch *branch_GroomedJet_AK7_rcores07 = newtree->Branch("GroomedJet_AK7_rcores07", &GroomedJet_AK7_rcores07, "GroomedJet_AK7_rcores07/F");
   TBranch *branch_GroomedJet_AK7_rcores08 = newtree->Branch("GroomedJet_AK7_rcores08", &GroomedJet_AK7_rcores08, "GroomedJet_AK7_rcores08/F");
   TBranch *branch_GroomedJet_AK7_rcores09 = newtree->Branch("GroomedJet_AK7_rcores09", &GroomedJet_AK7_rcores09, "GroomedJet_AK7_rcores09/F");
   TBranch *branch_GroomedJet_AK7_rcores10 = newtree->Branch("GroomedJet_AK7_rcores10", &GroomedJet_AK7_rcores10, "GroomedJet_AK7_rcores10/F");
   TBranch *branch_GroomedJet_AK7_rcores11 = newtree->Branch("GroomedJet_AK7_rcores11", &GroomedJet_AK7_rcores11, "GroomedJet_AK7_rcores11/F");

   Float_t GroomedJet_AK7_ptcores01 = -1, GroomedJet_AK7_ptcores02 = -1, GroomedJet_AK7_ptcores03 = -1, GroomedJet_AK7_ptcores04 = -1;
   Float_t GroomedJet_AK7_ptcores05 = -1, GroomedJet_AK7_ptcores06 = -1, GroomedJet_AK7_ptcores07 = -1, GroomedJet_AK7_ptcores08 = -1;
   Float_t GroomedJet_AK7_ptcores09 = -1, GroomedJet_AK7_ptcores10 = -1, GroomedJet_AK7_ptcores11 = -1;

   TBranch *branch_GroomedJet_AK7_ptcores01 = newtree->Branch("GroomedJet_AK7_ptcores01", &GroomedJet_AK7_ptcores01, "GroomedJet_AK7_ptcores01/F");
   TBranch *branch_GroomedJet_AK7_ptcores02 = newtree->Branch("GroomedJet_AK7_ptcores02", &GroomedJet_AK7_ptcores02, "GroomedJet_AK7_ptcores02/F");
   TBranch *branch_GroomedJet_AK7_ptcores03 = newtree->Branch("GroomedJet_AK7_ptcores03", &GroomedJet_AK7_ptcores03, "GroomedJet_AK7_ptcores03/F");
   TBranch *branch_GroomedJet_AK7_ptcores04 = newtree->Branch("GroomedJet_AK7_ptcores04", &GroomedJet_AK7_ptcores04, "GroomedJet_AK7_ptcores04/F");
   TBranch *branch_GroomedJet_AK7_ptcores05 = newtree->Branch("GroomedJet_AK7_ptcores05", &GroomedJet_AK7_ptcores05, "GroomedJet_AK7_ptcores05/F");
   TBranch *branch_GroomedJet_AK7_ptcores06 = newtree->Branch("GroomedJet_AK7_ptcores06", &GroomedJet_AK7_ptcores06, "GroomedJet_AK7_ptcores06/F");
   TBranch *branch_GroomedJet_AK7_ptcores07 = newtree->Branch("GroomedJet_AK7_ptcores07", &GroomedJet_AK7_ptcores07, "GroomedJet_AK7_ptcores07/F");
   TBranch *branch_GroomedJet_AK7_ptcores08 = newtree->Branch("GroomedJet_AK7_ptcores08", &GroomedJet_AK7_ptcores08, "GroomedJet_AK7_ptcores08/F");
   TBranch *branch_GroomedJet_AK7_ptcores09 = newtree->Branch("GroomedJet_AK7_ptcores09", &GroomedJet_AK7_ptcores09, "GroomedJet_AK7_ptcores09/F");
   TBranch *branch_GroomedJet_AK7_ptcores10 = newtree->Branch("GroomedJet_AK7_ptcores10", &GroomedJet_AK7_ptcores10, "GroomedJet_AK7_ptcores10/F");
   TBranch *branch_GroomedJet_AK7_ptcores11 = newtree->Branch("GroomedJet_AK7_ptcores11", &GroomedJet_AK7_ptcores11, "GroomedJet_AK7_ptcores11/F");

   Float_t GroomedJet_AK7_planarflow01 = -1, GroomedJet_AK7_planarflow02 = -1, GroomedJet_AK7_planarflow03 = -1, GroomedJet_AK7_planarflow04 = -1;
   Float_t GroomedJet_AK7_planarflow05 = -1, GroomedJet_AK7_planarflow06 = -1, GroomedJet_AK7_planarflow07 = -1, GroomedJet_AK7_planarflow08 = -1;
   Float_t GroomedJet_AK7_planarflow09 = -1, GroomedJet_AK7_planarflow10 = -1, GroomedJet_AK7_planarflow11 = -1;

   TBranch *branch_GroomedJet_AK7_planarflow01 = newtree->Branch("GroomedJet_AK7_planarflow01", &GroomedJet_AK7_planarflow01, "GroomedJet_AK7_planarflow01/F");
   TBranch *branch_GroomedJet_AK7_planarflow02 = newtree->Branch("GroomedJet_AK7_planarflow02", &GroomedJet_AK7_planarflow02, "GroomedJet_AK7_planarflow02/F");
   TBranch *branch_GroomedJet_AK7_planarflow03 = newtree->Branch("GroomedJet_AK7_planarflow03", &GroomedJet_AK7_planarflow03, "GroomedJet_AK7_planarflow03/F");
   TBranch *branch_GroomedJet_AK7_planarflow04 = newtree->Branch("GroomedJet_AK7_planarflow04", &GroomedJet_AK7_planarflow04, "GroomedJet_AK7_planarflow04/F");
   TBranch *branch_GroomedJet_AK7_planarflow05 = newtree->Branch("GroomedJet_AK7_planarflow05", &GroomedJet_AK7_planarflow05, "GroomedJet_AK7_planarflow05/F");
   TBranch *branch_GroomedJet_AK7_planarflow06 = newtree->Branch("GroomedJet_AK7_planarflow06", &GroomedJet_AK7_planarflow06, "GroomedJet_AK7_planarflow06/F");
   TBranch *branch_GroomedJet_AK7_planarflow07 = newtree->Branch("GroomedJet_AK7_planarflow07", &GroomedJet_AK7_planarflow07, "GroomedJet_AK7_planarflow07/F");
   TBranch *branch_GroomedJet_AK7_planarflow08 = newtree->Branch("GroomedJet_AK7_planarflow08", &GroomedJet_AK7_planarflow08, "GroomedJet_AK7_planarflow08/F");
   TBranch *branch_GroomedJet_AK7_planarflow09 = newtree->Branch("GroomedJet_AK7_planarflow09", &GroomedJet_AK7_planarflow09, "GroomedJet_AK7_planarflow09/F");
   TBranch *branch_GroomedJet_AK7_planarflow10 = newtree->Branch("GroomedJet_AK7_planarflow10", &GroomedJet_AK7_planarflow10, "GroomedJet_AK7_planarflow10/F");
   TBranch *branch_GroomedJet_AK7_planarflow11 = newtree->Branch("GroomedJet_AK7_planarflow11", &GroomedJet_AK7_planarflow11, "GroomedJet_AK7_planarflow11/F");

   Float_t GroomedJet_AK7_mass_sensi_tr = -1, GroomedJet_AK7_mass_sensi_ft = -1, GroomedJet_AK7_mass_sensi_pr = -1;
   TBranch *branch_GroomedJet_AK7_mass_sensi_tr = newtree->Branch("GroomedJet_AK7_mass_sensi_tr", &GroomedJet_AK7_mass_sensi_tr, "GroomedJet_AK7_mass_sensi_tr/F");
   TBranch *branch_GroomedJet_AK7_mass_sensi_ft = newtree->Branch("GroomedJet_AK7_mass_sensi_ft", &GroomedJet_AK7_mass_sensi_ft, "GroomedJet_AK7_mass_sensi_ft/F");
   TBranch *branch_GroomedJet_AK7_mass_sensi_pr = newtree->Branch("GroomedJet_AK7_mass_sensi_pr", &GroomedJet_AK7_mass_sensi_pr, "GroomedJet_AK7_mass_sensi_pr/F");

   Float_t GroomedJet_AK7_qjetmassvolatility = -1;
   TBranch *branch_GroomedJet_AK7_qjetmassvolatility = newtree->Branch("GroomedJet_AK7_qjetmassvolatility", &GroomedJet_AK7_qjetmassvolatility, "GroomedJet_AK7_qjetmassvolatility/F");

   Float_t GroomedJet_AK7_prsubjet1ptoverjetpt = -1, GroomedJet_AK7_prsubjet2ptoverjetpt = -1;
   Float_t GroomedJet_AK7_prsubjet1subjet2_deltaR = -1;

   TBranch *branch_GroomedJet_AK7_prsubjet1ptoverjetpt = newtree->Branch("GroomedJet_AK7_prsubjet1ptoverjetpt", &GroomedJet_AK7_prsubjet1ptoverjetpt, "GroomedJet_AK7_prsubjet1ptoverjetpt/F");
   TBranch *branch_GroomedJet_AK7_prsubjet2ptoverjetpt = newtree->Branch("GroomedJet_AK7_prsubjet2ptoverjetpt", &GroomedJet_AK7_prsubjet2ptoverjetpt, "GroomedJet_AK7_prsubjet2ptoverjetpt/F");
   TBranch *branch_GroomedJet_AK7_prsubjet1subjet2_deltaR = newtree->Branch("GroomedJet_AK7_prsubjet1subjet2_deltaR", &GroomedJet_AK7_prsubjet1subjet2_deltaR, "GroomedJet_AK7_prsubjet1subjet2_deltaR/F");

   Float_t boostedW_lvj_e_ak7 =-999,   boostedW_lvj_pt_ak7=-999,   boostedW_lvj_eta_ak7=-999,   boostedW_lvj_phi_ak7=-999,   boostedW_lvj_m_ak7=-999,   boostedW_lvj_y_ak7=-999;
   TBranch *branch_boostedW_lvj_e_ak7    = newtree->Branch("boostedW_lvj_e_ak7",    &boostedW_lvj_e_ak7,     "boostedW_lvj_e_ak7/F");
   TBranch *branch_boostedW_lvj_pt_ak7   = newtree->Branch("boostedW_lvj_pt_ak7",   &boostedW_lvj_pt_ak7,    "boostedW_lvj_pt_ak7/F");
   TBranch *branch_boostedW_lvj_eta_ak7  = newtree->Branch("boostedW_lvj_eta_ak7",  &boostedW_lvj_eta_ak7,   "boostedW_lvj_eta_ak7/F");
   TBranch *branch_boostedW_lvj_phi_ak7  = newtree->Branch("boostedW_lvj_phi_ak7",  &boostedW_lvj_phi_ak7,   "boostedW_lvj_phi_ak7/F");
   TBranch *branch_boostedW_lvj_m_ak7    = newtree->Branch("boostedW_lvj_m_ak7",    &boostedW_lvj_m_ak7,     "boostedW_lvj_m_ak7/F");
   TBranch *branch_boostedW_lvj_y_ak7    = newtree->Branch("boostedW_lvj_y_ak7",    &boostedW_lvj_y_ak7,     "boostedW_lvj_y_ak7/F");

   Float_t boostedW_wjj_ang_ha_ak7   = 999, boostedW_wjj_ang_hb_ak7 = 999, boostedW_wjj_ang_hs_ak7 = 999, boostedW_wjj_ang_phi_ak7 = 999, boostedW_wjj_ang_phia_ak7 = 999, boostedW_wjj_ang_phib_ak7 = 999;

   TBranch * branch_boostedW_wjj_ang_ha_ak7   = newtree->Branch("boostedW_wjj_ang_ha_ak7",   &boostedW_wjj_ang_ha_ak7,    "boostedW_wjj_ang_ha_ak7/F");
   TBranch * branch_boostedW_wjj_ang_hb_ak7   = newtree->Branch("boostedW_wjj_ang_hb_ak7",   &boostedW_wjj_ang_hb_ak7,    "boostedW_wjj_ang_hb_ak7/F");
   TBranch * branch_boostedW_wjj_ang_hs_ak7   = newtree->Branch("boostedW_wjj_ang_hs_ak7",   &boostedW_wjj_ang_hs_ak7,    "boostedW_wjj_ang_hs_ak7/F");
   TBranch * branch_boostedW_wjj_ang_phi_ak7  = newtree->Branch("boostedW_wjj_ang_phi_ak7",  &boostedW_wjj_ang_phi_ak7,   "boostedW_wjj_ang_phi_ak7/F");
   TBranch * branch_boostedW_wjj_ang_phia_ak7 = newtree->Branch("boostedW_wjj_ang_phia_ak7", &boostedW_wjj_ang_phia_ak7,  "boostedW_wjj_ang_phia_ak7/F");
   TBranch * branch_boostedW_wjj_ang_phib_ak7 = newtree->Branch("boostedW_wjj_ang_phib_ak7", &boostedW_wjj_ang_phib_ak7,  "boostedW_wjj_ang_phib_ak7/F");
   //End Some More Variables To be Added in the Reduced Tree Or used in the TMVA Training

   Float_t vbf_jj_e =-999,   vbf_jj_pt =-999,   vbf_jj_eta=-999,  vbf_jj_phi =-999, vbf_jj_m =-999;   
   Float_t vbf_aj_e =-999,   vbf_aj_pt =-999,   vbf_aj_eta=-999,  vbf_aj_phi =-999, vbf_aj_m =-999;   
   Float_t vbf_bj_e =-999,   vbf_bj_pt =-999,   vbf_bj_eta=-999,  vbf_bj_phi =-999, vbf_bj_m =-999;   
   Float_t vbf_jj_deta=-999; Float_t vbf_jj_dphi=-999;  Int_t   vbf_jj_type=0,   vbf_n_excj=0,   vbf_n_exfj=0,   vbf_n_gdjj=0;

   TBranch *branch_vbf_jj_e    = newtree->Branch("vbf_jj_e",    &vbf_jj_e,     "vbf_jj_e/F");
   TBranch *branch_vbf_jj_pt   = newtree->Branch("vbf_jj_pt",   &vbf_jj_pt,    "vbf_jj_pt/F");
   TBranch *branch_vbf_jj_eta  = newtree->Branch("vbf_jj_eta",  &vbf_jj_eta,   "vbf_jj_eta/F");
   TBranch *branch_vbf_jj_phi  = newtree->Branch("vbf_jj_phi",  &vbf_jj_phi,   "vbf_jj_phi/F");
   TBranch *branch_vbf_jj_m    = newtree->Branch("vbf_jj_m",    &vbf_jj_m,     "vbf_jj_m/F");

   TBranch *branch_vbf_aj_e    = newtree->Branch("vbf_aj_e",    &vbf_aj_e,     "vbf_aj_e/F");
   TBranch *branch_vbf_aj_pt   = newtree->Branch("vbf_aj_pt",   &vbf_aj_pt,    "vbf_aj_pt/F");
   TBranch *branch_vbf_aj_eta  = newtree->Branch("vbf_aj_eta",  &vbf_aj_eta,   "vbf_aj_eta/F");
   TBranch *branch_vbf_aj_phi  = newtree->Branch("vbf_aj_phi",  &vbf_aj_phi,   "vbf_aj_phi/F");
   TBranch *branch_vbf_aj_m    = newtree->Branch("vbf_aj_m",    &vbf_aj_m,     "vbf_aj_m/F");

   TBranch *branch_vbf_bj_e    = newtree->Branch("vbf_bj_e",    &vbf_bj_e,     "vbf_bj_e/F");
   TBranch *branch_vbf_bj_pt   = newtree->Branch("vbf_bj_pt",   &vbf_bj_pt,    "vbf_bj_pt/F");
   TBranch *branch_vbf_bj_eta  = newtree->Branch("vbf_bj_eta",  &vbf_bj_eta,   "vbf_bj_eta/F");
   TBranch *branch_vbf_bj_phi  = newtree->Branch("vbf_bj_phi",  &vbf_bj_phi,   "vbf_bj_phi/F");
   TBranch *branch_vbf_bj_m    = newtree->Branch("vbf_bj_m",    &vbf_bj_m,     "vbf_bj_m/F");

   TBranch *branch_vbf_jj_deta = newtree->Branch("vbf_jj_deta", &vbf_jj_deta,  "vbf_jj_deta/F");
   TBranch *branch_vbf_jj_dphi = newtree->Branch("vbf_jj_dphi", &vbf_jj_dphi,  "vbf_jj_dphi/F");
   TBranch *branch_vbf_jj_type = newtree->Branch("vbf_jj_type", &vbf_jj_type,  "vbf_jj_type/I");
   TBranch *branch_vbf_n_excj  = newtree->Branch("vbf_n_excj",  &vbf_n_excj,   "vbf_n_excj/I");
   TBranch *branch_vbf_n_exfj  = newtree->Branch("vbf_n_exfj",  &vbf_n_exfj,   "vbf_n_exfj/I");
   TBranch *branch_vbf_n_gdjj  = newtree->Branch("vbf_n_gdjj",  &vbf_n_gdjj,   "vbf_n_gdjj/I");

   Int_t vbf_aj_bj_Wjj_jetnumber = 0;
   TBranch *branch_vbf_aj_bj_Wjj_jetnumber = newtree->Branch("vbf_aj_bj_Wjj_jetnumber",&vbf_aj_bj_Wjj_jetnumber,"vbf_aj_bj_Wjj_jetnumber/I");
   Int_t vbf_waj_wbj_jetnumber = 0;
   TBranch *branch_vbf_waj_wbj_jetnumber = newtree->Branch("vbf_waj_wbj_jetnumber",&vbf_waj_wbj_jetnumber,"vbf_waj_wbj_jetnumber/I");

   Float_t vbf_lvwajbj_ajbj_dphi = -999;
   TBranch *branch_vbf_lvwajbj_ajbj_dphi = newtree->Branch("vbf_lvwajbj_ajbj_dphi",&vbf_lvwajbj_ajbj_dphi,"vbf_lvwajbj_ajbj_dphi/F");
   Float_t vbf_lvwajbj_ajbj_deta = -999;
   TBranch *branch_vbf_lvwajbj_ajbj_deta = newtree->Branch("vbf_lvwajbj_ajbj_deta",&vbf_lvwajbj_ajbj_deta,"vbf_lvwajbj_ajbj_deta/F");

   Float_t vbf_wjj_e =-999,   vbf_wjj_pt =-999,   vbf_wjj_eta =-999,   vbf_wjj_phi =-999,   vbf_wjj_m =-999;   
   Float_t vbf_waj_e =-999,   vbf_waj_pt =-999,   vbf_waj_eta =-999,   vbf_waj_phi =-999,   vbf_waj_m =-999;   
   Float_t vbf_wbj_e =-999,   vbf_wbj_pt =-999,   vbf_wbj_eta =-999,   vbf_wbj_phi =-999,   vbf_wbj_m =-999;   
   Float_t vbf_lvjj_e=-999,   vbf_lvjj_pt=-999,   vbf_lvjj_eta=-999,   vbf_lvjj_phi=-999,   vbf_lvjj_m=-999,   vbf_lvjj_y=-999;   

   TBranch *branch_vbf_wjj_e     = newtree->Branch("vbf_wjj_e",     &vbf_wjj_e,      "vbf_wjj_e/F");
   TBranch *branch_vbf_wjj_pt    = newtree->Branch("vbf_wjj_pt",    &vbf_wjj_pt,     "vbf_wjj_pt/F");
   TBranch *branch_vbf_wjj_eta   = newtree->Branch("vbf_wjj_eta",   &vbf_wjj_eta,    "vbf_wjj_eta/F");
   TBranch *branch_vbf_wjj_phi   = newtree->Branch("vbf_wjj_phi",   &vbf_wjj_phi,    "vbf_wjj_phi/F");
   TBranch *branch_vbf_wjj_m     = newtree->Branch("vbf_wjj_m",     &vbf_wjj_m,      "vbf_wjj_m/F");

   TBranch *branch_vbf_waj_e     = newtree->Branch("vbf_waj_e",     &vbf_waj_e,      "vbf_waj_e/F");
   TBranch *branch_vbf_waj_pt    = newtree->Branch("vbf_waj_pt",    &vbf_waj_pt,     "vbf_waj_pt/F");
   TBranch *branch_vbf_waj_eta   = newtree->Branch("vbf_waj_eta",   &vbf_waj_eta,    "vbf_waj_eta/F");
   TBranch *branch_vbf_waj_phi   = newtree->Branch("vbf_waj_phi",   &vbf_waj_phi,    "vbf_waj_phi/F");
   TBranch *branch_vbf_waj_m     = newtree->Branch("vbf_waj_m",     &vbf_waj_m,      "vbf_waj_m/F");

   TBranch *branch_vbf_wbj_e     = newtree->Branch("vbf_wbj_e",     &vbf_wbj_e,      "vbf_wbj_e/F");
   TBranch *branch_vbf_wbj_pt    = newtree->Branch("vbf_wbj_pt",    &vbf_wbj_pt,     "vbf_wbj_pt/F");
   TBranch *branch_vbf_wbj_eta   = newtree->Branch("vbf_wbj_eta",   &vbf_wbj_eta,    "vbf_wbj_eta/F");
   TBranch *branch_vbf_wbj_phi   = newtree->Branch("vbf_wbj_phi",   &vbf_wbj_phi,    "vbf_wbj_phi/F");
   TBranch *branch_vbf_wbj_m     = newtree->Branch("vbf_wbj_m",     &vbf_wbj_m,      "vbf_wbj_m/F");

   TBranch *branch_vbf_lvjj_e    = newtree->Branch("vbf_lvjj_e",    &vbf_lvjj_e,     "vbf_lvjj_e/F");
   TBranch *branch_vbf_lvjj_pt   = newtree->Branch("vbf_lvjj_pt",   &vbf_lvjj_pt,    "vbf_lvjj_pt/F");
   TBranch *branch_vbf_lvjj_eta  = newtree->Branch("vbf_lvjj_eta",  &vbf_lvjj_eta,   "vbf_lvjj_eta/F");
   TBranch *branch_vbf_lvjj_phi  = newtree->Branch("vbf_lvjj_phi",  &vbf_lvjj_phi,   "vbf_lvjj_phi/F");
   TBranch *branch_vbf_lvjj_m    = newtree->Branch("vbf_lvjj_m",    &vbf_lvjj_m,     "vbf_lvjj_m/F");
   TBranch *branch_vbf_lvjj_y    = newtree->Branch("vbf_lvjj_y",    &vbf_lvjj_y,     "vbf_lvjj_y/F");

   Int_t vbf_event = 0, vbf_aj_id = -1, vbf_bj_id = -1, vbf_waj_id = -1, vbf_wbj_id = -1;
   Float_t vbf_wjj_ang_ha   = 999, vbf_wjj_ang_hb = 999, vbf_wjj_ang_hs = 999, vbf_wjj_ang_phi = 999, vbf_wjj_ang_phia = 999, vbf_wjj_ang_phib = 999;

   TBranch *branch_vbf_event     = newtree->Branch("vbf_event",  &vbf_event,   "vbf_event/I");
   TBranch *branch_vbf_aj_id     = newtree->Branch("vbf_aj_id",  &vbf_aj_id,   "vbf_aj_id/I");
   TBranch *branch_vbf_bj_id     = newtree->Branch("vbf_bj_id",  &vbf_bj_id,   "vbf_bj_id/I");
   TBranch *branch_vbf_waj_id    = newtree->Branch("vbf_waj_id", &vbf_waj_id,  "vbf_waj_id/I");
   TBranch *branch_vbf_wbj_id    = newtree->Branch("vbf_wbj_id", &vbf_wbj_id,  "vbf_wbj_id/I");

   TBranch * branch_vbf_wjj_ang_ha   = newtree->Branch("vbf_wjj_ang_ha",   &vbf_wjj_ang_ha,    "vbf_wjj_ang_ha/F");
   TBranch * branch_vbf_wjj_ang_hb   = newtree->Branch("vbf_wjj_ang_hb",   &vbf_wjj_ang_hb,    "vbf_wjj_ang_hb/F");
   TBranch * branch_vbf_wjj_ang_hs   = newtree->Branch("vbf_wjj_ang_hs",   &vbf_wjj_ang_hs,    "vbf_wjj_ang_hs/F");
   TBranch * branch_vbf_wjj_ang_phi  = newtree->Branch("vbf_wjj_ang_phi",  &vbf_wjj_ang_phi,   "vbf_wjj_ang_phi/F");
   TBranch * branch_vbf_wjj_ang_phia = newtree->Branch("vbf_wjj_ang_phia", &vbf_wjj_ang_phia,  "vbf_wjj_ang_phia/F");
   TBranch * branch_vbf_wjj_ang_phib = newtree->Branch("vbf_wjj_ang_phib", &vbf_wjj_ang_phib,  "vbf_wjj_ang_phib/F");

   //Variables for the VBF topology of the di-boson events
   Int_t vbf_diboson_event = 0;
   Float_t vbf_diboson_dijetpt = -999, vbf_diboson_deltaeta_Wjj = -999, vbf_diboson_deltaphi_MET_leadingWjet = -999;

   TBranch *branch_vbf_diboson_event      = newtree->Branch("vbf_diboson_event",  &vbf_diboson_event,   "vbf_diboson_event/I");
   TBranch *branch_vbf_diboson_dijetpt   = newtree->Branch("vbf_diboson_dijetpt", &vbf_diboson_dijetpt, "vbf_diboson_dijetpt/F");
   TBranch *branch_vbf_diboson_deltaeta_Wjj  = newtree->Branch("vbf_diboson_deltaeta_Wjj", &vbf_diboson_deltaeta_Wjj, "vbf_diboson_deltaeta_Wjj/F");
   TBranch *branch_vbf_diboson_deltaphi_MET_leadingWjet  = newtree->Branch("vbf_diboson_deltaphi_MET_leadingWjet", &vbf_diboson_deltaphi_MET_leadingWjet, "vbf_diboson_deltaphi_MET_leadingWjet/F");

   //EWK W+2jets Analysis
   Int_t EWK_W_2jets_event = 0;
   TBranch *branch_EWK_W_2jets_event = newtree->Branch("EWK_W_2jets_event", &EWK_W_2jets_event, "EWK_W_2jets_event/I");

   Float_t EWK_W_2jets_tagjet1_pt = -999, EWK_W_2jets_tagjet1_eta = -999, EWK_W_2jets_tagjet1_phi = -999, EWK_W_2jets_tagjet1_e = -999, EWK_W_2jets_tagjet1_m = -999;
   Float_t EWK_W_2jets_tagjet2_pt = -999, EWK_W_2jets_tagjet2_eta = -999, EWK_W_2jets_tagjet2_phi = -999, EWK_W_2jets_tagjet2_e = -999, EWK_W_2jets_tagjet2_m = -999;
   TBranch *branch_EWK_W_2jets_tagjet1_pt = newtree->Branch("EWK_W_2jets_tagjet1_pt", &EWK_W_2jets_tagjet1_pt, "EWK_W_2jets_tagjet1_pt/F");
   TBranch *branch_EWK_W_2jets_tagjet1_eta = newtree->Branch("EWK_W_2jets_tagjet1_eta", &EWK_W_2jets_tagjet1_eta, "EWK_W_2jets_tagjet1_eta/F");
   TBranch *branch_EWK_W_2jets_tagjet1_phi = newtree->Branch("EWK_W_2jets_tagjet1_phi", &EWK_W_2jets_tagjet1_phi, "EWK_W_2jets_tagjet1_phi/F");
   TBranch *branch_EWK_W_2jets_tagjet1_e = newtree->Branch("EWK_W_2jets_tagjet1_e", &EWK_W_2jets_tagjet1_e, "EWK_W_2jets_tagjet1_e/F");
   TBranch *branch_EWK_W_2jets_tagjet1_m = newtree->Branch("EWK_W_2jets_tagjet1_m", &EWK_W_2jets_tagjet1_m, "EWK_W_2jets_tagjet1_m/F");
   TBranch *branch_EWK_W_2jets_tagjet2_pt = newtree->Branch("EWK_W_2jets_tagjet2_pt", &EWK_W_2jets_tagjet2_pt, "EWK_W_2jets_tagjet2_pt/F");
   TBranch *branch_EWK_W_2jets_tagjet2_eta = newtree->Branch("EWK_W_2jets_tagjet2_eta", &EWK_W_2jets_tagjet2_eta, "EWK_W_2jets_tagjet2_eta/F");
   TBranch *branch_EWK_W_2jets_tagjet2_phi = newtree->Branch("EWK_W_2jets_tagjet2_phi", &EWK_W_2jets_tagjet2_phi, "EWK_W_2jets_tagjet2_phi/F");
   TBranch *branch_EWK_W_2jets_tagjet2_e = newtree->Branch("EWK_W_2jets_tagjet2_e", &EWK_W_2jets_tagjet2_e, "EWK_W_2jets_tagjet2_e/F");
   TBranch *branch_EWK_W_2jets_tagjet2_m = newtree->Branch("EWK_W_2jets_tagjet2_m", &EWK_W_2jets_tagjet2_m, "EWK_W_2jets_tagjet2_m/F");

   Int_t EWK_W_2jets_tagjet_etasign = -999;
   Float_t EWK_W_2jets_tagjet_deltaeta =  -999, EWK_W_2jets_tagjet_sumeta = -999;
   Float_t EWK_W_2jets_tagjet_deltaphi = -999, EWK_W_2jets_tagjet_deltaR = -999, EWK_W_2jets_tagjet_mass = -999;
   TBranch *branch_EWK_W_2jets_tagjet_etasign = newtree->Branch("EWK_W_2jets_tagjet_etasign", &EWK_W_2jets_tagjet_etasign, "EWK_W_2jets_tagjet_etasign/I");
   TBranch *branch_EWK_W_2jets_tagjet_deltaeta = newtree->Branch("EWK_W_2jets_tagjet_deltaeta", &EWK_W_2jets_tagjet_deltaeta, "EWK_W_2jets_tagjet_deltaeta/F");
   TBranch *branch_EWK_W_2jets_tagjet_sumeta = newtree->Branch("EWK_W_2jets_tagjet_sumeta", &EWK_W_2jets_tagjet_sumeta, "EWK_W_2jets_tagjet_sumeta/F");
   TBranch *branch_EWK_W_2jets_tagjet_deltaphi = newtree->Branch("EWK_W_2jets_tagjet_deltaphi", &EWK_W_2jets_tagjet_deltaphi, "EWK_W_2jets_tagjet_deltaphi/F"); 
   TBranch *branch_EWK_W_2jets_tagjet_deltaR = newtree->Branch("EWK_W_2jets_tagjet_deltaR", &EWK_W_2jets_tagjet_deltaR, "EWK_W_2jets_tagjet_deltaR/F"); 
   TBranch *branch_EWK_W_2jets_tagjet_mass = newtree->Branch("EWK_W_2jets_tagjet_mass", &EWK_W_2jets_tagjet_mass, "EWK_W_2jets_tagjet_mass/F"); 

   Float_t EWK_W_2jets_l_pt = -999, EWK_W_2jets_l_eta = -999, EWK_W_2jets_l_phi = -999, EWK_W_2jets_l_e = -999;
   Float_t EWK_W_2jets_l_MET_deltaphi = -999;
   TBranch *branch_EWK_W_2jets_l_pt = newtree->Branch("EWK_W_2jets_l_pt", &EWK_W_2jets_l_pt, "EWK_W_2jets_l_pt/F");
   TBranch *branch_EWK_W_2jets_l_eta= newtree->Branch("EWK_W_2jets_l_eta", &EWK_W_2jets_l_eta, "EWK_W_2jets_l_eta/F");
   TBranch *branch_EWK_W_2jets_l_phi = newtree->Branch("EWK_W_2jets_l_phi", &EWK_W_2jets_l_phi, "EWK_W_2jets_l_phi/F");
   TBranch *branch_EWK_W_2jets_l_e = newtree->Branch("EWK_W_2jets_l_e", &EWK_W_2jets_l_e, "EWK_W_2jets_l_e/F");
   TBranch *branch_EWK_W_2jets_l_MET_deltaphi = newtree->Branch("EWK_W_2jets_l_MET_deltaphi", &EWK_W_2jets_l_MET_deltaphi, "EWK_W_2jets_l_MET_deltaphi/F");

   Float_t EWK_W_2jets_l_tagjet1_deltaeta = -999, EWK_W_2jets_l_tagjet1_deltaphi = -999, EWK_W_2jets_l_tagjet1_deltaR = -999;
   Float_t EWK_W_2jets_l_tagjet2_deltaeta = -999, EWK_W_2jets_l_tagjet2_deltaphi = -999, EWK_W_2jets_l_tagjet2_deltaR = -999;
   TBranch *branch_EWK_W_2jets_l_tagjet1_deltaeta  = newtree->Branch("EWK_W_2jets_l_tagjet1_deltaeta", &EWK_W_2jets_l_tagjet1_deltaeta, "EWK_W_2jets_l_tagjet1_deltaeta/F");
   TBranch *branch_EWK_W_2jets_l_tagjet1_deltaphi = newtree->Branch("EWK_W_2jets_l_tagjet1_deltaphi", &EWK_W_2jets_l_tagjet1_deltaphi, "EWK_W_2jets_l_tagjet1_deltaphi/F");
   TBranch *branch_EWK_W_2jets_l_tagjet1_deltaR = newtree->Branch("EWK_W_2jets_l_tagjet1_deltaR", &EWK_W_2jets_l_tagjet1_deltaR, "EWK_W_2jets_l_tagjet1_deltaR/F");
   TBranch *branch_EWK_W_2jets_l_tagjet2_deltaeta = newtree->Branch("EWK_W_2jets_l_tagjet2_deltaeta", &EWK_W_2jets_l_tagjet2_deltaeta, "EWK_W_2jets_l_tagjet2_deltaeta/F");
   TBranch *branch_EWK_W_2jets_l_tagjet2_deltaphi = newtree->Branch("EWK_W_2jets_l_tagjet2_deltaphi", &EWK_W_2jets_l_tagjet2_deltaphi, "EWK_W_2jets_l_tagjet2_deltaphi/F");
   TBranch *branch_EWK_W_2jets_l_tagjet2_deltaR = newtree->Branch("EWK_W_2jets_l_tagjet2_deltaR", &EWK_W_2jets_l_tagjet2_deltaR, "EWK_W_2jets_l_tagjet2_deltaR/F");

   Float_t EWK_W_2jets_W_pt = -999, EWK_W_2jets_W_eta = -999, EWK_W_2jets_W_rap = -999, EWK_W_2jets_W_phi = -999, EWK_W_2jets_W_e = -999, EWK_W_2jets_W_mT = -999;
   TBranch *branch_EWK_W_2jets_W_pt = newtree->Branch("EWK_W_2jets_W_pt", &EWK_W_2jets_W_pt, "EWK_W_2jets_W_pt/F");
   TBranch *branch_EWK_W_2jets_W_rap = newtree->Branch("EWK_W_2jets_W_rap", &EWK_W_2jets_W_rap, "EWK_W_2jets_W_rap/F");
   TBranch *branch_EWK_W_2jets_W_eta = newtree->Branch("EWK_W_2jets_W_eta", &EWK_W_2jets_W_eta, "EWK_W_2jets_W_eta/F");
   TBranch *branch_EWK_W_2jets_W_phi = newtree->Branch("EWK_W_2jets_W_phi", &EWK_W_2jets_W_phi, "EWK_W_2jets_W_phi/F");
   TBranch *branch_EWK_W_2jets_W_e = newtree->Branch("EWK_W_2jets_W_e", &EWK_W_2jets_W_e, "EWK_W_2jets_W_e");
   TBranch *branch_EWK_W_2jets_W_mT = newtree->Branch("EWK_W_2jets_W_mT", &EWK_W_2jets_W_mT, "EWK_W_2jets_W_mT");

   Float_t EWK_W_2jets_W_tagjet1_deltaphi = -999, EWK_W_2jets_W_tagjet1_deltaeta = -999, EWK_W_2jets_W_tagjet1_deltaR = -999;
   Float_t EWK_W_2jets_W_tagjet2_deltaphi = -999, EWK_W_2jets_W_tagjet2_deltaeta = -999, EWK_W_2jets_W_tagjet2_deltaR = -999;
   TBranch *branch_EWK_W_2jets_W_tagjet1_deltaphi = newtree->Branch("EWK_W_2jets_W_tagjet1_deltaphi", &EWK_W_2jets_W_tagjet1_deltaphi, "EWK_W_2jets_W_tagjet1_deltaphi/F");
   TBranch *branch_EWK_W_2jets_W_tagjet1_deltaeta = newtree->Branch("EWK_W_2jets_W_tagjet1_deltaeta", &EWK_W_2jets_W_tagjet1_deltaeta, "EWK_W_2jets_W_tagjet1_deltaeta/F");
   TBranch *branch_EWK_W_2jets_W_tagjet1_deltaR = newtree->Branch("EWK_W_2jets_W_tagjet1_deltaR", &EWK_W_2jets_W_tagjet1_deltaR, "EWK_W_2jets_W_tagjet1_deltaR/F");
   TBranch *branch_EWK_W_2jets_W_tagjet2_deltaphi = newtree->Branch("EWK_W_2jets_W_tagjet2_deltaphi", &EWK_W_2jets_W_tagjet2_deltaphi, "EWK_W_2jets_W_tagjet2_deltaphi/F");
   TBranch *branch_EWK_W_2jets_W_tagjet2_deltaeta = newtree->Branch("EWK_W_2jets_W_tagjet2_deltaeta", &EWK_W_2jets_W_tagjet2_deltaeta, "EWK_W_2jets_W_tagjet2_deltaeta/F");
   TBranch *branch_EWK_W_2jets_W_tagjet2_deltaR = newtree->Branch("EWK_W_2jets_W_tagjet2_deltaR", &EWK_W_2jets_W_tagjet2_deltaR, "EWK_W_2jets_W_tagjet2_deltaR/F");

   Float_t EWK_W_2jets_W_tagjet_Zeppenfield = -999;
   TBranch *branch_EWK_W_2jets_W_tagjet_Zeppenfield = newtree->Branch("EWK_W_2jets_W_tagjet_Zeppenfield", &EWK_W_2jets_W_tagjet_Zeppenfield, "EWK_W_2jets_W_tagjet_Zeppenfield/F");

   Int_t EWK_W_2jets_centraljetnum_20 = 0, EWK_W_2jets_centraljetnum_25 = 0, EWK_W_2jets_centraljetnum_30 = 0;
   TBranch *branch_EWK_W_2jets_centraljetnum_20 = newtree->Branch("EWK_W_2jets_centraljetnum_20", &EWK_W_2jets_centraljetnum_20, "EWK_W_2jets_centraljetnum_20/I");
   TBranch *branch_EWK_W_2jets_centraljetnum_25 = newtree->Branch("EWK_W_2jets_centraljetnum_25", &EWK_W_2jets_centraljetnum_25, "EWK_W_2jets_centraljetnum_25/I");
   TBranch *branch_EWK_W_2jets_centraljetnum_30 = newtree->Branch("EWK_W_2jets_centraljetnum_30", &EWK_W_2jets_centraljetnum_30, "EWK_W_2jets_centraljetnum_30/I");

   Int_t EWK_W_2jets_findcentraljet = 0;
   TBranch *branch_EWK_W_2jets_findcentraljet = newtree->Branch("EWK_W_2jets_findcentraljet", &EWK_W_2jets_findcentraljet, "EWK_W_2jets_findcentraljet/I");

   Float_t EWK_W_2jets_centraljet_pt = -999, EWK_W_2jets_centraljet_eta = -999, EWK_W_2jets_centraljet_phi = -999, EWK_W_2jets_centraljet_e = -999, EWK_W_2jets_centraljet_m = -999;
   TBranch *branch_EWK_W_2jets_centraljet_pt = newtree->Branch("EWK_W_2jets_centraljet_pt", &EWK_W_2jets_centraljet_pt, "EWK_W_2jets_centraljet_pt/F");
   TBranch *branch_EWK_W_2jets_centraljet_eta = newtree->Branch("EWK_W_2jets_centraljet_eta", &EWK_W_2jets_centraljet_eta, "EWK_W_2jets_centraljet_eta/F");
   TBranch *branch_EWK_W_2jets_centraljet_phi = newtree->Branch("EWK_W_2jets_centraljet_phi", &EWK_W_2jets_centraljet_phi, "EWK_W_2jets_centraljet_phi/F");
   TBranch *branch_EWK_W_2jets_centraljet_e = newtree->Branch("EWK_W_2jets_centraljet_e", &EWK_W_2jets_centraljet_e, "EWK_W_2jets_centraljet_e/F");
   TBranch *branch_EWK_W_2jets_centraljet_m = newtree->Branch("EWK_W_2jets_centraljet_m", &EWK_W_2jets_centraljet_m, "EWK_W_2jets_centraljet_m/F");

   Float_t EWK_W_2jets_centraljet_tagjet1_deltaeta = -999, EWK_W_2jets_centraljet_tagjet1_deltaphi = -999, EWK_W_2jets_centraljet_tagjet1_deltaR = -999; 
   Float_t EWK_W_2jets_centraljet_tagjet2_deltaeta = -999, EWK_W_2jets_centraljet_tagjet2_deltaphi = -999, EWK_W_2jets_centraljet_tagjet2_deltaR = -999;
   TBranch *branch_EWK_W_2jets_centraljet_tagjet1_deltaeta  = newtree->Branch("EWK_W_2jets_centraljet_tagjet1_deltaeta", &EWK_W_2jets_centraljet_tagjet1_deltaeta, "EWK_W_2jets_centraljet_tagjet1_deltaeta/F");
   TBranch *branch_EWK_W_2jets_centraljet_tagjet1_deltaphi = newtree->Branch("EWK_W_2jets_centraljet_tagjet1_deltaphi", &EWK_W_2jets_centraljet_tagjet1_deltaphi, "EWK_W_2jets_centraljet_tagjet1_deltaphi/F");
   TBranch *branch_EWK_W_2jets_centraljet_tagjet1_deltaR = newtree->Branch("EWK_W_2jets_centraljet_tagjet1_deltaR", &EWK_W_2jets_centraljet_tagjet1_deltaR, "EWK_W_2jets_centraljet_tagjet1_deltaR/F");
   TBranch *branch_EWK_W_2jets_centraljet_tagjet2_deltaeta  = newtree->Branch("EWK_W_2jets_centraljet_tagjet2_deltaeta", &EWK_W_2jets_centraljet_tagjet2_deltaeta, "EWK_W_2jets_centraljet_tagjet2_deltaeta/F");
   TBranch *branch_EWK_W_2jets_centraljet_tagjet2_deltaphi = newtree->Branch("EWK_W_2jets_centraljet_tagjet2_deltaphi", &EWK_W_2jets_centraljet_tagjet2_deltaphi, "EWK_W_2jets_centraljet_tagjet2_deltaphi/F");
   TBranch *branch_EWK_W_2jets_centraljet_tagjet2_deltaR = newtree->Branch("EWK_W_2jets_centraljet_tagjet2_deltaR", &EWK_W_2jets_centraljet_tagjet2_deltaR, "EWK_W_2jets_centraljet_tagjet2_deltaR/F");

   Float_t EWK_W_2jets_centraljet_tagjet_Zeppenfield = -999; 
   TBranch *branch_EWK_W_2jets_centraljet_tagjet_Zeppenfield = newtree->Branch("EWK_W_2jets_centraljet_tagjet_Zeppenfield", &EWK_W_2jets_centraljet_tagjet_Zeppenfield, "EWK_W_2jets_centraljet_tagjet_Zeppenfield/F");

   Float_t EWK_W_2jets_tagjet1_QGd = -999;
   Float_t EWK_W_2jets_tagjet2_QGd = -999;
   TBranch *branch_EWK_W_2jets_tagjet1_QGd = newtree->Branch("EWK_W_2jets_tagjet1_QGd", &EWK_W_2jets_tagjet1_QGd, "EWK_W_2jets_tagjet1_QGd/F");
   TBranch *branch_EWK_W_2jets_tagjet2_QGd = newtree->Branch("EWK_W_2jets_tagjet2_QGd", &EWK_W_2jets_tagjet2_QGd, "EWK_W_2jets_tagjet2_QGd/F");

   Float_t EWK_W_2jets_tagjet1_btagCSV = -999;
   Float_t EWK_W_2jets_tagjet2_btagCSV = -999;
   TBranch *branch_EWK_W_2jets_tagjet1_btagCSV = newtree->Branch("EWK_W_2jets_tagjet1_btagCSV", &EWK_W_2jets_tagjet1_btagCSV, "EWK_W_2jets_tagjet1_btagCSV/F");
   TBranch *branch_EWK_W_2jets_tagjet2_btagCSV = newtree->Branch("EWK_W_2jets_tagjet2_btagCSV", &EWK_W_2jets_tagjet2_btagCSV, "EWK_W_2jets_tagjet2_btagCSV/F");

   //EWK GEN information
   Float_t EWK_W_2jets_genW_pt = -999, EWK_W_2jets_genW_eta = -999, EWK_W_2jets_genW_phi = -999, EWK_W_2jets_genW_e = -999;
   TBranch *branch_EWK_W_2jets_genW_pt = newtree->Branch("EWK_W_2jets_genW_pt",&EWK_W_2jets_genW_pt, "EWK_W_2jets_genW_pt/F");
   TBranch *branch_EWK_W_2jets_genW_eta = newtree->Branch("EWK_W_2jets_genW_eta",&EWK_W_2jets_genW_eta, "EWK_W_2jets_genW_eta/F");
   TBranch *branch_EWK_W_2jets_genW_phi = newtree->Branch("EWK_W_2jets_genW_phi",&EWK_W_2jets_genW_phi, "EWK_W_2jets_genW_phi/F");
   TBranch *branch_EWK_W_2jets_genW_e = newtree->Branch("EWK_W_2jets_genW_e",&EWK_W_2jets_genW_e, "EWK_W_2jets_genW_e/F");

   Float_t EWK_W_2jets_genTagquark1_pt = -999, EWK_W_2jets_genTagquark1_eta = -999, EWK_W_2jets_genTagquark1_phi = -999, EWK_W_2jets_genTagquark1_e = -999;
   Int_t   EWK_W_2jets_genTagquark1_id = 0;
   TBranch *branch_EWK_W_2jets_genTagquark1_pt = newtree->Branch("EWK_W_2jets_genTagquark1_pt",&EWK_W_2jets_genTagquark1_pt, "EWK_W_2jets_genTagquark1_pt/F");
   TBranch *branch_EWK_W_2jets_genTagquark1_eta = newtree->Branch("EWK_W_2jets_genTagquark1_eta",&EWK_W_2jets_genTagquark1_eta, "EWK_W_2jets_genTagquark1_eta/F");
   TBranch *branch_EWK_W_2jets_genTagquark1_phi = newtree->Branch("EWK_W_2jets_genTagquark1_phi",&EWK_W_2jets_genTagquark1_phi, "EWK_W_2jets_genTagquark1_phi/F");
   TBranch *branch_EWK_W_2jets_genTagquark1_e = newtree->Branch("EWK_W_2jets_genTagquark1_e",&EWK_W_2jets_genTagquark1_e, "EWK_W_2jets_genTagquark1_e/F");
   TBranch *branch_EWK_W_2jets_genTagquark1_id = newtree->Branch("EWK_W_2jets_genTagquark1_id",&EWK_W_2jets_genTagquark1_id, "EWK_W_2jets_genTagquark1_id/I");

   Float_t EWK_W_2jets_genTagquark2_pt = -999, EWK_W_2jets_genTagquark2_eta = -999, EWK_W_2jets_genTagquark2_phi = -999, EWK_W_2jets_genTagquark2_e = -999;
   Int_t   EWK_W_2jets_genTagquark2_id = 0;
   TBranch *branch_EWK_W_2jets_genTagquark2_pt = newtree->Branch("EWK_W_2jets_genTagquark2_pt",&EWK_W_2jets_genTagquark2_pt, "EWK_W_2jets_genTagquark2_pt/F");
   TBranch *branch_EWK_W_2jets_genTagquark2_eta = newtree->Branch("EWK_W_2jets_genTagquark2_eta",&EWK_W_2jets_genTagquark2_eta, "EWK_W_2jets_genTagquark2_eta/F");
   TBranch *branch_EWK_W_2jets_genTagquark2_phi = newtree->Branch("EWK_W_2jets_genTagquark2_phi",&EWK_W_2jets_genTagquark2_phi, "EWK_W_2jets_genTagquark2_phi/F");
   TBranch *branch_EWK_W_2jets_genTagquark2_e = newtree->Branch("EWK_W_2jets_genTagquark2_e",&EWK_W_2jets_genTagquark2_e, "EWK_W_2jets_genTagquark2_e/F");
   TBranch *branch_EWK_W_2jets_genTagquark2_id = newtree->Branch("EWK_W_2jets_genTagquark2_id",&EWK_W_2jets_genTagquark2_id, "EWK_W_2jets_genTagquark2_id/I");

   //WJets for Counting the Number of Partons
   Int_t W_gen_numPartons = 0;
   TBranch *branch_W_gen_numPartons = newtree->Branch("W_gen_numPartons", &W_gen_numPartons, "W_gen_numPartons/I");

   Float_t W_nParton_weight = 1.0;
   TBranch *branch_W_nParton_weight = newtree->Branch("W_nParton_weight", &W_nParton_weight, "W_nParton_weight/F");
   //End for EWK W+2jets Analysis

   //New Category for ttH analysis
   Int_t ttH_check_event = 0;
   Int_t ttH_event = 0, ttH_waj_id = -1, ttH_wbj_id = -1, ttH_toplvj_aj_id = -1, ttH_topjjj_aj_id = -1, ttH_dijetaj_id = -1, ttH_dijetbj_id = -1;
   Int_t ttH_fitstatus = -1, ttH_fitNDF = -1;
   Float_t ttH_fitchi2 = -999.;
   TBranch *branch_ttH_check_event = newtree->Branch("ttH_check_event", &ttH_check_event, "ttH_check_event/I");
   TBranch *branch_ttH_event = newtree->Branch("ttH_event", &ttH_event, "ttH_event/I");
   TBranch *branch_ttH_fitstatus = newtree->Branch("ttH_fitstatus", &ttH_fitstatus, "ttH_fitstatus/I");
   TBranch *branch_ttH_fitNDF = newtree->Branch("ttH_fitNDF", &ttH_fitNDF, "ttH_fitNDF/I");
   TBranch *branch_ttH_fitchi2 = newtree->Branch("ttH_fitchi2", &ttH_fitchi2, "ttH_fitchi2/F");
   TBranch *branch_ttH_waj_id = newtree->Branch("ttH_waj_id", &ttH_waj_id, "ttH_waj_id/I");
   TBranch *branch_ttH_wbj_id = newtree->Branch("ttH_wbj_id", &ttH_wbj_id, "ttH_wbj_id/I");
   TBranch *branch_ttH_toplvj_aj_id = newtree->Branch("ttH_toplvj_aj_id", &ttH_toplvj_aj_id, "ttH_toplvj_aj_id/I");
   TBranch *branch_ttH_topjjj_aj_id = newtree->Branch("ttH_topjjj_aj_id", &ttH_topjjj_aj_id, "ttH_topjjj_aj_id/I");
   TBranch *branch_ttH_dijetaj_id = newtree->Branch("ttH_dijetaj_id", &ttH_dijetaj_id, "ttH_dijetaj_id/I");
   TBranch *branch_ttH_dijetbj_id = newtree->Branch("ttH_dijetbj_id", &ttH_dijetbj_id, "ttH_dijetbj_id/I");

   Float_t ttH_wlv_e = -999, ttH_wlv_pt = -999, ttH_wlv_eta = -999, ttH_wlv_phi = -999, ttH_wlv_m = -999;
   Float_t ttH_waj_e = -999, ttH_waj_pt = -999, ttH_waj_eta = -999, ttH_waj_phi = -999, ttH_waj_m = -999;
   Float_t ttH_wbj_e = -999, ttH_wbj_pt = -999, ttH_wbj_eta = -999, ttH_wbj_phi = -999, ttH_wbj_m = -999;
   Float_t ttH_wjj_e = -999, ttH_wjj_pt = -999, ttH_wjj_eta = -999, ttH_wjj_phi = -999, ttH_wjj_m = -999;
   Float_t ttH_topjjj_aj_e = -999, ttH_topjjj_aj_pt = -999, ttH_topjjj_aj_eta = -999, ttH_topjjj_aj_phi = -999, ttH_topjjj_aj_m = -999, ttH_topjjj_aj_btagcsv = -999;
   Float_t ttH_toplvj_aj_e = -999, ttH_toplvj_aj_pt = -999, ttH_toplvj_aj_eta = -999, ttH_toplvj_aj_phi = -999, ttH_toplvj_aj_m = -999, ttH_toplvj_aj_btagcsv = -999;
   Float_t ttH_topjjj_e = -999, ttH_topjjj_pt = -999, ttH_topjjj_eta = -999, ttH_topjjj_phi = -999, ttH_topjjj_m = -999;
   Float_t ttH_toplvj_e = -999, ttH_toplvj_pt = -999, ttH_toplvj_eta = -999, ttH_toplvj_phi = -999, ttH_toplvj_m = -999;
   Float_t ttH_dijetaj_e = -999, ttH_dijetaj_pt = -999, ttH_dijetaj_eta = -999, ttH_dijetaj_phi = -999, ttH_dijetaj_m = -999, ttH_dijetaj_btagcsv = -999;
   Float_t ttH_dijetbj_e = -999, ttH_dijetbj_pt = -999, ttH_dijetbj_eta = -999, ttH_dijetbj_phi = -999, ttH_dijetbj_m = -999, ttH_dijetbj_btagcsv = -999;
   Float_t ttH_dijetajbj_deltaR = -999, ttH_dijetajbj_deltaphi = -999;
   Float_t ttH_dijet_e = -999, ttH_dijet_pt = -999, ttH_dijet_eta = -999, ttH_dijet_phi = -999, ttH_dijet_m = -999, ttH_dijet_y = -999;
   Float_t ttH_ditop_e = -999, ttH_ditop_pt = -999, ttH_ditop_eta = -999, ttH_ditop_phi = -999, ttH_ditop_m = -999, ttH_ditop_y = -999;
   Float_t ttH_toplvjdijetaj_deltaR = -999, ttH_toplvjdijetaj_deltaphi = -999;
   Float_t ttH_topjjjdijetaj_deltaR = -999, ttH_topjjjdijetaj_deltaphi = -999;
   Float_t ttH_toplvjdijetbj_deltaR = -999, ttH_toplvjdijetbj_deltaphi = -999;
   Float_t ttH_topjjjdijetbj_deltaR = -999, ttH_topjjjdijetbj_deltaphi = -999;
   Float_t ttH_toplvjdijet_deltaR = -999, ttH_toplvjdijet_deltaphi = -999;
   Float_t ttH_topjjjdijet_deltaR = -999, ttH_topjjjdijet_deltaphi = -999;
   Float_t ttH_ditopdijet_deltaR  = -999, ttH_ditopdijet_deltaphi = -999;

   TBranch *branch_ttH_wlv_e   =  newtree->Branch("ttH_wlv_e", &ttH_wlv_e, "ttH_wlv_e/F");
   TBranch *branch_ttH_wlv_pt  =  newtree->Branch("ttH_wlv_pt", &ttH_wlv_pt, "ttH_wlv_pt/F");
   TBranch *branch_ttH_wlv_eta =  newtree->Branch("ttH_wlv_eta", &ttH_wlv_eta, "ttH_wlv_eta/F");
   TBranch *branch_ttH_wlv_phi =  newtree->Branch("ttH_wlv_phi", &ttH_wlv_phi, "ttH_wlv_phi/F");
   TBranch *branch_ttH_wlv_m   =  newtree->Branch("ttH_wlv_m", &ttH_wlv_m, "ttH_wlv_m/F");

   TBranch *branch_ttH_waj_e   =  newtree->Branch("ttH_waj_e", &ttH_waj_e, "ttH_waj_e/F");
   TBranch *branch_ttH_waj_pt  =  newtree->Branch("ttH_waj_pt", &ttH_waj_pt, "ttH_waj_pt/F");
   TBranch *branch_ttH_waj_eta =  newtree->Branch("ttH_waj_eta", &ttH_waj_eta, "ttH_waj_eta/F");
   TBranch *branch_ttH_waj_phi =  newtree->Branch("ttH_waj_phi", &ttH_waj_phi, "ttH_waj_phi/F");
   TBranch *branch_ttH_waj_m   =  newtree->Branch("ttH_waj_m", &ttH_waj_m, "ttH_waj_m/F");

   TBranch *branch_ttH_wbj_e   =  newtree->Branch("ttH_wbj_e", &ttH_wbj_e, "ttH_wbj_e/F");
   TBranch *branch_ttH_wbj_pt  =  newtree->Branch("ttH_wbj_pt", &ttH_wbj_pt, "ttH_wbj_pt/F");
   TBranch *branch_ttH_wbj_eta =  newtree->Branch("ttH_wbj_eta", &ttH_wbj_eta, "ttH_wbj_eta/F");
   TBranch *branch_ttH_wbj_phi =  newtree->Branch("ttH_wbj_phi", &ttH_wbj_phi, "ttH_wbj_phi/F");
   TBranch *branch_ttH_wbj_m   =  newtree->Branch("ttH_wbj_m", &ttH_wbj_m, "ttH_wbj_m/F");

   TBranch *branch_ttH_wjj_e   =  newtree->Branch("ttH_wjj_e", &ttH_wjj_e, "ttH_wjj_e/F");
   TBranch *branch_ttH_wjj_pt  =  newtree->Branch("ttH_wjj_pt", &ttH_wjj_pt, "ttH_wjj_pt/F");
   TBranch *branch_ttH_wjj_eta =  newtree->Branch("ttH_wjj_eta", &ttH_wjj_eta, "ttH_wjj_eta/F");
   TBranch *branch_ttH_wjj_phi =  newtree->Branch("ttH_wjj_phi", &ttH_wjj_phi, "ttH_wjj_phi/F");
   TBranch *branch_ttH_wjj_m   =  newtree->Branch("ttH_wjj_m", &ttH_wjj_m, "ttH_wjj_m/F");

   TBranch *branch_ttH_topjjj_aj_e   =  newtree->Branch("ttH_topjjj_aj_e", &ttH_topjjj_aj_e, "ttH_topjjj_aj_e/F");
   TBranch *branch_ttH_topjjj_aj_pt  =  newtree->Branch("ttH_topjjj_aj_pt", &ttH_topjjj_aj_pt, "ttH_topjjj_aj_pt/F");
   TBranch *branch_ttH_topjjj_aj_eta =  newtree->Branch("ttH_topjjj_aj_eta", &ttH_topjjj_aj_eta, "ttH_topjjj_aj_eta/F");
   TBranch *branch_ttH_topjjj_aj_phi =  newtree->Branch("ttH_topjjj_aj_phi", &ttH_topjjj_aj_phi, "ttH_topjjj_aj_phi/F");
   TBranch *branch_ttH_topjjj_aj_m   =  newtree->Branch("ttH_topjjj_aj_m", &ttH_topjjj_aj_m, "ttH_topjjj_aj_m/F");
   TBranch *branch_ttH_topjjj_aj_btagcsv = newtree->Branch("ttH_topjjj_aj_btagcsv", &ttH_topjjj_aj_btagcsv, "ttH_topjjj_aj_btagcsv/F");

   TBranch *branch_ttH_toplvj_aj_e   =  newtree->Branch("ttH_toplvj_aj_e", &ttH_toplvj_aj_e, "ttH_toplvj_aj_e/F");
   TBranch *branch_ttH_toplvj_aj_pt  =  newtree->Branch("ttH_toplvj_aj_pt", &ttH_toplvj_aj_pt, "ttH_toplvj_aj_pt/F");
   TBranch *branch_ttH_toplvj_aj_eta =  newtree->Branch("ttH_toplvj_aj_eta", &ttH_toplvj_aj_eta, "ttH_toplvj_aj_eta/F");
   TBranch *branch_ttH_toplvj_aj_phi =  newtree->Branch("ttH_toplvj_aj_phi", &ttH_toplvj_aj_phi, "ttH_toplvj_aj_phi/F");
   TBranch *branch_ttH_toplvj_aj_m   =  newtree->Branch("ttH_toplvj_aj_m", &ttH_toplvj_aj_m, "ttH_toplvj_aj_m/F");
   TBranch *branch_ttH_toplvj_aj_btagcsv = newtree->Branch("ttH_toplvj_aj_btagcsv", &ttH_toplvj_aj_btagcsv, "ttH_toplvj_aj_btagcsv/F");

   TBranch *branch_ttH_topjjj_e   =  newtree->Branch("ttH_topjjj_e", &ttH_topjjj_e, "ttH_topjjj_e/F");
   TBranch *branch_ttH_topjjj_pt  =  newtree->Branch("ttH_topjjj_pt", &ttH_topjjj_pt, "ttH_topjjj_pt/F");
   TBranch *branch_ttH_topjjj_eta =  newtree->Branch("ttH_topjjj_eta", &ttH_topjjj_eta, "ttH_topjjj_eta/F");
   TBranch *branch_ttH_topjjj_phi =  newtree->Branch("ttH_topjjj_phi", &ttH_topjjj_phi, "ttH_topjjj_phi/F");
   TBranch *branch_ttH_topjjj_m   =  newtree->Branch("ttH_topjjj_m", &ttH_topjjj_m, "ttH_topjjj_m/F");

   TBranch *branch_ttH_toplvj_e   =  newtree->Branch("ttH_toplvj_e", &ttH_toplvj_e, "ttH_toplvj_e/F");
   TBranch *branch_ttH_toplvj_pt  =  newtree->Branch("ttH_toplvj_pt", &ttH_toplvj_pt, "ttH_toplvj_pt/F");
   TBranch *branch_ttH_toplvj_eta =  newtree->Branch("ttH_toplvj_eta", &ttH_toplvj_eta, "ttH_toplvj_eta/F");
   TBranch *branch_ttH_toplvj_phi =  newtree->Branch("ttH_toplvj_phi", &ttH_toplvj_phi, "ttH_toplvj_phi/F");
   TBranch *branch_ttH_toplvj_m   =  newtree->Branch("ttH_toplvj_m", &ttH_toplvj_m, "ttH_toplvj_m/F");

   TBranch *branch_ttH_dijetaj_e   =  newtree->Branch("ttH_dijetaj_e", &ttH_dijetaj_e, "ttH_dijetaj_e/F");
   TBranch *branch_ttH_dijetaj_pt  =  newtree->Branch("ttH_dijetaj_pt", &ttH_dijetaj_pt, "ttH_dijetaj_pt/F");
   TBranch *branch_ttH_dijetaj_eta =  newtree->Branch("ttH_dijetaj_eta", &ttH_dijetaj_eta, "ttH_dijetaj_eta/F");
   TBranch *branch_ttH_dijetaj_phi =  newtree->Branch("ttH_dijetaj_phi", &ttH_dijetaj_phi, "ttH_dijetaj_phi/F");
   TBranch *branch_ttH_dijetaj_m   =  newtree->Branch("ttH_dijetaj_m", &ttH_dijetaj_m, "ttH_dijetaj_m/F");
   TBranch *branch_ttH_dijetaj_btagcsv = newtree->Branch("ttH_dijetaj_btagcsv", &ttH_dijetaj_btagcsv, "ttH_dijetaj_btagcsv/F");

   TBranch *branch_ttH_dijetbj_e   =  newtree->Branch("ttH_dijetbj_e", &ttH_dijetbj_e, "ttH_dijetbj_e/F");
   TBranch *branch_ttH_dijetbj_pt  =  newtree->Branch("ttH_dijetbj_pt", &ttH_dijetbj_pt, "ttH_dijetbj_pt/F");
   TBranch *branch_ttH_dijetbj_eta =  newtree->Branch("ttH_dijetbj_eta", &ttH_dijetbj_eta, "ttH_dijetbj_eta/F");
   TBranch *branch_ttH_dijetbj_phi =  newtree->Branch("ttH_dijetbj_phi", &ttH_dijetbj_phi, "ttH_dijetbj_phi/F");
   TBranch *branch_ttH_dijetbj_m   =  newtree->Branch("ttH_dijetbj_m", &ttH_dijetbj_m, "ttH_dijetbj_m/F");
   TBranch *branch_ttH_dijetbj_btagcsv = newtree->Branch("ttH_dijetbj_btagcsv", &ttH_dijetbj_btagcsv, "ttH_dijetbj_btagcsv/F");

   TBranch *branch_ttH_dijetajbj_deltaR =  newtree->Branch("ttH_dijetajbj_deltaR", &ttH_dijetajbj_deltaR, "ttH_dijetajbj_deltaR/F");
   TBranch *branch_ttH_dijetajbj_deltaphi =  newtree->Branch("ttH_dijetajbj_deltaphi", &ttH_dijetajbj_deltaphi, "ttH_dijetajbj_deltaphi/F");

   TBranch *branch_ttH_dijet_e   =  newtree->Branch("ttH_dijet_e", &ttH_dijet_e, "ttH_dijet_e/F");
   TBranch *branch_ttH_dijet_pt  =  newtree->Branch("ttH_dijet_pt", &ttH_dijet_pt, "ttH_dijet_pt/F");
   TBranch *branch_ttH_dijet_eta =  newtree->Branch("ttH_dijet_eta", &ttH_dijet_eta, "ttH_dijet_eta/F");
   TBranch *branch_ttH_dijet_phi =  newtree->Branch("ttH_dijet_phi", &ttH_dijet_phi, "ttH_dijet_phi/F");
   TBranch *branch_ttH_dijet_m   =  newtree->Branch("ttH_dijet_m", &ttH_dijet_m, "ttH_dijet_m/F");
   TBranch *branch_ttH_dijet_y   =  newtree->Branch("ttH_dijet_y", &ttH_dijet_y, "ttH_dijet_y/F");

   TBranch *branch_ttH_ditop_e   =  newtree->Branch("ttH_ditop_e", &ttH_ditop_e, "ttH_ditop_e/F");
   TBranch *branch_ttH_ditop_pt  =  newtree->Branch("ttH_ditop_pt", &ttH_ditop_pt, "ttH_ditop_pt/F");
   TBranch *branch_ttH_ditop_eta =  newtree->Branch("ttH_ditop_eta", &ttH_ditop_eta, "ttH_ditop_eta/F");
   TBranch *branch_ttH_ditop_phi =  newtree->Branch("ttH_ditop_phi", &ttH_ditop_phi, "ttH_ditop_phi/F");
   TBranch *branch_ttH_ditop_m   =  newtree->Branch("ttH_ditop_m", &ttH_ditop_m, "ttH_ditop_m/F");
   TBranch *branch_ttH_ditop_y   =  newtree->Branch("ttH_ditop_y", &ttH_ditop_y, "ttH_ditop_y/F");

   TBranch *branch_ttH_toplvjdijetaj_deltaR = newtree->Branch("ttH_toplvjdijetaj_deltaR", &ttH_toplvjdijetaj_deltaR, "ttH_toplvjdijetaj_deltaR/F");
   TBranch *branch_ttH_toplvjdijetaj_deltaphi = newtree->Branch("ttH_toplvjdijetaj_deltaphi", &ttH_toplvjdijetaj_deltaphi, "ttH_toplvjdijetaj_deltaphi/F");
   TBranch *branch_ttH_topjjjdijetaj_deltaR = newtree->Branch("ttH_topjjjdijetaj_deltaR", &ttH_topjjjdijetaj_deltaR, "ttH_topjjjdijetaj_deltaR/F");
   TBranch *branch_ttH_topjjjdijetaj_deltaphi = newtree->Branch("ttH_topjjjdijetaj_deltaphi", &ttH_topjjjdijetaj_deltaphi, "ttH_topjjjdijetaj_deltaphi/F");
   TBranch *branch_ttH_toplvjdijetbj_deltaR = newtree->Branch("ttH_toplvjdijetbj_deltaR", &ttH_toplvjdijetbj_deltaR, "ttH_toplvjdijetbj_deltaR/F");
   TBranch *branch_ttH_toplvjdijetbj_deltaphi = newtree->Branch("ttH_toplvjdijetbj_deltaphi", &ttH_toplvjdijetbj_deltaphi, "ttH_toplvjdijetbj_deltaphi/F");
   TBranch *branch_ttH_topjjjdijetbj_deltaR = newtree->Branch("ttH_topjjjdijetbj_deltaR", &ttH_topjjjdijetbj_deltaR, "ttH_topjjjdijetbj_deltaR/F");
   TBranch *branch_ttH_topjjjdijetbj_deltaphi = newtree->Branch("ttH_topjjjdijetbj_deltaphi", &ttH_topjjjdijetbj_deltaphi, "ttH_topjjjdijetbj_deltaphi/F");

   TBranch *branch_ttH_ditopdijet_deltaR   =  newtree->Branch("ttH_ditopdijet_deltaR", &ttH_ditopdijet_deltaR, "ttH_ditopdijet_deltaR/F");
   TBranch *branch_ttH_ditopdijet_deltaphi =  newtree->Branch("ttH_ditopdijet_deltaphi", &ttH_ditopdijet_deltaphi, "ttH_ditopdijet_deltaphi/F");
   TBranch *branch_ttH_toplvjdijet_deltaR  =  newtree->Branch("ttH_toplvjdijet_deltaR", &ttH_toplvjdijet_deltaR, "ttH_toplvjdijet_deltaR/F");  
   TBranch *branch_ttH_toplvjdijet_deltaphi =  newtree->Branch("ttH_toplvjdijet_deltaphi", &ttH_toplvjdijet_deltaphi, "ttH_toplvjdijet_deltaphi/F");  
   TBranch *branch_ttH_topjjjdijet_deltaR  =  newtree->Branch("ttH_topjjjdijet_deltaR", &ttH_topjjjdijet_deltaR, "ttH_topjjjdijet_deltaR/F");  
   TBranch *branch_ttH_topjjjdijet_deltaphi =  newtree->Branch("ttH_topjjjdijet_deltaphi", &ttH_topjjjdijet_deltaphi, "ttH_topjjjdijet_deltaphi/F");  
   //End for the ttH analysis

   // For MVA analysis
   const char* inputVars[] = { "ptlvjj", "ylvjj", "W_muon_charge", "ang_ha", "ang_hb", "ang_hs", "ang_phi", "ang_phib" };
   std::vector<std::string> inputVarsMVA;
   for (int i=0; i<8; ++i) inputVarsMVA.push_back( inputVars[i] );

   ReadMVA2j170mu mvaReader2j170mu( inputVarsMVA );  
   ReadMVA2j180mu mvaReader2j180mu( inputVarsMVA );  
   ReadMVA2j190mu mvaReader2j190mu( inputVarsMVA );  
   ReadMVA2j200mu mvaReader2j200mu( inputVarsMVA );  
   ReadMVA2j250mu mvaReader2j250mu( inputVarsMVA );  
   ReadMVA2j300mu mvaReader2j300mu( inputVarsMVA );  
   ReadMVA2j350mu mvaReader2j350mu( inputVarsMVA );  
   ReadMVA2j400mu mvaReader2j400mu( inputVarsMVA );  
   ReadMVA2j450mu mvaReader2j450mu( inputVarsMVA );  
   ReadMVA2j500mu mvaReader2j500mu( inputVarsMVA );  
   ReadMVA2j550mu mvaReader2j550mu( inputVarsMVA );  
   ReadMVA2j600mu mvaReader2j600mu( inputVarsMVA );  
   ReadMVA2j400interferencedownmu mvaReader2j400interferencedownmu( inputVarsMVA );
   ReadMVA2j400interferencenominalmu mvaReader2j400interferencenominalmu( inputVarsMVA );
   ReadMVA2j400interferenceupmu mvaReader2j400interferenceupmu( inputVarsMVA );
   ReadMVA2j450interferencedownmu mvaReader2j450interferencedownmu( inputVarsMVA );
   ReadMVA2j450interferencenominalmu mvaReader2j450interferencenominalmu( inputVarsMVA );
   ReadMVA2j450interferenceupmu mvaReader2j450interferenceupmu( inputVarsMVA );
   ReadMVA2j500interferencedownmu mvaReader2j500interferencedownmu( inputVarsMVA );
   ReadMVA2j500interferencenominalmu mvaReader2j500interferencenominalmu( inputVarsMVA );
   ReadMVA2j500interferenceupmu mvaReader2j500interferenceupmu( inputVarsMVA );
   ReadMVA2j550interferencedownmu mvaReader2j550interferencedownmu( inputVarsMVA );
   ReadMVA2j550interferencenominalmu mvaReader2j550interferencenominalmu( inputVarsMVA );
   ReadMVA2j550interferenceupmu mvaReader2j550interferenceupmu( inputVarsMVA );
   ReadMVA2j600interferencedownmu mvaReader2j600interferencedownmu( inputVarsMVA );
   ReadMVA2j600interferencenominalmu mvaReader2j600interferencenominalmu( inputVarsMVA );
   ReadMVA2j600interferenceupmu mvaReader2j600interferenceupmu( inputVarsMVA );
   ReadMVA2j700interferencedownmu mvaReader2j700interferencedownmu( inputVarsMVA );
   ReadMVA2j700interferencenominalmu mvaReader2j700interferencenominalmu( inputVarsMVA );
   ReadMVA2j700interferenceupmu mvaReader2j700interferenceupmu( inputVarsMVA );
   ReadMVA2j800interferencedownmu mvaReader2j800interferencedownmu( inputVarsMVA );
   ReadMVA2j800interferencenominalmu mvaReader2j800interferencenominalmu( inputVarsMVA );
   ReadMVA2j800interferenceupmu mvaReader2j800interferenceupmu( inputVarsMVA );
   ReadMVA2j900interferencedownmu mvaReader2j900interferencedownmu( inputVarsMVA );
   ReadMVA2j900interferencenominalmu mvaReader2j900interferencenominalmu( inputVarsMVA );
   ReadMVA2j900interferenceupmu mvaReader2j900interferenceupmu( inputVarsMVA );
   ReadMVA2j1000interferencedownmu mvaReader2j1000interferencedownmu( inputVarsMVA );
   ReadMVA2j1000interferencenominalmu mvaReader2j1000interferencenominalmu( inputVarsMVA );
   ReadMVA2j1000interferenceupmu mvaReader2j1000interferenceupmu( inputVarsMVA );

   ReadMVA3j170mu mvaReader3j170mu( inputVarsMVA );  
   ReadMVA3j180mu mvaReader3j180mu( inputVarsMVA );  
   ReadMVA3j190mu mvaReader3j190mu( inputVarsMVA );  
   ReadMVA3j200mu mvaReader3j200mu( inputVarsMVA );  
   ReadMVA3j250mu mvaReader3j250mu( inputVarsMVA );  
   ReadMVA3j300mu mvaReader3j300mu( inputVarsMVA );  
   ReadMVA3j350mu mvaReader3j350mu( inputVarsMVA );  
   ReadMVA3j400mu mvaReader3j400mu( inputVarsMVA );  
   ReadMVA3j450mu mvaReader3j450mu( inputVarsMVA );  
   ReadMVA3j500mu mvaReader3j500mu( inputVarsMVA );  
   ReadMVA3j550mu mvaReader3j550mu( inputVarsMVA );  
   ReadMVA3j600mu mvaReader3j600mu( inputVarsMVA );  
   ReadMVA3j400interferencedownmu mvaReader3j400interferencedownmu( inputVarsMVA );
   ReadMVA3j400interferencenominalmu mvaReader3j400interferencenominalmu( inputVarsMVA );
   ReadMVA3j400interferenceupmu mvaReader3j400interferenceupmu( inputVarsMVA );
   ReadMVA3j450interferencedownmu mvaReader3j450interferencedownmu( inputVarsMVA );
   ReadMVA3j450interferencenominalmu mvaReader3j450interferencenominalmu( inputVarsMVA );
   ReadMVA3j450interferenceupmu mvaReader3j450interferenceupmu( inputVarsMVA );
   ReadMVA3j500interferencedownmu mvaReader3j500interferencedownmu( inputVarsMVA );
   ReadMVA3j500interferencenominalmu mvaReader3j500interferencenominalmu( inputVarsMVA );
   ReadMVA3j500interferenceupmu mvaReader3j500interferenceupmu( inputVarsMVA );
   ReadMVA3j550interferencedownmu mvaReader3j550interferencedownmu( inputVarsMVA );
   ReadMVA3j550interferencenominalmu mvaReader3j550interferencenominalmu( inputVarsMVA );
   ReadMVA3j550interferenceupmu mvaReader3j550interferenceupmu( inputVarsMVA );
   ReadMVA3j600interferencedownmu mvaReader3j600interferencedownmu( inputVarsMVA );
   ReadMVA3j600interferencenominalmu mvaReader3j600interferencenominalmu( inputVarsMVA );
   ReadMVA3j600interferenceupmu mvaReader3j600interferenceupmu( inputVarsMVA );
   ReadMVA3j700interferencedownmu mvaReader3j700interferencedownmu( inputVarsMVA );
   ReadMVA3j700interferencenominalmu mvaReader3j700interferencenominalmu( inputVarsMVA );
   ReadMVA3j700interferenceupmu mvaReader3j700interferenceupmu( inputVarsMVA );
   ReadMVA3j800interferencedownmu mvaReader3j800interferencedownmu( inputVarsMVA );
   ReadMVA3j800interferencenominalmu mvaReader3j800interferencenominalmu( inputVarsMVA );
   ReadMVA3j800interferenceupmu mvaReader3j800interferenceupmu( inputVarsMVA );
   ReadMVA3j900interferencedownmu mvaReader3j900interferencedownmu( inputVarsMVA );
   ReadMVA3j900interferencenominalmu mvaReader3j900interferencenominalmu( inputVarsMVA );
   ReadMVA3j900interferenceupmu mvaReader3j900interferenceupmu( inputVarsMVA );
   ReadMVA3j1000interferencedownmu mvaReader3j1000interferencedownmu( inputVarsMVA );
   ReadMVA3j1000interferencenominalmu mvaReader3j1000interferencenominalmu( inputVarsMVA );
   ReadMVA3j1000interferenceupmu mvaReader3j1000interferenceupmu( inputVarsMVA );

   const char* DB_inputVars[] = { "W_pt", "event_met_pfmet", "W_muon_charge", "JetPFCor_QGLikelihood[0]", "JetPFCor_QGLikelihood[1]", "ang_hs", "ang_phib", "abs(JetPFCor_Eta[0]-JetPFCor_Eta[1])", "masslvjj" };
   std::vector<std::string> DB_inputVarsMVA;
   for (int i=0; i<9; ++i)  DB_inputVarsMVA.push_back( DB_inputVars[i] );
   ReadMVA2jdibosonmu mvaReader2jdibosonmu( DB_inputVarsMVA ); 
   ReadMVA3jdibosonmu mvaReader3jdibosonmu( DB_inputVarsMVA ); 

   const char* DBnoqg_inputVars[] = { "W_pt", "event_met_pfmet", "W_muon_charge", "ang_hs", "ang_phib", "abs(JetPFCor_Eta[0]-JetPFCor_Eta[1])", "masslvjj" };
   std::vector<std::string> DBnoqg_inputVarsMVA;
   for (int i=0; i<7; ++i)  DBnoqg_inputVarsMVA.push_back( DBnoqg_inputVars[i] );
   ReadMVA2jdibnoqgmu mvaReader2jdibnoqgmu( DBnoqg_inputVarsMVA ); 
   ReadMVA3jdibnoqgmu mvaReader3jdibnoqgmu( DBnoqg_inputVarsMVA ); 

   //const char* vbf_inputVars[] = { "vbf_lvjj_pt", "vbf_lvjj_y", "W_muon_charge", "vbf_wjj_ang_ha", "vbf_wjj_ang_hb", "vbf_wjj_ang_hs", "vbf_wjj_ang_phi", "vbf_wjj_ang_phib", "vbf_jj_deta", "vbf_jj_m" };
   const char* vbf_inputVars[] = { "vbf_lvjj_pt", "vbf_lvjj_y", "W_muon_charge", "vbf_wjj_ang_ha", "vbf_wjj_ang_hb", "vbf_wjj_ang_hs", "vbf_wjj_ang_phi", "vbf_wjj_ang_phib"};
   std::vector<std::string> vbf_inputVarsMVA;
   //for (int i=0; i<10; ++i) vbf_inputVarsMVA.push_back( vbf_inputVars[i] );
   for (int i=0; i<8; ++i) vbf_inputVarsMVA.push_back( vbf_inputVars[i] );
   ReadMVAVBF170mu mvaReadervbf170mu( vbf_inputVarsMVA );
   cout << "error 1" << endl;
   ReadMVAVBF180mu mvaReadervbf180mu( vbf_inputVarsMVA );
   ReadMVAVBF190mu mvaReadervbf190mu( vbf_inputVarsMVA );
   ReadMVAVBF200mu mvaReadervbf200mu( vbf_inputVarsMVA );
   ReadMVAVBF250mu mvaReadervbf250mu( vbf_inputVarsMVA );
   ReadMVAVBF300mu mvaReadervbf300mu( vbf_inputVarsMVA );
   ReadMVAVBF350mu mvaReadervbf350mu( vbf_inputVarsMVA );
   ReadMVAVBF400mu mvaReadervbf400mu( vbf_inputVarsMVA );
   ReadMVAVBF450mu mvaReadervbf450mu( vbf_inputVarsMVA );
   ReadMVAVBF500mu mvaReadervbf500mu( vbf_inputVarsMVA );
   ReadMVAVBF550mu mvaReadervbf550mu( vbf_inputVarsMVA );
   ReadMVAVBF600mu mvaReadervbf600mu( vbf_inputVarsMVA );

   // For Efficiency Correction
   //EffTableLoader muIDEff(            fDir + "scaleFactor-2012A-PromptReco-v1-PFMM-RecoToIso.txt");
   //EffTableLoader muHLTEff(           fDir + "efficiency-2012A-PromptReco-v1-PFMM-IsoToIsoMuHLT.txt");

   //EffTableLoader muIDEff(            fDir + "scaleFactor-Run2012ABC-RecoToIso.txt");
   //EffTableLoader muHLTEff(           fDir + "efficiency-Run2012ABC-IsoToIsoMuHLT.txt");

   EffTableLoader muIDEff(            fDir + "scaleFactor-Run2012ABCD-RecoToIso.txt");
   EffTableLoader muHLTEff(           fDir + "efficiency-Run2012ABCD-IsoToIsoMuHLT.txt");

   //For Interference Correction
   LOTable interferencetableggH400;
   LOTable interferencetableggH450;
   LOTable interferencetableggH500;
   LOTable interferencetableggH550;
   LOTable interferencetableggH600;
   LOTable interferencetableggH700;
   LOTable interferencetableggH800;
   LOTable interferencetableggH900;
   LOTable interferencetableggH1000;

   interferencetableggH400.LoadTable(fInterferenceDir + "ratio400.txt");
   interferencetableggH450.LoadTable(fInterferenceDir + "ratio450.txt");
   interferencetableggH500.LoadTable(fInterferenceDir + "ratio500.txt");
   interferencetableggH550.LoadTable(fInterferenceDir + "ratio550.txt");
   interferencetableggH600.LoadTable(fInterferenceDir + "ratio600.txt");
   interferencetableggH700.LoadTable(fInterferenceDir + "ratio700.txt");
   interferencetableggH800.LoadTable(fInterferenceDir + "ratio800.txt");
   interferencetableggH900.LoadTable(fInterferenceDir + "ratio900.txt");
   interferencetableggH1000.LoadTable(fInterferenceDir + "ratio1000.txt");

   //Complex Pole Weight
   pwhegwrapper powhegggH180;
   pwhegwrapper powhegggH190;
   pwhegwrapper powhegggH200;
   pwhegwrapper powhegggH250;
   pwhegwrapper powhegggH300;
   pwhegwrapper powhegggH350;
   pwhegwrapper powhegggH400;
   pwhegwrapper powhegggH450;
   pwhegwrapper powhegggH500;
   pwhegwrapper powhegggH550;
   pwhegwrapper powhegggH600;
   pwhegwrapper powhegggH700;
   pwhegwrapper powhegggH800;
   pwhegwrapper powhegggH900;
   pwhegwrapper powhegggH1000;

   // Pile up Re-weighting
   /*
      edm::Lumi3DReWeighting LumiWeights_ = edm::Lumi3DReWeighting("PUMC_dist.root", "PUData_dist.root", "pileup", "pileup", "Weight_3D.root");
      LumiWeights_.weight3D_init( 1.08 );

      edm::Lumi3DReWeighting up_LumiWeights_ = edm::Lumi3DReWeighting("PUMC_dist.root", "PUData_dist.root", "pileup", "pileup", "Weight_3D_up.root");
      up_LumiWeights_.weight3D_init( 1.16 );

      edm::Lumi3DReWeighting dn_LumiWeights_ = edm::Lumi3DReWeighting("PUMC_dist.root", "PUData_dist.root", "pileup", "pileup", "Weight_3D_down.root");
      dn_LumiWeights_.weight3D_init( 1.00 );
    */  
   // S7 MC PU True profile - hardcoded, wow
   // https://twiki.cern.ch/twiki/bin/viewauth/CMS/PileupMCReweightingUtilities
   // TFile *dataFile_      = new TFile( "PileupHistogramGold_190456-196531_8TeV_PromptReco_Collisions12_true.root" );
   //TFile *dataFile_      = new TFile( "Data190389-200041_PileupHistogram.root" );
   TFile *dataFile_      = new TFile( "Data190456-208686_PileupHistogram.root" );
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
         //Pile Up for S7
         /*2.344E-05,
           2.344E-05,
           2.344E-05,
           2.344E-05,
           4.687E-04,
           4.687E-04,
           7.032E-04,
           9.414E-04,
           1.234E-03,
           1.603E-03,
           2.464E-03,
           3.250E-03,
           5.021E-03,
           6.644E-03,
           8.502E-03,
           1.121E-02,
           1.518E-02,
           2.033E-02,
           2.608E-02,
           3.171E-02,
           3.667E-02,
           4.060E-02,
           4.338E-02,
           4.520E-02,
           4.641E-02,
           4.735E-02,
           4.816E-02,
           4.881E-02,
           4.917E-02,
           4.909E-02,
           4.842E-02,
           4.707E-02,
           4.501E-02,
           4.228E-02,
           3.896E-02,
           3.521E-02,
           3.118E-02,
           2.702E-02,
           2.287E-02,
           1.885E-02,
           1.508E-02,
           1.166E-02,
           8.673E-03,
           6.190E-03,
           4.222E-03,
           2.746E-03,
           1.698E-03,
           9.971E-04,
           5.549E-04,
           2.924E-04,
           1.457E-04,
           6.864E-05,
           3.054E-05,
           1.282E-05,
           5.081E-06,
           1.898E-06,
           6.688E-07,
           2.221E-07,
           6.947E-08,
           2.047E-08
          */
   };   
   for (int i=1;i<=60;i++)  {
      PU_generated->SetBinContent(i,Summer2012[i-1]);
   }
   PU_intended->Scale( 1.0/ PU_intended->Integral() );
   PU_generated->Scale( 1.0/ PU_generated->Integral() );

   TH1F *weights_ = new TH1F( *(PU_intended)) ;

   weights_->Divide(PU_generated);


   //Re-calculate Q/G Likelihood
   //QGLikelihoodCalculator *qglikeli_Spring11    = new QGLikelihoodCalculator("./QG_QCD_Pt_15to3000_TuneZ2_Flat_7TeV_pythia6_Spring11-PU_S1_START311_V1G1-v1.root");  
   //QGLikelihoodCalculator *qglikeli_Summer11    = new QGLikelihoodCalculator("./QG_QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6_Summer11-PU_S3_START42_V11-v2.root");  
   //QGLikelihoodCalculator *qglikeli_Summer11CHS = new QGLikelihoodCalculator("./QG_QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6_Summer11-PU_S3_START42_V11-v2_CHS.root");  

   // Parameter Setup
   const unsigned int jetsize         = 6;
   const double Jpt                   = 30;    // Jet pt threshold
   const double boostedWJpt           = 80;   // Conservative boosted Jet cut
   const double boostedWtranpt        = 150;
   const double btssv                 = 1.74;  // BTagging SSVHE Medium
   const double btcsvm                = 0.679; //CSVM
   const double btcsvl                = 0.244; //CSVL
   //const double VBF_MaxEta            = 4.5;   // VBF jet max eta
   const double VBF_MaxEta            = 4.7;   // Loose VBF jet max eta to 4.7
   const double mtop                  = 172.5; //Top mass
   // Loop over all events
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      //Long64_t ientry = LoadTree(jentry);
      //if (ientry < 0) break;
      if(jentry%100000==0){cout<< "jentry: " << jentry << endl;}
      nb = newtree->GetEntry(jentry);   nbytes += nb;
      // Cut variable definitions
      double jess    = 1.00; // control the jet energy scale
      //    double muoniso = (W_muon_pfiso_sumChargedHadronPt+W_muon_pfiso_sumNeutralHadronEt+W_muon_pfiso_sumPhotonEt-event_RhoForLeptonIsolation*3.141592653589*0.09)/W_muon_pt;
      //double muoniso = (W_muon_pfiso_sumChargedHadronPt+max(0.,W_muon_pfiso_sumNeutralHadronEt+W_muon_pfiso_sumPhotonEt-0.5*W_muon_pfiso_sumPUPt))/W_muon_pt;
      double dijetpt = sqrt(JetPFCor_Pt[0]*JetPFCor_Pt[0]+
            JetPFCor_Pt[1]*JetPFCor_Pt[1]+
            2*JetPFCor_Pt[0]*JetPFCor_Pt[1]*cos(JetPFCor_Phi[0]-JetPFCor_Phi[1]));

      // Save variable initialization
      ggdevt    = 0;
      evtNJ     = 0;
      ggdevtinclusive    = 0;

      fit_mu_px = 0; fit_mu_py = 0; fit_mu_pz = 0;  fit_mu_e  = 0; 
      fit_nv_px = 0; fit_nv_py = 0; fit_nv_pz = 0;  fit_nv_e  = 0; 
      fit_aj_px = 0; fit_aj_py = 0; fit_aj_pz = 0;  fit_aj_e  = 0; 
      fit_bj_px = 0; fit_bj_py = 0; fit_bj_pz = 0;  fit_bj_e  = 0; 
      fit_mlvjj = 0; fit_chi2  =999;fit_NDF   =999; fit_status=999;
      fit_mlv   = 0; fit_mjj   = 0;

      TopWm     = 0; TopWm5j   = 0; Tchi2     =999; Tchi25j   =999;

      ang_ha  = 999; ang_hb    =999;ang_hs    =999; ang_phi   =999; 
      ang_phia= 999; ang_phib  =999;
      masslvjj=-999; ptlvjj    =-999; ylvjj   =-999;philvjj   =-999;

      mva2j160mu = 999; mva2j170mu = 999; mva2j180mu = 999; mva2j190mu = 999; mva2j200mu = 999; mva2j250mu = 999; mva2j300mu = 999; mva2j350mu = 999; mva2j400mu = 999; mva2j450mu = 999; mva2j500mu = 999; mva2j550mu = 999; mva2j600mu = 999;
      mva2j400interferencenominalmu = 999; mva2j450interferencenominalmu = 999; mva2j500interferencenominalmu = 999; mva2j550interferencenominalmu = 999; mva2j600interferencenominalmu = 999; mva2j700interferencenominalmu = 999; mva2j800interferencenominalmu = 999; mva2j900interferencenominalmu = 999; mva2j1000interferencenominalmu = 999;
      mva2j400interferencedownmu = 999; mva2j450interferencedownmu = 999; mva2j500interferencedownmu = 999; mva2j550interferencedownmu = 999; mva2j600interferencedownmu = 999; mva2j700interferencedownmu = 999; mva2j800interferencedownmu = 999; mva2j900interferencedownmu = 999; mva2j1000interferencedownmu = 999;
      mva2j400interferenceupmu = 999; mva2j450interferenceupmu = 999; mva2j500interferenceupmu = 999; mva2j550interferenceupmu = 999; mva2j600interferenceupmu = 999; mva2j700interferenceupmu = 999; mva2j800interferenceupmu = 999; mva2j900interferenceupmu = 999; mva2j1000interferenceupmu = 999;
      mva3j160mu = 999; mva3j170mu = 999; mva3j180mu = 999; mva3j190mu = 999; mva3j200mu = 999; mva3j250mu = 999; mva3j300mu = 999; mva3j350mu = 999; mva3j400mu = 999; mva3j450mu = 999; mva3j500mu = 999; mva3j550mu = 999; mva3j600mu = 999;
      mva3j400interferencenominalmu = 999; mva3j450interferencenominalmu = 999; mva3j500interferencenominalmu = 999; mva3j550interferencenominalmu = 999; mva3j600interferencenominalmu = 999; mva3j700interferencenominalmu = 999; mva3j800interferencenominalmu = 999; mva3j900interferencenominalmu = 999; mva3j1000interferencenominalmu = 999;
      mva3j400interferencedownmu = 999; mva3j450interferencedownmu = 999; mva3j500interferencedownmu = 999; mva3j550interferencedownmu = 999; mva3j600interferencedownmu = 999; mva3j700interferencedownmu = 999; mva3j800interferencedownmu = 999; mva3j900interferencedownmu = 999; mva3j1000interferencedownmu = 999;
      mva3j400interferenceupmu = 999; mva3j450interferenceupmu = 999; mva3j500interferenceupmu = 999; mva3j550interferenceupmu = 999; mva3j600interferenceupmu = 999; mva3j700interferenceupmu = 999; mva3j800interferenceupmu = 999; mva3j900interferenceupmu = 999; mva3j1000interferenceupmu = 999;
      mva2jdibosonmu = 999; mva3jdibosonmu = 999; mva2jdibnoqgmu = 999; mva3jdibnoqgmu = 999;
      mvavbf160mu = 999; mvavbf170mu = 999; mvavbf180mu = 999; mvavbf190mu = 999; mvavbf200mu = 999; mvavbf250mu = 999; mvavbf300mu = 999; mvavbf350mu = 999; mvavbf400mu = 999; mvavbf450mu = 999; mvavbf500mu = 999; mvavbf550mu = 999; mvavbf600mu = 999;


      effwt = 1.0; puwt = 1.0; puwt_up = 1.0; puwt_down = 1.0;
      qgld_Spring11[0]= -1;       qgld_Spring11[1]= -1;       qgld_Spring11[2]= -1;       qgld_Spring11[3]= -1;       qgld_Spring11[4]= -1;       qgld_Spring11[5]= -1;
      qgld_Summer11[0]= -1;       qgld_Summer11[1]= -1;       qgld_Summer11[2]= -1;       qgld_Summer11[3]= -1;       qgld_Summer11[4]= -1;       qgld_Summer11[5]= -1;
      qgld_Summer11CHS[0]= -1;    qgld_Summer11CHS[1]= -1;    qgld_Summer11CHS[2]= -1;    qgld_Summer11CHS[3]= -1;    qgld_Summer11CHS[4]= -1;    qgld_Summer11CHS[5]= -1;

      //Interference Weight
      interferencewtggH400 = 1.0; interferencewtggH450 = 1.0; interferencewtggH500 = 1.0; interferencewtggH550 = 1.0; interferencewtggH600 = 1.0; interferencewtggH700 = 1.0; interferencewtggH800 = 1.0; interferencewtggH900 = 1.0; interferencewtggH1000 = 1.0;
      interferencewt_upggH400 = 1.0; interferencewt_upggH450 = 1.0; interferencewt_upggH500 = 1.0; interferencewt_upggH550 = 1.0; interferencewt_upggH600 = 1.0; interferencewt_upggH700 = 1.0; interferencewt_upggH800 = 1.0; interferencewt_upggH900 = 1.0; interferencewt_upggH1000 = 1.0;
      interferencewt_downggH400 = 1.0; interferencewt_downggH450 = 1.0; interferencewt_downggH500 = 1.0; interferencewt_downggH550 = 1.0; interferencewt_downggH600 = 1.0; interferencewt_downggH700 = 1.0; interferencewt_downggH800 = 1.0; interferencewt_downggH900 = 1.0; interferencewt_downggH1000 = 1.0;

      //Complex Pole Weight
      complexpolewtggH180 = 1.0; complexpolewtggH190 = 1.0; complexpolewtggH200 = 1.0; complexpolewtggH250 = 1.0; complexpolewtggH300 = 1.0; complexpolewtggH350 = 1.0; complexpolewtggH400 = 1.0; complexpolewtggH450 = 1.0; complexpolewtggH500 = 1.0; complexpolewtggH550 = 1.0; complexpolewtggH600 = 1.0; complexpolewtggH700 = 1.0; complexpolewtggH800 = 1.0; complexpolewtggH900 = 1.0; complexpolewtggH1000 = 1.0;

      //Average Complex Pole Weight for normalization
      avecomplexpolewtggH180 = 1.0; avecomplexpolewtggH190 = 1.0; avecomplexpolewtggH200 = 1.0; avecomplexpolewtggH250 = 1.0; avecomplexpolewtggH300 = 1.0; avecomplexpolewtggH350 = 1.0; avecomplexpolewtggH400 = 1.0; avecomplexpolewtggH450 = 1.0; avecomplexpolewtggH500 = 1.0; avecomplexpolewtggH550 = 1.0; avecomplexpolewtggH600 = 1.0; avecomplexpolewtggH700 = 1.0; avecomplexpolewtggH800 = 1.0; avecomplexpolewtggH900 = 1.0; avecomplexpolewtggH1000 = 1.0;

      //CA8
      isgengdboostedWevt = 0; ggdboostedWevt = 0; GroomedJet_numberbjets_csvm = 0; GroomedJet_numberbjets_csvl = 0; GroomedJet_numberbjets_ssvhem = 0; GroomedJet_numberbjets_csvl_veto = 0; GroomedJet_numberbjets_csvm_veto = 0; GroomedJet_numberbjets_ssvhem_veto = 0; GroomedJet_numberjets = 0;

      GroomedJet_CA8_deltaR_lca8jet = -999; GroomedJet_CA8_deltaphi_METca8jet = -999; GroomedJet_CA8_deltaphi_Vca8jet = -999;

      GroomedJet_CA8_rcores01 = -1; GroomedJet_CA8_rcores02 = -1; GroomedJet_CA8_rcores03 = -1; GroomedJet_CA8_rcores04 = -1;
      GroomedJet_CA8_rcores05 = -1; GroomedJet_CA8_rcores06 = -1; GroomedJet_CA8_rcores07 = -1; GroomedJet_CA8_rcores08 = -1;
      GroomedJet_CA8_rcores09 = -1; GroomedJet_CA8_rcores10 = -1; GroomedJet_CA8_rcores11 = -1;

      GroomedJet_CA8_ptcores01 = -1; GroomedJet_CA8_ptcores02 = -1; GroomedJet_CA8_ptcores03 = -1; GroomedJet_CA8_ptcores04 = -1;
      GroomedJet_CA8_ptcores05 = -1; GroomedJet_CA8_ptcores06 = -1; GroomedJet_CA8_ptcores07 = -1; GroomedJet_CA8_ptcores08 = -1;
      GroomedJet_CA8_ptcores09 = -1; GroomedJet_CA8_ptcores10 = -1; GroomedJet_CA8_ptcores11 = -1;

      GroomedJet_CA8_planarflow01 = -1; GroomedJet_CA8_planarflow02 = -1; GroomedJet_CA8_planarflow03 = -1; GroomedJet_CA8_planarflow04 = -1;
      GroomedJet_CA8_planarflow05 = -1; GroomedJet_CA8_planarflow06 = -1; GroomedJet_CA8_planarflow07 = -1; GroomedJet_CA8_planarflow08 = -1;
      GroomedJet_CA8_planarflow09 = -1; GroomedJet_CA8_planarflow10 = -1; GroomedJet_CA8_planarflow11 = -1;

      GroomedJet_CA8_mass_sensi_tr = -1; GroomedJet_CA8_mass_sensi_ft = -1; GroomedJet_CA8_mass_sensi_pr = -1;

      GroomedJet_CA8_qjetmassvolatility = -1;

      GroomedJet_CA8_prsubjet1ptoverjetpt = -1; GroomedJet_CA8_prsubjet2ptoverjetpt = -1;
      GroomedJet_CA8_prsubjet1subjet2_deltaR = -1;

      boostedW_lvj_e=-999;   boostedW_lvj_pt=-999;   boostedW_lvj_eta=-999;   boostedW_lvj_phi=-999;   boostedW_lvj_m=-999;   boostedW_lvj_y=-999;

      boostedW_wjj_ang_ha = 999; boostedW_wjj_ang_hb = 999; boostedW_wjj_ang_hs = 999; boostedW_wjj_ang_phi = 999; boostedW_wjj_ang_phia = 999; boostedW_wjj_ang_phib = 999;

      //AK7
      ggdboostedWevt_ak7 = 0; GroomedJet_numberbjets_csvm_ak7 = 0; GroomedJet_numberbjets_csvl_ak7 = 0; GroomedJet_numberbjets_ssvhem_ak7 = 0; GroomedJet_numberbjets_csvl_veto_ak7 = 0; GroomedJet_numberbjets_csvm_veto_ak7 = 0; GroomedJet_numberbjets_ssvhem_veto_ak7 = 0; GroomedJet_numberjets_ak7 = 0;

      GroomedJet_AK7_deltaR_lak7jet = -999; GroomedJet_AK7_deltaphi_METak7jet = -999; GroomedJet_AK7_deltaphi_Vak7jet = -999;

      GroomedJet_AK7_rcores01 = -1; GroomedJet_AK7_rcores02 = -1; GroomedJet_AK7_rcores03 = -1; GroomedJet_AK7_rcores04 = -1;
      GroomedJet_AK7_rcores05 = -1; GroomedJet_AK7_rcores06 = -1; GroomedJet_AK7_rcores07 = -1; GroomedJet_AK7_rcores08 = -1;
      GroomedJet_AK7_rcores09 = -1; GroomedJet_AK7_rcores10 = -1; GroomedJet_AK7_rcores11 = -1;

      GroomedJet_AK7_ptcores01 = -1; GroomedJet_AK7_ptcores02 = -1; GroomedJet_AK7_ptcores03 = -1; GroomedJet_AK7_ptcores04 = -1;
      GroomedJet_AK7_ptcores05 = -1; GroomedJet_AK7_ptcores06 = -1; GroomedJet_AK7_ptcores07 = -1; GroomedJet_AK7_ptcores08 = -1;
      GroomedJet_AK7_ptcores09 = -1; GroomedJet_AK7_ptcores10 = -1; GroomedJet_AK7_ptcores11 = -1;

      GroomedJet_AK7_planarflow01 = -1; GroomedJet_AK7_planarflow02 = -1; GroomedJet_AK7_planarflow03 = -1; GroomedJet_AK7_planarflow04 = -1;
      GroomedJet_AK7_planarflow05 = -1; GroomedJet_AK7_planarflow06 = -1; GroomedJet_AK7_planarflow07 = -1; GroomedJet_AK7_planarflow08 = -1;
      GroomedJet_AK7_planarflow09 = -1; GroomedJet_AK7_planarflow10 = -1; GroomedJet_AK7_planarflow11 = -1;

      GroomedJet_AK7_mass_sensi_tr = -1; GroomedJet_AK7_mass_sensi_ft = -1; GroomedJet_AK7_mass_sensi_pr = -1;

      GroomedJet_AK7_qjetmassvolatility = -1;

      GroomedJet_AK7_prsubjet1ptoverjetpt = -1; GroomedJet_AK7_prsubjet2ptoverjetpt = -1;
      GroomedJet_AK7_prsubjet1subjet2_deltaR = -1;

      boostedW_lvj_e_ak7=-999;   boostedW_lvj_pt_ak7=-999;   boostedW_lvj_eta_ak7=-999;   boostedW_lvj_phi_ak7=-999;   boostedW_lvj_m_ak7=-999;   boostedW_lvj_y_ak7=-999;

      boostedW_wjj_ang_ha_ak7 = 999; boostedW_wjj_ang_hb_ak7 = 999; boostedW_wjj_ang_hs_ak7 = 999; boostedW_wjj_ang_phi_ak7 = 999; boostedW_wjj_ang_phia_ak7 = 999; boostedW_wjj_ang_phib_ak7 = 999;

      vbf_jj_e =-999;   vbf_jj_pt =-999;   vbf_jj_eta=-999;  vbf_jj_phi =-999; vbf_jj_m =-999;   
      vbf_aj_e =-999;   vbf_aj_pt =-999;   vbf_aj_eta=-999;  vbf_aj_phi =-999; vbf_aj_m =-999;   
      vbf_bj_e =-999;   vbf_bj_pt =-999;   vbf_bj_eta=-999;  vbf_bj_phi =-999; vbf_bj_m =-999;   
      vbf_jj_deta=-999; vbf_jj_dphi=-999;  vbf_jj_type=0;    vbf_n_excj=0;     vbf_n_exfj=0;     vbf_n_gdjj=0;

      vbf_aj_bj_Wjj_jetnumber = 0; vbf_waj_wbj_jetnumber = 0;
      vbf_lvwajbj_ajbj_dphi = -999; vbf_lvwajbj_ajbj_deta = -999;

      vbf_wjj_e =-999;   vbf_wjj_pt =-999;   vbf_wjj_eta =-999;   vbf_wjj_phi =-999;   vbf_wjj_m =-999;   
      vbf_waj_e =-999;   vbf_waj_pt =-999;   vbf_waj_eta =-999;   vbf_waj_phi =-999;   vbf_waj_m =-999;   
      vbf_wbj_e =-999;   vbf_wbj_pt =-999;   vbf_wbj_eta =-999;   vbf_wbj_phi =-999;   vbf_wbj_m =-999;   
      vbf_lvjj_e=-999;   vbf_lvjj_pt=-999;   vbf_lvjj_eta=-999;   vbf_lvjj_phi=-999;   vbf_lvjj_m=-999;   vbf_lvjj_y=-999;   

      vbf_event = 0; vbf_aj_id = -1; vbf_bj_id = -1; vbf_waj_id = -1; vbf_wbj_id = -1;
      vbf_wjj_ang_ha   = 999; vbf_wjj_ang_hb = 999; vbf_wjj_ang_hs = 999; vbf_wjj_ang_phi = 999; vbf_wjj_ang_phia = 999; vbf_wjj_ang_phib = 999;

      //VBF diboson event
      vbf_diboson_event = 0;
      vbf_diboson_deltaeta_Wjj = -999; vbf_diboson_deltaphi_MET_leadingWjet = -999; vbf_diboson_dijetpt = -999;

      //EWK  W+2jets
      EWK_W_2jets_event = 0;

      EWK_W_2jets_tagjet1_pt = -999; EWK_W_2jets_tagjet1_eta = -999; EWK_W_2jets_tagjet1_phi = -999; EWK_W_2jets_tagjet1_e = -999; EWK_W_2jets_tagjet1_m = -999;
      EWK_W_2jets_tagjet2_pt = -999; EWK_W_2jets_tagjet2_eta = -999; EWK_W_2jets_tagjet2_phi = -999; EWK_W_2jets_tagjet2_e = -999; EWK_W_2jets_tagjet2_m = -999;

      EWK_W_2jets_tagjet_etasign = -999;
      EWK_W_2jets_tagjet_deltaeta =  -999; EWK_W_2jets_tagjet_sumeta = -999;
      EWK_W_2jets_tagjet_deltaphi = -999; EWK_W_2jets_tagjet_deltaR = -999; EWK_W_2jets_tagjet_mass = -999;

      EWK_W_2jets_l_pt = -999; EWK_W_2jets_l_eta = -999; EWK_W_2jets_l_phi = -999; EWK_W_2jets_l_e = -999;
      EWK_W_2jets_l_MET_deltaphi = -999;

      EWK_W_2jets_l_tagjet1_deltaeta = -999; EWK_W_2jets_l_tagjet1_deltaphi = -999; EWK_W_2jets_l_tagjet1_deltaR = -999;
      EWK_W_2jets_l_tagjet2_deltaeta = -999; EWK_W_2jets_l_tagjet2_deltaphi = -999; EWK_W_2jets_l_tagjet2_deltaR = -999;

      EWK_W_2jets_W_pt = -999; EWK_W_2jets_W_eta = -999; EWK_W_2jets_W_rap = -999; EWK_W_2jets_W_phi = -999; EWK_W_2jets_W_e = -999; EWK_W_2jets_W_mT = -999;

      EWK_W_2jets_W_tagjet1_deltaphi = -999; EWK_W_2jets_W_tagjet1_deltaeta = -999; EWK_W_2jets_W_tagjet1_deltaR = -999;
      EWK_W_2jets_W_tagjet2_deltaphi = -999; EWK_W_2jets_W_tagjet2_deltaeta = -999; EWK_W_2jets_W_tagjet2_deltaR = -999;

      EWK_W_2jets_W_tagjet_Zeppenfield = -999;

      EWK_W_2jets_centraljetnum_20 = 0; EWK_W_2jets_centraljetnum_25 = 0; EWK_W_2jets_centraljetnum_30 = 0;

      EWK_W_2jets_findcentraljet = 0;

      EWK_W_2jets_centraljet_pt = -999; EWK_W_2jets_centraljet_eta = -999; EWK_W_2jets_centraljet_phi = -999; EWK_W_2jets_centraljet_e = -999; EWK_W_2jets_centraljet_m = -999;

      EWK_W_2jets_centraljet_tagjet1_deltaeta = -999; EWK_W_2jets_centraljet_tagjet1_deltaphi = -999; EWK_W_2jets_centraljet_tagjet1_deltaR = -999; 
      EWK_W_2jets_centraljet_tagjet2_deltaeta = -999; EWK_W_2jets_centraljet_tagjet2_deltaphi = -999; EWK_W_2jets_centraljet_tagjet2_deltaR = -999;

      EWK_W_2jets_centraljet_tagjet_Zeppenfield = -999; 

      EWK_W_2jets_tagjet1_QGd = -999;
      EWK_W_2jets_tagjet2_QGd = -999;

      EWK_W_2jets_tagjet1_btagCSV = -999;
      EWK_W_2jets_tagjet2_btagCSV = -999;

      EWK_W_2jets_genW_pt = -999; EWK_W_2jets_genW_eta = -999; EWK_W_2jets_genW_phi = -999; EWK_W_2jets_genW_e = -999;

      EWK_W_2jets_genTagquark1_pt = -999; EWK_W_2jets_genTagquark1_eta = -999; EWK_W_2jets_genTagquark1_phi = -999; EWK_W_2jets_genTagquark1_e = -999;
      EWK_W_2jets_genTagquark1_id = 0;

      EWK_W_2jets_genTagquark2_pt = -999; EWK_W_2jets_genTagquark2_eta = -999; EWK_W_2jets_genTagquark2_phi = -999; EWK_W_2jets_genTagquark2_e = -999;
      EWK_W_2jets_genTagquark2_id = 0;

      //WJets for Counting the Number of Partons
      W_gen_numPartons = 0;

      W_nParton_weight = 1.0;

      //End for EWK W+2jets Analysis

      //ttH initilization
      ttH_check_event = 0;
      ttH_event = 0; ttH_waj_id = -1; ttH_wbj_id = -1; ttH_toplvj_aj_id = -1; ttH_topjjj_aj_id = -1; ttH_dijetaj_id = -1; ttH_dijetbj_id = -1;
      ttH_fitstatus = -1; ttH_fitNDF = -1; ttH_fitchi2 = -999;

      ttH_wlv_e = -999; ttH_wlv_pt = -999; ttH_wlv_eta = -999; ttH_wlv_phi = -999; ttH_wlv_m = -999;
      ttH_waj_e = -999; ttH_waj_pt = -999; ttH_waj_eta = -999; ttH_waj_phi = -999; ttH_waj_m = -999;
      ttH_wbj_e = -999; ttH_wbj_pt = -999; ttH_wbj_eta = -999; ttH_wbj_phi = -999; ttH_wbj_m = -999;
      ttH_wjj_e = -999; ttH_wjj_pt = -999; ttH_wjj_eta = -999; ttH_wjj_phi = -999; ttH_wjj_m = -999;
      ttH_topjjj_aj_e = -999; ttH_topjjj_aj_pt = -999; ttH_topjjj_aj_eta = -999; ttH_topjjj_aj_phi = -999; ttH_topjjj_aj_m = -999; ttH_topjjj_aj_btagcsv = -999;
      ttH_toplvj_aj_e = -999; ttH_toplvj_aj_pt = -999; ttH_toplvj_aj_eta = -999; ttH_toplvj_aj_phi = -999; ttH_toplvj_aj_m = -999; ttH_toplvj_aj_btagcsv = -999;
      ttH_topjjj_e = -999; ttH_topjjj_pt = -999; ttH_topjjj_eta = -999; ttH_topjjj_phi = -999; ttH_topjjj_m = -999;
      ttH_toplvj_e = -999; ttH_toplvj_pt = -999; ttH_toplvj_eta = -999; ttH_toplvj_phi = -999; ttH_toplvj_m = -999;
      ttH_dijetaj_e = -999; ttH_dijetaj_pt = -999; ttH_dijetaj_eta = -999; ttH_dijetaj_phi = -999; ttH_dijetaj_m = -999; ttH_dijetaj_btagcsv = -999;
      ttH_dijetbj_e = -999; ttH_dijetbj_pt = -999; ttH_dijetbj_eta = -999; ttH_dijetbj_phi = -999; ttH_dijetbj_m = -999; ttH_dijetbj_btagcsv = -999;
      ttH_dijetajbj_deltaR = -999; ttH_dijetajbj_deltaphi = -999;
      ttH_dijet_e = -999; ttH_dijet_pt = -999; ttH_dijet_eta = -999; ttH_dijet_phi = -999; ttH_dijet_m = -999; ttH_dijet_y = -999;
      ttH_ditop_e = -999; ttH_ditop_pt = -999; ttH_ditop_eta = -999; ttH_ditop_phi = -999; ttH_ditop_m = -999; ttH_ditop_y = -999;
      ttH_toplvjdijetaj_deltaR = -999; ttH_toplvjdijetaj_deltaphi = -999;
      ttH_topjjjdijetaj_deltaR = -999; ttH_topjjjdijetaj_deltaphi = -999;
      ttH_toplvjdijetbj_deltaR = -999; ttH_toplvjdijetbj_deltaphi = -999;
      ttH_topjjjdijetbj_deltaR = -999; ttH_topjjjdijetbj_deltaphi = -999;
      ttH_toplvjdijet_deltaR = -999; ttH_toplvjdijet_deltaphi = -999;
      ttH_topjjjdijet_deltaR = -999; ttH_topjjjdijet_deltaphi = -999;
      ttH_ditopdijet_deltaR  = -999; ttH_ditopdijet_deltaphi = -999;
      //End ttH 

      // Calculate efficiency
      effwt = 
         muIDEff.GetEfficiency(W_muon_pt, W_muon_eta) * 
         muHLTEff.GetEfficiency(W_muon_pt, W_muon_eta);

      // Pile up Re-weighting
      if (wda>20120999) {
         //      puwt      =    LumiWeights_.weight3D(event_mcPU_nvtx[0], event_mcPU_nvtx[1], event_mcPU_nvtx[2]);   
         puwt      =    weights_->GetBinContent(int(event_mcPU_trueInteractions+0.01)+1);   
         //      puwt_up   = up_LumiWeights_.weight3D(event_mcPU_nvtx[0], event_mcPU_nvtx[1], event_mcPU_nvtx[2]);   
         puwt_up   = puwt;
         //      puwt_down = dn_LumiWeights_.weight3D(event_mcPU_nvtx[0], event_mcPU_nvtx[1], event_mcPU_nvtx[2]);   
         puwt_down = puwt;   
      } else {effwt=1.0;puwt=1.0;puwt_up=1.0;puwt_down=1.0;} // if data, always put 1 as the weighting factor


      // Jet Loop
      //for(unsigned int iJet=0; iJet<jetsize;iJet++){
      //if (JetPFCor_Pt[iJet]<0) continue;
      //      qgld_Spring11[iJet]= qglikeli_Spring11->computeQGLikelihoodPU( JetPFCor_Pt[iJet], event_RhoForLeptonIsolation, 
      //								     JetPFCor_ChargedMultiplicity[iJet], 
      //								     JetPFCor_NeutralMultiplicity[iJet], 
      //								     JetPFCor_PtD[iJet]);	 
      //      qgld_Summer11[iJet]= qglikeli_Summer11->computeQGLikelihoodPU( JetPFCor_Pt[iJet], event_RhoForLeptonIsolation, 
      //								     JetPFCor_ChargedMultiplicity[iJet], 
      //								     JetPFCor_NeutralMultiplicity[iJet], 
      //								     JetPFCor_PtD[iJet]);	 
      //qgld_Summer11CHS[iJet]= qglikeli_Summer11CHS->computeQGLikelihoodPU( JetPFCor_Pt[iJet], event_RhoForLeptonIsolationCHS, 
      //      JetPFCor_ChargedMultiplicity[iJet], 
      //      JetPFCor_NeutralMultiplicity[iJet], 
      //      JetPFCor_PtD[iJet]);	 
      //}

      if (wda>20120999) {

         if(W_H_mass_gen > 0) //Real generated Mass Just for the ggH Signal Sample
         {
            //Interference Correction Weight
            //Table: 1 R2 Nominal Value; 0 R2 Up Value; 2 R2 Down Value
            //Real Interference factor = 1 + R2
            interferencewtggH400 = (1 + interferencetableggH400.GetValue(W_H_mass_gen)[1]);
            interferencewt_upggH400 = ( 1 + interferencetableggH400.GetValue(W_H_mass_gen)[0]);
            interferencewt_downggH400 = ( 1 + interferencetableggH400.GetValue(W_H_mass_gen)[2]);

            interferencewtggH450 = (1 + interferencetableggH450.GetValue(W_H_mass_gen)[1]);
            interferencewt_upggH450 = ( 1 + interferencetableggH450.GetValue(W_H_mass_gen)[0]);
            interferencewt_downggH450 = ( 1 + interferencetableggH450.GetValue(W_H_mass_gen)[2]);

            interferencewtggH500 = (1 + interferencetableggH500.GetValue(W_H_mass_gen)[1]);
            interferencewt_upggH500 = ( 1 + interferencetableggH500.GetValue(W_H_mass_gen)[0]);
            interferencewt_downggH500 = ( 1 + interferencetableggH500.GetValue(W_H_mass_gen)[2]);

            interferencewtggH550 = (1 + interferencetableggH550.GetValue(W_H_mass_gen)[1]);
            interferencewt_upggH550 = ( 1 + interferencetableggH550.GetValue(W_H_mass_gen)[0]);
            interferencewt_downggH550 = ( 1 + interferencetableggH550.GetValue(W_H_mass_gen)[2]);

            interferencewtggH600 = (1 + interferencetableggH600.GetValue(W_H_mass_gen)[1]);
            interferencewt_upggH600 = ( 1 + interferencetableggH600.GetValue(W_H_mass_gen)[0]);
            interferencewt_downggH600 = ( 1 + interferencetableggH600.GetValue(W_H_mass_gen)[2]);

            interferencewtggH700 = (1 + interferencetableggH700.GetValue(W_H_mass_gen)[1]);
            interferencewt_upggH700 =  (1 + interferencetableggH700.GetValue(W_H_mass_gen)[0]);
            interferencewt_downggH700 = (1 + interferencetableggH700.GetValue(W_H_mass_gen)[2]);

            interferencewtggH800 = (1 + interferencetableggH800.GetValue(W_H_mass_gen)[1]);
            interferencewt_upggH800 = (1 + interferencetableggH800.GetValue(W_H_mass_gen)[0]);
            interferencewt_downggH800 = (1 + interferencetableggH800.GetValue(W_H_mass_gen)[2]);

            interferencewtggH900 = (1 + interferencetableggH900.GetValue(W_H_mass_gen)[1]);
            interferencewt_upggH900 = (1 + interferencetableggH900.GetValue(W_H_mass_gen)[0]);
            interferencewt_downggH900 = (1 + interferencetableggH900.GetValue(W_H_mass_gen)[2]);

            interferencewtggH1000 = (1 + interferencetableggH1000.GetValue(W_H_mass_gen)[1]);
            interferencewt_upggH1000 = ( 1 + interferencetableggH1000.GetValue(W_H_mass_gen)[0]);
            interferencewt_downggH1000 = ( 1 + interferencetableggH1000.GetValue(W_H_mass_gen)[2]);

            //Complex Pole Weight
            //getweight(double mh,double gh,double mt,double m,int BWflag)
            /*
               c     INPUT
               c     mh : Higgs boson mass (used in the POWHEG BOX generation)
               c     gh : Higgs boson width (used in the POWHEG BOX generation)
               c     mt : top quark mass
               c     BWflag : 0    if the sample to reweight was produced with fixed Higgs width
               c              1    if the sample to reweight was produced with running Higgs 
               c                   width (this is the default in the POWHEG BOX)
               c     m : virtuality of the produced Higgs boson resonance
               c     OUTPUT
               c     w : the reweighting factor 
             */
            TString tmps;
            stringstream out;
            out << wda;
            tmps = out.str();
            if (tmps.EndsWith("180")) {complexpolewtggH180 = powhegggH180.getweight(180.0,0.631,172.5,W_H_mass_gen,1);avecomplexpolewtggH180 = 1.00690568528;}
            if (tmps.EndsWith("190")) {complexpolewtggH190 = powhegggH190.getweight(190.0,1.04,172.5,W_H_mass_gen,1);avecomplexpolewtggH190 = 1.00436986424;}
            if (tmps.EndsWith("200")) {complexpolewtggH200 = powhegggH200.getweight(200.0,1.43,172.5,W_H_mass_gen,1);avecomplexpolewtggH200 = 1.0064984894;}
            if (tmps.EndsWith("250")) {complexpolewtggH250 = powhegggH250.getweight(250.0,4.04,172.5,W_H_mass_gen,1);avecomplexpolewtggH250 = 1.04781870103;}
            if (tmps.EndsWith("300")) {complexpolewtggH300 = powhegggH300.getweight(300.0,8.43,172.5,W_H_mass_gen,1);avecomplexpolewtggH300 = 1.03953336721;}
            if (tmps.EndsWith("350")) {complexpolewtggH350 = powhegggH350.getweight(350.0,15.2,172.5,W_H_mass_gen,1);avecomplexpolewtggH350 = 1.05195969977;}
            if (tmps.EndsWith("400")) {complexpolewtggH400 = powhegggH400.getweight(400.0,29.2,172.5,W_H_mass_gen,1);avecomplexpolewtggH400 = 1.09643113407;}
            if (tmps.EndsWith("450")) {complexpolewtggH450 = powhegggH450.getweight(450.0,46.8,172.5,W_H_mass_gen,1);avecomplexpolewtggH450 = 1.120898086;}
            if (tmps.EndsWith("500")) {complexpolewtggH500 = powhegggH500.getweight(500.0,68.0,172.5,W_H_mass_gen,1);avecomplexpolewtggH500 = 1.13138773778;}
            if (tmps.EndsWith("550")) {complexpolewtggH550 = powhegggH550.getweight(550.0,93.0,172.5,W_H_mass_gen,1);avecomplexpolewtggH550 = 1.13255668803;}
            if (tmps.EndsWith("600")) {complexpolewtggH600 = powhegggH600.getweight(600.0,123.0,172.5,W_H_mass_gen,1);avecomplexpolewtggH600 = 1.128128288;}
            if (tmps.EndsWith("700")) {complexpolewtggH700 = powhegggH700.getweight(700.0,199.0,172.5,W_H_mass_gen,1);avecomplexpolewtggH700 = 1.12667978349;}
            if (tmps.EndsWith("800")) {complexpolewtggH800 = powhegggH800.getweight(800.0,304.0,172.5,W_H_mass_gen,1);avecomplexpolewtggH800 = 1.1206847853;}
            if (tmps.EndsWith("900")) {complexpolewtggH900 = powhegggH900.getweight(900.0,449.0,172.5,W_H_mass_gen,1);avecomplexpolewtggH900 = 1.70985534003;}
            if (tmps.EndsWith("1000")) {complexpolewtggH1000 = powhegggH1000.getweight(1000.0,647.0,172.5,W_H_mass_gen,1);avecomplexpolewtggH1000 = 1.09438091014;}
         }
         else{
            interferencewtggH400=1.0; interferencewtggH450=1.0; interferencewtggH500=1.0; interferencewtggH550=1.0; interferencewtggH600=1.0;interferencewtggH700=1.0;interferencewtggH800=1.0;interferencewtggH900=1.0;interferencewtggH1000=1.0;
            interferencewt_upggH400=1.0; interferencewt_upggH450=1.0; interferencewt_upggH500=1.0; interferencewt_upggH550=1.0; interferencewt_upggH600=1.0;interferencewt_upggH700=1.0;interferencewt_upggH800=1.0;interferencewt_upggH900=1.0;interferencewt_upggH1000=1.0;
            interferencewt_downggH400=1.0; interferencewt_downggH450=1.0; interferencewt_downggH500=1.0; interferencewt_downggH550=1.0; interferencewt_downggH600=1.0;interferencewt_downggH700=1.0;interferencewt_downggH800=1.0;interferencewt_downggH900=1.0;interferencewt_downggH1000=1.0;
            complexpolewtggH180 = 1.0; complexpolewtggH190 = 1.0; complexpolewtggH200 = 1.0; complexpolewtggH250 = 1.0; complexpolewtggH300 = 1.0; complexpolewtggH350 = 1.0; complexpolewtggH400 = 1.0; complexpolewtggH450 = 1.0; complexpolewtggH500 = 1.0; complexpolewtggH550 = 1.0; complexpolewtggH600 = 1.0; complexpolewtggH700 = 1.0; complexpolewtggH800 = 1.0; complexpolewtggH900 = 1.0; complexpolewtggH1000 = 1.0;
            avecomplexpolewtggH180 = 1.0; avecomplexpolewtggH190 = 1.0; avecomplexpolewtggH200 = 1.0; avecomplexpolewtggH250 = 1.0; avecomplexpolewtggH300 = 1.0; avecomplexpolewtggH350 = 1.0; avecomplexpolewtggH400 = 1.0; avecomplexpolewtggH450 = 1.0; avecomplexpolewtggH500 = 1.0; avecomplexpolewtggH550 = 1.0; avecomplexpolewtggH600 = 1.0; avecomplexpolewtggH700 = 1.0; avecomplexpolewtggH800 = 1.0; avecomplexpolewtggH900 = 1.0; avecomplexpolewtggH1000 = 1.0;
         }
      }else{
         interferencewtggH400=1.0; interferencewtggH450=1.0;  interferencewtggH500=1.0; interferencewtggH550=1.0; interferencewtggH600=1.0;interferencewtggH700=1.0;interferencewtggH800=1.0;interferencewtggH900=1.0;interferencewtggH1000=1.0;
         interferencewt_upggH400=1.0; interferencewt_upggH450=1.0; interferencewt_upggH500=1.0; interferencewt_upggH550=1.0; interferencewt_upggH600=1.0;interferencewt_upggH700=1.0;interferencewt_upggH800=1.0;interferencewt_upggH900=1.0;interferencewt_upggH1000=1.0;
         interferencewt_downggH400=1.0; interferencewt_downggH450=1.0; interferencewt_downggH500=1.0; interferencewt_downggH550=1.0; interferencewt_downggH600=1.0;interferencewt_downggH700=1.0;interferencewt_downggH800=1.0;interferencewt_downggH900=1.0;interferencewt_downggH1000=1.0;
         complexpolewtggH180 = 1.0; complexpolewtggH190 = 1.0; complexpolewtggH200 = 1.0; complexpolewtggH250 = 1.0; complexpolewtggH300 = 1.0; complexpolewtggH350 = 1.0; complexpolewtggH400 = 1.0; complexpolewtggH450 = 1.0; complexpolewtggH500 = 1.0; complexpolewtggH550 = 1.0; complexpolewtggH600 = 1.0; complexpolewtggH700 = 1.0; complexpolewtggH800 = 1.0; complexpolewtggH900 = 1.0; complexpolewtggH1000 = 1.0;
         avecomplexpolewtggH180 = 1.0; avecomplexpolewtggH190 = 1.0; avecomplexpolewtggH200 = 1.0; avecomplexpolewtggH250 = 1.0; avecomplexpolewtggH300 = 1.0; avecomplexpolewtggH350 = 1.0; avecomplexpolewtggH400 = 1.0; avecomplexpolewtggH450 = 1.0; avecomplexpolewtggH500 = 1.0; avecomplexpolewtggH550 = 1.0; avecomplexpolewtggH600 = 1.0; avecomplexpolewtggH700 = 1.0; avecomplexpolewtggH800 = 1.0; avecomplexpolewtggH900 = 1.0; avecomplexpolewtggH1000 = 1.0;
      }

      // Good Event Selection Requirement for all events
      int istep = 8; //starting selection step after preselection
      bool  isgengdevt = 0;
      if (JetPFCor_Pt[0]>Jpt 
            && JetPFCor_Pt[1]>Jpt 
            && W_mt>30. //Move to MVA MET Later
            //&& W_mtMVA>30.
            && W_muon_pt>25.
            && fabs(W_muon_dz000)<0.02
            && fabs(W_muon_dzPV)<0.5
            && fabs(W_muon_eta)<2.1 //Fix the Muon Eta Range to 2.1
         ) {isgengdevt = 1;}

      bool isgendevtnojetevt = 0; 
      if ( W_mt>30. //Move to MVA MET Later
            //&& W_mtMVA>30.
            && W_muon_pt>25.
            && fabs(W_muon_dz000)<0.02
            && fabs(W_muon_dzPV)<0.5
            && fabs(W_muon_eta)<2.1 //Fix the Muon Eta Range to 2.1
         ) {isgendevtnojetevt = 1;}

      if (JetPFCor_Pt[0]>Jpt ) {
         h_events          -> Fill ( istep ); 
         h_events_weighted -> Fill ( istep, effwt*puwt ); 
         istep++;
         if ( JetPFCor_Pt[1]>Jpt ) {
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

      // Event Selection Requirement for Standard vs QCD events
      if ( !isQCD ) {
         //keep muons with iso<0.20(loose=0.20;tight=0.12) && event_met_pfmet>25.
         //if ( !(muoniso<0.12)         ) {isgengdevt=0;}
         if ( !(event_met_pfmet>25.0) ) {isgengdevt=0;}
         if ( !(event_met_pfmet>25.0) ) {isgendevtnojetevt=0;}
         // if ( !(event_metMVA_met >25.0) ) isgengdevt=0; //Move to MVA MET Later
      } else {
         //keep muons with iso>0.20 (loose=0.20;tight=0.12)
         //if ( !(muoniso>0.12)         ) {isgengdevt=0;}
      }


      // Fill lepton information
      TLorentzVector  mup, nvp;
      mup.SetPtEtaPhiE(W_muon_pt,              W_muon_eta,       W_muon_phi,       W_muon_e               );
      nvp.SetPxPyPzE(event_met_pfmet * cos(event_met_pfmetPhi), event_met_pfmet * sin(event_met_pfmetPhi), 
            //nvp.SetPxPyPzE(event_metMVA_met * cos(event_metMVA_metPhi), event_metMVA_met * sin(event_metMVA_metPhi), 
         W_pzNu1, sqrt(event_met_pfmet*event_met_pfmet + W_pzNu1*W_pzNu1)                     );
            // W_pzNu1, sqrt(event_metMVA_met * event_metMVA_met + W_pzNu1*W_pzNu1)                     );
      TLorentzVector b_metpt; b_metpt.SetPxPyPzE(event_met_pfmet * cos(event_met_pfmetPhi), event_met_pfmet * sin(event_met_pfmetPhi), 0, sqrt(event_met_pfmet*event_met_pfmet) );
      //TLorentzVector b_metpt; b_metpt.SetPxPyPzE(event_metMVA_met * cos(event_metMVA_metPhi),  event_metMVA_met * sin(event_metMVA_metPhi), 0, sqrt(event_metMVA_met * event_metMVA_met) );//Move to MVA MET Later
      METzCalculator b_metpz;
      b_metpz.SetMET(b_metpt);
      b_metpz.SetLepton(mup);
      b_metpz.SetLeptonType("muon");
      double b_nvpz = b_metpz.Calculate(); // Default one
      TLorentzVector b_nvp; b_nvp.SetPxPyPzE(b_metpt.Px(), b_metpt.Py(), b_nvpz, sqrt(b_metpt.Px()*b_metpt.Px() + b_metpt.Py()*b_metpt.Py() + b_nvpz*b_nvpz) );
      if (b_metpz.IsComplex()) {// if this is a complix, change MET
         double nu_pt1 = b_metpz.getPtneutrino(1);
         double nu_pt2 = b_metpz.getPtneutrino(2);
         TLorentzVector tmpp1; 
         tmpp1.SetPxPyPzE(nu_pt1 * cos(event_met_pfmetPhi), nu_pt1 * sin(event_met_pfmetPhi), b_nvpz, sqrt(nu_pt1*nu_pt1 + b_nvpz*b_nvpz) );
         //tmpp1.SetPxPyPzE(nu_pt1 * cos(event_metMVA_metPhi), nu_pt1 * sin(event_metMVA_metPhi), b_nvpz, sqrt(nu_pt1*nu_pt1 + b_nvpz*b_nvpz));//Move to MVA MET Later
         TLorentzVector tmpp2; 
         tmpp2.SetPxPyPzE(nu_pt2 * cos(event_met_pfmetPhi), nu_pt2 * sin(event_met_pfmetPhi), b_nvpz, sqrt(nu_pt2*nu_pt2 + b_nvpz*b_nvpz) );
         //tmpp2.SetPxPyPzE(nu_pt2 * cos(event_metMVA_metPhi), nu_pt2 * sin(event_metMVA_metPhi), b_nvpz, sqrt(nu_pt2*nu_pt2 + b_nvpz*b_nvpz) ); //Move to MVA MET Later
         b_nvp = tmpp1;	if ( fabs((mup+tmpp1).M()-80.4) > fabs((mup+tmpp2).M()-80.4) ) 	b_nvp = tmpp2;
      }

      //###########Begin Boosted W analysis Flag ###################################
      //Event Flag  Passed The Boosted W analysis Leptonic W Pt > 150GeV
      TLorentzVector lepwtransversep = mup + b_metpt;
      float lepwtransversept = lepwtransversep.Pt();

      //isgengdboostedWevt = 0; //Initialized Already

      if(   GroomedJet_CA8_pt[0] > boostedWJpt 
            && W_mt>30. //Move to MVA MET Later
            // && W_mtMVA>30.
            && W_muon_pt>25.
            && fabs(W_muon_dz000)<0.02
            && fabs(W_muon_dzPV)<0.5
            && fabs(W_muon_eta)<2.1
            && lepwtransversept > boostedWtranpt 
        ) {isgengdboostedWevt = 1;}

      // Event Selection Requirement for Standard vs QCD events
      if ( !isQCD ) {
         //keep muons with iso<0.20(loose=0.20;tight=0.12) && event_met_pfmet>25.
         //if ( !(muoniso<0.12)         ) {isgengdboostedWevt = 0;}
         if ( !(event_met_pfmet>25.0) ) {isgengdboostedWevt = 0;}
         //if ( !(event_metMVA_met >25.0) ) isgengdboostedWevt = 0; //Move to MVA MET Later
      } else {
         //keep muons with iso>0.20 (loose=0.20;tight=0.12)
         //if ( !(muoniso>0.12)         ) {isgengdboostedWevt = 0;}
      }
      //###########End Boosted W analysis Flag ###################################


      // 2 and 3 jet event for Mjj
      if (isgengdevt 
            && fabs(JetPFCor_Eta[0]-JetPFCor_Eta[1])<1.5 ) { 
         h_events          -> Fill ( istep );  
         h_events_weighted -> Fill ( istep, effwt*puwt );  
         istep++; 
         if ( fabs(JetPFCor_dphiMET[0])>0.4 ) { 
            h_events          -> Fill ( istep );  
            h_events_weighted -> Fill ( istep, effwt*puwt );  
            istep++; 
            if ( dijetpt>40.){ 
               h_events          -> Fill ( istep );  
               h_events_weighted -> Fill ( istep, effwt*puwt );  
               istep++; 
               if ( JetPFCor_Pt[1] > Jpt && JetPFCor_Pt[2] < Jpt ) {evtNJ = 2;} 
               if ( JetPFCor_Pt[2] > Jpt && JetPFCor_Pt[3] < Jpt ) {evtNJ = 3;} 
            } 
         } 
      } 
      // 2 and 3 jet event for Hww
      if (isgengdevt) { ggdevt = 4;// Do the kinematic fit for all event!!!
         if ( JetPFCor_Pt[1] > Jpt && JetPFCor_Pt[2] < Jpt ) {ggdevt = 2;}
         if ( JetPFCor_Pt[2] > Jpt && JetPFCor_Pt[3] < Jpt ) {ggdevt = 3;}
         //Add the inclusive Jet bin
         for(size_t i = 0; i < jetsize; i++)
         {
            if(JetPFCor_Pt[i] > Jpt)
            {
               ggdevtinclusive++;
            }
         }

         int Aj = 0, Bj = 1;    TLorentzVector ajp, bjp; 
         ajp.SetPtEtaPhiE(jess * JetPFCor_Pt[Aj], JetPFCor_Eta[Aj], JetPFCor_Phi[Aj], jess * JetPFCor_E[Aj]  );
         bjp.SetPtEtaPhiE(jess * JetPFCor_Pt[Bj], JetPFCor_Eta[Bj], JetPFCor_Phi[Bj], jess * JetPFCor_E[Bj]  );

         // Do kinematic fit
         TLorentzVector fit_mup(0,0,0,0), fit_nvp(0,0,0,0), fit_ajp(0,0,0,0), fit_bjp(0,0,0,0) ;
         doKinematicFit( 1, mup, b_nvp, ajp, bjp,  fit_mup, fit_nvp, fit_ajp, fit_bjp, fit_chi2, fit_NDF, fit_status);
         fit_mu_px = fit_mup.Px(); fit_mu_py = fit_mup.Py(); fit_mu_pz = fit_mup.Pz(); fit_mu_e = fit_mup.E(); 
         fit_nv_px = fit_nvp.Px(); fit_nv_py = fit_nvp.Py(); fit_nv_pz = fit_nvp.Pz(); fit_nv_e = fit_nvp.E(); 
         fit_aj_px = fit_ajp.Px(); fit_aj_py = fit_ajp.Py(); fit_aj_pz = fit_ajp.Pz(); fit_aj_e = fit_ajp.E(); 
         fit_bj_px = fit_bjp.Px(); fit_bj_py = fit_bjp.Py(); fit_bj_pz = fit_bjp.Pz(); fit_bj_e = fit_bjp.E(); 
         fit_mlvjj = (fit_mup+fit_nvp+fit_ajp+fit_bjp).M();
         fit_mlv   = (fit_mup+fit_nvp).M();
         fit_mjj   = (fit_ajp+fit_bjp).M(); 

         // Calculate angular distribution
         masslvjj = (mup+b_nvp+ajp+bjp).M();
         ptlvjj   = (mup+b_nvp+ajp+bjp).Pt();
         ylvjj    = (mup+b_nvp+ajp+bjp).Rapidity();
         philvjj  = (mup+b_nvp+ajp+bjp).Phi();
         double a_costheta1, a_costheta2, a_phi, a_costhetastar, a_phistar1, a_phistar2;
         if (W_muon_charge < 0){
            calculateAngles(mup, b_nvp, ajp, bjp, a_costheta1, a_costheta2, a_phi, a_costhetastar, a_phistar1, a_phistar2);
         }
         else{
            calculateAngles(b_nvp, mup, ajp, bjp, a_costheta1, a_costheta2, a_phi, a_costhetastar, a_phistar1, a_phistar2);
         }
         ang_ha = a_costheta1; ang_hb = fabs(a_costheta2); ang_hs = a_costhetastar;  ang_phi = a_phi; ang_phia = a_phistar1; ang_phib = a_phistar2;

         // Fill the trained MVA output 
         std::vector<double> mvaInputVal;
         mvaInputVal.push_back( ptlvjj );
         mvaInputVal.push_back( ylvjj );
         mvaInputVal.push_back( W_muon_charge );   ///////different for electron and muon
         //mvaInputVal.push_back( JetPFCor_QGLikelihood[0] );
         //mvaInputVal.push_back( JetPFCor_QGLikelihood[1] );
         mvaInputVal.push_back( ang_ha );
         mvaInputVal.push_back( ang_hb );
         mvaInputVal.push_back( ang_hs );
         mvaInputVal.push_back( ang_phi );
         mvaInputVal.push_back( ang_phib );

         mva2j170mu = (float) mvaReader2j170mu.GetMvaValue( mvaInputVal );
         mva2j180mu = (float) mvaReader2j180mu.GetMvaValue( mvaInputVal );
         mva2j190mu = (float) mvaReader2j190mu.GetMvaValue( mvaInputVal );
         mva2j200mu = (float) mvaReader2j200mu.GetMvaValue( mvaInputVal );
         mva2j250mu = (float) mvaReader2j250mu.GetMvaValue( mvaInputVal );
         mva2j300mu = (float) mvaReader2j300mu.GetMvaValue( mvaInputVal );
         mva2j350mu = (float) mvaReader2j350mu.GetMvaValue( mvaInputVal );
         mva2j400mu = (float) mvaReader2j400mu.GetMvaValue( mvaInputVal );
         mva2j450mu = (float) mvaReader2j450mu.GetMvaValue( mvaInputVal );
         mva2j500mu = (float) mvaReader2j500mu.GetMvaValue( mvaInputVal );
         mva2j550mu = (float) mvaReader2j550mu.GetMvaValue( mvaInputVal );
         mva2j600mu = (float) mvaReader2j600mu.GetMvaValue( mvaInputVal );
         mva2j400interferencenominalmu = (float) mvaReader2j400interferencenominalmu.GetMvaValue( mvaInputVal );
         mva2j450interferencenominalmu = (float) mvaReader2j450interferencenominalmu.GetMvaValue( mvaInputVal );
         mva2j500interferencenominalmu = (float) mvaReader2j500interferencenominalmu.GetMvaValue( mvaInputVal );
         mva2j550interferencenominalmu = (float) mvaReader2j550interferencenominalmu.GetMvaValue( mvaInputVal );
         mva2j600interferencenominalmu = (float) mvaReader2j600interferencenominalmu.GetMvaValue( mvaInputVal );
         mva2j700interferencenominalmu = (float) mvaReader2j700interferencenominalmu.GetMvaValue( mvaInputVal );
         mva2j800interferencenominalmu = (float) mvaReader2j800interferencenominalmu.GetMvaValue( mvaInputVal );
         mva2j900interferencenominalmu = (float) mvaReader2j900interferencenominalmu.GetMvaValue( mvaInputVal );
         mva2j1000interferencenominalmu = (float) mvaReader2j1000interferencenominalmu.GetMvaValue( mvaInputVal );
         mva2j400interferencedownmu = (float) mvaReader2j400interferencedownmu.GetMvaValue( mvaInputVal );
         mva2j450interferencedownmu = (float) mvaReader2j450interferencedownmu.GetMvaValue( mvaInputVal );
         mva2j500interferencedownmu = (float) mvaReader2j500interferencedownmu.GetMvaValue( mvaInputVal );
         mva2j550interferencedownmu = (float) mvaReader2j550interferencedownmu.GetMvaValue( mvaInputVal );
         mva2j600interferencedownmu = (float) mvaReader2j600interferencedownmu.GetMvaValue( mvaInputVal );
         mva2j700interferencedownmu = (float) mvaReader2j700interferencedownmu.GetMvaValue( mvaInputVal );
         mva2j800interferencedownmu = (float) mvaReader2j800interferencedownmu.GetMvaValue( mvaInputVal );
         mva2j900interferencedownmu = (float) mvaReader2j900interferencedownmu.GetMvaValue( mvaInputVal );
         mva2j1000interferencedownmu = (float) mvaReader2j1000interferencedownmu.GetMvaValue( mvaInputVal );
         mva2j400interferenceupmu = (float) mvaReader2j400interferenceupmu.GetMvaValue( mvaInputVal );
         mva2j450interferenceupmu = (float) mvaReader2j450interferenceupmu.GetMvaValue( mvaInputVal );
         mva2j500interferenceupmu = (float) mvaReader2j500interferenceupmu.GetMvaValue( mvaInputVal );
         mva2j550interferenceupmu = (float) mvaReader2j550interferenceupmu.GetMvaValue( mvaInputVal );
         mva2j600interferenceupmu = (float) mvaReader2j600interferenceupmu.GetMvaValue( mvaInputVal );
         mva2j700interferenceupmu = (float) mvaReader2j700interferenceupmu.GetMvaValue( mvaInputVal );
         mva2j800interferenceupmu = (float) mvaReader2j800interferenceupmu.GetMvaValue( mvaInputVal );
         mva2j900interferenceupmu = (float) mvaReader2j900interferenceupmu.GetMvaValue( mvaInputVal );
         mva2j1000interferenceupmu = (float) mvaReader2j1000interferenceupmu.GetMvaValue( mvaInputVal );

         mva3j170mu = (float) mvaReader3j170mu.GetMvaValue( mvaInputVal );
         mva3j180mu = (float) mvaReader3j180mu.GetMvaValue( mvaInputVal );
         mva3j190mu = (float) mvaReader3j190mu.GetMvaValue( mvaInputVal );
         mva3j200mu = (float) mvaReader3j200mu.GetMvaValue( mvaInputVal );
         mva3j250mu = (float) mvaReader3j250mu.GetMvaValue( mvaInputVal );
         mva3j300mu = (float) mvaReader3j300mu.GetMvaValue( mvaInputVal );
         mva3j350mu = (float) mvaReader3j350mu.GetMvaValue( mvaInputVal );
         mva3j400mu = (float) mvaReader3j400mu.GetMvaValue( mvaInputVal );
         mva3j450mu = (float) mvaReader3j450mu.GetMvaValue( mvaInputVal );
         mva3j500mu = (float) mvaReader3j500mu.GetMvaValue( mvaInputVal );
         mva3j550mu = (float) mvaReader3j550mu.GetMvaValue( mvaInputVal );
         mva3j600mu = (float) mvaReader3j600mu.GetMvaValue( mvaInputVal );
         mva3j400interferencenominalmu = (float) mvaReader3j400interferencenominalmu.GetMvaValue( mvaInputVal );
         mva3j450interferencenominalmu = (float) mvaReader3j450interferencenominalmu.GetMvaValue( mvaInputVal );
         mva3j500interferencenominalmu = (float) mvaReader3j500interferencenominalmu.GetMvaValue( mvaInputVal );
         mva3j550interferencenominalmu = (float) mvaReader3j550interferencenominalmu.GetMvaValue( mvaInputVal );
         mva3j600interferencenominalmu = (float) mvaReader3j600interferencenominalmu.GetMvaValue( mvaInputVal );
         mva3j700interferencenominalmu = (float) mvaReader3j700interferencenominalmu.GetMvaValue( mvaInputVal );
         mva3j800interferencenominalmu = (float) mvaReader3j800interferencenominalmu.GetMvaValue( mvaInputVal );
         mva3j900interferencenominalmu = (float) mvaReader3j900interferencenominalmu.GetMvaValue( mvaInputVal );
         mva3j1000interferencenominalmu = (float) mvaReader3j1000interferencenominalmu.GetMvaValue( mvaInputVal );
         mva3j400interferencedownmu = (float) mvaReader3j400interferencedownmu.GetMvaValue( mvaInputVal );
         mva3j450interferencedownmu = (float) mvaReader3j450interferencedownmu.GetMvaValue( mvaInputVal );
         mva3j500interferencedownmu = (float) mvaReader3j500interferencedownmu.GetMvaValue( mvaInputVal );
         mva3j550interferencedownmu = (float) mvaReader3j550interferencedownmu.GetMvaValue( mvaInputVal );
         mva3j600interferencedownmu = (float) mvaReader3j600interferencedownmu.GetMvaValue( mvaInputVal );
         mva3j700interferencedownmu = (float) mvaReader3j700interferencedownmu.GetMvaValue( mvaInputVal );
         mva3j800interferencedownmu = (float) mvaReader3j800interferencedownmu.GetMvaValue( mvaInputVal );
         mva3j900interferencedownmu = (float) mvaReader3j900interferencedownmu.GetMvaValue( mvaInputVal );
         mva3j1000interferencedownmu = (float) mvaReader3j1000interferencedownmu.GetMvaValue( mvaInputVal );
         mva3j400interferenceupmu = (float) mvaReader3j400interferenceupmu.GetMvaValue( mvaInputVal );
         mva3j450interferenceupmu = (float) mvaReader3j450interferenceupmu.GetMvaValue( mvaInputVal );
         mva3j500interferenceupmu = (float) mvaReader3j500interferenceupmu.GetMvaValue( mvaInputVal );
         mva3j550interferenceupmu = (float) mvaReader3j550interferenceupmu.GetMvaValue( mvaInputVal );
         mva3j600interferenceupmu = (float) mvaReader3j600interferenceupmu.GetMvaValue( mvaInputVal );
         mva3j700interferenceupmu = (float) mvaReader3j700interferenceupmu.GetMvaValue( mvaInputVal );
         mva3j800interferenceupmu = (float) mvaReader3j800interferenceupmu.GetMvaValue( mvaInputVal );
         mva3j900interferenceupmu = (float) mvaReader3j900interferenceupmu.GetMvaValue( mvaInputVal );
         mva3j1000interferenceupmu = (float) mvaReader3j1000interferenceupmu.GetMvaValue( mvaInputVal );

         std::vector<double> DB_mvaInputVal;
         DB_mvaInputVal.push_back( W_pt );
         DB_mvaInputVal.push_back( event_met_pfmet );
         DB_mvaInputVal.push_back( W_muon_charge );   ///////different for electron and muon
         DB_mvaInputVal.push_back( JetPFCor_QGLikelihood[0] );
         DB_mvaInputVal.push_back( JetPFCor_QGLikelihood[1] );
         DB_mvaInputVal.push_back( ang_hs );
         DB_mvaInputVal.push_back( ang_phib );
         DB_mvaInputVal.push_back( fabs(JetPFCor_Eta[0]-JetPFCor_Eta[1]) );
         DB_mvaInputVal.push_back( masslvjj );

         mva2jdibosonmu = (float) mvaReader2jdibosonmu.GetMvaValue( DB_mvaInputVal );
         mva3jdibosonmu = (float) mvaReader3jdibosonmu.GetMvaValue( DB_mvaInputVal );

         std::vector<double> DBnoqg_mvaInputVal;
         DBnoqg_mvaInputVal.push_back( W_pt );
         DBnoqg_mvaInputVal.push_back( event_met_pfmet );
         DBnoqg_mvaInputVal.push_back( W_muon_charge );   ///////different for electron and muon
         DBnoqg_mvaInputVal.push_back( ang_hs );
         DBnoqg_mvaInputVal.push_back( ang_phib );
         DBnoqg_mvaInputVal.push_back( fabs(JetPFCor_Eta[0]-JetPFCor_Eta[1]) );
         DBnoqg_mvaInputVal.push_back( masslvjj );

         mva2jdibnoqgmu = (float) mvaReader2jdibnoqgmu.GetMvaValue( DBnoqg_mvaInputVal );
         mva3jdibnoqgmu = (float) mvaReader3jdibnoqgmu.GetMvaValue( DBnoqg_mvaInputVal );

      }
      // For Hadronic W in Top sample
      if (isgengdevt)
      {
         if (JetPFCor_Pt[3] > Jpt && JetPFCor_Pt[4] < Jpt){
            int nbjet = 0;
            int nbnot = 0;
            int Aj    = -999;
            int Bj    = -999;
            /*if (JetPFCor_bDiscriminator[0]>btssv) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=0; if (nbnot==2) Bj=0;}
              if (JetPFCor_bDiscriminator[1]>btssv) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=1; if (nbnot==2) Bj=1;}
              if (JetPFCor_bDiscriminator[2]>btssv) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=2; if (nbnot==2) Bj=2;}
              if (JetPFCor_bDiscriminator[3]>btssv) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=3; if (nbnot==2) Bj=3;}
             */
            if (JetPFCor_bDiscriminatorCSV[0]>btcsvm) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=0; if (nbnot==2) Bj=0;}
            if (JetPFCor_bDiscriminatorCSV[1]>btcsvm) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=1; if (nbnot==2) Bj=1;}
            if (JetPFCor_bDiscriminatorCSV[2]>btcsvm) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=2; if (nbnot==2) Bj=2;}
            if (JetPFCor_bDiscriminatorCSV[3]>btcsvm) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=3; if (nbnot==2) Bj=3;}

            if (nbjet==2 && nbnot==2 && Aj!=-999 && Bj!=-999){
               TLorentzVector  ajp, bjp; 
               ajp.SetPtEtaPhiE(jess * JetPFCor_Pt[Aj], JetPFCor_Eta[Aj], JetPFCor_Phi[Aj], jess * JetPFCor_E[Aj]  );
               bjp.SetPtEtaPhiE(jess * JetPFCor_Pt[Bj], JetPFCor_Eta[Bj], JetPFCor_Phi[Bj], jess * JetPFCor_E[Bj]  );
               TopWm   = (ajp+bjp).M(); 

               TLorentzVector fit_mup(0,0,0,0), fit_nvp(0,0,0,0), fit_ajp(0,0,0,0), fit_bjp(0,0,0,0) ; Int_t tmpa =0, tmpb=0;
               doKinematicFit( 1, mup, b_nvp, ajp, bjp,  fit_mup, fit_nvp, fit_ajp, fit_bjp, Tchi2, tmpa, tmpb);
            }
         }
      }
      if (isgengdevt)
      {
         if (JetPFCor_Pt[4] > Jpt && JetPFCor_Pt[5] < Jpt){
            int nbjet = 0;
            int nbnot = 0;
            int Aj    = -999;
            int Bj    = -999;
            /*if (JetPFCor_bDiscriminator[0]>btssv) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=0; if (nbnot==2) Bj=0;}
              if (JetPFCor_bDiscriminator[1]>btssv) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=1; if (nbnot==2) Bj=1;}
              if (JetPFCor_bDiscriminator[2]>btssv) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=2; if (nbnot==2) Bj=2;}
              if (JetPFCor_bDiscriminator[3]>btssv) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=3; if (nbnot==2) Bj=3;}
              if (JetPFCor_bDiscriminator[4]>btssv) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=4; if (nbnot==2) Bj=4;}
             */
            if (JetPFCor_bDiscriminatorCSV[0]>btcsvm) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=0; if (nbnot==2) Bj=0;}
            if (JetPFCor_bDiscriminatorCSV[1]>btcsvm) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=1; if (nbnot==2) Bj=1;}
            if (JetPFCor_bDiscriminatorCSV[2]>btcsvm) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=2; if (nbnot==2) Bj=2;}
            if (JetPFCor_bDiscriminatorCSV[3]>btcsvm) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=3; if (nbnot==2) Bj=3;}
            if (JetPFCor_bDiscriminatorCSV[4]>btcsvm) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=4; if (nbnot==2) Bj=4;}

            if (nbjet==2 && nbnot==3 && Aj!=-999 && Bj!=-999){
               TLorentzVector  ajp, bjp; 
               ajp.SetPtEtaPhiE(jess * JetPFCor_Pt[Aj], JetPFCor_Eta[Aj], JetPFCor_Phi[Aj], jess * JetPFCor_E[Aj]  );
               bjp.SetPtEtaPhiE(jess * JetPFCor_Pt[Bj], JetPFCor_Eta[Bj], JetPFCor_Phi[Bj], jess * JetPFCor_E[Bj]  );
               TopWm5j = (ajp+bjp).M(); 

               TLorentzVector fit_mup(0,0,0,0), fit_nvp(0,0,0,0), fit_ajp(0,0,0,0), fit_bjp(0,0,0,0) ; Int_t tmpa =0, tmpb=0;
               doKinematicFit( 1, mup, b_nvp, ajp, bjp,  fit_mup, fit_nvp, fit_ajp, fit_bjp, Tchi25j, tmpa, tmpb);
            }
         }
      }

      //################Begin Boosted W Analysis########################################
      if(isgengdboostedWevt){

         //CA8 Jet And we also need to check the AK7 Jet
         TLorentzVector ca8jetp4;
         ca8jetp4.SetPtEtaPhiE(GroomedJet_CA8_pt[0], GroomedJet_CA8_eta[0], GroomedJet_CA8_phi[0], GroomedJet_CA8_e[0]);
         double deltaR_lca8jet = mup.DeltaR(ca8jetp4);
         //double deltaphi_METca8jet = b_nvp.DeltaPhi(ca8jetp4);
         double deltaphi_METca8jet = getDeltaPhi(b_nvp.Phi(),ca8jetp4.Phi());
         TLorentzVector wbosonp = mup + b_nvp;
         //double deltaphi_Vca8jet = wbosonp.DeltaPhi(ca8jetp4);
         double deltaphi_Vca8jet = getDeltaPhi(wbosonp.Phi(),ca8jetp4.Phi());

         GroomedJet_CA8_deltaR_lca8jet = deltaR_lca8jet;
         GroomedJet_CA8_deltaphi_METca8jet = deltaphi_METca8jet;
         GroomedJet_CA8_deltaphi_Vca8jet = deltaphi_Vca8jet;

         //Count the number of B tag jet, for ttbar and contral plots
         //Synchrinize the Cuts with the Z'->tt group using the semi-leptonic channel selection
         for(int i = 0; i < numPFCorJets; i++)
         {
            if(JetPFCor_Pt[i] > Jpt)
            {
               TLorentzVector  ajp;
               ajp.SetPtEtaPhiE(jess * JetPFCor_Pt[i], JetPFCor_Eta[i], JetPFCor_Phi[i], jess * JetPFCor_E[i]  );

               double tmpdelatR = ca8jetp4.DeltaR(ajp);

               double tmpdeltaRlj = ajp.DeltaR(mup);

               if(tmpdelatR > 0.8)//Veto the AK5 jet in the CA8 jet cone
               {
                  GroomedJet_numberjets = GroomedJet_numberjets + 1;
               }

               //if(JetPFCor_bDiscriminator[i] > btssv && tmpdelatR > 0.8)//Veto the AK5 jet in the CA8 jet cone
               //if(JetPFCor_bDiscriminatorCSV[i] > btcsvm && tmpdelatR > 0.8)//Veto the AK5 jet in the CA8 jet cone and Move to CSVM tagger
               if(JetPFCor_bDiscriminatorCSV[i] > btcsvm && tmpdelatR > 0.8 && tmpdeltaRlj > TMath::Pi()/2.0)//Veto the AK5 jet in the CA8 jet cone and Move to CSVM tagger and leptonic and hadronic top should be in the different hemisphere for ttbar control
               {
                  GroomedJet_numberbjets_csvm = GroomedJet_numberbjets_csvm + 1;
               }

               if(JetPFCor_bDiscriminatorCSV[i] > btcsvl && tmpdelatR > 0.8 && tmpdeltaRlj > TMath::Pi()/2.0)//Veto the AK5 jet in the CA8 jet cone and Move to CSVM tagger and leptonic and hadronic top should be in the different hemisphere for ttbar control
               {
                  GroomedJet_numberbjets_csvl = GroomedJet_numberbjets_csvl + 1;
               }

               if(JetPFCor_bDiscriminator[i] > btssv && tmpdelatR > 0.8 && tmpdeltaRlj > TMath::Pi()/2.0)//Veto the AK5 jet in the CA8 jet cone and Move to CSVM tagger and leptonic and hadronic top should be in the different hemisphere for ttbar control
               {
                  GroomedJet_numberbjets_ssvhem = GroomedJet_numberbjets_ssvhem + 1;
               }

               if(JetPFCor_bDiscriminatorCSV[i] > btcsvl)//ttbar veto
               {
                  GroomedJet_numberbjets_csvl_veto = GroomedJet_numberbjets_csvl_veto + 1;
               }

               if(JetPFCor_bDiscriminatorCSV[i] > btcsvm)//ttbar veto
               {
                  GroomedJet_numberbjets_csvm_veto = GroomedJet_numberbjets_csvm_veto + 1;
               }

               if(JetPFCor_bDiscriminator[i] > btssv)//ttbar veto
               {
                  GroomedJet_numberbjets_ssvhem_veto = GroomedJet_numberbjets_ssvhem_veto + 1;
               }
            }
         }

         //if(GroomedJet_CA8_pt[0] > boostedWJpt && GroomedJet_CA8_pt[1] < boostedWJpt && deltaR_lca8jet > 1.0 && deltaphi_METca8jet > 0.4 && deltaphi_Vca8jet > 2.0) 
         //if(deltaR_lca8jet > 1.0 && deltaphi_METca8jet > 0.4 && deltaphi_Vca8jet > 2.0) 
         if(deltaR_lca8jet > TMath::Pi()/ 2.0 && deltaphi_METca8jet > 2.0 && deltaphi_Vca8jet > 2.0)//Tighter Angular Cuts 
         {
            ggdboostedWevt = 1;
         }

         GroomedJet_CA8_rcores01 = GroomedJet_CA8_rcores[0][0];
         GroomedJet_CA8_ptcores01 = GroomedJet_CA8_ptcores[0][0];
         GroomedJet_CA8_planarflow01 = GroomedJet_CA8_planarflow[0][0];

         GroomedJet_CA8_rcores02 = GroomedJet_CA8_rcores[1][0];
         GroomedJet_CA8_ptcores02 = GroomedJet_CA8_ptcores[1][0];
         GroomedJet_CA8_planarflow02 = GroomedJet_CA8_planarflow[1][0];

         GroomedJet_CA8_rcores03 = GroomedJet_CA8_rcores[2][0];
         GroomedJet_CA8_ptcores03 = GroomedJet_CA8_ptcores[2][0];
         GroomedJet_CA8_planarflow03 = GroomedJet_CA8_planarflow[2][0];

         GroomedJet_CA8_rcores04 = GroomedJet_CA8_rcores[3][0];
         GroomedJet_CA8_ptcores04 = GroomedJet_CA8_ptcores[3][0];
         GroomedJet_CA8_planarflow04 = GroomedJet_CA8_planarflow[3][0];

         GroomedJet_CA8_rcores05 = GroomedJet_CA8_rcores[4][0];
         GroomedJet_CA8_ptcores05 = GroomedJet_CA8_ptcores[4][0];
         GroomedJet_CA8_planarflow05 = GroomedJet_CA8_planarflow[4][0];

         GroomedJet_CA8_rcores06 = GroomedJet_CA8_rcores[5][0];
         GroomedJet_CA8_ptcores06 = GroomedJet_CA8_ptcores[5][0];
         GroomedJet_CA8_planarflow06 = GroomedJet_CA8_planarflow[5][0];

         GroomedJet_CA8_rcores07 = GroomedJet_CA8_rcores[6][0];
         GroomedJet_CA8_ptcores07 = GroomedJet_CA8_ptcores[6][0];
         GroomedJet_CA8_planarflow07 = GroomedJet_CA8_planarflow[6][0];

         GroomedJet_CA8_rcores08 = GroomedJet_CA8_rcores[7][0];
         GroomedJet_CA8_ptcores08 = GroomedJet_CA8_ptcores[7][0];
         GroomedJet_CA8_planarflow08 = GroomedJet_CA8_planarflow[7][0];

         GroomedJet_CA8_rcores09 = GroomedJet_CA8_rcores[8][0];
         GroomedJet_CA8_ptcores09 = GroomedJet_CA8_ptcores[8][0];
         GroomedJet_CA8_planarflow09 = GroomedJet_CA8_planarflow[8][0];

         GroomedJet_CA8_rcores10 = GroomedJet_CA8_rcores[9][0];
         GroomedJet_CA8_ptcores10 = GroomedJet_CA8_ptcores[9][0];
         GroomedJet_CA8_planarflow10 = GroomedJet_CA8_planarflow[9][0];

         GroomedJet_CA8_rcores11 = GroomedJet_CA8_rcores[10][0];
         GroomedJet_CA8_ptcores11 = GroomedJet_CA8_ptcores[10][0];
         GroomedJet_CA8_planarflow11 = GroomedJet_CA8_planarflow[10][0];

         GroomedJet_CA8_mass_sensi_tr = GroomedJet_CA8_mass_tr[0]/GroomedJet_CA8_mass[0];
         GroomedJet_CA8_mass_sensi_ft = GroomedJet_CA8_mass_ft[0]/GroomedJet_CA8_mass[0];
         GroomedJet_CA8_mass_sensi_pr = GroomedJet_CA8_mass_pr[0]/GroomedJet_CA8_mass[0];

         //QJet mass Volatility
         Int_t qjetsize = 50;
         double averagemsquare = 0;
         double averagem = 0;
         for(Int_t i = 0; i < qjetsize; i++)
         {
            averagemsquare = averagemsquare + GroomedJet_CA8_qjetmass[i] * GroomedJet_CA8_qjetmass[i];
            averagem = averagem + GroomedJet_CA8_qjetmass[i];
         } 

         averagemsquare = averagemsquare / qjetsize;
         averagem = averagem / qjetsize;

         GroomedJet_CA8_qjetmassvolatility = TMath::Sqrt(averagemsquare - TMath::Power(averagem,2))/averagem;

         TLorentzVector ca8subjet1p4;
         TLorentzVector ca8subjet2p4;
         TLorentzVector ca8prjetp4;

         ca8subjet1p4.SetPxPyPzE(GroomedJet_CA8_prsubjet1_px[0],GroomedJet_CA8_prsubjet1_py[0],GroomedJet_CA8_prsubjet1_pz[0],GroomedJet_CA8_prsubjet1_e[0]);
         ca8subjet2p4.SetPxPyPzE(GroomedJet_CA8_prsubjet2_px[0],GroomedJet_CA8_prsubjet2_py[0],GroomedJet_CA8_prsubjet2_pz[0],GroomedJet_CA8_prsubjet2_e[0]);
         ca8prjetp4.SetPtEtaPhiE(GroomedJet_CA8_pt_pr[0],GroomedJet_CA8_eta_pr[0],GroomedJet_CA8_phi_pr[0],GroomedJet_CA8_e_pr[0]);

         GroomedJet_CA8_prsubjet1ptoverjetpt = ca8subjet1p4.Pt()/ca8prjetp4.Pt();
         GroomedJet_CA8_prsubjet2ptoverjetpt = ca8subjet2p4.Pt()/ca8prjetp4.Pt();

         if((ca8subjet1p4.Pt() > 0.001) && (ca8subjet2p4.Pt() > 0.001)) //Avoid Too Samll Pt
         {GroomedJet_CA8_prsubjet1subjet2_deltaR = ca8subjet1p4.DeltaR(ca8subjet2p4);}

         //Angular Correlation For the Boosted W Analysis
         boostedW_lvj_e      = (mup+b_nvp+ca8jetp4).E();
         boostedW_lvj_pt     = (mup+b_nvp+ca8jetp4).Pt();
         boostedW_lvj_eta    = (mup+b_nvp+ca8jetp4).Eta();
         boostedW_lvj_phi    = (mup+b_nvp+ca8jetp4).Phi();
         boostedW_lvj_m      = (mup+b_nvp+ca8jetp4).M();
         boostedW_lvj_y      = (mup+b_nvp+ca8jetp4).Rapidity();

         double a_costheta1, a_costheta2, a_phi, a_costhetastar, a_phistar1, a_phistar2;
         //Use the Subjet in the Boosted W Analyisis
         if (W_muon_charge < 0){
            calculateAngles(mup, b_nvp, ca8subjet1p4, ca8subjet2p4, a_costheta1, a_costheta2, a_phi, a_costhetastar, a_phistar1, a_phistar2);
         }
         else{
            calculateAngles(b_nvp, mup, ca8subjet1p4, ca8subjet2p4, a_costheta1, a_costheta2, a_phi, a_costhetastar, a_phistar1, a_phistar2);
         }
         boostedW_wjj_ang_ha = a_costheta1; boostedW_wjj_ang_hb = fabs(a_costheta2); boostedW_wjj_ang_hs = a_costhetastar;  boostedW_wjj_ang_phi = a_phi; boostedW_wjj_ang_phia = a_phistar1; boostedW_wjj_ang_phib = a_phistar2;

         //Input For the TMVA Training And Classification TODO

         //check the AK7 Jet Used in our Reduced Tree
         TLorentzVector ak7jetp4;
         ak7jetp4.SetPtEtaPhiE(GroomedJet_AK7_pt[0], GroomedJet_AK7_eta[0], GroomedJet_AK7_phi[0], GroomedJet_AK7_e[0]);
         double deltaR_lak7jet = mup.DeltaR(ak7jetp4);
         //double deltaphi_METak7jet = b_nvp.DeltaPhi(ak7jetp4);
         double deltaphi_METak7jet = getDeltaPhi(b_nvp.Phi(),ak7jetp4.Phi());
         //TLorentzVector wbosonp = mup + b_nvp;
         //double deltaphi_Vak7jet = wbosonp.DeltaPhi(ak7jetp4);
         double deltaphi_Vak7jet = getDeltaPhi(wbosonp.Phi(),ak7jetp4.Phi());

         GroomedJet_AK7_deltaR_lak7jet = deltaR_lak7jet;
         GroomedJet_AK7_deltaphi_METak7jet = deltaphi_METak7jet;
         GroomedJet_AK7_deltaphi_Vak7jet = deltaphi_Vak7jet;

         //Count the number of B tag jet, for ttbar and contral plots
         for(int i = 0; i < numPFCorJets; i++)
         {
            if(JetPFCor_Pt[i] > Jpt)
            {
               TLorentzVector  ajp;
               ajp.SetPtEtaPhiE(jess * JetPFCor_Pt[i], JetPFCor_Eta[i], JetPFCor_Phi[i], jess * JetPFCor_E[i]  );

               double tmpdelatR = ak7jetp4.DeltaR(ajp);
               double tmpdeltaRlj = ajp.DeltaR(mup);

               if(tmpdelatR > 0.7)//Veto the AK5 jet in the AK7 jet cone
               {
                  GroomedJet_numberjets_ak7 = GroomedJet_numberjets_ak7 + 1;
               }

               //if(JetPFCor_bDiscriminator[i] > btssv && tmpdelatR > 0.8)//Veto the AK5 jet in the AK7 jet cone
               if(JetPFCor_bDiscriminatorCSV[i] > btcsvm && tmpdelatR > 0.7 && tmpdeltaRlj > TMath::Pi()/2.0)//Veto the AK5 jet in the AK7 jet cone and Move to CSVM tagger
               {
                  GroomedJet_numberbjets_csvm_ak7 = GroomedJet_numberbjets_csvm_ak7 + 1;
               }
               if(JetPFCor_bDiscriminatorCSV[i] > btcsvl && tmpdelatR > 0.7 && tmpdeltaRlj > TMath::Pi()/2.0)//Veto the AK5 jet in the AK7 jet cone and Move to CSVM tagger
               {
                  GroomedJet_numberbjets_csvl_ak7 = GroomedJet_numberbjets_csvl_ak7 + 1;
               }
               if(JetPFCor_bDiscriminator[i] > btssv && tmpdelatR > 0.7 && tmpdeltaRlj > TMath::Pi()/2.0)//Veto the AK5 jet in the AK7 jet cone and Move to CSVM tagger
               {
                  GroomedJet_numberbjets_ssvhem_ak7 = GroomedJet_numberbjets_ssvhem_ak7 + 1;
               }
               if(JetPFCor_bDiscriminatorCSV[i] > btcsvl)//ttbar veto
               {
                  GroomedJet_numberbjets_csvl_veto_ak7 = GroomedJet_numberbjets_csvl_veto_ak7 + 1;
               }
               if(JetPFCor_bDiscriminatorCSV[i] > btcsvm)//ttbar veto
               {
                  GroomedJet_numberbjets_csvm_veto_ak7 = GroomedJet_numberbjets_csvm_veto_ak7 + 1;
               }
               if(JetPFCor_bDiscriminator[i] > btssv)//ttbar veto
               {
                  GroomedJet_numberbjets_ssvhem_veto_ak7 = GroomedJet_numberbjets_ssvhem_veto_ak7 + 1;
               }
            }
         }

         //if(deltaR_lak7jet > 1.0 && deltaphi_METak7jet > 0.4 && deltaphi_Vak7jet > 2.0) 
         if(deltaR_lak7jet > TMath::Pi()/2.0 && deltaphi_METak7jet > 2.0 && deltaphi_Vak7jet > 2.0)//Tighter Angular Cuts 
         {
            ggdboostedWevt_ak7 = 1;
         }

         GroomedJet_AK7_rcores01 = GroomedJet_AK7_rcores[0][0];
         GroomedJet_AK7_ptcores01 = GroomedJet_AK7_ptcores[0][0];
         GroomedJet_AK7_planarflow01 = GroomedJet_AK7_planarflow[0][0];

         GroomedJet_AK7_rcores02 = GroomedJet_AK7_rcores[1][0];
         GroomedJet_AK7_ptcores02 = GroomedJet_AK7_ptcores[1][0];
         GroomedJet_AK7_planarflow02 = GroomedJet_AK7_planarflow[1][0];

         GroomedJet_AK7_rcores03 = GroomedJet_AK7_rcores[2][0];
         GroomedJet_AK7_ptcores03 = GroomedJet_AK7_ptcores[2][0];
         GroomedJet_AK7_planarflow03 = GroomedJet_AK7_planarflow[2][0];

         GroomedJet_AK7_rcores04 = GroomedJet_AK7_rcores[3][0];
         GroomedJet_AK7_ptcores04 = GroomedJet_AK7_ptcores[3][0];
         GroomedJet_AK7_planarflow04 = GroomedJet_AK7_planarflow[3][0];

         GroomedJet_AK7_rcores05 = GroomedJet_AK7_rcores[4][0];
         GroomedJet_AK7_ptcores05 = GroomedJet_AK7_ptcores[4][0];
         GroomedJet_AK7_planarflow05 = GroomedJet_AK7_planarflow[4][0];

         GroomedJet_AK7_rcores06 = GroomedJet_AK7_rcores[5][0];
         GroomedJet_AK7_ptcores06 = GroomedJet_AK7_ptcores[5][0];
         GroomedJet_AK7_planarflow06 = GroomedJet_AK7_planarflow[5][0];

         GroomedJet_AK7_rcores07 = GroomedJet_AK7_rcores[6][0];
         GroomedJet_AK7_ptcores07 = GroomedJet_AK7_ptcores[6][0];
         GroomedJet_AK7_planarflow07 = GroomedJet_AK7_planarflow[6][0];

         GroomedJet_AK7_rcores08 = GroomedJet_AK7_rcores[7][0];
         GroomedJet_AK7_ptcores08 = GroomedJet_AK7_ptcores[7][0];
         GroomedJet_AK7_planarflow08 = GroomedJet_AK7_planarflow[7][0];

         GroomedJet_AK7_rcores09 = GroomedJet_AK7_rcores[8][0];
         GroomedJet_AK7_ptcores09 = GroomedJet_AK7_ptcores[8][0];
         GroomedJet_AK7_planarflow09 = GroomedJet_AK7_planarflow[8][0];

         GroomedJet_AK7_rcores10 = GroomedJet_AK7_rcores[9][0];
         GroomedJet_AK7_ptcores10 = GroomedJet_AK7_ptcores[9][0];
         GroomedJet_AK7_planarflow10 = GroomedJet_AK7_planarflow[9][0];

         GroomedJet_AK7_rcores11 = GroomedJet_AK7_rcores[10][0];
         GroomedJet_AK7_ptcores11 = GroomedJet_AK7_ptcores[10][0];
         GroomedJet_AK7_planarflow11 = GroomedJet_AK7_planarflow[10][0];

         GroomedJet_AK7_mass_sensi_tr = GroomedJet_AK7_mass_tr[0]/GroomedJet_AK7_mass[0];
         GroomedJet_AK7_mass_sensi_ft = GroomedJet_AK7_mass_ft[0]/GroomedJet_AK7_mass[0];
         GroomedJet_AK7_mass_sensi_pr = GroomedJet_AK7_mass_pr[0]/GroomedJet_AK7_mass[0];

         //QJet mass Volatility
         Int_t qjetsizeak7 = 50;
         double averagemsquareak7 = 0;
         double averagemak7 = 0;
         for(Int_t i = 0; i < qjetsizeak7; i++)
         {
            averagemsquareak7 = averagemsquareak7 + GroomedJet_AK7_qjetmass[i] * GroomedJet_AK7_qjetmass[i];
            averagemak7 = averagemak7 + GroomedJet_AK7_qjetmass[i];
         } 

         averagemsquareak7 = averagemsquareak7 / qjetsizeak7;
         averagemak7 = averagemak7 / qjetsizeak7;

         GroomedJet_AK7_qjetmassvolatility = TMath::Sqrt(averagemsquareak7 - TMath::Power(averagemak7,2))/averagemak7;

         TLorentzVector ak7subjet1p4;
         TLorentzVector ak7subjet2p4;
         TLorentzVector ak7prjetp4;

         ak7subjet1p4.SetPxPyPzE(GroomedJet_AK7_prsubjet1_px[0],GroomedJet_AK7_prsubjet1_py[0],GroomedJet_AK7_prsubjet1_pz[0],GroomedJet_AK7_prsubjet1_e[0]);
         ak7subjet2p4.SetPxPyPzE(GroomedJet_AK7_prsubjet2_px[0],GroomedJet_AK7_prsubjet2_py[0],GroomedJet_AK7_prsubjet2_pz[0],GroomedJet_AK7_prsubjet2_e[0]);
         ak7prjetp4.SetPtEtaPhiE(GroomedJet_AK7_pt_pr[0],GroomedJet_AK7_eta_pr[0],GroomedJet_AK7_phi_pr[0],GroomedJet_AK7_e_pr[0]);

         GroomedJet_AK7_prsubjet1ptoverjetpt = ak7subjet1p4.Pt()/ak7prjetp4.Pt();
         GroomedJet_AK7_prsubjet2ptoverjetpt = ak7subjet2p4.Pt()/ak7prjetp4.Pt();

         if((ak7subjet1p4.Pt() > 0.001) && (ak7subjet2p4.Pt() > 0.001)) //Avoid Too Samll Pt
         {GroomedJet_AK7_prsubjet1subjet2_deltaR = ak7subjet1p4.DeltaR(ak7subjet2p4);}

         //Angular Correlation For the Boosted W Analysis
         boostedW_lvj_e_ak7      = (mup+b_nvp+ak7jetp4).E();
         boostedW_lvj_pt_ak7     = (mup+b_nvp+ak7jetp4).Pt();
         boostedW_lvj_eta_ak7    = (mup+b_nvp+ak7jetp4).Eta();
         boostedW_lvj_phi_ak7    = (mup+b_nvp+ak7jetp4).Phi();
         boostedW_lvj_m_ak7      = (mup+b_nvp+ak7jetp4).M();
         boostedW_lvj_y_ak7      = (mup+b_nvp+ak7jetp4).Rapidity();

         double tmpa_costheta1, tmpa_costheta2, tmpa_phi, tmpa_costhetastar, tmpa_phistar1, tmpa_phistar2;
         //Use the Subjet in the Boosted W Analyisis
         if (W_muon_charge < 0){
            calculateAngles(mup, b_nvp, ak7subjet1p4, ak7subjet2p4, tmpa_costheta1, tmpa_costheta2, tmpa_phi, tmpa_costhetastar, tmpa_phistar1, tmpa_phistar2);
         }
         else{
            calculateAngles(b_nvp, mup, ak7subjet1p4, ak7subjet2p4, tmpa_costheta1, tmpa_costheta2, tmpa_phi, tmpa_costhetastar, tmpa_phistar1, tmpa_phistar2);
         }
         boostedW_wjj_ang_ha_ak7 = tmpa_costheta1; boostedW_wjj_ang_hb_ak7 = fabs(tmpa_costheta2); boostedW_wjj_ang_hs_ak7 = tmpa_costhetastar;  boostedW_wjj_ang_phi_ak7 = tmpa_phi; boostedW_wjj_ang_phia_ak7 = tmpa_phistar1; boostedW_wjj_ang_phib_ak7 = tmpa_phistar2;

      }
      //###############End Boosted W Analysis########################################

      // For VBF Analysis ! Currently Gd Event Selection same as Hww
      if (isgengdevt)
      {
         // ========== Find lv , wjj, vbf tag jj 
         TLorentzVector vbf_ajp(0,0,0,0), vbf_bjp(0,0,0,0);
         TLorentzVector wjj_ajp(0,0,0,0), wjj_bjp(0,0,0,0); 
         float best_detatagjj = 0; // float best_mtagjj =0;
         float best_mjj = 0; // float best_mjj =0;
         int   n_excj =0, n_exfj = 0, n_gdjj = 0, jj_type = 0, tag_i_id = -1, tag_j_id = -1, wjj_a_id = -1, wjj_b_id = -1;
         for ( size_t i=0; i < jetsize*2; i++) {
            float i_rqpt= (i>5)?(30.0):(Jpt); if (runflag==1) i_rqpt= (i>5)?(25.0):(Jpt); if (runflag==2) i_rqpt= (i>5)?(20.0):(Jpt);
            float i_Pt  = (i>5)?(JetPFCorVBFTag_Pt[i-6])            :(JetPFCor_Pt[i]);
            float i_Eta = (i>5)?(JetPFCorVBFTag_Eta[i-6])           :(JetPFCor_Eta[i]);
            float i_Phi = (i>5)?(JetPFCorVBFTag_Phi[i-6])           :(JetPFCor_Phi[i]);
            float i_E   = (i>5)?(JetPFCorVBFTag_E[i-6])             :(JetPFCor_E[i]);
            //float i_bD  = (i>5)?(JetPFCorVBFTag_bDiscriminator[i-6]):(JetPFCor_bDiscriminator[i]);
            float i_bD  = (i>5)?(JetPFCorVBFTag_bDiscriminatorCSV[i-6]):(JetPFCor_bDiscriminatorCSV[i]);
            if (i_Pt>Jpt && fabs(i_Eta)<VBF_MaxEta) {  if (i>5) {n_exfj++;} else {n_excj++;} } // when count good jet, no btag!
            //if (i_Pt<i_rqpt || i_bD>btssv || fabs(i_Eta)>VBF_MaxEta) continue;
            if (i_Pt<i_rqpt || i_bD>btcsvm || fabs(i_Eta)>VBF_MaxEta) continue;
            for (size_t j=i+1; j <jetsize*2; j++) {
               float j_rqpt= (j>5)?(30.0):(Jpt); if (runflag==1) j_rqpt= (i>5)?(25.0):(Jpt); if (runflag==2) j_rqpt= (i>5)?(20.0):(Jpt);
               float j_Pt  = (j>5)?(JetPFCorVBFTag_Pt[j-6])            :(JetPFCor_Pt[j]);
               float j_Eta = (j>5)?(JetPFCorVBFTag_Eta[j-6])           :(JetPFCor_Eta[j]);
               float j_Phi = (j>5)?(JetPFCorVBFTag_Phi[j-6])           :(JetPFCor_Phi[j]);
               float j_E   = (j>5)?(JetPFCorVBFTag_E[j-6])             :(JetPFCor_E[j]);
               //float j_bD  = (j>5)?(JetPFCorVBFTag_bDiscriminator[j-6]):(JetPFCor_bDiscriminator[j]);
               float j_bD  = (j>5)?(JetPFCorVBFTag_bDiscriminatorCSV[j-6]):(JetPFCor_bDiscriminatorCSV[j]); //Move to CSV
               //if (j_Pt<j_rqpt || j_bD>btssv || fabs(j_Eta)>VBF_MaxEta) continue;
               if (j_Pt<j_rqpt || j_bD>btcsvm || fabs(j_Eta)>VBF_MaxEta) continue;//Move to CSV working point
               // vbf tag jet pair
               TLorentzVector i_p, j_p;
               i_p.SetPtEtaPhiE(jess * i_Pt, i_Eta, i_Phi, jess * i_E  );
               j_p.SetPtEtaPhiE(jess * j_Pt, j_Eta, j_Phi, jess * j_E  );

               if ( (i_Eta*j_Eta)>0 )                                continue;     // 1.  have to be one forward, one backward
               //if ( (fabs(i_Eta-j_Eta)<3.5) || ((i_p+j_p).M()<300) ) continue;     // 2.  Tag pair delta eta>3.5, Mjj>300
               if ( (fabs(i_Eta-j_Eta)<3.5) || ((i_p+j_p).M()<500) ) continue;     // 2.  MOve Tag pair delta eta>3.5, Mjj>500
               // if find more than one combinations
               if ( (i_p+j_p).M() > best_mjj ){                          // 3   Select best combination with maximum Mjj because of the bad angular resolution in the HF
                  best_detatagjj = fabs(i_Eta-j_Eta); n_gdjj++;
                  best_mjj = (i_p+j_p).M();

                  tag_i_id = i; tag_j_id = j; vbf_ajp = i_p; vbf_bjp = j_p;

                  vbf_jj_e      = (i_p+j_p).E();
                  vbf_jj_pt     = (i_p+j_p).Pt();
                  vbf_jj_eta    = (i_p+j_p).Eta();
                  vbf_jj_phi    = (i_p+j_p).Phi();
                  vbf_jj_m      = (i_p+j_p).M();

                  vbf_aj_e      = (i_p).E();
                  vbf_aj_pt     = (i_p).Pt();
                  vbf_aj_eta    = (i_p).Eta();
                  vbf_aj_phi    = (i_p).Phi();
                  vbf_aj_m      = (i_p).M();

                  vbf_bj_e      = (j_p).E();
                  vbf_bj_pt     = (j_p).Pt();
                  vbf_bj_eta    = (j_p).Eta();
                  vbf_bj_phi    = (j_p).Phi();
                  vbf_bj_m      = (j_p).M();

                  vbf_jj_deta   = (i_Eta-j_Eta);
                  vbf_jj_dphi   = (i_Phi-j_Phi);
                  if (i<=5&&j<=5) jj_type = 1;
                  if (i> 5&&j> 5) jj_type = 2;
                  if (i<=5&&j> 5) jj_type = 3;
                  if (i> 5&&j<=5) jj_type = 4; // impossible
                  vbf_jj_type = jj_type;
               }
            }
         }
         if (tag_i_id!=-1&&tag_j_id!=-1){                                        // 4.  Find W->jj
            for ( int i=0; i < (int) jetsize; i++) { // only loop over central jets
               if (JetPFCor_Pt[i] < Jpt) continue;    // require central jet pT for W
               if ( i!=tag_i_id&&i!=tag_j_id&&wjj_ajp.Pt()!=0 && wjj_bjp.Pt()==0 ) {int Bj = i;  wjj_bjp.SetPtEtaPhiE(jess * JetPFCor_Pt[Bj], JetPFCor_Eta[Bj], JetPFCor_Phi[Bj], jess * JetPFCor_E[Bj] ); wjj_b_id=Bj; }
               if ( i!=tag_i_id&&i!=tag_j_id&&wjj_ajp.Pt()==0 && wjj_bjp.Pt()==0 ) {int Aj = i;  wjj_ajp.SetPtEtaPhiE(jess * JetPFCor_Pt[Aj], JetPFCor_Eta[Aj], JetPFCor_Phi[Aj], jess * JetPFCor_E[Aj] ); wjj_a_id=Aj; }
            }
         }

         if (tag_i_id!=-1&&tag_j_id!=-1&&wjj_a_id!=-1&&wjj_b_id!=-1){            // 5.  Find two vbf jets and two W jets

            //Di-boson variables in the VBF topology
            float tmpWjjeta  = fabs(JetPFCor_Eta[wjj_a_id] - JetPFCor_Eta[wjj_b_id]);

            float tmpleadingjet_dphiMET = fabs(getDeltaPhi(JetPFCor_Phi[wjj_a_id], b_nvp.Phi()));

            float tmpdijetpt = sqrt(JetPFCor_Pt[wjj_a_id]*JetPFCor_Pt[wjj_a_id]+ JetPFCor_Pt[wjj_b_id]*JetPFCor_Pt[wjj_b_id]+ 2*JetPFCor_Pt[wjj_a_id]*JetPFCor_Pt[wjj_b_id]*cos(JetPFCor_Phi[wjj_a_id]-JetPFCor_Phi[wjj_b_id]));

            //The following cuts are for the di-boson selection in the VBF topology
            //Two additional Cuts are also considered when generating the plots and fit
            //Two Wjj jet Pt > 35 and btag jet veto requirement 
            if(tmpWjjeta < 1.5 && tmpleadingjet_dphiMET > 0.4 && tmpdijetpt > 20 )
            {
               vbf_diboson_event = 1;
            }

            vbf_event = 1; vbf_aj_id = tag_i_id; vbf_bj_id = tag_j_id; vbf_waj_id = wjj_a_id; vbf_wbj_id = wjj_b_id;

            vector<double> wjj_aj_bj_eta;
            wjj_aj_bj_eta.push_back(vbf_ajp.Eta());
            wjj_aj_bj_eta.push_back(vbf_bjp.Eta());
            wjj_aj_bj_eta.push_back(wjj_ajp.Eta());
            wjj_aj_bj_eta.push_back(wjj_bjp.Eta());

            sort(wjj_aj_bj_eta.begin(), wjj_aj_bj_eta.end()); // Sort the Eta form smallest to largest

            for(int i = 0; i < (int) jetsize * 2; ++i)
            {
               float i_rqpt= (i>5)?(30.0):(Jpt); if (runflag==1) i_rqpt= (i>5)?(25.0):(Jpt); if (runflag==2) i_rqpt= (i>5)?(20.0):(Jpt);
               float i_Pt  = (i>5)?(JetPFCorVBFTag_Pt[i-6]):(JetPFCor_Pt[i]);
               float i_Eta = (i>5)?(JetPFCorVBFTag_Eta[i-6]):(JetPFCor_Eta[i]); 
               //float i_bD  = (i>5)?(JetPFCorVBFTag_bDiscriminator[i-6]):(JetPFCor_bDiscriminator[i]);
               float i_bD  = (i>5)?(JetPFCorVBFTag_bDiscriminatorCSV[i-6]):(JetPFCor_bDiscriminatorCSV[i]);

               //if(i_Pt<i_rqpt || i_bD>btssv || fabs(i_Eta)>VBF_MaxEta) continue;
               if(i_Pt<i_rqpt || i_bD>btcsvm || fabs(i_Eta)>VBF_MaxEta) continue;

               if( (i_Eta > (wjj_aj_bj_eta[0] + 0.001) && i_Eta < (wjj_aj_bj_eta[1] - 0.001)) || (i_Eta > (wjj_aj_bj_eta[2] + 0.001) && i_Eta < (wjj_aj_bj_eta[3] - 0.001))) // Real Eta differences 
               {
                  vbf_aj_bj_Wjj_jetnumber = vbf_aj_bj_Wjj_jetnumber + 1;
               }

               if(i_Eta > (wjj_aj_bj_eta[1] + 0.001) && i_Eta < (wjj_aj_bj_eta[2] - 0.001)) //Real Eta Differences
               {
                  vbf_waj_wbj_jetnumber = vbf_waj_wbj_jetnumber + 1;
               }

            }

            vbf_lvwajbj_ajbj_dphi = ((mup+b_nvp+wjj_ajp+wjj_bjp).Phi() - (vbf_ajp + vbf_bjp).Phi()); //Two New Variables Added in the TMVA

            vbf_lvwajbj_ajbj_deta = TMath::Abs((mup+b_nvp+wjj_ajp+wjj_bjp).Eta() - (vbf_ajp.Eta() + vbf_bjp.Eta())/2.0); //Two New Variables Added in the TMVA

            vbf_wjj_e      = (wjj_ajp+wjj_bjp).E();
            vbf_wjj_pt     = (wjj_ajp+wjj_bjp).Pt();
            vbf_wjj_eta    = (wjj_ajp+wjj_bjp).Eta();
            vbf_wjj_phi    = (wjj_ajp+wjj_bjp).Phi();
            vbf_wjj_m      = (wjj_ajp+wjj_bjp).M();

            vbf_waj_e      = (wjj_ajp).E();
            vbf_waj_pt     = (wjj_ajp).Pt();
            vbf_waj_eta    = (wjj_ajp).Eta();
            vbf_waj_phi    = (wjj_ajp).Phi();
            vbf_waj_m      = (wjj_ajp).M();

            vbf_wbj_e      = (wjj_bjp).E();
            vbf_wbj_pt     = (wjj_bjp).Pt();
            vbf_wbj_eta    = (wjj_bjp).Eta();
            vbf_wbj_phi    = (wjj_bjp).Phi();
            vbf_wbj_m      = (wjj_bjp).M();

            vbf_lvjj_e      = (mup+b_nvp+wjj_ajp+wjj_bjp).E();
            vbf_lvjj_pt     = (mup+b_nvp+wjj_ajp+wjj_bjp).Pt();
            vbf_lvjj_eta    = (mup+b_nvp+wjj_ajp+wjj_bjp).Eta();
            vbf_lvjj_phi    = (mup+b_nvp+wjj_ajp+wjj_bjp).Phi();
            vbf_lvjj_m      = (mup+b_nvp+wjj_ajp+wjj_bjp).M();
            vbf_lvjj_y      = (mup+b_nvp+wjj_ajp+wjj_bjp).Rapidity();

            //Variabels used for the di-boson selection
            vbf_diboson_dijetpt = tmpdijetpt;
            vbf_diboson_deltaeta_Wjj = tmpWjjeta;
            vbf_diboson_deltaphi_MET_leadingWjet = tmpleadingjet_dphiMET;

            double a_costheta1, a_costheta2, a_phi, a_costhetastar, a_phistar1, a_phistar2;
            if (W_muon_charge < 0){
               calculateAngles(mup, b_nvp, wjj_ajp, wjj_bjp, a_costheta1, a_costheta2, a_phi, a_costhetastar, a_phistar1, a_phistar2);
            }
            else{
               calculateAngles(b_nvp, mup, wjj_ajp, wjj_bjp, a_costheta1, a_costheta2, a_phi, a_costhetastar, a_phistar1, a_phistar2);
            }
            vbf_wjj_ang_ha = a_costheta1; vbf_wjj_ang_hb = fabs(a_costheta2); vbf_wjj_ang_hs = a_costhetastar;  vbf_wjj_ang_phi = a_phi; vbf_wjj_ang_phia = a_phistar1; vbf_wjj_ang_phib = a_phistar2;

            // count numbers
            if (jj_type==0) {n_excj=n_excj-0; n_exfj=n_exfj-0;}
            if (jj_type==1) {n_excj=n_excj-4; n_exfj=n_exfj-0;}
            if (jj_type==2) {n_excj=n_excj-2; n_exfj=n_exfj-2;}
            if (jj_type==3) {n_excj=n_excj-3; n_exfj=n_exfj-1;}
            if (jj_type==4) {n_excj=n_excj-3; n_exfj=n_exfj-1;}
            vbf_n_excj = n_excj;
            vbf_n_exfj = n_exfj;
            vbf_n_gdjj = n_gdjj;

            // Write MVA variables
            std::vector<double> vbf_mvaInputVal;
            vbf_mvaInputVal.push_back( vbf_lvjj_pt );
            vbf_mvaInputVal.push_back( vbf_lvjj_y );
            vbf_mvaInputVal.push_back( W_muon_charge );   ///////different for electron and muon
            vbf_mvaInputVal.push_back( vbf_wjj_ang_ha );
            vbf_mvaInputVal.push_back( vbf_wjj_ang_hb );
            vbf_mvaInputVal.push_back( vbf_wjj_ang_hs );
            vbf_mvaInputVal.push_back( vbf_wjj_ang_phi );
            vbf_mvaInputVal.push_back( vbf_wjj_ang_phib );
            //vbf_mvaInputVal.push_back( vbf_jj_deta );
            //vbf_mvaInputVal.push_back( vbf_jj_m );

            mvavbf170mu = (float) mvaReadervbf170mu.GetMvaValue( vbf_mvaInputVal );
            mvavbf180mu = (float) mvaReadervbf180mu.GetMvaValue( vbf_mvaInputVal );
            mvavbf190mu = (float) mvaReadervbf190mu.GetMvaValue( vbf_mvaInputVal );
            mvavbf200mu = (float) mvaReadervbf200mu.GetMvaValue( vbf_mvaInputVal );
            mvavbf250mu = (float) mvaReadervbf250mu.GetMvaValue( vbf_mvaInputVal );
            mvavbf300mu = (float) mvaReadervbf300mu.GetMvaValue( vbf_mvaInputVal );
            mvavbf350mu = (float) mvaReadervbf350mu.GetMvaValue( vbf_mvaInputVal );
            mvavbf400mu = (float) mvaReadervbf400mu.GetMvaValue( vbf_mvaInputVal );
            mvavbf450mu = (float) mvaReadervbf450mu.GetMvaValue( vbf_mvaInputVal );
            mvavbf500mu = (float) mvaReadervbf500mu.GetMvaValue( vbf_mvaInputVal );
            mvavbf550mu = (float) mvaReadervbf550mu.GetMvaValue( vbf_mvaInputVal );
            mvavbf600mu = (float) mvaReadervbf600mu.GetMvaValue( vbf_mvaInputVal );

         }

         // ========== txt for Dan
         int * gdcjet  = new int[jetsize];
         int * gdfjet  = new int[jetsize];
         int   ngdcjet = 0, ngdfjet = 0;
         for ( size_t ijet=0; ijet < jetsize; ++ijet) {
            gdcjet[ijet] = 0;
            gdfjet[ijet] = 0;
            // Identify B Jet
            if (JetPFCor_Pt[ijet]>Jpt                        &&
                  JetPFCor_bDiscriminator[ijet]<btssv           ) {gdcjet[ijet] = 1; ngdcjet++;}
            if (JetPFCorVBFTag_Pt[ijet]>Jpt                  &&
                  JetPFCorVBFTag_bDiscriminator[ijet]<btssv    && 
                  fabs(JetPFCorVBFTag_Eta[ijet])<VBF_MaxEta     ) {gdfjet[ijet] = 1; ngdfjet++;}
         }
         if (ngdcjet>1 && (ngdcjet+ngdfjet)>3) { // Good VBF event has N total jet >3 and N central jet >1
            // ----- Output txt file for Dan -15 Lepton and -5 MET
            fprintf(textfile, "%12.5f  %12.5f  %12.5f  %12.5f  %12.5f  %12.5f  %12.5f \n",
                  -15.0, W_muon_pt,     W_muon_eta,     W_muon_phi,     0.0, 0.0, 0.0);
            fprintf(textfile, "%12.5f  %12.5f  %12.5f  %12.5f  %12.5f  %12.5f  %12.5f \n",
                  -5.0,  event_met_pfmet, event_met_pfmetPhi, event_met_pfmetsignificance, event_met_pfsumet, (double)event_nPV, 0.0); 
            //-5.0, event_metMVA_met , event_met_pfmetPhi, event_met_pfmetsignificance, event_met_pfsumet, (double)event_nPV, 0.0); 
            // ----- Output txt file for Dan Jet with pT > jetthreshold
            for ( size_t ijet=0; ijet < jetsize; ++ijet) {
               if(gdcjet[ijet]==1) 
                  fprintf(textfile, "%12.5f  %12.5f  %12.5f  %12.5f  %12.5f  %12.5f  %12.5f \n",
                        JetPFCor_E[ijet], JetPFCor_Pt[ijet], JetPFCor_Eta[ijet], JetPFCor_Phi[ijet], JetPFCor_bDiscriminator[ijet], 0.0, 0.0 );
               if(gdfjet[ijet]==1) 
                  fprintf(textfile, "%12.5f  %12.5f  %12.5f  %12.5f  %12.5f  %12.5f  %12.5f \n",
                        JetPFCorVBFTag_E[ijet], JetPFCorVBFTag_Pt[ijet], JetPFCorVBFTag_Eta[ijet], JetPFCorVBFTag_Phi[ijet], JetPFCorVBFTag_bDiscriminator[ijet], 0.0, 0.0 );
            }
         }
         // For VBF Analysis ! Currently Gd Event Selection same as Hww
      }

      //Next is for EWK W+2jets analysis
      if(isgendevtnojetevt)//One good muon, no jet requirement
      {

         vector<TLorentzVector*> sortjets;
         TMap jetsp4QGd;//Quark-Gluon Discriminator Map
         TMap jetsp4btagCSV; //B-tag Discriminator Map

         for(unsigned int i = 0; i < jetsize; i++)
         {     
            if(JetPFCor_Pt[i] > 20.0)
            {
               TLorentzVector *pfjet = new TLorentzVector(0,0,0,0);
               pfjet->SetPtEtaPhiE(jess * JetPFCor_Pt[i], JetPFCor_Eta[i], JetPFCor_Phi[i], jess * JetPFCor_E[i]);
               sortjets.push_back(pfjet);
               Float_t *tmp_qgd = &JetPFCor_QGLikelihood[i];
               jetsp4QGd.Add(pfjet,(TObject*)tmp_qgd);
               Float_t *tmp_btagCSV = &JetPFCor_bDiscriminatorCSV[i];
               jetsp4btagCSV.Add(pfjet,(TObject*)tmp_btagCSV);
            }
         }

         for(unsigned int j = 0; j < jetsize; j++)
         {
            if(JetPFCorVBFTag_Pt[j] > 20.0)
            {
               TLorentzVector *pfjet = new TLorentzVector(0,0,0,0);
               pfjet->SetPtEtaPhiE(jess * JetPFCorVBFTag_Pt[j], JetPFCorVBFTag_Eta[j], JetPFCorVBFTag_Phi[j], jess * JetPFCorVBFTag_E[j]);
               sortjets.push_back(pfjet);
               Float_t *tmp_qgd = &JetPFCorVBFTag_QGLikelihood[j];
               jetsp4QGd.Add(pfjet,(TObject*)tmp_qgd);
               Float_t *tmp_btagCSV = &JetPFCorVBFTag_bDiscriminatorCSV[j];
               jetsp4btagCSV.Add(pfjet,(TObject*)tmp_btagCSV);
            }
         }

         //Sort the jet according to Jet Pt
         sort(sortjets.begin(),sortjets.end(),mysortPt);

         TLorentzVector leadingjetp4;
         TLorentzVector secondjetp4;
         //The leading left jet between the tag jet pair eta region
         TLorentzVector centraljetp4;

         TLorentzVector wlv_p = mup + b_nvp;

         const float firsttagjetpt = 30.;
         const float secondtagjetpt = 30.;
         const float tagjeteta = 4.7;
         const float tagjetmass = 300.;

         //leading and second leading jet pT are considered as the tag jet pair
         //First try: very soft cut 
         if(sortjets.size() > 1 && sortjets[0]->Pt() > firsttagjetpt && sortjets[1]->Pt() > secondtagjetpt && fabs(sortjets[0]->Eta()) < tagjeteta && fabs(sortjets[1]->Eta()) < tagjeteta)
         {

            //Fill the gen level information for the signal sample
            TString tmpfilename(outfilename); 

            if(tmpfilename.Contains("EWKW2Jets"))
            {
               EWK_W_2jets_genW_pt = W_EWKW_pt;
               EWK_W_2jets_genW_eta = W_EWKW_eta;
               EWK_W_2jets_genW_phi = W_EWKW_phi;
               EWK_W_2jets_genW_e = W_EWKW_E;

               EWK_W_2jets_genTagquark1_pt = W_EWKTagQuark_pt[0];
               EWK_W_2jets_genTagquark1_eta = W_EWKTagQuark_eta[0];
               EWK_W_2jets_genTagquark1_phi = W_EWKTagQuark_phi[0];
               EWK_W_2jets_genTagquark1_e = W_EWKTagQuark_E[0];
               EWK_W_2jets_genTagquark1_id = W_EWKTagQuark_Id[0];

               EWK_W_2jets_genTagquark2_pt = W_EWKTagQuark_pt[1];
               EWK_W_2jets_genTagquark2_eta = W_EWKTagQuark_eta[1];
               EWK_W_2jets_genTagquark2_phi = W_EWKTagQuark_phi[1];
               EWK_W_2jets_genTagquark2_e = W_EWKTagQuark_E[1];
               EWK_W_2jets_genTagquark2_id = W_EWKTagQuark_Id[1];

            }

            if(tmpfilename.Contains("WJets")) 
            {
               W_gen_numPartons = W_nParton_Winclusive;

               Int_t NWJets  = 76102995;
               Int_t NW1Jets = 23141598;
               Int_t NW2Jets = 34044921;
               Int_t NW3Jets = 15539503;
               Int_t NW4Jets = 4369420;
               Float_t f_1 = 5400.0 / 30400.0; //LO W1Jets/ LO WJets inclusive
               Float_t f_2 = 1750.0 / 30400.0; //LO W2Jets/ LO WJets inclusive
               Float_t f_3 = 519.0 / 30400.0; //LO W3Jets/ LO WJets inclusive
               Float_t f_4 = 214.0 / 30400.0;//LO W4Jets/ LO WJets inclusive 

               //The assumption we put here: we think the LO/LO inclusive = NLO/NLO inclusive
               if(W_nParton_Winclusive != -4){

                  switch (W_nParton_Winclusive)
                  {
                     case 1:
                        W_nParton_weight = NWJets * f_1 /(NWJets * f_1 + NW1Jets);
                        break;
                     case 2:
                        W_nParton_weight = NWJets * f_2 /(NWJets * f_2 + NW2Jets);
                        break;
                     case 3:
                        W_nParton_weight = NWJets * f_3 /(NWJets * f_3 + NW3Jets);
                        break;
                     case 4:
                        W_nParton_weight = NWJets * f_4 /(NWJets * f_4 + NW4Jets);
                        break;
                     case 0:
                        W_nParton_weight = NWJets * (1.0 - f_1 - f_2 -f_3 - f_4) / (NWJets * (1.0 - f_1 - f_2 -f_3 - f_4));
                        break;
                     default:
                        W_nParton_weight = 1.0;
                        break;
                  }
               }
            }
            //End the gen level information

            leadingjetp4.SetPtEtaPhiE(sortjets[0]->Pt(), sortjets[0]->Eta(), sortjets[0]->Phi(), sortjets[0]->E());
            secondjetp4.SetPtEtaPhiE(sortjets[1]->Pt(), sortjets[1]->Eta(), sortjets[1]->Phi(), sortjets[1]->E());

            float lstagjetmass = (leadingjetp4 + secondjetp4).M();
            float rapdiff_W_dijet = fabs(wlv_p.Rapidity() - (leadingjetp4.Rapidity() + secondjetp4.Rapidity())/ 2.0);

            //no cuts for tag jet mass
            EWK_W_2jets_event = 1;

            //Basic kenimatic variables
            EWK_W_2jets_tagjet1_pt = leadingjetp4.Pt();
            EWK_W_2jets_tagjet1_eta = leadingjetp4.Eta();
            EWK_W_2jets_tagjet1_phi = leadingjetp4.Phi();
            EWK_W_2jets_tagjet1_e = leadingjetp4.E();
            EWK_W_2jets_tagjet1_m = leadingjetp4.M();

            EWK_W_2jets_tagjet2_pt = secondjetp4.Pt();
            EWK_W_2jets_tagjet2_eta = secondjetp4.Eta();
            EWK_W_2jets_tagjet2_phi = secondjetp4.Phi();
            EWK_W_2jets_tagjet2_e = secondjetp4.E();
            EWK_W_2jets_tagjet2_m = secondjetp4.M();

            //Tag Jet pair
            EWK_W_2jets_tagjet_etasign = (leadingjetp4.Eta() * secondjetp4.Eta() < 0 ? -1 : 1);
            EWK_W_2jets_tagjet_deltaeta = fabs(leadingjetp4.Eta() - secondjetp4.Eta());
            EWK_W_2jets_tagjet_sumeta = leadingjetp4.Eta() + secondjetp4.Eta();
            EWK_W_2jets_tagjet_deltaphi = getDeltaPhi(leadingjetp4.Phi(), secondjetp4.Phi());
            EWK_W_2jets_tagjet_deltaR = leadingjetp4.DeltaR(secondjetp4); 
            EWK_W_2jets_tagjet_mass = lstagjetmass;

            //Lepton and MET
            EWK_W_2jets_l_pt = mup.Pt();
            EWK_W_2jets_l_eta = mup.Eta();
            EWK_W_2jets_l_phi = mup.Phi();
            EWK_W_2jets_l_e = mup.E();
            EWK_W_2jets_l_MET_deltaphi = getDeltaPhi(mup.Phi(), nvp.Phi());

            //Lepton and tag jet pair
            EWK_W_2jets_l_tagjet1_deltaeta = fabs(mup.Eta() - leadingjetp4.Eta());
            EWK_W_2jets_l_tagjet1_deltaphi = getDeltaPhi(mup.Phi(), leadingjetp4.Phi());
            EWK_W_2jets_l_tagjet1_deltaR = mup.DeltaR(leadingjetp4);
            EWK_W_2jets_l_tagjet2_deltaeta = fabs(mup.Eta() - secondjetp4.Eta());
            EWK_W_2jets_l_tagjet2_deltaphi = getDeltaPhi(mup.Phi(), secondjetp4.Phi());
            EWK_W_2jets_l_tagjet2_deltaR = mup.DeltaR(secondjetp4);

            EWK_W_2jets_W_pt = wlv_p.Pt();
            EWK_W_2jets_W_eta = wlv_p.Eta();
            EWK_W_2jets_W_rap = wlv_p.Rapidity();
            EWK_W_2jets_W_phi = wlv_p.Phi();
            EWK_W_2jets_W_e = wlv_p.E();
            EWK_W_2jets_W_mT = W_mt;

            //W boson and tag jet pair
            EWK_W_2jets_W_tagjet1_deltaphi = getDeltaPhi(wlv_p.Phi(), leadingjetp4.Phi());
            EWK_W_2jets_W_tagjet1_deltaeta = fabs(wlv_p.Eta() - leadingjetp4.Eta());
            EWK_W_2jets_W_tagjet1_deltaR = wlv_p.DeltaR(leadingjetp4);
            EWK_W_2jets_W_tagjet2_deltaphi = getDeltaPhi(wlv_p.Phi(), secondjetp4.Phi());
            EWK_W_2jets_W_tagjet2_deltaeta = fabs(wlv_p.Eta() - secondjetp4.Eta());
            EWK_W_2jets_W_tagjet2_deltaR = wlv_p.DeltaR(secondjetp4);

            EWK_W_2jets_W_tagjet_Zeppenfield = rapdiff_W_dijet;

            vector<double> tagjet_1_2_eta;
            tagjet_1_2_eta.push_back(EWK_W_2jets_tagjet1_eta);
            tagjet_1_2_eta.push_back(EWK_W_2jets_tagjet2_eta);
            sort(tagjet_1_2_eta.begin(), tagjet_1_2_eta.end()); //Sort the jet eta from smallest to largest

            //Just count the central jet number when changing the Jet Pt threshold
            if(sortjets.size() > 2 && sortjets[2]->Pt() > 20.0)
            {
               for(unsigned int i = 2; i < sortjets.size(); i++)
               {    
                  TLorentzVector tmpp4;
                  tmpp4.SetPtEtaPhiE(sortjets[i]->Pt(), sortjets[i]->Eta(), sortjets[i]->Phi(), sortjets[i]->E());

                  if(tmpp4.Pt() > 20.0 && tmpp4.Eta() > tagjet_1_2_eta[0] && tmpp4.Eta() < tagjet_1_2_eta[1]) 
                  {
                     EWK_W_2jets_centraljetnum_20++;
                  }

                  if(tmpp4.Pt() > 25.0 && tmpp4.Eta() > tagjet_1_2_eta[0] && tmpp4.Eta() < tagjet_1_2_eta[1]) 
                  {
                     EWK_W_2jets_centraljetnum_25++;
                  }

                  if(tmpp4.Pt() > 30.0 && tmpp4.Eta() > tagjet_1_2_eta[0] && tmpp4.Eta() < tagjet_1_2_eta[1]) 
                  {
                     EWK_W_2jets_centraljetnum_30++;
                  }
               }
            }

            //Find the left FIRST central jet between the tag jet eta
            bool findcentraljet = false;

            if(sortjets.size() > 2 && sortjets[2]->Pt() > 20.0)// Make sure we have one real traditional jet
            {
               for(unsigned int i = 2; i < sortjets.size(); i++)
               {
                  TLorentzVector tmpp4;
                  tmpp4.SetPtEtaPhiE(sortjets[i]->Pt(), sortjets[i]->Eta(), sortjets[i]->Phi(), sortjets[i]->E());

                  if(tmpp4.Pt() > 20.0 && tmpp4.Eta() > tagjet_1_2_eta[0] && tmpp4.Eta() < tagjet_1_2_eta[1]) //Central jet between the tag jet eta region
                  {
                     findcentraljet = true;

                     EWK_W_2jets_findcentraljet = 1;

                     EWK_W_2jets_centraljet_pt = tmpp4.Pt();
                     EWK_W_2jets_centraljet_eta = tmpp4.Eta();
                     EWK_W_2jets_centraljet_phi = tmpp4.Phi();
                     EWK_W_2jets_centraljet_e = tmpp4.E();
                     EWK_W_2jets_centraljet_m = tmpp4.M();

                     EWK_W_2jets_centraljet_tagjet1_deltaeta = fabs(tmpp4.Eta() - leadingjetp4.Eta());
                     EWK_W_2jets_centraljet_tagjet1_deltaphi = getDeltaPhi(tmpp4.Phi(), leadingjetp4.Phi());
                     EWK_W_2jets_centraljet_tagjet1_deltaR = tmpp4.DeltaR(leadingjetp4);
                     EWK_W_2jets_centraljet_tagjet2_deltaeta = fabs(tmpp4.Eta() - secondjetp4.Eta());
                     EWK_W_2jets_centraljet_tagjet2_deltaphi = getDeltaPhi(tmpp4.Phi(), secondjetp4.Phi());
                     EWK_W_2jets_centraljet_tagjet2_deltaR = tmpp4.DeltaR(secondjetp4);

                     EWK_W_2jets_centraljet_tagjet_Zeppenfield = fabs(tmpp4.Rapidity() - (leadingjetp4.Rapidity() + secondjetp4.Rapidity())/2.0);

                  }

                  if(findcentraljet) break;
               }
            }

            //Tag jet pair Q-G information
            if((jetsp4QGd.FindObject(sortjets[0]) != 0) && (jetsp4QGd.FindObject(sortjets[1]) != 0))
            {
               Float_t *tmp1qg = (Float_t*) jetsp4QGd.GetValue(sortjets[0]);
               Float_t *tmp2qg = (Float_t*) jetsp4QGd.GetValue(sortjets[1]);
               EWK_W_2jets_tagjet1_QGd = *tmp1qg;
               EWK_W_2jets_tagjet2_QGd = *tmp2qg;
            } 
            if((jetsp4btagCSV.FindObject(sortjets[0]) != 0) && (jetsp4btagCSV.FindObject(sortjets[1]) != 0))
            {
               Float_t *tmp1btagCSV = (Float_t*) jetsp4btagCSV.GetValue(sortjets[0]);
               Float_t *tmp2btagCSV = (Float_t*) jetsp4btagCSV.GetValue(sortjets[1]);
               EWK_W_2jets_tagjet1_btagCSV = *tmp1btagCSV;
               EWK_W_2jets_tagjet2_btagCSV = *tmp2btagCSV;
            } 

         }//Loose tag jet selection

      }
      //End for EWK W+2jets analysis

      //Next is for ttH Analysis
      if(isgengdevt)
      {
         //ttH event is requiring 6 good jets in the event and at leat of two of them are (CSVM) btagged jet
         int ncsvmjet = 0, njet = 0;
         vector<TLorentzVector> jetsp4;

         for( unsigned int i = 0; i < jetsize; i++)
         {
            if(JetPFCor_Pt[i] > Jpt)
            {
               njet++;

               TLorentzVector tmpp4;
               tmpp4.SetPtEtaPhiE(jess * JetPFCor_Pt[i], JetPFCor_Eta[i], JetPFCor_Phi[i], jess * JetPFCor_E[i]);
               jetsp4.push_back(tmpp4);

               //if(JetPFCor_bDiscriminatorCSV[i] > btcsvm)
               if(JetPFCor_bDiscriminatorCSV[i] > btcsvl)
               {
                  ncsvmjet++;
               }
            }
         }

         //if(njet >= 6 && ncsvmjet >= 2)
         //if(njet >= 6 && ncsvmjet >= 4)
         if(njet >= 6)
         {
            ttH_check_event = 1;

            //the leading two b jets and then the left four jets are assuming to form the hadronic W candidate
            TLorentzVector waj_p(0.,0.,0.,0.), wbj_p(0.,0.,0.,0.), dijetaj_p(0.,0.,0.,0.), dijetbj_p(0.,0.,0.,0.);
            TLorentzVector toplvj_aj_p(0.,0.,0.,0.), topjjj_aj_p(0.,0.,0.,0.);
            TLorentzVector wjj_p(0.,0.,0.,0.), toplvj_p(0.,0.,0.,0.), topjjj_p(0.,0.,0.,0.), ditop_p(0.,0.,0.,0.);
            TLorentzVector dijet_p(0.,0.,0.,0.);
            TLorentzVector wlv_p = mup + b_nvp;

            Int_t topjetindex[4] = {-1, -1, -1, -1};

            //find dijet jet index
            Int_t dijetindex[2] = {-1, -1}; 

            //Double_t lepsigma2 = 295.4;
            //Double_t sigma2 = 103.6; //From the PAS Top-11-009
            //Double_t sigma2top = 302.4; 

            Double_t smallestfitchi2 = 9.0e+30;
            Int_t smallestfitstatus = -1;
            Int_t smallestfitNDF = -1;


            for ( Int_t iijet = 0; iijet < (njet ); ++iijet ) {//leptonic top jet
               for ( Int_t jjjet = 0; jjjet < (njet - 1); ++jjjet ) { //first hadronic top jet
                  for(Int_t kkjet = jjjet + 1; kkjet < njet; ++kkjet){ //second hadronic top jet
                     for(Int_t lljet = 0; lljet < njet; ++lljet){//third hadronic top jet
                        if(jjjet == iijet || jjjet == lljet || kkjet == lljet) continue;
                        if(kkjet == iijet) continue;
                        if(lljet == iijet) continue;
                        //if(JetPFCor_bDiscriminatorCSV[jjjet] > btcsvl || JetPFCor_bDiscriminatorCSV[kkjet] > btcsvl) continue;
                        //if(JetPFCor_bDiscriminatorCSV[iijet] < btcsvl || JetPFCor_bDiscriminatorCSV[lljet] < btcsvl) continue;
                        //######################At least#########################
                        //if((JetPFCor_bDiscriminatorCSV[jjjet] > btcsvl && JetPFCor_bDiscriminatorCSV[kkjet] > btcsvl)) continue;
                        //if((JetPFCor_bDiscriminatorCSV[iijet] < btcsvl && JetPFCor_bDiscriminatorCSV[lljet] < btcsvl)) continue;
                        //######################At least#########################
                        //#####################At least Three CSVL Btag Method, Remove the Btag Veto Requirement########################################################
                        /*if((JetPFCor_bDiscriminatorCSV[iijet] < btcsvl && JetPFCor_bDiscriminatorCSV[lljet] < btcsvl)) continue;
                          Int_t tmpdijetindex[2] = {-1, -1};
                          Int_t tmpcount = 0;
                          for(Int_t ijet = 0; ijet < njet; ijet++)
                          {
                          if(ijet == iijet || ijet == jjjet || ijet == kkjet || ijet == lljet) continue;
                          tmpdijetindex[tmpcount] = ijet;
                          tmpcount++;
                          }
                          if((JetPFCor_bDiscriminatorCSV[tmpdijetindex[0]] < btcsvl || JetPFCor_bDiscriminatorCSV[tmpdijetindex[1]] < btcsvl)) continue;
                         */
                        //#####################At least Three CSVL Btag Method, Remove the Btag Veto Requirement########################################################
                        //#####################Four CSVL Btag Method, Remove the Btag Veto Requirement########################################################
                        /*if((JetPFCor_bDiscriminatorCSV[iijet] < btcsvl || JetPFCor_bDiscriminatorCSV[lljet] < btcsvl)) continue;
                          Int_t tmpdijetindex[2] = {-1, -1};
                          Int_t tmpcount = 0;
                          for(Int_t ijet = 0; ijet < njet; ijet++)
                          {
                          if(ijet == iijet || ijet == jjjet || ijet == kkjet || ijet == lljet) continue;
                          tmpdijetindex[tmpcount] = ijet;
                          tmpcount++;
                          }
                          if((JetPFCor_bDiscriminatorCSV[tmpdijetindex[0]] < btcsvl || JetPFCor_bDiscriminatorCSV[tmpdijetindex[1]] < btcsvl)) continue;
                         */
                        //#####################Four CSVL Btag Method, Remove the Btag Veto Requirement########################################################
                        //#####################==Three CSVL Btag Method, Remove the Btag Veto Requirement########################################################
                        /*if((JetPFCor_bDiscriminatorCSV[iijet] < btcsvl && JetPFCor_bDiscriminatorCSV[lljet] < btcsvl) || (JetPFCor_bDiscriminatorCSV[iijet] > btcsvl && JetPFCor_bDiscriminatorCSV[lljet] > btcsvl)) continue;
                          Int_t tmpdijetindex[2] = {-1, -1};
                          Int_t tmpcount = 0;
                          for(Int_t ijet = 0; ijet < njet; ijet++)
                          {
                          if(ijet == iijet || ijet == jjjet || ijet == kkjet || ijet == lljet) continue;
                          tmpdijetindex[tmpcount] = ijet;
                          tmpcount++;
                          }
                          if((JetPFCor_bDiscriminatorCSV[tmpdijetindex[0]] < btcsvl || JetPFCor_bDiscriminatorCSV[tmpdijetindex[1]] < btcsvl)) continue;
                         */
                        //#####################==Three CSVL Btag Method, Remove the Btag Veto Requirement########################################################
                        //#####################==Three CSVL Btag Method, but don't require two extra jets should be csvl btag jets, Remove the Btag Veto Requirement########################################################
                        Int_t tmpdijetindex[2] = {-1, -1};
                        Int_t tmpcount = 0;
                        for(Int_t ijet = 0; ijet < njet; ijet++)
                        {
                           if(ijet == iijet || ijet == jjjet || ijet == kkjet || ijet == lljet) continue;
                           tmpdijetindex[tmpcount] = ijet;
                           tmpcount++;
                        }
                        Int_t tmpnbtagcount = 0;
                        if(JetPFCor_bDiscriminatorCSV[iijet] > btcsvl) tmpnbtagcount++;
                        if(JetPFCor_bDiscriminatorCSV[lljet] > btcsvl) tmpnbtagcount++;
                        if(JetPFCor_bDiscriminatorCSV[tmpdijetindex[0]] > btcsvl) tmpnbtagcount++;
                        if(JetPFCor_bDiscriminatorCSV[tmpdijetindex[1]] > btcsvl) tmpnbtagcount++;
                        if(tmpnbtagcount != 3) continue;
                        //#####################==Three CSVL Btag Method, Remove the Btag Veto Requirement########################################################
                        //TLorentzVector tmpleptop = mup + nvp + jetsp4[iijet];
                        //TLorentzVector tmpvv = jetsp4[jjjet] + jetsp4[kkjet];
                        //Double_t tmpmass = tmpvv.M();
                        //TLorentzVector tmptop = jetsp4[jjjet] + jetsp4[kkjet] + jetsp4[lljet];
                        //Double_t tmptopmass = tmptop.M();
                        //Double_t reconstructionchi2 = TMath::Abs(tmpleptop.M() - 172.5) * TMath::Abs(tmpleptop.M() - 172.5) /lepsigma2 + TMath::Abs(tmpmass - 80.4) * TMath::Abs(tmpmass - 80.4)/sigma2 + TMath::Abs(tmptopmass - 172.5) * TMath::Abs(tmptopmass - 172.5)/sigma2top;
                        Float_t reconstructionchi2 = 0.;
                        Int_t tmpfitstatus = -1;
                        Int_t tmpfitNDF = -1;
                        dottHKinematicFit(mup, b_nvp, jetsp4[jjjet], jetsp4[kkjet], jetsp4[iijet], jetsp4[lljet], reconstructionchi2, tmpfitNDF, tmpfitstatus);
                        if(tmpfitstatus != 0) continue;
                        if( smallestfitchi2 > reconstructionchi2){
                           smallestfitchi2 = reconstructionchi2;
                           smallestfitstatus = tmpfitstatus;
                           smallestfitNDF = tmpfitNDF;
                           topjetindex[0] = iijet;
                           topjetindex[1] = jjjet;
                           topjetindex[2] = kkjet;
                           topjetindex[3] = lljet;
                        }
                     }
                  }
               }
            }

            Int_t icount = 0;
            if(topjetindex[0] != -1 && topjetindex[1] != -1 && topjetindex[2] != -1 && topjetindex[3] != -1)
            {
               toplvj_aj_p.SetPtEtaPhiE(jess * JetPFCor_Pt[topjetindex[0]], JetPFCor_Eta[topjetindex[0]], JetPFCor_Phi[topjetindex[0]], jess * JetPFCor_E[topjetindex[0]]);
               waj_p.SetPtEtaPhiE(jess * JetPFCor_Pt[topjetindex[1]], JetPFCor_Eta[topjetindex[1]], JetPFCor_Phi[topjetindex[1]], jess * JetPFCor_E[topjetindex[1]]); 
               wbj_p.SetPtEtaPhiE(jess * JetPFCor_Pt[topjetindex[2]], JetPFCor_Eta[topjetindex[2]], JetPFCor_Phi[topjetindex[2]], jess * JetPFCor_E[topjetindex[2]]); 
               topjjj_aj_p.SetPtEtaPhiE(jess * JetPFCor_Pt[topjetindex[3]], JetPFCor_Eta[topjetindex[3]], JetPFCor_Phi[topjetindex[3]], jess * JetPFCor_E[topjetindex[3]]);
               wjj_p = waj_p +  wbj_p;
               toplvj_p = wlv_p + toplvj_aj_p;
               topjjj_p = wjj_p + topjjj_aj_p;
               ditop_p = toplvj_p + topjjj_p;

               for(Int_t ijet = 0; ijet < njet; ijet++)
               {
                  if(ijet == topjetindex[0] || ijet == topjetindex[1] || ijet == topjetindex[2] || ijet == topjetindex[3]) continue;
                  dijetindex[icount] = ijet;
                  icount++;
               }
            }

            if(dijetindex[0] != -1 && dijetindex[1] != -1 && topjetindex[0] != -1 && topjetindex[1] != -1 && topjetindex[2] != -1 && topjetindex[3] != -1)
            {
               dijetaj_p.SetPtEtaPhiE(jess * JetPFCor_Pt[dijetindex[0]], JetPFCor_Eta[dijetindex[0]], JetPFCor_Phi[dijetindex[0]], jess * JetPFCor_E[dijetindex[0]]);
               dijetbj_p.SetPtEtaPhiE(jess * JetPFCor_Pt[dijetindex[1]], JetPFCor_Eta[dijetindex[1]], JetPFCor_Phi[dijetindex[1]], jess * JetPFCor_E[dijetindex[1]]);
               dijet_p = dijetaj_p + dijetbj_p;

               ttH_event = 1;

               ttH_fitchi2 = smallestfitchi2;
               ttH_fitstatus = smallestfitstatus;
               ttH_fitNDF = smallestfitNDF;

               //Fill the value we want to store
               ttH_waj_id = topjetindex[1];
               ttH_wbj_id = topjetindex[2];
               ttH_toplvj_aj_id = topjetindex[0];
               ttH_topjjj_aj_id = topjetindex[3];
               ttH_dijetaj_id = dijetindex[0];
               ttH_dijetbj_id = dijetindex[1];

               //Kinenamatic variables
               //leptonic W
               ttH_wlv_e   =  wlv_p.E();
               ttH_wlv_pt  =  wlv_p.Pt();
               ttH_wlv_eta =  wlv_p.Eta();
               ttH_wlv_phi =  wlv_p.Phi();
               ttH_wlv_m   =  wlv_p.M();

               //hadronic W 
               ttH_waj_e   =  waj_p.E();
               ttH_waj_pt  =  waj_p.Pt();
               ttH_waj_eta =  waj_p.Eta();
               ttH_waj_phi =  waj_p.Phi();
               ttH_waj_m   =  waj_p.M();

               ttH_wbj_e   =  wbj_p.E();
               ttH_wbj_pt  =  wbj_p.Pt();
               ttH_wbj_eta =  wbj_p.Eta();
               ttH_wbj_phi =  wbj_p.Phi();
               ttH_wbj_m   =  wbj_p.M();

               ttH_wjj_e   =  wjj_p.E();
               ttH_wjj_pt  =  wjj_p.Pt();
               ttH_wjj_eta =  wjj_p.Eta();
               ttH_wjj_phi =  wjj_p.Phi();
               ttH_wjj_m   =  wjj_p.M();

               //Top
               ttH_toplvj_aj_e   = toplvj_aj_p.E();
               ttH_toplvj_aj_pt  = toplvj_aj_p.Pt();
               ttH_toplvj_aj_eta = toplvj_aj_p.Eta();
               ttH_toplvj_aj_phi = toplvj_aj_p.Phi();
               ttH_toplvj_aj_m   = toplvj_aj_p.M();
               ttH_toplvj_aj_btagcsv = JetPFCor_bDiscriminatorCSV[ttH_toplvj_aj_id];;

               ttH_topjjj_aj_e   = topjjj_aj_p.E();
               ttH_topjjj_aj_pt  = topjjj_aj_p.Pt();
               ttH_topjjj_aj_eta = topjjj_aj_p.Eta();
               ttH_topjjj_aj_phi = topjjj_aj_p.Phi();
               ttH_topjjj_aj_m   = topjjj_aj_p.M();
               ttH_topjjj_aj_btagcsv = JetPFCor_bDiscriminatorCSV[ttH_topjjj_aj_id];;

               ttH_toplvj_e   = toplvj_p.E();
               ttH_toplvj_pt  = toplvj_p.Pt();
               ttH_toplvj_eta = toplvj_p.Eta();
               ttH_toplvj_phi = toplvj_p.Phi();
               ttH_toplvj_m   = toplvj_p.M();

               ttH_topjjj_e   = topjjj_p.E();
               ttH_topjjj_pt  = topjjj_p.Pt();
               ttH_topjjj_eta = topjjj_p.Eta();
               ttH_topjjj_phi = topjjj_p.Phi();
               ttH_topjjj_m   = topjjj_p.M();

               //ditop
               ttH_ditop_e   = ditop_p.E();
               ttH_ditop_pt  = ditop_p.Pt();
               ttH_ditop_eta = ditop_p.Eta();
               ttH_ditop_phi = ditop_p.Phi();
               ttH_ditop_m   = ditop_p.M();
               ttH_ditop_y   = ditop_p.Rapidity();

               //Extral Jet to formulate the Z or H
               ttH_dijetaj_e   = dijetaj_p.E();
               ttH_dijetaj_pt  = dijetaj_p.Pt();
               ttH_dijetaj_eta = dijetaj_p.Eta();
               ttH_dijetaj_phi = dijetaj_p.Phi();
               ttH_dijetaj_m   = dijetaj_p.M();
               ttH_dijetaj_btagcsv = JetPFCor_bDiscriminatorCSV[ttH_dijetaj_id];

               ttH_dijetbj_e   = dijetbj_p.E();
               ttH_dijetbj_pt  = dijetbj_p.Pt();
               ttH_dijetbj_eta = dijetbj_p.Eta();
               ttH_dijetbj_phi = dijetbj_p.Phi();
               ttH_dijetbj_m   = dijetbj_p.M();
               ttH_dijetbj_btagcsv = JetPFCor_bDiscriminatorCSV[ttH_dijetbj_id];

               //DeltaR and DeltaPhi of dijet system
               ttH_dijetajbj_deltaR   = dijetaj_p.DeltaR(dijetbj_p);
               ttH_dijetajbj_deltaphi = getDeltaPhi(dijetaj_p.Phi(),dijetbj_p.Phi());

               ttH_dijet_e   = dijet_p.E();
               ttH_dijet_pt  = dijet_p.Pt();
               ttH_dijet_eta = dijet_p.Eta();
               ttH_dijet_phi = dijet_p.Phi();
               ttH_dijet_m   = dijet_p.M();
               ttH_dijet_y   = dijet_p.Rapidity();

               //DeltaR and DeltaPhi of Top and Anti-top and dijet subjet
               ttH_toplvjdijetaj_deltaR = toplvj_p.DeltaR(dijetaj_p);
               ttH_toplvjdijetaj_deltaphi = getDeltaPhi(toplvj_p.Phi(),dijetaj_p.Phi());

               ttH_topjjjdijetaj_deltaR = topjjj_p.DeltaR(dijetaj_p);
               ttH_topjjjdijetaj_deltaphi = getDeltaPhi(topjjj_p.Phi(),dijetaj_p.Phi());

               ttH_toplvjdijetbj_deltaR = toplvj_p.DeltaR(dijetbj_p);
               ttH_toplvjdijetbj_deltaphi = getDeltaPhi(toplvj_p.Phi(),dijetbj_p.Phi());

               ttH_topjjjdijetbj_deltaR = topjjj_p.DeltaR(dijetbj_p);
               ttH_topjjjdijetbj_deltaphi = getDeltaPhi(topjjj_p.Phi(),dijetbj_p.Phi());

               //DeltaR and DeltaPhi of TTbar and dijet
               ttH_topjjjdijet_deltaR = topjjj_p.DeltaR(dijet_p);
               ttH_topjjjdijet_deltaphi = getDeltaPhi(topjjj_p.Phi(),dijet_p.Phi());

               ttH_toplvjdijet_deltaR = toplvj_p.DeltaR(dijet_p);
               ttH_toplvjdijet_deltaphi = getDeltaPhi(toplvj_p.Phi(),dijet_p.Phi());

               ttH_ditopdijet_deltaR   = ditop_p.DeltaR(dijet_p);
               ttH_ditopdijet_deltaphi = getDeltaPhi(ditop_p.Phi(),dijet_p.Phi());
            }
         }
      }

      branch_ggdevt->Fill();
      branch_evtNJ ->Fill();
      branch_ggdevtinclusive->Fill();

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

      branch_TopWm->Fill();
      branch_TopWm5j->Fill();
      branch_Tchi2->Fill();
      branch_Tchi25j->Fill();

      branch_ha->Fill();   
      branch_hb->Fill();   
      branch_hs->Fill();  
      branch_phi->Fill(); 
      branch_phia->Fill();
      branch_phib->Fill();
      branch_orgm->Fill();
      branch_orgpt->Fill();
      branch_orgy->Fill();
      branch_orgph->Fill();

      branch_2j160mu->Fill();
      branch_2j170mu->Fill();
      branch_2j180mu->Fill();
      branch_2j190mu->Fill();
      branch_2j200mu->Fill();
      branch_2j250mu->Fill();
      branch_2j300mu->Fill();
      branch_2j350mu->Fill();
      branch_2j400mu->Fill();
      branch_2j450mu->Fill();
      branch_2j500mu->Fill();
      branch_2j550mu->Fill();
      branch_2j600mu->Fill();
      branch_2j400interferencenominalmu->Fill();
      branch_2j450interferencenominalmu->Fill();
      branch_2j500interferencenominalmu->Fill();
      branch_2j550interferencenominalmu->Fill();
      branch_2j600interferencenominalmu->Fill();
      branch_2j700interferencenominalmu->Fill();
      branch_2j800interferencenominalmu->Fill();
      branch_2j900interferencenominalmu->Fill();
      branch_2j1000interferencenominalmu->Fill();
      branch_2j400interferencedownmu->Fill();
      branch_2j450interferencedownmu->Fill();
      branch_2j500interferencedownmu->Fill();
      branch_2j550interferencedownmu->Fill();
      branch_2j600interferencedownmu->Fill();
      branch_2j700interferencedownmu->Fill();
      branch_2j800interferencedownmu->Fill();
      branch_2j900interferencedownmu->Fill();
      branch_2j1000interferencedownmu->Fill();
      branch_2j400interferenceupmu->Fill();
      branch_2j450interferenceupmu->Fill();
      branch_2j500interferenceupmu->Fill();
      branch_2j550interferenceupmu->Fill();
      branch_2j600interferenceupmu->Fill();
      branch_2j700interferenceupmu->Fill();
      branch_2j800interferenceupmu->Fill();
      branch_2j900interferenceupmu->Fill();
      branch_2j1000interferenceupmu->Fill();

      branch_3j160mu->Fill();
      branch_3j170mu->Fill();
      branch_3j180mu->Fill();
      branch_3j190mu->Fill();
      branch_3j200mu->Fill();
      branch_3j250mu->Fill();
      branch_3j300mu->Fill();
      branch_3j350mu->Fill();
      branch_3j400mu->Fill();
      branch_3j450mu->Fill();
      branch_3j500mu->Fill();
      branch_3j550mu->Fill();
      branch_3j600mu->Fill();
      branch_3j400interferencenominalmu->Fill();
      branch_3j450interferencenominalmu->Fill();
      branch_3j500interferencenominalmu->Fill();
      branch_3j550interferencenominalmu->Fill();
      branch_3j600interferencenominalmu->Fill();
      branch_3j700interferencenominalmu->Fill();
      branch_3j800interferencenominalmu->Fill();
      branch_3j900interferencenominalmu->Fill();
      branch_3j1000interferencenominalmu->Fill();
      branch_3j400interferencedownmu->Fill();
      branch_3j450interferencedownmu->Fill();
      branch_3j500interferencedownmu->Fill();
      branch_3j550interferencedownmu->Fill();
      branch_3j600interferencedownmu->Fill();
      branch_3j700interferencedownmu->Fill();
      branch_3j800interferencedownmu->Fill();
      branch_3j900interferencedownmu->Fill();
      branch_3j1000interferencedownmu->Fill();
      branch_3j400interferenceupmu->Fill();
      branch_3j450interferenceupmu->Fill();
      branch_3j500interferenceupmu->Fill();
      branch_3j550interferenceupmu->Fill();
      branch_3j600interferenceupmu->Fill();
      branch_3j700interferenceupmu->Fill();
      branch_3j800interferenceupmu->Fill();
      branch_3j900interferenceupmu->Fill();
      branch_3j1000interferenceupmu->Fill();

      branch_2jdibosonmu->Fill();
      branch_3jdibosonmu->Fill();
      branch_2jdibnoqgmu->Fill();
      branch_3jdibnoqgmu->Fill();

      branch_vbf160mu->Fill();
      branch_vbf170mu->Fill();
      branch_vbf180mu->Fill();
      branch_vbf190mu->Fill();
      branch_vbf200mu->Fill();
      branch_vbf250mu->Fill();
      branch_vbf300mu->Fill();
      branch_vbf350mu->Fill();
      branch_vbf400mu->Fill();
      branch_vbf450mu->Fill();
      branch_vbf500mu->Fill();
      branch_vbf550mu->Fill();
      branch_vbf600mu->Fill();

      branch_effwt->Fill();
      branch_puwt->Fill();
      branch_puwt_up->Fill();
      branch_puwt_down->Fill();

      branch_interferencewtggH400->Fill();
      branch_interferencewtggH450->Fill();
      branch_interferencewtggH500->Fill();
      branch_interferencewtggH550->Fill();
      branch_interferencewtggH600->Fill();
      branch_interferencewtggH700->Fill();
      branch_interferencewtggH800->Fill();
      branch_interferencewtggH900->Fill();
      branch_interferencewtggH1000->Fill();

      branch_interferencewt_upggH400->Fill();
      branch_interferencewt_upggH450->Fill();
      branch_interferencewt_upggH500->Fill();
      branch_interferencewt_upggH550->Fill();
      branch_interferencewt_upggH600->Fill();
      branch_interferencewt_upggH700->Fill();
      branch_interferencewt_upggH800->Fill();
      branch_interferencewt_upggH900->Fill();
      branch_interferencewt_upggH1000->Fill();

      branch_interferencewt_downggH400->Fill();
      branch_interferencewt_downggH450->Fill();
      branch_interferencewt_downggH500->Fill();
      branch_interferencewt_downggH550->Fill();
      branch_interferencewt_downggH600->Fill();
      branch_interferencewt_downggH700->Fill();
      branch_interferencewt_downggH800->Fill();
      branch_interferencewt_downggH900->Fill();
      branch_interferencewt_downggH1000->Fill();

      branch_complexpolewtggH180->Fill();
      branch_complexpolewtggH190->Fill();
      branch_complexpolewtggH200->Fill();
      branch_complexpolewtggH250->Fill();
      branch_complexpolewtggH300->Fill();
      branch_complexpolewtggH350->Fill();
      branch_complexpolewtggH400->Fill();
      branch_complexpolewtggH450->Fill();
      branch_complexpolewtggH500->Fill();
      branch_complexpolewtggH550->Fill();
      branch_complexpolewtggH600->Fill();
      branch_complexpolewtggH700->Fill();
      branch_complexpolewtggH800->Fill();
      branch_complexpolewtggH900->Fill();
      branch_complexpolewtggH1000->Fill();

      branch_avecomplexpolewtggH180->Fill();
      branch_avecomplexpolewtggH190->Fill();
      branch_avecomplexpolewtggH200->Fill();
      branch_avecomplexpolewtggH250->Fill();
      branch_avecomplexpolewtggH300->Fill();
      branch_avecomplexpolewtggH350->Fill();
      branch_avecomplexpolewtggH400->Fill();
      branch_avecomplexpolewtggH450->Fill();
      branch_avecomplexpolewtggH500->Fill();
      branch_avecomplexpolewtggH550->Fill();
      branch_avecomplexpolewtggH600->Fill();
      branch_avecomplexpolewtggH700->Fill();
      branch_avecomplexpolewtggH800->Fill();
      branch_avecomplexpolewtggH900->Fill();
      branch_avecomplexpolewtggH1000->Fill();

      branch_qgld_Spring11->Fill();
      branch_qgld_Summer11->Fill();
      branch_qgld_Summer11CHS->Fill();

      branch_vbf_jj_e->Fill();
      branch_vbf_jj_pt->Fill();
      branch_vbf_jj_eta->Fill();
      branch_vbf_jj_phi->Fill();
      branch_vbf_jj_m->Fill();

      branch_vbf_aj_e->Fill();
      branch_vbf_aj_pt->Fill();
      branch_vbf_aj_eta->Fill();
      branch_vbf_aj_phi->Fill();
      branch_vbf_aj_m->Fill();

      branch_vbf_bj_e->Fill();
      branch_vbf_bj_pt->Fill();
      branch_vbf_bj_eta->Fill();
      branch_vbf_bj_phi->Fill();
      branch_vbf_bj_m->Fill();

      branch_vbf_jj_deta->Fill();
      branch_vbf_jj_dphi->Fill();
      branch_vbf_jj_type->Fill();
      branch_vbf_n_excj->Fill();
      branch_vbf_n_exfj->Fill();
      branch_vbf_n_gdjj->Fill();

      branch_vbf_wjj_e->Fill();
      branch_vbf_wjj_pt->Fill();
      branch_vbf_wjj_eta->Fill();
      branch_vbf_wjj_phi->Fill();
      branch_vbf_wjj_m->Fill();

      branch_vbf_aj_bj_Wjj_jetnumber->Fill();
      branch_vbf_waj_wbj_jetnumber->Fill();
      branch_vbf_lvwajbj_ajbj_dphi->Fill();
      branch_vbf_lvwajbj_ajbj_deta->Fill();

      branch_vbf_waj_e->Fill();
      branch_vbf_waj_pt->Fill();
      branch_vbf_waj_eta->Fill();
      branch_vbf_waj_phi->Fill();
      branch_vbf_waj_m->Fill();

      branch_vbf_wbj_e->Fill();
      branch_vbf_wbj_pt->Fill();
      branch_vbf_wbj_eta->Fill();
      branch_vbf_wbj_phi->Fill();
      branch_vbf_wbj_m->Fill();

      branch_vbf_lvjj_e->Fill();
      branch_vbf_lvjj_pt->Fill();
      branch_vbf_lvjj_eta->Fill();
      branch_vbf_lvjj_phi->Fill();
      branch_vbf_lvjj_m->Fill();
      branch_vbf_lvjj_y->Fill();

      branch_vbf_event->Fill();
      branch_vbf_aj_id->Fill();
      branch_vbf_bj_id->Fill();
      branch_vbf_waj_id->Fill();
      branch_vbf_wbj_id->Fill();

      branch_vbf_wjj_ang_ha->Fill();
      branch_vbf_wjj_ang_hb->Fill();
      branch_vbf_wjj_ang_hs->Fill();
      branch_vbf_wjj_ang_phi->Fill();
      branch_vbf_wjj_ang_phia->Fill();
      branch_vbf_wjj_ang_phib->Fill();

      //VBF di-boson Event
      branch_vbf_diboson_event->Fill();
      branch_vbf_diboson_deltaeta_Wjj->Fill();
      branch_vbf_diboson_deltaphi_MET_leadingWjet->Fill();
      branch_vbf_diboson_dijetpt->Fill();

      //Boosted W Fill
      branch_isgengdboostedWevt->Fill();
      branch_ggdboostedWevt->Fill();
      branch_GroomedJet_CA8_deltaR_lca8jet->Fill();
      branch_GroomedJet_CA8_deltaphi_METca8jet->Fill();
      branch_GroomedJet_CA8_deltaphi_Vca8jet->Fill();
      branch_GroomedJet_numberbjets_csvl->Fill();
      branch_GroomedJet_numberbjets_csvm->Fill();
      branch_GroomedJet_numberbjets_ssvhem->Fill();
      branch_GroomedJet_numberbjets_csvl_veto->Fill();
      branch_GroomedJet_numberbjets_csvm_veto->Fill();
      branch_GroomedJet_numberbjets_ssvhem_veto->Fill();
      branch_GroomedJet_numberjets->Fill();
      branch_GroomedJet_CA8_rcores01->Fill();
      branch_GroomedJet_CA8_rcores02->Fill();
      branch_GroomedJet_CA8_rcores03->Fill();
      branch_GroomedJet_CA8_rcores04->Fill();
      branch_GroomedJet_CA8_rcores05->Fill();
      branch_GroomedJet_CA8_rcores06->Fill();
      branch_GroomedJet_CA8_rcores07->Fill();
      branch_GroomedJet_CA8_rcores08->Fill();
      branch_GroomedJet_CA8_rcores09->Fill();
      branch_GroomedJet_CA8_rcores10->Fill();
      branch_GroomedJet_CA8_rcores11->Fill();

      branch_GroomedJet_CA8_ptcores01->Fill();
      branch_GroomedJet_CA8_ptcores02->Fill();
      branch_GroomedJet_CA8_ptcores03->Fill();
      branch_GroomedJet_CA8_ptcores04->Fill();
      branch_GroomedJet_CA8_ptcores05->Fill();
      branch_GroomedJet_CA8_ptcores06->Fill();
      branch_GroomedJet_CA8_ptcores07->Fill();
      branch_GroomedJet_CA8_ptcores08->Fill();
      branch_GroomedJet_CA8_ptcores09->Fill();
      branch_GroomedJet_CA8_ptcores10->Fill();
      branch_GroomedJet_CA8_ptcores11->Fill();

      branch_GroomedJet_CA8_planarflow01->Fill();
      branch_GroomedJet_CA8_planarflow02->Fill();
      branch_GroomedJet_CA8_planarflow03->Fill();
      branch_GroomedJet_CA8_planarflow04->Fill();
      branch_GroomedJet_CA8_planarflow05->Fill();
      branch_GroomedJet_CA8_planarflow06->Fill();
      branch_GroomedJet_CA8_planarflow07->Fill();
      branch_GroomedJet_CA8_planarflow08->Fill();
      branch_GroomedJet_CA8_planarflow09->Fill();
      branch_GroomedJet_CA8_planarflow10->Fill();
      branch_GroomedJet_CA8_planarflow11->Fill();

      branch_GroomedJet_CA8_mass_sensi_tr->Fill();
      branch_GroomedJet_CA8_mass_sensi_ft->Fill();
      branch_GroomedJet_CA8_mass_sensi_pr->Fill();

      branch_GroomedJet_CA8_qjetmassvolatility->Fill();

      branch_GroomedJet_CA8_prsubjet1ptoverjetpt->Fill();
      branch_GroomedJet_CA8_prsubjet2ptoverjetpt->Fill();
      branch_GroomedJet_CA8_prsubjet1subjet2_deltaR->Fill();

      branch_boostedW_lvj_e->Fill();
      branch_boostedW_lvj_pt->Fill();
      branch_boostedW_lvj_eta->Fill();
      branch_boostedW_lvj_phi->Fill();
      branch_boostedW_lvj_m->Fill();
      branch_boostedW_lvj_y->Fill();

      branch_boostedW_wjj_ang_ha->Fill();
      branch_boostedW_wjj_ang_hb->Fill();
      branch_boostedW_wjj_ang_hs->Fill();
      branch_boostedW_wjj_ang_phi->Fill();
      branch_boostedW_wjj_ang_phia->Fill();
      branch_boostedW_wjj_ang_phib->Fill();

      //AK7 Jet Algorithm
      branch_ggdboostedWevt_ak7->Fill();
      branch_GroomedJet_AK7_deltaR_lak7jet->Fill();
      branch_GroomedJet_AK7_deltaphi_METak7jet->Fill();
      branch_GroomedJet_AK7_deltaphi_Vak7jet->Fill();
      branch_GroomedJet_numberbjets_csvl_ak7->Fill();
      branch_GroomedJet_numberbjets_csvm_ak7->Fill();
      branch_GroomedJet_numberbjets_ssvhem_ak7->Fill();
      branch_GroomedJet_numberbjets_csvl_veto_ak7->Fill();
      branch_GroomedJet_numberbjets_csvm_veto_ak7->Fill();
      branch_GroomedJet_numberbjets_ssvhem_veto_ak7->Fill();
      branch_GroomedJet_numberjets_ak7->Fill();
      branch_GroomedJet_AK7_rcores01->Fill();
      branch_GroomedJet_AK7_rcores02->Fill();
      branch_GroomedJet_AK7_rcores03->Fill();
      branch_GroomedJet_AK7_rcores04->Fill();
      branch_GroomedJet_AK7_rcores05->Fill();
      branch_GroomedJet_AK7_rcores06->Fill();
      branch_GroomedJet_AK7_rcores07->Fill();
      branch_GroomedJet_AK7_rcores08->Fill();
      branch_GroomedJet_AK7_rcores09->Fill();
      branch_GroomedJet_AK7_rcores10->Fill();
      branch_GroomedJet_AK7_rcores11->Fill();

      branch_GroomedJet_AK7_ptcores01->Fill();
      branch_GroomedJet_AK7_ptcores02->Fill();
      branch_GroomedJet_AK7_ptcores03->Fill();
      branch_GroomedJet_AK7_ptcores04->Fill();
      branch_GroomedJet_AK7_ptcores05->Fill();
      branch_GroomedJet_AK7_ptcores06->Fill();
      branch_GroomedJet_AK7_ptcores07->Fill();
      branch_GroomedJet_AK7_ptcores08->Fill();
      branch_GroomedJet_AK7_ptcores09->Fill();
      branch_GroomedJet_AK7_ptcores10->Fill();
      branch_GroomedJet_AK7_ptcores11->Fill();

      branch_GroomedJet_AK7_planarflow01->Fill();
      branch_GroomedJet_AK7_planarflow02->Fill();
      branch_GroomedJet_AK7_planarflow03->Fill();
      branch_GroomedJet_AK7_planarflow04->Fill();
      branch_GroomedJet_AK7_planarflow05->Fill();
      branch_GroomedJet_AK7_planarflow06->Fill();
      branch_GroomedJet_AK7_planarflow07->Fill();
      branch_GroomedJet_AK7_planarflow08->Fill();
      branch_GroomedJet_AK7_planarflow09->Fill();
      branch_GroomedJet_AK7_planarflow10->Fill();
      branch_GroomedJet_AK7_planarflow11->Fill();

      branch_GroomedJet_AK7_mass_sensi_tr->Fill();
      branch_GroomedJet_AK7_mass_sensi_ft->Fill();
      branch_GroomedJet_AK7_mass_sensi_pr->Fill();

      branch_GroomedJet_AK7_qjetmassvolatility->Fill();

      branch_GroomedJet_AK7_prsubjet1ptoverjetpt->Fill();
      branch_GroomedJet_AK7_prsubjet2ptoverjetpt->Fill();
      branch_GroomedJet_AK7_prsubjet1subjet2_deltaR->Fill();

      branch_boostedW_lvj_e_ak7->Fill();
      branch_boostedW_lvj_pt_ak7->Fill();
      branch_boostedW_lvj_eta_ak7->Fill();
      branch_boostedW_lvj_phi_ak7->Fill();
      branch_boostedW_lvj_m_ak7->Fill();
      branch_boostedW_lvj_y_ak7->Fill();

      branch_boostedW_wjj_ang_ha_ak7->Fill();
      branch_boostedW_wjj_ang_hb_ak7->Fill();
      branch_boostedW_wjj_ang_hs_ak7->Fill();
      branch_boostedW_wjj_ang_phi_ak7->Fill();
      branch_boostedW_wjj_ang_phia_ak7->Fill();
      branch_boostedW_wjj_ang_phib_ak7->Fill();

      //EWK W+2jets Analysis
      branch_EWK_W_2jets_event->Fill();

      branch_EWK_W_2jets_tagjet1_pt->Fill();
      branch_EWK_W_2jets_tagjet1_eta->Fill();
      branch_EWK_W_2jets_tagjet1_phi->Fill();
      branch_EWK_W_2jets_tagjet1_e->Fill();
      branch_EWK_W_2jets_tagjet1_m->Fill();
      branch_EWK_W_2jets_tagjet2_pt->Fill();
      branch_EWK_W_2jets_tagjet2_eta->Fill();
      branch_EWK_W_2jets_tagjet2_phi->Fill();
      branch_EWK_W_2jets_tagjet2_e->Fill();
      branch_EWK_W_2jets_tagjet2_m->Fill();

      branch_EWK_W_2jets_tagjet_etasign->Fill();
      branch_EWK_W_2jets_tagjet_deltaeta->Fill();
      branch_EWK_W_2jets_tagjet_sumeta->Fill();
      branch_EWK_W_2jets_tagjet_deltaphi->Fill(); 
      branch_EWK_W_2jets_tagjet_deltaR->Fill(); 
      branch_EWK_W_2jets_tagjet_mass->Fill(); 

      branch_EWK_W_2jets_l_pt->Fill();
      branch_EWK_W_2jets_l_eta->Fill();
      branch_EWK_W_2jets_l_phi->Fill();
      branch_EWK_W_2jets_l_e->Fill();
      branch_EWK_W_2jets_l_MET_deltaphi->Fill();

      branch_EWK_W_2jets_l_tagjet1_deltaeta->Fill();
      branch_EWK_W_2jets_l_tagjet1_deltaphi->Fill();
      branch_EWK_W_2jets_l_tagjet1_deltaR->Fill();
      branch_EWK_W_2jets_l_tagjet2_deltaeta->Fill();
      branch_EWK_W_2jets_l_tagjet2_deltaphi->Fill();
      branch_EWK_W_2jets_l_tagjet2_deltaR->Fill();

      branch_EWK_W_2jets_W_pt->Fill();
      branch_EWK_W_2jets_W_rap->Fill();
      branch_EWK_W_2jets_W_eta->Fill();
      branch_EWK_W_2jets_W_phi->Fill();
      branch_EWK_W_2jets_W_e->Fill();
      branch_EWK_W_2jets_W_mT->Fill();

      branch_EWK_W_2jets_W_tagjet1_deltaphi->Fill();
      branch_EWK_W_2jets_W_tagjet1_deltaeta->Fill();
      branch_EWK_W_2jets_W_tagjet1_deltaR->Fill();
      branch_EWK_W_2jets_W_tagjet2_deltaphi->Fill();
      branch_EWK_W_2jets_W_tagjet2_deltaeta->Fill();
      branch_EWK_W_2jets_W_tagjet2_deltaR->Fill();

      branch_EWK_W_2jets_W_tagjet_Zeppenfield->Fill();

      branch_EWK_W_2jets_centraljetnum_20->Fill();
      branch_EWK_W_2jets_centraljetnum_25->Fill();
      branch_EWK_W_2jets_centraljetnum_30->Fill();

      branch_EWK_W_2jets_findcentraljet->Fill();

      branch_EWK_W_2jets_centraljet_pt->Fill();
      branch_EWK_W_2jets_centraljet_eta->Fill();
      branch_EWK_W_2jets_centraljet_phi->Fill();
      branch_EWK_W_2jets_centraljet_e->Fill();
      branch_EWK_W_2jets_centraljet_m->Fill();

      branch_EWK_W_2jets_centraljet_tagjet1_deltaeta->Fill();
      branch_EWK_W_2jets_centraljet_tagjet1_deltaphi->Fill();
      branch_EWK_W_2jets_centraljet_tagjet1_deltaR->Fill();
      branch_EWK_W_2jets_centraljet_tagjet2_deltaeta->Fill();
      branch_EWK_W_2jets_centraljet_tagjet2_deltaphi->Fill();
      branch_EWK_W_2jets_centraljet_tagjet2_deltaR->Fill();

      branch_EWK_W_2jets_centraljet_tagjet_Zeppenfield->Fill();

      branch_EWK_W_2jets_tagjet1_QGd->Fill();
      branch_EWK_W_2jets_tagjet2_QGd->Fill();

      branch_EWK_W_2jets_tagjet1_btagCSV->Fill();
      branch_EWK_W_2jets_tagjet2_btagCSV->Fill();

      branch_EWK_W_2jets_genW_pt->Fill();
      branch_EWK_W_2jets_genW_eta->Fill();
      branch_EWK_W_2jets_genW_phi->Fill();
      branch_EWK_W_2jets_genW_e->Fill();

      branch_EWK_W_2jets_genTagquark1_pt->Fill();
      branch_EWK_W_2jets_genTagquark1_eta->Fill();
      branch_EWK_W_2jets_genTagquark1_phi->Fill();
      branch_EWK_W_2jets_genTagquark1_e->Fill();
      branch_EWK_W_2jets_genTagquark1_id->Fill();

      branch_EWK_W_2jets_genTagquark2_pt->Fill();
      branch_EWK_W_2jets_genTagquark2_eta->Fill();
      branch_EWK_W_2jets_genTagquark2_phi->Fill();
      branch_EWK_W_2jets_genTagquark2_e->Fill();
      branch_EWK_W_2jets_genTagquark2_id->Fill();

      branch_W_gen_numPartons->Fill();
      branch_W_nParton_weight->Fill();
      //End for EWK W+2jets Analysis

      //ttH Analysis
      branch_ttH_check_event->Fill();
      branch_ttH_event->Fill();
      branch_ttH_fitchi2->Fill();
      branch_ttH_fitstatus->Fill();
      branch_ttH_fitNDF->Fill();
      branch_ttH_waj_id->Fill();
      branch_ttH_wbj_id->Fill();
      branch_ttH_toplvj_aj_id->Fill();
      branch_ttH_topjjj_aj_id->Fill();
      branch_ttH_dijetaj_id->Fill();
      branch_ttH_dijetbj_id->Fill();

      branch_ttH_wlv_e->Fill();
      branch_ttH_wlv_pt->Fill();
      branch_ttH_wlv_eta->Fill();
      branch_ttH_wlv_phi->Fill();
      branch_ttH_wlv_m->Fill();

      branch_ttH_waj_e->Fill();
      branch_ttH_waj_pt->Fill();
      branch_ttH_waj_eta->Fill();
      branch_ttH_waj_phi->Fill();
      branch_ttH_waj_m->Fill();

      branch_ttH_wbj_e->Fill();
      branch_ttH_wbj_pt->Fill();
      branch_ttH_wbj_eta->Fill();
      branch_ttH_wbj_phi->Fill();
      branch_ttH_wbj_m->Fill();

      branch_ttH_wjj_e->Fill();
      branch_ttH_wjj_pt->Fill();
      branch_ttH_wjj_eta->Fill();
      branch_ttH_wjj_phi->Fill();
      branch_ttH_wjj_m->Fill();

      branch_ttH_topjjj_aj_e->Fill();
      branch_ttH_topjjj_aj_pt->Fill();
      branch_ttH_topjjj_aj_eta->Fill();
      branch_ttH_topjjj_aj_phi->Fill();
      branch_ttH_topjjj_aj_m->Fill();
      branch_ttH_topjjj_aj_btagcsv->Fill();

      branch_ttH_toplvj_aj_e->Fill();
      branch_ttH_toplvj_aj_pt->Fill();
      branch_ttH_toplvj_aj_eta->Fill();
      branch_ttH_toplvj_aj_phi->Fill();
      branch_ttH_toplvj_aj_m->Fill();
      branch_ttH_toplvj_aj_btagcsv->Fill();

      branch_ttH_topjjj_e->Fill();
      branch_ttH_topjjj_pt->Fill();
      branch_ttH_topjjj_eta->Fill();
      branch_ttH_topjjj_phi->Fill();
      branch_ttH_topjjj_m->Fill();

      branch_ttH_toplvj_e->Fill();
      branch_ttH_toplvj_pt->Fill();
      branch_ttH_toplvj_eta->Fill();
      branch_ttH_toplvj_phi->Fill();
      branch_ttH_toplvj_m->Fill();

      branch_ttH_dijetaj_e->Fill();
      branch_ttH_dijetaj_pt->Fill();
      branch_ttH_dijetaj_eta->Fill();
      branch_ttH_dijetaj_phi->Fill();
      branch_ttH_dijetaj_m->Fill();
      branch_ttH_dijetaj_btagcsv->Fill();

      branch_ttH_dijetbj_e->Fill();
      branch_ttH_dijetbj_pt->Fill();
      branch_ttH_dijetbj_eta->Fill();
      branch_ttH_dijetbj_phi->Fill();
      branch_ttH_dijetbj_m->Fill();
      branch_ttH_dijetbj_btagcsv->Fill();

      branch_ttH_dijetajbj_deltaR->Fill();
      branch_ttH_dijetajbj_deltaphi->Fill();

      branch_ttH_dijet_e->Fill();
      branch_ttH_dijet_pt->Fill();
      branch_ttH_dijet_eta->Fill();
      branch_ttH_dijet_phi->Fill();
      branch_ttH_dijet_m->Fill();
      branch_ttH_dijet_y->Fill();

      branch_ttH_ditop_e->Fill();
      branch_ttH_ditop_pt->Fill();
      branch_ttH_ditop_eta->Fill();
      branch_ttH_ditop_phi->Fill();
      branch_ttH_ditop_m->Fill();
      branch_ttH_ditop_y->Fill();

      branch_ttH_toplvjdijetaj_deltaR->Fill();
      branch_ttH_toplvjdijetaj_deltaphi->Fill();
      branch_ttH_topjjjdijetaj_deltaR->Fill();
      branch_ttH_topjjjdijetaj_deltaphi->Fill();
      branch_ttH_toplvjdijetbj_deltaR->Fill();
      branch_ttH_toplvjdijetbj_deltaphi->Fill();
      branch_ttH_topjjjdijetbj_deltaR->Fill();
      branch_ttH_topjjjdijetbj_deltaphi->Fill();

      branch_ttH_ditopdijet_deltaR->Fill();
      branch_ttH_ditopdijet_deltaphi->Fill();
      branch_ttH_toplvjdijet_deltaR->Fill();
      branch_ttH_toplvjdijet_deltaphi->Fill();
      branch_ttH_topjjjdijet_deltaR->Fill();
      branch_ttH_topjjjdijet_deltaphi->Fill();

   } // end event loop
   fresults.cd();
   newtree->Write("WJet",TObject::kOverwrite);
   h_events->Write();
   h_events_weighted->Write();
   delete newtree;
   fresults.Close();
   fclose(textfile);
   std::cout <<  wda << " Finish :: " << outfilename << "    "<< nentries  << std::endl;
}

double kanamuon::getDeltaPhi(double phi1, double phi2  )
{
   const double PI = 3.14159265;
   double result = phi1 - phi2;

   if(result > PI)
   {result = result - 2 * PI;}

   if(result <= (-1 * PI))
   {result = result + 2 * PI;}

   result = TMath::Abs(result);
   return result;
}

bool kanamuon::doKinematicFit(Int_t                 fflage,
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
   //TFitConstraintM *mCons1 = new TFitConstraintM( "WMassConstrainta", "WMass-Constrainta", 0, 0 , 80.4);
   mCons1->addParticles1( particle1, particle2 );

   TFitConstraintMGaus* mCons2 = new TFitConstraintMGaus( "W2MassConstraint", "W2Mass-Constraint", 0, 0 , 80.399, 2.085);
   //TFitConstraintM *mCons2 = new TFitConstraintM( "WMassConstraintb", "WMass-Constraintb", 0, 0 , 80.4);
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
}

void kanamuon::calculateAngles(TLorentzVector& thep4M11, TLorentzVector& thep4M12, TLorentzVector& thep4M21, TLorentzVector& thep4M22, double& costheta1, double& costheta2, double& phi, double& costhetastar, double& phistar1, double& phistar2){


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

   // calculate phi1, phi2, costhetastar
   ///phi1 = theZ1X_p3.Phi();
   ///phi2 = theZ2X_p3.Phi();

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
   /////TVector3 unitx_1 = -Hep3Vector(p4Z2Z1);
   TVector3 unitx_1( -p4Z2Z1.X(), -p4Z2Z1.Y(), -p4Z2Z1.Z() );
   norm = 1/(unitx_1.Mag());
   unitx_1*=norm;
   //boost daughters of z2
   TLorentzVector p4M21Z1(p4M21);
   TLorentzVector p4M22Z1(p4M22);
   p4M21Z1.Boost(boostZ1);
   p4M22Z1.Boost(boostZ1);
   //create z and y axes
   /////TVector3 unitz_1 = Hep3Vector(p4M21Z1).cross(Hep3Vector(p4M22Z1));
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
   //std::cout << "theta1: " << M11_Z1frame.Theta() << std::endl;
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
   //////////TVector3 n_unity_1 = n_p4M11inXFrame_unit.Cross( n_unitz_1 );
   TVector3 n_unity_1 = n_unitz_1.Cross( n_p4M11inXFrame_unit );
   TVector3 n_unitx_1 = n_unity_1.Cross( n_unitz_1 );

   TLorentzVector n_p4M21inXFrame( p4M21 );
   n_p4M21inXFrame.Boost( boostX );
   TVector3 n_p4M21inXFrame_unit = n_p4M21inXFrame.Vect().Unit();
   //rotate into other plane
   TVector3 n_p4M21inXFrame_unitprime( n_p4M21inXFrame_unit.Dot(n_unitx_1), n_p4M21inXFrame_unit.Dot(n_unity_1), n_p4M21inXFrame_unit.Dot(n_unitz_1) );

   ///////-----------------new way of calculating phi-----------------///////
   //double phi_n =  n_p4M21inXFrame_unitprime.Phi();
   /*
      std::cout << "---------------------------" << std::endl;
      std::cout << "phi: " << phi << std::endl;
      std::cout << "phi_n: " << phi_n << std::endl;
      std::cout << "phi + phi_n: " << (phi+phi_n) << std::endl;
    */
   /// and then calculate phistar1
   TVector3 n_p4PartoninXFrame_unit( 0.0, 0.0, 1.0 );
   TVector3 n_p4PartoninXFrame_unitprime( n_p4PartoninXFrame_unit.Dot(n_unitx_1), n_p4PartoninXFrame_unit.Dot(n_unity_1), n_p4PartoninXFrame_unit.Dot(n_unitz_1) );
   // negative sign is for arrow convention in paper
   phistar1 = (n_p4PartoninXFrame_unitprime.Phi());

   // and the calculate phistar2
   TLorentzVector n_p4Z2inXFrame( p4Z2 );
   n_p4Z2inXFrame.Boost( boostX );
   TVector3 n_p4Z2inXFrame_unit = n_p4Z2inXFrame.Vect().Unit();
   ///////TLorentzVector n_p4M21inXFrame( p4M21 );
   //////n_p4M21inXFrame.Boost( boostX );        
   ////TVector3 n_p4M21inXFrame_unit = n_p4M21inXFrame.Vect().Unit();  
   TVector3 n_unitz_2( n_p4Z2inXFrame_unit );
   //// y-axis is defined by neg lepton cross z-axis
   //// the subtle part is here...
   //////TVector3 n_unity_2 = n_p4M21inXFrame_unit.Cross( n_unitz_2 );
   TVector3 n_unity_2 = n_unitz_2.Cross( n_p4M21inXFrame_unit );
   TVector3 n_unitx_2 = n_unity_2.Cross( n_unitz_2 );
   TVector3 n_p4PartoninZ2PlaneFrame_unitprime( n_p4PartoninXFrame_unit.Dot(n_unitx_2), n_p4PartoninXFrame_unit.Dot(n_unity_2), n_p4PartoninXFrame_unit.Dot(n_unitz_2) );
   phistar2 = (n_p4PartoninZ2PlaneFrame_unitprime.Phi());

   /*
      double phistar12_0 = phistar1 + phistar2;
      if (phistar12_0 > TMath::Pi()) phistar12 = phistar12_0 - 2*TMath::Pi();
      else if (phistar12_0 < (-1.)*TMath::Pi()) phistar12 = phistar12_0 + 2*TMath::Pi();
      else phistar12 = phistar12_0;
    */

}

bool kanamuon::dottHKinematicFit(const TLorentzVector mup, const TLorentzVector nvp, const TLorentzVector wajp, const TLorentzVector wbjp, const TLorentzVector topajp, const TLorentzVector topbjp, Float_t & fit_chi2, Int_t & fit_NDF, Int_t & fit_status)
{

   bool OK                     = false;
   Resolution* resolution      = new Resolution();

   TMatrixD m1(3,3);
   TMatrixD m2(3,3);
   TMatrixD m3(3,3);
   TMatrixD m4(3,3);
   TMatrixD m5(3,3);
   TMatrixD m6(3,3);
   m1.Zero();
   m2.Zero();
   m3.Zero();
   m4.Zero();
   m5.Zero();
   m6.Zero();

   double etRes, etaRes, phiRes;
   // lepton resolution
   const std::string& leptonName = "muon";  const TLorentzVector lepton   = mup;
   if(leptonName == "electron") {
      OK = resolution->electronResolution(lepton.Et(), lepton.Eta(), etRes, etaRes, phiRes);
      if(!OK) return OK;
   } else {
      OK = resolution->muonResolution(lepton.Et(), lepton.Eta(), etRes, etaRes, phiRes);
      if(!OK) return OK;
   }
   m1(0,0) = resolution->square(etRes);
   m1(1,1) = resolution->square(etaRes);
   m1(2,2) = resolution->square(phiRes);
   // MET resolution
   OK = resolution->PFMETResolution( nvp.Et(), etRes, etaRes, phiRes);
   if(!OK) return OK;
   m2(0,0) = resolution->square(etRes);
   m2(1,1) = 0.01; // resolution->square(etaRes)
   m2(2,2) = resolution->square(phiRes);
   // W aJet resolution
   OK = resolution->udscPFJetResolution( wajp.Et(), wajp.Eta(), etRes, etaRes, phiRes);
   if(!OK) return OK;
   m3(0,0) = resolution->square(etRes);
   m3(1,1) = resolution->square(etaRes);
   m3(2,2) = resolution->square(phiRes);
   // W bJet resolution
   OK = resolution->udscPFJetResolution( wbjp.Et(), wbjp.Eta(), etRes, etaRes, phiRes);
   if(!OK) return OK;
   m4(0,0) = resolution->square(etRes);
   m4(1,1) = resolution->square(etaRes);
   m4(2,2) = resolution->square(phiRes);
   //Top aJet resolution
   OK = resolution->bPFJetResolution( topajp.Et(), topajp.Eta(), etRes, etaRes, phiRes);
   if(!OK) return OK;
   m5(0,0) = resolution->square(etRes);
   m5(1,1) = resolution->square(etaRes);
   m5(2,2) = resolution->square(phiRes);
   //Top bJet resolution
   OK = resolution->bPFJetResolution( topbjp.Et(), topbjp.Eta(), etRes, etaRes, phiRes);
   if(!OK) return OK;
   m6(0,0) = resolution->square(etRes);
   m6(1,1) = resolution->square(etaRes);
   m6(2,2) = resolution->square(phiRes);

   TLorentzVector tmp_mup = mup;
   TLorentzVector tmp_nvp = nvp;
   TLorentzVector tmp_ajp = wajp;
   TLorentzVector tmp_bjp = wbjp;
   TLorentzVector tmp_topajp = topajp;
   TLorentzVector tmp_topbjp = topbjp;

   // Fit Particle
   TFitParticleEtEtaPhi* particle1 = new TFitParticleEtEtaPhi( "Lepton",   "Lepton",   &tmp_mup,    &m1 );
   TFitParticleEtEtaPhi* particle2 = new TFitParticleEtEtaPhi( "Neutrino", "Neutrino", &tmp_nvp,    &m2 );
   TFitParticleEtEtaPhi* particle3 = new TFitParticleEtEtaPhi( "Jeta",     "Jeta",     &tmp_ajp,    &m3 );
   TFitParticleEtEtaPhi* particle4 = new TFitParticleEtEtaPhi( "Jetb",     "Jetb",     &tmp_bjp,    &m4 );
   TFitParticleEtEtaPhi* particle5 = new TFitParticleEtEtaPhi( "TopJeta",     "TopJeta",     &tmp_topajp,    &m5 );
   TFitParticleEtEtaPhi* particle6 = new TFitParticleEtEtaPhi( "TopJetb",     "TopJetb",     &tmp_topbjp,    &m6 );

   // Constraint
   TFitConstraintMGaus* mCons1 = new TFitConstraintMGaus( "W1MassConstraint", "W1Mass-Constraint", 0, 0 , 80.399, 2.085);
   mCons1->addParticles1( particle1, particle2 );

   TFitConstraintMGaus* mCons2 = new TFitConstraintMGaus( "W2MassConstraint", "W2Mass-Constraint", 0, 0 , 80.399, 2.085);
   mCons2->addParticles1( particle3, particle4 );

   TFitConstraintMGaus* mCons3 = new TFitConstraintMGaus( "Top1MassConstraint", "Top1Mass-Constraint", 0, 0 , 172.5, 13.1);
   mCons3->addParticles1( particle1, particle2, particle5 );

   TFitConstraintMGaus* mCons4 = new TFitConstraintMGaus( "Top2MassConstraint", "Top2Mass-Constraint", 0, 0 , 172.5, 13.1);
   mCons4->addParticles1( particle3, particle4, particle6 );

   //Definition of the fitter
   TKinFitter* fitter = new TKinFitter("fitter", "fitter");
   fitter->addMeasParticle( particle1 );
   fitter->addMeasParticle( particle2 );
   fitter->addMeasParticle( particle3 );
   fitter->addMeasParticle( particle4 );
   fitter->addMeasParticle( particle5 );
   fitter->addMeasParticle( particle6 );
   fitter->addConstraint( mCons1 );
   fitter->addConstraint( mCons2 );
   fitter->addConstraint( mCons3 );
   fitter->addConstraint( mCons4 );

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

   if(fitter->getStatus() == 0) { OK = true;  } else { OK = false;  }
   delete resolution;
   delete particle1;
   delete particle2;
   delete particle3;
   delete particle4;
   delete particle5;
   delete particle6;
   delete mCons1;
   delete mCons2;
   delete mCons3;
   delete mCons4;
   delete fitter;

   return OK;


}

// function used to fill the counters with preselction level cuts
void kanamuon::InitCounters( const char* input_file_name, TH1F* h_events, TH1F* h_events_weighted)
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
}


