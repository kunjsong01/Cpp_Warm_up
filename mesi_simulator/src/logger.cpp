/*
 * logger.cpp
 *
 *  Created on: 14 Dec 2017
 *      Author: kunson01
 */

#include <string>
#include <iostream>
#include "logger.h"

using namespace std;

void printCacheLine (string state, int tag, int data) {
	string msg = "\t\t Cache Line - Tag: " + to_string(tag) + ", " + \
					"State: " + state + ", " \
					"Data: " + to_string(data);
	cout << msg << endl;
}

void printCacheLocalOperation (ProcessorRole id, ProcessorRequest pr, int tag, HitMiss hm) {
	if (pr == PrRd) {
		cout << "\t\t [Cache Operation]: Processor id (" << id << "), " \
					"PrRd request - Cache tag: "<< tag << endl;
	}
	else {
		cout << "\t\t [Cache Operation]: Processor id (" << id << "), " \
							"PrWr request - Cache tag: "<< tag << endl;
	}

	cout << "\t\t [Cache Operation]: 0-Miss, 1-Hit? Result: " << hm << endl;
}

void printFSMOperation (string msg) {
	cout << "\t\t [FSM Operation]: " << msg << endl;
}

void printBus (BusRequest rqst, int tag) {
	string msg = "Request: " + to_string(rqst) + \
			", Tag: " + to_string(tag);

	cout << "\t\t [Bus Broadcasting]: " << msg << endl;
}

void printSniff (BusRequest rqst, int tag) {
	string msg = "Request: " + to_string(rqst) + \
			", Tag: " + to_string(tag);

	cout << "\t\t [Cache Sniffing]: " << msg << endl;
}
