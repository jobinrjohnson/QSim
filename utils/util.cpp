/*
 * util.cpp
 *
 *  Created on: 27 Jan 2019
 *      Author: jobinrjohnson
 */

#include <util.h>
#include <iostream>

char getLevel(unsigned short int level)
{
	char type;
	switch (level)
	{
	case LOG_LEVEL_VERBOSE:
		type = 'V';
		break;
	case LOG_LEVEL_INFO:
		type = 'I';
		break;
	case LOG_LEVEL_WARN:
		type = 'W';
		break;
	case LOG_LEVEL_ERROR:
		type = 'E';
		break;
	case LOG_LEVEL_FATAL:
		type = 'F';
		break;
	default:
		type = 'V';
	}

	return type;
}

void printdebug(unsigned short int level, const char *message)
{
	char type = getLevel(level);

	if (level < LOG_LEVEL)
	{
		return;
	}

	std::cout << type << ": " << message << "\n";
	// TODO add debugging options
}
