
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
 *   To fill lepton, jet, MET information into a specified TTree
 * History:
 *   
 *
 * Copyright (C) 2013 FNAL 
 *****************************************************************************/

// CMS includes
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TMath.h" 
// Header file
#include "ElectroWeakAnalysis/VPlusJets/interface/SnowmassTreeProducer.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/METReco/interface/GenMETCollection.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Candidate/interface/Particle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "EgammaAnalysis/ElectronTools/interface/ElectronEffectiveArea.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidatePhotonExtraFwd.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidatePhotonExtra.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "DataFormats/ParticleFlowReco/interface/PFClusterFwd.h"
#include "DataFormats/ParticleFlowReco/interface/PFCluster.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"


ewk::SnowmassTreeProducer::SnowmassTreeProducer(const edm::ParameterSet iConfig) :

  fOutputFileName ( iConfig.getParameter<std::string>("HistOutFile") ),
  hOutputFile ( new TFile( fOutputFileName.c_str(), "RECREATE" ) ), 
  tree_ ( new TTree("tree","tree") )
{
  mInputJets = iConfig.getParameter<edm::InputTag>("srcJets");
}


ewk::SnowmassTreeProducer::~SnowmassTreeProducer() {}



void ewk::SnowmassTreeProducer::beginJob()
{

  // Declare all the branches of the tree
  tree_->Branch("event_runNo",  &run,   "event_runNo/I");
  tree_->Branch("event_evtNo",  &event, "event_evtNo/I");
  tree_->Branch("event_lumi",   &lumi,  "event_lumi/I"); 
  tree_->Branch("event_bunch",  &bunch, "event_bunch/I"); 
  tree_->Branch("event_nPV",    &nPV,   "event_nPV/I"); 
  tree_->Branch("event_met",    &Met_Et,  "event_met/F"); 
  tree_->Branch("event_met_px", &Met_px,  "event_met_px/F"); 
  tree_->Branch("event_met_py", &Met_py,  "event_met_py/F"); 
  tree_->Branch("event_sumet",  &Met_SumET,"event_sumet/F"); 
  tree_->Branch("event_met_phi",&Met_Phi,  "event_met_phi/F"); 	
  tree_->Branch("event_fastJetRho",&fastJetRho,  "event_fastJetRho/F"); 

  // ----------------------- Declare branches -----------------------
  ///////////////////////////////////////////////
  SetBranch( &l1size,           "muon_size" );
  SetBranch( l1px,             "muon_px[muon_size]" );
  SetBranch( l1py,             "muon_py[muon_size]" );
  SetBranch( l1pz,             "muon_pz[muon_size]" );
  SetBranch( l1E,              "muon_e[muon_size]" );
  SetBranch( l1Pt,             "muon_pt[muon_size]" );
  SetBranch( l1Eta,            "muon_eta[muon_size]" ); 
  SetBranch( l1Phi,            "muon_phi[muon_size]" );
  SetBranch( l1Charge,         "muon_charge[muon_size]" );
  SetBranch( l1Vx,             "muon_vx[muon_size]" );
  SetBranch( l1Vy,             "muon_vy[muon_size]" );
  SetBranch( l1Vz,             "muon_vz[muon_size]" );
  SetBranch( l1Y,              "muon_y[muon_size]" );
  SetBranch( l1trackiso,              "muon_trackiso[muon_size]" );
  SetBranch( l1ecaliso,              "muon_ecaliso[muon_size]" );
  SetBranch( l1hcaliso,              "muon_hcaliso[muon_size]" );
  SetBranch( l1Type,              "muon_Type[muon_size]" );
  SetBranch( l1_numberOfChambers,              "muon_numberOfChambers[muon_size]" );
  SetBranch( l1_numberOfMatches,              "muon_numberOfMatches[muon_size]" );
  SetBranch( l1pfiso_sumChargedHadronPt,              "muon_pfiso_sumChargedHadronPt[muon_size]" );
  SetBranch( l1pfiso_sumChargedParticlePt,              "muon_pfiso_sumChargedParticlePt[muon_size]" );
  SetBranch( l1pfiso_sumNeutralHadronEt,              "muon_pfiso_sumNeutralHadronEt[muon_size]" );
  SetBranch( l1pfiso_sumPhotonEt,              "muon_pfiso_sumPhotonEt[muon_size]" );
  SetBranch( l1pfiso_sumPUPt,              "muon_pfiso_sumPUPt[muon_size]" );
  SetBranch( l1_d0bsp,              "muon_d0bsp[muon_size]" );
  SetBranch( l1_dz000,              "muon_dz000[muon_size]" );
  SetBranch( l1_IP3D,              "muon_IP3D[muon_size]" );
  SetBranch( l1_dzPV,              "muon_dzPV[muon_size]" );

	  
  ////////////////////////////////////////////////////////
  SetBranch( &l2size,           "electron_size" );
  SetBranch( l2px,             "electron_px[electron_size]" );
  SetBranch( l2py,             "electron_py[electron_size]" );
  SetBranch( l2pz,             "electron_pz[electron_size]" );
  SetBranch( l2E,              "electron_e[electron_size]" );
  SetBranch( l2Pt,             "electron_pt[electron_size]" );
  SetBranch( l2Eta,            "electron_eta[electron_size]" ); 
  SetBranch( l2Phi,            "electron_phi[electron_size]" );
  SetBranch( l2Charge,         "electron_charge[electron_size]" );
  SetBranch( l2Vx,             "electron_vx[electron_size]" );
  SetBranch( l2Vy,             "electron_vy[electron_size]" );
  SetBranch( l2Vz,             "electron_vz[electron_size]" );
  SetBranch( l2Y,              "electron_y[electron_size]" );
  SetBranch( l2trackiso,              "electron_trackiso[electron_size]" );
  SetBranch( l2ecaliso,              "electron_ecaliso[electron_size]" );
  SetBranch( l2hcaliso,              "electron_hcaliso[electron_size]" );
  SetBranch( l2_classification,              "electron_classification[electron_size]" );
  SetBranch( l2_HoverE,              "electron_HoverE[electron_size]" );
  SetBranch( l2_EoverP,              "electron_EoverP[electron_size]" );
  SetBranch( l2_DeltaEta,              "electron_DeltaEta[electron_size]" );
  SetBranch( l2_DeltaPhi,              "electron_DeltaPhi[electron_size]" );
  SetBranch( l2_numberOfBrems,              "electron_numberOfBrems[electron_size]" );
  SetBranch( l2_BremFraction,              "electron_BremFraction[electron_size]" );
  SetBranch( l2_SigmaIetaIeta,              "electron_SigmaIetaIeta[electron_size]" );
  SetBranch( l2_missingHits,              "electron_missingHits[electron_size]" );
  SetBranch( l2_dist,              "electron_convDist[electron_size]" );
  SetBranch( l2_dcot,              "electron_convDcot[electron_size]" );
  SetBranch( l2_convradius,              "electron_convRadius[electron_size]" );
  SetBranch( l2pfiso_chargedHadronIso,              "electron_pfiso_chargedHadron[electron_size]" );
  SetBranch( l2pfiso_photonIso,              "electron_pfiso_photon[electron_size]" );
  SetBranch( l2pfiso_neutralHadronIso,              "electron_pfiso_neutralHadron[electron_size]" );
  SetBranch( l2pfiso_EffAreaPU,              "electron_pfiso_EffAreaPU[electron_size]" );
  SetBranch( l2pfiso_pfIsoEA,              "electron_pfiso_pfIsoEA[electron_size]" );
  SetBranch( l2_d0bsp,              "electron_d0bsp[electron_size]" );
  SetBranch( l2_dz000,              "electron_dz000[electron_size]" );
  SetBranch( l2_IP3D,              "electron_IP3D[electron_size]" );
  SetBranch( l2_dzPV,              "electron_dzPV[electron_size]" );

  ////////////////////////////////////////////////////////
  SetBranch( &jet_size,          "jet_size" );
  SetBranch( jet_px,             "jet_px[jet_size]" );
  SetBranch( jet_py,             "jet_py[jet_size]" );
  SetBranch( jet_pz,             "jet_pz[jet_size]" );
  SetBranch( jet_E,              "jet_E[jet_size]" );
  SetBranch( jet_Pt,             "jet_pt[jet_size]" );
  SetBranch( jet_Eta,            "jet_eta[jet_size]" ); 
  SetBranch( jet_Phi,            "jet_phi[jet_size]" );
  SetBranch( jet_Y,              "jet_y[jet_size]" );
  SetBranch( jet_area,           "jet_area[jet_size]" );
  SetBranch( jet_bDiscriminatorSSVHE,           "jet_bDiscriminatorSSVHE[jet_size]" );
  SetBranch( jet_bDiscriminatorTCHE,           "jet_bDiscriminatorTCHE[jet_size]" );
  SetBranch( jet_bDiscriminatorCSV,           "jet_bDiscriminatorCSV[jet_size]" );
  SetBranch( jet_bDiscriminatorJP,           "jet_bDiscriminatorJP[jet_size]" );
  SetBranch( jet_bDiscriminatorSSVHP,           "jet_bDiscriminatorSSVHP[jet_size]" );
  SetBranch( jet_bDiscriminatorTCHP,           "jet_bDiscriminatorTCHP[jet_size]" );

  ////////////////////////////////////////////////////////
  SetBranch( &photon_size,          "photon_size" );
  SetBranch( photon_px, "photon_px[photon_size]");
  SetBranch( photon_py, "photon_py[photon_size]");
  SetBranch( photon_pz, "photon_pz[photon_size]");
  SetBranch( photon_E, "photon_E[photon_size]");
  SetBranch( photon_pt, "photon_pt[photon_size]");
  SetBranch( photon_eta, "photon_eta[photon_size]");
  SetBranch( photon_phi, "photon_phi[photon_size]");
  SetBranch( photon_vx, "photon_vx[photon_size]");
  SetBranch( photon_vy, "photon_vy[photon_size]");
  SetBranch( photon_vz, "photon_vz[photon_size]");
//   SetBranch( photon_pfiso_charged, "photon_pfiso_charged[photon_size]");
//   SetBranch( photon_pfiso_photon, "photon_pfiso_photon[photon_size]");
//   SetBranch( photon_pfiso_neutral, "photon_pfiso_neutral[photon_size]");
  SetBranch( photon_trackiso, "photon_trackiso[photon_size]");
  SetBranch( photon_ecaliso, "photon_ecaliso[photon_size]");
  SetBranch( photon_hcaliso, "photon_hcaliso[photon_size]");
  SetBranch( photon_HoverE, "photon_HoverE[photon_size]");
  SetBranch( photon_SigmaIetaIeta, "photon_SigmaIetaIeta[photon_size]");
  SetBranch( photon_hasPixelSeed, "photon_hasPixelSeed[photon_size]");
  SetBranch( photon_passElecVeto, "photon_passElecVeto[photon_size]");

  ////////////////////////////////////////////////////////
  /*
  SetBranch( &track_size,            "track_size" );
  SetBranch( track_px,               "track_px" );
  SetBranch( track_py,               "track_py" );
  SetBranch( track_pz,               "track_pz" );
  SetBranch( track_Vx,               "track_Vx" );
  SetBranch( track_Vy,               "track_Vy" );
  SetBranch( track_Vz,               "track_Vz" );
  SetBranch( track_Pt,               "track_Pt" );
  SetBranch( track_Eta,              "track_Eta" );
  SetBranch( track_Phi,              "track_Phi" );
  */

  ///////////////////////////////////////////////
  SetBranch( &genPart_size,          "genParticle_size" );
  SetBranch( genPart_px,             "genParticle_px[genParticle_size]" );
  SetBranch( genPart_py,             "genParticle_py[genParticle_size]" );
  SetBranch( genPart_pz,             "genParticle_pz[genParticle_size]" );
  SetBranch( genPart_E,              "genParticle_e[genParticle_size]" );
  SetBranch( genPart_Pt,             "genParticle_pt[genParticle_size]" );
  SetBranch( genPart_Eta,            "genParticle_eta[genParticle_size]" ); 
  SetBranch( genPart_Phi,            "genParticle_phi[genParticle_size]" );
  SetBranch( genPart_Charge,         "genParticle_charge[genParticle_size]" );
  SetBranch( genPart_Vx,             "genParticle_vx[genParticle_size]" );
  SetBranch( genPart_Vy,             "genParticle_vy[genParticle_size]" );
  SetBranch( genPart_Vz,             "genParticle_vz[genParticle_size]" );
  SetBranch( genPart_Y,              "genParticle_y[genParticle_size]" );
  SetBranch( genPart_Status,         "genPart_Status[genParticle_size]" );
  SetBranch( genPart_pdgId,          "genPart_pdgId[genParticle_size]" );

  ////////////////////////////////////////////////////////
  SetBranch( &genjet_size,          "genjet_size" );
  SetBranch( genjet_px,             "genjet_px[genjet_size]" );
  SetBranch( genjet_py,             "genjet_py[genjet_size]" );
  SetBranch( genjet_pz,             "genjet_pz[genjet_size]" );
  SetBranch( genjet_E,              "genjet_E[genjet_size]" );
  SetBranch( genjet_Pt,             "genjet_pt[genjet_size]" );
  SetBranch( genjet_Eta,            "genjet_eta[genjet_size]" ); 
  SetBranch( genjet_Phi,            "genjet_phi[genjet_size]" );
  SetBranch( genjet_Y,              "genjet_y[genjet_size]" );
  SetBranch( genjet_area,           "genjet_area[genjet_size]" );

}
/////////////////////////////////////////////////////////////////////////







