#!/bin/bash
# It will run a batch of pi.sh on SLURM

# set the number of nodes
#SBATCH -N 2

# set the number of cores
#SBATCH -n 32

# set output file name
#SBATCH -o pi.script.log

# set job name
#SBATCH -J pibatch1

# set submission queue
#SBATCH -p skx-dev

# set Project name
#SBATCH -A cse38018

# set max run time
#SBATCH -t 00:15:00

echo "Master Host = "'hostname'
echo "PWD_DIR: "'pwd'

./pi.sh 
