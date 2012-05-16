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
 *   To fill jet related quantities into a specified TTree
 *   Can work with CaloJet, GenJet, JPT jet, PF jet.
 *   Can work with jets in RECO/AOD/PAT data formats.
 * History:
 *   
 *
 * Copyright (C) 2010 FNAL 
 *****************************************************************************/


// user include files
#include "ElectroWeakAnalysis/VPlusJets/interface/VplusJetsAnalysis.h" 
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/METReco/interface/MET.h"
#include "DataFormats/METReco/interface/METCollection.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/METReco/interface/CaloMETCollection.h"
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/METReco/interface/GenMETCollection.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h" 

ewk::VplusJetsAnalysis::VplusJetsAnalysis(const edm::ParameterSet& iConfig) :
  fOutputFileName ( iConfig.getParameter<std::string>("HistOutFile") ),
  hOutputFile ( new TFile( fOutputFileName.c_str(), "RECREATE" ) ), 
  myTree ( new TTree(iConfig.getParameter<std::string>("TreeName").c_str(),"V+jets Tree") ),
  CaloJetFiller (  iConfig.existsAs<edm::InputTag>("srcCalo") ?
  new JetTreeFiller("CaloJetFiller", myTree, "Calo", iConfig) : 0),
  CorrectedCaloJetFiller ( iConfig.existsAs<edm::InputTag>("srcCaloCor") ? 
  new JetTreeFiller("CorrectedCaloJetFiller", myTree, "Cor", iConfig) : 0),
  CorrectedPFJetFiller ( iConfig.existsAs<edm::InputTag>("srcPFCor") ? 
  new JetTreeFiller("CorrectedPFJetFiller", myTree, "PFCor", iConfig) : 0),
  CorrectedPFJetFillerVBFTag ( iConfig.existsAs<edm::InputTag>("srcPFCorVBFTag") ? 
  new JetTreeFiller("CorrectedPFJetFillerVBFTag", myTree, "PFCorVBFTag", iConfig) : 0),
  CorrectedJPTJetFiller ( iConfig.existsAs<edm::InputTag>("srcJPTCor") ?  
  new JetTreeFiller("CorrectedJPTJetFiller", myTree, "JPTCor", iConfig) : 0),
  GenJetFiller ( (iConfig.existsAs<bool>("runningOverMC") && 
  iConfig.getParameter<bool>("runningOverMC") && 
  iConfig.existsAs<edm::InputTag>("srcGen")) ?  
  new JetTreeFiller("GenJetFiller", myTree, "Gen", iConfig) : 0),
  PFJetFiller ( iConfig.existsAs<edm::InputTag>("srcPFJets") ?   
  new JetTreeFiller("PFJetFiller", myTree, "PF", iConfig) : 0),
  JPTJetFiller ( iConfig.existsAs<edm::InputTag>("srcJPTJets") ?  
  new JetTreeFiller("JPTJetFiller", myTree, "JPT", iConfig) : 0),
  recoBosonFillerE( new VtoElectronTreeFiller( iConfig.getParameter<std::string>("VBosonType").c_str(), 
					       myTree, iConfig) ),
  recoBosonFillerMu( new VtoMuonTreeFiller( iConfig.getParameter<std::string>("VBosonType").c_str(), 
					    myTree, iConfig) ),
  genBosonFiller( (iConfig.existsAs<bool>("runningOverMC") && 
  iConfig.getParameter<bool>("runningOverMC")) ?
  new MCTreeFiller(iConfig.getParameter<std::string>("VBosonType").c_str(), myTree, iConfig) : 0)
{
  // Are we running over Monte Carlo ?
   if( iConfig.existsAs<bool>("runningOverMC") ) 
      runningOverMC_=iConfig.getParameter< bool >("runningOverMC");
   else runningOverMC_= false;
  if(  iConfig.existsAs<edm::InputTag>("srcVectorBoson") )
    mInputBoson = iConfig.getParameter<edm::InputTag>("srcVectorBoson"); 
  LeptonType_ = iConfig.getParameter<std::string>("LeptonType");
  VBosonType_ = iConfig.getParameter<std::string>("VBosonType");
  if(  iConfig.existsAs<edm::InputTag>("srcPrimaryVertex") )
    mPrimaryVertex = iConfig.getParameter<edm::InputTag>("srcPrimaryVertex"); 
  else mPrimaryVertex =  edm::InputTag("offlinePrimaryVertices");
  if(  iConfig.existsAs<edm::InputTag>("srcBeamSpot") )
    mInputBeamSpot = iConfig.getParameter<edm::InputTag>("srcBeamSpot"); 
  if(  iConfig.existsAs<edm::InputTag>("srcMet") )
    mInputMet = iConfig.getParameter<edm::InputTag>("srcMet");
  if(  iConfig.existsAs<edm::InputTag>("srcMet") )
    mInputcaloMet = iConfig.getParameter<edm::InputTag>("srcCaloMet");
  if(  iConfig.existsAs<edm::InputTag>("srcTcMet") )
    mInputtcMet = iConfig.getParameter<edm::InputTag>("srcTcMet"); 
  //*********************  Run Over AOD or PAT  ***********//
  if( iConfig.existsAs<bool>("runningOverAOD"))
	  runoverAOD = iConfig.getParameter<bool>("runningOverAOD");

  JetsFor_rho =  iConfig.getParameter<std::string>("srcJetsforRho") ; 
  JetsFor_rhoCHS =  iConfig.getParameter<std::string>("srcJetsforRhoCHS") ; 
  JetsFor_rho_lepIso =  iConfig.getParameter<std::string>("srcJetsforRho_lepIso") ; 
  JetsFor_rho_lepIsoCHS =  iConfig.getParameter<std::string>("srcJetsforRho_lepIsoCHS") ; 

  if(  iConfig.existsAs<edm::InputTag>("srcgenMet") )
	  mInputgenMet =  iConfig.getParameter<edm::InputTag>("srcgenMet") ; 
}

 

