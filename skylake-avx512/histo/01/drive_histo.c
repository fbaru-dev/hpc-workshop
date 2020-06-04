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
// icc -restrict -xcore-avx2  -qopt-report=4  drive_histo.c histo.c; ./a.out
// icc -restrict -xmic-avx512 -qopt-report=4  drive_histo.c histo.c; ./a.out

#ifndef NBIN
  #define NBIN 2000
#endif

#ifndef NEVENT
  #define NEVENT 10000000
#endif

#ifndef NTIMES
  #define NTIMES 10
#endif

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
// #define __USE_SVID     // drand48()  comes from System 5
extern double drand48 (void) __THROW;

void histo(float *, int *restrict, int, int) ;

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
	int h[NBIN];
	float x[NEVENT];
	float mysum=0.f;
	int i, n;
	double startTime, endTime, execTime = 0.0;

    for (i=0; i<NEVENT; i++) x[i] = drand48();
	for (i=0; i<NBIN;   i++) h[i] = 0;

    startTime = clock_it();

    for (i=0; i<NTIMES; i++) {
       histo(x, h, NEVENT, NBIN);
    }

    endTime = clock_it();
    execTime = endTime - startTime;

	for   (i=0;i<NBIN;i++) mysum+=(float)h[i];
	printf("time taken %f     sum= %f \n", execTime, mysum);
	printf("%d  %d  %d \n", h[0], h[(NBIN/2)-1], h[NBIN-1]);

	return 0;
}
