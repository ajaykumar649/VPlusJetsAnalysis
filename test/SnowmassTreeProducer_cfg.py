import FWCore.ParameterSet.Config as cms
import pprint
isMC = False

process = cms.Process("demo")

##---------  Load standard Reco modules ------------
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')



##----- this config frament brings you the generator information ----
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("PhysicsTools.HepMCCandAlgos.genParticles_cfi")
process.load("Configuration.StandardSequences.Generator_cff")


##----- Detector geometry : some of these needed for b-tag -------
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Geometry.CMSCommonData.cmsIdealGeometryXML_cfi")
process.load("Geometry.CommonDetUnit.globalTrackingGeometry_cfi")
process.load("RecoMuon.DetLayers.muonDetLayerGeometry_cfi")



##----- Global tag: conditions database ------------
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')


## ############################################
process.GlobalTag.globaltag = 'POSTLS161_V12::All'


numEventsToRun = 2000
## ############################################
########################################################################################
########################################################################################




process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(numEventsToRun)
)

process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 1
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )


process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring(
       'dcache:/pnfs/cms/WAX/11/store/user/lnujj/SnowMass13/ajkumar/TTtoAnything_14TeV_pythia6/SQWaT_PAT_601_SMv2/466338a8c77920bde95d5fb29d0e4448/pat_53x_test_v03_10_1_FH5.root'
) )




##########################################
# Apply loose PF jet ID
from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector
process.ak5PFGoodJets = cms.EDFilter("PFJetIDSelectionFunctorFilter",
     filterParams = pfJetIDSelector.clone(),
     src = cms.InputTag("selectedPatJetsPFlow"),
     filter = cms.bool(True)
)

process.ak5PFJetsLooseId = cms.EDFilter("PATJetRefSelector",
    src = cms.InputTag("ak5PFGoodJets"),
    cut = cms.string('pt > 20.0')
)

process.SnowmassTree = cms.EDAnalyzer("SnowmassTreeProducer", 
    HistOutFile = cms.string("test1.root"),
    srcJets = cms.InputTag("ak5PFJetsLooseId"),
)


#process.outpath.remove(process.out)
process.p = cms.Path( process.ak5PFGoodJets *
                      process.ak5PFJetsLooseId *
                      process.SnowmassTree)
