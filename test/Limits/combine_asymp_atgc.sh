#!/bin/sh

for datacard in $*
do
#  DIR=`dirname $datacard`
  DIR=.
  COMBINE_ARGS="-v0 -M Asymptotic --minosAlgo stepping"

  file=`basename $datacard .txt`
  suffix=${file##datacard_}
  lz=`echo $suffix | egrep -o "lz_[0-9\.\-]+" | sed 's#lz_##g'`

  COMBINE_ARGS="$COMBINE_ARGS -n _atgc_$suffix"

  if [ `echo "scale=4; $lz >= 0.1 || $lz <= -0.1" | bc ; exit` ]
  then
      COMBINE_ARGS="$COMBINE_ARGS --rMax=0.5"
  fi

  echo "combine $COMBINE_ARGS $datacard 2>&1 | tee ${DIR}/limit_${suffix}.log >/dev/null"
  combine $COMBINE_ARGS $datacard 2>&1 | tee ${DIR}/limit_${suffix}.log >/dev/null
done
