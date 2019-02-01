/*
 * q_reg.cpp
 *
 *  Created on: 31 Jan 2019
 *      Author: jobinrjohnson
 */

#include "q_reg.h"

#define ccout std::cout
#define cendl std::endl

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

void QReg::compute_cnot_matrix(int a, int b) {
	std::cout << "========================================" << std::endl;
	int i;

	gsl_matrix_complex * full_matrix = gsl_matrix_complex_alloc(
			pow(2, num_qubits), pow(2, num_qubits));

	gsl_matrix_complex * one_q_matrix = gsl_matrix_complex_alloc(1, 2);

	for (i = 0; i < pow(2, num_qubits); i++) {

		gsl_matrix_complex * ind_matrix = NULL;

		bool a_th = (i & (1 << (num_qubits - a - 1))) == 0 ? false : true;
		bool b_th = (i & (1 << (num_qubits - b - 1))) == 0 ? false : true;
		if (a_th) {
			b_th = !b_th;
		}

		int m;
		for (m = 0; m < num_qubits; m++) {

			int m_th = (i & (1 << (num_qubits - m - 1))) == 0 ? 0 : 1;

			if (m == b) {
				m_th = b_th ? 1 : 0;
			}

			if (m_th == 1) {
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

//			if (i == 2) {
//				ccout<< m_th;
//				print(one_q_matrix);
//			}

			if (ind_matrix == NULL) {
				ccout<<"\nGenerating No Kornicker ......";
				ind_matrix = gsl_matrix_complex_alloc(1, 2);
				gsl_matrix_complex_memcpy(ind_matrix,one_q_matrix);
//				ind_matrix = one_q_matrix;
				print(ind_matrix);
				ccout<<"MMMMMMMMMMMMMMMMMMMMMMMMMMMM";
			} else {

				ccout<<"\nGenerating Kornicker of ......";
				print(ind_matrix);
				ccout<<"And";
				print(one_q_matrix);
				ccout<<"----------------------------------";

				ind_matrix = generateKorniker(ind_matrix, one_q_matrix);
				print(ind_matrix);
				ccout<<"MMMMMMMMMMMMMMMMMMMMMMMMMMMM";
			}

//			if (i == 2) {
//				print(one_q_matrix);
//				ccout<<m<<" nulledddd";
//				print(ind_matrix);
//			}

		}


		gsl_vector_complex * v = gsl_vector_complex_alloc(pow(2, num_qubits));

		gsl_matrix_complex_get_row(v, ind_matrix, 0);
		gsl_matrix_complex_set_row(full_matrix, i, v);

		if (i == 2)
			ccout<<"fffffffffffffffffffffffff"<<std::endl;

		}

	print(full_matrix);

//	break;

//	return NULL;

}

gsl_matrix_complex * QReg::generate_gate_matrix(int GATE, int qubit,
		int qubit2 = -1) {

	gsl_matrix_complex * gate__matrix = Gates::get_gate_matrix(GATE);

	gsl_matrix_complex * identity = gsl_matrix_complex_alloc(2, 2);
	gsl_matrix_complex_set_identity(identity);

	int i;

	gsl_matrix_complex * accum = NULL;

	if (GATE == GATE_CNOT) {

		gate__matrix = Gates::get_gate_matrix(GATE_PAULI_X);

//		std::cout << "Got"<<std::endl;

		gsl_matrix_complex * c_matrix = gsl_matrix_complex_alloc(2, 2);
		gsl_matrix_complex_set_zero(c_matrix);
		gsl_matrix_complex_set(c_matrix, 0, 0, gsl_complex_rect(1, 0));
		gsl_matrix_complex_set(c_matrix, 1, 1, gsl_complex_rect(1, 0));

//		print(c_matrix);

		for (i = 0; i < num_qubits; i++) {

			if (i == qubit) {

				if (accum == NULL) {
					accum = c_matrix;
				} else {
					accum = generateKorniker(accum, c_matrix);
				}

			} else if (i == qubit2) {

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
//	print(accum);

	return accum;

}

void QReg::apply_gate(int GATE, int qubit1, int qubit2) {

	int num_states = pow(2, num_qubits);

	this->compute_cnot_matrix(0, 2);

	std::cout << std::endl << std::endl << std::endl;

	return;

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
