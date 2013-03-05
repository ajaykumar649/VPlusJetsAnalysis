#define kanaelec_cxx
#include "kanaelec.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <algorithm>
#include <string>
#include <TString.h>
#include <sstream>
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

#include "ClassifierOut/TMVAClassification_170_nJ2_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_180_nJ2_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_190_nJ2_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_200_nJ2_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_250_nJ2_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_300_nJ2_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_350_nJ2_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_400_nJ2_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_450_nJ2_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_500_nJ2_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_550_nJ2_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_600_nJ2_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_400_nJ2_el_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_400_nJ2_el_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_400_nJ2_el_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_450_nJ2_el_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_450_nJ2_el_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_450_nJ2_el_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_500_nJ2_el_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_500_nJ2_el_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_500_nJ2_el_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_550_nJ2_el_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_550_nJ2_el_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_550_nJ2_el_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_600_nJ2_el_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_600_nJ2_el_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_600_nJ2_el_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_700_nJ2_el_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_700_nJ2_el_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_700_nJ2_el_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_800_nJ2_el_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_800_nJ2_el_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_800_nJ2_el_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_900_nJ2_el_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_900_nJ2_el_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_900_nJ2_el_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_1000_nJ2_el_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_1000_nJ2_el_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_1000_nJ2_el_interferenceup_Likelihood.class.C"

#include "ClassifierOut/TMVAClassification_170_nJ3_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_180_nJ3_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_190_nJ3_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_200_nJ3_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_250_nJ3_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_300_nJ3_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_350_nJ3_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_400_nJ3_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_450_nJ3_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_500_nJ3_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_550_nJ3_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_600_nJ3_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_400_nJ3_el_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_400_nJ3_el_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_400_nJ3_el_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_450_nJ3_el_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_450_nJ3_el_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_450_nJ3_el_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_500_nJ3_el_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_500_nJ3_el_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_500_nJ3_el_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_550_nJ3_el_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_550_nJ3_el_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_550_nJ3_el_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_600_nJ3_el_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_600_nJ3_el_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_600_nJ3_el_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_700_nJ3_el_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_700_nJ3_el_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_700_nJ3_el_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_800_nJ3_el_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_800_nJ3_el_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_800_nJ3_el_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_900_nJ3_el_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_900_nJ3_el_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_900_nJ3_el_interferenceup_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_1000_nJ3_el_interferencedown_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_1000_nJ3_el_interferencenominal_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_1000_nJ3_el_interferenceup_Likelihood.class.C"

#include "ClassifierOut/TMVAClassification_noqg_nJ2_el_BDT.class.C"
#include "ClassifierOut/TMVAClassification_noqg_nJ3_el_BDT.class.C"
#include "ClassifierOut/TMVAClassification_withqg_nJ2_el_BDT.class.C"
#include "ClassifierOut/TMVAClassification_withqg_nJ3_el_BDT.class.C"

#include "ClassifierOut/TMVAClassification_170_VBF_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_180_VBF_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_190_VBF_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_200_VBF_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_250_VBF_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_300_VBF_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_350_VBF_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_400_VBF_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_450_VBF_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_500_VBF_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_550_VBF_el_Likelihood.class.C"
#include "ClassifierOut/TMVAClassification_600_VBF_el_Likelihood.class.C"

#include "EffTableReader.h"
#include "EffTableLoader.h"

//#include "PhysicsTools/Utilities/interface/Lumi3DReWeighting.h"

#include "ElectroWeakAnalysis/VPlusJets/interface/QGLikelihoodCalculator.h"
#include "MMozer/powhegweight/interface/pwhg_wrapper.h"

//const TString inDataDir  = "/eos/uscms/store/user/pdudero/lnujj/ICHEP12/MergedNtuples/";
//const TString inDataDir  = "/eos/uscms/store/user/lnujj/HCP2012METfix/MergedNtuples/";
//const TString inDataDir  = "/uscmst1b_scratch/lpc1/3DayLifetime/weizountuple/";
//const TString inDataDir  = "/eos/uscms/store/user/lnujj/Moriond2013/MergedNtuples/";
//const TString inDataDir  = "/eos/uscms/store/user/lnujj/Moriond2013/MergedNtuples_v1/";
const TString inDataDir  = "/eos/uscms/store/user/lnujj/Moriond2013/MergedNtuples_v1/";
//const TString inDataDir  = "/uscms_data/d2/andersj/Wjj/2012/data/Moriond2013/trees/";
//const TString inDataDir  = "/uscmst1b_scratch/lpc1/3DayLifetime/jdamgov/HCPlnjj/MergedNtuples/";
//const TString inDataDir  = "/uscmst1b_scratch/lpc1/3DayLifetime/weizountuple/";
const TString inQCDDir   = "/eos/uscms/store/user/lnujj/HCP2012METfix/MergedNtuples/";
//const TString outDataDir = "/uscms_data/d3/weizou/MakeNtuple/CMSSW_5_3_2_patch4/src/ElectroWeakAnalysis/VPlusJets/test/";
//const TString outDataDir = "/uscmst1b_scratch/lpc1/3DayLifetime/weizou/ttHsample/";
const TString outDataDir = "/uscmst1b_scratch/lpc1/3DayLifetime/weizou/BoostedWSample_v2/";
//const TString outDataDir = "/uscmst1b_scratch/lpc1/3DayLifetime/weizou/ttHsample_New_v14/";
const std::string fDir   = "EffTable2012/";
const std::string fInterferenceDir   = "InterferenceTable2012/";

bool large(const double &a, const double &b)
{
   return a > b;
}

