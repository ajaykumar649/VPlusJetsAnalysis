//root -b -q -l upperLimit.C+
#include <iostream>

#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TText.h"
#include "TLatex.h"
#include "TAxis.h"
#include "TLine.h"
#include "TH1F.h"
#include "TString.h"

#include "tdrstyle.C"

#include "wwgamaqgcinputs.h"

//#define LOGY

//#define ADD7TEV
#undef ADD7TEV

#define YMAX 5.0

////CMS Preliminary label and lumi -- upper left corner
void cmsLumi(bool prelim)
{
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);
  latex.SetTextFont(42);

#ifdef ADD7TEV
  float lumiel=intlumipbinv_el+5020;
  float lumimu=intlumipbinv_mu+5020;
#else
  float lumiel=intlumipbinv_el;
  float lumimu=intlumipbinv_mu;
#endif

  latex.SetTextAlign(31); // align right

#ifdef ADD7TEV
  latex.DrawLatex(0.95,0.96,"#sqrt{s} = 7TeV/8TeV");
#else
  latex.DrawLatex(0.90,0.96,Form("#sqrt{s} = %d TeV",beamcomenergytev));
#endif

  latex.SetTextAlign(11); // align left

  if (lumiel==lumimu)
    latex.DrawLatex(0.5,0.96,Form("#scale[0.5]{#int} #font[12]{L} dt = %.1f fb^{-1}", lumiel/1000.));
  else
    latex.DrawLatex(0.4,0.96,Form("#scale[0.5]{#int} #font[12]{L} dt = %.1f fb^{-1}(#mu)/%.1f fb^{-1}(#it{e})",
				  (lumimu)/1000.,(lumiel)/1000.));

  //latex.DrawLatex(0.4,0.96,Form("#scale[0.5]{#int} #font[12]{L} dt = %.1f fb^{-1}(#it{e})",LUMINOSITY));
  //latex.DrawLatex(0.45,0.96,Form("#scale[0.5]{#int} #font[12]{L} dt = %.1f fb^{-1} (scaled)", LUMINOSITY));

  latex.SetTextAlign(11); // align left
  latex.DrawLatex(0.18,0.96,prelim ? "CMS preliminary" : "CMS");
}

