#!/bin/bash

module load launcher

# add headings of out put
echo "# num_samples num_i pi_estimate relative_error time_accum" > iter.log

/bin/time -o time.log -f '%e' sbatch launcher.slurm
/bin/time -o time.log -f '%e' sbatch launcher.slurm

cat tmp.log | grep "^20000000" >> sample.log
cat time.log >> time_accu.log

i=1
num_samples=960000000
num_i=`cat sample.log|awk 'BEGIN{total=0}{total+=$2}END{print total}'`
pi_estimate=$(echo "scale=18; $num_i/960000000*4" | bc -l)
e_rel=$(echo "scale=6; $pi_estimate/3.141592653589793238-1" | bc -l)
time_accum=`cat time_accu.log | awk 'BEGIN{total=0}{total+=$1}END{print total}' `

# get absolute value of relative error
if [ $(echo "$e_rel < 0" | bc) -eq 1 ];then
        e_rel=$(echo "scale=4; 0 - $e_rel" | bc -l)
fi

echo $i $num_samples $num_i $pi_estimate $e_rel $time_accum >> ./iter.log
