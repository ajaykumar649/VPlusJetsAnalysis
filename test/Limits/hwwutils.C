#include <iostream>
#include <stdio.h>
#include <stdlib.h> // exit
#include <assert.h>
#include <math.h>
#include <map>
#include <climits> // INT_MAX

#define HWWUTILS_C
#include "hwwutils.h"
#include "hwwinputs.h"

using namespace std;

std::map<int,HdataPerMassPt> m_signals; // signal (Higgs) data per mass point

//================================================================================

void readHxsTable(const TString& fname, double scale=1.0)
{
  cout << "Reading cross sections table from " << fname << endl;

  FILE *mapf = fopen(fname.Data(),"r");
  if (!mapf) {
    cerr << "Couldn't open " << fname << endl;
    exit(-1);
  }

  char str[128];
  while (!feof(mapf) && fgets(str,128,mapf)) {
    if (str[0] == '#') continue;
    int mHgev;
    int n = sscanf(str,"%d",&mHgev);
    HdataPerMassPt& hd = m_signals[mHgev];
    if (fname.Contains("vbf")) {
      n += sscanf(str,"%*d %lf %*f %*f %lf %lf %lf %lf",
		  &hd.vbfcspb,
		  &hd.vbfscaleunchi,&hd.vbfscaleunclo,
		  &hd.vbfpdfunchi,&hd.vbfpdfunclo
		  );
      hd.vbfcspb       *= scale;
    } else {
      n += sscanf(str,"%*d %lf %*f %*f %lf %lf %lf %lf",
		  &hd.ggHcspb,
		  &hd.ggHscaleunchi,&hd.ggHscaleunclo,
		  &hd.ggHpdfunchi,&hd.ggHpdfunclo
		  );
      hd.ggHcspb       *= scale;
    }
    if (n != 6) {
      cerr << "Error reading from file " << fname << endl;
      exit(-1);
    }
    hd.massgev = (double)mHgev;
  }
  fclose(mapf);
}                                                                  // readHxsTable

//================================================================================

void readBRtable(const std::string& fname)
{
  cout << "Reading branching ratios table from " << fname << endl;

  FILE *brf = fopen(fname.c_str(),"r");
  if (!brf) {
    cerr << "Couldn't open " << fname << endl;
    exit(-1);
  }

  char str[128];
  while (!feof(brf) && fgets(str,128,brf)) {
    if (str[0] == '#') continue;
    int mHgev;
    double br2lnujj,br2ww;
    int n = sscanf(str,"%d %lf %lf",&mHgev,&br2lnujj,&br2ww);
    if (n != 3) {
      cerr << "Error reading from file " << fname << endl;
      exit(-1);
    }
    m_signals[mHgev].br2lnujj = 2*br2lnujj; // listed as for only one charge lepton
    m_signals[mHgev].br2ww    = br2ww;
  }
  fclose(brf);
}                                                                  // readBRtable

//================================================================================

void readJetBinErrTable(const std::string& fname)
{
  cout << "Reading exclusive jet bin theoretical nuisances from " << fname << endl;

  FILE *brf = fopen(fname.c_str(),"r");
  if (!brf) {
    cerr << "Couldn't open " << fname << endl;
    exit(-1);
  }

  char str[128];
  while (!feof(brf) && fgets(str,128,brf)) {
    if (str[0] == '#') continue;
    int mHgev;
    char param[25], val0j[20], val1j[20];
    int n = sscanf(str,"%d %s %s %s", &mHgev, param, val0j, val1j);
    if (n != 4) {
      cerr << "Error reading from file " << fname << endl;
      exit(-1);
    }
    if (!strcmp(param,"UEPS")) {
      m_signals[mHgev].ueps_0j = strtod(val0j,NULL);
      m_signals[mHgev].ueps_1j = strtod(val1j,NULL);
    } else if (!strcmp(param,"QCDscale_ggH1in")) {
      m_signals[mHgev].qcdscale_ggh1in0j = strtod(val0j,NULL);
      m_signals[mHgev].qcdscale_ggh1in1j = strtod(val1j,NULL);
    } else if (!strcmp(param,"QCDscale_ggH2in")) {
      m_signals[mHgev].qcdscale_ggh2in1j = strtod(val1j,NULL);
    } else if (!strcmp(param,"QCDscale_ggH")) {
      m_signals[mHgev].qcdscale_ggh0j = strtod(val0j,NULL);
    }
  }
  fclose(brf);
}

//================================================================================

