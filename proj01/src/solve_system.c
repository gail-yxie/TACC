#include <stdio.h>
#include <stdlib.h>
#include "parameter.h"
#include "function.h"

void solve_system(Parameter* solver)
{
	/* Variable needed: n, iter_method */
	int i, j, k;
	double diag;
	int n = solver.n;
	double tmp;

	/* Ask for dynamic memory */
	double* dz;	
	dz = (double*)malloc(n*sizeof(double));
	solver.z  = (double*)malloc(n*sizeof(double));
	
	/* Solve linear system using Jacobi iteration */
	if(solver.iter_method == 1)
	{	
		for(i=0;i<n;i++)
			solver.z[i] = 0;	
		for(k=0;k<solver.max_iter;k++)
		{
			for(i=0;i<n;i++)
			{
				tmp = solver.b[i];
				for(j=0;j<solver.A.nonzero[i];j++)
				{
					if(solver.A.col[i][j]!=i)
						tmp  = tmp - solver.A.val[i][j] * solver.z[solver.A.col[i][j]];
					else
						diag = solver.A.val[i][j];
				}
				dz[i] = tmp / diag; 
			}	
			/* Here act_n equals to n */
			if(error_norm(solver.z, dz, n, n) < solver.eps)
			{
				for(i=0;i<n;i++)
					solver.z[i] = dz[i];
				break;
			}
			else
				for(i=0;i<n;i++)
					solver.z[i] = dz[i];
		}
		free(dz);
	}

	/* Solve linear system using Gauss-Seidel iteration */
	if(iter_method == 2)
	{
		for(i=0;i<n;i++)
			solver.z[i] = 0;
		for(k=0;k<solver.max_iter;k++)
		{
			for(i=0;i<n;i++)
			{
				tmp = solver.b[i];
				for(j=0;j<solver.A.nonzero[i];j++)
				{
					if(solver.A.col[i][j]<i)
						tmp  = tmp - solver.A.val[i][j] * dz[A.col[i][j]];
					else if(A.col[i][j]>i)
						tmp  = tmp - solver.A.val[i][j] * solver.z[A.col[i][j]];
					else
						diag = solver.A.val[i][j];	
				}
				dz[i] = tmp / diag;
			}	
		
			if(error_norm(solver.z, dz, n, n) < eps)
			 	/* If the error_norm is less than eps, then break. */
				for(i=0;i<n;i++)
					solver.z[i] = dz[i];
				break;
			else
				for(i=0;i<n;i++)
					solver.z[i] = dz[i];
		}
		free(dz);
	}
}
