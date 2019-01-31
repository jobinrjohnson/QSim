/*
 * q_reg.h
 *
 *  Created on: 31 Jan 2019
 *      Author: jobinrjohnson
 */

#ifndef IMPLEMENTATION_Q_REG_H_
#define IMPLEMENTATION_Q_REG_H_

#include <qubit.h>
#include <math.h>
#include <bitset>

class QReg: private Qubit{

private:
	int num_qubits;

public:
	QReg(int);
	virtual ~QReg();
	void print_state();
	gsl_matrix_complex * generate_gate_matrix(int);
};

#endif /* IMPLEMENTATION_Q_REG_H_ */
