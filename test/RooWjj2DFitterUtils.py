import pyroot_logon
from RooWjj2DFitterPars import Wjj2DFitterPars
from ROOT import TH2D, TFile, gDirectory, TTreeFormula, RooDataHist, \
    RooHistPdf, RooArgList, RooArgSet, RooFit, RooDataSet, RooRealVar, \
    TRandom3, RooPowerLaw, RooClassFactory, gROOT, TClass, TH1D
from array import array
from EffLookupTable import EffLookupTable
import random

from HWWSignalShapes import HiggsCPWeight
import warnings
warnings.filterwarnings( action='ignore', category=RuntimeWarning, message='creating converter for unknown type "const char\*\*".*' )

class Wjj2DFitterUtils:
    # initialization for the class
    def __init__(self, pars):
        self.pars = pars

        self.files2EffTables()
        print 'full cuts:',self.fullCuts()

    # read files and store efficiency tables
    def files2EffTables(self):
        numLumiEpochs = len(self.pars.lumiPerEpoch)
        for eff in self.pars.effToDo:
            setattr(self, '%sEffTables' % eff, {})
            effTables = getattr(self, '%sEffTables' % eff)
            files = getattr(self.pars, '%sEffFiles' % eff)
            for key in files:
                effTables[key] = []
                for theFile in files[key]:
                    print eff,key,':',theFile
                    effTables[key].append(EffLookupTable(theFile))
                if (len(effTables[key]) != numLumiEpochs):
                    assert False, "Number of lumi epocs mismatch"
            # print effTables

    # create a new empty 2D histogram with the appropriate binning
    def newEmptyHist(self, histName):
        newHist = None
        histCmd = 'TH%iD("%s","%s"' % (len(self.pars.var), histName, histName)
        for v in self.pars.var:
            if len(self.pars.varRanges[v][3]) > 1:
                histCmd += ',%i,%s' % (len(self.pars.varRanges[v][3])-1,
                                       "array('d', self.pars.varRanges[v][3])")
            else:
                histCmd += ',%i,%f,%f' % (self.pars.varRanges[v][0],
                                          self.pars.varRanges[v][1],
                                          self.pars.varRanges[v][2])
        histCmd += ')'
        print 'histCmd=',histCmd
        newHist = eval(histCmd)

        return newHist

    # the cuts to be applied to any data
    def fullCuts(self):
        if len(self.pars.cuts) > 0:
            theCut = '(%s)' % self.pars.cuts
        else:
            theCut = '(1==1)'
        for v in self.pars.var:
            theCut += '&&(%s>%0.3f)&&(%s<%0.3f)'%(v,self.pars.varRanges[v][1],
                                                  v,self.pars.varRanges[v][2])
        return '(%s)' % theCut

    def btagVeto(self, row, vbf = False):
        jeti = 0
        veto = False
        while (jeti < 6) and (row.JetPFCor_Pt[jeti] >= 30.):
            if (abs(row.JetPFCor_Eta[jeti]) < 2.4) and \
                    (row.JetPFCor_bDiscriminatorCSV[jeti] > 0.898):
                veto = True

        return veto
            
    # generator function for looping over an event tree and applying the cuts
    def TreeLoopFromFile(self, fname, noCuts = False,
                         cutOverride = None, CPweight = False, 
                         interference = 0):

        # open file and get tree
        treeFile = TFile.Open(fname)
        theTree = treeFile.Get(self.pars.treeName)

        if not theTree:
            print 'failed to find tree %s in file %s' % (self.pars.treeName, 
                                                         fname)
            return

        # get the right cuts
        if cutOverride:
            theCuts = cutOverride
            print 'override cuts:',cutOverride
        elif noCuts:
            theCuts = ''
        else:
            theCuts = self.fullCuts()

        # create an entry list which apply the cuts to the tree
        if gDirectory.Get('cuts_evtList'):
            gDirectory.Delete('cuts_evtList')
        theTree.Draw('>>cuts_evtList', theCuts, 'entrylist')
        theList = gDirectory.Get('cuts_evtList')

        # create fomulae for the variables of interest
        rowVs = []
        for (i,v) in enumerate(self.pars.var):
            rowVs.append(TTreeFormula('v%i' % i, v, theTree))

        # loop over the selected events calculate their weight and yield
        # the two variable values and the weight for each selected event.
        print "selected events:",theList.GetN()
        while theTree.GetEntry(theList.Next()):
            if self.pars.isElectron:
                lep_pt = theTree.W_electron_pt
                lep_eta = theTree.W_electron_eta
            else:
                lep_pt = theTree.W_muon_pt
                lep_eta = theTree.W_muon_eta
            # jet_pt = []
            # jet_eta = []
            # for (idx, pt) in enumerate(theTree.JetPFCor_Pt):
            #     if pt > 0:
            #         jet_pt.append(pt)
            #         jet_eta.append(theTree.JetPFCor_Eta[idx])

            # effWgt = self.effWeight(lepton_pt = lep_pt, lepton_eta = lep_eta, 
            #                         #jet_pt = jet_pt, jet_eta,
            #                         mt_pt = theTree.W_mt, mt_eta = lep_eta,
            #                         met_pt = theTree.event_met_pfmet, 
            #                         met_eta = 0.)
            if (hasattr(self.pars, 'btagVeto')) and (self.pars.btagVeto) and \
                    self.btagVeto(theTree):
                continue

            effWgt = theTree.puwt*theTree.effwt
            if CPweight:
                if hasattr(theTree, 'complexpolewtggH%i' % self.pars.mHiggs):
                    cpw = getattr(theTree, 
                                  'complexpolewtggH%i' % self.pars.mHiggs)
                    cpw /= getattr(theTree, 
                                   'avecomplexpolewtggH%i' % self.pars.mHiggs)
                else:
                    cpw = HiggsCPWeight(self.pars.mHiggs, theTree.W_H_mass_gen)
            else:
                cpw = 1.
            if interference == 1:
                iwt = getattr(theTree, 
                              'interferencewtggH%i' % self.pars.mHiggs)
            elif interference == 2:
                iwt = getattr(theTree, 
                              'interferencewt_upggH%i' % self.pars.mHiggs)
            elif interference == 3:
                iwt = getattr(theTree,
                              'interferencewt_downggH%i' % self.pars.mHiggs)
            else:
                iwt = 1.
            row = [ v.EvalInstance() for v in rowVs ]
            yield (row, effWgt, cpw, iwt)

        return
        

    # from a file fill a 2D histogram
    def File2Hist(self, fname, histName, noCuts = False, 
                  cutOverride = None, CPweight = False,
                  doWeights = True, interference = 0):
        theHist = self.newEmptyHist(histName)

        print 'filename:',fname
        doEffWgt = (self.pars.doEffCorrections and not cutOverride \
                        and doWeights)
        
        for (row, effWgt, cpw, iwt) in self.TreeLoopFromFile(fname, 
                                                             noCuts, 
                                                             cutOverride,
                                                             CPweight,
                                                             interference):
            #print 'entry:',v1val,v2val,effWgt
            if not doEffWgt:
                effWgt = 1.0
            if CPweight:
                effWgt *= cpw
            if interference in [1,2,3]:
                effWgt *= iwt
            if len(row) == 1:
                theHist.Fill(row[0], effWgt)
            elif len(row) == 2:
                theHist.Fill(row[0], row[1], effWgt)
            elif len(row) == 3:
                theHist.Fill(row[0], row[1], row[2], effWgt)

        return theHist

    # take a 2D histogram and create a RooHistPdf
    def Hist2Pdf(self, hist, pdfName, ws, order = 0):
        if ws.pdf(pdfName):
            return ws.pdf(pdfName)

        try:
            obs = [ self.pars.varNames[x] for x in self.pars.var ]
        except AttributeError:
            obs = self.pars.var

        varList = RooArgList()
        for v in obs:
            varList.add(ws.var(v))
        newHist = RooDataHist(pdfName + '_hist', pdfName + '_hist',
                              varList, hist)
        
        thePdf = RooHistPdf(pdfName, pdfName, RooArgSet(varList), 
                            newHist, order)
        getattr(ws, 'import')(thePdf)

        return ws.pdf(pdfName)

    # from a file fill and return a RooDataSet
    def File2Dataset(self, fnames, dsName, ws, noCuts = False, 
                     weighted = False, CPweight = False, cutOverride = None,
                     interference = 0):
        if ws.data(dsName):
            return ws.data(dsName)

        cols = RooArgSet(ws.set('obsSet'))
        # print 'interference weight flag:',interference
        if weighted:
            evtWgt = RooRealVar('evtWgt', 'evtWgt', 1.0)
            cols.add(evtWgt)
            ds = RooDataSet(dsName, dsName, cols, 'evtWgt')
            print 'including weights for eff',
            if CPweight:
                print 'and CP weight',
            if interference in [1,2,3]:
                print 'and interference',
            print
        else:
            ds = RooDataSet(dsName, dsName, cols)
            
        if not (type(fnames) == type([])):
            fnames = [fnames]

        try:
            obs = [ self.pars.varNames[x] for x in self.pars.var ]
        except AttributeError:
            obs = self.pars.var

        for fname in fnames:
            for (row, effWgt, cpw, iwt) in \
                    self.TreeLoopFromFile(fname, noCuts,
                                          CPweight = CPweight,
                                          cutOverride = cutOverride,
                                          interference = interference):
                inRange = True
                for (i,v) in enumerate(obs):
                    inRange = (inRange and ws.var(v).inRange(row[i], ''))
                    cols.setRealValue(v, row[i])
                if CPweight:
                    effWgt *= cpw
                if interference in [1,2,3]:
                    effWgt *= iwt
                if inRange:
                    ds.add(cols, effWgt)

        getattr(ws, 'import')(ds)

        return ws.data(dsName)

    def reduceDataset(data, scale = 1.0):
        print 'reducing',data.GetName(),'by scale %.4g' % scale
        newData = data.emptyClone(data.GetName() + '_reduced')
        rnd = TRandom3()
        for i in range(0,data.numEntries()):
            if (rnd.Rndm() < scale):
                newData.add(data.get(i), data.weight())
        return newData

    # calculate the efficiency weight for a give event using the supplied
    # tables.
    def effWeight(self, **kinematics):
        # select which lumi/trigger epoch we are going to use for the 
        # computation
        epochSelector = random.random()
        sumLumi = 0.
        epoch = -1
        while (epochSelector > sumLumi/self.pars.integratedLumi) and \
                (epoch < len(self.pars.lumiPerEpoch)-1):
            epoch += 1
            sumLumi += self.pars.lumiPerEpoch[epoch]

        evtWgt = 1.0
        for eff in self.pars.effToDo:
            evtWgt *= self.computeEff(kinematics['%s_pt' % (eff)],
                                      kinematics['%s_eta' % (eff)],
                                      epoch, **(getattr(self,
                                                        '%sEffTables' % (eff)))
                                      )

        #print 'evtWgt:',evtWgt
        return evtWgt

    # take a dictionary of efficiency tables and compute the efficiency
    def computeEff(self, pt, eta, epoch, **tables):
        eff = 1.0
        #print 'efficiency tables:',tables
        for key in tables:
            eff *= tables[key][epoch].GetEfficiency(pt, eta)

        return eff

    # various analytic models that can be selected easily.
    def analyticPdf(self, ws, var, model, pdfName, idString = None, 
                    auxModel = None):
        if ws.pdf(pdfName):
            return ws.pdf(pdfName)

        if model==0:
            # exponential model
            ws.factory('RooExponential::%s(%s,c_%s[-10,10])' % \
                           (pdfName, var, idString)
                       )
        elif model==1:
            # power-law model
            ws.factory("power_%s[-2., -30., 30.]" % idString)
            ws.factory("RooPowerLaw::%s(%s, power_%s)" % \
                           (pdfName, var, idString)
                       )
        elif model== 2:
            # power law * exponential pdf
            ws.factory("power_%s[5., -30., 30.]" % idString)
            ws.factory("c_%s[-0.015, -10, 10]" % idString)
            ws.factory("RooPowerExpPdf::%s(%s, c_%s, power_%s)" %\
                           (pdfName, var, idString, idString)
                       )
        elif model==3:
            # a CrystalBall model
            ws.factory("RooCBShape::%s(%s,mean_%s[84,0,1000],sigma_%s[10.,0,500]," %\
                           (pdfName, var, idString, idString) + \
                           'alpha_%s[-0.5, -10., 10], npow_%s[10, -10, 100])' %\
                           (idString, idString)
                       )
        elif model==4:
            # a second order polynomial
            ws.factory("RooChebychev::%s(%s,{a1_%s[-10,10],a2_%s[-10,10]})" %\
                           (pdfName, var, idString, idString)
                       )
        elif model==5:
            # a double gaussian
            ws.factory("RooGaussian::%s_core" % pdfName + \
                           "(%s, mean_%s_core[84.,0,1000],sigma_%s_core[10.,0,500])" %\
                           (var, idString, idString)
                       )
            ws.factory("RooGaussian::%s_tail" % pdfName + \
                           "(%s, mean_%s_tail[100.,0,1000],sigma_%s_tail[50.,0,500])" %\
                           (var, idString, idString)
                       )
            ws.factory("SUM::%s(f_%s_core[0.5,0,1] * %s_core, %s_tail)" % \
                           (pdfName, idString, pdfName, pdfName)
                       )
        elif model==6:
            # a CB + gaussian with same means
            ws.factory("RooCBShape::%s_core" % pdfName + \
                           "(%s, mean_%s[84.,0,1000],sigma_%s_core[10.,0,500]," %\
                           (var, idString, idString) + \
                           "alpha_%s[2.,-10,10], npow_%s[2.])" %\
                           (idString, idString)
                       )
            ws.factory("RooGaussian::%s_tail" % pdfName + \
                           "(%s, mean_%s,sigma_%s_tail[50.,0,500])" %\
                           (var, idString, idString)
                       )
            ws.factory("SUM::%s(f_%s_core[0.5,0,1] * %s_core, %s_tail)" % \
                           (pdfName, idString, pdfName, pdfName)
                       )
        elif model==7:
            # a CB + exp
            ws.factory("RooCBShape::%s_core" % pdfName + \
                           "(%s, mean_%s_core[84.,0,1000],sigma_%s_core[10.,0,500]," %\
                           (var, idString, idString) + \
                           "alpha_%s[2.,-10,10], npow_%s[2.])" % \
                           (idString, idString)
                       )
            ws.factory("RooExponential::%s_tail" % pdfName + \
                           "(%s, c_%s_tail[-10, 10])" %\
                           (var, idString)
                       )
            ws.factory("SUM::%s(f_%s_core[0.5,0,1] * %s_core, %s_tail)" % \
                           (pdfName, idString, pdfName, pdfName)
                       )
        elif model== 8:
            # erf * exponential pdf
            ws.factory("c_%s[-0.015, -10, 10]" % idString)
            ws.factory("offset_%s[70, -100, 1000]" % idString)
            ws.factory("width_%s[20, 0, 1000]" % idString)
            ws.factory("RooErfExpPdf::%s(%s, c_%s, offset_%s, width_%s)" %\
                           (pdfName, var, idString, idString, idString)
                       )
        elif model == 9:
            # voitian pdf + gaussian
            ws.factory("RooVoigtian::%s_core(%s,mean_%s[84.,0,1000], " %\
                           (pdfName, var, idString) + \
                           "width_%s[15.], resolution_%s[10.,0,500])" %\
                           (idString, idString)
                       )
            ws.factory("RooGaussian::%s_tail" % (pdfName) + \
                           "(%s, mean_%s, sigma_%s_tail[100,0,500])" % \
                           (var, idString, idString)
                       )
            ws.factory("SUM::%s(f_%s_core[0.5,0,1] * %s_core, %s_tail)" % \
                           (pdfName, idString, pdfName, pdfName)
                       )
            ws.var('width_%s' % idString).setConstant(True)
        elif model == 10:
            #erf * 2 parameter power law
            ws.factory("offset_%s[40, 0, 1000]" % idString)
            ws.factory("width_%s[10, 0, 1000]" % idString)
            ws.factory("power_%s[2, -30, 30]" % idString)
            ws.factory("power2_%s[0, -20, 20]" % idString)
            ws.factory("EXPR::%s('(TMath::Erf((@0-@1)/@2)+1)/2./TMath::Power(@0,@3+@4*log(@0/@5))', %s, offset_%s, width_%s, power_%s, power2_%s, 8000)" % \
                           (pdfName, var, idString, idString, idString, 
                            idString)
                       )
        elif model == 11:
            #3th order polynomial
            ws.factory("RooChebychev::%s(%s,{a1_%s[-10,10],a2_%s[-10,10],a3_%s[-10,10]})" % \
                           (pdfName, var, idString, idString, idString)
                       )
        elif model == 12:
            # 2 parameter power law
            ws.factory("power_%s[2, -30, 30]" % idString)
            ws.factory("power2_%s[0, -20, 20]" % idString)
            ws.factory("EXPR::%s('1./TMath::Power(@0,@1+@2*log(@0/@3))', %s, power_%s, power2_%s, 8000)" % \
                           (pdfName, var, idString, idString)
                       )
        elif model == 13:
            # gaussian + erf*exp
            ws.factory("RooGaussian::%s_core" % pdfName + \
                           "(%s, mean_%s_core[84.,0,1000],sigma_%s_core[10.,0,500])" %\
                           (var, idString, idString)
                       )
            ws.factory("c_%s[-0.015, -10, 10]" % idString)
            ws.factory("offset_%s[70, -100, 1000]" % idString)
            ws.factory("width_%s[20, 0, 1000]" % idString)
            ws.factory("RooErfExpPdf::%s_tail(%s, c_%s, offset_%s, width_%s)" %\
                           (pdfName, var, idString, idString, idString)
                       )
            ws.factory("SUM::%s(f_%s_core[0.5,0,1] * %s_core, %s_tail)" % \
                           (pdfName, idString, pdfName, pdfName)
                       )
        elif model == 14:
            #erf * simple power law
            ws.factory("offset_%s[40, 0, 1000]" % idString)
            ws.factory("width_%s[10, 0, 1000]" % idString)
            ws.factory("power_%s[2, -30, 30]" % idString)
            ws.factory("EXPR::%s('(TMath::Erf((@0-@1)/@2)+1)/2./TMath::Power(@0,@3)', %s, offset_%s, width_%s, power_%s)" % \
                           (pdfName, var, idString, idString, idString)
                       )
        elif model == 15:
            #erf * 2 parameter power law + exp
            ws.factory("offset_%s[40, 0, 1000]" % idString)
            ws.factory("width_%s[10, 0, 1000]" % idString)
            ws.factory("power_%s[2, -30, 30]" % idString)
            ws.factory("power2_%s[0, -20, 20]" % idString)
            ws.factory("EXPR::%s_tail('(TMath::Erf((@0-@1)/@2)+1)/2./TMath::Power(@0,@3+@4*log(@0/@5))', %s, offset_%s, width_%s, power_%s, power2_%s, 8000)" % \
                           (pdfName, var, idString, idString, idString, 
                            idString)
                       )
            ws.factory('RooExponential::%s_core(%s,c_%s[-10,10])' % \
                           (pdfName, var, idString)
                       )
            ws.factory("SUM::%s(f_%s_core[0.1,0,1] * %s_core, %s_tail)" % \
                           (pdfName, idString, pdfName, pdfName)
                       )
        elif model == 16:
            #erf * simple power law + exp
            ws.factory("offset_%s[40, 0, 1000]" % idString)
            ws.factory("width_%s[10, 0, 1000]" % idString)
            ws.factory("power_%s[2, -30, 30]" % idString)
            ws.factory("EXPR::%s_tail('(TMath::Erf((@0-@1)/@2)+1)/2./TMath::Power(@0,@3)', %s, offset_%s, width_%s, power_%s)" % \
                           (pdfName, var, idString, idString, idString)
                       )
            ws.factory('RooExponential::%s_core(%s,c_%s[-10,10])' % \
                           (pdfName, var, idString)
                       )
            ws.factory("SUM::%s(f_%s_core[0.1,0,1] * %s_core, %s_tail)" % \
                           (pdfName, idString, pdfName, pdfName)
                       )
        elif model == 17:
            #4th order polynomial
            ws.factory("RooChebychev::%s(%s,{a1_%s[-10,10],a2_%s[-10,10],a3_%s[-10,10],a4_%s[-10,10]})" % \
                           (pdfName, var, idString, idString, idString, 
                            idString)
                       )
        elif model == 18:
            # QCD inspired power law
            p1 = ws.factory("power_%s[-100]" % idString)
            p1.setConstant(False)
            p2 = ws.factory("power2_%s[-15]" % idString)
            p2.setConstant(False)
            p3 = ws.factory("power3_%s[450.]" % idString)
            p3.setConstant(False)
            ws.factory("EXPR::%s('TMath::Power(1.-@0/@3,@4)/TMath::Power(@0/@3,@1+@2*log(@0/@3))', %s, power_%s, power2_%s, 8000, power3_%s)" % \
                           (pdfName, var, idString, idString, idString)
                       )
        elif model == 19:
            #alpha function morphed pdf where the pdf is passed as auxModel
            self.analyticPdf(ws, var, auxModel[0], '%s_side' % pdfName, 
                             idString + '_side')
            self.analyticPdf(ws, var, auxModel[1], '%s_sig' % pdfName, 
                             idString + '_sig')
            ws.factory("alphaFunction::%s_alpha(%s, %s_side, %s_sig)" % \
                           (pdfName, var, pdfName, pdfName)
                       )
            self.analyticPdf(ws, var, auxModel[2], '%s_pdf' % pdfName, idString)
            ws.factory("RooEffProd::%s(%s_pdf, %s_alpha)" % (pdfName, pdfName,
                                                            pdfName)
                       )
        elif model == 20:
            #alpha combination of two pdfs high and low
            lowPdf = self.analyticPdf(ws,var,auxModel[0],'%s_low' % pdfName,
                                      idString + '_low')
            lowPdf.getParameters(ws.set('obsSet')).setAttribAll(
                'Constant', True)
            highPdf = self.analyticPdf(ws,var,auxModel[1],'%s_high' % pdfName,
                                       idString + '_high')
            highPdf.getParameters(ws.set('obsSet')).setAttribAll(
                'Constant', True)
            ws.factory("SUM::%s(alpha_comb_%s[0.5, 0., 1.]*%s_low, %s_high)" % \
                           (pdfName, pdfName,pdfName,idString)
                       )
        else:
            # this is what will be returned if there isn't a model implemented
            # for a given model code.
            ws.factory("RooChebychev::%s(%s,{a1_%s[-10,10],a2_%s[-10,10]})" %\
                           (pdfName, var, idString, idString)
                       )

        return ws.pdf(pdfName)

    reduceDataset = staticmethod(reduceDataset)

