/*
 * util.h
 *
 *  Created on: 27 Jan 2019
 *      Author: jobinrjohnson
 */

#ifndef UTILS_UTIL_H_
#define UTILS_UTIL_H_

// LOG LEVELS
#define LOG_LEVEL_VERBOSE 0
#define LOG_LEVEL_INFO 1
#define LOG_LEVEL_WARN 2
#define LOG_LEVEL_ERROR 3
#define LOG_LEVEL_FATAL 4

extern int LOG_LEVEL;

extern void printdebug(unsigned short int, const char *);
extern char getLevel(unsigned short int);

#endif /* UTILS_UTIL_H_ */
