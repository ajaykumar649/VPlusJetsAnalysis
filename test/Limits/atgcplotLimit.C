#include <iostream>
#include <stdlib.h>
//#define __size_t unsigned // needed for glob.h!!
#include "/usr/lib/gcc/x86_64-redhat-linux/4.1.2/include/stddef.h"
#include <glob.h>

#include "TH2D.h"
#include "TRegexp.h"
#include "TGraph2D.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TGraphPolar.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TPaveText.h"
#include "TGraphAsymmErrors.h"
#include "TLine.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TROOT.h"
#include "TStyle.h"

#include "atgcstyle.C"

using namespace std;

const float intlumifbinv = 19.2;
const int   beamcometev  = 8;

//======================================================================

TString par2latex(const TString& parname)
{
  if (parname.EqualTo("lz") )  return "#lambda";
  if (parname.EqualTo("dkg") ) return "#Delta#kappa_{#gamma}";
  if (parname.EqualTo("dg1") ) return "#Delta G1";

  return "UNKNOWN PAR "+parname;
}

//======================================================================

float parmin(const TString& parname)
{
  if (parname.EqualTo("lz") )  return -0.03;
  if (parname.EqualTo("dkg") ) return -0.1;
  if (parname.EqualTo("dg1") ) return -0.1;

  return -999;
}

//======================================================================

float parmax(const TString& parname)
{
  if (parname.EqualTo("lz") )  return 0.03;
  if (parname.EqualTo("dkg") ) return 0.1;
  if (parname.EqualTo("dg1") ) return 0.1;

  return -999;
}

//======================================================================

void getFileNames(const string& fileglob,
		  vector<TString>& fnames)
{
  // File globbing pattern can select multiple files
  //
  glob_t globbuf;
  int stat = glob (fileglob.c_str(), GLOB_MARK, NULL, &globbuf);
  if (stat) {
    switch (stat) {
    case GLOB_NOMATCH: cerr << "No file matching glob pattern "; break;
    case GLOB_NOSPACE: cerr << "glob ran out of memory "; break;
    case GLOB_ABORTED: cerr << "glob read error "; break;
    default: cerr << "unknown glob error stat=" << stat << " "; break;
    }
    cerr << fileglob << endl;
    exit(-1);
  }
  cout<<globbuf.gl_pathc<<" files match the glob pattern"<<endl;
  for (size_t i=0; i<globbuf.gl_pathc; i++) {
    char *path = globbuf.gl_pathv[i];
    if (!strncmp(&path[strlen(path)-6],".root",5)) {
      cerr << "non-root file found in glob, skipping: " << path << endl;
    } else {
      fnames.push_back(TString(path));
    }
  }
  globfree(&globbuf);
}                                                        // getFileNames

//======================================================================

double extractParValue(const char *par,
		       const TString& file)
{
  TRegexp re(Form("%s_\\-?[0-9]*\\.?[0-9]*e?\\-?[0-9]*",par));

  int len = 0;
  int i = re.Index(file,&len);

  i  +=strlen(par)+1;
  len-=strlen(par)+1;

  //cout << file << "\t" << i << "\t" << len << "\t" << TString(file(i,len)) << endl;

  if (i > 0 && len > 0)
    return (TString(file(i,len))).Atof();

  cerr << "Could not find a valid value for par " <<  par << " in filename: " << file << endl;

  return -9e99;
}                                                     // extractParValue

