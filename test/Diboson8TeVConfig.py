from RooWjj2DFitterPars import Wjj2DFitterPars
from ROOT import kRed, kAzure, kGreen, kBlue, kCyan, kViolet, kGray, kYellow

def theConfig(Nj, mH, isElectron = False, initFile = [], includeSignal = True,
              btagged = False):
    pars = Wjj2DFitterPars()

    #pars.MCDirectory = '/uscms_data/d2/andersj/Wjj/2012/data/Moriond2013/ReducedTrees/'
    #pars.SecondaryDirectory = "/uscms_data/d3/ilyao/QCD8TeV/Moriond13/"
    # pars.MCDirectory = "root://cmseos:1094//eos/uscms/store/user/lnujj/HCP2012METfix/ReducedTrees/"
    #    fitterPars.MCDirectory = "root://cmssrv32.fnal.gov//store/user/lnujj/WjjTrees/Full2011DataFall11MC/OriginalTree_PAT/"
    pars.MCDirectory = "root://cmseos:1094//eos/uscms/store/user/lnujj/DibosonFitPostMoriond2013/"
    pars.SecondaryDirectory = pars.MCDirectory
    pars.isElectron = isElectron
    pars.btagSelection = btagged
    pars.boostedSelection = False
    pars.useTopSideband = False
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
 
    #implement topselection, btagged or anti-btagged cuts
    pars.btagVeto = False
    if pars.useTopSideband:
        pars.cuts += '&&(TopWm>0)'
    else:
        startRange = 0
        if pars.btagSelection:
            startRange = 2
            for i in range(0, startRange):
                # pars.cuts += '&&(JetPFCor_bDiscriminatorCSV[%i]>0.244)' % i
                pars.cuts += '&&(JetPFCor_bDiscriminatorCSV[%i]>0.679)' % i
        for i in range(startRange, 6):
            pars.cuts += '&&((abs(JetPFCor_Eta[%i])>2.4)||' % i + \
                         '(JetPFCor_Pt[%i]<30.)||' % i + \
                         '(JetPFCor_bDiscriminatorCSV[%i]<0.244))' % i    

    # veto boosted topology
    # pars.cuts += '&&(ggdboostedWevt==0)&&(W_pt<200.)'
    pars.cuts += '&&(W_pt<200.)'

    # veto vbf
    pars.cuts += '&&(vbf_event==0)'

    #pars.backgrounds = ['diboson', 'top', 'WpJ', 'ZpJ']
    pars.backgrounds = ['diboson', 'top', 'WpJ']
    pars.yieldConstraints = {'top' : 0.07, 'WpJ' : 0.05}
    pars.constrainShapes = ['WpJ']
    
    if pars.useTopSideband:
        pars.backgrounds = ['top', 'WpJ']
        pars.yieldConstraints = {}

    if pars.btagSelection:
        # pars.backgrounds = ['diboson', 'WHbb', 'top', 'WpJ', 'ZpJ']
        pars.backgrounds = ['diboson', 'top', 'WpJ', 'ZpJ']
        pars.yieldConstraints = {'top' : 0.07, 'WpJ' : 0.1, 'ZpJ' : 0.1 }
        pars.constrainShapes = ['top', 'WpJ', 'diboson']

    # you need a files entry and a models entry for each of the fit 
    # compoents in backgrounds and signals
    # the files should a list with entries like (filename, Ngen, xsec)
#################### Global Convolution Models ####################
    #pars.GlobalConvModels=[27]
    pars.GlobalConvModels=[-1]
    pars.GlobalConvModelsAlt=pars.GlobalConvModels
    
#####################  diboson: #######################################
    pars.dibosonFiles = [
        (pars.MCDirectory + 'RD_%s_WW_CMSSW532.root' % (flavorString),
         9450414, 57.1097),
        (pars.MCDirectory + 'RD_%s_WZ_CMSSW532.root' % (flavorString),
         10000267, 32.3161),
        ]
    pars.dibosonFracOfData = -1
    pars.dibosonModels = [22]
    #pars.dibosonModels = [-1]
    pars.dibosonModelsAlt = pars.dibosonModels
    pars.dibosonConvModels = pars.GlobalConvModels
    pars.dibosonConvModelsAlt = pars.dibosonConvModels
    
