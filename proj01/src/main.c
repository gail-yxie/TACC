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
	printf("Starting...\n");

	grvy_timer_init("Steady Heat Equation Solver");
	
	/* Run functions step by step*/ 	
	parse_input(&solver, argv[1]);
	printf("Parse_input is done!\n");
	init(&solver);
	printf("Init is done!\n");
	build_linear_system(&solver);
	printf("Build_linear_system is done!\n");
	solve_system(&solver);
	printf("Solve_system is done!\n");
	output(&solver);
	printf("Output is done!\n");

	grvy_timer_finalize();
	grvy_timer_summarize();

	return 0;
}
