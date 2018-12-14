#!/bin/bash

sed -i "23s/.*/fd_method   = 2/" input.dat

echo "start Jacobi..."
# Jacobi
sed -i "24s/.*/iter_method = 1/" input.dat
for i in 1 2; do
  echo "---$i D---"
  sed -i "13s/.*/dimensions  = $i/" input.dat

  filename=$(echo "./time_record/record_${i}D_jacobi")

  for j in `seq 1 12`; do
    sed -i "18s/.*/N    = $(($j*30))/" input.dat

    /bin/time -f %e -o $filename --append ./solver input.dat > /dev/null
    echo $j
  done
done

echo "start Gauss..."
# Gauss Seidel
sed -i "24s/.*/iter_method = 2/" input.dat

for i in 1 2; do
  echo "---$i D---"
  sed -i "13s/.*/dimensions  = $i/" input.dat

  filename=$(echo "./time_record/record_${i}D_gauss")

  for j in `seq 1 12`; do
    sed -i "18s/.*/N    = $(($j*30))/" input.dat

    /bin/time -f %e -o $filename --append ./solver input.dat > /dev/null
    echo $j
  done
done

echo "Start GMRES..."
# GMRES
sed -i "24s/.*/iter_method = 3/" input.dat

for i in 1 2; do
  echo "---$i D---"
  sed -i "13s/.*/dimensions  = $i/" input.dat

  filename=$(echo "./time_record/record_${i}D_gmres")

  for j in `seq 1 12`; do
    sed -i "18s/.*/N    = $(($j*30))/" input.dat

    /bin/time -f %e -o $filename --append mpirun -np 1 ./solver input.dat > /dev/null
    echo $j
  done
done 
