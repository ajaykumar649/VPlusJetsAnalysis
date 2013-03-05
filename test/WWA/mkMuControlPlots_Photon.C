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
/*

*/
void cmspre(double intlumifbinv)
{
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);

  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.85,0.93,"#sqrt{s} = 8 TeV");
  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.65,0.93,Form("#int #font[12]{L} dt = %.1f fb^{-1}", (float)intlumifbinv));
//  latex.DrawLatex(0.65,0.93,Form("2012B", (float)intlumifbinv));

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

void mkMuControlPlots_Photon(bool domu=true,bool domva=false,
		    bool dovbf=false)
{
    gROOT->ProcessLine(".L tdrstyle.C");

  const double intLUMI = 19300.;
//  const double WWASM_scale   = 8.782*0.115*1.5*2.* intLUMI/194504; // V
// hack for WWA 
  const double WWASM_scale   = (0.01362+0.01409)*1.5 *intLUMI/(198777+199183); // V
// RD_mu_WWA6m5m5MG_CMSSW532.root
  const double AQGC_scale   = 0.047*1.5* intLUMI/194029 ; // V
  const double H500_scale   = 1.439*0.080*1.5*2.* intLUMI/198470 ; // V

//  const double WJets_scale   = 36257.2* intLUMI/18353019; // V
//  const double WJets_scale   = 461.6* intLUMI/4802339; // V
  const double WJets_scale   = 1.108*9.37246* intLUMI/1049473; // V
  const double W4Jets_scale  = 172.6 * intLUMI/5000700;
  const double WWA_scale     = 1.5*0.01362   * intLUMI/198777; // V
  const double WWA2_scale     = 1.5*0.01409   * intLUMI/199183; // V
  const double WW_scale      = 0.*54.838   * intLUMI/9450414; // V
//  const double WZ_scale      = 32.3161   * intLUMI/10000267; // V
  const double WZ_scale      = 0.00578008*1.5 * intLUMI/497450; // WZA
  const double ZZ_scale      = 8.059   * intLUMI/9702850; // V
  const double ZAJets_scale  = 0.63196 * intLUMI/979207; // V

  const double QCD_scale     = 364000000 *    0.00037 * intLUMI/7529312 ; // V
  const double ZJets_scale   = 3503.71  * intLUMI/30209426; // V
  const double ttbar_scale   = 1.44 * intLUMI/604113; // V
  const double SToppS_scale  = 1.75776  * intLUMI/139974; // V anti-top
  const double SToppT_scale  = 30.0042  * intLUMI/1935066; // V
  const double SToppTW_scale = 11.1773  * intLUMI/493458; // V
  const double STopS_scale   = 3.89394  * intLUMI/259960; // top
  const double STopT_scale   = 55.531  * intLUMI/3758221; //V
  const double STopTW_scale  = 11.1773  * intLUMI/497657; // V



  const plotVar_t plotvars[] = {

  //    plotvar	MINRange  MAXRange  NBINS  slog xlabel outfile AMINRange  AMAXRange ANBINS mva_in hplot drawleg


//    { "Photon_SigmaIetaIeta[iPhoton11]",         0.005,  0.014, 100, 3,  "SigmaIetaIeta",     "Photon_SigmaIetaIeta",       0.005,  0.014, 100, 0, 0, 0 },
    { "mva2jWWAmuA",     -0.25, 0.95, 12, 3, "mva2jWWAmuA",  "mva2jWWAmuA",      -0.3, 1.0, 13, 0, 1, 1 },
    { "mva2jWWAmuA",     -0.25, 0.95, 24, 3, "mva2jWWAmuA1",  "mva2jWWAmuA1",      -0.3, 1.0, 26, 0, 1, 1 },
    { "mva2jWWAmuA",     -0.25, 0.95, 48, 3, "mva2jWWAmuA2",  "mva2jWWAmuA2",      -0.3, 1.0, 52, 0, 1, 1 },
    { "c2jMass11",     10, 430, 14, 3,   "m_{jj} (GeV)",            "mjj1",       10,  430, 14, 0, 1, 1},
    { "c2jMass11",     70, 100, 30, 3,   "m_{jj} (GeV)",            "mjj",       65,  105, 40, 0, 1, 1},
    { "masslvjja",  150, 1550, 28, 3, "M_{l#nujj#gamma}", "mlvjja", 150, 1550, 28, 0, 0, 1},
    { "masslvjja",  150, 1250, 11, 3, "M_{l#nujj#gamma}", "mlvjja1", 150, 1250, 11, 0, 0, 1},
    { "masslvjja",  150, 1350, 6, 3, "M_{l#nujj#gamma}", "mlvjja2", 150, 1350, 6, 0, 0, 1},
    { "mva2jWWAmuM",     -0.5, 0.9, 14, 3, "mva2jWWAmuM",  "mva2jWWAmuM",      -0.6, 1.0, 16, 0, 1, 1 },
    { "Photon_Et[iPhoton11]",         10, 260, 25, 3,  "Photon p_{T} (GeV)",     "Photon_et",       20,  260, 24, 0, 0, 0 },
    { "Photon_Et[iPhoton11]",         30, 270, 12, 3,  "Photon p_{T} (GeV)",     "Photon_et1",       30,  270, 12, 0, 0, 1 },
    { "Photon_Et[iPhoton11]",         30, 310, 7, 3,  "Photon p_{T} (GeV)",     "Photon_et2",       30,  310, 6, 0, 0, 0 },
    { "mva2jWWAmu",     -0.5, 0.9, 14, 3, "mva2jWWAmu",  "mva2jWWAmu",      -0.6, 1.0, 16, 0, 1, 1 },
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
    { "Photon_Et[iPhoton11]/W_muon_pt",0,10,10,3,"#gamma_{p_{T}}:l_{p_{T}}","gammapt_mupt",0,10,10,1,0,0},
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
    { "abs(W_muon_phi-Photon_Phi[iPhoton11])",  0, 6.28, 20, 3,   " |#Delta#phi(#gamma,l)| ",  "event_lep_pho_dphi",     0, 6.28, 20, 0, 0, 0 },

    { "(W_muon_eta-Photon_Eta[iPhoton11])",  -3.2,  3.2, 16, 3,   " #Delta#eta(#gamma,l) ",  "event_lep_pho_deta",     -3.2,  3.2, 16, 0, 0, 0 },
    { "(JetPFCor_Eta[i11Jet1]-Photon_Eta[iPhoton11])",  -3.2,  3.2, 16, 3,   " #Delta#eta(#gamma,J1) ",  "event_j1_pho_deta",     -3.2,  3.2, 16, 0, 0, 0 },
    { "(JetPFCor_Eta[i11Jet2]-Photon_Eta[iPhoton11])",  -3.2,  3.2, 16, 3,   " #Delta#eta(#gamma,J2) ",  "event_j2_pho_deta",     -3.2,  3.2, 16, 0, 0, 0 },

   { "event_met_pfsumet",  0, 2000, 40, 3,   "pf SET (GeV)",  "event_met_pfsumet",     0, 2000, 40, 0, 0, 0 },
    { "event_met_pfmetPhi",  -3.14, 3.14, 26, 3,   "pf MET #phi",  "event_met_pfmetPhi",     -3.14, 3.14, 26, 0, 0, 0 },
    { "event_metMVA_metPhi",  -3.14, 3.14, 26, 3,   "MVA MET #phi ",  "event_metMVA_metPhi",     -3.14, 3.14, 26, 0, 0, 0 },
    { "event_met_pfmet",  25, 155, 13, 3,   "pf MET (GeV)",  "event_met_pfmet",     15, 155, 14, 0, 0, 0 },
    { "event_metMVA_met",  25, 155, 13, 3,   "MVA MET (GeV)",  "event_metMVA_met",     15, 155, 14, 0, 0, 0 },
    { "W_muon_charge",    -1.2, 1.2, 24, 1, "Muon Charge" ,      "charge",   -1.2, 1.2, 24, 1, 0, 0 },

    { "sqrt((JetPFCor_Px[i11Jet1]+JetPFCor_Px[i11Jet2])**2+(JetPFCor_Py[i11Jet1]+JetPFCor_Py[i11Jet2])**2)",
                          15, 205, 19, 3,   "Dijet System p_{T} (GeV)", "dijet_pt", 5, 205, 20, 0, 0, 0},  

    { "(JetPFCor_Eta[i11Jet1]-JetPFCor_Eta[i11Jet2])",
                         -3.0, 3.0, 15, 1,  "#Delta #eta (j,j)",    "deltaeta_jj",   -3.2,  3.2, 16, 0, 0, 0 },
    { "W_muon_pt",         15, 155, 14, 3,  "Muon p_{T} (GeV)",     "W_muon_pt",       25,  155, 13, 0, 0, 0 },
    { "W_muon_eta",      -2.7, 2.7, 18, 1,  "Muon #eta",            "W_muon_eta",    -2.4,  2.4, 16, 0, 0, 0 },
    { "ptlvjj",              0, 150, 15, 3, "p_{T} of WW (GeV)", "ptlvjj",      0, 150, 15, 1, 0, 0 },
    { "ylvjj",            -2.5, 2.5, 25, 1, "WW rapidity" ,      "etalvjj",  -3.0, 3.0, 30, 1, 0, 0 },
    { "ang_ha",              0,   1,  5, 1, "Cos #theta_{1}" ,   "ha",          0,   1,  5, 1, 0, 1 },
    { "ang_hb",              0,   1,  5, 1, "Cos #theta_{2}" ,   "hb",          0,   1,  5, 1, 0, 0 },
    { "ang_hs",           -1.0,   1, 20, 1, "Cos #theta*" ,      "hs",       -1.0,   1, 20, 1, 0, 0 },
    { "ang_phi",          -3.2, 3.2, 16, 6, "#Phi (rad)" ,       "phi",      -3.6, 3.6, 18, 1, 0, 0 },
    { "ang_phib",         -3.2, 3.2, 16, 6, "#Phi_{1} (rad)",    "phib",     -3.6, 3.6, 18, 1, 0, 0 },
    { "W_muon_charge",    -1.2, 1.2, 24, 1, "Muon Charge" ,      "charge",   -1.2, 1.2, 24, 1, 0, 0 },



    { "sqrt((JetPFCor_Eta[i11Jet1]-JetPFCor_Eta[i11Jet2])**2+(abs(abs(abs(JetPFCor_Phi[i11Jet1]-JetPFCor_Phi[i11Jet2])-TMath::Pi())-TMath::Pi()))**2)",
                             0.4, 5.0, 23, 1, "#Delta R_{jj}",    "deltaRjj", 0.0, 5.4, 27, 0, 0, 1},

    { "", 0.0,0.0,0,0,"","",0.,0.,0.,0,0,0 }
  };


////////////////////////////////////////////higgs
  const plotVar_t higgsplotvars[] = {
  //    plotvar MINRange  MAXRange  NBINS  slog xlabel     outfile  AMINRange  AMAXRange ANBINS mva_in hplot drawleg

    { "MassV2j_PFCor",     140, 700, 14, 3, "m_{l#nujj} (GeV)",  "mlvjj",     100, 700, 15, 0, 1, 1 },
    { "MassV2j_PFCor_MVAMET",     140, 700, 14, 3, "m_{l#nujj} (GeV) MVA MET",  "mlvjjMVA",     100, 700, 15, 0, 1, 1 },
    { "mva2j500mu",       -0.2, 1.2, 28, 2, "Likelihood discriminant ( M_{H}=500 GeV )",   "mva2j500",  -0.2, 1.2, 28, 0, 1, 1 },
    { "mva2j190mu",          0,   1, 25, 2, "Likelihood discriminant ( M_{H}=190 GeV ) ",  "mva2j190", -0.1, 1.4, 30, 0, 1, 1 },
    { "mva2j350mu",          0,   1, 25, 2, "Likelihood discriminant ( M_{H}=350 GeV )",  "mva2j350_top", 0,   1, 10, 0, 0, 1 },
/*
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
    { "W_muon_charge",    -1.2, 1.2, 24, 1, "Muon Charge" ,      "vbfWmucharge",   -1.2, 1.2, 24, 1, 0, 0 },
    { "vbf_jj_deta",         3, 9.0, 30, 1, "Tagjet  #Delta#eta",    "vbftagjet_deta",      3,  9.0, 30, 1, 0, 0 },
    { "vbf_jj_m",         300, 1200, 18, 3, "Tagjet Invariant Mass (GeV)", "vbftagjet_mass", 200,  1200, 20, 1, 0, 0 },

    { "mvavbf500mu",       -0.2, 1.2, 28, 2, "Likelihood Output ",       "vbfmva500",  -0.2, 1.2, 28, 0, 0, 1 },
    { "mvavbf350mu",          0,   1, 25, 2, "Likelihood Output mu350 ", "vbfmva350",     0,   1, 10, 0, 0, 1 },
    { "mvavbf180el",          0,   1, 25, 2, "Likelihood Output el180 ", "vbfmva180",     0,   1, 10, 0, 0, 1 },
#endif
    { "", 0.0,0.0,0,0,"","",0.,0.,0,0,0 }
  };

  //  const char* the_cut = "1";
  //  double BINWIDTH = ((MAXRange-MINRange)/NBINS);


//  TCut the_cutFF("(1./(1.+1./(0.0345868 + 1.44022E04/((Photon_Et[iPhoton11])^2.89994))))*");
//  TCut the_cut("effwt*puwt*(iPhoton11>-1&&Photon_Et[iPhoton11]>30.&&i11Jet2>-1&&i11Jet1>-1&&JetPFCor_dRpho11[i11Jet1]>0.5&&JetPFCor_dRpho11[i11Jet2]>0.5&&abs(W_muon_eta)<2.1&&abs(JetPFCor_dphiMET[i11Jet1])>0.4&& abs(JetPFCor_dphiMET[i11Jet2])>0.4&&i11Jet3<0&&JetPFCor_bDiscriminatorCSV[i11Jet1]<0.679&&JetPFCor_bDiscriminatorCSV[i11Jet2]<0.679&&abs(JetPFCor_Eta[i11Jet1]-JetPFCor_Eta[i11Jet2])<1.4&&abs(Photon_Eta[iPhoton11])<1.44421&&W_muon_pt>25&&event_met_pfmet>25.&&c2jMass11>72.&&c2jMass11<98.&&W_mt>30.&&abs(W_muon_dz000)<0.02&&abs(W_muon_dzPV)<0.5&&mva2jWWAmuA>0.15)");
  TCut the_cut("effwt*puwt*(iPhoton11>-1&&Photon_Et[iPhoton11]>30.&&i11Jet2>-1&&i11Jet1>-1&&JetPFCor_dRpho11[i11Jet1]>0.5&&JetPFCor_dRpho11[i11Jet2]>0.5&&abs(W_muon_eta)<2.1&&abs(JetPFCor_dphiMET[i11Jet1])>0.4&& abs(JetPFCor_dphiMET[i11Jet2])>0.4&&i11Jet3<0&&JetPFCor_bDiscriminatorCSV[i11Jet1]<0.679&&JetPFCor_bDiscriminatorCSV[i11Jet2]<0.679&&abs(JetPFCor_Eta[i11Jet1]-JetPFCor_Eta[i11Jet2])<1.4&&abs(Photon_Eta[iPhoton11])<1.44421&&W_muon_pt>25&&event_met_pfmet>25.&&c2jMass11>72.&&c2jMass11<98.&&W_mt>30.&&abs(W_muon_dz000)<0.02&&abs(W_muon_dzPV)<0.5)");
//  TCut the_cut("effwt*puwt*(iPhoton11>-1&&Photon_Et[iPhoton11]>30.&&i11Jet2>-1&&i11Jet1>-1&&JetPFCor_dRpho11[i11Jet1]>0.5&&JetPFCor_dRpho11[i11Jet2]>0.5&&abs(W_muon_eta)<2.1&&abs(JetPFCor_dphiMET[i11Jet1])>0.4&& abs(JetPFCor_dphiMET[i11Jet2])>0.4&&i11Jet3<0&&JetPFCor_bDiscriminatorCSV[i11Jet1]<0.679&&JetPFCor_bDiscriminatorCSV[i11Jet2]<0.679&&abs(JetPFCor_Eta[i11Jet1]-JetPFCor_Eta[i11Jet2])<1.4&&abs(Photon_Eta[iPhoton11])<1.44421&&W_muon_pt>25&&event_met_pfmet>25.&&(c2jMass11<70. || c2jMass11>100.)&&W_mt>30.&&abs(W_muon_dz000)<0.02&&abs(W_muon_dzPV)<0.5)");

  TCut fkPhoton_cut(TString(the_cut)+TString("*(1/(1+(1/(0.0345868 + 1.44022E04/(Photon_Et[(iPhoton11>-1)? iPhoton11 : 0]^2.89994)))))"));

  if (dovbf)
    the_cut = TCut("vbf_event");

  TCut the_cut2("effwt*puwt*((ggdevt==2) && fit_status==0  &&abs(JetPFCor_dphiMET[0])>0.4 && abs(W_muon_eta)<2.1)");
  TCut the_cut3("effwt*puwt*((ggdevt==3) && fit_status==0  &&abs(JetPFCor_dphiMET[0])>0.4 && abs(W_muon_eta)<2.1)");

  TFile f("plotvar_histo.root", "RECREATE");

 // Get the input trees:

 // Data

  TFile *fin2,*WWASM_file,*H500_file,*AQGC_file,*wwShape_file,*wwaShape_file,*wwa2Shape_file,*wzShape_file,*zzShape_file,*wjetsShape_file,*w4jetShape_file,*ttbar_file,*qcd_file1,*zjets_file,*stops_file,*stopt_file,*stoptW_file;


  if (domu) {
    fin2            = new TFile("InData/RD_WmunuJets_DataAll_GoldenJSON_19p3invfb.root", "read");
//    WWASM_file       = new TFile("InData/RD_mu_HWWMWWASM_CMSSW532_private.root", "READ");
    WWASM_file       = new TFile("InData/RD_mu_WWA_merged_CMSSW532.root", "READ");
//    H500_file       = new TFile("InData/RD_mu_HWWMH500_CMSSW532_private.root", "READ");
//    AQGC_file       = new TFile("InData/RD_mu_HWWMAQGC_CMSSW532_private.root", "READ");
    AQGC_file       = new TFile("InData/RD_mu_KOG_m5m5MG_CMSSW532.root", "READ");
//    wwShape_file    = new TFile("InData/RD_mu_WW_CMSSW532.root", "READ");
    wwShape_file    = new TFile("InData/RD_mu_WW_CMSSW532.root", "READ");
    wwaShape_file    = new TFile("InData/RD_mu_qq_wpwma_wp_qq_wm_lvl.root", "READ");
    wwa2Shape_file    = new TFile("InData/RD_mu_qq_wpwma_wp_lvl_wm_qq.root", "READ");
    wzShape_file    = new TFile("InData/RD_mu_WZA_CMSSW532.root", "READ");
    zzShape_file    = new TFile("InData/RD_mu_ZZ_CMSSW532.root", "READ");
    wjetsShape_file = new TFile("InData/RD_mu_WGp23J_CMSSW532.root", "READ");
    ttbar_file      = new TFile("InData/RD_mu_TTbarGpJets_CMSSW532.root", "READ");
    qcd_file1       = new TFile("InData/RD_WmunuJets_DataAll_GoldenJSON_19p3invfb.root", "READ");
//    qcd_file1       = new TFile("InData/RD_mu_QCDMu_CMSSW532.root", "READ");
    zjets_file      = new TFile("InData/RD_mu_ZAp23J_CMSSW532.root", "READ");
    stops_file      = new TFile("InData/RD_mu_STopS_T_CMSSW532.root", "READ");
    stopt_file      = new TFile("InData/RD_mu_STopT_T_CMSSW532.root", "READ");
    stoptW_file     = new TFile("InData/RD_mu_STopTW_T_CMSSW532.root", "READ");

  } else { // electrons

    fin2            = new TFile("InData/RD_WenuJets_DataAllSingleElectronTrigger_GoldenJSON_3p5invfb.root", "READ");
//    WWASM_file       = new TFile("InData/RD_el_HWWMWWASM_CMSSW428.root", "READ");
//    H500_file       = new TFile("InData/RD_el_HWWMH500_CMSSW428.root", "READ");
    wwShape_file    = new TFile("InData/RD_el_WW_CMSSW532.root", "READ");
    wzShape_file    = new TFile("InData/RD_el_WZ_CMSSW532.root", "READ");
    if (dovbf)
      wjetsShape_file = new TFile("InData/RD_el_W4Jets_CMSSW428.root","READ");
    else
      wjetsShape_file = new TFile("InData/RD_el_WpJ_CMSSW532.root", "READ");
    ttbar_file      = new TFile("InData/RD_el_TTbar_CMSSW532.root", "READ");
    qcd_file1       = new TFile("InData/RDQCD_WenuJets_Isog0p3NoElMVA_1p6invfb.root", "READ");
//    qcd_file1       = new TFile("InData/RDQCD_WenuJets_DataAll_GoldenJSON_2p1invfb2011.root", "READ");
    zjets_file      = new TFile("InData/RD_el_ZpJ_CMSSW532.root", "READ");
    stops_file      = new TFile("InData/RD_el_STopS_T_CMSSW532.root", "READ");
    stopt_file      = new TFile("InData/RD_el_STopT_T_CMSSW532.root", "READ");
    stoptW_file     = new TFile("InData/RD_el_STopTW_T_CMSSW532.root", "READ");
  }

  TTree* treedata = (TTree*) fin2->Get("WJet");
  double nData = treedata->GetEntries();
  std::cout << "ndata =" << nData <<std::endl;

  TTree* treeWWASM  = (TTree*)       WWASM_file->Get("WJet");
//  TTree* treeh500  = (TTree*)       H500_file->Get("WJet");
  TTree* treeAQGC  = (TTree*)       AQGC_file->Get("WJet");
  TTree* treewwa    = (TTree*)    wwaShape_file->Get("WJet");
  TTree* treewwa2    = (TTree*)    wwa2Shape_file->Get("WJet");
  TTree* treeww    = (TTree*)    wwShape_file->Get("WJet");
  TTree* treewz    = (TTree*)    wzShape_file->Get("WJet");
  TTree* treezz    = (TTree*)    zzShape_file->Get("WJet");
  TTree* treewj    = (TTree*) wjetsShape_file->Get("WJet");
  TTree* treettb   = (TTree*)      ttbar_file->Get("WJet");
  TTree* treeqcd   = (TTree*)       qcd_file1->Get("WJet");
  TTree* treezj    = (TTree*)      zjets_file->Get("WJet");
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

    if (dovbf && pv.mva_in)
      the_cut = TCut("effwt*puwt*(vbf_event && vbf_wjj_m > 65.0 && vbf_wjj_m < 95.0)"); // plot only events in the signal region

    const double BINWIDTH = ((pv.MAXRange-pv.MINRange)/pv.NBINS);

    TH1* th1data  = new TH1D("th1data",  "th1data",  pv.NBINS, pv.MINRange, pv.MAXRange);
//    TH1* th1data1 = new TH1D("th1data1", "th1data1", pv.NBINS, pv.MINRange, pv.MAXRange);
    TBox *errbox = new TBox(pv.AMINRange,0.95,pv.AMAXRange,1.05);
    errbox->SetFillColor(kYellow);
    treedata->Draw(TString(pv.plotvar)+TString(">>th1data"), the_cut, "goff");
//    treedata->Draw(TString(pv.plotvar)+TString(">>th1data1"), the_cut, "goff");
    th1data->AddBinContent(pv.NBINS,th1data->GetBinContent(pv.NBINS+1));th1data->SetBinContent(pv.NBINS+1,0.);
 
    // Get Signal MC
/*
    TH1* th1H500 = new TH1D("th1H500", "th1H500", pv.NBINS, pv.MINRange, pv.MAXRange);
    treeh500->Draw(TString(pv.plotvar)+TString(">>th1H500"), the_cut, "goff");
    th1H500->Scale(H500_scale);

*/
    TH1* th1AQGC = new TH1D("th1AQGC", "th1AQGC", pv.NBINS, pv.MINRange, pv.MAXRange);
    th1AQGC->Sumw2();
    treeAQGC->Draw(TString(pv.plotvar)+TString(">>th1AQGC"), the_cut, "goff");
    th1AQGC->AddBinContent(pv.NBINS,th1AQGC->GetBinContent(pv.NBINS+1));th1AQGC->SetBinContent(pv.NBINS+1,0.);
    th1AQGC->Scale(AQGC_scale);

    TH1* th1WWASM = new TH1D("th1WWASM", "th1WWASM", pv.NBINS, pv.MINRange, pv.MAXRange);
    th1WWASM->Sumw2();
    treeWWASM->Draw(TString(pv.plotvar)+TString(">>th1WWASM"), the_cut, "goff");
    th1WWASM->AddBinContent(pv.NBINS,th1WWASM->GetBinContent(pv.NBINS+1));th1WWASM->SetBinContent(pv.NBINS+1,0.);
    th1WWASM->Scale(WWASM_scale);

    // Get WW/WZ/ZZ

    TH1* th1wwa = new TH1D("th1wwa", "th1wwa", pv.NBINS, pv.MINRange, pv.MAXRange);
    TH1* th1wwa2 = new TH1D("th1wwa2", "th1wwa2", pv.NBINS, pv.MINRange, pv.MAXRange);
    TH1* th1ww = new TH1D("th1ww", "th1ww", pv.NBINS, pv.MINRange, pv.MAXRange);
    TH1* th1wz = new TH1D("th1wz", "th1wz", pv.NBINS, pv.MINRange, pv.MAXRange);
    TH1* th1zz = new TH1D("th1zz", "th1zz", pv.NBINS, pv.MINRange, pv.MAXRange);
    th1wwa->Sumw2();
    th1wwa2->Sumw2();
    th1ww->Sumw2();
    th1wz->Sumw2();
    th1zz->Sumw2();

    treewwa->Draw(TString(pv.plotvar)+TString(">>th1wwa"), the_cut, "goff");
    th1wwa->AddBinContent(pv.NBINS,th1wwa->GetBinContent(pv.NBINS+1));th1wwa->SetBinContent(pv.NBINS+1,0.);
    treewwa2->Draw(TString(pv.plotvar)+TString(">>th1wwa2"), the_cut, "goff");
    th1wwa2->AddBinContent(pv.NBINS,th1wwa2->GetBinContent(pv.NBINS+1));th1wwa2->SetBinContent(pv.NBINS+1,0.);
    treeww->Draw(TString(pv.plotvar)+TString(">>th1ww"), the_cut, "goff");
    th1ww->AddBinContent(pv.NBINS,th1ww->GetBinContent(pv.NBINS+1));th1ww->SetBinContent(pv.NBINS+1,0.);
    treewz->Draw(TString(pv.plotvar)+TString(">>th1wz"), the_cut, "goff");
    th1wz->AddBinContent(pv.NBINS,th1wz->GetBinContent(pv.NBINS+1));th1wz->SetBinContent(pv.NBINS+1,0.);
    treezz->Draw(TString(pv.plotvar)+TString(">>th1zz"), the_cut, "goff");
    th1zz->AddBinContent(pv.NBINS,th1zz->GetBinContent(pv.NBINS+1));th1zz->SetBinContent(pv.NBINS+1,0.);


    // Get WJets

    TH1* th1wjets  = new TH1D("th1wjets",  "th1wjets",  pv.NBINS ,pv.MINRange,pv.MAXRange);
    th1wjets->Sumw2();

    treewj->Draw(TString(pv.plotvar)+TString(">>th1wjets"), the_cut, "goff");
    th1wjets->AddBinContent(pv.NBINS,th1wjets->GetBinContent(pv.NBINS+1));th1wjets->AddBinContent(pv.NBINS+1,-th1wjets->GetBinContent(pv.NBINS+1));


    // Get ttbar
 
    TH1* th1Top = new TH1D("th1Top", "th1Top", pv.NBINS, pv.MINRange, pv.MAXRange);
    th1Top->Sumw2();
    // cross section: 157.5 pb, events_gen = 3701947 (These are summer11 TTJets sample
  
    treettb->Draw(TString(pv.plotvar)+TString(">>th1Top"), the_cut, "goff");
    th1Top->AddBinContent(pv.NBINS,th1Top->GetBinContent(pv.NBINS+1));th1Top->SetBinContent(pv.NBINS+1,0.);

    // Get QCD

    TH1* th1qcd = new TH1D("th1qcd", "th1qcd", pv.NBINS, pv.MINRange, pv.MAXRange);
    th1qcd->Sumw2();
 
    treeqcd->Draw(TString(pv.plotvar)+TString(">>th1qcd"), fkPhoton_cut, "goff");
    th1qcd->AddBinContent(pv.NBINS,th1qcd->GetBinContent(pv.NBINS+1));th1qcd->SetBinContent(pv.NBINS+1,0.);
    float fperr = 0.;
//  photon fake rate uncert
    for(int hi=1;hi<=pv.NBINS;hi++) {
        fperr = (th1qcd->GetBinError(hi))*(th1qcd->GetBinError(hi));
        fperr + = 0.01*(th1qcd->GetBinContent(hi))*(th1qcd->GetBinContent(hi));
        th1qcd->SetBinError(hi,sqrt(fperr));
        th1AQGC->SetBinError(hi,0.0001);
    }
//  Norm uncert.
    for(int hi=1;hi<=pv.NBINS;hi++) {
        fperr = (th1wjets->GetBinError(hi))*(th1wjets->GetBinError(hi));
        fperr + = 0.065*0.065*(th1wjets->GetBinContent(hi))*(th1wjets->GetBinContent(hi));
        th1wjets->SetBinError(hi,sqrt(fperr));
    }

    
/*
    int n2 = treeqcd->Draw(TString(pv.plotvar),  the_cut2, "goff");
    int n3 = treeqcd->Draw(TString(pv.plotvar),  the_cut3 , "goff");

    std::cout << "got qcd " << " n2 " << n2 <<  " n3  " << n3 <<std::endl; 

*/
    // Get Z+Jets

    TH1* th1zjets = new TH1D("th1zjets", "th1zjets", pv.NBINS, pv.MINRange, pv.MAXRange);
    th1zjets->Sumw2();
    treezj->Draw(TString(pv.plotvar)+TString(">>th1zjets"), the_cut, "goff");
    th1zjets->AddBinContent(pv.NBINS,th1zjets->GetBinContent(pv.NBINS+1));th1zjets->SetBinContent(pv.NBINS+1,0.);

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

    TFile* stopps_file =  new TFile("InData/RD_mu_STopS_Tbar_CMSSW532.root", "READ");
    TTree* tree64 = (TTree*) stopps_file->Get("WJet");
    TFile* stoppt_file =  new TFile("InData/RD_mu_STopT_Tbar_CMSSW532.root", "READ");
    TTree* tree65 = (TTree*) stoppt_file->Get("WJet");
    TFile* stopptW_file =  new TFile("InData/RD_mu_STopTW_Tbar_CMSSW532.root", "READ");
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

    TCanvas* c1 = new TCanvas(pv.plotvar,pv.plotvar,10,10, 800, 800);
    TPad *d1, *d2;

    c1->Divide(1,2,0,0);
    d1 = (TPad*)c1->GetPad(1);
    d1->SetPad(0.01,0.30,0.95,0.99);
    d2 = (TPad*)c1->GetPad(2);
    d2->SetPad(0.01,0.02,0.95,0.30);

    // Setup the stack, scale the histos

    THStack* hs = new THStack("hs","MC contribution");
    th1Top->Scale(ttbar_scale);
    th1Top->SetFillColor(kGreen+2);
    th1Top->SetLineColor(kGreen+2);
    th1Top->SetLineWidth(0);

    th1stops->Scale(STopS_scale);
    th1stops->SetFillColor(7);
    th1stops->SetLineWidth(2);
    th1stopt->Scale(STopT_scale);
    th1stopt->SetFillColor(13);
    th1stopt->SetLineWidth(2);
    th1stoptw->Scale(STopTW_scale);
    th1stoptw->SetFillColor(9);
    th1stoptw->SetLineWidth(2);

    th1stopps->Scale(SToppS_scale);
    th1stopps->SetFillColor(7);
    th1stopps->SetLineWidth(2);
    th1stoppt->Scale(SToppT_scale);
    th1stoppt->SetFillColor(13);
    th1stoppt->SetLineWidth(2);
    th1stopptw->Scale(SToppTW_scale);
    th1stopptw->SetFillColor(9);
    th1stopptw->SetLineWidth(2);

    th1wjets->Scale(WJets_scale);
    th1wjets->SetFillColor(kRed);
    th1wjets->SetLineColor(kRed);
    th1wjets->SetLineWidth(0);
    th1wwa->Scale(WWA_scale);
    th1wwa2->Scale(WWA2_scale);
    th1wwa->SetFillColor(17);
    th1wwa->SetLineColor(17);
    th1wwa->SetLineWidth(0);
    th1ww->Scale(WW_scale);
    th1ww->SetFillColor(kAzure+8);
    th1ww->SetLineColor(kAzure+8);
    th1ww->SetLineWidth(0);
    th1wz->Scale(WZ_scale);
    th1wz->SetFillColor(11);
    th1wz->SetLineWidth(0);
    th1zz->Scale(ZZ_scale);
    th1zz->SetFillColor(11);
    th1zz->SetLineWidth(0);

    // th1qcd->Scale(QCD_scale);
  
    th1qcd->SetFillColor(kBlue+1);
    th1qcd->SetLineColor(kBlue+1);
    th1qcd->SetLineWidth(0);
    th1zjets->Scale(ZAJets_scale);
    th1zjets->SetFillColor(kYellow);
    th1zjets->SetLineColor(kYellow);
    th1zjets->SetLineWidth(0);
    std::cout << "fake photon " << th1qcd->Integral()   << std::endl;
    std::cout << "wa+jets "   << th1wjets->Integral()    << std::endl;
    std::cout << "wwa "   << th1wwa->Integral()+th1wwa2->Integral()    << std::endl;
    std::cout << "wza "   << th1wz->Integral()    << std::endl;
    std::cout << "tt "   << th1Top->Integral()   << std::endl;
    std::cout << "za+jets "    << th1zjets->Integral() << std::endl;
    std::cout << "zz "   << th1zz->Integral()    << std::endl;
  
    double den_qcd = 
      th1Top->Integral()+
      th1stops->Integral()+
      th1stopt->Integral()+
      th1stoptw->Integral()+
      th1stopps->Integral()+
      th1stoppt->Integral()+
      th1stopptw->Integral()+
      th1wjets->Integral()+
      th1wwa->Integral()+
      th1wwa2->Integral()+
      th1ww->Integral()+
      th1wz->Integral()+
      th1zz->Integral()+
      th1qcd->Integral() +
      th1zjets->Integral();
/*
    double qcd_scale;

    if (domu)
      qcd_scale = (n2*0.002 + n3*0.000) / (n2+n3) ;//muon
    else
      qcd_scale = (n2*0.0637 + n3*0.02) / (n2+n3); //electron


*/
//    std::cout << " qcd_scale  " << qcd_scale <<std::endl;
//    th1qcd->Scale(qcd_scale*den_qcd/th1qcd->Integral()); 

    double den = 
      th1Top->Integral()+
      th1stops->Integral()+
      th1stopt->Integral()+
      th1stoptw->Integral()+
      th1stopps->Integral()+
      th1stoppt->Integral()+
      th1stopptw->Integral()+
      th1wjets->Integral()+
      th1wwa2->Integral()+
      th1wwa->Integral()+
      th1ww->Integral()+
      th1wz->Integral()+
      th1zz->Integral()+
      th1zjets->Integral()+
      th1qcd->Integral();

    std::cout << "den = " <<den <<std::endl;
    std::cout <<" data " <<  th1data->Integral() << std::endl;
/*
//    th1qcd->Scale   (th1data->Integral()/den); std::cout <<"qcd "   << th1qcd->Integral()   << std::endl;
    th1Top->Scale   (th1data->Integral()/den); std::cout <<"tt "    << th1Top->Integral()   << std::endl;
    th1stops->Scale (th1data->Integral()/den); std::cout <<"stops " << th1stops->Integral() << std::endl;
    th1stopt->Scale (th1data->Integral()/den); std::cout <<"stopt " << th1stopt->Integral() << std::endl;
    th1stoptw->Scale(th1data->Integral()/den); std::cout <<"stoptw "<< th1stoptw->Integral()<< std::endl;
    th1stopps->Scale (th1data->Integral()/den); std::cout <<"stops " << th1stopps->Integral() << std::endl;
    th1stoppt->Scale (th1data->Integral()/den); std::cout <<"stopt " << th1stoppt->Integral() << std::endl;
    th1stopptw->Scale(th1data->Integral()/den); std::cout <<"stoptw "<< th1stopptw->Integral()<< std::endl;
    th1wjets->Scale (th1data->Integral()/den); std::cout <<"wjets " << th1wjets->Integral() << std::endl;
    th1wwa->Scale    (th1data->Integral()/den); std::cout <<"wwa "    << th1wwa->Integral()    << std::endl;
    th1wwa2->Scale    (th1data->Integral()/den); std::cout <<"wwa2 "    << th1wwa2->Integral()    << std::endl;
    th1ww->Scale    (th1data->Integral()/den); std::cout <<"ww "    << th1ww->Integral()    << std::endl;
    th1wz->Scale    (th1data->Integral()/den); std::cout << "wz "   << th1wz->Integral()    << std::endl;
    th1zz->Scale    (th1data->Integral()/den); std::cout << "zz "   << th1zz->Integral()    << std::endl;
    th1zjets->Scale (th1data->Integral()/den); std::cout << "z "    << th1zjets->Integral() << std::endl;
*/

    cout<<"(th1data->Integral()/den) = "<< (th1data->Integral()/den) <<endl;
    double den2 =
      th1Top->Integral()+
      th1stops->Integral()+
      th1stopt->Integral()+
      th1stoptw->Integral()+
      th1stopps->Integral()+
      th1stoppt->Integral()+
      th1stopptw->Integral()+
      th1wjets->Integral()+
      th1wwa->Integral()+
      th1wwa2->Integral()+
      th1ww->Integral()+
      th1wz->Integral()+
      th1zz->Integral()+
      th1zjets->Integral()+
      th1qcd->Integral();

    std::cout << "den2 " << den2 << std::endl;

    th1Top->Add(th1stopptw,1);
    th1Top->Add(th1stoppt,1);
    th1Top->Add(th1stopps,1);
    th1Top->Add(th1stoptw,1);
    th1Top->Add(th1stopt,1);
    th1Top->Add(th1stops,1);
//    th1ww->Add(th1wz,1);
    th1ww->Add(th1zz,1);
    th1wwa->Add(th1wwa2,1);
    th1wwa->Add(th1wz,1);
//    th1WWASM->Add(th1wz,1);

    // Sum all the backgrounds

    TH1D *th1tot = (TH1D*)th1wjets->Clone("th1tot");
    th1tot->Reset();
    th1tot->Add(th1ww,1);
    th1tot->Add(th1Top,1);
    th1tot->Add(th1wjets,1);
    th1tot->Add(th1zjets,1);
    th1tot->Add(th1qcd,1);
    TH1D *th1totAC = (TH1D*)th1tot->Clone();
    th1tot->Add(th1wwa,1);
    th1totAC->Add(th1AQGC,1);
    th1totAC->SetMarkerStyle(0);
    th1totAC->SetFillStyle(0);
    th1totAC->SetLineColor(1);
    th1totAC->SetLineWidth(3);

    th1AQGC->SetMarkerStyle(0);
    th1AQGC->SetFillStyle(0);
    th1AQGC->SetLineColor(4);
    th1AQGC->SetLineStyle(4);
    th1AQGC->SetLineWidth(3);

    TH1D* th1totClone = ( TH1D*) th1tot->Clone("th1totClone");
    th1totClone->SetMarkerStyle(0);
    th1totClone->SetFillStyle(3003);
    th1totClone->SetFillColor(11);
    th1totClone->SetLineColor(0);
    double binErr(0.0);
    for(int i=0; i<th1totClone->GetNbinsX(); ++i) {
      binErr = sqrt(
		    (th1wwa->GetBinError(i+1))**2 +
		    (th1zz->GetBinError(i+1))**2 +
		    (th1qcd->GetBinError(i+1))**2 + 
		    (th1Top->GetBinError(i+1))**2 +
		    (th1wjets->GetBinError(i+1))**2 +
		    (th1zjets->GetBinError(i+1))**2);
      th1totClone->SetBinError(i+1, binErr);
      th1totAC->SetBinError(i+1, 0.000001);
    }

    // Compose the stack

    hs->Add(th1wwa);
    d1->cd();
    gPad->SetBottomMargin(0.0);
    gPad->SetTopMargin(0.1);
    gPad->SetRightMargin(0.05);
    gPad->SetLeftMargin(0.14);

    hs->Add(th1wjets);
    hs->Add(th1zjets);
    hs->Add(th1Top);
    hs->Add(th1ww);
    hs->Add(th1qcd);

    // Set up the legend

    float  legX0=0.65, legX1=0.99, legY0=0.64, legY1=0.88;
    float  leg1X0=0.15, leg1X1=0.60, leg1Y0=0.64, leg1Y1=0.88;
    // float  legX0=0.35, legX1=0.85, legY0=0.4, legY1=0.88;
    // float  legX0=0.18, legX1=0.52, legY0=0.4, legY1=0.88;
    TLegend * Leg = new TLegend( legX0, legY0, legX1, legY1);
    TLegend * Leg1 = new TLegend( leg1X0, leg1Y0, leg1X1, leg1Y1);
    Leg->SetFillColor(0);
    Leg->SetFillStyle(0);
    Leg->SetTextSize(0.04);
    Leg->AddEntry(th1qcd,  "fake photons",  "f");
    Leg->AddEntry(th1Top,  "top",  "f");
    Leg->AddEntry(th1zjets,  "Z#gamma+Jets",  "f");
    Leg->AddEntry(th1wwa,  "WZ#gamma/WW#gamma ",  "f");
    Leg->SetFillColor(0);

    Leg1->SetFillColor(0);
    Leg1->SetFillStyle(0);
    Leg1->SetTextSize(0.04);
    Leg1->AddEntry(th1data,  "Muon Data",  "PLE");
    Leg1->AddEntry(th1tot,  "MC Uncertainty",  "f");
    Leg1->AddEntry(th1wjets,  "W#gamma+jets",  "f");
    Leg1->AddEntry(th1totAC,  "BG + a_{0}^{W} / #Lambda^{2} = -5x10^{-5}",  "l");
//    Leg1->AddEntry(th1AQGC,  "a_{0}^{W} / #Lambda^{2} = -5x10^{-5} x 20",  "l");
    Leg1->SetFillColor(0);

//    if (pv.hplot ==1&&!strstr(pv.plotvar,"mva2j190mu")) Leg->AddEntry(th1H500,  "H (500) x 200",  "L");
//    if (pv.hplot ==1&&!strstr(pv.plotvar,"mva2j190mu")&&!strstr(pv.plotvar,"mva2j500mu")) Leg->AddEntry(th1AQGC,  "H (300) x 200",  "L");
//    if (pv.hplot ==1&&!strstr(pv.plotvar,"mva2j500mu")) Leg->AddEntry(th1WWASM,  "H (190) x 100",  "L");
//    Leg->AddEntry(th1AQGC,  "a_{0}^{W} / #Lambda^{2} = -5x10^{-5} x 20",  "L");
//    Leg->AddEntry(th1WWASM,  "WW#gamma SM x 20",  "L");

/*
    th1H500->SetLineColor(kBlack);
    th1H500->SetLineWidth(3);
    th1H500->Scale(200);

*/
    th1AQGC->SetLineColor(4);
    th1AQGC->SetLineWidth(3);
    th1AQGC->SetLineStyle(2);
    th1AQGC->Scale(20);

    th1WWASM->SetLineColor(kBlue);
    th1WWASM->SetLineWidth(3);
    th1WWASM->Scale(20);

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
//    th1totempty->SetMaximum(2.5*maxval);
    th1totempty->SetMaximum(1.99*maxval);
    th1totempty->SetMinimum(0.01);
    if(pv.slog==1) th1totempty->SetMaximum(1.99*maxval);
    th1data->SetMinimum(0.01);

    // Draw it all

    th1totempty->Draw();
    //th1tot->Draw("e2same");
    th1data->Draw("esame");
    hs->Draw("samehist");
//    if (pv.hplot ==1&&!strstr(pv.plotvar,"mva2j190mu")) th1H500->Draw("same");
//    if (pv.hplot ==1&&!strstr(pv.plotvar,"mva2j190mu")&&!strstr(pv.plotvar,"mva2j500mu")) th1AQGC->Draw("same");
//    if (pv.hplot ==1&&!strstr(pv.plotvar,"mva2j500mu")) th1WWASM->Draw("same");
//    th1AQGC->Draw("same");
//    th1WWASM->Draw("same");
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
    hhratio->SetStats(0);

    gPad->SetLeftMargin(0.14);
    gPad->SetTopMargin(0);
    gPad->SetRightMargin(0.05);
    gPad->SetFrameBorderSize(0);
    gPad->SetBottomMargin(0.3);
    gPad->SetTickx();

    hhratio->SetMarkerSize(1.25);
    //  hhratio->GetYaxis()->SetRangeUser(0.48,1.52);
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
    th1emptyclone->GetYaxis()->SetRangeUser(0.0001,2.9999);
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

