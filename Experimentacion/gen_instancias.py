import numpy as np
import os

np.random.seed(323565897)

f = open("/home/gaspush/Facu/AlgoIII-2023-1/TP3/TP3-AlgoIII/Experimentacion/instDENSO.txt", "w")
f.write("10\n")

for n in range (10, 101, 10):
    m = n*n
    k = int(3*n/100)
    s = np.random.randint(1,n+1)
    t = np.random.randint(1,n+1)
    
    f.write(str(n)+" "+str(m)+" "+ str(k) +" "+ str(s) +" "+ str(t) +"\n")
    
    for i in range (m):
        x = np.random.randint(1,n+1)
        y = np.random.randint(1,n+1)
        w = np.random.randint(0,1001)
        f.write(str(x)+ " " + str(y)+ " "+str(w)+"\n")
        
    for i in range(k):
        x = np.random.randint(1,n+1)
        y = np.random.randint(1,n+1)
        w = np.random.randint(0,1001)
        f.write(str(x)+ " " + str(y)+ " "+str(w)+"\n")