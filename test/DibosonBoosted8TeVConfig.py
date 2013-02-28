from RooWjj2DFitterPars import Wjj2DFitterPars
from ROOT import kRed, kAzure, kGreen, kBlue, kCyan, kViolet, kGray

def theConfig(Nj, mH, isElectron = False, initFile = [], includeSignal = True):
    pars = Wjj2DFitterPars()

    # pars.MCDirectory = '/uscms_data/d2/andersj/Wjj/2012/data/Moriond2013/ReducedTrees/'
    pars.MCDirectory = '/uscms_data/d1/lnujj/RDTrees_BoostedW_2013_1_29/'
    pars.isElectron = isElectron
    pars.btagSelection = False
    pars.boostedSelection = True
    pars.useTopSideband = False
    pars.useTopMC = True
    
    pars.initialParametersFile = initFile

    pars.backgrounds = ['diboson', 'top', 'WpJ']
    pars.includeSignal = includeSignal
    pars.signals = []
    pars.constrainShapes = []
    if pars.btagSelection:
        pars.yieldConstraints = {'top' : 0.50, 'WpJ' : 0.50 }
    else:
        pars.yieldConstraints = {'top' : 0.07, 'WpJ' : 0.05 }
        pars.constrainShapes = ['WpJ', 'top', 'diboson']

    #pars.yieldConstraints = {}

#    pars.yieldConstraints = {'top' : 0.50, 'WpJ' : 0.50 }
    #pars.constrainShapes = ['WpJ']

    pars.Njets = Nj
    pars.mHiggs = mH

    if isElectron:
        flavorString = 'el'
    else:
        flavorString = 'mu'


    pars.cuts = \
              '(W_pt>200.)&&(GroomedJet_CA8_pt[0]>200)' +\
              '&&(abs(GroomedJet_CA8_eta[0])<2.4)' +\
              '&&(GroomedJet_CA8_mass_pr[0]>40)' +\
              '&&(GroomedJet_CA8_tau2tau1[0]<0.55)'

    pars.btagVeto = False

    if pars.useTopSideband:
        pars.cuts += '&&(GroomedJet_numberbjets_csvm>=1)'
    # elif pars.btagSelection:
    #     pars.cuts += '&&(GroomedJet_numberbjets==1)'
    else:
        pars.cuts += '&&(ggdboostedWevt==1)' +\
                     '&&(GroomedJet_CA8_deltaphi_METca8jet>2.0)' +\
                     '&&(GroomedJet_CA8_deltaR_lca8jet>1.57)'
        pars.cuts += '&&(numPFCorJetBTags<1)'

        

    # veto vbf
    pars.cuts += '&&(vbf_event==0)'

    # you need a files entry and a models entry for each of the fit 
    # compoents in backgrounds and signals
    # the files should a list with entries like (filename, Ngen, xsec)

    pars.dibosonFiles = [
        (pars.MCDirectory + 'RD_%s_WW_CMSSW532.root' % (flavorString),
         9450414, 57.1097),
        (pars.MCDirectory + 'RD_%s_WZ_CMSSW532.root' % (flavorString),
         10000267, 32.3161),
        ]
    pars.dibosonFracOfData = -1
    #pars.dibosonModels = [5]
    pars.dibosonModels = [22]



    pars.WpJFiles = [
        (pars.MCDirectory + 'RD_%s_WJets_madgraph_CMSSW532.root' % (flavorString),
         8955318, 1.3*228.9),
        ]
    if pars.btagSelection:
        pars.WpJFracOfData = 0.332
    else:
        if isElectron:
            pars.WpJFracOfData = 0.725
        else:
            pars.WpJFracOfData = 0.729

    pars.WpJModels = [8]

    ttkfactor = 1.07
    pars.topFiles = [
        (pars.MCDirectory + 'RD_%s_STopTW_Tbar_CMSSW532.root' % (flavorString),
         493458, 11.1773*ttkfactor),
        (pars.MCDirectory + 'RD_%s_STopTW_T_CMSSW532.root' % (flavorString),
         497657, 11.1773*ttkfactor),
        (pars.MCDirectory + 'RD_%s_TTJetsPoheg_CMSSW532.root' % (flavorString),
         20975917, 225.197*ttkfactor),
        (pars.MCDirectory + 'RD_%s_STopS_Tbar_CMSSW532.root' % (flavorString),
         139974, 1.75776*ttkfactor),
        (pars.MCDirectory + 'RD_%s_STopS_T_CMSSW532.root' % (flavorString),
         259960, 3.89394*ttkfactor),
        (pars.MCDirectory + 'RD_%s_STopT_Tbar_CMSSW532.root' % (flavorString),
         1935066, 30.0042*ttkfactor),
        (pars.MCDirectory + 'RD_%s_STopT_T_CMSSW532.root' % (flavorString),
         3758221, 55.531*ttkfactor),
        ]
    
    if pars.btagSelection:
        pars.topFracOfData = 0.616
