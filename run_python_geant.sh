#!/bin/bash

# Number of loops
n=2500

# Always overwrite / reinitialize final arrays
python << 'EOF'
import numpy as np

# Create empty arrays with shape (0, 4) and (0, 512, 512, 1)
np.save('rootFiles/final_output/y_train.npy', np.empty((0, 4)))
np.save('rootFiles/final_output/X_train.npy', np.empty((0, 512, 512, 1)))

print("Initialized fresh empty arrays:")
print("  y_train.npy -> (0, 4)")
print("  X_train.npy -> (0, 512, 512, 1)")
EOF

for ((i=1; i<=n; i++))
do
    echo "=== Running loop $i / $n ==="

    # Step 1: Run first Python script
    python input_ML.py

    # Step 2: Run Geant4 executable
    ~/geant4_workdir/bin/Linux-g++/sunShare

    # Step 3: Go to rootFiles and run second Python script
    cd rootFiles
    python master_py_script.py

    # for testing only
    #cd inclu_pp
    #cp mattrix_trial.root mattrix_trial_${i}.root
    #cd ../..

    cd ..

    # Append to final arrays
    python << 'EOF'
import numpy as np

y_train_temp = np.load('rootFiles/final_output/y_train_temp.npy')
X_train_temp = np.load('rootFiles/final_output/X_train_temp.npy')

y_train = np.load('rootFiles/final_output/y_train.npy')
X_train = np.load('rootFiles/final_output/X_train.npy')

y_train = np.vstack((y_train, y_train_temp))
X_train = np.concatenate((X_train, X_train_temp[np.newaxis, ...]), axis=0)

np.save('rootFiles/final_output/y_train.npy', y_train)
np.save('rootFiles/final_output/X_train.npy', X_train)

print("Updated shapes:", y_train.shape, X_train.shape)
EOF

done

echo " All loops complete. Final arrays saved as:"
echo "  - first_final.npy"
echo "  - second_final.npy"

