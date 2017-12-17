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

void printCacheLocalOperation (ProcessorRole id, ProcessorRequest pr, int tag) {
	if (pr == PrRd) {
		cout << "\t\t [Cache operation]: Processor id (" << id << "), " \
					"PrRd request - Cache tag: "<< tag << endl;
	}
	else {
		cout << "\t\t [Cache operation]: Processor id (" << id << "), " \
							"PrWr request - Cache tag: "<< tag << endl;
	}
}

void printFSMOperation (string msg) {
	cout << "\t\t [FSM operation]: " << msg << endl;
}
