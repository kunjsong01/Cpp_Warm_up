/*
 * cache_line.cpp
 *
 *  Created on: 13 Dec 2017
 *      Author: kunson01
 */
#include "cache_line.h"
#include "mesi_fsm.h"
#include <stddef.h>

// Cache line method implementation
CacheLine::CacheLine(State *state) {
	this->currentState = NULL;
	this->setState(state);
}

void CacheLine::setState( State *newState) {
	this->currentState = newState;
}

void CacheLine::stateOperation( ) {
	this->currentState->operation(this);
}

