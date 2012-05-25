import DibosonConfig

def theConfig(Nj, mcdir = '', initFile = '', btag = False, toydataFile="", e_FSU=-10.0, e_FMU=-10.0):
    fitterPars = DibosonConfig.theConfig(Nj, mcdir, initFile, btag, toydataFile, e_FSU, e_FMU)
    fitterPars.includeElectrons = False
    fitterPars.includeMuons = True

    fitterPars.cuts += '&& (W_mt>30.) ' + \
                       '&& (event_met_pfmet>25) ' + \
                       '&& (W_muon_pt>25.) ' + \
                       '&& (abs(W_muon_eta)<2.1) ' + \
                       '&& (abs(W_muon_d0bsp)<0.02) ' 

    fitterPars.QCDcuts = fitterPars.cuts
    
    fitterPars.cuts += '&& ((W_muon_trackiso+W_muon_hcaliso+W_muon_ecaliso-event_RhoForLeptonIsolation*3.141592653589*0.09)/W_muon_pt<0.1) '

    print 'cuts:',fitterPars.cuts
    print 'QCD cuts:', fitterPars.QCDcuts
    
    return fitterPars
