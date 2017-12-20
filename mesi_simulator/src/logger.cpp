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

// BusRqstTranslator method implementation
BusRqstTranslator::BusRqstTranslator() {
	this->busRqstDict[BusRd] = "BusRd";
	this->busRqstDict[BusRdx] = "BusRdx";
	this->busRqstDict[BusUpgr] = "BusUpgr";
	this->busRqstDict[Flush] = "Flush";
	this->busRqstDict[FlushOpt] = "FlushOpt";
	this->busRqstDict[NoFlushOpt] = "NoFlushOpt";
	this->busRqstDict[None] = "None";
}

string BusRqstTranslator::translate(BusRequest rqst) {
	return this->busRqstDict[rqst];
}

// logger method implementation
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

void printBus (BusRequest rqst, int tag, BusRqstTranslator &translator) {
	string msg = "Request: " + translator.translate(rqst) + \
			", Tag: " + to_string(tag);

	cout << "\t\t [Bus Broadcasting]: " << msg << endl;
}

void printSniff (BusRequest rqst, int tag, BusRqstTranslator &translator) {
	string msg = "Request: " + translator.translate(rqst) + \
			", Tag: " + to_string(tag);

	cout << "\t\t [Cache Sniffing]: " << msg << endl;
}

void printProcessingSniff (BusRequest rqst, int tag, BusRqstTranslator &translator) {

	string msg = "Request: " + translator.translate(rqst) + \
					", Tag: " + to_string(tag);

	if (rqst == None) {
		cout << "\t\t [Cache Processing Sniffed Signal]: " << msg \
				<< ". No signal to be processed ..." << endl;
	}
	else {
		cout << "\t\t [Cache Processing Sniffed Signal]: " << msg << endl;
	}
}

void printCacheDone() {
	cout << "\t\t [Cache Done]: No more actions or sniffs. This cache finished the job in this round." << endl;
}

void pintL2CacheOperation(int tag) {
	string msg = "Getting cache line with tag " + to_string(tag) + " from L2 ...";
	cout << "\t\t [L1d cache querying shared L2]: " << msg << endl;
}
