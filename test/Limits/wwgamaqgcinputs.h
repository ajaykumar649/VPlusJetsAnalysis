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
const double lumi_unc     = 0.044;
const double pdf_unc      = 0.036;
const double scale_unc    = 0.234;
const double jer_unc      = 0.01;
const double jes_unc      = 0.043;
const double phes_unc     = 0.01;
const double antibtag_unc = 0.02;
const double pileup_unc   = 0.01;

const double sigmvaseleffunc = 0.10;

// Background-specific uncertainties:
//
const double fkphoton_unc = 0.20;
const double wgamjet_unc[NUMCHAN] = {
  0.12, 0.08
};
const double zgamjet_unc = 0.20;
const double ttbgam_unc = 0.20;
const double qcd_e_unc  = 0.50;

//const double signal_xs_unc  = 0.034;

// for cut-and-count limits:
const double photonptmingev  = 245.;

#define NUMA0WPTS 26

const int a0W_points[NUMA0WPTS] = { -50,-38,-36,-34,-32,-30,-28,-26,-24,-22,-20,-18,-16,
				    16,18,20,22,24,26,28,30,32,34,36,38,50 }; // times 1e-4

#define NUMACWPTS 6

const int aCW_points[NUMACWPTS] = { -8,-5,-3,3,5,8 }; // times 1e-5

#define NUMLT0PTS 6

const int lt0_points[NUMLT0PTS] = { -8,-5,-3,3,5,8 }; // times 1e-11

// FILE/HISTO STRUCTURE: assumed same name objects contained in different files for the different inputs

const char *dir =
  //"/uscms/home/jfaulkn3/WWG/CMSSW_5_3_2_patch4/src/aQGC_limit/";
  //"/uscms_data/d2/jdamgov/NTuples_53X_MORIOND13/CMSSW_5_3_2_patch4/src/ElectroWeakAnalysis/VPlusJets/test/Utilities/aQGC_limit/";
  //".";
  "/uscms_data/d3/jfaulkn3/Limitsetter/CMSSW_6_1_1/src/ElectroWeakAnalysis/VPlusJets/test/Utilities/aQGC/Test";

// ordered the same as the inputs
//
const char *a0winputfiles[NUMCHAN] = {
  "sim_el_a0W_WWA_PhotonEt.root",
  "sim_mu_a0W_WWA_PhotonEt.root"
};

const char *aCwinputfiles[NUMCHAN] = {
  "sim_el_aCW_WWA_PhotonEt.root",
  "sim_mu_aCW_WWA_PhotonEt.root"
};

const char *lt0inputfiles[NUMCHAN] = {
  "sim_el_LT0_WWA_PhotonEt.root",
  "sim_mu_LT0_WWA_PhotonEt.root"
};

const char *SMinputfiles[NUMCHAN] = {
  "sim_el_WWA_WZA_PhotonEt.root",
  "sim_mu_WWA_WZA_PhotonEt.root"
};

const char *zgamjet = "Zgamjet";
const char *ttbgam  = "ttbgam";
const char *wgamjet = "Wgamjet";
const char *fkphoton = "fkphoton";
const char *sngltop  = "sngltop";
const char *wzgamsm  = "WZgamSM";
const char *wwgamsm  = "WWgamSM";
const char *qcd      = "QCD";

#define NUMBAKPROC 8
const char *bakprochistonames[NUMBAKPROC][2] = {
  {fkphoton, "th1fkdata"},
  {ttbgam,   "th1Top"},
  {sngltop,  "th1stop"},
  {wgamjet,  "th1wajets"},
  {zgamjet,  "th1zajets"},
  {wwgamsm,  "th1wwa"},
  {wzgamsm,  "th1wza"},
  {qcd,      "th1qcd"},
};

const char *signalfmtstr = "signal_%s_%s%2d"; //%s(1)="a0w"|"aCw|lt0", %s(2)="m" for minus or "" for plus
const char *SMsigfmtstr = "signal_SM";

const char *dataobjname = "data_obs";

#endif // _WWGAMAQGCINPUTS_H