void kanaelec::myana(double myflag, bool isQCD, int runflag)
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
      "P_{T}(W^{had}) > 40"
   };

   for ( int istep = 0; istep < n_step; istep++ ) {
      h_events -> GetXaxis() -> SetBinLabel( istep + 1, step_names[istep].c_str() );
      h_events_weighted -> GetXaxis() -> SetBinLabel( istep + 1, step_names[istep].c_str() );
   }

   TChain * myChain;
   cout << "isQCD=" << isQCD << endl;
   // 2011 data
   if (myflag == 20110000 || myflag == -100){
      myChain = new TChain("WJet"); 
      if ( !isQCD ) {
         InitCounters( inDataDir + "WenuJets_DataAllSingleElectronTrigger_GoldenJSON_4p7invfb.root", h_events, h_events_weighted);
         myChain->Add(                    inDataDir + "WenuJets_DataAllSingleElectronTrigger_GoldenJSON_4p7invfb.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20110000,runflag, outDataDir + "RD_WenuJets_DataAllSingleElectronTrigger_GoldenJSON_4p7invfb");
      } else {
         InitCounters( inDataDir + "WenuJets_DataAll_GoldenJSON_5invfb.root", h_events, h_events_weighted);
         myChain->Add(                    inQCDDir +     "WenuJets_DataAll_GoldenJSON_5invfb.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20110000,runflag, outDataDir + "RDQCD_WenuJets_DataAll_GoldenJSON_2p1invfb", isQCD);
      }
   }

   if (myflag == 20120000 || myflag == -100){
      myChain = new TChain("WJet"); 

      if ( !isQCD ) {
         //InitCounters( inDataDir + "WenuJets_DataAllSingleElectronTrigger_GoldenJSON_9p3invfb.root", h_events, h_events_weighted);
         //myChain->Add(                    inDataDir + "WenuJets_DataAllSingleElectronTrigger_GoldenJSON_9p3invfb.root"); 
         //Init(myChain);Loop( h_events, h_events_weighted, 20120000,runflag, outDataDir + "RD_WenuJets_DataAllSingleElectronTrigger_GoldenJSON_9p3invfb");
         //InitCounters( inDataDir + "WenuJets_DataAllSingleElectronTrigger_GoldenJSON_11p9invfb.root", h_events, h_events_weighted);
         //myChain->Add(                    inDataDir + "WenuJets_DataAllSingleElectronTrigger_GoldenJSON_11p9invfb.root"); 
         //Init(myChain);Loop( h_events, h_events_weighted, 20120000,runflag, outDataDir + "RD_WenuJets_DataAllSingleElectronTrigger_GoldenJSON_11p9invfb");
         //InitCounters( inDataDir + "WenuJets_DataAllSingleElectronTrigger_GoldenJSON_13p9invfb.root", h_events, h_events_weighted);
         //myChain->Add(                    inDataDir + "WenuJets_DataAllSingleElectronTrigger_GoldenJSON_13p9invfb.root"); 
         //InitCounters( inDataDir + "WenuJets_DataAllSingleElectronTrigger_GoldenJSON_18p65invfb.root", h_events, h_events_weighted);
         //myChain->Add(                    inDataDir + "WenuJets_DataAllSingleElectronTrigger_GoldenJSON_18p65invfb.root"); 
         InitCounters( inDataDir + "WenuJets_DataAllSingleElectronTrigger_GoldenJSON_19p2invfb.root", h_events, h_events_weighted);
         myChain->Add(                    inDataDir + "WenuJets_DataAllSingleElectronTrigger_GoldenJSON_19p2invfb.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20120000,runflag, outDataDir + "RD_WenuJets_DataAllSingleElectronTrigger_GoldenJSON_19p2invfb");
      } else {
         InitCounters( inDataDir + "QCD_WenuJets_DataAll_GoldenJSON_9p3invfb.root", h_events, h_events_weighted);
         myChain->Add(                    inQCDDir +     "QCD_WenuJets_DataAll_GoldenJSON_9p3invfb.root");
         Init(myChain);Loop( h_events, h_events_weighted, 20120000,runflag, outDataDir + "RDQCD_WenuJets_DataAll_GoldenJSON_9p3invfb.root", isQCD);
      }
   }

   if ( !isQCD ) {
      // Separate Electron Data
      if (myflag == 20110001 || myflag == -101){
         InitCounters( inDataDir + "SingleEleAndEleTwoPFJetTrigger.root", h_events, h_events_weighted);             
         myChain = new TChain("WJet");
         myChain->Add(                    inDataDir + "SingleEleAndEleTwoPFJetTrigger.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20110001,runflag, outDataDir + "RD_SingleEleAndEleTwoPFJetTrigger");
      }
      if (myflag == 20110002 || myflag == -102){
         InitCounters( inDataDir + "EleTwoCaloJetTrigger.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "EleTwoCaloJetTrigger.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20110002,runflag, outDataDir + "RD_EleTwoCaloJetTrigger");
      }
      if (myflag == 20110003 || myflag == -103){
         InitCounters( inDataDir + "WenuJets_175832-180252_SingleElectron-Run2011B-PromptReco-v1-trigallcombined.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "WenuJets_175832-180252_SingleElectron-Run2011B-PromptReco-v1-trigallcombined.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20110003,runflag, outDataDir + "RD_WenuJets_175832-180252_SingleElectron-Run2011B-PromptReco-v1-trigallcombined");
      }
      if (myflag == 20110004 || myflag == -104){
         InitCounters( inDataDir + "WenuJets_DataAll_GoldenJSON_4p7invfb.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "WenuJets_DataAll_GoldenJSON_4p7invfb.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20110004,runflag, outDataDir + "RD_WenuJets_DataAll_GoldenJSON_4p7invfb");
      }

      // General Background Samples
      if (myflag == 20111002 || myflag == -200){
         InitCounters( inDataDir + "el_STopS_Tbar_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_STopS_Tbar_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111002,runflag, outDataDir + "RD_el_STopS_Tbar_CMSSW428");
      }
      if (myflag == 20121002 || myflag == -200){
         InitCounters( inDataDir + "el_STopS_Tbar_CMSSW532.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_STopS_Tbar_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121002,runflag, outDataDir + "RD_el_STopS_Tbar_CMSSW532");
      }
      if (myflag == 20111003 || myflag == -200){
         InitCounters( inDataDir + "el_STopS_T_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_STopS_T_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111003,runflag, outDataDir + "RD_el_STopS_T_CMSSW428");
      }
      if (myflag == 20121003 || myflag == -200){
         InitCounters( inDataDir + "el_STopS_T_CMSSW532.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_STopS_T_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121003,runflag, outDataDir + "RD_el_STopS_T_CMSSW532");
      }
      if (myflag == 20111004 || myflag == -200){
         InitCounters( inDataDir + "el_STopT_Tbar_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_STopT_Tbar_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111004,runflag, outDataDir + "RD_el_STopT_Tbar_CMSSW428");
      }
      if (myflag == 20121004 || myflag == -200){
         InitCounters( inDataDir + "el_STopT_Tbar_CMSSW532.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_STopT_Tbar_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121004,runflag, outDataDir + "RD_el_STopT_Tbar_CMSSW532");
      }
      if (myflag == 20111005 || myflag == -200){
         InitCounters( inDataDir + "el_STopT_T_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_STopT_T_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111005,runflag, outDataDir + "RD_el_STopT_T_CMSSW428");
      }
      if (myflag == 20121005 || myflag == -200){
         InitCounters( inDataDir + "el_STopT_T_CMSSW532.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_STopT_T_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121005,runflag, outDataDir + "RD_el_STopT_T_CMSSW532");
      }
      if (myflag == 20111006 || myflag == -200){
         InitCounters( inDataDir + "el_STopTW_Tbar_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_STopTW_Tbar_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111006,runflag, outDataDir + "RD_el_STopTW_Tbar_CMSSW428");
      }
      if (myflag == 20121006 || myflag == -200){
         InitCounters( inDataDir + "el_STopTW_Tbar_CMSSW532.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_STopTW_Tbar_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121006,runflag, outDataDir + "RD_el_STopTW_Tbar_CMSSW532");
      }
      if (myflag == 20111007 || myflag == -200){
         InitCounters( inDataDir + "el_STopTW_T_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_STopTW_T_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111007,runflag, outDataDir + "RD_el_STopTW_T_CMSSW428");
      }
      if (myflag == 20121007 || myflag == -200){
         InitCounters( inDataDir + "el_STopTW_T_CMSSW532.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_STopTW_T_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121007,runflag, outDataDir + "RD_el_STopTW_T_CMSSW532");
      }
      if (myflag == 20111008 || myflag == -200){
         InitCounters( inDataDir + "el_TTbar_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_TTbar_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111008,runflag, outDataDir + "RD_el_TTbar_CMSSW428");
      }

      if (myflag == 20121008 || myflag == -200){
         InitCounters( inDataDir + "el_TTbar_CMSSW532.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_TTbar_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121008,runflag, outDataDir + "RD_el_TTbar_CMSSW532");
      }
      if (myflag == 20111009 || myflag == -500){
         InitCounters( inDataDir + "el_WpJ_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_WpJ_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111009,runflag, outDataDir + "RD_el_WpJ_CMSSW428");
      }

      if (myflag == 20121009 || myflag == -500){
         InitCounters( inDataDir + "el_WJets_CMSSW532.root", h_events, h_events_weighted);
         //InitCounters( inDataDir + "el_WpJ_CMSSW532.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_WJets_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121009,runflag, outDataDir + "RD_el_WpJ_CMSSW532");
      }

      if (myflag == 20111010 || myflag == -200){
         InitCounters( inDataDir + "el_WpJmatchingdown_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_WpJmatchingdown_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111010,runflag, outDataDir + "RD_el_WpJmatchingdown_CMSSW428");
      }
      if (myflag == 20111011 || myflag == -200){
         InitCounters( inDataDir + "el_WpJmatchingup_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_WpJmatchingup_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111011,runflag, outDataDir + "RD_el_WpJmatchingup_CMSSW428");
      }
      if (myflag == 20111012 || myflag == -200){
         InitCounters( inDataDir + "el_WpJscaledown_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_WpJscaledown_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111012,runflag, outDataDir + "RD_el_WpJscaledown_CMSSW428");
      }
      if (myflag == 20111013 || myflag == -200){
         InitCounters( inDataDir + "el_WpJscaleup_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_WpJscaleup_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111013,runflag, outDataDir + "RD_el_WpJscaleup_CMSSW428");
      }
      if (myflag == 20111014 || myflag ==  999){ // set 999 not run!!
         InitCounters( inDataDir + "el_WpJsherpa_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_WpJsherpa_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111014,runflag, outDataDir + "RD_el_WpJsherpa_CMSSW428");
      }
      if (myflag == 20111015 || myflag == -200){
         InitCounters( inDataDir + "el_WW_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_WW_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111015,runflag, outDataDir + "RD_el_WW_CMSSW428");
      }
      if (myflag == 20121015 || myflag == -200){
         InitCounters( inDataDir + "el_WW_CMSSW532.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_WW_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121015,runflag, outDataDir + "RD_el_WW_CMSSW532");
      }
      if (myflag == 20111016 || myflag == -200){
         InitCounters( inDataDir + "el_WZ_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_WZ_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111016,runflag, outDataDir + "RD_el_WZ_CMSSW428");
      }
      if (myflag == 20121016 || myflag == -200){
         InitCounters( inDataDir + "el_WZ_CMSSW532.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_WZ_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121016,runflag, outDataDir + "RD_el_WZ_CMSSW532");
      }
      if (myflag == 20111017 || myflag == -200){
         InitCounters( inDataDir + "el_ZpJ_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_ZpJ_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111017,runflag, outDataDir + "RD_el_ZpJ_CMSSW428");
      }
      if (myflag == 20121017 || myflag == -200){
         InitCounters( inDataDir + "el_ZpJ_CMSSW532.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_ZpJ_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121017,runflag, outDataDir + "RD_el_ZpJ_CMSSW532");
      }
      if (myflag == 20111018 || myflag ==  999){ // set 999 not run!!
         InitCounters( inDataDir + "el_QCDEl_BCtoE30to80_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_QCDEl_BCtoE30to80_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111018,runflag, outDataDir + "RD_el_QCDEl_BCtoE30to80_CMSSW428");
      }
      if (myflag == 20111019 || myflag ==  999){ // set 999 not run!!
         InitCounters( inDataDir + "el_QCDEl_BCtoE80to170_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_QCDEl_BCtoE80to170_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111019,runflag, outDataDir + "RD_el_QCDEl_BCtoE80to170_CMSSW428");
      }
      if (myflag == 20111020 || myflag ==  999){ // set 999 not run!!
         InitCounters( inDataDir + "el_QCDEl_Pt30to80_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_QCDEl_Pt30to80_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111020,runflag, outDataDir + "RD_el_QCDEl_Pt30to80_CMSSW428");
      }
      if (myflag == 20111021 || myflag ==  999){ // set 999 not run!!
         InitCounters( inDataDir + "el_QCDEl_Pt80to170_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_QCDEl_Pt80to170_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111021,runflag, outDataDir + "RD_el_QCDEl_Pt80to170_CMSSW428");
      }
      if (myflag == 20111022 || myflag ==  999){ // set 999 not run!!
         InitCounters( inDataDir + "el_TTbar_powheg_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_TTbar_powheg_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111022,runflag, outDataDir + "RD_el_TTbar_powheg_CMSSW428");
      }
      if (myflag == 20111023 || myflag == -200){
         InitCounters( inDataDir + "el_ZZ_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_ZZ_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20111023,runflag, outDataDir + "RD_el_ZZ_CMSSW428");
      }

      if (myflag == 20121023 || myflag == -200){
         InitCounters( inDataDir + "el_ZZ_CMSSW532.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_ZZ_CMSSW532.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20121023,runflag, outDataDir + "RD_el_ZZ_CMSSW532");
      }
      if (myflag == 20121024 || myflag == -200){
         InitCounters( inDataDir + "el_WpJ_PT100_CMSSW532.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");
         myChain->Add(                    inDataDir + "el_WpJ_PT100_CMSSW532.root");
         Init(myChain);Loop(  h_events, h_events_weighted,20121024,runflag, outDataDir + "RD_el_WpJPt100_CMSSW532");
      }
      if (myflag == 20121025 || myflag == -200){
         InitCounters( inDataDir + "el_W3Jets_CMSSW532.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");
         myChain->Add(                    inDataDir + "el_W3Jets_CMSSW532.root");
         Init(myChain);Loop(  h_events, h_events_weighted,20121025,runflag, outDataDir + "RD_el_W3Jets_CMSSW532");
      }
      if (myflag == 20121026 || myflag == -200){
         InitCounters( inDataDir + "el_W4Jets_CMSSW532.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");
         myChain->Add(                    inDataDir + "el_W4Jets_CMSSW532.root");
         Init(myChain);Loop(  h_events, h_events_weighted,20121026,runflag, outDataDir + "RD_el_W4Jets_CMSSW532");
      }
      if (myflag == 20121027 || myflag == -200){
         InitCounters( inDataDir + "el_ttZ_CMSSW532.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");
         myChain->Add(                    inDataDir + "el_ttZ_CMSSW532.root");
         Init(myChain);Loop(  h_events, h_events_weighted,20121027,runflag, outDataDir + "RD_el_ttZ_CMSSW532");
      }
      if (myflag == 20121028 || myflag == -200){
         InitCounters( inDataDir + "el_ttHbbMH125_CMSSW532.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");
         myChain->Add(                    inDataDir + "el_ttHbbMH125_CMSSW532.root");
         Init(myChain);Loop(  h_events, h_events_weighted,20121028,runflag, outDataDir + "RD_el_ttHbbMH125_CMSSW532");
      }
      if (myflag == 20121029 || myflag == -200){
         InitCounters( inDataDir + "el_ttHinclusivedecayMH125_CMSSW532.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");
         myChain->Add(                    inDataDir + "el_ttHinclusivedecayMH125_CMSSW532.root");
         Init(myChain);Loop(  h_events, h_events_weighted,20121029,runflag, outDataDir + "RD_el_ttHinclusivedecayMH125_CMSSW532");
      }
      if (myflag == 20121030 || myflag == -200){
         InitCounters( inDataDir + "el_ttW_CMSSW532.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");
         myChain->Add(                    inDataDir + "el_ttW_CMSSW532.root");
         Init(myChain);Loop(  h_events, h_events_weighted,20121030,runflag, outDataDir + "RD_el_ttW_CMSSW532");
      }
      if (myflag == 20121031 || myflag == -200){
         InitCounters( inDataDir + "el_WJets_herwig_CMSSW532.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");
         myChain->Add(                    inDataDir + "el_WJets_herwig_CMSSW532.root");
         Init(myChain);Loop(  h_events, h_events_weighted,20121030,runflag, outDataDir + "RD_el_WJets_herwig_CMSSW532");
      }
      if (myflag == 20121032 || myflag == -200){
         InitCounters( inDataDir + "el_WJets_madgraph_CMSSW532.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");
         myChain->Add(                    inDataDir + "el_WJets_madgraph_CMSSW532.root");
         Init(myChain);Loop(  h_events, h_events_weighted,20121030,runflag, outDataDir + "RD_el_WJets_madgraph_CMSSW532");
      }

      // Higgs Signal Samples
      if (myflag == 20112150 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH150_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH150_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112150,runflag, outDataDir + "RD_el_HWWMH150_CMSSW428");
      }
      if (myflag == 20122125 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH125_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH125_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122125,runflag, outDataDir + "RD_el_HWWMH125_CMSSW532_private");
      }
      if (myflag == 20122140 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH140_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH140_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122140,runflag, outDataDir + "RD_el_HWWMH140_CMSSW532_private");
      }
      if (myflag == 20122160 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH160_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH160_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122160,runflag, outDataDir + "RD_el_HWWMH160_CMSSW532_private");
      }

      if (myflag == 20112160 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH160_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH160_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112160,runflag, outDataDir + "RD_el_HWWMH160_CMSSW428");
      }
      if (myflag == 20112170 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH170_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH170_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112170,runflag, outDataDir + "RD_el_HWWMH170_CMSSW428");
      }

      if (myflag == 20122170 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH170_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH170_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122170,runflag, outDataDir + "RD_el_HWWMH170_CMSSW532_private");
      }

      if (myflag == 20112180 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH180_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH180_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112180,runflag, outDataDir + "RD_el_HWWMH180_CMSSW428");
      }
      if (myflag == 20122180 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH180_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH180_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122180,runflag, outDataDir + "RD_el_HWWMH180_CMSSW532_private");
      }
      if (myflag == 20112190 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH190_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH190_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112190,runflag, outDataDir + "RD_el_HWWMH190_CMSSW428");
      }
      if (myflag == 20112200 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH200_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH200_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112200,runflag, outDataDir + "RD_el_HWWMH200_CMSSW428");
      }
      if (myflag == 20122200 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH200_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH200_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122200,runflag, outDataDir + "RD_el_HWWMH200_CMSSW532_private");
      }
      if (myflag == 20112250 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH250_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH250_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112250,runflag, outDataDir + "RD_el_HWWMH250_CMSSW428");
      }
      if (myflag == 20112300 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH300_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH300_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112300,runflag, outDataDir + "RD_el_HWWMH300_CMSSW428");
      }
      if (myflag == 20122300 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH300_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH300_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122300,runflag, outDataDir + "RD_el_HWWMH300_CMSSW532_private");
      }
      if (myflag == 20112350 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH350_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH350_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112350,runflag, outDataDir + "RD_el_HWWMH350_CMSSW428");
      }
      if (myflag == 20122190 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH190_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");
         myChain->Add(                    inDataDir + "el_HWWMH190_CMSSW532_private.root");
         Init(myChain);Loop( h_events, h_events_weighted, 20122190,runflag, outDataDir + "RD_el_HWWMH190_CMSSW532_private");
      }
      if (myflag == 20122250 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH250_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");
         myChain->Add(                    inDataDir + "el_HWWMH250_CMSSW532_private.root");
         Init(myChain);Loop( h_events, h_events_weighted, 20122250,runflag, outDataDir + "RD_el_HWWMH250_CMSSW532_private");
      }
      if (myflag == 20122350 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH350_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");
         myChain->Add(                    inDataDir + "el_HWWMH350_CMSSW532_private.root");
         Init(myChain);Loop( h_events, h_events_weighted, 20122350,runflag, outDataDir + "RD_el_HWWMH350_CMSSW532_private");
      }
      if (myflag == 20112400 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH400_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH400_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112400,runflag, outDataDir + "RD_el_HWWMH400_CMSSW428");
      }
      if (myflag == 20122400 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH400_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH400_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122400,runflag, outDataDir + "RD_el_HWWMH400_CMSSW532_private");
      }
      if (myflag == 20112450 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH450_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH450_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112450,runflag, outDataDir + "RD_el_HWWMH450_CMSSW428");
      }
      if (myflag == 20122450 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH450_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH450_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122450,runflag, outDataDir + "RD_el_HWWMH450_CMSSW532_private");
      }
      if (myflag == 20112500 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH500_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH500_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112500,runflag, outDataDir + "RD_el_HWWMH500_CMSSW428");
      }
      if (myflag == 20122500 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH500_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH500_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122500,runflag, outDataDir + "RD_el_HWWMH500_CMSSW532_private");
      }
      if (myflag == 20112550 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH550_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH550_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112550,runflag, outDataDir + "RD_el_HWWMH550_CMSSW428");
      }
      /*if (myflag == 20122550 || myflag == -300){
        myChain = new TChain("WJet");  
        myChain->Add(                    inDataDir + "el_HWWMH550_CMSSW532_private.root"); 
        Init(myChain);Loop( h_events, h_events_weighted, 20122550,runflag, outDataDir + "RD_el_HWWMH550_CMSSW532_private");
        }
       */
      if (myflag == 20122550 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH550_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH550_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122550,runflag, outDataDir + "RD_el_HWWMH550_CMSSW532_private");
      }
      if (myflag == 20112600 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH600_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH600_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20112600,runflag, outDataDir + "RD_el_HWWMH600_CMSSW428");
      }
      /*if (myflag == 20122600 || myflag == -300){
        InitCounters( inDataDir + "el_HWWMH600_CMSSW532_private.root", h_events, h_events_weighted);
        myChain = new TChain("WJet");  
        myChain->Add(                    inDataDir + "el_HWWMH600_CMSSW532_private.root"); 
        Init(myChain);Loop( h_events, h_events_weighted, 20122600,runflag, outDataDir + "RD_el_HWWMH600_CMSSW532_private");
        }
       */
      if (myflag == 20122600 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH600_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH600_CMSSW532_private.root"); 
         Init(myChain);Loop(h_events, h_events_weighted ,20122600,runflag, outDataDir + "RD_el_HWWMH600_CMSSW532_private");
      }
      /*if (myflag == 20122700 || myflag == -300){
        myChain = new TChain("WJet");  
        myChain->Add(                    inDataDir + "el_HWWMH700_CMSSW532_private.root"); 
        Init(myChain);Loop( h_events, h_events_weighted, 20122700,runflag, outDataDir + "RD_el_HWWMH700_CMSSW532_private");
        }
       */
      if (myflag == 20122700 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH700_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH700_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122700,runflag, outDataDir + "RD_el_HWWMH700_CMSSW532_private");
      }
      if (myflag == 20122800 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH800_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH800_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122800,runflag, outDataDir + "RD_el_HWWMH800_CMSSW532_private");
      }
      if (myflag == 20122900 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH900_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH900_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20122900,runflag, outDataDir + "RD_el_HWWMH900_CMSSW532_private");
      }
      if (myflag == 201221000 || myflag == -300){
         InitCounters( inDataDir + "el_HWWMH1000_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWMH1000_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 201221000,runflag, outDataDir + "RD_el_HWWMH1000_CMSSW532_private");
      }

      // VBF Higgs MC Signal
      if (myflag == 20123125 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH125_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH125_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123125,runflag, outDataDir + "RD_el_VBFHWWMH125_CMSSW532_private");
      }
      if (myflag == 20113150 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH150_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH150_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113150,runflag, outDataDir + "RD_el_VBFHWWMH150_CMSSW428");
      }
      if (myflag == 20113160 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH160_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH160_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113160,runflag, outDataDir + "RD_el_VBFHWWMH160_CMSSW428");
      }
      if (myflag == 20113170 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH170_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH170_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113170,runflag, outDataDir + "RD_el_VBFHWWMH170_CMSSW428");
      }
      if (myflag == 20123170 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH170_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH170_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123170,runflag, outDataDir + "RD_el_VBFHWWMH170_CMSSW532_private");
      }
      if (myflag == 20113180 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH180_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH180_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113180,runflag, outDataDir + "RD_el_VBFHWWMH180_CMSSW428");
      }
      if (myflag == 20123180 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH180_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH180_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123180,runflag, outDataDir + "RD_el_VBFHWWMH180_CMSSW532_private");
      }
      if (myflag == 20113190 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH190_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH190_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113190,runflag, outDataDir + "RD_el_VBFHWWMH190_CMSSW428");
      }
      if (myflag == 20123190 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH190_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH190_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123190,runflag, outDataDir + "RD_el_VBFHWWMH190_CMSSW532_private");
      }
      if (myflag == 20113200 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH200_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH200_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113200,runflag, outDataDir + "RD_el_VBFHWWMH200_CMSSW428");
      }
      if (myflag == 20123200 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH200_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH200_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123200,runflag, outDataDir + "RD_el_VBFHWWMH200_CMSSW532_private");
      }
      if (myflag == 20113250 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH250_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH250_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113250,runflag, outDataDir + "RD_el_VBFHWWMH250_CMSSW428");
      }
      if (myflag == 20123250 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH250_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH250_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123250,runflag, outDataDir + "RD_el_VBFHWWMH250_CMSSW532_private");
      }
      if (myflag == 20113300 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH300_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH300_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113300,runflag, outDataDir + "RD_el_VBFHWWMH300_CMSSW428");
      }
      if (myflag == 20123300 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH300_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH300_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123300,runflag, outDataDir + "RD_el_VBFHWWMH300_CMSSW532_private");
      }
      if (myflag == 20113350 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH350_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH350_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113350,runflag, outDataDir + "RD_el_VBFHWWMH350_CMSSW428");
      }
      if (myflag == 20123350 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH350_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH350_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123350,runflag, outDataDir + "RD_el_VBFHWWMH350_CMSSW532_private");
      }
      if (myflag == 20113400 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH400_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH400_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113400,runflag, outDataDir + "RD_el_VBFHWWMH400_CMSSW428");
      }
      if (myflag == 20123400 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH400_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH400_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123400,runflag, outDataDir + "RD_el_VBFHWWMH400_CMSSW532_private");
      }
      if (myflag == 20113450 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH450_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH450_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113450,runflag, outDataDir + "RD_el_VBFHWWMH450_CMSSW428");
      }
      if (myflag == 20123450 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH450_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH450_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123450,runflag, outDataDir + "RD_el_VBFHWWMH450_CMSSW532_private");
      }
      if (myflag == 20113500 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH500_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH500_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113500,runflag, outDataDir + "RD_el_VBFHWWMH500_CMSSW428");
      }
      if (myflag == 20123500 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH500_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH500_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123500,runflag, outDataDir + "RD_el_VBFHWWMH500_CMSSW532_private");
      }
      if (myflag == 20113550 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH550_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH550_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113550,runflag, outDataDir + "RD_el_VBFHWWMH550_CMSSW428");
      }
      if (myflag == 20123550 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH550_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH550_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123550,runflag, outDataDir + "RD_el_VBFHWWMH550_CMSSW532_private");
      }
      if (myflag == 20113600 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH600_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH600_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20113600,runflag, outDataDir + "RD_el_VBFHWWMH600_CMSSW428");
      }
      if (myflag == 20123600 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH600_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH600_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123600,runflag, outDataDir + "RD_el_VBFHWWMH600_CMSSW532_private");
      }
      if (myflag == 20123700 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH700_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH700_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123700,runflag, outDataDir + "RD_el_VBFHWWMH700_CMSSW532_private");
      }
      if (myflag == 20123800 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH800_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH800_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123800,runflag, outDataDir + "RD_el_VBFHWWMH800_CMSSW532_private");
      }
      if (myflag == 20123900 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH900_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH900_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20123900,runflag, outDataDir + "RD_el_VBFHWWMH900_CMSSW532_private");
      }
      if (myflag == 201231000 || myflag == -300){
         InitCounters( inDataDir + "el_VBFHWWMH1000_CMSSW532_private.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBFHWWMH1000_CMSSW532_private.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 201231000,runflag, outDataDir + "RD_el_VBFHWWMH1000_CMSSW532_private");
      }

      // HTauTau MC Signal
      if (myflag == 20114150 || myflag == -400){
         InitCounters( inDataDir + "el_HWWTauNuMH150_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWTauNuMH150_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114150,runflag, outDataDir + "RD_el_HWWTauNuMH150_CMSSW428");
      }
      if (myflag == 20114160 || myflag == -400){
         InitCounters( inDataDir + "el_HWWTauNuMH160_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWTauNuMH160_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114160,runflag, outDataDir + "RD_el_HWWTauNuMH160_CMSSW428");
      }
      if (myflag == 20114170 || myflag == -400){
         InitCounters( inDataDir + "el_HWWTauNuMH170_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWTauNuMH170_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114170,runflag, outDataDir + "RD_el_HWWTauNuMH170_CMSSW428");
      }
      if (myflag == 20114180 || myflag == -400){
         InitCounters( inDataDir + "el_HWWTauNuMH180_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWTauNuMH180_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114180,runflag, outDataDir + "RD_el_HWWTauNuMH180_CMSSW428");
      }
      if (myflag == 20114190 || myflag == -400){
         InitCounters( inDataDir + "el_HWWTauNuMH190_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWTauNuMH190_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114190,runflag, outDataDir + "RD_el_HWWTauNuMH190_CMSSW428");
      }
      if (myflag == 20114200 || myflag == -400){
         InitCounters( inDataDir + "el_HWWTauNuMH200_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWTauNuMH200_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114200,runflag, outDataDir + "RD_el_HWWTauNuMH200_CMSSW428");
      }
      if (myflag == 20114250 || myflag == -400){
         InitCounters( inDataDir + "el_HWWTauNuMH250_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWTauNuMH250_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114250,runflag, outDataDir + "RD_el_HWWTauNuMH250_CMSSW428");
      }
      if (myflag == 20114300 || myflag == -400){
         InitCounters( inDataDir + "el_HWWTauNuMH300_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWTauNuMH300_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114300,runflag, outDataDir + "RD_el_HWWTauNuMH300_CMSSW428");
      }
      if (myflag == 20114350 || myflag == -400){
         InitCounters( inDataDir + "el_HWWTauNuMH350_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWTauNuMH350_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114350,runflag, outDataDir + "RD_el_HWWTauNuMH350_CMSSW428");
      }
      if (myflag == 20114400 || myflag == -400){
         InitCounters( inDataDir + "el_HWWTauNuMH400_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWTauNuMH400_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114400,runflag, outDataDir + "RD_el_HWWTauNuMH400_CMSSW428");
      }
      if (myflag == 20114450 || myflag == -400){
         InitCounters( inDataDir + "el_HWWTauNuMH450_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWTauNuMH450_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114450,runflag, outDataDir + "RD_el_HWWTauNuMH450_CMSSW428");
      }
      if (myflag == 20114500 || myflag == -400){
         InitCounters( inDataDir + "el_HWWTauNuMH500_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWTauNuMH500_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114500,runflag, outDataDir + "RD_el_HWWTauNuMH500_CMSSW428");
      }
      if (myflag == 20114550 || myflag == -400){
         InitCounters( inDataDir + "el_HWWTauNuMH550_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWTauNuMH550_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114550,runflag, outDataDir + "RD_el_HWWTauNuMH550_CMSSW428");
      }
      if (myflag == 20114600 || myflag == -400){
         InitCounters( inDataDir + "el_HWWTauNuMH600_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_HWWTauNuMH600_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20114600,runflag, outDataDir + "RD_el_HWWTauNuMH600_CMSSW428");
      }

      // VBF Background samples generated by Qiang and Andre
      if (myflag == 20115001 || myflag == -400){
         InitCounters( inDataDir + "el_VBF_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_VBF_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20115001,runflag, outDataDir + "RD_el_VBF_CMSSW428");
      }
      //new physics samples for the Mjj analysis
      if (myflag == 20115002 || myflag == -400){
         InitCounters( inDataDir + "el_ZprimeMadGraph_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_ZprimeMadGraph_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20115002,runflag, outDataDir + "RD_el_ZprimeMadGraph_CMSSW428");
      }
      if (myflag == 20115003 || myflag == -400){
         InitCounters( inDataDir + "el_TechnicolorPythia_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_TechnicolorPythia_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20115003,runflag, outDataDir + "RD_el_TechnicolorPythia_CMSSW428");
      }
      if (myflag == 20115004 || myflag == -400){
         InitCounters( inDataDir + "el_WH150qq_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_WH150qq_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20115004,runflag, outDataDir + "RD_el_WH150qq_CMSSW428");
      }
      if (myflag == 20115005 || myflag == -400){
         InitCounters( inDataDir + "el_WpJ100KCrossCheck_CMSSW428.root", h_events, h_events_weighted);
         myChain = new TChain("WJet");  
         myChain->Add(                    inDataDir + "el_WpJ100KCrossCheck_CMSSW428.root"); 
         Init(myChain);Loop( h_events, h_events_weighted, 20115005,runflag, outDataDir + "RD_el_WpJ100KCrossCheck_CMSSW428");
      }

   }

}
void kanaelec::Loop(TH1F* h_events, TH1F* h_events_weighted, int wda, int runflag, const char *outfilename, bool isQCD)
{
   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntries();
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
   // Drop gen jet information
   fChain->SetBranchStatus("*Gen*",    0);
   //fChain->SetBranchStatus("W_H_*",    0);
   fChain->SetBranchStatus("W_Parton_*",    0);
   fChain->SetBranchStatus("W_Lepton_*",    0);
   fChain->SetBranchStatus("W_Met_*",    0);

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

   TTree *newtree = fChain->CloneTree();
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

   TBranch *branch_mu_px = newtree->Branch("fit_el_px", &fit_mu_px,  "fit_el_px/F");
   TBranch *branch_mu_py = newtree->Branch("fit_el_py", &fit_mu_py,  "fit_el_py/F");
   TBranch *branch_mu_pz = newtree->Branch("fit_el_pz", &fit_mu_pz,  "fit_el_pz/F");
   TBranch *branch_mu_e  = newtree->Branch("fit_el_e",  &fit_mu_e,   "fit_el_e/F");

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

   Float_t mva2j160el = 999, mva2j170el = 999, mva2j180el = 999, mva2j190el = 999, mva2j200el = 999, mva2j250el = 999, mva2j300el = 999, mva2j350el = 999, mva2j400el = 999, mva2j450el = 999, mva2j500el = 999, mva2j550el = 999, mva2j600el = 999;
   Float_t mva2j400interferencenominalel = 999, mva2j450interferencenominalel = 999, mva2j500interferencenominalel = 999, mva2j550interferencenominalel = 999, mva2j600interferencenominalel = 999, mva2j700interferencenominalel = 999, mva2j800interferencenominalel = 999, mva2j900interferencenominalel = 999, mva2j1000interferencenominalel = 999; 
   Float_t mva2j400interferencedownel = 999, mva2j450interferencedownel = 999, mva2j500interferencedownel = 999, mva2j550interferencedownel = 999, mva2j600interferencedownel = 999, mva2j700interferencedownel = 999, mva2j800interferencedownel = 999, mva2j900interferencedownel = 999, mva2j1000interferencedownel = 999; 
   Float_t mva2j400interferenceupel = 999, mva2j450interferenceupel = 999, mva2j500interferenceupel = 999, mva2j550interferenceupel = 999, mva2j600interferenceupel = 999, mva2j700interferenceupel = 999, mva2j800interferenceupel = 999, mva2j900interferenceupel = 999, mva2j1000interferenceupel = 999;
   Float_t mva3j160el = 999, mva3j170el = 999, mva3j180el = 999, mva3j190el = 999, mva3j200el = 999, mva3j250el = 999, mva3j300el = 999, mva3j350el = 999, mva3j400el = 999, mva3j450el = 999, mva3j500el = 999, mva3j550el = 999, mva3j600el = 999;
   Float_t mva3j400interferencenominalel = 999, mva3j450interferencenominalel = 999, mva3j500interferencenominalel = 999, mva3j550interferencenominalel = 999, mva3j600interferencenominalel = 999, mva3j700interferencenominalel = 999, mva3j800interferencenominalel = 999, mva3j900interferencenominalel = 999, mva3j1000interferencenominalel = 999; 
   Float_t mva3j400interferencedownel = 999, mva3j450interferencedownel = 999, mva3j500interferencedownel = 999, mva3j550interferencedownel = 999, mva3j600interferencedownel = 999, mva3j700interferencedownel = 999, mva3j800interferencedownel = 999, mva3j900interferencedownel = 999, mva3j1000interferencedownel = 999; 
   Float_t mva3j400interferenceupel = 999, mva3j450interferenceupel = 999, mva3j500interferenceupel = 999, mva3j550interferenceupel = 999, mva3j600interferenceupel = 999, mva3j700interferenceupel = 999, mva3j800interferenceupel = 999, mva3j900interferenceupel = 999, mva3j1000interferenceupel = 999;
   Float_t mva2jdibosonel = 999,mva3jdibosonel = 999, mva2jdibnoqgel = 999,mva3jdibnoqgel = 999;
   Float_t mvavbf160el = 999, mvavbf170el = 999, mvavbf180el = 999, mvavbf190el = 999, mvavbf200el = 999, mvavbf250el = 999, mvavbf300el = 999, mvavbf350el = 999, mvavbf400el = 999, mvavbf450el = 999, mvavbf500el = 999, mvavbf550el = 999, mvavbf600el = 999;

   TBranch * branch_2j160el   =  newtree->Branch("mva2j160el",   &mva2j160el,    "mva2j160el/F");
   TBranch * branch_2j170el   =  newtree->Branch("mva2j170el",   &mva2j170el,    "mva2j170el/F");
   TBranch * branch_2j180el   =  newtree->Branch("mva2j180el",   &mva2j180el,    "mva2j180el/F");
   TBranch * branch_2j190el   =  newtree->Branch("mva2j190el",   &mva2j190el,    "mva2j190el/F");
   TBranch * branch_2j200el   =  newtree->Branch("mva2j200el",   &mva2j200el,    "mva2j200el/F");
   TBranch * branch_2j250el   =  newtree->Branch("mva2j250el",   &mva2j250el,    "mva2j250el/F");
   TBranch * branch_2j300el   =  newtree->Branch("mva2j300el",   &mva2j300el,    "mva2j300el/F");
   TBranch * branch_2j350el   =  newtree->Branch("mva2j350el",   &mva2j350el,    "mva2j350el/F");
   TBranch * branch_2j400el   =  newtree->Branch("mva2j400el",   &mva2j400el,    "mva2j400el/F");
   TBranch * branch_2j450el   =  newtree->Branch("mva2j450el",   &mva2j450el,    "mva2j450el/F");
   TBranch * branch_2j500el   =  newtree->Branch("mva2j500el",   &mva2j500el,    "mva2j500el/F");
   TBranch * branch_2j550el   =  newtree->Branch("mva2j550el",   &mva2j550el,    "mva2j550el/F");
   TBranch * branch_2j600el   =  newtree->Branch("mva2j600el",   &mva2j600el,    "mva2j600el/F");
   TBranch * branch_2j400interferencenominalel   =  newtree->Branch("mva2j400interferencenominalel",   &mva2j400interferencenominalel,    "mva2j400interferencenominalel/F");
   TBranch * branch_2j450interferencenominalel   =  newtree->Branch("mva2j450interferencenominalel",   &mva2j450interferencenominalel,    "mva2j450interferencenominalel/F");
   TBranch * branch_2j500interferencenominalel   =  newtree->Branch("mva2j500interferencenominalel",   &mva2j500interferencenominalel,    "mva2j500interferencenominalel/F");
   TBranch * branch_2j550interferencenominalel   =  newtree->Branch("mva2j550interferencenominalel",   &mva2j550interferencenominalel,    "mva2j550interferencenominalel/F");
   TBranch * branch_2j600interferencenominalel   =  newtree->Branch("mva2j600interferencenominalel",   &mva2j600interferencenominalel,    "mva2j600interferencenominalel/F");
   TBranch * branch_2j700interferencenominalel   =  newtree->Branch("mva2j700interferencenominalel",   &mva2j700interferencenominalel,    "mva2j700interferencenominalel/F");
   TBranch * branch_2j800interferencenominalel   =  newtree->Branch("mva2j800interferencenominalel",   &mva2j800interferencenominalel,    "mva2j800interferencenominalel/F");
   TBranch * branch_2j900interferencenominalel   =  newtree->Branch("mva2j900interferencenominalel",   &mva2j900interferencenominalel,    "mva2j900interferencenominalel/F");
   TBranch * branch_2j1000interferencenominalel   =  newtree->Branch("mva2j1000interferencenominalel",   &mva2j1000interferencenominalel,    "mva2j1000interferencenominalel/F");
   TBranch * branch_2j400interferenceupel   =  newtree->Branch("mva2j400interferenceupel",   &mva2j400interferenceupel,    "mva2j400interferenceupel/F");
   TBranch * branch_2j450interferenceupel   =  newtree->Branch("mva2j450interferenceupel",   &mva2j450interferenceupel,    "mva2j450interferenceupel/F");
   TBranch * branch_2j500interferenceupel   =  newtree->Branch("mva2j500interferenceupel",   &mva2j500interferenceupel,    "mva2j500interferenceupel/F");
   TBranch * branch_2j550interferenceupel   =  newtree->Branch("mva2j550interferenceupel",   &mva2j550interferenceupel,    "mva2j550interferenceupel/F");
   TBranch * branch_2j600interferenceupel   =  newtree->Branch("mva2j600interferenceupel",   &mva2j600interferenceupel,    "mva2j600interferenceupel/F");
   TBranch * branch_2j700interferenceupel   =  newtree->Branch("mva2j700interferenceupel",   &mva2j700interferenceupel,    "mva2j700interferenceupel/F");
   TBranch * branch_2j800interferenceupel   =  newtree->Branch("mva2j800interferenceupel",   &mva2j800interferenceupel,    "mva2j800interferenceupel/F");
   TBranch * branch_2j900interferenceupel   =  newtree->Branch("mva2j900interferenceupel",   &mva2j900interferenceupel,    "mva2j900interferenceupel/F");
   TBranch * branch_2j1000interferenceupel   =  newtree->Branch("mva2j1000interferenceupel",   &mva2j1000interferenceupel,    "mva2j1000interferenceupel/F");
   TBranch * branch_2j400interferencedownel   =  newtree->Branch("mva2j400interferencedownel",   &mva2j400interferencedownel,    "mva2j400interferencedownel/F");
   TBranch * branch_2j450interferencedownel   =  newtree->Branch("mva2j450interferencedownel",   &mva2j450interferencedownel,    "mva2j450interferencedownel/F");
   TBranch * branch_2j500interferencedownel   =  newtree->Branch("mva2j500interferencedownel",   &mva2j500interferencedownel,    "mva2j500interferencedownel/F");
   TBranch * branch_2j550interferencedownel   =  newtree->Branch("mva2j550interferencedownel",   &mva2j550interferencedownel,    "mva2j550interferencedownel/F");
   TBranch * branch_2j600interferencedownel   =  newtree->Branch("mva2j600interferencedownel",   &mva2j600interferencedownel,    "mva2j600interferencedownel/F");
   TBranch * branch_2j700interferencedownel   =  newtree->Branch("mva2j700interferencedownel",   &mva2j700interferencedownel,    "mva2j700interferencedownel/F");
   TBranch * branch_2j800interferencedownel   =  newtree->Branch("mva2j800interferencedownel",   &mva2j800interferencedownel,    "mva2j800interferencedownel/F");
   TBranch * branch_2j900interferencedownel   =  newtree->Branch("mva2j900interferencedownel",   &mva2j900interferencedownel,    "mva2j900interferencedownel/F");
   TBranch * branch_2j1000interferencedownel   =  newtree->Branch("mva2j1000interferencedownel",   &mva2j1000interferencedownel,    "mva2j1000interferencedownel/F");


   TBranch * branch_3j160el   =  newtree->Branch("mva3j160el",   &mva3j160el,    "mva3j160el/F");
   TBranch * branch_3j170el   =  newtree->Branch("mva3j170el",   &mva3j170el,    "mva3j170el/F");
   TBranch * branch_3j180el   =  newtree->Branch("mva3j180el",   &mva3j180el,    "mva3j180el/F");
   TBranch * branch_3j190el   =  newtree->Branch("mva3j190el",   &mva3j190el,    "mva3j190el/F");
   TBranch * branch_3j200el   =  newtree->Branch("mva3j200el",   &mva3j200el,    "mva3j200el/F");
   TBranch * branch_3j250el   =  newtree->Branch("mva3j250el",   &mva3j250el,    "mva3j250el/F");
   TBranch * branch_3j300el   =  newtree->Branch("mva3j300el",   &mva3j300el,    "mva3j300el/F");
   TBranch * branch_3j350el   =  newtree->Branch("mva3j350el",   &mva3j350el,    "mva3j350el/F");
   TBranch * branch_3j400el   =  newtree->Branch("mva3j400el",   &mva3j400el,    "mva3j400el/F");
   TBranch * branch_3j450el   =  newtree->Branch("mva3j450el",   &mva3j450el,    "mva3j450el/F");
   TBranch * branch_3j500el   =  newtree->Branch("mva3j500el",   &mva3j500el,    "mva3j500el/F");
   TBranch * branch_3j550el   =  newtree->Branch("mva3j550el",   &mva3j550el,    "mva3j550el/F");
   TBranch * branch_3j600el   =  newtree->Branch("mva3j600el",   &mva3j600el,    "mva3j600el/F");
   TBranch * branch_3j400interferencenominalel   =  newtree->Branch("mva3j400interferencenominalel",   &mva3j400interferencenominalel,    "mva3j400interferencenominalel/F");
   TBranch * branch_3j450interferencenominalel   =  newtree->Branch("mva3j450interferencenominalel",   &mva3j450interferencenominalel,    "mva3j450interferencenominalel/F");
   TBranch * branch_3j500interferencenominalel   =  newtree->Branch("mva3j500interferencenominalel",   &mva3j500interferencenominalel,    "mva3j500interferencenominalel/F");
   TBranch * branch_3j550interferencenominalel   =  newtree->Branch("mva3j550interferencenominalel",   &mva3j550interferencenominalel,    "mva3j550interferencenominalel/F");
   TBranch * branch_3j600interferencenominalel   =  newtree->Branch("mva3j600interferencenominalel",   &mva3j600interferencenominalel,    "mva3j600interferencenominalel/F");
   TBranch * branch_3j700interferencenominalel   =  newtree->Branch("mva3j700interferencenominalel",   &mva3j700interferencenominalel,    "mva3j700interferencenominalel/F");
   TBranch * branch_3j800interferencenominalel   =  newtree->Branch("mva3j800interferencenominalel",   &mva3j800interferencenominalel,    "mva3j800interferencenominalel/F");
   TBranch * branch_3j900interferencenominalel   =  newtree->Branch("mva3j900interferencenominalel",   &mva3j900interferencenominalel,    "mva3j900interferencenominalel/F");
   TBranch * branch_3j1000interferencenominalel   =  newtree->Branch("mva3j1000interferencenominalel",   &mva3j1000interferencenominalel,    "mva3j1000interferencenominalel/F");
   TBranch * branch_3j400interferenceupel   =  newtree->Branch("mva3j400interferenceupel",   &mva3j400interferenceupel,    "mva3j400interferenceupel/F");
   TBranch * branch_3j450interferenceupel   =  newtree->Branch("mva3j450interferenceupel",   &mva3j450interferenceupel,    "mva3j450interferenceupel/F");
   TBranch * branch_3j500interferenceupel   =  newtree->Branch("mva3j500interferenceupel",   &mva3j500interferenceupel,    "mva3j500interferenceupel/F");
   TBranch * branch_3j550interferenceupel   =  newtree->Branch("mva3j550interferenceupel",   &mva3j550interferenceupel,    "mva3j550interferenceupel/F");
   TBranch * branch_3j600interferenceupel   =  newtree->Branch("mva3j600interferenceupel",   &mva3j600interferenceupel,    "mva3j600interferenceupel/F");
   TBranch * branch_3j700interferenceupel   =  newtree->Branch("mva3j700interferenceupel",   &mva3j700interferenceupel,    "mva3j700interferenceupel/F");
   TBranch * branch_3j800interferenceupel   =  newtree->Branch("mva3j800interferenceupel",   &mva3j800interferenceupel,    "mva3j800interferenceupel/F");
   TBranch * branch_3j900interferenceupel   =  newtree->Branch("mva3j900interferenceupel",   &mva3j900interferenceupel,    "mva3j900interferenceupel/F");
   TBranch * branch_3j1000interferenceupel   =  newtree->Branch("mva3j1000interferenceupel",   &mva3j1000interferenceupel,    "mva3j1000interferenceupel/F");
   TBranch * branch_3j400interferencedownel   =  newtree->Branch("mva3j400interferencedownel",   &mva3j400interferencedownel,    "mva3j400interferencedownel/F");
   TBranch * branch_3j450interferencedownel   =  newtree->Branch("mva3j450interferencedownel",   &mva3j450interferencedownel,    "mva3j450interferencedownel/F");
   TBranch * branch_3j500interferencedownel   =  newtree->Branch("mva3j500interferencedownel",   &mva3j500interferencedownel,    "mva3j500interferencedownel/F");
   TBranch * branch_3j550interferencedownel   =  newtree->Branch("mva3j550interferencedownel",   &mva3j550interferencedownel,    "mva3j550interferencedownel/F");
   TBranch * branch_3j600interferencedownel   =  newtree->Branch("mva3j600interferencedownel",   &mva3j600interferencedownel,    "mva3j600interferencedownel/F");
   TBranch * branch_3j700interferencedownel   =  newtree->Branch("mva3j700interferencedownel",   &mva3j700interferencedownel,    "mva3j700interferencedownel/F");
   TBranch * branch_3j800interferencedownel   =  newtree->Branch("mva3j800interferencedownel",   &mva3j800interferencedownel,    "mva3j800interferencedownel/F");
   TBranch * branch_3j900interferencedownel   =  newtree->Branch("mva3j900interferencedownel",   &mva3j900interferencedownel,    "mva3j900interferencedownel/F");
   TBranch * branch_3j1000interferencedownel   =  newtree->Branch("mva3j1000interferencedownel",   &mva3j1000interferencedownel,    "mva3j1000interferencedownel/F");

   TBranch * branch_2jdibosonel   =  newtree->Branch("mva2jdibosonel",   &mva2jdibosonel,    "mva2jdibosonel/F");
   TBranch * branch_3jdibosonel   =  newtree->Branch("mva3jdibosonel",   &mva3jdibosonel,    "mva3jdibosonel/F");
   TBranch * branch_2jdibnoqgel   =  newtree->Branch("mva2jdibnoqgel",   &mva2jdibnoqgel,    "mva2jdibnoqgel/F");
   TBranch * branch_3jdibnoqgel   =  newtree->Branch("mva3jdibnoqgel",   &mva3jdibnoqgel,    "mva3jdibnoqgel/F");

   TBranch * branch_vbf160el   =  newtree->Branch("mvavbf160el",   &mvavbf160el,    "mvavbf160el/F");
   TBranch * branch_vbf170el   =  newtree->Branch("mvavbf170el",   &mvavbf170el,    "mvavbf170el/F");
   TBranch * branch_vbf180el   =  newtree->Branch("mvavbf180el",   &mvavbf180el,    "mvavbf180el/F");
   TBranch * branch_vbf190el   =  newtree->Branch("mvavbf190el",   &mvavbf190el,    "mvavbf190el/F");
   TBranch * branch_vbf200el   =  newtree->Branch("mvavbf200el",   &mvavbf200el,    "mvavbf200el/F");
   TBranch * branch_vbf250el   =  newtree->Branch("mvavbf250el",   &mvavbf250el,    "mvavbf250el/F");
   TBranch * branch_vbf300el   =  newtree->Branch("mvavbf300el",   &mvavbf300el,    "mvavbf300el/F");
   TBranch * branch_vbf350el   =  newtree->Branch("mvavbf350el",   &mvavbf350el,    "mvavbf350el/F");
   TBranch * branch_vbf400el   =  newtree->Branch("mvavbf400el",   &mvavbf400el,    "mvavbf400el/F");
   TBranch * branch_vbf450el   =  newtree->Branch("mvavbf450el",   &mvavbf450el,    "mvavbf450el/F");
   TBranch * branch_vbf500el   =  newtree->Branch("mvavbf500el",   &mvavbf500el,    "mvavbf500el/F");
   TBranch * branch_vbf550el   =  newtree->Branch("mvavbf550el",   &mvavbf550el,    "mvavbf550el/F");
   TBranch * branch_vbf600el   =  newtree->Branch("mvavbf600el",   &mvavbf600el,    "mvavbf600el/F");

   Float_t effwt = 1.0, puwt = 1.0, puwt_up = 1.0, puwt_down = 1.0;
   TBranch * branch_effwt          =  newtree->Branch("effwt",       &effwt,        "effwt/F");
   TBranch * branch_puwt           =  newtree->Branch("puwt",        &puwt,         "puwt/F");
   TBranch * branch_puwt_up        =  newtree->Branch("puwt_up",     &puwt_up,      "puwt_up/F");
   TBranch * branch_puwt_down      =  newtree->Branch("puwt_down",   &puwt_down,    "puwt_down/F");

   Float_t interferencewtggH400 = 1.0, interferencewtggH450 = 1.0, interferencewtggH500 = 1.0, interferencewtggH550 = 1.0, interferencewtggH600 = 1.0, interferencewtggH700 = 1.0, interferencewtggH800 = 1.0, interferencewtggH900 = 1.0, interferencewtggH1000 = 1.0;
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

   //End for the ttH analysis

   // For MVA analysis
   const char* inputVars[] = { "ptlvjj", "ylvjj", "W_muon_charge", "ang_ha", "ang_hb", "ang_hs", "ang_phi", "ang_phib" };
   const char* inputVars_v2[] = { "ptlvjj", "ylvjj", "W_electron_charge", "ang_ha", "ang_hb", "ang_hs", "ang_phi", "ang_phib" };
   std::vector<std::string> inputVarsMVA;
   for (int i=0; i<8; ++i) inputVarsMVA.push_back( inputVars[i] );
   std::vector<std::string> inputVarsMVA_v2;
   for (int i=0; i<8; ++i) inputVarsMVA_v2.push_back( inputVars_v2[i] );

   ReadMVA2j170el mvaReader2j170el( inputVarsMVA );  
   ReadMVA2j180el mvaReader2j180el( inputVarsMVA );  
   ReadMVA2j190el mvaReader2j190el( inputVarsMVA );  
   ReadMVA2j200el mvaReader2j200el( inputVarsMVA );  
   ReadMVA2j250el mvaReader2j250el( inputVarsMVA );  
   ReadMVA2j300el mvaReader2j300el( inputVarsMVA );  
   ReadMVA2j350el mvaReader2j350el( inputVarsMVA );  
   ReadMVA2j400el mvaReader2j400el( inputVarsMVA );  
   ReadMVA2j450el mvaReader2j450el( inputVarsMVA );  
   ReadMVA2j500el mvaReader2j500el( inputVarsMVA );  
   ReadMVA2j550el mvaReader2j550el( inputVarsMVA );  
   ReadMVA2j600el mvaReader2j600el( inputVarsMVA );  
   ReadMVA2j400interferencedownel mvaReader2j400interferencedownel( inputVarsMVA_v2 );
   ReadMVA2j400interferencenominalel mvaReader2j400interferencenominalel( inputVarsMVA_v2 );
   ReadMVA2j400interferenceupel mvaReader2j400interferenceupel( inputVarsMVA_v2 );
   ReadMVA2j450interferencedownel mvaReader2j450interferencedownel( inputVarsMVA_v2 );
   ReadMVA2j450interferencenominalel mvaReader2j450interferencenominalel( inputVarsMVA_v2 );
   ReadMVA2j450interferenceupel mvaReader2j450interferenceupel( inputVarsMVA_v2 );
   ReadMVA2j500interferencedownel mvaReader2j500interferencedownel( inputVarsMVA_v2 );
   ReadMVA2j500interferencenominalel mvaReader2j500interferencenominalel( inputVarsMVA_v2 );
   ReadMVA2j500interferenceupel mvaReader2j500interferenceupel( inputVarsMVA_v2 );
   ReadMVA2j550interferencedownel mvaReader2j550interferencedownel( inputVarsMVA_v2 );
   ReadMVA2j550interferencenominalel mvaReader2j550interferencenominalel( inputVarsMVA_v2 );
   ReadMVA2j550interferenceupel mvaReader2j550interferenceupel( inputVarsMVA_v2 );
   ReadMVA2j600interferencedownel mvaReader2j600interferencedownel( inputVarsMVA_v2 );
   ReadMVA2j600interferencenominalel mvaReader2j600interferencenominalel( inputVarsMVA_v2 );
   ReadMVA2j600interferenceupel mvaReader2j600interferenceupel( inputVarsMVA_v2 );
   ReadMVA2j700interferencedownel mvaReader2j700interferencedownel( inputVarsMVA_v2 );
   ReadMVA2j700interferencenominalel mvaReader2j700interferencenominalel( inputVarsMVA_v2 );
   ReadMVA2j700interferenceupel mvaReader2j700interferenceupel( inputVarsMVA_v2 );
   ReadMVA2j800interferencedownel mvaReader2j800interferencedownel( inputVarsMVA_v2 );
   ReadMVA2j800interferencenominalel mvaReader2j800interferencenominalel( inputVarsMVA_v2 );
   ReadMVA2j800interferenceupel mvaReader2j800interferenceupel( inputVarsMVA_v2 );
   ReadMVA2j900interferencedownel mvaReader2j900interferencedownel( inputVarsMVA_v2 );
   ReadMVA2j900interferencenominalel mvaReader2j900interferencenominalel( inputVarsMVA_v2 );
   ReadMVA2j900interferenceupel mvaReader2j900interferenceupel( inputVarsMVA_v2 );
   ReadMVA2j1000interferencedownel mvaReader2j1000interferencedownel( inputVarsMVA_v2 );
   ReadMVA2j1000interferencenominalel mvaReader2j1000interferencenominalel( inputVarsMVA_v2 );
   ReadMVA2j1000interferenceupel mvaReader2j1000interferenceupel( inputVarsMVA_v2 );

   ReadMVA3j170el mvaReader3j170el( inputVarsMVA );  
   ReadMVA3j180el mvaReader3j180el( inputVarsMVA );  
   ReadMVA3j190el mvaReader3j190el( inputVarsMVA );  
   ReadMVA3j200el mvaReader3j200el( inputVarsMVA );  
   ReadMVA3j250el mvaReader3j250el( inputVarsMVA );  
   ReadMVA3j300el mvaReader3j300el( inputVarsMVA );  
   ReadMVA3j350el mvaReader3j350el( inputVarsMVA );  
   ReadMVA3j400el mvaReader3j400el( inputVarsMVA );  
   ReadMVA3j450el mvaReader3j450el( inputVarsMVA );  
   ReadMVA3j500el mvaReader3j500el( inputVarsMVA );  
   ReadMVA3j550el mvaReader3j550el( inputVarsMVA );  
   ReadMVA3j600el mvaReader3j600el( inputVarsMVA );  
   ReadMVA3j400interferencedownel mvaReader3j400interferencedownel( inputVarsMVA_v2 );
   ReadMVA3j400interferencenominalel mvaReader3j400interferencenominalel( inputVarsMVA_v2 );
   ReadMVA3j400interferenceupel mvaReader3j400interferenceupel( inputVarsMVA_v2 );
   ReadMVA3j450interferencedownel mvaReader3j450interferencedownel( inputVarsMVA_v2 );
   ReadMVA3j450interferencenominalel mvaReader3j450interferencenominalel( inputVarsMVA_v2 );
   ReadMVA3j450interferenceupel mvaReader3j450interferenceupel( inputVarsMVA_v2 );
   ReadMVA3j500interferencedownel mvaReader3j500interferencedownel( inputVarsMVA_v2 );
   ReadMVA3j500interferencenominalel mvaReader3j500interferencenominalel( inputVarsMVA_v2 );
   ReadMVA3j500interferenceupel mvaReader3j500interferenceupel( inputVarsMVA_v2 );
   ReadMVA3j550interferencedownel mvaReader3j550interferencedownel( inputVarsMVA_v2 );
   ReadMVA3j550interferencenominalel mvaReader3j550interferencenominalel( inputVarsMVA_v2 );
   ReadMVA3j550interferenceupel mvaReader3j550interferenceupel( inputVarsMVA_v2 );
   ReadMVA3j600interferencedownel mvaReader3j600interferencedownel( inputVarsMVA_v2 );
   ReadMVA3j600interferencenominalel mvaReader3j600interferencenominalel( inputVarsMVA_v2 );
   ReadMVA3j600interferenceupel mvaReader3j600interferenceupel( inputVarsMVA_v2 );
   ReadMVA3j700interferencedownel mvaReader3j700interferencedownel( inputVarsMVA_v2 );
   ReadMVA3j700interferencenominalel mvaReader3j700interferencenominalel( inputVarsMVA_v2 );
   ReadMVA3j700interferenceupel mvaReader3j700interferenceupel( inputVarsMVA_v2 );
   ReadMVA3j800interferencedownel mvaReader3j800interferencedownel( inputVarsMVA_v2 );
   ReadMVA3j800interferencenominalel mvaReader3j800interferencenominalel( inputVarsMVA_v2 );
   ReadMVA3j800interferenceupel mvaReader3j800interferenceupel( inputVarsMVA_v2 );
   ReadMVA3j900interferencedownel mvaReader3j900interferencedownel( inputVarsMVA_v2 );
   ReadMVA3j900interferencenominalel mvaReader3j900interferencenominalel( inputVarsMVA_v2 );
   ReadMVA3j900interferenceupel mvaReader3j900interferenceupel( inputVarsMVA_v2 );
   ReadMVA3j1000interferencedownel mvaReader3j1000interferencedownel( inputVarsMVA_v2 );
   ReadMVA3j1000interferencenominalel mvaReader3j1000interferencenominalel( inputVarsMVA_v2 );
   ReadMVA3j1000interferenceupel mvaReader3j1000interferenceupel( inputVarsMVA_v2 );

   const char* DB_inputVars[] = { "W_pt", "event_met_pfmet", "W_muon_charge", "JetPFCor_QGLikelihood[0]", "JetPFCor_QGLikelihood[1]", "ang_hs", "ang_phib", "abs(JetPFCor_Eta[0]-JetPFCor_Eta[1])", "masslvjj" };
   std::vector<std::string> DB_inputVarsMVA;
   for (int i=0; i<9; ++i)  DB_inputVarsMVA.push_back( DB_inputVars[i] );
   ReadMVA2jdibosonel mvaReader2jdibosonel( DB_inputVarsMVA ); 
   ReadMVA3jdibosonel mvaReader3jdibosonel( DB_inputVarsMVA ); 

   const char* DBnoqg_inputVars[] = { "W_pt", "event_met_pfmet", "W_muon_charge", "ang_hs", "ang_phib", "abs(JetPFCor_Eta[0]-JetPFCor_Eta[1])", "masslvjj" };
   std::vector<std::string> DBnoqg_inputVarsMVA;
   for (int i=0; i<7; ++i)  DBnoqg_inputVarsMVA.push_back( DBnoqg_inputVars[i] );
   ReadMVA2jdibnoqgel mvaReader2jdibnoqgel( DBnoqg_inputVarsMVA ); 
   ReadMVA3jdibnoqgel mvaReader3jdibnoqgel( DBnoqg_inputVarsMVA ); 

   //const char* vbf_inputVars[] = { "vbf_lvjj_pt", "vbf_lvjj_y", "W_muon_charge", "vbf_wjj_ang_ha", "vbf_wjj_ang_hb", "vbf_wjj_ang_hs", "vbf_wjj_ang_phi", "vbf_wjj_ang_phib", "vbf_jj_deta", "vbf_jj_m" };
   const char* vbf_inputVars[] = { "vbf_lvjj_pt", "vbf_lvjj_y", "W_electron_charge", "vbf_wjj_ang_ha", "vbf_wjj_ang_hb", "vbf_wjj_ang_hs", "vbf_wjj_ang_phi", "vbf_wjj_ang_phib"}; //Be Careful we fix the electron charge problem
   std::vector<std::string> vbf_inputVarsMVA;
   //for (int i=0; i<10; ++i) vbf_inputVarsMVA.push_back( vbf_inputVars[i] );
   for (int i=0; i<8; ++i) vbf_inputVarsMVA.push_back( vbf_inputVars[i] );

   ReadMVAVBF170el mvaReadervbf170el( vbf_inputVarsMVA );   
   ReadMVAVBF180el mvaReadervbf180el( vbf_inputVarsMVA );   
   ReadMVAVBF190el mvaReadervbf190el( vbf_inputVarsMVA );   
   ReadMVAVBF200el mvaReadervbf200el( vbf_inputVarsMVA );   
   ReadMVAVBF250el mvaReadervbf250el( vbf_inputVarsMVA );   
   ReadMVAVBF300el mvaReadervbf300el( vbf_inputVarsMVA );   
   ReadMVAVBF350el mvaReadervbf350el( vbf_inputVarsMVA );   
   ReadMVAVBF400el mvaReadervbf400el( vbf_inputVarsMVA );   
   ReadMVAVBF450el mvaReadervbf450el( vbf_inputVarsMVA );   
   ReadMVAVBF500el mvaReadervbf500el( vbf_inputVarsMVA );   
   ReadMVAVBF550el mvaReadervbf550el( vbf_inputVarsMVA );   
   ReadMVAVBF600el mvaReadervbf600el( vbf_inputVarsMVA );

   // For Efficiency Correction
   //EffTableLoader eleIdEff(         fDir + "scaleFactor-2012A-PromptReco-v1-GsfElectronToId.txt");
   //EffTableLoader eleRecoEff(       fDir + "scaleFactor-2012A-PromptReco-v1-SCToElectron.txt");
   //EffTableLoader eleHLTEff(        fDir + "efficiency-2012A_PromptReco_v1-WP80ToHLTEle.txt");

   //EffTableLoader eleIdEff(         fDir + "scaleFactor-Run2012ABC-GsfElectronToId.txt");
   //EffTableLoader eleRecoEff(       fDir + "scaleFactor-Run2012ABC-SCToElectron.txt");
   //EffTableLoader eleHLTEff(        fDir + "efficiency-Run2012ABC-WP80ToHLTEle.txt");
   EffTableLoader eleIdEff(         fDir + "scaleFactor-Run2012ABCD-GsfElectronToId.txt");
   EffTableLoader eleRecoEff(       fDir + "scaleFactor-Run2012ABCD-SCToElectron.txt");
   EffTableLoader eleHLTEff(        fDir + "efficiency-Run2012ABCD-WP80ToHLTEle.txt");
   EffTableLoader eleJ30Eff(        fDir + "FullyEfficient.txt");
   EffTableLoader eleJ25NoJ30Eff(   fDir + "FullyEfficient_Jet2NoJet1.txt");
   EffTableLoader eleMHTEff(        fDir + "FullyEfficient_MHT.txt");
   //  EffTableLoader eleWMtEff(        fDir + "WMt50TriggerEfficiency.txt");
   EffTableLoader eleWMtEff(        fDir + "FullyEfficient.txt");

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
   const double btssv                 = 1.74;  // BTagging
   const double btcsvm                = 0.679; //CSVM
   const double btcsvl                = 0.244; //CSVL
   const double boostedWJpt           = 80;   // Conservative boosted Jet cut
   const double boostedWtranpt        = 150;
   //const double VBF_MaxEta            = 4.5;   // VBF jet max eta
   const double VBF_MaxEta            = 4.7;   // VBF jet max eta to 4.7
   const double mtop                  = 172.5; //Top mass
   // Loop over all events
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      //Long64_t ientry = LoadTree(jentry);
      //if (ientry < 0) break;
      nb = newtree->GetEntry(jentry);   nbytes += nb;
      // Cut variable definitions
      double jess    = 1.00; // control the jet energy scale
      //    double electroniso = (W_electron_pfiso_chargedHadronIso+W_electron_pfiso_photonIso+W_electron_pfiso_neutralHadronIso-event_RhoForLeptonIsolation*3.141592653589*0.09)/W_electron_pt;
      double EffectiveArea =0;
      double SCEta = W_electron_eta;
      if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.100;
      if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.120;
      if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.085;
      if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.110;
      if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.120;
      if (fabs(SCEta) >= 2.3 && fabs(SCEta) < 2.4 ) EffectiveArea = 0.120;
      if (fabs(SCEta) >= 2.4) EffectiveArea = 0.130;
      double electroniso = (W_electron_pfiso_chargedHadronIso+max(0.,W_electron_pfiso_photonIso+W_electron_pfiso_neutralHadronIso-event_fastJetRho*EffectiveArea))/W_electron_pt;
      //    cout<<"El iso  "<<electroniso<<endl;
      double dijetpt = sqrt(JetPFCor_Pt[0]*JetPFCor_Pt[0]+
            JetPFCor_Pt[1]*JetPFCor_Pt[1]+
            2*JetPFCor_Pt[0]*JetPFCor_Pt[1]*cos(JetPFCor_Phi[0]-JetPFCor_Phi[1]));

      // Save variable initialization
      ggdevt    = 0;
      evtNJ     = 0;
      ggdevtinclusive = 0;

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

      mva2j160el = 999; mva2j170el = 999; mva2j180el = 999; mva2j190el = 999; mva2j200el = 999; mva2j250el = 999; mva2j300el = 999; mva2j350el = 999; mva2j400el = 999; mva2j450el = 999; mva2j500el = 999; mva2j550el = 999; mva2j600el = 999;
      mva2j400interferencenominalel = 999; mva2j450interferencenominalel = 999; mva2j500interferencenominalel = 999; mva2j550interferencenominalel = 999; mva2j600interferencenominalel = 999; mva2j700interferencenominalel = 999; mva2j800interferencenominalel = 999; mva2j900interferencenominalel = 999; mva2j1000interferencenominalel = 999;
      mva2j400interferencedownel = 999; mva2j450interferencedownel = 999; mva2j500interferencedownel = 999; mva2j550interferencedownel = 999; mva2j600interferencedownel = 999;  mva2j700interferencedownel = 999; mva2j800interferencedownel = 999; mva2j900interferencedownel = 999; mva2j1000interferencedownel = 999;
      mva2j400interferenceupel = 999; mva2j450interferenceupel = 999; mva2j500interferenceupel = 999; mva2j550interferenceupel = 999; mva2j600interferenceupel = 999; mva2j700interferenceupel = 999; mva2j800interferenceupel = 999; mva2j900interferenceupel = 999; mva2j1000interferenceupel = 999;
      mva3j160el = 999; mva3j170el = 999; mva3j180el = 999; mva3j190el = 999; mva3j200el = 999; mva3j250el = 999; mva3j300el = 999; mva3j350el = 999; mva3j400el = 999; mva3j450el = 999; mva3j500el = 999; mva3j550el = 999; mva3j600el = 999;
      mva3j400interferencenominalel = 999; mva3j450interferencenominalel = 999; mva3j500interferencenominalel = 999; mva3j550interferencenominalel = 999; mva3j600interferencenominalel = 999; mva3j700interferencenominalel = 999; mva3j800interferencenominalel = 999; mva3j900interferencenominalel = 999; mva3j1000interferencenominalel = 999;
      mva3j400interferencedownel = 999; mva3j450interferencedownel = 999; mva3j500interferencedownel = 999; mva3j550interferencedownel = 999; mva3j600interferencedownel = 999;  mva3j700interferencedownel = 999; mva3j800interferencedownel = 999; mva3j900interferencedownel = 999; mva3j1000interferencedownel = 999;
      mva3j400interferenceupel = 999; mva3j450interferenceupel = 999; mva3j500interferenceupel = 999; mva3j550interferenceupel = 999; mva3j600interferenceupel = 999; mva3j700interferenceupel = 999; mva3j800interferenceupel = 999; mva3j900interferenceupel = 999; mva3j1000interferenceupel = 999;
      mva2jdibosonel = 999; mva3jdibosonel = 999; mva2jdibnoqgel = 999; mva3jdibnoqgel = 999;
      mvavbf160el = 999; mvavbf170el = 999; mvavbf180el = 999; mvavbf190el = 999; mvavbf200el = 999; mvavbf250el = 999; mvavbf300el = 999; mvavbf350el = 999; mvavbf400el = 999; mvavbf450el = 999; mvavbf500el = 999; mvavbf550el = 999; mvavbf600el = 999;


      effwt = 1.0; puwt = 1.0; puwt_up = 1.0; puwt_down = 1.0;
      qgld_Spring11[0]= -1;       qgld_Spring11[1]= -1;       qgld_Spring11[2]= -1;       qgld_Spring11[3]= -1;       qgld_Spring11[4]= -1;       qgld_Spring11[5]= -1;
      qgld_Summer11[0]= -1;       qgld_Summer11[1]= -1;       qgld_Summer11[2]= -1;       qgld_Summer11[3]= -1;       qgld_Summer11[4]= -1;       qgld_Summer11[5]= -1;
      qgld_Summer11CHS[0]= -1;    qgld_Summer11CHS[1]= -1;    qgld_Summer11CHS[2]= -1;    qgld_Summer11CHS[3]= -1;    qgld_Summer11CHS[4]= -1;    qgld_Summer11CHS[5]= -1;

      interferencewtggH400 = 1.0; interferencewtggH450 = 1.0; interferencewtggH500 = 1.0; interferencewtggH550 = 1.0; interferencewtggH600 = 1.0; interferencewtggH700 = 1.0; interferencewtggH800 = 1.0; interferencewtggH900 = 1.0; interferencewtggH1000 = 1.0;
      interferencewt_upggH400 = 1.0; interferencewt_upggH450 = 1.0; interferencewt_upggH500 = 1.0; interferencewt_upggH550 = 1.0; interferencewt_upggH600 = 1.0; interferencewt_upggH700 = 1.0; interferencewt_upggH800 = 1.0; interferencewt_upggH900 = 1.0; interferencewt_upggH1000 = 1.0;
      interferencewt_downggH400 = 1.0; interferencewt_downggH450 = 1.0; interferencewt_downggH500 = 1.0; interferencewt_downggH550 = 1.0; interferencewt_downggH600 = 1.0; interferencewt_downggH700 = 1.0; interferencewt_downggH800 = 1.0; interferencewt_downggH900 = 1.0; interferencewt_downggH1000 = 1.0;

      //Complex Pole Weight
      complexpolewtggH180 = 1.0; complexpolewtggH190 = 1.0; complexpolewtggH200 = 1.0; complexpolewtggH250 = 1.0; complexpolewtggH300 = 1.0; complexpolewtggH350 = 1.0; complexpolewtggH400 = 1.0; complexpolewtggH450 = 1.0; complexpolewtggH500 = 1.0; complexpolewtggH550 = 1.0; complexpolewtggH600 = 1.0; complexpolewtggH700 = 1.0; complexpolewtggH800 = 1.0; complexpolewtggH900 = 1.0; complexpolewtggH1000 = 1.0;

      //Average Complex Pole Weight for normalization
      avecomplexpolewtggH180 = 1.0; avecomplexpolewtggH190 = 1.0; avecomplexpolewtggH200 = 1.0; avecomplexpolewtggH250 = 1.0; avecomplexpolewtggH300 = 1.0; avecomplexpolewtggH350 = 1.0; avecomplexpolewtggH400 = 1.0; avecomplexpolewtggH450 = 1.0; avecomplexpolewtggH500 = 1.0; avecomplexpolewtggH550 = 1.0; avecomplexpolewtggH600 = 1.0; avecomplexpolewtggH700 = 1.0; avecomplexpolewtggH800 = 1.0; avecomplexpolewtggH900 = 1.0; avecomplexpolewtggH1000 = 1.0;

      isgengdboostedWevt = 0; ggdboostedWevt = 0;  GroomedJet_numberbjets_csvm = 0; GroomedJet_numberbjets_csvl = 0; GroomedJet_numberbjets_ssvhem = 0; GroomedJet_numberbjets_csvl_veto = 0; GroomedJet_numberbjets_csvm_veto = 0; GroomedJet_numberbjets_ssvhem_veto = 0; GroomedJet_numberjets = 0;

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
         eleIdEff.GetEfficiency(W_electron_pt, W_electron_eta) * 
         eleRecoEff.GetEfficiency(W_electron_pt, W_electron_eta) *
         eleHLTEff.GetEfficiency(W_electron_pt, W_electron_eta) *
         eleMHTEff.GetEfficiency(event_met_pfmet, 0) *
         eleWMtEff.GetEfficiency(W_mt, W_electron_eta);

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
      //   if (JetPFCor_Pt[iJet]<0) continue;
      //      qgld_Spring11[iJet]= qglikeli_Spring11->computeQGLikelihoodPU( JetPFCor_Pt[iJet], event_RhoForLeptonIsolation, 
      //								     JetPFCor_ChargedMultiplicity[iJet], 
      //								     JetPFCor_NeutralMultiplicity[iJet], 
      //								     JetPFCor_PtD[iJet]);	 
      //      qgld_Summer11[iJet]= qglikeli_Summer11->computeQGLikelihoodPU( JetPFCor_Pt[iJet], event_RhoForLeptonIsolation, 
      //								     JetPFCor_ChargedMultiplicity[iJet], 
      //								     JetPFCor_NeutralMultiplicity[iJet], 
      //								     JetPFCor_PtD[iJet]);	 
      //   qgld_Summer11CHS[iJet]= qglikeli_Summer11CHS->computeQGLikelihoodPU( JetPFCor_Pt[iJet], event_RhoForLeptonIsolationCHS, 
      //         JetPFCor_ChargedMultiplicity[iJet], 
      //         JetPFCor_NeutralMultiplicity[iJet], 
      //         JetPFCor_PtD[iJet]);	 
      //}

      if (wda>20120999) {

         if(W_H_mass_gen > 0) //Real generated Mass Just for the ggH Signal Sample
         {
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
            interferencewtggH500=1.0; interferencewtggH550=1.0; interferencewtggH600=1.0;interferencewtggH700=1.0;interferencewtggH800=1.0;interferencewtggH900=1.0;interferencewtggH1000=1.0;
            interferencewt_upggH500=1.0; interferencewt_upggH550=1.0;interferencewt_upggH600=1.0;interferencewt_upggH700=1.0;interferencewt_upggH800=1.0;interferencewt_upggH900=1.0;interferencewt_upggH1000=1.0;
            interferencewt_downggH500=1.0; interferencewt_downggH550=1.0; interferencewt_downggH600=1.0;interferencewt_downggH700=1.0;interferencewt_downggH800=1.0;interferencewt_downggH900=1.0;interferencewt_downggH1000=1.0;
            complexpolewtggH180 = 1.0; complexpolewtggH190 = 1.0; complexpolewtggH200 = 1.0; complexpolewtggH250 = 1.0; complexpolewtggH300 = 1.0; complexpolewtggH350 = 1.0; complexpolewtggH400 = 1.0; complexpolewtggH450 = 1.0; complexpolewtggH500 = 1.0; complexpolewtggH550 = 1.0; complexpolewtggH600 = 1.0; complexpolewtggH700 = 1.0; complexpolewtggH800 = 1.0; complexpolewtggH900 = 1.0; complexpolewtggH1000 = 1.0;
            avecomplexpolewtggH180 = 1.0; avecomplexpolewtggH190 = 1.0; avecomplexpolewtggH200 = 1.0; avecomplexpolewtggH250 = 1.0; avecomplexpolewtggH300 = 1.0; avecomplexpolewtggH350 = 1.0; avecomplexpolewtggH400 = 1.0; avecomplexpolewtggH450 = 1.0; avecomplexpolewtggH500 = 1.0; avecomplexpolewtggH550 = 1.0; avecomplexpolewtggH600 = 1.0; avecomplexpolewtggH700 = 1.0; avecomplexpolewtggH800 = 1.0; avecomplexpolewtggH900 = 1.0; avecomplexpolewtggH1000 = 1.0;
         }
      }else{
         interferencewtggH500=1.0; interferencewtggH550=1.0; interferencewtggH600=1.0;interferencewtggH700=1.0;interferencewtggH800=1.0;interferencewtggH900=1.0;interferencewtggH1000=1.0;
         interferencewt_upggH500=1.0; interferencewt_upggH550=1.0; interferencewt_upggH600=1.0;interferencewt_upggH700=1.0;interferencewt_upggH800=1.0;interferencewt_upggH900=1.0;interferencewt_upggH1000=1.0;
         interferencewt_downggH500=1.0; interferencewt_downggH550=1.0; interferencewt_downggH600=1.0;interferencewt_downggH600=1.0;interferencewt_downggH700=1.0;interferencewt_downggH800=1.0;interferencewt_downggH900=1.0;interferencewt_downggH1000=1.0;
         complexpolewtggH180 = 1.0; complexpolewtggH190 = 1.0; complexpolewtggH200 = 1.0; complexpolewtggH250 = 1.0; complexpolewtggH300 = 1.0; complexpolewtggH350 = 1.0; complexpolewtggH400 = 1.0; complexpolewtggH450 = 1.0; complexpolewtggH500 = 1.0; complexpolewtggH550 = 1.0; complexpolewtggH600 = 1.0; complexpolewtggH700 = 1.0; complexpolewtggH800 = 1.0; complexpolewtggH900 = 1.0; complexpolewtggH1000 = 1.0;
         avecomplexpolewtggH180 = 1.0; avecomplexpolewtggH190 = 1.0; avecomplexpolewtggH200 = 1.0; avecomplexpolewtggH250 = 1.0; avecomplexpolewtggH300 = 1.0; avecomplexpolewtggH350 = 1.0; avecomplexpolewtggH400 = 1.0; avecomplexpolewtggH450 = 1.0; avecomplexpolewtggH500 = 1.0; avecomplexpolewtggH550 = 1.0; avecomplexpolewtggH600 = 1.0; avecomplexpolewtggH700 = 1.0; avecomplexpolewtggH800 = 1.0; avecomplexpolewtggH900 = 1.0; avecomplexpolewtggH1000 = 1.0;
      }


      // Good Event Selection Requirement for all events
      int istep = 8; //starting selection step after preselection
      bool  isgengdevt = 0;

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
               if ( W_electron_et>30. ) { 
                  //&& sqrt((W_electron_vx-event_BeamSpot_x)*(W_electron_vx-event_BeamSpot_x)+(W_electron_vy-event_BeamSpot_y)*(W_electron_vy-event_BeamSpot_y))<0.02 // remove the impact parameter cut for electron only
                  h_events          -> Fill ( istep ); 
                  h_events_weighted -> Fill ( istep, effwt*puwt ); 
                  istep++;
                  isgengdevt = 1;
               }
            }
         }
      }

      // Event Selection Requirement for Standard vs QCD events
      if ( !isQCD ) {
         //keep electrons with event_met_pfmet>30.0 and passing MVA WP70 & EffArea PFiso.
         if ( !(event_met_pfmet>30.)  ) isgengdevt=0;
         // The following requirement is already asked in the Ntuples, Passing MVA WP80 for HCP2012
         /*if (fabs(W_electron_dist) < 0.02 && fabs(W_electron_dcot) < 0.02) isgengdevt=0;
           if ( fabs(W_electron_eta) <= 0.8 && electroniso > 0.093   ) isgengdevt=0;
           if ( fabs(W_electron_eta) > 0.8 &&  fabs(W_electron_eta) < 1.479  &&electroniso > 0.095   ) isgengdevt=0;
           if ( fabs(W_electron_eta) > 1.479 && electroniso > 0.171   ) isgengdevt=0;
          */
      } else {
         //keep electrons with MVAout>-1.
         if ( !( (-1.<W_electron_mvaTrigV0) )  ) isgengdevt=0;
         //      if ( !( (0.177<W_electron_pfIsoEA) )  ) isgengdevt=0;
      }

      // Fill lepton information
      TLorentzVector  mup, nvp;
      mup.SetPtEtaPhiE(W_electron_pt,      W_electron_eta,   W_electron_phi,   W_electron_e               );
      nvp.SetPxPyPzE(event_met_pfmet * cos(event_met_pfmetPhi), event_met_pfmet * sin(event_met_pfmetPhi), 
            W_pzNu1, sqrt(event_met_pfmet*event_met_pfmet + W_pzNu1*W_pzNu1)                     );
      TLorentzVector b_metpt; b_metpt.SetPxPyPzE(event_met_pfmet * cos(event_met_pfmetPhi), event_met_pfmet * sin(event_met_pfmetPhi), 0, sqrt(event_met_pfmet*event_met_pfmet) );
      METzCalculator b_metpz;
      b_metpz.SetMET(b_metpt);
      b_metpz.SetLepton(mup);
      b_metpz.SetLeptonType("electron");
      double b_nvpz = b_metpz.Calculate(); // Default one
      TLorentzVector b_nvp; b_nvp.SetPxPyPzE(b_metpt.Px(), b_metpt.Py(), b_nvpz, sqrt(b_metpt.Px()*b_metpt.Px() + b_metpt.Py()*b_metpt.Py() + b_nvpz*b_nvpz) );
      if (b_metpz.IsComplex()) {// if this is a complix, change MET
         double nu_pt1 = b_metpz.getPtneutrino(1);
         double nu_pt2 = b_metpz.getPtneutrino(2);
         TLorentzVector tmpp1; tmpp1.SetPxPyPzE(nu_pt1 * cos(event_met_pfmetPhi), nu_pt1 * sin(event_met_pfmetPhi), b_nvpz, sqrt(nu_pt1*nu_pt1 + b_nvpz*b_nvpz) );
         TLorentzVector tmpp2; tmpp2.SetPxPyPzE(nu_pt2 * cos(event_met_pfmetPhi), nu_pt2 * sin(event_met_pfmetPhi), b_nvpz, sqrt(nu_pt2*nu_pt2 + b_nvpz*b_nvpz) );
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
            && W_electron_pt>30.
            && lepwtransversept > boostedWtranpt
        ) {isgengdboostedWevt = 1;}

      // Event Selection Requirement for Standard vs QCD events
      if ( !isQCD ) {
         //keep electrons with event_met_pfmet>30.0 and passing MVA WP70 & EffArea PFiso.
         if ( !(event_met_pfmet>30.)  ) isgengdevt=0;
         // The following requirement is already asked in the Ntuples, Passing MVA WP80 for HCP2012 
         /*if (fabs(W_electron_dist) < 0.02 && fabs(W_electron_dcot) < 0.02) isgengdboostedWevt=0;
           if ( fabs(W_electron_eta) <= 0.8 && electroniso > 0.093   ) isgengdboostedWevt=0;
           if ( fabs(W_electron_eta) > 0.8 &&  fabs(W_electron_eta) < 1.479  &&electroniso > 0.095   ) isgengdboostedWevt=0;
           if ( fabs(W_electron_eta) > 1.479 && electroniso > 0.171   ) isgengdboostedWevt=0;
          */
      } else {
         //keep electrons with MVAout>-1.
         if ( !( (-1.<W_electron_mvaTrigV0) )  ) isgengdboostedWevt=0;
         //      if ( !( (0.177<W_electron_pfIsoEA) )  ) isgengdevt=0;

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
         if (W_electron_charge < 0){
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
         mvaInputVal.push_back( W_electron_charge );   ///////different for electron and muon
         //mvaInputVal.push_back( JetPFCor_QGLikelihood[0] );
         //mvaInputVal.push_back( JetPFCor_QGLikelihood[1] );
         mvaInputVal.push_back( ang_ha );
         mvaInputVal.push_back( ang_hb );
         mvaInputVal.push_back( ang_hs );
         mvaInputVal.push_back( ang_phi );
         mvaInputVal.push_back( ang_phib );

         mva2j170el = (float) mvaReader2j170el.GetMvaValue( mvaInputVal );
         mva2j180el = (float) mvaReader2j180el.GetMvaValue( mvaInputVal );
         mva2j190el = (float) mvaReader2j190el.GetMvaValue( mvaInputVal );
         mva2j200el = (float) mvaReader2j200el.GetMvaValue( mvaInputVal );
         mva2j250el = (float) mvaReader2j250el.GetMvaValue( mvaInputVal );
         mva2j300el = (float) mvaReader2j300el.GetMvaValue( mvaInputVal );
         mva2j350el = (float) mvaReader2j350el.GetMvaValue( mvaInputVal );
         mva2j400el = (float) mvaReader2j400el.GetMvaValue( mvaInputVal );
         mva2j450el = (float) mvaReader2j450el.GetMvaValue( mvaInputVal );
         mva2j500el = (float) mvaReader2j500el.GetMvaValue( mvaInputVal );
         mva2j550el = (float) mvaReader2j550el.GetMvaValue( mvaInputVal );
         mva2j600el = (float) mvaReader2j600el.GetMvaValue( mvaInputVal );
         mva2j400interferencenominalel = (float) mvaReader2j400interferencenominalel.GetMvaValue( mvaInputVal );
         mva2j450interferencenominalel = (float) mvaReader2j450interferencenominalel.GetMvaValue( mvaInputVal );
         mva2j500interferencenominalel = (float) mvaReader2j500interferencenominalel.GetMvaValue( mvaInputVal );
         mva2j550interferencenominalel = (float) mvaReader2j550interferencenominalel.GetMvaValue( mvaInputVal );
         mva2j600interferencenominalel = (float) mvaReader2j600interferencenominalel.GetMvaValue( mvaInputVal );
         mva2j700interferencenominalel = (float) mvaReader2j700interferencenominalel.GetMvaValue( mvaInputVal );
         mva2j800interferencenominalel = (float) mvaReader2j800interferencenominalel.GetMvaValue( mvaInputVal );
         mva2j900interferencenominalel = (float) mvaReader2j900interferencenominalel.GetMvaValue( mvaInputVal );
         mva2j1000interferencenominalel = (float) mvaReader2j1000interferencenominalel.GetMvaValue( mvaInputVal );
         mva2j400interferencedownel = (float) mvaReader2j400interferencedownel.GetMvaValue( mvaInputVal );
         mva2j450interferencedownel = (float) mvaReader2j450interferencedownel.GetMvaValue( mvaInputVal );
         mva2j500interferencedownel = (float) mvaReader2j500interferencedownel.GetMvaValue( mvaInputVal );
         mva2j550interferencedownel = (float) mvaReader2j550interferencedownel.GetMvaValue( mvaInputVal );
         mva2j600interferencedownel = (float) mvaReader2j600interferencedownel.GetMvaValue( mvaInputVal );
         mva2j700interferencedownel = (float) mvaReader2j700interferencedownel.GetMvaValue( mvaInputVal );
         mva2j800interferencedownel = (float) mvaReader2j800interferencedownel.GetMvaValue( mvaInputVal );
         mva2j900interferencedownel = (float) mvaReader2j900interferencedownel.GetMvaValue( mvaInputVal );
         mva2j1000interferencedownel = (float) mvaReader2j1000interferencedownel.GetMvaValue( mvaInputVal );
         mva2j400interferenceupel = (float) mvaReader2j400interferenceupel.GetMvaValue( mvaInputVal );
         mva2j450interferenceupel = (float) mvaReader2j450interferenceupel.GetMvaValue( mvaInputVal );
         mva2j500interferenceupel = (float) mvaReader2j500interferenceupel.GetMvaValue( mvaInputVal );
         mva2j550interferenceupel = (float) mvaReader2j550interferenceupel.GetMvaValue( mvaInputVal );
         mva2j600interferenceupel = (float) mvaReader2j600interferenceupel.GetMvaValue( mvaInputVal );
         mva2j700interferenceupel = (float) mvaReader2j700interferenceupel.GetMvaValue( mvaInputVal );
         mva2j800interferenceupel = (float) mvaReader2j800interferenceupel.GetMvaValue( mvaInputVal );
         mva2j900interferenceupel = (float) mvaReader2j900interferenceupel.GetMvaValue( mvaInputVal );
         mva2j1000interferenceupel = (float) mvaReader2j1000interferenceupel.GetMvaValue( mvaInputVal );

         mva3j170el = (float) mvaReader3j170el.GetMvaValue( mvaInputVal );
         mva3j180el = (float) mvaReader3j180el.GetMvaValue( mvaInputVal );
         mva3j190el = (float) mvaReader3j190el.GetMvaValue( mvaInputVal );
         mva3j200el = (float) mvaReader3j200el.GetMvaValue( mvaInputVal );
         mva3j250el = (float) mvaReader3j250el.GetMvaValue( mvaInputVal );
         mva3j300el = (float) mvaReader3j300el.GetMvaValue( mvaInputVal );
         mva3j350el = (float) mvaReader3j350el.GetMvaValue( mvaInputVal );
         mva3j400el = (float) mvaReader3j400el.GetMvaValue( mvaInputVal );
         mva3j450el = (float) mvaReader3j450el.GetMvaValue( mvaInputVal );
         mva3j500el = (float) mvaReader3j500el.GetMvaValue( mvaInputVal );
         mva3j550el = (float) mvaReader3j550el.GetMvaValue( mvaInputVal );
         mva3j600el = (float) mvaReader3j600el.GetMvaValue( mvaInputVal );
         mva3j400interferencenominalel = (float) mvaReader3j400interferencenominalel.GetMvaValue( mvaInputVal );
         mva3j450interferencenominalel = (float) mvaReader3j450interferencenominalel.GetMvaValue( mvaInputVal );
         mva3j500interferencenominalel = (float) mvaReader3j500interferencenominalel.GetMvaValue( mvaInputVal );
         mva3j550interferencenominalel = (float) mvaReader3j550interferencenominalel.GetMvaValue( mvaInputVal );
         mva3j600interferencenominalel = (float) mvaReader3j600interferencenominalel.GetMvaValue( mvaInputVal );
         mva3j700interferencenominalel = (float) mvaReader3j700interferencenominalel.GetMvaValue( mvaInputVal );
         mva3j800interferencenominalel = (float) mvaReader3j800interferencenominalel.GetMvaValue( mvaInputVal );
         mva3j900interferencenominalel = (float) mvaReader3j900interferencenominalel.GetMvaValue( mvaInputVal );
         mva3j1000interferencenominalel = (float) mvaReader3j1000interferencenominalel.GetMvaValue( mvaInputVal );
         mva3j400interferencedownel = (float) mvaReader3j400interferencedownel.GetMvaValue( mvaInputVal );
         mva3j450interferencedownel = (float) mvaReader3j450interferencedownel.GetMvaValue( mvaInputVal );
         mva3j500interferencedownel = (float) mvaReader3j500interferencedownel.GetMvaValue( mvaInputVal );
         mva3j550interferencedownel = (float) mvaReader3j550interferencedownel.GetMvaValue( mvaInputVal );
         mva3j600interferencedownel = (float) mvaReader3j600interferencedownel.GetMvaValue( mvaInputVal );
         mva3j700interferencedownel = (float) mvaReader3j700interferencedownel.GetMvaValue( mvaInputVal );
         mva3j800interferencedownel = (float) mvaReader3j800interferencedownel.GetMvaValue( mvaInputVal );
         mva3j900interferencedownel = (float) mvaReader3j900interferencedownel.GetMvaValue( mvaInputVal );
         mva3j1000interferencedownel = (float) mvaReader3j1000interferencedownel.GetMvaValue( mvaInputVal );
         mva3j400interferenceupel = (float) mvaReader3j400interferenceupel.GetMvaValue( mvaInputVal );
         mva3j450interferenceupel = (float) mvaReader3j450interferenceupel.GetMvaValue( mvaInputVal );
         mva3j500interferenceupel = (float) mvaReader3j500interferenceupel.GetMvaValue( mvaInputVal );
         mva3j550interferenceupel = (float) mvaReader3j550interferenceupel.GetMvaValue( mvaInputVal );
         mva3j600interferenceupel = (float) mvaReader3j600interferenceupel.GetMvaValue( mvaInputVal );
         mva3j700interferenceupel = (float) mvaReader3j700interferenceupel.GetMvaValue( mvaInputVal );
         mva3j800interferenceupel = (float) mvaReader3j800interferenceupel.GetMvaValue( mvaInputVal );
         mva3j900interferenceupel = (float) mvaReader3j900interferenceupel.GetMvaValue( mvaInputVal );
         mva3j1000interferenceupel = (float) mvaReader3j1000interferenceupel.GetMvaValue( mvaInputVal );

         std::vector<double> DB_mvaInputVal;
         DB_mvaInputVal.push_back( W_pt );
         DB_mvaInputVal.push_back( event_met_pfmet );
         DB_mvaInputVal.push_back( W_electron_charge );   ///////different for electron and muon
         DB_mvaInputVal.push_back( JetPFCor_QGLikelihood[0] );
         DB_mvaInputVal.push_back( JetPFCor_QGLikelihood[1] );
         DB_mvaInputVal.push_back( ang_hs );
         DB_mvaInputVal.push_back( ang_phib );
         DB_mvaInputVal.push_back( fabs(JetPFCor_Eta[0]-JetPFCor_Eta[1]) );
         DB_mvaInputVal.push_back( masslvjj );

         mva2jdibosonel = (float) mvaReader2jdibosonel.GetMvaValue( DB_mvaInputVal );
         mva3jdibosonel = (float) mvaReader3jdibosonel.GetMvaValue( DB_mvaInputVal );

         std::vector<double> DBnoqg_mvaInputVal;
         DBnoqg_mvaInputVal.push_back( W_pt );
         DBnoqg_mvaInputVal.push_back( event_met_pfmet );
         DBnoqg_mvaInputVal.push_back( W_electron_charge );   ///////different for electron and muon
         DBnoqg_mvaInputVal.push_back( ang_hs );
         DBnoqg_mvaInputVal.push_back( ang_phib );
         DBnoqg_mvaInputVal.push_back( fabs(JetPFCor_Eta[0]-JetPFCor_Eta[1]) );
         DBnoqg_mvaInputVal.push_back( masslvjj );

         mva2jdibnoqgel = (float) mvaReader2jdibnoqgel.GetMvaValue( DBnoqg_mvaInputVal );
         mva3jdibnoqgel = (float) mvaReader3jdibnoqgel.GetMvaValue( DBnoqg_mvaInputVal );

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
         for(int i = 0; i < numPFCorJets; i++)
         {
            if(JetPFCor_Pt[i] > Jpt)
            {
               TLorentzVector  ajp;
               ajp.SetPtEtaPhiE(jess * JetPFCor_Pt[i], JetPFCor_Eta[i], JetPFCor_Phi[i], jess * JetPFCor_E[i]  );

               double tmpdelatR = ca8jetp4.DeltaR(ajp);

               //cout << "Error 11" <<endl;
               double tmpdeltaRlj = ajp.DeltaR(mup);
               //cout << "Error 12" <<endl;

               if(tmpdelatR > 0.8)//Veto the AK5 jet in the CA8 jet cone
               {
                  GroomedJet_numberjets = GroomedJet_numberjets + 1;
               }

               //if(JetPFCor_bDiscriminator[i] > btssv && tmpdelatR > 0.8)//Veto the AK5 jet in the CA8 jet cone
               /*if(JetPFCor_bDiscriminatorCSV[i] > btcsvm && tmpdelatR > 0.8)//Veto the AK5 jet in the CA8 jet cone and Move to CSVM tagger
                 {
                 GroomedJet_numberbjets = GroomedJet_numberbjets + 1;
                 }
                */
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
         if (W_electron_charge < 0){
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

               //cout<<"Error 13"<< endl;
               double tmpdelatR = ak7jetp4.DeltaR(ajp);

               //double tmpdelatR = 0.5; //Current Sample doesn't have the AK7 informatio in the electron channel

               //cout<<"Error 14"<< endl;
               double tmpdeltaRlj = ajp.DeltaR(mup);
               //cout<<"Error 15"<< endl;

               if(tmpdelatR > 0.7)//Veto the AK5 jet in the AK7 jet cone
               {
                  GroomedJet_numberjets_ak7 = GroomedJet_numberjets_ak7 + 1;
               }

               //if(JetPFCor_bDiscriminator[i] > btssv && tmpdelatR > 0.8)//Veto the AK5 jet in the AK7 jet cone
               /*if(JetPFCor_bDiscriminatorCSV[i] > btcsvm && tmpdelatR > 0.8)//Veto the AK5 jet in the AK7 jet cone and Move to CSVM tagger
                 {
                 GroomedJet_numberbjets_ak7 = GroomedJet_numberbjets_ak7 + 1;
                 }
                */
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
         if (W_electron_charge < 0){
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
               //if ( (fabs(i_Eta-j_Eta)>best_detatagjj) ){                          // 3   Select best combination with maximum deta Eta
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


               vbf_event = 1; vbf_aj_id = tag_i_id; vbf_bj_id = tag_j_id; vbf_waj_id = wjj_a_id; vbf_wbj_id = wjj_b_id;

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
               if (W_electron_charge < 0){
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
               vbf_mvaInputVal.push_back( W_electron_charge );   ///////different for electron and muon
               vbf_mvaInputVal.push_back( vbf_wjj_ang_ha );
               vbf_mvaInputVal.push_back( vbf_wjj_ang_hb );
               vbf_mvaInputVal.push_back( vbf_wjj_ang_hs );
               vbf_mvaInputVal.push_back( vbf_wjj_ang_phi );
               vbf_mvaInputVal.push_back( vbf_wjj_ang_phib );
               //vbf_mvaInputVal.push_back( vbf_jj_deta );
               //vbf_mvaInputVal.push_back( vbf_jj_m );

               mvavbf170el = (float) mvaReadervbf170el.GetMvaValue( vbf_mvaInputVal );
               mvavbf180el = (float) mvaReadervbf180el.GetMvaValue( vbf_mvaInputVal );
               mvavbf190el = (float) mvaReadervbf190el.GetMvaValue( vbf_mvaInputVal );
               mvavbf200el = (float) mvaReadervbf200el.GetMvaValue( vbf_mvaInputVal );
               mvavbf250el = (float) mvaReadervbf250el.GetMvaValue( vbf_mvaInputVal );
               mvavbf300el = (float) mvaReadervbf300el.GetMvaValue( vbf_mvaInputVal );
               mvavbf350el = (float) mvaReadervbf350el.GetMvaValue( vbf_mvaInputVal );
               mvavbf400el = (float) mvaReadervbf400el.GetMvaValue( vbf_mvaInputVal );
               mvavbf450el = (float) mvaReadervbf450el.GetMvaValue( vbf_mvaInputVal );
               mvavbf500el = (float) mvaReadervbf500el.GetMvaValue( vbf_mvaInputVal );
               mvavbf550el = (float) mvaReadervbf550el.GetMvaValue( vbf_mvaInputVal );
               mvavbf600el = (float) mvaReadervbf600el.GetMvaValue( vbf_mvaInputVal );

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
                     -15.0, W_electron_pt, W_electron_eta, W_electron_phi, 0.0, 0.0, 0.0);
               fprintf(textfile, "%12.5f  %12.5f  %12.5f  %12.5f  %12.5f  %12.5f  %12.5f \n",
                     -5.0,  event_met_pfmet, event_met_pfmetPhi, event_met_pfmetsignificance, event_met_pfsumet, (double)event_nPV, 0.0); 
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

         branch_2j160el->Fill();
         branch_2j170el->Fill();
         branch_2j180el->Fill();
         branch_2j190el->Fill();
         branch_2j200el->Fill();
         branch_2j250el->Fill();
         branch_2j300el->Fill();
         branch_2j350el->Fill();
         branch_2j400el->Fill();
         branch_2j450el->Fill();
         branch_2j500el->Fill();
         branch_2j550el->Fill();
         branch_2j600el->Fill();
         branch_2j400interferencenominalel->Fill();
         branch_2j450interferencenominalel->Fill();
         branch_2j500interferencenominalel->Fill();
         branch_2j550interferencenominalel->Fill();
         branch_2j600interferencenominalel->Fill();
         branch_2j700interferencenominalel->Fill();
         branch_2j800interferencenominalel->Fill();
         branch_2j900interferencenominalel->Fill();
         branch_2j1000interferencenominalel->Fill();
         branch_2j400interferencedownel->Fill();
         branch_2j450interferencedownel->Fill();
         branch_2j500interferencedownel->Fill();
         branch_2j550interferencedownel->Fill();
         branch_2j600interferencedownel->Fill();
         branch_2j700interferencedownel->Fill();
         branch_2j800interferencedownel->Fill();
         branch_2j900interferencedownel->Fill();
         branch_2j1000interferencedownel->Fill();
         branch_2j400interferenceupel->Fill();
         branch_2j450interferenceupel->Fill();
         branch_2j500interferenceupel->Fill();
         branch_2j550interferenceupel->Fill();
         branch_2j600interferenceupel->Fill();
         branch_2j700interferenceupel->Fill();
         branch_2j800interferenceupel->Fill();
         branch_2j900interferenceupel->Fill();
         branch_2j1000interferenceupel->Fill();

         branch_3j160el->Fill();
         branch_3j170el->Fill();
         branch_3j180el->Fill();
         branch_3j190el->Fill();
         branch_3j200el->Fill();
         branch_3j250el->Fill();
         branch_3j300el->Fill();
         branch_3j350el->Fill();
         branch_3j400el->Fill();
         branch_3j450el->Fill();
         branch_3j500el->Fill();
         branch_3j550el->Fill();
         branch_3j600el->Fill();
         branch_3j400interferencenominalel->Fill();
         branch_3j450interferencenominalel->Fill();
         branch_3j500interferencenominalel->Fill();
         branch_3j550interferencenominalel->Fill();
         branch_3j600interferencenominalel->Fill();
         branch_3j700interferencenominalel->Fill();
         branch_3j800interferencenominalel->Fill();
         branch_3j900interferencenominalel->Fill();
         branch_3j1000interferencenominalel->Fill();
         branch_3j400interferencedownel->Fill();
         branch_3j450interferencedownel->Fill();
         branch_3j500interferencedownel->Fill();
         branch_3j550interferencedownel->Fill();
         branch_3j600interferencedownel->Fill();
         branch_3j700interferencedownel->Fill();
         branch_3j800interferencedownel->Fill();
         branch_3j900interferencedownel->Fill();
         branch_3j1000interferencedownel->Fill();
         branch_3j400interferenceupel->Fill();
         branch_3j450interferenceupel->Fill();
         branch_3j500interferenceupel->Fill();
         branch_3j550interferenceupel->Fill();
         branch_3j600interferenceupel->Fill();
         branch_3j700interferenceupel->Fill();
         branch_3j800interferenceupel->Fill();
         branch_3j900interferenceupel->Fill();
         branch_3j1000interferenceupel->Fill();

         branch_2jdibosonel->Fill();
         branch_3jdibosonel->Fill();
         branch_2jdibnoqgel->Fill();
         branch_3jdibnoqgel->Fill();

         branch_vbf160el->Fill();
         branch_vbf170el->Fill();
         branch_vbf180el->Fill();
         branch_vbf190el->Fill();
         branch_vbf200el->Fill();
         branch_vbf250el->Fill();
         branch_vbf300el->Fill();
         branch_vbf350el->Fill();
         branch_vbf400el->Fill();
         branch_vbf450el->Fill();
         branch_vbf500el->Fill();
         branch_vbf550el->Fill();
         branch_vbf600el->Fill();

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

   double kanaelec::getDeltaPhi(double phi1, double phi2  )
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

   bool kanaelec::dottHKinematicFit(const TLorentzVector mup, const TLorentzVector nvp, const TLorentzVector wajp, const TLorentzVector wbjp, const TLorentzVector topajp, const TLorentzVector topbjp, Float_t & fit_chi2, Int_t & fit_NDF, Int_t & fit_status)
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

   bool kanaelec::doKinematicFit(Int_t                 fflage,
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
      const std::string& leptonName = "electron";  const TLorentzVector lepton   = mup;
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

   void kanaelec::calculateAngles(TLorentzVector& thep4M11, TLorentzVector& thep4M12, TLorentzVector& thep4M21, TLorentzVector& thep4M22, double& costheta1, double& costheta2, double& phi, double& costhetastar, double& phistar1, double& phistar2){


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

   // function used to fill the counters with preselction level cuts
   void kanaelec::InitCounters( const char* input_file_name, TH1F* h_events, TH1F* h_events_weighted)
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

