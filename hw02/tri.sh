#!/bin/bash
# It will generate triangles for numbers and dots
# Author: Yuege Xie

for (( i=1;i<=10;i=i+1 ))

	do

	# generate the first triangle
	if [ $i -le 5 ]; then
		# calculate the number of " "
		res=$(( 5 - $i ))
		printf " %.0s" $(seq 0 $res)
		printf "$i %.0s" $(seq 1 $i)
	        printf "\n"

        # print the second triangle
	else
		# calculate the number of " " and .
		res=$(( 10 - $i ))
		num=$(( $i - 5 ))
		printf ' %.0s' $(seq 0 $res)
		printf '. %.0s' $(seq 1 $num)
 		printf "\n"
	fi
	
	done
