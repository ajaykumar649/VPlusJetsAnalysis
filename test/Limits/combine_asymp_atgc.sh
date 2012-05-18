#!/bin/sh

COMBINE_ARGS="-v0 -M Asymptotic --minosAlgo stepping"

for datacard in $*
do
  DIR=`dirname $datacard`
  file=`basename $datacard .txt`
  suffix=${file##datacard_}
  lz=`echo $suffix | egrep -o "lz[0-9\.\-]+" | sed 's#lz##g'`
  dkg=`echo $suffix | egrep -o "dkg[0-9\.\-]+" | sed 's#dkg##g'`
  echo "combine $COMBINE_ARGS -n _atgc_$suffix $datacard > ${DIR}/limit_${suffix}.log 2>&1"

  if [ `bashcalc.sh "$lz >= 0.36 || $lz <= -0.36"` ]
  then
      combine $COMBINE_ARGS --rMax=0.5 -n _atgc_$suffix $datacard > ${DIR}/limit_${suffix}.log 2>&1
  else
      combine $COMBINE_ARGS -n _atgc_$suffix $datacard > ${DIR}/limit_${suffix}.log 2>&1
  fi
done