//======================================================================
// adapted from HiggsAnalysis/CombinedLimit/test/plotting/bandUtils.cxx
//
int  getBands(TFile *file, int doSyst, int whichChannel,
	      double& obs,	 double& median,
	      double& s68hi,	 double& s68lo,
	      double& s95hi,	 double& s95lo)
{
#if 0
  printf("getBands(file=%lx,doSyst=%d,whichChannel=%d)\t",
  	 (unsigned long)file,doSyst,whichChannel);
#endif
  if (file == 0) return 0;

  TTree *t = (TTree *) file->Get("limit");

  if (t == 0) { 
    std::cerr<<"TFile "<<file->GetName()<<" does not contain the tree"<<std::endl;
    return 0; 
  }

  Double_t limit, limitErr = 0;
  Int_t syst, iChannel, iToy;

  t->SetBranchAddress("limit", &limit);
  if (t->GetBranch("limitErr"))
    t->SetBranchAddress("limitErr", &limitErr);

  t->SetBranchAddress("syst", &syst);
  t->SetBranchAddress("iChannel", &iChannel);
  t->SetBranchAddress("iToy", &iToy);

  std::vector<double>  dataset;
  std::vector<double>  errors;

  for (size_t i = 0, n = t->GetEntries(); i < n; ++i) {
    t->GetEntry(i);
    //if (!i) printf("%6d mh=%.1f iChannel=%d syst=%d limit=%8.3f +/- %8.3f toy=%5d", 
    //i, iChannel,syst,limit, limitErr, iToy);
    if (syst     != doSyst)            { /* cout<<"syst"<<endl;    */ continue; }
    if (iChannel != whichChannel)      { /* cout<<"channel"<<endl; */ continue; }
    if (limit == 0)                    { /* cout<<"limit==0"<<endl;*/ continue; }
      
    dataset.push_back(limit);
    errors.push_back(limitErr);
  }

  int nd = dataset.size();
  if (!nd) {
    cerr << "Zero entries for " << file->GetName() << endl;
    return 0;
  }

  std::sort(dataset.begin(), dataset.end());
    
  median = (dataset.size() % 2 == 0 ? 0.5*(dataset[nd/2]+dataset[nd/2+1]) : dataset[nd/2]);
  double mean = 0;
  for (int j = 0; j < nd; ++j) mean += dataset[j]; 
  mean /= nd;
  s68lo = dataset[             floor(0.5*nd*(1-0.68)+0.5)        ];
  s68hi = dataset[std::min(int(floor(0.5*nd*(1+0.68)+0.5)), nd-1)];
  s95lo = dataset[             floor(0.5*nd*(1-0.95)+0.5)        ];
  s95hi = dataset[std::min(int(floor(0.5*nd*(1+0.95)+0.5)), nd-1)];

  if (nd == 1) {
    obs = mean;
    if (errors.size() == 1) {
      s68lo = mean - errors[0];
      s68hi = mean + errors[0];
    } else {
      // could happen if limitErr is not available
      s68lo = s68hi = mean;
    }
  }
#if 0
  printf("nd=%d, mean=%.3g, median=%.3g, s68lo=%.3g, s68hi=%.3g\n",
	 nd, mean,median,s68lo,s68hi);
#endif
  return nd;
}                                                            // getBands

//======================================================================

void fillGraphsFromFiles( const TString& par1,
			  const TString& par2,
			  const vector<TString>& fnames,
			  const vector<string>&  keys,
			  map<string,TGraph2D *>& m_graphs)
{
  for (int i=0; i<6; i++) {
    m_graphs[keys[i]] = new TGraph2D();
    m_graphs[keys[i]]->SetName(Form("graph2D%s",keys[i].c_str()));
  }

  int nobs=0, nexp=0;
  for( size_t i=0; i<fnames.size(); i++) {
    
    double par1val = extractParValue(par1,fnames[i]);
    double par2val = extractParValue(par2,fnames[i]);

    //cout << par1val << "\t" << par2val << endl;

    if (par1val == -9e99 ||
	par2val == -9e99)
      continue;
    
    TFile *f = new TFile(fnames[i]);

    double obs,median,s68hi,s68lo,s95hi,s95lo;
    int num = getBands(f,1,0,obs,median,s68hi,s68lo,s95hi,s95lo);

    switch (num) {
    case 0: break;
    case 1:
      //cout << "SetPoint(i="<<nobs<<",par1="<<par1val<<",par2="<<par2val<<",obs="<<obs<<");"<<endl;
      m_graphs["obs"]->SetPoint(nobs,par1val,par2val,obs);
      nobs++;
      break;
    default:
      m_graphs["+2s"]->SetPoint(nexp,par1val,par2val,s95hi);
      m_graphs["-2s"]->SetPoint(nexp,par1val,par2val,s95lo);
      m_graphs["+1s"]->SetPoint(nexp,par1val,par2val,s68hi);
      m_graphs["-1s"]->SetPoint(nexp,par1val,par2val,s68lo);
      m_graphs["median"]->SetPoint(nexp,par1val,par2val,median);
      nexp++;
      break;
    }
        
    f->Close();

    delete f;

    //if (!(i%10)) cout << i << " " << std::flush;


  } // file loop

#if 0
  TGraph2D *gobs = m_graphs["obs"];
  cout << "obs has " << gobs->GetN() << " points" << endl;
  cout << "npx = " << gobs->GetNpx() << endl;
  cout << "npy = " << gobs->GetNpy() << endl;
  cout << "xmin = " << gobs->GetXmin() << endl;
  cout << "xmax = " << gobs->GetXmax() << endl;
  cout << "ymin = " << gobs->GetYmin() << endl;
  cout << "ymax = " << gobs->GetYmax() << endl;
  cout << "zmin = " << gobs->GetZmin() << endl;
  cout << "zmax = " << gobs->GetZmax() << endl;

  double *xvec = gobs->GetX();
  double *yvec = gobs->GetY();
  double *zvec = gobs->GetZ();
  for (int i=0; i<gobs->GetN(); i++)
    printf("%lf\t%lf\t%lf\n",xvec[i],yvec[i],zvec[i]);
#endif
}                                                 // fillGraphsFromFiles

