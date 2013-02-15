from optparse import OptionParser

parser = OptionParser()
parser.add_option('-b', action='store_true', dest='noX', default=False,
                  help='no X11 windows')
parser.add_option('-m', '--mode', default="HWW2DConfig", dest='modeConfig',
                  help='which config to select look at HWW2DConfig.py for ' +\
                      'an example.  Use the file name minus the .py extension.'
                  )
parser.add_option('-H', '--mH', dest='mH', default=350, type='int',
                  help='Higgs Mass Point')
parser.add_option('-j', '--Njets', dest='Nj', default=2, type='int',
                  help='Number of jets.')
parser.add_option('--comp', dest='component', default='diboson',
                  help='name of component to fit')
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
parser.add_option('--noNull', dest='nullFit', action='store_false',
                  default=True, help='do not perform the null hypothesis fit.')

(opts, args) = parser.parse_args()

import pyroot_logon

#import HWW2DConfig
config = __import__(opts.modeConfig)
import RooWjj2DFitter

from ROOT import TCanvas, RooFit, RooLinkedListIter, TMath, RooRandom, TFile, \
    RooDataHist, RooMsgService, TStopwatch, RooStats
import pulls

timer = TStopwatch()
timer.Start()

if not opts.debug:
    RooMsgService.instance().setGlobalKillBelow(RooFit.WARNING)

if hasattr(opts, "seed") and (opts.seed >= 0):
    print "random seed:", opts.seed
    RooRandom.randomGenerator().SetSeed(opts.seed)
pars = config.theConfig(Nj = opts.Nj, mH = opts.mH, 
                        isElectron = opts.isElectron, initFile = args,
                        includeSignal = opts.includeSignal)

fitter = RooWjj2DFitter.Wjj2DFitter(pars)
if opts.ws:
    fitter.loadWorkspaceFromFile(opts.ws, getFloatPars = False)
    
totalPdf = fitter.makeFitter()

#fitter.loadData()
fitter.readParametersFromFile()
fitter.expectedFromPars()
# fitter.WpJExpected = 25660.8
# fitter.topExpected = 3357.8
# fitter.dibosonExpected = 670.5
# fitter.HWWExpected = 225.1
# fitter.readParametersFromFile('WpJHWW350Parameters.txt')
# fitter.readParametersFromFile('topHWW350Parameters.txt')
# fitter.readParametersFromFile('dibosonHWW350Parameters.txt')
# fitter.readParametersFromFile('HWW350Parameters.txt')

startpars = totalPdf.getParameters(fitter.ws.set('obsSet'))
fitter.ws.defineSet("params", startpars)
fitter.ws.saveSnapshot("initPars", startpars)

if opts.toy:
    #generate toy dataset
    print 'Generated parameters'
    fitter.ws.set('params').Print('v')
    fitter.ws.saveSnapshot("genPars", startpars)

    data = totalPdf.generate(fitter.ws.set('obsSet'), RooFit.Name('data_obs'),
                             RooFit.Extended())
    if fitter.pars.binData:
        data = RooDataHist('data_obs', 'data_obs', fitter.ws.set('obsSet'),
                           data)
        data.Print('v')
    getattr(fitter.ws, 'import')(data)
else:    
    data = fitter.loadData()

#fitter.setMultijetYield()
data.Print()
fitter.resetYields()
startpars.IsA().Destructor(startpars)

print 'Time elapsed: %.1f sec' % timer.RealTime()
print 'CPU time used: %.1f sec' % timer.CpuTime()
print 'starting fitting routine'
timer.Continue()
#fitter.ws.var('top_nrm').setConstant()
fitter.ws.var('r_signal').setVal(1.0)
fitter.ws.var('r_signal').setError(0.04)
fr = None
fr = fitter.fit()
fr.SetName('fitResult_withSig')

plot1 = fitter.stackedPlot(pars.var[0])
leg1 = RooWjj2DFitter.Wjj2DFitter.legend4Plot(plot1)
plot1.addObject(leg1)

c1 = TCanvas('c1', fitter.ws.var(pars.var[0]).GetTitle() + ' plot')
plot1.Draw()
c1.Update()

#Make the Data-NonDiboson subtracted plot
#print 'plot1 : '
#plot1.Print()
xvar = fitter.ws.var(pars.var[0])
xvar.setRange('plotRange', xvar.getMin(), xvar.getMax())
dibosonSubtractedFrame = xvar.frame()
dibosonSubtractedFrame.SetName("%s_subtracted" % pars.var[0])
dibosonResidual = plot1.residHist('theData', pars.backgrounds[1], False, True)#The first background is the diboson
dibosonResidual.SetTitle('subtracted data')
dibosonSubtractedFrame.addPlotable(dibosonResidual, 'p', False, True)
fitter.ws.pdf('diboson').plotOn(dibosonSubtractedFrame)
dibosonSubtractedFrame.getCurve().SetTitle(pars.dibosonPlotting['title'])
dibosonSubtractedLegend = RooWjj2DFitter.Wjj2DFitter.legend4Plot(dibosonSubtractedFrame)
c2 = TCanvas('c2', fitter.ws.var(pars.var[0]).GetTitle() + ' Subtracted')
dibosonSubtractedFrame.GetYaxis().SetTitle(plot1.GetYaxis().GetTitle())
dibosonSubtractedFrame.addObject(dibosonSubtractedLegend)
dibosonSubtractedFrame.Draw()
c2.Update()

