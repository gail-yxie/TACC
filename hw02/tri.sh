#!/bin/bash
# It will generate triangles for numbers and dots
# Author: Yuege Xie

for (( i=1;i<=10;i=i+1 ))
	do
 
	# print the first triangle
	if [ $i -le 5 ]; then
		res=$(( 5 - $i ))
		printf " %.0s" $(seq 0 $res)
		printf "$i %.0s" $(seq 1 $i)
	        printf "\n"
	else
	# print the second triangle
		res=$(( 10 - $i ))
		num=$(( $i - 5 ))
                printf ' %.0s' $(seq 0 $res)
                printf '. %.0s' $(seq 1 $num)
		printf "\n"
	fi
	done
	
