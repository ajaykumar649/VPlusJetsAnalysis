from RooWjj2DFitterPars import Wjj2DFitterPars
from ROOT import kRed, kAzure, kGreen, kBlue, kCyan, kViolet, kGray, kYellow

def theConfig(Nj, mH, isElectron = False, initFile = [], includeSignal = True,
              btagged = False):
    pars = Wjj2DFitterPars()

    pars.MCDirectory = "root://cmseos:1094//eos/uscms/store/user/lnujj/DibosonFitPostMoriond2013/"

    pars.isElectron = isElectron
    pars.initialParametersFile = initFile

    pars.Njets = Nj
    pars.mHiggs = 126.

    if isElectron:
        flavorString = 'el'
    else:
        flavorString = 'mu'

    pars.cuts = '(sqrt(JetPFCor_Pt[0]**2+JetPFCor_Pt[1]**2+2*JetPFCor_Pt[0]*JetPFCor_Pt[1]*cos(JetPFCor_Phi[0]-JetPFCor_Phi[1]))>70.)' + \
        '&&(abs(JetPFCor_Eta[0]-JetPFCor_Eta[1])<1.5)' + \
        '&&(abs(JetPFCor_dphiMET[0])>0.4)' + \
        '&&(W_mt>30.)'


    pars.cuts += '&&(JetPFCor_Pt[1]>35.)' + \
        '&&(JetPFCor_Pt[0]>40.)' + \
        '&&(JetPFCor_Pt[2]<30.)'
##     pars.cuts += '&&(JetPFCor_Pt[1]>35.)' + \
##         '&&(JetPFCor_Pt[0]>40.)'
 
    pars.backgrounds = ['diboson', 'top', 'WpJ']
    pars.yieldConstraints = {'top' : 0.07, 'WpJ' : 0.05}

    pars.dibosonFiles = [
        (pars.MCDirectory + 'RD_%s_WW_CMSSW532.root' % (flavorString),
         9450414, 57.1097),
        (pars.MCDirectory + 'RD_%s_WZ_CMSSW532.root' % (flavorString),
         10000267, 32.3161),
        ]
    pars.dibosonFracOfData = -1
    pars.dibosonModels = [-1]

#####################  WpJ: #######################################
    wpj_kfactor = 1.16
    pars.WpJFiles = [
        # (pars.MCDirectory + 'RD_%s_WpJ_CMSSW532.root' % (flavorString),
        #  18353019+50768992, 36257.2),
        # (pars.MCDirectory + 'RD_%s_W1Jets_CMSSW532.root' % (flavorString),
        #  19871598, 5400.0*wpj_kfactor),
        (pars.MCDirectory + 'RD_%s_W2Jets_CMSSW532.root' % (flavorString),
         33004921, 1750.0*wpj_kfactor),
        (pars.MCDirectory + 'RD_%s_W3Jets_CMSSW532.root' % (flavorString),
         15059503, 519.0*wpj_kfactor),
        (pars.MCDirectory + 'RD_%s_W4Jets_CMSSW532.root' % (flavorString),
         12842803, 214.0*wpj_kfactor),
        (pars.MCDirectory + 'RD_%s_ZpJ_CMSSW532.root' % (flavorString),
         30209426, 3503.71),
        ]

    pars.WpJModels = [-1]
    pars.WpJFracOfData = -1
    

