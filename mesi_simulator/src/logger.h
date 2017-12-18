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
void printCacheLocalOperation (ProcessorRole id, ProcessorRequest pr, int tag, HitMiss hm);
void printFSMOperation (string msg);
void printBus (BusRequest rqst, int tag);
void printSniff (BusRequest rqst, int tag);
void printProcessingSniff (BusRequest rqst, int tag);
void printCacheDone();
void pintL2CacheOperation(int tag);

#endif /* LOGGER_H_ */
