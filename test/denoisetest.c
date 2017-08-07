#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../header/denoise.h"

int main() {
	double x[10] = {1.2,4.3,-0.7,90,4.7,123.5,-9.5,-100,0.0,89};

	printf("%g \n",mad(x,10));
	return 0;
}
