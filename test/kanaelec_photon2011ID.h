//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Sep 15 15:27:33 2011 by ROOT version 5.27/06b
// from TTree WJet/V+jets Tree
// found on file: /uscms_data/d2/yangf/ana/WuvWjj/DataFile/MergFile/WenuJets_DataAll_GoldenJSON_2p1invfb.root
//////////////////////////////////////////////////////////

#ifndef kanaelec_photon_h
#define kanaelec_photon_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>

#include "TLorentzVector.h"

class kanaelec_photon {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           numPFCorJets;
   Int_t           numPFCorJetBTags;
   Float_t         JetPFCor_Et[6];
   Float_t         JetPFCor_Pt[6];
   Float_t         JetPFCor_Eta[6];
   Float_t         JetPFCor_Phi[6];
   Float_t         JetPFCor_Theta[6];
   Float_t         JetPFCor_Px[6];
   Float_t         JetPFCor_Py[6];
   Float_t         JetPFCor_Pz[6];
   Float_t         JetPFCor_E[6];
   Float_t         JetPFCor_Y[6];
   Float_t         JetPFCor_Mass[6];
   Float_t         JetPFCor_etaetaMoment[6];
   Float_t         JetPFCor_phiphiMoment[6];
   Float_t         JetPFCor_etaphiMoment[6];
   Float_t         JetPFCor_maxDistance[6];
   Int_t           JetPFCor_nConstituents[6];
   Float_t         JetPFCor_Area[6];
   Float_t         VplusPFCorJet_Mass[6];
   Float_t         JetPFCor_dphiBoson[6];
   Float_t         JetPFCor_detaBoson[6];
   Float_t         JetPFCor_dRBoson[6];
   Float_t         JetPFCor_dphiMET[6];
   Float_t         JetPFCor_bDiscriminator[6];
   Float_t         JetPFCor_bDiscriminatorSSVHE[6];
   Float_t         JetPFCor_bDiscriminatorTCHE[6];
   Float_t         JetPFCor_bDiscriminatorCSV[6];
   Float_t         JetPFCor_bDiscriminatorJP[6];
   Float_t         JetPFCor_bDiscriminatorSSVHP[6];
   Float_t         JetPFCor_bDiscriminatorTCHP[6];
   Float_t         JetPFCor_secVertexMass[6];
   Float_t         JetPFCor_ChargedHadronEnergy[6];
   Float_t         JetPFCor_ChargedHadronEnergyFrac[6];
   Float_t         JetPFCor_NeutralHadronEnergy[6];
   Float_t         JetPFCor_NeutralHadronEnergyFrac[6];
   Float_t         JetPFCor_ChargedEmEnergy[6];
   Float_t         JetPFCor_ChargedEmEnergyFrac[6];
   Float_t         JetPFCor_ChargedMuEnergy[6];
   Float_t         JetPFCor_ChargedMuEnergyFrac[6];
   Float_t         JetPFCor_NeutralEmEnergy[6];
   Float_t         JetPFCor_NeutralEmEnergyFrac[6];
   Int_t           JetPFCor_ChargedMultiplicity[6];
   Int_t           JetPFCor_NeutralMultiplicity[6];
   Int_t           JetPFCor_MuonMultiplicity[6];
   Float_t         JetPFCor_PhotonEnergy[6];
   Float_t         JetPFCor_PhotonEnergyFraction[6];
   Float_t         JetPFCor_ElectronEnergy[6];
   Float_t         JetPFCor_ElectronEnergyFraction[6];
   Float_t         JetPFCor_MuonEnergy[6];
   Float_t         JetPFCor_MuonEnergyFraction[6];
   Float_t         JetPFCor_HFHadronEnergy[6];
   Float_t         JetPFCor_HFHadronEnergyFraction[6];
   Float_t         JetPFCor_HFEMEnergy[6];
   Float_t         JetPFCor_HFEMEnergyFraction[6];
   Int_t           JetPFCor_ChargedHadronMultiplicity[6];
   Int_t           JetPFCor_NeutralHadronMultiplicity[6];
   Int_t           JetPFCor_PhotonMultiplicity[6];
   Int_t           JetPFCor_ElectronMultiplicity[6];
   Int_t           JetPFCor_HFHadronMultiplicity[6];
   Int_t           JetPFCor_HFEMMultiplicity[6];
   Float_t         JetPFCor_SumPtCands[6];
   Float_t         JetPFCor_SumPt2Cands[6];
   Float_t         JetPFCor_rmsCands[6];
   Float_t         JetPFCor_PtD[6];
   Float_t         JetPFCor_QGLikelihood[6];
   Float_t         MassV2j_PFCor_MVAMET;
   Float_t         MassV2j_PFCor;
   Float_t         MassV3j_PFCor;
   Float_t         MassV4j_PFCor;
   Float_t         MassV5j_PFCor;
   Float_t         MassV6j_PFCor;
   Float_t         Mass2j_PFCor;
   Float_t         Mass3j_PFCor;
   Float_t         Mass4j_PFCor;
   Float_t         Mass5j_PFCor;
   Float_t         Mass6j_PFCor;
   Float_t         cosJacksonAngleV2j_PFCor;
   Float_t         cosJacksonAngle2j_PFCor;
   Float_t         cosJacksonAngleV3j_PFCor;
   Float_t         cosJacksonAngle3j12_PFCor;
   Float_t         cosJacksonAngle3j23_PFCor;
   Float_t         cosJacksonAngle3j31_PFCor;
   Float_t         cosphiDecayPlane_PFCor;
   Float_t         cosThetaLnu_PFCor;
   Float_t         cosThetaJJ_PFCor;
   Float_t         cosThetaJ1HiggsCM_PFCor;
   Float_t         cosThetaJ2HiggsCM_PFCor;
   Float_t         cosThetaL1HiggsCM_PFCor;
   Float_t         cosThetaL2HiggsCM_PFCor;
   Float_t         cosThetaV1HiggsCM_PFCor;
   Float_t         cosThetaV2HiggsCM_PFCor;
   Int_t           numGenJets;
   Int_t           numGenJetBTags;
   Float_t         JetGen_Et[6];
   Float_t         JetGen_Pt[6];
   Float_t         JetGen_Eta[6];
   Float_t         JetGen_Phi[6];
   Float_t         JetGen_Theta[6];
   Float_t         JetGen_Px[6];
   Float_t         JetGen_Py[6];
   Float_t         JetGen_Pz[6];
   Float_t         JetGen_E[6];
   Float_t         JetGen_Y[6];
   Float_t         JetGen_Mass[6];
   Float_t         JetGen_etaetaMoment[6];
   Float_t         JetGen_phiphiMoment[6];
   Float_t         JetGen_etaphiMoment[6];
   Float_t         JetGen_maxDistance[6];
   Int_t           JetGen_nConstituents[6];
   Float_t         JetGen_Area[6];
   Float_t         VplusGenJet_Mass[6];
   Float_t         JetGen_dphiBoson[6];
   Float_t         JetGen_detaBoson[6];
   Float_t         JetGen_dRBoson[6];
   Float_t         JetGen_dphiMET[6];
   Float_t         JetGen_bDiscriminator[6];
   Float_t         JetGen_bDiscriminatorSSVHE[6];
   Float_t         JetGen_bDiscriminatorTCHE[6];
   Float_t         JetGen_bDiscriminatorCSV[6];
   Float_t         JetGen_bDiscriminatorJP[6];
   Float_t         JetGen_bDiscriminatorSSVHP[6];
   Float_t         JetGen_bDiscriminatorTCHP[6];
   Float_t         JetGen_secVertexMass[6];
   Float_t         MassV2j_Gen_MVAMET;
   Float_t         MassV2j_Gen;
   Float_t         MassV3j_Gen;
   Float_t         MassV4j_Gen;
   Float_t         MassV5j_Gen;
   Float_t         MassV6j_Gen;
   Float_t         Mass2j_Gen;
   Float_t         Mass3j_Gen;
   Float_t         Mass4j_Gen;
   Float_t         Mass5j_Gen;
   Float_t         Mass6j_Gen;
   Float_t         cosJacksonAngleV2j_Gen;
   Float_t         cosJacksonAngle2j_Gen;
   Float_t         cosJacksonAngleV3j_Gen;
   Float_t         cosJacksonAngle3j12_Gen;
   Float_t         cosJacksonAngle3j23_Gen;
   Float_t         cosJacksonAngle3j31_Gen;
   Float_t         cosphiDecayPlane_Gen;
   Float_t         cosThetaLnu_Gen;
   Float_t         cosThetaJJ_Gen;
   Int_t           NumPhotons;
   Float_t         Photon_Et[6];   //[NumPhotons]
   Float_t         Photon_E[6];   //[NumPhotons]
   Float_t         Photon_Eta[6];   //[NumPhotons]
   Float_t         Photon_Phi[6];   //[NumPhotons]
   Float_t         Photon_Theta[6];   //[NumPhotons]
   Float_t         Photon_Px[6];   //[NumPhotons]
   Float_t         Photon_Py[6];   //[NumPhotons]
   Float_t         Photon_Pz[6];   //[NumPhotons]
   Float_t         Photon_Vx[6];   //[NumPhotons]
   Float_t         Photon_Vy[6];   //[NumPhotons]
   Float_t         Photon_Vz[6];   //[NumPhotons]
   Float_t         Photon_SC_Et[6];   //[NumPhotons]
   Float_t         Photon_SC_E[6];   //[NumPhotons]
   Float_t         Photon_SC_Eta[6];   //[NumPhotons]
   Float_t         Photon_SC_Phi[6];   //[NumPhotons]
   Float_t         Photon_SC_Theta[6];   //[NumPhotons]
   Float_t         Photon_SC_x[6];   //[NumPhotons]
   Float_t         Photon_SC_y[6];   //[NumPhotons]
   Float_t         Photon_SC_z[6];   //[NumPhotons]
   Float_t         PFisocharged03[6];   //[NumPhotons]
   Float_t         PFisophoton03[6];   //[NumPhotons]
   Float_t         PFisoneutral03[6];   //[NumPhotons]
//   Float_t         trkSumPtHollowConeDR04_Photon11[8]; //[NumPhotons]
//   Float_t         ecalRecHitSumEtConeDR04_Photon11[8]; //[NumPhotons]
//   Float_t         hcalTowerSumEtConeDR04_Photon11[8]; //[NumPhotons]
   Float_t         Photon_HoverE[6];   //[NumPhotons]
   Float_t         Photon_HoverE2011[6];   //[NumPhotons]
   Float_t         Photon_SigmaIetaIeta[6];   //[NumPhotons]
   Int_t           Photon_hasPixelSeed[6];   //[NumPhotons]
   Int_t           Photon_passElecVeto[6];   //[NumPhotons]
   Int_t           Photon_Id2011[6];   //[NumPhotons]
   Int_t           Photon_Id2012[6];   //[NumPhotons]
   Float_t         W_mass;
   Float_t         W_mt;
   Float_t         W_mtMVA;
   Float_t         W_px;
   Float_t         W_py;
   Float_t         W_pz;
   Float_t         W_e;
   Float_t         W_pt;
   Float_t         W_et;
   Float_t         W_eta;
   Float_t         W_phi;
   Float_t         W_vx;
   Float_t         W_vy;
   Float_t         W_vz;
   Float_t         W_y;
   Int_t           W_numTightElectrons;
   Int_t           W_numLooseElectrons;
   Float_t         W_pzNu1;
   Float_t         W_pzNu2;
   Float_t         W_electron_px;
   Float_t         W_electron_py;
   Float_t         W_electron_pz;
   Float_t         W_electron_e;
   Float_t         W_electron_pt;
   Float_t         W_electron_et;
   Float_t         W_electron_eta;
   Float_t         W_electron_theta;
   Float_t         W_electron_phi;
   Int_t           W_electron_charge;
   Float_t         W_electron_vx;
   Float_t         W_electron_vy;
   Float_t         W_electron_vz;
   Float_t         W_electron_y;
   Float_t         W_electron_trackiso;
   Float_t         W_electron_hcaliso;
   Float_t         W_electron_ecaliso;
   Int_t           W_electron_classification;
   Int_t           W_electron_missingHits;
   Float_t         W_electron_dist;
   Float_t         W_electron_dcot;
   Float_t         W_electron_d0bsp;
   Float_t         W_electron_dz000;
   Float_t         W_electron_mvaTrigV0;
   Float_t         W_electron_mvaNonTrigV0;
   Float_t         W_electron_pfiso_chargedHadronIso;
   Float_t         W_electron_pfiso_photonIso;
   Float_t         W_electron_pfiso_neutralHadronIso;
   Float_t         W_electron_pfIsoEA;
   Float_t         W_H_mass_gen;
   Float_t         W_H_px_gen;
   Float_t         W_H_py_gen;
   Float_t         W_H_pz_gen;
   Float_t         W_H_e_gen;
   Float_t         W_H_pt_gen;
   Float_t         W_H_et_gen;
   Float_t         W_H_eta_gen;
   Float_t         W_H_phi_gen;
   Float_t         W_H_vx_gen;
   Float_t         W_H_vy_gen;
   Float_t         W_H_vz_gen;
   Float_t         W_H_y_gen;
   Int_t           W_H_Id_gen;
   Float_t         W_electron_px_gen;
   Float_t         W_electron_py_gen;
   Float_t         W_electron_pz_gen;
   Float_t         W_electron_e_gen;
   Float_t         W_electron_pt_gen;
   Float_t         W_electron_et_gen;
   Float_t         W_electron_eta_gen;
   Float_t         W_electron_theta_gen;
   Float_t         W_electron_phi_gen;
   Int_t           W_electron_charge_gen;
   Float_t         W_electron_vx_gen;
   Float_t         W_electron_vy_gen;
   Float_t         W_electron_vz_gen;
   Float_t         W_electron_y_gen;
   Float_t         W_neutrino_px_gen;
   Float_t         W_neutrino_py_gen;
   Float_t         W_neutrino_pz_gen;
   Float_t         W_neutrino_e_gen;
   Float_t         W_neutrino_pt_gen;
   Float_t         W_neutrino_et_gen;
   Float_t         W_neutrino_eta_gen;
   Float_t         W_neutrino_theta_gen;
   Float_t         W_neutrino_phi_gen;
   Int_t           W_neutrino_charge_gen;
   Float_t         W_neutrino_vx_gen;
   Float_t         W_neutrino_vy_gen;
   Float_t         W_neutrino_vz_gen;
   Float_t         W_neutrino_y_gen;
   Float_t         W_Parton_px[2];
   Float_t         W_Parton_py[2];
   Float_t         W_Parton_pz[2];
   Float_t         W_Parton_E[2];
   Float_t         W_Parton_pt[2];
   Float_t         W_Parton_et[2];
   Float_t         W_Parton_eta[2];
   Float_t         W_Parton_theta[2];
   Float_t         W_Parton_phi[2];
   Int_t           W_Parton_charge[2];
   Float_t         W_Parton_vx[2];
   Float_t         W_Parton_vy[2];
   Float_t         W_Parton_vz[2];
   Float_t         W_Parton_y[2];
   Int_t           W_Parton_Id[2];
   Float_t         W_Lepton_px;
   Float_t         W_Lepton_py;
   Float_t         W_Lepton_pz;
   Float_t         W_Lepton_E;
   Float_t         W_Lepton_pt;
   Float_t         W_Lepton_et;
   Float_t         W_Lepton_eta;
   Float_t         W_Lepton_theta;
   Float_t         W_Lepton_phi;
   Int_t           W_Lepton_charge;
   Float_t         W_Lepton_vx;
   Float_t         W_Lepton_vy;
   Float_t         W_Lepton_vz;
   Float_t         W_Lepton_y;
   Int_t           W_Lepton_Id;
   Float_t         W_Met_px;
   Float_t         W_Met_py;
   Float_t         W_Met_pz;
   Float_t         W_Met_E;
   Float_t         W_Met_pt;
   Float_t         W_Met_et;
   Float_t         W_Met_eta;
   Float_t         W_Met_theta;
   Float_t         W_Met_phi;
   Int_t           W_Met_charge;
   Float_t         W_Met_vx;
   Float_t         W_Met_vy;
   Float_t         W_Met_vz;
   Float_t         W_Met_y;
   Int_t           W_Met_Id;
   Int_t           event_runNo;
   Int_t           event_evtNo;
   Int_t           event_lumi;
   Int_t           event_bunch;
   Int_t           event_nPV;
   Float_t         event_met_pfmet;
   Float_t         event_met_pfsumet;
   Float_t         event_met_pfmetsignificance;
   Float_t         event_met_pfmetPhi;
   Float_t         event_metMVA_met;
   Float_t         event_metMVA_sumet;
   Float_t         event_metMVA_metsignificance;
   Float_t         event_metMVA_metPhi;
   Float_t         event_fastJetRho;
   Float_t         event_met_genmet;
   Float_t         event_met_gensumet;
   Float_t         event_met_genmetsignificance;
   Float_t         event_met_genmetPhi;
   Float_t         event_mcPU_totnvtx;
   Float_t         event_mcPU_trueInteractions;
   Float_t         event_mcPU_bx[3];
   Float_t         event_mcPU_nvtx[3];

