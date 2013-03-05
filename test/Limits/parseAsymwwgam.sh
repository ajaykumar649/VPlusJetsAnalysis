#!/bin/bash

DIR=`dirname $1`
file=`basename $1 .log`
suffix=${file##limit_}
suffix=${suffix%%:[0-9e-]*}

echo "var   obsLimit        exp95lo         exp68lo         expLimit        exp68hi         exp95hi" | tee ${DIR}/limit_${suffix}.tab

for i in $*; do
    file=`basename $i .log`
    dc=`echo $file | egrep -o ":[0-9e-]+" | egrep -o "[0-9e-]+"`
    line=`grep "r <" $i | sed 's#.*r < ##g' | transpose.pl`
    echo "$dc	$line"
done 2>&1 | tee -a ${DIR}/limit_${suffix}.tab
