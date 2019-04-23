/*
 * q_reg.h
 *
 *  Created on: 31 Jan 2019
 *      Author: jobinrjohnson
 */

#ifndef IMPLEMENTATION_Q_REG_H_
#define IMPLEMENTATION_Q_REG_H_

#define STATUS_UNINITIALIZED 0
#define STATUS_INITIALIZED 1
#define STATUS_MEASURED 2

#include <qubit.h>
#include <gates.h>
#include <math.h>
#include <bitset>

class QReg : private Qubit, private Gates
{

private:
	int num_qubits;
	int status;
	gsl_matrix_complex *generate_gate_matrix(int, int, int);
	gsl_matrix_complex *compute_two_qubit_matrix(int, int, int);

public:
	QReg(int);
	QReg();
	virtual ~QReg();
	int get_status();
	void print_state();
	void produce_instance(int);
	void apply_gate(int, int, int qubit2 = -1);
	int measure();
	std::string measure_bit();
};

#endif /* IMPLEMENTATION_Q_REG_H_ */
