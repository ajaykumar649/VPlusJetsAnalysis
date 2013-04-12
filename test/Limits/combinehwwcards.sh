#!/bin/bash

cfgtag=130320noncheating

#for mass in 180 190 200 250 300 350 400 450 500 550 600
for mass in 500
do
  el2jet=datacard_8TeV_hwwelnu2j_${cfgtag}-M-${mass}.txt
  mu2jet=datacard_8TeV_hwwmunu2j_${cfgtag}-M-${mass}.txt
  echo "combineCards.py mu2jet=${mu2jet} el2jet=${el2jet} >datacard_8TeV_hww2chan_${cfgtag}-M=${mass}.txt"
  combineCards.py mu2jet=${mu2jet} el2jet=${el2jet} >datacard_8TeV_hww2chan_${cfgtag}-M=${mass}.txt
done
