#include <stdio.h>
#include <stdlib.h>
#include "parameter.h"
#include "function.h"

int main(int argc, char argv[])
{
	
	if(argv < 2)
	{
		grvy_printf(errorm, "\nUsage: solver [input-file] \n\n");
		exit(1);		
	}

	/* Define global struct and variable */
	struct Parameter* solver;
	const char* input_file = argv[1];

	/* Run functions step by step*/ 	
	parse_input(solver, input_file);
	init(solver);
	build_linear_system(solver);
	solve_system(solver);
	output(solver);

	/* Free dynamic variables*/
	free(solver.output_file);
	free(solver.z);
	
	return 0;
}
