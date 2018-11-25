#include <stdio.h>
#include <math.h>
#include "parameter.h"

double error_norm(double* x, double* y)
{
	double error;

	for(int i=0;i<solver.n;i++)
		error = error + (x[i] - y[i]) * (x[i] - y[i]); 
	
	error = sqrt(error/n);
	
	return error;
}
