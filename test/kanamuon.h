//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Sep 15 15:25:00 2011 by ROOT version 5.27/06b
// from TTree WJet/V+jets Tree
// found on file: /uscms_data/d2/yangf/ana/WuvWjj/DataFile/MergFile/WmunuJets_DataAll_GoldenJSON_2p1invfb.root
//////////////////////////////////////////////////////////

#ifndef kanamuon_h
#define kanamuon_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>

#include "TLorentzVector.h"

class kanamuon {
   public :
      TTree          *fChain;   //!pointer to the analyzed TTree or TChain
      Int_t           fCurrent; //!current Tree number in a TChain

      // Declaration of leaf types
   Int_t           numPFCorJets;
   Int_t           numPFCorJetBTags;
   Float_t         JetPFCor_Et[8];
   Float_t         JetPFCor_Pt[8];
   Float_t         JetPFCor_Eta[8];
   Float_t         JetPFCor_Phi[8];
   Float_t         JetPFCor_Theta[8];
   Float_t         JetPFCor_Px[8];
   Float_t         JetPFCor_Py[8];
   Float_t         JetPFCor_Pz[8];
   Float_t         JetPFCor_E[8];
   Float_t         JetPFCor_Y[8];
   Float_t         JetPFCor_Mass[8];
   Float_t         JetPFCor_etaetaMoment[8];
   Float_t         JetPFCor_phiphiMoment[8];
   Float_t         JetPFCor_etaphiMoment[8];
   Float_t         JetPFCor_maxDistance[8];
   Int_t           JetPFCor_nConstituents[8];
   Float_t         JetPFCor_Area[8];
   Float_t         VplusPFCorJet_Mass[8];
   Float_t         JetPFCor_dphiBoson[8];
   Float_t         JetPFCor_detaBoson[8];
   Float_t         JetPFCor_dRBoson[8];
   Float_t         JetPFCor_dphiMET[8];
   Float_t         JetPFCor_bDiscriminator[8];
   Float_t         JetPFCor_bDiscriminatorSSVHE[8];
   Float_t         JetPFCor_bDiscriminatorTCHE[8];
   Float_t         JetPFCor_bDiscriminatorCSV[8];
   Float_t         JetPFCor_bDiscriminatorJP[8];
   Float_t         JetPFCor_bDiscriminatorSSVHP[8];
   Float_t         JetPFCor_bDiscriminatorTCHP[8];
   Float_t         JetPFCor_secVertexMass[8];
   Float_t         JetPFCor_ChargedHadronEnergy[8];
   Float_t         JetPFCor_ChargedHadronEnergyFrac[8];
   Float_t         JetPFCor_NeutralHadronEnergy[8];
   Float_t         JetPFCor_NeutralHadronEnergyFrac[8];
   Float_t         JetPFCor_ChargedEmEnergy[8];
   Float_t         JetPFCor_ChargedEmEnergyFrac[8];
   Float_t         JetPFCor_ChargedMuEnergy[8];
   Float_t         JetPFCor_ChargedMuEnergyFrac[8];
   Float_t         JetPFCor_NeutralEmEnergy[8];
   Float_t         JetPFCor_NeutralEmEnergyFrac[8];
   Int_t           JetPFCor_ChargedMultiplicity[8];
   Int_t           JetPFCor_NeutralMultiplicity[8];
   Int_t           JetPFCor_MuonMultiplicity[8];
   Float_t         JetPFCor_PhotonEnergy[8];
   Float_t         JetPFCor_PhotonEnergyFraction[8];
   Float_t         JetPFCor_ElectronEnergy[8];
   Float_t         JetPFCor_ElectronEnergyFraction[8];
   Float_t         JetPFCor_MuonEnergy[8];
   Float_t         JetPFCor_MuonEnergyFraction[8];
   Float_t         JetPFCor_HFHadronEnergy[8];
   Float_t         JetPFCor_HFHadronEnergyFraction[8];
   Float_t         JetPFCor_HFEMEnergy[8];
   Float_t         JetPFCor_HFEMEnergyFraction[8];
   Int_t           JetPFCor_ChargedHadronMultiplicity[8];
   Int_t           JetPFCor_NeutralHadronMultiplicity[8];
   Int_t           JetPFCor_PhotonMultiplicity[8];
   Int_t           JetPFCor_ElectronMultiplicity[8];
   Int_t           JetPFCor_HFHadronMultiplicity[8];
   Int_t           JetPFCor_HFEMMultiplicity[8];
   Float_t         JetPFCor_SumPtCands[8];
   Float_t         JetPFCor_SumPt2Cands[8];
   Float_t         JetPFCor_rmsCands[8];
   Float_t         JetPFCor_PtD[8];
   Float_t         JetPFCor_QGLikelihood[8];
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
   Float_t         colorCorrPull01PFCor;
   Float_t         colorCorrPull02PFCor;
   Float_t         colorCorrPull12PFCor;
   Float_t         colorCorrPull03PFCor;
   Float_t         colorCorrPull13PFCor;
   Float_t         colorCorrPull23PFCor;
   Float_t         colorCorrPull04PFCor;
   Float_t         colorCorrPull14PFCor;
   Float_t         colorCorrPull24PFCor;
   Float_t         colorCorrPull34PFCor;
   Float_t         colorCorrPull05PFCor;
   Float_t         colorCorrPull15PFCor;
   Float_t         colorCorrPull25PFCor;
   Float_t         colorCorrPull35PFCor;
   Float_t         colorCorrPull45PFCor;
   Float_t         cosThetaJ1HiggsCM_PFCor;
   Float_t         cosThetaJ2HiggsCM_PFCor;
   Float_t         cosThetaL1HiggsCM_PFCor;
   Float_t         cosThetaL2HiggsCM_PFCor;
   Float_t         cosThetaV1HiggsCM_PFCor;
   Float_t         cosThetaV2HiggsCM_PFCor;
   Bool_t          JetPFCor_isPileUpJetLoose[8];
   Bool_t          JetPFCor_isPileUpJetMedium[8];
   Bool_t          JetPFCor_isPileUpJetTight[8];
   Int_t           numPFCorVBFTagJets;
   Int_t           numPFCorVBFTagJetBTags;
   Float_t         JetPFCorVBFTag_Et[8];
   Float_t         JetPFCorVBFTag_Pt[8];
   Float_t         JetPFCorVBFTag_Eta[8];
   Float_t         JetPFCorVBFTag_Phi[8];
   Float_t         JetPFCorVBFTag_Theta[8];
   Float_t         JetPFCorVBFTag_Px[8];
   Float_t         JetPFCorVBFTag_Py[8];
   Float_t         JetPFCorVBFTag_Pz[8];
   Float_t         JetPFCorVBFTag_E[8];
   Float_t         JetPFCorVBFTag_Y[8];
   Float_t         JetPFCorVBFTag_Mass[8];
   Float_t         JetPFCorVBFTag_etaetaMoment[8];
   Float_t         JetPFCorVBFTag_phiphiMoment[8];
   Float_t         JetPFCorVBFTag_etaphiMoment[8];
   Float_t         JetPFCorVBFTag_maxDistance[8];
   Int_t           JetPFCorVBFTag_nConstituents[8];
   Float_t         JetPFCorVBFTag_Area[8];
   Float_t         VplusPFCorVBFTagJet_Mass[8];
   Float_t         JetPFCorVBFTag_dphiBoson[8];
   Float_t         JetPFCorVBFTag_detaBoson[8];
   Float_t         JetPFCorVBFTag_dRBoson[8];
   Float_t         JetPFCorVBFTag_dphiMET[8];
   Float_t         JetPFCorVBFTag_bDiscriminator[8];
   Float_t         JetPFCorVBFTag_bDiscriminatorSSVHE[8];
   Float_t         JetPFCorVBFTag_bDiscriminatorTCHE[8];
   Float_t         JetPFCorVBFTag_bDiscriminatorCSV[8];
   Float_t         JetPFCorVBFTag_bDiscriminatorJP[8];
   Float_t         JetPFCorVBFTag_bDiscriminatorSSVHP[8];
   Float_t         JetPFCorVBFTag_bDiscriminatorTCHP[8];
   Float_t         JetPFCorVBFTag_secVertexMass[8];
   Float_t         JetPFCorVBFTag_ChargedHadronEnergy[8];
   Float_t         JetPFCorVBFTag_ChargedHadronEnergyFrac[8];
   Float_t         JetPFCorVBFTag_NeutralHadronEnergy[8];
   Float_t         JetPFCorVBFTag_NeutralHadronEnergyFrac[8];
   Float_t         JetPFCorVBFTag_ChargedEmEnergy[8];
   Float_t         JetPFCorVBFTag_ChargedEmEnergyFrac[8];
   Float_t         JetPFCorVBFTag_ChargedMuEnergy[8];
   Float_t         JetPFCorVBFTag_ChargedMuEnergyFrac[8];
   Float_t         JetPFCorVBFTag_NeutralEmEnergy[8];
   Float_t         JetPFCorVBFTag_NeutralEmEnergyFrac[8];
   Int_t           JetPFCorVBFTag_ChargedMultiplicity[8];
   Int_t           JetPFCorVBFTag_NeutralMultiplicity[8];
   Int_t           JetPFCorVBFTag_MuonMultiplicity[8];
   Float_t         JetPFCorVBFTag_PhotonEnergy[8];
   Float_t         JetPFCorVBFTag_PhotonEnergyFraction[8];
   Float_t         JetPFCorVBFTag_ElectronEnergy[8];
   Float_t         JetPFCorVBFTag_ElectronEnergyFraction[8];
   Float_t         JetPFCorVBFTag_MuonEnergy[8];
   Float_t         JetPFCorVBFTag_MuonEnergyFraction[8];
   Float_t         JetPFCorVBFTag_HFHadronEnergy[8];
   Float_t         JetPFCorVBFTag_HFHadronEnergyFraction[8];
   Float_t         JetPFCorVBFTag_HFEMEnergy[8];
   Float_t         JetPFCorVBFTag_HFEMEnergyFraction[8];
   Int_t           JetPFCorVBFTag_ChargedHadronMultiplicity[8];
   Int_t           JetPFCorVBFTag_NeutralHadronMultiplicity[8];
   Int_t           JetPFCorVBFTag_PhotonMultiplicity[8];
   Int_t           JetPFCorVBFTag_ElectronMultiplicity[8];
   Int_t           JetPFCorVBFTag_HFHadronMultiplicity[8];
   Int_t           JetPFCorVBFTag_HFEMMultiplicity[8];
   Float_t         JetPFCorVBFTag_SumPtCands[8];
   Float_t         JetPFCorVBFTag_SumPt2Cands[8];
   Float_t         JetPFCorVBFTag_rmsCands[8];
   Float_t         JetPFCorVBFTag_PtD[8];
   Float_t         JetPFCorVBFTag_QGLikelihood[8];
   Float_t         MassV2j_PFCorVBFTag_MVAMET;
   Float_t         MassV2j_PFCorVBFTag;
   Float_t         MassV3j_PFCorVBFTag;
   Float_t         MassV4j_PFCorVBFTag;
   Float_t         MassV5j_PFCorVBFTag;
   Float_t         MassV6j_PFCorVBFTag;
   Float_t         Mass2j_PFCorVBFTag;
   Float_t         Mass3j_PFCorVBFTag;
   Float_t         Mass4j_PFCorVBFTag;
   Float_t         Mass5j_PFCorVBFTag;
   Float_t         Mass6j_PFCorVBFTag;
   Float_t         cosJacksonAngleV2j_PFCorVBFTag;
   Float_t         cosJacksonAngle2j_PFCorVBFTag;
   Float_t         cosJacksonAngleV3j_PFCorVBFTag;
   Float_t         cosJacksonAngle3j12_PFCorVBFTag;
   Float_t         cosJacksonAngle3j23_PFCorVBFTag;
   Float_t         cosJacksonAngle3j31_PFCorVBFTag;
   Float_t         cosphiDecayPlane_PFCorVBFTag;
   Float_t         cosThetaLnu_PFCorVBFTag;
   Float_t         cosThetaJJ_PFCorVBFTag;
   Float_t         colorCorrPull01PFCorVBFTag;
   Float_t         colorCorrPull02PFCorVBFTag;
   Float_t         colorCorrPull12PFCorVBFTag;
   Float_t         colorCorrPull03PFCorVBFTag;
   Float_t         colorCorrPull13PFCorVBFTag;
   Float_t         colorCorrPull23PFCorVBFTag;
   Float_t         colorCorrPull04PFCorVBFTag;
   Float_t         colorCorrPull14PFCorVBFTag;
   Float_t         colorCorrPull24PFCorVBFTag;
   Float_t         colorCorrPull34PFCorVBFTag;
   Float_t         colorCorrPull05PFCorVBFTag;
   Float_t         colorCorrPull15PFCorVBFTag;
   Float_t         colorCorrPull25PFCorVBFTag;
   Float_t         colorCorrPull35PFCorVBFTag;
   Float_t         colorCorrPull45PFCorVBFTag;
   Float_t         cosThetaJ1HiggsCM_PFCorVBFTag;
   Float_t         cosThetaJ2HiggsCM_PFCorVBFTag;
   Float_t         cosThetaL1HiggsCM_PFCorVBFTag;
   Float_t         cosThetaL2HiggsCM_PFCorVBFTag;
   Float_t         cosThetaV1HiggsCM_PFCorVBFTag;
   Float_t         cosThetaV2HiggsCM_PFCorVBFTag;
   Bool_t          JetPFCorVBFTag_isPileUpJetLoose[8];
   Bool_t          JetPFCorVBFTag_isPileUpJetMedium[8];
   Bool_t          JetPFCorVBFTag_isPileUpJetTight[8];
   Float_t         GroomedJet_AK5_pt_uncorr[6];
   Float_t         GroomedJet_AK5_mass_uncorr[6];
   Float_t         GroomedJet_AK5_mass_tr_uncorr[6];
   Float_t         GroomedJet_AK5_mass_ft_uncorr[6];
   Float_t         GroomedJet_AK5_mass_pr_uncorr[6];
   Float_t         GroomedJet_AK5_tau2tau1[6];
   Float_t         GroomedJet_AK5_tau1[6];
   Float_t         GroomedJet_AK5_tau2[6];
   Float_t         GroomedJet_AK5_tau3[6];
   Float_t         GroomedJet_AK5_tau4[6];
   Float_t         GroomedJet_AK5_massdrop_pr_uncorr[6];
   Float_t         GroomedJet_AK5_pt[6];
   Float_t         GroomedJet_AK5_eta[6];
   Float_t         GroomedJet_AK5_phi[6];
   Float_t         GroomedJet_AK5_e[6];
   Float_t         GroomedJet_AK5_pt_tr_uncorr[6];
   Float_t         GroomedJet_AK5_pt_tr[6];
   Float_t         GroomedJet_AK5_eta_tr[6];
   Float_t         GroomedJet_AK5_phi_tr[6];
   Float_t         GroomedJet_AK5_e_tr[6];
   Float_t         GroomedJet_AK5_pt_ft_uncorr[6];
   Float_t         GroomedJet_AK5_pt_ft[6];
   Float_t         GroomedJet_AK5_eta_ft[6];
   Float_t         GroomedJet_AK5_phi_ft[6];
   Float_t         GroomedJet_AK5_e_ft[6];
   Float_t         GroomedJet_AK5_pt_pr_uncorr[6];
   Float_t         GroomedJet_AK5_pt_pr[6];
   Float_t         GroomedJet_AK5_eta_pr[6];
   Float_t         GroomedJet_AK5_phi_pr[6];
   Float_t         GroomedJet_AK5_e_pr[6];
   Float_t         GroomedJet_AK5_prsubjet1_px[6];
   Float_t         GroomedJet_AK5_prsubjet1_py[6];
   Float_t         GroomedJet_AK5_prsubjet1_pz[6];
   Float_t         GroomedJet_AK5_prsubjet1_e[6];
   Float_t         GroomedJet_AK5_prsubjet2_px[6];
   Float_t         GroomedJet_AK5_prsubjet2_py[6];
   Float_t         GroomedJet_AK5_prsubjet2_pz[6];
   Float_t         GroomedJet_AK5_prsubjet2_e[6];
   Float_t         GroomedJet_AK5_mass[6];
   Float_t         GroomedJet_AK5_mass_tr[6];
   Float_t         GroomedJet_AK5_mass_ft[6];
   Float_t         GroomedJet_AK5_mass_pr[6];
   Float_t         GroomedJet_AK5_massdrop_pr[6];
   Float_t         GroomedJet_AK5_area[6];
   Float_t         GroomedJet_AK5_area_tr[6];
   Float_t         GroomedJet_AK5_area_ft[6];
   Float_t         GroomedJet_AK5_area_pr[6];
   Float_t         GroomedJet_AK5_jetconstituents[6];
   Float_t         GroomedJet_AK5_jetcharge[6];
   Float_t         GroomedJet_AK5_rcores[11][6];
   Float_t         GroomedJet_AK5_ptcores[11][6];
   Float_t         GroomedJet_AK5_planarflow[11][6];
   Float_t         GroomedJet_AK5_qjetmass[50];
   Float_t         GroomedJet_AK5_qjetmassdrop[50];
   Float_t         GroomedJet_AK5_constituents0_eta[100];
   Float_t         GroomedJet_AK5_constituents0_phi[100];
   Float_t         GroomedJet_AK5_constituents0_e[100];
   Int_t           GroomedJet_AK5_nconstituents0;
   Float_t         GroomedJet_AK5_constituents0pr_eta[100];
   Float_t         GroomedJet_AK5_constituents0pr_phi[100];
   Float_t         GroomedJet_AK5_constituents0pr_e[100];
   Int_t           GroomedJet_AK5_nconstituents0pr;
   Float_t         GroomedJet_AK7_pt_uncorr[6];
   Float_t         GroomedJet_AK7_mass_uncorr[6];
   Float_t         GroomedJet_AK7_mass_tr_uncorr[6];
   Float_t         GroomedJet_AK7_mass_ft_uncorr[6];
   Float_t         GroomedJet_AK7_mass_pr_uncorr[6];
   Float_t         GroomedJet_AK7_tau2tau1[6];
   Float_t         GroomedJet_AK7_tau1[6];
   Float_t         GroomedJet_AK7_tau2[6];
   Float_t         GroomedJet_AK7_tau3[6];
   Float_t         GroomedJet_AK7_tau4[6];
   Float_t         GroomedJet_AK7_massdrop_pr_uncorr[6];
   Float_t         GroomedJet_AK7_pt[6];
   Float_t         GroomedJet_AK7_eta[6];
   Float_t         GroomedJet_AK7_phi[6];
   Float_t         GroomedJet_AK7_e[6];
   Float_t         GroomedJet_AK7_pt_tr_uncorr[6];
   Float_t         GroomedJet_AK7_pt_tr[6];
   Float_t         GroomedJet_AK7_eta_tr[6];
   Float_t         GroomedJet_AK7_phi_tr[6];
   Float_t         GroomedJet_AK7_e_tr[6];
   Float_t         GroomedJet_AK7_pt_ft_uncorr[6];
   Float_t         GroomedJet_AK7_pt_ft[6];
   Float_t         GroomedJet_AK7_eta_ft[6];
   Float_t         GroomedJet_AK7_phi_ft[6];
   Float_t         GroomedJet_AK7_e_ft[6];
   Float_t         GroomedJet_AK7_pt_pr_uncorr[6];
   Float_t         GroomedJet_AK7_pt_pr[6];
   Float_t         GroomedJet_AK7_eta_pr[6];
   Float_t         GroomedJet_AK7_phi_pr[6];
   Float_t         GroomedJet_AK7_e_pr[6];
   Float_t         GroomedJet_AK7_prsubjet1_px[6];
   Float_t         GroomedJet_AK7_prsubjet1_py[6];
   Float_t         GroomedJet_AK7_prsubjet1_pz[6];
   Float_t         GroomedJet_AK7_prsubjet1_e[6];
   Float_t         GroomedJet_AK7_prsubjet2_px[6];
   Float_t         GroomedJet_AK7_prsubjet2_py[6];
   Float_t         GroomedJet_AK7_prsubjet2_pz[6];
   Float_t         GroomedJet_AK7_prsubjet2_e[6];
   Float_t         GroomedJet_AK7_mass[6];
   Float_t         GroomedJet_AK7_mass_tr[6];
   Float_t         GroomedJet_AK7_mass_ft[6];
   Float_t         GroomedJet_AK7_mass_pr[6];
   Float_t         GroomedJet_AK7_massdrop_pr[6];
   Float_t         GroomedJet_AK7_area[6];
   Float_t         GroomedJet_AK7_area_tr[6];
   Float_t         GroomedJet_AK7_area_ft[6];
   Float_t         GroomedJet_AK7_area_pr[6];
   Float_t         GroomedJet_AK7_jetconstituents[6];
   Float_t         GroomedJet_AK7_jetcharge[6];
   Float_t         GroomedJet_AK7_rcores[11][6];
   Float_t         GroomedJet_AK7_ptcores[11][6];
   Float_t         GroomedJet_AK7_planarflow[11][6];
   Float_t         GroomedJet_AK7_qjetmass[50];
   Float_t         GroomedJet_AK7_qjetmassdrop[50];
   Float_t         GroomedJet_AK7_constituents0_eta[100];
   Float_t         GroomedJet_AK7_constituents0_phi[100];
   Float_t         GroomedJet_AK7_constituents0_e[100];
   Int_t           GroomedJet_AK7_nconstituents0;
   Float_t         GroomedJet_AK7_constituents0pr_eta[100];
   Float_t         GroomedJet_AK7_constituents0pr_phi[100];
   Float_t         GroomedJet_AK7_constituents0pr_e[100];
   Int_t           GroomedJet_AK7_nconstituents0pr;
   Float_t         GroomedJet_CA8_pt_uncorr[6];
   Float_t         GroomedJet_CA8_mass_uncorr[6];
   Float_t         GroomedJet_CA8_mass_tr_uncorr[6];
   Float_t         GroomedJet_CA8_mass_ft_uncorr[6];
   Float_t         GroomedJet_CA8_mass_pr_uncorr[6];
   Float_t         GroomedJet_CA8_tau2tau1[6];
   Float_t         GroomedJet_CA8_tau1[6];
   Float_t         GroomedJet_CA8_tau2[6];
   Float_t         GroomedJet_CA8_tau3[6];
   Float_t         GroomedJet_CA8_tau4[6];
   Float_t         GroomedJet_CA8_massdrop_pr_uncorr[6];
   Float_t         GroomedJet_CA8_pt[6];
   Float_t         GroomedJet_CA8_eta[6];
   Float_t         GroomedJet_CA8_phi[6];
   Float_t         GroomedJet_CA8_e[6];
   Float_t         GroomedJet_CA8_pt_tr_uncorr[6];
   Float_t         GroomedJet_CA8_pt_tr[6];
   Float_t         GroomedJet_CA8_eta_tr[6];
   Float_t         GroomedJet_CA8_phi_tr[6];
   Float_t         GroomedJet_CA8_e_tr[6];
   Float_t         GroomedJet_CA8_pt_ft_uncorr[6];
   Float_t         GroomedJet_CA8_pt_ft[6];
   Float_t         GroomedJet_CA8_eta_ft[6];
   Float_t         GroomedJet_CA8_phi_ft[6];
   Float_t         GroomedJet_CA8_e_ft[6];
   Float_t         GroomedJet_CA8_pt_pr_uncorr[6];
   Float_t         GroomedJet_CA8_pt_pr[6];
   Float_t         GroomedJet_CA8_eta_pr[6];
   Float_t         GroomedJet_CA8_phi_pr[6];
   Float_t         GroomedJet_CA8_e_pr[6];
   Float_t         GroomedJet_CA8_prsubjet1_px[6];
   Float_t         GroomedJet_CA8_prsubjet1_py[6];
   Float_t         GroomedJet_CA8_prsubjet1_pz[6];
   Float_t         GroomedJet_CA8_prsubjet1_e[6];
   Float_t         GroomedJet_CA8_prsubjet2_px[6];
   Float_t         GroomedJet_CA8_prsubjet2_py[6];
   Float_t         GroomedJet_CA8_prsubjet2_pz[6];
   Float_t         GroomedJet_CA8_prsubjet2_e[6];
   Float_t         GroomedJet_CA8_mass[6];
   Float_t         GroomedJet_CA8_mass_tr[6];
   Float_t         GroomedJet_CA8_mass_ft[6];
   Float_t         GroomedJet_CA8_mass_pr[6];
   Float_t         GroomedJet_CA8_massdrop_pr[6];
   Float_t         GroomedJet_CA8_area[6];
   Float_t         GroomedJet_CA8_area_tr[6];
   Float_t         GroomedJet_CA8_area_ft[6];
   Float_t         GroomedJet_CA8_area_pr[6];
   Float_t         GroomedJet_CA8_jetconstituents[6];
   Float_t         GroomedJet_CA8_jetcharge[6];
   Float_t         GroomedJet_CA8_rcores[11][6];
   Float_t         GroomedJet_CA8_ptcores[11][6];
   Float_t         GroomedJet_CA8_planarflow[11][6];
   Float_t         GroomedJet_CA8_qjetmass[50];
   Float_t         GroomedJet_CA8_qjetmassdrop[50];
   Float_t         GroomedJet_CA8_constituents0_eta[100];
   Float_t         GroomedJet_CA8_constituents0_phi[100];
   Float_t         GroomedJet_CA8_constituents0_e[100];
   Int_t           GroomedJet_CA8_nconstituents0;
   Float_t         GroomedJet_CA8_constituents0pr_eta[100];
   Float_t         GroomedJet_CA8_constituents0pr_phi[100];
   Float_t         GroomedJet_CA8_constituents0pr_e[100];
   Int_t           GroomedJet_CA8_nconstituents0pr;
   Float_t         GenGroomedJet_AK5_pt_uncorr[6];
   Float_t         GenGroomedJet_AK5_mass_uncorr[6];
   Float_t         GenGroomedJet_AK5_mass_tr_uncorr[6];
   Float_t         GenGroomedJet_AK5_mass_ft_uncorr[6];
   Float_t         GenGroomedJet_AK5_mass_pr_uncorr[6];
   Float_t         GenGroomedJet_AK5_tau2tau1[6];
   Float_t         GenGroomedJet_AK5_tau1[6];
   Float_t         GenGroomedJet_AK5_tau2[6];
   Float_t         GenGroomedJet_AK5_tau3[6];
   Float_t         GenGroomedJet_AK5_tau4[6];
   Float_t         GenGroomedJet_AK5_massdrop_pr_uncorr[6];
   Float_t         GenGroomedJet_AK5_pt[6];
   Float_t         GenGroomedJet_AK5_eta[6];
   Float_t         GenGroomedJet_AK5_phi[6];
   Float_t         GenGroomedJet_AK5_e[6];
   Float_t         GenGroomedJet_AK5_pt_tr_uncorr[6];
   Float_t         GenGroomedJet_AK5_pt_tr[6];
   Float_t         GenGroomedJet_AK5_eta_tr[6];
   Float_t         GenGroomedJet_AK5_phi_tr[6];
   Float_t         GenGroomedJet_AK5_e_tr[6];
   Float_t         GenGroomedJet_AK5_pt_ft_uncorr[6];
   Float_t         GenGroomedJet_AK5_pt_ft[6];
   Float_t         GenGroomedJet_AK5_eta_ft[6];
   Float_t         GenGroomedJet_AK5_phi_ft[6];
   Float_t         GenGroomedJet_AK5_e_ft[6];
   Float_t         GenGroomedJet_AK5_pt_pr_uncorr[6];
   Float_t         GenGroomedJet_AK5_pt_pr[6];
   Float_t         GenGroomedJet_AK5_eta_pr[6];
   Float_t         GenGroomedJet_AK5_phi_pr[6];
   Float_t         GenGroomedJet_AK5_e_pr[6];
   Float_t         GenGroomedJet_AK5_prsubjet1_px[6];
   Float_t         GenGroomedJet_AK5_prsubjet1_py[6];
   Float_t         GenGroomedJet_AK5_prsubjet1_pz[6];
   Float_t         GenGroomedJet_AK5_prsubjet1_e[6];
   Float_t         GenGroomedJet_AK5_prsubjet2_px[6];
   Float_t         GenGroomedJet_AK5_prsubjet2_py[6];
   Float_t         GenGroomedJet_AK5_prsubjet2_pz[6];
   Float_t         GenGroomedJet_AK5_prsubjet2_e[6];
   Float_t         GenGroomedJet_AK5_mass[6];
   Float_t         GenGroomedJet_AK5_mass_tr[6];
   Float_t         GenGroomedJet_AK5_mass_ft[6];
   Float_t         GenGroomedJet_AK5_mass_pr[6];
   Float_t         GenGroomedJet_AK5_massdrop_pr[6];
   Float_t         GenGroomedJet_AK5_area[6];
   Float_t         GenGroomedJet_AK5_area_tr[6];
   Float_t         GenGroomedJet_AK5_area_ft[6];
   Float_t         GenGroomedJet_AK5_area_pr[6];
   Float_t         GenGroomedJet_AK5_jetconstituents[6];
   Float_t         GenGroomedJet_AK5_jetcharge[6];
   Float_t         GenGroomedJet_AK5_rcores[11][6];
   Float_t         GenGroomedJet_AK5_ptcores[11][6];
   Float_t         GenGroomedJet_AK5_planarflow[11][6];
   Float_t         GenGroomedJet_AK5_qjetmass[50];
   Float_t         GenGroomedJet_AK5_qjetmassdrop[50];
   Float_t         GenGroomedJet_AK5_constituents0_eta[100];
   Float_t         GenGroomedJet_AK5_constituents0_phi[100];
   Float_t         GenGroomedJet_AK5_constituents0_e[100];
   Int_t           GenGroomedJet_AK5_nconstituents0;
   Float_t         GenGroomedJet_AK5_constituents0pr_eta[100];
   Float_t         GenGroomedJet_AK5_constituents0pr_phi[100];
   Float_t         GenGroomedJet_AK5_constituents0pr_e[100];
   Int_t           GenGroomedJet_AK5_nconstituents0pr;
   Float_t         GenGroomedJet_AK7_pt_uncorr[6];
   Float_t         GenGroomedJet_AK7_mass_uncorr[6];
   Float_t         GenGroomedJet_AK7_mass_tr_uncorr[6];
   Float_t         GenGroomedJet_AK7_mass_ft_uncorr[6];
   Float_t         GenGroomedJet_AK7_mass_pr_uncorr[6];
   Float_t         GenGroomedJet_AK7_tau2tau1[6];
   Float_t         GenGroomedJet_AK7_tau1[6];
   Float_t         GenGroomedJet_AK7_tau2[6];
   Float_t         GenGroomedJet_AK7_tau3[6];
   Float_t         GenGroomedJet_AK7_tau4[6];
   Float_t         GenGroomedJet_AK7_massdrop_pr_uncorr[6];
   Float_t         GenGroomedJet_AK7_pt[6];
   Float_t         GenGroomedJet_AK7_eta[6];
   Float_t         GenGroomedJet_AK7_phi[6];
   Float_t         GenGroomedJet_AK7_e[6];
   Float_t         GenGroomedJet_AK7_pt_tr_uncorr[6];
   Float_t         GenGroomedJet_AK7_pt_tr[6];
   Float_t         GenGroomedJet_AK7_eta_tr[6];
   Float_t         GenGroomedJet_AK7_phi_tr[6];
   Float_t         GenGroomedJet_AK7_e_tr[6];
   Float_t         GenGroomedJet_AK7_pt_ft_uncorr[6];
   Float_t         GenGroomedJet_AK7_pt_ft[6];
   Float_t         GenGroomedJet_AK7_eta_ft[6];
   Float_t         GenGroomedJet_AK7_phi_ft[6];
   Float_t         GenGroomedJet_AK7_e_ft[6];
   Float_t         GenGroomedJet_AK7_pt_pr_uncorr[6];
   Float_t         GenGroomedJet_AK7_pt_pr[6];
   Float_t         GenGroomedJet_AK7_eta_pr[6];
   Float_t         GenGroomedJet_AK7_phi_pr[6];
   Float_t         GenGroomedJet_AK7_e_pr[6];
   Float_t         GenGroomedJet_AK7_prsubjet1_px[6];
   Float_t         GenGroomedJet_AK7_prsubjet1_py[6];
   Float_t         GenGroomedJet_AK7_prsubjet1_pz[6];
   Float_t         GenGroomedJet_AK7_prsubjet1_e[6];
   Float_t         GenGroomedJet_AK7_prsubjet2_px[6];
   Float_t         GenGroomedJet_AK7_prsubjet2_py[6];
   Float_t         GenGroomedJet_AK7_prsubjet2_pz[6];
   Float_t         GenGroomedJet_AK7_prsubjet2_e[6];
   Float_t         GenGroomedJet_AK7_mass[6];
   Float_t         GenGroomedJet_AK7_mass_tr[6];
   Float_t         GenGroomedJet_AK7_mass_ft[6];
   Float_t         GenGroomedJet_AK7_mass_pr[6];
   Float_t         GenGroomedJet_AK7_massdrop_pr[6];
   Float_t         GenGroomedJet_AK7_area[6];
   Float_t         GenGroomedJet_AK7_area_tr[6];
   Float_t         GenGroomedJet_AK7_area_ft[6];
   Float_t         GenGroomedJet_AK7_area_pr[6];
   Float_t         GenGroomedJet_AK7_jetconstituents[6];
   Float_t         GenGroomedJet_AK7_jetcharge[6];
   Float_t         GenGroomedJet_AK7_rcores[11][6];
   Float_t         GenGroomedJet_AK7_ptcores[11][6];
   Float_t         GenGroomedJet_AK7_planarflow[11][6];
   Float_t         GenGroomedJet_AK7_qjetmass[50];
   Float_t         GenGroomedJet_AK7_qjetmassdrop[50];
   Float_t         GenGroomedJet_AK7_constituents0_eta[100];
   Float_t         GenGroomedJet_AK7_constituents0_phi[100];
   Float_t         GenGroomedJet_AK7_constituents0_e[100];
   Int_t           GenGroomedJet_AK7_nconstituents0;
   Float_t         GenGroomedJet_AK7_constituents0pr_eta[100];
   Float_t         GenGroomedJet_AK7_constituents0pr_phi[100];
   Float_t         GenGroomedJet_AK7_constituents0pr_e[100];
   Int_t           GenGroomedJet_AK7_nconstituents0pr;
   Float_t         GenGroomedJet_CA8_pt_uncorr[6];
   Float_t         GenGroomedJet_CA8_mass_uncorr[6];
   Float_t         GenGroomedJet_CA8_mass_tr_uncorr[6];
   Float_t         GenGroomedJet_CA8_mass_ft_uncorr[6];
   Float_t         GenGroomedJet_CA8_mass_pr_uncorr[6];
   Float_t         GenGroomedJet_CA8_tau2tau1[6];
   Float_t         GenGroomedJet_CA8_tau1[6];
   Float_t         GenGroomedJet_CA8_tau2[6];
   Float_t         GenGroomedJet_CA8_tau3[6];
   Float_t         GenGroomedJet_CA8_tau4[6];
   Float_t         GenGroomedJet_CA8_massdrop_pr_uncorr[6];
   Float_t         GenGroomedJet_CA8_pt[6];
   Float_t         GenGroomedJet_CA8_eta[6];
   Float_t         GenGroomedJet_CA8_phi[6];
   Float_t         GenGroomedJet_CA8_e[6];
   Float_t         GenGroomedJet_CA8_pt_tr_uncorr[6];
   Float_t         GenGroomedJet_CA8_pt_tr[6];
   Float_t         GenGroomedJet_CA8_eta_tr[6];
   Float_t         GenGroomedJet_CA8_phi_tr[6];
   Float_t         GenGroomedJet_CA8_e_tr[6];
   Float_t         GenGroomedJet_CA8_pt_ft_uncorr[6];
   Float_t         GenGroomedJet_CA8_pt_ft[6];
   Float_t         GenGroomedJet_CA8_eta_ft[6];
   Float_t         GenGroomedJet_CA8_phi_ft[6];
   Float_t         GenGroomedJet_CA8_e_ft[6];
   Float_t         GenGroomedJet_CA8_pt_pr_uncorr[6];
   Float_t         GenGroomedJet_CA8_pt_pr[6];
   Float_t         GenGroomedJet_CA8_eta_pr[6];
   Float_t         GenGroomedJet_CA8_phi_pr[6];
   Float_t         GenGroomedJet_CA8_e_pr[6];
   Float_t         GenGroomedJet_CA8_prsubjet1_px[6];
   Float_t         GenGroomedJet_CA8_prsubjet1_py[6];
   Float_t         GenGroomedJet_CA8_prsubjet1_pz[6];
   Float_t         GenGroomedJet_CA8_prsubjet1_e[6];
   Float_t         GenGroomedJet_CA8_prsubjet2_px[6];
   Float_t         GenGroomedJet_CA8_prsubjet2_py[6];
   Float_t         GenGroomedJet_CA8_prsubjet2_pz[6];
   Float_t         GenGroomedJet_CA8_prsubjet2_e[6];
   Float_t         GenGroomedJet_CA8_mass[6];
   Float_t         GenGroomedJet_CA8_mass_tr[6];
   Float_t         GenGroomedJet_CA8_mass_ft[6];
   Float_t         GenGroomedJet_CA8_mass_pr[6];
   Float_t         GenGroomedJet_CA8_massdrop_pr[6];
   Float_t         GenGroomedJet_CA8_area[6];
   Float_t         GenGroomedJet_CA8_area_tr[6];
   Float_t         GenGroomedJet_CA8_area_ft[6];
   Float_t         GenGroomedJet_CA8_area_pr[6];
   Float_t         GenGroomedJet_CA8_jetconstituents[6];
   Float_t         GenGroomedJet_CA8_jetcharge[6];
   Float_t         GenGroomedJet_CA8_rcores[11][6];
   Float_t         GenGroomedJet_CA8_ptcores[11][6];
   Float_t         GenGroomedJet_CA8_planarflow[11][6];
   Float_t         GenGroomedJet_CA8_qjetmass[50];
   Float_t         GenGroomedJet_CA8_qjetmassdrop[50];
   Float_t         GenGroomedJet_CA8_constituents0_eta[100];
   Float_t         GenGroomedJet_CA8_constituents0_phi[100];
   Float_t         GenGroomedJet_CA8_constituents0_e[100];
   Int_t           GenGroomedJet_CA8_nconstituents0;
   Float_t         GenGroomedJet_CA8_constituents0pr_eta[100];
   Float_t         GenGroomedJet_CA8_constituents0pr_phi[100];
   Float_t         GenGroomedJet_CA8_constituents0pr_e[100];
   Int_t           GenGroomedJet_CA8_nconstituents0pr;
   Int_t           numGenJets;
   Int_t           numGenJetBTags;
   Float_t         JetGen_Et[8];
   Float_t         JetGen_Pt[8];
   Float_t         JetGen_Eta[8];
   Float_t         JetGen_Phi[8];
   Float_t         JetGen_Theta[8];
   Float_t         JetGen_Px[8];
   Float_t         JetGen_Py[8];
   Float_t         JetGen_Pz[8];
   Float_t         JetGen_E[8];
   Float_t         JetGen_Y[8];
   Float_t         JetGen_Mass[8];
   Float_t         JetGen_etaetaMoment[8];
   Float_t         JetGen_phiphiMoment[8];
   Float_t         JetGen_etaphiMoment[8];
   Float_t         JetGen_maxDistance[8];
   Int_t           JetGen_nConstituents[8];
   Float_t         JetGen_Area[8];
   Float_t         VplusGenJet_Mass[8];
   Float_t         JetGen_dphiBoson[8];
   Float_t         JetGen_detaBoson[8];
   Float_t         JetGen_dRBoson[8];
   Float_t         JetGen_dphiMET[8];
   Float_t         JetGen_bDiscriminator[8];
   Float_t         JetGen_bDiscriminatorSSVHE[8];
   Float_t         JetGen_bDiscriminatorTCHE[8];
   Float_t         JetGen_bDiscriminatorCSV[8];
   Float_t         JetGen_bDiscriminatorJP[8];
   Float_t         JetGen_bDiscriminatorSSVHP[8];
   Float_t         JetGen_bDiscriminatorTCHP[8];
   Float_t         JetGen_secVertexMass[8];
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
   Float_t         Photon_Et[5];   //[NumPhotons]
   Float_t         Photon_E[5];   //[NumPhotons]
   Float_t         Photon_Eta[5];   //[NumPhotons]
   Float_t         Photon_Phi[5];   //[NumPhotons]
   Float_t         Photon_Theta[5];   //[NumPhotons]
   Float_t         Photon_Px[5];   //[NumPhotons]
   Float_t         Photon_Py[5];   //[NumPhotons]
   Float_t         Photon_Pz[5];   //[NumPhotons]
   Float_t         Photon_Vx[5];   //[NumPhotons]
   Float_t         Photon_Vy[5];   //[NumPhotons]
   Float_t         Photon_Vz[5];   //[NumPhotons]
   Float_t         Photon_SC_Et[5];   //[NumPhotons]
   Float_t         Photon_SC_E[5];   //[NumPhotons]
   Float_t         Photon_SC_Eta[5];   //[NumPhotons]
   Float_t         Photon_SC_Phi[5];   //[NumPhotons]
   Float_t         Photon_SC_Theta[5];   //[NumPhotons]
   Float_t         Photon_SC_x[5];   //[NumPhotons]
   Float_t         Photon_SC_y[5];   //[NumPhotons]
   Float_t         Photon_SC_z[5];   //[NumPhotons]
   Float_t         PFisocharged03[5];   //[NumPhotons]
   Float_t         PFisophoton03[5];   //[NumPhotons]
   Float_t         PFisoneutral03[5];   //[NumPhotons]
   Float_t         trkSumPtHollowConeDR04_Photon11[5];   //[NumPhotons]
   Float_t         ecalRecHitSumEtConeDR04_Photon11[5];   //[NumPhotons]
   Float_t         hcalTowerSumEtConeDR04_Photon11[5];   //[NumPhotons]
   Float_t         Photon_HoverE[5];   //[NumPhotons]
   Float_t         Photon_HoverE2011[5];   //[NumPhotons]
   Float_t         Photon_SigmaIetaIeta[5];   //[NumPhotons]
   Int_t           Photon_hasPixelSeed[5];   //[NumPhotons]
   Int_t           Photon_passElecVeto[5];   //[NumPhotons]
   Int_t           Photon_Id2011[5];   //[NumPhotons]
   Int_t           Photon_Id2012[5];   //[NumPhotons]
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
   Float_t         W_pzNu1;
   Float_t         W_pzNu2;
   Float_t         W_muon_px;
   Float_t         W_muon_py;
   Float_t         W_muon_pz;
   Float_t         W_muon_e;
   Float_t         W_muon_pt;
   Float_t         W_muon_et;
   Float_t         W_muon_eta;
   Float_t         W_muon_theta;
   Float_t         W_muon_phi;
   Int_t           W_muon_charge;
   Float_t         W_muon_vx;
   Float_t         W_muon_vy;
   Float_t         W_muon_vz;
   Float_t         W_muon_y;
   Float_t         W_muon_trackiso;
   Float_t         W_muon_hcaliso;
   Float_t         W_muon_ecaliso;
   Int_t           W_muon_type;
   Int_t           W_muon_numberOfChambers;
   Int_t           W_muon_numberOfMatches;
   Float_t         W_muon_d0bsp;
   Float_t         W_muon_dz000;
   Float_t         W_muon_dzPV;
   Float_t         W_muon_pfiso_sumChargedHadronPt;
   Float_t         W_muon_pfiso_sumChargedParticlePt;
   Float_t         W_muon_pfiso_sumNeutralHadronEt;
   Float_t         W_muon_pfiso_sumPhotonEt;
   Float_t         W_muon_pfiso_sumPUPt;
   Float_t         W_Photon_pt_gen;
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
   Float_t         W_muon_px_gen;
   Float_t         W_muon_py_gen;
   Float_t         W_muon_pz_gen;
   Float_t         W_muon_e_gen;
   Float_t         W_muon_pt_gen;
   Float_t         W_muon_et_gen;
   Float_t         W_muon_eta_gen;
   Float_t         W_muon_theta_gen;
   Float_t         W_muon_phi_gen;
   Int_t           W_muon_charge_gen;
   Float_t         W_muon_vx_gen;
   Float_t         W_muon_vy_gen;
   Float_t         W_muon_vz_gen;
   Float_t         W_muon_y_gen;
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
   Float_t         W_tParton_px[2];
   Float_t         W_tParton_py[2];
   Float_t         W_tParton_pz[2];
   Float_t         W_tParton_E[2];
   Float_t         W_tParton_pt[2];
   Float_t         W_tParton_et[2];
   Float_t         W_tParton_eta[2];
   Float_t         W_tParton_theta[2];
   Float_t         W_tParton_phi[2];
   Int_t           W_tParton_charge[2];
   Float_t         W_tParton_vx[2];
   Float_t         W_tParton_vy[2];
   Float_t         W_tParton_vz[2];
   Float_t         W_tParton_y[2];
   Int_t           W_tParton_Id[2];
   Float_t         W_tLepton_px;
   Float_t         W_tLepton_py;
   Float_t         W_tLepton_pz;
   Float_t         W_tLepton_E;
   Float_t         W_tLepton_pt;
   Float_t         W_tLepton_et;
   Float_t         W_tLepton_eta;
   Float_t         W_tLepton_theta;
   Float_t         W_tLepton_phi;
   Int_t           W_tLepton_charge;
   Float_t         W_tLepton_vx;
   Float_t         W_tLepton_vy;
   Float_t         W_tLepton_vz;
   Float_t         W_tLepton_y;
   Int_t           W_tLepton_Id;
   Float_t         W_tMet_px;
   Float_t         W_tMet_py;
   Float_t         W_tMet_pz;
   Float_t         W_tMet_E;
   Float_t         W_tMet_pt;
   Float_t         W_tMet_et;
   Float_t         W_tMet_eta;
   Float_t         W_tMet_theta;
   Float_t         W_tMet_phi;
   Int_t           W_tMet_charge;
   Float_t         W_tMet_vx;
   Float_t         W_tMet_vy;
   Float_t         W_tMet_vz;
   Float_t         W_tMet_y;
   Int_t           W_tMet_Id;
   Float_t         W_tb_px;
   Float_t         W_tb_py;
   Float_t         W_tb_pz;
   Float_t         W_tb_E;
   Float_t         W_tb_pt;
   Float_t         W_tb_et;
   Float_t         W_tb_eta;
   Float_t         W_tb_theta;
   Float_t         W_tb_phi;
   Int_t           W_tb_charge;
   Float_t         W_tb_vx;
   Float_t         W_tb_vy;
   Float_t         W_tb_vz;
   Float_t         W_tb_y;
   Int_t           W_tb_Id;
   Float_t         W_tbbar_px;
   Float_t         W_tbbar_py;
   Float_t         W_tbbar_pz;
   Float_t         W_tbbar_E;
   Float_t         W_tbbar_pt;
   Float_t         W_tbbar_et;
   Float_t         W_tbbar_eta;
   Float_t         W_tbbar_theta;
   Float_t         W_tbbar_phi;
   Int_t           W_tbbar_charge;
   Float_t         W_tbbar_vx;
   Float_t         W_tbbar_vy;
   Float_t         W_tbbar_vz;
   Float_t         W_tbbar_y;
   Int_t           W_tbbar_Id;
   Float_t         W_Hb_px;
   Float_t         W_Hb_py;
   Float_t         W_Hb_pz;
   Float_t         W_Hb_E;
   Float_t         W_Hb_pt;
   Float_t         W_Hb_et;
   Float_t         W_Hb_eta;
   Float_t         W_Hb_theta;
   Float_t         W_Hb_phi;
   Int_t           W_Hb_charge;
   Float_t         W_Hb_vx;
   Float_t         W_Hb_vy;
   Float_t         W_Hb_vz;
   Float_t         W_Hb_y;
   Int_t           W_Hb_Id;
   Float_t         W_Hbbar_px;
   Float_t         W_Hbbar_py;
   Float_t         W_Hbbar_pz;
   Float_t         W_Hbbar_E;
   Float_t         W_Hbbar_pt;
   Float_t         W_Hbbar_et;
   Float_t         W_Hbbar_eta;
   Float_t         W_Hbbar_theta;
   Float_t         W_Hbbar_phi;
   Int_t           W_Hbbar_charge;
   Float_t         W_Hbbar_vx;
   Float_t         W_Hbbar_vy;
   Float_t         W_Hbbar_vz;
   Float_t         W_Hbbar_y;
   Int_t           W_Hbbar_Id;
   Float_t         W_TagQuark_px[2];
   Float_t         W_TagQuark_py[2];
   Float_t         W_TagQuark_pz[2];
   Float_t         W_TagQuark_E[2];
   Float_t         W_TagQuark_pt[2];
   Float_t         W_TagQuark_et[2];
   Float_t         W_TagQuark_eta[2];
   Float_t         W_TagQuark_theta[2];
   Float_t         W_TagQuark_phi[2];
   Int_t           W_TagQuark_charge[2];
   Float_t         W_TagQuark_vx[2];
   Float_t         W_TagQuark_vy[2];
   Float_t         W_TagQuark_vz[2];
   Float_t         W_TagQuark_y[2];
   Int_t           W_TagQuark_Id[2];
   Float_t         W_EWKW_px;
   Float_t         W_EWKW_py;
   Float_t         W_EWKW_pz;
   Float_t         W_EWKW_E;
   Float_t         W_EWKW_pt;
   Float_t         W_EWKW_et;
   Float_t         W_EWKW_eta;
   Float_t         W_EWKW_theta;
   Float_t         W_EWKW_phi;
   Int_t           W_EWKW_charge;
   Float_t         W_EWKW_vx;
   Float_t         W_EWKW_vy;
   Float_t         W_EWKW_vz;
   Float_t         W_EWKW_y;
   Int_t           W_EWKW_Id;
   Float_t         W_EWKTagQuark_px[2];
   Float_t         W_EWKTagQuark_py[2];
   Float_t         W_EWKTagQuark_pz[2];
   Float_t         W_EWKTagQuark_E[2];
   Float_t         W_EWKTagQuark_pt[2];
   Float_t         W_EWKTagQuark_et[2];
   Float_t         W_EWKTagQuark_eta[2];
   Float_t         W_EWKTagQuark_theta[2];
   Float_t         W_EWKTagQuark_phi[2];
   Int_t           W_EWKTagQuark_charge[2];
   Float_t         W_EWKTagQuark_vx[2];
   Float_t         W_EWKTagQuark_vy[2];
   Float_t         W_EWKTagQuark_vz[2];
   Float_t         W_EWKTagQuark_y[2];
   Int_t           W_EWKTagQuark_Id[2];
   Int_t           W_nParton_Winclusive;
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
   TBranch        *b_colorCorrPull01PFCor;   //!
   TBranch        *b_colorCorrPull02PFCor;   //!
   TBranch        *b_colorCorrPull12PFCor;   //!
   TBranch        *b_colorCorrPull03PFCor;   //!
   TBranch        *b_colorCorrPull13PFCor;   //!
   TBranch        *b_colorCorrPull23PFCor;   //!
   TBranch        *b_colorCorrPull04PFCor;   //!
   TBranch        *b_colorCorrPull14PFCor;   //!
   TBranch        *b_colorCorrPull24PFCor;   //!
   TBranch        *b_colorCorrPull34PFCor;   //!
   TBranch        *b_colorCorrPull05PFCor;   //!
   TBranch        *b_colorCorrPull15PFCor;   //!
   TBranch        *b_colorCorrPull25PFCor;   //!
   TBranch        *b_colorCorrPull35PFCor;   //!
   TBranch        *b_colorCorrPull45PFCor;   //!
   TBranch        *b_cosThetaJ1HiggsCM_PFCor;   //!
   TBranch        *b_cosThetaJ2HiggsCM_PFCor;   //!
   TBranch        *b_cosThetaL1HiggsCM_PFCor;   //!
   TBranch        *b_cosThetaL2HiggsCM_PFCor;   //!
   TBranch        *b_cosThetaV1HiggsCM_PFCor;   //!
   TBranch        *b_cosThetaV2HiggsCM_PFCor;   //!
   TBranch        *b_JetPFCor_isPileUpJetLoose;   //!
   TBranch        *b_JetPFCor_isPileUpJetMedium;   //!
   TBranch        *b_JetPFCor_isPileUpJetTight;   //!
   TBranch        *b_numPFCorVBFTagJets;   //!
   TBranch        *b_numPFCorVBFTagJetBTags;   //!
   TBranch        *b_JetPFCorVBFTag_Et;   //!
   TBranch        *b_JetPFCorVBFTag_Pt;   //!
   TBranch        *b_JetPFCorVBFTag_Eta;   //!
   TBranch        *b_JetPFCorVBFTag_Phi;   //!
   TBranch        *b_JetPFCorVBFTag_Theta;   //!
   TBranch        *b_JetPFCorVBFTag_Px;   //!
   TBranch        *b_JetPFCorVBFTag_Py;   //!
   TBranch        *b_JetPFCorVBFTag_Pz;   //!
   TBranch        *b_JetPFCorVBFTag_E;   //!
   TBranch        *b_JetPFCorVBFTag_Y;   //!
   TBranch        *b_JetPFCorVBFTag_Mass;   //!
   TBranch        *b_JetPFCorVBFTag_etaetaMoment;   //!
   TBranch        *b_JetPFCorVBFTag_phiphiMoment;   //!
   TBranch        *b_JetPFCorVBFTag_etaphiMoment;   //!
   TBranch        *b_JetPFCorVBFTag_maxDistance;   //!
   TBranch        *b_JetPFCorVBFTag_nConstituents;   //!
   TBranch        *b_JetPFCorVBFTag_Area;   //!
   TBranch        *b_VplusPFCorVBFTagJet_Mass;   //!
   TBranch        *b_JetPFCorVBFTag_dphiBoson;   //!
   TBranch        *b_JetPFCorVBFTag_detaBoson;   //!
   TBranch        *b_JetPFCorVBFTag_dRBoson;   //!
   TBranch        *b_JetPFCorVBFTag_dphiMET;   //!
   TBranch        *b_JetPFCorVBFTag_bDiscriminator;   //!
   TBranch        *b_JetPFCorVBFTag_bDiscriminatorSSVHE;   //!
   TBranch        *b_JetPFCorVBFTag_bDiscriminatorTCHE;   //!
   TBranch        *b_JetPFCorVBFTag_bDiscriminatorCSV;   //!
   TBranch        *b_JetPFCorVBFTag_bDiscriminatorJP;   //!
   TBranch        *b_JetPFCorVBFTag_bDiscriminatorSSVHP;   //!
   TBranch        *b_JetPFCorVBFTag_bDiscriminatorTCHP;   //!
   TBranch        *b_JetPFCorVBFTag_secVertexMass;   //!
   TBranch        *b_JetPFCorVBFTag_ChargedHadronEnergy;   //!
   TBranch        *b_JetPFCorVBFTag_ChargedHadronEnergyFrac;   //!
   TBranch        *b_JetPFCorVBFTag_NeutralHadronEnergy;   //!
   TBranch        *b_JetPFCorVBFTag_NeutralHadronEnergyFrac;   //!
   TBranch        *b_JetPFCorVBFTag_ChargedEmEnergy;   //!
   TBranch        *b_JetPFCorVBFTag_ChargedEmEnergyFrac;   //!
   TBranch        *b_JetPFCorVBFTag_ChargedMuEnergy;   //!
   TBranch        *b_JetPFCorVBFTag_ChargedMuEnergyFrac;   //!
   TBranch        *b_JetPFCorVBFTag_NeutralEmEnergy;   //!
   TBranch        *b_JetPFCorVBFTag_NeutralEmEnergyFrac;   //!
   TBranch        *b_JetPFCorVBFTag_ChargedMultiplicity;   //!
   TBranch        *b_JetPFCorVBFTag_NeutralMultiplicity;   //!
   TBranch        *b_JetPFCorVBFTag_MuonMultiplicity;   //!
   TBranch        *b_JetPFCorVBFTag_PhotonEnergy;   //!
   TBranch        *b_JetPFCorVBFTag_PhotonEnergyFraction;   //!
   TBranch        *b_JetPFCorVBFTag_ElectronEnergy;   //!
   TBranch        *b_JetPFCorVBFTag_ElectronEnergyFraction;   //!
   TBranch        *b_JetPFCorVBFTag_MuonEnergy;   //!
   TBranch        *b_JetPFCorVBFTag_MuonEnergyFraction;   //!
   TBranch        *b_JetPFCorVBFTag_HFHadronEnergy;   //!
   TBranch        *b_JetPFCorVBFTag_HFHadronEnergyFraction;   //!
   TBranch        *b_JetPFCorVBFTag_HFEMEnergy;   //!
   TBranch        *b_JetPFCorVBFTag_HFEMEnergyFraction;   //!
   TBranch        *b_JetPFCorVBFTag_ChargedHadronMultiplicity;   //!
   TBranch        *b_JetPFCorVBFTag_NeutralHadronMultiplicity;   //!
   TBranch        *b_JetPFCorVBFTag_PhotonMultiplicity;   //!
   TBranch        *b_JetPFCorVBFTag_ElectronMultiplicity;   //!
   TBranch        *b_JetPFCorVBFTag_HFHadronMultiplicity;   //!
   TBranch        *b_JetPFCorVBFTag_HFEMMultiplicity;   //!
   TBranch        *b_JetPFCorVBFTag_SumPtCands;   //!
   TBranch        *b_JetPFCorVBFTag_SumPt2Cands;   //!
   TBranch        *b_JetPFCorVBFTag_rmsCands;   //!
   TBranch        *b_JetPFCorVBFTag_PtD;   //!
   TBranch        *b_JetPFCorVBFTag_QGLikelihood;   //!
   TBranch        *b_MassV2j_PFCorVBFTag_MVAMET;   //!
   TBranch        *b_MassV2j_PFCorVBFTag;   //!
   TBranch        *b_MassV3j_PFCorVBFTag;   //!
   TBranch        *b_MassV4j_PFCorVBFTag;   //!
   TBranch        *b_MassV5j_PFCorVBFTag;   //!
   TBranch        *b_MassV6j_PFCorVBFTag;   //!
   TBranch        *b_Mass2j_PFCorVBFTag;   //!
   TBranch        *b_Mass3j_PFCorVBFTag;   //!
   TBranch        *b_Mass4j_PFCorVBFTag;   //!
   TBranch        *b_Mass5j_PFCorVBFTag;   //!
   TBranch        *b_Mass6j_PFCorVBFTag;   //!
   TBranch        *b_cosJacksonAngleV2j_PFCorVBFTag;   //!
   TBranch        *b_cosJacksonAngle2j_PFCorVBFTag;   //!
   TBranch        *b_cosJacksonAngleV3j_PFCorVBFTag;   //!
   TBranch        *b_cosJacksonAngle3j12_PFCorVBFTag;   //!
   TBranch        *b_cosJacksonAngle3j23_PFCorVBFTag;   //!
   TBranch        *b_cosJacksonAngle3j31_PFCorVBFTag;   //!
   TBranch        *b_cosphiDecayPlane_PFCorVBFTag;   //!
   TBranch        *b_cosThetaLnu_PFCorVBFTag;   //!
   TBranch        *b_cosThetaJJ_PFCorVBFTag;   //!
   TBranch        *b_colorCorrPull01PFCorVBFTag;   //!
   TBranch        *b_colorCorrPull02PFCorVBFTag;   //!
   TBranch        *b_colorCorrPull12PFCorVBFTag;   //!
   TBranch        *b_colorCorrPull03PFCorVBFTag;   //!
   TBranch        *b_colorCorrPull13PFCorVBFTag;   //!
   TBranch        *b_colorCorrPull23PFCorVBFTag;   //!
   TBranch        *b_colorCorrPull04PFCorVBFTag;   //!
   TBranch        *b_colorCorrPull14PFCorVBFTag;   //!
   TBranch        *b_colorCorrPull24PFCorVBFTag;   //!
   TBranch        *b_colorCorrPull34PFCorVBFTag;   //!
   TBranch        *b_colorCorrPull05PFCorVBFTag;   //!
   TBranch        *b_colorCorrPull15PFCorVBFTag;   //!
   TBranch        *b_colorCorrPull25PFCorVBFTag;   //!
   TBranch        *b_colorCorrPull35PFCorVBFTag;   //!
   TBranch        *b_colorCorrPull45PFCorVBFTag;   //!
   TBranch        *b_cosThetaJ1HiggsCM_PFCorVBFTag;   //!
   TBranch        *b_cosThetaJ2HiggsCM_PFCorVBFTag;   //!
   TBranch        *b_cosThetaL1HiggsCM_PFCorVBFTag;   //!
   TBranch        *b_cosThetaL2HiggsCM_PFCorVBFTag;   //!
   TBranch        *b_cosThetaV1HiggsCM_PFCorVBFTag;   //!
   TBranch        *b_cosThetaV2HiggsCM_PFCorVBFTag;   //!
   TBranch        *b_JetPFCorVBFTag_isPileUpJetLoose;   //!
   TBranch        *b_JetPFCorVBFTag_isPileUpJetMedium;   //!
   TBranch        *b_JetPFCorVBFTag_isPileUpJetTight;   //!
   TBranch        *b_GroomedJet_AK5_pt_uncorr;   //!
   TBranch        *b_GroomedJet_AK5_mass_uncorr;   //!
   TBranch        *b_GroomedJet_AK5_mass_tr_uncorr;   //!
   TBranch        *b_GroomedJet_AK5_mass_ft_uncorr;   //!
   TBranch        *b_GroomedJet_AK5_mass_pr_uncorr;   //!
   TBranch        *b_GroomedJet_AK5_tau2tau1;   //!
   TBranch        *b_GroomedJet_AK5_tau1;   //!
   TBranch        *b_GroomedJet_AK5_tau2;   //!
   TBranch        *b_GroomedJet_AK5_tau3;   //!
   TBranch        *b_GroomedJet_AK5_tau4;   //!
   TBranch        *b_GroomedJet_AK5_massdrop_pr_uncorr;   //!
   TBranch        *b_GroomedJet_AK5_pt;   //!
   TBranch        *b_GroomedJet_AK5_eta;   //!
   TBranch        *b_GroomedJet_AK5_phi;   //!
   TBranch        *b_GroomedJet_AK5_e;   //!
   TBranch        *b_GroomedJet_AK5_pt_tr_uncorr;   //!
   TBranch        *b_GroomedJet_AK5_pt_tr;   //!
   TBranch        *b_GroomedJet_AK5_eta_tr;   //!
   TBranch        *b_GroomedJet_AK5_phi_tr;   //!
   TBranch        *b_GroomedJet_AK5_e_tr;   //!
   TBranch        *b_GroomedJet_AK5_pt_ft_uncorr;   //!
   TBranch        *b_GroomedJet_AK5_pt_ft;   //!
   TBranch        *b_GroomedJet_AK5_eta_ft;   //!
   TBranch        *b_GroomedJet_AK5_phi_ft;   //!
   TBranch        *b_GroomedJet_AK5_e_ft;   //!
   TBranch        *b_GroomedJet_AK5_pt_pr_uncorr;   //!
   TBranch        *b_GroomedJet_AK5_pt_pr;   //!
   TBranch        *b_GroomedJet_AK5_eta_pr;   //!
   TBranch        *b_GroomedJet_AK5_phi_pr;   //!
   TBranch        *b_GroomedJet_AK5_e_pr;   //!
   TBranch        *b_GroomedJet_AK5_prsubjet1_px;   //!
   TBranch        *b_GroomedJet_AK5_prsubjet1_py;   //!
   TBranch        *b_GroomedJet_AK5_prsubjet1_pz;   //!
   TBranch        *b_GroomedJet_AK5_prsubjet1_e;   //!
   TBranch        *b_GroomedJet_AK5_prsubjet2_px;   //!
   TBranch        *b_GroomedJet_AK5_prsubjet2_py;   //!
   TBranch        *b_GroomedJet_AK5_prsubjet2_pz;   //!
   TBranch        *b_GroomedJet_AK5_prsubjet2_e;   //!
   TBranch        *b_GroomedJet_AK5_mass;   //!
   TBranch        *b_GroomedJet_AK5_mass_tr;   //!
   TBranch        *b_GroomedJet_AK5_mass_ft;   //!
   TBranch        *b_GroomedJet_AK5_mass_pr;   //!
   TBranch        *b_GroomedJet_AK5_massdrop_pr;   //!
   TBranch        *b_GroomedJet_AK5_area;   //!
   TBranch        *b_GroomedJet_AK5_area_tr;   //!
   TBranch        *b_GroomedJet_AK5_area_ft;   //!
   TBranch        *b_GroomedJet_AK5_area_pr;   //!
   TBranch        *b_GroomedJet_AK5_jetconstituents;   //!
   TBranch        *b_GroomedJet_AK5_jetcharge;   //!
   TBranch        *b_GroomedJet_AK5_rcores;   //!
   TBranch        *b_GroomedJet_AK5_ptcores;   //!
   TBranch        *b_GroomedJet_AK5_planarflow;   //!
   TBranch        *b_GroomedJet_AK5_qjetmass;   //!
   TBranch        *b_GroomedJet_AK5_qjetmassdrop;   //!
   TBranch        *b_GroomedJet_AK5_constituents0_eta;   //!
   TBranch        *b_GroomedJet_AK5_constituents0_phi;   //!
   TBranch        *b_GroomedJet_AK5_constituents0_e;   //!
   TBranch        *b_GroomedJet_AK5_nconstituents0;   //!
   TBranch        *b_GroomedJet_AK5_constituents0pr_eta;   //!
   TBranch        *b_GroomedJet_AK5_constituents0pr_phi;   //!
   TBranch        *b_GroomedJet_AK5_constituents0pr_e;   //!
   TBranch        *b_GroomedJet_AK5_nconstituents0pr;   //!
   TBranch        *b_GroomedJet_AK7_pt_uncorr;   //!
   TBranch        *b_GroomedJet_AK7_mass_uncorr;   //!
   TBranch        *b_GroomedJet_AK7_mass_tr_uncorr;   //!
   TBranch        *b_GroomedJet_AK7_mass_ft_uncorr;   //!
   TBranch        *b_GroomedJet_AK7_mass_pr_uncorr;   //!
   TBranch        *b_GroomedJet_AK7_tau2tau1;   //!
   TBranch        *b_GroomedJet_AK7_tau1;   //!
   TBranch        *b_GroomedJet_AK7_tau2;   //!
   TBranch        *b_GroomedJet_AK7_tau3;   //!
   TBranch        *b_GroomedJet_AK7_tau4;   //!
   TBranch        *b_GroomedJet_AK7_massdrop_pr_uncorr;   //!
   TBranch        *b_GroomedJet_AK7_pt;   //!
   TBranch        *b_GroomedJet_AK7_eta;   //!
   TBranch        *b_GroomedJet_AK7_phi;   //!
   TBranch        *b_GroomedJet_AK7_e;   //!
   TBranch        *b_GroomedJet_AK7_pt_tr_uncorr;   //!
   TBranch        *b_GroomedJet_AK7_pt_tr;   //!
   TBranch        *b_GroomedJet_AK7_eta_tr;   //!
   TBranch        *b_GroomedJet_AK7_phi_tr;   //!
   TBranch        *b_GroomedJet_AK7_e_tr;   //!
   TBranch        *b_GroomedJet_AK7_pt_ft_uncorr;   //!
   TBranch        *b_GroomedJet_AK7_pt_ft;   //!
   TBranch        *b_GroomedJet_AK7_eta_ft;   //!
   TBranch        *b_GroomedJet_AK7_phi_ft;   //!
   TBranch        *b_GroomedJet_AK7_e_ft;   //!
   TBranch        *b_GroomedJet_AK7_pt_pr_uncorr;   //!
   TBranch        *b_GroomedJet_AK7_pt_pr;   //!
   TBranch        *b_GroomedJet_AK7_eta_pr;   //!
   TBranch        *b_GroomedJet_AK7_phi_pr;   //!
   TBranch        *b_GroomedJet_AK7_e_pr;   //!
   TBranch        *b_GroomedJet_AK7_prsubjet1_px;   //!
   TBranch        *b_GroomedJet_AK7_prsubjet1_py;   //!
   TBranch        *b_GroomedJet_AK7_prsubjet1_pz;   //!
   TBranch        *b_GroomedJet_AK7_prsubjet1_e;   //!
   TBranch        *b_GroomedJet_AK7_prsubjet2_px;   //!
   TBranch        *b_GroomedJet_AK7_prsubjet2_py;   //!
   TBranch        *b_GroomedJet_AK7_prsubjet2_pz;   //!
   TBranch        *b_GroomedJet_AK7_prsubjet2_e;   //!
   TBranch        *b_GroomedJet_AK7_mass;   //!
   TBranch        *b_GroomedJet_AK7_mass_tr;   //!
   TBranch        *b_GroomedJet_AK7_mass_ft;   //!
   TBranch        *b_GroomedJet_AK7_mass_pr;   //!
   TBranch        *b_GroomedJet_AK7_massdrop_pr;   //!
   TBranch        *b_GroomedJet_AK7_area;   //!
   TBranch        *b_GroomedJet_AK7_area_tr;   //!
   TBranch        *b_GroomedJet_AK7_area_ft;   //!
   TBranch        *b_GroomedJet_AK7_area_pr;   //!
   TBranch        *b_GroomedJet_AK7_jetconstituents;   //!
   TBranch        *b_GroomedJet_AK7_jetcharge;   //!
   TBranch        *b_GroomedJet_AK7_rcores;   //!
   TBranch        *b_GroomedJet_AK7_ptcores;   //!
   TBranch        *b_GroomedJet_AK7_planarflow;   //!
   TBranch        *b_GroomedJet_AK7_qjetmass;   //!
   TBranch        *b_GroomedJet_AK7_qjetmassdrop;   //!
   TBranch        *b_GroomedJet_AK7_constituents0_eta;   //!
   TBranch        *b_GroomedJet_AK7_constituents0_phi;   //!
   TBranch        *b_GroomedJet_AK7_constituents0_e;   //!
   TBranch        *b_GroomedJet_AK7_nconstituents0;   //!
   TBranch        *b_GroomedJet_AK7_constituents0pr_eta;   //!
   TBranch        *b_GroomedJet_AK7_constituents0pr_phi;   //!
   TBranch        *b_GroomedJet_AK7_constituents0pr_e;   //!
   TBranch        *b_GroomedJet_AK7_nconstituents0pr;   //!
   TBranch        *b_GroomedJet_CA8_pt_uncorr;   //!
   TBranch        *b_GroomedJet_CA8_mass_uncorr;   //!
   TBranch        *b_GroomedJet_CA8_mass_tr_uncorr;   //!
   TBranch        *b_GroomedJet_CA8_mass_ft_uncorr;   //!
   TBranch        *b_GroomedJet_CA8_mass_pr_uncorr;   //!
   TBranch        *b_GroomedJet_CA8_tau2tau1;   //!
   TBranch        *b_GroomedJet_CA8_tau1;   //!
   TBranch        *b_GroomedJet_CA8_tau2;   //!
   TBranch        *b_GroomedJet_CA8_tau3;   //!
   TBranch        *b_GroomedJet_CA8_tau4;   //!
   TBranch        *b_GroomedJet_CA8_massdrop_pr_uncorr;   //!
   TBranch        *b_GroomedJet_CA8_pt;   //!
   TBranch        *b_GroomedJet_CA8_eta;   //!
   TBranch        *b_GroomedJet_CA8_phi;   //!
   TBranch        *b_GroomedJet_CA8_e;   //!
   TBranch        *b_GroomedJet_CA8_pt_tr_uncorr;   //!
   TBranch        *b_GroomedJet_CA8_pt_tr;   //!
   TBranch        *b_GroomedJet_CA8_eta_tr;   //!
   TBranch        *b_GroomedJet_CA8_phi_tr;   //!
   TBranch        *b_GroomedJet_CA8_e_tr;   //!
   TBranch        *b_GroomedJet_CA8_pt_ft_uncorr;   //!
   TBranch        *b_GroomedJet_CA8_pt_ft;   //!
   TBranch        *b_GroomedJet_CA8_eta_ft;   //!
   TBranch        *b_GroomedJet_CA8_phi_ft;   //!
   TBranch        *b_GroomedJet_CA8_e_ft;   //!
   TBranch        *b_GroomedJet_CA8_pt_pr_uncorr;   //!
   TBranch        *b_GroomedJet_CA8_pt_pr;   //!
   TBranch        *b_GroomedJet_CA8_eta_pr;   //!
   TBranch        *b_GroomedJet_CA8_phi_pr;   //!
   TBranch        *b_GroomedJet_CA8_e_pr;   //!
   TBranch        *b_GroomedJet_CA8_prsubjet1_px;   //!
   TBranch        *b_GroomedJet_CA8_prsubjet1_py;   //!
   TBranch        *b_GroomedJet_CA8_prsubjet1_pz;   //!
   TBranch        *b_GroomedJet_CA8_prsubjet1_e;   //!
   TBranch        *b_GroomedJet_CA8_prsubjet2_px;   //!
   TBranch        *b_GroomedJet_CA8_prsubjet2_py;   //!
   TBranch        *b_GroomedJet_CA8_prsubjet2_pz;   //!
   TBranch        *b_GroomedJet_CA8_prsubjet2_e;   //!
   TBranch        *b_GroomedJet_CA8_mass;   //!
   TBranch        *b_GroomedJet_CA8_mass_tr;   //!
   TBranch        *b_GroomedJet_CA8_mass_ft;   //!
   TBranch        *b_GroomedJet_CA8_mass_pr;   //!
   TBranch        *b_GroomedJet_CA8_massdrop_pr;   //!
   TBranch        *b_GroomedJet_CA8_area;   //!
   TBranch        *b_GroomedJet_CA8_area_tr;   //!
   TBranch        *b_GroomedJet_CA8_area_ft;   //!
   TBranch        *b_GroomedJet_CA8_area_pr;   //!
   TBranch        *b_GroomedJet_CA8_jetconstituents;   //!
   TBranch        *b_GroomedJet_CA8_jetcharge;   //!
   TBranch        *b_GroomedJet_CA8_rcores;   //!
   TBranch        *b_GroomedJet_CA8_ptcores;   //!
   TBranch        *b_GroomedJet_CA8_planarflow;   //!
   TBranch        *b_GroomedJet_CA8_qjetmass;   //!
   TBranch        *b_GroomedJet_CA8_qjetmassdrop;   //!
   TBranch        *b_GroomedJet_CA8_constituents0_eta;   //!
   TBranch        *b_GroomedJet_CA8_constituents0_phi;   //!
   TBranch        *b_GroomedJet_CA8_constituents0_e;   //!
   TBranch        *b_GroomedJet_CA8_nconstituents0;   //!
   TBranch        *b_GroomedJet_CA8_constituents0pr_eta;   //!
   TBranch        *b_GroomedJet_CA8_constituents0pr_phi;   //!
   TBranch        *b_GroomedJet_CA8_constituents0pr_e;   //!
   TBranch        *b_GroomedJet_CA8_nconstituents0pr;   //!
   TBranch        *b_GenGroomedJet_AK5_pt_uncorr;   //!
   TBranch        *b_GenGroomedJet_AK5_mass_uncorr;   //!
   TBranch        *b_GenGroomedJet_AK5_mass_tr_uncorr;   //!
   TBranch        *b_GenGroomedJet_AK5_mass_ft_uncorr;   //!
   TBranch        *b_GenGroomedJet_AK5_mass_pr_uncorr;   //!
   TBranch        *b_GenGroomedJet_AK5_tau2tau1;   //!
   TBranch        *b_GenGroomedJet_AK5_tau1;   //!
   TBranch        *b_GenGroomedJet_AK5_tau2;   //!
   TBranch        *b_GenGroomedJet_AK5_tau3;   //!
   TBranch        *b_GenGroomedJet_AK5_tau4;   //!
   TBranch        *b_GenGroomedJet_AK5_massdrop_pr_uncorr;   //!
   TBranch        *b_GenGroomedJet_AK5_pt;   //!
   TBranch        *b_GenGroomedJet_AK5_eta;   //!
   TBranch        *b_GenGroomedJet_AK5_phi;   //!
   TBranch        *b_GenGroomedJet_AK5_e;   //!
   TBranch        *b_GenGroomedJet_AK5_pt_tr_uncorr;   //!
   TBranch        *b_GenGroomedJet_AK5_pt_tr;   //!
   TBranch        *b_GenGroomedJet_AK5_eta_tr;   //!
   TBranch        *b_GenGroomedJet_AK5_phi_tr;   //!
   TBranch        *b_GenGroomedJet_AK5_e_tr;   //!
   TBranch        *b_GenGroomedJet_AK5_pt_ft_uncorr;   //!
   TBranch        *b_GenGroomedJet_AK5_pt_ft;   //!
   TBranch        *b_GenGroomedJet_AK5_eta_ft;   //!
   TBranch        *b_GenGroomedJet_AK5_phi_ft;   //!
   TBranch        *b_GenGroomedJet_AK5_e_ft;   //!
   TBranch        *b_GenGroomedJet_AK5_pt_pr_uncorr;   //!
   TBranch        *b_GenGroomedJet_AK5_pt_pr;   //!
   TBranch        *b_GenGroomedJet_AK5_eta_pr;   //!
   TBranch        *b_GenGroomedJet_AK5_phi_pr;   //!
   TBranch        *b_GenGroomedJet_AK5_e_pr;   //!
   TBranch        *b_GenGroomedJet_AK5_prsubjet1_px;   //!
   TBranch        *b_GenGroomedJet_AK5_prsubjet1_py;   //!
   TBranch        *b_GenGroomedJet_AK5_prsubjet1_pz;   //!
   TBranch        *b_GenGroomedJet_AK5_prsubjet1_e;   //!
   TBranch        *b_GenGroomedJet_AK5_prsubjet2_px;   //!
   TBranch        *b_GenGroomedJet_AK5_prsubjet2_py;   //!
   TBranch        *b_GenGroomedJet_AK5_prsubjet2_pz;   //!
   TBranch        *b_GenGroomedJet_AK5_prsubjet2_e;   //!
   TBranch        *b_GenGroomedJet_AK5_mass;   //!
   TBranch        *b_GenGroomedJet_AK5_mass_tr;   //!
   TBranch        *b_GenGroomedJet_AK5_mass_ft;   //!
   TBranch        *b_GenGroomedJet_AK5_mass_pr;   //!
   TBranch        *b_GenGroomedJet_AK5_massdrop_pr;   //!
   TBranch        *b_GenGroomedJet_AK5_area;   //!
   TBranch        *b_GenGroomedJet_AK5_area_tr;   //!
   TBranch        *b_GenGroomedJet_AK5_area_ft;   //!
   TBranch        *b_GenGroomedJet_AK5_area_pr;   //!
   TBranch        *b_GenGroomedJet_AK5_jetconstituents;   //!
   TBranch        *b_GenGroomedJet_AK5_jetcharge;   //!
   TBranch        *b_GenGroomedJet_AK5_rcores;   //!
   TBranch        *b_GenGroomedJet_AK5_ptcores;   //!
   TBranch        *b_GenGroomedJet_AK5_planarflow;   //!
   TBranch        *b_GenGroomedJet_AK5_qjetmass;   //!
   TBranch        *b_GenGroomedJet_AK5_qjetmassdrop;   //!
   TBranch        *b_GenGroomedJet_AK5_constituents0_eta;   //!
   TBranch        *b_GenGroomedJet_AK5_constituents0_phi;   //!
   TBranch        *b_GenGroomedJet_AK5_constituents0_e;   //!
   TBranch        *b_GenGroomedJet_AK5_nconstituents0;   //!
   TBranch        *b_GenGroomedJet_AK5_constituents0pr_eta;   //!
   TBranch        *b_GenGroomedJet_AK5_constituents0pr_phi;   //!
   TBranch        *b_GenGroomedJet_AK5_constituents0pr_e;   //!
   TBranch        *b_GenGroomedJet_AK5_nconstituents0pr;   //!
   TBranch        *b_GenGroomedJet_AK7_pt_uncorr;   //!
   TBranch        *b_GenGroomedJet_AK7_mass_uncorr;   //!
   TBranch        *b_GenGroomedJet_AK7_mass_tr_uncorr;   //!
   TBranch        *b_GenGroomedJet_AK7_mass_ft_uncorr;   //!
   TBranch        *b_GenGroomedJet_AK7_mass_pr_uncorr;   //!
   TBranch        *b_GenGroomedJet_AK7_tau2tau1;   //!
   TBranch        *b_GenGroomedJet_AK7_tau1;   //!
   TBranch        *b_GenGroomedJet_AK7_tau2;   //!
   TBranch        *b_GenGroomedJet_AK7_tau3;   //!
   TBranch        *b_GenGroomedJet_AK7_tau4;   //!
   TBranch        *b_GenGroomedJet_AK7_massdrop_pr_uncorr;   //!
   TBranch        *b_GenGroomedJet_AK7_pt;   //!
   TBranch        *b_GenGroomedJet_AK7_eta;   //!
   TBranch        *b_GenGroomedJet_AK7_phi;   //!
   TBranch        *b_GenGroomedJet_AK7_e;   //!
   TBranch        *b_GenGroomedJet_AK7_pt_tr_uncorr;   //!
   TBranch        *b_GenGroomedJet_AK7_pt_tr;   //!
   TBranch        *b_GenGroomedJet_AK7_eta_tr;   //!
   TBranch        *b_GenGroomedJet_AK7_phi_tr;   //!
   TBranch        *b_GenGroomedJet_AK7_e_tr;   //!
   TBranch        *b_GenGroomedJet_AK7_pt_ft_uncorr;   //!
   TBranch        *b_GenGroomedJet_AK7_pt_ft;   //!
   TBranch        *b_GenGroomedJet_AK7_eta_ft;   //!
   TBranch        *b_GenGroomedJet_AK7_phi_ft;   //!
   TBranch        *b_GenGroomedJet_AK7_e_ft;   //!
   TBranch        *b_GenGroomedJet_AK7_pt_pr_uncorr;   //!
   TBranch        *b_GenGroomedJet_AK7_pt_pr;   //!
   TBranch        *b_GenGroomedJet_AK7_eta_pr;   //!
   TBranch        *b_GenGroomedJet_AK7_phi_pr;   //!
   TBranch        *b_GenGroomedJet_AK7_e_pr;   //!
   TBranch        *b_GenGroomedJet_AK7_prsubjet1_px;   //!
   TBranch        *b_GenGroomedJet_AK7_prsubjet1_py;   //!
   TBranch        *b_GenGroomedJet_AK7_prsubjet1_pz;   //!
   TBranch        *b_GenGroomedJet_AK7_prsubjet1_e;   //!
   TBranch        *b_GenGroomedJet_AK7_prsubjet2_px;   //!
   TBranch        *b_GenGroomedJet_AK7_prsubjet2_py;   //!
   TBranch        *b_GenGroomedJet_AK7_prsubjet2_pz;   //!
   TBranch        *b_GenGroomedJet_AK7_prsubjet2_e;   //!
   TBranch        *b_GenGroomedJet_AK7_mass;   //!
   TBranch        *b_GenGroomedJet_AK7_mass_tr;   //!
   TBranch        *b_GenGroomedJet_AK7_mass_ft;   //!
   TBranch        *b_GenGroomedJet_AK7_mass_pr;   //!
   TBranch        *b_GenGroomedJet_AK7_massdrop_pr;   //!
   TBranch        *b_GenGroomedJet_AK7_area;   //!
   TBranch        *b_GenGroomedJet_AK7_area_tr;   //!
   TBranch        *b_GenGroomedJet_AK7_area_ft;   //!
   TBranch        *b_GenGroomedJet_AK7_area_pr;   //!
   TBranch        *b_GenGroomedJet_AK7_jetconstituents;   //!
   TBranch        *b_GenGroomedJet_AK7_jetcharge;   //!
   TBranch        *b_GenGroomedJet_AK7_rcores;   //!
   TBranch        *b_GenGroomedJet_AK7_ptcores;   //!
   TBranch        *b_GenGroomedJet_AK7_planarflow;   //!
   TBranch        *b_GenGroomedJet_AK7_qjetmass;   //!
   TBranch        *b_GenGroomedJet_AK7_qjetmassdrop;   //!
   TBranch        *b_GenGroomedJet_AK7_constituents0_eta;   //!
   TBranch        *b_GenGroomedJet_AK7_constituents0_phi;   //!
   TBranch        *b_GenGroomedJet_AK7_constituents0_e;   //!
   TBranch        *b_GenGroomedJet_AK7_nconstituents0;   //!
   TBranch        *b_GenGroomedJet_AK7_constituents0pr_eta;   //!
   TBranch        *b_GenGroomedJet_AK7_constituents0pr_phi;   //!
   TBranch        *b_GenGroomedJet_AK7_constituents0pr_e;   //!
   TBranch        *b_GenGroomedJet_AK7_nconstituents0pr;   //!
   TBranch        *b_GenGroomedJet_CA8_pt_uncorr;   //!
   TBranch        *b_GenGroomedJet_CA8_mass_uncorr;   //!
   TBranch        *b_GenGroomedJet_CA8_mass_tr_uncorr;   //!
   TBranch        *b_GenGroomedJet_CA8_mass_ft_uncorr;   //!
   TBranch        *b_GenGroomedJet_CA8_mass_pr_uncorr;   //!
   TBranch        *b_GenGroomedJet_CA8_tau2tau1;   //!
   TBranch        *b_GenGroomedJet_CA8_tau1;   //!
   TBranch        *b_GenGroomedJet_CA8_tau2;   //!
   TBranch        *b_GenGroomedJet_CA8_tau3;   //!
   TBranch        *b_GenGroomedJet_CA8_tau4;   //!
   TBranch        *b_GenGroomedJet_CA8_massdrop_pr_uncorr;   //!
   TBranch        *b_GenGroomedJet_CA8_pt;   //!
   TBranch        *b_GenGroomedJet_CA8_eta;   //!
   TBranch        *b_GenGroomedJet_CA8_phi;   //!
   TBranch        *b_GenGroomedJet_CA8_e;   //!
   TBranch        *b_GenGroomedJet_CA8_pt_tr_uncorr;   //!
   TBranch        *b_GenGroomedJet_CA8_pt_tr;   //!
   TBranch        *b_GenGroomedJet_CA8_eta_tr;   //!
   TBranch        *b_GenGroomedJet_CA8_phi_tr;   //!
   TBranch        *b_GenGroomedJet_CA8_e_tr;   //!
   TBranch        *b_GenGroomedJet_CA8_pt_ft_uncorr;   //!
   TBranch        *b_GenGroomedJet_CA8_pt_ft;   //!
   TBranch        *b_GenGroomedJet_CA8_eta_ft;   //!
   TBranch        *b_GenGroomedJet_CA8_phi_ft;   //!
   TBranch        *b_GenGroomedJet_CA8_e_ft;   //!
   TBranch        *b_GenGroomedJet_CA8_pt_pr_uncorr;   //!
   TBranch        *b_GenGroomedJet_CA8_pt_pr;   //!
   TBranch        *b_GenGroomedJet_CA8_eta_pr;   //!
   TBranch        *b_GenGroomedJet_CA8_phi_pr;   //!
   TBranch        *b_GenGroomedJet_CA8_e_pr;   //!
   TBranch        *b_GenGroomedJet_CA8_prsubjet1_px;   //!
   TBranch        *b_GenGroomedJet_CA8_prsubjet1_py;   //!
   TBranch        *b_GenGroomedJet_CA8_prsubjet1_pz;   //!
   TBranch        *b_GenGroomedJet_CA8_prsubjet1_e;   //!
   TBranch        *b_GenGroomedJet_CA8_prsubjet2_px;   //!
   TBranch        *b_GenGroomedJet_CA8_prsubjet2_py;   //!
   TBranch        *b_GenGroomedJet_CA8_prsubjet2_pz;   //!
   TBranch        *b_GenGroomedJet_CA8_prsubjet2_e;   //!
   TBranch        *b_GenGroomedJet_CA8_mass;   //!
   TBranch        *b_GenGroomedJet_CA8_mass_tr;   //!
   TBranch        *b_GenGroomedJet_CA8_mass_ft;   //!
   TBranch        *b_GenGroomedJet_CA8_mass_pr;   //!
   TBranch        *b_GenGroomedJet_CA8_massdrop_pr;   //!
   TBranch        *b_GenGroomedJet_CA8_area;   //!
   TBranch        *b_GenGroomedJet_CA8_area_tr;   //!
   TBranch        *b_GenGroomedJet_CA8_area_ft;   //!
   TBranch        *b_GenGroomedJet_CA8_area_pr;   //!
   TBranch        *b_GenGroomedJet_CA8_jetconstituents;   //!
   TBranch        *b_GenGroomedJet_CA8_jetcharge;   //!
   TBranch        *b_GenGroomedJet_CA8_rcores;   //!
   TBranch        *b_GenGroomedJet_CA8_ptcores;   //!
   TBranch        *b_GenGroomedJet_CA8_planarflow;   //!
   TBranch        *b_GenGroomedJet_CA8_qjetmass;   //!
   TBranch        *b_GenGroomedJet_CA8_qjetmassdrop;   //!
   TBranch        *b_GenGroomedJet_CA8_constituents0_eta;   //!
   TBranch        *b_GenGroomedJet_CA8_constituents0_phi;   //!
   TBranch        *b_GenGroomedJet_CA8_constituents0_e;   //!
   TBranch        *b_GenGroomedJet_CA8_nconstituents0;   //!
   TBranch        *b_GenGroomedJet_CA8_constituents0pr_eta;   //!
   TBranch        *b_GenGroomedJet_CA8_constituents0pr_phi;   //!
   TBranch        *b_GenGroomedJet_CA8_constituents0pr_e;   //!
   TBranch        *b_GenGroomedJet_CA8_nconstituents0pr;   //!
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
   TBranch        *b_trkSumPtHollowConeDR04_Photon11;   //!
   TBranch        *b_ecalRecHitSumEtConeDR04_Photon11;   //!
   TBranch        *b_hcalTowerSumEtConeDR04_Photon11;   //!
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
   TBranch        *b_W_pzNu1;   //!
   TBranch        *b_W_pzNu2;   //!
   TBranch        *b_W_muon_px;   //!
   TBranch        *b_W_muon_py;   //!
   TBranch        *b_W_muon_pz;   //!
   TBranch        *b_W_muon_e;   //!
   TBranch        *b_W_muon_pt;   //!
   TBranch        *b_W_muon_et;   //!
   TBranch        *b_W_muon_eta;   //!
   TBranch        *b_W_muon_theta;   //!
   TBranch        *b_W_muon_phi;   //!
   TBranch        *b_W_muon_charge;   //!
   TBranch        *b_W_muon_vx;   //!
   TBranch        *b_W_muon_vy;   //!
   TBranch        *b_W_muon_vz;   //!
   TBranch        *b_W_muon_y;   //!
   TBranch        *b_W_muon_trackiso;   //!
   TBranch        *b_W_muon_hcaliso;   //!
   TBranch        *b_W_muon_ecaliso;   //!
   TBranch        *b_W_muon_type;   //!
   TBranch        *b_W_muon_numberOfChambers;   //!
   TBranch        *b_W_muon_numberOfMatches;   //!
   TBranch        *b_W_muon_d0bsp;   //!
   TBranch        *b_W_muon_dz000;   //!
   TBranch        *b_W_muon_dzPV;   //!
   TBranch        *b_W_muon_pfiso_sumChargedHadronPt;   //!
   TBranch        *b_W_muon_pfiso_sumChargedParticlePt;   //!
   TBranch        *b_W_muon_pfiso_sumNeutralHadronEt;   //!
   TBranch        *b_W_muon_pfiso_sumPhotonEt;   //!
   TBranch        *b_W_muon_pfiso_sumPUPt;   //!
   TBranch        *b_W_Photon_pt_gen;   //!
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
   TBranch        *b_W_muon_px_gen;   //!
   TBranch        *b_W_muon_py_gen;   //!
   TBranch        *b_W_muon_pz_gen;   //!
   TBranch        *b_W_muon_e_gen;   //!
   TBranch        *b_W_muon_pt_gen;   //!
   TBranch        *b_W_muon_et_gen;   //!
   TBranch        *b_W_muon_eta_gen;   //!
   TBranch        *b_W_muon_theta_gen;   //!
   TBranch        *b_W_muon_phi_gen;   //!
   TBranch        *b_W_muon_charge_gen;   //!
   TBranch        *b_W_muon_vx_gen;   //!
   TBranch        *b_W_muon_vy_gen;   //!
   TBranch        *b_W_muon_vz_gen;   //!
   TBranch        *b_W_muon_y_gen;   //!
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
   TBranch        *b_W_tParton_px;   //!
   TBranch        *b_W_tParton_py;   //!
   TBranch        *b_W_tParton_pz;   //!
   TBranch        *b_W_tParton_E;   //!
   TBranch        *b_W_tParton_pt;   //!
   TBranch        *b_W_tParton_et;   //!
   TBranch        *b_W_tParton_eta;   //!
   TBranch        *b_W_tParton_theta;   //!
   TBranch        *b_W_tParton_phi;   //!
   TBranch        *b_W_tParton_charge;   //!
   TBranch        *b_W_tParton_vx;   //!
   TBranch        *b_W_tParton_vy;   //!
   TBranch        *b_W_tParton_vz;   //!
   TBranch        *b_W_tParton_y;   //!
   TBranch        *b_W_tParton_Id;   //!
   TBranch        *b_W_tLepton_px;   //!
   TBranch        *b_W_tLepton_py;   //!
   TBranch        *b_W_tLepton_pz;   //!
   TBranch        *b_W_tLepton_E;   //!
   TBranch        *b_W_tLepton_pt;   //!
   TBranch        *b_W_tLepton_et;   //!
   TBranch        *b_W_tLepton_eta;   //!
   TBranch        *b_W_tLepton_theta;   //!
   TBranch        *b_W_tLepton_phi;   //!
   TBranch        *b_W_tLepton_charge;   //!
   TBranch        *b_W_tLepton_vx;   //!
   TBranch        *b_W_tLepton_vy;   //!
   TBranch        *b_W_tLepton_vz;   //!
   TBranch        *b_W_tLepton_y;   //!
   TBranch        *b_W_tLepton_Id;   //!
   TBranch        *b_W_tMet_px;   //!
   TBranch        *b_W_tMet_py;   //!
   TBranch        *b_W_tMet_pz;   //!
   TBranch        *b_W_tMet_E;   //!
   TBranch        *b_W_tMet_pt;   //!
   TBranch        *b_W_tMet_et;   //!
   TBranch        *b_W_tMet_eta;   //!
   TBranch        *b_W_tMet_theta;   //!
   TBranch        *b_W_tMet_phi;   //!
   TBranch        *b_W_tMet_charge;   //!
   TBranch        *b_W_tMet_vx;   //!
   TBranch        *b_W_tMet_vy;   //!
   TBranch        *b_W_tMet_vz;   //!
   TBranch        *b_W_tMet_y;   //!
   TBranch        *b_W_tMet_Id;   //!
   TBranch        *b_W_tb_px;   //!
   TBranch        *b_W_tb_py;   //!
   TBranch        *b_W_tb_pz;   //!
   TBranch        *b_W_tb_E;   //!
   TBranch        *b_W_tb_pt;   //!
   TBranch        *b_W_tb_et;   //!
   TBranch        *b_W_tb_eta;   //!
   TBranch        *b_W_tb_theta;   //!
   TBranch        *b_W_tb_phi;   //!
   TBranch        *b_W_tb_charge;   //!
   TBranch        *b_W_tb_vx;   //!
   TBranch        *b_W_tb_vy;   //!
   TBranch        *b_W_tb_vz;   //!
   TBranch        *b_W_tb_y;   //!
   TBranch        *b_W_tb_Id;   //!
   TBranch        *b_W_tbbar_px;   //!
   TBranch        *b_W_tbbar_py;   //!
   TBranch        *b_W_tbbar_pz;   //!
   TBranch        *b_W_tbbar_E;   //!
   TBranch        *b_W_tbbar_pt;   //!
   TBranch        *b_W_tbbar_et;   //!
   TBranch        *b_W_tbbar_eta;   //!
   TBranch        *b_W_tbbar_theta;   //!
   TBranch        *b_W_tbbar_phi;   //!
   TBranch        *b_W_tbbar_charge;   //!
   TBranch        *b_W_tbbar_vx;   //!
   TBranch        *b_W_tbbar_vy;   //!
   TBranch        *b_W_tbbar_vz;   //!
   TBranch        *b_W_tbbar_y;   //!
   TBranch        *b_W_tbbar_Id;   //!
   TBranch        *b_W_Hb_px;   //!
   TBranch        *b_W_Hb_py;   //!
   TBranch        *b_W_Hb_pz;   //!
   TBranch        *b_W_Hb_E;   //!
   TBranch        *b_W_Hb_pt;   //!
   TBranch        *b_W_Hb_et;   //!
   TBranch        *b_W_Hb_eta;   //!
   TBranch        *b_W_Hb_theta;   //!
   TBranch        *b_W_Hb_phi;   //!
   TBranch        *b_W_Hb_charge;   //!
   TBranch        *b_W_Hb_vx;   //!
   TBranch        *b_W_Hb_vy;   //!
   TBranch        *b_W_Hb_vz;   //!
   TBranch        *b_W_Hb_y;   //!
   TBranch        *b_W_Hb_Id;   //!
   TBranch        *b_W_Hbbar_px;   //!
   TBranch        *b_W_Hbbar_py;   //!
   TBranch        *b_W_Hbbar_pz;   //!
   TBranch        *b_W_Hbbar_E;   //!
   TBranch        *b_W_Hbbar_pt;   //!
   TBranch        *b_W_Hbbar_et;   //!
   TBranch        *b_W_Hbbar_eta;   //!
   TBranch        *b_W_Hbbar_theta;   //!
   TBranch        *b_W_Hbbar_phi;   //!
   TBranch        *b_W_Hbbar_charge;   //!
   TBranch        *b_W_Hbbar_vx;   //!
   TBranch        *b_W_Hbbar_vy;   //!
   TBranch        *b_W_Hbbar_vz;   //!
   TBranch        *b_W_Hbbar_y;   //!
   TBranch        *b_W_Hbbar_Id;   //!
   TBranch        *b_W_TagQuark_px;   //!
   TBranch        *b_W_TagQuark_py;   //!
   TBranch        *b_W_TagQuark_pz;   //!
   TBranch        *b_W_TagQuark_E;   //!
   TBranch        *b_W_TagQuark_pt;   //!
   TBranch        *b_W_TagQuark_et;   //!
   TBranch        *b_W_TagQuark_eta;   //!
   TBranch        *b_W_TagQuark_theta;   //!
   TBranch        *b_W_TagQuark_phi;   //!
   TBranch        *b_W_TagQuark_charge;   //!
   TBranch        *b_W_TagQuark_vx;   //!
   TBranch        *b_W_TagQuark_vy;   //!
   TBranch        *b_W_TagQuark_vz;   //!
   TBranch        *b_W_TagQuark_y;   //!
   TBranch        *b_W_TagQuark_Id;   //!
   TBranch        *b_W_EWKW_px;   //!
   TBranch        *b_W_EWKW_py;   //!
   TBranch        *b_W_EWKW_pz;   //!
   TBranch        *b_W_EWKW_E;   //!
   TBranch        *b_W_EWKW_pt;   //!
   TBranch        *b_W_EWKW_et;   //!
   TBranch        *b_W_EWKW_eta;   //!
   TBranch        *b_W_EWKW_theta;   //!
   TBranch        *b_W_EWKW_phi;   //!
   TBranch        *b_W_EWKW_charge;   //!
   TBranch        *b_W_EWKW_vx;   //!
   TBranch        *b_W_EWKW_vy;   //!
   TBranch        *b_W_EWKW_vz;   //!
   TBranch        *b_W_EWKW_y;   //!
   TBranch        *b_W_EWKW_Id;   //!
   TBranch        *b_W_EWKTagQuark_px;   //!
   TBranch        *b_W_EWKTagQuark_py;   //!
   TBranch        *b_W_EWKTagQuark_pz;   //!
   TBranch        *b_W_EWKTagQuark_E;   //!
   TBranch        *b_W_EWKTagQuark_pt;   //!
   TBranch        *b_W_EWKTagQuark_et;   //!
   TBranch        *b_W_EWKTagQuark_eta;   //!
   TBranch        *b_W_EWKTagQuark_theta;   //!
   TBranch        *b_W_EWKTagQuark_phi;   //!
   TBranch        *b_W_EWKTagQuark_charge;   //!
   TBranch        *b_W_EWKTagQuark_vx;   //!
   TBranch        *b_W_EWKTagQuark_vy;   //!
   TBranch        *b_W_EWKTagQuark_vz;   //!
   TBranch        *b_W_EWKTagQuark_y;   //!
   TBranch        *b_W_EWKTagQuark_Id;   //!
   TBranch        *b_W_nParton_Winclusive;   //!
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


