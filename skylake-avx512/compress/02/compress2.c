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

int compress(int n1, int n2, float a[][n2], float b[restrict]) {

	int nb = 0;
	int i,j;
#pragma omp simd
	for (i=0; i <n1; i++)  {
		float sc = 0.f;
		for (j=0; j<n2; j++) sc += a[i][j];
#pragma omp ordered simd monotonic(nb:1)
    	{ if (sc > 0.f) b[nb++] = sc; }
	}
	return nb;
}
