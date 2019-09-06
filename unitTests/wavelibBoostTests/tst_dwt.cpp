/*
 * Copyright (c) 2016 Holger Nahrstaedt (TU Berlin)
 */

#include <sstream>
#include <iostream>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "../../header/wavelib.h"

#include<vector>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

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

double RMS_Error(double *data, double *rec, int N) {
    int i;
    double sum = 0;
    for (i = 0; i < N; ++i) {
        sum += (data[i] - rec[i])*(data[i] - rec[i]);
    }
    return sqrt(sum/((double)N-1));
}

double REL_Error(double *data, double *rec, int N) {
    int i;
    double sum1 = 0;
    double sum2 = 0;
    for (i = 0; i < N; ++i) {
        sum1 += (data[i] - rec[i])*(data[i] - rec[i]);
        sum2 += data[i] * data[i];
    }
    return sqrt(sum1)/sqrt(sum2);
}

double generate_rnd() {
	double rnd;

	rnd = (double) (rand() % 100 + 1);

	return rnd;
}

void DWTReconstructionTest()
{

	wave_object obj;
	wt_object wt;
	double *inp,*out;
	int N, i,J;
    double epsilon = 1e-15;

    N = 79926;
    
    //N = 256;

	inp = (double*)malloc(sizeof(double)* N);
	out = (double*)malloc(sizeof(double)* N);
	//wmean = mean(temp, N);

	for (i = 0; i < N; ++i) {
        inp[i] = (rand() / (double)(RAND_MAX));
	}
    std::vector<std::string > waveletNames;

    for (unsigned int j = 0; j < 36; j++)
    {
        waveletNames.push_back(std::string("db") + patch::to_string(j + 1));
    }
    for (unsigned int j = 0; j < 17; j++)
    {
        waveletNames.push_back(std::string("coif") + patch::to_string(j + 1));
    }
    for (unsigned int j = 1; j < 20; j++)
    {
        waveletNames.push_back(std::string("sym") + patch::to_string(j + 1));
    }
    
    waveletNames.push_back("bior1.1");
    waveletNames.push_back("bior1.3");
    waveletNames.push_back("bior1.5");
    waveletNames.push_back("bior2.2");
    waveletNames.push_back("bior2.4");
    waveletNames.push_back("bior2.6");
    waveletNames.push_back("bior2.8");
    waveletNames.push_back("bior3.1");
    waveletNames.push_back("bior3.3");
    waveletNames.push_back("bior3.5");
    waveletNames.push_back("bior3.7");
    waveletNames.push_back("bior3.9");
    waveletNames.push_back("bior4.4");
    waveletNames.push_back("bior5.5");
    waveletNames.push_back("bior6.8");
    
    waveletNames.push_back("rbior1.1");
    waveletNames.push_back("rbior1.3");
    waveletNames.push_back("rbior1.5");
    waveletNames.push_back("rbior2.2");
    waveletNames.push_back("rbior2.4");
    waveletNames.push_back("rbior2.6");
    waveletNames.push_back("rbior2.8");
    waveletNames.push_back("rbior3.1");
    waveletNames.push_back("rbior3.3");
    waveletNames.push_back("rbior3.5");
    waveletNames.push_back("rbior3.7");
    waveletNames.push_back("rbior3.9");
    waveletNames.push_back("rbior4.4");
    waveletNames.push_back("rbior5.5");
    waveletNames.push_back("rbior6.8");

    for (unsigned int direct_fft = 0; direct_fft < 2; direct_fft++)
    {
        for (unsigned int sym_per = 0; sym_per < 2; sym_per++)
        {
            for (unsigned int j = 0; j < waveletNames.size(); j++)
            {
                char * name = new char[waveletNames[j].size() + 1];
                memcpy(name, waveletNames[j].c_str(), waveletNames[j].size() + 1);
                obj = wave_init(name);// Initialize the wavelet
                for (J = 1; J < 3; J++)
                {
                    //J = 3;

                    wt = wt_init(obj,(char*) "dwt", N, J);// Initialize the wavelet transform object
                    if (sym_per == 0)
                        setDWTExtension(wt, (char*) "sym");// Options are "per" and "sym". Symmetric is the default option
                    else
                        setDWTExtension(wt, (char*) "per");
                    if (direct_fft == 0)
                        setWTConv(wt, (char*) "direct");
                    else
                        setWTConv(wt, (char*) "fft");

                    dwt(wt, inp);// Perform DWT

                    idwt(wt, out);// Perform IDWT (if needed)
                    // Test Reconstruction

                    if (direct_fft == 0)
                        epsilon = 1e-8;
                    else
                        epsilon = 1e-10;
                    //BOOST_CHECK_SMALL(RMS_Error(out, inp, wt->siglength), epsilon); // If Reconstruction succeeded then the output should be a small value.
                    
					//printf("%g ",RMS_Error(out, inp, wt->siglength));
					if (RMS_Error(out, inp, wt->siglength) > epsilon) {
						printf("\n ERROR : DWT Reconstruction Unit Test Failed. Exiting. \n");
						exit(-1);
					}
                    wt_free(wt);
                }
                wave_free(obj);
                delete[] name;
            }
        }
    }
    
	free(out);
    free(inp);
}