      kanamuon(TTree *tree=0);
      virtual ~kanamuon();
      virtual Int_t    Cut(Long64_t entry);
      virtual Int_t    GetEntry(Long64_t entry);
      virtual Long64_t LoadTree(Long64_t entry);
      virtual void     Init(TTree *tree);
      virtual Bool_t   Notify();
      virtual void     Show(Long64_t entry = -1);

      virtual void     myana(double myflag = -999, bool isQCD = false, int runflag=0);
      virtual void     Loop(TH1F* h_events,
            TH1F* h_events_weighted,
            int wda,
            int runflag,
            const char * outfilename,
            bool isQCD = false);
      virtual double   getDeltaPhi(double phi1, double phi2);
      //virtual bool     large(const double &a, const double &b);
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
      virtual bool    dottHKinematicFit(const TLorentzVector     mup, 
            const TLorentzVector     nvp, 
            const TLorentzVector     wajp,
            const TLorentzVector     wbjp,
            const TLorentzVector     topajp,
            const TLorentzVector     topbjp,
            Float_t            & fit_chi2,
            Int_t              & fit_NDF,
            Int_t              & fit_status);
      virtual void     calculateAngles( TLorentzVector& thep4M11, TLorentzVector& thep4M12, TLorentzVector& thep4M21, TLorentzVector& thep4M22, double& costheta1, double& costheta2, double& phi, double& costhetastar, double& phistar1, double& phistar2);
      virtual void     InitCounters(const char* input_file_name, TH1F* h_events, TH1F* h_events_weighted);

};

