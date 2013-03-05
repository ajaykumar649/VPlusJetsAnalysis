#include <iostream>
#include "TLatex.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH1F.h"
#include "THStack.h"
#include "TString.h"
#include "TLegend.h"
#include "TLine.h"
#include "TPad.h"
#include "TCanvas.h"
//=====================================================================================
// SYNOPSIS:
//   1. Prepare "InData" and "OutDir" directories; e.g., "ln -s . OutDir" to go to current dir
//   2. root [0] .x mkControlPlots.C(0) for electron data, or
//      root [0] .x mkControlPlots.C(1) for muon data
//
// ====================================================================================
// Self Function
// ====================================================================================

void cmspre(double intlumifbinv)
{
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);

  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.85,0.93,"#sqrt{s} = 8 TeV");
  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.65,0.93,Form("#int #font[12]{L} dt = %.1f fb^{-1}", (float)intlumifbinv));

  latex.SetTextAlign(11); // align left
//  latex.DrawLatex(0.15,0.93,"CMS,  #sqrt{s} = 7 TeV");//preliminary 2011");
  latex.DrawLatex(0.15,0.96,"CMS preliminary");

}
#if 0
  PlotVar_t(char *inpv,double inmaxr,double inminr,int innbin,int inslog,char *inxl,char *inoutf,char *inoutf2,double inamax,double inamin,int inanb,int inhp,int indl) :
    plotvar(inpv),
    MAXRange(inmaxr),MINRange(inminr),NBINS(innbin),
    slog(inslog),xlabel(inxl),outfile(inoutf),outfile2(inoutf2),
    AMAXRange(inamax),AMINRange(inamin),ANBINS(inanb),
    hplot(inhp,drawleg(indl) {}
#endif
struct plotVar_t {
  char* plotvar;
  double MINRange;
  double MAXRange;
  int    NBINS;
  int    slog;
  char* xlabel;
  char* outfile;
  double AMINRange;
  double AMAXRange;
  int    ANBINS;
  int    mva_in;
  int    hplot;
  int  drawleg;
};

void mkElControlPlots_Photon(bool domu=false,bool domva=false,
		    bool dovbf=false)
{
    gROOT->ProcessLine(".L tdrstyle.C");
  const double intLUMI = 19200.;
  const double H190_scale   = 8.782*0.108*1.5*2.* intLUMI/193737; // V
  const double H500_scale   = 1.439*0.080*1.5*2.* intLUMI/131182 ; // V
  const double AQGC_scale   = 0.047*1.5* intLUMI/194029 ; // V

  const double WAJets_scale   = 1.045 * 9.37246 * intLUMI/1049473; // V
  const double WWA_scale     = 1.5 * 0.01362 * intLUMI/198777; // V
  const double WWA2_scale    = 1.5 * 0.01409 * intLUMI/199183; // V
  const double WZA_scale     = 1.5 * 0.00578008 * intLUMI/497450; // V
  const double ZAJets_scale  = 0.63196 * intLUMI/979207;
  const double ttbara_scale  = 1.44 * intLUMI/604113; // V

  const double ZZ_scale      = 8.059   * intLUMI/9702850; // V

  const double QCD_scale     = 1. ; // V
  const double SToppS_scale  = 1.75776  * intLUMI/139974; // V anti-top
  const double SToppT_scale  = 30.0042  * intLUMI/1935066; // V
  const double SToppTW_scale = 11.1773  * intLUMI/493458; // V
  const double STopS_scale   = 3.89394  * intLUMI/259960; // top
  const double STopT_scale   = 55.531  * intLUMI/3758221; //V
  const double STopTW_scale  = 11.1773  * intLUMI/497657; // V



  const plotVar_t plotvars[] = {

  //    plotvar	MINRange  MAXRange  NBINS  slog xlabel outfile AMINRange  AMAXRange ANBINS mva_in hplot drawleg
//    { "ggdevt",     -0.5, 5.5, 6, 3, "ggdevt",  "ggdevt",      -0.5, 5.5, 6, 0, 1, 1 },
    { "c2jMass11",     10, 430, 14, 3,   "m_{jj} (GeV)",            "mjj1",       10,  430, 14, 0, 1, 1},
    { "c2jMass11",     70, 100, 30, 3,   "m_{jj} (GeV)",            "mjj",       65,  105, 40, 0, 1, 1},
    { "mva2jWWAelA",     -0.4, 0.9, 13, 3, "mva2jWWAelA",  "mva2jWWAelA",      -0.5, 1.0, 15, 0, 1, 1 },
    { "mva2jWWAelA",     -0.4, 0.9, 26, 3, "mva2jWWAelA1",  "mva2jWWAelA1",      -0.5, 1.0, 30, 0, 1, 1 },
    { "mva2jWWAelA",     -0.4, 0.9, 52, 3, "mva2jWWAelA2",  "mva2jWWAelA2",      -0.5, 1.0, 60, 0, 1, 1 },
    { "masslvjja",  150, 1550, 28, 3, "M_{l#nujj#gamma}", "mlvjja", 150, 1550, 28, 0, 0, 1},
    { "masslvjja",  150, 1250, 11, 3, "M_{l#nujj#gamma}", "mlvjja1", 150, 1250, 11, 0, 0, 1},
    { "masslvjja",  150, 1350, 6, 3, "M_{l#nujj#gamma}", "mlvjja2", 150, 1350, 6, 0, 0, 1},
    { "mva2jWWAelM",     -0.5, 0.9, 14, 3, "mva2jWWAelM",  "mva2jWWAelM",      -0.6, 1.0, 16, 0, 1, 1 },
    { "Photon_Et[iPhoton11]",         10, 260, 25, 3,  "Photon p_{T} (GeV)",     "Photon_et",       20,  260, 24, 0, 0, 0 },
    { "Photon_Et[iPhoton11]",         30, 270, 12, 3,  "Photon p_{T} (GeV)",     "Photon_et1",       30,  270, 12, 0, 0, 1 },
    { "Photon_Et[iPhoton11]",         30, 310, 7, 3,  "Photon p_{T} (GeV)",     "Photon_et2",       30,  310, 6, 0, 0, 0 },
    { "mva2jWWAel",     -0.5, 0.9, 14, 3, "mva2jWWAel",  "mva2jWWAel",      -0.6, 1.0, 16, 0, 1, 1 },
    { "event_nPV",      -0.5, 50.5, 51, 1,  "Num PV",            "event_nPV",    -0.5,  50.5, 51, 0, 0, 0 },
    { "Photon_Eta[iPhoton11]",      -2.7, 2.7, 18, 1,  "Photon #eta",            "Photon_eta",    -2.4,  2.4, 16, 0, 0, 0 },
    { "Photon_Phi[iPhoton11]",      -3.2,  3.2, 16, 1,  "Photon #phi",            "Photon_phi",   -3.2,  3.2, 16, 0, 0, 0 },
    { "Photon_dRlep[iPhoton11]",-0.4, 5.0, 27, 1, "#Delta R_{l,#gamma}",    "deltaRla", -0.8, 5.4, 31, 0, 0, 0},
    { "JetPFCor_dRpho11[i11Jet1]",-0.4, 5.0, 27, 1, "#Delta R_{j1,#gamma}",    "deltaRj1a", -0.8, 5.4, 31, 0, 0, 0},
    { "JetPFCor_dRpho11[i11Jet2]",-0.4, 5.0, 27, 1, "#Delta R_{j2,#gamma}",    "deltaRj2a", -0.8, 5.4, 31, 0, 0, 0},
    { "JetPFCor_Pt[i11Jet1]",   30,   200, 17, 3, "Leading Jet  p_{T}", "jetld_pt",      20,  200, 18, 0, 0, 0},
    { "JetPFCor_Pt[i11Jet2]",   30,   150, 12, 3, "Jet 2 p_{T}",        "jetnt_pt",      20,  150, 13, 0, 0, 0 },
    { "JetPFCor_Eta[i11Jet1]", -2.4 , 2.4, 12, 1, "Leading Jet  #eta",  "jetld_eta",   -2.6 , 2.6, 13, 0, 0, 0 },
    { "JetPFCor_Eta[i11Jet2]", -2.4 , 2.4, 12, 1, "Jet 2 #eta",         "jetnt_eta",   -2.6 , 2.6, 13, 0, 0, 0 },
    { "JetPFCor_dphiMET[i11Jet1]", -3.2, 3.2, 16, 1, "#Delta #phi (Leading Jet, MET)", "deltaphi_jetldmet", -3.6, 3.6, 18, 0, 0, 0 },
    { "JetPFCor_dphiMET[i11Jet2]", -3.2, 3.2, 16, 1, "#Delta #phi (Second Jet, MET)", "deltaphi_jetndmet", -3.6, 3.6, 18, 0, 0, 0 },

//    { "colorCorrPull01PFCor",     0, 4, 20, 3,   "colorCorrPull01PFCor",            "colorCorrPull01PFCor",       0, 4, 20, 0, 1, 0},
//    { "colorCorrPull02PFCor",     0, 4, 20, 3,   "colorCorrPull02PFCor",            "colorCorrPull02PFCor",       0, 4, 20, 0, 1, 0},
//    { "colorCorrPull12PFCor",     0, 4, 20, 3,   "colorCorrPull12PFCor",            "colorCorrPull12PFCor",       0, 4, 20, 0, 1, 0},
//  From James
    { "Photon_Et[iPhoton11]/W_electron_pt",0,10,10,3,"#gamma_{p_{T}}:l_{p_{T}}","gammapt_elpt",0,10,10,1,0,0},
    { "Photon_Et[iPhoton11]/JetPFCor_Pt[i11Jet1]",0,10,10,3,"#gamma_{p_{T}}:Jet1_{p_{T}}","gammapt_j1pt",0,10,10,1,0,0},
    { "Photon_Et[iPhoton11]/JetPFCor_Pt[i11Jet2]",0,10,10,3,"#gamma_{p_{T}}:Jet2_{p_{T}}","gammapt_j2pt",0,10,10,1,0,0},
    { "ang_lva",          -1.0,   1, 20, 1, "Cos #Phi_{l#nu-#gamma}", "lva", -1.0,   1, 20, 0, 0, 0 },
    { "ang_jja",          -1.0,   1, 20, 1, "Cos #Phi_{jj-#gamma}"  , "jja", -1.0,   1, 20, 0, 0, 0 },
    { "masslvjja/ptlvjja",   0,100,10, 3, "Mass:p_{T} of WW#gamma (GeV)", "masslvjja_ptlvjja", 0, 100, 10, 1, 0, 0},
    { "ptlvjja",             0, 150, 15, 3, "p_{T} of WW#gamma (GeV)", "ptlvjja", 0, 150, 15, 1, 0, 0},



    { "W_mt",             20, 140, 12, 3,   "W Transverse Mass (GeV)", "W_mt",      20,  140, 12, 0, 1, 0 },
    { "W_pt",             20, 140, 12, 3,   "W Transverse Mom (GeV)", "W_pt",      20,  140, 12, 0, 1, 0 },
    { "W_mtMVA",             20, 140, 12, 3,   "W Transverse Mass (GeV) withMVA MET", "W_mtMVA",      20,  140, 12, 0, 1, 0 },
    { "abs(event_metMVA_metPhi-Photon_Phi[iPhoton11])",  0, 6.28, 20, 3,   " |#Delta#phi(#gamma,MVA MET)| ",  "event_metMVA_pho_dphi",     0, 6.28, 20, 0, 0, 0 },
    { "abs(event_met_pfmetPhi-Photon_Phi[iPhoton11])",  0, 6.28, 20, 3,   " |#Delta#phi(#gamma,pf MET)| ",  "event_pfmet_pho_dphi",     0, 6.28, 20, 0, 0, 0 },
    { "abs(JetPFCor_Phi[i11Jet1]-JetPFCor_Phi[i11Jet2])",  0, 6.28, 20, 3,   " |#Delta#phi(J1,J2)| ",  "event_j1_j2_dphi",     0, 6.28, 20, 0, 0, 0 },
    { "abs(JetPFCor_Phi[i11Jet1]-Photon_Phi[iPhoton11])",  0, 6.28, 20, 3,   " |#Delta#phi(#gamma,J1)| ",  "event_j1_pho_dphi",     0, 6.28, 20, 0, 0, 0 },
    { "abs(JetPFCor_Phi[i11Jet2]-Photon_Phi[iPhoton11])",  0, 6.28, 20, 3,   " |#Delta#phi(#gamma,J2)| ",  "event_j2_pho_dphi",     0, 6.28, 20, 0, 0, 0 },
    { "abs(W_electron_phi-Photon_Phi[iPhoton11])",  0, 6.28, 20, 3,   " |#Delta#phi(#gamma,l)| ",  "event_lep_pho_dphi",     0, 6.28, 20, 0, 0, 0 },

    { "(W_electron_eta-Photon_Eta[iPhoton11])",  -3.2,  3.2, 16, 3,   " #Delta#eta(#gamma,l) ",  "event_lep_pho_deta",     -3.2,  3.2, 16, 0, 0, 0 },
    { "(JetPFCor_Eta[i11Jet1]-Photon_Eta[iPhoton11])",  -3.2,  3.2, 16, 3,   " #Delta#eta(#gamma,J1) ",  "event_j1_pho_deta",     -3.2,  3.2, 16, 0, 0, 0 },
   { "event_met_pfsumet",  0, 2000, 40, 3,   "pf SET (GeV)",  "event_met_pfsumet",     0, 2000, 40, 0, 0, 0 },
    { "event_met_pfmetPhi",  -3.14, 3.14, 26, 3,   "pf MET #phi",  "event_met_pfmetPhi",     -3.14, 3.14, 26, 0, 0, 0 },
    { "event_metMVA_metPhi",  -3.14, 3.14, 26, 3,   "MVA MET #phi ",  "event_metMVA_metPhi",     -3.14, 3.14, 26, 0, 0, 0 },
    { "event_met_pfmet",  25, 155, 13, 3,   "pf MET (GeV)",  "event_met_pfmet",     15, 155, 14, 0, 0, 0 },
    { "event_metMVA_met",  25, 155, 13, 3,   "MVA MET (GeV)",  "event_metMVA_met",     15, 155, 14, 0, 0, 0 },
    { "W_electron_charge",    -1.2, 1.2, 24, 1, "electron Charge" ,      "charge",   -1.2, 1.2, 24, 1, 0, 0 },

    { "sqrt((JetPFCor_Px[i11Jet1]+JetPFCor_Px[i11Jet2])**2+(JetPFCor_Py[i11Jet1]+JetPFCor_Py[i11Jet2])**2)",
                          15, 205, 19, 3,   "Dijet System p_{T} (GeV)", "dijet_pt", 5, 205, 20, 0, 0, 0},

    { "(JetPFCor_Eta[i11Jet1]-JetPFCor_Eta[i11Jet2])",
                         -3.0, 3.0, 15, 1,  "#Delta #eta (j,j)",    "deltaeta_jj",   -3.2,  3.2, 16, 0, 0, 0 },
    { "W_electron_pt",         15, 155, 14, 3,  "El p_{T} (GeV)",     "W_electron_pt",       25,  155, 13, 0, 0, 0 },
    { "W_electron_eta",      -2.7, 2.7, 18, 1,  "El #eta",            "W_electron_eta",    -2.4,  2.4, 16, 0, 0, 0 },
    { "ptlvjj",              0, 150, 15, 3, "p_{T} of WW (GeV)", "ptlvjj",      0, 150, 15, 1, 0, 0 },
    { "ylvjj",            -2.5, 2.5, 25, 1, "WW rapidity" ,      "etalvjj",  -3.0, 3.0, 30, 1, 0, 0 },
    { "ang_ha",              0,   1,  5, 1, "Cos #theta_{1}" ,   "ha",          0,   1,  5, 1, 0, 1 },
    { "ang_hb",              0,   1,  5, 1, "Cos #theta_{2}" ,   "hb",          0,   1,  5, 1, 0, 0 },
    { "ang_hs",           -1.0,   1, 20, 1, "Cos #theta*" ,      "hs",       -1.0,   1, 20, 1, 0, 0 },
    { "ang_phi",          -3.2, 3.2, 16, 6, "#Phi (rad)" ,       "phi",      -3.6, 3.6, 18, 1, 0, 0 },
    { "ang_phib",         -3.2, 3.2, 16, 6, "#Phi_{1} (rad)",    "phib",     -3.6, 3.6, 18, 1, 0, 0 },
    { "W_electron_charge",    -1.2, 1.2, 24, 1, "electron Charge" ,      "charge",   -1.2, 1.2, 24, 1, 0, 0 },


    { "sqrt((JetPFCor_Eta[i11Jet1]-JetPFCor_Eta[i11Jet2])**2+(abs(abs(abs(JetPFCor_Phi[i11Jet1]-JetPFCor_Phi[i11Jet2])-TMath::Pi())-TMath::Pi()))**2)",
                             0.4, 5.0, 23, 1, "#Delta R_{jj}",    "deltaRjj", 0.0, 5.4, 27, 0, 0, 1},


    { "", 0.0,0.0,0,0,"","",0.,0.,0.,0,0,0 }
  };


////////////////////////////////////////////higgs
  const plotVar_t higgsplotvars[] = {
  //    plotvar MINRange  MAXRange  NBINS  slog xlabel     outfile  AMINRange  AMAXRange ANBINS mva_in hplot drawleg

    { "MassV2j_PFCor",     140, 700, 14, 3, "m_{l#nujj} (GeV)",  "mlvjj",     100, 700, 15, 0, 0, 1 },
    { "ptlvjj",              0, 150, 15, 3, "p_{T} of WW (GeV)", "ptlvjj",      0, 150, 15, 1, 0, 0 },
    { "ylvjj",            -2.5, 2.5, 25, 1, "WW rapidity" ,      "etalvjj",  -3.0, 3.0, 30, 1, 0, 0 },
    { "ang_ha",              0,   1,  5, 1, "Cos #theta_{1}" ,   "ha",          0,   1,  5, 1, 0, 1 },
    { "ang_hb",              0,   1,  5, 1, "Cos #theta_{2}" ,   "hb",          0,   1,  5, 1, 0, 0 },
    { "ang_hs",           -1.0,   1, 20, 1, "Cos #theta*" ,      "hs",       -1.0,   1, 20, 1, 0, 0 },
    { "ang_phi",          -3.2, 3.2, 16, 6, "#Phi (rad)" ,       "phi",      -3.6, 3.6, 18, 1, 0, 0 },
    { "ang_phib",         -3.2, 3.2, 16, 6, "#Phi_{1} (rad)",    "phib",     -3.6, 3.6, 18, 1, 0, 0 },
    { "W_electron_charge",-1.2, 1.2, 24, 1, "Electron Charge" ,  "charge",   -1.2, 1.2, 24, 1, 0, 0 },
/*
    { "mva2j500mu",       -0.2, 1.2, 28, 2, "Likelihood Output ",           "mva2j500",  -0.2, 1.2, 28, 0, 1, 1 },
    { "mva2j350mu",          0,   1, 25, 2, "Likelihood Output 2j mu350 ",  "mva2j350_top", 0,   1, 10, 0, 0, 1 },
    { "mva2j180el",          0,   1, 25, 2, "Likelihood Output 2j el180 ",  "mva2j180_top", 0,   1, 10, 0, 0, 1 },
    { "qgld_Summer11CHS[0]", 0,   1, 25, 2, "Q/G Likelihood of Leading Jet","jetld_qgl",    0,   1, 25, 0, 0, 0 },
    { "qgld_Summer11CHS[1]", 0,   1, 25, 2, "Q/G Likelihood of Second Jet", "jetnt_qgl",    0,   1, 25, 0, 0, 0 },
*/
    { "", 0.0,0.0,0,0,"","",0.,0.,0.,0,0,0 }
  };


////////////////////////////////////////////VBF
  const plotVar_t vbfplotvars[] = {
  //    plotvar MINRange  MAXRange  NBINS  slog xlabel    outfile  AMINRange  AMAXRange ANBINS mva_in hplot drawleg
#if 0
    { "vbf_wbj_pt/vbf_wjj_m",
                          0.3, 0.7,  20, 2, "Jet 2 p_{T}/m_{jj}", "vbfjet2pt_ov_mjj", 0.25, 0.75, 25, 0, 0, 0 },

    { "vbf_waj_pt",       40,   300, 27, 3, "Hadronic W Jet1 p_{T}", "vbfwjeta_pt",      20,  300, 28, 0, 0, 1 },
    { "vbf_wbj_pt",       30,   200, 17, 3, "Hadronic W Jet2 p_{T}", "vbfwjetb_pt",      20,  200, 18, 0, 0, 0 },
    { "vbf_waj_eta",     -2.5 , 2.5, 25, 1, "Hadronic W Jet1 #eta",  "vbfwjeta_eta",   -2.7,  2.7, 27, 0, 0, 0 },
    { "vbf_wbj_eta",     -2.5 , 2.5, 25, 1, "Hadronic W Jet2 #eta",  "vbfwjetb_eta",   -2.7,  2.7, 27, 0, 0, 0 },
#endif
    { "vbf_aj_pt",        40,   300, 27, 3, "Tagjet1  p_{T}",        "vbftagjeta_pt",    20,  300, 28, 0, 0, 1 },
#if 0
    { "vbf_bj_pt",        30,   200, 17, 3, "Tagjet2  p_{T}",        "vbftagjetb_pt",    20,  200, 18, 0, 0, 0 },
    { "vbf_aj_eta",      -4.5 , 4.5, 45, 1, "Tagjet1 #eta",          "vbftagjeta_eta", -5.0,  5.0, 50, 0, 0, 0 },
    { "vbf_bj_eta",      -4.5 , 4.5, 45, 1, "Tagjet2 #eta",          "vbftagjetb_eta", -5.0,  5.0, 50, 0, 0, 0 },
    { "vbf_wjj_m",        40,   400, 36, 3, "m_{jj} (GeV)",          "vbfwjjmass",       30,  400, 37, 0, 0, 0 },
    { "W_mt",             50,   170, 24, 3, "W Transverse Mass (GeV)", "vbf_W_mt",       40,  170, 26, 0, 0, 1 },
    { "event_met_pfmet",  25,   205, 18, 3, "pf MET (GeV)",     "event_met_pfmet"  ,     15, 205, 19,  0, 0, 0 },

    { "vbf_lvjj_m",        140, 700, 56, 3, "m_{l#nujj} (GeV)",  "vbfmlvjj",        110, 700, 59, 0, 0, 1 },

    // MVA training variables:
    { "vbf_lvjj_pt",         0, 150, 15, 3, "p_{T} of WW (GeV)", "vbfptlvjj",         0, 150, 15, 1, 0, 0 },
    { "vbf_lvjj_y",       -2.5, 2.5, 25, 1, "WW rapidity" ,      "vbfetalvjj"   ,  -3.0, 3.0, 30, 1, 0, 0 },
    { "vbf_wjj_ang_ha",      0,   1, 10, 1, "Cos #theta_{1}" ,   "vbfangha",          0,   1, 10, 1, 0, 1 },
    { "vbf_wjj_ang_hb",      0,   1, 10, 1, "Cos #theta_{2}" ,   "vbfanghb",          0,   1, 10, 1, 0, 0 },
    { "vbf_wjj_ang_hs",   -1.0,   1, 20, 1, "Cos #theta*" ,      "vbfanghs",       -1.0,   1, 20, 1, 0, 0 },
    { "vbf_wjj_ang_phi",  -3.2, 3.2, 32, 6, "#Phi (rad)" ,       "vbfangphi",      -3.5, 3.5, 35, 1, 0, 0 },
    { "vbf_wjj_ang_phib", -3.2, 3.2, 32, 6, "#Phi_{1} (rad)",    "vbfangphib",     -3.5, 3.5, 35, 1, 0, 0 },
    { "W_electron_charge",-1.2, 1.2, 24, 1, "Electron Charge" ,  "vbfWelcharge",   -1.2, 1.2, 24, 1, 0, 0 },
    { "vbf_jj_deta",         3, 9.0, 30, 1, "Tagjet  #Delta#eta",    "vbftagjet_deta",      3,  9.0, 30, 1, 0, 0 },
    { "vbf_jj_m",         300, 1200, 18, 3, "Tagjet Invariant Mass (GeV)", "vbftagjet_mass", 200,  1200, 20, 1, 0, 0 },

    { "mvavbf500mu",       -0.2, 1.2, 28, 2, "Likelihood Output ",       "vbfmva500",  -0.2, 1.2, 28, 0, 0, 1 },
    { "mvavbf350mu",          0,   1, 25, 2, "Likelihood Output mu350 ", "vbfmva350",     0,   1, 10, 0, 0, 1 },
    { "mvavbf180el",          0,   1, 25, 2, "Likelihood Output el180 ", "vbfmva180",     0,   1, 10, 0, 0, 1 },
#endif
    { "", 0.0,0.0,0,0,"","",0.,0.,0,0,0 }
  };


 

 TCut the_cut("effwt*puwt*(iPhoton11>-1 && i11Jet1>-1 && i11Jet2>-1 && i11Jet3<0 && abs(W_electron_eta)<2.5 && W_electron_pt>30 && event_met_pfmet>30. && W_mt>30 && abs(Photon_Eta[iPhoton11])<1.44421 && Photon_Et[iPhoton11]>30. && JetPFCor_dRpho11[i11Jet1]>0.5 && JetPFCor_dRpho11[i11Jet2]>0.5 && abs(JetPFCor_dphiMET[i11Jet1])>0.4 && abs(JetPFCor_dphiMET[i11Jet2])>0.4 && JetPFCor_bDiscriminatorCSV[i11Jet1]<0.679 && JetPFCor_bDiscriminatorCSV[i11Jet2]<0.679 && abs(JetPFCor_Eta[i11Jet1]-JetPFCor_Eta[i11Jet2])<1.4 && c2jMass11>72. && c2jMass11<98. && abs(91.1876-massla)>10. &&ggdevt==2)");
// TCut the_cut("effwt*puwt*(iPhoton11>-1 && i11Jet1>-1 && i11Jet2>-1 && i11Jet3<0 && abs(W_electron_eta)<2.5 && W_electron_pt>30 && event_met_pfmet>30. && W_mt>30 && abs(Photon_Eta[iPhoton11])<1.44421 && Photon_Et[iPhoton11]>30. && JetPFCor_dRpho11[i11Jet1]>0.5 && JetPFCor_dRpho11[i11Jet2]>0.5 && abs(JetPFCor_dphiMET[i11Jet1])>0.4 && abs(JetPFCor_dphiMET[i11Jet2])>0.4 && JetPFCor_bDiscriminatorCSV[i11Jet1]<0.679 && JetPFCor_bDiscriminatorCSV[i11Jet2]<0.679 && abs(JetPFCor_Eta[i11Jet1]-JetPFCor_Eta[i11Jet2])<1.4 && c2jMass11>72. && c2jMass11<98. && abs(91.1876-massla)>10. &&ggdevt==2&&mva2jWWAelA>0.1)");
// TCut the_cut("effwt*puwt*(iPhoton11>-1 && i11Jet1>-1 && i11Jet2>-1 && i11Jet3<0 && abs(W_electron_eta)<2.5 && W_electron_pt>30 && event_met_pfmet>30. && W_mt>30 && abs(Photon_Eta[iPhoton11])<1.44421 && Photon_Et[iPhoton11]>30. && JetPFCor_dRpho11[i11Jet1]>0.5 && JetPFCor_dRpho11[i11Jet2]>0.5 && abs(JetPFCor_dphiMET[i11Jet1])>0.4 && abs(JetPFCor_dphiMET[i11Jet2])>0.4 && JetPFCor_bDiscriminatorCSV[i11Jet1]<0.679 && JetPFCor_bDiscriminatorCSV[i11Jet2]<0.679 && abs(JetPFCor_Eta[i11Jet1]-JetPFCor_Eta[i11Jet2])<1.4 && (c2jMass11<70. || c2jMass11>100.) && abs(91.1876-massla)>10. &&ggdevt==2)");
  TCut fkPhoton_cut(TString(the_cut)+TString("*(1./(1.+1./(0.0345868+1.44022E04/(Photon_Et[(iPhoton11>-1)? iPhoton11 : 0]^2.89994))))"));

  if (dovbf)
    the_cut = TCut("vbf_event");

  TCut the_cut2("effwt*puwt*((ggdevt==2) && fit_status==0  &&abs(JetPFCor_dphiMET[0])>0.4 &&W_electron_pfIsoEA>0.3)");
  TCut the_cut3("effwt*puwt*((ggdevt==3) && fit_status==0  &&abs(JetPFCor_dphiMET[0])>0.4 &&W_electron_pfIsoEA>0.3)");

  TFile f("plotvar_histo.root", "RECREATE");

 // Get the input trees:

 // Data

  TFile *fin2,*AQGC_file,*wwaShape_file,*wwa2Shape_file,*wzaShape_file,*wajetsShape_file,*H190_file,*H500_file,*wwShape_file,*zzShape_file,*wzShape_file,*wjetsShape_file,*w4jetShape_file,*ttbar_file,*qcd_file1,*zjets_file,*stops_file,*stopt_file,*stoptW_file;


  if (domu) {
    std::cout<<"ooops,not a mu"<<std::endl;
  } else { // electrons

    fin2            = new TFile("InData/RD_WenuJets_DataAllSingleElectronTrigger_GoldenJSON_19p2invfb.root", "READ");
//    H190_file       = new TFile("InData/RD_el_HWWMH190_CMSSW428.root", "READ");
//    H500_file       = new TFile("InData/RD_el_HWWMH500_CMSSW428.root", "READ");
    AQGC_file       = new TFile("InData/RD_el_KOG_m5m5MG_CMSSW532.root", "READ");
    wwaShape_file    = new TFile("InData/RD_el_qq_wpwma_wp_qq_wm_lvl.root");
    wwa2Shape_file    = new TFile("InData/RD_el_qq_wpwma_wp_lvl_wm_qq.root");
    wzaShape_file    = new TFile("InData/RD_el_WZA_CMSSW532.root", "READ");
    wajetsShape_file = new TFile("InData/RD_el_WAp23Jets.root", "READ");
    ttbara_file      = new TFile("InData/RD_el_TTbarAJets.root", "READ");
    zajets_file      = new TFile("InData/RD_el_ZAp23J_CMSSW532.root", "READ");

    zzShape_file    = new TFile("InData/RD_el_ZZ_CMSSW532.root", "READ");
    qcd_file1       = new TFile("InData/RDQCD_WenuJets_DataAll_GoldenJSON_19p2invfb.root", "READ");
    stops_file      = new TFile("InData/RD_el_STopS_T_CMSSW532.root", "READ");
    stopt_file      = new TFile("InData/RD_el_STopT_T_CMSSW532.root", "READ");
    stoptW_file     = new TFile("InData/RD_el_STopTW_T_CMSSW532.root", "READ");
  }

  TTree* treedata = (TTree*) fin2->Get("WJet");
  double nData = treedata->GetEntries();
  std::cout << "ndata =" << nData <<std::endl;

//  TTree* treeh190  = (TTree*)       H190_file->Get("WJet");
//  TTree* treeh500  = (TTree*)       H500_file->Get("WJet");
  TTree* treeAQGC  = (TTree*)       AQGC_file->Get("WJet");
  TTree* treewwa    = (TTree*)    wwaShape_file->Get("WJet");
  TTree* treewwa2    = (TTree*)    wwa2Shape_file->Get("WJet");
  TTree* treewza    = (TTree*)    wzaShape_file->Get("WJet");
  TTree* treewaj    = (TTree*) wajetsShape_file->Get("WJet");
  TTree* treettba   = (TTree*)      ttbara_file->Get("WJet");
  TTree* treezaj    = (TTree*)      zajets_file->Get("WJet");
  TTree* treezz    = (TTree*)    zzShape_file->Get("WJet");
  TTree* treeqcd   = (TTree*)       qcd_file1->Get("WJet");
  TTree* treests   = (TTree*)      stops_file->Get("WJet");
  TTree* treestt   = (TTree*)      stopt_file->Get("WJet");
  TTree* treestw   = (TTree*)     stoptW_file->Get("WJet");

  for (int ivar=0; ; ivar++) {

    plotVar_t pv;
    if (dovbf)
      pv = vbfplotvars[ivar];
    else
      if(domva) 
        pv = higgsplotvars[ivar];
      else
        pv = plotvars[ivar];
 
    if ( !strlen(pv.plotvar) ) break;

    std::cout << TString(pv.plotvar) << "\t"<<pv.MINRange<<"\t" << pv.MAXRange<<"\t" << pv.NBINS<<"\tTHE CUT " << endl;

    if (domu) {
      if (strstr(pv.plotvar,"el")) continue;
    } else {
      if (strstr(pv.plotvar,"mu")) continue;
    }

    const double BINWIDTH = ((pv.MAXRange-pv.MINRange)/pv.NBINS);

    TH1* th1data  = new TH1D("th1data",  "th1data",  pv.NBINS, pv.MINRange, pv.MAXRange);
    TBox *errbox = new TBox(pv.AMINRange,0.95,pv.AMAXRange,1.05);
    errbox->SetFillColor(kYellow);
    treedata->Draw(TString(pv.plotvar)+TString(">>th1data"), the_cut, "goff");
    th1data->AddBinContent(pv.NBINS,th1data->GetBinContent(pv.NBINS+1));th1data->SetBinContent(pv.NBINS+1,0.);


    TH1* th1fkdata  = new TH1D("th1fkdata",  "th1fkdata",  pv.NBINS, pv.MINRange, pv.MAXRange);
    th1fkdata->Sumw2();
    treedata->Draw(TString(pv.plotvar)+TString(">>th1fkdata"), fkPhoton_cut, "goff");
    th1fkdata->AddBinContent(pv.NBINS,th1fkdata->GetBinContent(pv.NBINS+1));th1fkdata->SetBinContent(pv.NBINS+1,0.);

    float fperr = 0.;
    for(int hi=1;hi<=pv.NBINS;hi++) {
        fperr = (th1fkdata->GetBinError(hi))*(th1fkdata->GetBinError(hi));
        fperr + = 0.01*(th1fkdata->GetBinContent(hi))*(th1fkdata->GetBinContent(hi));
	th1fkdata->SetBinError(hi,sqrt(fperr));
    }

    // Get Signal MC

//    TH1* th1H500 = new TH1D("th1H500", "th1H500", pv.NBINS, pv.MINRange, pv.MAXRange);
//    treeh500->Draw(TString(pv.plotvar)+TString(">>th1H500"), the_cut, "goff");

    TH1* th1AQGC = new TH1D("th1AQGC", "th1AQGC", pv.NBINS, pv.MINRange, pv.MAXRange);
    th1AQGC->Sumw2();
    treeAQGC->Draw(TString(pv.plotvar)+TString(">>th1AQGC"), the_cut, "goff");
    th1AQGC->AddBinContent(pv.NBINS,th1AQGC->GetBinContent(pv.NBINS+1));th1AQGC->SetBinContent(pv.NBINS+1,0.);
    th1AQGC->Scale(AQGC_scale);
    th1AQGC->SetMarkerStyle(0);
    th1AQGC->SetLineColor(4);
    th1AQGC->SetLineStyle(2);
    th1AQGC->SetLineWidth(3);

    // Get WW/WZ/ZZ
    TH1* th1wwa = new TH1D("th1wwa", "th1wwa", pv.NBINS, pv.MINRange, pv.MAXRange);
    TH1* th1wwa2 = new TH1D("th1wwa2", "th1wwa2", pv.NBINS, pv.MINRange, pv.MAXRange);
    TH1* th1wza = new TH1D("th1wza", "th1wza", pv.NBINS, pv.MINRange, pv.MAXRange);
    th1wwa->Sumw2();
    th1wwa2->Sumw2();
    th1wza->Sumw2();


    TH1* th1ww = new TH1D("th1ww", "th1ww", pv.NBINS, pv.MINRange, pv.MAXRange);
    TH1* th1wz = new TH1D("th1wz", "th1wz", pv.NBINS, pv.MINRange, pv.MAXRange);
    TH1* th1zz = new TH1D("th1zz", "th1zz", pv.NBINS, pv.MINRange, pv.MAXRange);
    th1ww->Sumw2();
    th1wz->Sumw2();
    th1zz->Sumw2();

    treewwa->Draw(TString(pv.plotvar)+TString(">>th1wwa"), the_cut, "goff");
    th1wwa->AddBinContent(pv.NBINS,th1wwa->GetBinContent(pv.NBINS+1));th1wwa->SetBinContent(pv.NBINS+1,0.);

    treewwa2->Draw(TString(pv.plotvar)+TString(">>th1wwa2"), the_cut, "goff");
    th1wwa2->AddBinContent(pv.NBINS,th1wwa2->GetBinContent(pv.NBINS+1));th1wwa2->SetBinContent(pv.NBINS+1,0.);

    treewza->Draw(TString(pv.plotvar)+TString(">>th1wza"), the_cut, "goff");
    th1wza->AddBinContent(pv.NBINS,th1wza->GetBinContent(pv.NBINS+1));th1wza->SetBinContent(pv.NBINS+1,0.);

    treezz->Draw(TString(pv.plotvar)+TString(">>th1zz"), the_cut, "goff");
    th1zz->AddBinContent(pv.NBINS,th1zz->GetBinContent(pv.NBINS+1));th1zz->SetBinContent(pv.NBINS+1,0.);

    // Get WJets

    TH1* th1wajets  = new TH1D("th1wajets",  "th1wajets",  pv.NBINS ,pv.MINRange,pv.MAXRange);
    TH1* th1wajetsSQ  = new TH1D("th1wajetsSQ",  "th1wajetsSQ",  pv.NBINS ,pv.MINRange,pv.MAXRange);
    th1wajets->Sumw2();

    treewaj->Draw(TString(pv.plotvar)+TString(">>th1wajets"), the_cut, "goff");
    th1wajets->AddBinContent(pv.NBINS,th1wajets->GetBinContent(pv.NBINS+1));th1wajets->SetBinContent(pv.NBINS+1,0.);

    for(int hi=1;hi<=pv.NBINS;hi++) {
        fperr = (th1wajets->GetBinError(hi))*(th1wajets->GetBinError(hi));
        fperr + = 0.086*0.086*(th1wajets->GetBinContent(hi))*(th1wajets->GetBinContent(hi));
        th1wajets->SetBinError(hi,sqrt(fperr));
        th1AQGC->SetBinError(hi,0.0001);
    }
	

    // Get ttbar
 
    TH1* th1Top = new TH1D("th1Top", "th1Top", pv.NBINS, pv.MINRange, pv.MAXRange);
    th1Top->Sumw2();
  
    treettba->Draw(TString(pv.plotvar)+TString(">>th1Top"), the_cut, "goff");
    th1Top->AddBinContent(pv.NBINS,th1Top->GetBinContent(pv.NBINS+1));th1Top->SetBinContent(pv.NBINS+1,0.);

    // Get QCD

    TH1* th1qcd = new TH1D("th1qcd", "th1qcd", pv.NBINS, pv.MINRange, pv.MAXRange);
    th1qcd->Sumw2();
 
    treeqcd->Draw(TString(pv.plotvar)+TString(">>th1qcd"), the_cut, "goff");
    th1qcd->AddBinContent(pv.NBINS,th1qcd->GetBinContent(pv.NBINS+1));th1qcd->SetBinContent(pv.NBINS+1,0.);

    

    int n2 = treeqcd->Draw(TString(pv.plotvar),  the_cut, "goff");
    int n3 = treeqcd->Draw(TString(pv.plotvar),  the_cut3 , "goff");

    std::cout << "got qcd " << " n2 " << n2 <<  " n3  " << n3 <<std::endl; 



    // Get Z+Jets

    TH1* th1zajets = new TH1D("th1zajets", "th1zajets", pv.NBINS, pv.MINRange, pv.MAXRange);
    th1zajets->Sumw2();
    treezaj->Draw(TString(pv.plotvar)+TString(">>th1zajets"), the_cut, "goff");
    th1zajets->AddBinContent(pv.NBINS,th1zajets->GetBinContent(pv.NBINS+1));th1zajets->SetBinContent(pv.NBINS+1,0.);

    // Get Single top

    TH1* th1stops = new TH1D("th1stops", "th1stops", pv.NBINS, pv.MINRange, pv.MAXRange);
    TH1* th1stopt = new TH1D("th1stopt", "th1stopt", pv.NBINS, pv.MINRange, pv.MAXRange);
    TH1* th1stoptw = new TH1D("th1stoptw", "th1stoptw", pv.NBINS, pv.MINRange, pv.MAXRange);
    th1stops->Sumw2();
    th1stopt->Sumw2();
    th1stoptw->Sumw2();

    treests->Draw(TString(pv.plotvar)+TString(">>th1stops"), the_cut, "goff");
    th1stops->AddBinContent(pv.NBINS,th1stops->GetBinContent(pv.NBINS+1));th1stops->SetBinContent(pv.NBINS+1,0.);
    treestt->Draw(TString(pv.plotvar)+TString(">>th1stopt"), the_cut, "goff");
    th1stopt->AddBinContent(pv.NBINS,th1stopt->GetBinContent(pv.NBINS+1));th1stopt->SetBinContent(pv.NBINS+1,0.);
    treestw->Draw(TString(pv.plotvar)+TString(">>th1stoptw"), the_cut, "goff");
    th1stoptw->AddBinContent(pv.NBINS,th1stoptw->GetBinContent(pv.NBINS+1));th1stoptw->SetBinContent(pv.NBINS+1,0.);


    TFile* stopps_file =  new TFile("InData/RD_el_STopS_Tbar_CMSSW532.root", "READ");
    TTree* tree64 = (TTree*) stopps_file->Get("WJet");
    TFile* stoppt_file =  new TFile("InData/RD_el_STopT_Tbar_CMSSW532.root", "READ");
    TTree* tree65 = (TTree*) stoppt_file->Get("WJet");
    TFile* stopptW_file =  new TFile("InData/RD_el_STopTW_Tbar_CMSSW532.root", "READ");
    TTree* tree66 = (TTree*) stopptW_file->Get("WJet");
    TH1* th1stopps = new TH1D("th1stopps", "th1stopps", pv.NBINS, pv.MINRange, pv.MAXRange);
    TH1* th1stoppt = new TH1D("th1stoppt", "th1stoppt", pv.NBINS, pv.MINRange, pv.MAXRange);
    TH1* th1stopptw = new TH1D("th1stopptw", "th1stopptw", pv.NBINS, pv.MINRange, pv.MAXRange);
    th1stopps->Sumw2();
    th1stoppt->Sumw2();
    th1stopptw->Sumw2();
    tree64->Draw(TString(pv.plotvar)+TString(">>th1stopps"), the_cut, "goff");
    th1stopps->AddBinContent(pv.NBINS,th1stopps->GetBinContent(pv.NBINS+1));th1stopps->SetBinContent(pv.NBINS+1,0.);

    tree65->Draw(TString(pv.plotvar)+TString(">>th1stoppt"), the_cut, "goff");
    th1stoppt->AddBinContent(pv.NBINS,th1stoppt->GetBinContent(pv.NBINS+1));th1stoppt->SetBinContent(pv.NBINS+1,0.);

    tree66->Draw(TString(pv.plotvar)+TString(">>th1stopptw"), the_cut, "goff");
    th1stopptw->AddBinContent(pv.NBINS,th1stopptw->GetBinContent(pv.NBINS+1));th1stopptw->SetBinContent(pv.NBINS+1,0.);


    // Setup the canvas

//    gROOT->ProcessLine(".L tdrstyle.C");
    setTDRStyle();
    tdrStyle->SetErrorX(0.5);
    tdrStyle->SetPadRightMargin(0.05);

    tdrStyle->SetLegendBorderSize(0);

    th1data->Sumw2();
    th1fkdata->Sumw2();


    TCanvas* c1 = new TCanvas(pv.plotvar,pv.plotvar,10,10, 800, 800);
    TPad *d1, *d2;

    c1->Divide(1,2,0,0);
    d1 = (TPad*)c1->GetPad(1);
    d1->SetPad(0.01,0.30,0.95,0.99);
    d2 = (TPad*)c1->GetPad(2);
    d2->SetPad(0.01,0.02,0.95,0.30);

    // Setup the stack, scale the histos

    THStack* hs = new THStack("hs","MC contribution");

    th1fkdata->SetFillColor(kBlue+1);
    th1fkdata->SetLineColor(kBlue+1);
    th1fkdata->SetLineWidth(0);

    th1Top->Scale(ttbara_scale);
    th1Top->SetFillColor(kGreen+2);
    th1Top->SetLineColor(kGreen+2);
    th1Top->SetLineWidth(0);

    th1stops->Scale(STopS_scale);
    th1stops->SetFillColor(7);
    th1stops->SetLineWidth(2);
    th1stopps->Scale(SToppS_scale);
    th1stopps->SetFillColor(7);
    th1stopps->SetLineWidth(2);
    th1stopt->Scale(STopT_scale);
    th1stopt->SetFillColor(13);
    th1stopt->SetLineWidth(2);
    th1stoppt->SetLineWidth(2);
    th1stoppt->Scale(SToppT_scale);
    th1stoppt->SetFillColor(13);
    th1stoptw->Scale(STopTW_scale);
    th1stoptw->SetFillColor(9);
    th1stoptw->SetLineWidth(2);
    th1stopptw->Scale(SToppTW_scale);
    th1stopptw->SetFillColor(9);
    th1stopptw->SetLineWidth(2);

    th1wajets->Scale(WAJets_scale);
    th1wajets->SetFillColor(kRed);
    th1wajets->SetLineColor(kRed);
    th1wajets->SetLineWidth(0);
    th1wwa->Scale(WWA_scale);
    th1wwa2->Scale(WWA2_scale);
    th1wwa->Add(th1wwa2,1.);
    th1wwa->SetFillColor(17);
    th1wwa->SetLineColor(17);
    th1wwa->SetLineWidth(0);
    th1wza->Scale(WZA_scale);
    th1wza->SetFillColor(11);
    th1wza->SetLineWidth(0);
    th1zz->Scale(ZZ_scale);
    th1zz->SetFillColor(kAzure+8);
    th1zz->SetLineColor(kAzure+8);
    th1zz->SetLineWidth(0);
  
    th1qcd->SetFillColor(1);
    th1qcd->SetLineColor(1);
    th1qcd->SetLineWidth(0);
    th1zajets->Scale(ZAJets_scale);
    th1zajets->SetFillColor(kYellow);
    th1zajets->SetLineColor(kYellow);
    th1zajets->SetLineWidth(0);
    std::cout << "tt "   << th1Top->Integral()   << std::endl;
    std::cout << "wwa "   << th1wwa->Integral()    << std::endl;
    std::cout << "wza "   << th1wza->Integral()    << std::endl;
    std::cout << "wa+jets "   << th1wajets->Integral()    << std::endl;
    std::cout << "zz "   << th1zz->Integral()    << std::endl;
    std::cout << "za+jets "    << th1zajets->Integral() << std::endl;
  
    double den_qcd = 
      th1Top->Integral()+
      th1stops->Integral()+
      th1stopt->Integral()+
      th1stoptw->Integral()+
      th1stopps->Integral()+
      th1stoppt->Integral()+
      th1stopptw->Integral()+
      th1wajets->Integral()+
      th1wwa->Integral()+
      th1wza->Integral()+
      th1zz->Integral()+
      th1fkdata->Integral()+
      th1zajets->Integral();

    double qcd_scale;

//      qcd_scale = (n2*0.0637 + n3*0.02) / (n2+n3); //electron
      qcd_scale = 0.0637 ; //electron

    std::cout << " qcd_scale  " << qcd_scale <<std::endl;
    if(th1qcd->Integral()>0.)
       th1qcd->Scale(qcd_scale*den_qcd/th1qcd->Integral()); 

    double den = 
      th1Top->Integral()+
      th1stops->Integral()+
      th1stopt->Integral()+
      th1stoptw->Integral()+
      th1stopps->Integral()+
      th1stoppt->Integral()+
      th1stopptw->Integral()+
      th1wajets->Integral()+
      th1wwa->Integral()+
      th1wza->Integral()+
      th1zz->Integral()+
      th1qcd->Integral()+
      th1fkdata->Integral()+
      th1zajets->Integral();

    std::cout << "den = " <<den <<std::endl;
    std::cout <<" data " <<  th1data->Integral() << std::endl;
    std::cout <<" fake pho " <<  th1fkdata->Integral() << std::endl;
    std::cout << "qcd " << th1qcd->Integral()   << std::endl;
/*
    th1qcd->Scale   (th1data->Integral()/den); std::cout <<"qcd "   << th1qcd->Integral()   << std::endl;
    th1Top->Scale   (th1data->Integral()/den); std::cout <<"tt "    << th1Top->Integral()   << std::endl;
    th1stops->Scale (th1data->Integral()/den); std::cout <<"stops " << th1stops->Integral() << std::endl;
    th1stopt->Scale (th1data->Integral()/den); std::cout <<"stopt " << th1stopt->Integral() << std::endl;
    th1stoptw->Scale(th1data->Integral()/den); std::cout <<"stoptw "<< th1stoptw->Integral()<< std::endl;
    th1stopps->Scale (th1data->Integral()/den); std::cout <<"stops " << th1stopps->Integral() << std::endl;
    th1stoppt->Scale (th1data->Integral()/den); std::cout <<"stopt " << th1stoppt->Integral() << std::endl;
    th1stopptw->Scale(th1data->Integral()/den); std::cout <<"stoptw "<< th1stopptw->Integral()<< std::endl;
    th1wajets->Scale (th1data->Integral()/den); std::cout <<"wjets " << th1wajets->Integral() << std::endl;
    th1wwa->Scale    (th1data->Integral()/den); std::cout <<"wwa "    << th1wwa->Integral()    << std::endl;
    th1wza->Scale    (th1data->Integral()/den); std::cout << "wza "   << th1wza->Integral()    << std::endl;
    th1zz->Scale    (th1data->Integral()/den); std::cout << "zz "   << th1zz->Integral()    << std::endl;
    th1zajets->Scale (th1data->Integral()/den); std::cout << "za "    << th1zajets->Integral() << std::endl;
*/
    double den2 =
      th1Top->Integral()+
      th1stops->Integral()+
      th1stopt->Integral()+
      th1stoptw->Integral()+
      th1stopps->Integral()+
      th1stoppt->Integral()+
      th1stopptw->Integral()+
      th1wajets->Integral()+
      th1wwa->Integral()+
      th1wza->Integral()+
      th1zz->Integral()+
      th1qcd->Integral()+
      th1fkdata->Integral()+
      th1zajets->Integral();

    std::cout << "den2 " << den2 << std::endl;

    th1Top->Add(th1stoptw,1);
    th1Top->Add(th1stopt,1);
    th1Top->Add(th1stops,1);
    th1Top->Add(th1stopptw,1);
    th1Top->Add(th1stoppt,1);
    th1Top->Add(th1stopps,1);
    th1wwa->Add(th1wza,1);

    // Sum all the backgrounds

    TH1D *th1tot = (TH1D*)th1wajets->Clone("th1tot");
    th1tot->Reset();
    th1tot->Add(th1qcd,1);
    th1tot->Add(th1Top,1);
    th1tot->Add(th1wajets,1);
    th1tot->Add(th1zajets,1);
    th1tot->Add(th1zz,1);
    th1tot->Add(th1fkdata,1);
    TH1D *th1totAC = (TH1D*)th1tot->Clone();
    th1tot->Add(th1wwa,1);

    th1totAC->Add(th1AQGC,1);
    th1totAC->SetMarkerStyle(0);
    th1totAC->SetFillStyle(0);
    th1totAC->SetLineColor(1);
    th1totAC->SetLineWidth(3);

    th1AQGC->Scale(20);

    TH1D* th1totClone = ( TH1D*) th1tot->Clone("th1totClone");
    th1totClone->SetMarkerStyle(0);
    th1totClone->SetFillStyle(3003);
    th1totClone->SetFillColor(1);
    th1totClone->SetLineColor(0);
    double binErr(0.0);
    for(int i=0; i<th1totClone->GetNbinsX(); ++i) {
      binErr = sqrt(
                    (th1zz->GetBinError(i))**2 +
                    (th1wwa->GetBinError(i))**2 +
		    (th1qcd->GetBinError(i))**2 +
		    (th1Top->GetBinError(i))**2 +
		    (th1wajets->GetBinError(i))**2+
		    (th1zajets->GetBinError(i))**2);
      th1totClone->SetBinError(i, binErr);
      th1totAC->SetBinError(i+1, 0.000001);

    }

    // Compose the stack

    hs->Add(th1wwa);
    d1->cd();
    gPad->SetBottomMargin(0.0);
    gPad->SetTopMargin(0.1);
    gPad->SetRightMargin(0.05);
    gPad->SetLeftMargin(0.14);

    hs->Add(th1wajets);
    hs->Add(th1zajets);
    hs->Add(th1Top);
    hs->Add(th1zz);
    hs->Add(th1qcd);
    hs->Add(th1fkdata);

    // Set up the legend

    float  legX0=0.65, legX1=0.99, legY0=0.64, legY1=0.88;
    float  leg1X0=0.15, leg1X1=0.60, leg1Y0=0.64, leg1Y1=0.88;
//    float  legX0=0.65, legX1=0.99, legY0=0.4, legY1=0.88;
    // float  legX0=0.35, legX1=0.85, legY0=0.4, legY1=0.88;
    // float  legX0=0.18, legX1=0.52, legY0=0.4, legY1=0.88;
    TLegend * Leg = new TLegend( legX0, legY0, legX1, legY1);
    TLegend * Leg1 = new TLegend( leg1X0, leg1Y0, leg1X1, leg1Y1);
    Leg->SetFillColor(0);
    Leg->SetFillStyle(0);
    Leg->SetTextSize(0.04);
    Leg1->SetFillColor(0);
    Leg1->SetFillStyle(0);
    Leg1->SetTextSize(0.04);
    Leg1->AddEntry(th1data,  "Electron Data",  "PLE");
    Leg1->AddEntry(th1tot,  "MC Uncertainty",  "f");
    Leg->AddEntry(th1fkdata, "fake #gamma", "f");
    Leg->AddEntry(th1qcd,  "multijet",  "f");
    Leg->AddEntry(th1Top,  "top",  "f");
    Leg->AddEntry(th1zajets,  "Z#gamma+Jets",  "f");
    Leg1->AddEntry(th1wajets,  "W#gamma+jets",  "f");
    Leg->AddEntry(th1wwa,  "WW/WZ+#gamma ",  "f");
    Leg1->AddEntry(th1totAC,  "BG+a_{0}^{W} / #Lambda^{2} = -5x10^{-5}",  "l");
//    Leg1->AddEntry(th1AQGC,  "a_{0}^{W} / #Lambda^{2} = -5x10^{-5} x 20",  "l");

//    Leg->AddEntry(th1zz,  "ZZ",  "f");

//    if(pv.hplot==1) Leg->AddEntry(th1H500,  "H (500) x 10",  "L");
    Leg->SetFillColor(0);
    Leg1->SetFillColor(0);

/*
    th1H500->SetLineColor(kBlack);
    th1H500->SetLineWidth(3);
    th1H500->Scale(10);
*/

    TH1* th1totempty = new TH1D("th1totempty", "th1totempty", pv.ANBINS, pv.AMINRange, pv.AMAXRange);
    th1data->SetMarkerStyle(20);
    th1data->SetMarkerSize(1.25);
    th1data->SetLineWidth(2);

    th1tot->SetFillStyle(3001);
    th1tot->SetFillColor(1);
    th1tot->SetLineColor(1);
    th1tot->SetMarkerStyle(0);


    char tmpc[100];    sprintf(tmpc,"Events / %.1f GeV",BINWIDTH);
    if (pv.slog==1)    sprintf(tmpc,"Events/ %.1f",BINWIDTH);
    if (pv.slog==2)    sprintf(tmpc,"Events/ %.2f",BINWIDTH);
    if (pv.slog==3)    sprintf(tmpc,"Events/ %.0f GeV",BINWIDTH);
    if (pv.slog==6)    sprintf(tmpc,"Events/ %.1f rad",BINWIDTH);
    th1totempty->SetYTitle(tmpc);
    //  th1totempty->GetYaxis()->SetTitleSize(0.1);
    th1totempty->GetYaxis()->SetTitleOffset(1.2);
    th1totempty->GetYaxis()->SetLabelOffset(0.01);
    //  th1totempty->GetYaxis()->CenterTitle(true);
    th1totempty->GetYaxis()->SetLabelSize(0.04);
    // th1totClone->Draw("e3");   

    th1tot->SetMinimum(0.01);
    int maxbin = th1data->GetMaximumBin();
    float maxval = th1data->GetBinContent(maxbin);
    std::cout << "maxval " <<maxval <<std::endl;
    th1totempty->SetMaximum(1.99*maxval);
    th1totempty->SetMinimum(0.01);
    if(pv.slog==1) th1totempty->SetMaximum(1.99*maxval);
    th1data->SetMinimum(0.01);

    // Draw it all

    th1totempty->Draw();
    //th1tot->Draw("e2same");
    th1data->Draw("esame");
    hs->Draw("samehist");
//    if (pv.hplot ==1) th1H500->Draw("same");
    th1tot->Draw("e2same");
    th1totAC->Draw("hsame");
//    th1AQGC->Draw("hsame");

    th1data->Draw("esame");
    cmspre(intLUMI/1000.0);
    if (pv.drawleg ==1)  Leg->Draw();  
    if (pv.drawleg ==1)  Leg1->Draw();  
    // th1data->Draw("Axissame");
    gPad->RedrawAxis();
    d2->cd();

    TH1F    * hhratio    = (TH1F*) th1data->Clone("hhratio")  ;
    hhratio->Sumw2();

    gPad->SetLeftMargin(0.14);
    gPad->SetTopMargin(0);
    gPad->SetRightMargin(0.05);
    gPad->SetFrameBorderSize(0);
    gPad->SetBottomMargin(0.3);
    gPad->SetTickx();

    hhratio->SetMarkerSize(1.25);
    //  hhratio->GetYaxis()->SetRangeUser(0.001,3.52);
    hhratio->GetYaxis()->SetRangeUser(0.3,1.7);
    hhratio->GetXaxis()->SetTitle(pv.xlabel);
    hhratio->GetXaxis()->SetTitleOffset(0.9);
    hhratio->GetXaxis()->SetTitleSize(0.15);
    hhratio->GetXaxis()->SetLabelSize(0.15);
    hhratio->SetYTitle("Ratio Data/MC");
    hhratio->GetYaxis()->SetTitleSize(0.1);
    hhratio->GetYaxis()->SetTitleOffset(0.5);
    hhratio->GetYaxis()->CenterTitle(true);
    hhratio->GetYaxis()->SetLabelSize(0.1);
    std::cout << hhratio->GetNbinsX() << std::endl;
    std::cout << th1tot->GetNbinsX() << std::endl;
    hhratio->Divide(th1tot);
    double binError(0.0), mcbinentry(0.0), mcerror(0.0);
    for(int i=0; i<hhratio->GetNbinsX(); ++i) {
      binError = hhratio->GetBinError(i);
      mcerror = th1tot->GetBinError(i);
      mcbinentry = th1tot->GetBinContent(i);
      if(mcbinentry>0.) mcerror /= mcbinentry;
      else mcerror = 0.0;
      binError = sqrt(binError**2 + mcerror**2);
      hhratio->SetBinError(i, binError);
    }
    TH1D *th1emptyclone = new TH1D("th1emptyclone", "th1emptyclone", pv.ANBINS, pv.AMINRange, pv.AMAXRange);
    th1emptyclone->GetYaxis()->SetRangeUser(0.001,2.999);
    th1emptyclone->GetXaxis()->SetTitle(pv.xlabel);
    th1emptyclone->GetXaxis()->SetTitleOffset(0.9);
    th1emptyclone->GetXaxis()->SetTitleSize(0.15);
    th1emptyclone->GetXaxis()->SetLabelSize(0.15);
    th1emptyclone->SetYTitle("Ratio Data/MC");
    th1emptyclone->GetYaxis()->SetTitleSize(0.1);
    th1emptyclone->GetXaxis()->SetNdivisions(505);
    th1emptyclone->GetYaxis()->SetNdivisions(505);
    th1emptyclone->GetYaxis()->SetTitleOffset(0.5);
    th1emptyclone->GetYaxis()->CenterTitle(true);
    th1emptyclone->GetYaxis()->SetLabelSize(0.1);
    th1emptyclone->Draw();
    errbox->Draw();
    hhratio->Draw("esame");
    TLine *line; line = new TLine(pv.AMINRange,1.0,pv.AMAXRange,1.0);
    line->SetLineStyle(1);
    line->SetLineWidth(1);
    line->SetLineColor(1);
    line->Draw();

    TString outfile = TString("OutDir/")+(domu?TString("mu_"):TString("el_"))+TString(pv.outfile);

    c1->Print(outfile+".png");
    c1->Print(outfile+".C");
    //gPad->WaitPrimitive();
    c1->Modified();
    c1->Update();
    c1->SaveAs(outfile+".pdf"); 
    d1->cd(); gPad->SetLogy();
    c1->Print(outfile+"_log.png");
    c1->Print(outfile+"_log.pdf");

  } // var loop

  // f.Write();

}