//======================================================================

void fillGraphsFromFilesAsymp( const TString& par1,
			       const TString& par2,
			       const vector<TString>& fnames,
			       const vector<string>&  keys,
			       map<string,TGraph2D *>& m_graphs)
{
  for (int i=0; i<6; i++) {
    m_graphs[keys[i]] = new TGraph2D();
    m_graphs[keys[i]]->SetName(Form("graph2D%s",keys[i].c_str()));
  }

  for( size_t i=0; i<fnames.size(); i++) {
    
    double par1val = extractParValue(par1,fnames[i]);
    double par2val = extractParValue(par2,fnames[i]);

    //cout << par1val << "\t" << par2val << endl;

    if (par1val == -9e99 ||
	par2val == -9e99)
      continue;
    
    TFile *f = new TFile(fnames[i]);

    TTree *lTree = (TTree *)f->Get("limit");
    if (!lTree) {
      f->Close();
      delete f;
      cerr << "didn't find tree limit in file " << fnames[i] << endl;
      continue;
    }
    
    for (int j=0; j<6; j++) {
      lTree->GetEntry(j);
      double rval = lTree->GetLeaf("limit")->GetValue();
      m_graphs[keys[j]]->SetPoint(i,par1val,par2val,rval);
    }
        
    f->Close();

    delete f;

    //if (!(i%10)) cout << i << " " << std::flush;


  } // file loop
}                                            // fillGraphsFromFilesAsymp

//======================================================================

void collectContours(map<string,TGraph2D *>& m_graphs,
		     const vector<string>&  keys,
		     map<string,TList *>& m_contours)
{
  TCanvas *canv = new TCanvas("dummy","dummy",500,500);
  m_graphs["+2s"]->Draw("cont 5z list");

  //process TGraph2Ds into contours at r == 1
  for (int i=0; i<6; i++) {
    double one = 1.0;
    m_graphs[keys[i]]->GetHistogram()->SetContour(1,&one);
    m_graphs[keys[i]]->Draw("cont 2z list");
    canv->Update();
        
    TObjArray *contours = (TObjArray *)gROOT->GetListOfSpecials()->FindObject("contours");
    assert(contours);
    TList *contLevel = (TList*)contours->At(0);
    printf("%s: Contour has %d Graphs\n", keys[i].c_str(), contLevel->GetSize());

    TList *newlist = new TList();
    assert(contLevel->First());
    TGraph *curv = (TGraph*)(contLevel->First());

    for (int j=0; j<contLevel->GetSize(); j++) {
      newlist->Add((TGraph *)(curv->Clone()));
      curv=(TGraph *)(contLevel->After(curv));
    }

    //cout << "Inserting contour list for "<< keys[i] << " newlist="<<newlist<<endl;

    m_contours[keys[i]] = newlist;
  }
  delete canv;
}                                                     // collectContours

//======================================================================

