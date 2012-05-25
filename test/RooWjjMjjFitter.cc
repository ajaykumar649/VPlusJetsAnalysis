#include "RooWjjMjjFitter.h"

#include "TFile.h"
#include "TH1.h"
#include "TF1.h"
#include "TTree.h"
#include "TMath.h"
#include "TLine.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TVirtualFitter.h"
#include "Math/MinimizerOptions.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"
#include "TMatrixT.h"
#include "TVectorT.h"
#include "TMatrixDSymEigen.h"

#include "TPad.h"

#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif

#include "RooDataSet.h"
#include "RooArgSet.h"
#include "RooArgList.h"
#include "RooRealVar.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooPlot.h"
#include "RooCurve.h"
#include "RooHist.h"
#include "RooProdPdf.h"
#include "RooRandom.h"
#include "RooAbsBinning.h"
#include "RooTreeDataStore.h"
#include "RooGenericPdf.h"
#include "RooCBShape.h"
#include "RooExponential.h"


// #include "ComputeChi2.C"

using namespace RooFit;

Color_t const RooWjjMjjFitter::DibosonColor;

RooWjjMjjFitter::RooWjjMjjFitter() :
  ws_("ws", "ws"), initWjets_(0.), initDiboson_(0.),
  ttbarNorm_(0.), singleTopNorm_(0.), zjetsNorm_(0.),
  QCDNorm_(0.), QCDError_(0.), errorType_(RooAbsData::SumW2),
  histOrder(0)
{
}

RooWjjMjjFitter::RooWjjMjjFitter(RooWjjFitterParams & pars) :
  ws_("ws", "ws"), params_(pars), utils_(pars),
  initWjets_(0.), initDiboson_(0.), ttbarNorm_(0.), singleTopNorm_(0.), 
  zjetsNorm_(0.), QCDNorm_(0.), QCDError_(0.),errorType_(RooAbsData::SumW2),
  histOrder(pars.smoothingOrder)
{
  utils_.vars2ws(ws_);
  RooRealVar * mass = ws_.var(params_.var);
  mass->setRange("lowSideBand", params_.minFit, params_.minTrunc);
  mass->setRange("highSideBand", params_.maxTrunc, params_.maxFit);
  mass->setRange("fitRange", params_.minFit, params_.maxFit);

  rangeString_ = "fitRange";
  if (params_.truncRange) {
    // data = loadData(true);
    rangeString_ = "lowSideBand,highSideBand";
  }
}

RooFitResult * RooWjjMjjFitter::fit(bool repeat) {

  RooAbsPdf * totalPdf = makeFitter(true);
  // RooRealVar * mass = ws_.var(params_.var);

  cout << "Made dataset" << endl;
  RooAbsData * data = loadData();

  std::cout << "-------- Number of expected QCD events: " << QCDNorm_
	    << std::endl;

  RooFitResult *fitResult = 0;
  
  resetYields();
  RooArgSet * params = totalPdf->getParameters(data);
  loadParameters(params_.constraintParamsFile);
  
  RooRealVar * nQCD = ws_.var("nQCD");
  RooGaussian constQCD("constQCD","constQCD", *nQCD, RooConst(nQCD->getVal()),
		       RooConst(nQCD->getError())) ;
  RooRealVar * nTTbar = ws_.var("nTTbar");
  RooGaussian constTTbar("constTTbar","constTTbar", *nTTbar, 
			 RooConst(nTTbar->getVal()),
			 RooConst(nTTbar->getError())) ;
  RooRealVar * nSingleTop = ws_.var("nSingleTop");
  RooGaussian constSingleTop("constSingleTop","constSingleTop", *nSingleTop, 
			     RooConst(nSingleTop->getVal()),
			     RooConst(nSingleTop->getError())) ;
  RooRealVar * nZjets = ws_.var("nZjets");
  RooGaussian constZpJ("constZpJ", "constZpJ", *nZjets, 
		       RooConst(nZjets->getVal()), 
		       RooConst(nZjets->getError()));
  RooRealVar * nDiboson = ws_.var("nDiboson");
  RooGaussian constDiboson("constDiboson", "constDiboson", *nDiboson,
			   RooConst(nDiboson->getVal()), 
			   RooConst(nDiboson->getError()));
  RooRealVar * nWjets = ws_.var("nWjets");
  RooGaussian constWjets("constWjets", "constWjets", *nWjets,
			 RooConst(nWjets->getVal()), 
			 RooConst(nWjets->getError()));

  
  //RooArgList ConstrainedVars;
  RooArgList Constraints;
  
  if (params_.constrainDiboson) {
    Constraints.add(constDiboson);
  }
  if (params_.constrainWpJ) {
    Constraints.add(constWjets);
  }
  Constraints.add(constQCD);
  Constraints.add(constSingleTop);
  Constraints.add(constZpJ);
  Constraints.add(constTTbar);

  RooArgSet * wpjpars =  ws_.pdf("WpJPdf")->getParameters(data);
  RooArgList wpjconst;
  RooArgList constPars;
  TIter par(wpjpars->createIterator());
  par.Reset();
  RooRealVar * param;
  while ((param = dynamic_cast<RooRealVar *>(par.Next()))) {
    if (!param->isConstant()) {
      constPars.addClone(RooConst(param->getVal()));
      constPars.addClone(RooConst(param->getError()));
      RooGaussian theConst(TString::Format("const_%s", param->GetName()),
			   TString::Format("const_%s", param->GetName()),
			   *param, 
			   *((RooAbsReal *)constPars.at(constPars.getSize()-2)),
			   *((RooAbsReal *)constPars.at(constPars.getSize()-1)));
      wpjconst.addClone(theConst);
    }
  }

  delete wpjpars;

  RooArgSet * dibosonpars =  ws_.pdf("dibosonPdf")->getParameters(data);
  RooArgList dibosonconst;
  TIter dibosonpar(dibosonpars->createIterator());
  dibosonpar.Reset();
  while ((param = dynamic_cast<RooRealVar *>(dibosonpar.Next()))) {
    if (!param->isConstant()) {
      constPars.addClone(RooConst(param->getVal()));
      constPars.addClone(RooConst(param->getError()));
      RooGaussian theConst(TString::Format("const_%s", param->GetName()),
			   TString::Format("const_%s", param->GetName()),
			   *param, 
			   *((RooAbsReal *)constPars.at(constPars.getSize()-2)),
			   *((RooAbsReal *)constPars.at(constPars.getSize()-1)));
      dibosonconst.addClone(theConst);
    }
  }

  delete dibosonpars;
       
  if (params_.constrainWpJShape) {
    Constraints.add(wpjconst);
  }
  
  if (params_.constrainDibosonShape) {
    Constraints.add(dibosonconst);
  }
  
  loadParameters(params_.initParamsFile);
  if (repeat)
    loadParameters("lastWjjFitParams.txt");
  //cout << "params_.e_fSU=" << params_.e_fSU << endl;
  
  //ws_.Print();
  std::cout << "\n***constraints***\n";
  TIter con(Constraints.createIterator());
  RooGaussian * tc;
  while ((tc = (RooGaussian *)con()))
    tc->Print();
  std::cout << "*** ***\n\n";
  
  RooAbsPdf * fitPdf = totalPdf;
  if (!params_.externalConstraints) {
    Constraints.add(*totalPdf);
    fitPdf = new RooProdPdf("fitPdf", "fitPdf", Constraints);
  }
  fitResult = fitPdf->fitTo(*data, Save(true), 
			    ( (params_.externalConstraints) ?
			      ExternalConstraints(Constraints) :
			      Constrained() ),
			    RooFit::Extended(true), 
			    RooFit::Minos(false), 
			    RooFit::Hesse(true),
			    PrintEvalErrors(-1),
			    RooFit::Range(rangeString_),
			    Warnings(false) 
			    );
  
  fitResult->Print("v");
  params->writeToFile("lastWjjFitParams.txt");

  delete params;
  return fitResult;
}

double RooWjjMjjFitter::computeChi2(int& ndf, bool correct) {

  RooRealVar * mass = ws_.var(params_.var);
  RooAbsBinning& plotBins =  mass->getBinning("plotBinning");
  mass->setBinning(plotBins);
  RooAbsData * data = ws_.data("data");

  TH1 * dataHist = utils_.newEmptyHist("theData");
  RooTreeDataStore * dataStore = 
    dynamic_cast<RooTreeDataStore *>(data->store());
  dataStore->tree().Draw(TString::Format("%s>>%s", mass->GetName(),
					 "theData"),
			 utils_.fitCuts(), "goff");
  //dataHist->Scale(1., "width");
  RooHist h_data(*dataHist, 0., 1, errorType_, 1.0,
		 false);
  RooAbsPdf * totalPdf = ws_.pdf("totalPdf");


  int chi2bins;
  double chi2 = RooWjjFitterUtils::computeChi2(h_data, *totalPdf, *mass, 
					       chi2bins, correct);

  chi2bins -= ndf;
  std::cout << "\n *** chi^2/dof = " << chi2 << "/" << chi2bins << " = " 
	    << chi2/chi2bins << " ***\n"
	    << " *** chi^2 probability = " << TMath::Prob(chi2, chi2bins)
	    << " ***\n\n";

  delete dataHist;
  ndf = chi2bins;
  return chi2;
}

