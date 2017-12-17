/*
 * cache_line.cpp
 *
 *  Created on: 13 Dec 2017
 *      Author: kunson01
 */

#include "components.h"

#include <iostream>
#include <stddef.h>
#include "mesi_fsm.h"
#include "request.h"
#include "logger.h"
#include "simulator.h"

using namespace std;

/*******************************************************************************************
 * Cache line method implementation
 *******************************************************************************************/
CacheLine::CacheLine(int _tag, int _data) {
	this->tag = _tag;
	this->data = _data;

	// Each new cache line has default state is exclusive
	this->currentState = new Exclusive;
}

void CacheLine::setState( State *newState) {
	// need to delete current state and assign new one
	delete this->currentState;
	this->currentState = newState;
}

void CacheLine::stateOperation(Request request, ProcessorRequest prRqst, BusRequest busRqst) {

	if (request == Local) {
		this->currentState->localOperation(prRqst, this);
	}
	else {
		this->currentState->remoteOperation(busRqst, this);
	}

}

/*******************************************************************************************
 * L1d cache method implementation
 *******************************************************************************************/
LevelOneCache::LevelOneCache(LevelTwoCache *_l2cache): l2cache(_l2cache)  { }
LevelOneCache::~LevelOneCache() {
	//cout << "In L1 destroyer..." << endl;
	// delete cache line states on the heap
	this->storeItr = this->dataStore.begin();
	for(; this->storeItr != this->dataStore.end(); ++this->storeItr) {
		delete this->storeItr->currentState;
	}
}


void LevelOneCache::lruDelete() {
	// delete the Least Recently Used cache line
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

void LevelOneCache::processPrRequest(Processor *processor, ProcessorRequest prReq, int tag, int value) {

	// if L1d has the requested cache line and state is valid, return it.
	// if L1d has the requested cache line and state is invalid, or
	// if L1d does not have the requested cache line, place a BusRd request in bus signal buffer
	// if other L1d cache has it, it will be supplied by the other L1d cache
	// otherwise get it from L2 to model the temporal and spatial locality
	// meanwhile L1d needs to put a BusRequest on the shared bus

	// dealing with cache miss
	if (this->searchTagStore(tag) == false) {
		//this->addCacheLineOnMiss(tag, this->l2cache);

		// put BusRd on the bus if processor trying to read something not existing
		// in its L1d cache
	}

	string s;
	this->storeItr = this->dataStore.begin() + this->itrShift;

	// now processing the PrRequest
	switch(prReq) {
		case PrRd:
			// return the data and set processor state to success
			processor->state = Success;
			this->storeItr = this->dataStore.begin() + this->itrShift;
			printCacheLocalOperation(processor->role, prReq, tag);
			processor->printReadSuccess(\
					this->storeItr->currentState->StateName, this->storeItr->tag, this->storeItr->data);
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

/*******************************************************************************************
 * L2 cache method implementation
 *******************************************************************************************/
LevelTwoCache::LevelTwoCache() {
	// populate L2 cache
	for(int i = 1; i<=(this->maxSize); i++) {
		// tag is i, data is i*10
		CacheLine tmp(i, i*10);
		this->dataStore.push_back(tmp);
	}
}

LevelTwoCache::~LevelTwoCache() {
	//cout << "In L2 destroyer..." << endl;
	// delete cache line states on the heap
	storeItr = this->dataStore.begin();
	for(; storeItr != this->dataStore.end(); ++this->storeItr) {
		delete this->storeItr->currentState;
	}
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

/*******************************************************************************************
 * processor method implementation
 *******************************************************************************************/
Processor::Processor(ProcessorState _state, ProcessorRole _role, LevelTwoCache *l2cache): \
							state(_state), role(_role), lOneCache(l2cache) { }

void Processor::readCacheLine(int tag) {
	// processor goes to ReadWait state and send the PrRd request to its own L1d cache
	this->state = ReadWait;
	cout << "\t Processor " << this->role << " sends PrRd " << "requesting tag: " << tag << endl;
	this->lOneCache.processPrRequest(this, PrRd, tag, 0);
}

void Processor::writeCacheLine(ProcessorRequest prReq, int tag, int value) {

}

void Processor::printReadSuccess(string state, int tag, int data) {
	string rdSuccessMsg = "\t Processor " + to_string(this->role) + " PrRd success - ";
	cout << rdSuccessMsg << endl;
	printCacheLine(state, tag, data);
}

int Processor::getState() {
	return this->state;
}

/*******************************************************************************************
 * shared bus method implementation
 *******************************************************************************************/
void SharedBus::setCacheLineBuffer (CacheLine *cl) {
	this->lineBuffer = cl;
}

void SharedBus::setCacheRequestBuffer(BusRequest busRqst) {
	this->cacheRequestBuffer = busRqst;
}

/*******************************************************************************************
 * simulation executor method implementation
 *******************************************************************************************/
SimExecutor::SimExecutor() {
	cout << "Cache Coherence MESI simulator, start simulation ..." << endl;
	cout << endl;
}

void SimExecutor::levelOneCacheInsertion(Processor *pr, int tag) {
	pr->lOneCache.addCacheLineOnMiss(tag, \
			pr->lOneCache.l2cache);
}

void setBusSignal(SharedBus *bus, int tag) {



}