void DWT2ReconstructionTest()
{
    wave_object obj;
	wt2_object wt;
	int i, k, J, N, rows, cols;
	double *inp, *wavecoeffs,*out;
    double epsilon;

    rows = 1024;
    cols = 1000;

    N = rows*cols;

    inp = (double*)malloc(sizeof(double)* N);
	out = (double*)malloc(sizeof(double)* N);

    std::vector<std::string > waveletNames;

    for (unsigned int j = 0; j < 15; j++)
    {
        waveletNames.push_back(std::string("db") + patch::to_string(j + 1));
    }
    for (unsigned int j = 0; j < 5; j++)
    {
        waveletNames.push_back(std::string("coif") + patch::to_string(j + 1));
    }
    for (unsigned int j = 1; j < 10; j++)
    {
        waveletNames.push_back(std::string("sym") + patch::to_string(j + 1));
    }
    
    waveletNames.push_back("bior1.1");
    waveletNames.push_back("bior1.3");
    waveletNames.push_back("bior1.5");
    waveletNames.push_back("bior2.2");
    waveletNames.push_back("bior2.4");
    waveletNames.push_back("bior2.6");
    waveletNames.push_back("bior2.8");
    waveletNames.push_back("bior3.1");
    waveletNames.push_back("bior3.3");
    waveletNames.push_back("bior3.5");
    waveletNames.push_back("bior3.7");
    waveletNames.push_back("bior3.9");
    waveletNames.push_back("bior4.4");
    waveletNames.push_back("bior5.5");
    waveletNames.push_back("bior6.8");
    
    waveletNames.push_back("rbior1.1");
    waveletNames.push_back("rbior1.3");
    waveletNames.push_back("rbior1.5");
    waveletNames.push_back("rbior2.2");
    waveletNames.push_back("rbior2.4");
    waveletNames.push_back("rbior2.6");
    waveletNames.push_back("rbior2.8");
    waveletNames.push_back("rbior3.1");
    waveletNames.push_back("rbior3.3");
    waveletNames.push_back("rbior3.5");
    waveletNames.push_back("rbior3.7");
    waveletNames.push_back("rbior3.9");
    waveletNames.push_back("rbior4.4");
    waveletNames.push_back("rbior5.5");
    waveletNames.push_back("rbior6.8");

    for (i = 0; i < rows; ++i) {
		for (k = 0; k < cols; ++k) {
			//inp[i*cols + k] = i*cols + k;
			inp[i*cols + k] = generate_rnd();
			out[i*cols + k] = 0.0;
		}
	}

    for (unsigned int direct_fft = 0; direct_fft < 1; direct_fft++)
    {
        for (unsigned int sym_per = 0; sym_per < 2; sym_per++)
        {
            for (unsigned int j = 0; j < waveletNames.size(); j++)
            {
                char * name = new char[waveletNames[j].size() + 1];
                memcpy(name, waveletNames[j].c_str(), waveletNames[j].size() + 1);
                obj = wave_init(name);// Initialize the wavelet
                for (J = 1; J < 3; J++)
                {
                    //J = 3;

                    wt = wt2_init(obj,(char*) "dwt", rows,cols, J);// Initialize the wavelet transform object
                    if (sym_per == 0)
                        setDWT2Extension(wt, (char*) "sym");// Options are "per" and "sym". Symmetric is the default option
                    else
                        setDWT2Extension(wt, (char*) "per");

                    wavecoeffs = dwt2(wt, inp);// Perform DWT

                    idwt2(wt, wavecoeffs, out);// Perform IDWT (if needed)
                    // Test Reconstruction

                    if (direct_fft == 0)
                        epsilon = 1e-8;
                    else
                        epsilon = 1e-10;
                    //BOOST_CHECK_SMALL(RMS_Error(out, inp, wt->siglength), epsilon); // If Reconstruction succeeded then the output should be a small value.
                    
					//printf("%g ",RMS_Error(out, inp, wt->siglength));
					if (RMS_Error(out, inp, N) > epsilon) {
						printf("\n ERROR : DWT2 Reconstruction Unit Test Failed. Exiting. \n");
						exit(-1);
					}
                    wt2_free(wt);
                    free(wavecoeffs);
                }
                wave_free(obj);
                delete[] name;
            }
        }
    }

    free(inp);
    free(out);
}

