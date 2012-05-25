#import pyroot_logon
#from ROOT import gROOT
#gROOT.ProcessLine('.L RooWjjFitterParams.h+');
import MjjConfig
#from ROOT import RooWjjFitterParams

def theConfig(Nj, mcdir = '', initFile = '', toydataFile = '', e_minT=-1, e_maxT=-1):
    fitterPars = MjjConfig.theConfig(Nj, mcdir, initFile, toydataFile, e_minT, e_maxT)
    fitterPars.includeMuons = False
    fitterPars.includeElectrons = True

    fitterPars.cuts = fitterPars.cuts + \
                      '&& (W_electron_pt > 35) ' + \
                      '&& (JetPFCor_Pt[0] > 40) ' + \
                      '&& (JetPFCor_Pt[1] > 30) '

    return fitterPars
