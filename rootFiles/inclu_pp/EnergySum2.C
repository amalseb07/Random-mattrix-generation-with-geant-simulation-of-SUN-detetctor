


void EnergySum2()


{

TFile* f1 = new TFile("/mnt/analysis/sun/e1807_ANL/sebas_geant_2/sunShare/rootFiles/trial.root","READ");


TTree *t = (TTree*)f1->Get("t");

t->Project("ht1(500,1,10000,500,1,10000)","eneAll:eneT1");
t->Project("ht2(500,1,10000,500,1,10000)","eneAll:eneT2");
t->Project("ht3(500,1,10000,500,1,10000)","eneAll:eneT3");
t->Project("ht4(500,1,10000,500,1,10000)","eneAll:eneT4");

t->Project("hb1(500,1,10000,500,1,10000)","eneAll:eneB1");
t->Project("hb2(500,1,10000,500,1,10000)","eneAll:eneB2");
t->Project("hb3(500,1,10000,500,1,10000)","eneAll:eneB3");
t->Project("hb4(500,1,10000,500,1,10000)","eneAll:eneB4");

// Retrieve histograms from the current ROOT directory
TH2D *ht1 = (TH2D*)gDirectory->Get("ht1");
TH2D *ht2 = (TH2D*)gDirectory->Get("ht2");
TH2D *ht3 = (TH2D*)gDirectory->Get("ht3");
TH2D *ht4 = (TH2D*)gDirectory->Get("ht4");

TH2D *hb1 = (TH2D*)gDirectory->Get("hb1");
TH2D *hb2 = (TH2D*)gDirectory->Get("hb2");
TH2D *hb3 = (TH2D*)gDirectory->Get("hb3");
TH2D *hb4 = (TH2D*)gDirectory->Get("hb4");


TH2D *sum = new TH2D("sum","sum",500,1,10000,500,1,10000);

sum->Add(ht1);
sum->Add(ht2);
sum->Add(ht3);
sum->Add(ht4);
sum->Add(hb1);
sum->Add(hb2);
sum->Add(hb3);
sum->Add(hb4);




TFile *FNew = new TFile("/mnt/analysis/sun/e1807_ANL/sebas_geant_2/sunShare/rootFiles/inclu_pp/mattrix_trial.root", "RECREATE");
sum->Write();
FNew->Close(); // important!

f1->Close();   // do NOT delete t manually


}