void MODWTReconstructionTest()
{

    wave_object obj;
    wt_object wt;
    double *inp,*out;
    int N, i,J;
    double epsilon = 1e-15;
    double err;

    N = 79926;
    
    //N = 256;

    inp = (double*)malloc(sizeof(double)* N);
    out = (double*)malloc(sizeof(double)* N);
    //wmean = mean(temp, N);

    for (i = 0; i < N; ++i) {
        inp[i] = (rand() / (double)(RAND_MAX));
    }
    std::vector<std::string > waveletNames;

    for (unsigned int j = 0; j < 15; j++)
    {
        waveletNames.push_back(std::string("db") + patch::to_string(j + 1));
    }
    for (unsigned int j = 0; j < 5; j++)
    {
        waveletNames.push_back(std::string("coif") + patch::to_string(j + 1));
    }
    for (unsigned int j = 1; j < 10; j++)
    {
        waveletNames.push_back(std::string("sym") + patch::to_string(j + 1));
    }
    

    for (unsigned int direct_fft = 0; direct_fft < 1; direct_fft++)
    {
        for (unsigned int sym_per = 0; sym_per < 1; sym_per++)
        {
            for (unsigned int j = 0; j < waveletNames.size(); j++)
            {
                char * name = new char[waveletNames[j].size() + 1];
                memcpy(name, waveletNames[j].c_str(), waveletNames[j].size() + 1);
                obj = wave_init(name);// Initialize the wavelet
                for (J = 1; J < 3; J++)
                {
                    //J = 3;

                    wt = wt_init(obj,(char*) "modwt", N, J);// Initialize the wavelet transform object
                    
                    if (direct_fft == 0)
                        setWTConv(wt, (char*) "direct");
                    else
                        setWTConv(wt, (char*) "fft");

                    if (sym_per == 0)
                        setDWTExtension(wt, (char*) "per");// Options are "per" and "sym". Symmetric is the default option
                    else if (sym_per == 1 && direct_fft == 1)
                        setDWTExtension(wt, (char*) "sym");
                    else break;

                    modwt(wt, inp);// Perform DWT

                    imodwt(wt, out);// Perform IDWT (if needed)
                    // Test Reconstruction

                    if (direct_fft == 0)
                        epsilon = 1e-8;
                    else
                        epsilon = 1e-10;
                    //BOOST_CHECK_SMALL(RMS_Error(out, inp, wt->siglength), epsilon); // If Reconstruction succeeded then the output should be a small value.
                    
                    //printf("%g ",RMS_Error(out, inp, wt->siglength));
                    err = RMS_Error(out, inp, wt->siglength);
                    //printf("%d %d %g \n",direct_fft,sym_per,err);
                    if (err > epsilon) {
                        printf("\n ERROR : DWT Reconstruction Unit Test Failed. Exiting. \n");
                        exit(-1);
                    }
                    wt_free(wt);
                }
                wave_free(obj);
                delete[] name;
            }
        }
    }
    
    free(out);
    free(inp);
}

void MODWT2ReconstructionTest()
{
    wave_object obj;
	wt2_object wt;
	int i, k, J, N, rows, cols;
	double *inp, *wavecoeffs,*out;
    double epsilon;

    rows = 1024;
    cols = 1000;

    N = rows*cols;

    inp = (double*)malloc(sizeof(double)* N);
	out = (double*)malloc(sizeof(double)* N);

    std::vector<std::string > waveletNames;

    for (unsigned int j = 0; j < 15; j++)
    {
        waveletNames.push_back(std::string("db") + patch::to_string(j + 1));
    }
    for (unsigned int j = 0; j < 5; j++)
    {
        waveletNames.push_back(std::string("coif") + patch::to_string(j + 1));
    }
    for (unsigned int j = 1; j < 10; j++)
    {
        waveletNames.push_back(std::string("sym") + patch::to_string(j + 1));
    }
    

    for (i = 0; i < rows; ++i) {
		for (k = 0; k < cols; ++k) {
			//inp[i*cols + k] = i*cols + k;
			inp[i*cols + k] = generate_rnd();
			out[i*cols + k] = 0.0;
		}
	}

    for (unsigned int direct_fft = 0; direct_fft < 1; direct_fft++)
    {
        for (unsigned int sym_per = 0; sym_per < 1; sym_per++)
        {
            for (unsigned int j = 0; j < waveletNames.size(); j++)
            {
                char * name = new char[waveletNames[j].size() + 1];
                memcpy(name, waveletNames[j].c_str(), waveletNames[j].size() + 1);
                obj = wave_init(name);// Initialize the wavelet
                for (J = 1; J < 3; J++)
                {
                    //J = 3;

                    wt = wt2_init(obj,(char*) "modwt", rows,cols, J);// Initialize the wavelet transform object
                    if (sym_per == 0)
                        setDWT2Extension(wt, (char*) "per");// Options are "per"

                    wavecoeffs = modwt2(wt, inp);// Perform DWT

                    imodwt2(wt, wavecoeffs, out);// Perform IDWT (if needed)
                    // Test Reconstruction

                    if (direct_fft == 0)
                        epsilon = 1e-8;
                    else
                        epsilon = 1e-10;
                    //BOOST_CHECK_SMALL(RMS_Error(out, inp, wt->siglength), epsilon); // If Reconstruction succeeded then the output should be a small value.
                    
					//printf("%g ",RMS_Error(out, inp, wt->siglength));
					if (RMS_Error(out, inp, N) > epsilon) {
						printf("\n ERROR : MODWT2 Reconstruction Unit Test Failed. Exiting. \n");
						exit(-1);
					}
                    wt2_free(wt);
                    free(wavecoeffs);
                }
                wave_free(obj);
                delete[] name;
            }
        }
    }

    free(inp);
    free(out);
}