void ewk::SnowmassTreeProducer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // first initialize to the default values
  genPart_size       = 0;
  l1size             = 0; 
  l2size             = 0;
  jet_size           = 0;
  photon_size        = 0;
  genjet_size        = 0;
  track_size         = 0;

  Met_px              = -99999.;
  Met_py              = -99999.;
  Met_Et              = -99999.;
  Met_Phi             = -99999.;
  Met_SumET           = -99999.;

  for ( int i =0; i<999; i++){

    l1Charge[i]           = -99999;
    l1px[i]               = -99999.;
    l1py[i]               = -99999.;
    l1pz[i]               = -99999.;
    l1E[i]                = -99999.;
    l1Pt[i]               = -99999.;
    l1Eta[i]              = -99999.;
    l1Phi[i]              = -99999.;
    l1Vx[i]               = -99999.;
    l1Vy[i]               = -99999.;
    l1Vz[i]               = -99999.;
    l1Y[i]                = -99999.;
    l1trackiso[i]= -99999.;
    l1ecaliso[i]= -99999.;
    l1hcaliso[i]= -99999.;
    l1Type[i]= -99999;
    l1_numberOfChambers[i]= -99999.;      
    l1_numberOfMatches[i]= -99999.;
    l1pfiso_sumChargedHadronPt[i]= -99999.;
    l1pfiso_sumChargedParticlePt[i]= -99999.;
    l1pfiso_sumNeutralHadronEt[i]= -99999.;
    l1pfiso_sumPhotonEt[i]= -99999.;
    l1pfiso_sumPUPt[i]= -99999.;
    l1_d0bsp[i]= -99999.;
    l1_dz000[i]= -99999.;
    l1_IP3D[i]= -99999.;
    l1_dzPV[i]= -99999.;


    l2Charge[i]           = -99999;	  
    l2px[i]               = -99999.;
    l2py[i]               = -99999.;
    l2pz[i]               = -99999.;
    l2E[i]                = -99999.;
    l2Pt[i]               = -99999.;
    l2Eta[i]              = -99999.;
    l2Phi[i]              = -99999.;
    l2Vx[i]               = -99999.;
    l2Vy[i]               = -99999.;
    l2Vz[i]               = -99999.;
    l2Y[i]                = -99999.;
    l2trackiso[i]       = -99999.;
    l2ecaliso[i]        = -99999.;
    l2hcaliso[i]        = -99999.;
    l2_classification[i]  = -99999;
    l2_HoverE[i] = -99999.;	 
    l2_EoverP[i]       = -99999.;
    l2_DeltaEta[i]     = -99999.;
    l2_DeltaPhi[i]     = -99999.;
    l2_numberOfBrems[i]  = -99999;      
    l2_BremFraction[i]   = -99999.;
    l2_SigmaIetaIeta[i] = -99999.;
    l2_missingHits[i]   = -99999;
    l2_dist[i]          = -99999.;
    l2_dcot[i]          = -99999.;
    l2_convradius[i]    = -99999.;
    l2pfiso_chargedHadronIso[i]   = -99999.;
    l2pfiso_photonIso[i] = -99999.;
    l2pfiso_neutralHadronIso[i]   = -99999.;
    l2pfiso_EffAreaPU[i] = -99999.;
    l2pfiso_pfIsoEA[i] = -99999.;
    l2_d0bsp[i] = -99999.;
    l2_dz000[i] = -99999.;
    l2_IP3D[i] = -99999.;
    l2_dzPV[i] = -99999.;


    jet_px[i]             = -99999.;
    jet_py[i]             = -99999.;
    jet_pz[i]             = -99999.;
    jet_E[i]              = -99999.;
    jet_Pt[i]             = -99999.;
    jet_Eta[i]            = -99999.;
    jet_Phi[i]            = -99999.;
    jet_Y[i]              = -99999.;
    jet_area[i]           = -99999.;
    jet_bDiscriminatorSSVHE[i] = -99999.;
    jet_bDiscriminatorTCHE[i]  = -99999.;
    jet_bDiscriminatorCSV[i]   = -99999.;
    jet_bDiscriminatorJP[i]    = -99999.;
    jet_bDiscriminatorSSVHP[i] = -99999.;
    jet_bDiscriminatorTCHP[i]  = -99999.;
    
    photon_px[i]  = -99999.;
    photon_py[i]  = -99999.;
    photon_pz[i]  = -99999.;
    photon_E[i]  = -99999.;
    photon_pt[i]  = -99999.;
    photon_eta[i]  = -99999.;
    photon_phi[i]  = -99999.;
    photon_vx[i]  = -99999.;
    photon_vy[i]  = -99999.;
    photon_vz[i]  = -99999.;
    photon_pfiso_charged[i]  = -99999.;
    photon_pfiso_photon[i]  = -99999.;
    photon_pfiso_neutral[i]  = -99999.;
    photon_trackiso[i]  = -99999.;
    photon_ecaliso[i]  = -99999.;
    photon_hcaliso[i]  = -99999.;
    photon_HoverE[i]  = -99999.;
    photon_SigmaIetaIeta[i]  = -99999.;
    photon_hasPixelSeed[i]  = 0;
    photon_passElecVeto[i]  = 0;

    track_px[i]                 = -99999.;
    track_py[i]                 = -99999.;
    track_pz[i]                 = -99999.;
    track_Vx[i]                 = -99999.;
    track_Vy[i]                 = -99999.;
    track_Vz[i]                 = -99999.;
    track_Pt[i]                 = -99999.;
    track_Eta[i]                = -99999.;
    track_Phi[i]                = -99999.;

    genjet_px[i]             = -99999.;
    genjet_py[i]             = -99999.;
    genjet_pz[i]             = -99999.;
    genjet_E[i]              = -99999.;
    genjet_Pt[i]             = -99999.;
    genjet_Eta[i]            = -99999.;
    genjet_Phi[i]            = -99999.;
    genjet_Y[i]              = -99999.;
    genjet_area[i]           = -99999.;

    genPart_Charge[i]           = -99999;
    genPart_px[i]               = -99999.;
    genPart_py[i]               = -99999.;
    genPart_pz[i]               = -99999.;
    genPart_E[i]                = -99999.;
    genPart_Pt[i]               = -99999.;
    genPart_Eta[i]              = -99999.;
    genPart_Phi[i]              = -99999.;
    genPart_Vx[i]               = -99999.;
    genPart_Vy[i]               = -99999.;
    genPart_Vz[i]               = -99999.;
    genPart_Y[i]                = -99999.;	  
    genPart_Status[i]           = -99999;
    genPart_pdgId[i]            = -99999;
  }
  // initialization done



  // write event information: run, event, bunch crossing, ....
  run   = iEvent.id().run();
  event = iEvent.id().event();
  lumi  = iEvent.luminosityBlock();
  bunch = iEvent.bunchCrossing();



  // primary/secondary vertices
  // edm::Handle<reco::VertexCollection > recVtxs;
  edm::Handle <edm::View<reco::Vertex> > recVtxs;
  iEvent.getByLabel( "goodOfflinePrimaryVertices", recVtxs);
  nPV = recVtxs->size();




  /////// --- Pileup density "rho" in the event from fastJet pileup calculation --------
  edm::Handle<double> rho;
  const edm::InputTag eventrho("kt6PFJetsPFlow", "rho");
  iEvent.getByLabel(eventrho,rho);
  fastJetRho = *rho;



  //------------------ Met filling ------------------
  edm::Handle<edm::View<reco::MET> > pfmet;
  iEvent.getByLabel("patType1CorrectedPFMet", pfmet);
  if (pfmet->size() > 0) {
    Met_Phi             = (*pfmet)[0].phi();
    Met_px              = (*pfmet)[0].px();
    Met_py              = (*pfmet)[0].py();
    Met_Et              = (*pfmet)[0].et();
    Met_SumET           = (*pfmet)[0].sumEt(); 
  }




  //------------------ Muon filling ------------------
  typedef edm::View<reco::Muon> MuonView;
  edm::Handle<MuonView> muons;
  iEvent.getByLabel( "selectedPatMuonsPFlow", muons);
  l1size  = (int) (muons->size()); 
  if( l1size > 0 ) {
    int iMuon = 0;
    edm::View<reco::Muon>::const_iterator muon, endpmuons = muons->end(); 
    for (muon = muons->begin();  muon != endpmuons;  ++muon, ++iMuon) {

      l1Charge[iMuon]           = (*muon).charge();
      l1px[iMuon]               = (*muon).px();
      l1py[iMuon]               = (*muon).py();
      l1pz[iMuon]               = (*muon).pz();
      l1E[iMuon]                = (*muon).energy();
      l1Pt[iMuon]               = (*muon).pt();
      l1Eta[iMuon]              = (*muon).eta();
      l1Phi[iMuon]              = (*muon).phi();
      l1Vx[iMuon]               = (*muon).vx();
      l1Vy[iMuon]               = (*muon).vy();
      l1Vz[iMuon]               = (*muon).vz();
      l1Y[iMuon]                = (*muon).rapidity();    
      /// detector isolation 
      l1trackiso[iMuon]       = (*muon).isolationR03().sumPt;
      l1ecaliso[iMuon]        = (*muon).isolationR03().emEt;
      l1hcaliso[iMuon]        = (*muon).isolationR03().hadEt;
      /// ID
      l1Type[iMuon]  = (*muon).type();
      l1_numberOfChambers[iMuon]  = (*muon).numberOfChambers();      
      l1_numberOfMatches[iMuon]   = (*muon).numberOfMatches();
      /// PF isolation 
      l1pfiso_sumChargedHadronPt[iMuon]   = (*muon).pfIsolationR04().sumChargedHadronPt;
      l1pfiso_sumChargedParticlePt[iMuon] = (*muon).pfIsolationR04().sumChargedParticlePt;
      l1pfiso_sumNeutralHadronEt[iMuon]   = (*muon).pfIsolationR04().sumNeutralHadronEt;
      l1pfiso_sumPhotonEt[iMuon]          = (*muon).pfIsolationR04().sumPhotonEt;
      l1pfiso_sumPUPt[iMuon]              = (*muon).pfIsolationR04().sumPUPt;
      // vertex 
      const pat::Muon* patmuon1 = dynamic_cast<const pat::Muon *>( &*muon);
      l1_d0bsp[iMuon] = patmuon1->dB(pat::Muon::BS2D) ;
      l1_dz000[iMuon] = patmuon1->dB(pat::Muon::PV2D);
      l1_IP3D[iMuon] = patmuon1->dB(pat::Muon::PV3D);
      if(fabs(l1_IP3D[iMuon])>fabs(l1_dz000[iMuon])&&l1_IP3D[iMuon]<1000) 
	l1_dzPV[iMuon] = sqrt(l1_IP3D[iMuon]*l1_IP3D[iMuon]-l1_dz000[iMuon]*l1_dz000[iMuon]);
    }
  }


  //------------------ Electron filling ------------------
  typedef edm::View<reco::GsfElectron> ElectronView;
  edm::Handle<ElectronView> electrons;
  iEvent.getByLabel( "selectedPatElectronsPFlow", electrons);
  l2size  = (int) (electrons->size()); 
  if( l2size > 0 ) {
    int iElectron = 0;
    edm::View<reco::GsfElectron>::const_iterator electron, endpelectrons = electrons->end(); 
    for (electron = electrons->begin();  electron != endpelectrons;  ++electron, ++iElectron) {

      l2Charge[iElectron]           = (*electron).charge();
      l2px[iElectron]               = (*electron).px();
      l2py[iElectron]               = (*electron).py();
      l2pz[iElectron]               = (*electron).pz();
      l2E[iElectron]                = (*electron).energy();
      l2Pt[iElectron]               = (*electron).pt();
      l2Eta[iElectron]              = (*electron).eta();
      l2Phi[iElectron]              = (*electron).phi();
      l2Vx[iElectron]               = (*electron).vx();
      l2Vy[iElectron]               = (*electron).vy();
      l2Vz[iElectron]               = (*electron).vz();
      l2Y[iElectron]                = (*electron).rapidity();    
      /// detector isolation 
      l2trackiso[iElectron]       = (*electron).dr03TkSumPt();
      l2ecaliso[iElectron]        = (*electron).dr03EcalRecHitSumEt();
      l2hcaliso[iElectron]        = (*electron).dr03HcalTowerSumEt();
      /// ID
      l2_classification[iElectron]  = (*electron).classification();
      l2_HoverE[iElectron] = (*electron).hadronicOverEm();	 
      l2_EoverP[iElectron]       = (*electron).eSuperClusterOverP();
      l2_DeltaEta[iElectron]     = (*electron).deltaEtaSuperClusterTrackAtVtx();
      l2_DeltaPhi[iElectron]     = (*electron).deltaPhiSuperClusterTrackAtVtx();
      l2_numberOfBrems[iElectron]  = (*electron).numberOfBrems();      
      l2_BremFraction[iElectron]   = (*electron).fbrem();
      l2_SigmaIetaIeta[iElectron] = (*electron).sigmaIetaIeta();
      l2_missingHits[iElectron]   = (*electron).gsfTrack()->trackerExpectedHitsInner().numberOfHits();
      l2_dist[iElectron]          = (*electron).convDist();
      l2_dcot[iElectron]          = (*electron).convDcot();
      l2_convradius[iElectron]    = (*electron).convRadius();
      /// PF isolation 
      l2pfiso_chargedHadronIso[iElectron]   = (*electron).pfIsolationVariables().chargedHadronIso;
      l2pfiso_photonIso[iElectron] = (*electron).pfIsolationVariables().photonIso;
      l2pfiso_neutralHadronIso[iElectron]   = (*electron).pfIsolationVariables().neutralHadronIso;
      l2pfiso_EffAreaPU[iElectron] = ElectronEffectiveArea::GetElectronEffectiveArea( ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03 ,  (*electron).superCluster()->eta(), ElectronEffectiveArea::kEleEAData2011);
      l2pfiso_pfIsoEA[iElectron] = (l2pfiso_chargedHadronIso[iElectron] +
				    max((float)(0.), l2pfiso_neutralHadronIso[iElectron]+
					l2pfiso_photonIso[iElectron] -
					l2pfiso_EffAreaPU[iElectron]*fastJetRho)) / l2Pt[iElectron];
      // vertex 
      const pat::Electron* patelectron1 = dynamic_cast<const pat::Electron *>( &*electron);
      l2_d0bsp[iElectron] = patelectron1->dB(pat::Electron::BS2D) ;
      l2_dz000[iElectron] = patelectron1->dB(pat::Electron::PV2D);
      l2_IP3D[iElectron] = patelectron1->dB(pat::Electron::PV3D);
      if(fabs(l2_IP3D[iElectron])>fabs(l2_dz000[iElectron])&&l2_IP3D[iElectron]<1000) 
	l2_dzPV[iElectron] = sqrt(l2_IP3D[iElectron]*l2_IP3D[iElectron]-l2_dz000[iElectron]*l2_dz000[iElectron]);
    }
  }



  //--------------- jet filling ----------------------------
  edm::Handle<edm::View<reco::Jet> > jets;
  iEvent.getByLabel( mInputJets, jets ); 
  jet_size = (int) (jets->size());
  if( jet_size > 0) {
    int iJet = 0;
    edm::View<reco::Jet>::const_iterator jet, endpjets = jets->end(); 
    for (jet = jets->begin();  jet != endpjets;  ++jet, ++iJet) {

      jet_Y[iJet]               = (*jet).rapidity();
      jet_Eta[iJet]             = (*jet).eta();
      jet_Phi[iJet]             = (*jet).phi();
      jet_E[iJet]               = (*jet).energy();
      jet_px[iJet]              = (*jet).px();
      jet_py[iJet]              = (*jet).py();
      jet_pz[iJet]              = (*jet).pz();
      jet_Pt[iJet]              = (*jet).pt();
      jet_area[iJet]            = (*jet).jetArea();

      edm::Ptr<reco::Jet> ptrJet = jets->ptrAt( jet - jets->begin() );		  
      if ( ptrJet.isNonnull() && ptrJet.isAvailable() ) {
	const pat::Jet* pjet = dynamic_cast<const pat::Jet *>(ptrJet.get()) ;
	jet_bDiscriminatorSSVHE[iJet] = (*pjet).bDiscriminator("simpleSecondaryVertexHighEffBJetTags");
	jet_bDiscriminatorTCHE[iJet] = (*pjet).bDiscriminator("trackCountingHighEffBJetTags");
	jet_bDiscriminatorCSV[iJet] = (*pjet).bDiscriminator("combinedSecondaryVertexBJetTags");
	jet_bDiscriminatorJP[iJet] = (*pjet).bDiscriminator("jetProbabilityBJetTags");
	jet_bDiscriminatorSSVHP[iJet] = (*pjet).bDiscriminator("simpleSecondaryVertexHighPurBJetTags");
	jet_bDiscriminatorTCHP[iJet] = (*pjet).bDiscriminator("trackCountingHighPurBJetTags");
      }
    }
  }


  //--------------- photon filling ----------------------------
  edm::Handle<reco::PhotonCollection> photons;
  iEvent.getByLabel("photons",photons);
  edm::Handle<reco::BeamSpot> bsHandle;
  iEvent.getByLabel("offlineBeamSpot", bsHandle);
  const reco::BeamSpot &beamspot = *bsHandle.product();

  edm::Handle<reco::ConversionCollection> hConversions;
  iEvent.getByLabel("allConversions", hConversions);

  edm::Handle<reco::GsfElectronCollection> hElectrons;
  iEvent.getByLabel("gsfElectrons", hElectrons);

