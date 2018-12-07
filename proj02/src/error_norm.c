#include "function.h"

double error_norm(double* vecx, double* vecy, int vecn)
{
	double error = 0;

	for(int i=0;i<vecn;i++)
		error = error + (vecx[i] - vecy[i]) * (vecx[i] - vecy[i]); 
	
	/* Devide by vecn */
	/* If you want to calculate exact error, please add an additional act_n to be divided */
	error = sqrt(error/vecn);
	
	return error;
}
