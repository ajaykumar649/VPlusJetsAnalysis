import pyroot_logon
import limits

from ROOT import *

f = TFile('/uscms_data/d2/kalanand/junk/vplusjets/CMSSW_5_3_2_patch4/src/ElectroWeakAnalysis/VPlusJets/test/TGC/mu_boosted.root')

background = f.Get('background')
data_obs = f.Get('data_obs')
diboson = f.Get('diboson')

background.Add(diboson, -1.)

theWS = RooWorkspace('theWS', 'theWS')

wpt = theWS.factory('W_pt[%f,%f]' % (data_obs.GetBinLowEdge(1), 
                                     data_obs.GetBinLowEdge(data_obs.GetNbinsX())+data_obs.GetBinWidth(data_obs.GetNbinsX())))
wpt.setBins(data_obs.GetNbinsX())

lz = theWS.factory('lZ[0., -1., 1.]')
# lz = theWS.factory('lZ[0.]')
lz.setConstant(False)
dkg = theWS.factory('dkg[0., -0.5, 0.5]')
dg1 = theWS.factory('dg1[0.]')


vars = RooArgList(wpt)
varSet = RooArgSet(wpt)

data = RooDataHist('data', 'data', vars, data_obs)
bkgHist = RooDataHist('bkgHist', 'bkgHist', vars, background)
dibosonHist = RooDataHist('dibosonHist', 'dibosonHist', vars, diboson)

bkgPdf = RooHistPdf('bkgPdf', 'bkgPdf', varSet, bkgHist)
dibosonPdf = RooHistPdf('dibosonPdf', 'dibosonPdf', varSet, dibosonHist)

aTGC = RooATGCFunction('aTGC', 'aTGC', wpt, lz, dkg, dg1, 
                       'TGC/ATGC_shape_coefficients.root')
aTGCPdf = RooEffProd('aTGCPdf', 'aTGCPdf', dibosonPdf, aTGC)

nbkg = theWS.factory('prod::bkg_yield(n_bkg[%f],bkg_nrm[1.,-1.,5.])' % \
                         (background.Integral()))
ndiboson = theWS.factory('prod::diboson_yield(n_diboson[%f],diboson_nrm[1.,-1.,5.])' % \
                             (diboson.Integral()))

getattr(theWS, 'import')(data)
getattr(theWS, 'import')(bkgPdf)
getattr(theWS, 'import')(aTGCPdf)

theWS.factory('RooExtendPdf::bkg_extended(bkgPdf,bkg_yield)')
theWS.factory('RooExtendPdf::aTGC_extended(aTGCPdf,diboson_yield)')
comps = RooArgList(theWS.argSet('aTGC_extended,bkg_extended'))
total = RooAddPdf('total', 'total', comps)

getattr(theWS, 'import')(total)
theWS.factory('RooGaussian::bkg_const(bkg_nrm, 1.0, 0.05)')
total_const = theWS.factory('PROD::total_const(total, bkg_const)')

theWS.Print()

total_const.fitTo(data, RooFit.Constrained(), RooFit.Extended())

frame = wpt.frame()
data.plotOn(frame)
total_const.plotOn(frame)
total_const.plotOn(frame, RooFit.Components('bkg*'),
                   RooFit.LineColor(kRed),
                   RooFit.LineStyle(kDashed))
data.plotOn(frame)
frame.Draw()

gPad.Update()
gPad.WaitPrimitive()

poi = RooArgSet(lz, dkg)

limit = limits.plcLimit(wpt, poi, total_const, theWS, data, verbose = True)

#theWS.Print()
fout = TFile('ATGC_likelihood.root', 'recreate')
theWS.Write()
fout.Close()
