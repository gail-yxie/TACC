#include <time.h>
#include <cstdio>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
    if (argc <2) {
        printf ("Error! Please input at least one number!\n");
        exit(0);
     }

    /* code */
    int i, k;
    int N_o, N_i;
    double x, y, dist, pi_estimate, e_rel;
    double pi, dur;
    int N_samples = stoi(argv[1]);

    srand(time(0));

    N_o = 0;
    N_i = 0;
    pi = 3.141592653589793;

    for (i = 1; i <= N_samples; i++){
        x = rand()/double(RAND_MAX);
        y = rand()/double(RAND_MAX);
        dist = x*x + y*y;

        if (dist > 1)
            N_o++;

    }

    N_i = N_samples - N_o;
    pi_estimate = double(4 * N_i) / N_samples;
    e_rel = pi_estimate/pi - 1;

    if (e_rel < 0)
        e_rel = - e_rel;

    printf ("%d %d %d %0.15f %0.4f ", N_samples, N_i, N_o, pi_estimate, e_rel);

    return 0;
}