#!/bin/bash
# It will estimate the value of pi using sampling

# define RandomDraw
RandomDraw(){
	echo "scale=15; $RANDOM/32767" | bc -l
}

N_samples=$1
r=$(echo "scale=15; 1/1" | bc -l)
N_i=0
N_o=0

# use for loop to count
for (( i=1;i<=$N_samples;i=i+1 ))
        do
                x=$(RandomDraw)
                y=$(RandomDraw)
		r2=$(echo "scale=15; $x * $x + $y * $y" | bc -l)
                if [ $(echo "$r2 > $r" | bc) -eq 1 ];then
                                N_o=$(( N_o + 1 ))
                fi
        done

# calculate parameters
N_i=$(( $N_samples -  $N_o ))
pi_estimate=$(echo "scale=15; $N_i/$N_samples*4" | bc -l)
e_rel=$(echo "scale=4; $pi_estimate/3.14159265-1" | bc -l)

# get absolute value of relative error
if [ $(echo "$e_rel < 0" | bc) -eq 1 ];then
        e_rel=$(echo "scale=4; 0 - $e_rel" | bc -l)
fi

# output
echo $N_samples $N_i $N_o $pi_estimate $e_rel



