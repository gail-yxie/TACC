#!/bin/bash
# Author: Yuege Xie

# set the number of nodes
#SBATCH -N 1
# set the number of cores
#SBATCH -n 1 
# set output file name
#SBATCH -o integration.log
# set job name
#SBATCH -J integration
# set submission queue
#SBATCH -p skx-dev
# set Project name
#SBATCH -A cse38018
# set max run time
#SBATCH -t 00:05:00


# run for different methods for different N
for i in 1 2
	do
		for N in 10 20 40 80 160 320 640 1280 2560 5120 10240 20480 40960 81920 163840
			do
	 			./integrate $i $N
			done
	done
