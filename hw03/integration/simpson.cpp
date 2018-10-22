#include "simpson.h"
#include "fx.h"
#include <cstdio>
#include <stdlib.h>
#include <math.h>
#include <iostream>

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