RooAbsPdf * RooWjjMjjFitter::makeFitter(bool allOne) {

  if (ws_.pdf("totalPdf"))
    return ws_.pdf("totalPdf");

  //RooRealVar * mass = ws_.var(params_.var);
  RooAbsPdf * dibosonPdf = makeDibosonPdf();
  RooAbsPdf * WpJPdf = makeWpJPdf(allOne);
  RooAbsPdf * ttPdf = makettbarPdf();
  RooAbsPdf * stPdf = makeSingleTopPdf();
  RooAbsPdf * qcdPdf = makeQCDPdf();
  RooAbsPdf * ZpJPdf =  makeZpJPdf();

  //// Initialization only, the actual values are set by resetYields()
  RooRealVar nDiboson("nDiboson","nDiboson",  initDiboson_);
  nDiboson.setConstant(false);
  nDiboson.setError(initDiboson_*0.10);
  RooRealVar nTTbar("nTTbar","", ttbarNorm_);
  nTTbar.setError(ttbarNorm_*0.063);
  nTTbar.setConstant(false);
  RooRealVar nSingleTop("nSingleTop","", singleTopNorm_);
  nSingleTop.setError(singleTopNorm_*0.05);
  nSingleTop.setConstant(false);
  RooRealVar nQCD("nQCD","nQCD", QCDNorm_);
  nQCD.setError(QCDError_);
  nQCD.setConstant(false);
  RooRealVar nZjets("nZjets","nZjets", zjetsNorm_);
  nZjets.setError(zjetsNorm_*0.043);
  nZjets.setConstant(false);
  RooRealVar nNP("nNP", "N_{new physics}", 0., 0., 10000.);
  nNP.setError(100.);
  nNP.setConstant(false);

  RooAbsPdf * WpJPdfMU = ws_.pdf("WpJPdfMU");
  RooAbsReal * NMU = ws_.function("NMU");
  RooAbsPdf * WpJPdfMD = ws_.pdf("WpJPdfMD");
  RooAbsReal * NMD = ws_.function("NMD");
  RooAbsPdf * WpJPdfSU = ws_.pdf("WpJPdfSU");
  RooAbsReal * NSU = ws_.function("NSU");
  RooAbsPdf * WpJPdfSD = ws_.pdf("WpJPdfSD");
  RooAbsReal * NSD = ws_.function("NSD");

  RooAbsPdf * WpJPdfNom = ws_.pdf("WpJPdfNom");
  RooAbsReal * NNom = ws_.function("NNom");

  RooRealVar * nWjets = ws_.var("nWjets");

  RooArgList components(*dibosonPdf);
  RooArgList yields(nDiboson);
  if (allOne) {
    components.add(*WpJPdf);
    yields.add(*nWjets);
  } else {
    components.add(RooArgList(*WpJPdfMU,*WpJPdfMD,*WpJPdfSU,
			      *WpJPdfSD,*WpJPdfNom));
    yields.add(RooArgList(*NMU, *NMD, *NSU, *NSD, *NNom));
  }
  components.add(RooArgList(*ttPdf, *stPdf, *qcdPdf, *ZpJPdf));
  yields.add(RooArgList(nTTbar, nSingleTop, nQCD, nZjets));
  
  if (params_.doNewPhysics) {
    RooAbsPdf * NPPdf = makeNPPdf();
    components.add(*NPPdf);
    yields.add(nNP);
  }
  RooAddPdf totalPdf("totalPdf","extended sum pdf", components, yields);

  ws_.import(totalPdf);

  bool ToyMCGenerate=false;
  if ( ToyMCGenerate ) {
    /////*** Begin Toy MC Generation Code ***/////
    //   char I_char[5];
    //   sprintf(I_char,"%i",params_.njets);
    //   TString I_str=I_char;
    TString L_str="mu_";

    ///No btag:
    TString Tag_str="NoBtag_";
    Int_t Offset=470839;

    cout << "Generating Diboson" << endl;
    generateToyMCSet(dibosonPdf,"/uscms_data/d1/ilyao/DibosonS12/ErrorScans/1KMCSource/Diboson_"+ L_str + Tag_str+"2j_GenMC.root",1100*2000,5004+Offset);

    //  resetfSUfMU(0.0,0.0);
    cout << "Generating Wjj - default" << endl;
    generateToyMCSet(WpJPdfNom,"/uscms_data/d1/ilyao/DibosonS12/ErrorScans/1KMCSource/WjjDef_"+ L_str + Tag_str+"2j_GenMC.root",1100*70000,1837+Offset);

    //  resetfSUfMU(1.0,0.0);
    cout << "Generating Wjj - ScaleUp" << endl;
    generateToyMCSet(WpJPdfSU,"/uscms_data/d1/ilyao/DibosonS12/ErrorScans/1KMCSource/WjjSU_"+ L_str + Tag_str+"2j_GenMC.root",1100*5000,1632+Offset);

    //  resetfSUfMU(-1.0,0.0);
    cout << "Generating Wjj - ScaleDown" << endl;
    generateToyMCSet(WpJPdfSD,"/uscms_data/d1/ilyao/DibosonS12/ErrorScans/1KMCSource/WjjSD_"+ L_str + Tag_str+"2j_GenMC.root",1100*5000,44991+Offset);

    //  resetfSUfMU(0.0,1.0);
    cout << "Generating Wjj - MatchingUp" << endl;
    generateToyMCSet(WpJPdfMU,"/uscms_data/d1/ilyao/DibosonS12/ErrorScans/1KMCSource/WjjMU_"+ L_str + Tag_str+"2j_GenMC.root",1100*5000,607+Offset);

    //  resetfSUfMU(0.0,-1.0);
    cout << "Generating Wjj - MatchingDown" << endl;
    generateToyMCSet(WpJPdfMD,"/uscms_data/d1/ilyao/DibosonS12/ErrorScans/1KMCSource/WjjMD_"+ L_str + Tag_str+"2j_GenMC.root",1100*10000,4803+Offset);

    cout << "Generating tt" << endl;
    generateToyMCSet(ttPdf,"/uscms_data/d1/ilyao/DibosonS12/ErrorScans/1KMCSource/tt_"+ L_str + Tag_str+"2j_GenMC.root",1100*2000,5753+Offset);

    cout << "Generating singleTop" << endl;
    generateToyMCSet(stPdf,"/uscms_data/d1/ilyao/DibosonS12/ErrorScans/1KMCSource/singleTop_"+ L_str + Tag_str+"2j_GenMC.root",1100*1000,2237+Offset);

    cout << "Generating qcd" << endl;
    generateToyMCSet(qcdPdf,"/uscms_data/d1/ilyao/DibosonS12/ErrorScans/1KMCSource/qcd_"+ L_str + Tag_str+"2j_GenMC.root",1100*500,1891+Offset);

    cout << "Generating zjets" << endl;
    generateToyMCSet(ZpJPdf,"/uscms_data/d1/ilyao/DibosonS12/ErrorScans/1KMCSource/zjets_"+ L_str + Tag_str+"2j_GenMC.root",1100*5000,8058+Offset);


    ///With btag (mc for the fit not yet ready):
    //   TString Tab_str="WithBtag_";
    //   Int_t Offset=129839;

    /////*** End Toy MC Generation Code ***/////
  }

  return ws_.pdf("totalPdf"); 
}

RooAbsPdf * RooWjjMjjFitter::make4BodyPdf(RooWjjMjjFitter & fitter2body) {
  if (ws_.pdf("totalPdf4"))
    return ws_.pdf("totalPdf4");

  makeFitter();
  loadParameters(params_.initParamsFile);

  RooAbsPdf * dibosonPdf = makeDibosonPdf();
  RooAbsPdf * ttPdf = makettbarPdf();
  RooAbsPdf * stPdf = makeSingleTopPdf();
  RooAbsPdf * qcdPdf = makeQCDPdf();
  RooAbsPdf * ZpJPdf =  makeZpJPdf();
  RooAbsPdf * WpJPdf = makeWpJ4BodyPdf(fitter2body);

  RooRealVar * nWjets = ws_.var("nWjets");
  RooRealVar * nDiboson = ws_.var("nDiboson");
  RooRealVar * nTTbar = ws_.var("nTTbar");
  RooRealVar * nSingleTop = ws_.var("nSingleTop");
  RooRealVar * nQCD = ws_.var("nQCD");
  RooRealVar * nZjets = ws_.var("nZjets");

  RooArgList components(*dibosonPdf);
  RooArgList yields(*nDiboson);
  components.add(*WpJPdf);
  yields.add(*nWjets);
  components.add(RooArgList(*ttPdf, *stPdf, *qcdPdf, *ZpJPdf));
  yields.add(RooArgList(*nTTbar, *nSingleTop, *nQCD, *nZjets));

  if (params_.doNewPhysics) {
    RooAbsPdf * NPPdf = makeNPPdf();
    RooRealVar * nNP = ws_.var("nNP");
    components.add(*NPPdf);
    yields.add(*nNP);
  }

//   components.Print("v");
//   yields.Print("v");
  RooAddPdf totalPdf4("totalPdf4", "totalPdf4", components, yields);

  ws_.import(totalPdf4);

  return ws_.pdf("totalPdf4");
}

RooAbsData * RooWjjMjjFitter::loadData(bool trunc) {
  if ((trunc) && (ws_.data("truncData")))
    return ws_.data("truncData");
  if ((!trunc) && (ws_.data("data")))
    return ws_.data("data");

  RooRealVar * mass = ws_.var(params_.var);

  TString dataName("data");
  if (trunc)
    dataName = "truncData";

  RooDataSet data(dataName, dataName, RooArgSet(*mass));
  QCDNorm_ = 0.;
  QCDError_ = 0.;

  double rel2jet = 0.0663, rel3jet = 0.0229, rmu2jet = 0.001625, rmu3jet = 0.;
  double erel2jet = rel2jet*0.5, erel3jet = rel3jet*0.5, ermu2jet = 0.004214, ermu3jet = 0.0040797;


//   if (params_.fitToyDataset) {
//     RooDataSet * tds;
//     tds = utils_.File2Dataset(params_.ToyDatasetDirectory + 
// 					   params_.toydataFile, 
// 					   "data_muon",false,
// 					   trunc, true);
//     tds->Print();

//     double fracel=0.5;
//     double fracmu=0.5;
//     if ( params_.njets==3 ) {
//       fracel=0.442;
//       fracmu=0.558;
//       QCDNorm_ += (rmu3jet*fracmu+rel3jet*fracel)*tds->sumEntries();
//       QCDError_ += TMath::Power(ermu3jet*fracmu*tds->sumEntries(),2);
//       QCDError_ += TMath::Power(erel3jet*fracel*tds->sumEntries(),2);
//     } else {
//       fracel=0.434;
//       fracmu=0.566;
//       QCDNorm_ += (rmu2jet*fracmu+rel2jet*fracel)*tds->sumEntries();
//       QCDError_ += TMath::Power(ermu2jet*fracmu*tds->sumEntries(),2);
//       QCDError_ += TMath::Power(erel2jet*fracel*tds->sumEntries(),2);
//     }
//     data.append(*tds);
//     delete tds;

//   } else {
  if (params_.includeMuons) {
    RooDataSet * mds;
    if (params_.fitToyDataset) {
      mds = utils_.File2Dataset(params_.ToyDatasetDirectory + 
				params_.toydataFile, 
				"data_muon",false,
				trunc, true);

    } else {
      mds = utils_.File2Dataset(params_.DataDirectory + 
				params_.muonData, "data_muon", 
				false, trunc, false);
    }
    mds->Print();

    /// Note: for the 2+3 jets we use the 2jet bin coefficients
    if ( params_.njets==3 ) {
      QCDNorm_ += rmu3jet*mds->sumEntries();
      QCDError_ += TMath::Power(ermu3jet*mds->sumEntries(),2);
    } else {
      QCDNorm_ += rmu2jet*mds->sumEntries();
      QCDError_ += TMath::Power(ermu2jet*mds->sumEntries(),2);
    }
    data.append(*mds);
    delete mds;
  }
  if (params_.includeElectrons) {
    RooDataSet * eds;
    if (params_.fitToyDataset) {
      eds = utils_.File2Dataset(params_.ToyDatasetDirectory + 
				params_.toydataFile, 
				"data_electron", true, trunc, 
				false);
    } else {
      eds = utils_.File2Dataset(params_.DataDirectory + 
				params_.electronData, 
				"data_electron", true, trunc, 
				false);
    }
      
    eds->Print();
    if ( params_.njets==3 ) {
      QCDNorm_ += rel3jet*eds->sumEntries();
      QCDError_ += TMath::Power(erel3jet*eds->sumEntries(),2);
    } else {
      QCDNorm_ += rel2jet*eds->sumEntries();
      QCDError_ += TMath::Power(erel2jet*eds->sumEntries(),2);
    }

    data.append(*eds);
    delete eds;
  }
    //}
  QCDError_ = TMath::Sqrt(QCDError_);
  ws_.import(data);

  return ws_.data(dataName);
}

