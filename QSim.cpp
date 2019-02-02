/*
 * QSim.cpp
 *
 *  Created on: 27 Jan 2019
 *      Author: jobinrjohnson
 */

#include <gates.h>
#include <iostream>
#include <string>
#include <util.h>

#include <qubit.h>
#include <measure.h>

#include <q_reg.h>

using namespace std;

int LOG_LEVEL = LOG_LEVEL_VERBOSE;

int main(int argc, char **argv) {

//	Gates g = Gates();
//
//	printdebug(LOG_LEVEL_INFO, "Initialise a gate");
//	Qubit q = Qubit();
//	q.print_state();
//
//	printdebug(LOG_LEVEL_INFO, "Applying Hardamard Gate");
//
//	g.apply_gate(q, GATE_HARDAMARD);
//	q.print_state();
//
//	printdebug(LOG_LEVEL_INFO, "Applying Measurement Gate");
//	cout << Measure::get_measure(q);

	QReg reg = QReg(1);
//	reg.apply_gate(GATE_T,0); // @suppress("Invalid arguments")
	reg.apply_gate(GATE_HARDAMARD,0); // @suppress("Invalid arguments")
//	reg.apply_gate(GATE_SWAP,0,1); // @suppress("Invalid arguments")

	reg.print_state();

	return 0;

}