   // List of branches
   TBranch        *b_numPFCorJets;   //!
   TBranch        *b_numPFCorJetBTags;   //!
   TBranch        *b_JetPFCor_Et;   //!
   TBranch        *b_JetPFCor_Pt;   //!
   TBranch        *b_JetPFCor_Eta;   //!
   TBranch        *b_JetPFCor_Phi;   //!
   TBranch        *b_JetPFCor_Theta;   //!
   TBranch        *b_JetPFCor_Px;   //!
   TBranch        *b_JetPFCor_Py;   //!
   TBranch        *b_JetPFCor_Pz;   //!
   TBranch        *b_JetPFCor_E;   //!
   TBranch        *b_JetPFCor_Y;   //!
   TBranch        *b_JetPFCor_Mass;   //!
   TBranch        *b_JetPFCor_etaetaMoment;   //!
   TBranch        *b_JetPFCor_phiphiMoment;   //!
   TBranch        *b_JetPFCor_etaphiMoment;   //!
   TBranch        *b_JetPFCor_maxDistance;   //!
   TBranch        *b_JetPFCor_nConstituents;   //!
   TBranch        *b_JetPFCor_Area;   //!
   TBranch        *b_VplusPFCorJet_Mass;   //!
   TBranch        *b_JetPFCor_dphiBoson;   //!
   TBranch        *b_JetPFCor_detaBoson;   //!
   TBranch        *b_JetPFCor_dRBoson;   //!
   TBranch        *b_JetPFCor_dphiMET;   //!
   TBranch        *b_JetPFCor_bDiscriminator;   //!
   TBranch        *b_JetPFCor_bDiscriminatorSSVHE;   //!
   TBranch        *b_JetPFCor_bDiscriminatorTCHE;   //!
   TBranch        *b_JetPFCor_bDiscriminatorCSV;   //!
   TBranch        *b_JetPFCor_bDiscriminatorJP;   //!
   TBranch        *b_JetPFCor_bDiscriminatorSSVHP;   //!
   TBranch        *b_JetPFCor_bDiscriminatorTCHP;   //!
   TBranch        *b_JetPFCor_secVertexMass;   //!
   TBranch        *b_JetPFCor_ChargedHadronEnergy;   //!
   TBranch        *b_JetPFCor_ChargedHadronEnergyFrac;   //!
   TBranch        *b_JetPFCor_NeutralHadronEnergy;   //!
   TBranch        *b_JetPFCor_NeutralHadronEnergyFrac;   //!
   TBranch        *b_JetPFCor_ChargedEmEnergy;   //!
   TBranch        *b_JetPFCor_ChargedEmEnergyFrac;   //!
   TBranch        *b_JetPFCor_ChargedMuEnergy;   //!
   TBranch        *b_JetPFCor_ChargedMuEnergyFrac;   //!
   TBranch        *b_JetPFCor_NeutralEmEnergy;   //!
   TBranch        *b_JetPFCor_NeutralEmEnergyFrac;   //!
   TBranch        *b_JetPFCor_ChargedMultiplicity;   //!
   TBranch        *b_JetPFCor_NeutralMultiplicity;   //!
   TBranch        *b_JetPFCor_MuonMultiplicity;   //!
   TBranch        *b_JetPFCor_PhotonEnergy;   //!
   TBranch        *b_JetPFCor_PhotonEnergyFraction;   //!
   TBranch        *b_JetPFCor_ElectronEnergy;   //!
   TBranch        *b_JetPFCor_ElectronEnergyFraction;   //!
   TBranch        *b_JetPFCor_MuonEnergy;   //!
   TBranch        *b_JetPFCor_MuonEnergyFraction;   //!
   TBranch        *b_JetPFCor_HFHadronEnergy;   //!
   TBranch        *b_JetPFCor_HFHadronEnergyFraction;   //!
   TBranch        *b_JetPFCor_HFEMEnergy;   //!
   TBranch        *b_JetPFCor_HFEMEnergyFraction;   //!
   TBranch        *b_JetPFCor_ChargedHadronMultiplicity;   //!
   TBranch        *b_JetPFCor_NeutralHadronMultiplicity;   //!
   TBranch        *b_JetPFCor_PhotonMultiplicity;   //!
   TBranch        *b_JetPFCor_ElectronMultiplicity;   //!
   TBranch        *b_JetPFCor_HFHadronMultiplicity;   //!
   TBranch        *b_JetPFCor_HFEMMultiplicity;   //!
   TBranch        *b_JetPFCor_SumPtCands;   //!
   TBranch        *b_JetPFCor_SumPt2Cands;   //!
   TBranch        *b_JetPFCor_rmsCands;   //!
   TBranch        *b_JetPFCor_PtD;   //!
   TBranch        *b_JetPFCor_QGLikelihood;   //!
   TBranch        *b_MassV2j_PFCor_MVAMET;   //!
   TBranch        *b_MassV2j_PFCor;   //!
   TBranch        *b_MassV3j_PFCor;   //!
   TBranch        *b_MassV4j_PFCor;   //!
   TBranch        *b_MassV5j_PFCor;   //!
   TBranch        *b_MassV6j_PFCor;   //!
   TBranch        *b_Mass2j_PFCor;   //!
   TBranch        *b_Mass3j_PFCor;   //!
   TBranch        *b_Mass4j_PFCor;   //!
   TBranch        *b_Mass5j_PFCor;   //!
   TBranch        *b_Mass6j_PFCor;   //!
   TBranch        *b_cosJacksonAngleV2j_PFCor;   //!
   TBranch        *b_cosJacksonAngle2j_PFCor;   //!
   TBranch        *b_cosJacksonAngleV3j_PFCor;   //!
   TBranch        *b_cosJacksonAngle3j12_PFCor;   //!
   TBranch        *b_cosJacksonAngle3j23_PFCor;   //!
   TBranch        *b_cosJacksonAngle3j31_PFCor;   //!
   TBranch        *b_cosphiDecayPlane_PFCor;   //!
   TBranch        *b_cosThetaLnu_PFCor;   //!
   TBranch        *b_cosThetaJJ_PFCor;   //!
   TBranch        *b_cosThetaJ1HiggsCM_PFCor;   //!
   TBranch        *b_cosThetaJ2HiggsCM_PFCor;   //!
   TBranch        *b_cosThetaL1HiggsCM_PFCor;   //!
   TBranch        *b_cosThetaL2HiggsCM_PFCor;   //!
   TBranch        *b_cosThetaV1HiggsCM_PFCor;   //!
   TBranch        *b_cosThetaV2HiggsCM_PFCor;   //!
   TBranch        *b_numGenJets;   //!
   TBranch        *b_numGenJetBTags;   //!
   TBranch        *b_JetGen_Et;   //!
   TBranch        *b_JetGen_Pt;   //!
   TBranch        *b_JetGen_Eta;   //!
   TBranch        *b_JetGen_Phi;   //!
   TBranch        *b_JetGen_Theta;   //!
   TBranch        *b_JetGen_Px;   //!
   TBranch        *b_JetGen_Py;   //!
   TBranch        *b_JetGen_Pz;   //!
   TBranch        *b_JetGen_E;   //!
   TBranch        *b_JetGen_Y;   //!
   TBranch        *b_JetGen_Mass;   //!
   TBranch        *b_JetGen_etaetaMoment;   //!
   TBranch        *b_JetGen_phiphiMoment;   //!
   TBranch        *b_JetGen_etaphiMoment;   //!
   TBranch        *b_JetGen_maxDistance;   //!
   TBranch        *b_JetGen_nConstituents;   //!
   TBranch        *b_JetGen_Area;   //!
   TBranch        *b_VplusGenJet_Mass;   //!
   TBranch        *b_JetGen_dphiBoson;   //!
   TBranch        *b_JetGen_detaBoson;   //!
   TBranch        *b_JetGen_dRBoson;   //!
   TBranch        *b_JetGen_dphiMET;   //!
   TBranch        *b_JetGen_bDiscriminator;   //!
   TBranch        *b_JetGen_bDiscriminatorSSVHE;   //!
   TBranch        *b_JetGen_bDiscriminatorTCHE;   //!
   TBranch        *b_JetGen_bDiscriminatorCSV;   //!
   TBranch        *b_JetGen_bDiscriminatorJP;   //!
   TBranch        *b_JetGen_bDiscriminatorSSVHP;   //!
   TBranch        *b_JetGen_bDiscriminatorTCHP;   //!
   TBranch        *b_JetGen_secVertexMass;   //!
   TBranch        *b_MassV2j_Gen_MVAMET;   //!
   TBranch        *b_MassV2j_Gen;   //!
   TBranch        *b_MassV3j_Gen;   //!
   TBranch        *b_MassV4j_Gen;   //!
   TBranch        *b_MassV5j_Gen;   //!
   TBranch        *b_MassV6j_Gen;   //!
   TBranch        *b_Mass2j_Gen;   //!
   TBranch        *b_Mass3j_Gen;   //!
   TBranch        *b_Mass4j_Gen;   //!
   TBranch        *b_Mass5j_Gen;   //!
   TBranch        *b_Mass6j_Gen;   //!
   TBranch        *b_cosJacksonAngleV2j_Gen;   //!
   TBranch        *b_cosJacksonAngle2j_Gen;   //!
   TBranch        *b_cosJacksonAngleV3j_Gen;   //!
   TBranch        *b_cosJacksonAngle3j12_Gen;   //!
   TBranch        *b_cosJacksonAngle3j23_Gen;   //!
   TBranch        *b_cosJacksonAngle3j31_Gen;   //!
   TBranch        *b_cosphiDecayPlane_Gen;   //!
   TBranch        *b_cosThetaLnu_Gen;   //!
   TBranch        *b_cosThetaJJ_Gen;   //!
   TBranch        *b_NumPhotons;   //!
   TBranch        *b_Photon_Et;   //!
   TBranch        *b_Photon_E;   //!
   TBranch        *b_Photon_Eta;   //!
   TBranch        *b_Photon_Phi;   //!
   TBranch        *b_Photon_Theta;   //!
   TBranch        *b_Photon_Px;   //!
   TBranch        *b_Photon_Py;   //!
   TBranch        *b_Photon_Pz;   //!
   TBranch        *b_Photon_Vx;   //!
   TBranch        *b_Photon_Vy;   //!
   TBranch        *b_Photon_Vz;   //!
   TBranch        *b_Photon_SC_Et;   //!
   TBranch        *b_Photon_SC_E;   //!
   TBranch        *b_Photon_SC_Eta;   //!
   TBranch        *b_Photon_SC_Phi;   //!
   TBranch        *b_Photon_SC_Theta;   //!
   TBranch        *b_Photon_SC_x;   //!
   TBranch        *b_Photon_SC_y;   //!
   TBranch        *b_Photon_SC_z;   //!
   TBranch        *b_PFisocharged03;   //!
   TBranch        *b_PFisophoton03;   //!
   TBranch        *b_PFisoneutral03;   //!
//   TBranch        *b_trkSumPtHollowConeDR04_Photon11; //!
//   TBranch        *b_ecalRecHitSumEtConeDR04_Photon11; //!
//   TBranch        *b_hcalTowerSumEtConeDR04_Photon11; //!
   TBranch        *b_Photon_HoverE;   //!
   TBranch        *b_Photon_HoverE2011;   //!
   TBranch        *b_Photon_SigmaIetaIeta;   //!
   TBranch        *b_Photon_hasPixelSeed;   //!
   TBranch        *b_Photon_passElecVeto;   //!
   TBranch        *b_Photon_Id2011;   //!
   TBranch        *b_Photon_Id2012;   //!
   TBranch        *b_W_mass;   //!
   TBranch        *b_W_mt;   //!
   TBranch        *b_W_mtMVA;   //!
   TBranch        *b_W_px;   //!
   TBranch        *b_W_py;   //!
   TBranch        *b_W_pz;   //!
   TBranch        *b_W_e;   //!
   TBranch        *b_W_pt;   //!
   TBranch        *b_W_et;   //!
   TBranch        *b_W_eta;   //!
   TBranch        *b_W_phi;   //!
   TBranch        *b_W_vx;   //!
   TBranch        *b_W_vy;   //!
   TBranch        *b_W_vz;   //!
   TBranch        *b_W_y;   //!
   TBranch        *b_W_numTightElectrons;   //!
   TBranch        *b_W_numLooseElectrons;   //!
   TBranch        *b_W_pzNu1;   //!
   TBranch        *b_W_pzNu2;   //!
   TBranch        *b_W_electron_px;   //!
   TBranch        *b_W_electron_py;   //!
   TBranch        *b_W_electron_pz;   //!
   TBranch        *b_W_electron_e;   //!
   TBranch        *b_W_electron_pt;   //!
   TBranch        *b_W_electron_et;   //!
   TBranch        *b_W_electron_eta;   //!
   TBranch        *b_W_electron_theta;   //!
   TBranch        *b_W_electron_phi;   //!
   TBranch        *b_W_electron_charge;   //!
   TBranch        *b_W_electron_vx;   //!
   TBranch        *b_W_electron_vy;   //!
   TBranch        *b_W_electron_vz;   //!
   TBranch        *b_W_electron_y;   //!
   TBranch        *b_W_electron_trackiso;   //!
   TBranch        *b_W_electron_hcaliso;   //!
   TBranch        *b_W_electron_ecaliso;   //!
   TBranch        *b_W_electron_classification;   //!
   TBranch        *b_W_electron_missingHits;   //!
   TBranch        *b_W_electron_dist;   //!
   TBranch        *b_W_electron_dcot;   //!
   TBranch        *b_W_electron_d0bsp;   //!
   TBranch        *b_W_electron_dz000;   //!
   TBranch        *b_W_electron_mvaTrigV0;   //!
   TBranch        *b_W_electron_mvaNonTrigV0;   //!
   TBranch        *b_W_electron_pfiso_chargedHadronIso;   //!
   TBranch        *b_W_electron_pfiso_photonIso;   //!
   TBranch        *b_W_electron_pfiso_neutralHadronIso;   //!
   TBranch        *b_W_electron_pfIsoEA;   //!
   TBranch        *b_W_H_mass_gen;   //!
   TBranch        *b_W_H_px_gen;   //!
   TBranch        *b_W_H_py_gen;   //!
   TBranch        *b_W_H_pz_gen;   //!
   TBranch        *b_W_H_e_gen;   //!
   TBranch        *b_W_H_pt_gen;   //!
   TBranch        *b_W_H_et_gen;   //!
   TBranch        *b_W_H_eta_gen;   //!
   TBranch        *b_W_H_phi_gen;   //!
   TBranch        *b_W_H_vx_gen;   //!
   TBranch        *b_W_H_vy_gen;   //!
   TBranch        *b_W_H_vz_gen;   //!
   TBranch        *b_W_H_y_gen;   //!
   TBranch        *b_W_H_Id_gen;   //!
   TBranch        *b_W_electron_px_gen;   //!
   TBranch        *b_W_electron_py_gen;   //!
   TBranch        *b_W_electron_pz_gen;   //!
   TBranch        *b_W_electron_e_gen;   //!
   TBranch        *b_W_electron_pt_gen;   //!
   TBranch        *b_W_electron_et_gen;   //!
   TBranch        *b_W_electron_eta_gen;   //!
   TBranch        *b_W_electron_theta_gen;   //!
   TBranch        *b_W_electron_phi_gen;   //!
   TBranch        *b_W_electron_charge_gen;   //!
   TBranch        *b_W_electron_vx_gen;   //!
   TBranch        *b_W_electron_vy_gen;   //!
   TBranch        *b_W_electron_vz_gen;   //!
   TBranch        *b_W_electron_y_gen;   //!
   TBranch        *b_W_neutrino_px_gen;   //!
   TBranch        *b_W_neutrino_py_gen;   //!
   TBranch        *b_W_neutrino_pz_gen;   //!
   TBranch        *b_W_neutrino_e_gen;   //!
   TBranch        *b_W_neutrino_pt_gen;   //!
   TBranch        *b_W_neutrino_et_gen;   //!
   TBranch        *b_W_neutrino_eta_gen;   //!
   TBranch        *b_W_neutrino_theta_gen;   //!
   TBranch        *b_W_neutrino_phi_gen;   //!
   TBranch        *b_W_neutrino_charge_gen;   //!
   TBranch        *b_W_neutrino_vx_gen;   //!
   TBranch        *b_W_neutrino_vy_gen;   //!
   TBranch        *b_W_neutrino_vz_gen;   //!
   TBranch        *b_W_neutrino_y_gen;   //!
   TBranch        *b_W_Parton_px;   //!
   TBranch        *b_W_Parton_py;   //!
   TBranch        *b_W_Parton_pz;   //!
   TBranch        *b_W_Parton_E;   //!
   TBranch        *b_W_Parton_pt;   //!
   TBranch        *b_W_Parton_et;   //!
   TBranch        *b_W_Parton_eta;   //!
   TBranch        *b_W_Parton_theta;   //!
   TBranch        *b_W_Parton_phi;   //!
   TBranch        *b_W_Parton_charge;   //!
   TBranch        *b_W_Parton_vx;   //!
   TBranch        *b_W_Parton_vy;   //!
   TBranch        *b_W_Parton_vz;   //!
   TBranch        *b_W_Parton_y;   //!
   TBranch        *b_W_Parton_Id;   //!
   TBranch        *b_W_Lepton_px;   //!
   TBranch        *b_W_Lepton_py;   //!
   TBranch        *b_W_Lepton_pz;   //!
   TBranch        *b_W_Lepton_E;   //!
   TBranch        *b_W_Lepton_pt;   //!
   TBranch        *b_W_Lepton_et;   //!
   TBranch        *b_W_Lepton_eta;   //!
   TBranch        *b_W_Lepton_theta;   //!
   TBranch        *b_W_Lepton_phi;   //!
   TBranch        *b_W_Lepton_charge;   //!
   TBranch        *b_W_Lepton_vx;   //!
   TBranch        *b_W_Lepton_vy;   //!
   TBranch        *b_W_Lepton_vz;   //!
   TBranch        *b_W_Lepton_y;   //!
   TBranch        *b_W_Lepton_Id;   //!
   TBranch        *b_W_Met_px;   //!
   TBranch        *b_W_Met_py;   //!
   TBranch        *b_W_Met_pz;   //!
   TBranch        *b_W_Met_E;   //!
   TBranch        *b_W_Met_pt;   //!
   TBranch        *b_W_Met_et;   //!
   TBranch        *b_W_Met_eta;   //!
   TBranch        *b_W_Met_theta;   //!
   TBranch        *b_W_Met_phi;   //!
   TBranch        *b_W_Met_charge;   //!
   TBranch        *b_W_Met_vx;   //!
   TBranch        *b_W_Met_vy;   //!
   TBranch        *b_W_Met_vz;   //!
   TBranch        *b_W_Met_y;   //!
   TBranch        *b_W_Met_Id;   //!
   TBranch        *b_event_runNo;   //!
   TBranch        *b_event_evtNo;   //!
   TBranch        *b_event_lumi;   //!
   TBranch        *b_event_bunch;   //!
   TBranch        *b_event_nPV;   //!
   TBranch        *b_event_met_pfmet;   //!
   TBranch        *b_event_met_pfsumet;   //!
   TBranch        *b_event_met_pfmetsignificance;   //!
   TBranch        *b_event_met_pfmetPhi;   //!
   TBranch        *b_event_metMVA_met;   //!
   TBranch        *b_event_metMVA_sumet;   //!
   TBranch        *b_event_metMVA_metsignificance;   //!
   TBranch        *b_event_metMVA_metPhi;   //!
   TBranch        *b_event_fastJetRho;   //!
   TBranch        *b_event_met_genmet;   //!
   TBranch        *b_event_met_gensumet;   //!
   TBranch        *b_event_met_genmetsignificance;   //!
   TBranch        *b_event_met_genmetPhi;   //!
   TBranch        *b_event_mcPU_totnvtx;   //!
   TBranch        *b_event_mcPU_trueInteractions;   //!
   TBranch        *b_event_mcPU_bx;   //!
   TBranch        *b_event_mcPU_nvtx;   //!

