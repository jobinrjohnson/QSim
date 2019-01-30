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

using namespace std;

int LOG_LEVEL = LOG_LEVEL_VERBOSE;

int main(int argc, char **argv) {

	printdebug(LOG_LEVEL_INFO, "Simulator Started");

	Gates g = Gates();
//	g.apply_harhmard();

	Qubit q = Qubit();
	q.print_state();

	g.apply_gate(q, GATE_HARDAMARD);
	q.print_state();

	cout << Measure::get_measure(q);

	return 0;

}

