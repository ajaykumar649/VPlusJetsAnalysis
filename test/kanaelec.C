#define kanaelec_cxx
#include "kanaelec.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

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

#include "ClassifierOut/TMVAClassification_noqg_nJ2_el_BDT.class.C"
#include "ClassifierOut/TMVAClassification_noqg_nJ3_el_BDT.class.C"
#include "ClassifierOut/TMVAClassification_withqg_nJ2_el_BDT.class.C"
#include "ClassifierOut/TMVAClassification_withqg_nJ3_el_BDT.class.C"

#include "EffTableReader.h"
#include "EffTableLoader.h"

#include "PhysicsTools/Utilities/interface/Lumi3DReWeighting.h"

#include "ElectroWeakAnalysis/VPlusJets/interface/QGLikelihoodCalculator.h"

const TString inDataDir  = "/uscms_data/d2/yangf/ana/WuvWjj/Full2011Data/MergFile/";
const TString inQCDDir   = "/uscms_data/d2/yangf/ana/WuvWjj/QCDControlSample_PAT/MergFile/";
const TString outDataDir = "/uscms_data/d2/yangf/ana/WuvWjj/Full2011Data/RDTreeDebug/";
const std::string fDir   = "EffTableDir/";

void kanaelec::myana(double myflag, bool isQCD, int runflag)
{
  TChain * myChain;
  cout << "isQCD=" << isQCD << endl;
  // 2011 data
  if (myflag == 20110000 || myflag == -100){
    myChain = new TChain("WJet"); 
    
    if ( !isQCD ) {
      myChain->Add(                    inDataDir + "WenuJets_DataAllSingleElectronTrigger_GoldenJSON_4p7invfb.root"); 
      Init(myChain);Loop( 20110000,runflag, outDataDir + "RD_WenuJets_DataAllSingleElectronTrigger_GoldenJSON_4p7invfb");
    } else {
      myChain->Add(                    inQCDDir +     "WenuJets_DataAll_GoldenJSON_5invfb.root"); 
      Init(myChain);Loop( 20110000,runflag, outDataDir + "RDQCD_WenuJets_DataAll_GoldenJSON_2p1invfb", isQCD);
    }
  }
  
  if ( !isQCD ) {
    // Separate Electron Data
    if (myflag == 20110001 || myflag == -101){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "SingleEleAndEleTwoPFJetTrigger.root"); 
      Init(myChain);Loop( 20110001,runflag, outDataDir + "RD_SingleEleAndEleTwoPFJetTrigger");
    }
    if (myflag == 20110002 || myflag == -102){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "EleTwoCaloJetTrigger.root"); 
      Init(myChain);Loop( 20110002,runflag, outDataDir + "RD_EleTwoCaloJetTrigger");
    }
    if (myflag == 20110003 || myflag == -103){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "WenuJets_175832-180252_SingleElectron-Run2011B-PromptReco-v1-trigallcombined.root"); 
      Init(myChain);Loop( 20110003,runflag, outDataDir + "RD_WenuJets_175832-180252_SingleElectron-Run2011B-PromptReco-v1-trigallcombined");
    }
    if (myflag == 20110004 || myflag == -104){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "WenuJets_DataAll_GoldenJSON_4p7invfb.root"); 
      Init(myChain);Loop( 20110004,runflag, outDataDir + "RD_WenuJets_DataAll_GoldenJSON_4p7invfb");
    }

    // General Background Samples
    if (myflag == 20111002 || myflag == -200){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_STopS_Tbar_CMSSW428.root"); 
      Init(myChain);Loop( 20111002,runflag, outDataDir + "RD_el_STopS_Tbar_CMSSW428");
    }
    if (myflag == 20111003 || myflag == -200){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_STopS_T_CMSSW428.root"); 
      Init(myChain);Loop( 20111003,runflag, outDataDir + "RD_el_STopS_T_CMSSW428");
    }
    if (myflag == 20111004 || myflag == -200){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_STopT_Tbar_CMSSW428.root"); 
      Init(myChain);Loop( 20111004,runflag, outDataDir + "RD_el_STopT_Tbar_CMSSW428");
    }
    if (myflag == 20111005 || myflag == -200){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_STopT_T_CMSSW428.root"); 
      Init(myChain);Loop( 20111005,runflag, outDataDir + "RD_el_STopT_T_CMSSW428");
    }
    if (myflag == 20111006 || myflag == -200){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_STopTW_Tbar_CMSSW428.root"); 
      Init(myChain);Loop( 20111006,runflag, outDataDir + "RD_el_STopTW_Tbar_CMSSW428");
    }
    if (myflag == 20111007 || myflag == -200){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_STopTW_T_CMSSW428.root"); 
      Init(myChain);Loop( 20111007,runflag, outDataDir + "RD_el_STopTW_T_CMSSW428");
    }
    if (myflag == 20111008 || myflag == -200){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_TTbar_CMSSW428.root"); 
      Init(myChain);Loop( 20111008,runflag, outDataDir + "RD_el_TTbar_CMSSW428");
    }
    if (myflag == 20111009 || myflag == -500){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_WpJ_CMSSW428.root"); 
      Init(myChain);Loop( 20111009,runflag, outDataDir + "RD_el_WpJ_CMSSW428");
    }
    if (myflag == 20111010 || myflag == -200){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_WpJmatchingdown_CMSSW428.root"); 
      Init(myChain);Loop( 20111010,runflag, outDataDir + "RD_el_WpJmatchingdown_CMSSW428");
    }
    if (myflag == 20111011 || myflag == -200){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_WpJmatchingup_CMSSW428.root"); 
      Init(myChain);Loop( 20111011,runflag, outDataDir + "RD_el_WpJmatchingup_CMSSW428");
    }
    if (myflag == 20111012 || myflag == -200){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_WpJscaledown_CMSSW428.root"); 
      Init(myChain);Loop( 20111012,runflag, outDataDir + "RD_el_WpJscaledown_CMSSW428");
    }
    if (myflag == 20111013 || myflag == -200){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_WpJscaleup_CMSSW428.root"); 
      Init(myChain);Loop( 20111013,runflag, outDataDir + "RD_el_WpJscaleup_CMSSW428");
    }
    if (myflag == 20111014 || myflag ==  999){ // set 999 not run!!
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_WpJsherpa_CMSSW428.root"); 
      Init(myChain);Loop( 20111014,runflag, outDataDir + "RD_el_WpJsherpa_CMSSW428");
    }
    if (myflag == 20111015 || myflag == -200){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_WW_CMSSW428.root"); 
      Init(myChain);Loop( 20111015,runflag, outDataDir + "RD_el_WW_CMSSW428");
    }
    if (myflag == 20111016 || myflag == -200){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_WZ_CMSSW428.root"); 
      Init(myChain);Loop( 20111016,runflag, outDataDir + "RD_el_WZ_CMSSW428");
    }
    if (myflag == 20111017 || myflag == -200){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_ZpJ_CMSSW428.root"); 
      Init(myChain);Loop( 20111017,runflag, outDataDir + "RD_el_ZpJ_CMSSW428");
    }
    if (myflag == 20111018 || myflag ==  999){ // set 999 not run!!
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_QCDEl_BCtoE30to80_CMSSW428.root"); 
      Init(myChain);Loop( 20111018,runflag, outDataDir + "RD_el_QCDEl_BCtoE30to80_CMSSW428");
    }
    if (myflag == 20111019 || myflag ==  999){ // set 999 not run!!
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_QCDEl_BCtoE80to170_CMSSW428.root"); 
      Init(myChain);Loop( 20111019,runflag, outDataDir + "RD_el_QCDEl_BCtoE80to170_CMSSW428");
    }
    if (myflag == 20111020 || myflag ==  999){ // set 999 not run!!
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_QCDEl_Pt30to80_CMSSW428.root"); 
      Init(myChain);Loop( 20111020,runflag, outDataDir + "RD_el_QCDEl_Pt30to80_CMSSW428");
    }
    if (myflag == 20111021 || myflag ==  999){ // set 999 not run!!
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_QCDEl_Pt80to170_CMSSW428.root"); 
      Init(myChain);Loop( 20111021,runflag, outDataDir + "RD_el_QCDEl_Pt80to170_CMSSW428");
    }
    if (myflag == 20111022 || myflag ==  999){ // set 999 not run!!
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_TTbar_powheg_CMSSW428.root"); 
      Init(myChain);Loop( 20111022,runflag, outDataDir + "RD_el_TTbar_powheg_CMSSW428");
    }
    if (myflag == 20111023 || myflag == -200){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_ZZ_CMSSW428.root"); 
      Init(myChain);Loop( 20111023,runflag, outDataDir + "RD_el_ZZ_CMSSW428");
    }

    // Higgs Signal Samples
    if (myflag == 20112150 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWMH150_CMSSW428.root"); 
      Init(myChain);Loop( 20112150,runflag, outDataDir + "RD_el_HWWMH150_CMSSW428");
    }
    if (myflag == 20112160 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWMH160_CMSSW428.root"); 
      Init(myChain);Loop( 20112160,runflag, outDataDir + "RD_el_HWWMH160_CMSSW428");
    }
    if (myflag == 20112170 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWMH170_CMSSW428.root"); 
      Init(myChain);Loop( 20112170,runflag, outDataDir + "RD_el_HWWMH170_CMSSW428");
    }
    if (myflag == 20112180 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWMH180_CMSSW428.root"); 
      Init(myChain);Loop( 20112180,runflag, outDataDir + "RD_el_HWWMH180_CMSSW428");
    }
    if (myflag == 20112190 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWMH190_CMSSW428.root"); 
      Init(myChain);Loop( 20112190,runflag, outDataDir + "RD_el_HWWMH190_CMSSW428");
    }
    if (myflag == 20112200 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWMH200_CMSSW428.root"); 
      Init(myChain);Loop( 20112200,runflag, outDataDir + "RD_el_HWWMH200_CMSSW428");
    }
    if (myflag == 20112250 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWMH250_CMSSW428.root"); 
      Init(myChain);Loop( 20112250,runflag, outDataDir + "RD_el_HWWMH250_CMSSW428");
    }
    if (myflag == 20112300 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWMH300_CMSSW428.root"); 
      Init(myChain);Loop( 20112300,runflag, outDataDir + "RD_el_HWWMH300_CMSSW428");
    }
    if (myflag == 20112350 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWMH350_CMSSW428.root"); 
      Init(myChain);Loop( 20112350,runflag, outDataDir + "RD_el_HWWMH350_CMSSW428");
    }
    if (myflag == 20112400 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWMH400_CMSSW428.root"); 
      Init(myChain);Loop( 20112400,runflag, outDataDir + "RD_el_HWWMH400_CMSSW428");
    }
    if (myflag == 20112450 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWMH450_CMSSW428.root"); 
      Init(myChain);Loop( 20112450,runflag, outDataDir + "RD_el_HWWMH450_CMSSW428");
    }
    if (myflag == 20112500 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWMH500_CMSSW428.root"); 
      Init(myChain);Loop( 20112500,runflag, outDataDir + "RD_el_HWWMH500_CMSSW428");
    }
    if (myflag == 20112550 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWMH550_CMSSW428.root"); 
      Init(myChain);Loop( 20112550,runflag, outDataDir + "RD_el_HWWMH550_CMSSW428");
    }
    if (myflag == 20112600 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWMH600_CMSSW428.root"); 
      Init(myChain);Loop( 20112600,runflag, outDataDir + "RD_el_HWWMH600_CMSSW428");
    }

    // VBF Higgs MC Signal
    if (myflag == 20113150 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_VBFHWWMH150_CMSSW428.root"); 
      Init(myChain);Loop( 20113150,runflag, outDataDir + "RD_el_VBFHWWMH150_CMSSW428");
    }
    if (myflag == 20113160 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_VBFHWWMH160_CMSSW428.root"); 
      Init(myChain);Loop( 20113160,runflag, outDataDir + "RD_el_VBFHWWMH160_CMSSW428");
    }
    if (myflag == 20113170 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_VBFHWWMH170_CMSSW428.root"); 
      Init(myChain);Loop( 20113170,runflag, outDataDir + "RD_el_VBFHWWMH170_CMSSW428");
    }
    if (myflag == 20113180 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_VBFHWWMH180_CMSSW428.root"); 
      Init(myChain);Loop( 20113180,runflag, outDataDir + "RD_el_VBFHWWMH180_CMSSW428");
    }
    if (myflag == 20113190 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_VBFHWWMH190_CMSSW428.root"); 
      Init(myChain);Loop( 20113190,runflag, outDataDir + "RD_el_VBFHWWMH190_CMSSW428");
    }
    if (myflag == 20113200 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_VBFHWWMH200_CMSSW428.root"); 
      Init(myChain);Loop( 20113200,runflag, outDataDir + "RD_el_VBFHWWMH200_CMSSW428");
    }
    if (myflag == 20113250 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_VBFHWWMH250_CMSSW428.root"); 
      Init(myChain);Loop( 20113250,runflag, outDataDir + "RD_el_VBFHWWMH250_CMSSW428");
    }
    if (myflag == 20113300 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_VBFHWWMH300_CMSSW428.root"); 
      Init(myChain);Loop( 20113300,runflag, outDataDir + "RD_el_VBFHWWMH300_CMSSW428");
    }
    if (myflag == 20113350 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_VBFHWWMH350_CMSSW428.root"); 
      Init(myChain);Loop( 20113350,runflag, outDataDir + "RD_el_VBFHWWMH350_CMSSW428");
    }
    if (myflag == 20113400 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_VBFHWWMH400_CMSSW428.root"); 
      Init(myChain);Loop( 20113400,runflag, outDataDir + "RD_el_VBFHWWMH400_CMSSW428");
    }
    if (myflag == 20113450 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_VBFHWWMH450_CMSSW428.root"); 
      Init(myChain);Loop( 20113450,runflag, outDataDir + "RD_el_VBFHWWMH450_CMSSW428");
    }
    if (myflag == 20113500 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_VBFHWWMH500_CMSSW428.root"); 
      Init(myChain);Loop( 20113500,runflag, outDataDir + "RD_el_VBFHWWMH500_CMSSW428");
    }
    if (myflag == 20113550 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_VBFHWWMH550_CMSSW428.root"); 
      Init(myChain);Loop( 20113550,runflag, outDataDir + "RD_el_VBFHWWMH550_CMSSW428");
    }
    if (myflag == 20113600 || myflag == -300){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_VBFHWWMH600_CMSSW428.root"); 
      Init(myChain);Loop( 20113600,runflag, outDataDir + "RD_el_VBFHWWMH600_CMSSW428");
    }
    
    // HTauTau MC Signal
    if (myflag == 20114150 || myflag == -400){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWTauNuMH150_CMSSW428.root"); 
      Init(myChain);Loop( 20114150,runflag, outDataDir + "RD_el_HWWTauNuMH150_CMSSW428");
    }
    if (myflag == 20114160 || myflag == -400){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWTauNuMH160_CMSSW428.root"); 
      Init(myChain);Loop( 20114160,runflag, outDataDir + "RD_el_HWWTauNuMH160_CMSSW428");
    }
    if (myflag == 20114170 || myflag == -400){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWTauNuMH170_CMSSW428.root"); 
      Init(myChain);Loop( 20114170,runflag, outDataDir + "RD_el_HWWTauNuMH170_CMSSW428");
    }
    if (myflag == 20114180 || myflag == -400){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWTauNuMH180_CMSSW428.root"); 
      Init(myChain);Loop( 20114180,runflag, outDataDir + "RD_el_HWWTauNuMH180_CMSSW428");
    }
    if (myflag == 20114190 || myflag == -400){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWTauNuMH190_CMSSW428.root"); 
      Init(myChain);Loop( 20114190,runflag, outDataDir + "RD_el_HWWTauNuMH190_CMSSW428");
    }
    if (myflag == 20114200 || myflag == -400){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWTauNuMH200_CMSSW428.root"); 
      Init(myChain);Loop( 20114200,runflag, outDataDir + "RD_el_HWWTauNuMH200_CMSSW428");
    }
    if (myflag == 20114250 || myflag == -400){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWTauNuMH250_CMSSW428.root"); 
      Init(myChain);Loop( 20114250,runflag, outDataDir + "RD_el_HWWTauNuMH250_CMSSW428");
    }
    if (myflag == 20114300 || myflag == -400){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWTauNuMH300_CMSSW428.root"); 
      Init(myChain);Loop( 20114300,runflag, outDataDir + "RD_el_HWWTauNuMH300_CMSSW428");
    }
    if (myflag == 20114350 || myflag == -400){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWTauNuMH350_CMSSW428.root"); 
      Init(myChain);Loop( 20114350,runflag, outDataDir + "RD_el_HWWTauNuMH350_CMSSW428");
    }
    if (myflag == 20114400 || myflag == -400){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWTauNuMH400_CMSSW428.root"); 
      Init(myChain);Loop( 20114400,runflag, outDataDir + "RD_el_HWWTauNuMH400_CMSSW428");
    }
    if (myflag == 20114450 || myflag == -400){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWTauNuMH450_CMSSW428.root"); 
      Init(myChain);Loop( 20114450,runflag, outDataDir + "RD_el_HWWTauNuMH450_CMSSW428");
    }
    if (myflag == 20114500 || myflag == -400){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWTauNuMH500_CMSSW428.root"); 
      Init(myChain);Loop( 20114500,runflag, outDataDir + "RD_el_HWWTauNuMH500_CMSSW428");
    }
    if (myflag == 20114550 || myflag == -400){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWTauNuMH550_CMSSW428.root"); 
      Init(myChain);Loop( 20114550,runflag, outDataDir + "RD_el_HWWTauNuMH550_CMSSW428");
    }
    if (myflag == 20114600 || myflag == -400){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_HWWTauNuMH600_CMSSW428.root"); 
      Init(myChain);Loop( 20114600,runflag, outDataDir + "RD_el_HWWTauNuMH600_CMSSW428");
    }

    // VBF Background samples generated by Qiang and Andre
    if (myflag == 20115001 || myflag == -400){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_VBF_CMSSW428.root"); 
      Init(myChain);Loop( 20115001,runflag, outDataDir + "RD_el_VBF_CMSSW428");
    }
    //new physics samples for the Mjj analysis
    if (myflag == 20115002 || myflag == -400){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_ZprimeMadGraph_CMSSW428.root"); 
      Init(myChain);Loop( 20115002,runflag, outDataDir + "RD_el_ZprimeMadGraph_CMSSW428");
    }
    if (myflag == 20115003 || myflag == -400){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_TechnicolorPythia_CMSSW428.root"); 
      Init(myChain);Loop( 20115003,runflag, outDataDir + "RD_el_TechnicolorPythia_CMSSW428");
    }
    if (myflag == 20115004 || myflag == -400){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_WH150qq_CMSSW428.root"); 
      Init(myChain);Loop( 20115004,runflag, outDataDir + "RD_el_WH150qq_CMSSW428");
    }
    if (myflag == 20115005 || myflag == -400){
      myChain = new TChain("WJet");  
      myChain->Add(                    inDataDir + "el_WpJ100KCrossCheck_CMSSW428.root"); 
      Init(myChain);Loop( 20115005,runflag, outDataDir + "RD_el_WpJ100KCrossCheck_CMSSW428");
    }

  }

}

