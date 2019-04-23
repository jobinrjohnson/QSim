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

void add_error(std::string m_error, int line_number)
{
	error.append("\n");
	error.append("line " + std::to_string(line_number) + " : " + m_error);
}
void add_warn(std::string m_warning, int line_number)
{
	warning.append("\n");
	warning.append("line " + std::to_string(line_number) + " : " + m_warning);
}

int parse_apply(std::string line, int line_no)
{
	std::cout << ">> " << line << std::endl;
	if (line[0] == '#' || line.length() == 0)
	{
		return 0;
	}

	std::vector<std::string> items = explode(line, ' ');

	if (items[0].compare("QREG") == 0)
	{
		int no_qubit = atoi(items[1].c_str());
		if (no_qubit == 0)
		{
			add_error("Quantum register size error.", line_no);
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
				add_warn("No qubit index provided.", line_no);
			}
		}
		else if (items[0].compare("X") == 0)
		{
			if (items.size() > 1)
			{
				int _counter = 0;
				cout << "Applying PAULI X on";
				for (_counter = 1; _counter < items.size(); _counter++)
				{
					int qubit_no = atoi(items[_counter].c_str());
					cout << " " << qubit_no;
					::q_reg.apply_gate(GATE_PAULI_X, qubit_no);
				}
				cout << endl;
			}
			else
			{
				add_warn("No qubit index provided.", line_no);
			}
		}
		else if (items[0].compare("Y") == 0)
		{
			if (items.size() > 1)
			{
				int _counter = 0;
				cout << "Applying PAULI Y on";
				for (_counter = 1; _counter < items.size(); _counter++)
				{
					int qubit_no = atoi(items[_counter].c_str());
					cout << " " << qubit_no;
					::q_reg.apply_gate(GATE_PAULI_Y, qubit_no);
				}
				cout << endl;
			}
			else
			{
				add_warn("No qubit index provided.", line_no);
			}
		}
		else if (items[0].compare("X") == 0)
		{
			if (items.size() > 1)
			{
				int _counter = 0;
				cout << "Applying PAULI X on";
				for (_counter = 1; _counter < items.size(); _counter++)
				{
					int qubit_no = atoi(items[_counter].c_str());
					cout << " " << qubit_no;
					::q_reg.apply_gate(GATE_PAULI_Z, qubit_no);
				}
				cout << endl;
			}
			else
			{
				add_warn("No qubit index provided.", line_no);
			}
		}
		else if (items[0].compare("T") == 0)
		{
			if (items.size() > 1)
			{
				int _counter = 0;
				cout << "Applying T on";
				for (_counter = 1; _counter < items.size(); _counter++)
				{
					int qubit_no = atoi(items[_counter].c_str());
					cout << " " << qubit_no;
					::q_reg.apply_gate(GATE_T, qubit_no);
				}
				cout << endl;
			}
			else
			{
				add_warn("No qubit index provided.", line_no);
			}
		}
	}
	else
	{
		add_error("Error : Quantum register not initialized.", line_no);
		return -1;
	}

	return 0;
}

int read_cmd_line(char *filename)
{

	ifstream fin;
	fin.open(filename);
	string line;
	unsigned int line_no = 0;

	while (fin)
	{
		getline(fin, line);
		parse_apply(line, ++line_no);
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
