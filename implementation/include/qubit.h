/*
 * qubit.h
 *
 *  Created on: 28 Jan 2019
 *      Author: jobinrjohnson
 */

#ifndef IMPLEMENTATION_QUBIT_H_
#define IMPLEMENTATION_QUBIT_H_

#define COMPLEX_TEMPLATE long double

#include <complex>
#include <cmath>

class qubit {

	// Q = alpha |0> + beta |1>
private:
	std::complex<COMPLEX_TEMPLATE> state_alpha;
	std::complex<COMPLEX_TEMPLATE> state_beta;

	bool check_normalization(std::complex<COMPLEX_TEMPLATE>,std::complex<COMPLEX_TEMPLATE>);

public:
	qubit();
	qubit(COMPLEX_TEMPLATE, COMPLEX_TEMPLATE);
	virtual ~qubit();

};

#endif /* IMPLEMENTATION_QUBIT_H_ */
