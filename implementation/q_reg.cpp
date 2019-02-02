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

//TODO fix error from this by freeing pointers correctly
QReg::~QReg() {

	if (v_state != NULL)
		gsl_vector_complex_free(v_state);

}

void QReg::print_state() {

	int num_states = pow(2, num_qubits);
	int i;

	for (i = 0; i < num_states; i++) {

		//TODO find a better way to convert to binary
		std::bitset<16> binary(i);

		if (i > 0) {
			std::cout << " + ";
		}

		std::cout << GSL_REAL(gsl_vector_complex_get(v_state, i));
		if (GSL_IMAG(gsl_vector_complex_get(v_state, i)) != 0) {
			std::cout << "+" << GSL_IMAG(gsl_vector_complex_get(v_state, i))
					<< "i";
		}

		std::cout << "|" << binary.to_string().substr(16 - num_qubits) << "⟩";

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

	std::cout << std::endl;
//	std::cout << std::endl;

	for (i = 0; i < m; i++) {
		for (j = 0; j < p; j++) {
			std::cout << GSL_REAL(gsl_matrix_complex_get(a, i, j));
			std::cout << " ";

		}
		std::cout << std::endl;
	}

}

gsl_matrix_complex * QReg::compute_two_qubit_matrix(int GATE, int a, int b) {
	int i, m;

	gsl_matrix_complex * full_matrix = gsl_matrix_complex_alloc(
			pow(2, num_qubits), pow(2, num_qubits));

	gsl_matrix_complex * one_q_matrix = gsl_matrix_complex_alloc(1, 2);

	for (i = 0; i < pow(2, num_qubits); i++) {

		gsl_matrix_complex * ind_matrix = NULL;

		bool a_th = (i & (1 << (num_qubits - a - 1))) == 0 ? false : true;
		bool b_th = (i & (1 << (num_qubits - b - 1))) == 0 ? false : true;

		for (m = 0; m < num_qubits; m++) {

			bool m_th = (i & (1 << (num_qubits - m - 1))) == 0 ? false : true;

			if (GATE == GATE_SWAP) {

				if (m == a) {
					m_th = b_th;
				} else if (m == b) {
					m_th = a_th;
				}

			} else if (GATE == GATE_CNOT) {

				if (m == b) {
					if (a_th) {
						b_th = !b_th;
					}
					m_th = b_th ? 1 : 0;
				}
			}

			if (m_th) {
				gsl_matrix_complex_set(one_q_matrix, 0, 0,
						gsl_complex_rect(0, 0));
				gsl_matrix_complex_set(one_q_matrix, 0, 1,
						gsl_complex_rect(1, 0));
			} else {
				gsl_matrix_complex_set(one_q_matrix, 0, 0,
						gsl_complex_rect(1, 0));
				gsl_matrix_complex_set(one_q_matrix, 0, 1,
						gsl_complex_rect(0, 0));
			}

			if (ind_matrix == NULL) {
				ind_matrix = gsl_matrix_complex_alloc(1, 2);
				gsl_matrix_complex_memcpy(ind_matrix, one_q_matrix);
			} else {
				ind_matrix = generateKorniker(ind_matrix, one_q_matrix);
			}

		}

		gsl_vector_complex * v = gsl_vector_complex_alloc(pow(2, num_qubits));

		gsl_matrix_complex_get_row(v, ind_matrix, 0);
		gsl_matrix_complex_set_row(full_matrix, i, v);

		gsl_matrix_complex_free(ind_matrix);
		gsl_vector_complex_free(v);

	}
	gsl_matrix_complex_free(one_q_matrix);

	return full_matrix;
}

gsl_matrix_complex * QReg::generate_gate_matrix(int GATE, int qubit,
		int qubit2 = -1) {

	gsl_matrix_complex * gate__matrix = Gates::get_gate_matrix(GATE);

	if (num_qubits == 1) {
		return gate__matrix;
	}

	gsl_matrix_complex * identity = gsl_matrix_complex_alloc(2, 2);
	gsl_matrix_complex_set_identity(identity);

	int i;

	gsl_matrix_complex * accum = NULL;

	if (GATE == GATE_CNOT || GATE == GATE_SWAP) {
		accum = this->compute_two_qubit_matrix(GATE, qubit, qubit2);

	} else {

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

	}
	gsl_matrix_complex_free(identity);
	gsl_matrix_complex_free(gate__matrix);

	return accum;

}

void QReg::apply_gate(int GATE, int qubit1, int qubit2) {

	int num_states = pow(2, num_qubits);

	gsl_matrix_complex * gate_matrix = generate_gate_matrix(GATE, qubit1,
			qubit2);

// Create an output temp qubit
	gsl_vector_complex *op_qubit = NULL;
	op_qubit = gsl_vector_complex_alloc(num_states);
	gsl_vector_complex_set_all(op_qubit, GSL_COMPLEX_ZERO);

// get cross product
	gsl_blas_zgemv(CblasNoTrans,
	GSL_COMPLEX_ONE, gate_matrix, this->v_state,
	GSL_COMPLEX_ZERO, op_qubit);

	gsl_matrix_complex_free(gate_matrix);
	gsl_vector_complex_memcpy(v_state, op_qubit);
	gsl_vector_complex_free(op_qubit);

}
