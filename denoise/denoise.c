
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

void visushrink(double *signal,int N,int J,char *wname,char *method,char *ext,char *thresh,double *denoised) {
	int filt_len,iter,i,dlen,dwt_len,sgn, MaxIter;
	double sigma,td,tmp;
	wave_object wave;
	wt_object wt;
	double *dout;

	wave = wave_init(wname);
	
	filt_len = wave->filtlength;
	
	MaxIter = (int) (log((double)N / ((double)filt_len - 1.0)) / log(2.0));

	if (J > MaxIter) {
		printf("\n Error - The Signal Can only be iterated %d times using this wavelet. Exiting\n",MaxIter);
		exit(-1);
	}

	wt = wt_init(wave,method,N,J);
	setDWTExtension(wt,ext);

	dwt(wt,signal);

	//Set sigma

	iter = wt->length[0];
	dlen = wt->length[J];

	dout = (double*)malloc(sizeof(double) * dlen);

	for (i = 1; i < J; ++i) {
		iter += wt->length[i];
	}

	for(i = 0; i < dlen;++i) {
		dout[i] = wt->output[iter+i];
	}

	sigma = mad(dout,dlen);
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

	free(dout);
	wave_free(wave);
	wt_free(wt);
}

void sureshrink(double *signal,int N,int J,char *wname,char *method,char *ext,char *thresh,double *denoised) {
	int filt_len,i,it,len,dlen,dwt_len,min_index,sgn, MaxIter;
	double sigma,norm,td,tv,te,ct,thr,temp,x_sum;
	wave_object wave;
	wt_object wt;
	double *dout,*risk;

	wave = wave_init(wname);

	filt_len = wave->filtlength;

	MaxIter = (int) (log((double)N / ((double)filt_len - 1.0)) / log(2.0));
	// Depends on J
	if (J > MaxIter) {
		printf("\n Error - The Signal Can only be iterated %d times using this wavelet. Exiting\n",MaxIter);
		exit(-1);
	}

	wt = wt_init(wave,method,N,J);
	setDWTExtension(wt,ext);

	dwt(wt,signal);

	len = wt->length[0];
	dlen = wt->length[J];

	dout = (double*)malloc(sizeof(double) * dlen);
	risk = (double*)malloc(sizeof(double) * dlen);

	for(it = 0; it < J;++it) {
		dwt_len = wt->length[it+1];

		for(i = 0; i < dlen;++i) {
			dout[i] = wt->output[len+i];
		}

		sigma = mad(dout,dwt_len);

		if ( sigma < 0.00000001) {
			td = 0;
		} else {
			tv = sqrt(2.0 * log(dwt_len));
			norm = 0.0;
			for(i = 0; i < dwt_len;++i) {
				norm += (wt->output[len+i] *wt->output[len+i]);
			}
			te =(norm - (double) dwt_len)/(double) dwt_len;
			ct = pow(log((double) dwt_len)/log(2.0),1.5)/sqrt((double) dwt_len);

			if (te < ct) {
				td = tv;
			} else {
				x_sum = 0.0;

				for(i = 0; i < dlen;++i) {
					dout[i] = wt->output[len+i];
				}

				qsort(dout, N, sizeof(double), compare_double);
				for(i = 0; i < dwt_len;++i) {
					dout[i] = (dout[i]*dout[i]);
					x_sum += dout[i];
				}

				for(i = 0;i < dwt_len;++i) {
					risk[i] = ((double)dwt_len + 1 - 2 * ((double)i + 1) +x_sum +
							dout[i]*((double)dwt_len - 1 -(double) i))/(double)dwt_len;
				}

				min_index = minindex(risk,dwt_len);
				thr = sqrt(dout[min_index]);

				td = thr < tv ? thr : tv;
			}
		}

		td = td * sigma / 0.6745;

		if(!strcmp(thresh,"hard")) {
			for(i = 0; i < dwt_len;++i) {
				if (fabs(wt->output[len+i]) < td) {
					wt->output[len+i] = 0;
				}
			}
		} else if(!strcmp(thresh,"soft")) {
			for(i = 0; i < dwt_len;++i) {
					if (fabs(wt->output[len + i]) < td) {
						wt->output[len+i] = 0;
					} else {
						sgn = wt->output[len+i] >= 0 ? 1 : -1;
						temp = sgn * (fabs(wt->output[len+i]) - td);
						wt->output[len+i] = temp;
					}
				}
		}

		len += wt->length[it+1];
	}

	idwt(wt,denoised);

	free(dout);
	free(risk);
	wave_free(wave);
	wt_free(wt);
}
