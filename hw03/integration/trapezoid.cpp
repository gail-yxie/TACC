#include "trapezoid.h"
#include "fx.h"
#include <cstdio>
#include <stdlib.h>
#include <math.h>
#include <iostream>

double trapezoid(int N)
{
        double h = 1.0/N;
        double s = fx(0) + fx(1);

        for (int i=1; i<N; i++){
                s += 2*fx(i*h);
        }
        return h * s/sqrt(M_PI);
}
