/*
 * components.cpp
 */

#include "components.h"

#include <iostream>
#include <stddef.h>
#include "mesi_fsm.h"
#include "request.h"
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

string CacheLine::getCurrentStateName() {
	return this->currentState->StateName;
}

State* CacheLine::getCurrentState() {
	return this->currentState;
}

/*******************************************************************************************
 * L1d cache method implementation
 *******************************************************************************************/
LevelOneCache::LevelOneCache(LevelTwoCache *_l2cache, SharedBus *bus): l2cache(_l2cache)  {
	this->bus = bus;
	this->cacheState = new CacheIdle;
}

LevelOneCache::~LevelOneCache() {

	// delete cache state
	delete this->cacheState;
	//cout << "L1d cache before deleting: " << this->dataStore.size() << endl;

	// delete cache line states on the heap
	this->storeItr = this->dataStore.begin();
	for(; this->storeItr != this->dataStore.end(); ++this->storeItr) {
		//delete this->storeItr->currentState;
		delete this->storeItr->getCurrentState();
	}
}

void LevelOneCache::lruDelete() {
	// delete the Least Recently Used cache line
	this->storeItr = this->dataStore.begin();
	this->dataStore.erase(this->storeItr);
}

void LevelOneCache::addCacheLineOnMiss(int _tag, LevelTwoCache *nextLevelCache) {
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
		if (this->storeItr->tag == tag) {
			isIn = true;
			break;
		}
		++this->itrShift;
	}

	return isIn;
}

void LevelOneCache::processPrRequest(Processor *processor, ProcessorRequest prReq) {

	// set cache state
	int tag = this->prRequestedTag;

	// dealing with cache miss
	if (this->searchTagStore(tag) == true) {
		string s;
		this->storeItr = this->dataStore.begin() + this->itrShift;
		//cout << "This is shift" << itrShift << endl;

		// now processing the PrRequest
		switch(prReq) {
			case PrRd:
				// return the data and set processor state to success
				processor->state = Succcess;
				//this->storeItr = this->dataStore.begin() + this->itrShift;
				printCacheLocalOperation(processor->role, prReq, tag, Hit);
				delete this->cacheState;
				this->cacheState = new CacheIdle;
				//cout << "Data store size: " << this->dataStore.size() << endl;
				processor->printReadSuccess(\
						this->storeItr->currentState->StateName, this->storeItr->tag, this->storeItr->data);
				break;
			case PrWr:
				break;
			default:
				cout << " Unknown prReq" << endl;
		}
	}
	else {
		//this->addCacheLineOnMiss(tag, this->l2cache);
		// print cache miss
		printCacheLocalOperation(processor->role, prReq, tag, Miss);

		// set bus signal and requested cache line tag
		this->bus->setBusSignalBuffer(BusRd);
		this->bus->setBroadcastTag(tag);
	}
}

void LevelOneCache::getCacheLineFromL2(int tag) {
	pintL2CacheOperation(tag);
	this->addCacheLineOnMiss(tag, this->l2cache);
}

void LevelOneCache::putRequestOnBus(BusRequest busReq) {

}

void LevelOneCache::setCacheState(CacheState *_state) {
	delete this->cacheState;
	this->cacheState = _state;
}

void LevelOneCache::setPrRequestedTag(int tag) {
	this->prRequestedTag = tag;
}

void LevelOneCache::setPrRequest(ProcessorRequest request) {
	this->prRequest = request;
}

void LevelOneCache::processSniffedSignal(BusRequest sniffedBusSignal, int sniffedTag) {


}

void LevelOneCache::resetL1dCache() {
	this->storeItr = this->dataStore.begin();
	for (; this->storeItr != this->dataStore.end(); ++this->storeItr) {
		// delete state of each cache line
		delete this->storeItr->currentState;
		// prevent dangling pointer
		this->storeItr->currentState = NULL;
	}

	// erase the cache line
	this->dataStore.clear();
}

void LevelOneCache::act() {
	//cout << "Cache state in act: " << this->cacheState->StateName << endl;
	this->cacheState->operation(this);
}

void LevelOneCache::sniff() {

	if (this->cacheState->StateName != "CacheDone") {
		//cout << "Cache state in sniff: " << this->cacheState->StateName << endl;
		this->bsRequestSignal = this->bus->busSignal;
		this->prRequestedTag = this->bus->requestedTag;
		delete this->cacheState;
		this->cacheState = new CacheSniffing;
		this->cacheState->operation(this);

		delete this->cacheState;
		this->cacheState = new CacheProcessingSniffed;
		this->cacheState->operation(this);
	}
	else {
		this->cacheState->operation(this);
	}
}

void LevelOneCache::setProcessorOwnership(Processor *_processor) {
	this->processor = _processor;
}

