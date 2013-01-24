#ifndef _HWWCHANNELS_H
#define _HWWCHANNELS_H

#define ISHWW

//#define ISVBF
#undef ISVBF

//#define SEVENTEV
#undef SEVENTEV

//#define DO_INTERP
#undef DO_INTERP

namespace{ // makes all constants contained herein "file-private" to avoid link errors from multiple linked includes

//================================================================================
// High-level variables

#ifdef SEVENTEV
const bool BLINDING = false;
const double intlumipbinv = 5020.0;
const double global_scale = 1.0;
const int beamcomenergytev = 7;

// ordered the same as the channels
//
const char *dir = 
  //"/uscms_data/d2/pdudero/HWW/ICHEP2012/7tevInterp";
  "/uscms_data/d3/weizou/MakeNtuple/CMSSW_4_2_8/src/ElectroWeakAnalysis/VPlusJets/test/VBFTemplate2011";
#else

//const bool BLINDING = true;
const bool BLINDING = false;

//const double intlumipbinv_mu = 5100.0;
//const double intlumipbinv_el = 5100.0;
//const double intlumipbinv_mu = 6900.0;
//const double intlumipbinv_el = 6800.0;
//const double intlumipbinv_mu = 12000.0;
//const double intlumipbinv_el = 11900.0;
const double intlumipbinv_mu = 19300.0;
const double intlumipbinv_el = 19200.0;

const int beamcomenergytev = 8;

const char *dir =
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWW1p6Result";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWW3p5ResultUnblind";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWW3p5tightMuons";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWW3p5Injectx1";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWW3p5Injectx2";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWW3p5Injectx5";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWW3p5withInterp";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWW25JuneResult";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWW5p1Result26June";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWW5p1withInterp";
  //"/uscms_data/d2/pdudero/HWW/ICHEP2012/8tevInterp";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWW9p9MuonsResults";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWW9p9NoWeight";
  //"/uscmst1b_scratch/lpc1/3DayLifetime/pdudero";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWW11pXresult";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWW5p1ResultHighMass";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWW11pXtightCut";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWW5p1HighMassInterp";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWW11pX19Oct2012";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWW11pXnewAlpha";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWW11pXnewBinningAlpha";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWW11pX25Oct";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWWHCP26Oct";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWWHCP26OctWithInterp";
  //"/uscms_data/d2/pdudero/oldCMSSW/CMSSW_4_2_8/src/ElectroWeakAnalysis/VPlusJets/test/HWWHCPOct26withInterp";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWW2012C";
  //"/uscms_data/d2/andersj/Wjj/2012/CMSSW_4_2_3_patch5/src/ElectroWeakAnalysis/VPlusJets/test/HWW2012AB";
  "/uscms_data/d2/andersj/Wjj/2012/CMSSW_5_3_3_patch2/src/ElectroWeakAnalysis/VPlusJets/test/";
  //  "..";

const double global_scale = 1.0;
//const double global_scale = 5000.0/intlumipbinv;
//const double scalefrom7to8tev = 1.3;

const double scaleBRforTau = 1.5; // because the twiki page does not include tau in the quoted BR for lvqq!

#endif

//================================================================================

//----------------------------------------
#ifdef ISVBF
#define NUMCHAN 2

// must be put in lexicographical order
//
// for combination:
const char *channames[NUMCHAN] = {
  "vbfhwwelnu2j"
  ,"vbfhwwmunu2j"
};
#define ELORMUCHAR 6

const char *channames2[NUMCHAN] = {
  "Electron"
  ,"Muon"
};
//----------------------------------------
#else
#define NUMCHAN 2

// must be put in lexicographical order
//
#if 1
// for combination:
const char *channames[NUMCHAN] = {
  "hwwelnu2j"
  //,"hwwelnu3j"
  ,"hwwmunu2j"
  //,"hwwmunu3j"
};
#define ELORMUCHAR 3
#else
const char *channames[NUMCHAN] = {
  "el2jetCMS"
  //,"el3jetCMS"
  ,"mu2jetCMS"
  //,"mu3jetCMS"
};
#define ELORMUCHAR 0
#endif

const char *channames2[NUMCHAN] = {
  "Electron"
  //,"Electron"
  ,"Muon"
  //,"Muon"
};
#endif
//----------------------------------------

const double mutrigeff      = 1.0;
const double eltrigeff      = 1.0;
const double sigtrigeffunc  = 0.01;
const double siglepteffunc  = 0.02;
const double siglumiunc     = 0.044;

const double W2qqBR    = 0.6770;
const double W2taunuBR = 0.1125;


//--------------------------------------------------

const int NUMMASSPTS=12;
const int masspts[NUMMASSPTS] = {
  170, 180, 190, 200, 250, 300, 350, 400, 450, 500, 550, 600
  //180, 190, 200, 250, 300, 350, 400, 450, 500, 550, 600
  //300, 350, 400, 450, 500, 550, 600
  //700,800,900
};

//--------------------------------------------------

const int interpolatedmasspts[] = {
  172,174,176,178,    // 170-180
  182,184,186,188,    // 180-190

  192,194,196,198,    // 190-200
  202,204,206,208,210,
  212,214,216,218,220,
  222,224,226,228,230,
  232,234,236,238,240,
  242,244,246,248,    // 200-250

  252,254,256,258,260,
  262,264,266,268,270,
  272,274,276,278,280,
  282,284,286,288,290,
  295,                // 250-300
  305,310,315,320,325,
  330,335,340,345,    // 300-350

  360,370,380,390,
  420,440,            // 400-450
  460,480,            // 450-500
  520,540,            // 500-550
  560,580,            // 550-600
  -1
};

//--------------------------------------------------

// inputs are normalized to 1/nent

// FILE/HISTO STRUCTURE: assumed same name objects contained in different files for the different channels
// ordered the same as the channels
//
#ifdef ISVBF
const char *inputfilesfmtstr[NUMCHAN] = {
  "H%d_Electron_2Jets_Fit_Shapes.root",
  "H%d_Muon_2Jets_Fit_Shapes.root",
};
#else
const char *inputfilesfmtstr[NUMCHAN] = {
  "HWWlnujjH%d_electron_2jets_output.root",
  //"HWWlnujjH%d_electron_3jets_output.root",
  "HWWlnujjH%d_muon_2jets_output.root",
  //"HWWlnujjH%d_muon_3jets_output.root",
};
#endif

const char *dataobjname = "theData";
const char *bkgdobjname = "h_total";

#ifndef SEVENTEV

#if 0

// Run2012A+B ran Nov08, 5.1/fb 
double backnormerr[NUMMASSPTS*NUMCHAN] = {
  /*       el2j   el3j   mu2j   mu3j */
  /*170*/ 1.005, 1.005, 1.003, 1.003,
  /*180*/ 1.009, 1.005, 1.006, 1.003,
  /*190*/ 1.005, 1.005, 1.004, 1.003,
  /*200*/ 1.009, 1.006, 1.005, 1.004,
  /*250*/ 1.006, 1.006, 1.005, 1.007,
  /*300*/ 1.005, 1.016, 1.005, 1.007,
  /*350*/ 1.012, 1.021, 1.011, 1.013,
  /*400*/ 1.008, 1.022, 1.006, 1.012,
  /*450*/ 1.009, 1.024, 1.014, 1.033,
  /*500*/ 1.026, 1.048, 1.023, 1.046,
  /*550*/ 1.030, 1.030, 1.026, 1.036,
  /*600*/ 1.034, 1.038, 1.028, 1.035,
};

// Run2012C ran Nov06, 6.8/6.9/fb 
double backnormerr[NUMMASSPTS*NUMCHAN] = {
  /*       el2j   el3j   mu2j   mu3j */
  /*170*/ 1.005, 1.004, 1.003, 1.003,
  /*180*/ 1.009, 1.004, 1.007, 1.003,
  /*190*/ 1.004, 1.004, 1.004, 1.003,
  /*200*/ 1.009, 1.005, 1.006, 1.003,
  /*250*/ 1.006, 1.005, 1.004, 1.005,
  /*300*/ 1.005, 1.007, 1.004, 1.010,
  /*350*/ 1.008, 1.010, 1.011, 1.016,
  /*400*/ 1.005, 1.010, 1.008, 1.009,
  /*450*/ 1.006, 1.011, 1.011, 1.018,
  /*500*/ 1.023, 1.037, 1.023, 1.026,
  /*550*/ 1.025, 1.026, 1.029, 1.019,
  /*600*/ 1.031, 1.018, 1.032, 1.016,
};

// 2012 ICHEP top-up, 26June, 5.1/fb
double backnormerr[NUMMASSPTS*NUMCHAN] = {
  /*         el2j     el3j     mu2j     mu3j */
  /*170*/   1.003,   1.003,   1.002,   1.002, // taken from HCP 26Oct
  /*180*/   1.005,   1.004,   1.004,   1.003,
  /*190*/   1.005,   1.004,   1.004,   1.003,
  /*200*/   1.005,   1.007,   1.003,   1.004,
  /*250*/   1.008,   1.006,   1.004,   1.007,
  /*300*/   1.006,   1.007,   1.005,   1.007,
  /*350*/   1.009,   1.020,   1.006,   1.017,
  /*400*/   1.008,   1.024,   1.006,   1.014,
  /*450*/   1.010,   1.028,   1.011,   1.024,
  /*500*/   1.011,   1.000,   1.012,   1.000,
  /*550*/   1.011,   1.026,   1.013,   1.000,
  /*600*/   1.013,   1.028,   1.012,   1.000,
};

// 2012 HCP, 26Oct, 11.9/fb el, 12.0/fb mu, 11 masspts, 4 channels,
//                          interference included for 2jet 500-600
double backnormerr[NUMMASSPTS*NUMCHAN] = {
  /*       el2j   el3j   mu2j   mu3j */
  /*170*/ 1.003, 1.003, 1.002, 1.002,
  /*180*/ 1.005, 1.003, 1.005, 1.002,
  /*190*/ 1.003, 1.003, 1.003, 1.002,
  /*200*/ 1.007, 1.004, 1.004, 1.003,
  /*250*/ 1.004, 1.004, 1.003, 1.004,
  /*300*/ 1.003, 1.006, 1.003, 1.007,
  /*350*/ 1.010, 1.008, 1.007, 1.012,
  /*400*/ 1.004, 1.008, 1.005, 1.008,
  /*450*/ 1.006, 1.021, 1.009, 1.018,
  /*500*/ 1.017, 1.032, 1.016, 1.032,
  /*550*/ 1.019, 1.025, 1.019, 1.026,
  /*600*/ 1.024, 1.028, 1.020, 1.023, 
};

// 2012 HCP, 25Oct, 11.9/fb el, 11.5/fb mu, 11 masspts, 4 channels,
//                          phil's fixes
//                          interference included for 2jet 500-600
double backnormerr[NUMMASSPTS*NUMCHAN] = {
  /*       el2j   el3j   mu2j   mu3j */
  /*170*/ 1.003, 1.003, 1.003, 1.002,
  /*180*/ 1.005, 1.003, 1.011, 1.002,
  /*190*/ 1.003, 1.003, 1.005, 1.002,
  /*200*/ 1.007, 1.004, 1.004, 1.003,
  /*250*/ 1.008, 1.004, 1.004, 1.004,
  /*300*/ 1.003, 1.006, 1.003, 1.007,
  /*350*/ 1.010, 1.008, 1.007, 1.014,
  /*400*/ 1.004, 1.008, 1.006, 1.008,
  /*450*/ 1.006, 1.021, 1.009, 1.017,
  /*500*/ 1.015, 1.025, 1.013, 1.019,
  /*550*/ 1.019, 1.024, 1.018, 1.024,
  /*600*/ 1.023, 1.027, 1.020, 1.023,
};

// 2012 HCP, 25Oct, 11.9/fb el, 11.5/fb mu, 11 masspts, 4 channels,
//                          interference included for 2jet 500-600
double backnormerr[NUMMASSPTS*NUMCHAN] = {
  /*       el2j   el3j   mu2j   mu3j */
  /*170*/ 1.003, 1.003, 1.002, 1.002,
  /*180*/ 1.005, 1.003, 1.005, 1.002,
  /*190*/ 1.003, 1.003, 1.003, 1.002,
  /*200*/ 1.007, 1.004, 1.004, 1.003,
  /*250*/ 1.003, 1.004, 1.003, 1.003,
  /*300*/ 1.003, 1.006, 1.003, 1.007,
  /*350*/ 1.010, 1.008, 1.007, 1.014,
  /*400*/ 1.004, 1.008, 1.006, 1.008,
  /*450*/ 1.006, 1.021, 1.009, 1.017,
  /*500*/ 1.016, 1.025, 1.013, 1.019,
  /*550*/ 1.024, 1.019, 1.016, 1.020,
  /*600*/ 1.018, 1.024, 1.016, 1.018,
};

// 2012 HCP, 15Oct, 11.9/fb el, 11.5/fb mu, 11 masspts, 4 channels,
//                          interference included for 2jet 500-600
double backnormerr[NUMMASSPTS*NUMCHAN] = {
  /*       el2j   el3j   mu2j   mu3j */
  /*170*/ 1.002, 1.003, 1.002, 1.002,
  /*180*/ 1.005, 1.003, 1.005, 1.002,
  /*190*/ 1.003, 1.003, 1.003, 1.002,
  /*200*/ 1.006, 1.004, 1.004, 1.003,
  /*250*/ 1.003, 1.004, 1.003, 1.003,
  /*300*/ 1.003, 1.005, 1.003, 1.007,
  /*350*/ 1.009, 1.008, 1.025, 1.013,
  /*400*/ 1.004, 1.008, 1.005, 1.008,
  /*450*/ 1.006, 1.029, 1.007, 1.018,
  /*500*/ 1.009, 1.019, 1.010, 1.017,
  /*550*/ 1.009, 1.041, 1.012, 1.019,
  /*600*/ 1.016, 1.009, 1.013, 1.016,
};

// 2012 HCP, 16Oct, 11.9/fb el, 11.5/fb mu, single mass point test of 3j
double backnormerr[NUMMASSPTS*NUMCHAN] = {
  /*       el2j   el3j   mu2j  mu3j  */
  /*350*/ 1.009, 1.008, 1.025, 1.011
};

// 2012 HCP, 15Oct, 11.9/fb el, 11.5/fb mu, 12 masspts, no 3jet channel
double backnormerr[NUMMASSPTS*NUMCHAN] = {
  /*       el2j   mu2j */
  /*170*/ 1.002, 1.002,
  /*180*/ 1.005, 1.005,
  /*190*/ 1.003, 1.003,
  /*200*/ 1.006, 1.004,
  /*250*/ 1.003, 1.003,
  /*300*/ 1.003, 1.003,
  /*350*/ 1.009, 1.025,
  /*400*/ 1.004, 1.005,
  /*450*/ 1.006, 1.007,
  /*500*/ 1.009, 1.010, // with interference
  /*550*/ 1.009, 1.012,
  /*600*/ 1.016, 1.013,
};
#if 0
  /*500*/ 1.006, 1.010, // w/o interference
  /*550*/ 1.007, 1.009,
  /*600*/ 1.008, 1.012,
#endif

// 2012 HCP, 08Oct, 9.3/fb, 3 masspts, no 3jet channel
double backnormerr[NUMMASSPTS*NUMCHAN] = {
  /*       el2j   mu2j */
  /*700*/ 1.040, 1.000,
  /*800*/ 1.040, 1.000,
  /*900*/ 1.040, 1.000,
};

// 2012 HCP, 29Sep, 9.9/fb, 11 masspts, no 3jet channel
double backnormerr[NUMMASSPTS*NUMCHAN] = {
  /*       el2j   mu2j  */
  /*180*/ 1.006, 1.005,
  /*190*/ 1.004, 1.003,
  /*200*/ 1.006, 1.004,
  /*250*/ 1.008, 1.006,
  /*300*/ 1.008, 1.006,
  /*350*/ 1.015, 1.013,
  /*400*/ 1.007, 1.007,
  /*450*/ 1.011, 1.009,
  /*500*/ 1.011, 1.010,
  /*550*/ 1.014, 1.010,
  /*600*/ 1.017, 1.013,
};

// 2012 ICHEP, 27June, 3.5/fb, 11 masspts
double backnormerr[NUMMASSPTS*NUMCHAN] = {
  /*         el2j     el3j     mu2j     mu3j */
  /*180*/   1.006,   1.005,   1.004,   1.004,
  /*190*/   1.006,   1.005,   1.004,   1.004,
  /*200*/   1.006,   1.009,   1.004,   1.005,
  /*250*/   1.009,   1.007,   1.006,   1.006,
  /*300*/   1.006,   1.009,   1.010,   1.009,
  /*350*/   1.010,   1.016,   1.008,   1.021,
  /*400*/   1.009,   1.021,   1.007,   1.018,
  /*450*/   1.011,   1.022,   1.014,   1.031,
  /*500*/   1.011,   1.000,   1.014,   1.000,
  /*550*/   1.010,   1.031,   1.015,   1.000,
  /*600*/   1.012,   1.040,   1.013,   1.000,
};

// 2012 ICHEP top-up, 26June, 5.1/fb
double backnormerr[NUMMASSPTS*NUMCHAN] = {
  /*         el2j     el3j     mu2j     mu3j */
  /*180*/   1.005,   1.004,   1.004,   1.003,
  /*190*/   1.005,   1.004,   1.004,   1.003,
  /*200*/   1.005,   1.007,   1.003,   1.004,
  /*250*/   1.008,   1.006,   1.004,   1.007,
  /*300*/   1.006,   1.007,   1.005,   1.007,
  /*350*/   1.009,   1.020,   1.006,   1.017,
  /*400*/   1.008,   1.024,   1.006,   1.014,
  /*450*/   1.010,   1.028,   1.011,   1.024,
  /*500*/   1.011,   1.000,   1.012,   1.000,
  /*550*/   1.011,   1.026,   1.013,   1.000,
  /*600*/   1.013,   1.028,   1.012,   1.000,
};

// 2012 ICHEP pre-unblinding, 14June, 3.50/fb
double backnormerr[NUMMASSPTS*NUMCHAN] = {
  /*         el2j     el3j     mu2j     mu3j */
  /*180*/   1.006,   1.005,   1.004,   1.004, // added after unblinding
  /*200*/   1.007,   1.009,   1.004,   1.005,
  /*300*/   1.006,   1.009,   1.010,   1.009, 
  /*400*/   1.009,   1.021,   1.007,   1.018, 
  /*450*/   1.011,   1.022,   1.014,   1.031, 
  /*500*/   1.011,   1.000,   1.014,   1.000,
  /*550*/   1.010,   1.031,   1.015,   1.000, // added after unblinding
  /*600*/   1.012,   1.040,   1.013,   1.000, 
};

// 2012 ICHEP preapproval freeze, 1.60/fb
double backnormerr[NUMMASSPTS*NUMCHAN] = {
  /*         el2j     el3j     mu2j     mu3j */
  /*170*/   1.005,   1.006,   1.000,    1.006,
  /*180*/   1.009,   1.007,   1.006,    1.005,
  /*190*/   1.009,   1.007,   1.006,    1.006,
  /*200*/   1.009,   1.013,   1.006,    1.008,
  /*250*/   1.008,   1.018,   1.008,    1.010,
  /*300*/   1.008,   1.014,   1.013,    1.015,
  /*350*/   1.012,   1.032,   1.017,    1.025,
  /*400*/   1.010,   1.035,   1.013,    1.025,
  /*450*/   1.012,   1.056,   1.019,    1.045,
  /*500*/   1.011,   1.050,   1.018,    1.050,
  /*550*/   1.012,   1.035,   1.020,    1.035,
  /*600*/   1.013,   1.049,   1.020,    1.049,
};

// First limit of 2012, 560/fb
double backnormerr[NUMMASSPTS*NUMCHAN] = {
  /*         el2j     el3j     mu2j     mu3j */
  /*170*/   1.007,   1.012,   1.005,   1.008,
  /*180*/   1.013,   1.012,   1.011,   1.009,
  /*190*/   1.014,   1.012,   1.013,   1.009,
  /*200*/   1.015,   1.021,   1.013,   1.012,
  /*250*/   1.021,   1.020,   1.012,   1.020,
  /*300*/   1.023,   1.031,   1.013,   1.037,
  /*350*/   1.024,   1.044,   1.024,   1.047,
  /*400*/   1.020,   1.040,   1.028,   1.039,
  /*450*/   1.026,   1.102,   1.040,   1.100,
  /*500*/   1.035,   1.081,   1.041,   1.132,
  /*550*/   1.036,   1.056,   1.020,   1.097,
  //  /*600*/   1.047,	  ,   1.040,   1.138,
};
#endif

#else // SEVENTEV

// With MVA+Q/G, lumi=5.0/fb, VBF only
double backnormerr[NUMMASSPTS*NUMCHAN] = {
  /*         el2j     mu2j */
  /*300*/   1.006,   1.008,
  /*350*/   1.009,   1.010,
  /*400*/   1.008,   1.008,
  /*450*/   1.009,   1.009,
  /*500*/   1.010,   1.009,
  /*550*/   1.013,   1.010,
  /*600*/   1.015,   1.017,
};

#if 0
// With MVA+Q/G, lumi=5.0/fb
double backnormerr[NUMMASSPTS*NUMCHAN] = {
  /*         el2j     el3j     mu2j     mu3j */
  /*170*/   1.003,   1.004,   1.002,   1.003,
  /*180*/   1.005,   1.005,   1.004,   1.003,
  /*190*/   1.008,   1.005,   1.007,   1.004,
  /*200*/   1.009,   1.008,   1.006,   1.005,
  /*250*/   1.009,   1.009,   1.006,   1.007,
  /*300*/   1.006,   1.012,   1.008,   1.011,

  /*350*/   1.009,   1.036,   1.010,   1.025,
  /*400*/   1.008,   1.028,   1.008,   1.018,

  /*450*/   1.009,   1.030,   1.009,   1.032,
  /*500*/   1.010,   1.031,   1.009,   1.042,
  /*550*/   1.013,   1.044,   1.010,   1.031,
  /*600*/   1.015,   1.054,   1.017,   1.048,
};
#endif

#endif

#ifdef SEVENTEV
const double sigselefferrpctlomass =  7.0; // 2011 7TeV
const double sigselefferrpcthimass = 13.0; // 2011 7TeV
#else
const double sigselefferrpct8tev = 10.0; // 2012 8TeV
#endif

double ggsigaccptsyst[NUMMASSPTS] = {
  /*170*/ 1.02,
  /*180*/ 1.02,
  /*190*/ 1.02,
  /*200*/ 1.02,
  /*250*/ 1.015,
  /*300*/ 1.020,
  /*350*/ 1.023,
  /*400*/ 1.024,
  /*450*/ 1.027,
  /*500*/ 1.029,
  /*550*/ 1.032,
  /*600*/ 1.036,
  // /*700*/ 1.046,
  // /*800*/ 1.040,
  // /*900*/ 1.040,
};

double qqsigaccptsyst[NUMMASSPTS] = {
  /*170*/ 1.02,
  /*180*/ 1.02,
  /*190*/ 1.02,
  /*200*/ 1.02,
  /*250*/ 1.011,
  /*300*/ 1.009,
  /*350*/ 1.008,
  /*400*/ 1.006,
  /*450*/ 1.007,
  /*500*/ 1.009,
  /*550*/ 1.009,
  /*600*/ 1.007,
  //  /*700*/ 1.010,
  //  /*800*/ 1.010,
  //  /*900*/ 1.010,
};

} // end unnamed namespace

#endif // _HWWCHANNELS_H