ewk::VplusJetsAnalysis::~VplusJetsAnalysis() {}


void ewk::VplusJetsAnalysis::beginJob() {

  // Declare all the branches of the tree
  declareTreeBranches();
}




// ------------ method called to produce the data  ------------
void ewk::VplusJetsAnalysis::analyze(const edm::Event& iEvent, 
				     const edm::EventSetup& iSetup) {

  // write event information
  run   = 0;
  event = 0;
  lumi  = 0;
  bunch = 0;
  nPV   = 0; 
 
  // run, event, bunch crossing, ....
  run   = iEvent.id().run();
  event = iEvent.id().event();
  lumi  = iEvent.luminosityBlock();
  bunch = iEvent.bunchCrossing();


  // primary/secondary vertices
  // edm::Handle<reco::VertexCollection > recVtxs;
  edm::Handle <edm::View<reco::Vertex> > recVtxs;
  iEvent.getByLabel( mPrimaryVertex, recVtxs);
  for(unsigned int ind=0;ind<recVtxs->size();ind++) 
    {
      if(nPV>30) continue;
      mPVx[nPV] =   -10000.0;
      mPVy[nPV] =   -10000.0;
      mPVz[nPV] =   -10000.0;

      if (!((*recVtxs)[ind].isFake()) && ((*recVtxs)[ind].ndof()>=4) 
	  && (fabs((*recVtxs)[ind].z())<=24.0) &&  
	  ((*recVtxs)[ind].position().Rho()<=2.0) ) {

	mPVx[nPV] =  (*recVtxs)[ind].x() ;
	mPVy[nPV] =  (*recVtxs)[ind].y() ;
	mPVz[nPV] =  (*recVtxs)[ind].z() ;
	nPV += 1;
      }
    }

  //////////// Beam spot //////////////
//  if(runOverAOD){
  edm::Handle<reco::BeamSpot >beamSpot;
  if(runoverAOD){
	  iEvent.getByLabel(mInputBeamSpot, beamSpot);
	  mBSx = beamSpot->position().X();
	  mBSy = beamSpot->position().Y();
	  mBSz = beamSpot->position().Z();
  }



  ////////////// CaloMET information //////
  edm::Handle<edm::View<reco::CaloMET> > met;
  if(runoverAOD){
  iEvent.getByLabel(mInputcaloMet,met);
  if (met->size() == 0) {
    mMET   = -1.0;
    mSumET = -1.0;
    mMETSign  = -1.0;
    mMETPhi   = -10.0;
  }
  else {
    mMET   = (*met)[0].et();
    mSumET = (*met)[0].sumEt();
    mMETSign   = (*met)[0].significance();
    mMETPhi   = (*met)[0].phi();
  }

  }
  /////// TcMET information /////
  edm::Handle<edm::View<reco::MET> > tcmet;
  if(runoverAOD){
  iEvent.getByLabel(mInputtcMet, tcmet);
  if (tcmet->size() == 0) {
    mtcMET   = -1;
    mtcSumET = -1;
    mtcMETSign = -1;
    mtcMETPhi   = -10.0;
  }
  else {
    mtcMET   = (*tcmet)[0].et();
    mtcSumET = (*tcmet)[0].sumEt();
    mtcMETSign = (*tcmet)[0].significance();
    mtcMETPhi   = (*tcmet)[0].phi();
  }
  }
  /////// PfMET information /////
  edm::Handle<edm::View<reco::MET> > pfmet;
  iEvent.getByLabel(mInputMet, pfmet);
  if (pfmet->size() == 0) {
    mpfMET   = -1;
    mpfSumET = -1;
    mpfMETSign = -1;
    mpfMETPhi   = -10.0;
  }
  else {
    mpfMET   = (*pfmet)[0].et();
    mpfSumET = (*pfmet)[0].sumEt();
    mpfMETSign = (*pfmet)[0].significance();
    mpfMETPhi   = (*pfmet)[0].phi();
  }


  /////// Pileup density "rho" in the event from fastJet pileup calculation /////
  edm::Handle<double> rho;
  const edm::InputTag eventrho(JetsFor_rho, "rho");
  iEvent.getByLabel(eventrho,rho);
  if( *rho == *rho) fastJetRho = *rho;
  else  fastJetRho =  -999999.9;

  /////// Pileup density "rho" for lepton isolation subtraction /////
  //edm::Handle<double> rhoLepIso;
  //const edm::InputTag eventrhoLepIso(JetsFor_rho_lepIso, "rho");
  //iEvent.getByLabel(eventrhoLepIso, rhoLepIso);
  //if( *rhoLepIso == *rhoLepIso) lepIsoRho = *rhoLepIso;
  //else  lepIsoRho =  -999999.9;


  /////// CHARGED-HADRON-SUBTRACTED versions of pileup density rho:


  /////// Pileup density "rho" in the event from fastJet pileup calculation /////
  //edm::Handle<double> rhoCHS;
  //const edm::InputTag eventrhoCHS(JetsFor_rhoCHS, "rho");
  //iEvent.getByLabel(eventrhoCHS,rhoCHS);
  //if( *rhoCHS == *rhoCHS) fastJetRhoCHS = *rhoCHS;
  //else  fastJetRhoCHS =  -999999.9;

  /////// Pileup density "rho" for lepton isolation subtraction /////
  //edm::Handle<double> rhoLepIsoCHS;
  //const edm::InputTag eventrhoLepIsoCHS(JetsFor_rho_lepIsoCHS, "rho");
  //iEvent.getByLabel(eventrhoLepIsoCHS, rhoLepIsoCHS);
  //if( *rhoLepIsoCHS == *rhoLepIsoCHS) lepIsoRhoCHS = *rhoLepIsoCHS;
  //else  lepIsoRhoCHS =  -999999.9;

  // Notice! use only one rho everywhere, now four rhos have identical value
  lepIsoRho     = fastJetRho;
  fastJetRhoCHS = fastJetRho;
  lepIsoRhoCHS  = fastJetRho;

  /////////// GenMET information & MC Pileup Summary Info  //////////
  mcPUtotnvtx = 0;
  mcPUbx[0]   = -999; mcPUbx[1]   = -999; mcPUbx[2]   = -999;
  mcPUnvtx[0] = -999; mcPUnvtx[1] = -999; mcPUnvtx[2] = -999;
  if ( runningOverMC_ ){
    edm::Handle<reco::GenMETCollection> genMETs;
	if(runoverAOD){
		iEvent.getByLabel(mInputgenMet,genMETs);
		if ( genMETs->size() == 0) {
			genMET   = -1.0;
			genSumET = -1.0;
			genMETSign  = -1.0;
			genMETPhi   = -10.0;
		} else {
			genMET = (*genMETs)[0].et();
			genSumET = (*genMETs)[0].sumEt();  
			genMETSign = (*genMETs)[0].significance();  
			genMETPhi = (*genMETs)[0].phi();
		}
	}
    // MC Pileup Summary Info
    const edm::InputTag PileupSrc("addPileupInfo");
    edm::Handle<std::vector< PileupSummaryInfo > >  PupInfo;
    iEvent.getByLabel(PileupSrc, PupInfo);
    std::vector<PileupSummaryInfo>::const_iterator PVI;
    int ctid = 0;
    for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {
      if (ctid>2) break;
      mcPUbx[ctid]   =  PVI->getBunchCrossing();
      mcPUnvtx[ctid] =  PVI->getPU_NumInteractions();
      mcPUtotnvtx   +=  PVI->getPU_NumInteractions();
      ctid++;
    }
  }
  // fill jet branches
  edm::Handle<edm::View< reco::Candidate> > boson;
  iEvent.getByLabel( mInputBoson, boson);
  mNVB = boson->size();
  if( mNVB<1 ) return; // Nothing to fill


  if(CaloJetFiller.get()) CaloJetFiller->fill(iEvent);
  if(CorrectedCaloJetFiller.get()) CorrectedCaloJetFiller->fill(iEvent);
  if(GenJetFiller.get()) GenJetFiller->fill(iEvent);
  if(PFJetFiller.get()) PFJetFiller->fill(iEvent);
  if(JPTJetFiller.get()) JPTJetFiller->fill(iEvent);


  if(CorrectedPFJetFiller.get()) CorrectedPFJetFiller->fill(iEvent);
  if(CorrectedPFJetFillerVBFTag.get()) CorrectedPFJetFillerVBFTag->fill(iEvent);//For VBF Tag Jets
  if(CorrectedJPTJetFiller.get()) CorrectedJPTJetFiller->fill(iEvent);


  /**  Store reconstructed vector boson information */
  recoBosonFillerE->fill(iEvent, 0);
  if(mNVB==2) recoBosonFillerE->fill(iEvent, 1);

  recoBosonFillerMu->fill(iEvent,0);
  if(mNVB==2) recoBosonFillerMu->fill(iEvent, 1);

  /**  Store generated vector boson information */
  if(genBosonFiller.get()) genBosonFiller->fill(iEvent);
  
  myTree->Fill();

} // analyze method






