class Wjj2DFitterPars:
    # filenames and paths
    MCDirectory = '/uscms_data/d2/andersj/Wjj/2012/data/RDTrees_PAT/'

    DataFile = '/uscms_data/d2/andersj/Wjj/2012/data/RDTrees_PAT/RD_WmunuJets_DataAll_GoldenJSON_3p5invfb.root'

    treeName = 'WJet'
    isElectron = False
    order = 0

    initialParametersFile = ''

    backgrounds = []
    signals = []
    yieldConstraints = {}

    # cuts
    cuts = '(ggdevt==2)&&(fit_status==0)&&(W_mt>30)&&(abs(W_muon_eta)<2.1)'
    QCDcuts = ''

    # variables
    var = ['Mass2j_PFCor', 'fit_mlvjj']
    varRanges = { 'Mass2j_PFCor': (12, 55., 150., 
                                   [55.,60.,65.,70.,75.,80.,85.,95.,105.,
                                    115.,125.,135.,150.]),
                  'fit_mlvjj': (20, 200., 400., [])
                  }
    exclude = {}
    blind = False
    # varNames = {'GroomedJet_CA8_mass_pr[0]': 'GroomedJet_CA8_mass_pr' }
  
    # lumi
    integratedLumi = 3500.

    # efficiency corrections
    doEffCorrections = False
    effToDo = ['lepton']
    leptonEffFiles = {
        'id': ["EffTable2012/scaleFactor-2012A-PromptReco-v1-PFMM-RecoToIso.txt"],
        'HLT': ["EffTable2012/efficiency-2012A-PromptReco-v1-PFMM-IsoToIsoMuHLT.txt"]
        }
    lumiPerEpoch = [integratedLumi]

import copy
def copyPars(pars):
    newPars = Wjj2DFitterPars()
    if type(pars) == type(newPars):
        newPars.__dict__ = copy.deepcopy(pars.__dict__)
    return newPars
