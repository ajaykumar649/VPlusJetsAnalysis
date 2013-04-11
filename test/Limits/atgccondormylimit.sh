#!/bin/bash
#SRCDIR=/uscms/home/pdudero/work/CMSSW_5_3_3_patch3/src/ElectroWeakAnalysis/VPlusJets/test/Limits/
SRCDIR=/uscms/home/pdudero/work/CMSSW_6_1_1/src/Limits/
executable=${SRCDIR}/combine_asymp_atgc_batch.sh
cmbscript=${SRCDIR}/combine_asymp_atgc.sh
#executable=${SRCDIR}/combine_fc_atgc_batch.sh
#cmbscript=${SRCDIR}/combine_fc_atgc.sh

if [ $# -lt 1 ]
then
    echo "Usage: $0 datacard*lz*.txt"
    exit
fi

submit=submit.txt

printheader() {
cat >$submit <<EOF
Executable = $executable
Universe = vanilla
Requirements = Memory > 250 && FileSystemDomain=="fnal.gov" && Disk > 500000 && Arch=="X86_64"
Should_Transfer_Files = YES
WhenToTransferOutput = ON_EXIT
EOF
}

printheader

lzlist=`ls $* | egrep -o "lz_[0-9\.\-]+" | sed 's#lz_##g'|sort -u`
for lz in $lzlist
do
  arglist=`ls ${PWD}/datacard*_lz_${lz}*.txt|xargs`
  xferlist=`echo $arglist|sed 's# #,#g'`
  echo "transfer_input_files = $xferlist,el_dijet.root,el_boosted.root,mu_dijet.root,mu_boosted.root,${cmbscript}" >>$submit
  echo "Error = atgclimit_lz${lz}.err" >>$submit
  echo "Output = atgclimit_lz${lz}.out" >>$submit
  echo "Arguments = $arglist" >>$submit
  echo "Queue" >>$submit
done

# for dc in $*
# do
#   file=`basename $dc .txt`
#   suffix=${file##datacard_}
#   echo "transfer_input_files = $dc,el_dijet.root,el_boosted.root,mu_dijet.root,mu_boosted.root,${cmbscript}" >>$submit
# #  echo "transfer_input_files = $dc,el_noBtag.root,mu_noBtag.root,${cmbscript}" >>$submit
#   echo "Error  = limit_${suffix}.log" >>$submit
#   echo "Output = limit_${suffix}.log" >>$submit
#   echo "Arguments = $dc" >>$submit
#   echo "Queue" >>$submit
# done
