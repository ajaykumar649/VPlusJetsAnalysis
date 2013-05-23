def clipCurve(theCurve):
    if theCurve.GetX()[0] == theCurve.GetX()[1]:
        theCurve.RemovePoint(0)
    if theCurve.GetX()[theCurve.GetN()-1] == theCurve.GetX()[theCurve.GetN()-2]:
        theCurve.RemovePoint(theCurve.GetN()-1)
    return theCurve

def addPlots(plots):
    from ROOT import RooCurve, RooHist, TLine, TLegend, RooPlot, RooAbsData, \
         SetOwnership, TGraphErrors
    #print plots
    outplot = plots[0].emptyClone(plots[0].GetName())
    newMax = 0.
    for item in range(0, int(plots[0].numItems())):
        itemName = plots[0].nameOf(item)
        firstItem = plots[0].getObject(item)
        if (type(firstItem) == RooCurve):
            fullCurve = clipCurve(firstItem)
            for plot in range(1, len(plots)):
                nextCurve = clipCurve(plots[plot].getCurve(itemName))
                fullCurve = RooCurve(fullCurve.GetName(), fullCurve.GetTitle(),
                                     fullCurve, nextCurve)
            fullCurve.addPoint(fullCurve.GetX()[fullCurve.GetN()-1], 0)
            fullCurve.addPoint(fullCurve.GetX()[0], 0)
            fullCurve.SetLineColor(firstItem.GetLineColor());
            fullCurve.SetLineStyle(firstItem.GetLineStyle());
            fullCurve.SetFillColor(firstItem.GetFillColor());
            fullCurve.SetFillStyle(firstItem.GetFillStyle());
            outplot.addPlotable(fullCurve,
                                plots[0].getDrawOptions(itemName).Data())
            SetOwnership(fullCurve, False)

        if (type(firstItem) == RooHist):
            fullHist = firstItem
            for plot in range(1, len(plots)):
                nextHist = plots[plot].getHist(itemName)
                fullHist = addHists(fullHist, nextHist)
            fullHist.SetName(itemName)
            fullHist.SetTitle(firstItem.GetTitle())
            outplot.addPlotable(fullHist,
                                plots[0].getDrawOptions(itemName).Data())
            SetOwnership(fullHist, False)

        if (type(firstItem) == TGraphErrors):
            fullErrors = firstItem
            for plot in range(1, len(plots)):
                nextErrors = plots[plot].findObject(itemName)
                fullErrors = addErrors(fullErrors, nextErrors)
            fullErrors.SetName(itemName)
            fullErrors.SetTitle(firstItem.GetTitle())
            outplot.addObject(fullErrors,
                              plots[0].getDrawOptions(itemName).Data())
            SetOwnership(fullErrors, False)

        if (type(firstItem) == TLine):
            newLine = TLine(firstItem)
            newLine.SetY2(outplot.GetMaximum())
            SetOwnership(newLine, False)
            outplot.addObject(newLine)
            pass
            
        if (type(firstItem) == TLegend):
            newLeg = TLegend(firstItem)
            newLeg.SetY1NDC(0.92 - \
                            0.04*newLeg.GetListOfPrimitives().GetSize() - \
                            0.02)
            newLeg.SetY1(newLeg.GetY1NDC())
            SetOwnership(newLeg, False)
            outplot.addObject(newLeg)

    for plot in plots:
        newMax += plot.GetMaximum()

    outplot.SetMaximum(outplot.GetMaximum()*1.3)
    outplot.GetYaxis().SetTitle("Events / GeV")
##     outplot.SetMaximum(newMax)
##         outplot.Print("v")

    return outplot

def addHists(hist1, hist2):
    from ROOT import RooHist
    from math import sqrt

    newHist = RooHist(hist1)

    for i in range(0, newHist.GetN()):
        newHist.SetPoint(i, newHist.GetX()[i],
                         hist1.GetY()[i]+hist2.GetY()[i])
        newHist.SetPointError(i, hist1.GetErrorXlow(i), hist1.GetErrorXhigh(i),
                              sqrt(hist1.GetErrorYlow(i)**2 + \
                                   hist2.GetErrorYlow(i)**2),
                              sqrt(hist1.GetErrorYhigh(i)**2 + \
                                   hist2.GetErrorYhigh(i)**2)
                              )
    return newHist

