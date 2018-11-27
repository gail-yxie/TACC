#include "function.h"

void output(struct Parameter* solver)
{
	grvy_timer_begin(__func__);
	
	int i;
	if(solver->output_mode != 0)
		printf("   --> Writing output to sol.dat\n");
	/* Write solutions of heat equation to file output_file */
	FILE *fp = NULL;
	fp = fopen(solver->output_file,"w+");
	
	for(i=0;i<solver->n;i++)
		fprintf(fp, "%.18f ",solver->z[i]);
	fprintf(fp, "\n");
	fclose(fp);
	
	if(solver->output_mode == 2)
	{
		printf("[debug]: output 		- function end\n");
		printf("[debug]: error_norm		- function begin\n");
	}
	else if(solver->output_mode == 1)
		printf("\n\n");
	
	/* Use l2 norm to verify the solutions*/
	if(solver->verify_mode == 1)
	{	
		if(solver->output_mode != 0)
			printf("\n\n** Computing l2 error norm.\n");
		
		double error;
		error = error_norm(solver->z, solver->u, solver->n);
		
		printf("   --> l2 error norm = %e\n\n", error);
		
		/* If you need to save the error norm in file and to plot convergence rate */
		//FILE *fp2;
		//fp2 = fopen("conv_tmp","w+");
		//fprintf(fp2, "%d %e\n", solver->N ,error);
		//fclose(fp2);
		
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
	
	if(solver->output_mode == 2)
	{
		printf("[debug]: error_norm		- function end\n");
		printf("[debug]: ~Laplacian_FD		- function begin\n");
	}
}
