#!/bin/sh

#SRCDIR=/uscms/home/pdudero/work/CMSSW_5_3_3_patch3/src/ElectroWeakAnalysis/VPlusJets/test/Limits/
SRCDIR=/uscms/home/pdudero/work/CMSSW_6_1_1/src/Limits/
cd $SRCDIR
#export SCRAM_ARCH=slc5_amd64_gcc462
export SCRAM_ARCH=slc5_amd64_gcc472
eval `scram runtime -sh`
cd -

./combine_asymp_atgc.sh $*

