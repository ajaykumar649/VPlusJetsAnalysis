#!/bin/bash
for (( ilz =-30; ilz <=30; ilz++ ))
do
  printf -v lz "%.3f" `echo "scale=3; $ilz/1000." | bc`
  for (( idkg =-10; idkg <=10; idkg++ ))
  do
    printf -v dkg "%.2f" `echo "scale=2; $idkg/100." | bc`
    elboosted=datacard_lz_${lz}_dkg_${dkg}_elboosted.txt
    muboosted=datacard_lz_${lz}_dkg_${dkg}_muboosted.txt
    echo "combineCards.py muboosted=${muboosted} elboosted=${elboosted} >datacard_lz_${lz}_dkg_${dkg}_2chan.txt"
    combineCards.py muboosted=${muboosted} elboosted=${elboosted} >datacard_lz_${lz}_dkg_${dkg}_2chan.txt
  done
  for (( idg1 =-10; idg1 <=10; idg1++ ))
  do
    printf -v dg1 "%.2f" `echo "scale=2; $idg1/100." | bc`
    elboosted=datacard_lz_${lz}_dg1_${dg1}_elboosted.txt
    muboosted=datacard_lz_${lz}_dg1_${dg1}_muboosted.txt
    echo "combineCards.py muboosted=${muboosted} elboosted=${elboosted} >datacard_lz_${lz}_dg1_${dg1}_2chan.txt"
    combineCards.py muboosted=${muboosted} elboosted=${elboosted} >datacard_lz_${lz}_dg1_${dg1}_2chan.txt
  done
done
for (( idkg =-10; idkg <=10; idkg++ ))
do
  printf -v dkg "%.2f" `echo "scale=2; $idkg/100." | bc`
  for (( idg1 =-10; idg1 <=10; idg1++ ))
  do
    printf -v dg1 "%.2f" `echo "scale=2; $idg1/100." | bc`
    elboosted=datacard_dkg_${dkg}_dg1_${dg1}_elboosted.txt
    muboosted=datacard_dkg_${dkg}_dg1_${dg1}_muboosted.txt
    echo "combineCards.py muboosted=${muboosted} elboosted=${elboosted} >datacard_dkg_${dkg}_dg1_${dg1}_2chan.txt"
    combineCards.py muboosted=${muboosted} elboosted=${elboosted} >datacard_dkg_${dkg}_dg1_${dg1}_2chan.txt
  done
done
