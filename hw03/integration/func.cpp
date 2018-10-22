#include "func.h"
#include <cstdio>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

double fx(double x)
{
        return exp(-x*x);
}

double trapezoidal(int N)
{
        double h = 1.0/N;
        double s = fx(0) + fx(1);

        for (int i=1; i<N; i++){
                s += 2*fx(i*h);
        }
        return h * s/sqrt(M_PI);
}

double simpson(int N)
{
        double h = 1.0/N;
        double s = fx(0) + fx(1);
        for (int i=1; i<N; i++){
                if (i%2 != 0)
                        s += 4*fx(i*h);
                else
                        s += 2*fx(i*h);
        }
        return (h/3) * s * (2/sqrt(M_PI));
}
