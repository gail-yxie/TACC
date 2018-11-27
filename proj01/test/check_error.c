#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
	int i,n;
	double error = 0;
	double *sol, *ref;
	
	n = atio(argv[1]);
	sol = (double*)malloc(sizeof(double)*n);
	ref = (double*)malloc(sizeof(double)*n);
	
	/* open and read files*/
	fsol = fopen(argv[2], "rb");
	fref = fopen(argv[3], "rb");
	fread(sol, 1, sizeof(double)*n, fsol);
	fread(ref, 1, sizeof(double)*n, fref);

	for(i=0;i<n;i++)
		error = error + (ref[i] - sol[i]) * (ref[i] - sol[i]);
	error = sqrt(error/n);	

	printf("%e\n", error);

	return 0;
	
}
