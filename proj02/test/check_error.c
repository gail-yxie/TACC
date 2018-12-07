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
	
	/* Open and read files*/
	fsol = fopen(argv[2], "r");
	if(fsol == NULL)
		exit(1);
	
	fref = fopen(argv[3], "r");
	if(fref == NULL)
		exit(1);
	
	/* Read data and calculate error */
	for(i=0;i<n;i++)
	{
		fscanf(fsol, "%lf", &sol[i]);
		fscanf(fref, "%lf", &ref[i]);
		error = error + (ref[i] - sol[i]) * (ref[i] - sol[i]);
	}

	error = sqrt(error/n);	

        fclose(fsol);
        fclose(fref);

	printf("%.14f\n", error);

	return 0;
}
