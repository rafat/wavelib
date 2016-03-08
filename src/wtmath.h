/*
Copyright (c) 2014, Rafat Hussain
*/
#ifndef WTMATH_H_
#define WTMATH_H_

#include "wavefilt.h"

#ifdef __cplusplus
extern "C" {
#endif

int upsamp(double *x, int lenx, int M, double *y);

int upsamp2(double *x, int lenx, int M, double *y);

int downsamp(double *x, int lenx, int M, double *y);

int per_ext(double *sig, int len, int a,double *oup);

int symm_ext(double *sig, int len, int a,double *oup);

void circshift(double *array, int N, int L);

int testSWTlength(int N, int J);

int wmaxiter(int sig_len, int filt_len);

double costfunc(double *x, int N, char *entropy, double p);

#ifdef __cplusplus
}
#endif


#endif /* WAVELIB_H_ */
