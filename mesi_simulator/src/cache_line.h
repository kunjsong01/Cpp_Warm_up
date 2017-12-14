/*
 * cache_line.h
 *
 *  Created on: 13 Dec 2017
 *      Author: kunson01
 */

#ifndef CACHE_LINE_H_
#define CACHE_LINE_H_

#include "state.h"

class State;

/*
 * Cache line class
 */
class CacheLine {
	private:
		State *currentState;
		// state handles two types of request
		ProcessorRequest prReq;
		BusRequest busReq;
	public:
		CacheLine( State *state);
		void setState( State *state);
		void stateOperation();
};


#endif /* CACHE_LINE_H_ */
