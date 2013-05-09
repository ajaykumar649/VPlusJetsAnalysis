#!/bin/bash
SRCDIR=/uscms/home/pdudero/work/CMSSW_6_1_1/src/ElectroWeakAnalysis/VPlusJets/test/Limits
executable=${SRCDIR}/batchit.sh
#cmbscript1=${SRCDIR}/combine_plobs_atgc.sh
#cmbscript2=${SRCDIR}/combine_plexp_atgc.sh
cmbscript1=${SRCDIR}/combine_asymp_atgc.sh
#cmbscript1=${SRCDIR}/combine_fc_atgc.sh

if [ $# -lt 1 ]
then
    echo "Usage: $0 datacard*.txt"
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
echo "lzlist =" $lzlist
if [[ "$lzlist" != "" ]]
then
    for lz in $lzlist
    do
      arglist=`ls $* | grep "datacard_lz_${lz}"|xargs`
      xferlist=`echo $arglist|sed 's# #,#g'`
  # echo "transfer_input_files = $xferlist,el_dijet.root,el_boosted.root,mu_dijet.root,mu_boosted.root" >>$submit
      echo "transfer_input_files = $xferlist,el_boosted.root,mu_boosted.root" >>$submit
      echo "Error = atgclimit_lz${lz}.err" >>$submit
      echo "Output = atgclimit_lz${lz}.out" >>$submit
      echo "Arguments = $cmbscript1 $arglist" >>$submit
      echo "Queue" >>$submit
      
      if [[ "$cmbscript2" != "" ]]
      then
	  if [[ `echo "scale=4; $lz <= 0.003 && $lz >= -0.004" | bc` -ne 0 ]]
	  then
              # for these, allocate one file per job
	      filelist=`ls $* | grep "_\$lz"`
	      for file in $filelist
              #for file in $*
	      do
		base=`basename $file .txt`
		suffix=${basedatacard_}
		echo "transfer_input_files = $file,el_boosted.root,mu_boosted.root" >>$submit
		echo "Error = atgclimit_${suffix}_exp.err" >>$submit
		echo "Output = atgclimit_${suffix}_exp.out" >>$submit
		echo "Arguments = $cmbscript1 $file" >>$submit
		echo "Queue" >>$submit
	      done
	  else
	      echo "transfer_input_files = $xferlist,el_boosted.root,mu_boosted.root" >>$submit
	      echo "Error = atgclimit_lz${lz}_exp.err" >>$submit
	      echo "Output = atgclimit_lz${lz}_exp.out" >>$submit
	      echo "Arguments = $cmbscript2 $arglist" >>$submit
	      echo "Queue" >>$submit
	  fi
      fi
    done
else
    for file in $*
    do
      base=`basename $file .txt`
      suffix=${basedatacard_}
      echo "transfer_input_files = $file,el_boosted.root,mu_boosted.root" >>$submit
      echo "Error = atgclimit_${suffix}_exp.err" >>$submit
      echo "Output = atgclimit_${suffix}_exp.out" >>$submit
      echo "Arguments = $cmbscript1 $file" >>$submit
      echo "Queue" >>$submit
    done
fi


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
