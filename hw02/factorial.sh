#!/bin/bash
# It will calculate the factorial of a supplied number.

# input the supplied number
read -p "Pleas input n:" n

# initialize
fact=1

if [ $n -ge 1 ]
	then
		# use for loop to calculate
		for (( i=1;i<=n;i++))
			do
				fact=$(expr $fact \* $i) 
			done
elif [ $n -lt 0 ]
	then
		fact="Please input a right number."
else
	fact=1
fi

# output
echo $fact
