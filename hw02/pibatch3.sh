#!/bin/bash

#SBATCH -N 1
#SBATCH -n 48
#SBATCH -o iter.log
#SBATCH -J pibatch3
#SBATCH -p skx-dev
#SBATCH -t 00:30:00
#SBATCH -A cse38018

module load launcher

PARAMRUN="$TACC_LAUCHER_DIR/paramrun"
export LAUNCHER_PLUGIN_DIR="$TACC_LAUNCHER_DIR/plugins"
export LAUNCHER_WORKDIR="$PWD"
export LAUNCHER_RMI="SLURM"
export LAUNCHER_SCHED="interleaved"

set -u

# Make a list of jobs
PARAM=$(mktemp)
for i in $(seq 1 48)
	do
		echo "echo \"$i\" host \"\$(hostname)\" task \"\$LAUNCHER_TSK_ID\"" >> "$PARAM"
	done

NJOBS=$(wc -l "$PARAM" | awk '{print $1}')

# Launch the jobs

if [ $NJOBS -gt 0 ];then
	export LAUNCHER_JOB_FILE=$PARAM

	if [ $N_JOBS -gt 48 ];then 
		LAUNCHER_PPN=48
	else
		LAUNCHER_PPN=$NJOBS
	fi
	
	export LAUNCHER_PPN

	echo "Starting launcher on $NJOBS jobs"
	$PARAMRUN
	echo "Finished launcher"
else
	echo "Error! No jobs for launcher!"
fi
