import DibosonConfig

def theConfig(Nj, mcdir = '', initFile = '', btag = False):
    fitterPars = DibosonConfig.theConfig(Nj, mcdir, initFile, btag)
    fitterPars.includeElectrons = True
    fitterPars.includeMuons = False

    fitterPars.cuts += '&& (W_mt>50.) ' + \
                       '&& (event_met_pfmet>30) ' + \
                       '&& (W_electron_pt>35.) '

    fitterPars.QCDcuts = fitterPars.cuts
    fitterPars.cuts += '&& ( (abs(W_electron_eta)<1.5 && abs(W_electron_deltaphi_in)<0.03 && abs(W_electron_deltaeta_in)<0.004) || (abs(W_electron_eta)>1.5 && abs(W_electron_deltaphi_in)<0.02 && abs(W_electron_deltaeta_in)<0.005) ) '

    fitterPars.cuts += '&& ((W_electron_trackiso+W_electron_hcaliso+W_electron_ecaliso-event_RhoForLeptonIsolation*3.141592653589*0.09)/W_electron_pt<0.05) '


    print 'cuts:',fitterPars.cuts
    print 'QCD cuts:', fitterPars.QCDcuts
    
    return fitterPars
