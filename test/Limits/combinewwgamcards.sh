#!/bin/bash
for a0w in -2 -3 -5 2 3 5
do
  eldijet=datacard_wwgamaqgc_eldijet_a0w:${a0w}.txt
  mudijet=datacard_wwgamaqgc_mudijet_a0w:${a0w}.txt
  echo "combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_a0w:${a0w}.txt"
  combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_a0w:${a0w}.txt
done
for aCw in -3 -5 -8 3 5 8
do
  eldijet=datacard_wwgamaqgc_eldijet_aCw:${aCw}.txt
  mudijet=datacard_wwgamaqgc_mudijet_aCw:${aCw}.txt
  echo "combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_aCw:${aCw}.txt"
  combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_aCw:${aCw}.txt
done
for lt0 in -3 -5 -8 3 5 8
do
  eldijet=datacard_wwgamaqgc_eldijet_lt0:${lt0}.txt
  mudijet=datacard_wwgamaqgc_mudijet_lt0:${lt0}.txt
  echo "combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_lt0:${lt0}.txt"
  combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_lt0:${lt0}.txt
done

eldijet=datacard_wwgamaqgc_eldijet_SM.txt
mudijet=datacard_wwgamaqgc_mudijet_SM.txt
echo "combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_SM.txt"
combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_SM.txt
