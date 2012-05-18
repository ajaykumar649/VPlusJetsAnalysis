import pyroot_logon
from ROOT import gROOT
gROOT.ProcessLine('.L RooWjjFitterParams.h+');
from ROOT import RooWjjFitterParams

def theConfig(Nj, mcdir = '', initFile = '', btag = False):
    fitterPars = RooWjjFitterParams()
    fitterPars.smoothingOrder = 1
    # fitterPars.MCDirectory = "/uscms_data/d2/kalanand/WjjTrees/Full2011DataFall11MC/ReducedTree_PAT/RD_"
    fitterPars.MCDirectory = "/uscms_data/d2/kalanand/WjjTrees/Full2011DataFall11MC/OriginalTree_PAT/"
    fitterPars.WpJDirectory = fitterPars.MCDirectory
    if (len(mcdir) > 0):
        fitterPars.WpJDirectory = mcdir
        fitterPars.toyWpJ = False
    ##fitterPars.QCDDirectory = fitterPars.MCDirectory[:-3]
    fitterPars.QCDDirectory = "/uscms_data/d2/kalanand/WjjTrees/Full2011DataFall11MC/ReducedTree_PAT/"
        
    fitterPars.initParamsFile = initFile
    fitterPars.constraintParamsFile = initFile
    fitterPars.DataDirectory = fitterPars.MCDirectory 
    fitterPars.muonData = 'WmunuJets_DataAll_GoldenJSON_4p7invfb.root'
    fitterPars.includeMuons = True    
    fitterPars.electronData = 'WenuJets_DataAllSingleElectronTrigger_GoldenJSON_4p7invfb.root'
    fitterPars.includeElectrons = True
   
    fitterPars.NewPhysicsDirectory = fitterPars.MCDirectory
    fitterPars.minMass = 40.
    fitterPars.maxMass = 150.
    fitterPars.nbins = 32
    fitterPars.intLumi = 5020.
    
    binEdge = fitterPars.minMass
    fitterPars.binEdges.push_back(binEdge)
    print binEdge,' ',
    while (binEdge < fitterPars.maxMass):
        binEdge += round(0.10*binEdge)
        fitterPars.binEdges.push_back(binEdge)
        print binEdge,' ',

##     fitterPars.binEdges[fitterPars.binEdges.size()-1] = fitterPars.maxMass
    fitterPars.maxMass = fitterPars.binEdges[fitterPars.binEdges.size()-1]

    print "mass range:",fitterPars.minMass,'-',fitterPars.maxMass
    
    fitterPars.truncRange = False
    fitterPars.blind = False
    fitterPars.minTrunc = 65.

    binMin = fitterPars.minMass
    for binEdge in fitterPars.binEdges:
        if binEdge > fitterPars.minTrunc:
            fitterPars.minTrunc = binMin
            break
        binMin = binEdge

    fitterPars.maxTrunc = 94.
    for binEdge in fitterPars.binEdges:
        if binEdge > fitterPars.maxTrunc:
            fitterPars.maxTrunc = binEdge
            break

    fitterPars.minFit = fitterPars.minMass
    binMin = fitterPars.minMass
    for binEdge in fitterPars.binEdges:
        if binEdge > fitterPars.minFit:
            fitterPars.minFit = binMin
            break
        binMin = binEdge

    fitterPars.maxFit = fitterPars.maxMass
    for binEdge in fitterPars.binEdges:
        if binEdge > fitterPars.maxFit:
            fitterPars.maxFit = binEdge
            break


    fitterPars.minWmass = fitterPars.minTrunc
    fitterPars.maxWmass = fitterPars.maxTrunc
    
    print 'truncate:',fitterPars.truncRange,':', fitterPars.minTrunc,'-',\
          fitterPars.maxTrunc
    print 'fit range:',fitterPars.minFit,'-',fitterPars.maxFit
    
    fitterPars.njets = Nj
    fitterPars.constrainDiboson = False
    fitterPars.constrainDibosonShape = False
    fitterPars.constrainWpJShape = False
    fitterPars.constrainWpJ = True

    
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

    fitterPars.useExternalMorphingPars = False

##     jetCut = '(jetPFCor_Pt[%i] < 2) ' % (Nj)
##     for j in range(0, Nj):
##         jetCut += '&& (JetPFCor_Pt[%i] > 30) ' % (j)
##    jetCut = '(ggdevt == %i)' % (Nj)
##     if (Nj < 2):
##         jetCut = '((ggdevt == 2) || (ggdevt == 3))'

    btagCut = 1.74
    fitterPars.cuts = '(sqrt(JetPFCor_Pt[0]**2+JetPFCor_Pt[1]**2+2*JetPFCor_Pt[0]*JetPFCor_Pt[1]*cos(JetPFCor_Phi[0]-JetPFCor_Phi[1]))>20.) ' + \
                      '&& (abs(JetPFCor_Eta[0]-JetPFCor_Eta[1])<1.5) ' + \
                      '&& (abs(JetPFCor_dphiMET[0])>0.4) '
    fitterPars.cuts += '&& (JetPFCor_Pt[2]<30) '
    #fitterPars.cuts += '&& (fit_status==0) '

    if btag:
        fitterPars.cuts += '&& ( (JetPFCor_bDiscriminator[0]>%.2f) || (JetPFCor_bDiscriminator[1]>%.2f) ) ' % (btagCut,btagCut)
        fitterPars.cuts += '&& (JetPFCor_Pt[1]>35) '
    else:
        fitterPars.cuts += '&& (JetPFCor_bDiscriminator[0]<%.2f) && (JetPFCor_bDiscriminator[1]<%.2f) ' % (btagCut,btagCut)
        fitterPars.cuts += '&& (JetPFCor_Pt[1]>35.) '

    return fitterPars
