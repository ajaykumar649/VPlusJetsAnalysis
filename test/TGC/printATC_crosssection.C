#include <iostream>
#include <iomanip>

using namespace std;

void printATC_crosssection() {

  char temp[100];
  float xsection = 0.0, error = 0.0;
  float xsection2 = 0.0, error2 = 0.0;
  float smxsection = 0.0, smerror = 0.0;
  GetCrossSection("SM", smxsection, smerror);

  for (float i= -0.4; i<0.41; i += 0.04) {
    for (float j= 0.6; j>-0.1; j -= 0.2) {
      sprintf(temp, "LambdaZ_%.1f_dKgamma_%.1f.root", i, j);
      GetCrossSection(string(temp), xsection, error);    
      sprintf(temp, "LambdaZ_%.1f_dKgamma_%.1f.root", i, -j);
      GetCrossSection(string(temp), xsection2, error2);  
  
      cout << setiosflags(ios::fixed) << setprecision(2) << i << " & " << j << " & " << setiosflags(ios::fixed) << setprecision(4) << xsection/smxsection  <<  " $\\pm$ " << setiosflags(ios::fixed) << setprecision(4) << 1.442*error/smxsection << " & " << 
	setiosflags(ios::fixed) << setprecision(2) << i << " & " << -j << " & " << setiosflags(ios::fixed) << setprecision(4) << xsection2/smxsection  <<  " $\\pm$ " << setiosflags(ios::fixed) << setprecision(4) << 1.442*error2/smxsection << " \\\ " << endl;
    }
  }

}


