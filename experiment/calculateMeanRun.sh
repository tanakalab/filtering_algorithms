#! /bin/bash -

i=250
while [ $i != 260 ]
do
	cat 64_20_${i}_rule.txt | awk '{m+=$1} END{print m/NR;}'
	cat 64_20_${i}_node.txt | awk '{m+=$1} END{print m/NR;}'
	cat 64_20_${i}_ctime.txt | awk '{m+=$1} END{print m/NR;}'
	cat 64_20_${i}_cmem.txt | awk '{m+=$1} END{print m/NR;}'
	cat 64_20_${i}_stime.txt | awk '{m+=$1} END{print m/NR;}'
	echo $((i+=10))
	echo -e '\n'
done
