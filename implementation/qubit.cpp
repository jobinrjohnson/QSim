/*
 * qubit.cpp
 *
 *  Created on: 30 Jan 2019
 *      Author: jobinrjohnson
 */

#include "include/qubit.h"

Qubit::Qubit() {

	// Initiaize the Qubit to 1|0> + 0|1> state
	v_state = gsl_vector_complex_alloc(2);
	gsl_complex alpha = gsl_complex_rect(1, 0);
	gsl_complex beta = gsl_complex_rect(0, 0);
	gsl_vector_complex_set(v_state, 0, alpha);
	gsl_vector_complex_set(v_state, 1, beta);

}

Qubit::Qubit(double l_alpha, double l_beta, double l_alpha_imag = 0,
		double l_beta_imag = 0) {
	// Initiaize the Qubit to 1|0> + 0|1> state
	v_state = gsl_vector_complex_alloc(2);
	gsl_complex alpha = gsl_complex_rect(l_alpha, l_alpha_imag);
	gsl_complex beta = gsl_complex_rect(l_beta, l_beta_imag);
	gsl_vector_complex_set(v_state, 0, alpha);
	gsl_vector_complex_set(v_state, 1, beta);

}

Qubit::~Qubit() {
	// Free Vector memory
	if(v_state != NULL)
		gsl_vector_complex_free(v_state);
}

void Qubit::print_state() {

	std::cout << GSL_REAL(gsl_vector_complex_get(v_state, 0));
	if (GSL_IMAG(gsl_vector_complex_get(v_state, 0)) != 0) {
		std::cout << "+" << GSL_IMAG(gsl_vector_complex_get(v_state, 0)) << "i";
	}
	std::cout << "|0>";

	std::cout << " + ";

	std::cout << GSL_REAL(gsl_vector_complex_get(v_state, 1));
	if (GSL_IMAG(gsl_vector_complex_get(v_state, 1)) != 0) {
		std::cout << "+" << GSL_IMAG(gsl_vector_complex_get(v_state, 1)) << "i";
	}
	std::cout << "|1>";

	std::cout << std::endl;

}

gsl_vector_complex * Qubit::get_state() {
	return v_state;
}

bool Qubit::set_state(gsl_vector_complex * new_state) {
	gsl_vector_complex_free(v_state);
	v_state = new_state;
	return true;
}
