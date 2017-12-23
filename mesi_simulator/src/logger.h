/*
 * logger.h
 *
 *  Created on: 14 Dec 2017
 *      Author: kunson01
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <map>
#include <typeinfo>
#include "simulator.h"
#include "request.h"

using namespace std;

class BusRqstTranslator {
	public:
		map <int, string> busRqstDict;
		BusRqstTranslator();
		string translate(BusRequest rqst);
};

void printCacheLine (string state, int tag, int data);
void printCacheLocalOperation (ProcessorRole id, ProcessorRequest pr, int tag, HitMiss hm);
void printFSMOperation (string msg);
void printBus (BusRequest rqst, int tag, BusRqstTranslator &translator);
void printSniff (BusRequest rqst, int tag, BusRqstTranslator &translator);
void printCacheSearch(int tag);
void printProcessingSniff (BusRequest rqst, int tag, BusRqstTranslator &translator);
void printCacheDone();
void pintL2CacheOperation(int tag);
void printWriteBack(int tag, int data);
void printBoundary();

template <class T>
void printCache(int tag, T *cache) {
	string msg;
	if (cache->dataStore.size() != 0) {
		cache->storeItr = cache->dataStore.begin();
			for (; cache->storeItr != cache->dataStore.end(); ++cache->storeItr) {
				if (cache->storeItr->tag == tag) {
					break;
				}
			}

			string tmpType = typeid(*cache).name();
			string tmpL2Type = "LevelTwo";
			if (tmpType.find(tmpL2Type) != string::npos) {
				msg = "Current cache line status - tag: " + to_string(cache->storeItr->tag) \
						+ ", data: " + to_string(cache->storeItr->data);
			}
			else {
				msg = "Current cache line status - tag: " + to_string(cache->storeItr->tag) \
						+ ", data: " + to_string(cache->storeItr->data) + ", state: " + \
						cache->storeItr->getCurrentStateName();
			}
	}
	else {
		msg = "No cache line here";
	}

	cout << "\t\t [cache line info]: " << msg << endl;
}

#endif /* LOGGER_H_ */
