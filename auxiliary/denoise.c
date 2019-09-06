#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "waux.h"
#include "../header/wauxlib.h"

denoise_object denoise_init(int length, int J,const char* wname) {
	denoise_object obj = NULL;

	obj = (denoise_object)malloc(sizeof(struct denoise_set) +sizeof(double));

	obj->N = length;
	obj->J = J;

	strcpy(obj->wname,wname);

	//Set Default Values
	strcpy(obj->dmethod,"sureshrink");
	strcpy(obj->ext,"sym");
	strcpy(obj->level,"all");
	strcpy(obj->thresh,"soft");
	strcpy(obj->wmethod,"dwt");
	strcpy(obj->cmethod,"direct");

	return obj;
}

void visushrink(double *signal,int N,int J,const char *wname,const char *method,const char *ext,const char *thresh,const char *level,double *denoised) {
	int filt_len,iter,i,dlen,dwt_len,sgn, MaxIter,it;
	double sigma,td,tmp;
	wave_object wave;
	wt_object wt;
	double *dout,*lnoise;

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
	} else {
		printf("Acceptable WT methods are - dwt,swt and modwt\n");
		exit(-1);
	}

	lnoise = (double*)malloc(sizeof(double) * J);

	//Set sigma

	iter = wt->length[0];
	dlen = wt->length[J];

	dout = (double*)malloc(sizeof(double) * dlen);

	if(!strcmp(level,"first")) {
		for (i = 1; i < J; ++i) {
			iter += wt->length[i];
		}

		for(i = 0; i < dlen;++i) {
			dout[i] = fabs(wt->output[iter+i]);
		}

		sigma = median(dout,dlen) / 0.6745;
		for(it = 0; it < J;++it) {
			lnoise[it] = sigma;
		}
	} else if(!strcmp(level,"all")){
		for(it = 0; it < J;++it) {
			dlen = wt->length[it+1];
			for(i = 0; i < dlen;++i) {
				dout[i] = fabs(wt->output[iter+i]);
			}
			sigma = median(dout,dlen) / 0.6745;
			lnoise[it] = sigma;
			iter += dlen;
		}

	} else {
		printf("Acceptable Noise estimation level values are - first and all \n");
		exit(-1);
	}

	dwt_len = wt->outlength;
	iter = wt->length[0];
	for(it = 0; it < J;++it) {
		sigma = lnoise[it];
		dlen = wt->length[it+1];
		td = sqrt(2.0 * log(dwt_len)) * sigma;

		if(!strcmp(thresh,"hard")) {
			for(i = 0; i < dlen;++i) {
				if (fabs(wt->output[iter+i]) < td) {
					wt->output[iter+i] = 0;
				}
			}
		} else if(!strcmp(thresh,"soft")) {
			for(i = 0; i < dlen;++i) {
					if (fabs(wt->output[iter + i]) < td) {
						wt->output[iter+i] = 0;
					} else {
						sgn = wt->output[iter+i] >= 0 ? 1 : -1;
						tmp = sgn * (fabs(wt->output[iter+i]) - td);
						wt->output[iter+i] = tmp;
					}
				}
		}

		iter += wt->length[it+1];
	}

	if(!strcmp(method,"dwt")) {
		idwt(wt,denoised);
	} else if(!strcmp(method,"swt")) {
		iswt(wt,denoised);
	}

	free(dout);
	free(lnoise);
	wave_free(wave);
	wt_free(wt);
}

