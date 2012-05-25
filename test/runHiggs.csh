set syst=0
#echo "number of args: $#argv"
if ($#argv > 0) then 
    set syst=$1
endif

echo "systematic $syst"

#exit 0

foreach mH ( 250 300 350 400 450 500 550 600 )
    echo "Higgs mass: $mH muons 2 jets"
    python runHWWFitter.py -b -m HWWMuonsConfig -j 2 -H $mH -W 0 -s $syst >&! H"$mH"_Muon_2jets_FitterOutput.out
end

foreach mH ( 170 180 )
    echo "Higgs mass: $mH muons 2 jets"
    python runHWWFitter.py -b -m HWWMuonsConfig -j 2 -H $mH -W -1 -s $syst >&! H"$mH"_Muon_2jets_FitterOutput.out
end

foreach mH ( 190 200 )
    echo "Higgs mass: $mH muons 2 jets"
    python runHWWFitter.py -b -m HWWMuonsConfig -j 2 -H $mH -W 1 -s $syst >&! H"$mH"_Muon_2jets_FitterOutput.out
end

foreach mH ( 350 400 450 500 550 600 )
    echo "Higgs mass: $mH muons 3 jets"
    python runHWWFitter.py -b -m HWWMuonsConfig -j 3 -H $mH -W 0 -s $syst >&! H"$mH"_Muon_3jets_FitterOutput.out
end

foreach mH ( 170 180 190 200 )
    echo "Higgs mass: $mH muons 3 jets"
    python runHWWFitter.py -b -m HWWMuonsConfig -j 3 -H $mH -W -1 -s $syst >&! H"$mH"_Muon_3jets_FitterOutput.out
end

foreach mH ( 250 300 )
    echo "Higgs mass: $mH muons 3 jets"
    python runHWWFitter.py -b -m HWWMuonsConfig -j 3 -H $mH -W 5 -s $syst >&! H"$mH"_Muon_3jets_FitterOutput.out
end

foreach mH ( 250 300 350 400 450 500 550 600 )
    echo "Higgs mass: $mH electrons 2 jets"
    python runHWWFitter.py -b -m HWWElectronsConfig -j 2 -H $mH -W 0 -s $syst >&! H"$mH"_Electron_2jets_FitterOutput.out
end

foreach mH ( 170 180 )
    echo "Higgs mass: $mH electrons 2 jets"
    python runHWWFitter.py -b -m HWWElectronsConfig -j 2 -H $mH -W -1 -s $syst >&! H"$mH"_Electron_2jets_FitterOutput.out
end

foreach mH ( 190 200 )
    echo "Higgs mass: $mH electrons 2 jets"
    python runHWWFitter.py -b -m HWWElectronsConfig -j 2 -H $mH -W 1 -s $syst >&! H"$mH"_Electron_2jets_FitterOutput.out
end

foreach mH ( 350 400 450 500 550 600 )
    echo "Higgs mass: $mH electrons 3 jets"
    python runHWWFitter.py -b -m HWWElectronsConfig -j 3 -H $mH -W 0 -s $syst >&! H"$mH"_Electron_3jets_FitterOutput.out
end

foreach mH ( 170 180 190 200 )
    echo "Higgs mass: $mH electrons 3 jets"
    python runHWWFitter.py -b -m HWWElectronsConfig -j 3 -H $mH -W -1 -s $syst >&! H"$mH"_Electron_3jets_FitterOutput.out
end

foreach mH ( 250 300 )
    echo "Higgs mass: $mH electrons 3 jets"
    python runHWWFitter.py -b -m HWWElectronsConfig -j 3 -H $mH -W 5 -s $syst >&! H"$mH"_Electron_3jets_FitterOutput.out
end

echo "non Poisson fractional errors"
grep -i 'Poisson' H???_*_?jets_*out | awk -F '[_ =/]+' '{print $3,$2,$1,$NF}' | sort
