#include <math.h>
#ifndef _SIMD

float myfun(float);

void hist_fill(float *x, int *restrict contents, int n, int nbin) {
   float bot=-1.f, top=1.f, invbinw = (float)nbin / (top-bot);

    for (int i=0; i<n; i++) {
      float y = myfun(x[i]);
      int ih  = floor( (y-bot)*invbinw );
      ih      = ih >= 0      ? ih : 0;
      ih      = ih <= nbin-1 ? ih : nbin-1;
        ++contents[ih];
	}
}

#else

#pragma omp declare simd
float myfun(float);

void hist_fill(float *x, int *restrict contents, int n, int nbin) {
   float bot=-1.f, top=1.f, invbinw = (float)nbin / (top-bot);

#pragma omp simd
    for (int i=0; i<n; i++) {
      float y = myfun(x[i]);
      int ih  = floor( (y-bot)*invbinw );
      ih      = ih >= 0      ? ih : 0;
      ih      = ih <= nbin-1 ? ih : nbin-1;
#pragma omp ordered simd overlap (ih)
        ++contents[ih];
        }
}

#endif
