from RooWjj2DFitterUtils import Wjj2DFitterUtils
from ROOT import RooWorkspace, RooFormulaVar, RooAddPdf, RooAbsReal, RooFit, RooCmdArg, \
    RooBinning, RooAbsData, RooHist, RooArgList, RooArgSet, TFile, RooDataHist,\
    kRed, kBlue, kGreen, kYellow, kGray, kAzure, kCyan, gROOT, TLegend, TTree, \
    TBox, kBlack
from math import sqrt
from array import array
import sys

colorwheel = [ kAzure+8,
               kRed,
               kGreen+2,
               kGray+1,
               kYellow,
               kCyan+2
               ]
class Wjj2DFitter:

    def __init__ (self, pars):
        self.pars = pars
        self.ws = RooWorkspace('wjj2dfitter')
        self.utils = Wjj2DFitterUtils(self.pars)
        self.useImportPars = False

        self.rangeString = None
        obs = []
        for v in self.pars.var:
            
            try:
                vName = self.pars.varNames[v]
            except AttributeError:
                vName = v

            obs.append(vName)
            var1 = self.ws.factory('%s[%f,%f]' % (vName, 
                                                  self.pars.varRanges[v][1], 
                                                  self.pars.varRanges[v][2])
                                   )
            var1.setUnit('GeV')
            try:
                var1.SetTitle(self.pars.varTitles[v])
            except AttributeError:
                var1.SetTitle('m_{jj}')
            var1.setPlotLabel(var1.GetTitle())
            if len(self.pars.varRanges[v][3]) > 1:
                vbinning = RooBinning(len(self.pars.varRanges[v][3]) - 1, 
                                   array('d', self.pars.varRanges[v][3]),
                                   '%sBinning' % vName)
                var1.setBinning(vbinning)
            else:
                var1.setBins(self.pars.varRanges[v][0])
            var1.Print()
            if v in self.pars.exclude:
                var1.setRange('signalRegion', self.pars.exclude[v][0],
                              self.pars.exclude[v][1])
                var1.setRange('lowSideband', var1.getMin(), 
                              self.pars.exclude[v][0])
                var1.setRange('highSideband', self.pars.exclude[v][1],
                              var1.getMax())
                self.rangeString = 'lowSideband,highSideband'
        self.ws.defineSet('obsSet', ','.join(obs))

    def loadDataFromWorkspace(self, other, cut = None):
        #pull unbinned data from other workspace
        unbinnedData = other.data('data_unbinned')
        if not unbinnedData:
            unbinnedData = other.data('data_obs')

        if cut:
            unbinnedData = unbinnedData.reduce(cut)

        unbinnedData.Print()
        if self.pars.binData:
            #bin and import data
            unbinnedData.SetName('data_unbinned')
            getattr(self.ws, 'import')(unbinnedData)
            data = RooDataHist('data_obs', 'data_obs', other.set('obsSet'), 
                               unbinnedData)
            getattr(self.ws, 'import')(data)
        else:
            #just import data
            unbinnedData.SetName('data_obs')
            getattr(self.ws, 'import')(unbinnedData)

    def loadHistogramsFromWorkspace(self, other):
        #pull RooHist pdfs from other workspace
        pdfs = other.allPdfs()
        pdfIter = pdfs.createIterator()
        pdf = pdfIter.Next()
        while pdf:
            if pdf.IsA().InheritsFrom('RooHistPdf'):
                print 'importing',pdf.GetName(),'from old workspace'
                getattr(self.ws, 'import')(pdf)
            pdf = pdfIter.Next()

    def loadWorkspaceFromFile(self, filename, wsname = 'w', 
                              getFloatPars = True):
        print 'loading data workspace %s from file %s' % (wsname, filename)
        fin = TFile.Open(filename)
        if not fin:
            print 'failed to open the file',filename
            import os
            print 'cwd:',os.getcwd()
            print 'access of',filename,os.access(filename, os.R_OK)
            print 'list of root files in cwd'
            for f in os.listdir(os.getcwd()):
                if f[-5:] == '.root':
                    print f,len(f),len(filename)
            fin = TFile.Open(os.getcwd() + '/' + filename)
            assert(fin)

        other = fin.Get(wsname)

        #pull unbinned data from other workspace
        self.loadDataFromWorkspace(other)

        #pull in histogram pdfs to save time
        self.loadHistogramsFromWorkspace(other)

        if getFloatPars and other.loadSnapshot('fitPars'):
            self.useImportPars = True
            self.ws.saveSnapshot('importParams', other.set('floatingParams'), 
                                 True)

        # self.ws.Print()
    
    # put together a fitting model and return the pdf
    def makeFitter(self):
        if self.ws.pdf('total'):
            return self.ws.pdf('total')

        compPdfs = []
        for component in self.pars.backgrounds:
            # print 'getting compModels'
            compModels = getattr(self.pars, '%sModels' % component)
            # print 'compModels = %s' % compModels
            compFiles = getattr(self.pars, '%sFiles' % component)
            compPdf = self.makeComponentPdf(component, compFiles, 
                                            compModels)
                
            norm = self.ws.factory('prod::f_%s_norm' % component + \
                                       '(n_%s[0.,1e6],' % component + \
                                       '%s_nrm[1.,-0.5,5.])' % component)
            self.ws.var('n_%s' % component).setConstant(True)
            if hasattr(self, '%sExpected' % component):
                self.ws.var('n_%s' % component).setVal(
                    getattr(self, '%sExpected' % component))
            compPdfs.append(
                self.ws.factory('RooExtendPdf::%s_extended(%s,%s)' % \
                                    (compPdf.GetName(), 
                                     compPdf.GetName(),
                                     norm.GetName())
                                )
                )
                                    
        self.ws.factory('r_signal[0., -200., 200.]')
        self.ws.var('r_signal').setConstant(False)

        try:
            obs = [ self.pars.varNames[x] for x in self.pars.var ]
        except AttributeError:
            obs = self.pars.var

        for component in self.pars.signals:
            compFile = getattr(self.pars, '%sFiles' % component)
            compModels = getattr(self.pars, '%sModels' % component)
            compPdf = self.makeComponentPdf(component, compFiles,
                                            compModels)
            norm = self.ws.factory(
                "prod::f_%s_norm(n_%s[0., 1e6],r_signal)" % \
                    (component, component)
                )
            self.ws.var('n_%s' % component).setConstant(True)
            if hasattr(self, '%sExpected' % component):
                self.ws.var('n_%s' % component).setVal(
                    getattr(self, '%sExpected' % component))
            pdf = self.ws.factory('RooExtendPdf::%s_extended(%s,%s)' % \
                                      (compPdf.GetName(), 
                                       compPdf.GetName(),
                                       norm.GetName())
                                  )
            
            if (hasattr(self.pars, '%sInterference' % component)) and \
                    getattr(self.pars, '%sInterference' % component):
                getattr(self.ws, 'import') \
                    (pdf, RooFit.RenameAllNodes('interf_%sUp' % component),
                     RooFit.RenameAllVariablesExcept('interf_%sUp' % component,
                                                     ','.join(obs)),
                     RooFit.Silence()
                     )
                getattr(self.ws, 'import') \
                    (pdf, RooFit.RenameAllNodes('interf_%sDown' % component),
                     RooFit.RenameAllVariablesExcept('interf_%sDown'%component,
                                                     ','.join(obs)),
                     RooFit.Silence()
                     )
            if self.pars.includeSignal:
                compPdfs.append(pdf)

        #print compPdfs
        
        prodList = [ '%s' % (pdf.GetName()) \
                         for (idx, pdf) in enumerate(compPdfs) ]
        comps = RooArgList(self.ws.argSet(','.join(prodList)))
        getattr(self.ws, 'import')(RooAddPdf('total', 'total', comps))

        return self.ws.pdf('total')

    # define the constraints on the yields, etc that will be part of the fit.
    def makeConstraints(self):

        if self.ws.set('constraintSet'):
            return self.ws.set('constraintSet')

        constraints = []
        constrainedParameters = []
        for constraint in self.pars.yieldConstraints:
            theYield = self.ws.var('%s_nrm' % constraint)
            if not theYield.isConstant():
                self.ws.factory('RooGaussian::%s_const(%s, 1.0, %f)' % \
                                    (constraint, theYield.GetName(),
                                     self.pars.yieldConstraints[constraint])
                                )
                constraints.append('%s_const' % constraint)
                constrainedParameters.append(theYield.GetName())

        if hasattr(self.pars, 'constrainShapes'):
            for component in self.pars.constrainShapes:
                pc = self.ws.pdf(component).getParameters(self.ws.set('obsSet'))
                parIter = pc.createIterator()
                par = parIter.Next()
                while par:
                    if not par.isConstant():
                        theConst = self.ws.factory('RooGaussian::%s_const' % \
                                                       (par.GetName()) + \
                                                       '(%s, %f, %f)' % \
                                                       (par.GetName(),
                                                        par.getVal(),
                                                        par.getError())
                                                   )
                        constraints.append(theConst.GetName())
                        constrainedParameters.append(par.GetName())
                    par = parIter.Next()
                pc.IsA().Destructor(pc)

        self.ws.defineSet('constraintSet', ','.join(constraints))
        self.ws.defineSet('constrainedSet', ','.join(constrainedParameters))

        return self.ws.set('constraintSet')

    # fit the data using the pdf
    def fit(self, keepParameterValues = False):
        print 'construct fit pdf ...'
        fitter = self.makeFitter()

        print 'load data ...'
        data = self.loadData()

        self.resetYields()

        constraintSet = self.makeConstraints()

        if not keepParameterValues:
            self.readParametersFromFile()

        self.resetYields()
        # print constraints, self.pars.yieldConstraints
        print '\nfit constraints'
        constIter = constraintSet.createIterator()
        constraint = constIter.Next()
        constraints = []
        while constraint:
            constraint.Print()
            constraints.append(constraint.GetName())
            constraint = constIter.Next()
            
        constraintCmd = RooCmdArg.none()
        if constraintSet.getSize() > 0:
            constraints.append(fitter.GetName())
            fitter = self.ws.pdf('totalFit_const')
            if not fitter:
                fitter = self.ws.factory('PROD::totalFit_const(%s)' % \
                                             (','.join(constraints))
                                         )
            constraintCmd = RooFit.Constrained()
            # constraintCmd = RooFit.ExternalConstraints(self.ws.set('constraintSet'))

        if self.useImportPars:
            self.ws.loadSnapshot('importParams')
        self.ws.Print()

        # for constraint in pars.constraints:
        #     self.ws.pdf(constraint).Print()
        # print

        rangeCmd = RooCmdArg.none()
        if self.rangeString:
            rangeCmd = RooFit.Range(self.rangeString)

        print 'fitting ...'
        fr = fitter.fitTo(data, RooFit.Save(True),
                          RooFit.Extended(True),
                          RooFit.Minos(False),
                          RooFit.PrintEvalErrors(-1),
                          RooFit.Warnings(False),
                          constraintCmd,
                          rangeCmd)
        fr.Print()

        

        return fr

    # determine the fitting model for each component and return them
    def makeComponentPdf(self, component, files, models):
        print 'making ComponentPdf %s' % component
        # print 'models = %s' % models
        # print 'files = %s' % files
        if (models[0] == -1):
            thePdf = self.makeComponentHistPdf(component, files)
        elif (models[0] == -2):
            thePdf = self.makeMorphingPdf(component)
        else:
            thePdf = self.makeComponentAnalyticPdf(component, models)
        return thePdf
            
    #create a simple 2D histogram pdf
    def makeComponentHistPdf(self, component, files):
        if self.ws.pdf(component):
            return self.ws.pdf(component)

        compHist = self.utils.newEmptyHist('hist%s' % component)
        sumYields = 0.
        sumxsec = 0.
        sumExpected = 0.
        for (idx,fset) in enumerate(files):
            if hasattr(self.pars, '%scuts' % component):
                cutOverride = getattr(self.pars, '%scuts' % component)
            else:
                cutOverride = None
            filename = fset[0]
            tmpHist = self.utils.File2Hist(filename, 
                                           'hist%s_%i' % (component, idx),
                                           False,cutOverride,False,True,0)
            sumYields += tmpHist.Integral()
            sumxsec += fset[2]
            compHist.Add(tmpHist, self.pars.integratedLumi*fset[2]/fset[1])
            sumExpected += tmpHist.Integral()*fset[2]* \
                self.pars.integratedLumi/fset[1]
            print filename,'acc x eff: %.3g' % (tmpHist.Integral()/fset[1])
            print filename,'N_expected: %.1f' % \
                (tmpHist.Integral()*fset[2]*self.pars.integratedLumi/fset[1])
            #tmpHist.Print()

        #compHist.Print()
        print '%s acc x eff: %.3g' % \
            (component, sumExpected/sumxsec/self.pars.integratedLumi)
        print 'Number of expected %s events: %.1f' % (component, sumExpected)
        setattr(self, '%sExpected' % component, sumExpected)

        return self.utils.Hist2Pdf(compHist, component, 
                                   self.ws, self.pars.order)

    # create a pdf using the "template morphing" technique
    def makeMorphingPdf(self, component):
        if self.ws.pdf(component):
            return self.ws.pdf(component)
        
        filesNom = getattr(self.pars, '%s_NomFiles' % component)
        modelsNom = getattr(self.pars, '%s_NomModels' % component)
        filesMU = getattr(self.pars, '%s_MUFiles' % component)
        modelsMU = getattr(self.pars, '%s_MUModels' % component)
        filesMD = getattr(self.pars, '%s_MDFiles' % component)
        modelsMD = getattr(self.pars, '%s_MDModels' % component)
        filesSU = getattr(self.pars, '%s_SUFiles' % component)
        modelsSU = getattr(self.pars, '%s_SUModels' % component)
        filesSD = getattr(self.pars, '%s_SDFiles' % component)
        modelsSD = getattr(self.pars, '%s_SDModels' % component)

        # Adds five (sub)components for the component with suffixes Nom, MU, MD, SU, SD
        NomPdf = self.makeComponentPdf('%s_Nom' % component, filesNom, modelsNom)
        if hasattr(self, '%s_NomExpected' % component):
            setattr(self, '%sExpected' % component,
                    getattr(self, '%s_NomExpected' % component))
        MUPdf = self.makeComponentPdf('%s_MU' % component, filesMU, modelsMU)
        MDPdf = self.makeComponentPdf('%s_MD' % component, filesMD, modelsMD)
        SUPdf = self.makeComponentPdf('%s_SU' % component, filesSU, modelsSU)
        SDPdf = self.makeComponentPdf('%s_SD' % component, filesSD, modelsSD)

        fMU_comp = self.ws.factory("fMU_%s[0., -1., 1.]" % component)
        fSU_comp = self.ws.factory("fSU_%s[0., -1., 1.]" % component)

        fMU = RooFormulaVar("f_fMU_%s" % component, "1.0*@0*(@0 >= 0.)", 
                            RooArgList( fMU_comp ) )
        fMD = RooFormulaVar("f_fMD_%s" % component, "-1.0*@0*(@0 < 0.)", 
                            RooArgList( fMU_comp ) )
        fSU = RooFormulaVar("f_fSU_%s" % component, "@0*(@0 >= 0.)", 
                            RooArgList( fSU_comp ) )
        fSD = RooFormulaVar("f_fSD_%s" % component, "@0*(-1)*(@0 < 0.)", 
                            RooArgList( fSU_comp ) )
        fNom = RooFormulaVar("f_fNom_%s" % component, "(1.-abs(@0)-abs(@1))", 
                             RooArgList(fMU_comp,fSU_comp) )
        morphPdf = RooAddPdf(component,component, 
                             RooArgList(MUPdf,MDPdf,SUPdf,SDPdf,NomPdf),
                             RooArgList(fMU, fMD, fSU, fSD, fNom))
        morphPdf.SetName(component)
        getattr(self.ws, 'import')(morphPdf)
        return self.ws.pdf(component)

    # create a pdf using an analytic function.
    def makeComponentAnalyticPdf(self, component, models):
        if self.ws.pdf(component):
            return self.ws.pdf(component)

        pdfList = []
        for (idx,model) in enumerate(models):
            var = self.pars.var[idx]
            try:
                vName = self.pars.varNames[var]
            except AttributeError:
                vName = var

            if hasattr(self.pars, '%sAuxModels' % component):
                auxModel = getattr(self.pars, '%sAuxModels' % component)[idx]
            else:
                auxModel = None
            pdfList.append(self.utils.analyticPdf(self.ws, vName, model, 
                                                  '%s_%s'%(component,vName), 
                                                  '%s_%s'%(component,vName),
                                                  auxModel
                                                  )
                           )
        
        pdfListNames = [ pdf.GetName() for pdf in pdfList ]
        if len(pdfList) > 1:
            self.ws.factory('PROD::%s(%s)' % \
                                (component, ','.join(pdfListNames)))
        else:
            pdfList[0].SetName(component)
                        
        return self.ws.pdf(component)

    def loadData(self, weight = False):
        if self.ws.data('data_obs'):
            return self.ws.data('data_obs')

        unbinnedName = 'data_obs'
        if self.pars.binData:
            unbinnedName = 'data_unbinned'
        data = self.utils.File2Dataset(self.pars.DataFile, unbinnedName, 
                                       self.ws, weighted = weight)
        if self.pars.binData:
            data = RooDataHist('data_obs', 'data_obs', self.ws.set('obsSet'), 
                               data)
            getattr(self.ws, 'import')(data)
            data = self.ws.data('data_obs')

        return data

    def stackedPlot(self, var, logy = False, pdfName = None):
        if not pdfName:
            pdfName = 'total'

        xvar = self.ws.var(var)
        xvar.setRange('plotRange', xvar.getMin(), xvar.getMax())

        sframe = xvar.frame()
        sframe.SetName("%s_stacked" % var)
        pdf = self.ws.pdf(pdfName)

        if isinstance(pdf, RooAddPdf):
            compList = RooArgList(pdf.pdfList())
        else:
            compList = None

        data = self.ws.data('data_obs')
        nexp = pdf.expectedEvents(self.ws.set('obsSet'))

        print pdf.GetName(),'expected: %.0f' % (nexp)
        print 'data events: %.0f' % (data.sumEntries())

        if nexp < 1:
            nexpt = data.sumEntries()
        theComponents = [] 
        if self.pars.includeSignal:
            theComponents += self.pars.signals
        theComponents += self.pars.backgrounds
        data.plotOn(sframe, RooFit.Invisible())
        # dataHist = RooAbsData.createHistogram(data,'dataHist_%s' % var, xvar,
        #                                       RooFit.Binning('%sBinning' % var))
        # #dataHist.Scale(1., 'width')
        # invData = RooHist(dataHist, 1., 1, RooAbsData.SumW2, 1.0, False)
        # #invData.Print('v')
        # sframe.addPlotable(invData, 'pe', True, True)
        for (idx,component) in enumerate(theComponents):
            print 'plotting',component,'...',
            if hasattr(self.pars, '%sPlotting' % (component)):
                plotCharacteristics = getattr(self.pars, '%sPlotting' % \
                                                  (component))
            else:
                plotCharacteristics = {'color' : colorwheel[idx%6],
                                       'title' : component }

            compCmd = RooCmdArg.none()
            if compList:
                compSet = RooArgSet(compList)
                if compSet.getSize() > 0:
                    compCmd = RooFit.Components(compSet)
                removals = compList.selectByName('%s*' % component)
                compList.remove(removals)

            print 'events', self.ws.function('f_%s_norm' % component).getVal()
            sys.stdout.flush()
            if abs(self.ws.function('f_%s_norm' % component).getVal()) >= 1.:
                pdf.plotOn(sframe, #RooFit.ProjWData(data),
                           RooFit.DrawOption('LF'), RooFit.FillStyle(1001),
                           RooFit.FillColor(plotCharacteristics['color']),
                           RooFit.LineColor(plotCharacteristics['color']),
                           RooFit.VLines(),
                           RooFit.Range('plotRange'),
                           RooFit.NormRange('plotRange'),
                           RooFit.Normalization(nexp, RooAbsReal.NumEvent),
                           compCmd
                           )
                tmpCurve = sframe.getCurve()
                tmpCurve.SetName(component)
                tmpCurve.SetTitle(plotCharacteristics['title'])
                if 'visible' in plotCharacteristics:
                    sframe.setInvisible(component, 
                                        plotCharacteristics['visible'])

        data.plotOn(sframe, RooFit.Name('theData'))
        sframe.getHist('theData').SetTitle('data')
        # theData = RooHist(dataHist, 1., 1, RooAbsData.SumW2, 1.0, True)
        # theData.SetName('theData')
        # theData.SetTitle('data')
        # sframe.addPlotable(theData, 'pe')

        if (logy):
            sframe.SetMinimum(0.01)
            sframe.SetMaximum(1.0e6)
        else:
            sframe.SetMaximum(sframe.GetMaximum()*1.25)
            pass

        excluded = (var in self.pars.exclude)
        bname = var
        if not excluded:
            for v in self.pars.exclude:
                if self.pars.varNames[v] == var:
                    excluded = True
                    bname = v
        if self.pars.blind and excluded:
            blinder = TBox(self.pars.exclude[bname][0], sframe.GetMinimum(),
                           self.pars.exclude[bname][1], sframe.GetMaximum())
            # blinder.SetName('blinder')
            # blinder.SetTitle('signal region')
            blinder.SetFillColor(kBlack)
            blinder.SetFillStyle(1001)
            sframe.addObject(blinder)
        elif self.pars.blind:
            print "blind but can't find exclusion region for", var
            print 'excluded',excluded,self.pars.exclude
            print 'hiding data points'
            sframe.setInvisible('theData', True)

        #sframe.GetYaxis().SetTitle('Events / GeV')
        # dataHist.IsA().Destructor(dataHist)
        print

        return sframe

    def readParametersFromFile(self, fname=None):
        if (not fname):
            fname = self.pars.initialParametersFile
        
        if isinstance(fname, str):
            flist = [ fname ]
        else:
            flist = fname

        for tmpName in flist:
            if len(tmpName) > 0:
                print 'loading parameters from file',tmpName
                self.ws.allVars().readFromFile(tmpName)

    def expectedFromPars(self):
        components = self.pars.signals + self.pars.backgrounds
        for component in components:
            theYield = self.ws.var('n_%s' % component)
            setattr(self, '%sExpected' % component, theYield.getVal())

    def resetYields(self):
        if self.ws.data('data_obs'):
            Ndata = self.ws.data('data_obs').sumEntries()
        else:
            Ndata = 10000.
        print 'resetting yields...'
        components = self.pars.signals + self.pars.backgrounds
        for component in components:
            theYield = self.ws.var('n_%s' % component)
            theNorm = self.ws.var('%s_nrm' % component)
            fracofdata = getattr(self.pars, '%sFracOfData' % component)
            if (fracofdata >= 0.):
                print 'explicitly setting ', component,' yield to be', fracofdata,' of data'
                theYield.setVal(fracofdata*Ndata)
            elif hasattr(self, '%sExpected' % component):
                theYield.setVal(getattr(self, '%sExpected' % component))
            else:
                print 'no expected value for',component
                theYield.setVal(Ndata/len(components))
            if theNorm and not theNorm.isConstant():
                theNorm.setVal(1.0)
            if component in self.pars.yieldConstraints:
                theYield.setError(theYield.getVal() * \
                                      self.pars.yieldConstraints[component])
                if theNorm:
                    theNorm.setError(self.pars.yieldConstraints[component])
            else:
                theYield.setError(sqrt(theYield.getVal()))
            theYield.Print()

    def generateToyMCSet(self,var,inputPdf,outFileName,NEvts):
        fMC = TFile(outFileName, "RECREATE");