void atgcplotLimit(const string& fileglob)
{
  atgcstyle();

  gStyle->SetPalette(1);

  vector<TString> fnames;
  getFileNames(fileglob, fnames);

  assert(fnames.size());

  TString   par1;
  TString   par2;

  // get names of coupling parameters from root filename
  //
  if (fnames[0].Contains("lz")) {       par1 = TString("lz");
    if (fnames[0].Contains("dkg"))      par2 = TString("dkg");
    else if (fnames[0].Contains("dg1")) par2 = TString("dg1");
  } else if  (fnames[0].Contains("dkg") &&
	      fnames[0].Contains("dg1")) {
    par1 = TString("dkg");
    par2 = TString("dg1");
  } 
  if (!par1.Length() || !par2.Length() ) {
    cerr << "Unknown coupling parameters in name " << fnames[0] << endl;
    exit(-1);
  }

  TString method("Other");
  if (fnames[0].Contains("Asymptotic"))
    method = TString("Asymptotic");

  cout << "Plotting " << par2 << " versus " << par1 << ", method = " << method << endl;

  vector<string> keys;
  keys.push_back("-2s");
  keys.push_back("-1s");
  keys.push_back("median");
  keys.push_back("+1s");
  keys.push_back("+2s");
  keys.push_back("obs");

  map<string,TGraph2D *> m_graphs;

  if (method.EqualTo("Asymptotic"))
    fillGraphsFromFilesAsymp(par1,par2,fnames,keys,m_graphs);
  else
    fillGraphsFromFiles(par1,par2,fnames,keys,m_graphs);

  // for limit in limits:
  //   limits[limit][0].Print()

  TCanvas *canv2 = new TCanvas("two","two",800,600);

#if 0
  // for a first look
  canv2->Divide(3,2);
  canv2->cd(1);  m_graphs["+2s"]->Draw("TRI"); gPad->SetLogz(1);
  canv2->cd(2);  m_graphs["+1s"]->Draw("TRI"); gPad->SetLogz(1);
  canv2->cd(3);  m_graphs["median"]->Draw("TRI"); gPad->SetLogz(1);
  canv2->cd(4);  m_graphs["-1s"]->Draw("TRI"); gPad->SetLogz(1);
  canv2->cd(5);  m_graphs["-2s"]->Draw("TRI"); gPad->SetLogz(1);
  canv2->cd(6);  m_graphs["obs"]->Draw("TRI"); gPad->SetLogz(1);
#else
  m_graphs["obs"]->Draw("TRI");

  map<string,TList *> m_contours;

  collectContours(m_graphs,keys,m_contours);

  //from here we build the two-dimensional aTGC limit

  TCanvas *finalPlot = new TCanvas("final","limits",500,500);
  finalPlot->cd();

  TLegend *legend = new TLegend(0.212,0.686,0.554,0.917,"","NDC");
  legend->SetFillStyle(0);
  legend->SetBorderSize(0);
  legend->SetHeader("CMS Preliminary");
  //legend->SetHeader("CMS");
  legend->SetTextFont(42);

  cout << "Drawing +2s" << endl;

  TList *contLevel = m_contours["+2s"];

  assert(contLevel);

  TGraph *curv = (TGraph*)(contLevel->First());

  //curv->GetYaxis()->SetRangeUser(-1.25*curv->GetYaxis()->GetXmax(),
				 //+2.0*curv->GetYaxis()->GetXmax());
  curv->GetYaxis()->SetRangeUser(-0.1,0.15);

  curv->SetTitle();
  curv->GetXaxis()->SetTitle(par2latex(par1));
  curv->GetXaxis()->SetTitleFont(42);
  curv->GetYaxis()->SetTitle(par2latex(par2));
  curv->GetYaxis()->SetTitleFont(42);
  curv->GetYaxis()->SetTitleOffset(1.20);

  for (int i=0; i<contLevel->GetSize(); i++) {
    assert(curv);
    curv->SetLineColor(kYellow);
    curv->SetFillColor(kYellow);
    curv->GetXaxis()->SetLimits(parmin(par1),parmax(par1));
    if (!i) {
      curv->Draw("ACF");
      legend->AddEntry(curv,"#pm 2#sigma","F");
    } else 
      curv->Draw("SAME CF");
    curv=(TGraph *)(contLevel->After(curv));
  }

  cout << "Drawing +1s" << endl;
  
  contLevel = m_contours["+1s"];
  curv = (TGraph*)(contLevel->First());
  for (int i=0; i<contLevel->GetSize(); i++) {
    curv->SetLineColor(kGreen);
    curv->SetFillColor(kGreen);
    curv->Draw("SAME CF");
    if (!i) legend->AddEntry(curv,"#pm 1#sigma","F");
    curv=(TGraph *)(contLevel->After(curv));
  }

  cout << "Drawing -1s" << endl;

  contLevel = m_contours["-1s"];
  curv = (TGraph*)(contLevel->First());
  for (int i=0; i<contLevel->GetSize(); i++) {
    curv->SetLineColor(kYellow);
    curv->SetFillColor(kYellow);
    curv->Draw("SAME CF");
    curv=(TGraph *)(contLevel->After(curv));
  }

  cout << "Drawing -2s" << endl;
  
  contLevel = m_contours["-2s"];
  curv = (TGraph*)(contLevel->First());
  for (int i=0; i<contLevel->GetSize(); i++) {
    curv->SetFillColor(kWhite);
    curv->SetLineColor(kYellow);
    curv->Draw("SAME CF");
    curv=(TGraph *)(contLevel->After(curv));
  }

  cout << "Drawing median" << endl;
  
  curv = (TGraph*)(m_contours["median"]->First());
  curv->SetLineColor(kBlack);
  curv->SetLineWidth(2);
  curv->SetLineStyle(2);
  curv->Draw("SAME C");

  legend->AddEntry(curv,"Expected","L");
  
  cout << "Drawing obs" << endl;

  contLevel = m_contours["obs"];
  curv = (TGraph*)(contLevel->First());
  for (int i=0; i<contLevel->GetSize(); i++) {
    curv->SetLineColor(kBlack);
    curv->SetLineWidth(2);
    curv->Draw("SAME C");
    if (!i) legend->AddEntry(curv,"Observed","L");
    curv=(TGraph *)(contLevel->After(curv));
  }

  
  TGraph *SMpoint = new TGraph(1);
  SMpoint->SetPoint(1,0,0);
  SMpoint->Draw("SAME Po");
  
  // smLabel = TPaveText(0,
  //                     m_contours["-2s"]->GetYaxis()->GetXmax()/8,
  //                     m_contours["-2s"]->GetXaxis()->GetXmax()/3->5,
  //                     -m_contours["-2s"]->GetYaxis()->GetXmax()/8);
  // smLabel->SetFillStyle(0);
  // smLabel->SetBorderSize(0);
  // smLabel->AddText(" SM");
  // smLabel->Draw();

  legend->Draw();

  TPaveText *text = new TPaveText(0.516,0.720,0.915,0.951,"NDC");
  text->SetFillStyle(0);
  text->SetBorderSize(0);
  text->AddText(Form("95%% CL Limit on %s and %s",par2latex(par1).Data(),par2latex(par2).Data()));
  text->AddText(0,0.35,Form("#intL dt= %.1f fb^{-1}, #sqrt{s} = %d TeV",intlumifbinv,beamcometev));
  text->Draw();

  // text2 = TPaveText(0.155,0.199,0.974,0.244,"NDC");
  // text2->SetFillStyle(0);
  // text2->SetBorderSize(0);
  // text2->AddText("Values outside contour excluded");
  // text2->Draw();

  //text3 = TPaveText(0.506,0.699,0.905,0.758,"NDC");
  //text3->SetFillStyle(0);
  //text3->SetBorderSize(0);
  //text3->AddText(options.flavorText);
  //text3->Draw();    
  
  finalPlot->RedrawAxis();
  finalPlot->ResetAttPad();
  finalPlot->Update();

  finalPlot->Draw();
  finalPlot->Update();
  finalPlot->Modified();
  finalPlot->Update();
  finalPlot->Print(Form("%s_%s_2dlimit_cls.pdf",par1.Data(),par2.Data()));
  finalPlot->Print(Form("%s_%s_2dlimit_cls.eps",par1.Data(),par2.Data()));
  finalPlot->Print(Form("%s_%s_2dlimit_cls.png",par1.Data(),par2.Data()));
#endif
}
