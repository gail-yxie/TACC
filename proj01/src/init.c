#include <stdlib.h>

void init()
{
	/* Variables need: */

	double h;
	
	h = (xmax - xmin) / N; 
	if(dimensions == 1)
	{	
		masa_init("","1d");
		masa_set_param("k",*k);

		double* b;
        	b = (double*)malloc((N+1)*sizeof(double));
		int k = 0;
	
		for(int i=0; i<=N; i++)
		{      
                        /* generate mesh */
			x = xmin + i * h;
			/* source term */
			f[i] = masa_eval_1d_source_f(x);
			/* manufactured solution */
			u[i] = masa_eval_2d_exact_phi(x);
			
			if((i==0)||(i==N))
				b[i] = u[i];
			else
				b[i] = f[i];
		}

		if(fd_method == 4)
		{
			b[1]   = u[1];
			b[N-1] = u[N-1];
		}
	}	

	if(dimensions == 2)
	{	
		masa_init("","");
		masa_set_param("k",*k);

		double* b;
		b = (double*) malloc((N+1)*(N+1)*sizeof(double));

		for(int i=0; i<=N; i++)
			for(int j=0; j<=N; j++)
			{	
				/* generate mesh */
				x = xmin + i * h;
				y = ymin + j * h;

				/* source term */
				f[i][j] = masa_eval_2d_source_f(x,y);
				/* manufactured solution */
				u[i][j] = masa_eval_2d_exact_phi(x,y);

				if((i==0)||(i==N)||(j==0)||(j==N))
					b[i*(N+1)+j] = u[i][j];
				else
					b[i*(N+1)+j] = f[i][j];
			}

		if(fd_method == 4)
		{
			for(j=0;j<=N;j++)
				b[N+1+j]         = u[1][j];
				b[(N-1)*(N+1)+j] = u[N-1][j];
			for(i=0;i<=N;i++)
				b[i*(N+1)+1]     = u[i][1];
				b[i*(N+1)+N-1]   = u[i][N-1];
		}
	}
}
