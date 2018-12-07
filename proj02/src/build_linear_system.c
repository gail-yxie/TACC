#include "function.h"

void build_linear_system(struct Parameter* solver)
{
	grvy_timer_begin(__func__);

	int i;
	int j;
 	int l;

	double con = -solver->k/(solver->h*solver->h);
	int N = solver->N;
	
	if(solver->output_mode != 0)
	{
		printf("\n\n** Building linear system...\n");
		printf("   --> Enforcing analytic Dirichlet BCs using MASA (%dD)\n", solver->dimensions);
	}
	
	if(solver->dimensions == 1)
	{
		if(solver->fd_method == 2)
		{	
			double v1d2nd[3] = {con, -2*con, con};
			
			/* Define matrix */	
			solver->nonzero = (int*)malloc(sizeof(int)*(N+1));
			solver->col = (int**)malloc(sizeof(int*)*(N+1));
			solver->val = (double**)malloc(sizeof(double*)*(N+1));
	
			for(i=0;i<N+1;i++)
			{
				solver->col[i] = (int*)malloc(sizeof(int) * 3);
				solver->val[i] = (double*)malloc(sizeof(double) * 3);
			}
	 
			for(i=0;i<N+1;i++)
			{	
				if((i==0)||(i==N))
				{
					solver->nonzero[i] = 1;
        	                        solver->col[i][0]  = i;
	                                solver->val[i][0]  = 1;
				}	
				else
				{
					solver->nonzero[i] = 3;
					for(j=0;j<solver->nonzero[i];j++)
					{
						solver->col[i][j] = i-1+j;
						solver->val[i][j] = v1d2nd[j];
					}
				}
			}
		}

		if(solver->fd_method == 4)
		{
			double v1d4th[5] = {-1.0/12*con, 4.0/3*con, -5.0/2*con, 4.0/3*con, -1.0/12*con};
				
			/* Define matrix */	
			solver->nonzero = (int*)malloc(sizeof(int)*(N+1));
			solver->col = (int**)malloc(sizeof(int*)*(N+1));
			solver->val = (double**)malloc(sizeof(double*)*(N+1));
			
			for(i=0;i<N+1;i++)
			{
				solver->col[i] = (int *)malloc(sizeof(int) * 5);
				solver->val[i] = (double *)malloc(sizeof(double) * 5);
			}

			for(i=0;i<=N;i++)
			{
				if((i==0)||(i==1)||(i==N-1)||(i==N))
				{
					solver->nonzero[i] = 1;
					solver->col[i][0]  = i;
					solver->val[i][0]  = 1;
				}
				else
				{
					solver->nonzero[i] = 5;
					for(j=0;j<solver->nonzero[i];j++)
					{
						solver->col[i][j] = i-2+j;
						solver->val[i][j] = v1d4th[j];
					}
				}
			}
		}
	}

	if(solver->dimensions == 2)
	{
		if(solver->fd_method == 2)
		{
			double v2d2nd[5] = {con, con, -4*con, con, con};
			
			/* Define matrix */	
			solver->nonzero = (int*)malloc(sizeof(int)*(N+1)*(N+1));
			solver->col = (int**)malloc(sizeof(int*)*(N+1)*(N+1));
			solver->val = (double**)malloc(sizeof(double*)*(N+1)*(N+1));
			
			for(i=0;i<(N+1)*(N+1);i++)
			{
				solver->col[i] = (int *)malloc(sizeof(int) * 5);
				solver->val[i] = (double *)malloc(sizeof(double) * 5);
			}

			for(l=0;l<=N;l++)
			{
				if((l==0)||(l==N))
				{
					for(i=0;i<=N;i++)
					{ 
						solver->nonzero[l*(N+1)+i] = 1;
						solver->col[l*(N+1)+i][0]  = l*(N+1)+i;
						solver->val[l*(N+1)+i][0]  = 1;
					}
				}
				else
				{
					for(i=0;i<=N;i++)
					{
						if((i==0)||(i==N))
						{
							solver->nonzero[l*(N+1)+i] = 1;
							solver->col[l*(N+1)+i][0]  = l*(N+1)+i;
							solver->val[l*(N+1)+i][0]  = 1;
						}
						else
						{
							solver->nonzero[l*(N+1)+i] = 5;
							solver->col[l*(N+1)+i][0]  = (l-1)*(N+1)+i;
							solver->col[l*(N+1)+i][4]  = (l+1)*(N+1)+i;
							
							for(j=1;j<solver->nonzero[l*(N+1)+i]-1;j++)
								solver->col[l*(N+1)+i][j] = l*(N+1)+i+j-2;
							for(j=0;j<solver->nonzero[l*(N+1)+i];j++)
								solver->val[l*(N+1)+i][j] = v2d2nd[j];
						}
					}
				}	
			}		
		}
				
                if(solver->fd_method == 4)
		{
			double v2d4th[9] = {-1.0/12*con, 4.0/3*con, -1.0/12*con, 4.0/3*con, -5*con, 4.0/3*con, -1.0/12*con, 4.0/3*con, -1.0/12*con};
			
			//for(i=0;i<9;i++)
				//printf("%f  ",v2d4th[i]);
			//printf("\n");
			
			/* Define matrix */	
			solver->nonzero = (int*)malloc(sizeof(int)*(N+1)*(N+1));
			solver->col = (int**)malloc(sizeof(int*)*(N+1)*(N+1));
			solver->val = (double**)malloc(sizeof(double*)*(N+1)*(N+1));
			
			for(i=0;i<(N+1)*(N+1);i++)
			{
				solver->col[i] = (int *)malloc(sizeof(int) * 9);
				solver->val[i] = (double *)malloc(sizeof(double) * 9);
			}
			
			for(l=0;l<=N;l++)
			{
				if((l==0)||(l==1)||(l==N-1)||(l==N))
				{
					for(i=0;i<=N;i++)
					{ 
						solver->nonzero[l*(N+1)+i] = 1;
						solver->col[l*(N+1)+i][0]  = l*(N+1)+i;
						solver->val[l*(N+1)+i][0]  = 1;
					}
				}
				else
				{
					for(i=0;i<=N;i++)
					{
						if((i==0)||(i==1)||(i==N-1)||(i==N))
						{
							solver->nonzero[l*(N+1)+i] = 1;
							solver->col[l*(N+1)+i][0]  = l*(N+1)+i;
							solver->val[l*(N+1)+i][0]  = 1;
						}
						else
						{
							solver->nonzero[l*(N+1)+i] = 9;
							solver->col[l*(N+1)+i][0]  = (l-2)*(N+1)+i;
							solver->col[l*(N+1)+i][1]  = (l-1)*(N+1)+i;
							solver->col[l*(N+1)+i][7]  = (l+1)*(N+1)+i;
							solver->col[l*(N+1)+i][8]  = (l+2)*(N+1)+i;
							
							for(j=2;j<solver->nonzero[l*(N+1)+i]-2;j++)
								solver->col[l*(N+1)+i][j] = l*(N+1)+i+j-4;
							for(j=0;j<solver->nonzero[l*(N+1)+i];j++)
								solver->val[l*(N+1)+i][j] = v2d4th[j];
						}
					}
				}
			}				
		}
	}
	grvy_timer_end(__func__);
	
	/* Debug matrix*/
	if(solver->output_mode == 2)
	{
		printf("\n----------sparse matrix A------------\n");
		printf("\n");
		
		printf("Number of nonzeros for each row [i]\n");
		for(i=0;i<solver->n;i++)
                        printf("%d  ", solver->nonzero[i]);
                printf("\n\n");
		
		printf("Index of nonzero columns for each row [i]\n");
		for(i=0;i<solver->n;i++)
		{
			for(j=0;j<solver->nonzero[i];j++)
                        	printf("%d  ", solver->col[i][j]);
                	printf("\n");
		}
		printf("\n");
		
		printf("Nonzero matrix values for each row [i]\n");
		for(i=0;i<solver->n;i++)
                {
                        for(j=0;j<solver->nonzero[i];j++)
                                printf("%f  ", solver->val[i][j]);
                        printf("\n");
                }
		printf("\n");
	}
	
	/* Debug right hand side values*/
	if(solver->output_mode == 2)
	{
		printf("\nb =\n\n[\n");
		for(i=0;i<solver->n;i++)
			printf("  %f;\n", solver->b[i]);
		printf("];\n\n");
	}
	
	if(solver->output_mode == 2)
	{
		printf("[debug]: build_linear_system	- function end\n");
		printf("[debug]: solve_system		- function begin\n");
	}
	
}
