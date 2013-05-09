#!/bin/bash

DIR=`dirname $1`
file=`basename $1 .log`

echo "#lz	dkg	dg1   obsLimit exp95lo exp68lo expLimit exp68hi exp95hi" | tee ${DIR}/limits_atgc.tab

for i in $*; do
    file=`basename $i .log`
    suffix=${file##limit_}
    lz=`echo $suffix | egrep -o "lz_[0-9\.\-]+" | sed 's#lz_##g'`
    dkg=`echo $suffix | egrep -o "dkg_[0-9\.\-]+" | sed 's#dkg_##g'`
    dg1=`echo $suffix | egrep -o "dg1_[0-9\.\-]+" | sed 's#dg1_##g'`
    line=`grep "r <" $i | sed 's#.*r < ##g' | transpose.pl`
    echo "$lz	$dkg	$dg1	$line"
done 2>&1 | tee -a ${DIR}/limits_atgc.tab
