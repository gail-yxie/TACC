#!/bin/bash
# It will add two integers supplied as command line arguments

# verify the number of variables

# check the number of inputs
if [ $# -lt 2 ]; then
	echo "Please input at least two numbers to do addition."
	exit
else
	# calculate and output the result
	sum=$(( $1 + $2 ))
	echo $sum
fi
