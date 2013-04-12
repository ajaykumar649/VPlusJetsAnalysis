#!/bin/bash

DIR=`dirname $1`
file=`basename $1 .log`
suffix=${file##limit_}
suffix=${suffix%%[-_]M=[0-9]*}

echo "hmass    obs   exp95lo  exp68lo   exp  exp68hi  exp95hi" | tee ${DIR}/limit_${suffix}.tab

for i in $*; do
    file=`basename $i .log`
    dc=`echo $file | egrep -o "M=[0-9]+" | egrep -o "[0-9]+"`
    line=`grep "r <" $i | sed 's#.*r < ##g' | transpose.pl`
    echo "$dc	$line"
done 2>&1 | tee -a ${DIR}/limit_${suffix}.tab