RooAbsPdf * RooWjjMjjFitter::makeDibosonPdf(int parameterize) {

  //Scale the trees by the Crossection/Ngenerated (43/4225916=1.01753087377979123e-05 for WW and 18.2/4265243=4.22015814808206740e-06 for WZ).
  if (ws_.pdf("dibosonPdf"))
    return ws_.pdf("dibosonPdf");
//   //CMS Preliminary:
//   double WWweight = 53./4225916.;
//   double WZweight = 17./4265243.;
  //NLO Predictions
  int const NgenWW = 4225916, NgenWZ = 4265243;
  double const WWxsec = 47.0, WZxsec = 18.6;
  double WWweight = WWxsec/NgenWW;
  double WZweight = WZxsec/NgenWZ;
  //VBF Predictions
  int const NgenVBFWpWm = 454720, NgenVBFWmWp = 112991;
  double const VBFWpWmxsec = 0.0009, VBFWmWpxsec = 0.0009;
  double VBFWpWmweight = VBFWpWmxsec/NgenVBFWpWm;
  double VBFWmWpweight = VBFWmWpxsec/NgenVBFWmWp;


  int dibosonScale = 1;
  TH1 * th1diboson = utils_.newEmptyHist("th1diboson", dibosonScale);

  TH1 * tmpHist;

  double sumWW = 0., sumWZ = 0.;
  double sumVBFWpWm = 0., sumVBFWmWp = 0.;
//   double NWW = 0, NWZ = 0;
  if (params_.overwriteDibosonPDFWithVBFWW) {
    if (params_.includeMuons) {
      tmpHist = utils_.File2Hist(params_.MCDirectory+"mu_qiangli-WpWmEW_CMSSW428.root",
				 "hist_ww_mu", false, 0, false, dibosonScale);
      sumVBFWpWm += tmpHist->Integral();
      th1diboson->Add(tmpHist, VBFWpWmweight);
      delete tmpHist;

      tmpHist = utils_.File2Hist(params_.MCDirectory+"mu_qiangli_qed6_CMSSW428.root",
				 "hist_ww_mu", false, 0, false, dibosonScale);
      sumVBFWmWp += tmpHist->Integral();
      th1diboson->Add(tmpHist, VBFWmWpweight);
      delete tmpHist;
    }
    if (params_.includeElectrons) {
      double fakeSampleCorrFactor=0.7329;
      tmpHist = utils_.File2Hist(params_.MCDirectory+"el_qiangli-WpWmEW_CMSSW428_FakeFromMuon.root",
				 "hist_ww_el", true, 0, false, dibosonScale);
      sumVBFWpWm += fakeSampleCorrFactor*tmpHist->Integral();
      th1diboson->Add(tmpHist, fakeSampleCorrFactor*VBFWpWmweight);
      delete tmpHist;

      tmpHist = utils_.File2Hist(params_.MCDirectory+"el_qiangli_qed6_CMSSW428_FakeFromMuon.root",
				 "hist_ww_el", true, 0, false, dibosonScale);
      sumVBFWmWp += fakeSampleCorrFactor*tmpHist->Integral();
      th1diboson->Add(tmpHist, fakeSampleCorrFactor*VBFWmWpweight);
      delete tmpHist;
    }
  } else {
    if (params_.includeMuons) {
      tmpHist  = utils_.File2Hist(params_.MCDirectory+"mu_WW_CMSSW428.root",
				  "hist_ww_mu", false, 0, false, dibosonScale);
      sumWW += tmpHist->Integral();
      //     NWW += NgenWW/2.;
      th1diboson->Add(tmpHist, WWweight);
      delete tmpHist;
      tmpHist = utils_.File2Hist(params_.MCDirectory+"mu_WZ_CMSSW428.root",
				 "hist_wz_mu", false, 0, false, dibosonScale);
      sumWZ += tmpHist->Integral();
      //     NWZ += NgenWZ/2.;
      th1diboson->Add(tmpHist, WZweight);
      delete tmpHist;
    }
    if (params_.includeElectrons) {
      tmpHist  = utils_.File2Hist(params_.MCDirectory+"el_WW_CMSSW428.root",
				  "hist_ww_el", true, 0, false, dibosonScale);
      sumWW += tmpHist->Integral();
      //     NWW += NgenWW/2.;
      th1diboson->Add(tmpHist, WWweight);
      delete tmpHist;
      tmpHist = utils_.File2Hist(params_.MCDirectory+"el_WZ_CMSSW428.root",
				 "hist_wz_el", true, 0, false, dibosonScale);
      sumWZ += tmpHist->Integral();
      //     NWZ += NgenWZ/2.;
      th1diboson->Add(tmpHist, WZweight);
      delete tmpHist;
    }
  }
//   std::cout << "min bin: " << th1diboson->FindBin(params_.minFit)
// 	    << " max bin: " << th1diboson->FindBin(params_.maxFit) 
// 	    << " n bins: " << th1diboson->GetNbinsX()
// 	    << '\n';
  initDiboson_ = th1diboson->Integral(th1diboson->FindBin(params_.minFit),
				      th1diboson->FindBin(params_.maxFit)-1) * 
    params_.intLumi;
  if (params_.overwriteDibosonPDFWithVBFWW) {
    cout << "-------- Number of expected VBFWW events = " 
	 << th1diboson->Integral() << " x " << params_.intLumi 
	 << " = " <<  initDiboson_ << '\n';

    cout <<"----------- VBFWpWm: acc x eff = " << sumVBFWpWm*VBFWpWmweight*params_.intLumi 
	 << "/" << NgenVBFWpWm*VBFWpWmweight*params_.intLumi << " = " <<sumVBFWpWm/NgenVBFWpWm
	 << '\n';
    cout <<"----------- VBFWmWp: acc x eff = " << sumVBFWmWp*VBFWmWpweight*params_.intLumi 
	 << "/" << NgenVBFWmWp*VBFWmWpweight*params_.intLumi << " = " <<sumVBFWmWp/NgenVBFWmWp
	 << '\n';
    cout << "----------- VBFWW: acc x eff = " << (sumVBFWpWm/NgenVBFWpWm*VBFWpWmxsec + sumVBFWmWp/NgenVBFWmWp*VBFWmWpxsec)/(VBFWpWmxsec + VBFWmWpxsec)
	 << '\n';
    cout.flush();
  } else {
    cout << "-------- Number of expected WW+WZ events = " 
	 << th1diboson->Integral() << " x " << params_.intLumi 
	 << " = " <<  initDiboson_ << '\n';

    cout <<"----------- WW: acc x eff = " << sumWW*WWweight*params_.intLumi 
	 << "/" << NgenWW*WWweight*params_.intLumi << " = " <<sumWW/NgenWW 
	 << '\n';
    cout <<"----------- WZ: acc x eff = " << sumWZ*WZweight*params_.intLumi 
	 << "/" << NgenWZ*WZweight*params_.intLumi << " = " <<sumWZ/NgenWZ 
	 << '\n';
    cout << "----------- diboson: acc x eff = " << (sumWW/NgenWW*WWxsec + sumWZ/NgenWZ*WZxsec)/(WWxsec + WZxsec)
	 << '\n';
    cout.flush();
  }

  if (parameterize) {

    if (parameterize == 1) {
      ws_.factory(TString::Format("RooCBShape::sig_WW(%s, mean_WW[85], "
				  "expr::sigma_WW('mean_WW*resolution_WW',"
				  "mean_WW,resolution_WW[0.095])"
				  ", alpha[1.7], n[2.5])", 
				  params_.var.Data()));
      ws_.factory(TString::Format("RooCBShape::sig_WZ(%s, mean_WZ[85], "
				  "expr::sigma_WZ('mean_WZ*resolution_WZ',"
				  "mean_WZ,resolution_WZ[0.095])"
				  ", alpha[1.7], n[2.5])", 
				  params_.var.Data()));
      ws_.factory(TString::Format("EXPR::tail('(TMath::Erf((@0-@1)/@2)+1)/2',"
				  "%s, turnOn_diboson[80], width_turnOn[38])", 
				  params_.var.Data()));
      ws_.factory("SUM::WWPdf(f_core[0.588]*sig_WW,tail)");
      ws_.factory("SUM::WZPdf(f_core*sig_WZ,tail)");
    } else {
      ws_.factory(TString::Format("RooGaussian::sig_WW(%s, mean_WW[85], "
				  "expr::sigma_WW('mean_WW*resolution_WW',"
				  "mean_WW,resolution_WW[0.095]))",
				  params_.var.Data()));
      ws_.factory(TString::Format("RooGaussian::sig_WZ(%s, mean_WZ[85], "
				  "expr::sigma_WZ('mean_WZ*resolution_WZ',"
				  "mean_WZ,resolution_WZ[0.095]))",
				  params_.var.Data()));
      ws_.factory(TString::Format("RooBifurGauss::tail(%s, m_tail[70],"
				  "sig_left[20], sig_right[20])",
				  params_.var.Data()));
      ws_.factory("SUM::WWPdf(f_core[0.588]*sig_WW,tail)");
      ws_.factory("SUM::WZPdf(f_core*sig_WZ,tail)");      
    }

    ws_.factory(TString::Format("SUM::dibosonPdf(f_WW[%.4f]*WWPdf, WZPdf)",
			       sumWW*WWweight/(sumWW*WWweight+sumWZ*WZweight)));

  } else {
    th1diboson->Scale(1., "width");
    RooAbsPdf * dibosonPdf = utils_.Hist2Pdf(th1diboson, "dibosonPdf",
					     ws_, histOrder);
    ws_.import(*dibosonPdf);
    //delete dibosonPdf;
  }

  delete th1diboson;

  return ws_.pdf("dibosonPdf");

}

