#!/bin/bash

#SBATCH -N 1
#SBATCH -n 48
#SBATCH -o tmp.log
#SBATCH -J pibatch3
#SBATCH -p skx-dev
#SBATCH -t 00:15:00
#SBATCH -A cse38018

module load launcher

export LAUNCHER_PLUGIN_DIR=$LAUNCHER_DIR/plugins
export LAUNCHER_RMI=SLURM
export LAUNCHER_SCHED=interleaved
export LAUNCHER_NPROCS=48
export LAUNCHER_JOB_FILE="$PWD/paramlist"
export LAUNCHER_WORKDIR="$PWD"

# add headings of out put
echo "# num_samples num_i pi_estimate relative_error time_accum" >./iter.log

i=0
e_rel_goal=0.000005
e_rel=1 

while [  $(echo "$e_rel > $e_rel_goal"| bc) -eq 1 ]
	do

	$LAUNCHER_DIR/paramrun
	
	i=$(( $i + 1 ))
	
	cat ./tmp.log | grep "^20000000" > ./sample.log
	num_samples=`cat ./sample.log|awk 'BEGIN{total=0}{total+=$1}END{print total}'`
	num_i=`cat ./sample.log|awk 'BEGIN{total=0}{total+=$2}END{print total}'`
	pi_estimate=$(echo "scale=18; $num_i/$num_samples*4" | bc -l)
	e_rel=$(echo "scale=7; $pi_estimate/3.141592653589793238-1" | bc -l)
	time_accum=`cat ./sample.log|awk 'BEGIN{total=0}{total+=$6}END{print total}'`
	
	# get absolute value of relative error
	if [ $(echo "$e_rel < 0" | bc) -eq 1 ];then
        	e_rel=$(echo "scale=7; 0 - $e_rel" | bc -l)
	fi

	echo $i $num_samples $num_i $pi_estimate $e_rel $time_accum >> ./iter.log
	
	done

