#include "function.h"

double error_norm(double* vecx, double* vecy, int vecn)
{
	double error = 0;

	for(int i=0;i<vecn;i++)
		error = error + (vecx[i] - vecy[i]) * (vecx[i] - vecy[i]); 
	
	error = sqrt(error/vecn);
	
	return error;
}