RooAbsPdf * RooWjjMjjFitter::makeWpJPdf(bool allOne) {  

  if (ws_.pdf("WpJPdf"))
    return ws_.pdf("WpJPdf");

  TH1 * th1WpJ = utils_.newEmptyHist("th1WpJ");
  TH1 * th1WpJInc = utils_.newEmptyHist("th1WpJInc");
  TH1 * th1WpJMU = utils_.newEmptyHist("th1WpJMU");
  TH1 * th1WpJMD = utils_.newEmptyHist("th1WpJMD");
  TH1 * th1WpJSU = utils_.newEmptyHist("th1WpJSU");
  TH1 * th1WpJSD = utils_.newEmptyHist("th1WpJSD");

  TH1 * tmpHist;
  if (params_.includeMuons) {
    tmpHist = utils_.File2Hist(params_.WpJDirectory + 
			       "mu_WpJ_CMSSW428.root",
			       "hist_wpj_mu", false, 1, params_.toyWpJ);
    th1WpJInc->Add(tmpHist);
    delete tmpHist;
    if ( params_.useWbbPDF ) {
      cout << "Using the Wbb sample as WJets" << endl;
      tmpHist = utils_.File2Hist("/uscms_data/d2/yangf/ana/WuvWjj/Full2011Data/RDTreeDebug/RD_mu_WbbCrossCheck_CMSSW428.root",
				 "hist_wpj_mu", false, 1, params_.toyWpJ);
      th1WpJ->Add(tmpHist);
      cout << "NWJetDefaultHistEntries=" << th1WpJ->GetEntries() << endl;
      delete tmpHist;
    } else {
      tmpHist = utils_.File2Hist(params_.WpJDirectory + 
				 //"mu_W4Jets_CMSSW428.root",
				 "mu_WpJ_CMSSW428.root",
				 "hist_wpj_mu", false, 1, params_.toyWpJ);
      th1WpJ->Add(tmpHist);
      cout << "NWJetDefaultHistEntries=" << th1WpJ->GetEntries() << endl;
      delete tmpHist;
    }
    tmpHist = utils_.File2Hist(params_.WpJDirectory + 
			       "mu_WpJmatchingup_CMSSW428.root",
			       "hist_wpj_mu_mu", false, 1, params_.toyWpJ);
    th1WpJMU->Add(tmpHist);
    delete tmpHist;
    tmpHist = utils_.File2Hist(params_.WpJDirectory + 
			       "mu_WpJmatchingdown_CMSSW428.root",
			       "hist_wpj_mu_md", false, 1, params_.toyWpJ);
    th1WpJMD->Add(tmpHist);
    delete tmpHist;
    tmpHist = utils_.File2Hist(params_.WpJDirectory + 
			       "mu_WpJscaleup_CMSSW428.root",
			       "hist_wpj_mu_su", false, 1, params_.toyWpJ);
    th1WpJSU->Add(tmpHist);
    delete tmpHist;
    tmpHist = utils_.File2Hist(params_.WpJDirectory + 
			       "mu_WpJscaledown_CMSSW428.root",
			       "hist_wpj_mu_sd", false, 1, params_.toyWpJ);
    th1WpJSD->Add(tmpHist);
    delete tmpHist;
  }

  if (params_.includeElectrons) {
    tmpHist = utils_.File2Hist(params_.WpJDirectory + 
			       "el_WpJ_CMSSW428.root",
			       "hist_wpj_el", true, 1, params_.toyWpJ);
    th1WpJInc->Add(tmpHist);
    delete tmpHist;
    if ( params_.useWbbPDF ) {
      cerr << "No Wbb sample for electrons" << endl;
    } else {
      tmpHist = utils_.File2Hist(params_.WpJDirectory + 
				 //"mu_W4Jets_CMSSW428.root",
				 "el_WpJ_CMSSW428.root",
				 "hist_wpj_el", true, 1, params_.toyWpJ);
      th1WpJ->Add(tmpHist);
      cout << "NWJetDefaultHistEntries=" << th1WpJ->GetEntries() << endl;
      delete tmpHist;
    }


    tmpHist = utils_.File2Hist(params_.WpJDirectory + 
			       "el_WpJmatchingup_CMSSW428.root",
			       "hist_wpj_el_mu", true, 1, params_.toyWpJ);
    th1WpJMU->Add(tmpHist);
    delete tmpHist;
    tmpHist = utils_.File2Hist(params_.WpJDirectory + 
			       "el_WpJmatchingdown_CMSSW428.root",
			       "hist_wpj_el_md", true, 1, params_.toyWpJ);
    th1WpJMD->Add(tmpHist);
    delete tmpHist;
    tmpHist = utils_.File2Hist(params_.WpJDirectory + 
			       "el_WpJscaleup_CMSSW428.root",
			       "hist_wpj_el_su", true, 1, params_.toyWpJ);
    th1WpJSU->Add(tmpHist);
    delete tmpHist;
    tmpHist = utils_.File2Hist(params_.WpJDirectory + 
			       "el_WpJscaledown_CMSSW428.root",
			       "hist_wpj_el_sd", true, 1, params_.toyWpJ);
    th1WpJSD->Add(tmpHist);
    delete tmpHist;
  }

  double WJetsCrossX=31314.;
  double WJetsNGen=81352581.;

//   ///Not reliable, take the number of excpected events to be the same as for the WJets inclusive sample
//   if ( params_.useWbbPDF ) {
//     WJetsCrossX=85.6;
//     WJetsNGen=22503418;
//   }

  cout << "Using the Inclusive WJets sample to compute the number of initial events" << endl;
  initWjets_ = (WJetsCrossX/WJetsNGen) * 
    (th1WpJInc->Integral(th1WpJInc->FindBin(params_.minFit),
		      th1WpJInc->FindBin(params_.maxFit)-1)) * 
    params_.intLumi;
  cout << "-------- Number of expected Wjj events = " <<  initWjets_ << endl;

//   th1WpJ->Draw();
//   gPad->Update();
//   gPad->WaitPrimitive();

  th1WpJ->Scale(1, "width");
  th1WpJMU->Scale(1, "width");
  th1WpJMD->Scale(1, "width");
  th1WpJSU->Scale(1, "width");
  th1WpJSD->Scale(1, "width");

//   th1WpJ->Draw();
//   gPad->Update();
//   gPad->WaitPrimitive();

  RooArgList pdfs;
  RooArgList coefs;

  RooRealVar nWjets("nWjets","nWjets", initWjets_);
  nWjets.setConstant(false);
  nWjets.setError(TMath::Sqrt(initWjets_));

  RooAbsPdf * WpJPdfSU = utils_.Hist2Pdf(th1WpJSU, "WpJPdfSU", ws_, histOrder);
  RooRealVar fSU("fSU", "f_{scaleUp}", 0., -1., 1.);
  RooAbsPdf * WpJPdfSD = utils_.Hist2Pdf(th1WpJSD, "WpJPdfSD", ws_, histOrder);

  RooAbsPdf * WpJPdfMU = utils_.Hist2Pdf(th1WpJMU, "WpJPdfMU", ws_, histOrder);
  RooRealVar fMU("fMU", "f_{matchingUp}", 0., -1., 1.);

  if (params_.useExternalMorphingPars) {
    if ( params_.e_fMU>-1.1 ) {
      fMU.setVal(params_.e_fMU);
      fMU.setConstant();
    }
    if ( params_.e_fSU>-1.1 ) {
      fSU.setVal(params_.e_fSU);
      fSU.setConstant();
    }
  }

  RooAbsPdf * WpJPdfMD = utils_.Hist2Pdf(th1WpJMD, "WpJPdfMD", ws_, histOrder);

  RooAbsPdf * WpJPdfNom = utils_.Hist2Pdf(th1WpJ, "WpJPdfNom", ws_, histOrder);

  RooFormulaVar NMU("NMU", "@0*@1*(@1 >= 0.)", RooArgList(nWjets,fMU));
  RooFormulaVar NMD("NMD", "@0*@1*(-1)*(@1 < 0.)", RooArgList(nWjets,fMU));
  RooFormulaVar NSU("NSU", "@0*@1*(@1 >= 0.)", RooArgList(nWjets,fSU));
  RooFormulaVar NSD("NSD", "@0*@1*(-1)*(@1 < 0.)", RooArgList(nWjets,fSU));
  RooFormulaVar NNom("NNom", "@0*(1.-abs(@1)-abs(@2))",RooArgList(nWjets,fMU,fSU));

  RooRealVar * mass = ws_.var(params_.var);
  RooRealVar turnOn("turnOn","turnOn", 40.);
  turnOn.setConstant(false);
  turnOn.setMin(0.);
  RooRealVar width("width","width", 15.);
  width.setError(5.);
  width.setMin(0.);
  width.setConstant(false);
  RooRealVar seff("seff", "seff", 7000., 0., 10000.);
  seff.setConstant(true);
  RooRealVar power("power", "power", 2, -100., 1000.);
  power.setError(0.2);
  RooRealVar power2("power2", "power2", 0., -100., 1000.);
  power2.setError(0.2);
  RooRealVar mean("mean", "peak", 67);
  mean.setConstant(false);
  RooRealVar alpha("alpha", "alpha", -1.0);
  alpha.setConstant(false);
  RooGenericPdf WpJPdfPower("WpJPdfPower", "WpJPdfPower",
			    "1./TMath::Power(@0,@1+@2*log(@0/@3))",
			    RooArgList(*mass,power,power2,seff));
  RooGenericPdf bkgErf("WpJPdfErf","WpJPdfErf",
		       "(TMath::Erf((@0-@1)/@2)+1)/2.",
		       RooArgList(*mass, turnOn, width));
  RooGenericPdf bkgFermi("WpJPdfFermi","WpJPdfFermi",
		       "1./(1+exp(-(@0-@1)/@2))",
		       RooArgList(*mass, turnOn, width));
  RooRealVar tau("tau", "tau", -0.02);
  tau.setConstant(false);
  RooExponential WpJPdfExp("WpJPdfExp", "WpJPdfExp", *mass, tau);
  RooRealVar sigma("sigma", "#sigma", 80.);
  sigma.setConstant(false);
  RooGaussian bkgGaus("bkgGaus", "bkgGaus", *mass, mean, sigma);
  RooRealVar f_g("f_g", "f_g", 0.59, 0., 1.);
  RooRealVar m_tail("m_tail", "m_tail", 147, 0., 500.);
  RooRealVar sig_tail("sigma_tail", "sigma_tail", 30., 0., 200.);
  RooGaussian bkgGausTail("bkgGausTail", "bkgGausTail", *mass, 
			  m_tail, sigma);

  if (allOne) {
    switch (params_.WpJfunction) {
    case 1:
      power2.setVal(0.);
      power2.setConstant(true);
    case 7:
      turnOn.setVal(45.);
      width.setVal(20.);
      ws_.import(RooProdPdf("WpJPdf", "WpJPdf", 
			    RooArgList(WpJPdfPower,WpJPdfExp,bkgErf), 
			    1e-5));
      break;
    case 2:
      width.setVal(10);
      ws_.import(RooProdPdf("WpJPdf", "WpJPdf", 
			    RooArgList(WpJPdfPower, bkgFermi), 1e-5));
      break;
    case 3:
      width.setVal(10);
      ws_.import(RooProdPdf("WpJPdf", "WpJPdf", 
			    RooArgList(WpJPdfExp, bkgFermi), 1e-5));
      break;
    case 4:
      power2.setVal(0.);
      power2.setConstant(true);      
    case 5:
      power.setVal(-4.);
      tau.setVal(-0.033);
      ws_.import(RooProdPdf("WpJPdf", "WpJPdf", 
			    RooArgList(WpJPdfExp,WpJPdfPower), 1e-5));
      break;
    case 8:
      turnOn.setVal(31.);
      width.setVal(9.9);
      tau.setVal(-0.01);
      ws_.import(RooProdPdf("WpJPdf", "WpJPdf", RooArgList(bkgErf,WpJPdfExp),
			    1e-6));
      break;
    case 9:
      ws_.import(RooAddPdf("WpJPdf", "WpJPdf", bkgGaus, WpJPdfExp, f_g));
      break;
    case 10:
      ws_.import(RooAddPdf("WpJPdf", "WpJPdf", bkgGaus, bkgGausTail, f_g));
      break;
    case 6:
      power2.setVal(0.);
      power2.setConstant(true);
    case 0:
    default:
      if ( params_.useWbbPDF ) {
	RooRealVar tempVar("tempVar","tempVar",0.5);
	ws_.import(RooAddPdf("WpJPdf","WpJPdf", RooArgList(*WpJPdfNom,*WpJPdfNom),RooArgList(tempVar,tempVar)));
      } else {
	ws_.import(RooProdPdf("WpJPdf", "WpJPdf", 
			      RooArgList(WpJPdfPower, bkgErf), 1e-5));
      }
    //     WpJPdfPower.SetName("WpJPdf");
//     ws_.import(WpJPdfPower);
//     WpJPdfCB.SetName("WpJPdf");
//     ws_.import(WpJPdfCB);
    }
    ws_.import(nWjets);
  } else {
    RooAddPdf WpJPdf("WpJPdf","WpJPdf", RooArgList(*WpJPdfMU,*WpJPdfMD,
						   *WpJPdfSU,*WpJPdfSD,
						   *WpJPdfNom),
		     RooArgList(NMU, NMD, NSU, NSD, NNom));
    ws_.import(WpJPdf);
  }


  delete th1WpJSU;
  delete th1WpJSD;
  delete th1WpJMU;
  delete th1WpJMD;
  delete th1WpJ;

  return ws_.pdf("WpJPdf");
  //return WjetsShape;
}

RooAbsPdf * RooWjjMjjFitter::makettbarPdf() {

  if (ws_.pdf("ttPdf"))
    return ws_.pdf("ttPdf");

  int ttScale = 1;
  double NttbarGenerated = 3701947.0;
  TH1 * th1tt = utils_.newEmptyHist("th1tt", ttScale);

  TH1 * tmpHist;
  TString TTbarFileSuffix="TTbar_CMSSW428.root";

  switch ( params_.implementTTbarScaleMatchingSystOption ) {

  case 1:
    cout << "Fitting Using TTbar : MatchingUp" << endl;
    TTbarFileSuffix="TTbarMatchingUp_CMSSW428.root";
    NttbarGenerated=4029823;
    break;

  case -1:
    cout << "Fitting Using TTbar : MatchingDown" << endl;
    TTbarFileSuffix="TTbarMatchingDown_CMSSW428.root";
    NttbarGenerated=207317;
    break;

  case 2:
    cout << "Fitting Using TTbar : ScaleUp" << endl;
    TTbarFileSuffix="TTbarScaleUp_CMSSW428.root";
    NttbarGenerated=3696269;
    break;

  case -2:
    cout << "Fitting Using TTbar : ScaleDown" << endl;
    TTbarFileSuffix="TTbarScaleDown_CMSSW428.root";
    NttbarGenerated=4004587;
    break;
  }

  if (params_.includeMuons) {
    tmpHist = utils_.File2Hist(params_.MCDirectory + 
			       "mu_" + TTbarFileSuffix,
			       "hist_tt_mu", false, 1, false, ttScale);
    th1tt->Add(tmpHist);
    delete tmpHist;
  }
  if (params_.includeElectrons) {
    tmpHist = utils_.File2Hist(params_.MCDirectory + 
			       "el_" + TTbarFileSuffix,
			       "hist_tt_el", true, 1, false, ttScale);
    th1tt->Add(tmpHist);
    delete tmpHist;
  }


  ttbarNorm_ = (163./NttbarGenerated) * 
    th1tt->Integral(th1tt->FindBin(params_.minFit),
		    th1tt->FindBin(params_.maxFit)-1) * 
    params_.intLumi;
  cout << "-------- Number of expected ttbar events = " 
       << th1tt->Integral() << " x " << params_.intLumi << " = " 
       << ttbarNorm_ << endl;

  th1tt->Scale(1., "width");
  RooAbsPdf * ttPdf = utils_.Hist2Pdf(th1tt, "ttPdf", ws_, histOrder);
  delete th1tt;
  return ttPdf;

}

