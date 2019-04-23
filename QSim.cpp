/*
 * QSim.cpp
 *
 *  Created on: 27 Jan 2019
 *      Author: jobinrjohnson
 */

#include <iostream>
#include <fstream>
#include <string>
#include <gates.h>
#include <util.h>

#include <string>
#include <vector>
#include <sstream>
#include <utility>

#include <qubit.h>
#include <measure.h>

#include <q_reg.h>

using namespace std;

int LOG_LEVEL = LOG_LEVEL_VERBOSE;
std::string error = "";
std::string warning = "";

QReg q_reg;

std::vector<std::string> explode(std::string const &s, char delim)
{
	std::vector<std::string> result;
	std::istringstream iss(s);

	for (std::string token; std::getline(iss, token, delim);)
	{
		result.push_back(std::move(token));
	}

	return result;
}

int add_error(std::string error,int line_number){
	
}
int add_warn(std::string m_warning,int line_number){
	warning.append("\n");
	warning.append(m_warning);
}

int parse_apply(std::string line)
{
	std::cout << ">> " << line << std::endl;
	if (line[0] == '#' || line.length() == 0)
	{
		return 0;
	}

	error.append(line);

	std::vector<std::string> items = explode(line, ' ');

	if (items[0].compare("QREG") == 0)
	{
		int no_qubit = atoi(items[1].c_str());
		if (no_qubit == 0)
		{
			error.append("Error : Quantum register size error.");
			return -1;
		}
		::q_reg.produce_instance(no_qubit);
		std::cout << "Register initialized for : " << no_qubit << " qubits" << std::endl;
	}
	else if (1) //(q_reg == NULL) TODO FIX this condition
	{
		if (items[0].compare("MEASURE") == 0)
		{
			std::cout << "Measuring the register : " << ::q_reg.measure() << std::endl;
			::q_reg.print_state();
			return 0;
		}
		else if (items[0].compare("HARDAMARD") == 0)
		{
			if (items.size() > 1)
			{
				int _counter = 0;
				cout << "Applying hardamard on";
				for (_counter = 1; _counter < items.size(); _counter++)
				{
					int qubit_no = atoi(items[_counter].c_str());
					cout << " " << qubit_no;
					::q_reg.apply_gate(GATE_HARDAMARD, qubit_no);
				}
				cout << endl;
			}
			else
			{
				add_warn("No qubit index provided.",0);
			}
		}
	}
	else
	{
		error.append("Error : Quantum register not initialized.");
		return -1;
	}

	return 0;
}

int read_cmd_line(char *filename)
{

	ifstream fin;
	fin.open(filename);
	string line;

	while (fin)
	{
		getline(fin, line);
		parse_apply(line);
	}

	fin.close();

	return 1;
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		cerr << "Invalid arguements" << endl;
		return -1;
	}

	cout << "\n\n\n";

	return read_cmd_line(argv[1]);

	cout << "\n\n\n";
	QReg reg = QReg(2);
	reg.apply_gate(GATE_PAULI_Z, 0);
	reg.print_state();
	cout << "On Measure : " << reg.measure_bit();
	cout << "\n\n\n";

	return 0;
}
