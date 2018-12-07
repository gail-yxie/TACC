#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "parameter.h"
#include <grvy.h>
#include <masa.h>

#ifndef FUNCTION_H
#define FUNCTION_H

/* Function prototypes */

void parse_input(struct Parameter* solver, const char* input_file);
void init(struct Parameter* solver);
void build_linear_system(struct Parameter* solver);
void solve_system(struct Parameter* solver);
void output(struct Parameter* solver);
double error_norm(double* vecx, double* vecy, int vecn);

#endif