RooAbsPdf * RooWjjMjjFitter::makeSingleTopPdf() {

  if (ws_.pdf("stPdf"))
    return ws_.pdf("stPdf");

  // --------- s channel cross section: Tbar - 1.44 pb, events_gen = 137980; T - 3.19 pb, events_gen = 259971
  // --------- t channel cross section: Tbar - 22.65 pb, events_gen = 1944826; T - 41.92 pb, events_gen = 3900171
  // --------- tW channel cross section: Tbar - 7.87 pb, events_gen = 787629; T - 7.87 pb, events_gen = 795379
  // --------- https://twiki.cern.ch/twiki/bin/viewauth/CMS/SingleTopSigma 

  double STopWeight = 3.19/259971;
  double STopBarWeight = 1.44/137980;
  double TTopWeight = 41.92/3900171;
  double TTopBarWeight = 22.65/1944826;
  double TWTopWeight = 7.87/795379;
  double TWTopBarWeight = 7.87/787629;

  std::cout << "s channel tbar: " << STopBarWeight
	    << " t: " << STopWeight << "\n"
	    << "t channel tbar: " << TTopBarWeight
	    << " t: " << TTopWeight << "\n"
	    << "tW channel tbar: " << TWTopBarWeight
	    << " t: " << TWTopWeight
	    << "\n";

  int stScale = 1;

  TH1 * th1st = utils_.newEmptyHist("th1st", stScale);

  TH1 * tmpHist;
  if (params_.includeMuons) {
    tmpHist = utils_.File2Hist(params_.MCDirectory + 
			       "mu_STopS_Tbar_CMSSW428.root",
			       "hist_stbar_mu", false, 1, false, stScale);
    th1st->Add(tmpHist, STopBarWeight);
//     tmpHist->Print();
    delete tmpHist;
    tmpHist = utils_.File2Hist(params_.MCDirectory + 
			       "mu_STopS_T_CMSSW428.root",
			       "hist_st_mu", false, 1, false, stScale);
    th1st->Add(tmpHist, STopWeight);
//     tmpHist->Print();
    delete tmpHist;
    tmpHist = utils_.File2Hist(params_.MCDirectory + 
			       "mu_STopT_Tbar_CMSSW428.root",
			       "hist_stbar_mu", false, 1, false, stScale);
    th1st->Add(tmpHist, TTopBarWeight);
//     tmpHist->Print();
    delete tmpHist;
    tmpHist = utils_.File2Hist(params_.MCDirectory + 
			       "mu_STopT_T_CMSSW428.root",
			       "hist_st_mu", false, 1, false, stScale);
    th1st->Add(tmpHist, TTopWeight);
//     tmpHist->Print();
    delete tmpHist;
    tmpHist = utils_.File2Hist(params_.MCDirectory + 
			       "mu_STopTW_Tbar_CMSSW428.root",
			       "hist_stbar_mu", false, 1, false, stScale);
    th1st->Add(tmpHist, TWTopBarWeight);
//     tmpHist->Print();
    delete tmpHist;
    tmpHist = utils_.File2Hist(params_.MCDirectory + 
			       "mu_STopTW_T_CMSSW428.root",
			       "hist_st_mu", false, 1, false, stScale);
    th1st->Add(tmpHist, TWTopWeight);
//     tmpHist->Print();
    delete tmpHist;
  }
  if (params_.includeElectrons) {
    tmpHist = utils_.File2Hist(params_.MCDirectory + 
			       "el_STopS_Tbar_CMSSW428.root",
			       "hist_stbar_el", true, 1, false, stScale);
    th1st->Add(tmpHist, STopBarWeight);
//     tmpHist->Print();
    delete tmpHist;
    tmpHist = utils_.File2Hist(params_.MCDirectory + 
			       "el_STopS_T_CMSSW428.root",
			       "hist_st_el", true, 1, false, stScale);
    th1st->Add(tmpHist, STopWeight);
//     tmpHist->Print();
    delete tmpHist;
    tmpHist = utils_.File2Hist(params_.MCDirectory + 
			       "el_STopT_Tbar_CMSSW428.root",
			       "hist_stbar_el", true, 1, false, stScale);
    th1st->Add(tmpHist, TTopBarWeight);
//     tmpHist->Print();
    delete tmpHist;
    tmpHist = utils_.File2Hist(params_.MCDirectory + 
			       "el_STopT_T_CMSSW428.root",
			       "hist_st_el", true, 1, false, stScale);
    th1st->Add(tmpHist, TTopWeight);
//     tmpHist->Print();
    delete tmpHist;
    tmpHist = utils_.File2Hist(params_.MCDirectory + 
			       "el_STopTW_Tbar_CMSSW428.root",
			       "hist_stbar_el", true, 1, false, stScale);
    th1st->Add(tmpHist, TWTopBarWeight);
//     tmpHist->Print();
    delete tmpHist;
    tmpHist = utils_.File2Hist(params_.MCDirectory + 
			       "el_STopTW_T_CMSSW428.root",
			       "hist_st_el", true, 1, false, stScale);
    th1st->Add(tmpHist, TWTopWeight);
//     tmpHist->Print();
    delete tmpHist;
  }

  singleTopNorm_ = th1st->Integral(th1st->FindBin(params_.minFit),
				   th1st->FindBin(params_.maxFit)-1) * 
    params_.intLumi;

//   if (params_.includeElectrons && params_.includeMuons)
//     singleTopNorm_ *= 2;
  cout << "-------- Number of expected single top events = " << 
    th1st->Integral() << " x " << params_.intLumi << " = " << singleTopNorm_ << endl;

  th1st->Scale(1., "width");
  RooAbsPdf * stPdf = utils_.Hist2Pdf(th1st, "stPdf", ws_, histOrder);
  delete th1st;
  return stPdf;

}


// ***** Function to return the QCD Pdf **** //
RooAbsPdf* RooWjjMjjFitter::makeQCDPdf() {  

  if (ws_.pdf("qcdPdf"))
    return ws_.pdf("qcdPdf");

  //// Scaling Coefficients = 84679.3/25080241, 3866200/70392060, 139500/2194800, 136804/2030033, 9360/1082691 = 3.37633517955429532e-03, 5.49238081681371476e-02, 6.35593220338983023e-02, 6.73900375018534198e-02, 8.64512589464584008e-03 
//   double weight1 = 84679.3/25080241;
//   double weight2 = 3866200./70392060.;
//   double weight3 = 139500./2194800.;
//   double weight4 = 136804./2030033.;
//   double weight5 = 9360./1082691.;

  TH1 * th1qcd = utils_.newEmptyHist("th1qcd");

  TH1 * tmpHist;
  if (params_.includeMuons) {
    tmpHist = utils_.File2Hist(params_.QCDDirectory + 
			       "RDQCD_WmunuJets_DataAll_GoldenJSON_2p1invfb.root",
			       "hist_qcd_mu", false, 1, false, 1, 
			       params_.QCDcuts);
    th1qcd->Add(tmpHist);
    delete tmpHist;
  }
  if (params_.includeElectrons) {
    tmpHist = utils_.File2Hist(params_.QCDDirectory + 
			       "RDQCD_WenuJets_DataAll_GoldenJSON_2p1invfb.root",
			       "hist_qcd_el", true, 1, false, 1,
			       params_.QCDcuts);
    th1qcd->Add(tmpHist);
    delete tmpHist;
  }

  th1qcd->Print();
  th1qcd->Scale(1., "width");
  RooAbsPdf* qcdPdf = utils_.Hist2Pdf(th1qcd,"qcdPdf", ws_, histOrder);
  delete th1qcd;    
  return qcdPdf;
}


// ***** Function to return the Z+jets Pdf **** //
RooAbsPdf * RooWjjMjjFitter::makeZpJPdf() {  

  if (ws_.pdf("ZpJPdf"))
    return ws_.pdf("ZpJPdf");
  
  int ZpJScale = 1;

  TH1 * th1ZpJ = utils_.newEmptyHist("th1ZpJ", ZpJScale);

  TH1 * tmpHist;

  if (params_.includeMuons) {
    tmpHist = utils_.File2Hist(params_.MCDirectory + "mu_ZpJ_CMSSW428.root",
			       "hist_zpj_mu", false, 1, false, ZpJScale);
    th1ZpJ->Add(tmpHist);
    delete tmpHist;
  }
  if (params_.includeElectrons) {
    tmpHist = utils_.File2Hist(params_.MCDirectory + "el_ZpJ_CMSSW428.root",
			       "hist_zpj_el", true, 1, false, ZpJScale);
    th1ZpJ->Add(tmpHist);
    delete tmpHist;
  }

  zjetsNorm_ = (3048./36277961.) * 
    th1ZpJ->Integral(th1ZpJ->FindBin(params_.minFit),
		     th1ZpJ->FindBin(params_.maxFit)-1) * 
    params_.intLumi;
  cout << "-------- Number of expected zjets events = " 
       << th1ZpJ->Integral() << " x " << params_.intLumi << " = " 
       << zjetsNorm_ << endl;

  th1ZpJ->Scale(1., "width");

  RooAbsPdf * ZpJPdf = utils_.Hist2Pdf(th1ZpJ, "ZpJPdf", ws_, histOrder);
  delete th1ZpJ;
  return ZpJPdf;
}

RooAbsPdf * RooWjjMjjFitter::makeNPPdf() {

  if (ws_.pdf("NPPdf"))
    return ws_.pdf("NPPdf");

  TH1 * th1NP = utils_.newEmptyHist("th1NP", 1);

//   TH1 * tmpHist;
//   if (params_.includeMuons) {
//     tmpHist = utils_.File2Hist(params_.NewPhysicsDirectory + 
// 			       "mu_ZprimeMadGraph_CMSSW428.root",
// 			       "hist_np_mu", false, 1, false);
//     th1NP->Add(tmpHist);
//     delete tmpHist;
//   }
//   if (params_.includeElectrons) {
//     tmpHist = utils_.File2Hist(params_.NewPhysicsDirectory + 
// 			       "el_ZprimeMadGraph_CMSSW428.root",
// 			       "hist_np_el", true, 1, false);
//     th1NP->Add(tmpHist);
//     delete tmpHist;
//   }

  TF1 genGaussian("genGaussian", "TMath::Gaus(x, [0], [1])",
		  params_.minMass, params_.maxMass);
  genGaussian.SetParameters(150., 15.);
  th1NP->FillRandom("genGaussian", 100000);
  th1NP->Scale(1., "width");

  RooAbsPdf * NPPdf = utils_.Hist2Pdf(th1NP, "NPPdf", ws_, 
				      (histOrder==1)? histOrder+1 : histOrder);
  delete th1NP;
  return NPPdf;
}

