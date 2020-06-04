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
#include <math.h>
void histo(float *x, int *h, int nevent, int nbin ) {
   int i, ih;
   float y, bot=-1.f, top=1.f, invbinw, twopi=2.f*acos(-1.f);

   invbinw = (float)nbin / (top-bot);

   for (i=0; i<nevent; i++)  {
      y     = sinf(x[i]*twopi);
      ih    = floor((y-bot)*invbinw);
      ih    = ih > 0    ? ih : 0;
      ih    = ih < nbin-1 ? ih : nbin-1;
      h[ih] = h[ih] + 1;
   }
 }
