/*
 * Gates.h
 *
 *  Created on: 28 Jan 2019
 *      Author: jobinrjohnson
 */

#ifndef IMPLEMENTATION_GATES_H_
#define IMPLEMENTATION_GATES_H_

#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_math.h>
#include <iostream>

class Gates {

public:
	Gates();
	virtual ~Gates();

	void apply_harhmard();

};

#endif /* IMPLEMENTATION_GATES_H_ */
