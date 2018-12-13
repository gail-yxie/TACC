#include "function.h"

int main(int argc, char *argv[])
{
	
	if(argc < 2)
	{
		grvy_printf(GRVY_ERROR, "\nUsage: solver [input-file] \n\n");
		exit(1);		
	}

	/* Define global struct and variable */
	struct Parameter solver;

	grvy_timer_init("Steady Heat Equation Solver");
	
	/* Run functions step by step*/ 	
	parse_input(&solver, argv[1]);
	init(&solver);
	build_linear_system(&solver);
	
	#ifdef HAVE_PETSC
	if(solver.iter_method==3)
	{
		/* Initialization */
		PetscErrorCode ierr;
		ierr = PetscInitialize(&argc, &argv, 0, 0);
		CHKERRQ(ierr);
	}
	#endif
	
	solve_system(&solver);
	output(&solver);

	grvy_timer_finalize();
	
	if(solver.output_mode != 0)
		grvy_timer_summarize();
	
	if(solver.output_mode == 2)
		printf("[debug]: ~Laplacian_FD		- function end\n");

	return 0;
}