void SWTReconstructionTest()
{

    wave_object obj;
    wt_object wt;
    double *inp,*out;
    int N, i,J;
    double epsilon = 1e-15;
    double err;

    N = 4000;
    
    //N = 256;

    inp = (double*)malloc(sizeof(double)* N);
    out = (double*)malloc(sizeof(double)* N);
    //wmean = mean(temp, N);

    for (i = 0; i < N; ++i) {
        inp[i] = (rand() / (double)(RAND_MAX));
    }
    std::vector<std::string > waveletNames;

    for (unsigned int j = 0; j < 15; j++)
    {
        waveletNames.push_back(std::string("db") + patch::to_string(j + 1));
    }
    for (unsigned int j = 0; j < 5; j++)
    {
        waveletNames.push_back(std::string("coif") + patch::to_string(j + 1));
    }
    for (unsigned int j = 1; j < 10; j++)
    {
        waveletNames.push_back(std::string("sym") + patch::to_string(j + 1));
    }
    
    waveletNames.push_back("bior1.1");
    waveletNames.push_back("bior1.3");
    waveletNames.push_back("bior1.5");
    waveletNames.push_back("bior2.2");
    waveletNames.push_back("bior2.4");
    waveletNames.push_back("bior2.6");
    waveletNames.push_back("bior2.8");
    waveletNames.push_back("bior3.1");
    waveletNames.push_back("bior3.3");
    waveletNames.push_back("bior3.5");
    waveletNames.push_back("bior3.7");
    waveletNames.push_back("bior3.9");
    waveletNames.push_back("bior4.4");
    waveletNames.push_back("bior5.5");
    waveletNames.push_back("bior6.8");
    
    waveletNames.push_back("rbior1.1");
    waveletNames.push_back("rbior1.3");
    waveletNames.push_back("rbior1.5");
    waveletNames.push_back("rbior2.2");
    waveletNames.push_back("rbior2.4");
    waveletNames.push_back("rbior2.6");
    waveletNames.push_back("rbior2.8");
    waveletNames.push_back("rbior3.1");
    waveletNames.push_back("rbior3.3");
    waveletNames.push_back("rbior3.5");
    waveletNames.push_back("rbior3.7");
    waveletNames.push_back("rbior3.9");
    waveletNames.push_back("rbior4.4");
    waveletNames.push_back("rbior5.5");
    waveletNames.push_back("rbior6.8");

    for (unsigned int direct_fft = 0; direct_fft < 2; direct_fft++)
    {
        for (unsigned int sym_per = 0; sym_per < 1; sym_per++)
        {
            for (unsigned int j = 0; j < waveletNames.size(); j++)
            {
                char * name = new char[waveletNames[j].size() + 1];
                memcpy(name, waveletNames[j].c_str(), waveletNames[j].size() + 1);
                obj = wave_init(name);// Initialize the wavelet
                for (J = 1; J < 3; J++)
                {
                    //J = 3;

                    wt = wt_init(obj,(char*) "swt", N, J);// Initialize the wavelet transform object
                    
                    if (direct_fft == 0)
                        setWTConv(wt, (char*) "direct");
                    else
                        setWTConv(wt, (char*) "fft");

                    if (sym_per == 0)
                        setDWTExtension(wt, (char*) "per");// Options are "per" and "sym". Symmetric is the default option
                    else if (sym_per == 1 && direct_fft == 1)
                        setDWTExtension(wt, (char*) "sym");
                    else break;

                    swt(wt, inp);// Perform DWT

                    iswt(wt, out);// Perform IDWT (if needed)
                    // Test Reconstruction

                    if (direct_fft == 0)
                        epsilon = 1e-8;
                    else
                        epsilon = 1e-10;
                    //BOOST_CHECK_SMALL(RMS_Error(out, inp, wt->siglength), epsilon); // If Reconstruction succeeded then the output should be a small value.
                    
                    //printf("%g ",RMS_Error(out, inp, wt->siglength));
                    err = RMS_Error(out, inp, wt->siglength);
                    //printf("%d %d %g \n",direct_fft,sym_per,err);
                    if (err > epsilon) {
                        printf("\n ERROR : SWT Reconstruction Unit Test Failed. Exiting. \n");
                        exit(-1);
                    }
                    wt_free(wt);
                }
                wave_free(obj);
                delete[] name;
            }
        }
    }
    
    free(out);
    free(inp);
}

