#! /usr/bin/env python

from optparse import OptionParser

wpjhelp = '''Parameterization for W+jets fit ---
-1 : histograms with floating fMU and fSU
 0 : erf * (power law with two params)
 1 : erf * (power law ith one param) * exponential
 2 : (fermi turn on) * (power law with two params)
 3 : (fermi turn on) * exponential
 4 : exponential * (power law with one param)
 5 : exponential * (power law with two params)
 6 : erf * (power law with one param)
everything else : same as zero
'''

parser = OptionParser()
parser.add_option('-b', action='store_true', dest='noX', default=False,
                  help='no X11 windows')
parser.add_option('-j', '--Njets', dest='Nj', default=2, type='int',
                  help='Number of jets.')
parser.add_option('--fSU', dest='e_FSU', default=-100.0, type='float',
                  help='Externally set scaling up fraction. Floating when set fSU<-10.0.')
parser.add_option('--fMU', dest='e_FMU', default=-100.0, type='float',
                  help='Externally set matching up fraction. Floating when set fMU<-10.0.')
parser.add_option('--TD', dest='toydataFile', default='',
                  help='a file corresponding to a toy dataset')
parser.add_option('-i', '--init', dest='startingFile',
                  default='',
                  help='File to use as the initial template')
parser.add_option('-d', '--dir', dest='mcdir', default='',
                  help='directory to pick up the W+jets shapes')
parser.add_option('-m', '--mode', default="MjjOptimizeConfig",
                  dest='modeConfig',
                  help='which config to select look at HWWconfig.py for an '+ \
                  'example.  Use the file name minus the .py extension.')
parser.add_option('--btag', default=False, action='store_true', dest='btag',
                  help='b tag both jets')
parser.add_option('--Err', dest='Err', default=-1., type='float',
                  help='error band level')
parser.add_option('-W', '--WpJ', dest='ParamWpJ', type='int',
                  default=-1, help=wpjhelp)
(opts, args) = parser.parse_args()

import pyroot_logon
config = __import__(opts.modeConfig)

from ROOT import gPad, TFile, Double, Long, gROOT, TCanvas
## gROOT.ProcessLine('.L RooWjjFitterParams.h+');
gROOT.ProcessLine('.L EffTableReader.cc+')
gROOT.ProcessLine('.L EffTableLoader.cc+')
gROOT.ProcessLine('.L RooWjjFitterUtils.cc+')
gROOT.ProcessLine('.L RooWjjMjjFitter.cc+')
from ROOT import RooWjjMjjFitter, RooFitResult, \
     RooMsgService, RooFit, TLatex, TMatrixDSym, RooArgList, RooArgSet, \
     gPad, RooAbsReal, kBlue, kCyan, kRed, RooCurve, RooPlot
from math import sqrt


RooMsgService.instance().setGlobalKillBelow(RooFit.WARNING)

fitterPars = config.theConfig(opts.Nj, opts.mcdir, opts.startingFile, opts.btag, opts.toydataFile, opts.e_FSU, opts.e_FMU)

fitterPars.WpJfunction = opts.ParamWpJ
#fitterPars.truncRange = True
if opts.ParamWpJ<0:
    fitterPars.smoothingOrder = 0

if fitterPars.includeMuons and fitterPars.includeElectrons:
    modeString = ''
elif fitterPars.includeMuons:
    modeString = 'Muon'
elif fitterPars.includeElectrons:
    modeString = 'Electron'
else:
    modeString = ''

dibosonParameterize = 0
if opts.btag:
    dibosonParameterize = 2
    fitterPars.constrainWpJShape = True
    fitterPars.constrainDibosonShape = True

theFitter = RooWjjMjjFitter(fitterPars)

theFitter.makeDibosonPdf(dibosonParameterize)
theFitter.makeFitter((opts.ParamWpJ>=0))

#theFitter.getWorkSpace().Print()
fr = theFitter.fit()

# chi2 = Double(0.)
#ndf = Long(2)
extraNdf = 0
if not opts.btag:
    extraNdf = 2
## if (fitterPars.doNewPhysics):
##     extraNdf += 1
## if not fitterPars.constrainDiboson:
##     extraNdf += 1
## ndf = Long(3+extraNdf)
ndf = Long(1+extraNdf)
print ' *** uncorrected chi2 ***'
chi2 = theFitter.computeChi2(ndf, False)
print ' *** corrected chi2 ***'
ndf = Long(1+extraNdf)
chi2 = theFitter.computeChi2(ndf, True)
print ' *** '
chi2 = 0
# chi2frame.Draw()

# assert False, "fit done"

yields = fr.floatParsFinal()
mass = theFitter.getWorkSpace().var(fitterPars.var)
iset = RooArgSet(mass)
covMatrix = TMatrixDSym(fr.covarianceMatrix())

sig2 = 0.
sig2All = 0.
for v1 in range(0, covMatrix.GetNrows()):
    for v2 in range(0, covMatrix.GetNcols()):
        if ((yields[v1].GetName())[0] == 'n') and \
               ((yields[v2].GetName())[0] == 'n'):
            #print v1, yields[v1].GetName(),',', v2, yields[v2].GetName()
            if not (yields[v1].GetName() == 'nDiboson') \
                   and not (yields[v2].GetName() == 'nDiboson'):
                sig2 += covMatrix(v1, v2)
            sig2All += covMatrix(v1, v2)

