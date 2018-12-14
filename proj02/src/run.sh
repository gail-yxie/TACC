#!/bin/bash

sed -i "23s/.*/fd_method   = 2/" input.dat

# Jacobi
sed -i "24s/.*/iter_method = 1/" input.dat
for i in 1 2; do
  sed -i "13s/.*/dimensions  = $i/" input.dat

  filename=$(echo "record_${i}D_jacobi")

  for j in `seq 1 6`; do
    sed -i "18s/.*/N    = $(($j*30))/" input.dat

    /bin/time -f %e -o $filename --append ./solver input.dat > /dev/null
    echo $j
  done
done

# Gauss Seidel
sed -i "24s/.*/iter_method = 2/" input.dat

for i in 1 2; do
  sed -i "13s/.*/dimensions  = $i/" input.dat

  filename=$(echo "record_${i}D_gauss")

  for j in `seq 1 6`; do
    sed -i "18s/.*/N    = $(($j*30))/" input.dat

    /bin/time -f %e -o $filename --append ./solver input.dat > /dev/null
    echo $j
  done
done

# GMRES
sed -i "24s/.*/iter_method = 3/" input.dat

for i in 1 2; do
  sed -i "13s/.*/dimensions  = $i/" input.dat

  filename=$(echo "record_${i}D_gmres")

  for j in `seq 1 6`; do
    sed -i "18s/.*/N    = $(($j*30))/" input.dat

    /bin/time -f %e -o $filename --append mpirun -np 1 ./solver input.dat > /dev/null
    echo $j
  done
done 