#        thevar = self.ws.var(var);
        print 'thevar='
        print var
#        print thevar
        print '...'
#        varList = RooArgList()
#        varList.add(self.ws.var(var))
        toymc = inputPdf.generate(RooArgSet(self.ws.var(var)),NEvts);
        tMC = toymc.tree();
        fMC.cd();
        tMC.Write();
        fMC.Close();

    


    def legend4Plot(plot, left = False):
        if left:
            theLeg = TLegend(0.2, 0.62, 0.55, 0.92, "", "NDC")
        else:
            theLeg = TLegend(0.55, 0.62, 0.92, 0.92, "", "NDC")
        theLeg.SetName('theLegend')

        theLeg.SetBorderSize(0)
        theLeg.SetLineColor(0)
        theLeg.SetFillColor(0)
        theLeg.SetFillStyle(0)
        theLeg.SetLineWidth(0)
        theLeg.SetLineStyle(0)
        theLeg.SetTextFont(42)
        theLeg.SetTextSize(.045)

        entryCnt = 0
        for obj in range(0, int(plot.numItems())):
            objName = plot.nameOf(obj)
            if (not plot.getInvisible(objName)):
                theObj = plot.getObject(obj)
                objTitle = theObj.GetTitle()
                if len(objTitle) < 1:
                    objTitle = objName
                dopts = plot.getDrawOptions(objName).Data()
                # print 'obj:',theObj,'title:',objTitle,'opts:',dopts,'type:',type(dopts)
                if theObj.IsA().InheritsFrom('TNamed'):
                    theLeg.AddEntry(theObj, objTitle, dopts)
                    entryCnt += 1
        theLeg.SetY1NDC(0.9 - 0.05*entryCnt - 0.005)
        theLeg.SetY1(theLeg.GetY1NDC())
        return theLeg

    legend4Plot = staticmethod(legend4Plot)


