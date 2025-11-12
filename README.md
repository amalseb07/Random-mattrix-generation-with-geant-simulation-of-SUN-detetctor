# Random mattrix generation for Ex- Eg 

## Description
This program generates n random Ex-Eg mattrices for fixed number of gamma -rays k ( a user input ). The core of the program is 2 python scripts and geant simulation. The user needs to execute the script shell ./run_python_geant which contains

- input_ML.py : This program takes as argument (k,num_sim) where k is the number of gamma rays you want in the mattrix and num_sum is the number of geant simulation you need. The final_output consist of 2 parts . First , it creates a rootFiles/Final_output/y_train.npy which has a an initial
  shape (k,4). The 4 column consist of (E_g,E_x,I_x,flag). E_g = Energy of gamma_ray, E_x = Excitation enrgy, I_x= Intensity of feeding, flag = 0/1 for ML autoregressive projects. Second it creates an input_random.txt file in the same directory.

- geant executable : This is the usual geant simulation that creates a output rootfile called trial.root in rootFiles/.

- master_py_script.py: Takes the trial.root from rootFiles/ and creates rootFiles/final_output/X_train.npy which is initially a (512,512,1) npy file corresponding to the k-gamma-ray set.

  At the end of n loops we have y_train accumulating to y_train = (n*k,4) numpy array and each k-set consists of 1 (512,512,1) corresponding mattrix. So X_train final  shape is (n,512,512,1).

   
  

## Setup Instructions
1. Clone the repository:
   ```bash
   git clone https://github.com/amalseb07/cmse802_project.git](https://github.com/amalseb07/Random-mattrix-generation-with-geant-simulation-of-SUN-detetctor.git
   cd Random-mattrix-generation-with-geant-simulation-of-SUN-detetctor

2. Make command for geant executable
     
3. Open the input_ML.py and specify in the last line (k, num_sim)

IMPORTANT NOTE : minimum E_g is set at 50 , make sure depending on number of gamma rays k, the minimum excitation energy in the def excitation_energy(l): is set at at least k*50+50.

4. Now you can run the script ./run_python_geant.py
   
  


