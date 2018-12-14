#!/bin/bash

executable="../src/solver"

# verify executable exists
if [ ! -x "$executable" ]; then
	echo "Error: expecting executable -> $executable"
	exit 1
fi
