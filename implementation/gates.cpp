/*
 * qubit.cpp
 *
 *  Created on: 28 Jan 2019
 *      Author: jobinrjohnson
 */

#include <gates.h>

Gates::Gates() {

}

Gates::~Gates() {
	// TODO Auto-generated destructor stub
}

gsl_matrix_complex * Gates::get_gate_matrix(int gate_name) {

	if (gate_name == GATE_HARDAMARD) {

		gsl_matrix_complex * hardmard_matrix = gsl_matrix_complex_alloc(2, 2);
		gsl_matrix_complex_set(hardmard_matrix, 0, 0, gsl_complex_rect(1, 0));
		gsl_matrix_complex_set(hardmard_matrix, 0, 1, gsl_complex_rect(1, 0));
		gsl_matrix_complex_set(hardmard_matrix, 1, 0, gsl_complex_rect(1, 0));
		gsl_matrix_complex_set(hardmard_matrix, 1, 1, gsl_complex_rect(-1, 0));
		gsl_matrix_complex_scale(hardmard_matrix,
				gsl_complex_rect(M_SQRT1_2, 0));

		return hardmard_matrix;
	}else if(gate_name == GATE_PAULI_X){

		gsl_matrix_complex * pauli_x_matrix = gsl_matrix_complex_alloc(2, 2);
		gsl_matrix_complex_set(pauli_x_matrix, 0, 0, gsl_complex_rect(0, 0));
		gsl_matrix_complex_set(pauli_x_matrix, 0, 1, gsl_complex_rect(1, 0));
		gsl_matrix_complex_set(pauli_x_matrix, 1, 0, gsl_complex_rect(1, 0));
		gsl_matrix_complex_set(pauli_x_matrix, 1, 1, gsl_complex_rect(0, 0));

		return pauli_x_matrix;

	}else if(gate_name == GATE_PAULI_Y){

		gsl_matrix_complex * pauli_y_matrix = gsl_matrix_complex_alloc(2, 2);
		gsl_matrix_complex_set(pauli_y_matrix, 0, 0, gsl_complex_rect(0, 0));
		gsl_matrix_complex_set(pauli_y_matrix, 0, 1, gsl_complex_rect(0, -1));
		gsl_matrix_complex_set(pauli_y_matrix, 1, 0, gsl_complex_rect(1, 0));
		gsl_matrix_complex_set(pauli_y_matrix, 1, 1, gsl_complex_rect(0, 0));

		return pauli_y_matrix;

	}else if(gate_name == GATE_PAULI_Z){

		gsl_matrix_complex * pauli_z_matrix = gsl_matrix_complex_alloc(2, 2);
		gsl_matrix_complex_set(pauli_z_matrix, 0, 0, gsl_complex_rect(1, 0));
		gsl_matrix_complex_set(pauli_z_matrix, 0, 1, gsl_complex_rect(0, 0));
		gsl_matrix_complex_set(pauli_z_matrix, 1, 0, gsl_complex_rect(0, 0));
		gsl_matrix_complex_set(pauli_z_matrix, 1, 1, gsl_complex_rect(-1, 0));

		return pauli_z_matrix;

	}else if(gate_name == GATE_T){

		double gate_angle = 0;
		if(gate_name == GATE_T){
			gate_angle = M_PI_4;
		}

		gsl_matrix_complex * gate_matrix = gsl_matrix_complex_alloc(2, 2);
		gsl_matrix_complex_set_all(gate_matrix, gsl_complex_rect(0, 0));

		gsl_matrix_complex_set(gate_matrix, 0, 0, gsl_complex_rect(1, 0));
		gsl_matrix_complex_set(gate_matrix, 1, 1, gsl_complex_rect(cos(gate_angle), sin(gate_angle)));

		return gate_matrix;

	}
	return NULL;

}

void Gates::apply_gate(Qubit &qubit, int gate_name) {

	gsl_matrix_complex * gate_matrix = get_gate_matrix(gate_name);
	// Create an output temp qubit
	gsl_vector_complex *op_qubit = NULL;
	op_qubit = gsl_vector_complex_alloc(2);
	gsl_vector_complex_set_all(op_qubit, GSL_COMPLEX_ZERO);

	// get cross product
	gsl_blas_zgemv(CblasNoTrans,
	GSL_COMPLEX_ONE, gate_matrix, qubit.get_state(),
	GSL_COMPLEX_ZERO, op_qubit);

	qubit.set_state(op_qubit);
}

void Gates::apply_harhmard() {

	//Setup Hardmard matrix
	gsl_matrix_complex * hardmard_matrix = gsl_matrix_complex_alloc(2, 2);
	gsl_matrix_complex_set(hardmard_matrix, 0, 0, gsl_complex_rect(1, 0));
	gsl_matrix_complex_set(hardmard_matrix, 0, 1, gsl_complex_rect(1, 0));
	gsl_matrix_complex_set(hardmard_matrix, 1, 0, gsl_complex_rect(1, 0));
	gsl_matrix_complex_set(hardmard_matrix, 1, 1, gsl_complex_rect(-1, 0));

	gsl_matrix_complex_scale(hardmard_matrix, gsl_complex_rect(M_SQRT1_2, 0));

	// Create a sample Qubit
	gsl_vector_complex * qubit = gsl_vector_complex_alloc(2);
	gsl_complex alpha = gsl_complex_rect(1, 0);
	gsl_complex beta = gsl_complex_rect(0, 0);
	gsl_vector_complex_set(qubit, 0, alpha);
	gsl_vector_complex_set(qubit, 1, beta);

	gsl_vector_complex *op_qubit = NULL;
	op_qubit = gsl_vector_complex_alloc(2);
	gsl_vector_complex_set_all(op_qubit, GSL_COMPLEX_ZERO);

	// Simply view
	for (int i = 0; i < 2; i++) {
		std::cout << GSL_REAL(gsl_vector_complex_get(qubit, i)) << " "
				<< GSL_IMAG(gsl_vector_complex_get(qubit, i)) << std::endl;
	}

	// get cross product
	gsl_blas_zgemv(CblasNoTrans,
	GSL_COMPLEX_ONE, hardmard_matrix, qubit,
	GSL_COMPLEX_ZERO, op_qubit);

	// Simply view
	for (int i = 0; i < 2; i++) {
		std::cout << GSL_REAL(gsl_vector_complex_get(op_qubit, i)) << " "
				<< GSL_IMAG(gsl_vector_complex_get(op_qubit, i)) << std::endl;
	}

}

