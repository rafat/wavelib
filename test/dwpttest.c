#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../header/wavelib.h"

double absmax(double *array, int N) {
	double max;
	int i;

	max = 0.0;
	for (i = 0; i < N; ++i) {
		if (fabs(array[i]) >= max) {
			max = fabs(array[i]);
		}
	}

	return max;
}

int main() {
	int i, J, N;
	wave_object obj;
	wpt_object wt;
	double *inp, *oup, *diff;

	char *name = "db4";
	obj = wave_init(name);// Initialize the wavelet
	N = 788 + 23;
	inp = (double*)malloc(sizeof(double)* N);
	oup = (double*)malloc(sizeof(double)* N);
	diff = (double*)malloc(sizeof(double)* N);
	for (i = 1; i < N + 1; ++i) {
		//inp[i - 1] = -0.25*i*i*i + 25 * i *i + 10 * i;
		inp[i - 1] = i;
	}
	J = 4;

	wt = wpt_init(obj, N, J);// Initialize the wavelet transform Tree object
	setDWPTExtension(wt, "per");// Options are "per" and "sym". Symmetric is the default option
	setDWPTEntropy(wt, "logenergy", 0);

	dwpt(wt, inp); // Discrete Wavelet Packet Transform

	idwpt(wt, oup); // Inverse Discrete Wavelet Packet Transform

	for (i = 0; i < N; ++i) {
		diff[i] = (inp[i] - oup[i])/inp[i];
	}

	wpt_summary(wt); // Tree Summary

	printf("\n MAX %g \n", absmax(diff, wt->siglength)); // If Reconstruction succeeded then the output should be a small value.

	free(inp);
	free(oup);
	free(diff);
	wave_free(obj);
	wpt_free(wt);
	return 0;
}
