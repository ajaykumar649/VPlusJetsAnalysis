{
float NoMVA[6] ={3.11887, 1.78854, 2.69813, 4.67396, 7.48473, 9.85048};
float MVA[6] = {2.48057, 1.60169, 2.40216, 4.18358, 6.58034, 9.39087};
float MVA2[6] = {2.55795, 1.42395, 2.11952, 3.84904, 5.79142, 8.37007};
float MVA3[6] = {3.71051, 1.3344, 2.01792, 3.22259, 5.33897, 7.49388};
float MVA4[6] = {5.44821, 1.39287, 2.13449, 3.54081, 5.66619, 7.67241};
float MVA5[6] = {5.0584, 1.46049, 2.16707, 3.504, 5.59603, 8.02826};

TH1F *h = new TH1F("h","WV#gamma Signal Strength",25,0,25);
TH1F *h1 = new TH1F("h1","limits 2",25,0,25);

h->SetBinContent(2,(NoMVA[1]+NoMVA[5])/2);
h->SetBinError(2,(NoMVA[1]-NoMVA[5])/2);
h->SetBinContent(4,(MVA[1]+NoMVA[5])/2);
h->SetBinError(4,(MVA[1]-NoMVA[5])/2);
h->SetBinContent(6,(MVA2[1]+NoMVA[5])/2);
h->SetBinError(6,(MVA2[1]-NoMVA[5])/2);
h->SetBinContent(8,(MVA3[1]+NoMVA[5])/2);
h->SetBinError(8,(MVA3[1]-NoMVA[5])/2);
h->SetBinContent(10,(MVA4[1]+NoMVA[5])/2);
h->SetBinError(10,(MVA4[1]-NoMVA[5])/2);
h->SetBinContent(12,(MVA5[1]+NoMVA[5])/2);
h->SetBinError(12,(MVA5[1]-NoMVA[5])/2);

h1->SetBinContent(2,(NoMVA[2]+NoMVA[4])/2);
h1->SetBinError(2,(NoMVA[2]-NoMVA[4])/2);
h1->SetBinContent(4,(MVA[2]+NoMVA[4])/2);
h1->SetBinError(4,(MVA[2]-NoMVA[4])/2);
h1->SetBinContent(6,(MVA2[2]+NoMVA[4])/2);
h1->SetBinError(6,(MVA2[2]-NoMVA[4])/2);
h1->SetBinContent(8,(MVA3[2]+NoMVA[4])/2);
h1->SetBinError(8,(MVA3[2]-NoMVA[4])/2);
h1->SetBinContent(10,(MVA4[2]+NoMVA[4])/2);
h1->SetBinError(10,(MVA4[2]-NoMVA[4])/2);
h1->SetBinContent(12,(MVA5[2]+NoMVA[4])/2);
h1->SetBinError(12,(MVA5[2]-NoMVA[4])/2);

TLine *l1 = new TLine(1,NoMVA[3] , 2., NoMVA[3]);
TLine *l2 = new TLine(1,NoMVA[0] , 2., NoMVA[0]);
l1->SetLineWidth(3);
l1->SetLineStyle(2);
l2->SetLineWidth(3);

TLine *l3 = new TLine(3,MVA[3] , 4., MVA[3]);
TLine *l4 = new TLine(3,MVA[0] , 4., MVA[0]);
TLine *l5 = new TLine(5,MVA2[3] , 6., MVA2[3]);
TLine *l6 = new TLine(5,MVA2[0] , 6., MVA2[0]);
TLine *l7 = new TLine(7,MVA3[3] , 8., MVA3[3]);
TLine *l8 = new TLine(7,MVA3[0] , 8., MVA3[0]);
TLine *l9 = new TLine(9,MVA4[3] , 10., MVA4[3]);
TLine *l10 = new TLine(9,MVA4[0] , 10., MVA4[0]);
TLine *l11 = new TLine(11,MVA5[3] , 12., MVA5[3]);
TLine *l12 = new TLine(11,MVA5[0] , 12., MVA5[0]);
l3->SetLineWidth(3);
l3->SetLineStyle(2);
l4->SetLineWidth(3);
l5->SetLineWidth(3);
l5->SetLineStyle(2);
l6->SetLineWidth(3);
l7->SetLineWidth(3);
l7->SetLineStyle(2);
l8->SetLineWidth(3);
l9->SetLineWidth(3);
l9->SetLineStyle(2);
l10->SetLineWidth(3);
l11->SetLineWidth(3);
l11->SetLineStyle(2);
l12->SetLineWidth(3);

TLine *l0 = new TLine(0,1. , 12., 1.);
l0->SetLineWidth(2);


 h->GetXaxis()->SetBinLabel(2,"NoMVA");
 h->GetXaxis()->SetBinLabel(4,"MVA 0.0");
 h->GetXaxis()->SetBinLabel(6,"MVA 0.1");
 h->GetXaxis()->SetBinLabel(8,"MVA 0.2");
 h->GetXaxis()->SetBinLabel(10,"MVA 0.21");
 h->GetXaxis()->SetBinLabel(12,"MVA 0.225");
 h->GetYaxis()->SetNdivisions(520);
 h->GetXaxis()->SetLabelSize(0.07);
 h->GetYaxis()->SetLabelSize(0.06);

gStyle->SetOptStat(0);
h->SetFillColor(kYellow);
h1->SetFillColor(kGreen);
h->Draw("e2");
h1->Draw("e2same");
l1->Draw("same");
l2->Draw("same");
l3->Draw("same");
l4->Draw("same");
l5->Draw("same");
l6->Draw("same");
l7->Draw("same");
l8->Draw("same");
l9->Draw("same");
l10->Draw("same");
l11->Draw("same");
l12->Draw("same");
l0->Draw("same");

    TLegend * Leg = new TLegend( 0.53, 0.6, 0.95, 0.9);
    Leg->SetFillColor(0);
    Leg->SetFillStyle(1);
    Leg->SetTextSize(0.04);
    Leg->AddEntry(l2,  "95 % C.L. Observed Limit",  "l");
    Leg->AddEntry(l1,  "95 % C.L. Expected Limit",  "l");
    Leg->AddEntry(h1,  "#pm 1#sigma Expected Limit",  "f");
    Leg->AddEntry(h,  "#pm 2#sigma Expected Limit",  "f");
    Leg->Draw();
    c1->SetGridy();
    c1->Print("WVAsignalstrength.png");
}