void kanaelec::Loop(int wda, int runflag, const char *outfilename, bool isQCD)
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
  // Drop gen jet information
  fChain->SetBranchStatus("*Gen*",    0);

  TTree *newtree = fChain->CloneTree();
  char textfn[100]; 
  sprintf(textfn,"%s.txt", rootfn);
  FILE *textfile = fopen(textfn,"w");
  
  Int_t   ggdevt   =0,   evtNJ     =0;

  TBranch *branch_ggdevt= newtree->Branch("ggdevt",    &ggdevt,     "ggdevt/I");
  TBranch *branch_evtNJ = newtree->Branch("evtNJ",     &evtNJ,      "evtNJ/I");

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
  Float_t mva3j160el = 999, mva3j170el = 999, mva3j180el = 999, mva3j190el = 999, mva3j200el = 999, mva3j250el = 999, mva3j300el = 999, mva3j350el = 999, mva3j400el = 999, mva3j450el = 999, mva3j500el = 999, mva3j550el = 999, mva3j600el = 999;
  Float_t mva2jdibosonel = 999,mva3jdibosonel = 999, mva2jdibnoqgel = 999,mva3jdibnoqgel = 999;
  
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

  TBranch * branch_2jdibosonel   =  newtree->Branch("mva2jdibosonel",   &mva2jdibosonel,    "mva2jdibosonel/F");
  TBranch * branch_3jdibosonel   =  newtree->Branch("mva3jdibosonel",   &mva3jdibosonel,    "mva3jdibosonel/F");
  TBranch * branch_2jdibnoqgel   =  newtree->Branch("mva2jdibnoqgel",   &mva2jdibnoqgel,    "mva2jdibnoqgel/F");
  TBranch * branch_3jdibnoqgel   =  newtree->Branch("mva3jdibnoqgel",   &mva3jdibnoqgel,    "mva3jdibnoqgel/F");

  Float_t effwt = 1.0, puwt = 1.0, puwt_up = 1.0, puwt_down = 1.0;
  TBranch * branch_effwt          =  newtree->Branch("effwt",       &effwt,        "effwt/F");
  TBranch * branch_puwt           =  newtree->Branch("puwt",        &puwt,         "puwt/F");
  TBranch * branch_puwt_up        =  newtree->Branch("puwt_up",     &puwt_up,      "puwt_up/F");
  TBranch * branch_puwt_down      =  newtree->Branch("puwt_down",   &puwt_down,    "puwt_down/F");
  
  Float_t qgld_Spring11[6]={-1,-1,-1,-1,-1,-1}; 
  Float_t qgld_Summer11[6]={-1,-1,-1,-1,-1,-1};
  Float_t qgld_Summer11CHS[6]={-1,-1,-1,-1,-1,-1};

  TBranch * branch_qgld_Spring11     =  newtree->Branch("qgld_Spring11",     qgld_Spring11,        "qgld_Spring11[6]/F");
  TBranch * branch_qgld_Summer11     =  newtree->Branch("qgld_Summer11",     qgld_Summer11,        "qgld_Summer11[6]/F");
  TBranch * branch_qgld_Summer11CHS  =  newtree->Branch("qgld_Summer11CHS",  qgld_Summer11CHS,     "qgld_Summer11CHS[6]/F");

  
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

  // For MVA analysis
  const char* inputVars[] = { "ptlvjj", "ylvjj", "W_muon_charge", "ang_ha", "ang_hb", "ang_hs", "ang_phi", "ang_phib" };
  std::vector<std::string> inputVarsMVA;
  for (int i=0; i<8; ++i) inputVarsMVA.push_back( inputVars[i] );

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

  // For Efficiency Correction
  EffTableLoader eleIdEff(         fDir + "eleEffsRecoToWP80_ScaleFactors.txt");
  EffTableLoader eleRecoEff(       fDir + "eleEffsSCToReco_ScaleFactors.txt");
  EffTableLoader eleHLTEff(        fDir + "eleEffsSingleElectron.txt");
  EffTableLoader eleJ30Eff(        fDir + "FullyEfficient.txt");
  EffTableLoader eleJ25NoJ30Eff(   fDir + "FullyEfficient_Jet2NoJet1.txt");
  EffTableLoader eleMHTEff(        fDir + "FullyEfficient_MHT.txt");
  EffTableLoader eleWMtEff(        fDir + "WMt50TriggerEfficiency.txt");

  // Pile up Re-weighting
  edm::Lumi3DReWeighting LumiWeights_ = edm::Lumi3DReWeighting("PUMC_dist.root", "PUData_dist.root", "pileup", "pileup", "Weight_3D.root");
  LumiWeights_.weight3D_init( 1.08 );
  
  edm::Lumi3DReWeighting up_LumiWeights_ = edm::Lumi3DReWeighting("PUMC_dist.root", "PUData_dist.root", "pileup", "pileup", "Weight_3D_up.root");
  up_LumiWeights_.weight3D_init( 1.16 );
  
  edm::Lumi3DReWeighting dn_LumiWeights_ = edm::Lumi3DReWeighting("PUMC_dist.root", "PUData_dist.root", "pileup", "pileup", "Weight_3D_down.root");
  dn_LumiWeights_.weight3D_init( 1.00 );
  
  //Re-calculate Q/G Likelihood
  //QGLikelihoodCalculator *qglikeli_Spring11    = new QGLikelihoodCalculator("./QG_QCD_Pt_15to3000_TuneZ2_Flat_7TeV_pythia6_Spring11-PU_S1_START311_V1G1-v1.root");  
  //QGLikelihoodCalculator *qglikeli_Summer11    = new QGLikelihoodCalculator("./QG_QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6_Summer11-PU_S3_START42_V11-v2.root");  
  QGLikelihoodCalculator *qglikeli_Summer11CHS = new QGLikelihoodCalculator("./QG_QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6_Summer11-PU_S3_START42_V11-v2_CHS.root");  

  // Parameter Setup
  const unsigned int jetsize         = 6;
  const double Jpt                   = 30;    // Jet pt threshold
  const double btssv                 = 1.74;  // BTagging
  const double VBF_MaxEta            = 4.5;   // VBF jet max eta
  // Loop over all events
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    //Long64_t ientry = LoadTree(jentry);
    //if (ientry < 0) break;
    nb = newtree->GetEntry(jentry);   nbytes += nb;
    // Cut variable definitions
    double jess    = 1.00; // control the jet energy scale
    double electroniso = (W_electron_trackiso+W_electron_hcaliso+W_electron_ecaliso-event_RhoForLeptonIsolation*3.141592653589*0.09)/W_electron_pt;
    double dijetpt = sqrt(JetPFCor_Pt[0]*JetPFCor_Pt[0]+
			  JetPFCor_Pt[1]*JetPFCor_Pt[1]+
			  2*JetPFCor_Pt[0]*JetPFCor_Pt[1]*cos(JetPFCor_Phi[0]-JetPFCor_Phi[1]));

    // Save variable initialization
    ggdevt    = 0;
    evtNJ     = 0;

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
    mva3j160el = 999; mva3j170el = 999; mva3j180el = 999; mva3j190el = 999; mva3j200el = 999; mva3j250el = 999; mva3j300el = 999; mva3j350el = 999; mva3j400el = 999; mva3j450el = 999; mva3j500el = 999; mva3j550el = 999; mva3j600el = 999;
    mva2jdibosonel = 999; mva3jdibosonel = 999; mva2jdibnoqgel = 999; mva3jdibnoqgel = 999;


    effwt = 1.0; puwt = 1.0; puwt_up = 1.0; puwt_down = 1.0;
    qgld_Spring11[0]= -1;       qgld_Spring11[1]= -1;       qgld_Spring11[2]= -1;       qgld_Spring11[3]= -1;       qgld_Spring11[4]= -1;       qgld_Spring11[5]= -1;
    qgld_Summer11[0]= -1;       qgld_Summer11[1]= -1;       qgld_Summer11[2]= -1;       qgld_Summer11[3]= -1;       qgld_Summer11[4]= -1;       qgld_Summer11[5]= -1;
    qgld_Summer11CHS[0]= -1;    qgld_Summer11CHS[1]= -1;    qgld_Summer11CHS[2]= -1;    qgld_Summer11CHS[3]= -1;    qgld_Summer11CHS[4]= -1;    qgld_Summer11CHS[5]= -1;

    vbf_jj_e =-999;   vbf_jj_pt =-999;   vbf_jj_eta=-999;  vbf_jj_phi =-999; vbf_jj_m =-999;   
    vbf_aj_e =-999;   vbf_aj_pt =-999;   vbf_aj_eta=-999;  vbf_aj_phi =-999; vbf_aj_m =-999;   
    vbf_bj_e =-999;   vbf_bj_pt =-999;   vbf_bj_eta=-999;  vbf_bj_phi =-999; vbf_bj_m =-999;   
    vbf_jj_deta=-999; vbf_jj_dphi=-999;  vbf_jj_type=0;    vbf_n_excj=0;     vbf_n_exfj=0;     vbf_n_gdjj=0;
    
    vbf_wjj_e =-999;   vbf_wjj_pt =-999;   vbf_wjj_eta =-999;   vbf_wjj_phi =-999;   vbf_wjj_m =-999;   
    vbf_waj_e =-999;   vbf_waj_pt =-999;   vbf_waj_eta =-999;   vbf_waj_phi =-999;   vbf_waj_m =-999;   
    vbf_wbj_e =-999;   vbf_wbj_pt =-999;   vbf_wbj_eta =-999;   vbf_wbj_phi =-999;   vbf_wbj_m =-999;   
    vbf_lvjj_e=-999;   vbf_lvjj_pt=-999;   vbf_lvjj_eta=-999;   vbf_lvjj_phi=-999;   vbf_lvjj_m=-999;   vbf_lvjj_y=-999;   
    
    vbf_event = 0; vbf_aj_id = -1; vbf_bj_id = -1; vbf_waj_id = -1; vbf_wbj_id = -1;
    vbf_wjj_ang_ha   = 999; vbf_wjj_ang_hb = 999; vbf_wjj_ang_hs = 999; vbf_wjj_ang_phi = 999; vbf_wjj_ang_phia = 999; vbf_wjj_ang_phib = 999;

    // Calculate efficiency
    effwt = 
      eleIdEff.GetEfficiency(W_electron_pt, W_electron_eta) * 
      eleRecoEff.GetEfficiency(W_electron_pt, W_electron_eta) *
      eleHLTEff.GetEfficiency(W_electron_pt, W_electron_eta) *
      eleMHTEff.GetEfficiency(event_met_pfmet, 0) *
      eleWMtEff.GetEfficiency(W_mt, W_electron_eta);

    // Pile up Re-weighting
    if (wda>20110999) {
      puwt      =    LumiWeights_.weight3D(event_mcPU_nvtx[0], event_mcPU_nvtx[1], event_mcPU_nvtx[2]);   
      puwt_up   = up_LumiWeights_.weight3D(event_mcPU_nvtx[0], event_mcPU_nvtx[1], event_mcPU_nvtx[2]);   
      puwt_down = dn_LumiWeights_.weight3D(event_mcPU_nvtx[0], event_mcPU_nvtx[1], event_mcPU_nvtx[2]);   
    } else {effwt=1.0;puwt=1.0;puwt_up=1.0;puwt_down=1.0;} // if data, always put 1 as the weighting factor

    // Jet Loop
    for(unsigned int iJet=0; iJet<jetsize;iJet++){
      if (JetPFCor_Pt[iJet]<0) continue;
      //      qgld_Spring11[iJet]= qglikeli_Spring11->computeQGLikelihoodPU( JetPFCor_Pt[iJet], event_RhoForLeptonIsolation, 
      //								     JetPFCor_ChargedMultiplicity[iJet], 
      //								     JetPFCor_NeutralMultiplicity[iJet], 
      //								     JetPFCor_PtD[iJet]);	 
      //      qgld_Summer11[iJet]= qglikeli_Summer11->computeQGLikelihoodPU( JetPFCor_Pt[iJet], event_RhoForLeptonIsolation, 
      //								     JetPFCor_ChargedMultiplicity[iJet], 
      //								     JetPFCor_NeutralMultiplicity[iJet], 
      //								     JetPFCor_PtD[iJet]);	 
      qgld_Summer11CHS[iJet]= qglikeli_Summer11CHS->computeQGLikelihoodPU( JetPFCor_Pt[iJet], event_RhoForLeptonIsolationCHS, 
									   JetPFCor_ChargedMultiplicity[iJet], 
									   JetPFCor_NeutralMultiplicity[iJet], 
									   JetPFCor_PtD[iJet]);	 
    }


    // Good Event Selection Requirement for all events
    bool  isgengdevt = 0;
    if (JetPFCor_Pt[0]>Jpt 
	&& JetPFCor_Pt[1]>Jpt 
	&& W_mt>50.
	&& W_electron_et>35. 
	&& ( (fabs(W_electron_eta)<1.5 && fabs(W_electron_deltaphi_in)<0.03 && fabs(W_electron_deltaeta_in)<0.004) || (fabs(W_electron_eta)>1.5 && fabs(W_electron_deltaphi_in)<0.02 && fabs(W_electron_deltaeta_in)<0.005) ) 
	//&& sqrt((W_electron_vx-event_BeamSpot_x)*(W_electron_vx-event_BeamSpot_x)+(W_electron_vy-event_BeamSpot_y)*(W_electron_vy-event_BeamSpot_y))<0.02 // remove the impact parameter cut for electron only
        ) isgengdevt = 1;

    // Event Selection Requirement for Standard vs QCD events
    if ( !isQCD ) {
      //keep electrons with iso<0.05, event_met_pfmet>30.0 and passing WP80.
      if ( !(electroniso<0.05)     ) isgengdevt=0;
      if ( !(event_met_pfmet>30.)  ) isgengdevt=0;
      if ( !(W_electron_isWP80==1) ) isgengdevt=0;
    } else {
      //keep electrons with 0.1<iso
      if ( !( (0.1<electroniso) )  ) isgengdevt=0;
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
    
    // 2 and 3 jet event for Mjj
    if (isgengdevt
	&& fabs(JetPFCor_Eta[0]-JetPFCor_Eta[1])<1.5
        && fabs(JetPFCor_dphiMET[0])>0.4
	&& dijetpt>40.){
      if ( JetPFCor_Pt[1] > Jpt && JetPFCor_Pt[2] < Jpt ) {evtNJ = 2;}
      if ( JetPFCor_Pt[2] > Jpt && JetPFCor_Pt[3] < Jpt ) {evtNJ = 3;}
    }
    // 2 and 3 jet event for Hww
    if (isgengdevt) { ggdevt = 4;// Do the kinematic fit for all event!!!
      if ( JetPFCor_Pt[1] > Jpt && JetPFCor_Pt[2] < Jpt ) {ggdevt = 2;}
      if ( JetPFCor_Pt[2] > Jpt && JetPFCor_Pt[3] < Jpt ) {ggdevt = 3;}
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
	  if (JetPFCor_bDiscriminator[0]>btssv) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=0; if (nbnot==2) Bj=0;}
	  if (JetPFCor_bDiscriminator[1]>btssv) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=1; if (nbnot==2) Bj=1;}
	  if (JetPFCor_bDiscriminator[2]>btssv) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=2; if (nbnot==2) Bj=2;}
	  if (JetPFCor_bDiscriminator[3]>btssv) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=3; if (nbnot==2) Bj=3;}
	  
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
	  if (JetPFCor_bDiscriminator[0]>btssv) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=0; if (nbnot==2) Bj=0;}
	  if (JetPFCor_bDiscriminator[1]>btssv) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=1; if (nbnot==2) Bj=1;}
	  if (JetPFCor_bDiscriminator[2]>btssv) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=2; if (nbnot==2) Bj=2;}
	  if (JetPFCor_bDiscriminator[3]>btssv) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=3; if (nbnot==2) Bj=3;}
	  if (JetPFCor_bDiscriminator[4]>btssv) { nbjet++; } else { nbnot++; if (nbnot==1) Aj=4; if (nbnot==2) Bj=4;}
	  
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
    // For VBF Analysis ! Currently Gd Event Selection same as Hww
    if (isgengdevt)
      {
	// ========== Find lv , wjj, vbf tag jj 
	TLorentzVector vbf_ajp(0,0,0,0), vbf_bjp(0,0,0,0);
	TLorentzVector wjj_ajp(0,0,0,0), wjj_bjp(0,0,0,0); 
	float best_detatagjj = 0; // float best_mtagjj =0;
	int   n_excj =0, n_exfj = 0, n_gdjj = 0, jj_type = 0, tag_i_id = -1, tag_j_id = -1, wjj_a_id = -1, wjj_b_id = -1;
	for ( size_t i=0; i < jetsize*2; i++) {
	  float i_rqpt= (i>5)?(30.0):(Jpt); if (runflag==1) i_rqpt= (i>5)?(25.0):(Jpt); if (runflag==2) i_rqpt= (i>5)?(20.0):(Jpt);
	  float i_Pt  = (i>5)?(JetPFCorVBFTag_Pt[i-6])            :(JetPFCor_Pt[i]);
	  float i_Eta = (i>5)?(JetPFCorVBFTag_Eta[i-6])           :(JetPFCor_Eta[i]);
	  float i_Phi = (i>5)?(JetPFCorVBFTag_Phi[i-6])           :(JetPFCor_Phi[i]);
	  float i_E   = (i>5)?(JetPFCorVBFTag_E[i-6])             :(JetPFCor_E[i]);
	  float i_bD  = (i>5)?(JetPFCorVBFTag_bDiscriminator[i-6]):(JetPFCor_bDiscriminator[i]);
	  if (i_Pt>Jpt && fabs(i_Eta)<VBF_MaxEta) {  if (i>5) {n_exfj++;} else {n_excj++;} } // when count good jet, no btag!
	  if (i_Pt<i_rqpt || i_bD>btssv || fabs(i_Eta)>VBF_MaxEta) continue;
	  for (size_t j=i+1; j <jetsize*2; j++) {
	    float j_rqpt= (j>5)?(30.0):(Jpt); if (runflag==1) j_rqpt= (i>5)?(25.0):(Jpt); if (runflag==2) j_rqpt= (i>5)?(20.0):(Jpt);
	    float j_Pt  = (j>5)?(JetPFCorVBFTag_Pt[j-6])            :(JetPFCor_Pt[j]);
	    float j_Eta = (j>5)?(JetPFCorVBFTag_Eta[j-6])           :(JetPFCor_Eta[j]);
	    float j_Phi = (j>5)?(JetPFCorVBFTag_Phi[j-6])           :(JetPFCor_Phi[j]);
	    float j_E   = (j>5)?(JetPFCorVBFTag_E[j-6])             :(JetPFCor_E[j]);
	    float j_bD  = (j>5)?(JetPFCorVBFTag_bDiscriminator[j-6]):(JetPFCor_bDiscriminator[j]);
	    if (j_Pt<j_rqpt || j_bD>btssv || fabs(j_Eta)>VBF_MaxEta) continue;
	    // vbf tag jet pair
	    TLorentzVector i_p, j_p;
	    i_p.SetPtEtaPhiE(jess * i_Pt, i_Eta, i_Phi, jess * i_E  );
	    j_p.SetPtEtaPhiE(jess * j_Pt, j_Eta, j_Phi, jess * j_E  );
	    
	    if ( (i_Eta*j_Eta)>0 )                                continue;     // 1.  have to be one forward, one backward
	    if ( (fabs(i_Eta-j_Eta)<3.5) || ((i_p+j_p).M()<300) ) continue;     // 2.  Tag pair delta eta>3.5, Mjj>300
	    // if find more than one combinations
	    if ( (fabs(i_Eta-j_Eta)>best_detatagjj) ){                          // 3   Select best combination with maximum deta Eta
	      best_detatagjj = fabs(i_Eta-j_Eta); n_gdjj++;
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
    branch_ggdevt->Fill();
    branch_evtNJ ->Fill();
    
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

    branch_2jdibosonel->Fill();
    branch_3jdibosonel->Fill();
    branch_2jdibnoqgel->Fill();
    branch_3jdibnoqgel->Fill();

    branch_effwt->Fill();
    branch_puwt->Fill();
    branch_puwt_up->Fill();
    branch_puwt_down->Fill();

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

  } // end event loop
  fresults.cd();
  newtree->Write("WJet");
  fresults.Close();
  fclose(textfile);
  std::cout <<  wda << " Finish :: " << outfilename << "    "<< nentries  << std::endl;
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

