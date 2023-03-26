import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np
import os

inputs = ["in", "output", "merged"]

directory = "iterations"

for filename in os.listdir(directory):
    path = os.path.join(directory,filename)
    with open(path) as f:
        lines = f.readlines()
    
    xs, ys = [], []
    for line in lines:
        if line.strip() == "":
            plt.fill(xs, ys, color='w',edgecolor='black', linewidth=0.5)
            xs, ys = [], []
        else:
            if ',' not in line:
                continue
            x, y = map(float, line.split(','))
            xs.append(x)
            ys.append(y)
    plt.fill(xs, ys, edgecolor='black', linewidth=0.5)
    plt.title(str(filename))
    plt.show()



for filename in os.listdir(directory):
    #delete the file
    path = os.path.join(directory,filename)
    os.remove(path)
