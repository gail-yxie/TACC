#include <stdio.h>
#include "matrix.h"

#ifndef FUNCTION_H
#define FUNCTION_H

/* Function prototypes */

void parse_input(Parameter*solver, const char* input_file);
void init(Parameter* solver);
void build_linear_system(Parameter* solver);
void solve_system(Parameter* solver);;
void output(*Parameter solver);;
double error_norm(*Parameter solver);

#endif
