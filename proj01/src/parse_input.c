#include <stdio.h>
#include <stdlib.h>
#include <grvy.h>

void parse_input(int argc, char** argv)
{
	/* Use GRVY tool to read inputs from ./input.mat */
	
	int igot;
	int dimensions, N, fd_method, max_iter, verify_mode, output_mode;
	double k, xmin, xmax, ymin, ymax, eps;
	char *output_file, *iter_method;	

	/* Initialize/read the file */
	
	igot = grvy_input_fopen("./input.dat");

	/* Read specific variables and echo locally */	

	if(grvy_input_fread_double("k",&k))
                printf("--> %-10s = %f\n","k",k);

	if(grvy_input_fread_int("verify_mode",&verify_mode))
                printf("--> %-10s = %i\n","verify_mode",verify_mode);
	
	if(grvy_input_fread_int("output_mode",&output_mode))
                printf("--> %-10s = %i\n","output_mode",output_mode);

	if(grvy_input_fread_char("output_file",&output_file))
                printf("--> %-10s = %s\n","output_file",output_file);

	free(output_file);
	
	/* Read variables from the mesh section */
	
	if(grvy_input_fread_int("mesh/dimensions",&dimensions))
                printf("--> %-10s = %i\n","mesh/dimensions",dimensions);
	
	if(grvy_input_fread_double("mesh/xmin",&xmin))
                printf("--> %-10s = %f\n","mesh/xmin",xmin);

	if(grvy_input_fread_double("mesh/xmax",&xmax))
                printf("--> %-10s = %f\n","mesh/xmax",xmax);

	if(grvy_input_fread_double("mesh/ymin",&ymin))
                printf("--> %-10s = %f\n","mesh/ymin",ymin);

	if(grvy_input_fread_double("mesh/ymax",&ymax))
                printf("--> %-10s = %f\n","mesh/ymax",ymax);

	if(grvy_input_fread_int("mesh/N",&N))
                printf("--> %-10s = %i\n","mesh/N",N);

	/* Read variables from the solver section */

	if(grvy_input_fread_int("solver/fd_method",&fd_method))
                printf("--> %-10s = %i\n","mesh/fd_method",fd_method);

	if(grvy_input_fread_char("solver/iter_method",&iter_method))
                printf("--> %-10s = %s\n","solver/iter_method",iter_method);

	if(grvy_input_fread_double("solver/eps",&eps))
                printf("--> %-10s = %f\n","solver/eps",eps);

	if(grvy_input_fread_int("solver/max_iter",&max_iter))
                printf("--> %-10s = %i\n","solver/max_iter",max_iter);

	
	free(iter_method);
		
	/* Close the file */
	grvy_input_fclose();


}
