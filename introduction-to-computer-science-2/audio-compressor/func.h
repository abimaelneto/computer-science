#ifndef _func_
#define _func_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <math.h>

unsigned char* read_wav_data(char* fname);
double complex *DFT(unsigned char *audio, int length);
unsigned char* RFT(double complex *data, int length);

#endif
