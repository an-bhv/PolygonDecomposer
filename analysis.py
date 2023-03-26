import matplotlib.pyplot as plt
import numpy as np

f = open("output.csv", "r")

x = []
mp1time = []
totaltime = []


for line in f:
    a = line.split(",")
    x.append(float(a[1]))    
    mp1time.append(float(a[3]))
    totaltime.append(float(a[3])+ float(a[6]))



# x = np.array(x)
# totaltime = np.array(totaltime)
plt.plot(x,mp1time,label="MP1")
plt.plot(x,totaltime,label="Total")
plt.xlabel('Number of points')
plt.ylabel('Time (ms)')
plt.legend()
plt.show()