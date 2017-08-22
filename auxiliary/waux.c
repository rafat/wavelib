#include "waux.h"

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

int minindex(double *arr, int N) {
	double min;
	int index,i;

	min = DBL_MAX;
	index = 0;
	for(i = 0; i < N;++i) {
		if (arr[i] < min) {
			min = arr[i];
			index = i;
		}
	}

	return index;

}

void getDWTAppx(wt_object wt, double *appx,int N) {
	/*
	Wavelet decomposition is stored as
	[A(J) D(J) D(J-1) ..... D(1)] in wt->output vector

	Length of A(J) , N = wt->length[0]
	*/
	int i;

	for (i = 0; i < N; ++i) {
		appx[i] = wt->output[i];
	}
}

void getDWTDetail(wt_object wt, double *detail, int N, int level) {
	/*
	returns Detail coefficents at the jth level where j = 1,2,.., J
	and Wavelet decomposition is stored as
	[A(J) D(J) D(J-1) ..... D(1)] in wt->output vector
	Use getDWTAppx() to get A(J)
	Level 1 : Length of D(J), ie N, is stored in wt->length[1]
	Level 2 :Length of D(J-1), ie N, is stored in wt->length[2]
	....
	Level J : Length of D(1), ie N, is stored in wt->length[J]
	*/
	int i, iter, J;
	J = wt->J;

	if (level > J) {
		printf("The decomposition only has %d levels", J);
	}

	iter = wt->length[0];

	for (i = 1; i < level; ++i) {
		iter += wt->length[i];
	}

	for (i = 0; i < N; ++i) {
		detail[i] = wt->output[i + iter];
	}
}


