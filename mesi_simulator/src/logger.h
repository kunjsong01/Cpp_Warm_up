/*
 * logger.h
 *
 *  Created on: 14 Dec 2017
 *      Author: kunson01
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include "simulator.h"
#include "request.h"

using namespace std;

void printCacheLine (string state, int tag, int data);
void printCacheLocalOperation (ProcessorRole id, ProcessorRequest pr, int tag);
void printFSMOperation (string msg);

#endif /* LOGGER_H_ */
