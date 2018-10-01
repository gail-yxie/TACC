#!/bin/bash
# It will calculate the factorial of a supplied number.

# input the supplied number
read -p "Pleas input n:" n

# initialize
fact=1

# use for loop to calculate
for (( i=1;i<=n;i++))
	do
		fact=$(expr $fact \* $i) 
	done

# output
echo $fact
