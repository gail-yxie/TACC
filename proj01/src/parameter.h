#include <stdio.h>

#ifndef PARAMETER_H
#define PARAMETER_H

struct Matrix{

        int* nonzero;
        int** col;
        double** val;

};

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

	/* solver parameters */
	
	int fd_method;
	int iter_method;
	double eps
	int max_iter;

	/* linear system parameters */
	Matrix* A;
	double* b;
	double* z;
};

#endif
