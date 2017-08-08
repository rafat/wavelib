/*
Copyright (c) 2017, Rafat Hussain
*/
#ifndef DENOISE_H_
#define DENOISE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include "../header/wavelib.h"

#ifdef __cplusplus
extern "C" {
#endif


void visushrink(double *signal,int N,char *wname,char *method,char *ext,char *thresh,double *denoised);

void sureshrink(double *signal,int N,char *wname,char *method,char *ext,char *thresh,double *denoised);

double mad(double *x, int N);


#ifdef __cplusplus
}
#endif


#endif /* DENOISE_H_ */
