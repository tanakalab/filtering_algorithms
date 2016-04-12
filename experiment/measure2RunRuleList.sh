#! /bin/bash -

i=140
while [ $i != 150 ]
#while [ $i != 250 ]
do
	j=1
	#while [ $j != 4 ]
	while [ $j != 11 ]
	do
		../c++/main ../rulelists/64_just2_${i}_${j} ../packets/64_10000 > tmp${j}
		cat tmp${j} | awk 'NR==1' | awk '{ print $NF }' > tmpnode${j}
		cat tmp${j} | awk 'NR==2' | awk '{ print $NF }' > tmpctime${j}
		cat tmp${j} | awk 'NR==3' | awk '{ print $NF }' > tmpcmem${j}
		cat tmp${j} | awk 'NR==4' | awk '{ print $NF }' > tmpstime${j}
		echo $((j++))
	done
	cat tmpnode* > 64_just2_${i}_node.txt
	cat tmpctime* > 64_just2_${i}_ctime.txt
	cat tmpcmem* > 64_just2_${i}_cmem.txt
	cat tmpstime* > 64_just2_${i}_stime.txt
	rm tmp*
	echo $((i+=10))
done
