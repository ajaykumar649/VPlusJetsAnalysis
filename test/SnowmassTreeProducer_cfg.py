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
eventsToSkip = 0
outFileName = "test1.root"

## numEventsToRun = -1
## eventsToSkip = 0
## outFileName = "TTdileptons_14TeV_PU50_POSTLS161.root"


## numEventsToRun = -1
## eventsToSkip = 0
## outFileName = "TTdileptons_14TeV_PU50bx25_POSTLS161.root"


## numEventsToRun = -1
## eventsToSkip = 0
## outFileName = "DYToLL_M_20_TuneZ2star_14TeV_PU50_POSTLS161.root"

## numEventsToRun = -1
## eventsToSkip = 0
## outFileName = "DYToLL_M_20_TuneZ2star_14TeV_PU50bx25_POSTLS161.root"

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

            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/TTdileptons_14TeV_pythia6/TTdileptons_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_TopPAT/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_10_1_Xqs.root',

    
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/TTdileptons_14TeV_pythia6/TTdileptons_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_TopPAT/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_10_1_Xqs.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/TTdileptons_14TeV_pythia6/TTdileptons_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_TopPAT/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_1_1_Yjl.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/TTdileptons_14TeV_pythia6/TTdileptons_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_TopPAT/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_2_2_WkL.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/TTdileptons_14TeV_pythia6/TTdileptons_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_TopPAT/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_3_1_lfs.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/TTdileptons_14TeV_pythia6/TTdileptons_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_TopPAT/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_4_1_Hps.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/TTdileptons_14TeV_pythia6/TTdileptons_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_TopPAT/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_5_1_uFG.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/TTdileptons_14TeV_pythia6/TTdileptons_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_TopPAT/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_6_1_GTL.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/TTdileptons_14TeV_pythia6/TTdileptons_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_TopPAT/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_7_1_ykz.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/TTdileptons_14TeV_pythia6/TTdileptons_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_TopPAT/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_8_1_shi.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/TTdileptons_14TeV_pythia6/TTdileptons_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_TopPAT/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_9_1_RN4.root',



##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/TTdileptons_14TeV_pythia6/TTdileptons_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_TopPAT/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_1_1_BNo.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/TTdileptons_14TeV_pythia6/TTdileptons_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_TopPAT/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_2_1_1V2.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/TTdileptons_14TeV_pythia6/TTdileptons_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_TopPAT/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_3_1_u5y.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/TTdileptons_14TeV_pythia6/TTdileptons_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_TopPAT/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_4_1_Yyw.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/TTdileptons_14TeV_pythia6/TTdileptons_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_TopPAT/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_5_1_JHg.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/TTdileptons_14TeV_pythia6/TTdileptons_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_TopPAT/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_6_1_739.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/TTdileptons_14TeV_pythia6/TTdileptons_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_TopPAT/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_7_1_Feb.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/TTdileptons_14TeV_pythia6/TTdileptons_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_TopPAT/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_8_1_NHk.root',



##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_10_1_w4a.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_11_1_rVq.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_12_1_3K2.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_13_1_hCQ.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_14_1_QVb.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_15_1_NeQ.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_16_1_FBm.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_17_1_e9M.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_18_1_0i9.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_19_1_nlg.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_1_1_KoE.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_20_1_j1e.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_21_1_7TR.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_22_1_Ust.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_23_1_R3u.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_24_1_7be.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_2_1_Luo.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_3_1_JNz.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_4_1_ECl.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_5_1_2nE.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_6_1_bpm.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_7_1_Jwj.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_8_1_7hX.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_9_1_sVP.root',


           
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_10_1_kKC.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_11_1_8eJ.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_12_1_P4C.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_13_1_JRx.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_14_1_wbh.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_15_1_QS6.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_16_1_Rs7.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_17_1_JM7.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_18_1_qze.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_19_1_acz.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_1_1_ERy.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_20_1_kRG.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_21_1_h0k.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_22_1_0Wy.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_23_1_ENk.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_24_1_hNe.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_25_1_3x0.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_26_1_idZ.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_2_1_Rvb.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_3_1_KJi.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_4_1_eL8.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_5_1_KDn.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_6_1_IqT.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_7_1_9vU.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_8_1_sE3.root',
##            'dcache:/pnfs/cms/WAX/11/store/user/jstupak/snowmass/jstupak/DYToLL_M_20_TuneZ2star_14TeV_pythia6/DYToLL_M_20_TuneZ2star_14TeV_pythia6_Summer12_PU50bx25_POSTLS161_V12_v1_AODSIM/0b89362859f64009081d5401e4e9f0ea/pat_53x_test_v03_9_1_bli.root',

           ),
       skipEvents = cms.untracked.uint32(eventsToSkip),
 )




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
                                          HistOutFile = cms.string(outFileName),
                                          srcJets = cms.InputTag("ak5PFJetsLooseId"),
                                      )


#process.outpath.remove(process.out)
process.p = cms.Path( process.ak5PFGoodJets *
                                            process.ak5PFJetsLooseId *
                                            process.SnowmassTree)
