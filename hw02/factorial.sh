#!/bin/bash
# It will calculate the factorial of a supplied number.
# Author: Yuege Xie

# check the number of arguments
if [ $# -lt 1 ];then
	echo "Error! Please input at least one number to get its factorial."
	exit
elif [ $1 -lt 0 ];then
	echo "Error! Please input a nonnegative number."
	exit
else 
	# initialize
	fact=1
	i=$1
	
	# do while loop to get result
	while [ $i -gt 1 ]
		do
			fact=$(expr $fact \* $i)
			i=$(expr $i - 1) 
		done
	# output
	echo $fact
fi

