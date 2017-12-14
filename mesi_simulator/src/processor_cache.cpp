/*
 * cache_line.cpp
 *
 *  Created on: 13 Dec 2017
 *      Author: kunson01
 */
#include <iostream>
#include <stddef.h>
#include "mesi_fsm.h"
#include "processor_cache.h"
#include "request.h"

using namespace std;

// Cache line method implementation
CacheLine::CacheLine(int _tag, int _data) {
	this->tag = _tag;
	this->data = _data;
	this->currentState = NULL;

	// Each new cache line has default state is exclusive
	this->currentState = new Exclusive;
}

void CacheLine::setState( State *newState) {
	// need to delete current state and assign new one
	delete this->currentState;
	this->currentState = newState;
}

void CacheLine::stateOperation( ) {
	this->currentState->operation(this);
}

// L1d cache method implementation
void LevelOneCache::lruDelete() {
	// delete the Least Recently Used cacheline
	this->storeItr = this->dataStore.begin();
	this->dataStore.erase(this->storeItr);
}

void LevelOneCache::addCacheLineOnMiss(int _tag, LevelTwoCache nextLevel) {
	// first put request on bus to notify the other caches in the cluster
	// TO-DO:

	// check capacity
	if (this->dataStore.size() == 5 ) {
		this->storeItr = this->dataStore.begin();
		this->dataStore.erase(this->storeItr);
	}

	// query the next level cache, i.e. L2 cache for the missing line
	this->dataStore.push_back(nextLevel.returnCacheLine(_tag));
}

void LevelOneCache::processPrRequest(ProcessorRequest prReq) {


}

void LevelOneCache::processBusRequest(BusRequest busReq) {

}

void LevelOneCache::putRequestOnBus(BusRequest busReq) {

}

// L2 cache method implementation
LevelTwoCache::LevelTwoCache() {
	// populate L2 cache
	for(int i = 1; i<=(this->maxSize); i++) {
		// tag is i, data is i*10
		CacheLine tmp(i, i*10);
		this->dataStore.push_back(tmp);
	}

	cout << "Size of L2 cache: " << this->dataStore.size() << endl;
}

CacheLine LevelTwoCache::returnCacheLine(int _tag) {
	// return cachline using the input tag
	// ********* TO-DO: add tag checking here, if tag not recognized *************
	this->storeItr = this->dataStore.begin();
	for (; this->storeItr != this->dataStore.end(); ++this->storeItr) {
		// break on the matching cache line
		if ((this->storeItr->tag) == _tag) {
			break;
		};
	}
	return *(this->storeItr);
}
