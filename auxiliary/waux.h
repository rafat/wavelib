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

double mean(double* vec, int N);

double var(double* vec, int N);

double median(double *x, int N);

double mad(double *x, int N);

int minindex(double *arr, int N);

void getDWTAppx(wt_object wt, double *appx,int N);

void getDWTDetail(wt_object wt, double *detail, int N, int level);

void getDWTRecCoeff(double *coeff,int *length,char *ctype,char *ext, int level, int J,double *lpr,
		double *hpr,int lf,int siglength,double *reccoeff);

void autocovar(double* vec,int N,double* acov, int M);

void autocorr(double* vec,int N,double* acorr, int M);


#ifdef __cplusplus
}
#endif



#endif /* AUXILIARY_WAUX_H_ */
