#include <stdio.h>
#include "matrix.h"

#ifndef FUNCTION_H
#define FUNCTION_H

/* Function prototypes */

void parss_input();
void init();
void build_linear_system();
void solve_system(int n, char* iter_method);
void output();
double error_norm(double* x, double* dx);

/* Global state variables */

#endif
