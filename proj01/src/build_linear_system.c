#include <stdio.h>
#include <stdlib.h>
#include "parameter.h"

void build_linear_system(Parameter* solver)
{
	int i,j,l;
	double con = -solver.k/(solver.h*solver.h);
	double N = solver.N;
		
	if(solver.dimensions == 1)
	{
		if(solver.fd_method == 2)
		{	
			double v1d2nd[3] = {con, -2*con, con};
			
			/* Define matrix A */	
			solver.A.nonzero = (int*)malloc(sizeof(int)*(N+1));
			solver.A.col = (int**)malloc(sizeof(int*)*(N+1));
			solver.A.val = (double**)malloc(sizeof(double*)*(N+1));
			
			for(i=0;i<N+1;i++)
			{
				solver.A.col[i] = (int *)malloc(sizeof(int) * 3);//allocate memory for each pointer.
				solver.A.val[i] = (double *)malloc(sizeof(double) * 3);//allocate memory for each pointer.
			}
				 
			for(i=0;i<=N;i++)
			{	
				if((i==0)||(i==N))
				{
					solver.A.nonzero[i] = 1;
        	                        solver.A.col[i][0]  = i;
	                                solver.A.val[N][0]  = con;
				}	
				else
				{
					solver.A.nonzero[i] = 3;
					for(j=0;j<solver.A.nonzero[i],j++)
					{
						solver.A.col[i][j] = i-1+j;
						solver.A.val[i][j] = v1d2nd[j];
					}
				}
			}
		}

		if(solver.fd_method == 4)
		{
			double v1d4th[5] = {-1/12*con, 4/3*con, -5/2*con, 4/3*con, -1/12*con};
				
			/* Define matrix */	
			solver.A.nonzero = (int*)malloc(sizeof(int)*(N+1));
			solver.A.col = (int**)malloc(sizeof(int*)*(N+1));
			solver.A.val = (double**)malloc(sizeof(double*)*(N+1));
			
			for(i=0;i<N+1;i++)
			{
				solver.A.col[i] = (int *)malloc(sizeof(int) * 5);
				solver.A.val[i] = (double *)malloc(sizeof(double) * 5);
			}

			for(i=0;i<=N;i++)
			{
				if((i==0)||(i==1)||(i==N-1)||(i==N))
				{
					solver.A.nonzero[i] = 1;
					solver.A.col[i][0]  = i;
					solver.A.val[i][0]  = con;
				}
				else
				{
					solver.A.nonzero[i] = 5;
					for(j=0;j<solver.A.nonzero[i],j++)
					{
						solver.A.col[i][j] = i-2+j;
						solver.A.val[i][j] = v1d4th[j];
					}
				}
			}
		}
	}

	if(solver.dimensions == 2)
	{
		if(solver.fd_method == 2)
		{
			double v2d2nd[5] = {con, con, -4*con, con, con};
			
			/* Define matrix */	
			solver.A.nonzero = (int*)malloc(sizeof(int)*(N+1)*(N+1));
			solver.A.col = (int**)malloc(sizeof(int*)*(N+1)*(N+1));
			solver.A.val = (double**)malloc(sizeof(double*)*(N+1)*(N+1));
			
			for(i=0;i<(N+1)*(N+1);i++)
			{
				solver.A.col[i] = (int *)malloc(sizeof(int) * 5);
				solver.A.val[i] = (double *)malloc(sizeof(double) * 5);
			}

			for(l=0;l<=N;l++)
			{
				if((l==0)||(l==N))
				{
					for(i=0;i<=N;i++)
					{ 
						solver.A.nonzero[l*(N+1)+i] = 1;
						solver.A.col[l*(N+1)+i][0]  = l*(N+1)+i;
						solver.A.val[l*(N+1)+i][0]  = con;
					}
				}
				else
				{
					for(i=0;i<=N;i++)
					{
						if((i==0)||(i==N))
						{
							solver.A.nonzero[l*(N+1)+i] = 1;
							solver.A.col[l*(N+1)+i][0]  = l*(N+1)+i;
							solver.A.val[l*(N+1)+i][0]  = con;
						}
						else
						{
							solver.A.nonzero[l*(N+1)+i] = 5;
							solver.A.col[l*(N+1)+i][0]  = (l-1)*(N+1)+i;
							solver.A.col[l*(N+1)+i][4]  = (l+1)*(N+1)+i;
							
							for(j=1;j<solver.A.nonzero[l*(N+1)+i]-1;j++)
								solver.A.col[l*(N+1)+i][j] = l*(N+1)+j-1;
							for(j=0;j<solver.A.nonzero[l*(N+1)+i];j++)
								solver.A.val[l*(N+1)+i][j] = v2d2nd[j];
						}
					}
				}	
			}		
		}
				
                if(solver.fd_method == 4)
		{
			double v2d4th[9] = {-1/12*con, 4/3*con, -1/12*con, 4/3*con, -5*con, 4/3*con, -1/12*con, 4/3*con, -1/12*con};
		
			/* Define matrix */	
			solver.A.nonzero = (int*)malloc(sizeof(int)*(N+1)*(N+1));
			solver.A.col = (int**)malloc(sizeof(int*)*(N+1)*(N+1));
			solver.A.val = (double**)malloc(sizeof(double*)*(N+1)*(N+1));
			
			for(i=0;i<(N+1)*(N+1);i++)
			{
				solver.A.col[i] = (int *)malloc(sizeof(int) * 9);
				solver.A.val[i] = (double *)malloc(sizeof(double) * 9);
			}
			
			for(l=0;l<=N;l++)
			{
				if((l==0)||(l==1)||(l==N-1)||(l==N))
				{
					for(i=0;i<=N;i++)
					{ 
						solver.A.nonzero[l*(N+1)+i] = 1;
						solver.A.col[l*(N+1)+i][0]  = l*(N+1)+i;
						solver.A.val[l*(N+1)+i][0]  = con;
					}
				}
				else
				{
					for(i=0;i<=N;i++)
					{
						if((i==0)||(i==1)||(i==N-1)||(i==N))
						{
							solver.A.nonzero[l*(N+1)+i] = 1;
							solver.A.col[l*(N+1)+i][0]  = l*(N+1)+i;
							solver.A.val[l*(N+1)+i][0]  = con;
						}
						else
						{
							solver.A.nonzero[l*(N+1)+i] = 9;
							solver.A.col[l*(N+1)+i][0]  = (l-2)*(N+1)+i;
							solver.A.col[l*(N+1)+i][1]  = (l-1)*(N+1)+i;
							solver.A.col[l*(N+1)+i][7]  = (l+1)*(N+1)+i;
							solver.A.col[l*(N+1)+i][8]  = (l+2)*(N+1)+i;
							
							for(j=2;j<solver.A.nonzero[l*(N+1)+i]-2;j++)
								solver.A.col[l*(N+1)+i][j] = l*(N+1)+j-2;
							for(j=0;j<solver.A.nonzero[l*(N+1)+i];j++)
								solver.A.val[l*(N+1)+i][j] = v2d4th[j];
						}
					}
				}
			}				
		}
	}	
}