if __name__ == '__main__':
    import RooWjj2DFitterPars

    pars = RooWjj2DFitterPars.Wjj2DFitterPars()
    pars.backgrounds = ['WpJ']
    pars.signals = []
    pars.WpJFiles = [('', 0, 0)]
    pars.WpJModels = [20, 0]
    
    fitter = Wjj2DFitter(pars)
    fitter.makeFitter()
    fitter.loadData()
    fitter.resetYields()

    fitter.ws.var('turnOn_WpJ_Mass2j_PFCor_0').setVal(60.)
    fitter.ws.var('turnOn_WpJ_Mass2j_PFCor_0').setError(10.)
    fitter.ws.var('width_WpJ_Mass2j_PFCor_0').setVal(20.)
    fitter.ws.var('width_WpJ_Mass2j_PFCor_0').setError(2.)
    fitter.ws.var('c_WpJ_Mass2j_PFCor_1').setVal(-0.015)
    fitter.ws.var('c_WpJ_Mass2j_PFCor_1').setError(0.01)
    fitter.ws.var('c_WpJ_fit_mlvjj').setVal(-0.015)
    fitter.ws.var('c_WpJ_fit_mlvjj').setError(0.01)

    #fitter.fit()
    plot1 = fitter.stackedPlot(pars.var[0])
    plot2 = fitter.stackedPlot(pars.var[1])

    plot1.Draw()

    fitter.ws.Print()
