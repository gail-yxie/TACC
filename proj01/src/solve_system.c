#include <stdio.h>
#include <stdlib.h>
#include "parameter.h"
#include "function.h"

void solve_system(Parameter* solver)
{
	/* Variable needed: n, iter_method */
	int i, j, k;
	double diag;
	double n = solver.n;

	/* Ask for dynamic memory */
	double* dz;	
	dz = (double*)malloc(n*sizeof(double));
	solver.z  = (double*)malloc(n*sizeof(double));
	
	/* Solve linear system using Jacobi iteration */
	if(solver.iter_method == 1)
	{	
		for(i=0;i<n;i++)
			solver.z[i] = solver.b[i];	
		for(k=0; k<solver.max_iter; k++)
		{
			for(i=0; i<n; i++)
			{
				dz[i] = solver.b[i];
				for(j=0; j<solver.A.nonzero[i]; j++)
				{
					if(solver.A.col[i][j]!=i)
						dz[i] -= solver.A.val[i][j] * solver.z[solver.A.col[i][j]];
					else
						diag   = solver.A.val[i][j];
				}
				dz[i] = dz[i] / diag; 
			}	
		
			if(error_norm(solver.z,dz,n)< solver.eps)
				break;
			else
				for(i=0; i<n; i++)
					solver.z[i] = dz[i];
		}
	}

	/* Solve linear system using Gauss-Seidel iteration */
	if(iter_method == 'Gauss_Seidel')
	{
		for(k=0; k<max_iter; k++)
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
	}
}
