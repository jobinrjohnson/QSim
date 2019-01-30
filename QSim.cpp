/*
 * QSim.cpp
 *
 *  Created on: 27 Jan 2019
 *      Author: jobinrjohnson
 */

#include <iostream>
#include <string>
#include <util.h>

#include <Gates.h>
#include <qubit.h>

using namespace std;

int LOG_LEVEL = LOG_LEVEL_VERBOSE;

int main(int argc, char **argv) {

	printdebug(LOG_LEVEL_INFO, "Simulator Started");

	Gates g =  Gates();
//	g.apply_harhmard();

	Qubit q = Qubit();
	q.print_state();

	g.apply_gate(q,GATE_HARDAMARD);
	q.print_state();

	return 0;

}

