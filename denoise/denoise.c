#include <stdio.h>
#include <stdlib.h>
#include "../header/wavelib.h"

int compare_double(const void* a, const void* b)
{
    double arg1 = *(const double*)a;
    double arg2 = *(const double*)b;
 
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
 
}

double median(double *x, int N) {
	double sigma;
 
    qsort(x, N, sizeof(double), compare_double);
    
    if ((N % 2) == 0) {
		sigma = (x[N/2 - 1] + x[N/2] ) / 2.0;
	} else {
		sigma = x[N/2];
	}
	
	return sigma;
}
 
int main(void)
{
	int i;
    double x[10] = { -2.4, 100.9,33 ,34,0,-6, -74.3, 2.9789, 271, 42 };
    
 
    printf("Median %g \n",median(x,10));
    for(i = 0; i < 10;++i) {
		printf("%g ",x[i]);
	}
}
