#include <iostream>
#include <stdlib.h>
//#define __size_t unsigned // needed for glob.h!!
#include "/usr/lib/gcc/x86_64-redhat-linux/4.1.2/include/stddef.h"
#include <glob.h>
#include <assert.h>

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
  if (parname.EqualTo("dkg") ) return -0.15;
  if (parname.EqualTo("dg1") ) return -0.1;

  return -999;
}

//======================================================================

float parmax(const TString& parname)
{
  if (parname.EqualTo("lz") )  return 0.03;
  if (parname.EqualTo("dkg") ) return 0.15;
  if (parname.EqualTo("dg1") ) return 0.1;

  return -999;
}

//======================================================================

int parbins(const TString& parname)
{
  if (parname.EqualTo("lz") )  return 61;
  if (parname.EqualTo("dkg") ) return 31;
  if (parname.EqualTo("dg1") ) return 101;

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

void fillGraphsFromTextTables( const TString& fname,
			       map<string,TGraph2D *>& m_graphs)
{
  m_graphs["obs"] = new TGraph2D(fname,"%lg %lg %lg %*lg %*lg %*lg %*lg %*lg");
  m_graphs["obs"]->SetName("graph2Dobs");

  m_graphs["-2s"] = new TGraph2D(fname,"%lg %lg %*lg %*lg %*lg %*lg %*lg %lg");
  m_graphs["-2s"]->SetName("graph2D-2s");

  m_graphs["-1s"] = new TGraph2D(fname,"%lg %lg %*lg %*lg %*lg %*lg %lg %*lg");
  m_graphs["-1s"]->SetName("graph2D-1s");

  m_graphs["median"] = new TGraph2D(fname,"%lg %lg %*lg %*lg %*lg %lg %*lg %*lg");
  m_graphs["median"]->SetName("graph2Dmedian");

  m_graphs["+1s"] = new TGraph2D(fname,"%lg %lg %*lg %*lg %lg %*lg %*lg %*lg");
  m_graphs["+1s"]->SetName("graph2D+1s");

  m_graphs["+2s"] = new TGraph2D(fname,"%lg %lg %*lg %lg %*lg %*lg %*lg %*lg");
  m_graphs["+2s"]->SetName("graph2D+2s");
}                                            // fillGraphsFromTextTables

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
		     map<string,TList *>& m_contours,
		     double contourval)
{
  TCanvas *canv = new TCanvas("dummy","dummy",100,100);
  //m_graphs["+2s"]->Draw("cont 5z list");
  //canv->Divide(3,2);

  //process TGraph2Ds into contours at z=contourval
  for (int i=0; i<6; i++) {
    m_graphs[keys[i]]->GetHistogram()->SetContour(1,&contourval);
    //canv->cd(i+1);
    m_graphs[keys[i]]->Draw("cont 2z list");
    canv->Update();
        
    TObjArray *contours = (TObjArray *)gROOT->GetListOfSpecials()->FindObject("contours");
    assert(contours);
    TList *contLevel = (TList*)contours->At(0);
    printf("%s: Contour has %d Graphs\n", keys[i].c_str(), contLevel->GetSize());

    TList *newlist = 0;
    if (contLevel->GetSize()) {
      newlist = new TList();
      assert(contLevel->First());
      TGraph *curv = (TGraph*)(contLevel->First());

      for (int j=0; j<contLevel->GetSize(); j++) {
	newlist->Add((TGraph *)(curv->Clone()));
	curv=(TGraph *)(contLevel->After(curv));
      }

      //cout << "Inserting contour list for "<< keys[i] << " newlist="<<newlist<<endl;
    }
    m_contours[keys[i]] = newlist;
  }
  //delete canv;
}                                                     // collectContours

//======================================================================

