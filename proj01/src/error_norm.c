#include <stdio.h>
#include <math.h>
#include "parameter.h"

double error_norm(double* x, double* y, int n, int act_n)
{
	double error;

	for(int i=0;i<solver.n;i++)
		error = error + (x[i] - y[i]) * (x[i] - y[i]); 
	
	error = sqrt(error/act_n);
	
	return error;
}
