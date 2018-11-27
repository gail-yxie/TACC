#include "function.h"

void output(struct Parameter* solver)
{
	grvy_timer_begin(__func__);
	
	int i,j;
	
	FILE *fp = NULL;
	fp = fopen(solver->output_file,"w+");
	
	for(i=0;i<solver->n;i++)
		fprintf(fp, "%.18f ",solver->z[i]);
	fprintf(fp, "\n");
	
	if(solver->verify_mode == 1)
	{
		double error;
		error = error_norm(solver->z, solver->u, solver->n);
		printf("%d	%e\n", solver->N ,error);
	}

	/* silent mode */
	if(solver->output_mode == 0)
	{
		//only output the result solver->z;
	}

	FILE *fp1 = NULL;
	fp1 = fopen("../test/ref.txt", "w+");
	for(i=0;i<solver->n;i++)
                fprintf(fp1, "%.18f ",solver->u[i]);
        fprintf(fp1, "\n"); 
	
	/* standard mode */
	if(solver->output_mode == 3)
	{
		/* output the matrix */
		printf("---matrix---\n");

		for(i=0;i<solver->n;i++)
                        printf("%d  ", solver->nonzero[i]);
                printf("\n");
		for(i=0;i<solver->n;i++)
		{
			for(j=0;j<solver->nonzero[i];j++)
                        	printf("%d  ", solver->col[i][j]);
                	printf("\n");
		}

		for(i=0;i<solver->n;i++)
                {
                        for(j=0;j<solver->nonzero[i];j++)
                                printf("%f  ", solver->val[i][j]);
                        printf("\n");
                }	

		for(i=0;i<solver->n;i++)
                        printf("%f  ", solver->z[i]);
                printf("\n");
                for(i=0;i<solver->n;i++)
                        printf("%f  ", solver->u[i]);
                printf("\n");
		
		if(solver->verify_mode == 1)
		{
			double error;
			error = error_norm(solver->z, solver->u, solver->n);
			printf("Total n is: %d\n Error norm is %e\n", solver->n, error);
		}	
	}
	
	/* debug mode */
	if(solver->output_mode == 2)
	{
	
	}
	
	fclose(fp);

	 /* Free dynamic variables*/
        free(solver->output_file);
        free(solver->b);
        free(solver->z);
        free(solver->nonzero);
	for(i=0;i<solver->n;i++)
	{
		free(solver->col[i]);
		free(solver->val[i]);
	}
        free(solver->f);
        free(solver->u);

	grvy_timer_end(__func__);
}