#####################  WpJ: #######################################
    wpj_kfactor = 1.16
    if pars.btagSelection:
        wpj_kfactor = 2.05 # from arXiv:1011.6647 [hep-ph]
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

    # To implement Template Morphing set pars.WpJModels=[-2]
    # and be sure to edit the WpJ*InputParameters.txt file so that the
    # naming scheme corresponds to the correct components/subcomponents.
    # E.g. the parameters from the shape fit to WpJ default MC should
    # contain the suffix Nom, while the overall yield shouldn't, and the
    # lines
    # fMU_WpJ = 0.0 +/- 100.0 L(-1 - 1)
    # fSU_WpJ = 0.0 +/- 100.0 L(-1 - 1)
    # should be added to the .txt file

    # pars.WpJModels = [-2]

    if pars.btagSelection:
        pars.WpJModels = [14]
        pars.WpJFracOfData = -1
    else:
        pars.WpJModels = [10]
        #pars.WpJModels = [-2]
        #pars.WpJFracOfData = 0.78 
        pars.WpJFracOfData = -1
    
    pars.WpJ_NomFiles = pars.WpJFiles
#    pars.WpJ_NomModels = [23]
    pars.WpJ_NomModels = [-1]
    pars.WpJ_NomAuxModels = [5]
    pars.WpJ_MUFiles = [ (pars.MCDirectory + 'RD_%s_WpJmatchingup_CMSSW532.root' % (flavorString), 20976007, 36257.2), (pars.SecondaryDirectory + 'RD_%s_WpJmatchingup_CMSSW532_UserGen.root' % (flavorString), 20976007, 36257.2), ]##the centrally produced and user generated samples are added with equal weights
    pars.WpJ_MUModels = [-1]
    pars.WpJ_MDFiles = [ (pars.MCDirectory + 'RD_%s_WpJmatchingdown_CMSSW532.root' % (flavorString), 21364575, 36257.2), (pars.SecondaryDirectory + 'RD_%s_WpJmatchingdown_CMSSW532_UserGen.root' % (flavorString), 21364575, 36257.2), ]
    pars.WpJ_MDModels = [-1]
    pars.WpJ_SUFiles = [ (pars.MCDirectory + 'RD_%s_WpJscaleup_CMSSW532.root' % (flavorString), 20784694, 36257.2), (pars.SecondaryDirectory + 'RD_%s_WpJscaleup_CMSSW532_UserGen.root' % (flavorString), 20784694, 36257.2), ]
    pars.WpJ_SUModels = [-1]
    pars.WpJ_SDFiles = [ (pars.MCDirectory + 'RD_%s_WpJscaledown_CMSSW532.root' % (flavorString), 20760830, 36257.2), (pars.SecondaryDirectory + 'RD_%s_WpJscaledown_CMSSW532_UserGen.root' % (flavorString), 20760830, 36257.2), ]
    pars.WpJ_SDModels = [-1]

##     #Fitting the alternate samples as a cross check (& to potentially inflate the fit errors)
##     pars.WpJ_MUModels = [10]
##     pars.WpJ_MDModels = [10]
##     pars.WpJ_SUModels = [10]
##     pars.WpJ_SDModels = [10]
    
    
    pars.WpJModelsAlt = [24]
    pars.WpJAuxModelsAlt = [3]
##     if isElectron:
##         pars.WpJModelsAlt = [23]
##         pars.WpJAuxModelsAlt = [4]
    
    pars.WpJ_NomModelsAlt = pars.WpJ_NomModels
    pars.WpJ_NomAuxModelsAlt = pars.WpJ_NomAuxModels
    pars.WpJ_MUModelsAlt = pars.WpJ_MUModels
    pars.WpJ_MDModelsAlt = pars.WpJ_MDModels
    pars.WpJ_SUModelsAlt = pars.WpJ_SUModels
    pars.WpJ_SDModelsAlt = pars.WpJ_SDModels
    pars.WpJConvModels = pars.GlobalConvModels
    pars.WpJConvModelsAlt = pars.WpJConvModels
    
    if pars.useTopSideband:
        pars.WpJModels = [-1]