from plotMjjFit import plot2BodyDist

if (opts.Err >= 0) and (opts.Err < 1):
    opts.Err = sqrt(sig2)

leftLegend = True #(not opts.btag)
PrefixString = "Diboson"
if opts.btag:
    PrefixString += "_btag"
(plots, cans) = plot2BodyDist(theFitter, fitterPars, chi2, ndf,
                              opts.Err, Prefix = PrefixString,
                              Left = leftLegend)

h_total = plots[0].getCurve('h_total')
theData = plots[0].getHist('theData')

## mass.setRange('signal', fitterPars.minTrunc, fitterPars.maxTrunc)
## sigInt = theFitter.makeFitter().createIntegral(iset, 'signal')
## sigFullInt = theFitter.makeFitter().createIntegral(iset)
## dibosonInt = theFitter.makeDibosonPdf().createIntegral(iset, 'signal')
## dibosonFullInt = theFitter.makeDibosonPdf().createIntegral(iset)
## WpJInt = theFitter.makeWpJPdf().createIntegral(iset, 'signal')
## WpJFullInt = theFitter.makeWpJPdf().createIntegral(iset)
## ttbarInt = theFitter.makettbarPdf().createIntegral(iset, 'signal')
## ttbarFullInt = theFitter.makettbarPdf().createIntegral(iset)
## SingleTopInt = theFitter.makeSingleTopPdf().createIntegral(iset, 'signal')
## SingleTopFullInt = theFitter.makeSingleTopPdf().createIntegral(iset)
## QCDInt = theFitter.makeQCDPdf().createIntegral(iset, 'signal')
## QCDFullInt = theFitter.makeQCDPdf().createIntegral(iset)
## ZpJInt = theFitter.makeZpJPdf().createIntegral(iset, 'signal')
## ZpJFullInt = theFitter.makeZpJPdf().createIntegral(iset)
## ## print "*** yield vars ***"
## ## yields.Print("v")

## usig2 = 0.
bkgYield = 0.
totalYield = 0.

## sigYieldsFile = open('lastMjjSigYield.txt', 'w')
## print
## print '-------------------------------'
## print 'Yields in signal box'
## print '-------------------------------'
for i in range(0, yields.getSize()):
    theName = yields.at(i).GetName()
    if (theName[0] == 'n'):
        totalYield += yields.at(i).getVal()
        if not (theName == 'nDiboson'):
            bkgYield += yields.at(i).getVal()
##         theIntegral = 1.
##         if (theName == 'nDiboson'):
##             theIntegral = dibosonInt.getVal()/dibosonFullInt.getVal()
##         elif (theName == 'nWjets'):
##             theIntegral = WpJInt.getVal()/WpJFullInt.getVal()
##         elif (theName == 'nTTbar'):
##             theIntegral = ttbarInt.getVal()/ttbarFullInt.getVal()
##         elif (theName == 'nSingleTop'):
##             theIntegral = SingleTopInt.getVal()/SingleTopFullInt.getVal()
##         elif (theName == 'nQCD'):
##             theIntegral = QCDInt.getVal()/QCDFullInt.getVal()
##         elif (theName == 'nZjets'):
##             theIntegral = ZpJInt.getVal()/ZpJFullInt.getVal()

##         yieldString = '%s = %0.0f +/- %0.0f' % (theName,
##                                                 yields.at(i).getVal()*theIntegral,
##                                                 yields.at(i).getError()*theIntegral)
##         print yieldString
##     else:
##         yieldString = '%s = %0.3f +/- %0.3f' % (theName,
##                                                 yields.at(i).getVal(),
##                                                 yields.at(i).getError())
##     sigYieldsFile.write(yieldString + '\n')
## print '-------------------------------'
## print 'total yield: %0.0f +/- %0.0f' % (totalYield*sigInt.getVal()/sigFullInt.getVal(), sigInt.getVal()*sqrt(sig2))
## print '-------------------------------'

## sigYieldsFile.close()

## if opts.qplot:
##     import makeQPlot
##     qplotPars = makeQPlot.theConfig(fitterPars, 'lastMjjSigYield.txt')
##     (cq, shapeHist, totalHist) = makeQPlot.qPlot(qplotPars)
##     pyroot_logon.cmsPrelim(cq, fitterPars.intLumi/1000)
##     cq.Print('Wjj_Mjj_%s_%ijets_Q.pdf' % (modeString, opts.Nj))
##     cq.Print('Wjj_Mjj_%s_%ijets_Q.png' % (modeString, opts.Nj))

fr.SetName('nll')
fr.Print()
nll=fr.minNll()
print '***** nll = ',nll,' ***** \n'
print 'background yield: %0.0f +/- %0.0f' % (bkgYield, sqrt(sig2))
print 'Total yield: %0.0f +/- %0.0f' % (totalYield, sqrt(sig2All))

print 'shape file created'
ShapeFile = TFile('%s_%s_%iJets_Fit_Shapes.root' % (PrefixString, modeString,
                                                    opts.Nj), 'recreate')
h_total.Write()
theData.Write()
fr.Write()
for frame in plots:
    frame.Write()
ShapeFile.Close()
