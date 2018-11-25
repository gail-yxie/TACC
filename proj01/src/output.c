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
}
