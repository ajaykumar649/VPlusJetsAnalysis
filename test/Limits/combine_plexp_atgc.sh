#!/bin/sh

for datacard in $*
do
#  DIR=`dirname $datacard`
  DIR=.
  COMBINE_ARGS="-v0 -M ProfileLikelihood"

  file=`basename $datacard .txt`
  suffix=${file##datacard_}
  lz=`echo $suffix | egrep -o "lz_[0-9\.\-]+" | sed 's#lz_##g'`

  COMBINE_ARGS="$COMBINE_ARGS -n _atgc_exp_$suffix -t 1000 -s -1"

  echo "combine $COMBINE_ARGS $datacard 2>&1 | tee ${DIR}/limit_exp_${suffix}.log >/dev/null"
  combine $COMBINE_ARGS $datacard 2>&1 | tee -a ${DIR}/limit_exp_${suffix}.log >/dev/null
done