void SWT2ReconstructionTest()
{
    wave_object obj;
	wt2_object wt;
	int i, k, J, N, rows, cols;
	double *inp, *wavecoeffs,*out;
    double epsilon;

    rows = 1024;
    cols = 1000;

    N = rows*cols;

    inp = (double*)malloc(sizeof(double)* N);
	out = (double*)malloc(sizeof(double)* N);

    std::vector<std::string > waveletNames;

    for (unsigned int j = 0; j < 15; j++)
    {
        waveletNames.push_back(std::string("db") + patch::to_string(j + 1));
    }
    for (unsigned int j = 0; j < 5; j++)
    {
        waveletNames.push_back(std::string("coif") + patch::to_string(j + 1));
    }
    for (unsigned int j = 1; j < 10; j++)
    {
        waveletNames.push_back(std::string("sym") + patch::to_string(j + 1));
    }
    
    waveletNames.push_back("bior1.1");
    waveletNames.push_back("bior1.3");
    waveletNames.push_back("bior1.5");
    waveletNames.push_back("bior2.2");
    waveletNames.push_back("bior2.4");
    waveletNames.push_back("bior2.6");
    waveletNames.push_back("bior2.8");
    waveletNames.push_back("bior3.1");
    waveletNames.push_back("bior3.3");
    waveletNames.push_back("bior3.5");
    waveletNames.push_back("bior3.7");
    waveletNames.push_back("bior3.9");
    waveletNames.push_back("bior4.4");
    waveletNames.push_back("bior5.5");
    waveletNames.push_back("bior6.8");
    
    waveletNames.push_back("rbior1.1");
    waveletNames.push_back("rbior1.3");
    waveletNames.push_back("rbior1.5");
    waveletNames.push_back("rbior2.2");
    waveletNames.push_back("rbior2.4");
    waveletNames.push_back("rbior2.6");
    waveletNames.push_back("rbior2.8");
    waveletNames.push_back("rbior3.1");
    waveletNames.push_back("rbior3.3");
    waveletNames.push_back("rbior3.5");
    waveletNames.push_back("rbior3.7");
    waveletNames.push_back("rbior3.9");
    waveletNames.push_back("rbior4.4");
    waveletNames.push_back("rbior5.5");
    waveletNames.push_back("rbior6.8");

    for (i = 0; i < rows; ++i) {
		for (k = 0; k < cols; ++k) {
			//inp[i*cols + k] = i*cols + k;
			inp[i*cols + k] = generate_rnd();
			out[i*cols + k] = 0.0;
		}
	}

    for (unsigned int direct_fft = 0; direct_fft < 1; direct_fft++)
    {
        for (unsigned int sym_per = 0; sym_per < 1; sym_per++)
        {
            for (unsigned int j = 0; j < waveletNames.size(); j++)
            {
                char * name = new char[waveletNames[j].size() + 1];
                memcpy(name, waveletNames[j].c_str(), waveletNames[j].size() + 1);
                obj = wave_init(name);// Initialize the wavelet
                for (J = 1; J < 3; J++)
                {
                    //J = 3;

                    wt = wt2_init(obj,(char*) "swt", rows,cols, J);// Initialize the wavelet transform object
                    if (sym_per == 0)
                        setDWT2Extension(wt, (char*) "per");// Options are "per"

                    wavecoeffs = swt2(wt, inp);// Perform DWT

                    iswt2(wt, wavecoeffs, out);// Perform IDWT (if needed)
                    // Test Reconstruction

                    if (direct_fft == 0)
                        epsilon = 1e-8;
                    else
                        epsilon = 1e-10;
                    //BOOST_CHECK_SMALL(RMS_Error(out, inp, wt->siglength), epsilon); // If Reconstruction succeeded then the output should be a small value.
                    
					//printf("%g ",RMS_Error(out, inp, wt->siglength));
					if (RMS_Error(out, inp, N) > epsilon) {
						printf("\n ERROR : SWT2 Reconstruction Unit Test Failed. Exiting. \n");
						exit(-1);
					}
                    wt2_free(wt);
                    free(wavecoeffs);
                }
                wave_free(obj);
                delete[] name;
            }
        }
    }

    free(inp);
    free(out);
}

