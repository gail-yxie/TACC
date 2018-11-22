#include "solver.h"

int main(int argc, char argv[])
{
 	Laplacian_FD Solver;
	
	if(argv < 2)
	{
		grvy_printf(errorm, "\nUsage: solver [input-file] \n\n");
		exit(1);		
	}
 	
	parse_input(argv[1]);
	init();
	build_linear_system();
	solve_system();
	output();
	error_norm();
	
	return 0;
	
}
