
void makeTreeFromText() {

   makeTreeFromText("params-ww-kappa-lambda-cteq6l1-001-fitted-new-1TeV.list", 
   "root_kappa-lambda.root", "lambda", "dkappa");

   makeTreeFromText("params-ww-lambda-g1z-cteq6l1-001-fitted-new-1TeV.list", 
   "root_lambda-g1.root", "lambda", "dg1");

   makeTreeFromText("params-ww-kappa-g1z-cteq6l1-001-fitted-new-1TeV.list",
   "root_kappa-g1.root", "dkappa", "dg1");
}

void makeTreeFromText(char* inputFile, char* outputFile, char* first, char* second) {
   TFile fout( outputFile, "recreate");
   TTree tree("tree","tree");
   char vars[1000];
   sprintf(vars, "%s/F:%s:p0:p1:p2:p3:p4:p5:p6:chi2", first, second);

   //char* branches = "first/F:second:p0:p1:p2:p3:p4:p5:p6:chi2";
   tree.ReadFile( inputFile, vars);

   tree.Write();
   // fout.Close();
}
