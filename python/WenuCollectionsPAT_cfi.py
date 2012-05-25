import FWCore.ParameterSet.Config as cms

#WP80 electrons, only track iso, remove H/E cut


isQCD = False

superclusterCutString_EB = cms.string("")
superclusterCutString_EE = cms.string("")
isolationCutString = cms.string("")

if isQCD:
    superclusterCutString_EB = "1==1"
    superclusterCutString_EE = "1==1"
    isolationCutString = "(dr03TkSumPt/p4.Pt >0.05)"
else:
    superclusterCutString_EB = "( -0.06<deltaPhiSuperClusterTrackAtVtx<0.06 )&&( -0.004<deltaEtaSuperClusterTrackAtVtx<0.004 )"
    superclusterCutString_EE = "( -0.03<deltaPhiSuperClusterTrackAtVtx<0.03 )&&( -0.007<deltaEtaSuperClusterTrackAtVtx<0.007 )"
    isolationCutString = "(dr03TkSumPt/p4.Pt <0.1)"


tightElectrons = cms.EDFilter("PATElectronRefSelector",
    src = cms.InputTag( "selectedPatElectronsPFlow" ),
    cut = cms.string(
    "(ecalDrivenSeed==1) && (abs(superCluster.eta)<2.5)"
    " && !(1.4442<abs(superCluster.eta)<1.566)"
    " && (et>20.0)"
    " && (gsfTrack.trackerExpectedHitsInner.numberOfHits==0 && !(-0.02<convDist<0.02 && -0.02<convDcot<0.02))"
    " && " + isolationCutString +
    " && ((isEB"
    " && (sigmaIetaIeta<0.01)"
    " && " + superclusterCutString_EB +
    ")"
    " || (isEE"
    " && (sigmaIetaIeta<0.03)"
    " && " + superclusterCutString_EE +
    "))"
    )
)



WToEnu = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("tightElectrons patMETsPFlow"),
## Note: the 'mt()' method doesn't compute the transverse mass correctly, so we have to do it by hand.
    cut = cms.string('daughter(0).pt >20 && daughter(1).pt >20  && sqrt(2*daughter(0).pt*daughter(1).pt*(1-cos(daughter(0).phi-daughter(1).phi)))>40'),
    checkCharge = cms.bool(False),
)




bestWToEnu =cms.EDFilter("LargestPtCandViewSelector",
    maxNumber = cms.uint32(10),
    src = cms.InputTag("WToEnu")                 
)


##  Define loose electron selection for veto ######
## modified WP95
looseElectrons = cms.EDFilter("PATElectronRefSelector",
    src = cms.InputTag( "selectedPatElectronsPFlow" ),
    cut = cms.string(
    "ecalDrivenSeed==1 && (abs(superCluster.eta)<2.5)"
    " && !(1.4442<abs(superCluster.eta)<1.566)"
    " && (ecalEnergy*sin(superClusterPosition.theta)>20.0)"
    " && (gsfTrack.trackerExpectedHitsInner.numberOfHits == 0)"
    " && (dr03TkSumPt/p4.Pt <0.2)" 
    " && ((isEB"
    " && (sigmaIetaIeta<0.01)"
    " && ( -0.8<deltaPhiSuperClusterTrackAtVtx<0.8 )"
    " && ( -0.007<deltaEtaSuperClusterTrackAtVtx<0.007 )"
    ")"
    " || (isEE"
    " && (sigmaIetaIeta<0.03)"
    " && ( -0.7<deltaPhiSuperClusterTrackAtVtx<0.7 )"
    " && ( -0.01<deltaEtaSuperClusterTrackAtVtx<0.01 )"
    "))"
    )
)


looseElectronFilter = cms.EDFilter("PATCandViewCountFilter",
    minNumber = cms.uint32(1),
    maxNumber = cms.uint32(1),
    src = cms.InputTag("looseElectrons")                     
)


##  Define loose muon selection for veto ######
looseMuons = cms.EDFilter("PATMuonRefSelector",
    src = cms.InputTag("selectedPatMuonsPFlow"),
    cut = cms.string("pt>10 && isGlobalMuon && isTrackerMuon && abs(eta)<2.5"
                     " && (isolationR03().sumPt+isolationR03().emEt+isolationR03().hadEt)/pt< 0.3")     
)

looseMuonFilter = cms.EDFilter("PATCandViewCountFilter",
    minNumber = cms.uint32(0),
    maxNumber = cms.uint32(0),
    src = cms.InputTag("looseMuons")                     
)


WSequence = cms.Sequence(tightElectrons *
                         WToEnu *
                         bestWToEnu
                         )
VetoSequence = cms.Sequence( looseElectrons *
                             looseElectronFilter *
                             looseMuons *
                             looseMuonFilter
                             )

WPath = cms.Sequence(WSequence*VetoSequence)

