#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <immintrin.h>
#include "mkl.h"

int mnk=4;

double mytime(){
  timeval v;
  gettimeofday(&v,0);
  return v.tv_sec+v.tv_usec/1000000.0;
}

void matrixmul_mnk(double* c,double* a,double* b){
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
	      mnk, mnk, mnk, 1, a, mnk, b, mnk, 1, c, mnk);
}
// for i c_I,0:3 = c_i,0:3 + sum_k a_i,k b_k,0:3
void matrixmul_mnk_opt1(double* c, double* a, double* b){
int i;
__m512d xa0;
__m512d xa1;
__m512d xa2;
__m512d xa3;
__m512d xb0;
__m512d xb1;
__m512d xb2;
__m512d xb3;
__m512d xc0;
__mmask8 xm = _mm512_int2mask(15);
 xb0 = _mm512_maskz_loadu_pd(xm,&b[0+0]);
 xb1 = _mm512_maskz_loadu_pd(xm,&b[4+0]);
 xb2 = _mm512_maskz_loadu_pd(xm,&b[8+0]);
 xb3 = _mm512_maskz_loadu_pd(xm,&b[12+0]);
for(i=0;i<4;i+=1){
    xc0 = _mm512_maskz_loadu_pd(xm,&c[i*4+0]);
    xa0=_mm512_set1_pd(a[i*4+0]);
    xa1=_mm512_set1_pd(a[i*4+1]);
    xa2=_mm512_set1_pd(a[i*4+2]);
    xa3=_mm512_set1_pd(a[i*4+3]);
    xc0=_mm512_mask3_fmadd_pd(xa0,xb0,xc0,xm);
    xc0=_mm512_mask3_fmadd_pd(xa1,xb1,xc0,xm);
    xc0=_mm512_mask3_fmadd_pd(xa2,xb2,xc0,xm);
    xc0=_mm512_mask3_fmadd_pd(xa3,xb3,xc0,xm);
    _mm512_mask_storeu_pd(&c[i*4+0],xm,xc0);
   }
}

int main(void){
  int iter=10;
  int nmatrices=10000000;
  int size=mnk*mnk*nmatrices;
  double* a= (double*) _mm_malloc(sizeof(double)*size,64);
  double* b= (double*) _mm_malloc(sizeof(double)*size,64);
  double* c= (double*) _mm_malloc(sizeof(double)*size,64);
  double time1,time2;
  for(int i=0;i<size;i++){
    a[i]=rand();
    b[i]=rand();
    c[i]=rand();
  }
  
  time1=mytime();
  for(int n=0;n<iter;n++){
    for(int i=0;i<size;i+=mnk*mnk){
      //matrixmul_mnk(&c[i],&a[i],&b[i]);
	  //you code goes here	
      matrixmul_mnk_opt1(&c[i],&a[i],&b[i]);
    }
  }
  time2=mytime();



  printf("time = %f s\n", time2-time1);
  printf("perf = %f GFLOPs\n", (2.0*mnk*mnk*mnk*nmatrices*iter)/(time2-time1)/1000.0/1000.0/1000.0);
}
