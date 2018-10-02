#include <iostream>
#include <time.h>
#include <cstdlib>
#include <stdlib.h>

using namespace std;


int main()
{
    /* code */
    int i, k;
    int N_samples, N_o, N_i;
    double x, y, dist, pi_estimate, e_rel;
    double pi;	

    cin >> N_samples;
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
    
    cout << N_samples<<" "<< N_i<<" "<< N_o << " "<< pi_estimate<<" "<<e_rel;

    return 0;
}
