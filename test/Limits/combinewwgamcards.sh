#!/bin/bash
#

###########################################################################
## a0W/Lambda^2 Limits (Form Factor with Lambda_FF = 500, n = 2):
###########################################################################
#for a0w in -80 -100 -140 80 100 140
#for a0w in -177 -174 -171 -168 -165 -162 -159 -156 -153 -150 -140 -100 -80 80 100 140 150 153 156 159 162 165 168 171 174 177


##########################################################################
## a0W/Lambda^2 Limits (no Form Factor):
##########################################################################
 #for a0w in -2 -3 -5 2 3 5
 for a0w in -16 -18 -20 -22 -24 -26 -28 -30 -32 -34 -36 -38 -50 16 18 20 22 24 26 28 30 32 34 36 38 50

 do
   eldijet=datacard_wwgamaqgc_el_a0W:${a0w}.txt
   mudijet=datacard_wwgamaqgc_mu_a0W:${a0w}.txt
   echo "combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_a0W:${a0w}.txt"
   combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_a0W:${a0w}.txt
 done


##########################################################################
## aCw/Lambda^2 Limits:
##########################################################################
 for aCw in  -80 -50 -48 -46 -44 -42 -40 -38 -36 -34 -32 -30 -28 -26 26 28 30 32 34 36 38 40 42 44 46 48 50 80
 do
   eldijet=datacard_wwgamaqgc_el_aCW:${aCw}.txt
   mudijet=datacard_wwgamaqgc_mu_aCW:${aCw}.txt
   echo "combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_aCW:${aCw}.txt"
   combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_aCW:${aCw}.txt
 done


##########################################################################
## L_T,0 Limits:
##########################################################################
 for lt0 in -80 -50 -38 -36 -34 -32 -30 -28 -26 -24 -22 -20 -18 18 20 22 24 26 28 30 32 34 36 38 50 80
 do
   eldijet=datacard_wwgamaqgc_el_LT0:${lt0}.txt
   mudijet=datacard_wwgamaqgc_mu_LT0:${lt0}.txt
   echo "combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_LT0:${lt0}.txt"
   combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_LT0:${lt0}.txt
 done


##########################################################################
## k0W/Lambda^2 Limits:
##########################################################################
 for K0W in -20 -17 -16 -15 -14 -13 -12 -11 -10 -5 5 10 11 12 13 14 15 16 17 20
 do
   eldijet=datacard_wwgamaqgc_el_K0W:${K0W}.txt
   mudijet=datacard_wwgamaqgc_mu_K0W:${K0W}.txt
   echo "combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_K0W:${K0W}.txt"
   combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_K0W:${K0W}.txt
 done


##########################################################################
## SM Limits with variying MVA cuts:
##########################################################################
# eldijet=datacard_wwgamaqgc_el_SM.txt
# mudijet=datacard_wwgamaqgc_mu_SM.txt
# echo "combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_SM.txt"
# combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_SM.txt

# eldijet=datacard_wwgamaqgc_el_SM_MVA000.txt
# mudijet=datacard_wwgamaqgc_mu_SM_MVA000.txt
# echo "combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_SM_MVA000.txt"
# combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_SM_MVA000.txt

# eldijet=datacard_wwgamaqgc_el_SM_MVA010.txt
# mudijet=datacard_wwgamaqgc_mu_SM_MVA010.txt
# echo "combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_SM_MVA010.txt"
# combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_SM_MVA010.txt

# eldijet=datacard_wwgamaqgc_el_SM_MVA020.txt
# mudijet=datacard_wwgamaqgc_mu_SM_MVA020.txt
# echo "combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_SM_MVA020.txt"
# combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_SM_MVA020.txt

# eldijet=datacard_wwgamaqgc_el_SM_MVA021.txt
# mudijet=datacard_wwgamaqgc_mu_SM_MVA021.txt
# echo "combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_SM_MVA021.txt"
# combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_SM_MVA021.txt

# eldijet=datacard_wwgamaqgc_el_SM_MVA0225.txt
# mudijet=datacard_wwgamaqgc_mu_SM_MVA0225.txt
# echo "combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_SM_MVA0225.txt"
# combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_SM_MVA0225.txt

