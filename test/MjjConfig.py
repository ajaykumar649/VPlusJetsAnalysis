import pyroot_logon
from ROOT import gROOT
gROOT.ProcessLine('.L RooWjjFitterParams.h+');
from ROOT import RooWjjFitterParams

def theConfig(Nj, mcdir = '', initFile = '', toydataFile = '', e_minT = -1.0, e_maxT = -1.0):
    fitterPars = RooWjjFitterParams()

    fitterPars.smoothingOrder = 0
    fitterPars.MCDirectory = '/uscms_data/d2/kalanand/WjjTrees/Full2011DataFall11MC/ReducedTree_AOD/RD_'
    fitterPars.WpJDirectory = fitterPars.MCDirectory
    if (len(mcdir) > 0):
        fitterPars.WpJDirectory = mcdir
        fitterPars.toyWpJ = True
    fitterPars.QCDDirectory = fitterPars.MCDirectory[:-3]
    fitterPars.initParamsFile = initFile

    fitterPars.DataDirectory = fitterPars.MCDirectory
    fitterPars.muonData = 'WmunuJets_DataAll_GoldenJSON_4p7invfb.root'
    fitterPars.includeMuons = True
    fitterPars.electronData = 'WenuJets_DataAllSingleElectronTrigger_GoldenJSON_4p7invfb.root'
##     fitterPars.electronData = 'WenuJets_DataAll_GoldenJSON_4p7invfb.root'
    fitterPars.includeElectrons = True

##     fitterPars.NewPhysicsDirectory = '/uscms_data/d2/kalanand/WjjTrees/ReducedTree/NewKfitRDTree/RD_'
    fitterPars.NewPhysicsDirectory = fitterPars.MCDirectory
    fitterPars.fitToyDataset = False
    fitterPars.ToyDatasetDirectory = '/uscms_data/d1/ilyao/KinematicFitterS11/ErrorScans/1KMCSets/'
    fitterPars.toydataFile = toydataFile

    fitterPars.minMass = 30.
    fitterPars.maxMass = 400.
    fitterPars.nbins = 34
    fitterPars.intLumi = 4700. #5030.

    fitterPars.binEdges.push_back(fitterPars.minMass)

    binEdge = fitterPars.minMass
    print binEdge,' ',

## ### Scan between Min=120-140 (Max=160-180)
##     while (binEdge < 120.0):
##         binEdge += round(0.15*binEdge)
##         fitterPars.binEdges.push_back(binEdge)
##         print binEdge,' ',

##     binEdge=120;
##     fitterPars.binEdges[fitterPars.binEdges.size()-1] = binEdge;
##     print 'replaced with ',binEdge,' '

##     while (binEdge < 140.0):
##         binEdge += 2.0
##         fitterPars.binEdges.push_back(binEdge)
##         print binEdge,' ',

##     binEdge=140;
##     fitterPars.binEdges[fitterPars.binEdges.size()-1] = binEdge;
##     print 'replaced with ', binEdge,' ',

##     binEdge=160;
##     fitterPars.binEdges.push_back(binEdge)
##     print binEdge,' ',
    
##     while (binEdge < 182.0):
##         binEdge += 2.0
##         fitterPars.binEdges.push_back(binEdge)
##         print binEdge,' ',

##     binEdge=182;
##     fitterPars.binEdges[fitterPars.binEdges.size()-1] = binEdge;
##     print 'replaced with ',binEdge,' ',
    
    while (binEdge <= fitterPars.maxMass):
        binEdge += round(0.15*binEdge)
        fitterPars.binEdges.push_back(binEdge)
        print binEdge,' ',




    fitterPars.binEdges[fitterPars.binEdges.size()-1] = fitterPars.maxMass
