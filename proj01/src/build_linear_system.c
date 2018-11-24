#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

/* Parameters need: N, k, h, dimensions, fd_method */

void build_linear_system()
{
	int i,j,l;
	int N;
	double con = -k/(h*h);
	
	if(dimensions == 1)
	{
		if(fd_method == 2)
		{	
			double v1d2nd[3] = {con, -2*con, con};
			
			/* Define matrix */	
			struct Matrix* A;
			A.nonzero = (int*)malloc(sizeof(int)*(N+1));
			A.col = (int*)malloc(sizeof(int)*(N+1)*3);
			A.val = (double*)malloc(sizeof(double)*(N+1)*3);
				 
			for(i=0;i<=N;i++)
			{	
				if((i==0)||(i==N))
				{
					A.nonzero[i] = 1;
        	                        A.col[i][0]  = i;
	                                A.val[N][0]  = con;
				}	
				else
				{
					A.nonzero[i] = 3;
					for(j=0;j<A.nonzero[i],j++)
					{
						A.col[i][j] = i-1+j;
						A.val[i][j] = v1d2nd[j];
					}
				}
			}
		}

		if(fd_method == 4)
		{
			double v1d4th[5] = {-1/12*con, 4/3*con, -5/2*con, 4/3*con, -1/12*con};
				
			/* Define matrix */	
			struct Matrix* A;
			A.nonzero = (int*)malloc(sizeof(int)*(N+1));
			A.col = (int*)malloc(sizeof(int)*(N+1)*5);
			A.val = (double*)malloc(sizeof(double)*(N+1)*5);

			for(i=0;i<=N;i++)
			{
				if((i==0)||(i==1)||(i==N-1)||(i==N))
				{
					A.nonzero[i] = 1;
					A.col[i][0]  = i;
					A.val[i][0]  = con;
				}
				else
				{
					A.nonzero[i] = 5;
					for(j=0;j<A.nonzero[i],j++)
					{
						A.col[i][j] = i-2+j;
						A.val[i][j] = v1d4th[j];
					}
				}
			}
		}
	}

	if(dimensions == 2)
	{
		if(fd_method == 2)
		{
			double v2d2nd[5] = {con, con, -4*con, con, con};
			
			/* Define matrix */	
			struct Matrix* A;
			A.nonzero = (int*)malloc(sizeof(int)*(N+1)*(N+1));
			A.col = (int*)malloc(sizeof(int)*(N+1)*(N+1)*5);
			A.val = (double*)malloc(sizeof(double)*(N+1)*(N+1)*5);

			for(l=0;l<=N;l++)
			{
				if((l==0)||(l==N))
				{
					for(i=0;i<=N;i++)
					{ 
						A.nonzero[l*(N+1)+i] = 1;
						A.col[l*(N+1)+i][0]  = l*(N+1)+i;
						A.val[l*(N+1)+i][0]  = con;
					}
				}
				else
				{
					for(i=0;i<=N;i++)
					{
						if((i==0)||(i==N))
						{
							A.nonzero[l*(N+1)+i] = 1;
							A.col[l*(N+1)+i][0]  = l*(N+1)+i;
							A.val[l*(N+1)+i][0]  = con;
						}
						else
						{
							A.nonzero[l*(N+1)+i] = 5;
							A.col[l*(N+1)+i][0]  = (l-1)*(N+1)+i;
							A.col[l*(N+1)+i][4]  = (l+1)*(N+1)+i;
							for(j=1;j<A.nonzero[l*(N+1)+i]-1;j++)
							{
								A.col[l*(N+1)+i][j] = l*(N+1)+j-1;
								A.val[i][j] = v2d2nd[j];
							}
						}
					}
				}	
			}		
		}
				
                if(fd_method == 4)
		{
			double v2d4th[9] = {-1/12*con, 4/3*con, -1/12*con, 4/3*con, -5*con, 4/3*con, -1/12*con, 4/3*con, -1/12*con};
		
			/* Define matrix */	
			struct Matrix* A;
			A.nonzero = (int*)malloc(sizeof(int)*(N+1)*(N+1));
			A.col = (int*)malloc(sizeof(int)*(N+1)*(N+1)*9);
			A.val = (double*)malloc(sizeof(double)*(N+1)*(N+1)*9);
			
			for(l=0;l<=N;l++)
			{
				if((l==0)||(l==1)||(l==N-1)||(l==N))
				{
					for(i=0;i<=N;i++)
					{ 
						A.nonzero[l*(N+1)+i] = 1;
						A.col[l*(N+1)+i][0]  = l*(N+1)+i;
						A.val[l*(N+1)+i][0]  = con;
					}
				}
				else
				{
					for(i=0;i<=N;i++)
					{
						if((i==0)||(i==1)||(i==N-1)||(i==N))
						{
							A.nonzero[l*(N+1)+i] = 1;
							A.col[l*(N+1)+i][0]  = l*(N+1)+i;
							A.val[l*(N+1)+i][0]  = con;
						}
						else
						{
							A.nonzero[l*(N+1)+i] = 9;
							A.col[l*(N+1)+i][0]  = (l-2)*(N+1)+i;
							A.col[l*(N+1)+i][1]  = (l-1)*(N+1)+i;
							A.col[l*(N+1)+i][7]  = (l+1)*(N+1)+i;
							A.col[l*(N+1)+i][8]  = (l+2)*(N+1)+i;
							for(j=2;j<A.nonzero[l*(N+1)+i]-2;j++)
							{
								A.col[l*(N+1)+i][j] = l*(N+1)+j-2;
								A.val[i][j] = v2d4th[j];
							}
						}
					}
				}
			}				
		}
	}	
}