   kanaelec_photon(TTree *tree=0);
   virtual ~kanaelec_photon();
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   Float_t dRCalc(Float_t etaC, Float_t phiC, Float_t etaCrys, Float_t phiCrys);
   virtual void     myana(double myflag = -999, bool isQCD = false, int runflag=0);
   virtual void     Loop(TH1F* h_events, 
                         TH1F* h_events_weighted,
                         int wda, 
                         int runflag, 
                         const char * outfilename, 
                         bool isQCD = false);
   virtual double   getDeltaPhi(double phi1, double phi2);
   virtual bool     doKinematicFit(Int_t                 fflage,
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
				   Int_t              & fit_status);
   virtual void     calculateAngles( TLorentzVector& thep4M11, TLorentzVector& thep4M12, TLorentzVector& thep4M21, TLorentzVector& thep4M22, double& costheta1, double& costheta2, double& phi, double& costhetastar, double& phistar1, double& phistar2);
    virtual void     gammaCalcAngles( TLorentzVector& thep4gamma, TLorentzVector& thep4M11, TLorentzVector& thep4M12, double& cosine_gamma_vs_decayplane_phi);
   virtual void     InitCounters(const char* input_file_name, TH1F* h_events, TH1F* h_events_weighted);

};

#endif

#ifdef kanaelec_photon_cxx
kanaelec_photon::kanaelec_photon(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/uscms_data/d3/weizou/MakeNtuple/CMSSW_5_3_2_patch4/src/ElectroWeakAnalysis/VPlusJets/test/el_STopS_Tbar_CMSSW532.root");
      if (!f) {
         f = new TFile("/uscms_data/d3/weizou/MakeNtuple/CMSSW_5_3_2_patch4/src/ElectroWeakAnalysis/VPlusJets/test/el_STopS_Tbar_CMSSW532.root");
      }
      tree = (TTree*)gDirectory->Get("WJet");

   }
   Init(tree);
}

