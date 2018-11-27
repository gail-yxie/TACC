#!/bin/bash

echo "" > convergence.txt

# run for different N
for N in 10 20 30 40 60 80 100 120 140 160
	do
    ./solver input.dat $N
    cat sol.dat| grep '' | awk '{print $NF}'
	done
