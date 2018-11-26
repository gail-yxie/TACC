#include "function.h"

void solve_system(struct Parameter* solver)
{
	grvy_timer_begin(__func__);
	/* Variable needed: n, iter_method */
	int i, j, k;
	double diag = 1;
	int n = solver->n;
	double tmp;

	/* Ask for dynamic memory */
	double* old_z;	
	old_z = (double*)malloc(n*sizeof(double));
	solver->z  = (double*)malloc(n*sizeof(double));
	
	/* Solve linear system using Jacobi iteration */
	if(solver->iter_method == 1)
	{	
		for(i=0;i<n;i++)
			old_z[i] = 0;	
		for(k=0;k<solver->max_iter;k++)
		{
			for(i=0;i<n;i++)
			{
				tmp = solver->b[i];
				for(j=0;j<solver->nonzero[i];j++)
				{
					if(solver->col[i][j]!=i)
						tmp  = tmp - solver->val[i][j] * old_z[solver->col[i][j]];
					else
						diag = solver->val[i][j];
				}
				solver->z[i] = tmp / diag; 
			}	
			/* Here act_n equals to n */
			if(error_norm(solver->z, old_z, n) < solver->eps)
				break;
			else
				for(i=0;i<n;i++)
					old_z[i] = solver->z[i];
		}
		free(old_z);
	}

	/* Solve linear system using Gauss-Seidel iteration */
	else if(solver->iter_method == 2)
	{
		for(i=0;i<n;i++)
		{
			solver->z[i] = 0;
			old_z[i]     = 0;
		}
		for(k=0;k<solver->max_iter;k++)
		{
			for(i=0;i<n;i++)
			{
				tmp = solver->b[i];
				for(j=0;j<solver->nonzero[i];j++)
				{
					if(solver->col[i][j]!=i)
						tmp  = tmp - solver->val[i][j] * solver->z[solver->col[i][j]];
					else
						diag = solver->val[i][j];	
				}
				solver->z[i] = tmp / diag;
			}	
		
			if(error_norm(solver->z, old_z, n) < solver->eps)
				break;
			else
				for(i=0;i<n;i++)
					old_z[i] = solver->z[i];
		}
		free(old_z);
	}
	grvy_timer_end(__func__);
}