void DWPTReconstructionTest()
{

	wave_object obj;
	wpt_object wt;
	double *inp,*out;
	int N, i,J;
    double epsilon = 1e-8;

    N = 79926;
    
    //N = 256;

	inp = (double*)malloc(sizeof(double)* N);
	out = (double*)malloc(sizeof(double)* N);
	//wmean = mean(temp, N);

	for (i = 0; i < N; ++i) {
        inp[i] = (rand() / (double)(RAND_MAX));
	}
    std::vector<std::string > waveletNames;

    for (unsigned int j = 0; j < 36; j++)
    {
        waveletNames.push_back(std::string("db") + patch::to_string(j + 1));
    }
    for (unsigned int j = 0; j < 17; j++)
    {
        waveletNames.push_back(std::string("coif") + patch::to_string(j + 1));
    }
    for (unsigned int j = 1; j < 20; j++)
    {
        waveletNames.push_back(std::string("sym") + patch::to_string(j + 1));
    }
    
    waveletNames.push_back("bior1.1");
    waveletNames.push_back("bior1.3");
    waveletNames.push_back("bior1.5");
    waveletNames.push_back("bior2.2");
    waveletNames.push_back("bior2.4");
    waveletNames.push_back("bior2.6");
    waveletNames.push_back("bior2.8");
    waveletNames.push_back("bior3.1");
    waveletNames.push_back("bior3.3");
    waveletNames.push_back("bior3.5");
    waveletNames.push_back("bior3.7");
    waveletNames.push_back("bior3.9");
    waveletNames.push_back("bior4.4");
    waveletNames.push_back("bior5.5");
    waveletNames.push_back("bior6.8");
    
    waveletNames.push_back("rbior1.1");
    waveletNames.push_back("rbior1.3");
    waveletNames.push_back("rbior1.5");
    waveletNames.push_back("rbior2.2");
    waveletNames.push_back("rbior2.4");
    waveletNames.push_back("rbior2.6");
    waveletNames.push_back("rbior2.8");
    waveletNames.push_back("rbior3.1");
    waveletNames.push_back("rbior3.3");
    waveletNames.push_back("rbior3.5");
    waveletNames.push_back("rbior3.7");
    waveletNames.push_back("rbior3.9");
    waveletNames.push_back("rbior4.4");
    waveletNames.push_back("rbior5.5");
    waveletNames.push_back("rbior6.8");

    for (unsigned int ent = 0; ent < 2; ent++)
    {
        for (unsigned int sym_per = 0; sym_per < 2; sym_per++)
        {
            for (unsigned int j = 0; j < waveletNames.size(); j++)
            {
                char * name = new char[waveletNames[j].size() + 1];
                memcpy(name, waveletNames[j].c_str(), waveletNames[j].size() + 1);
                obj = wave_init(name);// Initialize the wavelet
                for (J = 1; J < 3; J++)
                {
                    //J = 3;

                    wt = wpt_init(obj, N, J);// Initialize the wavelet transform object
                    if (sym_per == 0)
                        setDWPTExtension(wt, (char*) "sym");// Options are "per" and "sym". Symmetric is the default option
                    else
                        setDWPTExtension(wt, (char*) "per");
                        
                    if (ent == 0)
                        setDWPTEntropy(wt, (char*) "shannon",0);
                    else
                        setDWPTEntropy(wt, (char*) "logenergy",0);

                    dwpt(wt, inp);// Perform DWT

                    idwpt(wt, out);// Perform IDWT (if needed)
                    // Test Reconstruction

                    
                    //BOOST_CHECK_SMALL(RMS_Error(out, inp, wt->siglength), epsilon); // If Reconstruction succeeded then the output should be a small value.
                    
					//printf("%s %g \n",name,RMS_Error(out, inp, wt->siglength));
					
					if (RMS_Error(out, inp, wt->siglength) > epsilon) {
						printf("\n ERROR : DWPT Reconstruction Unit Test Failed. Exiting. \n");
						exit(-1);
					}
                    wpt_free(wt);
                }
                wave_free(obj);
                delete[] name;
            }
        }
    }
    
	free(out);
    free(inp);
}

void CWTReconstructionTest() {
	int i, N, J,subscale,a0;
	double *inp,*oup;
	double dt, dj,s0, pi,t;
	double epsilon;
	int it1,it2;
	cwt_object wt;
	

	char *wave[3];
	wave[0] = (char*) "morl";
	wave[1] =(char*) "paul";
	wave[2] = (char*) "dog";
	double param[30] = {4.5,5,5.5,6,6.5,8,10,13,17,20,
		4,5,7,8,10,12,13,14,17,20,2,4,6,8,10,12,14,16,18,20};
	char *type = (char*) "pow";
	
	epsilon = 0.01;
	N = 2048;
	dt = 0.000125;
	subscale = 20;
	dj = 1.0 / (double) subscale;
	s0 = dt/32;	
	J = 32 * subscale;
	a0 = 2;//power
	

	inp = (double*)malloc(sizeof(double)* N);
	oup = (double*)malloc(sizeof(double)* N);
	
	pi = 4.0 * atan(1.0);


	for (i = 0; i < N; ++i) {
		t = dt * i;
		inp[i] = sin(2 * pi * 500 * t) + sin(2 * pi * 1000 * t) + 0.1 * sin(2 * pi * 8 * t);
		if (i == 1200 || i ==1232) {
			inp[i] += 5.0;
		}
	}
	
	for(it1 = 0; it1 < 3;++it1) {
		for(it2 = 0; it2 < 10;++it2) {
	
			wt = cwt_init(wave[it1], param[it1*10+it2], N,dt, J);

			setCWTScales(wt, s0, dj, type, a0);

			cwt(wt, inp);


			icwt(wt, oup);


			//printf("\nWavelet : %s Parameter %g Error %g \n", wave[it1],param[it1*10+it2],REL_Error(inp,oup, wt->siglength));
			if (REL_Error(inp,oup, wt->siglength) > epsilon) {
				printf("\n ERROR : DWPT Reconstruction Unit Test Failed. Exiting. \n");
				exit(-1);
			}
	
			cwt_free(wt);
		}
	}
	


	free(inp);
	free(oup);
	
}


