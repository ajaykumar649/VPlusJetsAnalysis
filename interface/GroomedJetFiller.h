/*****************************************************************************
 * Project: CMS detector at the CERN
 *
 * Package: ElectroWeakAnalysis/VplusJetSubstructure
 *
 *
 * Authors:
 *   Nhan V Tran, Fermilab - kalanand@fnal.gov
 *   Kalanand Mishra, Fermilab - kalanand@fnal.gov
 *
 * Description:
 *   To fill groomed jet related quantities into a specified TTree
 *   Works with jets in PAT data format.
 * History:
 *   
 *
 * Copyright (C) 2012 FNAL 
 *****************************************************************************/

#ifndef GroomedJetFiller_h
#define GroomedJetFiller_h

// system include files
#include <memory>
#include <string>
#include <iostream>
#include <map>
#include <fstream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h" 

#include "TFile.h"
#include "TTree.h"

#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"

#include <fastjet/JetDefinition.hh>
#include <fastjet/PseudoJet.hh>

#include <stdlib.h>
#include <math.h>
#include "TMatrixD.h"
#include "TMatrixDSym.h"
//
// class decleration
//
namespace ewk
{
    class GroomedJetFiller {
    public:
    /// specify the name of the TTree, and the configuration for it
      GroomedJetFiller(const char *name, 
		       TTree* tree, 
		       const std::string jetLabel,
		       const std::string srcGroomedJet,
		       const edm::ParameterSet& iConfig, bool isGen = 0);

      /// default constructor
      GroomedJetFiller() {};


    /// Destructor, does nothing 
      //~GroomedJetFiller(){  if(jec_) delete jec_;  if(jecUnc_) delete jecUnc_; };
      ~GroomedJetFiller(){ };
         
    /// To be called once per event to fill the values for groomed jets
    void fill(const edm::Event& iEvent);        

    static const int NUM_JET_MAX = 6;

    protected:
      // 'mutable' because we will fill it from a 'const' method
      mutable std::vector<std::string> bnames;
     /// Helper function for main constructor
    void SetBranch( float* x, std::string name);
    void SetBranch( int* x, std::string name);
    void SetBranchSingle( float* x, std::string name);
    void SetBranchSingle( int* x, std::string name);
    double getJEC(double curJetEta, double curJetPt, double curJetE, double curJetArea); 
    TLorentzVector getCorrectedJet(fastjet::PseudoJet& jet, double inArea);
    void computeCore( std::vector<fastjet::PseudoJet> constits, double Rval, float &m_core, float &pt_core );
    void computePlanarflow(std::vector<fastjet::PseudoJet> constits,double Rval,fastjet::PseudoJet jet,std::string mJetAlgo,float &planarflow);
        float computeJetCharge( std::vector<fastjet::PseudoJet> constits, std::vector<float> pdgIds, float PTjet );        
        float getPdgIdCharge( float fid );        

    TTree* tree_;
    bool runningOverMC_;
    bool applyJECToGroomedJets_;

    FactorizedJetCorrector* jec_;
    JetCorrectionUncertainty* jecUnc_;
    
    std::string jetLabel_;
    std::string JetsFor_rho;
    std::string JEC_GlobalTag_forGroomedJet;
    edm::InputTag mPrimaryVertex;
    std::string mGroomedJet;
        
            // specific parameters
        double mJetRadius;
        std::string mJetAlgo;        
        std::string lableGen;        
        
        double mJetChargeKappa;
        bool mDoQJets; 
        int mQJetsPreclustering;
        int mQJetsN;
        double mNsubjettinessKappa;
        bool mSaveConstituents;

    private:
    
    // ----------member data ---------------------------
    // names of modules, producing object collections    
    float jetmass_uncorr[NUM_JET_MAX];
    float jetmass_tr_uncorr[NUM_JET_MAX];
    float jetmass_ft_uncorr[NUM_JET_MAX];
    float jetmass_pr_uncorr[NUM_JET_MAX];
    float tau2tau1[NUM_JET_MAX];
    float tau1[NUM_JET_MAX];
    float tau2[NUM_JET_MAX];
    float tau3[NUM_JET_MAX];
    float tau4[NUM_JET_MAX];
    float massdrop_pr_uncorr[NUM_JET_MAX];
    
    float jetpt_uncorr[NUM_JET_MAX];
    float jetpt[NUM_JET_MAX];
    float jeteta[NUM_JET_MAX];
    float jetphi[NUM_JET_MAX];
    float jete[NUM_JET_MAX];

    float jetpt_tr_uncorr[NUM_JET_MAX];
    float jetpt_tr[NUM_JET_MAX];
    float jeteta_tr[NUM_JET_MAX];
    float jetphi_tr[NUM_JET_MAX];
    float jete_tr[NUM_JET_MAX];

    float jetpt_ft_uncorr[NUM_JET_MAX];
    float jetpt_ft[NUM_JET_MAX];
    float jeteta_ft[NUM_JET_MAX];
    float jetphi_ft[NUM_JET_MAX];
    float jete_ft[NUM_JET_MAX];

    float jetpt_pr_uncorr[NUM_JET_MAX];
    float jetpt_pr[NUM_JET_MAX];
    float jeteta_pr[NUM_JET_MAX];
    float jetphi_pr[NUM_JET_MAX];
    float jete_pr[NUM_JET_MAX];
        
    float prsubjet1_px[NUM_JET_MAX];
    float prsubjet1_py[NUM_JET_MAX];
    float prsubjet1_pz[NUM_JET_MAX];
    float prsubjet1_e[NUM_JET_MAX];        
    float prsubjet2_px[NUM_JET_MAX];
    float prsubjet2_py[NUM_JET_MAX];
    float prsubjet2_pz[NUM_JET_MAX];
    float prsubjet2_e[NUM_JET_MAX];        
        
        
    float jetmass[NUM_JET_MAX];
    float jetmass_tr[NUM_JET_MAX];
    float jetmass_ft[NUM_JET_MAX];
    float jetmass_pr[NUM_JET_MAX];
    float jetarea[NUM_JET_MAX];
    float jetarea_tr[NUM_JET_MAX];
    float jetarea_ft[NUM_JET_MAX];
    float jetarea_pr[NUM_JET_MAX];        
    float massdrop_pr[NUM_JET_MAX];
    float jetconstituents[NUM_JET_MAX];   
    float jetcharge[NUM_JET_MAX];           
    float jetGeneralizedECF[NUM_JET_MAX];           

    float rcores[11][NUM_JET_MAX];
    float ptcores[11][NUM_JET_MAX];
     
    float planarflow[11][NUM_JET_MAX];

    float qjetmass[50];
    float qjetmassdrop[50];

        float constituents0_eta[100];
        float constituents0_phi[100];        
        float constituents0_e[100];        
        int nconstituents0;    
        
        float constituents0pr_eta[100];
        float constituents0pr_phi[100];        
        float constituents0pr_e[100];        
        int nconstituents0pr;   
        
        std::vector<int> neutrals;
        std::vector<int> positives;
        std::vector<int> negatives;        
        std::vector<float>  charge_handle_Gen;

    
    double rhoVal_;
    double nPV_;
    bool isGenJ;
    };
}
#endif
