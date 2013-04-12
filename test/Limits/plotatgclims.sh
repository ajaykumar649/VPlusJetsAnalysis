#!/bin/bash

if [ $# -lt 1 ]
then
    echo "Usage: $0 glob-pattern-rootfiles(~ expansion is NOT supported)"
    exit
fi

#python make_cls_plot.py -b --input=$1 --par1 lz --par2 dkg --par1Latex '#lambda_{Z}' --par2Latex '#Delta#kappa_{#gamma}'
#python make_cls_plot.py -b --input=$1 --par1 lz --par2 dkg --par1Latex '#lambda' --par2Latex '#Delta#kappa_{#gamma}'
python make_cls_plot.py -b --input=$1 --par1 lz_ --par2 dg1_ --par1Latex '#lambda' --par2Latex '#Delta G1'
