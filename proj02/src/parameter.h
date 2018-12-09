#include <stdio.h>

#ifndef PARAMETER_H
#define PARAMETER_H

struct Parameter{

	/* input/output parameters */
	double k;
	int verify_mode;
        int output_mode;
	char* output_file;
	
	/* mesh parameters  */
	int dimensions;
	
	double xmin;
	double xmax;
	double ymin;
	double ymax;
	
	int N;
	double h;

	/* solver parameters */
	
	int fd_method;
	int iter_method;
	double eps;
	int max_iter;

	/* linear system parameters */
	int* nonzero;
        int** col;
        double** val;

	double* b;
	double* z;
	double* cor_x;
	double* cor_y;
	int n;
	
	/* theorectical values*/
	double* f;
	double* u;
};

#endif
