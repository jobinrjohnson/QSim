/*
 * qubit.h
 *
 *  Created on: 30 Jan 2019
 *      Author: jobinrjohnson
 */

#ifndef IMPLEMENTATION_QUBIT_H_
#define IMPLEMENTATION_QUBIT_H_

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include <iostream>

class Qubit {

protected:
	gsl_vector_complex * v_state;

public:
	Qubit();
	Qubit(double, double, double, double);
	virtual ~Qubit();
	void print_state();
	gsl_vector_complex * get_state();
	bool set_state(gsl_vector_complex *);
};

#endif /* IMPLEMENTATION_QUBIT_H_ */
