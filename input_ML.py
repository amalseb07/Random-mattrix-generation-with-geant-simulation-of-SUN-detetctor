import os
import numpy as np
import random
import time

# number of gammas partition
def random_partition(n):
    # Choose random cut points between 1 and n-1
    cuts = sorted(random.sample(range(1, n), random.randint(0, n-1))) # tree-cutter logic ...
    #print(cuts)
    parts = [a - b for a, b in zip(cuts + [n], [0] + cuts)]

    parts=np.array(parts)
    #print(type(parts))
    return parts


#  excitation energy generator function
def excitation_energy(l):       # l is length of patition generated in the gamma_partition generator function
    Ex = sorted(random.sample(range(200, 9500), l))
    return Ex



def intensity_partition(l, min_val=0.1):
    if l * min_val > 1:                                  
        raise ValueError("min_val too large for given n (sum would exceed 1).")
    
    # remaining portion after giving each part the minimum
    remaining = 1 - l * min_val
    
    # randomly partition the remaining portion using Dirichlet
    parts = np.random.dirichlet(np.ones(l)) * remaining
    
    # add the minimum to each part
    parts += min_val
    return parts



def gamma_energy_partition(Ex,p):
    # Choose random cut points between 1 and n-1
    k=0
    while k==0:
        cuts = sorted(random.sample(range(50, Ex), p-1))
        #print(cuts)
       # print("hi")
       # print(cuts)
        parts = [a - b for a, b in zip(cuts + [Ex], [0] + cuts)]


        parts =sorted(parts)
       # print(parts)

       # print(parts)

        #parts2 = [parts[i] - parts[i-1] for i in range(1, p)]

        #print(type(parts2))
        parts= np.array(parts)

        unique_elements = np.unique(parts)

        if len(unique_elements)== len(parts) and (parts > 50).all()==True:
            k=1         


    return parts 


    


# label generation for each Ex
def label_generator(Ex,part,E_g,Ix):

    # last element indices in the loop that follows
    end1 = len(Ex)-1
    end2= part[len(part)-1]-1  # last element of part -1 
     

   # SInce Ex and E_g already sorted , the labelling part will be such that ordering takes with smallest Ex , and in each Ex , smallest E_g 

    label=[]
    for i in range(len(Ex)):
        for j in range(part[i]):
            if i == end1 and j == end2:
                label.append([E_g[i][j],Ex[i],Ix[i],1])
            else :
                label.append([E_g[i][j],Ex[i],Ix[i],0])
                    

    label =np.array(label)  
    np.save("rootFiles/final_output/y_train_temp.npy", label)

	
    return label


def geant_input_generator(num_sim,E_g,Ix):

    Ix= Ix*100

    # Step 1: Find maximum length
    max_len = max(len(a) for a in E_g)

    # Step 2: Pad with zeros
    padded = [np.pad(a, (0, max_len - len(a)), mode='constant') for a in E_g]

    # Convert to a 2D numpy array
    E_gamma = np.vstack(padded)

    # number of cascades
    num_cas= E_gamma.shape[0]
    # number of gamma rays per cascade
    num_gam= E_gamma.shape[1]

    file=open("input_random.txt", 'w')

    # first line of geant file
    file.write(str(num_sim))
    file.write(' ')
    file.write(str(num_cas))
    file.write(' ')
    file.write(str(num_gam))
    file.write(os.linesep)

    # 2-last line in geant4 file    
    for i in range(num_cas):
        file.write(str(Ix[i]))
        for j in range(num_gam):
            file.write(' ')
            file.write(str(E_gamma[i,j]))
        file.write(os.linesep)

    file.close()



def input_generator(num_gamma, num_sim):

    part= random_partition(num_gamma)   # partition n gammas to sets e.g 4 to [1,2,1]
    print("instance")
    print("partition:",part)

    len_part = len(part)

    Ex = excitation_energy(len_part)   # assign Ex to each partion e.g ..[300,700,1200] .. ascending order
    print("Ex:",Ex)
    Ix = intensity_partition(len_part,0.1)  # Partition intensity 1 among them such that it >0.1 each... e.g [0.3,0.2, 0.5]
    print("Ix:",Ix)

    # need to partition Ex into each gamma ray energy according to the partion
    E_g=[]
    for j in range(len(Ex)):
        E_g.append(gamma_energy_partition(Ex[j],part[j]))
	
    print("Eg")	
    print(E_g)
    #print(E_g)
    # at this point We have set of Ex , set of Ix, Set of gamma-rays that are partitioned into
    # next we need to generate the labels and input files for Geant

        
    label=label_generator(Ex,part,E_g,Ix)

    print("label")
    print(label)	
		
    geant_input_generator(num_sim,E_g,Ix)
    
    #time.sleep(10)
   
if __name__ == "__main__":
    input_generator(3, 100000)





