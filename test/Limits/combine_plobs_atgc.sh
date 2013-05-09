#!/bin/sh

for datacard in $*
do
#  DIR=`dirname $datacard`
  DIR=.
  COMBINE_ARGS="-v0 -M ProfileLikelihood"

  file=`basename $datacard .txt`
  suffix=${file##datacard_}
  lz=`echo $suffix | egrep -o "lz_[0-9\.\-]+" | sed 's#lz_##g'`

  COMBINE_ARGS="$COMBINE_ARGS -n _atgc_obs_$suffix"
#  COMBINE_ARGS="$COMBINE_ARGS --bruteForce -n _atgc_obs_$suffix"

  echo "combine $COMBINE_ARGS $datacard 2>&1 | tee ${DIR}/limit_${suffix}.log >/dev/null"
  combine $COMBINE_ARGS $datacard 2>&1 | tee ${DIR}/limit_${suffix}.log >/dev/null
done
