#!/bin/bash

if [ $# -lt 2 ]
then
    DIR=.
else
    DIR=$2
fi


if stat -t ${DIR}/datacard_${1}[-_]M=??0.txt >/dev/null 2>&1
then
    for datacard in ${DIR}/datacard_${1}[-_]M=??0.txt
    do
      DIR=`dirname $datacard`
      file=`basename $datacard .txt`
      suffix=${file##datacard_}
      mass=`ls $datacard | egrep -o "M=[0-9]+" | egrep -o "[0-9]+"`
      echo "text2workspace.py -m $mass $datacard -b -o wkspace_${1}_M=${mass}.root"
#     text2workspace.py -m $mass $datacard -b -o wkspace_${1}_M=${mass}.root

      sed "s#model.root#wkspace_${1}_M=${mass}.root#g;s#log.txt#limit_${1}_M=${mass}.log#g" combine_crab.sh >combine_crab_${1}_M=${mass}.sh
      sed "s#model.root#wkspace_${1}_M=${mass}.root#g;s#log.txt#limit_${1}_M=${mass}.log#g;s#combine_crab#combine_crab_${1}_M=${mass}#g" combine_crab.cfg >combine_crab_${1}_M=${mass}.cfg
    done
fi
