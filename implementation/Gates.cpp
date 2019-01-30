/*
 * qubit.cpp
 *
 *  Created on: 28 Jan 2019
 *      Author: jobinrjohnson
 */

#include "include/Gates.h"

Gates::Gates() {

}

Gates::~Gates() {
	// TODO Auto-generated destructor stub
}

void Gates::apply_harhmard() {

	//Setup Hardmard matrix
	gsl_matrix * hardmard_matrix = gsl_matrix_alloc(2, 2);
	gsl_matrix_set(hardmard_matrix, 0, 0, 1);
	gsl_matrix_set(hardmard_matrix, 0, 1, 1);
	gsl_matrix_set(hardmard_matrix, 1, 0, 1);
	gsl_matrix_set(hardmard_matrix, 1, 1, -1);
	gsl_matrix_scale(hardmard_matrix, M_SQRT1_2);

	// Create a sample Qubit
	gsl_vector_complex * qubit = gsl_vector_complex_alloc(2);
	gsl_complex alpha = gsl_complex_rect(1, 0);
	gsl_complex beta = gsl_complex_rect(0, 0);
	gsl_vector_complex_set(qubit, 0, alpha);
	gsl_vector_complex_set(qubit, 1, beta);

	// Simply view
	for (int i = 0; i < 2; i++) {
		std::cout << GSL_REAL(gsl_vector_complex_get(qubit, i)) << " "
				<< GSL_IMAG(gsl_vector_complex_get(qubit, i)) << std::endl;
	}

}