//////////////////////// Get the right cross section for each sample ////////////
void GetCrossSection(string paramName, float& xsec, float& err) {

  if(paramName.compare("SM")==0) { xsec =       871.321; err =     0.933;}
  if(paramName.compare("LambdaZ_-0.6_dKgamma_-0.6.root")==0) { xsec =      2009.016;     err = 1.278;}
  if(paramName.compare("LambdaZ_-0.6_dKgamma_-0.4.root")==0) { xsec =      1960.101;     err = 1.293;}
  if(paramName.compare("LambdaZ_-0.6_dKgamma_-0.2.root")==0) { xsec =      1928.489;     err = 1.274;}
  if(paramName.compare("LambdaZ_-0.6_dKgamma_0.0.root")==0) { xsec =      1915.580;     err = 1.288;}
  if(paramName.compare("LambdaZ_-0.6_dKgamma_0.2.root")==0) { xsec =      1920.435;     err = 1.327;}
  if(paramName.compare("LambdaZ_-0.6_dKgamma_0.4.root")==0) { xsec =      1943.721;     err = 1.281;}
  if(paramName.compare("LambdaZ_-0.6_dKgamma_0.6.root")==0) { xsec =      1986.124;     err = 1.290;}
  ////////////////////
  if(paramName.compare("LambdaZ_-0.4_dKgamma_-0.6.root")==0) { xsec =      1412.035;     err = 0.929;}
  if(paramName.compare("LambdaZ_-0.4_dKgamma_-0.4.root")==0) { xsec =      1362.865;     err = 1.000;}
  if(paramName.compare("LambdaZ_-0.4_dKgamma_-0.2.root")==0) { xsec =      1330.305;     err = 0.959;}
  if(paramName.compare("LambdaZ_-0.4_dKgamma_0.0.root")==0) { xsec =      1317.236;     err = 0.889;}
  if(paramName.compare("LambdaZ_-0.4_dKgamma_0.2.root")==0) { xsec =      1322.865;     err = 0.889;}
  if(paramName.compare("LambdaZ_-0.4_dKgamma_0.4.root")==0) { xsec =      1345.060;     err = 0.893;}
  if(paramName.compare("LambdaZ_-0.4_dKgamma_0.6.root")==0) { xsec =      1386.598;     err = 0.936;}
  ///////////////////////
  if(paramName.compare("LambdaZ_-0.36_dKgamma_-0.6.root")==0) { xsec =      1322.075;     err =     0.887;}
  if(paramName.compare("LambdaZ_-0.36_dKgamma_-0.4.root")==0) { xsec =      1273.228;     err =     0.853;}
  if(paramName.compare("LambdaZ_-0.36_dKgamma_-0.2.root")==0) { xsec =      1241.664;     err =     0.863;}
  if(paramName.compare("LambdaZ_-0.36_dKgamma_0.0.root")==0) { xsec =      1227.865;     err =     0.854;}
  if(paramName.compare("LambdaZ_-0.36_dKgamma_0.2.root")==0) { xsec =      1233.102;     err =     0.855;}
  if(paramName.compare("LambdaZ_-0.36_dKgamma_0.4.root")==0) { xsec =      1255.881;     err =     0.877;}
  if(paramName.compare("LambdaZ_-0.36_dKgamma_0.6.root")==0) { xsec =      1296.479;     err =     0.870;}
  if(paramName.compare("LambdaZ_-0.32_dKgamma_-0.6.root")==0) { xsec =      1243.804;     err =     0.795;}
  if(paramName.compare("LambdaZ_-0.32_dKgamma_-0.4.root")==0) { xsec =      1193.668;     err =     0.842;}
  if(paramName.compare("LambdaZ_-0.32_dKgamma_-0.2.root")==0) { xsec =      1162.341;     err =     0.795;}
  if(paramName.compare("LambdaZ_-0.32_dKgamma_0.0.root")==0) { xsec =      1148.747;     err =     0.793;}
  if(paramName.compare("LambdaZ_-0.32_dKgamma_0.2.root")==0) { xsec =      1153.152;     err =     0.811;}
  if(paramName.compare("LambdaZ_-0.32_dKgamma_0.4.root")==0) { xsec =      1176.140;     err =     0.866;}
  if(paramName.compare("LambdaZ_-0.32_dKgamma_0.6.root")==0) { xsec =      1218.219;     err =     0.801;}
  if(paramName.compare("LambdaZ_-0.28_dKgamma_-0.6.root")==0) { xsec =      1174.339;     err =     0.770;}
  if(paramName.compare("LambdaZ_-0.28_dKgamma_-0.4.root")==0) { xsec =      1124.658;     err =     0.762;}
  if(paramName.compare("LambdaZ_-0.28_dKgamma_-0.2.root")==0) { xsec =      1092.637;     err =     0.754;}
  if(paramName.compare("LambdaZ_-0.28_dKgamma_0.0.root")==0) { xsec =      1079.080;     err =     0.804;}
  if(paramName.compare("LambdaZ_-0.28_dKgamma_0.2.root")==0) { xsec =      1083.809;     err =     0.779;}
  if(paramName.compare("LambdaZ_-0.28_dKgamma_0.4.root")==0) { xsec =      1106.704;     err =     0.811;}
  if(paramName.compare("LambdaZ_-0.28_dKgamma_0.6.root")==0) { xsec =      1147.925;     err =     0.784;}
  if(paramName.compare("LambdaZ_-0.24_dKgamma_-0.6.root")==0) { xsec =      1115.123;     err =     0.804;}
  if(paramName.compare("LambdaZ_-0.24_dKgamma_-0.4.root")==0) { xsec =      1065.394;     err =     0.730;}
  if(paramName.compare("LambdaZ_-0.24_dKgamma_-0.2.root")==0) { xsec =      1033.485;     err =     0.705;}
  if(paramName.compare("LambdaZ_-0.24_dKgamma_0.0.root")==0) { xsec =      1019.781;     err =     0.690;}
  if(paramName.compare("LambdaZ_-0.24_dKgamma_0.2.root")==0) { xsec =      1024.549;     err =     0.709;}
  if(paramName.compare("LambdaZ_-0.24_dKgamma_0.4.root")==0) { xsec =      1047.110;     err =     0.772;}
  if(paramName.compare("LambdaZ_-0.24_dKgamma_0.6.root")==0) { xsec =      1088.493;     err =     0.758;}
  ///////////////////////
  if(paramName.compare("LambdaZ_-0.2_dKgamma_-0.6.root")==0) { xsec =      1066.104;     err = 0.699;}
  if(paramName.compare("LambdaZ_-0.2_dKgamma_-0.4.root")==0) { xsec =      1016.150;     err = 0.716;}
  if(paramName.compare("LambdaZ_-0.2_dKgamma_-0.2.root")==0) { xsec =       983.940;     err = 0.674;}
  if(paramName.compare("LambdaZ_-0.2_dKgamma_0.0.root")==0) { xsec =       970.492;     err = 0.706;}
  if(paramName.compare("LambdaZ_-0.2_dKgamma_0.2.root")==0) { xsec =       975.325;     err = 0.717;}
  if(paramName.compare("LambdaZ_-0.2_dKgamma_0.4.root")==0) { xsec =       997.318;     err = 0.717;}
  if(paramName.compare("LambdaZ_-0.2_dKgamma_0.6.root")==0) { xsec =      1039.045;     err = 0.704;}
  ///////////////////////
  if(paramName.compare("LambdaZ_-0.16_dKgamma_-0.6.root")==0) { xsec =      1025.975;     err =     0.697;}
  if(paramName.compare("LambdaZ_-0.16_dKgamma_-0.4.root")==0) { xsec =       976.590;     err =     0.661;}
  if(paramName.compare("LambdaZ_-0.16_dKgamma_-0.2.root")==0) { xsec =       945.054;     err =     0.811;}
  if(paramName.compare("LambdaZ_-0.16_dKgamma_0.0.root")==0) { xsec =       930.364;     err =     0.849;}
  if(paramName.compare("LambdaZ_-0.16_dKgamma_0.2.root")==0) { xsec =       935.780;     err =     0.864;}
  if(paramName.compare("LambdaZ_-0.16_dKgamma_0.4.root")==0) { xsec =       957.699;     err =     0.679;}
  if(paramName.compare("LambdaZ_-0.16_dKgamma_0.6.root")==0) { xsec =       998.528;     err =     0.683;}
  if(paramName.compare("LambdaZ_-0.12_dKgamma_-0.6.root")==0) { xsec =       996.331;     err =     0.748;}
  if(paramName.compare("LambdaZ_-0.12_dKgamma_-0.4.root")==0) { xsec =       947.651;     err =     0.785;}
  if(paramName.compare("LambdaZ_-0.12_dKgamma_-0.2.root")==0) { xsec =       914.681;     err =     0.808;}
  if(paramName.compare("LambdaZ_-0.12_dKgamma_0.0.root")==0) { xsec =       900.694;     err =     0.966;}
  if(paramName.compare("LambdaZ_-0.12_dKgamma_0.2.root")==0) { xsec =       905.221;     err =     1.112;}
  if(paramName.compare("LambdaZ_-0.12_dKgamma_0.4.root")==0) { xsec =       928.604;     err =     0.876;}
  if(paramName.compare("LambdaZ_-0.12_dKgamma_0.6.root")==0) { xsec =       969.159;     err =     0.715;}
  if(paramName.compare("LambdaZ_-0.08_dKgamma_-0.6.root")==0) { xsec =       977.633;     err =     0.648;}
  if(paramName.compare("LambdaZ_-0.08_dKgamma_-0.4.root")==0) { xsec =       928.642;     err =     0.773;}
  if(paramName.compare("LambdaZ_-0.08_dKgamma_-0.2.root")==0) { xsec =       894.158;     err =     1.214;}
  if(paramName.compare("LambdaZ_-0.08_dKgamma_0.0.root")==0) { xsec =       880.042;     err =     0.997;}
  if(paramName.compare("LambdaZ_-0.08_dKgamma_0.2.root")==0) { xsec =       885.037;     err =     1.127;}
  if(paramName.compare("LambdaZ_-0.08_dKgamma_0.4.root")==0) { xsec =       908.776;     err =     0.953;}
  if(paramName.compare("LambdaZ_-0.08_dKgamma_0.6.root")==0) { xsec =       949.328;     err =     0.853;}
  if(paramName.compare("LambdaZ_-0.04_dKgamma_-0.6.root")==0) { xsec =       968.604;     err =     0.693;}
  if(paramName.compare("LambdaZ_-0.04_dKgamma_-0.4.root")==0) { xsec =       917.399;     err =     0.922;}
  if(paramName.compare("LambdaZ_-0.04_dKgamma_-0.2.root")==0) { xsec =       886.634;     err =     0.784;}
  if(paramName.compare("LambdaZ_-0.04_dKgamma_0.0.root")==0) { xsec =       871.023;     err =     1.004;}
  if(paramName.compare("LambdaZ_-0.04_dKgamma_0.2.root")==0) { xsec =       875.293;     err =     1.163;}
  if(paramName.compare("LambdaZ_-0.04_dKgamma_0.4.root")==0) { xsec =       897.010;     err =     1.042;}
  if(paramName.compare("LambdaZ_-0.04_dKgamma_0.6.root")==0) { xsec =       940.234;     err =     0.921;}
  ///////////////////////
  if(paramName.compare("LambdaZ_0.0_dKgamma_-0.6.root")==0) { xsec =       968.721;     err = 0.833;}
  if(paramName.compare("LambdaZ_0.0_dKgamma_-0.4.root")==0) { xsec =       917.636;     err = 1.035;}
  if(paramName.compare("LambdaZ_0.0_dKgamma_-0.2.root")==0) { xsec =       886.128;     err = 0.992;}
  if(paramName.compare("LambdaZ_0.0_dKgamma_0.0.root")==0) { xsec =       871.321;     err = 0.933;}
  if(paramName.compare("LambdaZ_0.0_dKgamma_0.2.root")==0) { xsec =       876.816;     err = 0.859;}
  if(paramName.compare("LambdaZ_0.0_dKgamma_0.4.root")==0) { xsec =       898.762;     err = 1.196;}
  if(paramName.compare("LambdaZ_0.0_dKgamma_0.6.root")==0) { xsec =       939.693;     err = 0.796;}
  ///////////////////////
  if(paramName.compare("LambdaZ_0.04_dKgamma_-0.6.root")==0) { xsec =       978.779;     err =     0.836;}
  if(paramName.compare("LambdaZ_0.04_dKgamma_-0.4.root")==0) { xsec =       928.028;     err =     0.934;}
  if(paramName.compare("LambdaZ_0.04_dKgamma_-0.2.root")==0) { xsec =       895.007;     err =     1.022;}
  if(paramName.compare("LambdaZ_0.04_dKgamma_0.0.root")==0) { xsec =       882.263;     err =     1.253;}
  if(paramName.compare("LambdaZ_0.04_dKgamma_0.2.root")==0) { xsec =       885.911;     err =     0.850;}
  if(paramName.compare("LambdaZ_0.04_dKgamma_0.4.root")==0) { xsec =       908.897;     err =     1.201;}
  if(paramName.compare("LambdaZ_0.04_dKgamma_0.6.root")==0) { xsec =       950.346;     err =     0.799;}
  if(paramName.compare("LambdaZ_0.08_dKgamma_-0.6.root")==0) { xsec =       999.897;     err =     0.710;}
  if(paramName.compare("LambdaZ_0.08_dKgamma_-0.4.root")==0) { xsec =       949.121;     err =     0.885;}
  if(paramName.compare("LambdaZ_0.08_dKgamma_-0.2.root")==0) { xsec =       915.892;     err =     1.143;}
  if(paramName.compare("LambdaZ_0.08_dKgamma_0.0.root")==0) { xsec =       902.536;     err =     1.089;}
  if(paramName.compare("LambdaZ_0.08_dKgamma_0.2.root")==0) { xsec =       906.592;     err =     0.840;}
  if(paramName.compare("LambdaZ_0.08_dKgamma_0.4.root")==0) { xsec =       928.519;     err =     1.018;}
  if(paramName.compare("LambdaZ_0.08_dKgamma_0.6.root")==0) { xsec =       969.486;     err =     0.841;}
  if(paramName.compare("LambdaZ_0.12_dKgamma_-0.6.root")==0) { xsec =      1030.357;     err =     0.688;}
  if(paramName.compare("LambdaZ_0.12_dKgamma_-0.4.root")==0) { xsec =       980.025;     err =     0.849;}
  if(paramName.compare("LambdaZ_0.12_dKgamma_-0.2.root")==0) { xsec =       946.810;     err =     1.065;}
  if(paramName.compare("LambdaZ_0.12_dKgamma_0.0.root")==0) { xsec =       932.162;     err =     0.996;}
  if(paramName.compare("LambdaZ_0.12_dKgamma_0.2.root")==0) { xsec =       937.948;     err =     0.884;}
  if(paramName.compare("LambdaZ_0.12_dKgamma_0.4.root")==0) { xsec =       959.057;     err =     0.856;}
  if(paramName.compare("LambdaZ_0.12_dKgamma_0.6.root")==0) { xsec =       999.778;     err =     0.676;}
  if(paramName.compare("LambdaZ_0.16_dKgamma_-0.6.root")==0) { xsec =      1070.731;     err =     0.704;}
  if(paramName.compare("LambdaZ_0.16_dKgamma_-0.4.root")==0) { xsec =      1020.139;     err =     0.716;}
  if(paramName.compare("LambdaZ_0.16_dKgamma_-0.2.root")==0) { xsec =       987.434;     err =     0.659;}
  if(paramName.compare("LambdaZ_0.16_dKgamma_0.0.root")==0) { xsec =       973.579;     err =     0.805;}
  if(paramName.compare("LambdaZ_0.16_dKgamma_0.2.root")==0) { xsec =       977.249;     err =     0.715;}
  if(paramName.compare("LambdaZ_0.16_dKgamma_0.4.root")==0) { xsec =       998.903;     err =     0.680;}
  if(paramName.compare("LambdaZ_0.16_dKgamma_0.6.root")==0) { xsec =      1039.462;     err =     0.718;}
  ///////////////////////
  if(paramName.compare("LambdaZ_0.2_dKgamma_-0.6.root")==0) { xsec =      1120.865;     err = 0.761;}
  if(paramName.compare("LambdaZ_0.2_dKgamma_-0.4.root")==0) { xsec =      1069.652;     err = 0.750;}
  if(paramName.compare("LambdaZ_0.2_dKgamma_-0.2.root")==0) { xsec =      1037.285;     err = 0.723;}
  if(paramName.compare("LambdaZ_0.2_dKgamma_0.0.root")==0) { xsec =      1023.622;     err = 0.759;}
  if(paramName.compare("LambdaZ_0.2_dKgamma_0.2.root")==0) { xsec =      1026.999;     err = 0.751;}
  if(paramName.compare("LambdaZ_0.2_dKgamma_0.4.root")==0) { xsec =      1048.993;     err = 0.703;}
  if(paramName.compare("LambdaZ_0.2_dKgamma_0.6.root")==0) { xsec =      1088.660;     err = 0.788;}
  ///////////////////////
  if(paramName.compare("LambdaZ_0.24_dKgamma_-0.6.root")==0) { xsec =      1180.713;     err =     0.790;}
  if(paramName.compare("LambdaZ_0.24_dKgamma_-0.4.root")==0) { xsec =      1130.458;     err =     0.773;}
  if(paramName.compare("LambdaZ_0.24_dKgamma_-0.2.root")==0) { xsec =      1097.027;     err =     0.714;}
  if(paramName.compare("LambdaZ_0.24_dKgamma_0.0.root")==0) { xsec =      1083.328;     err =     0.763;}
  if(paramName.compare("LambdaZ_0.24_dKgamma_0.2.root")==0) { xsec =      1086.900;     err =     0.750;}
  if(paramName.compare("LambdaZ_0.24_dKgamma_0.4.root")==0) { xsec =      1109.013;     err =     0.755;}
  if(paramName.compare("LambdaZ_0.24_dKgamma_0.6.root")==0) { xsec =      1148.299;     err =     0.755;}
  if(paramName.compare("LambdaZ_0.28_dKgamma_-0.6.root")==0) { xsec =      1250.479;     err =     0.817;}
  if(paramName.compare("LambdaZ_0.28_dKgamma_-0.4.root")==0) { xsec =      1201.022;     err =     0.808;}
  if(paramName.compare("LambdaZ_0.28_dKgamma_-0.2.root")==0) { xsec =      1167.289;     err =     0.843;}
  if(paramName.compare("LambdaZ_0.28_dKgamma_0.0.root")==0) { xsec =      1153.416;     err =     0.779;}
  if(paramName.compare("LambdaZ_0.28_dKgamma_0.2.root")==0) { xsec =      1156.832;     err =     0.768;}
  if(paramName.compare("LambdaZ_0.28_dKgamma_0.4.root")==0) { xsec =      1178.955;     err =     0.831;}
  if(paramName.compare("LambdaZ_0.28_dKgamma_0.6.root")==0) { xsec =      1219.681;     err =     0.797;}
  if(paramName.compare("LambdaZ_0.32_dKgamma_-0.6.root")==0) { xsec =      1331.319;     err =     0.843;}
  if(paramName.compare("LambdaZ_0.32_dKgamma_-0.4.root")==0) { xsec =      1280.899;     err =     0.883;}
  if(paramName.compare("LambdaZ_0.32_dKgamma_-0.2.root")==0) { xsec =      1247.598;     err =     0.834;}
  if(paramName.compare("LambdaZ_0.32_dKgamma_0.0.root")==0) { xsec =      1232.666;     err =     0.865;}
  if(paramName.compare("LambdaZ_0.32_dKgamma_0.2.root")==0) { xsec =      1236.907;     err =     0.857;}
  if(paramName.compare("LambdaZ_0.32_dKgamma_0.4.root")==0) { xsec =      1258.628;     err =     0.851;}
  if(paramName.compare("LambdaZ_0.32_dKgamma_0.6.root")==0) { xsec =      1298.336;     err =     0.833;}
  if(paramName.compare("LambdaZ_0.36_dKgamma_-0.6.root")==0) { xsec =      1421.945;     err =     0.920;}
  if(paramName.compare("LambdaZ_0.36_dKgamma_-0.4.root")==0) { xsec =      1370.137;     err =     0.859;}
  if(paramName.compare("LambdaZ_0.36_dKgamma_-0.2.root")==0) { xsec =      1337.348;     err =     0.911;}
  if(paramName.compare("LambdaZ_0.36_dKgamma_0.0.root")==0) { xsec =      1322.509;     err =     0.915;}
  if(paramName.compare("LambdaZ_0.36_dKgamma_0.2.root")==0) { xsec =      1326.793;     err =     0.864;}
  if(paramName.compare("LambdaZ_0.36_dKgamma_0.4.root")==0) { xsec =      1348.830;     err =     0.907;}
  if(paramName.compare("LambdaZ_0.36_dKgamma_0.6.root")==0) { xsec =      1387.351;     err =     0.955;}
  ///////////////////////
  if(paramName.compare("LambdaZ_0.4_dKgamma_-0.6.root")==0) { xsec =      1521.679;     err = 0.999;}
  if(paramName.compare("LambdaZ_0.4_dKgamma_-0.4.root")==0) { xsec =      1470.608;     err = 0.981;}
  if(paramName.compare("LambdaZ_0.4_dKgamma_-0.2.root")==0) { xsec =      1437.806;     err = 0.931;}
  if(paramName.compare("LambdaZ_0.4_dKgamma_0.0.root")==0) { xsec =      1422.839;     err = 0.997;}
  if(paramName.compare("LambdaZ_0.4_dKgamma_0.2.root")==0) { xsec =      1427.382;     err = 0.973;}
  if(paramName.compare("LambdaZ_0.4_dKgamma_0.4.root")==0) { xsec =      1447.684;     err = 1.080;}
  if(paramName.compare("LambdaZ_0.4_dKgamma_0.6.root")==0) { xsec =      1487.612;     err = 0.938;}
  if(paramName.compare("LambdaZ_0.6_dKgamma_-0.6.root")==0) { xsec =      2172.604;     err = 1.419;}
  if(paramName.compare("LambdaZ_0.6_dKgamma_-0.4.root")==0) { xsec =      2122.149;     err = 1.356;}
  if(paramName.compare("LambdaZ_0.6_dKgamma_-0.2.root")==0) { xsec =      2088.321;     err = 1.352;}
  if(paramName.compare("LambdaZ_0.6_dKgamma_0.0.root")==0) { xsec =      2072.907;     err = 1.387;}
  if(paramName.compare("LambdaZ_0.6_dKgamma_0.2.root")==0) { xsec =      2074.902;     err = 1.341;}
  if(paramName.compare("LambdaZ_0.6_dKgamma_0.4.root")==0) { xsec =      2097.831;     err = 1.328;}
  if(paramName.compare("LambdaZ_0.6_dKgamma_0.6.root")==0) { xsec =      2138.094;     err = 1.358;}

  /*
  if(paramName.compare("SM")==0) { xsec =       856.199; err =     1.045;}
  if(paramName.compare("LambdaZ_-0.6_dKgamma_-0.6.root")==0) { xsec =      2049.823; err =     1.385;}
  if(paramName.compare("LambdaZ_-0.6_dKgamma_-0.4.root")==0) { xsec =      2001.091; err =     1.351;}
  if(paramName.compare("LambdaZ_-0.6_dKgamma_-0.2.root")==0) { xsec =      1971.554; err =     1.372;}
  if(paramName.compare("LambdaZ_-0.6_dKgamma_0.0.root")==0) { xsec =      1959.936; err =     1.355;}
  if(paramName.compare("LambdaZ_-0.6_dKgamma_0.2.root")==0) { xsec =      1964.816; err =     1.343;}
  if(paramName.compare("LambdaZ_-0.6_dKgamma_0.4.root")==0) { xsec =      1987.817; err =     1.350;}
  if(paramName.compare("LambdaZ_-0.6_dKgamma_0.6.root")==0) { xsec =      2028.575; err =     1.372;}
  if(paramName.compare("LambdaZ_-0.4_dKgamma_-0.6.root")==0) { xsec =      1417.959; err =     1.024;}
  if(paramName.compare("LambdaZ_-0.4_dKgamma_-0.4.root")==0) { xsec =      1369.149; err =     0.946;}
  if(paramName.compare("LambdaZ_-0.4_dKgamma_-0.2.root")==0) { xsec =      1340.213; err =     0.991;}
  if(paramName.compare("LambdaZ_-0.4_dKgamma_0.0.root")==0) { xsec =      1326.794; err =     0.958;}
  if(paramName.compare("LambdaZ_-0.4_dKgamma_0.2.root")==0) { xsec =      1331.933; err =     1.004;}
  if(paramName.compare("LambdaZ_-0.4_dKgamma_0.4.root")==0) { xsec =      1354.890; err =     0.968;}
  if(paramName.compare("LambdaZ_-0.4_dKgamma_0.6.root")==0) { xsec =      1394.851; err =     0.972;}
  if(paramName.compare("LambdaZ_-0.2_dKgamma_-0.6.root")==0) { xsec =      1053.221; err =     0.733;}
  if(paramName.compare("LambdaZ_-0.2_dKgamma_-0.4.root")==0) { xsec =      1004.695; err =     0.737;}
  if(paramName.compare("LambdaZ_-0.2_dKgamma_-0.2.root")==0) { xsec =       974.390; err =     0.729;}
  if(paramName.compare("LambdaZ_-0.2_dKgamma_0.0.root")==0) { xsec =       960.664; err =     0.725;}
  if(paramName.compare("LambdaZ_-0.2_dKgamma_0.2.root")==0) { xsec =       965.478; err =     0.733;}
  if(paramName.compare("LambdaZ_-0.2_dKgamma_0.4.root")==0) { xsec =       987.523; err =     0.774;}
  if(paramName.compare("LambdaZ_-0.2_dKgamma_0.6.root")==0) { xsec =      1026.728; err =     0.724;}
  if(paramName.compare("LambdaZ_0.0_dKgamma_-0.6.root")==0) { xsec =       952.089; err =     0.800;}
  if(paramName.compare("LambdaZ_0.0_dKgamma_-0.4.root")==0) { xsec =       901.500; err =     0.856;}
  if(paramName.compare("LambdaZ_0.0_dKgamma_-0.2.root")==0) { xsec =       870.836; err =     1.296;}
  if(paramName.compare("LambdaZ_0.0_dKgamma_0.0.root")==0) { xsec =       856.199; err =     1.045;}
  if(paramName.compare("LambdaZ_0.0_dKgamma_0.2.root")==0) { xsec =       861.957; err =     1.225;}
  if(paramName.compare("LambdaZ_0.0_dKgamma_0.4.root")==0) { xsec =       883.845; err =     0.856;}
  if(paramName.compare("LambdaZ_0.0_dKgamma_0.6.root")==0) { xsec =       923.050; err =     0.820;}
  if(paramName.compare("LambdaZ_0.2_dKgamma_-0.6.root")==0) { xsec =      1111.790; err =     0.791;}
  if(paramName.compare("LambdaZ_0.2_dKgamma_-0.4.root")==0) { xsec =      1063.428; err =     0.817;}
  if(paramName.compare("LambdaZ_0.2_dKgamma_-0.2.root")==0) { xsec =      1030.739; err =     0.773;}
  if(paramName.compare("LambdaZ_0.2_dKgamma_0.0.root")==0) { xsec =      1016.994; err =     0.757;}
  if(paramName.compare("LambdaZ_0.2_dKgamma_0.2.root")==0) { xsec =      1020.137; err =     0.798;}
  if(paramName.compare("LambdaZ_0.2_dKgamma_0.4.root")==0) { xsec =      1041.589; err =     0.742;}
  if(paramName.compare("LambdaZ_0.2_dKgamma_0.6.root")==0) { xsec =      1080.398; err =     0.796;}
  if(paramName.compare("LambdaZ_0.4_dKgamma_-0.6.root")==0) { xsec =      1535.021; err =     1.040;}
  if(paramName.compare("LambdaZ_0.4_dKgamma_-0.4.root")==0) { xsec =      1484.369; err =     1.037;}
  if(paramName.compare("LambdaZ_0.4_dKgamma_-0.2.root")==0) { xsec =      1453.069; err =     1.009;}
  if(paramName.compare("LambdaZ_0.4_dKgamma_0.0.root")==0) { xsec =      1439.129; err =     1.028;}
  if(paramName.compare("LambdaZ_0.4_dKgamma_0.2.root")==0) { xsec =      1442.755; err =     1.035;}
  if(paramName.compare("LambdaZ_0.4_dKgamma_0.4.root")==0) { xsec =      1462.876; err =     1.006;}
  if(paramName.compare("LambdaZ_0.4_dKgamma_0.6.root")==0) { xsec =      1502.613; err =     1.017;}
  if(paramName.compare("LambdaZ_0.6_dKgamma_-0.6.root")==0) { xsec =      2224.066; err =     1.492;}
  if(paramName.compare("LambdaZ_0.6_dKgamma_-0.4.root")==0) { xsec =      2174.382; err =     1.432;}
  if(paramName.compare("LambdaZ_0.6_dKgamma_-0.2.root")==0) { xsec =      2141.274; err =     1.451;}
  if(paramName.compare("LambdaZ_0.6_dKgamma_0.0.root")==0) { xsec =      2127.033; err =     1.443;}
  if(paramName.compare("LambdaZ_0.6_dKgamma_0.2.root")==0) { xsec =      2129.372; err =     1.448;}
  if(paramName.compare("LambdaZ_0.6_dKgamma_0.4.root")==0) { xsec =      2150.308; err =     1.436;}
  if(paramName.compare("LambdaZ_0.6_dKgamma_0.6.root")==0) { xsec =      2188.084; err =     1.431;}
 

 
  ///// all numbers are in the units of fb ///////////
  if(paramName.compare("SM")==0) { xsec =       693.0 ; err =      0.7 ;}
  if(paramName.compare("Delta_g1_Z-0.25d0")==0) { xsec =       697.238 ; err =      1.855 ;}
  if(paramName.compare("Delta_g1_Z-0.2d0")==0) { xsec =       695.873 ; err =      2.016 ;}
  if(paramName.compare("Delta_g1_Z-0.15d0")==0) { xsec =       692.746 ; err =      1.630 ;}
  if(paramName.compare("Delta_g1_Z-0.1d0")==0) { xsec =       692.702 ; err =      1.988 ;}
  if(paramName.compare("Delta_g1_Z-0.05d0")==0) { xsec =       693.278 ; err =      2.005 ;}
  if(paramName.compare("Delta_g1_Z0.05d0")==0) { xsec =       693.544 ; err =      1.676 ;}
  if(paramName.compare("Delta_g1_Z0.1d0")==0) { xsec =       693.238 ; err =      1.897 ;}
  if(paramName.compare("Delta_g1_Z0.15d0")==0) { xsec =       696.764 ; err =      2.096 ;}
  if(paramName.compare("Delta_g1_Z0.2d0")==0) { xsec =       697.837 ; err =      1.691 ;}
  if(paramName.compare("Delta_g1_Z0.25d0")==0) { xsec =      700.0;  err = 2.0 ;}
  if(paramName.compare("Delta_K_Z-0.25d0")==0) { xsec =       793.863 ; err =      2.141 ;}
  if(paramName.compare("Delta_K_Z-0.2d0")==0) { xsec =       756.142 ; err =      1.832 ;}
  if(paramName.compare("Delta_K_Z-0.15d0")==0) { xsec =       730.164 ; err =      1.399 ;}
  if(paramName.compare("Delta_K_Z-0.1d0")==0) { xsec =       712.810 ; err =      1.700 ;}
  if(paramName.compare("Delta_K_Z-0.05d0")==0) { xsec =       700.142 ; err =      2.044 ;}
  if(paramName.compare("Delta_K_Z0.05d0")==0) { xsec =       694.202 ; err =      2.052 ;}
  if(paramName.compare("Delta_K_Z0.1d0")==0) { xsec =       696.469 ; err =      1.700 ;}
  if(paramName.compare("Delta_K_Z0.15d0")==0) { xsec =       709.119 ; err =      1.922 ;}
  if(paramName.compare("Delta_K_Z0.2d0")==0) { xsec =       727.232 ; err =      1.833 ;}
  if(paramName.compare("Delta_K_Z0.25d0")==0) { xsec =       755.345 ; err =      1.981 ;}
  if(paramName.compare("Delta_K_gamma-0.25d0")==0) { xsec =       715.286 ; err =      1.958 ;}
  if(paramName.compare("Delta_K_gamma-0.2d0")==0) { xsec =       712.681 ; err =      1.969 ;}
  if(paramName.compare("Delta_K_gamma-0.15d0")==0) { xsec =       704.529 ; err =      2.133 ;}
  if(paramName.compare("Delta_K_gamma-0.1d0")==0) { xsec =       696.965 ; err =      1.837 ;}
  if(paramName.compare("Delta_K_gamma-0.05d0")==0) { xsec =       692.775 ; err =      1.667 ;}
  if(paramName.compare("Delta_K_gamma0.05d0")==0) { xsec =       689.879 ; err =      1.748 ;}
  if(paramName.compare("Delta_K_gamma0.1d0")==0) { xsec =       690.957 ; err =      1.896 ;}
  if(paramName.compare("Delta_K_gamma0.15d0")==0) { xsec =       692.173 ; err =      2.121 ;}
  if(paramName.compare("Delta_K_gamma0.2d0")==0) { xsec =       691.701 ; err =      1.754 ;}
  if(paramName.compare("Delta_K_gamma0.25d0")==0) { xsec =       695.953 ; err =      1.882 ;}
  if(paramName.compare("Lambda_Z-0.25d0")==0) { xsec =       788.894 ; err =      2.013 ;}
  if(paramName.compare("Lambda_Z-0.2d0")==0) { xsec =       746.479 ; err =      1.851 ;}
  if(paramName.compare("Lambda_Z-0.15d0")==0) { xsec =       718.517 ; err =      1.831 ;}
  if(paramName.compare("Lambda_Z-0.05d0")==0) { xsec =       689.782 ; err =      1.713 ;}
  if(paramName.compare("Lambda_Z0.05d0")==0) { xsec =       700.448 ; err =      1.751 ;}
  if(paramName.compare("Lambda_Z0.1d0")==0) { xsec =       720.156 ; err =      2.095 ;}
  if(paramName.compare("Lambda_Z0.15d0")==0) { xsec =       751.032 ; err =      1.977 ;}
  if(paramName.compare("Lambda_Z0.2d0")==0) { xsec =       793.941 ; err =      1.803 ;}
  if(paramName.compare("Lambda_Z0.25d0")==0) { xsec =       842.683 ; err =      1.637 ;}
  if(paramName.compare("Lambda_gamma-0.25d0")==0) { xsec =       706.943 ; err =      1.693 ;}
  if(paramName.compare("Lambda_gamma-0.2d0")==0) { xsec =       700.210 ; err =      1.923 ;}
  if(paramName.compare("Lambda_gamma-0.15d0")==0) { xsec =       696.097 ; err =      1.912 ;}
  if(paramName.compare("Lambda_gamma-0.1d0")==0) { xsec =       691.994 ; err =      2.053 ;}
  if(paramName.compare("Lambda_gamma-0.05d0")==0) { xsec =       691.558 ; err =      1.667 ;}
  if(paramName.compare("Lambda_gamma0.05d0")==0) { xsec =       692.655 ; err =      1.568 ;}
  if(paramName.compare("Lambda_gamma0.1d0")==0) { xsec =       692.777 ; err =      2.107 ;}
  if(paramName.compare("Lambda_gamma0.15d0")==0) { xsec =       703.369 ; err =      1.878 ;}
  if(paramName.compare("Lambda_gamma0.2d0")==0) { xsec =       711.104 ; err =      1.743 ;}
  if(paramName.compare("Lambda_gamma0.25d0")==0) { xsec =      720.0; err = 2.0 ;} 
  */
}