void DBCoefTests()
{
    wave_object obj;
    double epsilon = 1e-15;
    double t1,t2,t3,t4,t5;
    std::vector<std::string > waveletNames;
    waveletNames.resize(38);
    for (unsigned int i = 0; i < waveletNames.size();i++)
    {
        waveletNames[i] = std::string("db") + patch::to_string(i+1);
    }

    for (unsigned int j = 0; j < waveletNames.size(); j++)
    {
        char * name = new char[waveletNames[j].size() + 1];
        memcpy(name, waveletNames[j].c_str(), waveletNames[j].size() + 1);
        obj = wave_init(name);// Initialize the wavelet
        t1 = sum1(obj->lpr, obj->lpr_len) - sqrt(2.0);
        t2 = sum2(obj->lpr, obj->lpr_len) - 1. / sqrt(2.0);
        t3 = sum3(obj->lpr, obj->lpr_len) - 1. / sqrt(2.0);
        t4 = sum4(obj->lpr, obj->lpr_len) - 1.;
        
        if (fabs(t1) > epsilon || fabs(t2) > epsilon || fabs(t3) > epsilon || fabs(t4) > epsilon) {
			printf("\n ERROR : DB Coefficients Unit Test Failed. Exiting. \n");
			exit(-1);
		}
        
        for (int m = 1; m < (obj->lpr_len / 2) - 1;m++) {
			t5 = sum5(obj->lpr, obj->lpr_len, m);
            if (fabs(t5) > epsilon) {
				printf("\n ERROR : DB Coefficients Unit Test Failed. Exiting. \n");
				exit(-1);
			}
		}
        wave_free(obj);
        delete[] name;
    }
}


void CoifCoefTests()
{
    wave_object obj;
    double epsilon = 1e-15;
    double t1,t2,t3,t4,t5;
    std::vector<std::string > waveletNames;
    waveletNames.resize(17);
    for (unsigned int i = 0; i < waveletNames.size(); i++)
    {
        waveletNames[i] = std::string("coif") + patch::to_string(i + 1);
    }

    for (unsigned int j = 0; j < waveletNames.size(); j++)
    {
        char * name = new char[waveletNames[j].size() + 1];
        memcpy(name, waveletNames[j].c_str(), waveletNames[j].size() + 1);
        obj = wave_init(name);// Initialize the wavelet
        t1 = sum1(obj->lpr, obj->lpr_len) - sqrt(2.0);
        t2 = sum2(obj->lpr, obj->lpr_len) - 1. / sqrt(2.0);
        t3 = sum3(obj->lpr, obj->lpr_len) - 1. / sqrt(2.0);
        t4 = sum4(obj->lpr, obj->lpr_len) - 1.;
        
        if (fabs(t1) > epsilon || fabs(t2) > epsilon || fabs(t3) > epsilon || fabs(t4) > epsilon) {
			printf("\n ERROR : Coif Coefficients Unit Test Failed. Exiting. \n");
			exit(-1);
		}
        
        for (int m = 1; m < (obj->lpr_len / 2) - 1;m++) {
			t5 = sum5(obj->lpr, obj->lpr_len, m);
            if (fabs(t5) > epsilon) {
				printf("\n ERROR : Coif Coefficients Unit Test Failed. Exiting. \n");
				exit(-1);
			}
		}
        wave_free(obj);
        delete[] name;
    }
}

void SymCoefTests()
{
    wave_object obj;
    double epsilon = 1e-10;
    double t1,t2,t3,t4,t5;
    std::vector<std::string > waveletNames;
    for (unsigned int i = 1; i < 20; i++)
    {
        waveletNames.push_back(std::string("sym") + patch::to_string(i + 1));
    }

    for (unsigned int j = 0; j < waveletNames.size(); j++)
    {
        char * name = new char[waveletNames[j].size() + 1];
        memcpy(name, waveletNames[j].c_str(), waveletNames[j].size() + 1);
        obj = wave_init(name);// Initialize the wavelet
        t1 = sum1(obj->lpr, obj->lpr_len) - sqrt(2.0);
        t2 = sum2(obj->lpr, obj->lpr_len) - 1. / sqrt(2.0);
        t3 = sum3(obj->lpr, obj->lpr_len) - 1. / sqrt(2.0);
        t4 = sum4(obj->lpr, obj->lpr_len) - 1.;
        
        if (fabs(t1) > epsilon || fabs(t2) > epsilon || fabs(t3) > epsilon || fabs(t4) > epsilon) {
			printf("\n ERROR : Sym Coefficients Unit Test Failed. Exiting. \n");
			exit(-1);
		}
        
        for (int m = 1; m < (obj->lpr_len / 2) - 1;m++) {
			t5 = sum5(obj->lpr, obj->lpr_len, m);
            if (fabs(t5) > epsilon) {
				printf("\n ERROR : Sym Coefficients Unit Test Failed. Exiting. \n");
				exit(-1);
			}
		}
        wave_free(obj);
        delete[] name;
    }
}

