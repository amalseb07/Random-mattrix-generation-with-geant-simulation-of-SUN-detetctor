//Accepts a range of ROOT histogram plots of the form
//2dplots_{energy}_keVgamma.root and converts their bin contents to a single-line CSV file.

void histo2csv(){
      //Define output name
      ofstream fileout("/mnt/analysis/sun/e1807_ANL/sebas_geant_2/sunShare/rootFiles/inclu_pp/trial.csv");
      
      //Open ROOT Histogram
      TFile *f = new TFile("/mnt/analysis/sun/e1807_ANL/sebas_geant_2/sunShare/rootFiles/inclu_pp/mattrix_trial.root");

      //cout << "got file " << i << endl;
      
      //Get TH2D from the ROOT Histogram
      TH2F *hsum = (TH2F*)f->Get("sum");
      
      //Get Number of bins from the histograms
      int nbinsx=hsum->GetXaxis()->GetNbins();
      int nbinsy=hsum->GetXaxis()->GetNbins();

      for (int y=1; y<=nbinsy; y++)
        {
	  for (int x=1; x<=nbinsx; x++)
            {
	      fileout<<hsum->GetBinContent(x,y)<<",";
	      
            }
        }

   

      fileout<<endl;

      //delete hsum;
      f->Close();
      delete f;
      
    
}
