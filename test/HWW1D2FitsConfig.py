from RooWjj2DFitterPars import Wjj2DFitterPars
from ROOT import kRed, kAzure, kGreen, kBlue, kCyan, kViolet, kGray
import HWWSignalShapes

# dictionaries of tuples keyed on the Higgs mass.  The tuple structure is
# (0: mavVariableName, 1: mvaCut, 2: min4BodyMass, 3: max4BodyMass, 
#  4: n4BodyBins, 5: dictionary with tuples specifying the model for 
#  each of the two components of the fit)
mu2Pars = {
    170: ( "mva2j170mu", 0.550, 165.0, 245.0, 10,
           {'diboson':(22, 8),'top':(13, 8),'WpJ':(15, 14),
            'ggH':(13, 5),'qqH':(13, 5)} ),
    180: ( "mva2j180mu", 0.750, 165.0, 245.0, 10,
           {'diboson': (22, 11),'top':(13, 8),'WpJ':(15, 14),
            'ggH':(13, 5),'qqH':(13, 5)} ),
    190: ( "mva2j190mu", 0.750, 165.0, 245.0, 10,
           {'diboson': (22, 11), 'top': (13, 8), 'WpJ': (15, 14), 
            'ggH': (13, 5), 'qqH': (13, 5)} ),
    200: ( "mva2j200mu", 0.750, 165.0, 245.0, 10,
           {'diboson': (22, 11), 'top': (13, 8), 'WpJ': (15, 14), 
            'ggH': (13, 5), 'qqH': (13, 5)} ),
    250: ( "mva2j250mu", 0.800, 200.0, 400.0, 10,
           {'diboson': (22, 11), 'top': (13, 10), 'WpJ': (10, 14), 
            'ggH': (13, 5), 'qqH': (7, 5)} ),
    300: ( "mva2j300mu", 0.800, 240.0, 400.0, 8,
           {'diboson': (22, 11), 'top': (5, 10), 'WpJ': (10, 12), 
            'ggH': (13, 5), 'qqH': (7, 5)} ),
    350: ( "mva2j350mu", 0.800, 250., 475., 9,
           {'diboson': (22, 11),'top':(5, 11),'WpJ':(10, 12),
            'ggH':(13, 5),'qqH':(7, 5)} ),
    400: ( "mva2j400mu", 0.800, 300.0, 600, 10,
           {'diboson':(31, 11),'top':(5, 10),'WpJ':(10, 12),
            'ggH':(13, 5),'qqH':(7, 5)} ),
    450: ( "mva2j450mu", 0.800, 340.0, 740.0, 10,
           {'diboson':(31, 12),'top':(5, 12),'WpJ':(10, 18),
            'ggH':(13, 5),'qqH':(7, 5)} ),
    500: ( "mva2j500mu", 0.750, 340.0, 780.0, 11,
           {'diboson': (22, 12), 'top': (5, 12), 'WpJ': (10, 18),
            'ggH': (13, 5),'qqH': (7, 5)} ),
    550: ( "mva2j550mu", 0.750, 340.0, 780.0, 11,
           {'diboson': (22, 12), 'top': (5, 12), 'WpJ': (10, 18),
            'ggH': (13, 5),'qqH': (7, 5)} ),
    600: ( "mva2j600mu", 0.750, 340.0, 780.0, 11,
           {'diboson': (22, 12), 'top': (5, 12), 'WpJ': (10, 18),
            'ggH': (13, 5),'qqH': (7, 5)} ),
    }

el2Pars = {
    170: ( "mva2j170el", 0.550, 165.0, 245.0, 10,
           {'diboson':(22, 8),'top':(13, 8),'WpJ':(15, 10),
            'ggH':(13, 5),'qqH':(13, 5)} ),
    180: ( "mva2j180el", 0.750, 165.0, 245.0, 10,
           {'diboson': (22, 11),'top':(13, 8),'WpJ':(10, 14),
            'ggH':(13, 5),'qqH':(13, 5)} ),
    190: ( "mva2j190el", 0.750, 165.0, 245.0, 10,
           {'diboson': (22, 11), 'top': (13, 8), 'WpJ': (10, 10), 
            'ggH': (13, 5), 'qqH': (13, 5)} ),
    200: ( "mva2j200el", 0.750, 165.0, 245.0, 10 ,
           {'diboson': (22, 11), 'top': (13, 8), 'WpJ': (10, 10), 
            'ggH': (13, 5), 'qqH': (7, 5)}),
    250: ( "mva2j250el", 0.800, 240.0, 400.0, 16,
           {'diboson': (22, 11), 'top': (5, 10), 'WpJ': (10, 12), 
            'ggH': (13, 5), 'qqH': (7, 5)} ),
    300: ( "mva2j300el", 0.800, 240.0, 400.0, 16,
           {'diboson': (22, 11), 'top': (5, 10), 'WpJ': (10, 12), 
            'ggH': (13, 5), 'qqH': (7, 5)} ),
    350: ( "mva2j350el", 0.800, 250., 475., 15,
           {'diboson': (22, 11),'top':(13, 11),'WpJ':(10, 12),
            'ggH':(13, 5),'qqH':(7, 5)} ),
    400: ( "mva2j400el", 0.800, 300.0, 600, 15,
           {'diboson':(22, 11),'top':(9, 10),'WpJ':(10, 12),
            'ggH':(13, 5),'qqH':(7, 5)} ),
    450: ( "mva2j450el", 0.800, 340.0, 780.0, 22,
           {'diboson':(22, 11),'top':(13, 12),'WpJ':(10, 12),
            'ggH':(13, 5),'qqH':(7, 5)} ),
    500: ( "mva2j500el", 0.750, 340.0, 780.0, 22,
           {'diboson': (22, 12), 'top': (5, 12), 'WpJ': (10, 12),
            'ggH': (13, 5),'qqH': (7, 5)} ),
    550: ( "mva2j550el", 0.750, 340.0, 780.0, 22,
           {'diboson': (22, 12), 'top': (5, 12), 'WpJ': (10, 12),
            'ggH': (13, 5),'qqH': (7, 5)} ),
    600: ( "mva2j600el", 0.750, 340.0, 780.0, 22,
           {'diboson': (22, 12), 'top': (5, 12), 'WpJ': (10, 12),
            'ggH': (13, 5),'qqH': (7, 5)} ),
    }

