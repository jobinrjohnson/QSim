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

#include <qubit.h>

#define GATE_HARDAMARD 1
#define GATE_PAULI_X 2
#define GATE_CNOT 3

#include <iostream>

class Gates {

protected:
	gsl_matrix_complex * get_gate_matrix(int);

public:
	Gates();
	virtual ~Gates();
	void apply_harhmard();

	void apply_gate(Qubit &, int);

};

#endif /* IMPLEMENTATION_GATES_H_ */
