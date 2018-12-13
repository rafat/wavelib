/*
 * waux.h
 *
 *  Created on: Aug 22, 2017
 *      Author: Rafat Hussain
 */

#ifndef AUXILIARY_WAUX_H_
#define AUXILIARY_WAUX_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include "../header/wavelib.h"

#ifdef __cplusplus
extern "C" {
#endif

int compare_double(const void* a, const void* b);

double mean(const double* vec, int N);

double var(const double* vec, int N);

double median(double *x, int N);

int minindex(const double *arr, int N);

void getDWTAppx(wt_object wt, double *appx,int N);

void getDWTDetail(wt_object wt, double *detail, int N, int level);

void autocovar(const double* vec,int N,double* acov, int M);

void autocorr(const double* vec,int N,double* acorr, int M);


#ifdef __cplusplus
}
#endif



#endif /* AUXILIARY_WAUX_H_ */
