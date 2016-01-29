#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../header/wavelib.h"

int main() {
	int i, J, N, len;
	int X, Y;
	wave_object obj;
	wtree_object wt;
	double *inp, *oup;

	char *name = "db3";
	obj = wave_init(name);// Initialize the wavelet
	N = 147;
	inp = (double*)malloc(sizeof(double)* N);
	for (i = 1; i < N + 1; ++i) {
		inp[i - 1] = -0.25*i*i*i + 25 * i *i + 10 * i;
	}
	J = 3;

	wt = wtree_init(obj, N, J);// Initialize the wavelet transform object
	setWTREEExtension(wt, "sym");// Options are "per" and "sym". Symmetric is the default option

	wtree(wt, inp);
	wtree_summary(wt);
	X = 3;
	Y = 5;
	len = getWTREENodelength(wt, X);
	printf("\n %d", len);
	printf("\n");
	oup = (double*)malloc(sizeof(double)* len);

	printf("Node [%d %d] Coefficients : \n",X,Y);
	getWTREECoeffs(wt, X, Y, oup, len);
	for (i = 0; i < len; ++i) {
		printf("%g ", oup[i]);
	}
	printf("\n");

	free(inp);
	free(oup);
	wave_free(obj);
	wtree_free(wt);
	return 0;
}
