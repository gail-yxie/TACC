#!/bin/bash

if [ -d "time_record" ];then
	rm -rf time_record
fi

mkdir time_record
sed -i "23s/.*/fd_method   = 2/" time.input

echo "start Jacobi..."
# Jacobi
sed -i "24s/.*/iter_method = 1/" time.input
for i in 1 2; do
  echo "---$i D---"
  sed -i "13s/.*/dimensions  = $i/" time.input

  filename=$(echo "./time_record/record_${i}D_jacobi")

  for j in `seq 1 12`; do
    sed -i "18s/.*/N    = $(($j*30))/" time.input

    /bin/time -f %e -o $filename --append ./src/solver time.input > /dev/null
    echo $j
  done
done

echo "start Gauss..."
# Gauss Seidel
sed -i "24s/.*/iter_method = 2/" time.input

for i in 1 2; do
  echo "---$i D---"
  sed -i "13s/.*/dimensions  = $i/" time.input

  filename=$(echo "./time_record/record_${i}D_gauss")

  for j in `seq 1 12`; do
    sed -i "18s/.*/N    = $(($j*30))/" time.input

    /bin/time -f %e -o $filename --append ./src/solver time.input > /dev/null
    echo $j
  done
done

echo "Start GMRES..."
# GMRES
sed -i "24s/.*/iter_method = 3/" time.input

for i in 1 2; do
  echo "---$i D---"
  sed -i "13s/.*/dimensions  = $i/" time.input

  filename=$(echo "./time_record/record_${i}D_gmres")

  for j in `seq 1 12`; do
    sed -i "18s/.*/N    = $(($j*30))/" time.input

    /bin/time -f %e -o $filename --append mpirun -np 1 ./src/solver input.dat > /dev/null
    echo $j
  done
done 
