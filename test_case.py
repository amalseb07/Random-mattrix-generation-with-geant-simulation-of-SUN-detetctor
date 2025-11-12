import os
import numpy as np
import random
import time




def geant_input_generator():

   
    file=open("input_random.txt", 'w')

    # first line of geant file
    file.write(str(100000))
    file.write(' ')
    file.write(str(1))
    file.write(' ')
    file.write(str(2))
    file.write(os.linesep)

    file.write(str(100))
    file.write(' ')
    file.write(str(640))
    file.write(' ')
    file.write(str(4320))

    file.close()



    a= np.array([[640,4960,1,0],[4320,4960,1,1]])

    np.save("rootFiles/final_output/y_train_temp.npy",a)


    print(a)
    time.sleep(10)

if __name__ == "__main__":
    geant_input_generator()
