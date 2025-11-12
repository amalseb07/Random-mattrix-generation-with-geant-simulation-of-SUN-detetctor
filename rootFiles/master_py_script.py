
import ROOT
import numpy as np
import random



# Load the macro
ROOT.gROOT.LoadMacro("inclu_pp/EnergySum2.C")
# Call the function inside the macro
ROOT.EnergySum2()


ROOT.gROOT.LoadMacro("inclu_pp/histo2csv.C")
ROOT.histo2csv()


# Read the file
data = open('inclu_pp/trial.csv', 'r')

    
# Split and clean
data = data.read().split(',')
data = data[:-1]  # remove last empty entry if there is one
    
# Convert to float
data = np.array(data, dtype=float)
    
# Reshape into square array
length_data = int(np.sqrt(len(data)))
data = np.reshape(data, [length_data, length_data])
    
# Rearrange into data2
data2 = np.zeros([length_data, length_data])

for j in range(length_data):
	data2[length_data - j-1,:] = data[j,:]
    
    	

data2 = data2.astype(np.float16)
data2 = np.expand_dims(data2, axis=-1)

# add padding to make it (512,512)	
data2 = np.pad(data2, ((12,0),(0,12),(0,0)), 'minimum')	

    
# Save to .npy file
np.save('final_output/X_train_temp.npy', data2)
print("Saved successfully!")
print(data2.shape)
