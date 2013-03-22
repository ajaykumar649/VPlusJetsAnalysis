#ifndef _ATGCINPUTS_H
#define _ATGCINPUTS_H

// never uncomment this line!
//#define ISHWW // now you've done it!

#define NUMMASSPTS 1
const int masspts[NUMMASSPTS] = { 150 };

#define NUMCHAN 2

const char *channames[NUMCHAN] = {
  //  "elboosted",
  "eldijet",
  //  "muboosted",
  "mudijet",
};

const TString AnalStr       = "ATGC";

const double mutrigeff      = 1.;
const double eltrigeff      = 1.;
const double sigtrigeffunc  = 0.01;
const double siglepteffunc  = 0.02;
const double siglumiunc     = 0.044;
const double signal_xs_unc  = 0.034;

// for cut-and-count limits:
const double dijetptmingev  = 350.;

const float LAMBDAZ_MIN = -0.1;
const float LAMBDAZ_MAX =  0.1;
const float LAMBDAZ_INC = 0.005; //  41 pts

const float dKG_MIN =  -0.30;
const float dKG_MAX =   0.30;
const float dKG_INC =   0.02;    // x31 pts

const float dg1_MIN =  -0.60;
const float dg1_MAX =   0.60;
const float dg1_INC =   0.05;    // x25 pts = 31775 total pts

// FILE/HISTO STRUCTURE: assumed same name objects contained in different files for the different inputs

//const char *dir = "/uscms_data/d2/kalanand/junk/vplusjets/CMSSW_4_2_8/src/ElectroWeakAnalysis/VPlusJets/test/TGC/";
const char *dir = ".";

// ordered the same as the inputs
//
const char *inputfiles[NUMCHAN] = {
  //"el_boosted.root",
  "el_dijet.root",
  //"mu_boosted.root",
  "mu_dijet.root",
};

const char *signalfmtstr = "lambdaZ_%.3f_deltaKappaGamma_%.3f";

const char *dataobjname = "data";
const char *bkgdobjname = "background";

#endif // _ATGCINPUTS_H
