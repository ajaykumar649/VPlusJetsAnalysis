// -*- mode: c++ -*-

#ifndef ROODIBOSONHISTPDF
#define ROODIBOSONHISTPDF

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooAbsReal.h"
#include "RooDataHist.h"

class RooDibosonHistPdf : public RooAbsPdf {
public:

  RooDibosonHistPdf ();
  RooDibosonHistPdf (const char * name, const char * title,
                    RooAbsReal& _x, RooAbsReal& _lZ,
                    RooAbsReal& _dkg, RooAbsReal& _dg1,
                    RooDataHist& _dhist);
  RooDibosonHistPdf (const RooDibosonHistPdf& other, const char * name);
  virtual TObject * clone(const char * newname) const { 
    return new RooDibosonHistPdf(*this, newname);
  }

  inline virtual ~RooDibosonHistPdf () {}

protected:

  RooRealProxy x;
  RooRealProxy lZ;
  RooRealProxy dkg;
  RooRealProxy dg1;
  RooDataHist * dhist;

  double anomalousRatio() const ;
  virtual double evaluate() const ;

  bool importWorkspaceHook(RooWorkspace& ws);

private:

  ClassDef(RooDibosonHistPdf, 1) // Diboson pdf + aTGC parameters
};

#endif