RooAbsPdf * RooWjjMjjFitter::makeWpJ4BodyPdf(RooWjjMjjFitter & fitter2body) {
  if (ws_.pdf("WpJ4BodyPdf"))
    return ws_.pdf("WpJ4BodyPdf");

  fitter2body.ws_.var(fitter2body.params_.var)->setRange("RangeWmass", 
							 params_.minWmass,
							 params_.maxWmass);
  ws_.var(params_.var)->SetTitle("m_{l#nujj}");

  RooWjjFitterParams parsSBHi(params_);
  parsSBHi.cuts = params_.SBHicut;
  RooWjjMjjFitter shapesSBHi(parsSBHi);
  shapesSBHi.makeQCDPdf();
  shapesSBHi.makettbarPdf();
  shapesSBHi.makeSingleTopPdf();
  shapesSBHi.makeZpJPdf();
  shapesSBHi.makeDibosonPdf();

  RooWjjFitterParams parsSBLo(params_);
  parsSBLo.cuts = params_.SBLocut;
  RooWjjMjjFitter shapesSBLo(parsSBLo);
  shapesSBLo.makeQCDPdf();
  shapesSBLo.makettbarPdf();
  shapesSBLo.makeSingleTopPdf();
  shapesSBLo.makeZpJPdf();
  shapesSBLo.makeDibosonPdf();

  TH1 * th1wjets = utils_.newEmptyHist("th1wjets");

  TH1 * wjets = 0;
  std::vector<TH1*> shapes;
  TH1 * alphaDownHist = utils_.newEmptyHist("wjets_alphaDown");
  TH1 * alphaUpHist = utils_.newEmptyHist("wjets_alphaUp");
  for (unsigned int range = 0; range < params_.alphas.size(); ++range) {
    wjets = getWpJHistFromData(TString::Format("wjets%i", range),
			       params_.alphas[range], 
			       params_.alphaDowns[range],
			       params_.alphaUps[range],
			       params_.minMasses[range],
			       params_.maxMasses[range],
			       fitter2body, shapesSBHi,
			       shapesSBLo,
			       alphaDownHist, alphaUpHist);

    wjets->Print();
    alphaDownHist->Print();
    alphaUpHist->Print();
//     wjets->Draw();
//     gPad->Update();
//     gPad->WaitPrimitive();

    shapes.push_back(wjets);
  }

  for(unsigned int range = 0; range < shapes.size(); ++range) {
    th1wjets->Add(shapes[range]);
    delete shapes[range];
  }

  double n2bWpJ = ws_.var("nWjets")->getVal();

  std::cout << "n2bWpJ: " << n2bWpJ << '\n';
  th1wjets->Print();
  alphaDownHist->Print();
  alphaUpHist->Print();
//   th1wjets->Scale(1./th1wjets->Integral());
// //   th1wjets->Scale(1., "width");
//   th1wjets->Print();

  RooRealVar * mass = ws_.var(params_.var);
  RooDataHist theSBData("theSBData", "theSBData", RooArgList(*mass), th1wjets);
  RooDataHist theSBAlphaDown("theSBAlphaDown", "theSBAlphaDown", 
			     RooArgList(*mass), alphaDownHist);
  RooDataHist theSBAlphaUp("theSBAlphaUp", "theSBAlphaUp", 
			   RooArgList(*mass), alphaUpHist);
  theSBData.Print();

  double localMax = params_.maxMass;
  int localBin = th1wjets->GetNbinsX();
  std::cout << "localMax: " << localMax 
	    << " last bin: " << th1wjets->GetBinContent(localBin) << " +/- "
	    << th1wjets->GetBinError(localBin)
	    << '\n';
  while ((th1wjets->GetBinContent(localBin) <= 0) && (localBin > 0)) {
    localMax = th1wjets->GetBinLowEdge(localBin);
    --localBin;
  }
  localBin = 1;
  while ( (localBin <= th1wjets->GetNbinsX()) && 
	  (th1wjets->GetBinContent(localBin++) >= 0)) ;
  if ( (localMax > th1wjets->GetBinLowEdge(localBin)) &&
       (th1wjets->GetBinContent(localBin-1) <= 0) )
    localMax = th1wjets->GetBinLowEdge(localBin-1);
  
  std::cout << "localMax: " << localMax 
	    << " last bin: " << th1wjets->GetBinContent(localBin) << " +/- "
	    << th1wjets->GetBinError(localBin)
	    << '\n';

  th1wjets->Scale(1./th1wjets->Integral());
  RooDataHist theSBDataNorm("theSBDataNorm", "theSBDataNorm", 
			    RooArgList(*mass), th1wjets);
//   TF1 * fitf = 0;
//   if (params_.model == 1) {
//     TString fitString("exp([0]*x)*[0]/(exp([0]*[1])-exp([0]*[2]))");
//     fitf = new TF1("fitf", fitString, params_.minMass, localMax);
//     fitf->SetParameter(0, -0.015);
//     fitf->FixParameter(1, localMax);
//     fitf->FixParameter(2, params_.minMass);

//   } else if (params_.model == 2) {
//     fitf = new TF1("fitf", "[0]/TMath::Power(x-[2], [1])", 
// 		   params_.minMass, localMax);
//     fitf->SetParameters(2e11, 5.);
//   } else if (params_.model == 3) {
//     fitf = new TF1("fitf", 
// 		   TString::Format("[0]*TMath::Gaus(x,[1]+%0.0f,[2])", 
// 				   params_.minMass), 
// 		   params_.minMass, localMax);
//   } else if (params_.model == 4) {
//     TString fitString("exp([0]+[1]*x)");
//     fitf = new TF1("fitf", fitString, th1wjets->GetBinLowEdge(2), localMax);
//     fitf->SetParameters(6.0, -0.015);
//   } else if (params_.model == 5) {
//     TString fitString("exp([0]+[1]*x)*(TMath::Erf((x-[2])/[3])+1)");
//     fitf = new TF1("fitf", fitString, th1wjets->GetBinLowEdge(1), localMax);
//     fitf->SetParameters(6.0, -0.015, 170., 15.);
//     fitf->FixParameter(3, 15.);
//   }

//   TVirtualFitter::SetMaxIterations(10000);
//   TFitResultPtr fr;
//   if (fitf) {
//     //fitf->Print();
//     fr = th1wjets->Fit("fitf", "wlrsq0");
//     fr->Print("v");
//   }

//   th1wjets->SetStats(false);
//   th1wjets->Draw();
//   th1wjets->SetXTitle("m_{l#nujj} (GeV)");
//   th1wjets->SetYTitle("Events / GeV");
//   gPad->Update();
//   if (th1wjets->GetMinimum() > 1.) {
//     th1wjets->SetMinimum(0.);
//   }
//   gPad->WaitPrimitive();
//   RooAbsPdf * WpJ4BodyPdf = utils_.Hist2Pdf(th1wjets, "WpJ4BodyPdf", 
// 					    ws_, histOrder);
  RooRealVar c("c", "c", -0.015);
  c.setConstant(false);
  c.Print();
  RooExponential expPdf("WpJ4BodyExp", "exp", *mass, c);
  RooRealVar turnOn("turnOn4", "turnOn4", 170.);
  turnOn.setConstant(false);
  RooRealVar width("width4", "width4", 15.);
  RooGenericPdf erf("WpJ4BodyErf","erf",
		    "(TMath::Erf((@0-@1)/@2)+1)",
		    RooArgList(*mass, turnOn, width));
  RooFitResult * fr = 0;
  mass->setRange("SBFitRange", params_.minMass, localMax);
  if (params_.model == 4)
    mass->setRange("SBFitRange", th1wjets->GetBinLowEdge(2), localMax);
  double diff = 0, newErr = 0;
  switch (params_.model) {
  case 4:
  case 5:
  case 1:     
    if (params_.model == 5) {
      ws_.import(RooProdPdf("WpJ4BodyPdf", "WpJ4BodyPdf", 
			    RooArgList(erf, expPdf)));
      
    } else {
      expPdf.SetName("WpJ4BodyPdf");
      //expPdf.Print("v");
      ws_.import(expPdf);
    }
    ws_.import(*(ws_.pdf("WpJ4BodyPdf")), 
	       RooFit::RenameVariable("c","c_down"),
	       RooFit::RenameAllNodes("down"));
    ws_.import(*(ws_.pdf("WpJ4BodyPdf")), 
	       RooFit::RenameVariable("c", "c_up"),
	       RooFit::RenameAllNodes("up"));
    ws_.Print();
    ws_.pdf("WpJ4BodyPdf_down")->fitTo(theSBAlphaDown, 
				       RooFit::Minos(false),
				       RooFit::SumW2Error(false),
				       RooFit::Range("SBFitRange")
				       );
    ws_.pdf("WpJ4BodyPdf_up")->fitTo(theSBAlphaUp, 
				       RooFit::Minos(false),
				       RooFit::SumW2Error(false),
				       RooFit::Range("SBFitRange")
				       );
    fr = ws_.pdf("WpJ4BodyPdf")->fitTo(theSBData, RooFit::Minos(false),
				       RooFit::SumW2Error(false),
				       RooFit::Range("SBFitRange"),
				       RooFit::Save(true));

    diff = 
      TMath::Max(fabs(ws_.var("c")->getVal() - ws_.var("c_down")->getVal()),
		 fabs(ws_.var("c")->getVal() - ws_.var("c_up")->getVal()));
    newErr = TMath::Power(ws_.var("c")->getError(), 2) + diff*diff;
    ws_.var("c")->setError(sqrt(newErr));
    break;
//   case 2: {
//     RooRealVar power("power", "power", fitf->GetParameter(1));
//     power.setError(fitf->GetParError(1));
//     RooGenericPdf WpJ4Body2("WpJ4BodyPdf", "power",
// 			    "1/TMath::Power(@0, @1)",
// 			    RooArgList(*mass, power));
//     ws_.import(WpJ4Body2);
//   }
//     break;
//   case 3: {
//     RooRealVar mean("mean", "mean", fitf->GetParameter(2)+params_.minMass);
//     mean.setError(fitf->GetParError(1));
//     mean.setConstant(false);
//     RooRealVar sigma("sigma", "sigma", fitf->GetParameter(3));
//     sigma.setError(fitf->GetParError(2));
//     sigma.setConstant(false);
//     RooGaussian WpJ4Body3("WpJ4BodyPdf", "gaussian", *mass, mean, sigma);
// //     RooFitResult * fr4 = WpJ4Body3.fitTo(theSBData, 
// // 					 RooFit::Minos(false),
// // 					 RooFit::SumW2Error(false),
// // 					 RooFit::Save(true));
// //     fr4->Print();
//     ws_.import(WpJ4Body3);
//   }
//     break;
  default:
    utils_.Hist2Pdf(th1wjets, "WpJ4BodyPdf", ws_, histOrder);
  }

//   if (fr >= 0) {
//     TMatrixDSymEigen eigen(fr->GetCovarianceMatrix());
//     TVectorD errs2(eigen.GetEigenValues());
//     TMatrixD V(eigen.GetEigenVectors());
//     TMatrixD Vt(V.T());
//     TGraph * fitGraph = new TGraph(fitf);
//     fitGraph->SetLineColor(kRed+1);
//     fitGraph->SetLineWidth(3);
//     TGraphAsymmErrors * errGraph = 
//       new TGraphAsymmErrors(fitGraph->GetN(), fitGraph->GetX(),
// 			    fitGraph->GetY());
//     errGraph->SetFillColor(kBlue+1);
//     errGraph->SetLineColor(kBlue+1);
//     errGraph->SetFillStyle(3353);
//     double diff;
//     for (int i = 0; i<errs2.GetNrows(); ++i) {
//       for (int updown = -1; updown<= 1; updown+=2) {
// 	TMatrixD newVals(fitf->GetNpar(), 1, fitf->GetParameters());
// 	TMatrixD newValsp(newVals);
// 	newValsp.Mult(Vt, newVals);
// 	newValsp[i][0] += updown*sqrt(errs2[i]);
// 	newVals.Mult(newValsp.T(), V);
// 	TF1 * fitf_new = new TF1(*fitf);
// 	fitf_new->SetName( TString::Format( "fitf%d_%s",i,
// 					    ((updown<0)?"down":"up") ) );
// 	fitf_new->SetParameter(0, newVals[0][0]);
// 	fitf_new->SetParameter(1, newVals[1][0]);
// 	//fitf_new->SetLineColor(kBlue);
// 	//fitf_new->Draw("lsame");
// 	for (int xi = 0; xi < fitGraph->GetN(); ++xi) {
// 	  diff = (*fitf_new)(fitGraph->GetX()[xi]) - 
// 	    (*fitf)(fitGraph->GetX()[xi]);
// 	  if (diff > 0)
// 	    errGraph->SetPointEYhigh(xi, 
// 				     errGraph->GetErrorYhigh(xi) + diff*diff);
// 	  else
// 	    errGraph->SetPointEYlow(xi, 
// 				    errGraph->GetErrorYlow(xi) + diff*diff);
// 	}
// 	delete fitf_new;
//       }
//     }
//     fitf->SetLineWidth(3);
//     for (int xi=0; xi < errGraph->GetN(); ++xi) {
//       errGraph->SetPointEYhigh(xi, sqrt(errGraph->GetErrorYhigh(xi)));
//       errGraph->SetPointEYlow(xi, sqrt(errGraph->GetErrorYlow(xi)));
//     }
// //     TGraphErrors * confGraph = 
// //       new TGraphErrors(fitGraph->GetN(), fitGraph->GetX(), fitGraph->GetY());
// //     confGraph->SetLineColor(kCyan+2);
// //     confGraph->SetFillColor(kCyan+2);
// //     confGraph->SetFillStyle(3335);  
// //     TVirtualFitter::GetFitter()->GetConfidenceIntervals(confGraph, 0.68);
// //     confGraph->Draw("3");
//     errGraph->Draw("3");
//     fitGraph->Draw("l");
//     th1wjets->Draw("same");
//   }

  RooPlot * sbf = mass->frame(RooFit::Name("SideBandPlot"));
  theSBDataNorm.plotOn(sbf);
  ws_.pdf("WpJ4BodyPdf")->plotOn(sbf);
  sbf->Draw();
  sbf->GetYaxis()->SetTitle("normalized units");
  gPad->Modified();
  gPad->Update();
  
  cout << "chi2/ndf: " << sbf->chiSquare(fr->floatParsFinal().getSize())
       << " n bins: " << sbf->GetNbinsX();

  if (fr) {
    cout << " parameters: " << fr->floatParsFinal().getSize();
    delete fr;
  }
  cout << '\n';

//   if (fitf)
//     delete fitf;
  //delete th1wjets;
  
  return ws_.pdf("WpJ4BodyPdf");
}

