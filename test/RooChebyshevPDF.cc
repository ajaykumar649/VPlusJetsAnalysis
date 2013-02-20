// -*- mode: c++ -*- 
// -- CLASS DESCRIPTION [PDF] --
// This implements a PDF which is a series of Chebyshev polynomials.
// 
//              ---
// pdf(x) = 1 + \   coef[n]*ChebysevP_n(x)
//              /
//              ---
//               n
//
// This implementation works well when combined with the needs of the
// full angular B0 --> D*+D*- pdfs.  This implementation can go to arbitrary.
// order however orders higher than 6 may see slowing as higher and higher 
// orders are added.  If the range of x is not -1 to 1 then its range is mapped
// into this range.  If x is not bounded on both the upper and lower sides
// then the output of this pdf is not well defined and the pdf should not
// be used.

#include "Riostream.h"

#include "RooChebyshevPDF.h"

using namespace std;

ClassImp(RooChebyshevPDF)
;

RooChebyshevPDF::RooChebyshevPDF(const char *name, const char *title, 
				 RooAbsReal& var, RooArgList& coefList) :
  RooAbsPdf(name,title),
  x("x", "x", this, var),
  coefs("coefs", "coefs", this) {

  TIterator *cx = coefList.createIterator();
  RooAbsReal *coef;
  while ((coef = (RooAbsReal*)cx->Next())) {
    if (!dynamic_cast<RooAbsReal*>(coef)) {
      cerr << "Coefficient " << coef->GetName() << " is not good." << endl;
      assert(0);
    }
    coefs.add(*coef);
  }
  delete cx;
}

RooChebyshevPDF::RooChebyshevPDF(const RooChebyshevPDF& other, 
				 const char *name) :
  RooAbsPdf(other, name),
  x("x", this, other.x),
  coefs("coefs", this, other.coefs) {

}

RooChebyshevPDF::~RooChebyshevPDF() {
}

Double_t RooChebyshevPDF::ChebyshevP(Int_t order, Double_t v) {
  if (order == 0) return 1.0;
  if (order == 1) return v;
  if (order == 2) return 2.0*v*v - 1.0;
  if (order == 3) return 4.0*v*v*v - 3.0*v;
  if (order == 4) return 8.0*v*v*v*v - 8.0*v*v + 1.0;
  if (order == 5) return 16.*v*v*v*v*v - 20.*v*v*v + 5.*v;
  if (order == 6) return 32.*v*v*v*v*v*v - 48.*v*v*v*v + 18.*v*v - 1.0;
  if (order == 7) return 64.*v*v*v*v*v*v*v - 112.*v*v*v*v*v + 56.*v*v*v - 7.*v;
  if (order > 7) return 2.0*v*ChebyshevP(order-1,v)-ChebyshevP(order-2,v);
  assert(order > -1);
  return 0.0;
}

Double_t RooChebyshevPDF::evaluate() const {
  RooAbsReal *coef;
  Int_t tord = 1;
  Double_t val = 1.0;
  Double_t v = 2.0/(x.max()-x.min())*(x - (x.min() + (x.max()-x.min())/2.0));
  for (tord = 1; tord <= coefs.getSize(); ++tord) {
    coef = dynamic_cast<RooAbsReal*>(coefs.at(tord-1));
    val += coef->getVal()*ChebyshevP(tord,v);
  }
  return val;
}

Int_t RooChebyshevPDF::getAnalyticalIntegral(RooArgSet& allVars, 
					  RooArgSet& analVars,
					  const char */*rangeName*/) const {
  if (matchArgs(allVars, analVars, x)) return 1;
  return 0;
}

Double_t RooChebyshevPDF::analyticalIntegral(Int_t code, 
					     const char *rangeName) const {
  assert(code);
  RooAbsReal *coef;
  Int_t tord = 1;
  Double_t dv = (x.max()-x.min())/2.0;
  Double_t vmax = 2.0/(x.max()-x.min())*(x.max(rangeName) - 
					 (x.min() + (x.max()-x.min())/2.0));
  Double_t vmin = 2.0/(x.max()-x.min())*(x.min(rangeName) - 
					 (x.min() + (x.max()-x.min())/2.0));
  Double_t val = vmax-vmin;
  for (tord = 1; tord <= coefs.getSize(); ++tord) {
    coef = dynamic_cast<RooAbsReal*>(coefs.at(tord-1));
    if (tord == 1) {
      val += coef->getVal()*vmax*vmax/2.0;
      val -= coef->getVal()*vmin*vmin/2.0;
    } else {
      val += coef->getVal()*(tord*ChebyshevP(tord+1, vmax)/(tord*tord-1) - 
			     vmax*ChebyshevP(tord, vmax)/(tord-1));
      val -= coef->getVal()*(tord*ChebyshevP(tord+1, vmin)/(tord*tord-1) - 
			     vmin*ChebyshevP(tord, vmin)/(tord-1));
    }
  }
  return dv*val;
}
