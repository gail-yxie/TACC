#include "function.h"

void init(struct Parameter* solver)
{	
	if(solver->output_mode!=0)
		printf("** Initializing data structures...\n");
	
	grvy_timer_begin(__func__);

	/* Compute mesh size */
	int N = solver->N;
	int i;
		
	if(solver->dimensions == 1)
	{	
		solver->n = N+1;

		/* Initialize masa: we can choose "bob" or "nick" */
		/* we can use  "masa_list_mms();" to initialize mms */
		masa_init("bob","heateq_1d_steady_const");

		/* Set parameter for masa example */
		masa_set_param("k_0", solver->k);
		masa_set_param("A_x" , 3*M_PI);
		
		/* Allocate dynamic memory */
        	solver->b = (double*)malloc((N+1)*sizeof(double));
		solver->f = (double*)malloc((N+1)*sizeof(double));
		solver->u = (double*)malloc((N+1)*sizeof(double));
	
		for(i=0; i<=N; i++)
		{      
                        /* generate mesh */
			solver->cor_x[i] = solver->xmin + i * solver->h;
			/* source term */
			solver->f[i] = masa_eval_1d_source_t(solver->cor_x[i]);
			/* manufactured solution */
			solver->u[i] = masa_eval_1d_exact_t(solver->cor_x[i]);
			
			if((i==0)||(i==N))
				/* Record boundary conditions*/
				solver->b[i] = solver->u[i];
			else
				/* Record source terms */
				solver->b[i] = solver->f[i];
		}

		if(solver->fd_method == 4)
		{
			solver->b[1]   = solver->u[1];
			solver->b[N-1] = solver->u[N-1];
		}
	}	
	
	if(solver->dimensions == 2)
	{	
		int j;
		solver->n = (N+1)*(N+1);

		/* Initialize masa: we can choose "bob" or "nick" */
		/* we can use  "masa_list_mms();" to initialize mms */
		masa_init("bob","heateq_2d_steady_const");

		/* Set parameter for masa example */
		masa_set_param("k_0", solver->k);
		masa_set_param("A_x", 3*M_PI);
		masa_set_param("B_y", 3*M_PI);

		/* Allocate dynamic memory */
        	solver->b = (double*)malloc((N+1)*(N+1)*sizeof(double));
		solver->f = (double*)malloc((N+1)*(N+1)*sizeof(double));
		solver->u = (double*)malloc((N+1)*(N+1)*sizeof(double));

		for(i=0; i<=N; i++)
			for(j=0; j<=N; j++)
			{	
				/* generate mesh */
				solver->cor_x[i*(N+1)+j] = solver->xmin + i * solver->h;
				solver->cor_y[i*(N+1)+j] = solver->ymin + j * solver->h;

				/* source term */
				solver->f[i*(N+1)+j] = masa_eval_2d_source_t(solver->cor_x[i*(N+1)+j],solver->cor_y[i*(N+1)+j]);
				/* manufactured solution */
				solver->u[i*(N+1)+j] = masa_eval_2d_exact_t(solver->cor_x[i*(N+1)+j],solver->cor_y[i*(N+1)+j]);
		
				if((i==0)||(i==N)||(j==0)||(j==N))
					/* Record boundary conditions*/
					solver->b[i*(N+1)+j] = solver->u[i*(N+1)+j];
				else
					/* Record source terms */
					solver->b[i*(N+1)+j] = solver->f[i*(N+1)+j];
			}
		
		/* Add "cheating" boundary conditions */
		if(solver->fd_method == 4)
		{
			for(j=0;j<=N;j++)
			{
				solver->b[N+1+j]         = solver->u[N+1+j];
				solver->b[(N-1)*(N+1)+j] = solver->u[(N-1)*(N+1)+j];
			}
			for(i=0;i<=N;i++)
			{
				solver->b[i*(N+1)+1]     = solver->u[i*(N+1)+1];
				solver->b[i*(N+1)+N-1]   = solver->u[i*(N+1)+N-1];
			}
		}
	}

	grvy_timer_end(__func__);
	
	if(solver->output_mode == 2)
	{
		printf("[debug]: init		- function end \n");
		printf("[debug]: build_linear_system - function begin\n");
	}
}
