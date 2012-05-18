import os,sys
import string, re
from time import gmtime, localtime, strftime

my3DayArea = "/uscmst1b_scratch/lpc1/3DayLifetime/kalanand/"

def clean_up_output(change1, change2):
    subdir = "LambdaZ_" + str(change1) + "_dKgamma_" + str(change2)  
    dirName = my3DayArea +  subdir
    child = os.system("./convert_rz.csh " + dirName)
    print "The .rz files have been converted.\n"

###################
for i in range(-3,4):
    for j in range(-3,4):
        clean_up_output(0.2*i, 0.2*j)
