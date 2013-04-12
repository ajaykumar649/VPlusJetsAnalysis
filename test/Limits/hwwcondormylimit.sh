#!/bin/bash
BASEDIR=/uscms/home/pdudero/data/HWW/HWWmvaOptFit130219
SRCDIR=/uscms/home/pdudero/work/CMSSW_5_3_3_patch3/src/ElectroWeakAnalysis/VPlusJets/test/Limits/
submit=condor_submit.txt
executable=${SRCDIR}/hwwrunCombine.sh

printheader() {
cat >$submit <<EOF
Executable = $executable
Universe = vanilla
Requirements = Memory > 250 && FileSystemDomain=="fnal.gov" && Disk > 500000 && Arch=="X86_64"
Should_Transfer_Files = YES
transfer_input_files = $SRCDIR/ggHtable8tev.txt,$SRCDIR/twikiBRtable.txt,$SRCDIR/vbfHtable8tev.txt,$SRCDIR/jetbinerrtable.txt
WhenToTransferOutput = ON_EXIT
EOF
}

printargs() {
    echo "Error = $BASEDIR/limit_M=${mH}.log" >>$submit
    echo "Output = $BASEDIR/limit_M=${mH}.log" >>$submit
    echo "Arguments = $rootf" >>$submit
    echo "Queue" >>$submit
}

printheader
for rootf in $BASEDIR/*.root
  do
  mH=`echo $rootf | egrep -o "HWW[0-9]{3}" | egrep -o "[0-9]{3}"`
  printargs
done

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
