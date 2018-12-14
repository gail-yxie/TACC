#!/bin/bash

executable="../src/solver"

# verify 2d 2nd jacobi
$executable input.2d.2nd.jacobi
h5diff --delta=1.0E-8 ref_2d_2nd_jacobi.h5 sol.dat T_sol T_sol
if [ $(echo $?) -ne 0 ]; then
	echo "Error: error norm is too large!"
	exit 1
fi