#endif

#ifdef kanamuon_cxx
kanamuon::kanamuon(TTree *tree)
{
   // if parameter tree is not specified (or zero), connect the file
   // used to generate this class and read the Tree.
   if (tree == 0) {
      //TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/uscms_data/d3/weizou/MakeNtuple/CMSSW_5_3_2_patch4/src/ElectroWeakAnalysis/VPlusJets/test/mu_STopS_Tbar_CMSSW532.root");
      //TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/uscms/store/user/lnujj/Moriond2013/MergedNtuples_v1/mu_VBFHWWMH170_CMSSW532_private.root");
      //TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/uscms_data/d3/weizou/test/CopySample/mu_VBFHWWMH170_CMSSW532_private.root");
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/uscms/store/user/lnujj/Moriond2013/MergedNtuples_v2_nojetnum/mu_WJets_CMSSW532_pt1_v2.root");
      if (!f) {
         //f = new TFile("/uscms_data/d3/weizou/MakeNtuple/CMSSW_5_3_2_patch4/src/ElectroWeakAnalysis/VPlusJets/test/mu_STopS_Tbar_CMSSW532.root");
         //f = new TFile("/eos/uscms/store/user/lnujj/Moriond2013/MergedNtuples_v1/mu_VBFHWWMH170_CMSSW532_private.root");
         //f = new TFile("/uscms_data/d3/weizou/test/CopySample/mu_VBFHWWMH170_CMSSW532_private.root");
         f = new TFile("/eos/uscms/store/user/lnujj/Moriond2013/MergedNtuples_v2_nojetnum/mu_WJets_CMSSW532_pt1_v2.root");
      }
      tree = (TTree*)gDirectory->Get("WJet");

   }
   Init(tree);
}

