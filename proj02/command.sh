#!/bin/bash
# This should work on Stampede2

autoreconf -f -i

export PKGPATH=/work/00161/karl/stampede2/public
export CLASSPATH=/work/00161/karl/stampede2/public
export MODULEPATH=$CLASSPATH/ohpc/pub/modulefiles/:$MODULEPATH

# load fixed toolchain
module swap intel gnu7

# verify the correct version: /work/00161/karl/stampede2/public/ohpc/pub/compiler/gcc/7.1.0/bin/gcc
which gcc

module load hdf5
module load petsc 

# configure 
./configure CC=gcc --with-masa=$PKGPATH/masa-gnu7-0.50 --with-grvy=$PKGPATH/grvy-gnu7-0.34 --with-hdf5=$TACC_HDF5_DIR --enable-coverage

# when choose different option, remeber to use make clean
make clean

# choose PETSC
./configure CC=mpicc --with-masa=$PKGPATH/masa-gnu7-0.50 --with-grvy=$PKGPATH/grvy-gnu7-0.34 --with-hdf5=$TACC_HDF5_DIR --with-petsc=$PETSC_DIR