//   IsoDepositVals photonIsoValPFId(3);
//   iEvent.getByLabel("phoPFIso:chIsoForGsfEle", photonIsoValPFId[0]);
//   iEvent.getByLabel("phoPFIso:phIsoForGsfEle", photonIsoValPFId[1]);
//   iEvent.getByLabel("phoPFIso:nhIsoForGsfEle", photonIsoValPFId[2]);

//   const IsoDepositVals * photonIsoVals = &photonIsoValPFId;

  photon_size = (int) (photons->size());
  if( photon_size > 0) {
    int iPhoton = 0;
    for(unsigned ipho=0; ipho < photons->size(); ++ipho) {
      reco::PhotonRef myPhotonRef(photons,ipho);
      photon_px[iPhoton]  = myPhotonRef->px();
      photon_py[iPhoton]  = myPhotonRef->py();
      photon_pz[iPhoton]  = myPhotonRef->pz();
      photon_E[iPhoton]   = myPhotonRef->energy();
      photon_pt[iPhoton]  = myPhotonRef->et();
      photon_eta[iPhoton] = myPhotonRef->eta();
      photon_phi[iPhoton] = myPhotonRef->phi();
      photon_vx[iPhoton]  = myPhotonRef->vx();
      photon_vy[iPhoton]  = myPhotonRef->vy();
      photon_vz[iPhoton]  = myPhotonRef->vz();

//       photon_pfiso_charged[iPhoton]  = max((*(*photonIsoVals)[0])[myPhotonRef] - fastJetRho*EAch(fabs(myPhotonRef->eta())),0.);
//       photon_pfiso_photon[iPhoton]  = max((*(*photonIsoVals)[1])[myPhotonRef] - fastJetRho*EAnh(fabs(myPhotonRef->eta())),0.);
//       photon_pfiso_neutral[iPhoton]  = max((*(*photonIsoVals)[2])[myPhotonRef] - fastJetRho*EApho(fabs(myPhotonRef->eta())),0.);

      photon_trackiso[iPhoton]  = myPhotonRef->trkSumPtHollowConeDR04();
      photon_ecaliso[iPhoton]   = myPhotonRef->ecalRecHitSumEtConeDR04();
      photon_hcaliso[iPhoton]   = myPhotonRef->hcalTowerSumEtConeDR04();
      photon_HoverE[iPhoton]    = myPhotonRef->hadTowOverEm();
      photon_SigmaIetaIeta[iPhoton]  = myPhotonRef->sigmaIetaIeta();

      if(myPhotonRef->hasPixelSeed()) photon_hasPixelSeed[iPhoton] = 1;
      else photon_hasPixelSeed[iPhoton]   = 0;

      bool passConv = !(ConversionTools::hasMatchedPromptElectron(myPhotonRef->superCluster(), hElectrons, hConversions, beamspot.position()));
      if(passConv) photon_passElecVeto[iPhoton]   = 1;
      else photon_passElecVeto[iPhoton]   = 0;
    }
  }


  //  ************* Load Tracks **********************
  /*
  edm::Handle<reco::TrackCollection> tracks;
  iEvent.getByLabel("generalTracks", tracks);
  track_size = (int) (tracks->size());  
  reco::TrackCollection::const_iterator trk;
  if(track_size > 0) {
    int iTracks = 0;
    for ( trk = tracks->begin(); trk != tracks->end(); ++trk){
      track_px[iTracks] = trk->px();
      track_py[iTracks] = trk->py();
      track_pz[iTracks] = trk->pz();
      track_Vx[iTracks] = trk->px();
      track_Vy[iTracks] = trk->py();
      track_Vz[iTracks] = trk->pz();
      track_Pt[iTracks] = trk->pt();
      track_Eta[iTracks] = trk->eta();
      track_Phi[iTracks] = trk->phi();
      iTracks++;
    }
  }
  */
  // ---------------------------------------------





  // --- genParticles loop -------------------
  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel("genParticles", genParticles);
  //  const reco::Candidate *genPart=NULL;
  const reco::GenParticle* genPart=NULL;

  genPart_size = (int) (genParticles->size());  
  if(genPart_size > 0) {
    for(size_t i = 0; i < genParticles->size(); ++ i) {

      genPart = &((*genParticles)[i]);
      genPart_Charge[i]           = genPart->charge();
      genPart_Vx[i]               = genPart->vx();
      genPart_Vy[i]               = genPart->vy();
      genPart_Vz[i]               = genPart->vz();
      genPart_Y[i]                = genPart->rapidity();
      genPart_Eta[i]              = genPart->eta();    
      genPart_Phi[i]              = genPart->phi();
      genPart_E[i]                = genPart->energy();
      genPart_px[i]               = genPart->px();
      genPart_py[i]               = genPart->py();
      genPart_pz[i]               = genPart->pz();
      genPart_Pt[i]               = genPart->pt();
      genPart_Status[i]           = genPart->status();
      genPart_pdgId[i]            = genPart->pdgId();
    }// end genParticles loop
  }


  //--------------- genjet filling ----------------------------
  edm::Handle<edm::View<reco::Jet> > genjets;
  iEvent.getByLabel( "ak5GenJets", genjets ); 
  genjet_size = (int) (genjets->size());
  if( genjet_size > 0) {
    int iGenJet = 0;
    edm::View<reco::Jet>::const_iterator genjet, endpgenjets = genjets->end(); 
    for (genjet = genjets->begin();  genjet != endpgenjets;  ++genjet, ++iGenJet) {

      genjet_Y[iGenJet]               = (*genjet).rapidity();
      genjet_Eta[iGenJet]             = (*genjet).eta();
      genjet_Phi[iGenJet]             = (*genjet).phi();
      genjet_E[iGenJet]               = (*genjet).energy();
      genjet_px[iGenJet]              = (*genjet).px();
      genjet_py[iGenJet]              = (*genjet).py();
      genjet_pz[iGenJet]              = (*genjet).pz();
      genjet_Pt[iGenJet]              = (*genjet).pt();
      genjet_area[iGenJet]            = (*genjet).jetArea();
    }
  }






  tree_->Fill();
}


