#!/bin/sh

COMBINE_ARGS="-v0 -M Asymptotic --minosAlgo stepping"

for datacard in $*
do
#  DIR=`dirname $datacard`
  DIR=.
  file=`basename $datacard .txt`
  suffix=${file##datacard_}

  echo "combine $COMBINE_ARGS -n _$suffix $datacard > ${DIR}/limit_${suffix}.log 2>&1"

#  a0w=`echo $suffix | egrep -o "a0w=[0-9\.\-]+" | sed 's#a0w=##g'`
#  if [ `echo "scale=4; $lz >= 0.36 || $lz <= -0.36" | bc ; exit` ]
#  then
#      combine $COMBINE_ARGS --rMax=0.5 -n _$suffix $datacard > ${DIR}/limit_${suffix}.log 2>&1
#  else

  combine $COMBINE_ARGS -n _$suffix $datacard > ${DIR}/limit_${suffix}.log 2>&1

#  fi
done