void
draw2DLimit(map<string,TList *>& m_contours,
	    const TString& par1,
	    const TString& par2,
	    const TString& plotprefix,
	    TLegend *legend)
{

  //from here we build the two-dimensional aTGC limit

  TCanvas *finalPlot = new TCanvas("final","limits",500,500);
  finalPlot->cd();

  cout << "Drawing +2s" << endl;

  TList *contLevel = m_contours["+2s"];
  TGraph *curv;

  assert(contLevel);

  curv = (TGraph*)(contLevel->First());

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

  if (!contLevel)
    //  this can happen more often for this contour if there is insufficient
    // sensitivity close to the SM
    cerr << "No contour level for +2s, have to fill in the central region" << endl;
  else {
    curv = (TGraph*)(contLevel->First());
    for (int i=0; i<contLevel->GetSize(); i++) {
      curv->SetFillColor(kWhite);
      curv->SetLineColor(kYellow);
      curv->Draw("SAME CF");
      curv=(TGraph *)(contLevel->After(curv));
    }
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
  finalPlot->Print(Form("%s.pdf",plotprefix.Data()));
  finalPlot->Print(Form("%s.eps",plotprefix.Data()));
  finalPlot->Print(Form("%s.png",plotprefix.Data()));

}                                                         // draw2Dlimit

//======================================================================

void
draw1DLimit(map<string,TGraph2D *> m_graphs,
	    const TString& parname,
	    const TString& plotprefix,
	    int      npts,
	    double   boundScale,   // used to exclude region closest to SM from plotting
	    double   exclusionlimit,
	    bool     isX,
	    TLegend *legend)
{
  TCanvas *c1 = new TCanvas(Form("%slimit",parname.Data()),
			    Form("%slimit",parname.Data()),
			    500,500);

  map<string,TGraphAsymmErrors *> m_limits1d;

  m_limits1d["2s"]     = new TGraphAsymmErrors();
  m_limits1d["1s"]     = new TGraphAsymmErrors();
  m_limits1d["-median"] = new TGraphAsymmErrors();
  m_limits1d["-obs"]    = new TGraphAsymmErrors();
  m_limits1d["+median"] = new TGraphAsymmErrors();
  m_limits1d["+obs"]    = new TGraphAsymmErrors();

  double parSize = parmax(parname) - parmin(parname);

  double lowerLimit=0.0,        upperLimit=0.0;
  bool   lowerLimitFound=false, upperLimitFound=false;

  double parcutoff = parmin(parname)*boundScale;

  double bound = 0.0;    // bound =  the max y value for the minus side
  if (isX)
    bound = m_graphs["-2s"]->Interpolate(parcutoff,0.0);
  else
    bound = m_graphs["-2s"]->Interpolate(0.0,parcutoff);

  // print parmin, parmax, boundScale, bound

  int nnegpts=0,npospts=0;
  for (int i=0; i<npts; i++) {
    double obs, median, p1s, m1s, p2s, m2s;
    double parval = parmin(parname) + i*parSize/npts;
        
    if (isX) {
      obs  = m_graphs["obs"]->Interpolate(parval,0.0);
      median = m_graphs["median"]->Interpolate(parval,0.0);
      p1s  = m_graphs["+1s"]->Interpolate(parval,0.0);
      m1s  = m_graphs["-1s"]->Interpolate(parval,0.0);
      p2s  = m_graphs["+2s"]->Interpolate(parval,0.0);
      m2s  = m_graphs["-2s"]->Interpolate(parval,0.0);
    } else {
      obs  = m_graphs["obs"]->Interpolate(0.0,parval);
      median = m_graphs["median"]->Interpolate(0.0,parval);
      p1s  = m_graphs["+1s"]->Interpolate(0.0,parval);
      m1s  = m_graphs["-1s"]->Interpolate(0.0,parval);
      p2s  = m_graphs["+2s"]->Interpolate(0.0,parval);
      m2s  = m_graphs["-2s"]->Interpolate(0.0,parval);
    }

    //print m2s, m1s, median, p1s, p2s
        
    if (obs > exclusionlimit && !lowerLimitFound && (parval < 0)) {
      lowerLimit = parval;
      lowerLimitFound = true;
    } else if (obs < exclusionlimit && !upperLimitFound && (parval > 0)) {
      upperLimit = parval;
      upperLimitFound = true;
    }

    if ( (m2s < bound) &&
	 (fabs(parval) > fabs(parcutoff))
       ) {
      //par1 observed limit
      //obs and median
      if (parval < 0) {
	m_limits1d["-median"]->SetPoint(nnegpts,parval,median);
	m_limits1d["-obs"]->SetPoint(nnegpts++,parval,obs);
      } else {
	m_limits1d["+median"]->SetPoint(npospts,parval,median);
	m_limits1d["+obs"]->SetPoint(npospts++,parval,obs);
      }
      // one sigma expected
      m_limits1d["1s"]->SetPoint(i,parval,median);
      m_limits1d["1s"]->SetPointError(i,0,0,median-m1s,p1s-median);
      //two sigma expected    
      m_limits1d["2s"]->SetPoint(i,parval,median);
      m_limits1d["2s"]->SetPointError(i,0,0,median-m2s,p2s-median);
    } else {
      m_limits1d["1s"]->SetPoint(i,parval,bound+0.1);
      m_limits1d["1s"]->SetPointError(i,0,0,0,0);
      m_limits1d["2s"]->SetPoint(i,parval,bound+0.1);
      m_limits1d["2s"]->SetPointError(i,0,0,0,0);
    }
  }  // npts loop

  //print "95% CL on"+" %s = [%.3g,%.3g]"%(par,lowerLimit,upperLimit)

  c1->cd();
  c1->SetLogy();

  m_limits1d["2s"]->SetFillColor(kYellow);
  m_limits1d["2s"]->Draw("A E3");
    
  m_limits1d["1s"]->SetFillColor(kGreen);
  m_limits1d["1s"]->Draw("SAME E3");
    
  m_limits1d["-median"]->SetLineStyle(2);
  m_limits1d["-median"]->SetLineWidth(2);
  m_limits1d["-median"]->Draw("SAME C");
    
  m_limits1d["+median"]->SetLineStyle(2);
  m_limits1d["+median"]->SetLineWidth(2);
  m_limits1d["+median"]->Draw("SAME C");
    
  m_limits1d["-obs"]->SetLineWidth(2);
  m_limits1d["-obs"]->Draw("SAME C");
    
  m_limits1d["+obs"]->SetLineWidth(2);
  m_limits1d["+obs"]->Draw("SAME C");
    
  //titles
  if (exclusionlimit==1)
    m_limits1d["2s"]->GetYaxis()->SetTitle("95% CL limit on #sigma/#sigma_{aTGC}");
  else
    m_limits1d["2s"]->GetYaxis()->SetTitle(Form("p_{S+B}(%s)",par2latex(parname).Data()));

  m_limits1d["2s"]->GetYaxis()->SetTitleFont(42);
  m_limits1d["2s"]->GetXaxis()->SetTitle(par2latex(parname));
  m_limits1d["2s"]->GetXaxis()->SetTitleFont(42);
  
  m_limits1d["2s"]->GetYaxis()->SetRangeUser(m_limits1d["2s"]->GetYaxis()->GetXmin()*0.75,10); //,bound);
  m_limits1d["2s"]->GetXaxis()->SetRangeUser(parmin(parname)*0.985,parmax(parname)*0.96);

#if 0    
  legend->SetX1NDC(0.43);
  legend->SetY1NDC(0.43);
  legend->SetX2NDC(0.75);
  legend->SetY2NDC(0.65);
#endif
  legend->Draw();
  
  TPaveText *text1d = new TPaveText(0.516,0.720,0.915,0.951,"NDC");
  //TPaveText *text1d = new TPaveText(0.359,0.24,0.758,0.44,"NDC");
  text1d->SetFillStyle(0);
  text1d->SetBorderSize(0);
  text1d->AddText(Form("95%% CL Limit on #bf{%s}",par2latex(parname).Data()));
  text1d->AddText(0,0.35,"#intL dt= 19.2 fb^{-1}, #sqrt{s} = 8 TeV");
  text1d->Draw();
    
  // text3.SetX1NDC(0.357);
  // text3.SetY1NDC(0.246);
  // text3.SetX2NDC(0.756);
  // text3.SetY2NDC(0.305);
  // text3.Draw();
  
  TPaveText *obslimtext = new TPaveText(0.357,0.197,0.754,0.246,"NDC");
  obslimtext->SetFillStyle(0);
  obslimtext->SetBorderSize(0);
  obslimtext->AddText(Form("%.3f < %s  < %.3f",
			   lowerLimit,par2latex(parname).Data(),upperLimit));
  obslimtext->Draw();
  
  //lowLimitLine = TLine(lowerLimit,m_limits1d["2s"]->GetYaxis()->GetXmin()*0.75,
  //                     lowerLimit,1)
  //lowLimitLine->SetLineColor(14)
  //lowLimitLine->SetLineWidth(2)
  //lowLimitLine->Draw()
  //upLimitLine = TLine(upperLimit,m_limits1d["2s"]->GetYaxis()->GetXmin()*0.75,
  //                    upperLimit,1)
  //upLimitLine->SetLineColor(14)
  //upLimitLine->SetLineWidth(2)
  //upLimitLine->Draw()

  TLine *oneLine = new TLine(parmin(parname)*0.985,exclusionlimit,
			     parmax(parname)*0.960,exclusionlimit);
  oneLine->SetLineStyle(9);
  oneLine->SetLineColor(14);
  oneLine->Draw();
    
  c1->Draw();
  c1->Update();
  c1->Modified();
  c1->Update();

  c1->Print(Form("%s.pdf",plotprefix.Data()));
  c1->Print(Form("%s.eps",plotprefix.Data()));
  c1->Print(Form("%s.png",plotprefix.Data()));
}                                                         // draw1Dlimit

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
    method = TString("asympCLs");

  cout << "Plotting " << par2 << " versus " << par1 << ", method = " << method << endl;

  vector<string> keys;
  keys.push_back("-2s");
  keys.push_back("-1s");
  keys.push_back("median");
  keys.push_back("+1s");
  keys.push_back("+2s");
  keys.push_back("obs");

  map<string,TGraph2D *> m_graphs;

  if (method.EqualTo("asympCLs"))
    fillGraphsFromFilesAsymp(par1,par2,fnames,keys,m_graphs);
  else if (fnames.size() == 1) {
    fillGraphsFromTextTables(fnames[0],m_graphs);

    TCanvas *canv = new TCanvas("dummy2","dummy2",500,500);
#if 0
    m_graphs["-2s"]->Draw("COLZ TEXT");
#else
    TGraph2D *gr = m_graphs["-2s"];
    TH2D *h2 = new TH2D("h2d","h2d",
			parbins(par1),parmin(par1),parmax(par1),
			parbins(par2),parmin(par2),parmax(par2));
    h2->FillN(gr->GetN(),gr->GetX(),gr->GetY(),gr->GetZ());
    h2->Draw("COLZ TEXT");
#endif

  }  else
    fillGraphsFromFiles(par1,par2,fnames,keys,m_graphs);

  //return;

  // for limit in limits:
  //   limits[limit]->Print()


#if 0
  // for a first look
  TCanvas *canv2 = new TCanvas("two","two",800,600);
  canv2->Divide(3,2);
  canv2->cd(1);  m_graphs["+2s"]->Draw("TRI"); gPad->SetLogz(1);
  canv2->cd(2);  m_graphs["+1s"]->Draw("TRI"); gPad->SetLogz(1);
  canv2->cd(3);  m_graphs["median"]->Draw("TRI"); gPad->SetLogz(1);
  canv2->cd(4);  m_graphs["-1s"]->Draw("TRI"); gPad->SetLogz(1);
  canv2->cd(5);  m_graphs["-2s"]->Draw("TRI"); gPad->SetLogz(1);
  canv2->cd(6);  m_graphs["obs"]->Draw("TRI"); gPad->SetLogz(1);
#else
  //m_graphs["obs"]->Draw("TRI");

  map<string,TList *> m_contours;

  double exclusion_limit = fnames.size()==1? 0.05 : 1;
  collectContours(m_graphs,keys,m_contours,exclusion_limit);

  TLegend *legend = new TLegend(0.212,0.686,0.554,0.917,"","NDC");
  legend->SetFillStyle(0);
  legend->SetBorderSize(0);
  legend->SetHeader("CMS Preliminary");
  //legend->SetHeader("CMS");
  legend->SetTextFont(42);

  TString plotprefix=Form("%s_%s_2dlimit_%s",par1.Data(),par2.Data(),method.Data());

  draw2DLimit(m_contours,par1,par2,plotprefix,legend);

  plotprefix=Form("%s_1dlimit_%s",par1.Data(),method.Data());
  draw1DLimit(m_graphs,par1,plotprefix,1000,0.05,exclusion_limit,true,legend);

  plotprefix=Form("%s_1dlimit_%s",par2.Data(),method.Data());
  draw1DLimit(m_graphs,par2,plotprefix,1000,0.02,exclusion_limit,false,legend);

#endif
}
