// -*- mode: c++ -*- 

#ifndef ROOCHEBYSHEVPDF_H
#define ROOCHEBYSHEVPDF_H

#include "RooAbsPdf.h"
#include "RooAbsReal.h"
#include "RooArgList.h"
#include "RooRealProxy.h"
#include "RooListProxy.h"

class RooChebyshevPDF : public RooAbsPdf {
public:

  RooChebyshevPDF() {} ;
  RooChebyshevPDF(const char *name, const char *title, RooAbsReal& var,
		  RooArgList& coefList);
  RooChebyshevPDF(const RooChebyshevPDF& other, const char *name=0);
  virtual TObject* clone(const char *newname) const {
    return new RooChebyshevPDF(*this, newname); }

  virtual ~RooChebyshevPDF();

  Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, 
			      const char *rangeName = 0) const;
  Double_t analyticalIntegral(Int_t code, const char *rangeName = 0) const;

  static Double_t ChebyshevP(Int_t order, Double_t v);

protected:

  RooRealProxy x;
  RooListProxy coefs;

  Double_t evaluate() const;

private:

  ClassDef(RooChebyshevPDF,1) //Chebyshev polynomial implementation.
};

#endif
