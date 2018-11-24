#include <stdio.h>
#include <stdlib.h>
#include <grvy.h>
#include "parameter.h"

void parse_input(Parameter* solver, const char* input_file);
{
	/* Use GRVY tool to read inputs from ./input.mat */
	
	int igot;

	/* Initialize/read the file */
	
	igot = grvy_input_fopen(input_file);

	/* Read specific variables and echo locally */	

	if(grvy_input_fread_double("k",&solver.k))
                printf("--> %-10s = %f\n","k",solver.k);

	if(grvy_input_fread_int("verify_mode",&solver.verify_mode))
                printf("--> %-10s = %i\n","verify_mode",solver.verify_mode);
	
	if(grvy_input_fread_int("output_mode",&solver.output_mode))
                printf("--> %-10s = %i\n","output_mode",solver.output_mode);

	if(grvy_input_fread_char("output_file",&solver.output_file))
                printf("--> %-10s = %s\n","output_file",solver.output_file);

	
	/* Read variables from the mesh section */
	
	if(grvy_input_fread_int("mesh/dimensions",&solver.dimensions))
                printf("--> %-10s = %i\n","mesh/dimensions",solver.dimensions);
	
	if(grvy_input_fread_double("mesh/xmin",&solver.xmin))
                printf("--> %-10s = %f\n","mesh/xmin",solver.xmin);

	if(grvy_input_fread_double("mesh/xmax",&solver.xmax))
                printf("--> %-10s = %f\n","mesh/xmax",solver.xmax);

	if(grvy_input_fread_double("mesh/ymin",&solver.ymin))
                printf("--> %-10s = %f\n","mesh/ymin",solver.ymin);

	if(grvy_input_fread_double("mesh/ymax",&solver.ymax))
                printf("--> %-10s = %f\n","mesh/ymax",solver.ymax);

	if(grvy_input_fread_int("mesh/N",&solver.N))
                printf("--> %-10s = %i\n","mesh/N",solver.N);

	/* Read variables from the solver section */

	if(grvy_input_fread_int("solver/fd_method",&solver.fd_method))
                printf("--> %-10s = %i\n","mesh/fd_method",solver.fd_method);

	if(grvy_input_fread_int("solver/iter_method",&solver.iter_method))
                printf("--> %-10s = %s\n","solver/iter_method",solver.iter_method);

	if(grvy_input_fread_double("solver/eps",&solver.eps))
                printf("--> %-10s = %f\n","solver/eps",solver.eps);

	if(grvy_input_fread_int("solver/max_iter",&solver.max_iter))
                printf("--> %-10s = %i\n","solver/max_iter",solver.max_iter);

		
	/* Close the file */
	grvy_input_fclose();

}
