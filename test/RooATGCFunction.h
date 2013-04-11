// -*- mode: c++ -*-

#ifndef ROOATGCFUNCTION
#define ROOATGCFUNCTION

#include "RooRealProxy.h"
#include "RooAbsReal.h"
#include "TProfile2D.h"
#include "TString.h"

class RooATGCFunction : public RooAbsReal {
public:

  RooATGCFunction ();
  RooATGCFunction (const char * name, const char * title,
                   RooAbsReal& _x, RooAbsReal& _lZ,
                   RooAbsReal& _dkg, RooAbsReal& _dg1,
                   const char * parFilename);
  RooATGCFunction (const RooATGCFunction& other, const char * name);
  virtual TObject * clone(const char * newname) const { 
    return new RooATGCFunction(*this, newname);
  }

  virtual ~RooATGCFunction ();

  void readProfiles(TDirectory& dir) const ;

protected:

  RooRealProxy x;
  RooRealProxy lZ;
  RooRealProxy dkg;
  RooRealProxy dg1;

  TString profileFilename;

  TProfile2D ** P_dk; //!
  TProfile2D ** P_dg1; //!

  void initializeProfiles();
  void readProfiles(RooATGCFunction const& other);

  virtual double evaluate() const ;

private:

  ClassDef(RooATGCFunction, 1) // aTGC function 
};

#endif
