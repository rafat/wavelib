/*
Copyright (c) 2014, Rafat Hussain
*/
#include "wtmath.h"

int upsamp(double *x, int lenx, int M, double *y) {
	int N, i, j, k;

	if (M < 0) {
		return -1;
	}

	if (M == 0) {
		for (i = 0; i < lenx; ++i) {
			y[i] = x[i];
		}
		return lenx;
	}

	N = M * (lenx - 1) + 1;
	j = 1;
	k = 0;

	for (i = 0; i < N; ++i) {
		j--;
		y[i] = 0.0;
		if (j == 0) {
			y[i] = x[k];
			k++;
			j = M;
		}
	}

	return N;
}

int upsamp2(double *x, int lenx, int M, double *y) {
	int N, i, j, k;
	// upsamp2 returns even numbered output. Last value is set to zero
	if (M < 0) {
		return -1;
	}

	if (M == 0) {
		for (i = 0; i < lenx; ++i) {
			y[i] = x[i];
		}
		return lenx;
	}

	N = M * lenx;
	j = 1;
	k = 0;

	for (i = 0; i < N; ++i) {
		j--;
		y[i] = 0.0;
		if (j == 0) {
			y[i] = x[k];
			k++;
			j = M;
		}
	}

	return N;
}

int downsamp(double *x, int lenx, int M, double *y) {
	int N, i;

	if (M < 0) {
		return -1;
	}
	if (M == 0) {
		for (i = 0; i < lenx; ++i) {
			y[i] = x[i];
		}
		return lenx;
	}

	N = (lenx - 1) / M + 1;

	for (i = 0; i < N; ++i) {
		y[i] = x[i*M];
	}

	return N;
}
/*
int per_ext(double *sig, int len, int a,double *oup) {
	int i,len2;
	// oup is of length len + (len%2) + 2 * a
	for (i = 0; i < len; ++i) {
		oup[a + i] = sig[i];
	}
	len2 = len;
	if ((len % 2) != 0) {
		len2 = len + 1;
		oup[a + len] = sig[len - 1];
	}
	for (i = 0; i < a; ++i) {
		oup[a-1-i] = sig[len - 1 - i];
		oup[len2 + a + i] = sig[i];
	}

	return len2;

}
*/

int per_ext(double *sig, int len, int a, double *oup) {
	int i, len2;
	double temp1;
	double temp2;
	for (i = 0; i < len; ++i) {
		oup[a + i] = sig[i];
	}
	len2 = len;
	if ((len % 2) != 0) {
		len2 = len + 1;
		oup[a + len] = sig[len - 1];
	}
	for (i = 0; i < a; ++i) {
		temp1 = oup[a + i];
		temp2 = oup[a + len2 - 1 - i];
		oup[a - 1 - i] = temp2;
		oup[len2 + a + i] = temp1;
	}
	return len2;
}
/*
int symm_ext(double *sig, int len, int a, double *oup) {
	int i, len2;
	// oup is of length len + 2 * a
	for (i = 0; i < len; ++i) {
		oup[a + i] = sig[i];
	}
	len2 = len;
	for (i = 0; i < a; ++i) {
		oup[a - 1 - i] = sig[i];
		oup[len2 + a + i] = sig[len - 1 - i];
	}

	return len2;

}
*/

int symm_ext(double *sig, int len, int a, double *oup) {
	int i, len2;
	double temp1;
	double temp2;
	// oup is of length len + 2 * a
	for (i = 0; i < len; ++i) {
		oup[a + i] = sig[i];
	}
	len2 = len;
	for (i = 0; i < a; ++i) {
		temp1 = oup[a + i];
		temp2 = oup[a + len2 - 1 - i];
		oup[a - 1 - i] = temp1;
		oup[len2 + a + i] = temp2;
	}

	return len2;

}

static int isign(int N) {
	int M;
	if (N >= 0) {
		M = 1;
	}
	else {
		M = -1;
	}

	return M;
}

static int iabs(int N) {
	if (N >= 0) {
		return N;
	}
	else {
		return -N;
	}
}

void circshift(double *array, int N, int L) {
	int i;
	double *temp;
	if (iabs(L) > N) {
		L = isign(L) * (iabs(L) % N);
	}
	if (L < 0) {
		L = (N + L) % N;
	}

	temp = (double*)malloc(sizeof(double) * L);

	for (i = 0; i < L; ++i) {
		temp[i] = array[i];
	}

	for (i = 0; i < N - L; ++i) {
		array[i] = array[i + L];
	}

	for (i = 0; i < L; ++i) {
		array[N - L + i] = temp[i];
	}

	free(temp);
}

int testSWTlength(int N, int J) {
	int ret,div,i;
	ret = 1;

	div = 1;
	for (i = 0; i < J; ++i) {
		div *= 2;
	}

	if (N % div) {
		ret = 0;
	}

	return ret;

}

int wmaxiter(int sig_len, int filt_len) {
	int lev;
	double temp;

	temp = log((double)sig_len / ((double)filt_len - 1.0)) / log(2.0);
	lev = (int)temp;

	return lev;
}

static double entropy_s(double *x,int N) {
  int i;
  double val,x2;

  val = 0.0;

  for(i = 0; i < N; ++i) {
    if (x[i] != 0) {
      x2 = x[i] * x[i];
      val -= x2 * log(x2);
    }
  }
  return val;
}

static double entropy_t(double *x,int N, double t) {
  int i;
  double val,x2;
  if (t < 0) {
    printf("Threshold value must be >= 0");
    exit(1);
  }
  val = 0.0;

  for(i = 0; i < N; ++i) {
    x2 = fabs(x[i]);
    if (x2 > t) {
      val += 1;
    }

  }

  return val;

}

static double entropy_n(double *x,int N,double p) {
  int i;
  double val,x2;
  if (p < 1) {
    printf("Norm power value must be >= 1");
    exit(1);
  }
  val = 0.0;
  for(i = 0; i < N; ++i) {
    x2 = fabs(x[i]);
    val += pow(x2,(double)p);

  }

  return val;
}

static double entropy_l(double *x,int N) {
  int i;
  double val,x2;

  val = 0.0;

  for(i = 0; i < N; ++i) {
    if (x[i] != 0) {
      x2 = x[i] * x[i];
      val += log(x2);
    }
  }
  return val;
}

double costfunc(double *x, int N ,char *entropy,double p) {
	double val;

	if (!strcmp(entropy, "shannon")) {
		val = entropy_s(x, N);
	}
	else if (!strcmp(entropy, "threshold")) {
		val = entropy_t(x, N,p);
	}
	else if (!strcmp(entropy, "norm")) {
		val = entropy_n(x, N,p);
	}
	else if (!strcmp(entropy, "logenergy") || !strcmp(entropy, "log energy") || !strcmp(entropy, "energy")) {
		val = entropy_l(x, N);
	}
	else {
		printf("Entropy must be one of shannon, threshold, norm or energy");
		exit(-1);
	}

	return val;
}
