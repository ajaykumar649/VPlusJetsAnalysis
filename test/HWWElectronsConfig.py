import pyroot_logon
import HWWconfig

## list of tuples that have the optimized inputs for each mass point
## tuple is (0: mass, 1: mvaVariableName, 2: mvaCut, 3: min4bodymass,
##           4: max4bodymass, 5: nbins, 6: alpha, 7: alphaDown, 8: alphaUp,
##           9: lowSideband, 10: highSideband, 11: qglCut)

optimalPars2 = [
( 170, "mva2j170el", 0.300, 170.0, 250.0, 8, 0.10, 0.060, 0.130, (55.0,65.0), (95.0,115.0), 0. ),
( 180, "mva2j180el", 0.550, 170.0, 250.0, 8, 0.050, 0.000, 0.110, (55.0,65.0), (95.0,115.0), 0. ),
( 190, "mva2j190el", 0.550, 170.0, 250.0, 8, 0.050, 0.000, 0.120, (55.0,65.0), (110.0,125.0), 0. ),
( 200, "mva2j200el", 0.600, 180.0, 250.0, 7, 0.220, 0.160, 0.280, (55.0,65.0), (95.0,115.0), 0. ),
( 250, "mva2j250el", 0.650, 200.0, 400.0, 10, 0.220, 0.150, 0.290, (55.0,65.0), (95.0,200.0), 0. ),
( 300, "mva2j300el", 0.600, 240.0, 400.0, 8, 0.440, 0.330, 0.550, (55.0,65.0), (95.0,200.0), 0. ),
( 350, "mva2j350el", 0.600, 300.0, 780.0, 12, 0.030, 0.000, 0.220, (55.0,65.0), (95.0,200.0), 0. ),
( 400, "mva2j400el", 0.550, 300.0, 780.0, 12, 0.000, 0.000, 0.260, (55.0,65.0), (95.0,200.0), 0. ),
( 450, "mva2j450el", 0.500, 340.0, 780.0, 11, 0.000, 0.000, 0.160, (55.0,65.0), (95.0,200.0), 0. ),
( 500, "mva2j500el", 0.500, 340.0, 780.0, 11, 0.000, 0.000, 0.070, (55.0,65.0), (95.0,200.0), 0.2 ),
( 550, "mva2j550el", 0.550, 340.0, 780.0, 11, 0.000, 0.000, 0.090, (40.0,65.0), (95.0,200.0), 0.35 ),
( 600, "mva2j600el", 0.600, 340.0, 780.0, 11, 0.000, 0.000, 0.040, (40.0,65.0), (95.0,200.0), 0.45 ),
]

optimalPars3 = [
( 170, "mva3j170el", 0.300, 170.0, 250.0, 8, 0.230, 0.150, 0.310, (55.0,65.0), (95.0,115.0), 0. ),
( 180, "mva3j180el", 0.300, 170.0, 250.0, 8, 0.270, 0.190, 0.360, (55.0,65.0), (95.0,115.0), 0. ),
( 190, "mva3j190el", 0.300, 170.0, 250.0, 8, 0.220, 0.120, 0.320, (55.0,65.0), (95.0,115.0), 0. ),
( 200, "mva3j200el", 0.400, 180.0, 250.0, 7, 0.270, 0.140, 0.410, (55.0,65.0), (95.0,115.0), 0. ),
( 250, "mva3j250el", 0.400, 200.0, 400.0, 10, 0.500, 0.410, 0.590, (55.0,65.0), (95.0,200.0), 0. ),
( 300, "mva3j300el", 0.500, 240.0, 400.0, 8, 0.660, 0.450, 0.940, (55.0,65.0), (95.0,200.0), 0. ),
( 350, "mva3j350el", 0.650, 300.0, 780.0, 12, 0.860, 0.630, 1.000, (55.0,65.0), (95.0,200.0), 0. ),
( 400, "mva3j400el", 0.600, 300.0, 780.0, 12, 0.000, 0.000, 0.190, (55.0,65.0), (95.0,200.0), 0. ),
( 450, "mva3j450el", 0.550, 340.0, 780.0, 11, 0.380, 0.080, 0.620, (55.0,65.0), (95.0,200.0), 0. ),
( 500, "mva3j500el", 0.600, 340.0, 780.0, 11, 0.430, 0.240, 0.610, (55.0,65.0), (95.0,200.0), 0.2 ),
( 550, "mva3j550el", 0.500, 340.0, 780.0, 11, 0.300, 0.100, 0.490, (40.0,65.0), (95.0,200.0), 0.35 ),
( 600, "mva3j600el", 0.600, 340.0, 780.0, 11, 0.190, 0.000, 0.500, (40.0,65.0), (95.0,200.0), 0.45 ),
]

def theConfig(Nj, mcdir = '', initFile = '', mH=400, mvaCut = None,
              qgCut = None):
    if Nj == 3:
        optPars = HWWconfig.getOptimalPars(mH, optimalPars3)
    else:
        optPars = HWWconfig.getOptimalPars(mH, optimalPars2)
    
    mvaVarNames  = optPars[1]
    mvaCutValues = optPars[2]
    HWWconfig.minMlvjj = optPars[3]
    HWWconfig.maxMlvjj = optPars[4]

    fitterPars = HWWconfig.theConfig(Nj, mcdir, initFile)
    fitterPars.includeMuons = False
    fitterPars.includeElectrons = True

    if (mvaCut):
        mvaCutValues = mvaCut
    
    fitterPars.cuts += '&& (%s > %f) ' % (mvaVarNames,mvaCutValues) + \
                       '&& (W_electron_pt > 35) '
    if not qgCut:
        qgCut = optPars[11]
    fitterPars.cuts += '&& (%s > %f) ' % ("qgld_Summer11CHS[1]",qgCut)

    print '2-body cuts:', fitterPars.cuts

    return fitterPars

def the4BodyConfig(twoBodyConfig, mH=400, syst=0, alphaOverride = None):
    if twoBodyConfig.njets == 3:
        optPars = HWWconfig.getOptimalPars(mH, optimalPars3)
    else:
        optPars = HWWconfig.getOptimalPars(mH, optimalPars2)
    HWWconfig.minMlvjj = optPars[3]
    HWWconfig.maxMlvjj = optPars[4]
    alpha = optPars[6+syst]
    alphaDown = optPars[6+1]
    alphaUp = optPars[6+2]
    if alphaOverride:
        alpha = alphaOverride
        alphaDown = alphaOverride
        alphaUp = alphaOverride
    fitterPars = HWWconfig.the4BodyConfig(twoBodyConfig, alpha, optPars[9],
                                          optPars[10],
                                          alphaRange = (alphaDown,alphaUp))
    fitterPars.nbins = optPars[5]
    fitterPars.model = 1
    if (mH <= 200) and (twoBodyConfig.njets == 2):
        fitterPars.model = 4
    if (mH == 190) and (twoBodyConfig.njets == 2):
        fitterPars.model = 5

    return fitterPars
