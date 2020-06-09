 
#ifndef _SQ_MATRIX_HPP
#define _SQ_MATRIX_HPP

#include <iostream>
#include "types.hpp"
#include "mkl.h"

static void sq_dgemm(real_type* c, real_type* a, real_type* b, const int nrows_a, const int ncols_b, const int ncols_a);

static void sq_dgemm(real_type* c, real_type* a, real_type* b, const int nrows_a, const int ncols_b, const int ncols_a)
{
     cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, nrows_a, ncols_b, ncols_a, 1., a, ncols_a, 
          b, ncols_b, 0., c, ncols_a);
}

#endif