void ewk::SnowmassTreeProducer::endJob()
{
//   hOutputFile->SetCompressionLevel(2);
//   hOutputFile->cd();
//   tree_->Write();

//   delete tree_;
//   hOutputFile->Close();
//   delete hOutputFile;
}





////////////////// utilities, helpers ///////////////////
 
void ewk::SnowmassTreeProducer::SetBranch( float* x, std::string brName)
{
  tree_->Branch( brName.c_str(), x, ( brName+"/F").c_str() );
}


void ewk::SnowmassTreeProducer::SetBranch( int* x, std::string brName)
{
  tree_->Branch( brName.c_str(), x, ( brName+"/I").c_str() );
}


void ewk::SnowmassTreeProducer::SetBranch( bool* x, std::string brName)
{
  tree_->Branch( brName.c_str(), x, ( brName+"/O").c_str() );
}



//////////////////////////////////////////////////////////////////
/////// Helper for Effective Areas ///////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
float ewk::SnowmassTreeProducer::EAch( float x){
 float EA = 0.012;
 if(x>1.0)   EA = 0.010;
 if(x>1.479) EA = 0.014;
 if(x>2.0)   EA = 0.012;
 if(x>2.2)   EA = 0.016;
 if(x>2.3)   EA = 0.020;
 if(x>2.4)   EA = 0.012;
 return EA;
}

float ewk::SnowmassTreeProducer::EAnh( float x){
 float EA = 0.030;
 if(x>1.0)   EA = 0.057;
 if(x>1.479) EA = 0.039;
 if(x>2.0)   EA = 0.015;
 if(x>2.2)   EA = 0.024;
 if(x>2.3)   EA = 0.039;
 if(x>2.4)   EA = 0.072;
 return EA;
}

float ewk::SnowmassTreeProducer::EApho( float x){
 float EA = 0.148;
 if(x>1.0)   EA = 0.130;
 if(x>1.479) EA = 0.112;
 if(x>2.0)   EA = 0.216;
 if(x>2.2)   EA = 0.262;
 if(x>2.3)   EA = 0.260;
 if(x>2.4)   EA = 0.266;
 return EA;
}


// declare this class as a plugin
#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
using ewk::SnowmassTreeProducer;
DEFINE_FWK_MODULE(SnowmassTreeProducer);
