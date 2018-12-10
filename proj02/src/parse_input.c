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
	
	grvy_input_fread_int("output_mode",&solver->output_mode);
	
	if(solver->output_mode!=0)
	{
		printf("\n\n");
		printf("** Finite-difference based Heat Equation Solver (steady-state)\n");
		printf("   --> Parsing runtime options from %s\n", input_file);
	}
	
	/* Read specific variables */	
	grvy_input_fread_double("k",&solver->k);
	grvy_input_fread_int("verify_mode",&solver->verify_mode);
	grvy_input_fread_char("output_file",&solver->output_file);

	/* Read variables from the mesh section */
	grvy_input_fread_int("mesh/dimensions",&solver->dimensions);
	grvy_input_fread_double("mesh/xmin",&solver->xmin);
	grvy_input_fread_double("mesh/xmax",&solver->xmax);
	grvy_input_fread_double("mesh/ymin",&solver->ymin);
	grvy_input_fread_double("mesh/ymax",&solver->ymax);
	grvy_input_fread_int("mesh/N",&solver->N);
	
	if((solver->dimensions !=1) && (solver->dimensions !=2))
	{
		printf("Error! Please input a correct dimension!\n");
		exit(1);
	}
	
	if(solver->N < 0)
	{
		printf("Error! Please input a positive N for solving!\n");
		exit(1);
	}
	
	/* Calculate h from inputs */
	solver->h = (solver->xmax - solver->xmin) / solver-> N;
	
	if(solver->output_mode!=0)
		printf("   --> %-10s = %f\n\n\n","h", solver->h);
	
	if(solver->output_mode == 2)
	{
		printf("MASA :: Solution has 2 variables.\n");
		printf("*-------------------------------------*\n");
		printf("A_x is set to: 9.424777960769379\n");
		printf("k_0 is set to: 1\n");
		printf("*-------------------------------------*\n");
		printf("[debug]: summarize_options	- function begin\n\n");
	}
	
	if(solver->output_mode!=0)
	{
		printf("** Runtime mesh settings  (%dD):\n", solver->dimensions);
		printf("   --> %-10s = %d	(xmin,xmax) = (%f, %f)\n","nx", solver->N, solver->xmin, solver->xmax);
		if(solver->dimensions == 2)
			printf("   --> %-10s = %d	(ymin,ymax) = (%f, %f)\n","ny", solver->N, solver->ymin, solver->ymax);
		printf("\n\n");
	}
	
	/* Read variables from the solver section */
	grvy_input_fread_int("solver/fd_method",&solver->fd_method);
	grvy_input_fread_int("solver/iter_method",&solver->iter_method);
	grvy_input_fread_double("solver/eps",&solver->eps);
	grvy_input_fread_int("solver/max_iter",&solver->max_iter);
	
	if((solver->iter_method!=1) && (solver->iter_method!=2) && (solver->iter_method!=3))
	{
		printf("Error! Please input a correct iter_method!\n");
		exit(1);
	}
		
	/* Close the file */
	grvy_input_fclose();
	
	/* Outputs */
	if(solver->output_mode!=0)
	{		
		printf("** Runtime solver settings:\n");
		printf("   --> %-10s = CENTRAL%d\n","finite difference method", solver->fd_method);
		if(solver->iter_method == 1)
			printf("   --> %-10s = %s\n","iterative method", "JACOBI");
		else if(solver->iter_method == 2)
			printf("   --> %-10s = %s\n","iterative method", "GAUSS_SEIDEL");
		printf("   --> %-10s = %d\n","max iterations", solver->max_iter);
		printf("   --> %-10s = %f\n","thermal conductivity", solver->k);
		printf("   --> %-10s = %s\n\n","solution output file", solver->output_file);
	}
	
	if(solver->output_mode == 2)
	{
		printf("[debug]: summarize_options	- function end\n");
		printf("[debug]: parse_input		- function end\n");
		printf("[debug]: init			- function begin\n\n\n");
	}
	else if(solver->output_mode == 1)
		printf("\n");
	
	grvy_timer_end(__func__);
}
