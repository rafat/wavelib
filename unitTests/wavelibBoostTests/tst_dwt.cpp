/*
 * Copyright (c) 2016 Holger Nahrstaedt (TU Berlin)
 */

#include "BoostTest.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../src/wavelib.h"
#include<vector>


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

double sum1(double *array, int N) {
    double sum;
    int i;

    sum = 0.0;
    for (i = 0; i < N; ++i) {
            sum += array[i];
    }
    return sum;
}
double sum2(double *array, int N) {
    double sum;
    int i;

    sum = 0.0;
    for (i = 0; i < N; i+=2) {
        sum += array[i];
    }
    return sum;
}
double sum3(double *array, int N) {
    double sum;
    int i;

    sum = 0.0;
    for (i = 1; i < N; i += 2) {
        sum += array[i];
    }
    return sum;
}
//np.sum(w[2*m:(2*N+2*m)]*w[0:2*N])
double sum4(double *array, int N) {
    double sum;
    int i;

    sum = 0.0;
    for (i = 0; i < N; i += 1) {
        sum += array[i] * array[i];
    }
    return sum;
}
//np.sum(w[2 * m:(2 * N)] * w[0:2 * N - 2 * m])
double sum5(double *array, int N,int m) {
    double sum;
    int i;

    sum = 0.0;
    for (i = 2*m; i < N; i += 1) {
        sum += array[i] * array[i-2*m];
    }
    return sum;
}

BOOST_AUTO_TEST_SUITE(DWTTests)

BOOST_AUTO_TEST_CASE(ReconstructionTest)
{

	wave_object obj;
	wt_object wt;
	double *inp,*out,*diff;
	int N, i,J;

	FILE *ifp;
    double temp[79926];


	//ifp = fopen("s1.txt", "r");
    ifp = fopen("signal.txt", "r");
	i = 0;
	BOOST_REQUIRE(ifp);

	while (!feof(ifp)) {
		fscanf(ifp, "%lf \n", &temp[i]);
		i++;
	}
    //N = 79926;
    
    N = 256;

	inp = (double*)malloc(sizeof(double)* N);
	out = (double*)malloc(sizeof(double)* N);
	diff = (double*)malloc(sizeof(double)* N);
	//wmean = mean(temp, N);

	for (i = 0; i < N; ++i) {
		inp[i] = temp[i];
	}
    std::vector<std::string > waveletNames;
    waveletNames.resize(15);
    for (unsigned int j = 0; j < waveletNames.size(); j++)
    {
        waveletNames[j] = std::string("db") + std::to_string(j+1);
    }
    for (unsigned int direct_fft = 0; direct_fft < 2; direct_fft++)
    {
        for (unsigned int sym_per = 0; sym_per < 2; sym_per++)
        {
            for (unsigned int j = 0; j < waveletNames.size(); j++)
            {
                char * name = new char[waveletNames[j].size() + 1];
                memcpy(name, waveletNames[j].c_str(), waveletNames[j].size() + 1);
                obj = wave_init(name);// Initialize the wavelet
                for (J = 1; J < 4; J++)
                {
                    //J = 3;

                    wt = wt_init(obj, "dwt", N, J);// Initialize the wavelet transform object
                    if (sym_per == 0)
                        setDWTExtension(wt, "sym");// Options are "per" and "sym". Symmetric is the default option
                    else
                        setDWTExtension(wt, "per");
                    if (direct_fft == 0)
                        setWTConv(wt, "direct");
                    else
                        setWTConv(wt, "fft");

                    dwt(wt, inp);// Perform DWT

                    idwt(wt, out);// Perform IDWT (if needed)
                    // Test Reconstruction
                    for (i = 0; i < wt->siglength; ++i) {
                        diff[i] = out[i] - inp[i];
                    }
                    if (direct_fft == 0)
                        BOOST_CHECK_SMALL(absmax(diff, wt->siglength), 1e-12); // If Reconstruction succeeded then the output should be a small value.
                    else
                        BOOST_CHECK_SMALL(absmax(diff, wt->siglength), 1e-8);

                    wt_free(wt);
                }
                wave_free(obj);
            }
        }
    }

	free(out);
	free(diff);
    free(inp);
}

BOOST_AUTO_TEST_CASE(DBCoefTests)
{
    wave_object obj;
    double epsilon = 1e-15;
    std::vector<std::string > waveletNames;
    waveletNames.resize(38);
    for (unsigned int i = 0; i < waveletNames.size();i++)
    {
        waveletNames[i] = std::string("db") + std::to_string(i+1);
    }

    for (unsigned int j = 0; j < waveletNames.size(); j++)
    {
        char * name = new char[waveletNames[j].size() + 1];
        memcpy(name, waveletNames[j].c_str(), waveletNames[j].size() + 1);
        obj = wave_init(name);// Initialize the wavelet
        BOOST_CHECK_SMALL(sum1(obj->lpr, obj->lpr_len) - std::sqrt(2.0), epsilon);
        BOOST_CHECK_SMALL(sum2(obj->lpr, obj->lpr_len) - 1. / std::sqrt(2.0), epsilon);
        BOOST_CHECK_SMALL(sum3(obj->lpr, obj->lpr_len) - 1. / std::sqrt(2.0), epsilon);
        BOOST_CHECK_SMALL(sum4(obj->lpr, obj->lpr_len) - 1., epsilon);
        for (int m = 1; m < (obj->lpr_len / 2) - 1;m++)
            BOOST_CHECK_SMALL(sum5(obj->lpr, obj->lpr_len, m), epsilon);
        wave_free(obj);
    }
}

BOOST_AUTO_TEST_SUITE_END()