kanaelec_photon::~kanaelec_photon()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t kanaelec_photon::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t kanaelec_photon::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void kanaelec_photon::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("numPFCorJets", &numPFCorJets, &b_numPFCorJets);
   fChain->SetBranchAddress("numPFCorJetBTags", &numPFCorJetBTags, &b_numPFCorJetBTags);
   fChain->SetBranchAddress("JetPFCor_Et", JetPFCor_Et, &b_JetPFCor_Et);
   fChain->SetBranchAddress("JetPFCor_Pt", JetPFCor_Pt, &b_JetPFCor_Pt);
   fChain->SetBranchAddress("JetPFCor_Eta", JetPFCor_Eta, &b_JetPFCor_Eta);
   fChain->SetBranchAddress("JetPFCor_Phi", JetPFCor_Phi, &b_JetPFCor_Phi);
   fChain->SetBranchAddress("JetPFCor_Theta", JetPFCor_Theta, &b_JetPFCor_Theta);
   fChain->SetBranchAddress("JetPFCor_Px", JetPFCor_Px, &b_JetPFCor_Px);
   fChain->SetBranchAddress("JetPFCor_Py", JetPFCor_Py, &b_JetPFCor_Py);
   fChain->SetBranchAddress("JetPFCor_Pz", JetPFCor_Pz, &b_JetPFCor_Pz);
   fChain->SetBranchAddress("JetPFCor_E", JetPFCor_E, &b_JetPFCor_E);
   fChain->SetBranchAddress("JetPFCor_Y", JetPFCor_Y, &b_JetPFCor_Y);
   fChain->SetBranchAddress("JetPFCor_Mass", JetPFCor_Mass, &b_JetPFCor_Mass);
   fChain->SetBranchAddress("JetPFCor_etaetaMoment", JetPFCor_etaetaMoment, &b_JetPFCor_etaetaMoment);
   fChain->SetBranchAddress("JetPFCor_phiphiMoment", JetPFCor_phiphiMoment, &b_JetPFCor_phiphiMoment);
   fChain->SetBranchAddress("JetPFCor_etaphiMoment", JetPFCor_etaphiMoment, &b_JetPFCor_etaphiMoment);
   fChain->SetBranchAddress("JetPFCor_maxDistance", JetPFCor_maxDistance, &b_JetPFCor_maxDistance);
   fChain->SetBranchAddress("JetPFCor_nConstituents", JetPFCor_nConstituents, &b_JetPFCor_nConstituents);
   fChain->SetBranchAddress("JetPFCor_Area", JetPFCor_Area, &b_JetPFCor_Area);
   fChain->SetBranchAddress("VplusPFCorJet_Mass", VplusPFCorJet_Mass, &b_VplusPFCorJet_Mass);
   fChain->SetBranchAddress("JetPFCor_dphiBoson", JetPFCor_dphiBoson, &b_JetPFCor_dphiBoson);
   fChain->SetBranchAddress("JetPFCor_detaBoson", JetPFCor_detaBoson, &b_JetPFCor_detaBoson);
   fChain->SetBranchAddress("JetPFCor_dRBoson", JetPFCor_dRBoson, &b_JetPFCor_dRBoson);
   fChain->SetBranchAddress("JetPFCor_dphiMET", JetPFCor_dphiMET, &b_JetPFCor_dphiMET);
   fChain->SetBranchAddress("JetPFCor_bDiscriminator", JetPFCor_bDiscriminator, &b_JetPFCor_bDiscriminator);
   fChain->SetBranchAddress("JetPFCor_bDiscriminatorSSVHE", JetPFCor_bDiscriminatorSSVHE, &b_JetPFCor_bDiscriminatorSSVHE);
   fChain->SetBranchAddress("JetPFCor_bDiscriminatorTCHE", JetPFCor_bDiscriminatorTCHE, &b_JetPFCor_bDiscriminatorTCHE);
   fChain->SetBranchAddress("JetPFCor_bDiscriminatorCSV", JetPFCor_bDiscriminatorCSV, &b_JetPFCor_bDiscriminatorCSV);
   fChain->SetBranchAddress("JetPFCor_bDiscriminatorJP", JetPFCor_bDiscriminatorJP, &b_JetPFCor_bDiscriminatorJP);
   fChain->SetBranchAddress("JetPFCor_bDiscriminatorSSVHP", JetPFCor_bDiscriminatorSSVHP, &b_JetPFCor_bDiscriminatorSSVHP);
   fChain->SetBranchAddress("JetPFCor_bDiscriminatorTCHP", JetPFCor_bDiscriminatorTCHP, &b_JetPFCor_bDiscriminatorTCHP);
   fChain->SetBranchAddress("JetPFCor_secVertexMass", JetPFCor_secVertexMass, &b_JetPFCor_secVertexMass);
   fChain->SetBranchAddress("JetPFCor_ChargedHadronEnergy", JetPFCor_ChargedHadronEnergy, &b_JetPFCor_ChargedHadronEnergy);
   fChain->SetBranchAddress("JetPFCor_ChargedHadronEnergyFrac", JetPFCor_ChargedHadronEnergyFrac, &b_JetPFCor_ChargedHadronEnergyFrac);
   fChain->SetBranchAddress("JetPFCor_NeutralHadronEnergy", JetPFCor_NeutralHadronEnergy, &b_JetPFCor_NeutralHadronEnergy);
   fChain->SetBranchAddress("JetPFCor_NeutralHadronEnergyFrac", JetPFCor_NeutralHadronEnergyFrac, &b_JetPFCor_NeutralHadronEnergyFrac);
   fChain->SetBranchAddress("JetPFCor_ChargedEmEnergy", JetPFCor_ChargedEmEnergy, &b_JetPFCor_ChargedEmEnergy);
   fChain->SetBranchAddress("JetPFCor_ChargedEmEnergyFrac", JetPFCor_ChargedEmEnergyFrac, &b_JetPFCor_ChargedEmEnergyFrac);
   fChain->SetBranchAddress("JetPFCor_ChargedMuEnergy", JetPFCor_ChargedMuEnergy, &b_JetPFCor_ChargedMuEnergy);
   fChain->SetBranchAddress("JetPFCor_ChargedMuEnergyFrac", JetPFCor_ChargedMuEnergyFrac, &b_JetPFCor_ChargedMuEnergyFrac);
   fChain->SetBranchAddress("JetPFCor_NeutralEmEnergy", JetPFCor_NeutralEmEnergy, &b_JetPFCor_NeutralEmEnergy);
   fChain->SetBranchAddress("JetPFCor_NeutralEmEnergyFrac", JetPFCor_NeutralEmEnergyFrac, &b_JetPFCor_NeutralEmEnergyFrac);
   fChain->SetBranchAddress("JetPFCor_ChargedMultiplicity", JetPFCor_ChargedMultiplicity, &b_JetPFCor_ChargedMultiplicity);
   fChain->SetBranchAddress("JetPFCor_NeutralMultiplicity", JetPFCor_NeutralMultiplicity, &b_JetPFCor_NeutralMultiplicity);
   fChain->SetBranchAddress("JetPFCor_MuonMultiplicity", JetPFCor_MuonMultiplicity, &b_JetPFCor_MuonMultiplicity);
   fChain->SetBranchAddress("JetPFCor_PhotonEnergy", JetPFCor_PhotonEnergy, &b_JetPFCor_PhotonEnergy);
   fChain->SetBranchAddress("JetPFCor_PhotonEnergyFraction", JetPFCor_PhotonEnergyFraction, &b_JetPFCor_PhotonEnergyFraction);
   fChain->SetBranchAddress("JetPFCor_ElectronEnergy", JetPFCor_ElectronEnergy, &b_JetPFCor_ElectronEnergy);
   fChain->SetBranchAddress("JetPFCor_ElectronEnergyFraction", JetPFCor_ElectronEnergyFraction, &b_JetPFCor_ElectronEnergyFraction);
   fChain->SetBranchAddress("JetPFCor_MuonEnergy", JetPFCor_MuonEnergy, &b_JetPFCor_MuonEnergy);
   fChain->SetBranchAddress("JetPFCor_MuonEnergyFraction", JetPFCor_MuonEnergyFraction, &b_JetPFCor_MuonEnergyFraction);
   fChain->SetBranchAddress("JetPFCor_HFHadronEnergy", JetPFCor_HFHadronEnergy, &b_JetPFCor_HFHadronEnergy);
   fChain->SetBranchAddress("JetPFCor_HFHadronEnergyFraction", JetPFCor_HFHadronEnergyFraction, &b_JetPFCor_HFHadronEnergyFraction);
   fChain->SetBranchAddress("JetPFCor_HFEMEnergy", JetPFCor_HFEMEnergy, &b_JetPFCor_HFEMEnergy);
   fChain->SetBranchAddress("JetPFCor_HFEMEnergyFraction", JetPFCor_HFEMEnergyFraction, &b_JetPFCor_HFEMEnergyFraction);
   fChain->SetBranchAddress("JetPFCor_ChargedHadronMultiplicity", JetPFCor_ChargedHadronMultiplicity, &b_JetPFCor_ChargedHadronMultiplicity);
   fChain->SetBranchAddress("JetPFCor_NeutralHadronMultiplicity", JetPFCor_NeutralHadronMultiplicity, &b_JetPFCor_NeutralHadronMultiplicity);
   fChain->SetBranchAddress("JetPFCor_PhotonMultiplicity", JetPFCor_PhotonMultiplicity, &b_JetPFCor_PhotonMultiplicity);
   fChain->SetBranchAddress("JetPFCor_ElectronMultiplicity", JetPFCor_ElectronMultiplicity, &b_JetPFCor_ElectronMultiplicity);
   fChain->SetBranchAddress("JetPFCor_HFHadronMultiplicity", JetPFCor_HFHadronMultiplicity, &b_JetPFCor_HFHadronMultiplicity);
   fChain->SetBranchAddress("JetPFCor_HFEMMultiplicity", JetPFCor_HFEMMultiplicity, &b_JetPFCor_HFEMMultiplicity);
   fChain->SetBranchAddress("JetPFCor_SumPtCands", JetPFCor_SumPtCands, &b_JetPFCor_SumPtCands);
   fChain->SetBranchAddress("JetPFCor_SumPt2Cands", JetPFCor_SumPt2Cands, &b_JetPFCor_SumPt2Cands);
   fChain->SetBranchAddress("JetPFCor_rmsCands", JetPFCor_rmsCands, &b_JetPFCor_rmsCands);
   fChain->SetBranchAddress("JetPFCor_PtD", JetPFCor_PtD, &b_JetPFCor_PtD);
   fChain->SetBranchAddress("JetPFCor_QGLikelihood", JetPFCor_QGLikelihood, &b_JetPFCor_QGLikelihood);
   fChain->SetBranchAddress("MassV2j_PFCor_MVAMET", &MassV2j_PFCor_MVAMET, &b_MassV2j_PFCor_MVAMET);
   fChain->SetBranchAddress("MassV2j_PFCor", &MassV2j_PFCor, &b_MassV2j_PFCor);
   fChain->SetBranchAddress("MassV3j_PFCor", &MassV3j_PFCor, &b_MassV3j_PFCor);
   fChain->SetBranchAddress("MassV4j_PFCor", &MassV4j_PFCor, &b_MassV4j_PFCor);
   fChain->SetBranchAddress("MassV5j_PFCor", &MassV5j_PFCor, &b_MassV5j_PFCor);
   fChain->SetBranchAddress("MassV6j_PFCor", &MassV6j_PFCor, &b_MassV6j_PFCor);
   fChain->SetBranchAddress("Mass2j_PFCor", &Mass2j_PFCor, &b_Mass2j_PFCor);
   fChain->SetBranchAddress("Mass3j_PFCor", &Mass3j_PFCor, &b_Mass3j_PFCor);
   fChain->SetBranchAddress("Mass4j_PFCor", &Mass4j_PFCor, &b_Mass4j_PFCor);
   fChain->SetBranchAddress("Mass5j_PFCor", &Mass5j_PFCor, &b_Mass5j_PFCor);
   fChain->SetBranchAddress("Mass6j_PFCor", &Mass6j_PFCor, &b_Mass6j_PFCor);
   fChain->SetBranchAddress("cosJacksonAngleV2j_PFCor", &cosJacksonAngleV2j_PFCor, &b_cosJacksonAngleV2j_PFCor);
   fChain->SetBranchAddress("cosJacksonAngle2j_PFCor", &cosJacksonAngle2j_PFCor, &b_cosJacksonAngle2j_PFCor);
   fChain->SetBranchAddress("cosJacksonAngleV3j_PFCor", &cosJacksonAngleV3j_PFCor, &b_cosJacksonAngleV3j_PFCor);
   fChain->SetBranchAddress("cosJacksonAngle3j12_PFCor", &cosJacksonAngle3j12_PFCor, &b_cosJacksonAngle3j12_PFCor);
   fChain->SetBranchAddress("cosJacksonAngle3j23_PFCor", &cosJacksonAngle3j23_PFCor, &b_cosJacksonAngle3j23_PFCor);
   fChain->SetBranchAddress("cosJacksonAngle3j31_PFCor", &cosJacksonAngle3j31_PFCor, &b_cosJacksonAngle3j31_PFCor);
   fChain->SetBranchAddress("cosphiDecayPlane_PFCor", &cosphiDecayPlane_PFCor, &b_cosphiDecayPlane_PFCor);
   fChain->SetBranchAddress("cosThetaLnu_PFCor", &cosThetaLnu_PFCor, &b_cosThetaLnu_PFCor);
   fChain->SetBranchAddress("cosThetaJJ_PFCor", &cosThetaJJ_PFCor, &b_cosThetaJJ_PFCor);
   fChain->SetBranchAddress("cosThetaJ1HiggsCM_PFCor", &cosThetaJ1HiggsCM_PFCor, &b_cosThetaJ1HiggsCM_PFCor);
   fChain->SetBranchAddress("cosThetaJ2HiggsCM_PFCor", &cosThetaJ2HiggsCM_PFCor, &b_cosThetaJ2HiggsCM_PFCor);
   fChain->SetBranchAddress("cosThetaL1HiggsCM_PFCor", &cosThetaL1HiggsCM_PFCor, &b_cosThetaL1HiggsCM_PFCor);
   fChain->SetBranchAddress("cosThetaL2HiggsCM_PFCor", &cosThetaL2HiggsCM_PFCor, &b_cosThetaL2HiggsCM_PFCor);
   fChain->SetBranchAddress("cosThetaV1HiggsCM_PFCor", &cosThetaV1HiggsCM_PFCor, &b_cosThetaV1HiggsCM_PFCor);
   fChain->SetBranchAddress("cosThetaV2HiggsCM_PFCor", &cosThetaV2HiggsCM_PFCor, &b_cosThetaV2HiggsCM_PFCor);
   fChain->SetBranchAddress("numGenJets", &numGenJets, &b_numGenJets);
   fChain->SetBranchAddress("numGenJetBTags", &numGenJetBTags, &b_numGenJetBTags);
   fChain->SetBranchAddress("JetGen_Et", JetGen_Et, &b_JetGen_Et);
   fChain->SetBranchAddress("JetGen_Pt", JetGen_Pt, &b_JetGen_Pt);
   fChain->SetBranchAddress("JetGen_Eta", JetGen_Eta, &b_JetGen_Eta);
   fChain->SetBranchAddress("JetGen_Phi", JetGen_Phi, &b_JetGen_Phi);
   fChain->SetBranchAddress("JetGen_Theta", JetGen_Theta, &b_JetGen_Theta);
   fChain->SetBranchAddress("JetGen_Px", JetGen_Px, &b_JetGen_Px);
   fChain->SetBranchAddress("JetGen_Py", JetGen_Py, &b_JetGen_Py);
   fChain->SetBranchAddress("JetGen_Pz", JetGen_Pz, &b_JetGen_Pz);
   fChain->SetBranchAddress("JetGen_E", JetGen_E, &b_JetGen_E);
   fChain->SetBranchAddress("JetGen_Y", JetGen_Y, &b_JetGen_Y);
   fChain->SetBranchAddress("JetGen_Mass", JetGen_Mass, &b_JetGen_Mass);
   fChain->SetBranchAddress("JetGen_etaetaMoment", JetGen_etaetaMoment, &b_JetGen_etaetaMoment);
   fChain->SetBranchAddress("JetGen_phiphiMoment", JetGen_phiphiMoment, &b_JetGen_phiphiMoment);
   fChain->SetBranchAddress("JetGen_etaphiMoment", JetGen_etaphiMoment, &b_JetGen_etaphiMoment);
   fChain->SetBranchAddress("JetGen_maxDistance", JetGen_maxDistance, &b_JetGen_maxDistance);
   fChain->SetBranchAddress("JetGen_nConstituents", JetGen_nConstituents, &b_JetGen_nConstituents);
   fChain->SetBranchAddress("JetGen_Area", JetGen_Area, &b_JetGen_Area);
   fChain->SetBranchAddress("VplusGenJet_Mass", VplusGenJet_Mass, &b_VplusGenJet_Mass);
   fChain->SetBranchAddress("JetGen_dphiBoson", JetGen_dphiBoson, &b_JetGen_dphiBoson);
   fChain->SetBranchAddress("JetGen_detaBoson", JetGen_detaBoson, &b_JetGen_detaBoson);
   fChain->SetBranchAddress("JetGen_dRBoson", JetGen_dRBoson, &b_JetGen_dRBoson);
   fChain->SetBranchAddress("JetGen_dphiMET", JetGen_dphiMET, &b_JetGen_dphiMET);
   fChain->SetBranchAddress("JetGen_bDiscriminator", JetGen_bDiscriminator, &b_JetGen_bDiscriminator);
   fChain->SetBranchAddress("JetGen_bDiscriminatorSSVHE", JetGen_bDiscriminatorSSVHE, &b_JetGen_bDiscriminatorSSVHE);
   fChain->SetBranchAddress("JetGen_bDiscriminatorTCHE", JetGen_bDiscriminatorTCHE, &b_JetGen_bDiscriminatorTCHE);
   fChain->SetBranchAddress("JetGen_bDiscriminatorCSV", JetGen_bDiscriminatorCSV, &b_JetGen_bDiscriminatorCSV);
   fChain->SetBranchAddress("JetGen_bDiscriminatorJP", JetGen_bDiscriminatorJP, &b_JetGen_bDiscriminatorJP);
   fChain->SetBranchAddress("JetGen_bDiscriminatorSSVHP", JetGen_bDiscriminatorSSVHP, &b_JetGen_bDiscriminatorSSVHP);
   fChain->SetBranchAddress("JetGen_bDiscriminatorTCHP", JetGen_bDiscriminatorTCHP, &b_JetGen_bDiscriminatorTCHP);
   fChain->SetBranchAddress("JetGen_secVertexMass", JetGen_secVertexMass, &b_JetGen_secVertexMass);
   fChain->SetBranchAddress("MassV2j_Gen_MVAMET", &MassV2j_Gen_MVAMET, &b_MassV2j_Gen_MVAMET);
   fChain->SetBranchAddress("MassV2j_Gen", &MassV2j_Gen, &b_MassV2j_Gen);
   fChain->SetBranchAddress("MassV3j_Gen", &MassV3j_Gen, &b_MassV3j_Gen);
   fChain->SetBranchAddress("MassV4j_Gen", &MassV4j_Gen, &b_MassV4j_Gen);
   fChain->SetBranchAddress("MassV5j_Gen", &MassV5j_Gen, &b_MassV5j_Gen);
   fChain->SetBranchAddress("MassV6j_Gen", &MassV6j_Gen, &b_MassV6j_Gen);
   fChain->SetBranchAddress("Mass2j_Gen", &Mass2j_Gen, &b_Mass2j_Gen);
   fChain->SetBranchAddress("Mass3j_Gen", &Mass3j_Gen, &b_Mass3j_Gen);
   fChain->SetBranchAddress("Mass4j_Gen", &Mass4j_Gen, &b_Mass4j_Gen);
   fChain->SetBranchAddress("Mass5j_Gen", &Mass5j_Gen, &b_Mass5j_Gen);
   fChain->SetBranchAddress("Mass6j_Gen", &Mass6j_Gen, &b_Mass6j_Gen);
   fChain->SetBranchAddress("cosJacksonAngleV2j_Gen", &cosJacksonAngleV2j_Gen, &b_cosJacksonAngleV2j_Gen);
   fChain->SetBranchAddress("cosJacksonAngle2j_Gen", &cosJacksonAngle2j_Gen, &b_cosJacksonAngle2j_Gen);
   fChain->SetBranchAddress("cosJacksonAngleV3j_Gen", &cosJacksonAngleV3j_Gen, &b_cosJacksonAngleV3j_Gen);
   fChain->SetBranchAddress("cosJacksonAngle3j12_Gen", &cosJacksonAngle3j12_Gen, &b_cosJacksonAngle3j12_Gen);
   fChain->SetBranchAddress("cosJacksonAngle3j23_Gen", &cosJacksonAngle3j23_Gen, &b_cosJacksonAngle3j23_Gen);
   fChain->SetBranchAddress("cosJacksonAngle3j31_Gen", &cosJacksonAngle3j31_Gen, &b_cosJacksonAngle3j31_Gen);
   fChain->SetBranchAddress("cosphiDecayPlane_Gen", &cosphiDecayPlane_Gen, &b_cosphiDecayPlane_Gen);
   fChain->SetBranchAddress("cosThetaLnu_Gen", &cosThetaLnu_Gen, &b_cosThetaLnu_Gen);
   fChain->SetBranchAddress("cosThetaJJ_Gen", &cosThetaJJ_Gen, &b_cosThetaJJ_Gen);
   fChain->SetBranchAddress("NumPhotons", &NumPhotons, &b_NumPhotons);
   fChain->SetBranchAddress("Photon_Et", Photon_Et, &b_Photon_Et);
   fChain->SetBranchAddress("Photon_E", Photon_E, &b_Photon_E);
   fChain->SetBranchAddress("Photon_Eta", Photon_Eta, &b_Photon_Eta);
   fChain->SetBranchAddress("Photon_Phi", Photon_Phi, &b_Photon_Phi);
   fChain->SetBranchAddress("Photon_Theta", Photon_Theta, &b_Photon_Theta);
   fChain->SetBranchAddress("Photon_Px", Photon_Px, &b_Photon_Px);
   fChain->SetBranchAddress("Photon_Py", Photon_Py, &b_Photon_Py);
   fChain->SetBranchAddress("Photon_Pz", Photon_Pz, &b_Photon_Pz);
   fChain->SetBranchAddress("Photon_Vx", Photon_Vx, &b_Photon_Vx);
   fChain->SetBranchAddress("Photon_Vy", Photon_Vy, &b_Photon_Vy);
   fChain->SetBranchAddress("Photon_Vz", Photon_Vz, &b_Photon_Vz);
   fChain->SetBranchAddress("Photon_SC_Et", Photon_SC_Et, &b_Photon_SC_Et);
   fChain->SetBranchAddress("Photon_SC_E", Photon_SC_E, &b_Photon_SC_E);
   fChain->SetBranchAddress("Photon_SC_Eta", Photon_SC_Eta, &b_Photon_SC_Eta);
   fChain->SetBranchAddress("Photon_SC_Phi", Photon_SC_Phi, &b_Photon_SC_Phi);
   fChain->SetBranchAddress("Photon_SC_Theta", Photon_SC_Theta, &b_Photon_SC_Theta);
   fChain->SetBranchAddress("Photon_SC_x", Photon_SC_x, &b_Photon_SC_x);
   fChain->SetBranchAddress("Photon_SC_y", Photon_SC_y, &b_Photon_SC_y);
   fChain->SetBranchAddress("Photon_SC_z", Photon_SC_z, &b_Photon_SC_z);
   fChain->SetBranchAddress("PFisocharged03", PFisocharged03, &b_PFisocharged03);
   fChain->SetBranchAddress("PFisophoton03", PFisophoton03, &b_PFisophoton03);
   fChain->SetBranchAddress("PFisoneutral03", PFisoneutral03, &b_PFisoneutral03);
