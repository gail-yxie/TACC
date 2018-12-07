#!/bin/bash

executable="../src/solver"

# verify executable exists
if [ ! -x "$executable" ]; then
	echo "Error: expecting executable -> $executable"
	exit 1
fi

# verify 1d 2nd jacobi
err_ref_1=0.001
$executable input.1d.2nd.jacobi
./check_error 129 sol.dat ref_1d.txt > .tmp_output
err="$(cat .tmp_output)"
if [ $(echo "$err <= $err_ref_1" | bc -l) = 0 ]; then
	echo "Error: error norm is too large!"
	exit 1
fi

# verify 1d 2nd gauss
$executable input.1d.2nd.gauss
./check_error 129 sol.dat ref_1d.txt > .tmp_output
err="$(cat .tmp_output)"
if [ $(echo "$err <= $err_ref_1" | bc -l) = 0 ]; then
	echo "Error: error norm is too large!"
	exit 1
fi

# verify 1d 4th gauss
err_ref_2=0.0001
$executable input.1d.4th.gauss
./check_error 129 sol.dat ref_1d.txt > .tmp_output
err="$(cat .tmp_output)"
if [ $(echo "$err <= $err_ref_2" | bc -l) = 0 ]; then
	echo "Error: error norm is too large!"
	exit 1
fi

# verify 2d 2nd jacobi
$executable input.2d.2nd.jacobi
./check_error 16641 sol.dat ref_2d.txt > .tmp_output
err="$(cat .tmp_output)"
if [ $(echo "$err <= $err_ref_1" | bc -l) = 0 ]; then
	echo "Error: error norm is too large!"
	exit 1
fi

# verify 2d 2nd gauss
$executable input.2d.2nd.gauss
./check_error 16641 sol.dat ref_2d.txt > .tmp_output
err="$(cat .tmp_output)"
if [ $(echo "$err <= $err_ref_1" | bc -l) = 0 ]; then
	echo "Error: error norm is too large!"
	exit 1
fi

# verify 2d 4th gauss
$executable input.2d.4th.gauss
./check_error 16641 sol.dat ref_2d.txt > .tmp_output
err="$(cat .tmp_output)"
if [ $(echo "$err <= $err_ref_2" | bc -l) = 0 ]; then
	echo "Error: error norm is too large!"
	exit 1
fi
