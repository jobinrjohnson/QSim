/*
 * qubit.cpp
 *
 *  Created on: 28 Jan 2019
 *      Author: jobinrjohnson
 */

#include "include/Gates.h"

Gates::Gates() {
    
  double x = 5.0;
  double y = gsl_sf_bessel_J0 (x);
  printf ("J0(%g) = %.18e\n", x, y);
	
}

Gates::~Gates() {
	// TODO Auto-generated destructor stub
}