void BiorCoefTests()
{
    wave_object obj;
    double epsilon = 1e-10;
    double t1,t2,t3,t4,t5,t6;
    std::vector<std::string > waveletNames;
    waveletNames.push_back("bior1.1");
    waveletNames.push_back("bior1.3");
    waveletNames.push_back("bior1.5");
    waveletNames.push_back("bior2.2");
    waveletNames.push_back("bior2.4");
    waveletNames.push_back("bior2.6");
    waveletNames.push_back("bior2.8");
    waveletNames.push_back("bior3.1");
    waveletNames.push_back("bior3.3");
    waveletNames.push_back("bior3.5");
    waveletNames.push_back("bior3.7");
    waveletNames.push_back("bior3.9");
    waveletNames.push_back("bior4.4");
    waveletNames.push_back("bior5.5");
    waveletNames.push_back("bior6.8");

    for (unsigned int j = 0; j < waveletNames.size(); j++)
    {
        char * name = new char[waveletNames[j].size() + 1];
        memcpy(name, waveletNames[j].c_str(), waveletNames[j].size() + 1);
        obj = wave_init(name);// Initialize the wavelet
        
        t1 = sum1(obj->lpr, obj->lpr_len) - sqrt(2.0);
        t2 = sum1(obj->lpd, obj->lpd_len) - sqrt(2.0);
        
        t3 = sum2(obj->lpr, obj->lpr_len) - 1. / sqrt(2.0);
        t4 = sum2(obj->lpd, obj->lpd_len) - 1. / sqrt(2.0);
        
        t5 = sum3(obj->lpr, obj->lpr_len) - 1. / sqrt(2.0);
        t6 = sum3(obj->lpd, obj->lpd_len) - 1. / sqrt(2.0);
        
        if (fabs(t1) > epsilon || fabs(t2) > epsilon || fabs(t3) > epsilon || fabs(t4) > epsilon || fabs(t5) > epsilon || fabs(t6) > epsilon ) {
			printf("\n ERROR : Bior Coefficients Unit Test Failed. Exiting. \n");
			exit(-1);
		}
        
        
        wave_free(obj);
        delete[] name;
    }
}

void RBiorCoefTests()
{
    wave_object obj;
    double epsilon = 1e-10;
    double t1,t2,t3,t4,t5,t6;
    std::vector<std::string > waveletNames;
    waveletNames.push_back("rbior1.1");
    waveletNames.push_back("rbior1.3");
    waveletNames.push_back("rbior1.5");
    waveletNames.push_back("rbior2.2");
    waveletNames.push_back("rbior2.4");
    waveletNames.push_back("rbior2.6");
    waveletNames.push_back("rbior2.8");
    waveletNames.push_back("rbior3.1");
    waveletNames.push_back("rbior3.3");
    waveletNames.push_back("rbior3.5");
    waveletNames.push_back("rbior3.7");
    waveletNames.push_back("rbior3.9");
    waveletNames.push_back("rbior4.4");
    waveletNames.push_back("rbior5.5");
    waveletNames.push_back("rbior6.8");

    for (unsigned int j = 0; j < waveletNames.size(); j++)
    {
        char * name = new char[waveletNames[j].size() + 1];
        memcpy(name, waveletNames[j].c_str(), waveletNames[j].size() + 1);
        obj = wave_init(name);// Initialize the wavelet
        
        t1 = sum1(obj->lpr, obj->lpr_len) - sqrt(2.0);
        t2 = sum1(obj->lpd, obj->lpd_len) - sqrt(2.0);
        
        t3 = sum2(obj->lpr, obj->lpr_len) - 1. / sqrt(2.0);
        t4 = sum2(obj->lpd, obj->lpd_len) - 1. / sqrt(2.0);
        
        t5 = sum3(obj->lpr, obj->lpr_len) - 1. / sqrt(2.0);
        t6 = sum3(obj->lpd, obj->lpd_len) - 1. / sqrt(2.0);
        
        if (fabs(t1) > epsilon || fabs(t2) > epsilon || fabs(t3) > epsilon || fabs(t4) > epsilon || fabs(t5) > epsilon || fabs(t6) > epsilon ) {
			printf("\n ERROR : RBior Coefficients Unit Test Failed. Exiting. \n");
			exit(-1);
		}
        wave_free(obj);
        delete[] name;
    }
}

int main() {
	printf("Running Unit Tests : \n \n");
	printf("Running DBCoefTests ... ");
	DBCoefTests();
	printf("DONE \n");
	printf("Running CoifCoefTests ... ");
	CoifCoefTests();
	printf("DONE \n");
	printf("Running SymCoefTests ... ");
	SymCoefTests();
	printf("DONE \n");
	printf("Running BiorCoefTests ... ");
	BiorCoefTests();
	printf("DONE \n");
	printf("Running RBiorCoefTests ... ");
	RBiorCoefTests();
	printf("DONE \n");
	printf("Running DWT ReconstructionTests ... ");
	DWTReconstructionTest();
	printf("DONE \n");
    printf("Running MODWT ReconstructionTests ... ");
    MODWTReconstructionTest();
    printf("DONE \n");
    printf("Running SWT ReconstructionTests ... ");
    SWTReconstructionTest();
    printf("DONE \n");
	printf("Running DWPT ReconstructionTests ... ");
	DWPTReconstructionTest();
	printf("DONE \n");
	printf("Running CWT ReconstructionTests ... ");
	CWTReconstructionTest();
	printf("DONE \n");
    printf("Running DWT2 ReconstructionTests ... ");
	DWT2ReconstructionTest();
	printf("DONE \n");
    printf("Running MODWT2 ReconstructionTests ... ");
	MODWT2ReconstructionTest();
	printf("DONE \n");
    printf("Running SWT2 ReconstructionTests ... ");
	SWT2ReconstructionTest();
	printf("DONE \n");
	printf("\n\nUnit Tests Successful\n\n");
	return 0;
	
}

