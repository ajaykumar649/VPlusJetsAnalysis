#include <iostream>
#include <stdlib.h>
//#define __size_t unsigned // needed for glob.h!!
//#include "/usr/lib/gcc/x86_64-redhat-linux/4.1.2/include/stddef.h"
//#include <glob.h>
#include <algorithm>
#include <vector>
#include <iterator>
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

//======================================================================
// adapted from HiggsAnalysis/CombinedLimit/test/plotting/bandUtils.cxx
//
int  getBands(TFile *file, int doSyst, int whichChannel,
	      double& obs,	 double& median,
	      double& s68hi,	 double& s68lo,
	      double& s95hi,	 double& s95lo)
{
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
  s68hi = std::min(int(floor(0.5*nd*(1+0.68)+0.5)),nd-1);
  s68hi = dataset[s68hi];
  s95lo = dataset[             floor(0.5*nd*(1-0.95)+0.5)        ];
  s95hi = std::min(int(floor(0.5*nd*(1+0.95)+0.5)),nd-1);
  s95hi = dataset[s95hi];


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
  return nd;
}                                                            // getBands

//======================================================================

//void extractLimits(const vector<TString>& fnames){
void extractLimits(TString limit_file){

    TFile *f = new TFile(limit_file);

    double obs,median,s68hi,s68lo,s95hi,s95lo;
    int num = getBands(f,1,0,obs,median,s68hi,s68lo,s95hi,s95lo);

    cout<<obs<<" "<<s95lo<<" "<<s68lo<<" "<<median<<" "<<s68hi<<" "<<s95hi<<endl<<endl;

    f->Close();

    delete f;

}

//======================================================================

void aqgcplotLimit(TString limit_file)
{
  extractLimits(limit_file);

}
