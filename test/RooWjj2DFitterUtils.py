import pyroot_logon
from RooWjj2DFitterPars import Wjj2DFitterPars
from ROOT import TH2D, TFile, gDirectory, TTreeFormula, RooDataHist, \
    RooHistPdf, RooArgList, RooArgSet, RooFit, RooDataSet, RooRealVar, \
    TRandom3, RooPowerLaw, RooClassFactory, gROOT, TClass, TH1D, \
    RooChebyshevPDF, TH1F
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
    def newEmptyHist(self, histName, pickVar = None):
        newHist = None
        histCmd = 'TH%iF("%s","%s"' % (1 if pickVar else len(self.pars.var),
                                       histName, histName)
        for (i,v) in enumerate(self.pars.var):
            if ((pickVar) and (pickVar == i+1)) or (not pickVar):
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
    def fullCuts(self, override = None):
        if len(self.pars.cuts) > 0:
            theCut = '(%s)' % self.pars.cuts
        else:
            theCut = '(1==1)'
        if override:
            theCut = '(%s)' % override
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
            theCuts = self.fullCuts(cutOverride)
            print 'override cuts:',theCuts
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
                     interference = 0, additionalWgt = 1.0):
        if ws.data(dsName):
            return ws.data(dsName)

        cols = RooArgSet(ws.set('obsSet'))
        # print 'interference weight flag:',interference
        if (weighted):
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
                    ds.add(cols, effWgt*additionalWgt)

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
            self.analyticPdf(ws, var, 23, pdfName, idString, 2)
        elif model==5:
            # a double gaussian
            self.analyticPdf(ws, var, 27, '%s_core' % pdfName,
                             '%s_core' % idString, 84.)
            self.analyticPdf(ws, var, 27, '%s_tail' % pdfName,
                             '%s_tail' % idString, 100.)
            ws.factory("SUM::%s(f_%s_core[0.5,0,1] * %s_core, %s_tail)" % \
                           (pdfName, idString, pdfName, pdfName)
                       )
        elif model==6:
            # a CB + gaussian with same means
            ws.factory("RooCBShape::%s_core" % pdfName + \
                           "(%s, mean_%s[84.,0,1000],sigma_%s_core[10.,0,500]," %\
                           (var, idString, idString) + \
                           "alpha_%s[2.,1,10], npow_%s[2.])" %\
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
            # CB + exp
            self.analyticPdf(ws, var, 3, '%s_core' % pdfName,
                             '%s_core' % idString)
            self.analyticPdf(ws, var, 0, '%s_tail' % pdfName,
                             '%s_tail' % idString)
            ws.factory("SUM::%s(f_%s_core[0.5,0,1] * %s_core, %s_tail)" % \
                           (pdfName, idString, pdfName, pdfName)
                       )
        elif model== 8:
            # erf * exponential pdf
            ws.factory("c_%s[-0.015, -10, 10]" % idString)
            offset = ws.factory("offset_%s[70, -100, 1000]" % idString)
            width = ws.factory("width_%s[20, 0, 1000]" % idString)
            offset.setVal(ws.var(var).getMin())
            offset.setError(offset.getVal()*0.2)
            width.setVal(offset.getVal()*0.2)
            width.setError(width.getVal()*0.2)
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
            self.analyticPdf(ws, var, 27, '%s_tail' % pdfName,
                             '%s_tail' % idString, 100.)
            ws.factory("SUM::%s(f_%s_core[0.5,0,1] * %s_core, %s_tail)" % \
                           (pdfName, idString, pdfName, pdfName)
                       )
            ws.var('width_%s' % idString).setConstant(True)
        elif model == 10:
            #erf * 2 parameter power law
            pdfErf = self.analyticPdf(ws, var, 25, '%s_turnon' % pdfName,
                                      idString)
            pdfPower = self.analyticPdf(ws, var, 12, '%s_power' % pdfName,
                                        idString)
            ws.factory("PROD::%s(%s,%s)" % (pdfName, pdfErf.GetName(),
                                            pdfPower.GetName()))
        elif model == 11:
            #3th order polynomial
            self.analyticPdf(ws, var, 23, pdfName, idString, 3)
        elif model == 12:
            # 2 parameter power law
            ws.factory("power_%s[2, -30, 30]" % idString)
            ws.factory("power2_%s[0, -20, 20]" % idString)
            ws.factory("EXPR::%s('1./TMath::Power(@0,@1+@2*log(@0/@3))', %s, power_%s, power2_%s, 8000)" % \
                           (pdfName, var, idString, idString)
                       )
        elif model == 13:
            # gaussian + erf*exp
            self.analyticPdf(ws, var, 27, '%s_core' % pdfName,
                             '%s_core' % idString, 84.)
            self.analyticPdf(ws, var, 8, '%s_tail' % pdfName, idString)
            ws.factory("SUM::%s(f_%s_core[0.5,0,1] * %s_core, %s_tail)" % \
                           (pdfName, idString, pdfName, pdfName)
                       )
        elif model == 14:
            #erf * simple power law
            pdfErf = self.analyticPdf(ws, var, 25, '%s_turnon' % pdfName,
                                      idString)
            pdfPower = self.analyticPdf(ws, var, 1, '%s_power' % pdfName,
                                        idString)
            ws.factory("PROD::%s(%s,%s)" % (pdfName, pdfErf.GetName(),
                                            pdfPower.GetName()))
        elif model == 15:
            #erf * 2 parameter power law + exp
            self.analyticPdf(ws, var, 10, '%s_tail' % pdfName, idString)
            self.analyticPdf(ws, var, 0, '%s_core' % pdfName, idString)
            ws.factory("SUM::%s(f_%s_core[0.1,0,1] * %s_core, %s_tail)" % \
                           (pdfName, idString, pdfName, pdfName)
                       )
        elif model == 16:
            #erf * simple power law + exp
            self.analyticPdf(ws, var, 14, '%s_tail' % pdfName, idString)
            self.analyticPdf(ws, var, 0, '%s_core' % pdfName, idString)
            ws.factory("SUM::%s(f_%s_core[0.1,0,1] * %s_core, %s_tail)" % \
                           (pdfName, idString, pdfName, pdfName)
                       )
        elif model == 17:
            #4th order polynomial
            self.analyticPdf(ws, var, 23, pdfName, idString, 4)
        elif model == 18:
            # QCD inspired power law
            p1 = ws.factory("power_%s[-5.]" % idString)
            p1.setConstant(False)
            p2 = ws.factory("power2_%s[-3.]" % idString)
            p2.setConstant(False)
            p3 = ws.factory("power3_%s[7.]" % idString)
            p3.setConstant(False)
            ws.factory("EXPR::%s('TMath::Power(1.-@0/@3,@4)/TMath::Power(@0/@3,@1+@2*log(@0/@3))', %s, power_%s, power2_%s, m_scale[1200], power3_%s)" % \
                           (pdfName, var, idString, idString, idString)
                       )
            # ws.var('m_scale').setConstant(False)
        elif model == 19:
            #alpha function morphed pdf where the pdf is passed as auxModel
            self.analyticPdf(ws, var, auxModel[0], '%s_side' % pdfName, 
                             idString + '_side', auxModel[3])
            self.analyticPdf(ws, var, auxModel[1], '%s_sig' % pdfName, 
                             idString + '_sig', auxModel[4])
            ws.factory("alphaFunction::%s_alpha(%s, %s_side, %s_sig)" % \
                           (pdfName, var, pdfName, pdfName)
                       )
            self.analyticPdf(ws, var, auxModel[2], '%s_pdf' % pdfName, idString,
                             auxModel[5])
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
        elif model == 21:
            # a 2 parameter power law formerly used by Milano
            ws.factory("power_%s[2, -30, 30]" % idString)
            ws.factory("power2_%s[0, -20, 20]" % idString)
            ws.factory("EXPR::%s('TMath::Power(1-@0/@3,@2)/TMath::Power(@0,@1)', %s, power_%s, power2_%s, m_scale[1200])" % \
                           (pdfName, var, idString, idString)
                       )
        elif model == 22:
            # diboson specific model for the resonant shape
            ws.factory("prod::sigma_%s_W" % (idString) + \
                       "(mean_%s_W[80.3, 50., 100.]," % (idString) + \
                       "resolution_%s[0.1, 0., 5.])" % (idString))
            ws.factory('sum::mean_%s_Z' % (idString) + \
                       "(mean_%s_W, 10.8026)" % (idString))
            ws.factory('prod::sigma_%s_Z(mean_%s_Z,resolution_%s)' % \
                       (idString, idString, idString))
            ws.factory("RooGaussian::%s_W" % pdfName + \
                       "(%s, mean_%s_W, sigma_%s_W)" % (var, idString,
                                                        idString)
                       )
            ws.factory("RooGaussian::%s_Z" % pdfName + \
                       "(%s, mean_%s_Z, sigma_%s_Z)" % (var, idString,
                                                        idString)
                       )
            self.analyticPdf(ws, var, 8, '%s_tail' % pdfName, idString)
            ws.factory("SUM::%s(f_W_%s[0.4,0.,1.]*%s_W,f_Z_%s[0.1,0.,1.]*%s_Z,%s_tail)" % \
                       (pdfName, idString, pdfName, idString, pdfName, pdfName))
        elif model == 23:
            #Nth order polynomial where n is passed in as the auxModel
            print 'polynomial of order',auxModel
            parSet = []
            parList = RooArgList('parList')
            for i in range(0, auxModel):
                parSet.append('a%i_%s' % (i+1, idString))
                a = ws.factory('%s[0.]' % parSet[-1])
                a.setConstant(False)
                parList.add(a)
                # print varSet[-1]
                # a.Print()
            factoryStatement = "RooChebyshevPDF::%s(%s,{%s})" % \
                           (pdfName, var, ','.join(parSet))
            #print factoryStatement
            pdf = RooChebyshevPDF(pdfName, pdfName, ws.var(var), parList)
            getattr(ws, 'import')(pdf)
            #ws.Print()
            #ws.factory(factoryStatement)
        elif model == 24:
            # Nth order polynomial where n is passed in as the auxModel and an
            # erf for turn-on
            print 'polynomial of order',auxModel,'times an erf'
            pdfPoly = self.analyticPdf(ws, var, 23, "%s_poly" % pdfName,
                                       idString, auxModel)
            pdfErf = self.analyticPdf(ws, var, 25, '%s_turnon' % pdfName,
                                      idString)
            ws.factory("PROD::%s(%s,%s)" % (pdfName, pdfPoly.GetName(),
                                            pdfErf.GetName()))
        elif model == 25:
            # erf model
            offset = ws.factory("offset_%s[50, -100, 1000]" % idString)
            offset.setVal(ws.var(var).getMin())
            offset.setError(offset.getVal()*0.2)
            width = ws.factory("width_%s[5, 0, 1000]" % idString)
            width.setVal(offset.getVal()*0.2)
            width.setError(width.getVal()*0.2)
            factoryStatement = "RooErfPdf::%s(%s, offset_%s, width_%s)"%\
                               (pdfName, var, idString, idString)
            ws.factory(factoryStatement)
        elif model == 26:
            # erf * 2 parameter power law + gaussian
            pdfErf = self.analyticPdf(ws, var, 10, '%s_tail' % pdfName,
                                     idString)
            pdfGaus = self.analyticPdf(ws, var, 27, '%s_wiggle' % pdfName,
                                       idString, 150)
            ws.factory('SUM::%s(f_%s[0.1, -1., 1.]*%s, %s)' % \
                       (pdfName, idString, pdfGaus.GetName(), pdfErf.GetName()))
        elif model == 27:
            # gaussian model with optional mean passed as auxModel
            mean = ws.factory('mean_%s[0.,1000.]' % idString)
            sigma = ws.factory('sigma_%s[0.,500.]' % idString)
            if auxModel:
                mean.setVal(auxModel)
                mean.setError(auxModel*0.15)
                sigma.setVal(auxModel*0.15)
                sigma.setError(auxModel*0.15*0.2)
            ws.factory('RooGaussian::%s(%s,mean_%s,sigma_%s)' % \
                       (pdfName, var, idString, idString))
        elif model == 28:
            # QCD inspired model with a erf turnon
            pdfErf = self.analyticPdf(ws, var, 25, '%s_turnon' % pdfName,
                                      idString)
            pdfPower = self.analyticPdf(ws, var, 18, '%s_power' % pdfName,
                                        idString)
            ws.factory('PROD::%s(%s,%s)' % (pdfName, pdfErf.GetName(),
                                            pdfPower.GetName()))
        elif model == 29:
            # QCD inspired model with a erf turnon + gaussian
            pdfPower = self.analyticPdf(ws, var, 28, '%s_tail' % pdfName,
                                        idString)
            pdfGaus = self.analyticPdf(ws, var, 27, '%s_wiggle' % pdfName,
                                       idString, 150.)
            ws.factory('SUM::%s(f_%s[0.1, -1., 1.]*%s, %s)' % \
                       (pdfName, idString, pdfGaus.GetName(),
                        pdfPower.GetName()))
        elif model == 30:
            # 2 gaussian + erf*exp
            pdfCore = self.analyticPdf(ws, var, 27, '%s_core' % pdfName,
                                       '%s_core' % idString, 84.)
            sigma = ws.factory('prod::sigma_%s_wide(sigma_%s_core, wider_%s[4.559, 1., 10.])' % \
                               (idString,idString,idString))
            ws.var('wider_%s' % idString).setConstant(True)
            pdfWide = ws.factory('RooGaussian::%s_wide(%s,mean_%s_core,%s)' % \
                                 (pdfName, var, idString, sigma.GetName()))
            pdfTail = self.analyticPdf(ws, var, 8, '%s_tail' % pdfName,
                                       idString)
            fcore = ws.factory('f_%s_core[0.3, 0., 1.]' % idString)
            fwide = ws.factory('prod::f_%s_wide(%s,0.7787)' % \
                               (idString, fcore.GetName()))
            ws.factory("SUM::%s(%s*%s," % \
                       (pdfName, fcore.GetName(), pdfCore.GetName()) + \
                       '%s*%s,' % \
                       (fwide.GetName(), pdfWide.GetName()) +\
                       "%s)" % (pdfTail.GetName())
                       )
        elif model == 31:
            # diboson specific model for the resonant shape
            ws.factory("prod::sigma_%s_W" % (idString) + \
                       "(mean_%s_W[80.3, 50., 100.]," % (idString) + \
                       "resolution_%s[0.1, 0., 5.])" % (idString))
            ws.factory('sum::mean_%s_Z' % (idString) + \
                       "(mean_%s_W, 10.8026)" % (idString))
            ws.factory('prod::sigma_%s_Z(mean_%s_Z,resolution_%s)' % \
                       (idString, idString, idString))
            ws.factory("RooGaussian::%s_W" % pdfName + \
                       "(%s, mean_%s_W, sigma_%s_W)" % (var, idString,
                                                        idString)
                       )
            ws.factory("RooGaussian::%s_Z" % pdfName + \
                       "(%s, mean_%s_Z, sigma_%s_Z)" % (var, idString,
                                                        idString)
                       )
            self.analyticPdf(ws, var, 0, '%s_tail' % pdfName, idString)
            ws.factory("SUM::%s(f_W_%s[0.4,0.,1.]*%s_W,f_Z_%s[0.1,0.,1.]*%s_Z,%s_tail)" % \
                       (pdfName, idString, pdfName, idString, pdfName, pdfName))
        elif model == 32:
            # sum of exponentials
            factoryString = 'SUM::%s(' % (pdfName)
            for i in range(0, auxModel):
                pdf = ws.factory(
                    'RooExponential::%s_%i(%s,c_%s_%i[0.012,-10,10])' % \
                    (pdfName, i, var, idString, i))
                f = ws.factory('f_%i[%.3f,0.,1.]' % (i, 1./auxModel))
                if i < (auxModel-1):
                    factoryString += f.GetName() + '*'
                factoryString += pdf.GetName() + ','
            factoryString = factoryString[:-1] + ')'
            print factoryString
            ws.factory(factoryString)
        else:
            # this is what will be returned if there isn't a model implemented
            # for a given model code.
            self.analyticPdf(ws, var, 4, pdfName, idString)

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
