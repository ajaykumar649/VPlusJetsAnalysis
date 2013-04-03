#!/usr/bin/env perl
if (@ARGV == 1) {
    $file=shift;
    open(STDIN,"<$file") or die "can not open file";
#   print "Usage: $0 <filename>\n";
#   exit(1);
}

$col=0;
$row=0;
while(<>){
        $_=~ tr/\n//d;
        @arr=split(",",$_);
	if ($#arr==-1) {
	    for($a=0;$a<=$col;$a++) {
		for($b=1;$b<=$row;$b++){
		    $t=sprintf("%s%s",$b,$a);
		    print $hash{$t},"\t";
		}
		print "\n";
	    }
	    $row=0;
	    %hash=();
	    print "\n";
	} else {
	    $col=$#arr;
	    $row++;
#	    print "$col\n";
	    for($i=0;$i<=$#arr;$i++){
                $index=sprintf("%s%s",$row,$i);
                $hash{$index}=$arr[$i];
#		print "$arr[$i]\t";
	    }
#	    print "\n";
	}
}
for($a=0;$a<=$col;$a++) {
    for($b=1;$b<=$row;$b++){
	$t=sprintf("%s%s",$b,$a);
	print $hash{$t},"\t";
    }
    print "\n";
}
close(STDIN);
