#!/bin/bash
for a0w in -2 -3 -5 2 3 5
do
  eldijet=datacard_wwgamaqgc_eldijet_a0w:${a0w}e-5.txt
  mudijet=datacard_wwgamaqgc_mudijet_a0w:${a0w}e-5.txt
  echo "combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_a0w:${a0w}e-5.txt"
  combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_a0w:${a0w}e-5.txt
done
for aCw in -3 -5 -8 3 5 8
do
  eldijet=datacard_wwgamaqgc_eldijet_aCw:${aCw}e-5.txt
  mudijet=datacard_wwgamaqgc_mudijet_aCw:${aCw}e-5.txt
  echo "combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_aCw:${aCw}e-5.txt"
  combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_aCw:${aCw}e-5.txt
done
for lt0 in -3 -5 -8 3 5 8
do
  eldijet=datacard_wwgamaqgc_eldijet_lt0:${lt0}e-11.txt
  mudijet=datacard_wwgamaqgc_mudijet_lt0:${lt0}e-11.txt
  echo "combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_lt0:${lt0}e-11.txt"
  combineCards.py mudijet=${mudijet} eldijet=${eldijet} >datacard_wwgamaqgc_2chan_lt0:${lt0}e-11.txt
done