##         if isElectron:
##             pars.topModels = [5]
##         else:
##             pars.topModels = [13]
    else:
        if isElectron:
            pars.topFracOfData = 0.209
        else:
            pars.topFracOfData = 0.207


    pars.topModels = [30]


    pars.dibosonPlotting = {'color' : kAzure+8, 'title' : 'WW+WZ'}
    pars.WpJPlotting = { 'color' : kRed, 'title' : 'V+jets'}
    pars.topPlotting = {'color' : kGreen+2, 'title' : 'top'}
    pars.ggHPlotting = {'color' : kBlue, 'title' : "ggH(%i) #rightarrow WW" % mH}

    pars.var = ['GroomedJet_CA8_mass_pr[0]']
    pars.varRanges = {'GroomedJet_CA8_mass_pr[0]': (10, 40., 140., []),}
    pars.varTitles = {'GroomedJet_CA8_mass_pr[0]': 'm_{J}',
                      }
    pars.varNames = {'GroomedJet_CA8_mass_pr[0]': 'GroomedJet_CA8_mass_pr' }

    
    pars.exclude = {}
    pars.blind = False

    pars.integratedLumi = 19300.

    pars.binData = False
    # pars.binData = True

    return customizeElectrons(pars) if isElectron else \
        customizeMuons(pars)

def customizeElectrons(pars):
    pars.DataFile = pars.MCDirectory + 'RD_WenuJets_DataAllSingleElectronTrigger_GoldenJSON_19p2invfb.root'

    if pars.useTopSideband and not pars.useTopMC:
        pars.topFiles = [(pars.DataFile,1,1),]
    
    pars.integratedLumi = 19200.
    pars.doEffCorrections = True
    pars.effToDo = ['lepton']
    pars.leptonEffFiles = {
        'id': ["EffTable2012/scaleFactor-Run2012ABC-GsfElectronToId.txt"],
        'reco': ["EffTable2012/scaleFactor-Run2012ABC-SCToElectron.txt"],
        'HLT': ["EffTable2012/efficiency-Run2012ABC-WP80ToHLTEle.txt"]
        }
    pars.lumiPerEpoch = [pars.integratedLumi]

##     pars.cuts += '&&(W_electron_pt>30)'
    pars.cuts += '&&(event_met_pfmet >70)&&(W_electron_pt>35)'
    return pars

def customizeMuons(pars):
    pars.DataFile = pars.MCDirectory + 'RD_WmunuJets_DataAll_GoldenJSON_19p3invfb.root'

    if pars.useTopSideband and not pars.useTopMC:
        pars.topFiles = [(pars.DataFile,1,1),]
    
    pars.doEffCorrections = True
    pars.effToDo = ['lepton']
    pars.leptonEffFiles = {
        'id': ["EffTable2012/scaleFactor-Run2012ABC-RecoToIso.txt"],
        'HLT': ["EffTable2012/efficiency-Run2012ABC-IsoToIsoMuHLT.txt"]
        }
    pars.lumiPerEpoch = [pars.integratedLumi]

    pars.cuts += '&&(event_met_pfmet >50)&&(abs(W_muon_eta)<2.1)&&(W_muon_pt>30.)'
    
    return pars
