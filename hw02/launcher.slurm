#!/bin/bash

#SBATCH -N 1
#SBATCH -n 48
#SBATCH -o tmp.log
#SBATCH -J pibatch3
#SBATCH -p skx-dev
#SBATCH -t 00:01:00
#SBATCH -A cse38018

export LAUNCHER_PLUGIN_DIR=$LAUNCHER_DIR/plugins
export LAUNCHER_RMI=SLURM
export LAUNCHER_SCHED=interleaved
export LAUNCHER_NPROCS=48
export LAUNCHER_JOB_FILE="$PWD/paramlist"
export LAUNCHER_WORKDIR="$PWD"

$LAUNCHER_DIR/paramrun
