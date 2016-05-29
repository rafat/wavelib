#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../header/wavelib.h"

int main() {
	int i, N, J,subscale,a0,iter,nd,k;
	double *inp,*oup;
	double dt, dj,s0, param,mn;
	double td,tn,den, num, recon_mean, recon_var;
	cwt_object wt;

	FILE *ifp;
	double temp[1200];

	char *wave = "morlet";// Set Morlet wavelet. Other options "paul" and "dog"
	char *type = "pow";

	N = 504;
	param = 6.0;
	subscale = 4;
	dt = 0.25;
	s0 = dt;
	dj = 1.0 / (double)subscale;
	J = 11 * subscale; // Total Number of scales
	a0 = 2;//power

	ifp = fopen("sst_nino3.dat", "r");
	i = 0;
	if (!ifp) {
		printf("Cannot Open File");
		exit(100);
	}
	while (!feof(ifp)) {
		fscanf(ifp, "%lf \n", &temp[i]);
		i++;
	}

	fclose(ifp);

	wt = cwt_init(wave, param, N,dt, J);

	inp = (double*)malloc(sizeof(double)* N);
	oup = (double*)malloc(sizeof(double)* N);

	for (i = 0; i < N; ++i) {
		inp[i] = temp[i] ;
	}

	setCWTScales(wt, s0, dj, type, a0);

	cwt(wt, inp);

	printf("\n MEAN %g \n", wt->smean);
	
	mn = 0.0;

	for (i = 0; i < N; ++i) {
		mn += sqrt(wt->output[i].re * wt->output[i].re + wt->output[i].im * wt->output[i].im);
	}
	
	cwt_summary(wt);

	printf("\n abs mean %g \n", mn / N);
	
	printf("\n\n");
	printf("Let CWT w = w(j, n/2 - 1) where n = %d\n\n", N);
	nd = N/2 - 1;
	
	printf("%-15s%-15s%-15s%-15s \n","j","Scale","Period","ABS(w)^2");
	for(k = 0; k < wt->J;++k) {
		iter = nd + k * N;
		printf("%-15d%-15lf%-15lf%-15lf \n",k,wt->scale[k],wt->period[k],
		wt->output[iter].re * wt->output[iter].re + wt->output[iter].im * wt->output[iter].im);
	}

	icwt(wt, oup);

	num = den = recon_var = recon_mean = 0.0;
	printf("\n\n");
	printf("Signal Reconstruction\n");
	printf("%-15s%-15s%-15s \n","i","Input(i)","Output(i)");

	for (i = N - 10; i < N; ++i) {
		printf("%-15d%-15lf%-15lf \n", i,inp[i] , oup[i]);
	}

	for (i = 0; i < N; ++i) {
		//printf("%g %g \n", oup[i] ,inp[i] - wt->smean);
		td = inp[i] ;
		tn = oup[i] - td;
		num += (tn * tn);
		den += (td * td);
		recon_mean += oup[i];
	}

	recon_var = sqrt(num / N);
	recon_mean /= N;

	printf("\nRMS Error %g \n", sqrt(num) / sqrt(den));
	printf("\nVariance %g \n", recon_var);
	printf("\nMean %g \n", recon_mean);

	free(inp);
	free(oup);
	cwt_free(wt);
	return 0;
}