int findMasspt2use(int massgev)
{
  // NB: the scheme of which mass to use for uncertainties must be coordinated manually
  //     with which shapes are used in the interpolation of points!
  //
  // find nearest masspoint, use that mass for the uncertainty info
  int mindiff = INT_MAX;
  int imass2use=-1;

  // adjust the mass2use for some interpolated points
  //int comparemassgev = (massgev >= 222 && massgev <= 225) ? 250 : massgev;
  int comparemassgev = massgev;

  for (int i=0; i<NUMMASSPTS; i++) {
    int diff = abs(comparemassgev-masspts[i]);
    if (diff < mindiff) {
      mindiff = diff;
      imass2use = i;
    }
    else if (diff > mindiff) break; // assume increasing order, so not going to find better!
  }
  assert(imass2use>=0);

  return imass2use;
}

//================================================================================
const std::pair<double,double> zeropair(0.,0.);

void makeTheoretUncert4Sig(int massgev,
			   const TString& procname,
			   pair<double,double>& pdfunc,   // down/up pair to put in card
			   pair<double,double>& scaleunc0, // down/up pair to put in card
			   pair<double,double>& scaleunc1,
			   pair<double,double>& scaleunc2,
			   pair<double,double>& scaleunc3,
			   pair<double,double>& ueps0j,
			   pair<double,double>& ueps1j)
{
  std::map<int,HdataPerMassPt>::const_iterator it =  m_signals.find(massgev);
  if (it == m_signals.end()) {
    cerr << "Mass " << massgev << "GeV not represented in signal tables." << endl;
    exit(-1);
  }

  scaleunc1 = zeropair;
  scaleunc2 = zeropair;
  scaleunc3 = zeropair;
  ueps0j    = zeropair;
  ueps1j    = zeropair;
    
  const HdataPerMassPt& hd = it->second;

  int imass2use = findMasspt2use(massgev);

  cout << "Using mass " << masspts[imass2use] << " GeV for uncertainties."<<endl;

  if (procname.Contains("qq") ) { // vbf process
#if 0
    // this version gives two sided inputs to combine
    pdfunc.first     = 1.0 + (hd.vbfpdfunclo/100.0);
    pdfunc.second    = 1.0 + (hd.vbfpdfunchi/100.0);
    scaleunc0.first  = 1.0 + (hd.vbfscaleunclo/100.0);
    scaleunc0.second = 1.0 + (hd.vbfscaleunchi/100.0);
#else
    // this version takes the geometric mean of low and high to feed as single number
    pdfunc.first     = 0.0;
    pdfunc.second    = sqrt( (1.0+(hd.vbfpdfunchi/100.))/(1.0+(hd.vbfpdfunclo/100.)) );
    scaleunc0.first  = 0.0;
    scaleunc0.second = sqrt( (1.0+(hd.vbfscaleunchi/100.))/(1.0+(hd.vbfscaleunclo/100.)) );
#endif
    // add signal acceptance effect of PDF variation in quadrature:
    pdfunc.second = 1.0 + sqrt((pdfunc.second-1)*(pdfunc.second-1) +
			       (qqsigaccptsyst[imass2use]-1)*(qqsigaccptsyst[imass2use]-1));
  } else { // default gg fusion process
#if 0
    // this version gives two sided inputs to combine
    pdfunc.first     = 1.0 + (hd.ggHpdfunclo/100.0);
    pdfunc.second    = 1.0 + (hd.ggHpdfunchi/100.0);
    scaleunc0.first  = 1.0 + (hd.ggHscaleunclo/100.0);
    scaleunc0.second = 1.0 + (hd.ggHscaleunchi/100.0);
#else
    // this version takes the geometric mean of low and high to feed as single number
    pdfunc    = std::pair<double,double>(0.0, sqrt( (1.0+(hd.ggHpdfunchi/100.))/(1.0+(hd.ggHpdfunclo/100.))));
    scaleunc0 = std::pair<double,double>(0.0, hd.qcdscale_ggh0j);
    scaleunc1 = std::pair<double,double>(0.0, hd.qcdscale_ggh1in0j);
    scaleunc2 = std::pair<double,double>(0.0, hd.qcdscale_ggh1in1j);
    scaleunc3 = std::pair<double,double>(0.0, hd.qcdscale_ggh2in1j);
    ueps0j    = std::pair<double,double>(0.0, hd.ueps_0j);
    ueps1j    = std::pair<double,double>(0.0, hd.ueps_1j);
#endif
    // add signal acceptance effect of PDF variation in quadrature:
    pdfunc.second = 1.0 + sqrt((pdfunc.second-1)*(pdfunc.second-1) +
			       (ggsigaccptsyst[imass2use]-1)*(ggsigaccptsyst[imass2use]-1));
  }

}                                                         // makeTheoretUncert4Sig
