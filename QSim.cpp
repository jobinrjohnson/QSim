/*
 * QSim.cpp
 *
 *  Created on: 27 Jan 2019
 *      Author: jobinrjohnson
 */

#include <iostream>
#include <string>
#include <util.h>

#include <qubit.h>

using namespace std;

int LOG_LEVEL = LOG_LEVEL_VERBOSE;

int main(int argc, char **argv) {

	printdebug(LOG_LEVEL_INFO, "Simulator Started");

	qubit q1 =  qubit(1,0);

	return 0;

}

