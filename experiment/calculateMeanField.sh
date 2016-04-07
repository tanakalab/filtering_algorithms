#! /bin/bash -

i=1900
while [ $i != 2100 ]
do
	cat 32_32_${i}_node.txt | awk '{m+=$1} END{print m/NR;}'
	cat 32_32_${i}_ctime.txt | awk '{m+=$1} END{print m/NR;}'
	cat 32_32_${i}_cmem.txt | awk '{m+=$1} END{print m/NR;}'
	cat 32_32_${i}_stime.txt | awk '{m+=$1} END{print m/NR;}'
	echo $((i+=100))
	echo -e '\n'
done
