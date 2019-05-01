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
	else if (::q_reg.get_status() == STATUS_INITIALIZED)
	{
		if (items[0].compare("MEASURE") == 0)
		{
			std::cout << "Measuring the register : " << ::q_reg.measure() << std::endl;
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
		else if (items[0].compare("CNOT") == 0)
		{
			if (items.size() == 3)
			{
				int qubit_no1 = atoi(items[1].c_str());
				int qubit_no2 = atoi(items[2].c_str());
				::q_reg.apply_gate(GATE_CNOT, qubit_no1, qubit_no2);
				cout << "Applying CNOT on " << qubit_no1 << " and " << qubit_no2;
				cout << endl;
			}
			else
			{
				add_warn("invalid qubit indices provided for CNOT.", line_no);
			}
		}
		else if (items[0].compare("SWAP") == 0)
		{
			if (items.size() == 3)
			{
				int qubit_no1 = atoi(items[1].c_str());
				int qubit_no2 = atoi(items[2].c_str());
				::q_reg.apply_gate(GATE_SWAP, qubit_no1, qubit_no2);
				cout << "Applying SWAP on " << qubit_no1 << " and " << qubit_no2;
				cout << endl;
			}
			else
			{
				add_warn("invalid qubit indices provided for SWAP.", line_no);
			}
		}
		else
		{
			add_error("Invalid operation.", line_no);
		}
	}
	else if (::q_reg.get_status() == STATUS_UNINITIALIZED)
	{
		add_error("Quantum register not initialized.", line_no);
		return -1;
	}
	else if (::q_reg.get_status() == STATUS_MEASURED)
	{
		add_error("Quantum register measurement done, no further calculations on it.", line_no);
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
		if (line == "")
		{
			continue;
		}
		parse_apply(line, ++line_no);
		if (error != "")
		{
			break;
		}
		cout << "Φ : ";
		::q_reg.print_state();
		cout << endl;
		line = "";
	}

	fin.close();

	cout << "====================================================" << endl;
	if (::q_reg.get_status() != STATUS_MEASURED)
	{
		add_warn("Register not measured. use 'MEASURE'", ++line_no);
	}
	cout << warning << endl;
	cout << "====================================================" << endl;
	cout << error << endl;
	cout << "====================================================" << endl;
	if (::q_reg.get_status() == STATUS_MEASURED)
	{
		::q_reg.print_p_amps();
	}
	cout << "====================================================" << endl;

	if (::q_reg.get_status() == STATUS_MEASURED)
	{
		std::bitset<16> binary(::q_reg.measure());
		cout << binary.to_string().substr(16 - ::q_reg.get_num_qubits());
	}
	else
	{
		cout << "N/A";
	}

	return 1;
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		cerr << "Invalid arguements" << endl;
		return -1;
	}

	return read_cmd_line(argv[1]);

	QReg reg = QReg(2);
	reg.apply_gate(GATE_PAULI_Z, 0);
	reg.print_state();
	cout << "On Measure : " << reg.measure_bit();

	return 0;
}
