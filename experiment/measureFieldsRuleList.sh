#! /bin/bash -

i=200
while [ $i != 2100 ]
do
	j=1
	while [ $j != 11 ]
	do
		../c++/main ../rulelists/32_32_${i}_${j} ../packets/64_10000 > tmp${j}
#		cat tmp${j} | awk 'NR==1' | awk '{ print $NF }' > tmprule${j}
		cat tmp${j} | awk 'NR==2' | awk '{ print $NF }' > tmpnode${j}
		cat tmp${j} | awk 'NR==3' | awk '{ print $NF }' > tmpctime${j}
		cat tmp${j} | awk 'NR==4' | awk '{ print $NF }' > tmpcmem${j}
		cat tmp${j} | awk 'NR==5' | awk '{ print $NF }' > tmpstime${j}
		echo $((j++))
	done
	cat tmpnode* > 32_32_${i}_node.txt
	cat tmpctime* > 32_32_${i}_ctime.txt
	cat tmpcmem* > 32_32_${i}_cmem.txt
	cat tmpstime* > 32_32_${i}_stime.txt
	rm tmp*
	echo $((i+=100))
done