RooPlot * RooWjjMjjFitter::stackedPlot(bool logy, fitMode fm, bool leftLeg) {
  RooRealVar * mass = ws_.var(params_.var);
  mass->setRange("RangeForPlot", params_.minMass, 
				 params_.maxMass);
  RooAbsBinning& plotBins =  mass->getBinning("plotBinning");
  mass->setBinning(plotBins);
//   ws_.var(params_.var)->Print("v");
  RooPlot * sframe = mass->frame();
  sframe->SetName("mass_stacked");
  RooAbsData * data = ws_.data("data");

  TString plotHistName(TString::Format("dataHistPlot_%i", logy));
  TH1 * dataHist = utils_.newEmptyHist(plotHistName);
  RooTreeDataStore * dataStore = 
    dynamic_cast<RooTreeDataStore *>(data->store());
  dataStore->tree().Draw(TString::Format("%s>>%s", mass->GetName(),
					 plotHistName.Data()),
			 "", "goff");
  dataHist->SetTitle("data");

  
//   dataHist->Draw();
//   gPad->Update();
//   gPad->WaitPrimitive();
  dataHist->Scale(1., "width");
  RooHist * h_data = new RooHist(*dataHist, 0., 1, errorType_, 1.0,
				 false);
  RooHist * theData = new RooHist(*h_data);
//   dataHist->Draw();
//   gPad->Update();
//   gPad->WaitPrimitive();

  RooAddPdf * totalPdf = dynamic_cast<RooAddPdf *>(ws_.pdf("totalPdf"));
  if (fm == mlnujj) 
    totalPdf = dynamic_cast<RooAddPdf *>(ws_.pdf("totalPdf4"));
  totalPdf->Print();
  RooArgList components(totalPdf->pdfList());

//   components.Print("v");
//   h_data->SetName("h_data");
//   sframe->addPlotable(h_data, "pe", true, true);
//   data->plotOn(sframe, RooFit::DataError(errorType_), 
// 	       RooFit::Binning(plotBins),
// 	       RooFit::Name("h_data"),
// 	       RooFit::Invisible());

  int comp(1);
  double nexp(totalPdf->expectedEvents(RooArgSet(*(ws_.var(params_.var)))));
  std::cout << totalPdf->GetName() << " expected: " << nexp << '\n'
	    << "data normalization: " << dataHist->GetEntries() << '\n'
// 	    << "frame NEvt: " << sframe->getFitRangeNEvt() << '\n'
// 	    << "frame BinW: " << sframe->getFitRangeBinW() << '\n'
 	    << '\n';
  if (fm == mlnujj)
    nexp = dataHist->GetEntries();
  delete dataHist;
//   TH1 * pdfHist = totalPdf->createHistogram("pdfHist", *mass,
// 					    Binning(plotBins),
// 					    Scaling(false));

//   pdfHist->Scale(nexp);
//   pdfHist->SetLineColor(kRed);
//   pdfHist->SetMarkerColor(kRed);
//   pdfHist->Draw();
//   dataHist->Draw("same");
//   gPad->Update();
//   gPad->WaitPrimitive();

  totalPdf->plotOn(sframe,ProjWData(*data), DrawOption("LF"), FillStyle(1001),
		   FillColor(DibosonColor), LineColor(DibosonColor), 
		   Name("h_total"),
 		   NormRange("RangeForPlot"),
		   Normalization(nexp, RooAbsReal::Raw),
		   VLines(), Range("RangeForPlot"));
  RooCurve * tmpCurve = sframe->getCurve("h_total");
  tmpCurve->SetTitle("WW/WZ");
  components.remove(*(components.find("dibosonPdf")));
  if (params_.doNewPhysics) {
    totalPdf->plotOn(sframe, ProjWData(*data), DrawOption("LF"), 
		     FillStyle(1001), //Name("h_NP"), 
		     VLines(),
		     FillColor(kCyan+2), LineColor(kCyan+2), 
		     Normalization(nexp, RooAbsReal::Raw),
		     Components(RooArgSet(components)),
		     NormRange("RangeForPlot"),
		     Range("RangeForPlot"));
    tmpCurve = sframe->getCurve();
    tmpCurve->SetName("h_NP");
    tmpCurve->SetTitle("Gaussian signal");
    components.remove(*(components.find("NPPdf")));
  }
  int linec(kRed);
  int fills(1001);
  TString pdfName("h_background");
  RooAbsCollection * removals;
  while (components.getSize() > 0) {
    totalPdf->plotOn(sframe, ProjWData(*data), FillColor(linec), 
// 		     Name(pdfName),
		     DrawOption("LF"), Range("RangeForPlot"),
		     NormRange("RangeForPlot"),
		     Normalization(nexp, RooAbsReal::Raw),
		     Components(RooArgSet(components)), VLines(),
		     FillStyle(fills), LineColor(linec));
    tmpCurve = sframe->getCurve();
    tmpCurve->SetName(pdfName);
    removals = 0;
    switch (comp) {
    case 1: 
      removals = components.selectByName("WpJ*");
      linec = kGreen+2;
      //fills = 3444;
      tmpCurve->SetTitle("W+jets");
      break;
    case 2: 
      linec = kGray+1;
      //fills = 1001;
      removals = components.selectByName("ttPdf*,stPdf*");
      tmpCurve->SetTitle("top");
      break;
    case 3: 
      linec = kYellow; 
      //fills = 3395;
      removals = components.selectByName("qcdPdf*");
      tmpCurve->SetTitle("QCD");
      break;
    default:
      linec = kCyan;
      //fills = 1001;
      removals = components.selectByName("ZpJPdf*");
      tmpCurve->SetTitle("Z+jets");
    }
    if (removals) {
      components.remove(*removals);
      delete removals;
    }
    if (components.getSize() > 0) {
      pdfName = components[0].GetName();
      pdfName = "h_" + pdfName;
    }
    ++comp;
  }
  theData->SetName("theData");
  sframe->addPlotable(theData, "pe");
//   data->plotOn(sframe, RooFit::DataError(errorType_), Name("theData"),
// 	       RooFit::Binning(plotBins));
  RooHist * tmpHist = sframe->getHist("theData");
  tmpHist->SetTitle("data");
//   sframe->addObject(dataHist, "samepe");
  TLegend * legend = RooWjjFitterUtils::legend4Plot(sframe, leftLeg);
  sframe->addObject(legend);
  if (params_.truncRange) {
    TLine * lowerLine = new TLine(params_.minTrunc, 0., params_.minTrunc, 
				  sframe->GetMaximum());
    lowerLine->SetLineWidth(2);
    lowerLine->SetLineColor(kGray+2);
    lowerLine->SetLineStyle(9);
    TLine * upperLine = new TLine(params_.maxTrunc, 0., params_.maxTrunc, 
				  sframe->GetMaximum());
    upperLine->SetLineWidth(2);
    upperLine->SetLineColor(kGray+2);
    upperLine->SetLineStyle(9);
    sframe->addObject(lowerLine);
    sframe->addObject(upperLine);
  }
  if (logy) {
    sframe->SetMinimum(0.01);
    sframe->SetMaximum(1.0e6);
  } else {
    sframe->SetMinimum(1e-6);
    sframe->SetMaximum(1.4*sframe->GetMaximum());
  }
  if ((params_.truncRange) && (params_.blind)) {
    TBox * blind = new TBox(params_.minTrunc,sframe->GetMinimum(),
			    params_.maxTrunc,sframe->GetMaximum());
    blind->SetFillColor(kBlack);
    blind->SetFillStyle(1001);
    sframe->addObject(blind);
  }
  sframe->GetYaxis()->SetTitle("Events / GeV");
  return sframe;
}

RooPlot * RooWjjMjjFitter::residualPlot(RooPlot * thePlot, TString curveName,
					TString pdfName, bool normalize, 
					fitMode fm) {
  RooPlot * rframe = thePlot->emptyClone("mass_residuals");
  RooAbsData * data = ws_.data("data");
  RooAddPdf * totalPdf = dynamic_cast<RooAddPdf *>(ws_.pdf("totalPdf"));
  if (fm == mlnujj) 
    totalPdf = dynamic_cast<RooAddPdf *>(ws_.pdf("totalPdf4"));
  RooCurve * tmpCurve;
//   RooHist * theData = new RooHist(*(thePlot->getHist("theData")));
  if (pdfName.Length() > 0) {
    double nexp(totalPdf->expectedEvents(RooArgSet(*(ws_.var(params_.var)))));
    totalPdf->plotOn(rframe, ProjWData(*data), Components(pdfName),
		     Normalization(nexp, RooAbsReal::Raw),
		     DrawOption("LF"), FillStyle(1001), VLines(),
		     FillColor(DibosonColor), //Name("h_"+ pdfName), 
		     LineColor(DibosonColor), 
		     NormRange("RangeForPlot"),
		     Range("RangeForPlot"));
    tmpCurve = rframe->getCurve();
    tmpCurve->SetName("h_" + pdfName);
    tmpCurve->SetTitle("WW/WZ");
    if (params_.doNewPhysics) {
      totalPdf->plotOn(rframe, ProjWData(*data), Components("NPPdf"),
		       Normalization(nexp, RooAbsReal::Raw),
		       //DrawOption("LF"), VLines(), FillStyle(1001),
		       //FillColor(kCyan+2), //Name("h_NP"),
		       LineColor(kCyan+2), 
		       NormRange("RangeForPlot"),
		       Range("RangeForPlot"));
      tmpCurve = rframe->getCurve();
      tmpCurve->SetName("h_NP");
      tmpCurve->SetTitle("Gaussian signal");
    }
  }
  RooHist * hresid = thePlot->residHist("theData", curveName, normalize);
  hresid->SetTitle("data");
  hresid->SetName("theData");
//   RooHist * bands = new RooHist(*hresid);
//   bands->SetName("band");
//   bands->SetTitle("error bands");
//   bands->SetFillStyle(1001);
//   rframe->addPlotable(bands, "e3");
  rframe->addPlotable(hresid, "p");
  
  TLegend * legend = RooWjjFitterUtils::legend4Plot(rframe);
  rframe->addObject(legend);

  if (!normalize) {
    rframe->SetMaximum(rframe->GetMaximum()*1.2);
    rframe->SetMinimum(rframe->GetMinimum()*1.1);
    rframe->GetYaxis()->SetTitle("Events / GeV");
  } else {
    rframe->SetMaximum(5.);
    rframe->SetMinimum(-5.);
    rframe->GetYaxis()->SetTitle("pull ( #sigma )");
  }

  if (params_.truncRange) {
    TLine * lowerLine = new TLine(params_.minTrunc,rframe->GetMinimum()*0.6,
				  params_.minTrunc,rframe->GetMaximum()*0.6);
    lowerLine->SetLineWidth(2);
    lowerLine->SetLineColor(kGray+2);
    lowerLine->SetLineStyle(9);
    TLine * upperLine = new TLine(params_.maxTrunc,rframe->GetMinimum()*0.6, 
				  params_.maxTrunc,rframe->GetMaximum()*0.6);
    upperLine->SetLineWidth(2);
    upperLine->SetLineColor(kGray+2);
    upperLine->SetLineStyle(9);
    rframe->addObject(lowerLine);
    rframe->addObject(upperLine);
  }  
  if ((params_.truncRange) && (params_.blind)) {
    TBox * blind = new TBox(params_.minTrunc,rframe->GetMinimum(),
			    params_.maxTrunc,rframe->GetMaximum());
    blind->SetFillColor(kBlack);
    blind->SetFillStyle(1001);
    rframe->addObject(blind);
  }

  return rframe;

}

