NgenHWW = {160 : (109992,9.080,0.133),
           170 : (109989,7.729,0.141),
           180 : (109325,6.739,0.137),
           190 : (109986,5.896,0.115),
           200 : (109315,5.249,0.108),
           250 : (109992,3.312,0.103),
           300 : (109990,2.422,0.101),
           350 : (109313,2.306,0.099),
           400 : (107879,2.032,0.0852),
           450 : (107158,1.359,0.0808),
           500 : (107169,0.849,0.0799),
           550 : (107870,0.528,0.0806),
           600 : (108561,0.327,0.0818)
           }

NgenVBFHWW = {160 : (169351),
              170 : (161768),
              180 : (219267),
              190 : (213014),
              200 : (217423),
              250 : (218679),
              300 : (217427),
              350 : (213673),
              400 : (204894),
              450 : (164553),
              500 : (218520),
              550 : (215938),
              600 : (214510)
              }

NgenHWWTauNu = {160 : (109993),
                170 : (102459),
                180 : (105475),
                190 : (109985),
                200 : (93789),
                250 : (105936),
                300 : (102570),
                350 : (105270),
                400 : (106818),
                450 : (104259),
                500 : (104268),
                550 : (106658),
                600 : (109970)
                }

modes = ['HWW', 'VBFHWW', 'HWWTauNu']
Ngens = [NgenHWW, NgenVBFHWW, NgenHWWTauNu]

Ngen = dict(zip(modes,Ngens))

from ROOT import RooWjjFitterUtils

fitUtils = None

def NgenHiggs(mH, mode):
    if type(Ngen[mode][mH]) == type(2):
        halfVal = Ngen[mode][mH]/2
    else:
        halfVal = Ngen[mode][mH][0]/2
    return (halfVal, Ngen[mode][mH])

def makeHiggsHist(mH, pars, mode):
    global fitUtils

    if pars.includeMuons and pars.includeElectrons:
        modeString = ''
    elif pars.includeMuons:
        modeString = 'Muon'
    elif pars.includeElectrons:
        modeString = 'Electron'
    else:
        modeString = ''

    if not fitUtils:
        fitUtils = RooWjjFitterUtils(pars)

    hist = fitUtils.newEmptyHist('%s%i_%s_shape' % (mode, mH,modeString))

    if pars.includeMuons:
        thehist = fitUtils.File2Hist(pars.MCDirectory + \
                                         'mu_%sMH%i_CMSSW428.root' % (mode, mH),
                                     '%s%i_mu' % (mode, mH), False, 1, False)
        hist.Add(thehist)
    if pars.includeElectrons:
        thehist = fitUtils.File2Hist(pars.MCDirectory + \
                                         'el_%sMH%i_CMSSW428.root' % (mode, mH),
                                     '%s%i_mu' % (mode, mH), True, 1, False)
        hist.Add(thehist)

    return hist

def GenHiggsHists(pars, mH):
    hists = []

    for mode in modes:
        tmpHist = makeHiggsHist(mH, pars, mode)
        if type(Ngen[mode][mH]) == type(2):
            tmpHist.Scale(1/float(Ngen[mode][mH]/2), 'width')
        else:
            tmpHist.Scale(1/float(Ngen[mode][mH][0]/2), 'width')            
        hists.append(tmpHist)
        
    return dict(zip(modes, hists))
