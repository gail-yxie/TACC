#!/bin/bash
# It will calculate the factorial of a supplied number.

read -p "Pleas input n:" n
fact=1

for (( i=1;i<=n;i++))
	do
		fact=$(expr $fact \* $i) 
	done

echo $fact
