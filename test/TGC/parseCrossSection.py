import os,sys
import string, re
from time import gmtime, localtime, strftime


def change(change1, change2):
    dirName = "/uscms_data/d2/kalanand/software/MCFM/Bin/"
    infile = "LambdaZ_" + str(change1) + "_dKgamma_" + str(change2) + ".stdout"
    fin  = open(dirName + infile)
    fout = open("cross_sections_atgc.txt","a")
    for line in fin.readlines():
        if  line.find("Value of final tota integral is")!=-1:
            line=line.replace("Value of final tota integral is",  infile+ ": ")
            fout.write(line)


###################
for i in range(-10,11):
    for j in range(-3,4):
        change(0.04*i, 0.2*j)


for j in range(-3,4):
    change(-0.6, 0.2*j)
    change(0.6, 0.2*j)
    
