/*
 * mesi_fsm.cpp
 *
 *  Created on: 13 Dec 2017
 *      Author: kunson01
 */

#include <iostream>
#include "mesi_fsm.h"

using namespace std;

/*
 * Protocol implementation of Modified state
 */
Modified::~Modified() { }
Modified::Modified() {
	this->StateName = "Modified";
}

void Modified::localOperation(ProcessorRequest stimulus, CacheLine *cl) {
	// now processing the PrRequest
	switch(stimulus) {
		case PrRd:
			// no state change for local read in modified state
			break;
		case PrWr:
			break;
		default:
			cout << " Cache Line: Unknown stimulus in Modified state!" << endl;
	}
}

void Modified::remoteOperation(BusRequest stimulus, CacheLine *cl) {

}

/*
 * Protocol implementation of Exclusive state
 */
Exclusive::~Exclusive() { cout << "In exclusive: destroying " << endl;}
Exclusive::Exclusive() {
	//this->StateName = "Exclusive";
}

void Exclusive::localOperation(ProcessorRequest stimulus, CacheLine *cl) {
	switch(stimulus) {
		case PrRd:
			// no state change for local read in modified state
			break;
		case PrWr:
			break;
		default:
			cout << " Cache Line: Unknown stimulus in Modified state" << endl;
	}
}

void Exclusive::remoteOperation(BusRequest stimulus, CacheLine *cl) {

}

/*
 * Protocol implementation of Shared state
 */
Shared::~Shared() { }
Shared::Shared() {
	this->StateName = "Shared";
}

void Shared::localOperation(ProcessorRequest stimulus, CacheLine *cl) {
	switch(stimulus) {
		case PrRd:
			// no state change for local read in modified state
			break;
		case PrWr:
			break;
		default:
			cout << " Cache Line: Unknown stimulus in Modified state" << endl;
	}
}

void Shared::remoteOperation(BusRequest stimulus, CacheLine *cl) {

}

/*
 * Protocol implementation of Invalid state
 */
Invalid::~Invalid() { }

void Invalid::localOperation(ProcessorRequest stimulus, CacheLine *cl) {
	switch(stimulus) {
		case PrRd:
			// no state change for local read in modified state
			break;
		case PrWr:
			break;
		default:
			cout << " Cache Line: Unknown stimulus in Modified state" << endl;
	}
}

void Invalid::remoteOperation(BusRequest stimulus, CacheLine *cl) {

}

