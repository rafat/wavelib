/*
Copyright (c) 2017, Rafat Hussain
*/
#ifndef DENOISE_H_
#define DENOISE_H_

#include "wavelib.h"

#ifdef __cplusplus
extern "C" {
#endif

//depends on J

void visushrink(double *signal,int N,int J,char *wname,char *method,char *ext,char *thresh,double *denoised);

void sureshrink(double *signal,int N,int J,char *wname,char *method,char *ext,char *thresh,double *denoised);

void getDWTRecCoeff(double *coeff,int *length,char *ctype,char *ext, int level, int J,double *lpr,
		double *hpr,int lf,int siglength,double *reccoeff);

double mad(double *x, int N);


#ifdef __cplusplus
}
#endif


#endif /* DENOISE_H_ */
