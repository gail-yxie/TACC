#include "function.h"

void output(struct Parameter* solver)
{
	int i,j;
	/* silent mode */
	if(solver->output_mode == 0)
	{
		//only output the result solver->z;
	}
	
	/* standard mode */
	if(solver->output_mode == 1)
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

		double error;
		error = error_norm(solver->z, solver->u, solver->n);
		printf("Error norm is %e\n", error);	
	}
	
	/* debug mode */
	if(solver->output_mode == 2)
	{
	
	}
	
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
}
