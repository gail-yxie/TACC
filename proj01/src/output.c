#include <stdio.h>
#include <stdlib.h>
#include "parameter.h"

void output(Parameter* solver)
{
	/* silent mode */
	if(solver.output_mode == 0)
	{
		//only output the result solver.z;
	}
	
	/* standard mode */
	if(solver.output_mode == 1)
	{
	
	}
	
	/* debug mode */
	if(solver.output_mode == 2)
	{
	
	}
	
	 /* Free dynamic variables*/
        free(solver.output_file);
        free(solver.b);
        free(solver.z);
        free(solver.A.nonzero);
	for(i=0;i<solver.n;i++)
	{
		free(solver.A.col[i]);
		free(solver.A.val[i]);
	}
        free(solver.f);
        free(solver.u)
}
