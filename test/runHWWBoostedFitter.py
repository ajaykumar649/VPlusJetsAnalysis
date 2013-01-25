from optparse import OptionParser

parser = OptionParser()
parser.add_option('-b', action='store_true', dest='noX', default=False,
                  help='no X11 windows')
parser.add_option('-m', '--mode', default="HWWBoostedConfig", dest='modeConfig',
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

(opts, args) = parser.parse_args()

import pyroot_logon

#import HWW2DConfig
config = __import__(opts.modeConfig)
import RooWjj2DFitter

from ROOT import TCanvas, RooFit, RooLinkedListIter, TMath, RooRandom, TFile, \
    RooDataHist, RooMsgService, TStopwatch, RooAbsPdf, TBox, kBlack, kRed, \
    kBlue, kOrange, kDashed, RooAbsCollection
import pulls

timer = TStopwatch()
timer.Start()

RooAbsPdf.defaultIntegratorConfig().setEpsRel(1e-9) ;
RooAbsPdf.defaultIntegratorConfig().setEpsAbs(1e-9) ;
if not opts.debug:
    RooMsgService.instance().setGlobalKillBelow(RooFit.WARNING)

if hasattr(opts, "seed") and (opts.seed >= 0):
    print "random seed:", opts.seed
    RooRandom.randomGenerator().SetSeed(opts.seed)

mjjArgs = []
sidebandArgs = []
mWWArgs = []
for arg in args:
    if arg[-7:] == '_mj.txt':
        mjjArgs.append(arg)
    elif arg[-8:] == '_mWW.txt':
        mWWArgs.append(arg)
    elif arg[-13:] == '_sideband.txt':
        sidebandArgs.append(arg)

print mjjArgs
pars = config.theConfig(Nj = opts.Nj, mH = opts.mH, 
                        isElectron = opts.isElectron, initFile = mjjArgs,
                        includeSignal = opts.includeSignal)

fitter = RooWjj2DFitter.Wjj2DFitter(pars)
fitter.ws.SetName("w_mjj")

totalPdf = fitter.makeFitter()

if opts.ws:
    fitter.loadWorkspaceFromFile(opts.ws, getFloatPars = False,
                                 wsname = 'w_mjj')

#fitter.loadData()
fitter.readParametersFromFile()
fitter.expectedFromPars()
# fitter.WpJExpected = 25660.8
# fitter.topExpected = 3357.8
# fitter.dibosonExpected = 670.5
# fitter.HWWExpected = 225.1
fitter.resetYields()
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

fitter.setMultijetYield()
data.Print()
startpars.IsA().Destructor(startpars)

print 'Time elapsed: %.1f sec' % timer.RealTime()
print 'CPU time used: %.1f sec' % timer.CpuTime()
print 'starting fitting routine'
timer.Continue()
fitter.ws.var('diboson_nrm').setConstant()
fitter.ws.var('top_nrm').setConstant()
fitter.ws.var('r_signal').setVal(1.0)
fitter.ws.var('r_signal').setError(0.04)
fr = None
fr = fitter.fit()

vName1 = pars.varNames[pars.var[0]]
plot1 = fitter.stackedPlot(vName1)
leg1 = RooWjj2DFitter.Wjj2DFitter.legend4Plot(plot1)

c1 = TCanvas('c1', vName1 + ' plot')
plot1.addObject(leg1)
plot1.Draw()
c1.Update()

ndf = 0

if fr:
    floatVars = [ fr.floatParsFinal().at(i).GetName() \
                      for i in range(0, fr.floatParsFinal().getSize()) ]
    fitter.ws.defineSet('floatingParams', ','.join(floatVars))
    fitter.ws.saveSnapshot("fitPars", ','.join(floatVars))
    ndf = fr.floatParsFinal().getSize() - \
        fitter.ws.set('constraintSet').getSize()
    # fr.Print('v')

print '%i free parameters in the fit' % ndf

firstCurve1 = plot1.getObject(1)
# firstCurve1.Print()

(chi2_1, ndf_1) = pulls.computeChi2(plot1.getHist('theData'), firstCurve1)
pull1 = pulls.createPull(plot1.getHist('theData'), firstCurve1)
    

chi2 = chi2_1
ndf = ndf_1-ndf

cp1 = TCanvas("cp1", vName1 + ' pull')
pull1.Draw('ap')
pull1.SetName(vName1 + "_pull")
cp1.SetGridy()
cp1.Update()
pull1.GetXaxis().SetLimits(pars.varRanges[pars.var[0]][1], 
                           pars.varRanges[pars.var[0]][2])
pull1.GetXaxis().SetTitle(fitter.ws.var(vName1).getTitle(True).Data())
pull1.GetYaxis().SetTitle("pull (#sigma)")

blinder = plot1.findObject('TBox')
blinder2 = None
if blinder:
    blinder2 = TBox(pars.exclude[pars.var[0]][0], pull1.GetYaxis().GetXmin(),
                    pars.exclude[pars.var[0]][1], pull1.GetYaxis().GetXmax())
    blinder2.SetFillColor(kBlack)
    blinder2.SetFillStyle(1001)

if blinder2:
    #blinder2.Print()
    blinder2.Draw()

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

mode = 'muon'
if opts.isElectron:
    mode = 'electron'

WpJPdf = fitter.ws.pdf('WpJ')
WpJInt = WpJPdf.createIntegral(fitter.ws.set('obsSet'), 
                               fitter.ws.set('obsSet'), 
                               'highSideband')
WpJFullInt = WpJPdf.createIntegral(fitter.ws.set('obsSet'), 
                                   fitter.ws.set('obsSet'))

print "WpJ","sideband integral",WpJInt.getVal(),
print "full integral",WpJFullInt.getVal(),
print "ratio",WpJInt.getVal()/WpJFullInt.getVal()

print 'sideband yield', WpJInt.getVal()/WpJFullInt.getVal()*fitter.ws.function('f_WpJ_norm').getVal()


print 'Time elapsed: %.1f sec' % timer.RealTime()
print 'CPU time used: %.1f sec' % timer.CpuTime()
print 'starting sideband fit routine'
timer.Continue()

import HWWBoostedConfig_sideband
print sidebandArgs
pars_sideband = HWWBoostedConfig_sideband.theConfig(opts.Nj, opts.mH, 
                                               opts.isElectron, sidebandArgs,
                                               False)
pars_sideband.yieldConstraints['WpJ'] = fitter.ws.var('WpJ_nrm').getError()
fitter_sideband = RooWjj2DFitter.Wjj2DFitter(pars_sideband)
fitter_sideband.ws.SetName("w_sideband")
totalPdf_sideband = fitter_sideband.makeFitter()
fitter_sideband.readParametersFromFile()
WpJ_sideband = fitter_sideband.ws.var('n_WpJ')
WpJ_sideband.setVal(WpJ_sideband.getVal()*fitter.ws.var('WpJ_nrm').getVal())
#fitter_sideband.ws.Print()
fitter_sideband.expectedFromPars()
# fitter_sideband.resetYields()

# sidebandCut = '((%s<%.0f)||(%s>%.0f))' % \
#     (pars.var[0], pars.exclude[pars.var[0]][0],
#      pars.var[0], pars.exclude[pars.var[0]][1])

# #high sideband only
# sidebandCut = '(%s>%.0f)' % \
#      (pars.var[0], pars.exclude[pars.var[0]][1])

#low sideband only
sidebandCut = '(%s<%.0f)' % \
     (vName1, pars.exclude[pars.var[0]][0])

fitter_sideband.loadDataFromWorkspace(fitter.ws, sidebandCut)

fr_sideband = None
fr_sideband = fitter_sideband.fit()

plot_sideband = fitter_sideband.stackedPlot(pars_sideband.var[0])
plot_sideband.SetName('%s_sideband_%s_plot_stacked' % \
                          (vName1, pars_sideband.var[0]))
leg_sideband = RooWjj2DFitter.Wjj2DFitter.legend4Plot(plot_sideband)

c_sideband = \
    TCanvas('c_sideband', 
            vName1 + ' sideband ' + pars_sideband.var[0] + ' plot')
plot_sideband.addObject(leg_sideband)
plot_sideband.Draw()
c_sideband.Update()

(chi2_sideband, ndf_sideband) = \
    pulls.computeChi2(plot_sideband.getHist('theData'), 
                      plot_sideband.getObject(1))
ndf_sideband -= (fr_sideband.floatParsFinal().getSize() - \
                     fitter_sideband.ws.set('constraintSet').getSize())
pull_sideband = pulls.createPull(plot_sideband.getHist('theData'), 
                                 plot_sideband.getObject(1))
cp_sideband = TCanvas('cp_sideband', vName1 + ' sideband pull')
pull_sideband.SetName('sideband_pull')
pull_sideband.Draw('ap')
cp_sideband.SetGridy()
cp_sideband.Update()
pull_sideband.GetXaxis().SetLimits(
    pars_sideband.varRanges[pars_sideband.var[0]][1], 
    pars_sideband.varRanges[pars_sideband.var[0]][2]
    )
pull_sideband.GetXaxis().SetTitle(
    fitter_sideband.ws.var(pars_sideband.var[0]).getTitle(True).Data()
    )
pull_sideband.GetYaxis().SetTitle("pull")
cp_sideband.Update()
WpJParams = fitter_sideband.ws.pdf('WpJ').getParameters(
    fitter_sideband.ws.set('obsSet')
    )


print 'Time elapsed: %.1f sec' % timer.RealTime()
print 'CPU time used: %.1f sec' % timer.CpuTime()
print 'starting signal box routine'
timer.Continue()

import HWWBoostedConfig_mWW
print mWWArgs
pars_mWW = HWWBoostedConfig_mWW.theConfig(opts.Nj, opts.mH, 
                                     opts.isElectron, mWWArgs,
                                     False)
pars_mWW.yieldConstraints['WpJ'] = fitter.ws.var('WpJ_nrm').getError()
fitter_mWW = RooWjj2DFitter.Wjj2DFitter(pars_mWW)
fitter_mWW.ws.SetName("w_mWW")
mc_side = fitter_mWW.utils.analyticPdf(fitter_mWW.ws, pars_mWW.var[0], 
                                       pars_sideband.WpJSidebandModels[0],
                                       'WpJ_%s_side' % pars_mWW.var[0],
                                       'WpJ_%s_side' % pars_mWW.var[0])
mc_sig = fitter_mWW.utils.analyticPdf(fitter_mWW.ws, pars_mWW.var[0], 
                                       pars_mWW.WpJSidebandModels[0],
                                       'WpJ_%s_sig' % pars_mWW.var[0],
                                       'WpJ_%s_sig' % pars_mWW.var[0])
#fitter_mWW.ws.factory('WpJ_%s_alpha[1.]' % pars_mWW.var[0])
totalPdf_mWW = fitter_mWW.makeFitter()
fitter_mWW.readParametersFromFile()
RooAbsCollection.__assign__(fitter_mWW.ws.allVars(), WpJParams)
WpJ_mWW = fitter_mWW.ws.var('n_WpJ')
WpJ_mWW.setVal(WpJ_mWW.getVal()*fitter.ws.var('WpJ_nrm').getVal())
fitter_mWW.expectedFromPars()

mWWCut = '((%s<%.0f)&&(%s<%.0f))' % \
    (vName1, pars.exclude[pars.var[0]][0],
     vName1, pars.exclude[pars.var[0]][1])
fitter_mWW.loadDataFromWorkspace(fitter.ws, mWWCut)
fitter_mWW.resetYields()

mc_closure = fitter_mWW.ws.factory(
    "RooEffProd::mc_closure(%s, WpJ_%s_alpha)" % (mc_side.GetName(), 
                                                 pars_mWW.var[0])
    )

fitter_mWW.ws.Print()

pdfPlot = fitter_mWW.ws.var(pars_mWW.var[0]).frame()
pdfPlot.SetName('WpJSigAndSideband')
mc_side.plotOn(pdfPlot, RooFit.LineColor(kBlue))
mc_sig.plotOn(pdfPlot, RooFit.LineColor(kRed))
mc_closure.plotOn(pdfPlot, RooFit.LineColor(kOrange+1),
                  RooFit.LineStyle(kDashed))
cpdf = TCanvas('cpdf', 'MC signal and sideband for W+jets')
pdfPlot.Draw()
pdfPlot.GetYaxis().SetTitle('normalized units')
cpdf.Update()

alphaPlot = fitter_mWW.ws.var(pars_mWW.var[0]).frame()
alphaPlot.SetName('WpJAlphaFunction')
fitter_mWW.ws.function('WpJ_%s_alpha' % pars_mWW.var[0]).plotOn(
    alphaPlot, RooFit.LineColor(kBlack) )
calpha = TCanvas('calpha', 'alpha function')
alphaPlot.Draw()
alphaPlot.GetYaxis().SetTitle('MC signal/sideband ratio')

wpjPlot = fitter_mWW.ws.var(pars_mWW.var[0]).frame()
fitter_mWW.ws.pdf('WpJ').plotOn(wpjPlot, RooFit.LineColor(kRed))
fitter_mWW.ws.pdf('WpJ_%s_pdf' % pars_mWW.var[0]).plotOn(
    wpjPlot, RooFit.LineColor(kBlue)
    )
cwpj = TCanvas('cwpj', 'W+jets shape')
wpjPlot.Draw()
wpjPlot.GetYaxis().SetTitle('normalized units')
cwpj.Update()

plot_mWW = fitter_mWW.stackedPlot(pars_mWW.var[0])
plot_mWW.SetName('%s_plot_stacked' % (pars_mWW.var[0]))
leg_mWW = RooWjj2DFitter.Wjj2DFitter.legend4Plot(plot_mWW)

c_mWW = TCanvas('c_mWW', pars_mWW.var[0] + ' plot')
plot_mWW.addObject(leg_mWW)
plot_mWW.Draw()
if blinder:
    plot_mWW.setInvisible('theData', True)
c_mWW.Update()

(chi2_mWW, ndf_mWW) = pulls.computeChi2(plot_mWW.getHist('theData'), 
                                        plot_mWW.getObject(1))
pull_mWW = pulls.createPull(plot_mWW.getHist('theData'), 
                            plot_mWW.getObject(1))
cp_mWW = TCanvas('cp_mWW', 'mWW pull')
pull_mWW.SetName('mWW_pull')
pull_mWW.Draw('ap')
cp_mWW.SetGridy()
cp_mWW.Update()
pull_mWW.GetXaxis().SetLimits(
    pars_mWW.varRanges[pars_mWW.var[0]][1], 
    pars_mWW.varRanges[pars_mWW.var[0]][2]
    )
pull_mWW.GetXaxis().SetTitle(
    fitter_mWW.ws.var(pars_mWW.var[0]).getTitle(True).Data()
    )
pull_mWW.GetYaxis().SetTitle("pull")
cp_mWW.Update()

output = TFile("HWW%ilnujj_%s_%ijets_Boosted_output.root" % (opts.mH,mode, opts.Nj),
               "recreate")

fr.SetName('fit_result')
fr.Write()
fr_sideband.SetName('fit_result_sideband')
fr_sideband.Write()
plot1.Write()
pull1.Write()
plot_sideband.Write()
pdfPlot.Write()
alphaPlot.Write()
plot_mWW.Write()
pull_mWW.Write()
fitter.ws.Write()
# fitter_sideband.ws.Write()
# fitter_mWW.ws.Write()

#fitter.ws.Print()
output.Close()

print 'Time elapsed: %.1f sec' % timer.RealTime()
print 'CPU time used: %.1f sec' % timer.CpuTime()

print '***',pars.var[0], 'fit ***'
print '%i degrees of freedom' % ndf
print 'chi2: %.2f / %i = %.2f' % (chi2_1, ndf, (chi2/ndf))
print 'chi2 probability: %.4g' % (TMath.Prob(chi2, ndf))

print '*** sideband fit ***'
print '%i degrees of freedom' % ndf_sideband
print 'chi2: %.2f / %i = %.2f' % (chi2_sideband, ndf_sideband, 
                                  (chi2_sideband/ndf_sideband))
print 'chi2 probability: %.4g' % (TMath.Prob(chi2_sideband, ndf_sideband))

print '*** mWW fit ***'
print '%i degrees of freedom' % ndf_mWW
print 'chi2: %.2f / %i = %.2f' % (chi2_mWW, ndf_mWW, 
                                  (chi2_mWW/ndf_mWW))
print 'chi2 probability: %.4g' % (TMath.Prob(chi2_mWW, ndf_mWW))
