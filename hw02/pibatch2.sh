#!/bin/bash
# It will run a batch of pi.sh on SLURM

# set the number of nodes
#SBATCH -N 1

# set the number of cores
#SBATCH -n 32

# set output file name
#SBATCH -o pi.compiled.log

# set job name
#SBATCH -J pibatch2

# set submission queue
#SBATCH -p skx-dev

# set Project name
#SBATCH -A cse38018

# set max run time
#SBATCH -t 00:15:00
#SBATCH --mail-user=yuege@ices.utexas.edu
#SBATCH --mail-type=begin

make pi
# run for different n
for n in 10 100 500 1000 5000 10000 50000
        do
                /bin/time -f '%e' ./pi $n
        done
