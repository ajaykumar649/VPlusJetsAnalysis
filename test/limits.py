from ROOT import RooStats, Double, RooArgSet, RooFit, RooDataHist

# profiled likelihood limit
def plcLimit(obs_, poi_, model, ws, data, CL = 0.95, verbose = False):
    # obs : observable variable or RooArgSet of observables
    # poi : parameter of interest or RooArgSet of parameters
    # model : RooAbsPdf of model to consider including any constraints
    # data : RooAbsData of the data
    # CL : confidence level for interval
    # returns a dictionary with the upper and lower limits for the first/only
    # parameter in poi_ as well as the interval object and status flag
    
    obs = RooArgSet(obs_)
    obs.setName('observables')
    poi = RooArgSet(poi_)
    poi.setName('poi')
    poi.setAttribAll('Constant', False)
    nuis = model.getParameters(obs)
    nuis.remove(poi)
    nuis.remove(nuis.selectByAttrib('Constant', True))
    nuis.setName('nuisance')

    if verbose:
        print 'observables'
        obs.Print('v')
        print 'parameters of interest'
        poi.Print('v')
        print 'nuisance parameters'
        nuis.Print('v')
 
    mc = RooStats.ModelConfig('mc')
    mc.SetWorkspace(ws)
    mc.SetPdf(model)
    mc.SetObservables(obs)
    mc.SetParametersOfInterest(poi)
    mc.SetNuisanceParameters(nuis)

    plc = RooStats.ProfileLikelihoodCalculator(data, mc)
    plc.SetConfidenceLevel(CL)

    interval = plc.GetInterval()

    upperLimit = Double(999.)
    lowerLimit = Double(0.)
    Limits = {}

    paramIter = poi.createIterator()
    param = paramIter.Next()
    while param:
        ok = interval.FindLimits(param, lowerLimit, upperLimit)
        Limits[param.GetName()] = {'ok' : ok, 'upper' : float(upperLimit),
                                   'lower' : float(lowerLimit)}
        param = paramIter.Next()

    if verbose:
        print '%.0f%% CL limits' % (interval.ConfidenceLevel() * 100)
        print Limits

    Limits['interval'] = interval
    return Limits

def expectedPlcLimit(obs_, poi_, model, ws, ntoys = 30, CL = 0.95,
                     binData = False):
    # obs : observable variable or RooArgSet of observables
    # poi : parameter of interest or RooArgSet of parameters
    # model : RooAbsPdf of model to consider including any constraints
    #         the parameters should have the values corresponding to the
    #         background-only hypothesis which will be used to  estimate the
    #         expected limit.
    # ntoys : number of toy datsets to generate to get expected limit
    # CL : confidence level for interval
    # returns a dictionary containing the expected limits and their 1 sigma
    # errors for the first/only parameter in poi_ and a list of the results
    # from the individual toys.

    from math import sqrt
    obs = RooArgSet(obs_)
    obs.setName('observables')
    mPars = model.getParameters(obs)
    genPars = mPars.snapshot()

    print "parameters for generating toy datasets"
    genPars.Print("v")

    limits = []
    sumUpper = 0.
    sumUpper2 = 0.
    sumLower = 0.
    sumLower2 = 0.
    nOK = 0
    for i in range(0,ntoys):
        print 'generate limit of toy %i of %i' % (i+1, ntoys)
        mPars.assignValueOnly(genPars)

        toyData = model.generate(obs, RooFit.Extended())
        if binData:
            toyData = RooDataHist('data_obs_%i' % i, 'data_obs_%i' % i,
                                  obs, toyData)
        toyData.SetName('data_obs_%i' % i)
        toyData.Print()

        limits.append(plcLimit(obs_, poi_, model, ws, toyData, CL))

        # print limits[-1]
        if limits[-1][poi_.GetName()]['ok']:
            nOK += 1
            sumUpper += limits[-1][poi_.GetName()]['upper']
            sumUpper2 += limits[-1][poi_.GetName()]['upper']**2
            sumLower += limits[-1][poi_.GetName()]['lower']
            sumLower2 += limits[-1][poi_.GetName()]['lower']**2

        toyData.IsA().Destructor(toyData)

    expLimits = {'upper' : sumUpper/nOK,
                 'upperErr' : sqrt(sumUpper2/(nOK-1)-sumUpper**2/nOK/(nOK-1)),
                 'lower' : sumLower/nOK,
                 'lowerErr' : sqrt(sumLower2/(nOK-1)-sumLower**2/nOK/(nOK-1)),
                 'ntoys': nOK
                 }
    return (expLimits, limits)
