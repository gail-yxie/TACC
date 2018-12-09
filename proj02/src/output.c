#include "function.h"

void output(struct Parameter* solver)
{
	grvy_timer_begin(__func__);
	
	int i, j;
	if(solver->output_mode != 0)
		printf("   --> Writing output to sol.dat\n");
	
	/* Write solutions of heat equation to file output_file self-defined */
	// need to be comment
	//FILE *fp = NULL;
	//fp = fopen(solver->output_file,"w+");
	
	//for(i=0;i<solver->n;i++)
		//fprintf(fp, "%.18f ",solver->z[i]);
	//fprintf(fp, "\n");
	//fclose(fp);
	
	/* Write solutions of heat equation to file output_file HDF5 */
	hid_t    file, group, dataset, dataspace;	/* file and dataset handles */
	hsize_t  dimsf[1];			/* dataset dimensions */
	herr_t   status;
	
	/* Create a new file using default properties. */
	file = H5Fcreate(solver->output_file, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
	/* Create the data space for the dataset. */
	dimsf[0] = solver->n;
	dataspace = H5Screate_simple(1, dimsf, NULL);
	/* Create the dataset using defined dataspace and default properties. */
	dataset = H5Dcreate2(file, "cor_x", H5T_NATIVE_DOUBLE, dataspace, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	/* Write the data to the dataset using default transfer properties. */
	status = H5Dwrite(dataset, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, solver->cor_x);
	H5Sclose(dataspace);
	H5Dclose(dataset);
	
	dataspace = H5Screate_simple(1, dimsf, NULL);
	dataset = H5Dcreate2(file, "T_sol", H5T_NATIVE_DOUBLE, dataspace, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	status = H5Dwrite(dataset, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, solver->z);
	H5Sclose(dataspace);
	H5Dclose(dataset);
	
	/* Close/release resources. */
	
	H5Fclose(file);
	
	if(status!=0)
	{
		printf("Error!Can not write the output file!\n");
		exit(1);
	}
		
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
		
		if(solver->output_mode != 0)
			printf("   --> l2 error norm = %e\n\n", error);
		
		/* If you need to save the error norm in file and to plot convergence rate */
		//FILE *fp2;
		//fp2 = fopen("conv_tmp","w+");
		//fprintf(fp2, "%d %e\n", solver->N ,error);
		//fclose(fp2);	
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
        free(solver->val);
	free(solver->col);
	free(solver->f);
        free(solver->u);

	grvy_timer_end(__func__);
	
	if(solver->output_mode == 2)
	{
		printf("[debug]: error_norm		- function end\n");
		printf("[debug]: ~Laplacian_FD		- function begin\n");
	}
}
