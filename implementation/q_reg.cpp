/*
 * q_reg.cpp
 *
 *  Created on: 31 Jan 2019
 *      Author: jobinrjohnson
 */

#include "q_reg.h"

QReg::QReg(int num_qubits) {

	this->num_qubits = num_qubits;
	int num_states = pow(2, num_qubits);

	v_state = gsl_vector_complex_alloc(num_states);
	// initialise state vector to |0>

	int i = 0;
	gsl_vector_complex_set(v_state, i++, gsl_complex_rect(1, 0));

	for (; i < num_states; i++) {
		gsl_vector_complex_set(v_state, i, gsl_complex_rect(0, 0));
	}

}

QReg::~QReg() {

	Qubit::~Qubit();

}

void QReg::print_state() {

	int num_states = pow(2, num_qubits);
	int i;

	for (i = 0; i < num_states; i++) {

		//TODO find a better way to convert to binary
		std::bitset<3> binary(i);

		if (i > 0) {
			std::cout << " + ";
		}

		std::cout << GSL_REAL(gsl_vector_complex_get(v_state, i));
		if (GSL_IMAG(gsl_vector_complex_get(v_state, i)) != 0) {
			std::cout << "+" << GSL_IMAG(gsl_vector_complex_get(v_state, i))
					<< "i";
		}

		std::cout << "|" << binary.to_string() << "⟩";

	}

	std::cout << std::endl;

}

// TODO move to utils
gsl_matrix_complex * generateKorniker(gsl_matrix_complex * a,
		gsl_matrix_complex *b) {
	int i, j, k, l;

	gsl_matrix_complex *c = gsl_matrix_complex_alloc(a->size1 * b->size1,
			a->size2 * b->size2);
	gsl_complex first, second;

	for (i = 0; i < a->size1; i++) {
		for (j = 0; j < a->size2; j++) {
			first = gsl_matrix_complex_get(a, i, j);
			for (k = 0; k < b->size1; k++) {
				for (l = 0; l < b->size2; l++) {
					second = gsl_matrix_complex_get(b, k, l);
					gsl_matrix_complex_set(c, b->size1 * i + k,
							b->size2 * j + l, gsl_complex_mul(first, second));
				}
			}
		}
	}

	return c;
}

//TODO remove this function
void print(gsl_matrix_complex * a) {
	int i, j;
	int m, p;

	m = a->size1;
	p = a->size2;

	for (i = 0; i < m; i++) {
		for (j = 0; j < p; j++) {
			std::cout << GSL_REAL(gsl_matrix_complex_get(a, i, j));
			std::cout << " ";

		}
		std::cout << std::endl;
	}

}

gsl_matrix_complex * QReg::generate_gate_matrix(int qubit = 1) {

	gsl_matrix_complex * gate__matrix = gsl_matrix_complex_alloc(2, 2);
	gsl_matrix_complex_set(gate__matrix, 0, 0, gsl_complex_rect(0, 0));
	gsl_matrix_complex_set(gate__matrix, 0, 1, gsl_complex_rect(1, 0));
	gsl_matrix_complex_set(gate__matrix, 1, 0, gsl_complex_rect(1, 0));
	gsl_matrix_complex_set(gate__matrix, 1, 1, gsl_complex_rect(0, 0));

	gsl_matrix_complex * identity = gsl_matrix_complex_alloc(2, 2);
	gsl_matrix_complex_set_identity(identity);

	int i;

	gsl_matrix_complex * accum = NULL;
	for (i = 0; i < num_qubits; i++) {

		if (i == qubit) {

			if (accum == NULL) {
				accum = gate__matrix;
			} else {
				accum = generateKorniker(accum, gate__matrix);
			}

		} else {

			if (accum == NULL) {
				accum = identity;
			} else {
				accum = generateKorniker(accum, identity);
			}

		}

	}
	print(accum);

	return accum;

}

