import os

directory = "..\\Countries"

for filename in os.listdir(directory):
    path = os.path.join(directory,filename)
    os.rename(path, path.replace(' ','_'))
