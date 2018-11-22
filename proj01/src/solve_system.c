#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "error_norm.h"

void solve_system(int n, char* iter_method)
{
	/* Variable needed: n, iter_method */
	int i, j, k;
	double diag;
	double *dz, *z;
	dz = (double*) mcalloc(n*sizeof(double));
	z  = (double*) mcalloc(n*sizeof(double));
	
	/* Solve linear system using Jacobi iteration */
	if(iter_method == 'Jacobi')
	{
		for(k=1; k<max_iter; k++)
		{
			for(i=0; i<n; i++)
			{
				dz[i] = b[i];
				for(j=0; j<A.nonzero[i]; j++)
				{
					if(A.col[i][j]!=i)
						dz[i] -= A.val[i][j] * x[A.col[i][j]];
					else
						diag   = A.val[i][j];
				}
				dz[i] = dz[i] / diag; 
			}	
		
			if(error_norm(*z,*dz, n)<= eps) 
				break;
			else  //how to assign value?
				for(i=0; i<n; i++)
					z[i] = dz[i];
		}
		/*??? Free memory*/	
		free(z);
		free(dz);
	}

	/* Solve linear system using Gauss-Seidel iteration */
	if(iter_method == 'Gauss_Seidel')
	{
		for(k=1; k<max_iter; k++)
		{
			for(i=0; i<n; i++)
			{
				dz[i] = b[i];
				for(j=0; j<A.nonzero[i]; j++)
				{
					if(A.col[i][j]<i)
						dz[i] -= A.val[i][j] * dx[A.col[i][j]];
					else if(A.col[i][j]>i)
						dz[i] -= A.val[i][j] * x[A.col[i][j]];
					else
						diag   = A.val[i][j];	
				}
				dz[i] = dz[i] / diag; 
			}	
		
			if(error_norm(*z,*dz, n)<= eps) 
				break;
			else  //how to assign value?
				for(i=0; i<n; i++)
					z[i] = dz[i];
		}
		/*??? Free memory*/	
		free(z);
		free(dz);
	}
}
