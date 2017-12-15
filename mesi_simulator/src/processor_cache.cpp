/*
 * cache_line.cpp
 *
 *  Created on: 13 Dec 2017
 *      Author: kunson01
 */
#include <iostream>
#include <stddef.h>
#include <string>
#include "mesi_fsm.h"
#include "processor_cache.h"
#include "request.h"
#include "logger.h"
#include "simulator.h"

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
LevelOneCache::LevelOneCache(LevelTwoCache *_l2cache): l2cache(_l2cache)  { }

void LevelOneCache::lruDelete() {
	// delete the Least Recently Used cacheline
	this->storeItr = this->dataStore.begin();
	this->dataStore.erase(this->storeItr);
}

void LevelOneCache::addCacheLineOnMiss(int _tag, LevelTwoCache *nextLevelCache) {
	// first put request on bus to notify the other caches in the cluster
	// TO-DO:

	// check capacity
	if (this->dataStore.size() == this->maxSize ) {
		this->storeItr = this->dataStore.begin();
		this->dataStore.erase(this->storeItr);
	}

	// query the next level cache, i.e. L2 cache for the missing line
	this->dataStore.push_back(nextLevelCache->returnCacheLine(_tag));
}

bool LevelOneCache::searchTagStore(int tag) {

	bool isIn = false;

	// search the tag in this cache
	this->storeItr = this->dataStore.begin();
	this->itrShift = 0;
	for (; this->storeItr != this->dataStore.end(); ++this->storeItr) {
		++this->itrShift;
		if (this->storeItr->tag == tag) {
			isIn = true;
			break;
		}
	}

	return isIn;
}

void LevelOneCache::processPrRequest(ProcessorRequest prReq, int tag, int value) {

	// if L1d has the requested cache line, return it.
	// otherwise get it from L2 to model the temporal and spatial locality
	// meanwhile L1d needs to put a BusRequest on the shared bus

	// dealing with cache miss
	if (this->searchTagStore(tag) == false) {
		this->addCacheLineOnMiss(tag, this->l2cache);
	}

	string s;
	this->storeItr = this->dataStore.begin() + this->itrShift;

	// now processing the PrRequest
	switch(prReq) {
		case PrRd:
			s = "PrRd operation on cache line with tag: " + to_string(this->storeItr->tag) + ", data: " + to_string(this->storeItr->data);
			printCacheOperation(s);
			break;
		case PrWr:
			break;
		default:
			cout << " Unknown prReq" << endl;
	}
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

// processor method implementation
Processor::Processor(ProcessorRole _role, LevelTwoCache *l2cache): role(_role), lOneCache(l2cache) { }

void Processor::readCacheLine(int tag) {
	// call the process PrRequest method in L1d cache to do memory operation
	this->lOneCache.processPrRequest(PrRd, tag, 0);
}

void Processor::writeCacheLine(ProcessorRequest prReq, int tag, int value) {

}
