/*
 * q_reg.h
 *
 *  Created on: 31 Jan 2019
 *      Author: jobinrjohnson
 */

#ifndef IMPLEMENTATION_Q_REG_H_
#define IMPLEMENTATION_Q_REG_H_

#include <qubit.h>
#include <gates.h>
#include <math.h>
#include <bitset>

class QReg: private Qubit, private Gates{

private:
	int num_qubits;
	gsl_matrix_complex * generate_gate_matrix(int, int, int);
	gsl_matrix_complex * compute_cnot_matrix(int, int);

public:
	QReg(int);
	virtual ~QReg();
	void print_state();
	void apply_gate(int, int, int qubit2 = -1);
};

#endif /* IMPLEMENTATION_Q_REG_H_ */
