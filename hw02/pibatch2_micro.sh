#!/bin/bash
#It will run a batch of pi.sh on SLURM

# set the number of nodes
#SBATCH -N 1

# set the number of cores
#SBATCH -n 32

# set output file name
#SBATCH -o pi.compiled.micro.log

# set job name
#SBATCH -J pibatch2_micro

# set submission queue
#SBATCH -p skx-dev

# set Project name
#SBATCH -A cse38018

# set max run time
#SBATCH -t 00:10:00
#SBATCH --mail-user=yuege@ices.utexas.edu
#SBATCH --mail-type=begin

g++ -std=c++11 -o pi pi.cpp

# run for different n
for n in 10 100 500 1000 5000 10000 50000
        do
                ./pi_micro $n
        done
