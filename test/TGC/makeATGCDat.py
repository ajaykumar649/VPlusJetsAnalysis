import os,sys
import string, re
from time import gmtime, localtime, strftime

ConfigFile = "inputWWToLnuJJ.DAT"
my3DayArea = "/uscmst1b_scratch/lpc1/3DayLifetime/kalanand/"
myMCFM     = "/uscms_data/d2/kalanand/software/MCFM/Bin/"
thisDirectory = "/uscms_data/d2/kalanand/junk/vplusjets/CMSSW_4_2_8/src/ElectroWeakAnalysis/VPlusJets/test/TGC/"

def changeConfigFile(change1, change2):    
    subdir = "LambdaZ_" + str(change1) + "_dKgamma_" + str(change2)  
    dirName = my3DayArea +  subdir
    child1 = os.mkdir(dirName)
    command = "cp ${PWD}/*.* "+ myMCFM
    child2 = os.system(command)
    child3 = os.chdir(myMCFM)
    child4 = os.symlink(myMCFM+"Pdfdata", dirName+"/Pdfdata")
    child5 = os.symlink(myMCFM+"process.DAT", dirName+"/process.DAT")
    fin  = open(thisDirectory+ConfigFile)
    pset_cfg = subdir +".DAT"
    fout = open(pset_cfg,"w")
    for line in fin.readlines():
        if  line.find("Lambda(Z)")!=-1:
            line=line.replace("0.0d0", str(change1)+"d0" )
        if  line.find("Lambda(gamma)")!=-1:
            line=line.replace("0.0d0", str(change1)+"d0" )
        if  line.find("Delta_K(gamma)")!=-1:
            line=line.replace("0.0d0", str(change2)+"d0" )
        if  line.find("Delta_K(Z)")!=-1:
            line=line.replace("0.0d0", str(-0.2864 * change2)+"d0")            
        fout.write(line)
    print pset_cfg + " has been written.\n"
    command = "./submitToCondor.py -c " + pset_cfg 
    print "Submitting job: " + command + "\n"
    child9 = os.system(command)


    
###################
for i in range(-3,4):
    for j in range(-3,4):
        changeConfigFile(0.2*i, 0.2*j)

#changeConfigFile(0.9, 0.9)
