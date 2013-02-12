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
parser.add_option('--bn', dest='bn', default='ShapeParameters',
                  help='basis name for the output files.')
parser.add_option('--comp', dest='component', default='diboson',
                  help='name of component to fit')
parser.add_option('--electrons', dest='isElectron', action='store_true',
                  default=False, help='do electrons instead of muons')
parser.add_option('--makeFree', dest='makeConstant', action='store_false',
                  default=True, help='make parameters free in output')
parser.add_option('--sideband', dest='sb', type='int',
                  default=0, help='use sideband model instead')
parser.add_option('--signal', dest='sig', action='store_true',
                  default=False, help='use signal model instead')
parser.add_option('-i', '--interference', dest='interference', default=0, 
                  type='int', help='ggH interference to use.  '+\
                      '(0): none [default]  (1): nominal'+\
                      '  (2): +1 sigma  (3): -1 sigma  ')

(opts, args) = parser.parse_args()


import pyroot_logon

#import HWW2DConfig
config = __import__(opts.modeConfig)
#import VBF2DConfig
import RooWjj2DFitter
import HWWSignalShapes
#from RooWjj2DFitterUtils import Wjj2DFitterUtils

from ROOT import RooFit, TCanvas, TLegend, RooArgSet, TFile, RooAbsReal, RooAbsData, \
    RooHist, TMath, kRed, kDashed, kOrange, RooMsgService

import pulls

RooMsgService.instance().setGlobalKillBelow(RooFit.WARNING)

pars = config.theConfig(Nj = opts.Nj, mH = opts.mH, 
                        isElectron = opts.isElectron, initFile = args)

files = getattr(pars, '%sFiles' % opts.component)
models = getattr(pars, '%sModels' % opts.component)
if opts.sb or opts.sig:
    models = getattr(pars, '%sSidebandModels' % opts.component)

# print 'eff lumi WW: %.1f invpb' % (pars.dibosonFiles[0][1]/pars.dibosonFiles[0][2])
# print 'eff lumi WZ: %.1f invpb' % (pars.dibosonFiles[1][1]/pars.dibosonFiles[1][2])

#pars.DataFile = files[0][0]
fitter = RooWjj2DFitter.Wjj2DFitter(pars)

#fitter.makeFitter()
#data = fitter.loadData(True)
#data.Print()
data = None
sumNExp = 0.
weighted = True
cutOverride = None
## if opts.component == 'QCD':
##     weighted = False
##     cutOverride = pars.QCDcuts
cpw = False
if (opts.component == "ggH") or (opts.component == 'qqH'):
    cpw = True
if (opts.component == 'qqH') and (opts.mH == 170):
    cpw = False
#print 'interference option:',opts.interference
for (ifile, (filename, ngen, xsec)) in enumerate(files):
    if opts.component == 'QCD':
        tmpData = fitter.utils.File2Dataset(filename, 'data%i' % ifile, fitter.ws,
                                            weighted = False, CPweight = cpw,
                                            cutOverride = cutOverride,
                                            interference = opts.interference, isQCD = True)
    else:
        tmpData = fitter.utils.File2Dataset(filename, 'data%i' % ifile, fitter.ws,
                                            weighted = weighted, CPweight = cpw,
                                            cutOverride = cutOverride,
                                            interference = opts.interference)
    
    tmpData.Print()
    expectedYield = xsec*pars.integratedLumi*tmpData.sumEntries()/ngen
    print filename,'A x eff: %.3g' % (tmpData.sumEntries()/ngen)
    print filename,'expected yield: %.1f' % expectedYield
    sumNExp += expectedYield
    if not data:
        scale = 1.0
        data = fitter.utils.reduceDataset(tmpData, scale)
        refEffLumi = ngen/xsec
    else:
        scale = refEffLumi/(ngen/xsec)
        reducedData = fitter.utils.reduceDataset(tmpData, scale)
        data.append(reducedData)

print opts.component,'total expected yield: %.1f' % sumNExp
hist2d = None
try:
    obs = [ pars.varNames[x] for x in pars.var ]
except AttributeError:
    obs = pars.var