void plotLimit(TString limitFile = "limit-cfginfo.tab",
	       bool plotObs = true,
	       bool plotPrelim=true)
{
  double aXw;
  double paXw[10],pobs[10],pexp[10],psig1hi[10],psig1lo[10],psig2hi[10],psig2lo[10];
  double maXw[10],mobs[10],mexp[10],msig1hi[10],msig1lo[10],msig2hi[10],msig2lo[10];
  char line[256];

  FILE *fp=fopen(limitFile.Data(),"r");
  if (!fp) {
    cerr << limitFile << " doesn't exist." << endl;
    exit(-1);
  }
  int npts=0;
  int ip,im;
  for (ip=im=0; !feof(fp) && fgets(line,256,fp); ) {
    if (line[0]=='#') continue;
    int nread = sscanf(line,"%lf",&aXw);
    if (aXw<0) {
      nread = sscanf(line,"%lf %lf %lf %lf %lf %lf %lf",
		     &maXw[im],&mobs[im],&msig2lo[im],&msig1lo[im],&mexp[im],&msig1hi[im],&msig2hi[im]);
      if (nread == 0) continue;
      if (nread == 7) {
	msig1hi[im] -= mexp[im];
	msig1lo[im]  = mexp[im]-msig1lo[im];
	msig2hi[im] -= mexp[im];
	msig2lo[im]  = mexp[im]-msig2lo[im];
	im++;
      }
    } else {
      nread = sscanf(line,"%lf %lf %lf %lf %lf %lf %lf",
		     &paXw[ip],&pobs[ip],&psig2lo[ip],&psig1lo[ip],&pexp[ip],&psig1hi[ip],&psig2hi[ip]);
      if (nread == 0) continue;
      if (nread == 7) {
	psig1hi[ip] -= pexp[ip];
	psig1lo[ip]  = pexp[ip]-psig1lo[ip];
	psig2hi[ip] -= pexp[ip];
	psig2lo[ip]  = pexp[ip]-psig2lo[ip];
	ip++;
      }
    }
    npts=ip+im;
  }
  fclose(fp);

  cout << "Read " << npts << " points." << endl;

  TGraph *mobslim=new TGraph(im,maXw,mobs);
  TGraph *pobslim=new TGraph(ip,paXw,pobs);
  TGraph *mexplim=new TGraph(im,maXw,mexp);
  TGraph *pexplim=new TGraph(ip,paXw,pexp);
  TGraphAsymmErrors *mexp1sig=new TGraphAsymmErrors(im,maXw,mexp,0,0,msig1lo,msig1hi);
  TGraphAsymmErrors *pexp1sig=new TGraphAsymmErrors(ip,paXw,pexp,0,0,psig1lo,psig1hi);
  TGraphAsymmErrors *mexp2sig=new TGraphAsymmErrors(im,maXw,mexp,0,0,msig2lo,msig2hi);
  TGraphAsymmErrors *pexp2sig=new TGraphAsymmErrors(ip,paXw,pexp,0,0,psig2lo,psig2hi);

  setTDRStyle();

  gStyle->SetLegendBorderSize(0);

  // Style for lines
  pexplim->SetLineWidth(3);
  pexplim->SetLineStyle(2);
  mexplim->SetLineWidth(3);
  mexplim->SetLineStyle(2);
  pobslim->SetLineWidth(3);
  pobslim->SetLineColor(1);
  pobslim->SetLineStyle(1);
  mobslim->SetLineWidth(3);
  mobslim->SetLineColor(1);
  mobslim->SetLineStyle(1);
  pexp1sig->SetFillColor(kGreen); // kBlue - 7);
  mexp1sig->SetFillColor(kGreen); // kBlue - 7);
  pexp2sig->SetFillColor(kYellow);
  mexp2sig->SetFillColor(kYellow);

  TMultiGraph* mg = new TMultiGraph();
  mg->SetName("");
  if (limitFile.Contains("a0w"))
    mg->SetTitle(";a0w;#sigma_{excluded} / #sigma_{SM}");
  else if (limitFile.Contains("aCw"))
    mg->SetTitle(";aCw;#sigma_{excluded} / #sigma_{SM}");
  else if (limitFile.Contains("lt0"))
    mg->SetTitle(";LT0;#sigma_{excluded} / #sigma_{SM}");

  mg->Add(pexp2sig, "E3");
  mg->Add(mexp2sig, "E3");
  mg->Add(pexp1sig, "E3");
  mg->Add(mexp1sig, "E3");
  mg->Add(pexplim, "L");
  mg->Add(mexplim, "L");
  if (plotObs) {
    mg->Add(pobslim, "L");
    mg->Add(mobslim, "L");
  }

  TCanvas *c1 = new TCanvas("c1","c1",800,600);

  mg->Draw("AH");

#ifdef LOGY
  mg->GetYaxis()->SetRangeUser(5e-2,40) ;
#else
  mg->GetYaxis()->SetRangeUser(0,YMAX) ;
#endif

  //mg->Draw("A");

  TLine l;
  l.SetLineWidth(2);
  l.SetLineColor(2);
  l.DrawLine(mg->GetXaxis()->GetXmin(),1.0,mg->GetXaxis()->GetXmax(),1.0);

  gPad->SetRightMargin(0.1);

  gPad->SetGridy();

#ifdef LOGY
  gPad->SetLogy();
#endif

  mg->GetHistogram()->DrawCopy("sameaxis");
  mg->GetHistogram()->DrawCopy("sameaxig");

  TLegend *leg = new TLegend(0.38, 0.77, 0.75, 0.94, NULL, "brNDC");
  leg->SetTextSize(0.04);
  leg->SetTextFont(42);
  leg->SetFillColor(0);
  if (plotObs)
    leg->AddEntry(pobslim, "95% C.L. Observed Limit", "L");
  leg->AddEntry(pexplim, "95% C.L. Expected Limit", "L");
  leg->AddEntry(pexp1sig, "#pm1#sigma Expected Limit", "F");
  leg->AddEntry(pexp2sig, "#pm2#sigma Expected Limit", "F");
  leg->Draw();

  cmsLumi(plotPrelim);

  gPad->Update();

  TString output1=limitFile, output2=limitFile;

  output1.Replace(limitFile.Length()-4,4, plotObs ? ".png" : "_exponly.png");
  output2.Replace(limitFile.Length()-4,4, plotObs ? ".eps" : "_exponly.eps");

  gPad->SaveAs(output1.Data());
  gPad->SaveAs(output2.Data());
}
