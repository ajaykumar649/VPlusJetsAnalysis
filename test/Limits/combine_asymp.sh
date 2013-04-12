#!/bin/sh

if [ $# -lt 1 ]
then
    echo "Usage: $0 <datacards>"
    exit
fi

#COMBINE_ARGS="-v0 -n HWW2lnujjObs -M Asymptotic --minosAlgo stepping --rMin=0.1 --rMax=5"
COMBINE_ARGS="-v4 -n HWW2lnujjObs -M Asymptotic --minosAlgo stepping"

#for mass in 170 180 190 200 250 300 350 400 450 500 550 600
#for mass in 180 250 400
for datacard in $*
do
  DIR=`dirname $datacard`
  file=`basename $datacard .txt`
  suffix=${file##datacard_}
  mass=`ls $datacard | egrep -o "M=[0-9]+" | egrep -o "[0-9]+"`
#
# "tee" used per recommendation from Giovanni, since it captures the stdout/stderr better than straight redirection;
# the combine tool mucks with the stdout FILE descriptor...
#
  echo "combine $COMBINE_ARGS -m ${mass} $datacard 2>&1 | tee ${DIR}/limit_${suffix}.log >/dev/null"
  combine $COMBINE_ARGS -m ${mass} $datacard 2>&1 | tee ${DIR}/limit_${suffix}.log >/dev/null
#  combine $COMBINE_ARGS -m ${mass} ${DIR}/datacard_${mass}.txt 2>&1 | tee ${DIR}/limit_${mass}.log >/dev/null
#  combine $COMBINE_ARGS -m ${mass} ${DIR}/datacard_mu2jet_${mass}.txt 2>&1 | tee ${DIR}/limit_mu2jet_${mass}.log >/dev/null
#  combine $COMBINE_ARGS -m ${mass} ${DIR}/datacard_withVBF_${mass}.txt 2>&1 | tee ${DIR}/limit_withVBF_${mass}.log >/dev/null
#  combine $COMBINE_ARGS -m ${mass} ${DIR}/datacard_5pctsyst_${mass}.txt 2>&1 | tee ${DIR}/limit_5pctsyst_${mass}.log >/dev/null
#  combine $COMBINE_ARGS -m ${mass} ${DIR}/datacard_milwin_candc_2j_${mass}.txt 2>&1 | tee ${DIR}/limit_milwin_candc_2j_${mass}.log >/dev/null
done
