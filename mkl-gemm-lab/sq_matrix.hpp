
#ifndef _SQ_MULTIPLY_HPP
#define _SQ_MULTIPLY_HPP
#include <iostream>
#include "types.hpp"

class sq_matrix
{
	public:
	  int nrows;
	  int ncols;
	  real_type *values;
	  
	  sq_matrix(int nsize) : nrows(nsize), ncols(nsize)
	  {
		values = new real_type[nrows*ncols];
	  };
	  
	  ~sq_matrix()
	  {
		delete [] values;  
	  };
	  
	  void initialize(real_type n)
	  {
		for(int i=0; i<nrows; ++i)
		  for(int j=0; j<ncols; ++j)
		    values[i*ncols + j] = n;
	  };
	  	  
	  void print()
	  {
		for(int i=0; i<nrows; ++i)
		  for(int j=0; j<ncols; ++j)
		    std::cout << "m[" << i << "][" << j << "]= " << values[i*ncols + j] << std::endl;
      }	  	  
};
#endif
