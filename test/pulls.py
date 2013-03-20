def createPull(theData, curve, curveUp = None, curveDown = None):
    from ROOT import TGraphErrors, TMath

    pullGraph = TGraphErrors(theData.GetN())

    for datapt in range(0, theData.GetN()):
        binmin = theData.GetX()[datapt] - theData.GetEXlow()[datapt]
        binmax = theData.GetX()[datapt] + theData.GetEXhigh()[datapt]

        binN = theData.GetY()[datapt]*(binmax-binmin)

        curveN = curve.average(binmin, binmax)*(binmax-binmin)

        diffUp = 0.
        diffDown = 0.
        if curveUp and curveDown:
            diffUp = curveUp.average(binmin,binmax)*(binmax-binmin) - curveN
            diffDown = curveN - curveDown.average(binmin,binmax)*(binmax-binmin)

            if diffUp < 0:
                #print diffUp
                hold = diffDown
                diffDown = -1.*diffUp
                diffUp = -1.*diffDown
                
        
        if (binN > curveN):
            errN = TMath.Sqrt((theData.GetEYlow()[datapt]*(binmax-binmin))**2 \
                                  + diffUp**2)
        else:
            errN = TMath.Sqrt((theData.GetEYhigh()[datapt]*(binmax-binmin))**2 \
                                  + diffDown**2)

        pull = 0.
        if errN > 0:
            pull = (binN - curveN)/errN

        # print 'bin: (', binmin, ',', binmax, ') N:', binN, '+/-', errN,
        # print 'curve N:', curveN

        pullGraph.SetPoint(datapt, theData.GetX()[datapt], pull)
        pullGraph.SetPointError(datapt, 0., 1.)

    return pullGraph

def computeChi2(theData, curve):
    pullGraph = createPull(theData, curve)
    chi2 = 0.
    for pnt in range(0, pullGraph.GetN()):
        chi2 += pullGraph.GetY()[pnt]**2

    return (chi2, pullGraph.GetN())

def splitErrCurve(curve):
    from ROOT import RooCurve

    upperCurve = RooCurve()
    upperCurve.SetName('%s_upper' % curve.GetName())

    lowerCurve = RooCurve()
    lowerCurve.SetName('%s_lower' % curve.GetName())

    lastx = curve.GetX()[0]
    lasty = curve.GetY()[0]
    inCurve = False
    currentCurve = upperCurve
    for pt in range(0, curve.GetN()):
        x = curve.GetX()[pt]
        y = curve.GetY()[pt]

        if (lastx > x):
            currentCurve = lowerCurve

        if (x == lastx) and inCurve:
            if (lasty != y):
                inCurve = False
        elif not inCurve and (lastx != x):
            inCurve = True
            currentCurve.addPoint(lastx, lasty if (lasty>0.) else 0.)

        if (x != lastx) and inCurve:
            currentCurve.addPoint(x, y if (y>0.) else 0.)

        lastx = x
        lasty = y

    upperCurve.Sort()
    lowerCurve.Sort()
    if lowerCurve.GetY()[0] > upperCurve.GetY()[0]:
        tmp = lowerCurve
        lowerCurve = upperCurve
        upperCurve = tmp
        
    return (upperCurve, lowerCurve)

def curveToHist(curve, hist, debug = False):
    from math import sqrt
    from ROOT import gPad
    #hist.Sumw2()
    for binx in range(1, hist.GetNbinsX()+1):
        low = hist.GetBinLowEdge(binx)
        high = low + hist.GetBinWidth(binx)
        hist.SetBinContent(binx, curve.average(low,high))
        #hist.SetBinError(binx, sqrt(hist.GetBinContent(binx)))
    if debug:
        print 'drawing background histogram...'
        curve.Draw('al')
        hist.Draw('same')
        gPad.Update()
        gPad.WaitPrimitive()

    return hist