void LevelOneCache::printData(int tag) {
	printCache<LevelOneCache>(tag, this);
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

	this->dataStore.clear();
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

void LevelTwoCache::printData(int tag) {
	cout << "Tag " << tag << " in L2 cache: " << endl;
	printCache<LevelTwoCache>(tag, this);
}

/*******************************************************************************************
 * processor method implementation
 *******************************************************************************************/
Processor::Processor(ProcessorState _state, ProcessorRole _role, LevelTwoCache *l2cache, SharedBus *bus): \
							state(_state), role(_role), lOneCache(l2cache, bus) { }

void Processor::readCacheLine(int tag) {
	// processor goes to ReadWait state and send the PrRd request to its own L1d cache
	this->state = ReadWait;
	cout << "\t Processor " << this->role << " sends PrRd " << "requesting tag: " << tag << endl;
	this->lOneCache.setProcessorOwnership(this);
	this->lOneCache.setCacheState((new CacheProcessingPrRd));
	this->lOneCache.setPrRequestedTag(tag);
	this->lOneCache.setPrRequest(PrRd);
}

void Processor::writeCacheLine(ProcessorRequest prReq, int tag, int value) {

}

void Processor::printReadSuccess(string state, int tag, int data) {
	string rdSuccessMsg = "\t Processor " + to_string(this->role) + " PrRd success - ";
	cout << rdSuccessMsg << endl;
	printCacheLine(state, tag, data);
}

ProcessorState Processor::getState() {
	return this->state;
}

ProcessorRole Processor::getRole() {
	return this->role;
}

void Processor::cacheAct() {
	this->lOneCache.act();
}

void Processor::cacheSniff() {
	// cache sniffs the bus
	// just print out the bus signal and data buffers to confirm that this cache actually
	// sniffs the bus
	this->lOneCache.sniff();
}

void Processor::processorReset() {
	// reset processor state
	this->state = Idle;

	if (this->lOneCache.dataStore.size() != 0) {
		// reset the L1d cache of this processor
		this->lOneCache.resetL1dCache();
	}
}

LevelOneCache* Processor::getL1Cache() {
	return &(this->lOneCache);
}

/*******************************************************************************************
 * shared bus method implementation
 *******************************************************************************************/
SharedBus::SharedBus(): busData(255, 255) {
	this->busSignal = None;
	this->requestedTag = 255; // 255 means "no data"
	BusRqstTranslator _translator;
	this->translator = _translator;
}

SharedBus::~SharedBus() {
	delete this->busData.getCurrentState();
}

void SharedBus::setBusDataBuffer (CacheLine cl) {
	this->busData = cl;
}

void SharedBus::setBusSignalBuffer(BusRequest busRqst) {
	this->busSignal = busRqst;
}

BusRequest SharedBus::getBussSingalBuffer() {
	return this->busSignal;
}
int SharedBus::getBroadcastTag() {
	return this->requestedTag;
}

void SharedBus::printBusInfo () {
	printBus(this->busSignal, this->requestedTag, this->translator);
}

void SharedBus::setBroadcastTag(int tag) {
	this->requestedTag = tag;
}

void SharedBus::busReset() {
	this->busSignal = None;
	this->requestedTag = 255; // 255 means "no data"
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

void SimExecutor::setBusSignal(SharedBus *bus, BusRequest busRqst) {

}

void SimExecutor::printBusBroadcast(SharedBus *bus) {
	bus->printBusInfo();
}

void SimExecutor::setCacheAct(Processor *pr) {
	pr->cacheAct();
}

void SimExecutor::setCacheSniff(Processor *pr) {
	pr->cacheSniff();
}

void SimExecutor::resetSharedBus(SharedBus *bus) {
	bus->busReset();
}

void SimExecutor::resetProcessor(Processor *p) {
	p->processorReset();
}

/*******************************************************************************************
 * cache state method implementation
 *******************************************************************************************/
CacheIdle::CacheIdle() { this->StateName = "CacheIdle"; };
CacheIdle::~CacheIdle() { };
void CacheIdle::operation(LevelOneCache *l1cache) {

}

CacheProcessingPrRd::CacheProcessingPrRd() { this->StateName = "CacheProcessingPrRd"; };
CacheProcessingPrRd::~CacheProcessingPrRd() { }
void CacheProcessingPrRd::operation(LevelOneCache *l1cache) {
	l1cache->processPrRequest(l1cache->processor, l1cache->prRequest);
}

CacheProcessingPrWr::CacheProcessingPrWr() { this->StateName = "CacheProcessingPrWr"; };
CacheProcessingPrWr::~CacheProcessingPrWr() { }
void CacheProcessingPrWr::operation(LevelOneCache *l1cache) {

}

CacheSniffing::CacheSniffing() { this->StateName = "CacheSniffing"; };
CacheSniffing::~CacheSniffing() { }
void CacheSniffing::operation(LevelOneCache *l1cache) {
	printSniff(l1cache->bus->getBussSingalBuffer(), l1cache->bus->getBroadcastTag(), l1cache->bus->translator);
}

CacheProcessingSniffed::CacheProcessingSniffed() { 	this->StateName = "CacheProcessingSniffed"; };
CacheProcessingSniffed::~CacheProcessingSniffed() { }
void CacheProcessingSniffed::operation(LevelOneCache *l1cache) {
	// otherwise indicate "I don't have it"
	l1cache->bus->setBusSignalBuffer(NoFlushOpt);
	printProcessingSniff(l1cache->bus->getBussSingalBuffer(), l1cache->bus->getBroadcastTag(), l1cache->bus->translator);
	// sniffing cache has the copy, set to shared and return it because the acting cache is trying to read it
	if (l1cache->bsRequestSignal == BusRd) {
		if (l1cache->searchTagStore(l1cache->prRequestedTag) == true) {
			l1cache->bus->setBusSignalBuffer(FlushOpt);
			l1cache->storeItr = l1cache->dataStore.begin() + l1cache->itrShift;
			l1cache->bus->setBusDataBuffer(*(l1cache->storeItr));
		}
		else {
			delete l1cache->cacheState;
			l1cache->cacheState = new CacheDone;
		}
	}

	if ( l1cache->bsRequestSignal == NoFlushOpt ) {
		if (l1cache->cacheState->StateName != "CacheDone") {
			// upon completion, reset the bus
			l1cache->bus->busReset();
			l1cache->getCacheLineFromL2(l1cache->prRequestedTag);
			delete l1cache->cacheState;
			l1cache->cacheState = new CacheProcessingPrRd;
		}
	}
}

CacheDone::CacheDone() { this->StateName = "CacheDone"; };
CacheDone::~CacheDone() { };
void CacheDone::operation(LevelOneCache *l1cache) {
	printCacheDone();
}