if (len(pars.var) > 1):
    hist2d = data.createHistogram(fitter.ws.var(obs[0]),
                                  fitter.ws.var(obs[1]), '',
                                  'hist2d')
    print 'correlation between the first two observables:', hist2d.GetCorrelationFactor()

if opts.interference in [1,2,3]:
    fitter.makeFitter()
    # fitter.ws.Print()
    if opts.interference == 1:
        pdfName = '%s' % opts.component
    elif opts.interference == 2:
        pdfName = '%s_interf_%sUp' % (opts.component, opts.component)
    elif opts.interference == 3:
        pdfName = '%s_interf_%sDown' % (opts.component, opts.component)
    print pdfName
    sigPdf = fitter.ws.pdf(pdfName)
    if sigPdf:
        sigPdf.Print()
    else:
        print 'failed to fined pdf',pdfName
else:
    sigPdf = fitter.makeComponentPdf(opts.component, files, models)

extraTag = ''
if opts.interference == 2:
    extraTag = '_interf_%sUp' % opts.component
if opts.interference == 3:
    extraTag = '_interf_%sDown' % opts.component

if fitter.ws.var('mean_%s_fit_mlvjj_core%s' % (opts.component,extraTag)):
    fitter.ws.var('mean_%s_fit_mlvjj_core%s' % \
                      (opts.component,extraTag)).setVal(opts.mH)
if fitter.ws.var('mean_%s_fit_mlvjj_tail%s' % (opts.component,extraTag)):
    fitter.ws.var('mean_%s_fit_mlvjj_tail%s' % \
                      (opts.component,extraTag)).setVal(opts.mH)
if fitter.ws.var('sigma_%s_fit_mlvjj_tail%s' % (opts.component,extraTag)):
    fitter.ws.var('sigma_%s_fit_mlvjj_tail%s' % \
                      (opts.component,extraTag)).setVal(opts.mH*0.25)
if fitter.ws.var('sigma_%s_fit_mlvjj_core%s' % (opts.component,extraTag)):
    fitter.ws.var('sigma_%s_fit_mlvjj_core%s' % \
                      (opts.component,extraTag)).setVal(opts.mH*0.1)

params = sigPdf.getParameters(data)
parCopy = params.snapshot()
for filename in args:
    parCopy.readFromFile(filename)
    params.assignValueOnly(parCopy)

parCopy.IsA().Destructor(parCopy)
    
if fitter.ws.var('npow_ggH_Mass2j_PFCor'):
    # fitter.ws.var('npow_ggH_Mass2j_PFCor').setConstant(False)
    # fitter.ws.var('alpha_ggH_Mass2j_PFCor').setVal(1.0)
    # fitter.ws.var('alpha_ggH_Mass2j_PFCor').setConstant(True)
    pass

if fitter.ws.var('npow_diboson_Mass2j_PFCor'):
    fitter.ws.var('npow_diboson_Mass2j_PFCor').setConstant(True)
    fitter.ws.var('npow_diboson_Mass2j_PFCor').setError(0.5)

if fitter.ws.var('npow_WpJ_Mass2j_PFCor'):
    fitter.ws.var('npow_WpJ_Mass2j_PFCor').setConstant(False)

fitter.ws.Print()


fr = None
fr = sigPdf.fitTo(data, RooFit.Save(), 
                  RooFit.SumW2Error(False)
                  )


cans = []
plots = []
chi2s = []
ndfs = []