#####################  ZpJ: #######################################
    pars.ZpJFiles = [
        (pars.MCDirectory + 'RD_%s_ZpJ_CMSSW532.root' % (flavorString),
         30209426, 3503.71),
        ]

    pars.ZpJFracOfData = -1
    #pars.ZpJFracOfData = 0.045
    pars.ZpJModels = [14]
    #pars.ZpJModels = [-1]
    #pars.ZpJAuxModels = [4]
    if pars.btagSelection:
        pars.ZpJModels = [0]
        pars.ZpJAuxModels = [3]
        pars.ZpJFracOfData = -1

    pars.ZpJModelsAlt = pars.ZpJModels
    pars.ZpJConvModels = pars.GlobalConvModels
    pars.ZpJConvModelsAlt = pars.ZpJConvModels

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

    if pars.btagSelection:
        pars.topFracOfData = -1
        pars.topModels = [17] #btag selection
    else:
        pars.topFracOfData = -1
        #pars.topFracOfData = 0.046
        pars.topModels = [13] #anti-btag selection

    #pars.topModels = [-1]
    pars.topModelsAlt = pars.topModels
    pars.topConvModels = pars.GlobalConvModels
    pars.topConvModelsAlt = pars.topConvModels

    if pars.useTopSideband:
        pars.topModels = [-1]

#####################  HWH: #######################################
    pars.HWHFiles = [
        (pars.MCDirectory + 'RD_%s_WH_WToLNu_HToBB_M-125_CMSSW532.root' % (flavorString), 999998, 0.6966*0.577*(0.1075+0.1057+0.1125)),
        ]

    pars.HWHFracOfData = -1
    pars.HWHModels = [5]

    pars.HWHModelsAlt = pars.HWHModels
    pars.HWHConvModels = pars.GlobalConvModels
    pars.HWHConvModelsAlt = pars.HWHConvModels

###################################################################
    
    pars.dibosonPlotting = {'color' : kAzure+8, 'title' : 'WW+WZ'}
    pars.WpJPlotting = { 'color' : kRed, 'title' : 'V+jets'}
    pars.ZpJPlotting = { 'color' : kYellow, 'title' : 'Z+jets'}
    pars.topPlotting = {'color' : kGreen+2, 'title' : 'top'}
    pars.QCDPlotting = {'color' : kGray, 'title' : 'multijet'}
    pars.HWHPlotting = {'color' : kBlue, 'title' : 'WHbb'}

    pars.var = ['Mass2j_PFCor']
    pars.varRanges = {'Mass2j_PFCor': (14, 48., 160., []),
    #pars.varRanges = {'Mass2j_PFCor': (12, 48., 144., []),
                      }
    if pars.btagSelection:
        pars.varRanges = {'Mass2j_PFCor': (15, 40., 160., []),
                          }
    pars.varTitles = {'Mass2j_PFCor': 'm_{jj}',
                      }
    pars.varNames = {'Mass2j_PFCor': 'Mass2j_PFCor' }


    if pars.useTopSideband:
        pars.var = ['TopWm']
        pars.varRanges = {'TopWm': (14, 48., 160., []),}
        pars.varTitles = {'TopWm': 'Top m_{jj}',}
        pars.varNames = {'TopWm': 'TopWm' }
    
    
    pars.exclude = {}
    pars.blind = False
    # pars.v1binEdges = [50, 55.,60.,65.,70.,75.,80.,85.,95.,
    #                    105.,115.,125.,135.,150.,165.,180.,200.]
    # pars.v1nbins = len(pars.v1binEdges)-1

    pars.integratedLumi = 19300.

    # pars.binData = False
    pars.binData = False

    #Standard vs QCD cuts:
    pars.QCDcuts = pars.cuts
    pars.cuts += '&&(event_met_pfmet>25)'
    pars.QCDcuts += '&&(event_met_pfmet>20)'


    pars.includeSignal = includeSignal
    pars.signals = []

    return customizeElectrons(pars) if isElectron else \
        customizeMuons(pars)

    
        
def customizeElectrons(pars):
    
    pars.DataFile = pars.MCDirectory + 'RD_WenuJets_DataAllSingleElectronTrigger_GoldenJSON_19p2invfb.root'

    pars.QCDFiles = [
        (pars.SecondaryDirectory + 'RDQCD_WenuJets_Isog0p3NoElMVA_19p2invfb.root',
         1,1), #The events come from the data sideband
        ]
    
    if pars.btagSelection:
        pars.QCDModels = [0]
        pars.yieldConstraints['QCD'] = 0.5
    else:
        pars.backgrounds.append('QCD')

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
