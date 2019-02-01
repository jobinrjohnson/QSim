/*
 * Measure.h
 *
 *  Created on: 27 Jan 2019
 *      Author: jobinrjohnson
 */

#ifndef IMPLEMENTATION_MEASURE_H_
#define IMPLEMENTATION_MEASURE_H_

#include <qubit.h>
#include <gsl/gsl_rng.h>

class Measure {
public:
	Measure();
	virtual ~Measure();
	static bool get_measure(Qubit &q) {

		// TODO Better random and measure implementation

		gsl_vector_complex *state = q.get_state();
		double amp_0 = gsl_complex_abs2(gsl_vector_complex_get(state, 0));

		const gsl_rng_type * T;
		gsl_rng * r;
		gsl_rng_env_setup();
		gsl_rng_default_seed = time(NULL);
		T = gsl_rng_default;
		r = gsl_rng_alloc(T);

		double u = gsl_rng_uniform(r);

		gsl_rng_free(r);

		if (u >= amp_0) {
			return true;
		}

		return false;

	}
};

#endif /* IMPLEMENTATION_MEASURE_H_ */
