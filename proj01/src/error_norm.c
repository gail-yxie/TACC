#include <stdio.h>
#include <math.h>

double error_norm(double* z, double* dz, int n)
{
	int i;
	double error;

	for(i=0;i<n;i++)
		error += (z[i] - dz[i]) * (z[i] - dz[i]); 
	
	error = sqrt(error/n);
	
	return error;
}
