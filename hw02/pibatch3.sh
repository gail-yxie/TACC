#!/bin/bash

module load launcher

# add headings of out put
echo "# num_samples num_i pi_estimate relative_error time_accum" > iter.log

i=0
num_samples=0
e_rel_goal=0.000005
e_rel=1

# clear the log files
rm sample.log
rm time_accu.log
rm time.log
echo "" >  tmp.log

while [  $(echo "$e_rel > $e_rel_goal"| bc) -eq 1 ]
	do

	/bin/time -o time.log -f '%e' sbatch launcher.slurm

	while [ `cat tmp.log| tail -1| grep "exit"|wc -l` -ne 1 ]
		do
		sleep 10
		done	
	cat tmp.log | grep "^20000000" >> sample.log
	cat time.log >> time_accu.log
	
	i=$(( $i + 1 ))
	num_samples=$(( $num_samples + 960000000 ))
 	
	num_i=`cat sample.log|awk 'BEGIN{total=0}{total+=$2}END{print total}'`
	pi_estimate=$(echo "scale=18; $num_i/$i/960000000*4" | bc -l)
	e_rel=$(echo "scale=6; $pi_estimate/3.141592653589793238-1" | bc -l)
	time_accum=`cat time_accu.log | awk 'BEGIN{total=0}{total+=$1}END{print total}' `
	
	# get absolute value of relative error
	if [ $(echo "$e_rel < 0" | bc) -eq 1 ];then
        	e_rel=$(echo "scale=4; 0 - $e_rel" | bc -l)
	fi

	echo $i $num_samples $num_i $pi_estimate $e_rel $time_accum >> ./iter.log
	
	done