def theConfig(Nj, mH, isElectron = False, initFile = [], includeSignal = True):
    pars = Wjj2DFitterPars()

    pars.MCDirectory = '/uscms_data/d2/andersj/Wjj/2012/data/Moriond2013/ReducedTrees/'
    # pars.MCDirectory = "root://cmseos:1094//eos/uscms/store/user/lnujj/Moriond2013/RD_includingDiboson/"
    # pars.MCDirectory = "root://cmseos:1094//eos/uscms/store/user/lnujj/HCP2012METfix/ReducedTrees/"

    pars.DataDirectory = '/uscms_data/d2/andersj/Wjj/2012/data/Moriond2013/HWWTrees/'
    pars.isElectron = isElectron
    pars.initialParametersFile = initFile

    pars.backgrounds = ['diboson', 'WpJ', 'top']
    pars.includeSignal = includeSignal
    pars.signals = ['ggH', 'qqH']
    pars.yieldConstraints = { 'diboson' : 0.034, 'top' : 0.07 }
    #pars.yieldConstraints = {}
    pars.constrainShapes = ['WpJ']
    if mH > 200:
        pars.constrainShapes = ['WpJ']

    pars.Njets = Nj
    pars.mHiggs = mH

    modePars = mu2Pars
    if isElectron:
        flavorString = 'el'
        if Nj == 3:
            modePars = el3Pars
        else:
            modePars = el2Pars
    else:
        flavorString = 'mu'
        if Nj == 3:
            modePars = mu3Pars
        else:
            modePars = mu2Pars

    pars.cuts = '(ggdevt==%i)&&(fit_status==0)&&(W_mt>30)' % Nj
    pars.cuts += '&&(%s>%.3f)' % (modePars[mH][0], modePars[mH][1])
    # pars.cuts = '(fit_status==0)&&(W_mt>30)' + \
    #     '&&(%s>%.3f)' % (modePars[mH][0], modePars[mH][1])
    # pars.cuts += '&&(fit_mlvjj>%.0f)&&(fit_mlvjj<%.0f)' % (modePars[mH][2],
    #                                                        modePars[mH][3])
    
    #btag veto
    pars.btagVeto = False
    # for i in range(0, 6):
    #     pars.cuts += '&&((abs(JetPFCor_Eta[%i])>2.4)||' % i + \
    #         '(JetPFCor_Pt[%i]<30.)||' % i + \
    #         '(JetPFCor_bDiscriminatorCSV[%i]<0.679))' % i

    # veto boosted topology
    # if mH >= 600:
    #     pars.cuts += '&&(W_pt<200.)'

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
    pars.dibosonModels = [ modePars[mH][5]['diboson'][0] ]

    wpj_kfactor = 1.16
    pars.WpJFiles = [
        # (pars.MCDirectory + 'RD_%s_WpJ_CMSSW532.root' % (flavorString),
        #  18353019+50768992, 36257.2),
        (pars.MCDirectory + 'RD_%s_ZpJ_CMSSW532.root' % (flavorString),
         30209426, 3503.71),
        # (pars.MCDirectory + 'RD_%s_W1Jets_CMSSW532.root' % (flavorString),
        #  19871598, 5400.0*wpj_kfactor),
        (pars.MCDirectory + 'RD_%s_W2Jets_CMSSW532.root' % (flavorString),
         33004921, 1750.0*wpj_kfactor),
        (pars.MCDirectory + 'RD_%s_W3Jets_CMSSW532.root' % (flavorString),
         15059503, 519.0*wpj_kfactor),
        (pars.MCDirectory + 'RD_%s_W4Jets_CMSSW532.root' % (flavorString),
         12842803, 214.0*wpj_kfactor),
        ]
    pars.WpJModels = [ modePars[mH][5]['WpJ'][0] ]

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
    pars.topModels = [ modePars[mH][5]['top'][0] ]

    ngen = HWWSignalShapes.NgenHiggs(mH, 'ggH')
    pars.ggHFiles = [
        (pars.MCDirectory + HWWSignalShapes.makeSignalFilename(mH, "ggH",
                                                               isElectron),
         ngen[0], ngen[1]*ngen[2])
        ]
    pars.ggHModels = [ modePars[mH][5]['ggH'][0] ]
    if pars.mHiggs >= 400:
        pars.ggHInterference = True


    ngen = HWWSignalShapes.NgenHiggs(mH, 'qqH')
    pars.qqHFiles = [
        (pars.MCDirectory + HWWSignalShapes.makeSignalFilename(mH, "qqH",
                                                               isElectron),
         ngen[0], ngen[1]*ngen[2])
        ]
    pars.qqHModels = [ modePars[mH][5]['qqH'][0] ]

    pars.dibosonPlotting = {'color' : kAzure+8, 'title' : 'WW+WZ'}
    pars.WpJPlotting = { 'color' : kRed, 'title' : 'V+jets'}
    pars.topPlotting = {'color' : kGreen+2, 'title' : 'top'}
    pars.ggHPlotting = {'color' : kBlue, 'title' : "H(%i) #rightarrow WW" % mH}
    pars.qqHPlotting = {'color' : kBlue, 'title' : "H(%i) #rightarrow WW" % mH,
                        'visible' : True}

    pars.var = ['Mass2j_PFCor', 'fit_mlvjj']
    pars.varRanges = {'Mass2j_PFCor': (12, 50., 146., []),
                      'fit_mlvjj': (modePars[mH][4], modePars[mH][2], 
                                    modePars[mH][3], [])
                      }
    pars.varTitles = {'Mass2j_PFCor': 'm_{jj}',
                      'fit_mlvjj' : 'm_{l#nujj}'
                      }
    pars.exclude = {'Mass2j_PFCor' : (66., 66.+32.)}
    pars.blind = True

    pars.binData = False
    # pars.binData = True

    return customizeElectrons(pars) if isElectron else \
        customizeMuons(pars)

