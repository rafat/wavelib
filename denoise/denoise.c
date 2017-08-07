
#include "denoise.h"

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

void visushrink(double *signal,int N,char *wname,char *method,char *ext,char *thresh,double *denoised) {
	int J,filt_len,iter,i,dlen,dwt_len,sgn;
	double sigma,td,tmp;
	wave_object wave;
	wt_object wt;

	wave = wave_init(wname);
	
	filt_len = wave->filtlength;
	
	J = (int) (log((double)N / ((double)filt_len - 1.0)) / log(2.0));

	if (J > 50) {
		J = 50;
	}

	wt = wt_init(wave,method,N,J);
	setDWTExtension(wt,ext);

	dwt(wt,signal);

	//Set sigma

	iter = wt->length[0];
	dlen = wt->length[J];

	for (i = 1; i < J; ++i) {
		iter += wt->length[i];
	}

	sigma = mad(wt->output+iter,dlen);
	dwt_len = wt->outlength;

	td = sqrt(2.0 * log(dwt_len)) * sigma / 0.6745;

	if(!strcmp(thresh,"hard")) {
		for(i = 0; i < dwt_len;++i) {
			if (fabs(wt->output[i]) < td) {
				wt->output[i] = 0;
			}
		}
	} else if(!strcmp(thresh,"soft")) {
		for(i = 0; i < dwt_len;++i) {
				if (fabs(wt->output[i]) < td) {
					wt->output[i] = 0;
				} else {
					sgn = wt->output[i] >= 0 ? 1 : -1;
					tmp = sgn * (fabs(wt->output[i]) - td);
					wt->output[i] = tmp;
				}
			}
	}

	idwt(wt,denoised);

	wave_free(wave);
	wt_free(wt);
}
