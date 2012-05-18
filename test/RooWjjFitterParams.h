// -*- mode: C++ -*-

#ifndef RooWjjFitterParams_h
#define RooWjjFitterParams_h

#include <vector>
#include "TString.h"

class RooWjjFitterParams {
public:
  RooWjjFitterParams();
//   RooWjjFitterParams(RooWjjFitterParams const& other);
  virtual ~RooWjjFitterParams() { }

  TString MCDirectory;
  TString WpJDirectory;
  TString DataDirectory;
  TString NewPhysicsDirectory;
  TString QCDDirectory;
  int nbins;
  std::vector<double> binEdges;
  double minMass;
  double maxMass;
  int njets;
  std::vector<double> JES_scales;
  bool includeMuons;
  bool includeElectrons;
  bool truncRange;
  double minTrunc;
  double maxTrunc;
  bool blind;
  double minWmass;
  double maxWmass;
  bool doNewPhysics;
  bool doAllPlots;
  TString initParamsFile;
  TString constraintParamsFile;
  TString cuts;
  TString QCDcuts;
  TString var;
  TString treeName;
  bool toyWpJ;
  TString muonData;
  TString electronData;
  double intLumi;
  bool overwriteDibosonPDFWithVBFWW;
  bool constrainDiboson;
  bool constrainDibosonShape;
  bool externalConstraints;
  bool constrainWpJShape;
  bool constrainWpJ;
  int WpJfunction;

  //4 body parameters
  bool do4body;
  double minSBHi, maxSBHi;
  TString SBHicut;
  double minSBLo, maxSBLo;
  TString SBLocut;
  std::vector<double> minMasses;
  std::vector<double> maxMasses;
  std::vector<double> alphas;
  std::vector<double> alphaUps;
  std::vector<double> alphaDowns;
  std::vector<double> falphas;
  int smoothWpJ;
  int model;

  //efficiency corrections
  bool doEffCorrections;
  std::vector<TString> muIdEffFiles;
  std::vector<TString> muHLTEffFiles;
  std::vector<double> lumiPerEpochMuon;
  std::vector<TString> eleIdEffFiles;
  std::vector<TString> eleRecoEffFiles;
  std::vector<TString> eleHLTEffFiles;
  std::vector<TString> eleJ30EffFiles;
  std::vector<TString> eleJ25NoJ30EffFiles;
  std::vector<TString> eleMHTEffFiles;
  std::vector<TString> eleWMtEffFiles;
  std::vector<double> lumiPerEpochElectron;

  //fitting range
  double minFit, maxFit;

  ///Use for toyDataset Fitting
  bool fitToyDataset;
  TString ToyDatasetDirectory;
  TString toydataFile;

  ///External Parameters
  bool useExternalMorphingPars;
  double e_fSU;
  double e_fMU;
  double e_minT;
  double e_maxT;

  //histogram smoothing
  int smoothingOrder;

};

RooWjjFitterParams::RooWjjFitterParams() :
  MCDirectory(""), WpJDirectory(""), DataDirectory(""), 
  NewPhysicsDirectory(""),QCDDirectory(""), nbins(24),
  minMass(60.), maxMass(300.), njets(2), JES_scales(2, 0.),
  includeMuons(true), includeElectrons(true),
  truncRange(false), minTrunc(130.), maxTrunc(170.), blind(false),
  minWmass(65.), maxWmass(95.), doNewPhysics(false),
  doAllPlots(false), initParamsFile(""), constraintParamsFile(""),
  cuts(""), QCDcuts(""), var("Mass2j_PFCor"), treeName("WJet"), toyWpJ(false),
  muonData("WmunuJets_DataAll_GoldenJSON_2p1invfb.root"),
  electronData("WenuJets_DataAll_GoldenJSON_2p1invfb.root"),
  intLumi(2100.), overwriteDibosonPDFWithVBFWW(false), 
  constrainDiboson(true), constrainDibosonShape(false),
  externalConstraints(true), constrainWpJShape(false), constrainWpJ(false),
  WpJfunction(0),
  do4body(false),
  minSBHi(95.), maxSBHi(105.), SBHicut(""), 
  minSBLo(55.), maxSBLo(65.), SBLocut(""), smoothWpJ(1), model(1),
  doEffCorrections(false), 
  minFit(minMass), maxFit(maxMass),
  fitToyDataset(false), ToyDatasetDirectory(""), toydataFile(""),
  useExternalMorphingPars(false), e_fSU(-100.0), e_fMU(-100.0),
  e_minT(-1.0), e_maxT(-1.0),
  smoothingOrder(0)
{
}

/*
RooWjjFitterParams::RooWjjFitterParams(RooWjjFitterParams const& other) :
  MCDirectory(other.MCDirectory), WpJDirectory(other.WpJDirectory),
  DataDirectory(other.DataDirectory), 
  NewPhysicsDirectory(other.NewPhysicsDirectory),
  QCDDirectory(other.QCDDirectory),
  nbins(other.nbins), binEdges(other.binEdges), minMass(other.minMass), 
  maxMass(other.maxMass),
  njets(other.njets), JES_scales(other.JES_scales),
  includeMuons(other.includeMuons),
  includeElectrons(other.includeElectrons), truncRange(other.truncRange),
  minTrunc(other.minTrunc), maxTrunc(other.maxTrunc),
  minWmass(other.minWmass), maxWmass(other.maxWmass),
  doNewPhysics(other.doNewPhysics), doAllPlots(other.doAllPlots),
  initParamsFile(other.initParamsFile),
  constraintParamsFile(other.constraintParamsFile),
  cuts(other.cuts), var(other.var), treeName(other.treeName),
  toyWpJ(other.toyWpJ), muonData(other.muonData), 
  electronData(other.electronData), intLumi(other.intLumi),
  constrainDiboson(other.constrainDiboson), 
  externalConstraints(other.externalConstraints),
  do4body(other.do4body),
  minSBHi(other.minSBHi), maxSBHi(other.maxSBHi), SBHicut(other.SBHicut), 
  minSBLo(other.minSBLo), maxSBLo(other.maxSBLo), SBLocut(other.SBLocut),
  minMasses(other.minMasses), maxMasses(other.maxMasses), alphas(other.alphas),
  falphas(other.falphas),
  doEffCorrections(other.doEffCorrections), effDir(other.effDir),

  useExternalMorphingPars(other.useExternalMorphingPars), e_fSU(other.e_fSU), e_fMU(other.e_fMU),
  fitToyDataset(other.fitToyDataset), ToyDatasetDirectory(other.ToyDatasetDirectory), toydataFile(other.toydataFile)
{
}
*/
#endif