def addErrors(err1, err2):
    from ROOT import TGraphErrors
    from math import sqrt

    newErrs = TGraphErrors(err1)

    for i in range(0, newErrs.GetN()):
        newErrs.SetPoint(i, newErrs.GetX()[i],
                         err1.GetY()[i]+err2.GetY()[i])
        newErrs.SetPointError(i, err1.GetErrorX(i),
                              sqrt(err1.GetErrorY(i)**2 + \
                                   err2.GetErrorY(i)**2)
                              )
    return newErrs
        
    
if __name__ == "__main__":
    from optparse import OptionParser

    parser = OptionParser()
    parser.add_option('-b', action='store_true', dest='noX', default=False,
                      help='no X11 windows')
    parser.add_option('-o', '--output', dest='output',
                      default='combinedPlots.root',
                      help='output file name')
    parser.add_option('-l', '--lumi', dest='lumi', type='float', default=5020.,
                      help='luminosity in inverse picobarns')
    parser.add_option('--prefix', dest='prefix', default='Mjj',
                      help='name for plots')
    (opts, args) = parser.parse_args()

    import pyroot_logon

    from ROOT import TFile, TCanvas, gROOT, RooPlot, gPad, TLine, SetOwnership
    import plotMjjFit

    plots = {'%s_stacked' % (opts.prefix): [],
             '%s_subtracted' % (opts.prefix): []}
    #print plots
    cans = []

    for f in args:
        inF = TFile.Open(f)
        gROOT.cd()
        for plotName in plots:
            thePlot = inF.Get(plotName)
            if thePlot:
                plots[plotName].append(thePlot.Clone())
        inF.Close()

    print plots

    cplots = []
    outFile = TFile(opts.output, 'recreate')
    for plot in plots:
        outPlot = addPlots(plots[plot])

        can = TCanvas()
        cans.append(can)
        cplots.append(outPlot)
        outPlot.Draw()
        pyroot_logon.cmsLabel(can, opts.lumi/1000.)
        # gPad.WaitPrimitive()

        outPlot.Write()

        if (plot == '%s_subtracted' % (opts.prefix)):
            outPlot.SetMaximum(outPlot.GetMaximum()*1.3)
            outPlot.SetMinimum(outPlot.GetMinimum()*1.1)
            if outPlot.findObject('ErrBand'):
                corrPull = plotMjjFit.sub2pull(outPlot.getHist('theData'),
                                               outPlot.findObject('ErrBand'))
            else:
                corrPull = plotMjjFit.sub2pull(outPlot.getHist('theData'),
                                               outPlot.findObject('h_dibosonPdf'))
            
            corrPull.SetMinimum(-5.)
            corrPull.SetMaximum(5.)
            corrPull.GetXaxis().SetTitle('m_{jj} (GeV)')
            corrPull.GetYaxis().SetTitle('pull (#sigma)')
            corrPull.GetXaxis().Set(corrPull.GetN(),
                                    outPlot.GetXaxis().GetXmin(),
                                    outPlot.GetXaxis().GetXmax())
            canpf = TCanvas()
            canpf.SetGridy()
            cans.append(canpf)
            corrPull.Draw('ap0')
            for item in range(0, int(outPlot.numItems())):
                firstItem = outPlot.getObject(item)
                if (type(firstItem) == TLine):
                    newLine = TLine(firstItem)
                    newLine.SetY1(4.)
                    newLine.SetY2(-4.)
                    newLine.Draw()
                    SetOwnership(newLine, False)
            pyroot_logon.cmsLabel(canpf, opts.lumi/1000.)
            gPad.Update()
            canpf.Print('%s_%s_combined.png' % (opts.prefix, 'Pull'))
            canpf.Print('%s_%s_combined.pdf' % (opts.prefix, 'Pull'))
            corrPull.Write()

        gPad.Update()
        can.Print('%s_combined.png' % (plot))
        can.Print('%s_combined.pdf' % (plot))

    outFile.Close()