void sureshrink(double *signal,int N,int J,const char *wname,const char *method,const char *ext,const char *thresh,const char *level,double *denoised) {
	int filt_len,i,it,len,dlen,dwt_len,min_index,sgn, MaxIter,iter;
	double sigma,norm,td,tv,te,ct,thr,temp,x_sum;
	wave_object wave;
	wt_object wt;
	double *dout,*risk,*dsum,*lnoise;

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
	} else {
		printf("Acceptable WT methods are - dwt and swt\n");
		exit(-1);
	}

	len = wt->length[0];
	dlen = wt->length[J];

	dout = (double*)malloc(sizeof(double) * dlen);
	risk = (double*)malloc(sizeof(double) * dlen);
	dsum = (double*)malloc(sizeof(double) * dlen);
	lnoise = (double*)malloc(sizeof(double) * J);

	iter = wt->length[0];

	if(!strcmp(level,"first")) {
		for (i = 1; i < J; ++i) {
			iter += wt->length[i];
		}

		for(i = 0; i < dlen;++i) {
			dout[i] = fabs(wt->output[iter+i]);
		}

		sigma = median(dout,dlen) / 0.6745;
		for(it = 0; it < J;++it) {
			lnoise[it] = sigma;
		}
	} else if(!strcmp(level,"all")){
		for(it = 0; it < J;++it) {
			dlen = wt->length[it+1];
			for(i = 0; i < dlen;++i) {
				dout[i] = fabs(wt->output[iter+i]);
			}
			sigma = median(dout,dlen) / 0.6745;
			lnoise[it] = sigma;
			iter += dlen;
		}

	} else {
		printf("Acceptable Noise estimation level values are - first and all \n");
		exit(-1);
	}


	for(it = 0; it < J;++it) {
		dwt_len = wt->length[it+1];
		sigma = lnoise[it];

		if ( sigma < 0.00000001) {
			td = 0;
		} else {
			tv = sqrt(2.0 * log(dwt_len));
			norm = 0.0;
			for(i = 0; i < dwt_len;++i) {
				norm += (wt->output[len+i] *wt->output[len+i] /(sigma*sigma));
			}
			te =(norm - (double) dwt_len)/(double) dwt_len;
			ct = pow(log((double) dwt_len)/log(2.0),1.5)/sqrt((double) dwt_len);

			if (te < ct) {
				td = tv;
			} else {
				x_sum = 0.0;

				for(i = 0; i < dwt_len;++i) {
					dout[i] = fabs(wt->output[len+i]/sigma);
				}

				qsort(dout, dwt_len, sizeof(double), compare_double);
				for(i = 0; i < dwt_len;++i) {
					dout[i] = (dout[i]*dout[i]);
					x_sum += dout[i];
					dsum[i] = x_sum;
				}

				for(i = 0;i < dwt_len;++i) {
					risk[i] = ((double)dwt_len - 2 * ((double)i + 1) +dsum[i] +
							dout[i]*((double)dwt_len - 1 -(double) i))/(double)dwt_len;
				}
				min_index = minindex(risk,dwt_len);
				thr = sqrt(dout[min_index]);
				td = thr < tv ? thr : tv;
			}
		}

		td = td * sigma;

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
	}
	free(dout);
	free(dsum);
	free(risk);
	free(lnoise);
	wave_free(wave);
	wt_free(wt);
}

void modwtshrink(double *signal, int N, int J, const char *wname, const char *cmethod, const char *ext, const char *thresh, double *denoised) {
	int filt_len, iter, i, dlen, sgn, MaxIter, it;
	double sigma, td, tmp, M, llen;
	wave_object wave;
	wt_object wt;
	double *dout, *lnoise;

	wave = wave_init(wname);

	filt_len = wave->filtlength;

	MaxIter = (int)(log((double)N / ((double)filt_len - 1.0)) / log(2.0));

	if (J > MaxIter) {
		printf("\n Error - The Signal Can only be iterated %d times using this wavelet. Exiting\n", MaxIter);
		exit(-1);
	}

	wt = wt_init(wave, "modwt", N, J);

	if (!strcmp(ext, "sym") && !strcmp(cmethod,"fft")) {
		setWTConv(wt, "fft");
		setDWTExtension(wt, "sym");
	}
	else if (!strcmp(ext, "sym") && !strcmp(cmethod, "direct")) {
		printf("Symmetric Extension is not available for direct method");
		exit(-1);
	}
	else if (!strcmp(ext, "per") && !strcmp(cmethod, "direct"))  {
		setWTConv(wt, "direct");
		setDWTExtension(wt, "per");
	}
	else if (!strcmp(ext, "per") && !strcmp(cmethod, "fft"))  {
		setWTConv(wt, "fft");
		setDWTExtension(wt, "per");
	}
	else {
		printf("Signal extension can be either per or sym");
		exit(-1);
	}

	modwt(wt, signal);

	lnoise = (double*)malloc(sizeof(double)* J);

	//Set sigma

	iter = wt->length[0];
	dlen = wt->length[J];
	dout = (double*)malloc(sizeof(double)* dlen);

	for (it = 0; it < J; ++it) {
		dlen = wt->length[it + 1];
		for (i = 0; i < dlen; ++i) {
			dout[i] = fabs(wt->output[iter + i]);
		}

		sigma = sqrt(2.0) * median(dout, dlen) / 0.6745;
		lnoise[it] = sigma;
		iter += dlen;
	}

	M = pow(2.0,J);
	llen = log((double)wt->modwtsiglength);
	// Thresholding

	iter = wt->length[0];
	for (it = 0; it < J; ++it) {
		sigma = lnoise[it];
		dlen = wt->length[it + 1];
		td = sqrt(2.0 * llen / M) * sigma;

		if (!strcmp(thresh, "hard")) {
			for (i = 0; i < dlen; ++i) {
				if (fabs(wt->output[iter + i]) < td) {
					wt->output[iter + i] = 0;
				}
			}
		}
		else if (!strcmp(thresh, "soft")) {
			for (i = 0; i < dlen; ++i) {
				if (fabs(wt->output[iter + i]) < td) {
					wt->output[iter + i] = 0;
				}
				else {
					sgn = wt->output[iter + i] >= 0 ? 1 : -1;
					tmp = sgn * (fabs(wt->output[iter + i]) - td);
					wt->output[iter + i] = tmp;
				}
			}
		}

		iter += wt->length[it + 1];
		M /= 2.0;
	}

	imodwt(wt, denoised);

	free(dout);
	free(lnoise);
	wave_free(wave);
	wt_free(wt);
}


