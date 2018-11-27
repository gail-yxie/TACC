#include "function.h"

void parse_input(struct Parameter* solver, const char* input_file)
{
	grvy_timer_begin(__func__);
	/* Use GRVY tool to read inputs from /input.mat */
	int igot;

	/* Initialize/read the file */
	
	igot = grvy_input_fopen(input_file);

	if(igot!=1)
	{
		printf("Error!Can not read the input file!\n");
		exit(1);
	}
	
	/* Read specific variables and echo locally */	
	grvy_input_fread_double("k",&solver->k);
	grvy_input_fread_int("verify_mode",&solver->verify_mode);
	grvy_input_fread_int("output_mode",&solver->output_mode);
	grvy_input_fread_char("output_file",&solver->output_file);

	/* Read variables from the mesh section */
	grvy_input_fread_int("mesh/dimensions",&solver->dimensions);
	grvy_input_fread_double("mesh/xmin",&solver->xmin);
	grvy_input_fread_double("mesh/xmax",&solver->xmax);
	grvy_input_fread_double("mesh/ymin",&solver->ymin);
	grvy_input_fread_double("mesh/ymax",&solver->ymax);
	grvy_input_fread_int("mesh/N",&solver->N);

	/* Read variables from the solver section */
	grvy_input_fread_int("solver/fd_method",&solver->fd_method);
	grvy_input_fread_int("solver/iter_method",&solver->iter_method);
	grvy_input_fread_double("solver/eps",&solver->eps);
	grvy_input_fread_int("solver/max_iter",&solver->max_iter);
		
	/* Close the file */
	grvy_input_fclose();
	
	solver->h = (solver->xmax - solver->xmin) / solver-> N;
	
	/* Outputs */
	if(solver->output_mode!=0)
	{
		printf("\n\n");
		printf("** Finite-difference based Heat Equation Solver (steady-state)\n");
		printf("   --> Parsing runtime options from %s\n", input_file);
		printf("   --> %-10s = %f\n\n\n","h", solver->h);
		
		printf("** Runtime mesh settings  (%dD):\n", solver->dimensions);
		printf("   --> %-10s = %d	(xmin,xmax) = (%f, %f)\n","nx", solver->N, solver->xmin, solver->xmax);
		if(solver->dimensions == 2)
			printf("   --> %-10s = %d	(ymin,ymax) = (%f, %f)\n","ny", solver->N, solver->ymin, solver->ymax);
		printf("\n\n");
		
		printf("** Runtime solver settings:\n");
		printf("   --> %-10s = CENTRAL%d\n","finite difference method", solver->fd_method);
		if(solver->iter_method == 1)
			printf("   --> %-10s = %s\n","iterative method", "JACOBI");
		else if(solver->iter_method == 2)
			printf("   --> %-10s = %s\n","iterative method", "GAUSS_SEIDEL");
		printf("   --> %-10s = %d\n","max iterations", solver->max_iter);
		printf("   --> %-10s = %f\n","thermal conductivity", solver->k);
		printf("   --> %-10s = %s\n","solution output file", solver->output_file);
	}
	grvy_timer_end(__func__);
}