if __name__ == '__main__':

    #import pyroot_logon
    from ROOT import gPad, RooWorkspace

    params = Wjj2DFitterPars()
    utils = Wjj2DFitterUtils(params)

    # dataHist = utils.File2Hist(params.MCDirectory + \
    #                                'RD_mu_HWWMH250_CMSSW525_private.root',
    #                            'dataHist')
    # dataHist.Print()
    # dataHist.Draw('colz')
    # gPad.Update()
    # gPad.WaitPrimitive()

    theWS = RooWorkspace()
    theWS.factory('%s[%f,%f]' % (params.var[0], 
                                 params.varRanges[params.var[0]][1], 
                                 params.varRanges[params.var[0]][2]))
    theWS.factory('%s[%f,%f]' % (params.var[1], 
                                 params.varRanges[params.var[1]][1], 
                                 params.varRanges[params.var[1]][2]))
    theWS.defineSet('obsSet', ','.join(params.var))

    #theWS.Print()
    # utils.Hist2Pdf(dataHist, "H250SignalHist", theWS)
    #theWS.Print()

    # dataset = utils.File2Dataset(params.MCDirectory + \
    #                                  'RD_mu_HWWMH250_CMSSW525_private.root', 
    #                              "H250SignalData", theWS)
    # dataset.Print()

    print 

    for model in range(10):
        utils.analyticPdf(theWS, params.var[0], model, 'pdf_%i' % model,
                          '%i_%s' % (model,params.var[0]))

    theWS.Print()
