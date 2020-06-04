#include <math.h>
#ifdef _SIMD
#pragma omp declare simd
#endif
float myfun(float x) {
  float twopi=2.f*acosf(-1.f);
  float y = sinf(x*twopi);
  return y*y*y;
}
