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

#SBATCH --mail-user=yuege@ices.utexas.edu
#SBATCH --mail-type=begin

echo "Master Host = "'hostname'
echo "PWD_DIR: "'pwd'

# run for different n
./pi.sh 10
./pi.sh 100
./pi.sh 500
./pi.sh 1000
./pi.sh 5000
./pi.sh 10000
./pi.sh 50000

{ time ./pi.sh 10 ;} 2> batch1_time.txt
{ time ./pi.sh 100 ;} 2>> batch1_time.txt
{ time ./pi.sh 500 ;} 2>> batch1_time.txt
{ time ./pi.sh 1000 ;} 2>> batch1_time.txt
{ time ./pi.sh 5000 ;} 2>> batch1_time.txt
{ time ./pi.sh 10000 ;} 2>> batch1_time.txt
{ time ./pi.sh 50000 ;} 2>> batch1_time.txt
