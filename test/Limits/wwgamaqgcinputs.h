#ifndef _WWGAMAQGCINPUTS_H
#define _WWGAMAQGCINPUTS_H

#define NUMCHAN 2

#define ELORMUCHAR 0

const char *channames[NUMCHAN] = {
  "eldijet",
  "mudijet",
};

const float intlumipbinv_el = 19166;
const float intlumipbinv_mu = 19297;
const int   beamcomenergytev = 8;

const TString AnalStr       = "WWGAMAQGC";

const double mutrigeff      = 1.;
const double eltrigeff      = 1.;

const double met_unc      = 0.01;
const double trigeff_unc  = 0.01;
const double lepteff_unc  = 0.02;
const double lumi_unc     = 0.03;
const double pdf_unc      = 0.03;
const double scale_unc    = 0.03;
const double jer_unc      = 0.01;
const double jes_unc      = 0.01;
const double antibtag_unc = 0.01;
const double pileup_unc   = 0.01;

const double sigmvaseleffunc = 0.10;

//const double signal_xs_unc  = 0.034;

// for cut-and-count limits:
const double photonptmingev  = 245.;

#define NUMA0WPTS 6

const int a0W_points[NUMA0WPTS] = { -5,-3,-2,2,3,5 }; // times 1e-5

#define NUMACWPTS 6

const int aCW_points[NUMACWPTS] = { -8,-5,-3,3,5,8 }; // times 1e-5

#define NUMLT0PTS 6

const int lt0_points[NUMLT0PTS] = { -8,-5,-3,3,5,8 }; // times 1e-11

// FILE/HISTO STRUCTURE: assumed same name objects contained in different files for the different inputs

const char *dir =
  //"/uscms/home/jfaulkn3/WWG/CMSSW_5_3_2_patch4/src/aQGC_limit/";
  //"/uscms_data/d2/jdamgov/NTuples_53X_MORIOND13/CMSSW_5_3_2_patch4/src/ElectroWeakAnalysis/VPlusJets/test/Utilities/aQGC_limit/";
  ".";
// ordered the same as the inputs
//
const char *a0winputfiles[NUMCHAN] = {
  "el_a0W_WWA_PhotonEt_MVA01.root",
  "mu_a0W_WWA_PhotonEt_MVA01.root"
};

const char *aCwinputfiles[NUMCHAN] = {
  "el_aCW_WWA_PhotonEt_MVA01.root",
  "mu_aCW_WWA_PhotonEt_MVA01.root"
};

const char *lt0inputfiles[NUMCHAN] = {
  "el_LT0_WWA_PhotonEt_MVA01.root",
  "mu_LT0_WWA_PhotonEt_MVA01.root"
};

const char *SMinputfiles[NUMCHAN] = {
  "el_WWA_WZA_PhotonEt.root",
  "mu_WWA_WZA_PhotonEt.root"
};

const char *signalfmtstr = "signal_%s_%s%d"; //%s(1)="a0w"|"aCw|lt0", %s(2)="m" for minus or "" for plus
const char *SMsigfmtstr = "signal_SM";

const char *dataobjname = "data_obs";
const char *bkgdobjname = "background";

#endif // _WWGAMAQGCINPUTS_H
