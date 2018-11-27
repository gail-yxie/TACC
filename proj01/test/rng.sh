#!/bin/bash

executable="../src/solver"

# verify executable exists
if [ ! -x "$executable" ]; then
	echo "Error: expecting executable -> $executable"
	exit 1
fi

err_ref=0.001

# verify 1d 2nd jacobi
$executable input.dat
./check_error 129 sol.dat ref.txt > .tmp_output
err="$(cat .tmp_output)"
if [ $(echo "$err <= $err_ref" | bc -l) = 0 ]; then
	echo "Error: error norm is too large!"
	exit 1
fi

 
