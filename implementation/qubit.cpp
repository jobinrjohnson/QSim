/*
 * qubit.cpp
 *
 *  Created on: 28 Jan 2019
 *      Author: jobinrjohnson
 */

#include "include/qubit.h"

qubit::qubit() {
	// initialize the qubit to zero
	this->state_alpha = std::complex<COMPLEX_TEMPLATE>(1.0,0.0);
	this->state_beta = std::complex<COMPLEX_TEMPLATE>(0.0,0.0);
}

qubit::qubit(COMPLEX_TEMPLATE a, COMPLEX_TEMPLATE b){

	std::complex<COMPLEX_TEMPLATE> state_A(a,0.0);
	std::complex<COMPLEX_TEMPLATE> state_B(b,0.0);

	if(!this->check_normalization(state_A,state_B)){
		throw "Incorrect Qubit formation";
		return;
	}

	// initialize with given types
	this->state_alpha = state_A;
	this->state_beta = state_B;

}


bool qubit::check_normalization(std::complex<COMPLEX_TEMPLATE> state_A, std::complex<COMPLEX_TEMPLATE> state_B){

	double a = pow(state_A.real(),2) - pow(state_A.imag(),2);
	double b = pow(state_B.real(),2) - pow(state_B.imag(),2);

	if(( a*a + b*b ) == 1){
		return true;
	}

	return false;

}


qubit::~qubit() {
	// TODO Auto-generated destructor stub
}

