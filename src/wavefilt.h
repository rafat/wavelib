#ifndef WAVEFILT_H_
#define WAVEFILT_H_

#include <stdio.h>
#include "conv.h"

#ifdef __cplusplus
extern "C" {
#endif


int filtlength(char* name);

int filtcoef(char* name, double *lp1, double *hp1, double *lp2, double *hp2);


#ifdef __cplusplus
}
#endif


#endif /* WAVEFILT_H_ */