void ewk::VplusJetsAnalysis::endJob()
{
  hOutputFile->SetCompressionLevel(2);
  hOutputFile->cd();
  myTree->Write();

  delete myTree;
  hOutputFile->Close();
  delete hOutputFile;
}




//  **** Utility: declare TTree branches for ntuple variables ***
void ewk::VplusJetsAnalysis::declareTreeBranches() {

  myTree->Branch("event_runNo",  &run,   "event_runNo/I");
  myTree->Branch("event_evtNo",  &event, "event_evtNo/I");
  myTree->Branch("event_lumi",   &lumi,  "event_lumi/I"); 
  myTree->Branch("event_bunch",  &bunch, "event_bunch/I"); 
  myTree->Branch("event_nPV",    &nPV,   "event_nPV/I"); 
  myTree->Branch("event_PVx",    mPVx,   "event_PVx[30]/F"); 
  myTree->Branch("event_PVy",    mPVy,   "event_PVy[30]/F"); 
  myTree->Branch("event_PVz",    mPVz,   "event_PVz[30]/F");
  if(runoverAOD){
	  myTree->Branch("event_met_calomet",    &mMET,  "event_met_calomet/F"); 
	  myTree->Branch("event_met_calosumet",  &mSumET,"event_met_calosumet/F"); 
	  myTree->Branch("event_met_calometsignificance", &mMETSign,  "event_met_calometsignificance/F"); 
	  myTree->Branch("event_met_calometPhi",    &mMETPhi,  "event_met_calometPhi/F"); 
	  myTree->Branch("event_met_tcmet",    &mtcMET,  "event_met_tcmet/F"); 
	  myTree->Branch("event_met_tcsumet",  &mtcSumET,"event_met_tcsumet/F"); 
	  myTree->Branch("event_met_tcmetsignificance", &mtcMETSign,  "event_met_tcmetsignificance/F"); 
	  myTree->Branch("event_met_tcmetPhi",    &mtcMETPhi,  "event_met_tcmetPhi/F");
  }
  myTree->Branch("event_met_pfmet",             &mpfMET,      "event_met_pfmet/F"); 
  myTree->Branch("event_met_pfsumet",           &mpfSumET,    "event_met_pfsumet/F"); 
  myTree->Branch("event_met_pfmetsignificance", &mpfMETSign,  "event_met_pfmetsignificance/F"); 
  myTree->Branch("event_met_pfmetPhi",          &mpfMETPhi,   "event_met_pfmetPhi/F"); 

  myTree->Branch("event_fastJetRho",                &fastJetRho,    "event_fastJetRho/F"); 
  myTree->Branch("event_fastJetRhoCHS",             &fastJetRhoCHS, "event_fastJetRhoCHS/F"); 
  myTree->Branch("event_RhoForLeptonIsolation",     &lepIsoRho,     "event_RhoForLeptonIsolation/F");
  myTree->Branch("event_RhoForLeptonIsolationCHS",  &lepIsoRhoCHS,  "event_RhoForLeptonIsolationCHS/F");
  
	  myTree->Branch("event_BeamSpot_x"       ,&mBSx              ,"event_BeamSpot_x/F");
	  myTree->Branch("event_BeamSpot_y"       ,&mBSy              ,"event_BeamSpot_y/F");
	  myTree->Branch("event_BeamSpot_z"       ,&mBSz              ,"event_BeamSpot_z/F");
  
  
  myTree->Branch(("num"+VBosonType_).c_str(),&mNVB ,("num"+VBosonType_+"/I").c_str());

  if ( runningOverMC_ ){

    myTree->Branch("event_met_genmet",    &genMET,  "event_met_genmet/F"); 
    myTree->Branch("event_met_gensumet",  &genSumET,"event_met_gensumet/F"); 
    myTree->Branch("event_met_genmetsignificance", &genMETSign,  "event_met_genmetsignificance/F"); 
    myTree->Branch("event_met_genmetPhi",    &genMETPhi,  "event_met_genmetPhi/F"); 
	  
    myTree->Branch("event_mcPU_totnvtx",    &mcPUtotnvtx,  "event_mcPU_totnvtx/F"); 
    myTree->Branch("event_mcPU_bx",         mcPUbx ,       "event_mcPU_bx[3]/F"); 
    myTree->Branch("event_mcPU_nvtx",       mcPUnvtx,      "event_mcPU_nvtx[3]/F"); 

  }

}  





// declare this class as a plugin
#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
using ewk::VplusJetsAnalysis;
DEFINE_FWK_MODULE(VplusJetsAnalysis);
