#!/bin/bash
# It will estimate the value of pi using sampling

# define RandomDraw
function RandomDraw(){
	echo "scale=15; $RANDOM/32767" | bc -l
}

RandomDraw
