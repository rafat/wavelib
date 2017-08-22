
#include "denoise.h"

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
	if(!strcmp(method,"dwt")) {
		setDWTExtension(wt,ext);
		dwt(wt,signal);
	} else if(!strcmp(method,"swt")) {
		swt(wt,signal);
	} else if(!strcmp(method,"modwt")) {
		modwt(wt,signal);
	} else {
		printf("Acceptable WT methods are - dwt,swt and modwt\n");
	}

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

	if(!strcmp(method,"dwt")) {
		idwt(wt,denoised);
	} else if(!strcmp(method,"swt")) {
		iswt(wt,denoised);
	} else if(!strcmp(method,"modwt")) {
		imodwt(wt,denoised);
	}

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

	if(!strcmp(method,"dwt")) {
		setDWTExtension(wt,ext);
		dwt(wt,signal);
	} else if(!strcmp(method,"swt")) {
		swt(wt,signal);
	} else if(!strcmp(method,"modwt")) {
		modwt(wt,signal);
	} else {
		printf("Acceptable WT methods are - dwt,swt and modwt\n");
	}

	len = wt->length[0];
	dlen = wt->length[J];

	dout = (double*)malloc(sizeof(double) * dlen);
	risk = (double*)malloc(sizeof(double) * dlen);

	for(it = 0; it < J;++it) {
		dwt_len = wt->length[it+1];

		for(i = 0; i < dwt_len;++i) {
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

				for(i = 0; i < dwt_len;++i) {
					dout[i] = wt->output[len+i];
				}

				qsort(dout, dwt_len, sizeof(double), compare_double);
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

	if(!strcmp(method,"dwt")) {
		idwt(wt,denoised);
	} else if(!strcmp(method,"swt")) {
		iswt(wt,denoised);
	} else if(!strcmp(method,"modwt")) {
		imodwt(wt,denoised);
	}

	free(dout);
	free(risk);
	wave_free(wave);
	wt_free(wt);
}
