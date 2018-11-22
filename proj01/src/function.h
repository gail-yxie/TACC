#include <matrix.h>

#ifndef FUNCTION_H
#define FUNCTION_H

// Read data from input file into parameters
void parss_input();
void init();
void build_linear_system();
void solve_system();
void output();
double error_norm();

#endif
