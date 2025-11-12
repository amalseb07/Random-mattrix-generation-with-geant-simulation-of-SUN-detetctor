Author: Steve Quinn
Date: 07 August 2014

Overview: This is the GEANT4 simulation for the SuN detector. I did not write it from scratch but did extensive modification of an existing code. I am not an expert at C++ so I apologize for any inefficiency.

The general scheme of things is that you build your detector with the correct geometry and shoot out a particle with a certain energy. GEANT4 handles all the physics of the interaction and calculates the energy deposited. The output is saved as a ROOT file.  The code should be commented to get you started with making modifications.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Description of files:


----- GNUmakefile: 
 The Makefile that builds the executable. The 'name' variable in the Makefile should be the same name as the main *.cc file (in this case sunShare.cc).


----- input:  
 The input file that contains the energies of the particles you want to simulate. The format for the input file is:
		numberOfEventsToSimulate	numberOfCascades  numberOfGammaRaysPerCascade
		intensityOfCascade1		energyGamma1		energyGamma2		energyGamma3.....
		intensityOfCascade2		energyGamma1		energyGamma2		energyGamma3.....
		intensityOfCascade3		energyGamma1		energyGamma2		energyGamma3.....
		....									....						....						....

	For example the input file for simulating 100000 decays of Co-60 is
			100000 1 2
			100.0 1173 1332


----- sunShare.cc:  
 The main program. This contains the one line that can be uncommented if you would like to see the detector visualization. Also this file contains the global variables that get used in the simulation.  Very important: If you add additional detectors to the simulation, you need to modify the global variables of nDetectors, detectorName, energy_MeV, energy_keV, sigma, and energy to specify how many detectors there are.  You will also need to update this information in all the include/*.hh files.


----- vis.mac  
 When the visualization is in use, this is a macro that draws the picture to your liking.  It also contains the commands to use to rotate, zoomIn, etc.


---- rootFiles:  
 The directory where the output ROOT files get saved. The name of the ROOT file can be specified in /src/RunAction.cc.  However, I usually name every output file trial.root and then rename it afterwards.


----- include:  
 Directory for all of the .hh files (see below).


----- src: 
 Directory for all of the .cc files (see below).
 

-----DetectorConstruction
 File where you build the detector.


-----RunAction
 File that specifies what to do at the beginning and end of each run.


-----EventAction 
 File that specifies what to do before and after shooting each particle.


-----SteppingAction
 File that specifies what to do at each timestep in the simulation.


-----PrimaryGeneratorAction
 File that specifies the properties of the particle you want to shoot.


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



Instructions:

  - to set GEANT4 environment (at least on the NSCL machines):  > module load geant4

  - to compile:  > make

  - to run:  > yourExecutable 
						 > exit

    in some cases it is   > ~/geant4_workdir/bin/Linux-g++/yourExecutable

