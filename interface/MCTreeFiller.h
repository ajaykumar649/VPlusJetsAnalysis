/*****************************************************************************
 * Project: CMS detector at the CERN
 *
 * Package: ElectroWeakAnalysis/VPlusJets
 * Class:   MCTreeFiller
 *
 * Authors:
 *
 *   Kalanand Mishra, Fermilab - kalanand@fnal.gov
 *
 * Description:
 *   To fill W/Z related MC information into a specified TTree
 *   Can work with jets in RECO/AOD/PAT data formats.
 * History:
 *   
 *
 * Copyright (C) 2010 FNAL 
 *****************************************************************************/

#ifndef ElectroWeakAnalysis_VPlusJets_MCTreeFiller_h
#define ElectroWeakAnalysis_VPlusJets_MCTreeFiller_h

#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include "TTree.h" 
#include "FWCore/Framework/interface/Event.h" 
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"


namespace ewk {

  class MCTreeFiller {
  public:
    /// specify the name of the TTree, and the configuration for it
    MCTreeFiller(const char *name, TTree* tree, 
			  const edm::ParameterSet iConfig );

    /// default constructor
    MCTreeFiller() {};


    /// Destructor, does nothing 
      ~MCTreeFiller() {};


    /// To be called once per event to fill the values for jets
    void fill(const edm::Event &iEvent);


  protected:

    /// To be called once per event, to initialize variable values to default
    void init();
    /// Helper function for main constructor
    void SetBranches(); 
    void SetBranch( float* x, std::string name );
    void SetBranch( int* x, std::string name );
    void SetBranch( bool* x, std::string name );

    TTree* tree_;
    const char *  name_;
    std::string Vtype_;
    std::string ptype_;
    int pdgIdDau_;
    edm::InputTag mInputBoson;

  private:
    // private data members
    
    float V_mass;
    float V_px;
    float V_py;
    float V_pz;
    float V_E;
    float V_Pt;
    float V_Et;
    float V_Eta;
    float V_Phi;
    float V_Vx;
    float V_Vy;
    float V_Vz;
    float V_Y;

    int l1Charge;
    int l2Charge;

    float l1px;
    float l1py;
    float l1pz;
    float l1E;
    float l1Et;
    float l1Pt;
    float l1Eta;
    float l1Theta;
    float l1Phi;
    float l1Vx;
    float l1Vy;
    float l1Vz;
    float l1Y;
	  
    ///////////////////
    float l2px;
    float l2py;
    float l2pz;
    float l2E;
    float l2Pt;
    float l2Et;
    float l2Eta;
    float l2Theta;
    float l2Phi;
    float l2Vx;
    float l2Vy;
    float l2Vz;
    float l2Y;	  

  };

} //namespace

#endif


