#include <matrix.h>

#ifndef FUNCTION_H
#define FUNCTION_H

// Read data from input file into parameters
int parss_input();
int init();
int build_linear_system();
int solve_system();
int output();
double error_norm();

#endif
