#include <cstdio>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "fx.h"
#include "simpson.h"
#include "trapezoid.h"
using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 3) {
        	printf("Error! Please input at least a method and a number!\n");
        	exit(0);
    	}
 
	int N = stoi(argv[2]);
	int method = stoi(argv[1]);
	double inte;
	double error;
	double stand = 0.84270079295;
 	
	/* if method is 1, we use trapezodial rule, 2 is simpson's rule.*/
	if (method == 1){
		inte = trapezoid(N);
		error = abs(inte - stand); 
		}
	else if (method == 2){
		inte = simpson(N);
		error = abs(inte - stand);
		}
	else
		printf("Error, please input method 1 or 2!\n");
	printf("%d %d %0.11f %0.11f\n", method, N, inte, error);
	return 0;
}
