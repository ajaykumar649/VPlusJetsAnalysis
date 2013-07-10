#ifndef _WWGAMAQGCINPUTS_H
#define _WWGAMAQGCINPUTS_H

#define NUMCHAN 2

#define ELORMUCHAR 0

const char *channames[NUMCHAN] = {
  "el",
  "mu",
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

//const double antibtag_unc = 0.02;
const double antibtag_ttgam_unc = 0.11;
const double antibtag_stop_unc  = 0.05;

const double pileup_unc   = 0.01;

const double sigmvaseleffunc = 0.10;

// Background-specific uncertainties:
//
const double wgamjet_unc[NUMCHAN] = {
  0.079, 0.067
};
const double zgamjet_unc = 0.20;
const double ttbgam_unc = 0.20;
const double qcd_e_unc  = 0.50;

//const double signal_xs_unc  = 0.034;

// for cut-and-count limits:
const double photonptmingev  = 30.;

//#define FORMFACTOR_LIMITS
#undef FORMFACTOR_LIMITS

//======================================================================
#ifdef FORMFACTOR_LIMITS
//======================================================================

//Form Factor Test
#define NUMA0WPTS 26
const int a0W_points[NUMA0WPTS] = {-177,-174,-171,-168,-165,-162,-159,-156,-153,-150,-140,-100,-80,
				   80,100,140,150,153,156,159,162,165,168,171,174,177};
#if 0
#define NUMA0WPTS 6
const int a0W_points[NUMA0WPTS] = { -140,-100,-80,80,100,140 };

#define NUMA0WPTS 26
const int a0W_points[NUMA0WPTS] = {-140000,-130000,-120000,-110000,-100000,-90000,-80000,-70000,-60000,-50000,-140,-100,-80,
				   80,100,140,50000,60000,70000,80000,90000,100000,110000,120000,130000,140000};

#define NUMA0WPTS 26
const int a0W_points[NUMA0WPTS] = {-140000,-130000,-120000,-110000,-100000,-90000,-80000,-70000,-60000,-50000,-140,-100,-80,
				   80,100,140,10000,60000,70000,80000,90000,100000,110000,120000,130000,140000};
#endif

//======================================================================
#else
//======================================================================

#define NUMA0WPTS 26
const int a0W_points[NUMA0WPTS] = { -50,-38,-36,-34,-32,-30,-28,-26,-24,-22,-20,-18,-16,     // times 1e-6
				    16,18,20,22,24,26,28,30,32,34,36,38,50 };

#define NUMACWPTS 28
const int aCW_points[NUMACWPTS] = { -80,-50,-48,-46,-44,-42,-40,-38,-36,-34,-32,-30,-28,-26, // times 1e-6
				    26,28,30,32,34,36,38,40,42,44,46,48,50,80 };

#define NUMLT0PTS 26
const int lt0_points[NUMLT0PTS] = { -80,-50,-38,-36,-34,-32,-30,-28,-26,-24,-22,-20,-18,     // times 1e-12
				    18,20,22,24,26,28,30,32,34,36,38,50,80 };

#define NUMK0WPTS 20
const int K0W_points[NUMACWPTS] = { -20,-17,-16,-15,-14,-13,-12,-11,-10,-5,                  // times 1e-6
				    5,10,11,12,13,14,15,16,17,20 };

#define NUMKCWPTS 26
const int KCW_points[NUMACWPTS] = { -32,-30,-28,-25,-22,-20,-18,-15,-12,-10,-8,-5,-2,        // times 1e-6
                                    2,5,8,10,12,15,18,20,22,25,28,30,32 };

//======================================================================
#endif
//======================================================================


// FILE/HISTO STRUCTURE: assumed same name objects contained in different files for the different inputs

const char *dir =
//  "/uscms_data/d3/jfaulkn3/Limitsetter/CMSSW_6_1_1/src/ElectroWeakAnalysis/VPlusJets/test/Utilities/aQGC/";
  //"/uscms_data/d3/jfaulkn3/Limitsetter/CMSSW_6_1_1/src/ElectroWeakAnalysis/VPlusJets/test/Utilities/aQGC/Test/Mlvjja/";
  //"/uscms/home/jfaulkn3/WWG/CMSSW_5_3_2_patch4/src/aQGC_limit/";
  //"/uscms_data/d2/jdamgov/NTuples_53X_MORIOND13/CMSSW_5_3_2_patch4/src/ElectroWeakAnalysis/VPlusJets/test/Utilities/aQGC_limit/";
  //".";
  //"/uscms_data/d3/jfaulkn3/Limitsetter/CMSSW_6_1_1/src/ElectroWeakAnalysis/VPlusJets/test/Utilities/aQGC/Test";
  //"/uscms_data/d3/jfaulkn3/Limitsetter/CMSSW_6_1_1/src/ElectroWeakAnalysis/VPlusJets/test/Utilities/aQGC/Test/NewMethods/ROOTFiles/SM/";
  "/uscms_data/d3/jfaulkn3/Limitsetter/CMSSW_6_1_1/src/ElectroWeakAnalysis/VPlusJets/test/Utilities/aQGC/Test/NewMethods/ROOTFiles/PhotonET/";

inline TString parinputfiles(int chan,const TString& par) {
  return "sim_"+TString(channames[chan>0])+"_"+par+"_WWA_PhotonEt.root";
}
inline TString a0winputfiles(int chan) {
  return parinputfiles(chan,"a0W");
}
inline TString aCwinputfiles(int chan) {
  return parinputfiles(chan,"aCW");
}
inline TString lt0inputfiles(int chan) {
  return parinputfiles(chan,"LT0");
}
inline TString K0Winputfiles(int chan) {
  return parinputfiles(chan,"K0W");
}
inline TString KCWinputfiles(int chan) {
  return parinputfiles(chan,"KCW");
}

// For SM limits with varying MVA cuts:
#define NUMMVACUTS 6
const char *MVAcuts4SM[NUMMVACUTS] = { "","_MVA000","_MVA010","_MVA020","_MVA021","_MVA0225" };
inline TString SMinputfiles(int chan,const TString& mvacut) {
  return TString(channames[chan>0])+"_WWA_WZA_PhotonEt"+mvacut+".root";
}

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

const char *signalfmtstr = "signal_%s_%s%d"; //%s(1)="a0w"|"aCw|lt0", %s(2)="m" for minus or "" for plus
const char *SMsigfmtstr = "signal_SM";

const char *dataobjname = "data_obs";

#endif // _WWGAMAQGCINPUTS_H
