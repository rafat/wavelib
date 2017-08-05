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

double mad(double *x, int N) {
	double sigma;
	int i;
	
	sigma = median(x,N);
	
	for(i = 0; i < N;++i) {
		x[i] = (x[i] - sigma) > 0 ? (x[i] - sigma) : -(x[i] - sigma);
	}
	
	sigma = median(x,N);
	
	return sigma;
}

void visushrink(wave_object wave,double *signal,int N) {
	int J,filt_len;
	double sigma;
	
	filt_len = wave->filtlength;
	
	J = (int) (log((double)N / ((double)filt_len - 1.0)) / log(2.0));
}
 
int main(void)
{
    double x[10] = { 1123.78,234,40,-34,-56.89,98,0.2,23.9,-1236.3,3.14};
    
 
    printf("Mad %g \n",mad(x,10));
    
}
