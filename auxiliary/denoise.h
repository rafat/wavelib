/*
Copyright (c) 2017, Rafat Hussain
*/
#ifndef DENOISE_H_
#define DENOISE_H_


#include "waux.h"

#ifdef __cplusplus
extern "C" {
#endif

//depends on J
void visushrink(double *signal,int N,int J,char *wname,char *method,char *ext,char *thresh,double *denoised);

void sureshrink(double *signal,int N,int J,char *wname,char *method,char *ext,char *thresh,double *denoised);


#ifdef __cplusplus
}
#endif


#endif /* DENOISE_H_ */
