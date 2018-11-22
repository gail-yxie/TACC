#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "error_norm.h"

void solve_system()
{
	/* Variable needed: n, iter_method */
	int i, j, k;
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
				}
				dz[i] = dz[i] / A.val[i][]; 
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
	

}

