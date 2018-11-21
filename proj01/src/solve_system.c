#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main(int N, double **val, double *nonzero, double **col, double *b, double eps, int max_iter, double *x)
{

	int i, j, k;
	double *dx, *y;
	dx = (double*) calloc(N, sizeof(double));
	y  = (double*) calloc(N, sizeof(double));
	
	/* Solve linear system using Jacobi iteration */
	if(iter_method == 'Jacobi')

	for(k=1; k<max_iter; k++)
	{
		double sum = 0.0;
		for(i=0; i<=N; i++)
		{
			
			dx[i] = b[i];

			for(j=0; j<=nonzero[i]; j++)
				dx[i] -= val[i][col[i][j]]*x[col[i][j]];

			dx[i] /= val[i][];
			y[i] += dx[i]; 			

		}
		
		if(sum <= eps) break;

	}

	free(dx);
	free(y);

	/* Solve linear system using Gauss Seidel iteration */
	if(iter_method == 'Gauss_Seidel')

	

	return 0;

}


