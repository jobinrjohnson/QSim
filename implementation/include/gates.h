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

#define ccout std::cout
#define cendl std::endl

#include <qubit.h>

#define GATE_HARDAMARD 1
#define GATE_PAULI_X 2
#define GATE_PAULI_Y 6
#define GATE_PAULI_Z 7
#define GATE_CNOT 3
#define GATE_SWAP 4
#define GATE_T 5

#include <iostream>

class Gates
{

  protected:
	gsl_matrix_complex *get_gate_matrix(int);

  public:
	Gates();
	virtual ~Gates();

	static bool get_measure(Qubit &q)
	{

		// TODO Better random and measure implementation

		gsl_vector_complex *state = q.get_state();
		double amp_0 = gsl_complex_abs2(gsl_vector_complex_get(state, 0));

		const gsl_rng_type *T;
		gsl_rng *r;
		gsl_rng_env_setup();
		gsl_rng_default_seed = time(NULL);
		T = gsl_rng_default;
		r = gsl_rng_alloc(T);

		double u = gsl_rng_uniform(r);

		gsl_rng_free(r);

		if (u >= amp_0)
		{
			return true;
		}

		return false;
	}
};

#endif /* IMPLEMENTATION_GATES_H_ */