void RooWjjMjjFitter::loadParameters(TString fname) {
  if (fname.Length() > 0) {
    std::cout << "loading parameters from file " << fname << "\n";
    RooArgSet obs(*(ws_.var(params_.var)));
    RooArgSet * params = ws_.pdf("totalPdf")->getParameters(obs);
    params->readFromFile(fname);
    if ( params_.useExternalMorphingPars ) {
      resetfSUfMU(params_.e_fSU, params_.e_fMU);
    }
      
    delete params;
  }
}

void RooWjjMjjFitter::resetYields() {
  ws_.var("nWjets")->setVal(initWjets_);
  ws_.var("nWjets")->setError(initWjets_*0.05);
  ws_.var("nDiboson")->setVal(initDiboson_);
  ws_.var("nDiboson")->setError(initDiboson_*0.034);
  ws_.var("nTTbar")->setVal(ttbarNorm_);
  ws_.var("nTTbar")->setError(ttbarNorm_*0.07);
  ws_.var("nSingleTop")->setVal(singleTopNorm_);
  ws_.var("nSingleTop")->setError(singleTopNorm_*0.05);
  ws_.var("nQCD")->setVal(QCDNorm_);
  ws_.var("nQCD")->setError(QCDError_);
  ws_.var("nZjets")->setVal(zjetsNorm_);
  ws_.var("nZjets")->setError(zjetsNorm_*0.043);
  if (params_.doNewPhysics) {
    ws_.var("nNP")->setVal( 0. );
    ws_.var("nNP")->setError(100.);
  }
}

////////////////////////////////////////////////////////////////////
////   Use For MC Dataset Toy Generation
////////////////////////////////////////////////////////////////////

void RooWjjMjjFitter::generateToyMCSet(RooAbsPdf *inputPdf, const char* outFileName, int NEvts, int seedInitializer)
/// Generates a ToyMC dataset (for the mjj distribution) from the inputPdf
{
  int seed;
  seed=3487+seedInitializer*3;
  RooRandom::randomGenerator()->SetSeed(seed);
  TFile *fMC = new TFile(outFileName, "RECREATE");

  RooRealVar * mass = ws_.var(params_.var);
  RooDataSet* toymc =  inputPdf->generate(*mass,NEvts);
  const TTree* tMC  = toymc->tree();
  fMC->cd();
  tMC->Write();
  fMC->Close();

}


void RooWjjMjjFitter::resetfSUfMU(double fSU, double fMU) {
  RooArgSet * params = ws_.pdf("totalPdf")->getParameters(ws_.data("data"));
  if ( fSU>0 ) {
    params->setRealValue("fSU",fSU);
    params->setRealValue("fSD",0.0);
  } else {
    params->setRealValue("fSU",0.0);
    params->setRealValue("fSD",-fSU);
  }
  if ( fMU>0 ) {
    params->setRealValue("fMU",fMU);
    params->setRealValue("fMD",0.0);
  } else {
    params->setRealValue("fMU",0.0);
    params->setRealValue("fMD",-fMU);
  }

  delete params;
}

////////////////////////////////////////////////////////////////////

TH1 * RooWjjMjjFitter::getWpJHistFromData(TString histName, double alpha,
					  double alphaDown, double alphaUp,
					  double xMin, double xMax, 
					  RooWjjMjjFitter & fitter2body,
					  RooWjjMjjFitter & shapesSBHi,
					  RooWjjMjjFitter & shapesSBLo,
					  TH1 * const alphaDownHist, 
					  TH1 * const alphaUpHist) {
  TString massCut(TString::Format("((%s > %f) && (%s < %f))", 
				  params_.var.Data(), xMin, params_.var.Data(),
				  xMax));
  TString cutsSBHi(TString::Format("(%s) && (%s)",
				   massCut.Data(), params_.SBHicut.Data()));
  TString cutsSBLo(TString::Format("(%s) && (%s)",
				   massCut.Data(), params_.SBLocut.Data()));

//   int tmpBins((xMax-xMin)/(params_.maxMass-params_.minMass)*params_.nbins 
// 	      + 0.5);

  TH1 * th1wpjHi = utils_.newEmptyHist(histName + "_Hi");
  TH1 * th1wpjLo = utils_.newEmptyHist(histName + "_Lo");

  TH1 * tmpHist;
  if (params_.includeMuons) {
    tmpHist = utils_.File2Hist(params_.DataDirectory + params_.muonData, 
			       histName + "_Hi_mu", false, 1, false, 1, 
			       cutsSBHi);
    th1wpjHi->Add(tmpHist);
    delete tmpHist;
    tmpHist = utils_.File2Hist(params_.DataDirectory + params_.muonData, 
			       histName + "_Lo_mu", false, 1, false, 1, 
			       cutsSBLo);
    th1wpjLo->Add(tmpHist);
    delete tmpHist;
  }
  if (params_.includeElectrons) {
    tmpHist = utils_.File2Hist(params_.DataDirectory + params_.electronData, 
			       histName + "_Hi_el", true, 1, false, 1, 
			       cutsSBHi);
    th1wpjHi->Add(tmpHist);
    delete tmpHist;
    tmpHist = utils_.File2Hist(params_.DataDirectory + params_.electronData, 
			       histName + "_Lo_el", true, 1, false, 1, 
			       cutsSBLo);
    th1wpjLo->Add(tmpHist);
    delete tmpHist;
  }

//   th1wpjHi->Print();
//   th1wpjHi->Draw();
//   gPad->WaitPrimitive();

  subtractHistogram(*th1wpjHi, HighSB, xMin, xMax, fitter2body, shapesSBHi);

//   th1wpjHi->Print();
//   th1wpjHi->Draw();
//   gPad->WaitPrimitive();

//   th1wpjLo->Print();
//   th1wpjLo->Draw();
//   gPad->WaitPrimitive();

  subtractHistogram(*th1wpjLo, LowSB, xMin, xMax, fitter2body, shapesSBLo);

//   th1wpjLo->Print();
//   th1wpjLo->Draw();
//   gPad->WaitPrimitive();

  double EventsHi = th1wpjHi->Integral();
  double EventsLo = th1wpjLo->Integral();
  TH1 * th1wpj = utils_.newEmptyHist(histName);

  th1wpjHi->Scale(1./th1wpjHi->Integral());
  th1wpjLo->Scale(1./th1wpjLo->Integral());

  th1wpjHi->Print();
  th1wpjLo->Print();

  th1wpj->Add(th1wpjLo, th1wpjHi, alpha, 1. - alpha);
  alphaDownHist->Add(th1wpjLo, th1wpjHi, alphaDown, 1. - alphaDown);
  alphaUpHist->Add(th1wpjLo, th1wpjHi, alphaUp, 1. - alphaUp);

  delete th1wpjLo;
  delete th1wpjHi;

//   th1wpjHi->Print();
//   th1wpjHi->Draw();
//   gPad->Update();
//   gPad->WaitPrimitive();

  std::cout << "WpJ statistics in SB (Lo: " << EventsLo
	    << " Hi: " << EventsHi << ") alpha: "  << alpha 
	    << " alphaDown: " << alphaDown << " alphaUp: " << alphaUp
	    << "\n";
  if (params_.smoothWpJ > 0)
    th1wpj->Smooth(params_.smoothWpJ);

//   th1wpjHi->Print();
//   th1wpjHi->Draw();
//   gPad->Update();
//   gPad->WaitPrimitive();

//   for (int bin = 1; bin <= th1wpjHi->GetNbinsX(); ++bin) {
//     std::cout << TString::Format("bin %i  %0.0f : %0.3f +/- %0.3f\n",
// 				 bin, th1wpjHi->GetBinCenter(bin),
// 				 th1wpjHi->GetBinContent(bin),
// 				 th1wpjHi->GetBinError(bin));
//     if (th1wpjHi->GetBinContent(bin) < 0.25) {
//       th1wpjHi->SetBinContent(bin, 0.);
//       th1wpjHi->SetBinError(bin, 1.);
//     }
//   }

  th1wpj->Scale(alpha*EventsLo+ (1-alpha)*EventsHi);
  alphaDownHist->Scale(alphaDown*EventsLo+ (1-alphaDown)*EventsHi);
  alphaUpHist->Scale(alphaUp*EventsLo+ (1-alphaUp)*EventsHi);
  th1wpj->Print();
  alphaDownHist->Print();
  alphaUpHist->Print();
//   th1wpjHi->Draw();
//   gPad->Update();
//   gPad->WaitPrimitive();

  return th1wpj;
}

void RooWjjMjjFitter::subtractHistogram(TH1& hist, SideBand sideBand,
					double m4min, double m4max, 
					RooWjjMjjFitter & fitter2body,
					RooWjjMjjFitter & shapesSB) {
  RooRealVar * mass = fitter2body.ws_.var(fitter2body.params_.var);
  RooRealVar * m4b = shapesSB.ws_.var(params_.var);
  double maxLimit = params_.maxSBLo, minLimit = params_.minSBLo;
  if (sideBand == HighSB) {
    maxLimit = params_.maxSBHi;
    minLimit = params_.minSBHi;
  }

  mass->setRange("sideband", minLimit, maxLimit);
  TString pdfName("qcdPdf");
  TString normName("nQCD");
  RooAbsReal * fullInt;
  RooAbsReal * SBInt;
  TH1 * tempHist;

  int nbins = hist.GetNbinsX(), ibin;
//   double xMin = hist.GetBinLowEdge(1);
//   double xMax = hist.GetBinLowEdge(nbins+1);
  double x;
  hist.Print();
  for (int comp = 0; comp < 5; ++comp) {
    switch (comp) {
    case 0:
      normName = "nDiboson";
      pdfName = "dibosonPdf";
      break;
    case 1:
      normName = "nTTbar";
      pdfName = "ttPdf";
      break;
    case 2:
      normName = "nSingleTop";
      pdfName = "stPdf";
      break;
    case 3:
      normName = "nQCD";
      pdfName = "qcdPdf";
      break;
    case 4:
      normName = "nZjets";
      pdfName = "ZpJPdf";
      break;
    }

    fullInt = fitter2body.ws_.pdf(pdfName)->createIntegral(*mass, *mass);
    SBInt = fitter2body.ws_.pdf(pdfName)->createIntegral(*mass, *mass, 
							 "sideband");

    std::cout << pdfName << " full integral: " << fullInt->getVal()
	      << " sideband integral: " << SBInt->getVal()
	      << " normalization: " << fitter2body.ws_.var(normName)->getVal()
	      << '\n';
    tempHist = 
      shapesSB.ws_.pdf(pdfName)->createHistogram(pdfName + "_tempHist", *m4b);
//     tempHist->Print();
    tempHist->Scale( fitter2body.ws_.var(normName)->getVal()/tempHist->Integral() * SBInt->getVal()/fullInt->getVal() );
    for (ibin = 1; ibin <= nbins; ++ibin) {
      x = tempHist->GetBinCenter(ibin);
      if ((x < m4min) || (x >= m4max)) {
	tempHist->SetBinContent(ibin, 0);
	tempHist->SetBinError(ibin, 0);
      }
    }
    tempHist->Print();
//     tempHist->Draw();
//     gPad->Update();
//     gPad->WaitPrimitive();
    if ( fitter2body.ws_.var(normName)->getVal() * 
	 SBInt->getVal()/fullInt->getVal() >= hist.Integral()*0.001)
      hist.Add(tempHist, -1.);

    delete tempHist;
    delete fullInt;
    delete SBInt;
  }
  // for (ibin = 1; ibin <= nbins; ++ibin) {
  //   if (hist.GetBinContent(ibin) <= 0.) 
  //     hist.SetBinContent(ibin, 1e-3);
  // }
}

void RooWjjMjjFitter::addHistograms(TH1& hist1, TH1& hist2, double weight) {
  int bin;
  double x;
  for( bin = 1; bin <= hist2.GetNbinsX(); ++bin) {
    x = hist2.GetBinCenter(bin);
    hist1.Fill(x, hist2.GetBinContent(bin)*weight);
  }
}