def customizeElectrons(pars):
    pars.DataFile = pars.DataDirectory + 'RD_WenuJets_DataAllSingleElectronTrigger_GoldenJSON_19p2invfb.root'
    pars.integratedLumi = 19200

    # pars.backgrounds.append('multijet')

    # pars.multijetFraction = 0.0637
    # pars.multijetFiles = [
    #     (pars.MCDirectory + 'RDQCD_WenuJets_Isog0p3NoElMVA_11p9invfb.root',
    #      1, pars.multijetFraction/pars.integratedLumi)
    #     ]
    # pars.multijetModels = (11, 1)
    # pars.yieldConstraints['multijet'] = 0.2
    # pars.multijetPlotting = {'color' : kGray+1, 'title' : 'multijet'}

    # pars.multijet_cuts = '(ggdevt==%i)&&(fit_status==0)&&(W_mt>30)' % pars.Njets
    # pars.multijet_cuts += '&&(abs(JetPFCor_dphiMET[0])>0.8)' + \
    #     '&&(W_electron_pt>35)' + \
    #     '&&(W_electron_pfIsoEA>0.3)'

    pars.doEffCorrections = True
    pars.effToDo = ['lepton']
    pars.leptonEffFiles = {
        'id': ["EffTable2012/scaleFactor-Run2012ABC-GsfElectronToId.txt"],
        'reco': ["EffTable2012/scaleFactor-Run2012ABC-SCToElectron.txt"],
        'HLT': ["EffTable2012/efficiency-Run2012ABC-WP80ToHLTEle.txt"]
        }
    pars.lumiPerEpoch = [pars.integratedLumi]

    pars.cuts += '&&(abs(JetPFCor_dphiMET[0])>0.8)&&(W_electron_pt>35)'
    return pars

def customizeMuons(pars):
    pars.DataFile = pars.DataDirectory + 'RD_WmunuJets_DataAll_GoldenJSON_19p3invfb.root'
    pars.integratedLumi = 19300

    pars.doEffCorrections = True
    pars.effToDo = ['lepton']
    pars.leptonEffFiles = {
        'id': ["EffTable2012/scaleFactor-Run2012ABC-RecoToIso.txt"],
        'HLT': ["EffTable2012/efficiency-Run2012ABC-IsoToIsoMuHLT.txt"]
        }
    pars.lumiPerEpoch = [pars.integratedLumi]

    pars.cuts += '&&(abs(JetPFCor_dphiMET[0])>0.4)&&(abs(W_muon_eta)<2.1)'
    
    return pars
