#!/bin/bash
#
#
SRCDIR=/uscms/home/pdudero/work/CMSSW_5_3_3_patch3/src/ElectroWeakAnalysis/VPlusJets/test/Limits/

COMBINE_ARGS="-v3 -n HWW2lnujjObs -M Asymptotic --rMin 0.05 --rMax 1.0"

rootf=$1
cd $SRCDIR
eval `scramv1 runtime -sh`
cd -

nametag=fit130219Fansmvacuts

$SRCDIR/makeDataCardFromRooWorkspace.exe $rootf $nametag

if stat -t datacard*${nametag}[-_]M=*.txt
    then
    mH=`echo $datacard*${nametag}*.txt | egrep -o "M=[0-9]{3}" | egrep -o "[0-9]{3}"`
    combine $COMBINE_ARGS -m ${mH} datacard*${nametag}[-_]M=*.txt
else
    echo "Couldn't find datacards"
fi

# ################################################################################
# #   S T A R T    H E R E       S T A R T    H E R E       
# ################################################################################

# for cutvalue in `ls -d $BASEDIR/cutvalue0.* | egrep -o "cutvalue[0-9.]+" | egrep -o "[0-9.]+"`
# do
#   for rootf in $BASEDIR/cutvalue/*.root
#   do
#     runCombine1scanPt
#   done
# done

# do
#   outputfile="explimvscutval-M=${masspt}_${channel}.tab"
#   echo "#Cutval	explim" >$outputfile
#   for cutvalue in `ls -d $BASEDIR/cutvalue=0.* | egrep -o "cutvalue=[0-9.]+" | egrep -o "[0-9.]+"`
#     do
#     LOGFILE=$BASEDIR/cutvalue=${cutvalue}/limit*${channel}*${masspt}*log
#     explim=""
#     if stat -t $LOGFILE >/dev/null 2>&1
#     then
# 	explim=`grep -h "Expected 50" $LOGFILE | egrep -o "r < [0-9.]+" | egrep -o "[0-9.]+"`
#     fi
#     if [ "$explim" = "" ]
#     then
# 	explim=-1
#     fi
#     echo "$cutvalue	$explim" >>$outputfile
#   done
# done
