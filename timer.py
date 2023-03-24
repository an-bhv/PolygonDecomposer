#write code to run cpp file
import os

directory = "..\\Countries"

for filename in os.listdir(directory):
    inp = os.path.join(directory,filename)
    output = filename + ',' + os.popen(".\\timer " + inp).read().replace(" ",', ') + "\n"

    #make output a csv file
    with open('output.csv', 'a') as f:
        f.write(output)