#####################  top: #######################################    
    pars.topFiles = [
        (pars.MCDirectory + 'RD_%s_TTbar_CMSSW532.root' % (flavorString),
         6893735, 225.197),
        (pars.MCDirectory + 'RD_%s_STopS_Tbar_CMSSW532.root' % (flavorString),
         139974, 1.75776),
        (pars.MCDirectory + 'RD_%s_STopS_T_CMSSW532.root' % (flavorString),
         259960, 3.89394),
        (pars.MCDirectory + 'RD_%s_STopT_Tbar_CMSSW532.root' % (flavorString),
         1935066, 30.0042),
        (pars.MCDirectory + 'RD_%s_STopT_T_CMSSW532.root' % (flavorString),
         3758221, 55.531),
        (pars.MCDirectory + 'RD_%s_STopTW_Tbar_CMSSW532.root' % (flavorString),
         493458, 11.1773),
        (pars.MCDirectory + 'RD_%s_STopTW_T_CMSSW532.root' % (flavorString),
         497657, 11.1773),
        ]

    pars.topFracOfData = -1
    pars.topModels = [-1] #anti-btag selection
    
    pars.dibosonPlotting = {'color' : kAzure+8, 'title' : 'WW+WZ'}
    pars.WpJPlotting = { 'color' : kRed, 'title' : 'V+jets'}
    pars.ZpJPlotting = { 'color' : kYellow, 'title' : 'Z+jets'}
    pars.topPlotting = {'color' : kGreen+2, 'title' : 'top'}
    pars.QCDPlotting = {'color' : kGray, 'title' : 'multijet'}
    pars.WHbbPlotting = {'color' : kBlue, 'title' : 'WHbb'}

    pars.var = ['Mass2j_PFCor']
    pars.varRanges = {'Mass2j_PFCor': (14, 48., 160., []),}
    pars.varTitles = {'Mass2j_PFCor': 'm_{jj}',
                      }
    pars.varNames = {'Mass2j_PFCor': 'Mass2j_PFCor' }

    pars.integratedLumi = 19300.

    # pars.binData = False
    pars.binData = True

    pars.includeSignal = includeSignal
    pars.signals = []

    return customizeElectrons(pars) if isElectron else \
        customizeMuons(pars)

    
        
def customizeElectrons(pars):
    
    pars.DataFile = pars.MCDirectory + 'RD_WenuJets_DataAllSingleElectronTrigger_GoldenJSON_19p2invfb.root'

    if ((not pars.useTopSideband) and (not pars.btagSelection)):
        pars.QCDFiles = [(pars.SecondaryDirectory + 'RDQCD_WenuJets_Isog0p3NoElMVA_19p2invfb.root',
                          1,1), #The events come from the data sideband
                         ]
        pars.backgrounds.append('QCD')
        
##         if pars.btagSelection:
##             pars.QCDFracOfData = 0.054
##             pars.QCDModels = [0]
##             pars.yieldConstraints['QCD'] = 0.5
        pars.QCDFracOfData = 0.07
        pars.QCDModels = [17]
        #pars.QCDModels = [-1]
        pars.yieldConstraints['QCD'] = 0.5

            
        pars.QCDModelsAlt = pars.QCDModels
        pars.QCDConvModels = pars.GlobalConvModels
        pars.QCDConvModelsAlt = pars.QCDConvModels


    pars.doEffCorrections = True
    pars.effToDo = ['lepton']
    pars.leptonEffFiles = {
        'id': ["EffTable2012/scaleFactor-Run2012ABC-GsfElectronToId.txt"],
        'reco': ["EffTable2012/scaleFactor-Run2012ABC-SCToElectron.txt"],
        'HLT': ["EffTable2012/efficiency-Run2012ABC-WP80ToHLTEle.txt"]
        }
    pars.lumiPerEpoch = [pars.integratedLumi]

    pars.integratedLumi = 19200.
    pars.QCDcuts += '&&(W_electron_pt>30)'
    pars.cuts += '&&(W_electron_pt>30)'
    return pars

def customizeMuons(pars):

    pars.DataFile = pars.MCDirectory + 'RD_WmunuJets_DataAll_GoldenJSON_19p3invfb.root'
    
    pars.doEffCorrections = True
    pars.effToDo = ['lepton']
    pars.leptonEffFiles = {
        'id': ["EffTable2012/scaleFactor-Run2012ABC-RecoToIso.txt"],
        'HLT': ["EffTable2012/efficiency-Run2012ABC-IsoToIsoMuHLT.txt"]
        }
    pars.lumiPerEpoch = [pars.integratedLumi]

    pars.QCDcuts += '&&(abs(W_muon_eta)<2.1)&&(W_muon_pt>25.)'
    pars.cuts += '&&(abs(W_muon_eta)<2.1)&&(W_muon_pt>25.)'
    
    return pars
