#include "function.h"

void output(struct Parameter* solver)
{
	grvy_timer_begin(__func__);
	
	int i,j;
	
	/* Write solutions of heat equation to file output_file */
	FILE *fp = NULL;
	fp = fopen(solver->output_file,"w+");
	
	for(i=0;i<solver->n;i++)
		fprintf(fp, "%.18f ",solver->z[i]);
	fprintf(fp, "\n");
	fclose(fp);
	
	/* Use l2 norm to verify the solutions*/
	if(solver->verify_mode == 1)
	{
		double error;
		error = error_norm(solver->z, solver->u, solver->n);
		
		printf("Error norm for verification is %e", error);
		
		/* If you need to save the error norm in file and to plot convergence rate */
		\\FILE *fp2;
		\\fp2 = fopen("conv_tmp","w+");
		\\fprintf(fp2, "%d %e\n", solver->N ,error);
		\\fclose(fp2);
	}
	
	/* codes to generate reference data for check, please comment it when using the program. */
	//FILE *fp1 = NULL;
	//fp1 = fopen("../test/ref_2d.txt", "w+");
	//for(i=0;i<solver->n;i++)
                //fprintf(fp1, "%.18f ",solver->u[i]);
        //fprintf(fp1, "\n"); 

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
