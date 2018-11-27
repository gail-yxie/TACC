#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
	int i,n;
	double error = 0;
	double *sol, *ref;
	FILE *fsol, *fref;
	
	n = atoi(argv[1]);
	sol = (double*)malloc(sizeof(double)*n);
	ref = (double*)malloc(sizeof(double)*n);
	
	/* open and read files*/
	fsol = fopen(argv[2], "r");
	fref = fopen(argv[3], "r");

	for(i=0;i<n;i++)
	{
		fscanf(fsol, "%f ", &sol[i]);
		fscanf(fref, "%f ", &ref[i]);
		error = error + (ref[i] - sol[i]) * (ref[i] - sol[i]);
		printf("%f %f\n", sol[i], ref[i]);
	}
	error = sqrt(error/n);	

	printf("%e\n", error);

	return 0;
	
}