for (i,m) in enumerate(models):
    par = obs[i]
    c1 = TCanvas('c%i' % i, par)
    sigPlot = fitter.ws.var(par).frame(RooFit.Name('%s_Plot' % par))
    # dataHist = RooAbsData.createHistogram(data,'dataHist_%s' % par,
    #                                       fitter.ws.var(par),
    #                                       RooFit.Binning('%sBinning' % par))
    # theData = RooHist(dataHist, 1., 1, RooAbsData.SumW2, 1.0, True)
    # theData.SetName('theData')
    # theData.SetTitle('data')
    # sigPlot.addPlotable(theData, 'pe', False, True)
    data.plotOn(sigPlot, RooFit.Name('theData'),
                RooFit.DataError(RooAbsData.SumW2))
    sigPlot.getHist('theData').SetTitle('data')
    if fr:
        sigPdf.plotOn(sigPlot, 
                      RooFit.VisualizeError(fr, 1, True),
                      RooFit.FillColor(kOrange+1),
                      RooFit.FillStyle(3001))
    sigPdf.plotOn(sigPlot, RooFit.Name('fitCurve'))
    sigPdf.plotOn(sigPlot, RooFit.Name('fitTails'),
                  RooFit.Components('*tail'),
                  RooFit.LineColor(kRed),
                  RooFit.LineStyle(kDashed))

    # sigPlot.GetYaxis().SetTitle('Events / GeV')

    sigPlot.Draw()
    c1.Update()
    sigPlot.SetMinimum(1e-6)
    cans.append(c1)
    plots.append(sigPlot)
    (chi2_1, ndf_1) = pulls.computeChi2(sigPlot.getHist('theData'),
                                        sigPlot.getCurve('fitCurve'))
    chi2s.append(chi2_1)
    ndfs.append(ndf_1)

mode = 'muon'
if opts.isElectron:
    mode = 'electron'

lgnd = TLegend(0.65, 0.72, 0.92, 0.89, '', 'NDC')
lgnd.AddEntry('fitCurve', '%s fit pdf' % opts.component, 'l')
lgnd.AddEntry('theData','%s MC' % opts.component,'p')
lgnd.Draw('same')

if pars.btagSelection:
    if pars.boostedSelection:
        c1.SaveAs("DibosonBoostedBtaglnuJ_%s_%s_%ijets.png" % (opts.component, mode, opts.Nj))
    else:
        c1.SaveAs("DibosonBtaglnujj_%s_%s_%ijets.png" % (opts.component, mode, opts.Nj))
else:
    if pars.boostedSelection:
        c1.SaveAs("DibosonBoostedlnuJ_%s_%s_%ijets.png" % (opts.component, mode, opts.Nj))
    else:
        c1.SaveAs("Dibosonlnujj_%s_%s_%ijets.png" % (opts.component, mode, opts.Nj))
    

ndf = 0
# print chi2s
# print ndfs

if fr:
    fr.Print('v')
    finalPars = params.snapshot()

    sigFile = TFile('%s.root' % opts.bn, 'recreate')
    fr.Write('fr')
    for plot in plots:
        plot.Write()
    fitter.ws.Write()
    if hist2d:
        hist2d.Write()

    sigFile.Close()

    if opts.makeConstant:
        finalPars.setAttribAll('Constant', True)
    finalPars.writeToFile("%s.txt" % opts.bn)

    if opts.component != 'multijet':
        paramsFile = open('%s.txt' % opts.bn)
        lines = paramsFile.readlines()
        paramsFile.close()
        outfile = open('%s.txt' % opts.bn, 'w')
        for line in lines:
            if opts.sb or opts.sig:
                tag = '_side ' if opts.sb else '_sig '
                if opts.sb == 2:
                    tag = '_low '
                elif opts.sb == 3:
                    tag = '_high '
                words = line.split()
                outfile.write(words[0] + tag + ' '.join(words[1:]) + '\n')
            else:
                outfile.write(line)
        compName = opts.component
        if opts.interference == 2:
            compName += '_interf_%sUp' % compName
        elif opts.interference == 3:
            compName += '_interf_%sDown' % compName
        if opts.sb:
            compName = 'dummy'
        outfile.write('n_%s = %.1f +/- %.1f C\n' % (compName, sumNExp, 
                                                    TMath.Sqrt(sumNExp))
                      )
        outfile.close()

    ndf = fr.floatParsFinal().getSize()
    finalPars.IsA().Destructor(finalPars)

params.IsA().Destructor(params)

print '%i free parameters in the fit' % ndf
chi2 = 0
print 'chi2: (',
for c in chi2s:
    chi2 += c
    if c != chi2s[-1]:
        print '%.2f +' % c,
    else:
        print '%.2f )' % c,
bins = 0
for b in ndfs:
    bins += b
ndf = bins-ndf

print '/%i = %.2f' % (ndf, (chi2/ndf))
print 'chi2 probability: %.4g' % (TMath.Prob(chi2, ndf))