ndf = 0

if fr:
    floatVars = [ fr.floatParsFinal().at(i).GetName() \
                      for i in range(0, fr.floatParsFinal().getSize()) ]
    fitter.ws.defineSet('floatingParams', ','.join(floatVars))
    fitter.ws.saveSnapshot("fitPars", ','.join(floatVars))
    ndf = fr.floatParsFinal().getSize() - \
        fitter.ws.set('constraintSet').getSize()
    fr.Print('v')

print '%i free parameters in the fit' % ndf

firstCurve1 = plot1.getObject(1)
# firstCurve1.Print()

(chi2_1, ndf_1) = pulls.computeChi2(plot1.getHist('theData'), firstCurve1)
pull1 = pulls.createPull(plot1.getHist('theData'), firstCurve1)

chi2 = chi2_1
ndf = ndf_1-ndf

cp1 = TCanvas("cp1", fitter.ws.var(pars.var[0]).GetTitle() + ' pull')
pull1.Draw('ap')
pull1.SetName(pars.var[0] + "_pull")
cp1.SetGridy()
cp1.Update()
pull1.GetXaxis().SetLimits(pars.varRanges[pars.var[0]][1], 
                           pars.varRanges[pars.var[0]][2])
pull1.GetXaxis().SetTitle(fitter.ws.var(pars.var[0]).getTitle(True).Data())
pull1.GetYaxis().SetTitle("pull (#sigma)")
cp1.Update()

if opts.toyOut:
    outFile = open(opts.toyOut, 'a', 1)
    fitter.ws.loadSnapshot("genPars")

    line = '%s %.6g %.6g %.6g '
    outFile.write('nll %f covQual %i edm %.4g ' % (fr.minNll(), fr.covQual(),
                                                   fr.edm())
                  )
    outFile.write('chi2Prob %f ' % (TMath.Prob(chi2, ndf)))
    for cycle in range(0, fr.numStatusHistory()):
        outFile.write('%s %i ' % (fr.statusLabelHistory(cycle),
                                  fr.statusCodeHistory(cycle))
                      )
    for i in range(0, fr.floatParsFinal().getSize()):
        outFile.write(line % (fr.floatParsFinal().at(i).GetName(),
                              fr.floatParsFinal().at(i).getVal(),
                              fr.floatParsFinal().at(i).getError(),
                              fitter.ws.var(fr.floatParsFinal().at(i).GetName()).getVal()
                              )
                      )
    outFile.write('\n')
    outFile.close()


if opts.nullFit:
    print 'doing fit under null hypothesis'

    fitter_null = RooWjj2DFitter.Wjj2DFitter(pars)
    fitter_null.loadHistogramsFromWorkspace(fitter.ws)
    totalPdf_null = fitter_null.makeFitter()
    fitter_null.readParametersFromFile()
    fitter_null.expectedFromPars()
    fitter_null.resetYields()

    fitter_null.loadDataFromWorkspace(fitter.ws)

    fitter_null.ws.var('diboson_nrm').setVal(0.)
    fitter_null.ws.var('diboson_nrm').setConstant()

    fr_null = fitter_null.fit()
    fr_null.SetName('fitResult_null')
    fr_null.Print('v')

mode = 'muon'
if opts.isElectron:
    mode = 'electron'

if pars.btagSelection:
    output = TFile("DibosonBtaglnujj_%s_%ijets_output.root" % (mode, opts.Nj),"recreate")
else:
    output = TFile("Dibosonlnujj_%s_%ijets_output.root" % (mode, opts.Nj),"recreate")
fr.Write()
if opts.nullFit:
    fr_null.Write()
plot1.Write()
dibosonSubtractedFrame.Write()
pull1.Write()
fitter.ws.SetName("w")
fitter.ws.Write()
#fitter.ws.Print()
output.Close()

if pars.btagSelection:
    c1.SaveAs("DibosonBtaglnujj_%s_%ijets_Stacked.png" % (mode, opts.Nj))
    c2.SaveAs("DibosonBtaglnujj_%s_%ijets_Subtracted.png" % (mode, opts.Nj))
    cp1.SaveAs("DibosonBtaglnujj_%s_%ijets_Pull.png" % (mode, opts.Nj))
else:
    c1.SaveAs("Dibosonlnujj_%s_%ijets_Stacked.png" % (mode, opts.Nj))
    c2.SaveAs("Dibosonlnujj_%s_%ijets_Subtracted.png" % (mode, opts.Nj))
    cp1.SaveAs("Dibosonlnujj_%s_%ijets_Pull.png" % (mode, opts.Nj))

print 'Time elapsed: %.1f sec' % timer.RealTime()
print 'CPU time used: %.1f sec' % timer.CpuTime()

print '%i degrees of freedom' % ndf
print 'chi2: %.2f / %i = %.2f' % (chi2_1, ndf, (chi2/ndf))
print 'chi2 probability: %.4g' % (TMath.Prob(chi2, ndf))

if opts.nullFit:
    likelihoodRatio = 2.*fr_null.minNll()-2.*fr.minNll()
    print '2*nll_null - 2*nll:', 2.*fr_null.minNll(), '-', 2.*fr.minNll(), '=',
    print likelihoodRatio

    pval = TMath.Prob(likelihoodRatio, 1)
    print 'p-value:', pval
    print 'Gaussian significance:', RooStats.PValueToSignificance(pval)