//  fChain->SetBranchAddress("trkSumPtHollowConeDR04_Photon11", trkSumPtHollowConeDR04_Photon11, &b_trkSumPtHollowConeDR04_Photon11);
//  fChain->SetBranchAddress("ecalRecHitSumEtConeDR04_Photon11", ecalRecHitSumEtConeDR04_Photon11, &b_ecalRecHitSumEtConeDR04_Photon11);
//  fChain->SetBranchAddress("hcalTowerSumEtConeDR04_Photon11", hcalTowerSumEtConeDR04_Photon11, &b_hcalTowerSumEtConeDR04_Photon11);
   fChain->SetBranchAddress("Photon_HoverE", Photon_HoverE, &b_Photon_HoverE);
   fChain->SetBranchAddress("Photon_HoverE2011", Photon_HoverE2011, &b_Photon_HoverE2011);
   fChain->SetBranchAddress("Photon_SigmaIetaIeta", Photon_SigmaIetaIeta, &b_Photon_SigmaIetaIeta);
   fChain->SetBranchAddress("Photon_hasPixelSeed", Photon_hasPixelSeed, &b_Photon_hasPixelSeed);
   fChain->SetBranchAddress("Photon_passElecVeto", Photon_passElecVeto, &b_Photon_passElecVeto);
   fChain->SetBranchAddress("Photon_Id2011", Photon_Id2011, &b_Photon_Id2011);
   fChain->SetBranchAddress("Photon_Id2012", Photon_Id2012, &b_Photon_Id2012);
   fChain->SetBranchAddress("W_mass", &W_mass, &b_W_mass);
   fChain->SetBranchAddress("W_mt", &W_mt, &b_W_mt);
   fChain->SetBranchAddress("W_mtMVA", &W_mtMVA, &b_W_mtMVA);
   fChain->SetBranchAddress("W_px", &W_px, &b_W_px);
   fChain->SetBranchAddress("W_py", &W_py, &b_W_py);
   fChain->SetBranchAddress("W_pz", &W_pz, &b_W_pz);
   fChain->SetBranchAddress("W_e", &W_e, &b_W_e);
   fChain->SetBranchAddress("W_pt", &W_pt, &b_W_pt);
   fChain->SetBranchAddress("W_et", &W_et, &b_W_et);
   fChain->SetBranchAddress("W_eta", &W_eta, &b_W_eta);
   fChain->SetBranchAddress("W_phi", &W_phi, &b_W_phi);
   fChain->SetBranchAddress("W_vx", &W_vx, &b_W_vx);
   fChain->SetBranchAddress("W_vy", &W_vy, &b_W_vy);
   fChain->SetBranchAddress("W_vz", &W_vz, &b_W_vz);
   fChain->SetBranchAddress("W_y", &W_y, &b_W_y);
   fChain->SetBranchAddress("W_numTightElectrons", &W_numTightElectrons, &b_W_numTightElectrons);
   fChain->SetBranchAddress("W_numLooseElectrons", &W_numLooseElectrons, &b_W_numLooseElectrons);
   fChain->SetBranchAddress("W_pzNu1", &W_pzNu1, &b_W_pzNu1);
   fChain->SetBranchAddress("W_pzNu2", &W_pzNu2, &b_W_pzNu2);
   fChain->SetBranchAddress("W_electron_px", &W_electron_px, &b_W_electron_px);
   fChain->SetBranchAddress("W_electron_py", &W_electron_py, &b_W_electron_py);
   fChain->SetBranchAddress("W_electron_pz", &W_electron_pz, &b_W_electron_pz);
   fChain->SetBranchAddress("W_electron_e", &W_electron_e, &b_W_electron_e);
   fChain->SetBranchAddress("W_electron_pt", &W_electron_pt, &b_W_electron_pt);
   fChain->SetBranchAddress("W_electron_et", &W_electron_et, &b_W_electron_et);
   fChain->SetBranchAddress("W_electron_eta", &W_electron_eta, &b_W_electron_eta);
   fChain->SetBranchAddress("W_electron_theta", &W_electron_theta, &b_W_electron_theta);
   fChain->SetBranchAddress("W_electron_phi", &W_electron_phi, &b_W_electron_phi);
   fChain->SetBranchAddress("W_electron_charge", &W_electron_charge, &b_W_electron_charge);
   fChain->SetBranchAddress("W_electron_vx", &W_electron_vx, &b_W_electron_vx);
   fChain->SetBranchAddress("W_electron_vy", &W_electron_vy, &b_W_electron_vy);
   fChain->SetBranchAddress("W_electron_vz", &W_electron_vz, &b_W_electron_vz);
   fChain->SetBranchAddress("W_electron_y", &W_electron_y, &b_W_electron_y);
   fChain->SetBranchAddress("W_electron_trackiso", &W_electron_trackiso, &b_W_electron_trackiso);
   fChain->SetBranchAddress("W_electron_hcaliso", &W_electron_hcaliso, &b_W_electron_hcaliso);
   fChain->SetBranchAddress("W_electron_ecaliso", &W_electron_ecaliso, &b_W_electron_ecaliso);
   fChain->SetBranchAddress("W_electron_classification", &W_electron_classification, &b_W_electron_classification);
   fChain->SetBranchAddress("W_electron_missingHits", &W_electron_missingHits, &b_W_electron_missingHits);
   fChain->SetBranchAddress("W_electron_dist", &W_electron_dist, &b_W_electron_dist);
   fChain->SetBranchAddress("W_electron_dcot", &W_electron_dcot, &b_W_electron_dcot);
   fChain->SetBranchAddress("W_electron_d0bsp", &W_electron_d0bsp, &b_W_electron_d0bsp);
   fChain->SetBranchAddress("W_electron_dz000", &W_electron_dz000, &b_W_electron_dz000);
   fChain->SetBranchAddress("W_electron_mvaTrigV0", &W_electron_mvaTrigV0, &b_W_electron_mvaTrigV0);
   fChain->SetBranchAddress("W_electron_mvaNonTrigV0", &W_electron_mvaNonTrigV0, &b_W_electron_mvaNonTrigV0);
   fChain->SetBranchAddress("W_electron_pfiso_chargedHadronIso", &W_electron_pfiso_chargedHadronIso, &b_W_electron_pfiso_chargedHadronIso);
   fChain->SetBranchAddress("W_electron_pfiso_photonIso", &W_electron_pfiso_photonIso, &b_W_electron_pfiso_photonIso);
   fChain->SetBranchAddress("W_electron_pfiso_neutralHadronIso", &W_electron_pfiso_neutralHadronIso, &b_W_electron_pfiso_neutralHadronIso);
   fChain->SetBranchAddress("W_electron_pfIsoEA", &W_electron_pfIsoEA, &b_W_electron_pfIsoEA);
   fChain->SetBranchAddress("W_H_mass_gen", &W_H_mass_gen, &b_W_H_mass_gen);
   fChain->SetBranchAddress("W_H_px_gen", &W_H_px_gen, &b_W_H_px_gen);
   fChain->SetBranchAddress("W_H_py_gen", &W_H_py_gen, &b_W_H_py_gen);
   fChain->SetBranchAddress("W_H_pz_gen", &W_H_pz_gen, &b_W_H_pz_gen);
   fChain->SetBranchAddress("W_H_e_gen", &W_H_e_gen, &b_W_H_e_gen);
   fChain->SetBranchAddress("W_H_pt_gen", &W_H_pt_gen, &b_W_H_pt_gen);
   fChain->SetBranchAddress("W_H_et_gen", &W_H_et_gen, &b_W_H_et_gen);
   fChain->SetBranchAddress("W_H_eta_gen", &W_H_eta_gen, &b_W_H_eta_gen);
   fChain->SetBranchAddress("W_H_phi_gen", &W_H_phi_gen, &b_W_H_phi_gen);
   fChain->SetBranchAddress("W_H_vx_gen", &W_H_vx_gen, &b_W_H_vx_gen);
   fChain->SetBranchAddress("W_H_vy_gen", &W_H_vy_gen, &b_W_H_vy_gen);
   fChain->SetBranchAddress("W_H_vz_gen", &W_H_vz_gen, &b_W_H_vz_gen);
   fChain->SetBranchAddress("W_H_y_gen", &W_H_y_gen, &b_W_H_y_gen);
   fChain->SetBranchAddress("W_H_Id_gen", &W_H_Id_gen, &b_W_H_Id_gen);
   fChain->SetBranchAddress("W_electron_px_gen", &W_electron_px_gen, &b_W_electron_px_gen);
   fChain->SetBranchAddress("W_electron_py_gen", &W_electron_py_gen, &b_W_electron_py_gen);
   fChain->SetBranchAddress("W_electron_pz_gen", &W_electron_pz_gen, &b_W_electron_pz_gen);
   fChain->SetBranchAddress("W_electron_e_gen", &W_electron_e_gen, &b_W_electron_e_gen);
   fChain->SetBranchAddress("W_electron_pt_gen", &W_electron_pt_gen, &b_W_electron_pt_gen);
   fChain->SetBranchAddress("W_electron_et_gen", &W_electron_et_gen, &b_W_electron_et_gen);
   fChain->SetBranchAddress("W_electron_eta_gen", &W_electron_eta_gen, &b_W_electron_eta_gen);
   fChain->SetBranchAddress("W_electron_theta_gen", &W_electron_theta_gen, &b_W_electron_theta_gen);
   fChain->SetBranchAddress("W_electron_phi_gen", &W_electron_phi_gen, &b_W_electron_phi_gen);
   fChain->SetBranchAddress("W_electron_charge_gen", &W_electron_charge_gen, &b_W_electron_charge_gen);
   fChain->SetBranchAddress("W_electron_vx_gen", &W_electron_vx_gen, &b_W_electron_vx_gen);
   fChain->SetBranchAddress("W_electron_vy_gen", &W_electron_vy_gen, &b_W_electron_vy_gen);
   fChain->SetBranchAddress("W_electron_vz_gen", &W_electron_vz_gen, &b_W_electron_vz_gen);
   fChain->SetBranchAddress("W_electron_y_gen", &W_electron_y_gen, &b_W_electron_y_gen);
   fChain->SetBranchAddress("W_neutrino_px_gen", &W_neutrino_px_gen, &b_W_neutrino_px_gen);
   fChain->SetBranchAddress("W_neutrino_py_gen", &W_neutrino_py_gen, &b_W_neutrino_py_gen);
   fChain->SetBranchAddress("W_neutrino_pz_gen", &W_neutrino_pz_gen, &b_W_neutrino_pz_gen);
   fChain->SetBranchAddress("W_neutrino_e_gen", &W_neutrino_e_gen, &b_W_neutrino_e_gen);
   fChain->SetBranchAddress("W_neutrino_pt_gen", &W_neutrino_pt_gen, &b_W_neutrino_pt_gen);
   fChain->SetBranchAddress("W_neutrino_et_gen", &W_neutrino_et_gen, &b_W_neutrino_et_gen);
   fChain->SetBranchAddress("W_neutrino_eta_gen", &W_neutrino_eta_gen, &b_W_neutrino_eta_gen);
   fChain->SetBranchAddress("W_neutrino_theta_gen", &W_neutrino_theta_gen, &b_W_neutrino_theta_gen);
   fChain->SetBranchAddress("W_neutrino_phi_gen", &W_neutrino_phi_gen, &b_W_neutrino_phi_gen);
   fChain->SetBranchAddress("W_neutrino_charge_gen", &W_neutrino_charge_gen, &b_W_neutrino_charge_gen);
   fChain->SetBranchAddress("W_neutrino_vx_gen", &W_neutrino_vx_gen, &b_W_neutrino_vx_gen);
   fChain->SetBranchAddress("W_neutrino_vy_gen", &W_neutrino_vy_gen, &b_W_neutrino_vy_gen);
   fChain->SetBranchAddress("W_neutrino_vz_gen", &W_neutrino_vz_gen, &b_W_neutrino_vz_gen);
   fChain->SetBranchAddress("W_neutrino_y_gen", &W_neutrino_y_gen, &b_W_neutrino_y_gen);
   fChain->SetBranchAddress("W_Parton_px[2]", W_Parton_px, &b_W_Parton_px);
   fChain->SetBranchAddress("W_Parton_py[2]", W_Parton_py, &b_W_Parton_py);
   fChain->SetBranchAddress("W_Parton_pz[2]", W_Parton_pz, &b_W_Parton_pz);
   fChain->SetBranchAddress("W_Parton_E[2]", W_Parton_E, &b_W_Parton_E);
   fChain->SetBranchAddress("W_Parton_pt[2]", W_Parton_pt, &b_W_Parton_pt);
   fChain->SetBranchAddress("W_Parton_et[2]", W_Parton_et, &b_W_Parton_et);
   fChain->SetBranchAddress("W_Parton_eta[2]", W_Parton_eta, &b_W_Parton_eta);
   fChain->SetBranchAddress("W_Parton_theta[2]", W_Parton_theta, &b_W_Parton_theta);
   fChain->SetBranchAddress("W_Parton_phi[2]", W_Parton_phi, &b_W_Parton_phi);
   fChain->SetBranchAddress("W_Parton_charge[2]", W_Parton_charge, &b_W_Parton_charge);
   fChain->SetBranchAddress("W_Parton_vx[2]", W_Parton_vx, &b_W_Parton_vx);
   fChain->SetBranchAddress("W_Parton_vy[2]", W_Parton_vy, &b_W_Parton_vy);
   fChain->SetBranchAddress("W_Parton_vz[2]", W_Parton_vz, &b_W_Parton_vz);
   fChain->SetBranchAddress("W_Parton_y[2]", W_Parton_y, &b_W_Parton_y);
   fChain->SetBranchAddress("W_Parton_Id[2]", W_Parton_Id, &b_W_Parton_Id);
   fChain->SetBranchAddress("W_Lepton_px", &W_Lepton_px, &b_W_Lepton_px);
   fChain->SetBranchAddress("W_Lepton_py", &W_Lepton_py, &b_W_Lepton_py);
   fChain->SetBranchAddress("W_Lepton_pz", &W_Lepton_pz, &b_W_Lepton_pz);
   fChain->SetBranchAddress("W_Lepton_E", &W_Lepton_E, &b_W_Lepton_E);
   fChain->SetBranchAddress("W_Lepton_pt", &W_Lepton_pt, &b_W_Lepton_pt);
   fChain->SetBranchAddress("W_Lepton_et", &W_Lepton_et, &b_W_Lepton_et);
   fChain->SetBranchAddress("W_Lepton_eta", &W_Lepton_eta, &b_W_Lepton_eta);
   fChain->SetBranchAddress("W_Lepton_theta", &W_Lepton_theta, &b_W_Lepton_theta);
   fChain->SetBranchAddress("W_Lepton_phi", &W_Lepton_phi, &b_W_Lepton_phi);
   fChain->SetBranchAddress("W_Lepton_charge", &W_Lepton_charge, &b_W_Lepton_charge);
   fChain->SetBranchAddress("W_Lepton_vx", &W_Lepton_vx, &b_W_Lepton_vx);
   fChain->SetBranchAddress("W_Lepton_vy", &W_Lepton_vy, &b_W_Lepton_vy);
   fChain->SetBranchAddress("W_Lepton_vz", &W_Lepton_vz, &b_W_Lepton_vz);
   fChain->SetBranchAddress("W_Lepton_y", &W_Lepton_y, &b_W_Lepton_y);
   fChain->SetBranchAddress("W_Lepton_Id", &W_Lepton_Id, &b_W_Lepton_Id);
   fChain->SetBranchAddress("W_Met_px", &W_Met_px, &b_W_Met_px);
   fChain->SetBranchAddress("W_Met_py", &W_Met_py, &b_W_Met_py);
   fChain->SetBranchAddress("W_Met_pz", &W_Met_pz, &b_W_Met_pz);
   fChain->SetBranchAddress("W_Met_E", &W_Met_E, &b_W_Met_E);
   fChain->SetBranchAddress("W_Met_pt", &W_Met_pt, &b_W_Met_pt);
   fChain->SetBranchAddress("W_Met_et", &W_Met_et, &b_W_Met_et);
   fChain->SetBranchAddress("W_Met_eta", &W_Met_eta, &b_W_Met_eta);
   fChain->SetBranchAddress("W_Met_theta", &W_Met_theta, &b_W_Met_theta);
   fChain->SetBranchAddress("W_Met_phi", &W_Met_phi, &b_W_Met_phi);
   fChain->SetBranchAddress("W_Met_charge", &W_Met_charge, &b_W_Met_charge);
   fChain->SetBranchAddress("W_Met_vx", &W_Met_vx, &b_W_Met_vx);
   fChain->SetBranchAddress("W_Met_vy", &W_Met_vy, &b_W_Met_vy);
   fChain->SetBranchAddress("W_Met_vz", &W_Met_vz, &b_W_Met_vz);
   fChain->SetBranchAddress("W_Met_y", &W_Met_y, &b_W_Met_y);
   fChain->SetBranchAddress("W_Met_Id", &W_Met_Id, &b_W_Met_Id);
   fChain->SetBranchAddress("event_runNo", &event_runNo, &b_event_runNo);
   fChain->SetBranchAddress("event_evtNo", &event_evtNo, &b_event_evtNo);
   fChain->SetBranchAddress("event_lumi", &event_lumi, &b_event_lumi);
   fChain->SetBranchAddress("event_bunch", &event_bunch, &b_event_bunch);
   fChain->SetBranchAddress("event_nPV", &event_nPV, &b_event_nPV);
   fChain->SetBranchAddress("event_met_pfmet", &event_met_pfmet, &b_event_met_pfmet);
   fChain->SetBranchAddress("event_met_pfsumet", &event_met_pfsumet, &b_event_met_pfsumet);
   fChain->SetBranchAddress("event_met_pfmetsignificance", &event_met_pfmetsignificance, &b_event_met_pfmetsignificance);
   fChain->SetBranchAddress("event_met_pfmetPhi", &event_met_pfmetPhi, &b_event_met_pfmetPhi);
   fChain->SetBranchAddress("event_metMVA_met", &event_metMVA_met, &b_event_metMVA_met);
   fChain->SetBranchAddress("event_metMVA_sumet", &event_metMVA_sumet, &b_event_metMVA_sumet);
   fChain->SetBranchAddress("event_metMVA_metsignificance", &event_metMVA_metsignificance, &b_event_metMVA_metsignificance);
   fChain->SetBranchAddress("event_metMVA_metPhi", &event_metMVA_metPhi, &b_event_metMVA_metPhi);
   fChain->SetBranchAddress("event_fastJetRho", &event_fastJetRho, &b_event_fastJetRho);
   fChain->SetBranchAddress("event_met_genmet", &event_met_genmet, &b_event_met_genmet);
   fChain->SetBranchAddress("event_met_gensumet", &event_met_gensumet, &b_event_met_gensumet);
   fChain->SetBranchAddress("event_met_genmetsignificance", &event_met_genmetsignificance, &b_event_met_genmetsignificance);
   fChain->SetBranchAddress("event_met_genmetPhi", &event_met_genmetPhi, &b_event_met_genmetPhi);
   fChain->SetBranchAddress("event_mcPU_totnvtx", &event_mcPU_totnvtx, &b_event_mcPU_totnvtx);
   fChain->SetBranchAddress("event_mcPU_trueInteractions", &event_mcPU_trueInteractions, &b_event_mcPU_trueInteractions);
   fChain->SetBranchAddress("event_mcPU_bx", event_mcPU_bx, &b_event_mcPU_bx);
   fChain->SetBranchAddress("event_mcPU_nvtx", event_mcPU_nvtx, &b_event_mcPU_nvtx);

   Notify();
}

Bool_t kanaelec_photon::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

Float_t kanaelec_photon::dRCalc(Float_t etaC, Float_t phiC, Float_t etaCrys, Float_t phiCrys){
    // Float_t ClusPhi = 0;
    // if (phiC>0) ClusPhi = phiC;
    // else ClusPhi = TMath::Pi()*2. + phiC;
    // Float_t CrysPhi = 0;
    // if (phiC>0) CrysPhi = phiCrys;
    // else CrysPhi = TMath::Pi()*2. + phiCrys;
    Float_t ClusPhi = phiC;
    Float_t CrysPhi = phiCrys;

    Float_t dphi = fabs(CrysPhi -ClusPhi);
    Float_t tempdphi=dphi;
    if (dphi > TMath::Pi()) tempdphi = TMath::Pi()*2. - dphi;
    dphi = tempdphi;
    Float_t deta = fabs(etaC - etaCrys);
    Float_t dR = sqrt(deta*deta + dphi*dphi);
    return dR;
}

void kanaelec_photon::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

#endif // #ifdef kanaelec_photon_cxx