kanamuon::~kanamuon()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t kanamuon::GetEntry(Long64_t entry)
{
   // Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t kanamuon::LoadTree(Long64_t entry)
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

void kanamuon::Init(TTree *tree)
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
   fChain->SetBranchAddress("colorCorrPull01PFCor", &colorCorrPull01PFCor, &b_colorCorrPull01PFCor);
   fChain->SetBranchAddress("colorCorrPull02PFCor", &colorCorrPull02PFCor, &b_colorCorrPull02PFCor);
   fChain->SetBranchAddress("colorCorrPull12PFCor", &colorCorrPull12PFCor, &b_colorCorrPull12PFCor);
   fChain->SetBranchAddress("colorCorrPull03PFCor", &colorCorrPull03PFCor, &b_colorCorrPull03PFCor);
   fChain->SetBranchAddress("colorCorrPull13PFCor", &colorCorrPull13PFCor, &b_colorCorrPull13PFCor);
   fChain->SetBranchAddress("colorCorrPull23PFCor", &colorCorrPull23PFCor, &b_colorCorrPull23PFCor);
   fChain->SetBranchAddress("colorCorrPull04PFCor", &colorCorrPull04PFCor, &b_colorCorrPull04PFCor);
   fChain->SetBranchAddress("colorCorrPull14PFCor", &colorCorrPull14PFCor, &b_colorCorrPull14PFCor);
   fChain->SetBranchAddress("colorCorrPull24PFCor", &colorCorrPull24PFCor, &b_colorCorrPull24PFCor);
   fChain->SetBranchAddress("colorCorrPull34PFCor", &colorCorrPull34PFCor, &b_colorCorrPull34PFCor);
   fChain->SetBranchAddress("colorCorrPull05PFCor", &colorCorrPull05PFCor, &b_colorCorrPull05PFCor);
   fChain->SetBranchAddress("colorCorrPull15PFCor", &colorCorrPull15PFCor, &b_colorCorrPull15PFCor);
   fChain->SetBranchAddress("colorCorrPull25PFCor", &colorCorrPull25PFCor, &b_colorCorrPull25PFCor);
   fChain->SetBranchAddress("colorCorrPull35PFCor", &colorCorrPull35PFCor, &b_colorCorrPull35PFCor);
   fChain->SetBranchAddress("colorCorrPull45PFCor", &colorCorrPull45PFCor, &b_colorCorrPull45PFCor);
   fChain->SetBranchAddress("cosThetaJ1HiggsCM_PFCor", &cosThetaJ1HiggsCM_PFCor, &b_cosThetaJ1HiggsCM_PFCor);
   fChain->SetBranchAddress("cosThetaJ2HiggsCM_PFCor", &cosThetaJ2HiggsCM_PFCor, &b_cosThetaJ2HiggsCM_PFCor);
   fChain->SetBranchAddress("cosThetaL1HiggsCM_PFCor", &cosThetaL1HiggsCM_PFCor, &b_cosThetaL1HiggsCM_PFCor);
   fChain->SetBranchAddress("cosThetaL2HiggsCM_PFCor", &cosThetaL2HiggsCM_PFCor, &b_cosThetaL2HiggsCM_PFCor);
   fChain->SetBranchAddress("cosThetaV1HiggsCM_PFCor", &cosThetaV1HiggsCM_PFCor, &b_cosThetaV1HiggsCM_PFCor);
   fChain->SetBranchAddress("cosThetaV2HiggsCM_PFCor", &cosThetaV2HiggsCM_PFCor, &b_cosThetaV2HiggsCM_PFCor);
   fChain->SetBranchAddress("JetPFCor_isPileUpJetLoose", JetPFCor_isPileUpJetLoose, &b_JetPFCor_isPileUpJetLoose);
   fChain->SetBranchAddress("JetPFCor_isPileUpJetMedium", JetPFCor_isPileUpJetMedium, &b_JetPFCor_isPileUpJetMedium);
   fChain->SetBranchAddress("JetPFCor_isPileUpJetTight", JetPFCor_isPileUpJetTight, &b_JetPFCor_isPileUpJetTight);
   fChain->SetBranchAddress("numPFCorVBFTagJets", &numPFCorVBFTagJets, &b_numPFCorVBFTagJets);
   fChain->SetBranchAddress("numPFCorVBFTagJetBTags", &numPFCorVBFTagJetBTags, &b_numPFCorVBFTagJetBTags);
   fChain->SetBranchAddress("JetPFCorVBFTag_Et", JetPFCorVBFTag_Et, &b_JetPFCorVBFTag_Et);
   fChain->SetBranchAddress("JetPFCorVBFTag_Pt", JetPFCorVBFTag_Pt, &b_JetPFCorVBFTag_Pt);
   fChain->SetBranchAddress("JetPFCorVBFTag_Eta", JetPFCorVBFTag_Eta, &b_JetPFCorVBFTag_Eta);
   fChain->SetBranchAddress("JetPFCorVBFTag_Phi", JetPFCorVBFTag_Phi, &b_JetPFCorVBFTag_Phi);
   fChain->SetBranchAddress("JetPFCorVBFTag_Theta", JetPFCorVBFTag_Theta, &b_JetPFCorVBFTag_Theta);
   fChain->SetBranchAddress("JetPFCorVBFTag_Px", JetPFCorVBFTag_Px, &b_JetPFCorVBFTag_Px);
   fChain->SetBranchAddress("JetPFCorVBFTag_Py", JetPFCorVBFTag_Py, &b_JetPFCorVBFTag_Py);
   fChain->SetBranchAddress("JetPFCorVBFTag_Pz", JetPFCorVBFTag_Pz, &b_JetPFCorVBFTag_Pz);
   fChain->SetBranchAddress("JetPFCorVBFTag_E", JetPFCorVBFTag_E, &b_JetPFCorVBFTag_E);
   fChain->SetBranchAddress("JetPFCorVBFTag_Y", JetPFCorVBFTag_Y, &b_JetPFCorVBFTag_Y);
   fChain->SetBranchAddress("JetPFCorVBFTag_Mass", JetPFCorVBFTag_Mass, &b_JetPFCorVBFTag_Mass);
   fChain->SetBranchAddress("JetPFCorVBFTag_etaetaMoment", JetPFCorVBFTag_etaetaMoment, &b_JetPFCorVBFTag_etaetaMoment);
   fChain->SetBranchAddress("JetPFCorVBFTag_phiphiMoment", JetPFCorVBFTag_phiphiMoment, &b_JetPFCorVBFTag_phiphiMoment);
   fChain->SetBranchAddress("JetPFCorVBFTag_etaphiMoment", JetPFCorVBFTag_etaphiMoment, &b_JetPFCorVBFTag_etaphiMoment);
   fChain->SetBranchAddress("JetPFCorVBFTag_maxDistance", JetPFCorVBFTag_maxDistance, &b_JetPFCorVBFTag_maxDistance);
   fChain->SetBranchAddress("JetPFCorVBFTag_nConstituents", JetPFCorVBFTag_nConstituents, &b_JetPFCorVBFTag_nConstituents);
   fChain->SetBranchAddress("JetPFCorVBFTag_Area", JetPFCorVBFTag_Area, &b_JetPFCorVBFTag_Area);
   fChain->SetBranchAddress("VplusPFCorVBFTagJet_Mass", VplusPFCorVBFTagJet_Mass, &b_VplusPFCorVBFTagJet_Mass);
   fChain->SetBranchAddress("JetPFCorVBFTag_dphiBoson", JetPFCorVBFTag_dphiBoson, &b_JetPFCorVBFTag_dphiBoson);
   fChain->SetBranchAddress("JetPFCorVBFTag_detaBoson", JetPFCorVBFTag_detaBoson, &b_JetPFCorVBFTag_detaBoson);
   fChain->SetBranchAddress("JetPFCorVBFTag_dRBoson", JetPFCorVBFTag_dRBoson, &b_JetPFCorVBFTag_dRBoson);
   fChain->SetBranchAddress("JetPFCorVBFTag_dphiMET", JetPFCorVBFTag_dphiMET, &b_JetPFCorVBFTag_dphiMET);
   fChain->SetBranchAddress("JetPFCorVBFTag_bDiscriminator", JetPFCorVBFTag_bDiscriminator, &b_JetPFCorVBFTag_bDiscriminator);
   fChain->SetBranchAddress("JetPFCorVBFTag_bDiscriminatorSSVHE", JetPFCorVBFTag_bDiscriminatorSSVHE, &b_JetPFCorVBFTag_bDiscriminatorSSVHE);
   fChain->SetBranchAddress("JetPFCorVBFTag_bDiscriminatorTCHE", JetPFCorVBFTag_bDiscriminatorTCHE, &b_JetPFCorVBFTag_bDiscriminatorTCHE);
   fChain->SetBranchAddress("JetPFCorVBFTag_bDiscriminatorCSV", JetPFCorVBFTag_bDiscriminatorCSV, &b_JetPFCorVBFTag_bDiscriminatorCSV);
   fChain->SetBranchAddress("JetPFCorVBFTag_bDiscriminatorJP", JetPFCorVBFTag_bDiscriminatorJP, &b_JetPFCorVBFTag_bDiscriminatorJP);
   fChain->SetBranchAddress("JetPFCorVBFTag_bDiscriminatorSSVHP", JetPFCorVBFTag_bDiscriminatorSSVHP, &b_JetPFCorVBFTag_bDiscriminatorSSVHP);
   fChain->SetBranchAddress("JetPFCorVBFTag_bDiscriminatorTCHP", JetPFCorVBFTag_bDiscriminatorTCHP, &b_JetPFCorVBFTag_bDiscriminatorTCHP);
   fChain->SetBranchAddress("JetPFCorVBFTag_secVertexMass", JetPFCorVBFTag_secVertexMass, &b_JetPFCorVBFTag_secVertexMass);
   fChain->SetBranchAddress("JetPFCorVBFTag_ChargedHadronEnergy", JetPFCorVBFTag_ChargedHadronEnergy, &b_JetPFCorVBFTag_ChargedHadronEnergy);
   fChain->SetBranchAddress("JetPFCorVBFTag_ChargedHadronEnergyFrac", JetPFCorVBFTag_ChargedHadronEnergyFrac, &b_JetPFCorVBFTag_ChargedHadronEnergyFrac);
   fChain->SetBranchAddress("JetPFCorVBFTag_NeutralHadronEnergy", JetPFCorVBFTag_NeutralHadronEnergy, &b_JetPFCorVBFTag_NeutralHadronEnergy);
   fChain->SetBranchAddress("JetPFCorVBFTag_NeutralHadronEnergyFrac", JetPFCorVBFTag_NeutralHadronEnergyFrac, &b_JetPFCorVBFTag_NeutralHadronEnergyFrac);
   fChain->SetBranchAddress("JetPFCorVBFTag_ChargedEmEnergy", JetPFCorVBFTag_ChargedEmEnergy, &b_JetPFCorVBFTag_ChargedEmEnergy);
   fChain->SetBranchAddress("JetPFCorVBFTag_ChargedEmEnergyFrac", JetPFCorVBFTag_ChargedEmEnergyFrac, &b_JetPFCorVBFTag_ChargedEmEnergyFrac);
   fChain->SetBranchAddress("JetPFCorVBFTag_ChargedMuEnergy", JetPFCorVBFTag_ChargedMuEnergy, &b_JetPFCorVBFTag_ChargedMuEnergy);
   fChain->SetBranchAddress("JetPFCorVBFTag_ChargedMuEnergyFrac", JetPFCorVBFTag_ChargedMuEnergyFrac, &b_JetPFCorVBFTag_ChargedMuEnergyFrac);
   fChain->SetBranchAddress("JetPFCorVBFTag_NeutralEmEnergy", JetPFCorVBFTag_NeutralEmEnergy, &b_JetPFCorVBFTag_NeutralEmEnergy);
   fChain->SetBranchAddress("JetPFCorVBFTag_NeutralEmEnergyFrac", JetPFCorVBFTag_NeutralEmEnergyFrac, &b_JetPFCorVBFTag_NeutralEmEnergyFrac);
   fChain->SetBranchAddress("JetPFCorVBFTag_ChargedMultiplicity", JetPFCorVBFTag_ChargedMultiplicity, &b_JetPFCorVBFTag_ChargedMultiplicity);
   fChain->SetBranchAddress("JetPFCorVBFTag_NeutralMultiplicity", JetPFCorVBFTag_NeutralMultiplicity, &b_JetPFCorVBFTag_NeutralMultiplicity);
   fChain->SetBranchAddress("JetPFCorVBFTag_MuonMultiplicity", JetPFCorVBFTag_MuonMultiplicity, &b_JetPFCorVBFTag_MuonMultiplicity);
   fChain->SetBranchAddress("JetPFCorVBFTag_PhotonEnergy", JetPFCorVBFTag_PhotonEnergy, &b_JetPFCorVBFTag_PhotonEnergy);
   fChain->SetBranchAddress("JetPFCorVBFTag_PhotonEnergyFraction", JetPFCorVBFTag_PhotonEnergyFraction, &b_JetPFCorVBFTag_PhotonEnergyFraction);
   fChain->SetBranchAddress("JetPFCorVBFTag_ElectronEnergy", JetPFCorVBFTag_ElectronEnergy, &b_JetPFCorVBFTag_ElectronEnergy);
   fChain->SetBranchAddress("JetPFCorVBFTag_ElectronEnergyFraction", JetPFCorVBFTag_ElectronEnergyFraction, &b_JetPFCorVBFTag_ElectronEnergyFraction);
   fChain->SetBranchAddress("JetPFCorVBFTag_MuonEnergy", JetPFCorVBFTag_MuonEnergy, &b_JetPFCorVBFTag_MuonEnergy);
   fChain->SetBranchAddress("JetPFCorVBFTag_MuonEnergyFraction", JetPFCorVBFTag_MuonEnergyFraction, &b_JetPFCorVBFTag_MuonEnergyFraction);
   fChain->SetBranchAddress("JetPFCorVBFTag_HFHadronEnergy", JetPFCorVBFTag_HFHadronEnergy, &b_JetPFCorVBFTag_HFHadronEnergy);
   fChain->SetBranchAddress("JetPFCorVBFTag_HFHadronEnergyFraction", JetPFCorVBFTag_HFHadronEnergyFraction, &b_JetPFCorVBFTag_HFHadronEnergyFraction);
   fChain->SetBranchAddress("JetPFCorVBFTag_HFEMEnergy", JetPFCorVBFTag_HFEMEnergy, &b_JetPFCorVBFTag_HFEMEnergy);
   fChain->SetBranchAddress("JetPFCorVBFTag_HFEMEnergyFraction", JetPFCorVBFTag_HFEMEnergyFraction, &b_JetPFCorVBFTag_HFEMEnergyFraction);
   fChain->SetBranchAddress("JetPFCorVBFTag_ChargedHadronMultiplicity", JetPFCorVBFTag_ChargedHadronMultiplicity, &b_JetPFCorVBFTag_ChargedHadronMultiplicity);
   fChain->SetBranchAddress("JetPFCorVBFTag_NeutralHadronMultiplicity", JetPFCorVBFTag_NeutralHadronMultiplicity, &b_JetPFCorVBFTag_NeutralHadronMultiplicity);
   fChain->SetBranchAddress("JetPFCorVBFTag_PhotonMultiplicity", JetPFCorVBFTag_PhotonMultiplicity, &b_JetPFCorVBFTag_PhotonMultiplicity);
   fChain->SetBranchAddress("JetPFCorVBFTag_ElectronMultiplicity", JetPFCorVBFTag_ElectronMultiplicity, &b_JetPFCorVBFTag_ElectronMultiplicity);
   fChain->SetBranchAddress("JetPFCorVBFTag_HFHadronMultiplicity", JetPFCorVBFTag_HFHadronMultiplicity, &b_JetPFCorVBFTag_HFHadronMultiplicity);
   fChain->SetBranchAddress("JetPFCorVBFTag_HFEMMultiplicity", JetPFCorVBFTag_HFEMMultiplicity, &b_JetPFCorVBFTag_HFEMMultiplicity);
   fChain->SetBranchAddress("JetPFCorVBFTag_SumPtCands", JetPFCorVBFTag_SumPtCands, &b_JetPFCorVBFTag_SumPtCands);
   fChain->SetBranchAddress("JetPFCorVBFTag_SumPt2Cands", JetPFCorVBFTag_SumPt2Cands, &b_JetPFCorVBFTag_SumPt2Cands);
   fChain->SetBranchAddress("JetPFCorVBFTag_rmsCands", JetPFCorVBFTag_rmsCands, &b_JetPFCorVBFTag_rmsCands);
   fChain->SetBranchAddress("JetPFCorVBFTag_PtD", JetPFCorVBFTag_PtD, &b_JetPFCorVBFTag_PtD);
   fChain->SetBranchAddress("JetPFCorVBFTag_QGLikelihood", JetPFCorVBFTag_QGLikelihood, &b_JetPFCorVBFTag_QGLikelihood);
   fChain->SetBranchAddress("MassV2j_PFCorVBFTag_MVAMET", &MassV2j_PFCorVBFTag_MVAMET, &b_MassV2j_PFCorVBFTag_MVAMET);
   fChain->SetBranchAddress("MassV2j_PFCorVBFTag", &MassV2j_PFCorVBFTag, &b_MassV2j_PFCorVBFTag);
   fChain->SetBranchAddress("MassV3j_PFCorVBFTag", &MassV3j_PFCorVBFTag, &b_MassV3j_PFCorVBFTag);
   fChain->SetBranchAddress("MassV4j_PFCorVBFTag", &MassV4j_PFCorVBFTag, &b_MassV4j_PFCorVBFTag);
   fChain->SetBranchAddress("MassV5j_PFCorVBFTag", &MassV5j_PFCorVBFTag, &b_MassV5j_PFCorVBFTag);
   fChain->SetBranchAddress("MassV6j_PFCorVBFTag", &MassV6j_PFCorVBFTag, &b_MassV6j_PFCorVBFTag);
   fChain->SetBranchAddress("Mass2j_PFCorVBFTag", &Mass2j_PFCorVBFTag, &b_Mass2j_PFCorVBFTag);
   fChain->SetBranchAddress("Mass3j_PFCorVBFTag", &Mass3j_PFCorVBFTag, &b_Mass3j_PFCorVBFTag);
   fChain->SetBranchAddress("Mass4j_PFCorVBFTag", &Mass4j_PFCorVBFTag, &b_Mass4j_PFCorVBFTag);
   fChain->SetBranchAddress("Mass5j_PFCorVBFTag", &Mass5j_PFCorVBFTag, &b_Mass5j_PFCorVBFTag);
   fChain->SetBranchAddress("Mass6j_PFCorVBFTag", &Mass6j_PFCorVBFTag, &b_Mass6j_PFCorVBFTag);
   fChain->SetBranchAddress("cosJacksonAngleV2j_PFCorVBFTag", &cosJacksonAngleV2j_PFCorVBFTag, &b_cosJacksonAngleV2j_PFCorVBFTag);
   fChain->SetBranchAddress("cosJacksonAngle2j_PFCorVBFTag", &cosJacksonAngle2j_PFCorVBFTag, &b_cosJacksonAngle2j_PFCorVBFTag);
   fChain->SetBranchAddress("cosJacksonAngleV3j_PFCorVBFTag", &cosJacksonAngleV3j_PFCorVBFTag, &b_cosJacksonAngleV3j_PFCorVBFTag);
   fChain->SetBranchAddress("cosJacksonAngle3j12_PFCorVBFTag", &cosJacksonAngle3j12_PFCorVBFTag, &b_cosJacksonAngle3j12_PFCorVBFTag);
   fChain->SetBranchAddress("cosJacksonAngle3j23_PFCorVBFTag", &cosJacksonAngle3j23_PFCorVBFTag, &b_cosJacksonAngle3j23_PFCorVBFTag);
   fChain->SetBranchAddress("cosJacksonAngle3j31_PFCorVBFTag", &cosJacksonAngle3j31_PFCorVBFTag, &b_cosJacksonAngle3j31_PFCorVBFTag);
   fChain->SetBranchAddress("cosphiDecayPlane_PFCorVBFTag", &cosphiDecayPlane_PFCorVBFTag, &b_cosphiDecayPlane_PFCorVBFTag);
   fChain->SetBranchAddress("cosThetaLnu_PFCorVBFTag", &cosThetaLnu_PFCorVBFTag, &b_cosThetaLnu_PFCorVBFTag);
   fChain->SetBranchAddress("cosThetaJJ_PFCorVBFTag", &cosThetaJJ_PFCorVBFTag, &b_cosThetaJJ_PFCorVBFTag);
   fChain->SetBranchAddress("colorCorrPull01PFCorVBFTag", &colorCorrPull01PFCorVBFTag, &b_colorCorrPull01PFCorVBFTag);
   fChain->SetBranchAddress("colorCorrPull02PFCorVBFTag", &colorCorrPull02PFCorVBFTag, &b_colorCorrPull02PFCorVBFTag);
   fChain->SetBranchAddress("colorCorrPull12PFCorVBFTag", &colorCorrPull12PFCorVBFTag, &b_colorCorrPull12PFCorVBFTag);
   fChain->SetBranchAddress("colorCorrPull03PFCorVBFTag", &colorCorrPull03PFCorVBFTag, &b_colorCorrPull03PFCorVBFTag);
   fChain->SetBranchAddress("colorCorrPull13PFCorVBFTag", &colorCorrPull13PFCorVBFTag, &b_colorCorrPull13PFCorVBFTag);
   fChain->SetBranchAddress("colorCorrPull23PFCorVBFTag", &colorCorrPull23PFCorVBFTag, &b_colorCorrPull23PFCorVBFTag);
   fChain->SetBranchAddress("colorCorrPull04PFCorVBFTag", &colorCorrPull04PFCorVBFTag, &b_colorCorrPull04PFCorVBFTag);
   fChain->SetBranchAddress("colorCorrPull14PFCorVBFTag", &colorCorrPull14PFCorVBFTag, &b_colorCorrPull14PFCorVBFTag);
   fChain->SetBranchAddress("colorCorrPull24PFCorVBFTag", &colorCorrPull24PFCorVBFTag, &b_colorCorrPull24PFCorVBFTag);
   fChain->SetBranchAddress("colorCorrPull34PFCorVBFTag", &colorCorrPull34PFCorVBFTag, &b_colorCorrPull34PFCorVBFTag);
   fChain->SetBranchAddress("colorCorrPull05PFCorVBFTag", &colorCorrPull05PFCorVBFTag, &b_colorCorrPull05PFCorVBFTag);
   fChain->SetBranchAddress("colorCorrPull15PFCorVBFTag", &colorCorrPull15PFCorVBFTag, &b_colorCorrPull15PFCorVBFTag);
   fChain->SetBranchAddress("colorCorrPull25PFCorVBFTag", &colorCorrPull25PFCorVBFTag, &b_colorCorrPull25PFCorVBFTag);
   fChain->SetBranchAddress("colorCorrPull35PFCorVBFTag", &colorCorrPull35PFCorVBFTag, &b_colorCorrPull35PFCorVBFTag);
   fChain->SetBranchAddress("colorCorrPull45PFCorVBFTag", &colorCorrPull45PFCorVBFTag, &b_colorCorrPull45PFCorVBFTag);
   fChain->SetBranchAddress("cosThetaJ1HiggsCM_PFCorVBFTag", &cosThetaJ1HiggsCM_PFCorVBFTag, &b_cosThetaJ1HiggsCM_PFCorVBFTag);
   fChain->SetBranchAddress("cosThetaJ2HiggsCM_PFCorVBFTag", &cosThetaJ2HiggsCM_PFCorVBFTag, &b_cosThetaJ2HiggsCM_PFCorVBFTag);
   fChain->SetBranchAddress("cosThetaL1HiggsCM_PFCorVBFTag", &cosThetaL1HiggsCM_PFCorVBFTag, &b_cosThetaL1HiggsCM_PFCorVBFTag);
   fChain->SetBranchAddress("cosThetaL2HiggsCM_PFCorVBFTag", &cosThetaL2HiggsCM_PFCorVBFTag, &b_cosThetaL2HiggsCM_PFCorVBFTag);
   fChain->SetBranchAddress("cosThetaV1HiggsCM_PFCorVBFTag", &cosThetaV1HiggsCM_PFCorVBFTag, &b_cosThetaV1HiggsCM_PFCorVBFTag);
   fChain->SetBranchAddress("cosThetaV2HiggsCM_PFCorVBFTag", &cosThetaV2HiggsCM_PFCorVBFTag, &b_cosThetaV2HiggsCM_PFCorVBFTag);
   fChain->SetBranchAddress("JetPFCorVBFTag_isPileUpJetLoose", JetPFCorVBFTag_isPileUpJetLoose, &b_JetPFCorVBFTag_isPileUpJetLoose);
   fChain->SetBranchAddress("JetPFCorVBFTag_isPileUpJetMedium", JetPFCorVBFTag_isPileUpJetMedium, &b_JetPFCorVBFTag_isPileUpJetMedium);
   fChain->SetBranchAddress("JetPFCorVBFTag_isPileUpJetTight", JetPFCorVBFTag_isPileUpJetTight, &b_JetPFCorVBFTag_isPileUpJetTight);
   fChain->SetBranchAddress("GroomedJet_AK5_pt_uncorr", GroomedJet_AK5_pt_uncorr, &b_GroomedJet_AK5_pt_uncorr);
   fChain->SetBranchAddress("GroomedJet_AK5_mass_uncorr", GroomedJet_AK5_mass_uncorr, &b_GroomedJet_AK5_mass_uncorr);
   fChain->SetBranchAddress("GroomedJet_AK5_mass_tr_uncorr", GroomedJet_AK5_mass_tr_uncorr, &b_GroomedJet_AK5_mass_tr_uncorr);
   fChain->SetBranchAddress("GroomedJet_AK5_mass_ft_uncorr", GroomedJet_AK5_mass_ft_uncorr, &b_GroomedJet_AK5_mass_ft_uncorr);
   fChain->SetBranchAddress("GroomedJet_AK5_mass_pr_uncorr", GroomedJet_AK5_mass_pr_uncorr, &b_GroomedJet_AK5_mass_pr_uncorr);
   fChain->SetBranchAddress("GroomedJet_AK5_tau2tau1", GroomedJet_AK5_tau2tau1, &b_GroomedJet_AK5_tau2tau1);
   fChain->SetBranchAddress("GroomedJet_AK5_tau1", GroomedJet_AK5_tau1, &b_GroomedJet_AK5_tau1);
   fChain->SetBranchAddress("GroomedJet_AK5_tau2", GroomedJet_AK5_tau2, &b_GroomedJet_AK5_tau2);
   fChain->SetBranchAddress("GroomedJet_AK5_tau3", GroomedJet_AK5_tau3, &b_GroomedJet_AK5_tau3);
   fChain->SetBranchAddress("GroomedJet_AK5_tau4", GroomedJet_AK5_tau4, &b_GroomedJet_AK5_tau4);
   fChain->SetBranchAddress("GroomedJet_AK5_massdrop_pr_uncorr", GroomedJet_AK5_massdrop_pr_uncorr, &b_GroomedJet_AK5_massdrop_pr_uncorr);
   fChain->SetBranchAddress("GroomedJet_AK5_pt", GroomedJet_AK5_pt, &b_GroomedJet_AK5_pt);
   fChain->SetBranchAddress("GroomedJet_AK5_eta", GroomedJet_AK5_eta, &b_GroomedJet_AK5_eta);
   fChain->SetBranchAddress("GroomedJet_AK5_phi", GroomedJet_AK5_phi, &b_GroomedJet_AK5_phi);
   fChain->SetBranchAddress("GroomedJet_AK5_e", GroomedJet_AK5_e, &b_GroomedJet_AK5_e);
   fChain->SetBranchAddress("GroomedJet_AK5_pt_tr_uncorr", GroomedJet_AK5_pt_tr_uncorr, &b_GroomedJet_AK5_pt_tr_uncorr);
   fChain->SetBranchAddress("GroomedJet_AK5_pt_tr", GroomedJet_AK5_pt_tr, &b_GroomedJet_AK5_pt_tr);
   fChain->SetBranchAddress("GroomedJet_AK5_eta_tr", GroomedJet_AK5_eta_tr, &b_GroomedJet_AK5_eta_tr);
   fChain->SetBranchAddress("GroomedJet_AK5_phi_tr", GroomedJet_AK5_phi_tr, &b_GroomedJet_AK5_phi_tr);
   fChain->SetBranchAddress("GroomedJet_AK5_e_tr", GroomedJet_AK5_e_tr, &b_GroomedJet_AK5_e_tr);
   fChain->SetBranchAddress("GroomedJet_AK5_pt_ft_uncorr", GroomedJet_AK5_pt_ft_uncorr, &b_GroomedJet_AK5_pt_ft_uncorr);
   fChain->SetBranchAddress("GroomedJet_AK5_pt_ft", GroomedJet_AK5_pt_ft, &b_GroomedJet_AK5_pt_ft);
   fChain->SetBranchAddress("GroomedJet_AK5_eta_ft", GroomedJet_AK5_eta_ft, &b_GroomedJet_AK5_eta_ft);
   fChain->SetBranchAddress("GroomedJet_AK5_phi_ft", GroomedJet_AK5_phi_ft, &b_GroomedJet_AK5_phi_ft);
   fChain->SetBranchAddress("GroomedJet_AK5_e_ft", GroomedJet_AK5_e_ft, &b_GroomedJet_AK5_e_ft);
   fChain->SetBranchAddress("GroomedJet_AK5_pt_pr_uncorr", GroomedJet_AK5_pt_pr_uncorr, &b_GroomedJet_AK5_pt_pr_uncorr);
   fChain->SetBranchAddress("GroomedJet_AK5_pt_pr", GroomedJet_AK5_pt_pr, &b_GroomedJet_AK5_pt_pr);
   fChain->SetBranchAddress("GroomedJet_AK5_eta_pr", GroomedJet_AK5_eta_pr, &b_GroomedJet_AK5_eta_pr);
   fChain->SetBranchAddress("GroomedJet_AK5_phi_pr", GroomedJet_AK5_phi_pr, &b_GroomedJet_AK5_phi_pr);
   fChain->SetBranchAddress("GroomedJet_AK5_e_pr", GroomedJet_AK5_e_pr, &b_GroomedJet_AK5_e_pr);
   fChain->SetBranchAddress("GroomedJet_AK5_prsubjet1_px", GroomedJet_AK5_prsubjet1_px, &b_GroomedJet_AK5_prsubjet1_px);
   fChain->SetBranchAddress("GroomedJet_AK5_prsubjet1_py", GroomedJet_AK5_prsubjet1_py, &b_GroomedJet_AK5_prsubjet1_py);
   fChain->SetBranchAddress("GroomedJet_AK5_prsubjet1_pz", GroomedJet_AK5_prsubjet1_pz, &b_GroomedJet_AK5_prsubjet1_pz);
   fChain->SetBranchAddress("GroomedJet_AK5_prsubjet1_e", GroomedJet_AK5_prsubjet1_e, &b_GroomedJet_AK5_prsubjet1_e);
   fChain->SetBranchAddress("GroomedJet_AK5_prsubjet2_px", GroomedJet_AK5_prsubjet2_px, &b_GroomedJet_AK5_prsubjet2_px);
   fChain->SetBranchAddress("GroomedJet_AK5_prsubjet2_py", GroomedJet_AK5_prsubjet2_py, &b_GroomedJet_AK5_prsubjet2_py);
   fChain->SetBranchAddress("GroomedJet_AK5_prsubjet2_pz", GroomedJet_AK5_prsubjet2_pz, &b_GroomedJet_AK5_prsubjet2_pz);
   fChain->SetBranchAddress("GroomedJet_AK5_prsubjet2_e", GroomedJet_AK5_prsubjet2_e, &b_GroomedJet_AK5_prsubjet2_e);
   fChain->SetBranchAddress("GroomedJet_AK5_mass", GroomedJet_AK5_mass, &b_GroomedJet_AK5_mass);
   fChain->SetBranchAddress("GroomedJet_AK5_mass_tr", GroomedJet_AK5_mass_tr, &b_GroomedJet_AK5_mass_tr);
   fChain->SetBranchAddress("GroomedJet_AK5_mass_ft", GroomedJet_AK5_mass_ft, &b_GroomedJet_AK5_mass_ft);
   fChain->SetBranchAddress("GroomedJet_AK5_mass_pr", GroomedJet_AK5_mass_pr, &b_GroomedJet_AK5_mass_pr);
   fChain->SetBranchAddress("GroomedJet_AK5_massdrop_pr", GroomedJet_AK5_massdrop_pr, &b_GroomedJet_AK5_massdrop_pr);
   fChain->SetBranchAddress("GroomedJet_AK5_area", GroomedJet_AK5_area, &b_GroomedJet_AK5_area);
   fChain->SetBranchAddress("GroomedJet_AK5_area_tr", GroomedJet_AK5_area_tr, &b_GroomedJet_AK5_area_tr);
   fChain->SetBranchAddress("GroomedJet_AK5_area_ft", GroomedJet_AK5_area_ft, &b_GroomedJet_AK5_area_ft);
   fChain->SetBranchAddress("GroomedJet_AK5_area_pr", GroomedJet_AK5_area_pr, &b_GroomedJet_AK5_area_pr);
   fChain->SetBranchAddress("GroomedJet_AK5_jetconstituents", GroomedJet_AK5_jetconstituents, &b_GroomedJet_AK5_jetconstituents);
   fChain->SetBranchAddress("GroomedJet_AK5_jetcharge", GroomedJet_AK5_jetcharge, &b_GroomedJet_AK5_jetcharge);
   fChain->SetBranchAddress("GroomedJet_AK5_rcores", GroomedJet_AK5_rcores, &b_GroomedJet_AK5_rcores);
   fChain->SetBranchAddress("GroomedJet_AK5_ptcores", GroomedJet_AK5_ptcores, &b_GroomedJet_AK5_ptcores);
   fChain->SetBranchAddress("GroomedJet_AK5_planarflow", GroomedJet_AK5_planarflow, &b_GroomedJet_AK5_planarflow);
   fChain->SetBranchAddress("GroomedJet_AK5_qjetmass", GroomedJet_AK5_qjetmass, &b_GroomedJet_AK5_qjetmass);
   fChain->SetBranchAddress("GroomedJet_AK5_qjetmassdrop", GroomedJet_AK5_qjetmassdrop, &b_GroomedJet_AK5_qjetmassdrop);
   fChain->SetBranchAddress("GroomedJet_AK5_constituents0_eta", GroomedJet_AK5_constituents0_eta, &b_GroomedJet_AK5_constituents0_eta);
   fChain->SetBranchAddress("GroomedJet_AK5_constituents0_phi", GroomedJet_AK5_constituents0_phi, &b_GroomedJet_AK5_constituents0_phi);
   fChain->SetBranchAddress("GroomedJet_AK5_constituents0_e", GroomedJet_AK5_constituents0_e, &b_GroomedJet_AK5_constituents0_e);
   fChain->SetBranchAddress("GroomedJet_AK5_nconstituents0", &GroomedJet_AK5_nconstituents0, &b_GroomedJet_AK5_nconstituents0);
   fChain->SetBranchAddress("GroomedJet_AK5_constituents0pr_eta", GroomedJet_AK5_constituents0pr_eta, &b_GroomedJet_AK5_constituents0pr_eta);
   fChain->SetBranchAddress("GroomedJet_AK5_constituents0pr_phi", GroomedJet_AK5_constituents0pr_phi, &b_GroomedJet_AK5_constituents0pr_phi);
   fChain->SetBranchAddress("GroomedJet_AK5_constituents0pr_e", GroomedJet_AK5_constituents0pr_e, &b_GroomedJet_AK5_constituents0pr_e);
   fChain->SetBranchAddress("GroomedJet_AK5_nconstituents0pr", &GroomedJet_AK5_nconstituents0pr, &b_GroomedJet_AK5_nconstituents0pr);
   fChain->SetBranchAddress("GroomedJet_AK7_pt_uncorr", GroomedJet_AK7_pt_uncorr, &b_GroomedJet_AK7_pt_uncorr);
   fChain->SetBranchAddress("GroomedJet_AK7_mass_uncorr", GroomedJet_AK7_mass_uncorr, &b_GroomedJet_AK7_mass_uncorr);
   fChain->SetBranchAddress("GroomedJet_AK7_mass_tr_uncorr", GroomedJet_AK7_mass_tr_uncorr, &b_GroomedJet_AK7_mass_tr_uncorr);
   fChain->SetBranchAddress("GroomedJet_AK7_mass_ft_uncorr", GroomedJet_AK7_mass_ft_uncorr, &b_GroomedJet_AK7_mass_ft_uncorr);
   fChain->SetBranchAddress("GroomedJet_AK7_mass_pr_uncorr", GroomedJet_AK7_mass_pr_uncorr, &b_GroomedJet_AK7_mass_pr_uncorr);
   fChain->SetBranchAddress("GroomedJet_AK7_tau2tau1", GroomedJet_AK7_tau2tau1, &b_GroomedJet_AK7_tau2tau1);
   fChain->SetBranchAddress("GroomedJet_AK7_tau1", GroomedJet_AK7_tau1, &b_GroomedJet_AK7_tau1);
   fChain->SetBranchAddress("GroomedJet_AK7_tau2", GroomedJet_AK7_tau2, &b_GroomedJet_AK7_tau2);
   fChain->SetBranchAddress("GroomedJet_AK7_tau3", GroomedJet_AK7_tau3, &b_GroomedJet_AK7_tau3);
   fChain->SetBranchAddress("GroomedJet_AK7_tau4", GroomedJet_AK7_tau4, &b_GroomedJet_AK7_tau4);
   fChain->SetBranchAddress("GroomedJet_AK7_massdrop_pr_uncorr", GroomedJet_AK7_massdrop_pr_uncorr, &b_GroomedJet_AK7_massdrop_pr_uncorr);
   fChain->SetBranchAddress("GroomedJet_AK7_pt", GroomedJet_AK7_pt, &b_GroomedJet_AK7_pt);
   fChain->SetBranchAddress("GroomedJet_AK7_eta", GroomedJet_AK7_eta, &b_GroomedJet_AK7_eta);
   fChain->SetBranchAddress("GroomedJet_AK7_phi", GroomedJet_AK7_phi, &b_GroomedJet_AK7_phi);
   fChain->SetBranchAddress("GroomedJet_AK7_e", GroomedJet_AK7_e, &b_GroomedJet_AK7_e);
   fChain->SetBranchAddress("GroomedJet_AK7_pt_tr_uncorr", GroomedJet_AK7_pt_tr_uncorr, &b_GroomedJet_AK7_pt_tr_uncorr);
   fChain->SetBranchAddress("GroomedJet_AK7_pt_tr", GroomedJet_AK7_pt_tr, &b_GroomedJet_AK7_pt_tr);
   fChain->SetBranchAddress("GroomedJet_AK7_eta_tr", GroomedJet_AK7_eta_tr, &b_GroomedJet_AK7_eta_tr);
   fChain->SetBranchAddress("GroomedJet_AK7_phi_tr", GroomedJet_AK7_phi_tr, &b_GroomedJet_AK7_phi_tr);
   fChain->SetBranchAddress("GroomedJet_AK7_e_tr", GroomedJet_AK7_e_tr, &b_GroomedJet_AK7_e_tr);
   fChain->SetBranchAddress("GroomedJet_AK7_pt_ft_uncorr", GroomedJet_AK7_pt_ft_uncorr, &b_GroomedJet_AK7_pt_ft_uncorr);
   fChain->SetBranchAddress("GroomedJet_AK7_pt_ft", GroomedJet_AK7_pt_ft, &b_GroomedJet_AK7_pt_ft);
   fChain->SetBranchAddress("GroomedJet_AK7_eta_ft", GroomedJet_AK7_eta_ft, &b_GroomedJet_AK7_eta_ft);
   fChain->SetBranchAddress("GroomedJet_AK7_phi_ft", GroomedJet_AK7_phi_ft, &b_GroomedJet_AK7_phi_ft);
   fChain->SetBranchAddress("GroomedJet_AK7_e_ft", GroomedJet_AK7_e_ft, &b_GroomedJet_AK7_e_ft);
   fChain->SetBranchAddress("GroomedJet_AK7_pt_pr_uncorr", GroomedJet_AK7_pt_pr_uncorr, &b_GroomedJet_AK7_pt_pr_uncorr);
   fChain->SetBranchAddress("GroomedJet_AK7_pt_pr", GroomedJet_AK7_pt_pr, &b_GroomedJet_AK7_pt_pr);
   fChain->SetBranchAddress("GroomedJet_AK7_eta_pr", GroomedJet_AK7_eta_pr, &b_GroomedJet_AK7_eta_pr);
   fChain->SetBranchAddress("GroomedJet_AK7_phi_pr", GroomedJet_AK7_phi_pr, &b_GroomedJet_AK7_phi_pr);
   fChain->SetBranchAddress("GroomedJet_AK7_e_pr", GroomedJet_AK7_e_pr, &b_GroomedJet_AK7_e_pr);
   fChain->SetBranchAddress("GroomedJet_AK7_prsubjet1_px", GroomedJet_AK7_prsubjet1_px, &b_GroomedJet_AK7_prsubjet1_px);
   fChain->SetBranchAddress("GroomedJet_AK7_prsubjet1_py", GroomedJet_AK7_prsubjet1_py, &b_GroomedJet_AK7_prsubjet1_py);
   fChain->SetBranchAddress("GroomedJet_AK7_prsubjet1_pz", GroomedJet_AK7_prsubjet1_pz, &b_GroomedJet_AK7_prsubjet1_pz);
   fChain->SetBranchAddress("GroomedJet_AK7_prsubjet1_e", GroomedJet_AK7_prsubjet1_e, &b_GroomedJet_AK7_prsubjet1_e);
   fChain->SetBranchAddress("GroomedJet_AK7_prsubjet2_px", GroomedJet_AK7_prsubjet2_px, &b_GroomedJet_AK7_prsubjet2_px);
   fChain->SetBranchAddress("GroomedJet_AK7_prsubjet2_py", GroomedJet_AK7_prsubjet2_py, &b_GroomedJet_AK7_prsubjet2_py);
   fChain->SetBranchAddress("GroomedJet_AK7_prsubjet2_pz", GroomedJet_AK7_prsubjet2_pz, &b_GroomedJet_AK7_prsubjet2_pz);
   fChain->SetBranchAddress("GroomedJet_AK7_prsubjet2_e", GroomedJet_AK7_prsubjet2_e, &b_GroomedJet_AK7_prsubjet2_e);
   fChain->SetBranchAddress("GroomedJet_AK7_mass", GroomedJet_AK7_mass, &b_GroomedJet_AK7_mass);
   fChain->SetBranchAddress("GroomedJet_AK7_mass_tr", GroomedJet_AK7_mass_tr, &b_GroomedJet_AK7_mass_tr);
   fChain->SetBranchAddress("GroomedJet_AK7_mass_ft", GroomedJet_AK7_mass_ft, &b_GroomedJet_AK7_mass_ft);
   fChain->SetBranchAddress("GroomedJet_AK7_mass_pr", GroomedJet_AK7_mass_pr, &b_GroomedJet_AK7_mass_pr);
   fChain->SetBranchAddress("GroomedJet_AK7_massdrop_pr", GroomedJet_AK7_massdrop_pr, &b_GroomedJet_AK7_massdrop_pr);
   fChain->SetBranchAddress("GroomedJet_AK7_area", GroomedJet_AK7_area, &b_GroomedJet_AK7_area);
   fChain->SetBranchAddress("GroomedJet_AK7_area_tr", GroomedJet_AK7_area_tr, &b_GroomedJet_AK7_area_tr);
   fChain->SetBranchAddress("GroomedJet_AK7_area_ft", GroomedJet_AK7_area_ft, &b_GroomedJet_AK7_area_ft);
   fChain->SetBranchAddress("GroomedJet_AK7_area_pr", GroomedJet_AK7_area_pr, &b_GroomedJet_AK7_area_pr);
   fChain->SetBranchAddress("GroomedJet_AK7_jetconstituents", GroomedJet_AK7_jetconstituents, &b_GroomedJet_AK7_jetconstituents);
   fChain->SetBranchAddress("GroomedJet_AK7_jetcharge", GroomedJet_AK7_jetcharge, &b_GroomedJet_AK7_jetcharge);
   fChain->SetBranchAddress("GroomedJet_AK7_rcores", GroomedJet_AK7_rcores, &b_GroomedJet_AK7_rcores);
   fChain->SetBranchAddress("GroomedJet_AK7_ptcores", GroomedJet_AK7_ptcores, &b_GroomedJet_AK7_ptcores);
   fChain->SetBranchAddress("GroomedJet_AK7_planarflow", GroomedJet_AK7_planarflow, &b_GroomedJet_AK7_planarflow);
   fChain->SetBranchAddress("GroomedJet_AK7_qjetmass", GroomedJet_AK7_qjetmass, &b_GroomedJet_AK7_qjetmass);
   fChain->SetBranchAddress("GroomedJet_AK7_qjetmassdrop", GroomedJet_AK7_qjetmassdrop, &b_GroomedJet_AK7_qjetmassdrop);
   fChain->SetBranchAddress("GroomedJet_AK7_constituents0_eta", GroomedJet_AK7_constituents0_eta, &b_GroomedJet_AK7_constituents0_eta);
   fChain->SetBranchAddress("GroomedJet_AK7_constituents0_phi", GroomedJet_AK7_constituents0_phi, &b_GroomedJet_AK7_constituents0_phi);
   fChain->SetBranchAddress("GroomedJet_AK7_constituents0_e", GroomedJet_AK7_constituents0_e, &b_GroomedJet_AK7_constituents0_e);
   fChain->SetBranchAddress("GroomedJet_AK7_nconstituents0", &GroomedJet_AK7_nconstituents0, &b_GroomedJet_AK7_nconstituents0);
   fChain->SetBranchAddress("GroomedJet_AK7_constituents0pr_eta", GroomedJet_AK7_constituents0pr_eta, &b_GroomedJet_AK7_constituents0pr_eta);
   fChain->SetBranchAddress("GroomedJet_AK7_constituents0pr_phi", GroomedJet_AK7_constituents0pr_phi, &b_GroomedJet_AK7_constituents0pr_phi);
   fChain->SetBranchAddress("GroomedJet_AK7_constituents0pr_e", GroomedJet_AK7_constituents0pr_e, &b_GroomedJet_AK7_constituents0pr_e);
   fChain->SetBranchAddress("GroomedJet_AK7_nconstituents0pr", &GroomedJet_AK7_nconstituents0pr, &b_GroomedJet_AK7_nconstituents0pr);
   fChain->SetBranchAddress("GroomedJet_CA8_pt_uncorr", GroomedJet_CA8_pt_uncorr, &b_GroomedJet_CA8_pt_uncorr);
   fChain->SetBranchAddress("GroomedJet_CA8_mass_uncorr", GroomedJet_CA8_mass_uncorr, &b_GroomedJet_CA8_mass_uncorr);
   fChain->SetBranchAddress("GroomedJet_CA8_mass_tr_uncorr", GroomedJet_CA8_mass_tr_uncorr, &b_GroomedJet_CA8_mass_tr_uncorr);
   fChain->SetBranchAddress("GroomedJet_CA8_mass_ft_uncorr", GroomedJet_CA8_mass_ft_uncorr, &b_GroomedJet_CA8_mass_ft_uncorr);
   fChain->SetBranchAddress("GroomedJet_CA8_mass_pr_uncorr", GroomedJet_CA8_mass_pr_uncorr, &b_GroomedJet_CA8_mass_pr_uncorr);
   fChain->SetBranchAddress("GroomedJet_CA8_tau2tau1", GroomedJet_CA8_tau2tau1, &b_GroomedJet_CA8_tau2tau1);
   fChain->SetBranchAddress("GroomedJet_CA8_tau1", GroomedJet_CA8_tau1, &b_GroomedJet_CA8_tau1);
   fChain->SetBranchAddress("GroomedJet_CA8_tau2", GroomedJet_CA8_tau2, &b_GroomedJet_CA8_tau2);
   fChain->SetBranchAddress("GroomedJet_CA8_tau3", GroomedJet_CA8_tau3, &b_GroomedJet_CA8_tau3);
   fChain->SetBranchAddress("GroomedJet_CA8_tau4", GroomedJet_CA8_tau4, &b_GroomedJet_CA8_tau4);
   fChain->SetBranchAddress("GroomedJet_CA8_massdrop_pr_uncorr", GroomedJet_CA8_massdrop_pr_uncorr, &b_GroomedJet_CA8_massdrop_pr_uncorr);
   fChain->SetBranchAddress("GroomedJet_CA8_pt", GroomedJet_CA8_pt, &b_GroomedJet_CA8_pt);
   fChain->SetBranchAddress("GroomedJet_CA8_eta", GroomedJet_CA8_eta, &b_GroomedJet_CA8_eta);
   fChain->SetBranchAddress("GroomedJet_CA8_phi", GroomedJet_CA8_phi, &b_GroomedJet_CA8_phi);
   fChain->SetBranchAddress("GroomedJet_CA8_e", GroomedJet_CA8_e, &b_GroomedJet_CA8_e);
   fChain->SetBranchAddress("GroomedJet_CA8_pt_tr_uncorr", GroomedJet_CA8_pt_tr_uncorr, &b_GroomedJet_CA8_pt_tr_uncorr);
   fChain->SetBranchAddress("GroomedJet_CA8_pt_tr", GroomedJet_CA8_pt_tr, &b_GroomedJet_CA8_pt_tr);
   fChain->SetBranchAddress("GroomedJet_CA8_eta_tr", GroomedJet_CA8_eta_tr, &b_GroomedJet_CA8_eta_tr);
   fChain->SetBranchAddress("GroomedJet_CA8_phi_tr", GroomedJet_CA8_phi_tr, &b_GroomedJet_CA8_phi_tr);
   fChain->SetBranchAddress("GroomedJet_CA8_e_tr", GroomedJet_CA8_e_tr, &b_GroomedJet_CA8_e_tr);
   fChain->SetBranchAddress("GroomedJet_CA8_pt_ft_uncorr", GroomedJet_CA8_pt_ft_uncorr, &b_GroomedJet_CA8_pt_ft_uncorr);
   fChain->SetBranchAddress("GroomedJet_CA8_pt_ft", GroomedJet_CA8_pt_ft, &b_GroomedJet_CA8_pt_ft);
   fChain->SetBranchAddress("GroomedJet_CA8_eta_ft", GroomedJet_CA8_eta_ft, &b_GroomedJet_CA8_eta_ft);
   fChain->SetBranchAddress("GroomedJet_CA8_phi_ft", GroomedJet_CA8_phi_ft, &b_GroomedJet_CA8_phi_ft);
   fChain->SetBranchAddress("GroomedJet_CA8_e_ft", GroomedJet_CA8_e_ft, &b_GroomedJet_CA8_e_ft);
   fChain->SetBranchAddress("GroomedJet_CA8_pt_pr_uncorr", GroomedJet_CA8_pt_pr_uncorr, &b_GroomedJet_CA8_pt_pr_uncorr);
   fChain->SetBranchAddress("GroomedJet_CA8_pt_pr", GroomedJet_CA8_pt_pr, &b_GroomedJet_CA8_pt_pr);
   fChain->SetBranchAddress("GroomedJet_CA8_eta_pr", GroomedJet_CA8_eta_pr, &b_GroomedJet_CA8_eta_pr);
   fChain->SetBranchAddress("GroomedJet_CA8_phi_pr", GroomedJet_CA8_phi_pr, &b_GroomedJet_CA8_phi_pr);
   fChain->SetBranchAddress("GroomedJet_CA8_e_pr", GroomedJet_CA8_e_pr, &b_GroomedJet_CA8_e_pr);
   fChain->SetBranchAddress("GroomedJet_CA8_prsubjet1_px", GroomedJet_CA8_prsubjet1_px, &b_GroomedJet_CA8_prsubjet1_px);
   fChain->SetBranchAddress("GroomedJet_CA8_prsubjet1_py", GroomedJet_CA8_prsubjet1_py, &b_GroomedJet_CA8_prsubjet1_py);
   fChain->SetBranchAddress("GroomedJet_CA8_prsubjet1_pz", GroomedJet_CA8_prsubjet1_pz, &b_GroomedJet_CA8_prsubjet1_pz);
   fChain->SetBranchAddress("GroomedJet_CA8_prsubjet1_e", GroomedJet_CA8_prsubjet1_e, &b_GroomedJet_CA8_prsubjet1_e);
   fChain->SetBranchAddress("GroomedJet_CA8_prsubjet2_px", GroomedJet_CA8_prsubjet2_px, &b_GroomedJet_CA8_prsubjet2_px);
   fChain->SetBranchAddress("GroomedJet_CA8_prsubjet2_py", GroomedJet_CA8_prsubjet2_py, &b_GroomedJet_CA8_prsubjet2_py);
   fChain->SetBranchAddress("GroomedJet_CA8_prsubjet2_pz", GroomedJet_CA8_prsubjet2_pz, &b_GroomedJet_CA8_prsubjet2_pz);
   fChain->SetBranchAddress("GroomedJet_CA8_prsubjet2_e", GroomedJet_CA8_prsubjet2_e, &b_GroomedJet_CA8_prsubjet2_e);
   fChain->SetBranchAddress("GroomedJet_CA8_mass", GroomedJet_CA8_mass, &b_GroomedJet_CA8_mass);
   fChain->SetBranchAddress("GroomedJet_CA8_mass_tr", GroomedJet_CA8_mass_tr, &b_GroomedJet_CA8_mass_tr);
   fChain->SetBranchAddress("GroomedJet_CA8_mass_ft", GroomedJet_CA8_mass_ft, &b_GroomedJet_CA8_mass_ft);
   fChain->SetBranchAddress("GroomedJet_CA8_mass_pr", GroomedJet_CA8_mass_pr, &b_GroomedJet_CA8_mass_pr);
   fChain->SetBranchAddress("GroomedJet_CA8_massdrop_pr", GroomedJet_CA8_massdrop_pr, &b_GroomedJet_CA8_massdrop_pr);
   fChain->SetBranchAddress("GroomedJet_CA8_area", GroomedJet_CA8_area, &b_GroomedJet_CA8_area);
   fChain->SetBranchAddress("GroomedJet_CA8_area_tr", GroomedJet_CA8_area_tr, &b_GroomedJet_CA8_area_tr);
   fChain->SetBranchAddress("GroomedJet_CA8_area_ft", GroomedJet_CA8_area_ft, &b_GroomedJet_CA8_area_ft);
   fChain->SetBranchAddress("GroomedJet_CA8_area_pr", GroomedJet_CA8_area_pr, &b_GroomedJet_CA8_area_pr);
   fChain->SetBranchAddress("GroomedJet_CA8_jetconstituents", GroomedJet_CA8_jetconstituents, &b_GroomedJet_CA8_jetconstituents);
   fChain->SetBranchAddress("GroomedJet_CA8_jetcharge", GroomedJet_CA8_jetcharge, &b_GroomedJet_CA8_jetcharge);
   fChain->SetBranchAddress("GroomedJet_CA8_rcores", GroomedJet_CA8_rcores, &b_GroomedJet_CA8_rcores);
   fChain->SetBranchAddress("GroomedJet_CA8_ptcores", GroomedJet_CA8_ptcores, &b_GroomedJet_CA8_ptcores);
   fChain->SetBranchAddress("GroomedJet_CA8_planarflow", GroomedJet_CA8_planarflow, &b_GroomedJet_CA8_planarflow);
   fChain->SetBranchAddress("GroomedJet_CA8_qjetmass", GroomedJet_CA8_qjetmass, &b_GroomedJet_CA8_qjetmass);
   fChain->SetBranchAddress("GroomedJet_CA8_qjetmassdrop", GroomedJet_CA8_qjetmassdrop, &b_GroomedJet_CA8_qjetmassdrop);
   fChain->SetBranchAddress("GroomedJet_CA8_constituents0_eta", GroomedJet_CA8_constituents0_eta, &b_GroomedJet_CA8_constituents0_eta);
   fChain->SetBranchAddress("GroomedJet_CA8_constituents0_phi", GroomedJet_CA8_constituents0_phi, &b_GroomedJet_CA8_constituents0_phi);
   fChain->SetBranchAddress("GroomedJet_CA8_constituents0_e", GroomedJet_CA8_constituents0_e, &b_GroomedJet_CA8_constituents0_e);
   fChain->SetBranchAddress("GroomedJet_CA8_nconstituents0", &GroomedJet_CA8_nconstituents0, &b_GroomedJet_CA8_nconstituents0);
   fChain->SetBranchAddress("GroomedJet_CA8_constituents0pr_eta", GroomedJet_CA8_constituents0pr_eta, &b_GroomedJet_CA8_constituents0pr_eta);
   fChain->SetBranchAddress("GroomedJet_CA8_constituents0pr_phi", GroomedJet_CA8_constituents0pr_phi, &b_GroomedJet_CA8_constituents0pr_phi);
   fChain->SetBranchAddress("GroomedJet_CA8_constituents0pr_e", GroomedJet_CA8_constituents0pr_e, &b_GroomedJet_CA8_constituents0pr_e);
   fChain->SetBranchAddress("GroomedJet_CA8_nconstituents0pr", &GroomedJet_CA8_nconstituents0pr, &b_GroomedJet_CA8_nconstituents0pr);
   fChain->SetBranchAddress("GenGroomedJet_AK5_pt_uncorr", GenGroomedJet_AK5_pt_uncorr, &b_GenGroomedJet_AK5_pt_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_AK5_mass_uncorr", GenGroomedJet_AK5_mass_uncorr, &b_GenGroomedJet_AK5_mass_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_AK5_mass_tr_uncorr", GenGroomedJet_AK5_mass_tr_uncorr, &b_GenGroomedJet_AK5_mass_tr_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_AK5_mass_ft_uncorr", GenGroomedJet_AK5_mass_ft_uncorr, &b_GenGroomedJet_AK5_mass_ft_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_AK5_mass_pr_uncorr", GenGroomedJet_AK5_mass_pr_uncorr, &b_GenGroomedJet_AK5_mass_pr_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_AK5_tau2tau1", GenGroomedJet_AK5_tau2tau1, &b_GenGroomedJet_AK5_tau2tau1);
   fChain->SetBranchAddress("GenGroomedJet_AK5_tau1", GenGroomedJet_AK5_tau1, &b_GenGroomedJet_AK5_tau1);
   fChain->SetBranchAddress("GenGroomedJet_AK5_tau2", GenGroomedJet_AK5_tau2, &b_GenGroomedJet_AK5_tau2);
   fChain->SetBranchAddress("GenGroomedJet_AK5_tau3", GenGroomedJet_AK5_tau3, &b_GenGroomedJet_AK5_tau3);
   fChain->SetBranchAddress("GenGroomedJet_AK5_tau4", GenGroomedJet_AK5_tau4, &b_GenGroomedJet_AK5_tau4);
   fChain->SetBranchAddress("GenGroomedJet_AK5_massdrop_pr_uncorr", GenGroomedJet_AK5_massdrop_pr_uncorr, &b_GenGroomedJet_AK5_massdrop_pr_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_AK5_pt", GenGroomedJet_AK5_pt, &b_GenGroomedJet_AK5_pt);
   fChain->SetBranchAddress("GenGroomedJet_AK5_eta", GenGroomedJet_AK5_eta, &b_GenGroomedJet_AK5_eta);
   fChain->SetBranchAddress("GenGroomedJet_AK5_phi", GenGroomedJet_AK5_phi, &b_GenGroomedJet_AK5_phi);
   fChain->SetBranchAddress("GenGroomedJet_AK5_e", GenGroomedJet_AK5_e, &b_GenGroomedJet_AK5_e);
   fChain->SetBranchAddress("GenGroomedJet_AK5_pt_tr_uncorr", GenGroomedJet_AK5_pt_tr_uncorr, &b_GenGroomedJet_AK5_pt_tr_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_AK5_pt_tr", GenGroomedJet_AK5_pt_tr, &b_GenGroomedJet_AK5_pt_tr);
   fChain->SetBranchAddress("GenGroomedJet_AK5_eta_tr", GenGroomedJet_AK5_eta_tr, &b_GenGroomedJet_AK5_eta_tr);
   fChain->SetBranchAddress("GenGroomedJet_AK5_phi_tr", GenGroomedJet_AK5_phi_tr, &b_GenGroomedJet_AK5_phi_tr);
   fChain->SetBranchAddress("GenGroomedJet_AK5_e_tr", GenGroomedJet_AK5_e_tr, &b_GenGroomedJet_AK5_e_tr);
   fChain->SetBranchAddress("GenGroomedJet_AK5_pt_ft_uncorr", GenGroomedJet_AK5_pt_ft_uncorr, &b_GenGroomedJet_AK5_pt_ft_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_AK5_pt_ft", GenGroomedJet_AK5_pt_ft, &b_GenGroomedJet_AK5_pt_ft);
   fChain->SetBranchAddress("GenGroomedJet_AK5_eta_ft", GenGroomedJet_AK5_eta_ft, &b_GenGroomedJet_AK5_eta_ft);
   fChain->SetBranchAddress("GenGroomedJet_AK5_phi_ft", GenGroomedJet_AK5_phi_ft, &b_GenGroomedJet_AK5_phi_ft);
   fChain->SetBranchAddress("GenGroomedJet_AK5_e_ft", GenGroomedJet_AK5_e_ft, &b_GenGroomedJet_AK5_e_ft);
   fChain->SetBranchAddress("GenGroomedJet_AK5_pt_pr_uncorr", GenGroomedJet_AK5_pt_pr_uncorr, &b_GenGroomedJet_AK5_pt_pr_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_AK5_pt_pr", GenGroomedJet_AK5_pt_pr, &b_GenGroomedJet_AK5_pt_pr);
   fChain->SetBranchAddress("GenGroomedJet_AK5_eta_pr", GenGroomedJet_AK5_eta_pr, &b_GenGroomedJet_AK5_eta_pr);
   fChain->SetBranchAddress("GenGroomedJet_AK5_phi_pr", GenGroomedJet_AK5_phi_pr, &b_GenGroomedJet_AK5_phi_pr);
   fChain->SetBranchAddress("GenGroomedJet_AK5_e_pr", GenGroomedJet_AK5_e_pr, &b_GenGroomedJet_AK5_e_pr);
   fChain->SetBranchAddress("GenGroomedJet_AK5_prsubjet1_px", GenGroomedJet_AK5_prsubjet1_px, &b_GenGroomedJet_AK5_prsubjet1_px);
   fChain->SetBranchAddress("GenGroomedJet_AK5_prsubjet1_py", GenGroomedJet_AK5_prsubjet1_py, &b_GenGroomedJet_AK5_prsubjet1_py);
   fChain->SetBranchAddress("GenGroomedJet_AK5_prsubjet1_pz", GenGroomedJet_AK5_prsubjet1_pz, &b_GenGroomedJet_AK5_prsubjet1_pz);
   fChain->SetBranchAddress("GenGroomedJet_AK5_prsubjet1_e", GenGroomedJet_AK5_prsubjet1_e, &b_GenGroomedJet_AK5_prsubjet1_e);
   fChain->SetBranchAddress("GenGroomedJet_AK5_prsubjet2_px", GenGroomedJet_AK5_prsubjet2_px, &b_GenGroomedJet_AK5_prsubjet2_px);
   fChain->SetBranchAddress("GenGroomedJet_AK5_prsubjet2_py", GenGroomedJet_AK5_prsubjet2_py, &b_GenGroomedJet_AK5_prsubjet2_py);
   fChain->SetBranchAddress("GenGroomedJet_AK5_prsubjet2_pz", GenGroomedJet_AK5_prsubjet2_pz, &b_GenGroomedJet_AK5_prsubjet2_pz);
   fChain->SetBranchAddress("GenGroomedJet_AK5_prsubjet2_e", GenGroomedJet_AK5_prsubjet2_e, &b_GenGroomedJet_AK5_prsubjet2_e);
   fChain->SetBranchAddress("GenGroomedJet_AK5_mass", GenGroomedJet_AK5_mass, &b_GenGroomedJet_AK5_mass);
   fChain->SetBranchAddress("GenGroomedJet_AK5_mass_tr", GenGroomedJet_AK5_mass_tr, &b_GenGroomedJet_AK5_mass_tr);
   fChain->SetBranchAddress("GenGroomedJet_AK5_mass_ft", GenGroomedJet_AK5_mass_ft, &b_GenGroomedJet_AK5_mass_ft);
   fChain->SetBranchAddress("GenGroomedJet_AK5_mass_pr", GenGroomedJet_AK5_mass_pr, &b_GenGroomedJet_AK5_mass_pr);
   fChain->SetBranchAddress("GenGroomedJet_AK5_massdrop_pr", GenGroomedJet_AK5_massdrop_pr, &b_GenGroomedJet_AK5_massdrop_pr);
   fChain->SetBranchAddress("GenGroomedJet_AK5_area", GenGroomedJet_AK5_area, &b_GenGroomedJet_AK5_area);
   fChain->SetBranchAddress("GenGroomedJet_AK5_area_tr", GenGroomedJet_AK5_area_tr, &b_GenGroomedJet_AK5_area_tr);
   fChain->SetBranchAddress("GenGroomedJet_AK5_area_ft", GenGroomedJet_AK5_area_ft, &b_GenGroomedJet_AK5_area_ft);
   fChain->SetBranchAddress("GenGroomedJet_AK5_area_pr", GenGroomedJet_AK5_area_pr, &b_GenGroomedJet_AK5_area_pr);
   fChain->SetBranchAddress("GenGroomedJet_AK5_jetconstituents", GenGroomedJet_AK5_jetconstituents, &b_GenGroomedJet_AK5_jetconstituents);
   fChain->SetBranchAddress("GenGroomedJet_AK5_jetcharge", GenGroomedJet_AK5_jetcharge, &b_GenGroomedJet_AK5_jetcharge);
   fChain->SetBranchAddress("GenGroomedJet_AK5_rcores", GenGroomedJet_AK5_rcores, &b_GenGroomedJet_AK5_rcores);
   fChain->SetBranchAddress("GenGroomedJet_AK5_ptcores", GenGroomedJet_AK5_ptcores, &b_GenGroomedJet_AK5_ptcores);
   fChain->SetBranchAddress("GenGroomedJet_AK5_planarflow", GenGroomedJet_AK5_planarflow, &b_GenGroomedJet_AK5_planarflow);
   fChain->SetBranchAddress("GenGroomedJet_AK5_qjetmass", GenGroomedJet_AK5_qjetmass, &b_GenGroomedJet_AK5_qjetmass);
   fChain->SetBranchAddress("GenGroomedJet_AK5_qjetmassdrop", GenGroomedJet_AK5_qjetmassdrop, &b_GenGroomedJet_AK5_qjetmassdrop);
   fChain->SetBranchAddress("GenGroomedJet_AK5_constituents0_eta", GenGroomedJet_AK5_constituents0_eta, &b_GenGroomedJet_AK5_constituents0_eta);
   fChain->SetBranchAddress("GenGroomedJet_AK5_constituents0_phi", GenGroomedJet_AK5_constituents0_phi, &b_GenGroomedJet_AK5_constituents0_phi);
   fChain->SetBranchAddress("GenGroomedJet_AK5_constituents0_e", GenGroomedJet_AK5_constituents0_e, &b_GenGroomedJet_AK5_constituents0_e);
   fChain->SetBranchAddress("GenGroomedJet_AK5_nconstituents0", &GenGroomedJet_AK5_nconstituents0, &b_GenGroomedJet_AK5_nconstituents0);
   fChain->SetBranchAddress("GenGroomedJet_AK5_constituents0pr_eta", GenGroomedJet_AK5_constituents0pr_eta, &b_GenGroomedJet_AK5_constituents0pr_eta);
   fChain->SetBranchAddress("GenGroomedJet_AK5_constituents0pr_phi", GenGroomedJet_AK5_constituents0pr_phi, &b_GenGroomedJet_AK5_constituents0pr_phi);
   fChain->SetBranchAddress("GenGroomedJet_AK5_constituents0pr_e", GenGroomedJet_AK5_constituents0pr_e, &b_GenGroomedJet_AK5_constituents0pr_e);
   fChain->SetBranchAddress("GenGroomedJet_AK5_nconstituents0pr", &GenGroomedJet_AK5_nconstituents0pr, &b_GenGroomedJet_AK5_nconstituents0pr);
   fChain->SetBranchAddress("GenGroomedJet_AK7_pt_uncorr", GenGroomedJet_AK7_pt_uncorr, &b_GenGroomedJet_AK7_pt_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_AK7_mass_uncorr", GenGroomedJet_AK7_mass_uncorr, &b_GenGroomedJet_AK7_mass_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_AK7_mass_tr_uncorr", GenGroomedJet_AK7_mass_tr_uncorr, &b_GenGroomedJet_AK7_mass_tr_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_AK7_mass_ft_uncorr", GenGroomedJet_AK7_mass_ft_uncorr, &b_GenGroomedJet_AK7_mass_ft_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_AK7_mass_pr_uncorr", GenGroomedJet_AK7_mass_pr_uncorr, &b_GenGroomedJet_AK7_mass_pr_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_AK7_tau2tau1", GenGroomedJet_AK7_tau2tau1, &b_GenGroomedJet_AK7_tau2tau1);
   fChain->SetBranchAddress("GenGroomedJet_AK7_tau1", GenGroomedJet_AK7_tau1, &b_GenGroomedJet_AK7_tau1);
   fChain->SetBranchAddress("GenGroomedJet_AK7_tau2", GenGroomedJet_AK7_tau2, &b_GenGroomedJet_AK7_tau2);
   fChain->SetBranchAddress("GenGroomedJet_AK7_tau3", GenGroomedJet_AK7_tau3, &b_GenGroomedJet_AK7_tau3);
   fChain->SetBranchAddress("GenGroomedJet_AK7_tau4", GenGroomedJet_AK7_tau4, &b_GenGroomedJet_AK7_tau4);
   fChain->SetBranchAddress("GenGroomedJet_AK7_massdrop_pr_uncorr", GenGroomedJet_AK7_massdrop_pr_uncorr, &b_GenGroomedJet_AK7_massdrop_pr_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_AK7_pt", GenGroomedJet_AK7_pt, &b_GenGroomedJet_AK7_pt);
   fChain->SetBranchAddress("GenGroomedJet_AK7_eta", GenGroomedJet_AK7_eta, &b_GenGroomedJet_AK7_eta);
   fChain->SetBranchAddress("GenGroomedJet_AK7_phi", GenGroomedJet_AK7_phi, &b_GenGroomedJet_AK7_phi);
   fChain->SetBranchAddress("GenGroomedJet_AK7_e", GenGroomedJet_AK7_e, &b_GenGroomedJet_AK7_e);
   fChain->SetBranchAddress("GenGroomedJet_AK7_pt_tr_uncorr", GenGroomedJet_AK7_pt_tr_uncorr, &b_GenGroomedJet_AK7_pt_tr_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_AK7_pt_tr", GenGroomedJet_AK7_pt_tr, &b_GenGroomedJet_AK7_pt_tr);
   fChain->SetBranchAddress("GenGroomedJet_AK7_eta_tr", GenGroomedJet_AK7_eta_tr, &b_GenGroomedJet_AK7_eta_tr);
   fChain->SetBranchAddress("GenGroomedJet_AK7_phi_tr", GenGroomedJet_AK7_phi_tr, &b_GenGroomedJet_AK7_phi_tr);
   fChain->SetBranchAddress("GenGroomedJet_AK7_e_tr", GenGroomedJet_AK7_e_tr, &b_GenGroomedJet_AK7_e_tr);
   fChain->SetBranchAddress("GenGroomedJet_AK7_pt_ft_uncorr", GenGroomedJet_AK7_pt_ft_uncorr, &b_GenGroomedJet_AK7_pt_ft_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_AK7_pt_ft", GenGroomedJet_AK7_pt_ft, &b_GenGroomedJet_AK7_pt_ft);
   fChain->SetBranchAddress("GenGroomedJet_AK7_eta_ft", GenGroomedJet_AK7_eta_ft, &b_GenGroomedJet_AK7_eta_ft);
   fChain->SetBranchAddress("GenGroomedJet_AK7_phi_ft", GenGroomedJet_AK7_phi_ft, &b_GenGroomedJet_AK7_phi_ft);
   fChain->SetBranchAddress("GenGroomedJet_AK7_e_ft", GenGroomedJet_AK7_e_ft, &b_GenGroomedJet_AK7_e_ft);
   fChain->SetBranchAddress("GenGroomedJet_AK7_pt_pr_uncorr", GenGroomedJet_AK7_pt_pr_uncorr, &b_GenGroomedJet_AK7_pt_pr_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_AK7_pt_pr", GenGroomedJet_AK7_pt_pr, &b_GenGroomedJet_AK7_pt_pr);
   fChain->SetBranchAddress("GenGroomedJet_AK7_eta_pr", GenGroomedJet_AK7_eta_pr, &b_GenGroomedJet_AK7_eta_pr);
   fChain->SetBranchAddress("GenGroomedJet_AK7_phi_pr", GenGroomedJet_AK7_phi_pr, &b_GenGroomedJet_AK7_phi_pr);
   fChain->SetBranchAddress("GenGroomedJet_AK7_e_pr", GenGroomedJet_AK7_e_pr, &b_GenGroomedJet_AK7_e_pr);
   fChain->SetBranchAddress("GenGroomedJet_AK7_prsubjet1_px", GenGroomedJet_AK7_prsubjet1_px, &b_GenGroomedJet_AK7_prsubjet1_px);
   fChain->SetBranchAddress("GenGroomedJet_AK7_prsubjet1_py", GenGroomedJet_AK7_prsubjet1_py, &b_GenGroomedJet_AK7_prsubjet1_py);
   fChain->SetBranchAddress("GenGroomedJet_AK7_prsubjet1_pz", GenGroomedJet_AK7_prsubjet1_pz, &b_GenGroomedJet_AK7_prsubjet1_pz);
   fChain->SetBranchAddress("GenGroomedJet_AK7_prsubjet1_e", GenGroomedJet_AK7_prsubjet1_e, &b_GenGroomedJet_AK7_prsubjet1_e);
   fChain->SetBranchAddress("GenGroomedJet_AK7_prsubjet2_px", GenGroomedJet_AK7_prsubjet2_px, &b_GenGroomedJet_AK7_prsubjet2_px);
   fChain->SetBranchAddress("GenGroomedJet_AK7_prsubjet2_py", GenGroomedJet_AK7_prsubjet2_py, &b_GenGroomedJet_AK7_prsubjet2_py);
   fChain->SetBranchAddress("GenGroomedJet_AK7_prsubjet2_pz", GenGroomedJet_AK7_prsubjet2_pz, &b_GenGroomedJet_AK7_prsubjet2_pz);
   fChain->SetBranchAddress("GenGroomedJet_AK7_prsubjet2_e", GenGroomedJet_AK7_prsubjet2_e, &b_GenGroomedJet_AK7_prsubjet2_e);
   fChain->SetBranchAddress("GenGroomedJet_AK7_mass", GenGroomedJet_AK7_mass, &b_GenGroomedJet_AK7_mass);
   fChain->SetBranchAddress("GenGroomedJet_AK7_mass_tr", GenGroomedJet_AK7_mass_tr, &b_GenGroomedJet_AK7_mass_tr);
   fChain->SetBranchAddress("GenGroomedJet_AK7_mass_ft", GenGroomedJet_AK7_mass_ft, &b_GenGroomedJet_AK7_mass_ft);
   fChain->SetBranchAddress("GenGroomedJet_AK7_mass_pr", GenGroomedJet_AK7_mass_pr, &b_GenGroomedJet_AK7_mass_pr);
   fChain->SetBranchAddress("GenGroomedJet_AK7_massdrop_pr", GenGroomedJet_AK7_massdrop_pr, &b_GenGroomedJet_AK7_massdrop_pr);
   fChain->SetBranchAddress("GenGroomedJet_AK7_area", GenGroomedJet_AK7_area, &b_GenGroomedJet_AK7_area);
   fChain->SetBranchAddress("GenGroomedJet_AK7_area_tr", GenGroomedJet_AK7_area_tr, &b_GenGroomedJet_AK7_area_tr);
   fChain->SetBranchAddress("GenGroomedJet_AK7_area_ft", GenGroomedJet_AK7_area_ft, &b_GenGroomedJet_AK7_area_ft);
   fChain->SetBranchAddress("GenGroomedJet_AK7_area_pr", GenGroomedJet_AK7_area_pr, &b_GenGroomedJet_AK7_area_pr);
   fChain->SetBranchAddress("GenGroomedJet_AK7_jetconstituents", GenGroomedJet_AK7_jetconstituents, &b_GenGroomedJet_AK7_jetconstituents);
   fChain->SetBranchAddress("GenGroomedJet_AK7_jetcharge", GenGroomedJet_AK7_jetcharge, &b_GenGroomedJet_AK7_jetcharge);
   fChain->SetBranchAddress("GenGroomedJet_AK7_rcores", GenGroomedJet_AK7_rcores, &b_GenGroomedJet_AK7_rcores);
   fChain->SetBranchAddress("GenGroomedJet_AK7_ptcores", GenGroomedJet_AK7_ptcores, &b_GenGroomedJet_AK7_ptcores);
   fChain->SetBranchAddress("GenGroomedJet_AK7_planarflow", GenGroomedJet_AK7_planarflow, &b_GenGroomedJet_AK7_planarflow);
   fChain->SetBranchAddress("GenGroomedJet_AK7_qjetmass", GenGroomedJet_AK7_qjetmass, &b_GenGroomedJet_AK7_qjetmass);
   fChain->SetBranchAddress("GenGroomedJet_AK7_qjetmassdrop", GenGroomedJet_AK7_qjetmassdrop, &b_GenGroomedJet_AK7_qjetmassdrop);
   fChain->SetBranchAddress("GenGroomedJet_AK7_constituents0_eta", GenGroomedJet_AK7_constituents0_eta, &b_GenGroomedJet_AK7_constituents0_eta);
   fChain->SetBranchAddress("GenGroomedJet_AK7_constituents0_phi", GenGroomedJet_AK7_constituents0_phi, &b_GenGroomedJet_AK7_constituents0_phi);
   fChain->SetBranchAddress("GenGroomedJet_AK7_constituents0_e", GenGroomedJet_AK7_constituents0_e, &b_GenGroomedJet_AK7_constituents0_e);
   fChain->SetBranchAddress("GenGroomedJet_AK7_nconstituents0", &GenGroomedJet_AK7_nconstituents0, &b_GenGroomedJet_AK7_nconstituents0);
   fChain->SetBranchAddress("GenGroomedJet_AK7_constituents0pr_eta", GenGroomedJet_AK7_constituents0pr_eta, &b_GenGroomedJet_AK7_constituents0pr_eta);
   fChain->SetBranchAddress("GenGroomedJet_AK7_constituents0pr_phi", GenGroomedJet_AK7_constituents0pr_phi, &b_GenGroomedJet_AK7_constituents0pr_phi);
   fChain->SetBranchAddress("GenGroomedJet_AK7_constituents0pr_e", GenGroomedJet_AK7_constituents0pr_e, &b_GenGroomedJet_AK7_constituents0pr_e);
   fChain->SetBranchAddress("GenGroomedJet_AK7_nconstituents0pr", &GenGroomedJet_AK7_nconstituents0pr, &b_GenGroomedJet_AK7_nconstituents0pr);
   fChain->SetBranchAddress("GenGroomedJet_CA8_pt_uncorr", GenGroomedJet_CA8_pt_uncorr, &b_GenGroomedJet_CA8_pt_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_CA8_mass_uncorr", GenGroomedJet_CA8_mass_uncorr, &b_GenGroomedJet_CA8_mass_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_CA8_mass_tr_uncorr", GenGroomedJet_CA8_mass_tr_uncorr, &b_GenGroomedJet_CA8_mass_tr_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_CA8_mass_ft_uncorr", GenGroomedJet_CA8_mass_ft_uncorr, &b_GenGroomedJet_CA8_mass_ft_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_CA8_mass_pr_uncorr", GenGroomedJet_CA8_mass_pr_uncorr, &b_GenGroomedJet_CA8_mass_pr_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_CA8_tau2tau1", GenGroomedJet_CA8_tau2tau1, &b_GenGroomedJet_CA8_tau2tau1);
   fChain->SetBranchAddress("GenGroomedJet_CA8_tau1", GenGroomedJet_CA8_tau1, &b_GenGroomedJet_CA8_tau1);
   fChain->SetBranchAddress("GenGroomedJet_CA8_tau2", GenGroomedJet_CA8_tau2, &b_GenGroomedJet_CA8_tau2);
   fChain->SetBranchAddress("GenGroomedJet_CA8_tau3", GenGroomedJet_CA8_tau3, &b_GenGroomedJet_CA8_tau3);
   fChain->SetBranchAddress("GenGroomedJet_CA8_tau4", GenGroomedJet_CA8_tau4, &b_GenGroomedJet_CA8_tau4);
   fChain->SetBranchAddress("GenGroomedJet_CA8_massdrop_pr_uncorr", GenGroomedJet_CA8_massdrop_pr_uncorr, &b_GenGroomedJet_CA8_massdrop_pr_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_CA8_pt", GenGroomedJet_CA8_pt, &b_GenGroomedJet_CA8_pt);
   fChain->SetBranchAddress("GenGroomedJet_CA8_eta", GenGroomedJet_CA8_eta, &b_GenGroomedJet_CA8_eta);
   fChain->SetBranchAddress("GenGroomedJet_CA8_phi", GenGroomedJet_CA8_phi, &b_GenGroomedJet_CA8_phi);
   fChain->SetBranchAddress("GenGroomedJet_CA8_e", GenGroomedJet_CA8_e, &b_GenGroomedJet_CA8_e);
   fChain->SetBranchAddress("GenGroomedJet_CA8_pt_tr_uncorr", GenGroomedJet_CA8_pt_tr_uncorr, &b_GenGroomedJet_CA8_pt_tr_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_CA8_pt_tr", GenGroomedJet_CA8_pt_tr, &b_GenGroomedJet_CA8_pt_tr);
   fChain->SetBranchAddress("GenGroomedJet_CA8_eta_tr", GenGroomedJet_CA8_eta_tr, &b_GenGroomedJet_CA8_eta_tr);
   fChain->SetBranchAddress("GenGroomedJet_CA8_phi_tr", GenGroomedJet_CA8_phi_tr, &b_GenGroomedJet_CA8_phi_tr);
   fChain->SetBranchAddress("GenGroomedJet_CA8_e_tr", GenGroomedJet_CA8_e_tr, &b_GenGroomedJet_CA8_e_tr);
   fChain->SetBranchAddress("GenGroomedJet_CA8_pt_ft_uncorr", GenGroomedJet_CA8_pt_ft_uncorr, &b_GenGroomedJet_CA8_pt_ft_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_CA8_pt_ft", GenGroomedJet_CA8_pt_ft, &b_GenGroomedJet_CA8_pt_ft);
   fChain->SetBranchAddress("GenGroomedJet_CA8_eta_ft", GenGroomedJet_CA8_eta_ft, &b_GenGroomedJet_CA8_eta_ft);
   fChain->SetBranchAddress("GenGroomedJet_CA8_phi_ft", GenGroomedJet_CA8_phi_ft, &b_GenGroomedJet_CA8_phi_ft);
   fChain->SetBranchAddress("GenGroomedJet_CA8_e_ft", GenGroomedJet_CA8_e_ft, &b_GenGroomedJet_CA8_e_ft);
   fChain->SetBranchAddress("GenGroomedJet_CA8_pt_pr_uncorr", GenGroomedJet_CA8_pt_pr_uncorr, &b_GenGroomedJet_CA8_pt_pr_uncorr);
   fChain->SetBranchAddress("GenGroomedJet_CA8_pt_pr", GenGroomedJet_CA8_pt_pr, &b_GenGroomedJet_CA8_pt_pr);
   fChain->SetBranchAddress("GenGroomedJet_CA8_eta_pr", GenGroomedJet_CA8_eta_pr, &b_GenGroomedJet_CA8_eta_pr);
   fChain->SetBranchAddress("GenGroomedJet_CA8_phi_pr", GenGroomedJet_CA8_phi_pr, &b_GenGroomedJet_CA8_phi_pr);
   fChain->SetBranchAddress("GenGroomedJet_CA8_e_pr", GenGroomedJet_CA8_e_pr, &b_GenGroomedJet_CA8_e_pr);
   fChain->SetBranchAddress("GenGroomedJet_CA8_prsubjet1_px", GenGroomedJet_CA8_prsubjet1_px, &b_GenGroomedJet_CA8_prsubjet1_px);
   fChain->SetBranchAddress("GenGroomedJet_CA8_prsubjet1_py", GenGroomedJet_CA8_prsubjet1_py, &b_GenGroomedJet_CA8_prsubjet1_py);
   fChain->SetBranchAddress("GenGroomedJet_CA8_prsubjet1_pz", GenGroomedJet_CA8_prsubjet1_pz, &b_GenGroomedJet_CA8_prsubjet1_pz);
   fChain->SetBranchAddress("GenGroomedJet_CA8_prsubjet1_e", GenGroomedJet_CA8_prsubjet1_e, &b_GenGroomedJet_CA8_prsubjet1_e);
   fChain->SetBranchAddress("GenGroomedJet_CA8_prsubjet2_px", GenGroomedJet_CA8_prsubjet2_px, &b_GenGroomedJet_CA8_prsubjet2_px);
   fChain->SetBranchAddress("GenGroomedJet_CA8_prsubjet2_py", GenGroomedJet_CA8_prsubjet2_py, &b_GenGroomedJet_CA8_prsubjet2_py);
   fChain->SetBranchAddress("GenGroomedJet_CA8_prsubjet2_pz", GenGroomedJet_CA8_prsubjet2_pz, &b_GenGroomedJet_CA8_prsubjet2_pz);
   fChain->SetBranchAddress("GenGroomedJet_CA8_prsubjet2_e", GenGroomedJet_CA8_prsubjet2_e, &b_GenGroomedJet_CA8_prsubjet2_e);
   fChain->SetBranchAddress("GenGroomedJet_CA8_mass", GenGroomedJet_CA8_mass, &b_GenGroomedJet_CA8_mass);
   fChain->SetBranchAddress("GenGroomedJet_CA8_mass_tr", GenGroomedJet_CA8_mass_tr, &b_GenGroomedJet_CA8_mass_tr);
   fChain->SetBranchAddress("GenGroomedJet_CA8_mass_ft", GenGroomedJet_CA8_mass_ft, &b_GenGroomedJet_CA8_mass_ft);
   fChain->SetBranchAddress("GenGroomedJet_CA8_mass_pr", GenGroomedJet_CA8_mass_pr, &b_GenGroomedJet_CA8_mass_pr);
   fChain->SetBranchAddress("GenGroomedJet_CA8_massdrop_pr", GenGroomedJet_CA8_massdrop_pr, &b_GenGroomedJet_CA8_massdrop_pr);
   fChain->SetBranchAddress("GenGroomedJet_CA8_area", GenGroomedJet_CA8_area, &b_GenGroomedJet_CA8_area);
   fChain->SetBranchAddress("GenGroomedJet_CA8_area_tr", GenGroomedJet_CA8_area_tr, &b_GenGroomedJet_CA8_area_tr);
   fChain->SetBranchAddress("GenGroomedJet_CA8_area_ft", GenGroomedJet_CA8_area_ft, &b_GenGroomedJet_CA8_area_ft);
   fChain->SetBranchAddress("GenGroomedJet_CA8_area_pr", GenGroomedJet_CA8_area_pr, &b_GenGroomedJet_CA8_area_pr);
   fChain->SetBranchAddress("GenGroomedJet_CA8_jetconstituents", GenGroomedJet_CA8_jetconstituents, &b_GenGroomedJet_CA8_jetconstituents);
   fChain->SetBranchAddress("GenGroomedJet_CA8_jetcharge", GenGroomedJet_CA8_jetcharge, &b_GenGroomedJet_CA8_jetcharge);
   fChain->SetBranchAddress("GenGroomedJet_CA8_rcores", GenGroomedJet_CA8_rcores, &b_GenGroomedJet_CA8_rcores);
   fChain->SetBranchAddress("GenGroomedJet_CA8_ptcores", GenGroomedJet_CA8_ptcores, &b_GenGroomedJet_CA8_ptcores);
   fChain->SetBranchAddress("GenGroomedJet_CA8_planarflow", GenGroomedJet_CA8_planarflow, &b_GenGroomedJet_CA8_planarflow);
   fChain->SetBranchAddress("GenGroomedJet_CA8_qjetmass", GenGroomedJet_CA8_qjetmass, &b_GenGroomedJet_CA8_qjetmass);
   fChain->SetBranchAddress("GenGroomedJet_CA8_qjetmassdrop", GenGroomedJet_CA8_qjetmassdrop, &b_GenGroomedJet_CA8_qjetmassdrop);
   fChain->SetBranchAddress("GenGroomedJet_CA8_constituents0_eta", GenGroomedJet_CA8_constituents0_eta, &b_GenGroomedJet_CA8_constituents0_eta);
   fChain->SetBranchAddress("GenGroomedJet_CA8_constituents0_phi", GenGroomedJet_CA8_constituents0_phi, &b_GenGroomedJet_CA8_constituents0_phi);
   fChain->SetBranchAddress("GenGroomedJet_CA8_constituents0_e", GenGroomedJet_CA8_constituents0_e, &b_GenGroomedJet_CA8_constituents0_e);
   fChain->SetBranchAddress("GenGroomedJet_CA8_nconstituents0", &GenGroomedJet_CA8_nconstituents0, &b_GenGroomedJet_CA8_nconstituents0);
   fChain->SetBranchAddress("GenGroomedJet_CA8_constituents0pr_eta", GenGroomedJet_CA8_constituents0pr_eta, &b_GenGroomedJet_CA8_constituents0pr_eta);
   fChain->SetBranchAddress("GenGroomedJet_CA8_constituents0pr_phi", GenGroomedJet_CA8_constituents0pr_phi, &b_GenGroomedJet_CA8_constituents0pr_phi);
   fChain->SetBranchAddress("GenGroomedJet_CA8_constituents0pr_e", GenGroomedJet_CA8_constituents0pr_e, &b_GenGroomedJet_CA8_constituents0pr_e);
   fChain->SetBranchAddress("GenGroomedJet_CA8_nconstituents0pr", &GenGroomedJet_CA8_nconstituents0pr, &b_GenGroomedJet_CA8_nconstituents0pr);
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
   fChain->SetBranchAddress("trkSumPtHollowConeDR04_Photon11", trkSumPtHollowConeDR04_Photon11, &b_trkSumPtHollowConeDR04_Photon11);
   fChain->SetBranchAddress("ecalRecHitSumEtConeDR04_Photon11", ecalRecHitSumEtConeDR04_Photon11, &b_ecalRecHitSumEtConeDR04_Photon11);
   fChain->SetBranchAddress("hcalTowerSumEtConeDR04_Photon11", hcalTowerSumEtConeDR04_Photon11, &b_hcalTowerSumEtConeDR04_Photon11);
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
   fChain->SetBranchAddress("W_pzNu1", &W_pzNu1, &b_W_pzNu1);
   fChain->SetBranchAddress("W_pzNu2", &W_pzNu2, &b_W_pzNu2);
   fChain->SetBranchAddress("W_muon_px", &W_muon_px, &b_W_muon_px);
   fChain->SetBranchAddress("W_muon_py", &W_muon_py, &b_W_muon_py);
   fChain->SetBranchAddress("W_muon_pz", &W_muon_pz, &b_W_muon_pz);
   fChain->SetBranchAddress("W_muon_e", &W_muon_e, &b_W_muon_e);
   fChain->SetBranchAddress("W_muon_pt", &W_muon_pt, &b_W_muon_pt);
   fChain->SetBranchAddress("W_muon_et", &W_muon_et, &b_W_muon_et);
   fChain->SetBranchAddress("W_muon_eta", &W_muon_eta, &b_W_muon_eta);
   fChain->SetBranchAddress("W_muon_theta", &W_muon_theta, &b_W_muon_theta);
   fChain->SetBranchAddress("W_muon_phi", &W_muon_phi, &b_W_muon_phi);
   fChain->SetBranchAddress("W_muon_charge", &W_muon_charge, &b_W_muon_charge);
   fChain->SetBranchAddress("W_muon_vx", &W_muon_vx, &b_W_muon_vx);
   fChain->SetBranchAddress("W_muon_vy", &W_muon_vy, &b_W_muon_vy);
   fChain->SetBranchAddress("W_muon_vz", &W_muon_vz, &b_W_muon_vz);
   fChain->SetBranchAddress("W_muon_y", &W_muon_y, &b_W_muon_y);
   fChain->SetBranchAddress("W_muon_trackiso", &W_muon_trackiso, &b_W_muon_trackiso);
   fChain->SetBranchAddress("W_muon_hcaliso", &W_muon_hcaliso, &b_W_muon_hcaliso);
   fChain->SetBranchAddress("W_muon_ecaliso", &W_muon_ecaliso, &b_W_muon_ecaliso);
   fChain->SetBranchAddress("W_muon_type", &W_muon_type, &b_W_muon_type);
   fChain->SetBranchAddress("W_muon_numberOfChambers", &W_muon_numberOfChambers, &b_W_muon_numberOfChambers);
   fChain->SetBranchAddress("W_muon_numberOfMatches", &W_muon_numberOfMatches, &b_W_muon_numberOfMatches);
   fChain->SetBranchAddress("W_muon_d0bsp", &W_muon_d0bsp, &b_W_muon_d0bsp);
   fChain->SetBranchAddress("W_muon_dz000", &W_muon_dz000, &b_W_muon_dz000);
   fChain->SetBranchAddress("W_muon_dzPV", &W_muon_dzPV, &b_W_muon_dzPV);
   fChain->SetBranchAddress("W_muon_pfiso_sumChargedHadronPt", &W_muon_pfiso_sumChargedHadronPt, &b_W_muon_pfiso_sumChargedHadronPt);
   fChain->SetBranchAddress("W_muon_pfiso_sumChargedParticlePt", &W_muon_pfiso_sumChargedParticlePt, &b_W_muon_pfiso_sumChargedParticlePt);
   fChain->SetBranchAddress("W_muon_pfiso_sumNeutralHadronEt", &W_muon_pfiso_sumNeutralHadronEt, &b_W_muon_pfiso_sumNeutralHadronEt);
   fChain->SetBranchAddress("W_muon_pfiso_sumPhotonEt", &W_muon_pfiso_sumPhotonEt, &b_W_muon_pfiso_sumPhotonEt);
   fChain->SetBranchAddress("W_muon_pfiso_sumPUPt", &W_muon_pfiso_sumPUPt, &b_W_muon_pfiso_sumPUPt);
   fChain->SetBranchAddress("W_Photon_pt_gen", &W_Photon_pt_gen, &b_W_Photon_pt_gen);
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
   fChain->SetBranchAddress("W_muon_px_gen", &W_muon_px_gen, &b_W_muon_px_gen);
   fChain->SetBranchAddress("W_muon_py_gen", &W_muon_py_gen, &b_W_muon_py_gen);
   fChain->SetBranchAddress("W_muon_pz_gen", &W_muon_pz_gen, &b_W_muon_pz_gen);
   fChain->SetBranchAddress("W_muon_e_gen", &W_muon_e_gen, &b_W_muon_e_gen);
   fChain->SetBranchAddress("W_muon_pt_gen", &W_muon_pt_gen, &b_W_muon_pt_gen);
   fChain->SetBranchAddress("W_muon_et_gen", &W_muon_et_gen, &b_W_muon_et_gen);
   fChain->SetBranchAddress("W_muon_eta_gen", &W_muon_eta_gen, &b_W_muon_eta_gen);
   fChain->SetBranchAddress("W_muon_theta_gen", &W_muon_theta_gen, &b_W_muon_theta_gen);
   fChain->SetBranchAddress("W_muon_phi_gen", &W_muon_phi_gen, &b_W_muon_phi_gen);
   fChain->SetBranchAddress("W_muon_charge_gen", &W_muon_charge_gen, &b_W_muon_charge_gen);
   fChain->SetBranchAddress("W_muon_vx_gen", &W_muon_vx_gen, &b_W_muon_vx_gen);
   fChain->SetBranchAddress("W_muon_vy_gen", &W_muon_vy_gen, &b_W_muon_vy_gen);
   fChain->SetBranchAddress("W_muon_vz_gen", &W_muon_vz_gen, &b_W_muon_vz_gen);
   fChain->SetBranchAddress("W_muon_y_gen", &W_muon_y_gen, &b_W_muon_y_gen);
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
   fChain->SetBranchAddress("W_tParton_px[2]", W_tParton_px, &b_W_tParton_px);
   fChain->SetBranchAddress("W_tParton_py[2]", W_tParton_py, &b_W_tParton_py);
   fChain->SetBranchAddress("W_tParton_pz[2]", W_tParton_pz, &b_W_tParton_pz);
   fChain->SetBranchAddress("W_tParton_E[2]", W_tParton_E, &b_W_tParton_E);
   fChain->SetBranchAddress("W_tParton_pt[2]", W_tParton_pt, &b_W_tParton_pt);
   fChain->SetBranchAddress("W_tParton_et[2]", W_tParton_et, &b_W_tParton_et);
   fChain->SetBranchAddress("W_tParton_eta[2]", W_tParton_eta, &b_W_tParton_eta);
   fChain->SetBranchAddress("W_tParton_theta[2]", W_tParton_theta, &b_W_tParton_theta);
   fChain->SetBranchAddress("W_tParton_phi[2]", W_tParton_phi, &b_W_tParton_phi);
   fChain->SetBranchAddress("W_tParton_charge[2]", W_tParton_charge, &b_W_tParton_charge);
   fChain->SetBranchAddress("W_tParton_vx[2]", W_tParton_vx, &b_W_tParton_vx);
   fChain->SetBranchAddress("W_tParton_vy[2]", W_tParton_vy, &b_W_tParton_vy);
   fChain->SetBranchAddress("W_tParton_vz[2]", W_tParton_vz, &b_W_tParton_vz);
   fChain->SetBranchAddress("W_tParton_y[2]", W_tParton_y, &b_W_tParton_y);
   fChain->SetBranchAddress("W_tParton_Id[2]", W_tParton_Id, &b_W_tParton_Id);
   fChain->SetBranchAddress("W_tLepton_px", &W_tLepton_px, &b_W_tLepton_px);
   fChain->SetBranchAddress("W_tLepton_py", &W_tLepton_py, &b_W_tLepton_py);
   fChain->SetBranchAddress("W_tLepton_pz", &W_tLepton_pz, &b_W_tLepton_pz);
   fChain->SetBranchAddress("W_tLepton_E", &W_tLepton_E, &b_W_tLepton_E);
   fChain->SetBranchAddress("W_tLepton_pt", &W_tLepton_pt, &b_W_tLepton_pt);
   fChain->SetBranchAddress("W_tLepton_et", &W_tLepton_et, &b_W_tLepton_et);
   fChain->SetBranchAddress("W_tLepton_eta", &W_tLepton_eta, &b_W_tLepton_eta);
   fChain->SetBranchAddress("W_tLepton_theta", &W_tLepton_theta, &b_W_tLepton_theta);
   fChain->SetBranchAddress("W_tLepton_phi", &W_tLepton_phi, &b_W_tLepton_phi);
   fChain->SetBranchAddress("W_tLepton_charge", &W_tLepton_charge, &b_W_tLepton_charge);
   fChain->SetBranchAddress("W_tLepton_vx", &W_tLepton_vx, &b_W_tLepton_vx);
   fChain->SetBranchAddress("W_tLepton_vy", &W_tLepton_vy, &b_W_tLepton_vy);
   fChain->SetBranchAddress("W_tLepton_vz", &W_tLepton_vz, &b_W_tLepton_vz);
   fChain->SetBranchAddress("W_tLepton_y", &W_tLepton_y, &b_W_tLepton_y);
   fChain->SetBranchAddress("W_tLepton_Id", &W_tLepton_Id, &b_W_tLepton_Id);
   fChain->SetBranchAddress("W_tMet_px", &W_tMet_px, &b_W_tMet_px);
   fChain->SetBranchAddress("W_tMet_py", &W_tMet_py, &b_W_tMet_py);
   fChain->SetBranchAddress("W_tMet_pz", &W_tMet_pz, &b_W_tMet_pz);
   fChain->SetBranchAddress("W_tMet_E", &W_tMet_E, &b_W_tMet_E);
   fChain->SetBranchAddress("W_tMet_pt", &W_tMet_pt, &b_W_tMet_pt);
   fChain->SetBranchAddress("W_tMet_et", &W_tMet_et, &b_W_tMet_et);
   fChain->SetBranchAddress("W_tMet_eta", &W_tMet_eta, &b_W_tMet_eta);
   fChain->SetBranchAddress("W_tMet_theta", &W_tMet_theta, &b_W_tMet_theta);
   fChain->SetBranchAddress("W_tMet_phi", &W_tMet_phi, &b_W_tMet_phi);
   fChain->SetBranchAddress("W_tMet_charge", &W_tMet_charge, &b_W_tMet_charge);
   fChain->SetBranchAddress("W_tMet_vx", &W_tMet_vx, &b_W_tMet_vx);
   fChain->SetBranchAddress("W_tMet_vy", &W_tMet_vy, &b_W_tMet_vy);
   fChain->SetBranchAddress("W_tMet_vz", &W_tMet_vz, &b_W_tMet_vz);
   fChain->SetBranchAddress("W_tMet_y", &W_tMet_y, &b_W_tMet_y);
   fChain->SetBranchAddress("W_tMet_Id", &W_tMet_Id, &b_W_tMet_Id);
   fChain->SetBranchAddress("W_tb_px", &W_tb_px, &b_W_tb_px);
   fChain->SetBranchAddress("W_tb_py", &W_tb_py, &b_W_tb_py);
   fChain->SetBranchAddress("W_tb_pz", &W_tb_pz, &b_W_tb_pz);
   fChain->SetBranchAddress("W_tb_E", &W_tb_E, &b_W_tb_E);
   fChain->SetBranchAddress("W_tb_pt", &W_tb_pt, &b_W_tb_pt);
   fChain->SetBranchAddress("W_tb_et", &W_tb_et, &b_W_tb_et);
   fChain->SetBranchAddress("W_tb_eta", &W_tb_eta, &b_W_tb_eta);
   fChain->SetBranchAddress("W_tb_theta", &W_tb_theta, &b_W_tb_theta);
   fChain->SetBranchAddress("W_tb_phi", &W_tb_phi, &b_W_tb_phi);
   fChain->SetBranchAddress("W_tb_charge", &W_tb_charge, &b_W_tb_charge);
   fChain->SetBranchAddress("W_tb_vx", &W_tb_vx, &b_W_tb_vx);
   fChain->SetBranchAddress("W_tb_vy", &W_tb_vy, &b_W_tb_vy);
   fChain->SetBranchAddress("W_tb_vz", &W_tb_vz, &b_W_tb_vz);
   fChain->SetBranchAddress("W_tb_y", &W_tb_y, &b_W_tb_y);
   fChain->SetBranchAddress("W_tb_Id", &W_tb_Id, &b_W_tb_Id);
   fChain->SetBranchAddress("W_tbbar_px", &W_tbbar_px, &b_W_tbbar_px);
   fChain->SetBranchAddress("W_tbbar_py", &W_tbbar_py, &b_W_tbbar_py);
   fChain->SetBranchAddress("W_tbbar_pz", &W_tbbar_pz, &b_W_tbbar_pz);
   fChain->SetBranchAddress("W_tbbar_E", &W_tbbar_E, &b_W_tbbar_E);
   fChain->SetBranchAddress("W_tbbar_pt", &W_tbbar_pt, &b_W_tbbar_pt);
   fChain->SetBranchAddress("W_tbbar_et", &W_tbbar_et, &b_W_tbbar_et);
   fChain->SetBranchAddress("W_tbbar_eta", &W_tbbar_eta, &b_W_tbbar_eta);
   fChain->SetBranchAddress("W_tbbar_theta", &W_tbbar_theta, &b_W_tbbar_theta);
   fChain->SetBranchAddress("W_tbbar_phi", &W_tbbar_phi, &b_W_tbbar_phi);
   fChain->SetBranchAddress("W_tbbar_charge", &W_tbbar_charge, &b_W_tbbar_charge);
   fChain->SetBranchAddress("W_tbbar_vx", &W_tbbar_vx, &b_W_tbbar_vx);
   fChain->SetBranchAddress("W_tbbar_vy", &W_tbbar_vy, &b_W_tbbar_vy);
   fChain->SetBranchAddress("W_tbbar_vz", &W_tbbar_vz, &b_W_tbbar_vz);
   fChain->SetBranchAddress("W_tbbar_y", &W_tbbar_y, &b_W_tbbar_y);
   fChain->SetBranchAddress("W_tbbar_Id", &W_tbbar_Id, &b_W_tbbar_Id);
   fChain->SetBranchAddress("W_Hb_px", &W_Hb_px, &b_W_Hb_px);
   fChain->SetBranchAddress("W_Hb_py", &W_Hb_py, &b_W_Hb_py);
   fChain->SetBranchAddress("W_Hb_pz", &W_Hb_pz, &b_W_Hb_pz);
   fChain->SetBranchAddress("W_Hb_E", &W_Hb_E, &b_W_Hb_E);
   fChain->SetBranchAddress("W_Hb_pt", &W_Hb_pt, &b_W_Hb_pt);
   fChain->SetBranchAddress("W_Hb_et", &W_Hb_et, &b_W_Hb_et);
   fChain->SetBranchAddress("W_Hb_eta", &W_Hb_eta, &b_W_Hb_eta);
   fChain->SetBranchAddress("W_Hb_theta", &W_Hb_theta, &b_W_Hb_theta);
   fChain->SetBranchAddress("W_Hb_phi", &W_Hb_phi, &b_W_Hb_phi);
   fChain->SetBranchAddress("W_Hb_charge", &W_Hb_charge, &b_W_Hb_charge);
   fChain->SetBranchAddress("W_Hb_vx", &W_Hb_vx, &b_W_Hb_vx);
   fChain->SetBranchAddress("W_Hb_vy", &W_Hb_vy, &b_W_Hb_vy);
   fChain->SetBranchAddress("W_Hb_vz", &W_Hb_vz, &b_W_Hb_vz);
   fChain->SetBranchAddress("W_Hb_y", &W_Hb_y, &b_W_Hb_y);
   fChain->SetBranchAddress("W_Hb_Id", &W_Hb_Id, &b_W_Hb_Id);
   fChain->SetBranchAddress("W_Hbbar_px", &W_Hbbar_px, &b_W_Hbbar_px);
   fChain->SetBranchAddress("W_Hbbar_py", &W_Hbbar_py, &b_W_Hbbar_py);
   fChain->SetBranchAddress("W_Hbbar_pz", &W_Hbbar_pz, &b_W_Hbbar_pz);
   fChain->SetBranchAddress("W_Hbbar_E", &W_Hbbar_E, &b_W_Hbbar_E);
   fChain->SetBranchAddress("W_Hbbar_pt", &W_Hbbar_pt, &b_W_Hbbar_pt);
   fChain->SetBranchAddress("W_Hbbar_et", &W_Hbbar_et, &b_W_Hbbar_et);
   fChain->SetBranchAddress("W_Hbbar_eta", &W_Hbbar_eta, &b_W_Hbbar_eta);
   fChain->SetBranchAddress("W_Hbbar_theta", &W_Hbbar_theta, &b_W_Hbbar_theta);
   fChain->SetBranchAddress("W_Hbbar_phi", &W_Hbbar_phi, &b_W_Hbbar_phi);
   fChain->SetBranchAddress("W_Hbbar_charge", &W_Hbbar_charge, &b_W_Hbbar_charge);
   fChain->SetBranchAddress("W_Hbbar_vx", &W_Hbbar_vx, &b_W_Hbbar_vx);
   fChain->SetBranchAddress("W_Hbbar_vy", &W_Hbbar_vy, &b_W_Hbbar_vy);
   fChain->SetBranchAddress("W_Hbbar_vz", &W_Hbbar_vz, &b_W_Hbbar_vz);
   fChain->SetBranchAddress("W_Hbbar_y", &W_Hbbar_y, &b_W_Hbbar_y);
   fChain->SetBranchAddress("W_Hbbar_Id", &W_Hbbar_Id, &b_W_Hbbar_Id);
   fChain->SetBranchAddress("W_TagQuark_px[2]", W_TagQuark_px, &b_W_TagQuark_px);
   fChain->SetBranchAddress("W_TagQuark_py[2]", W_TagQuark_py, &b_W_TagQuark_py);
   fChain->SetBranchAddress("W_TagQuark_pz[2]", W_TagQuark_pz, &b_W_TagQuark_pz);
   fChain->SetBranchAddress("W_TagQuark_E[2]", W_TagQuark_E, &b_W_TagQuark_E);
   fChain->SetBranchAddress("W_TagQuark_pt[2]", W_TagQuark_pt, &b_W_TagQuark_pt);
   fChain->SetBranchAddress("W_TagQuark_et[2]", W_TagQuark_et, &b_W_TagQuark_et);
   fChain->SetBranchAddress("W_TagQuark_eta[2]", W_TagQuark_eta, &b_W_TagQuark_eta);
   fChain->SetBranchAddress("W_TagQuark_theta[2]", W_TagQuark_theta, &b_W_TagQuark_theta);
   fChain->SetBranchAddress("W_TagQuark_phi[2]", W_TagQuark_phi, &b_W_TagQuark_phi);
   fChain->SetBranchAddress("W_TagQuark_charge[2]", W_TagQuark_charge, &b_W_TagQuark_charge);
   fChain->SetBranchAddress("W_TagQuark_vx[2]", W_TagQuark_vx, &b_W_TagQuark_vx);
   fChain->SetBranchAddress("W_TagQuark_vy[2]", W_TagQuark_vy, &b_W_TagQuark_vy);
   fChain->SetBranchAddress("W_TagQuark_vz[2]", W_TagQuark_vz, &b_W_TagQuark_vz);
   fChain->SetBranchAddress("W_TagQuark_y[2]", W_TagQuark_y, &b_W_TagQuark_y);
   fChain->SetBranchAddress("W_TagQuark_Id[2]", W_TagQuark_Id, &b_W_TagQuark_Id);
   fChain->SetBranchAddress("W_EWKW_px", &W_EWKW_px, &b_W_EWKW_px);
   fChain->SetBranchAddress("W_EWKW_py", &W_EWKW_py, &b_W_EWKW_py);
   fChain->SetBranchAddress("W_EWKW_pz", &W_EWKW_pz, &b_W_EWKW_pz);
   fChain->SetBranchAddress("W_EWKW_E", &W_EWKW_E, &b_W_EWKW_E);
   fChain->SetBranchAddress("W_EWKW_pt", &W_EWKW_pt, &b_W_EWKW_pt);
   fChain->SetBranchAddress("W_EWKW_et", &W_EWKW_et, &b_W_EWKW_et);
   fChain->SetBranchAddress("W_EWKW_eta", &W_EWKW_eta, &b_W_EWKW_eta);
   fChain->SetBranchAddress("W_EWKW_theta", &W_EWKW_theta, &b_W_EWKW_theta);
   fChain->SetBranchAddress("W_EWKW_phi", &W_EWKW_phi, &b_W_EWKW_phi);
   fChain->SetBranchAddress("W_EWKW_charge", &W_EWKW_charge, &b_W_EWKW_charge);
   fChain->SetBranchAddress("W_EWKW_vx", &W_EWKW_vx, &b_W_EWKW_vx);
   fChain->SetBranchAddress("W_EWKW_vy", &W_EWKW_vy, &b_W_EWKW_vy);
   fChain->SetBranchAddress("W_EWKW_vz", &W_EWKW_vz, &b_W_EWKW_vz);
   fChain->SetBranchAddress("W_EWKW_y", &W_EWKW_y, &b_W_EWKW_y);
   fChain->SetBranchAddress("W_EWKW_Id", &W_EWKW_Id, &b_W_EWKW_Id);
   fChain->SetBranchAddress("W_EWKTagQuark_px[2]", W_EWKTagQuark_px, &b_W_EWKTagQuark_px);
   fChain->SetBranchAddress("W_EWKTagQuark_py[2]", W_EWKTagQuark_py, &b_W_EWKTagQuark_py);
   fChain->SetBranchAddress("W_EWKTagQuark_pz[2]", W_EWKTagQuark_pz, &b_W_EWKTagQuark_pz);
   fChain->SetBranchAddress("W_EWKTagQuark_E[2]", W_EWKTagQuark_E, &b_W_EWKTagQuark_E);
   fChain->SetBranchAddress("W_EWKTagQuark_pt[2]", W_EWKTagQuark_pt, &b_W_EWKTagQuark_pt);
   fChain->SetBranchAddress("W_EWKTagQuark_et[2]", W_EWKTagQuark_et, &b_W_EWKTagQuark_et);
   fChain->SetBranchAddress("W_EWKTagQuark_eta[2]", W_EWKTagQuark_eta, &b_W_EWKTagQuark_eta);
   fChain->SetBranchAddress("W_EWKTagQuark_theta[2]", W_EWKTagQuark_theta, &b_W_EWKTagQuark_theta);
   fChain->SetBranchAddress("W_EWKTagQuark_phi[2]", W_EWKTagQuark_phi, &b_W_EWKTagQuark_phi);
   fChain->SetBranchAddress("W_EWKTagQuark_charge[2]", W_EWKTagQuark_charge, &b_W_EWKTagQuark_charge);
   fChain->SetBranchAddress("W_EWKTagQuark_vx[2]", W_EWKTagQuark_vx, &b_W_EWKTagQuark_vx);
   fChain->SetBranchAddress("W_EWKTagQuark_vy[2]", W_EWKTagQuark_vy, &b_W_EWKTagQuark_vy);
   fChain->SetBranchAddress("W_EWKTagQuark_vz[2]", W_EWKTagQuark_vz, &b_W_EWKTagQuark_vz);
   fChain->SetBranchAddress("W_EWKTagQuark_y[2]", W_EWKTagQuark_y, &b_W_EWKTagQuark_y);
   fChain->SetBranchAddress("W_EWKTagQuark_Id[2]", W_EWKTagQuark_Id, &b_W_EWKTagQuark_Id);
   fChain->SetBranchAddress("W_nParton_Winclusive", &W_nParton_Winclusive, &b_W_nParton_Winclusive);
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

Bool_t kanamuon::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void kanamuon::Show(Long64_t entry)
{
   // Print contents of entry.
   // If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t kanamuon::Cut(Long64_t entry)
{
   // This function may be called from Loop.
   // returns  1 if entry is accepted.
   // returns -1 otherwise.
   Long64_t tmp; tmp=entry;
   return 1;
}
#endif // #ifdef kanamuon_cxx
