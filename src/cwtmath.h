#ifndef CWTMATH_H_
#define CWTMATH_H_

#include "wtmath.h"
#include "hsfft.h"

#ifdef __cplusplus
extern "C" {
#endif

void nsfft_exec(fft_object obj, fft_data *inp, fft_data *oup,double lb,double ub,double *w);// lb -lower bound, ub - upper bound, w - time or frequency grid (Size N)

double cwt_gamma(double x);

int nint(double N);

#ifdef __cplusplus
}
#endif


#endif /* WAVELIB_H_ */