##     fitterPars.maxMass = fitterPars.binEdges[fitterPars.binEdges.size()-1]
    
    print "mass range:",fitterPars.minMass,'-',fitterPars.maxMass
    
    fitterPars.truncRange = True
    fitterPars.blind = False
    fitterPars.minTrunc = 130.
    if e_minT>0:
        fitterPars.minTrunc = e_minT

    binMin = fitterPars.minMass
    for binEdge in fitterPars.binEdges:
        if binEdge > fitterPars.minTrunc:
            fitterPars.minTrunc = binMin
            break
        binMin = binEdge

    fitterPars.maxTrunc = 170.
    if e_maxT>0:
        fitterPars.maxTrunc = e_maxT
    
    for binEdge in fitterPars.binEdges:
        if binEdge > fitterPars.maxTrunc:
            fitterPars.maxTrunc = binEdge
            break

    fitterPars.minFit = 60.
    binMin = fitterPars.minMass
    for binEdge in fitterPars.binEdges:
        if binEdge > fitterPars.minFit:
            fitterPars.minFit = binMin
            break
        binMin = binEdge

    fitterPars.maxFit = 400.
    for binEdge in fitterPars.binEdges:
        if binEdge > fitterPars.maxFit:
            fitterPars.maxFit = binEdge
            break

    print 'truncate:',fitterPars.truncRange,':', fitterPars.minTrunc,'-',\
          fitterPars.maxTrunc
    print 'fit range:',fitterPars.minFit,'-',fitterPars.maxFit

    fitterPars.njets = Nj
    fitterPars.constrainDiboson = True

    fitterPars.doEffCorrections = True
    fitterPars.muIdEffFiles.push_back("EffTableDir/muonEffsRecoToIso_ScaleFactors.txt")
    fitterPars.muHLTEffFiles.push_back("EffTableDir/muonEffsIsoToHLT_data_LP_LWA.txt")
    fitterPars.lumiPerEpochMuon.push_back(fitterPars.intLumi)

    
    fitterPars.eleIdEffFiles.push_back("EffTableDir/eleEffsRecoToWP80_ScaleFactors.txt")
    fitterPars.eleRecoEffFiles.push_back("EffTableDir/eleEffsSCToReco_ScaleFactors.txt")
    fitterPars.eleHLTEffFiles.push_back("EffTableDir/eleEffsSingleElectron.txt")
    fitterPars.eleJ30EffFiles.push_back("EffTableDir/FullyEfficient.txt")
    fitterPars.eleJ25NoJ30EffFiles.push_back("EffTableDir/FullyEfficient_Jet2NoJet1.txt")
    fitterPars.eleMHTEffFiles.push_back("EffTableDir/FullyEfficient_MHT.txt")
    fitterPars.eleWMtEffFiles.push_back("EffTableDir/WMt50TriggerEfficiency.txt")
    fitterPars.lumiPerEpochElectron.push_back(fitterPars.intLumi)

##     fitterPars.eleIdEffFiles.push_back("EffTableDir/eleEffsRecoToWP80_ScaleFactors.txt")
##     fitterPars.eleRecoEffFiles.push_back("EffTableDir/eleEffsSCToReco_ScaleFactors.txt")
##     fitterPars.eleHLTEffFiles.push_back("EffTableDir/eleEffsHLTEle2jPfMht_data_LWA_Ele.txt")
##     fitterPars.eleJ30EffFiles.push_back("EffTableDir/eleEffsHLTEle2jPfMht_data_Jet30_FracLumi_post-epsCaloLWA.txt")
##     fitterPars.eleJ25NoJ30EffFiles.push_back("EffTableDir/eleEffsHLTEle2jPfMht_data_Jet25Not30_FracLumi_post-epsCaloLWA.txt")
##     fitterPars.eleMHTEffFiles.push_back("EffTableDir/eleEffsHLTEle2jPfMht_data_LWA_PfMht.txt")
##     fitterPars.lumiPerEpochElectron.push_back(3700)

    fitterPars.useExternalMorphingPars = False

    jetCut = '(evtNJ == %i)' % (Nj)
    if (Nj < 2):
        jetCut = '((evtNJ == 2) || (evtNJ == 3))'
       
    fitterPars.cuts = '(W_mt > 50.) ' + \
                      '&& %s ' % (jetCut) + \
                      '&& (abs(JetPFCor_Eta[0]-JetPFCor_Eta[1])<1.2) ' + \
                      '&& (sqrt(JetPFCor_Pt[0]**2+JetPFCor_Pt[1]**2+2*JetPFCor_Pt[0]*JetPFCor_Pt[1]*cos(JetPFCor_Phi[0]-JetPFCor_Phi[1]))>45.) ' + \
                      '&& (JetPFCor_Pt[1]/Mass2j_PFCor>0.3) ' + \
                      '&& (JetPFCor_Pt[1]/Mass2j_PFCor<0.7) ' + \
                      '&& (JetPFCor_Pt[0] > 40) '

    return fitterPars
