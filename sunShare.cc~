#include "G4RunManager.hh"
#include "G4UImanager.hh" 
#include "G4UIterminal.hh"
#include "G4ios.hh"  

//#include "LHEP_PRECO_HP.hh"
#include "QGSP_BIC_HP.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "TTree.h"
#include "TFile.h"
#include "TROOT.h"
#include "TRint.h"
#include "TPluginManager.h"

#include "G4VisExecutive.hh"


// GLOBAL VARIABLES

  int runTimes;    //total number of events to simulate
  int nCascades; //number of gamma ray cascades from the excited state 
  int nEnergies;   //number of gamma rays in each cascade

	//if you change the following variables you also need to update all of the include/*.hh files
	int nDetectors = 8;       //number of detectors you want the energy for in your ROOT file
  G4String detectorName[8]; //the name of your detectors (see src/DetectorConstruction.cc)
  G4double energy_MeV[8];   //deposited energy in MeV
  G4double energy_keV[8];   //deposited energy in keV
  G4double sigma[8];        //resolution of your detectors
  G4double energy[8];       //energy that will be saved to the ROOT file
  G4double energy_tot;      //total energy deposited in all of your detectors of interest
  int mult;                 //multiplicity of detectors hit

  float inputArray[500][50]; //array of energies to simulate [cascade][energies]
  float inputCutoff[500];    //keeps track of how many events there should be for each cascade
  int cascade=0;             //keeps track of which cascade the simulation is at

  TFile *newfile;
  TTree *t;
  TBranch *ebranch;


// THE MAIN PROGRAM

int main(int argc, char** argv)
{
  // Construct the default run manager
  G4RunManager *runManager = new G4RunManager;

  // set mandatory initialization classes
  DetectorConstruction *Det = new DetectorConstruction;
  runManager->SetUserInitialization(Det);
  runManager->SetUserInitialization(new QGSP_BIC_HP);

  #ifdef G4VIS_USE
    G4VisManager* visManager = new G4VisExecutive;
     visManager->Initialize();
  #endif

 // set optional user action class
  runManager->SetUserAction(new RunAction);

  // Read input file and create array of energies to simulate 
  std::ifstream fin("input");

  fin >> runTimes >> nCascades >> nEnergies;
 
  for (int i=0; i<nCascades; i++)
  { 
     fin >> inputArray[i][0];
     if (i==0)
       inputCutoff[i] = inputArray[i][0]*runTimes/100.0;
     else
       inputCutoff[i] = inputCutoff[i-1] + inputArray[i][0]*runTimes/100.0;
     for (int j=1; j<=nEnergies; j++)
      {
        fin >> inputArray[i][j];
      }
  }
 
  // set mandatory user action class
  runManager->SetUserAction(new PrimaryGeneratorAction);

  EventAction *eventAction = new EventAction;
  runManager->SetUserAction(eventAction);

  runManager->SetUserAction(new SteppingAction(Det)); 


  // Initialize G4 kernel
  runManager->Initialize();


  // for visualization purposes
  if (argc==1)
  {
    G4UIsession *Session = new G4UIterminal;

    //if you want visualization you have to uncomment the next line
    G4UImanager::GetUIpointer()->ApplyCommand("/control/execute vis.mac");

    Session->SessionStart();
    delete Session;
  }
  else
  {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];  
    G4UImanager::GetUIpointer()->ApplyCommand(command+fileName);
  }

  // run the program
  runManager->BeamOn(runTimes);


  // job termination
  fin.close();
  newfile->Close();

  G4cout << "Rootfile closed!" << G4endl;

  #ifdef G4VIS_USE
     delete visManager;
  #endif

  delete runManager;
  G4cout << "RunManager closed!" << G4endl;

  return 0;
}
