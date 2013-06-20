from optparse import OptionParser

parser = OptionParser()
parser.add_option('-b', action='store_true', dest='noX', default=False,
                  help='no X11 windows')
parser.add_option('-m', '--mode', default="HWW1D2FitsConfig", 
                  dest='modeConfig',
                  help='which config to select look at HWW2DConfig.py for ' +\
                      'an example.  Use the file name minus the .py extension.'
                  )
parser.add_option('-H', '--mH', dest='mH', default=350, type='int',
                  help='Higgs Mass Point')
parser.add_option('-j', '--Njets', dest='Nj', default=2, type='int',
                  help='Number of jets.')
parser.add_option('--electrons', dest='isElectron', action='store_true',
                  default=False, help='do electrons instead of muons')
parser.add_option('--nosig', dest='includeSignal', action='store_false',
                  default=True, help='include signal shape in fit')
parser.add_option('--toy', dest='toy', action='store_true',
                  help='use pseudo-data instead of data file')
parser.add_option('--toyOut', dest='toyOut', help='filename for toy output')
parser.add_option('--seed', dest='seed', type='int', help='random seed')
parser.add_option('--ws', dest='ws', 
                  help='filename that contains workspace to be used cloned ' +\
                      'for use')
parser.add_option('--debug', dest='debug', action='store_true', default=False,
                  help='turn on extra debugging information')
parser.add_option('--limit', dest='doLimit', type='int',
                  default=0,
                  help='calculate expected limits using profile likelihood, number of toys to use.')
parser.add_option('--obsLimit', dest='obsLimit', action='store_true',
                  default=False,
                  help='calculate observed limit too')

(opts, args) = parser.parse_args()

import pyroot_logon

#import HWW2DConfig
config = __import__('WWAConfig')
import RooWjj2DFitter

from ROOT import TCanvas, RooFit, RooLinkedListIter, TMath, RooRandom, TFile, \
    RooDataHist, RooMsgService, TStopwatch, RooAbsPdf, TBox, kBlack, kRed, \
    kBlue, kOrange, kDashed, RooAbsCollection, RooArgSet, RooStats, Double, \
    RooAbsReal, RooAbsData, TH1F
import pulls

timer = TStopwatch()
timer.Start()

#RooAbsPdf.defaultIntegratorConfig().setEpsRel(1e-9)
#RooAbsPdf.defaultIntegratorConfig().setEpsAbs(1e-9)
if not opts.debug:
    RooMsgService.instance().setGlobalKillBelow(RooFit.WARNING)

if hasattr(opts, "seed") and (opts.seed >= 0):
    print "random seed:", opts.seed
    RooRandom.randomGenerator().SetSeed(opts.seed)

print args
pars = config.theConfig(Nj = opts.Nj, mH = opts.mH, 
                        isElectron = opts.isElectron, initFile = args,
                        includeSignal = False)

fitter = RooWjj2DFitter.Wjj2DFitter(pars)
fitter.ws.SetName("w_mjj")

totalPdf = fitter.makeFitter()

if opts.ws:
    fitter.loadWorkspaceFromFile(opts.ws, getFloatPars = False,
                                 wsname = 'w_mjj')

fitter.readParametersFromFile()
fitter.expectedFromPars()
fitter.resetYields()

startpars = totalPdf.getParameters(fitter.ws.set('obsSet'))
fitter.ws.defineSet("params", startpars)
fitter.ws.saveSnapshot("initPars", startpars)
startpars.IsA().Destructor(startpars)

print 'Time elapsed: %.1f sec' % timer.RealTime()
print 'CPU time used: %.1f sec' % timer.CpuTime()
print 'starting fitting routine'
timer.Continue()
fitter.ws.var('r_signal').setVal(1.0)
fitter.ws.var('r_signal').setError(0.04)

fr = None
fr = fitter.fit()

plot1 = fitter.stackedPlot(pars.var[0])
leg1 = RooWjj2DFitter.Wjj2DFitter.legend4Plot(plot1)

c1 = TCanvas('c1', pars.var[0] + ' plot')
plot1.addObject(leg1)
plot1.Draw()
c1.Update()

firstCurve1 = plot1.getObject(1)
pull1 = pulls.createPull(plot1.getHist('theData'), firstCurve1)
    
cp1 = TCanvas("cp1", pars.var[0] + ' pull')
pull1.Draw('ap')
pull1.SetName(pars.var[0] + "_pull")
cp1.SetGridy()
cp1.Update()
pull1.GetXaxis().SetLimits(pars.varRanges[pars.var[0]][1], 
                           pars.varRanges[pars.var[0]][2])
pull1.GetXaxis().SetTitle(fitter.ws.var(pars.var[0]).getTitle(True).Data())
pull1.GetYaxis().SetTitle("pull (#sigma)")

cp1.Update()

mode = 'muon'
if opts.isElectron:
    mode = 'electron'

fr.Print('v')

print 'Time elapsed: %.1f sec' % timer.RealTime()
print 'CPU time used: %.1f sec' % timer.CpuTime()
