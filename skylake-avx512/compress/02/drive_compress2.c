//==============================================================
//
// SAMPLE SOURCE CODE - SUBJECT TO THE TERMS OF SAMPLE CODE LICENSE AGREEMENT,
// http://software.intel.com/en-us/articles/intel-sample-source-code-license-agreement/
//
// Copyright 2016 Intel Corporation
//
// THIS FILE IS PROVIDED "AS IS" WITH NO WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO ANY IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, NON-INFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS.
//
// =============================================================
// icc -restrict -xcore-avx2  -qopt-report=4  drive_compress.c compress.c; ./a.out
// icc -restrict -xmic-avx512 -qopt-report=4  drive_compress.c compress.c; ./a.out

#ifndef SIZE1
  #define SIZE1 100000
  #define SIZE2 5
#endif

#ifndef NTIMES
  #define NTIMES 1000
#endif

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

extern double drand48 (void) __THROW;
int compress(int, int, float [][SIZE2], float [restrict]);

double clock_it(void)
{
	double duration = 0.0;
	struct timeval start;

	gettimeofday(&start, NULL);
	duration = (double)(start.tv_sec + start.tv_usec/1000000.0);
	return duration;
}

int main()
{
	float a[SIZE1][SIZE2], b[SIZE1];
	int nb;
	int i,j;
	double startTime, endTime, execTime = 0.0;

    for (i=0; i<SIZE1; i++) {
		for (j=0; j<SIZE2; j++) {
			a[i][j] = (float) (2. * drand48() - 1.);
		}
	}

    startTime = clock_it();

    for (i=0; i<NTIMES; i++) {
       nb = compress(SIZE1, SIZE2, a, b);
    }

    endTime = clock_it();
    execTime = endTime - startTime;

    float mysum = 0.0f;
    for   (i=0;i<SIZE1;i++) mysum+=b[i];
    printf("sum of %d  out of %d = %f \n", nb, SIZE1, mysum);
    printf("time = %f \n", execTime);
    return 0;
}
