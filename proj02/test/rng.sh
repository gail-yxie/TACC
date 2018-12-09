#!/bin/bash

executable="../src/solver"

# verify executable exists
if [ ! -x "$executable" ]; then
	echo "Error: expecting executable -> $executable"
	exit 1
fi

# verify 1d 2nd jacobi
$executable input.1d.2nd.jacobi
h5diff --use-system-epsilon ref_1d_2nd_jacobi.h5 sol.dat T_sol T_sol
if [ $(echo $?) -ne 0 ]; then
	echo "Error: error norm is too large!"
	exit 1
fi

# verify 1d 2nd gauss
$executable input.1d.2nd.gauss
h5diff --use-system-epsilon ref_1d_2nd_gauss.h5 sol.dat T_sol T_sol
if [ $(echo $?) -ne 0 ]; then
	echo "Error: error norm is too large!"
	exit 1
fi

# verify 1d 4th gauss
$executable input.1d.4th.gauss
h5diff --use-system-epsilon ref_1d_4th_gauss.h5 sol.dat T_sol T_sol
if [ $(echo $?) -ne 0 ]; then
	echo "Error: error norm is too large!"
	exit 1
fi

# verify 2d 2nd jacobi
$executable input.2d.2nd.jacobi
h5diff --use-system-epsilon ref_2d_2nd_jacobi.h5 sol.dat T_sol T_sol
if [ $(echo $?) -ne 0 ]; then
	echo "Error: error norm is too large!"
	exit 1
fi

# verify 2d 2nd gauss
$executable input.2d.2nd.gauss
h5diff --use-system-epsilon ref_2d_2nd_gauss.h5 sol.dat T_sol T_sol
if [ $(echo $?) -ne 0 ]; then
	echo "Error: error norm is too large!"
	exit 1
fi

# verify 2d 4th gauss
$executable input.2d.4th.gauss
h5diff --use-system-epsilon ref_2d_4th_gauss.h5 sol.dat T_sol T_sol
if [ $(echo $?) -ne 0 ]; then
	echo "Error: error norm is too large!"
	exit 1
fi
