/*****************************************************************************
 * Project: CMS detector at the CERN
 *
 * Package: ElectroWeakAnalysis/VPlusJets
 *
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

// CMS includes
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TMath.h" 
// Header file
#include "ElectroWeakAnalysis/VPlusJets/interface/MCTreeFiller.h"


ewk::MCTreeFiller::MCTreeFiller(const char *name, TTree* tree, 
				const edm::ParameterSet iConfig)
{

  // ********** Vector boson ********** //
  tree_     = tree;
  name_     = name;
  Vtype_    = iConfig.getParameter<std::string>("VBosonType"); 
  ptype_    = iConfig.getParameter<std::string>("LeptonType");
  pdgIdDau_ = 11;
  if(ptype_=="muon") pdgIdDau_ = 13; 
  if( !(tree==0) ) SetBranches();
}





void ewk::MCTreeFiller::SetBranches()
{
  // Declare jet branches
  std::string lept1;
  std::string lept2;
  if( Vtype_=="Z" ) {
    if(ptype_=="muon") {
      lept1 = "muplus";
      lept2 = "muminus";
    } else {
      lept1 = "eplus";
      lept2 = "eminus";
    } 
  } else {
    if(ptype_=="muon") {
      lept1 = "muon";
      lept2 = "neutino";
    } else {
      lept1 = "electron";
      lept2 = "neutrino";
    }
  }

  SetBranch( &V_mass,      "mass_gen");
  SetBranch( &V_px,        "px_gen");
  SetBranch( &V_py,        "py_gen");
  SetBranch( &V_pz,        "pz_gen");
  SetBranch( &V_E,         "e_gen");
  SetBranch( &V_Pt,        "pt_gen");
  SetBranch( &V_Et,        "et_gen");
  SetBranch( &V_Eta,       "eta_gen");    
  SetBranch( &V_Phi,       "phi_gen");
  SetBranch( &V_Vx,        "vx_gen");
  SetBranch( &V_Vy,        "vy_gen");
  SetBranch( &V_Vz,        "vz_gen");
  SetBranch( &V_Y,         "y_gen");
  ///////////////////////////////////////////////
  SetBranch( &l1px,             lept1+"_px_gen" );
  SetBranch( &l1py,             lept1+"_py_gen" );
  SetBranch( &l1pz,             lept1+"_pz_gen" );
  SetBranch( &l1E,              lept1+"_e_gen" );
  SetBranch( &l1Pt,             lept1+"_pt_gen" );
  SetBranch( &l1Et,             lept1+"_et_gen" );
  SetBranch( &l1Eta,            lept1+"_eta_gen" ); 
  SetBranch( &l1Theta,          lept1+"_theta_gen" ); 
  SetBranch( &l1Phi,            lept1+"_phi_gen" );
  SetBranch( &l1Charge,         lept1+"_charge_gen" );
  SetBranch( &l1Vx,             lept1+"_vx_gen" );
  SetBranch( &l1Vy,             lept1+"_vy_gen" );
  SetBranch( &l1Vz,             lept1+"_vz_gen" );
  SetBranch( &l1Y,              lept1+"_y_gen" );
	  
  ////////////////////////////////////////////////////////
  SetBranch( &l2px,             lept2+"_px_gen" );
  SetBranch( &l2py,             lept2+"_py_gen" );
  SetBranch( &l2pz,             lept2+"_pz_gen" );
  SetBranch( &l2E,              lept2+"_e_gen" );
  SetBranch( &l2Pt,             lept2+"_pt_gen" );
  SetBranch( &l2Et,             lept2+"_et_gen" );
  SetBranch( &l2Eta,            lept2+"_eta_gen" ); 
  SetBranch( &l2Theta,          lept2+"_theta_gen" );    
  SetBranch( &l2Phi,            lept2+"_phi_gen" );
  SetBranch( &l2Charge,         lept2+"_charge_gen" );
  SetBranch( &l2Vx,             lept2+"_vx_gen" );
  SetBranch( &l2Vy,             lept2+"_vy_gen" );
  SetBranch( &l2Vz,             lept2+"_vz_gen" );
  SetBranch( &l2Y,              lept2+"_y_gen" );
    
}
/////////////////////////////////////////////////////////////////////////






void ewk::MCTreeFiller::init()   
{
  // initialize private data members
  V_mass                  = -1.;
  V_px                  = -99999.;
  V_py                  = -99999.;
  V_pz                  = -99999.;
  V_E                   = -1.;
  V_Pt                  = -1.;
  V_Et                  = -1.;
  V_Eta                 = -10.;
  V_Phi                 = -10.;
  V_Vx                  = -10.;
  V_Vy                  = -10.;
  V_Vz                  = -10.;
  V_Y                   = -10.;

  l1Charge           = -10;
  l2Charge          = -10;

  l1px               = -99999.;
  l1py               = -99999.;
  l1pz               = -99999.;
  l1E                = -1.;
  l1Et               = -1.;
  l1Pt               = -1.;
  l1Eta              = -10.;
  l1Theta            = -99999.;
  l1Phi              = -10.;
  l1Vx               = -10.;
  l1Vy               = -10.;
  l1Vz               = -10.;
  l1Y                = -10.;	  
	  
  l2px              = -99999.;
  l2py              = -99999.;
  l2pz              = -99999.;
  l2E               = -1.;
  l2Pt              = -1.;
  l2Et              = -1.;
  l2Eta             = -10.;
  l2Theta           = -99999.;
  l2Phi             = -10.;
  l2Vx              = -10.;
  l2Vy              = -10.;
  l2Vz              = -10.;
  l2Y               = -10.;
  // initialization done
}







void ewk::MCTreeFiller::fill(const edm::Event& iEvent)
{
  // first initialize to the default values
  init();


  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel("genParticles", genParticles);

  size_t nGen = genParticles->size();
  if( nGen < 1 ) return; // Nothing to fill


  // now iterate over the daughters  
  const reco::Candidate *V=NULL;
  const reco::Candidate* lepton1=NULL;
  const reco::Candidate* lepton2=NULL;

  for(size_t i = 0; i < nGen; ++ i) {

    V = &((*genParticles)[i]);

    // The vector boson must have stutus==3  
    if( !(abs(V->status())==3) ) continue;

    size_t ndau = 0;
    if(!(V==NULL)) ndau = V->numberOfDaughters();

    // The vector boson must decay to leptons
    if(ndau<1) continue;
    if( (Vtype_=="Z") && !( V->pdgId()==22 || V->pdgId()==23) ) continue;
    if( (Vtype_=="W") && !(abs(V->pdgId())==24) ) continue;

    // Loop over daugthers
    for(size_t j = 0; j < ndau; ++ j) {
      const reco::Candidate *d = V->daughter( j );
      // first look for Z --> l+l-
      if( !(d==NULL) && (V->pdgId()==23 || V->pdgId()==22) ) {
        if (d->pdgId()==-pdgIdDau_)  lepton1  = d;
        if (d->pdgId()==pdgIdDau_) lepton2 = d;
      } // if not, then look for W-->lnu
      else if( !(d==NULL) && abs(V->pdgId())==24) {
        if ( abs(d->pdgId())==pdgIdDau_ )  lepton1  = d;
        if ( abs(d->pdgId())==(pdgIdDau_+1) )  lepton2  = d;
      } 
    } // end ndaughter loop

  } // end nGen loop

  if( V==NULL ) return;
  ////////// Vector boson quantities //////////////
  V_mass = V->mass();
  V_Eta = V->eta();   
  V_Phi = V->phi();
  V_Vx = V->vx();
  V_Vy = V->vy();
  V_Vz = V->vz();
  V_Y  = V->rapidity();
  V_px = V->px();
  V_py = V->py();
  V_pz = V->pz();
  V_E  = V->energy();
  V_Pt = V->pt();
  V_Et = V->et();

  ////////// lepton #1 quantities //////////////
  if( !(lepton1 == NULL) ) {
    l1Charge           = lepton1-> charge();
    l1Vx               = lepton1->vx();
    l1Vy               = lepton1->vy();
    l1Vz               = lepton1->vz();
    l1Y                = lepton1->rapidity();
    l1Theta            = lepton1->theta();
    l1Eta              = lepton1->eta();    
    l1Phi              = lepton1->phi();
    l1E                = lepton1->energy();
    l1px               = lepton1->px();
    l1py               = lepton1->py();
    l1pz               = lepton1->pz();
    l1Pt               = lepton1->pt();
    l1Et               = lepton1->et();	  
  }

  ////////// lepton #2 quantities: in case of Z ///////
  if( !(lepton2 == NULL) ) {
    l2Charge          = lepton2->charge();
    l2Vx              = lepton2->vx();
    l2Vy              = lepton2->vy();
    l2Vz              = lepton2->vz();
    l2Y               = lepton2->rapidity();
    l2Theta           = lepton2->theta();
    l2Eta             = lepton2->eta();    
    l2Phi             = lepton2->phi();
    l2E               = lepton2->energy();
    l2px              = lepton2->px();
    l2py              = lepton2->py();
    l2pz              = lepton2->pz();
    l2Pt              = lepton2->pt();
    l2Et              = lepton2->et();	 
  } 

}





////////////////// utilities, helpers ///////////////////
 
void ewk::MCTreeFiller::SetBranch( float* x, std::string name)
{
  std::string brName = std::string(name_) + "_" + name;
  tree_->Branch( brName.c_str(), x, ( brName+"/F").c_str() );
}


void ewk::MCTreeFiller::SetBranch( int* x, std::string name)
{
  std::string brName = std::string(name_) + "_" + name;
  tree_->Branch( brName.c_str(), x, ( brName+"/I").c_str() );
}


void ewk::MCTreeFiller::SetBranch( bool* x, std::string name)
{
  std::string brName = std::string(name_) + "_" + name;
  tree_->Branch( brName.c_str(), x, ( brName+"/O").c_str() );
}

