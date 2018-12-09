#include "function.h"

void output(struct Parameter* solver)
{
	grvy_timer_begin(__func__);
	
	int i, j;
	if(solver->output_mode != 0)
		printf("   --> Writing output to sol.dat\n");
	
	/* Write solutions of heat equation to file output_file self-defined */
	// need to be comment
	FILE *fp = NULL;
	fp = fopen(solver->output_file,"w+");
	
	for(i=0;i<solver->n;i++)
		fprintf(fp, "%.18f ",solver->z[i]);
	fprintf(fp, "\n");
	fclose(fp);
	
	/* Write solutions of heat equation to file output_file HDF5 */
	hid_t    file, dataset, dataspace;	/* file and dataset handles */
	hsize_t  dimsf[2];			/* dataset dimensions */
	herr_t   status;
	
	int 	 ny;
	double** data;
	int N = solver->N;
	
	if(solver->dimensions == 1)
		ny = 2;
	else
		ny = 3;
	if(solver->verify_mode == 1)
		ny = ny + 1;
	
	/* Initialize data buffer. */
	data = (double**)malloc(sizeof(double*) * solver->n);
	for(i=0;i<solver->n;i++)
		data[i] = (double*)malloc(sizeof(double) * ny);
	
	if(solver->dimensions == 1)
		for(i=0;i<=N;i++)
		{
			data[i][0] = solver->xmin + i * solver->h;
			data[i][1] = solver->z[i];
			if(solver->verify_mode == 1)
				data[i][2] = solver->u[i];	
		}
	
	if(solver->dimensions == 2)	
		for(i=0;i<=N;i++)
			for(j=0;j<=N;j++)
			{
				data[i*(N+1)+j][0] = solver->xmin + i * solver->h;
				data[i*(N+1)+j][1] = solver->ymin + j * solver->h;
				data[i*(N+1)+j][2] = solver->z[i*(N+1)+j];
				if(solver->verify_mode == 1)
					data[i*(N+1)+j][3] = solver->u[i*(N+1)+j];
			}
		
	/* Create a new file using default properties. */
	//need change file name
	file = H5Fcreate("sol.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
	/* Create the data space for the dataset. */
	dimsf[0] = solver->n;
	dimsf[1] = ny;
	dataspace = H5Screate_simple(2, dimsf, NULL);
	/* Create the dataset using defined dataspace and default properties. */
	// what does "" mean?
	dataset = H5Dcreate2(file, "heat eq sol", H5T_NATIVE_DOUBLE, dataspace, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	/* Write the data to the dataset using default transfer properties. */
	status = H5Dwrite(dataset, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
	/* Close/release resources. */
	H5Sclose(dataspace);
	H5Dclose(dataset);
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
		free(data[i]);
	}
        free(solver->val);
	free(solver->col);
	free(data);
	free(solver->f);
        free(solver->u);

	grvy_timer_end(__func__);
	
	if(solver->output_mode == 2)
	{
		printf("[debug]: error_norm		- function end\n");
		printf("[debug]: ~Laplacian_FD		- function begin\n");
	}
}