void denoise(denoise_object obj, double *signal,double *denoised) {
	if(!strcmp(obj->dmethod,"sureshrink")) {
		if (!strcmp(obj->wmethod, "modwt")) {
			printf("sureshrink method only works with swt and dwt. Please use setDenoiseWTMethod to set the correct method\n");
			exit(-1);
		}
		sureshrink(signal,obj->N,obj->J,obj->wname,obj->wmethod,obj->ext,obj->thresh,obj->level,denoised);
	} else if(!strcmp(obj->dmethod,"visushrink")) {
		if (!strcmp(obj->wmethod, "modwt")) {
			printf("visushrink method only works with swt and dwt. Please use setDenoiseWTMethod to set the correct method\n");
			exit(-1);
		}
		visushrink(signal,obj->N,obj->J,obj->wname,obj->wmethod,obj->ext,obj->thresh,obj->level,denoised);;
	} else if(!strcmp(obj->dmethod,"modwtshrink")) {
		if (strcmp(obj->wmethod, "modwt")) {
			printf("modwtshrink method only works with modwt. Please use setDenoiseWTMethod to set the correct method\n");
			exit(-1);
		}
		modwtshrink(signal,obj->N,obj->J,obj->wname,obj->cmethod,obj->ext,obj->thresh,denoised);;
	} else {
		printf("Acceptable Denoising methods are - sureshrink and visushrink\n");
		exit(-1);
	}
}

void setDenoiseMethod(denoise_object obj, const char *dmethod) {
	if (!strcmp(dmethod, "sureshrink")) {
		strcpy(obj->dmethod, "sureshrink");
	}
	else if (!strcmp(dmethod, "visushrink")) {
		strcpy(obj->dmethod, "visushrink");
	}
	 else if (!strcmp(dmethod, "modwtshrink")) {
		strcpy(obj->dmethod, "modwtshrink");
	}
	else {
		printf("Acceptable Denoising methods are - sureshrink, visushrink and modwtshrink\n");
		exit(-1);
	}
}

void setDenoiseWTMethod(denoise_object obj, const char *wmethod) {
	if (!strcmp(wmethod, "dwt")) {
		strcpy(obj->wmethod, "dwt");
	}
	else if (!strcmp(wmethod, "swt")) {
		strcpy(obj->wmethod, "swt");
	}
	 else if (!strcmp(wmethod, "modwt")) {
		strcpy(obj->wmethod, "modwt");
	}
	else {
		printf("Wavelet decomposition method can be one of dwt, modwt or swt.\n");
		exit(-1);
	}
}

void setDenoiseWTExtension(denoise_object obj, const char *extension) {
	if (!strcmp(extension, "sym")) {
		strcpy(obj->ext, "sym");
	}
	else if (!strcmp(extension, "per")) {
		strcpy(obj->ext, "per");
	}
	else {
		printf("Signal extension can be either per or sym");
		exit(-1);
	}
}

void setDenoiseParameters(denoise_object obj, const char *thresh,const char *level) {

	//Set thresholding
	if (!strcmp(thresh, "soft")) {
		strcpy(obj->thresh, "soft");
	}
	else if (!strcmp(thresh, "hard")) {
		strcpy(obj->thresh, "hard");
	}
	else {
		printf("Thresholding Method - soft or hard");
		exit(-1);
	}

	// Set Noise estimation at the first level or at all levels

	if (!strcmp(level, "first")) {
		strcpy(obj->level, "first");
	}
	else if (!strcmp(level, "all")) {
		strcpy(obj->level, "all");
	}
	else {
		printf("Noise Estimation at level - first or all");
		exit(-1);
	}
}

void denoise_free(denoise_object object) {
	free(object);
}
