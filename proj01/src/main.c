#include <stdio.h>
#include <stdlib.h>
#include "parameter.h"
#include "function.h"

int main(int argc, char** argv[])
{
	
	if(argv < 2)
	{
		grvy_printf(errorm, "\nUsage: solver [input-file] \n\n");
		exit(1);		
	}

	/* Define global struct and variable */
	struct Parameter solver;

	/* Run functions step by step*/ 	
	parse_input(&solver, argv[1]);
	init(&solver);
	build_linear_system(&solver);
	solve_system(&solver);
	output(&solver);

	/* Freeing dynamic variables is in output.c*/

	return 0;
}
