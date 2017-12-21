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

void CacheLine::setdata(int value) {
	this->data = value;
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

void CacheLine::relocateStatePtr() {
	this->currentState = new Exclusive;
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
				processor->state = Success;
				//this->storeItr = this->dataStore.begin() + this->itrShift;
				printCacheLocalOperation(processor->role, prReq, tag, Hit);
				delete this->cacheState;
				this->cacheState = new CacheIdle;
				//cout << "Data store size: " << this->dataStore.size() << endl;
				processor->printReadSuccess(\
						this->storeItr->currentState->StateName, this->storeItr->tag, this->storeItr->data);
				break;
			case PrWr:
				// report write success
				processor->state = Success;
				printCacheLocalOperation(processor->role, prReq, tag, Hit);
				delete this->cacheState;
				this->cacheState = new CacheIdle;
				// write new data into that cache line, if using the same iterator, gives problems for the next printWriteSuccess call
				this->writeCacheLineData(this->prRequestedTag, this->prRequestedValue);
				// report success
				processor->printWriteSuccess(this->storeItr->currentState->StateName, this->storeItr->tag, this->storeItr->data);

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
	this->addCacheLineOnMiss<LevelTwoCache>(tag, this->l2cache);
}

void LevelOneCache::getCacheLineFromBus(int tag) {
	this->addCacheLineOnMiss<SharedBus>(tag, this->bus);
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

void LevelOneCache::setPrRequestedValue(int value) {
	this->prRequestedValue = value;
}

void LevelOneCache::setPrRequest(ProcessorRequest request) {
	this->prRequest = request;
}

void LevelOneCache::processSniffedSignal(BusRequest sniffedBusSignal, int sniffedTag) {


}

void LevelOneCache::resetL1dCache() {
	// reset L1d cache state
	delete this->cacheState;
	this->cacheState = new CacheIdle;

	if (this->dataStore.size() != 0) {
		// delete state of each cache line
		this->storeItr = this->dataStore.begin();
		for (; this->storeItr != this->dataStore.end(); ++this->storeItr) {
			delete this->storeItr->currentState;
			// prevent dangling pointer
			this->storeItr->currentState = NULL;
		}

		// erase the cache line
		this->dataStore.clear();
	}
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

void LevelOneCache::copyCacheLineState() {
	// copy state, not a good design...
	// to avoid multiple cache line copies sharing the same dynamically allocated state
	string tmpState = this->dataStore.back().currentState->StateName;

	if (tmpState == "Exclusive") {
		this->dataStore.back().currentState = new Exclusive;
	}

	if (tmpState == "Shared") {
		this->dataStore.back().currentState = new Shared;
	}
}

void LevelOneCache::writeCacheLineData(int _tag, int _value) {
	vector<CacheLine>::iterator tmpWriteItr = this->dataStore.begin();
	for(; tmpWriteItr != this->dataStore.end(); ++tmpWriteItr) {
		if (tmpWriteItr->tag == _tag) {
			// write new data
			tmpWriteItr->setdata(_value);
			tmpWriteItr->currentState->localOperation(this->prRequest, &(*tmpWriteItr));
		}
	}
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
		this->storeItr->currentState = NULL;
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
		}
	}

	return *(this->storeItr);
}

void LevelTwoCache::statePtrRelocate(int tag) {
	// re-allocate the cache line state pointer in the data source
	// this is to prevent "ptr being freed was not allocated"
	this->storeItr = this->dataStore.begin();
	for (; this->storeItr != this->dataStore.end(); ++this->storeItr) {
		// break on the matching cache line
		if ((this->storeItr->tag) == tag) {
			break;
		}
	}

	this->storeItr->currentState = new Exclusive;
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

void Processor::writeCacheLine(int tag, int value) {
	this->state = WriteWait;
	cout << "\t Processor " << this->role << " sends PrWr " << "requesting tag: " << tag \
			<< ", requesting value: " << value << endl;
	this->lOneCache.setProcessorOwnership(this);
	this->lOneCache.setCacheState(new CacheProcessingPrWr);
	this->lOneCache.setPrRequestedTag(tag);
	this->lOneCache.setPrRequestedValue(value);
	this->lOneCache.setPrRequest(PrWr);
}

void Processor::printReadSuccess(string state, int tag, int data) {
	string rdSuccessMsg = "\t Processor " + to_string(this->role) + " PrRd success - ";
	cout << rdSuccessMsg << endl;
	printCacheLine(state, tag, data);
}

void Processor::printWriteSuccess(string state, int tag, int data) {
	string rdSuccessMsg = "\t Processor " + to_string(this->role) + " PrWr success - ";
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

	// reset the L1d cache of this processor
	this->lOneCache.resetL1dCache();
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

CacheLine SharedBus::returnCacheLine(int tag) {
	// copy the state to avoid "ptr being freed was not allocated"
	return this->busData;
}

void SharedBus::statePtrRelocate(int tag) {
	this->busData.relocateStatePtr();
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
	l1cache->processPrRequest(l1cache->processor, l1cache->prRequest);
}

CacheSniffing::CacheSniffing() { this->StateName = "CacheSniffing"; };
CacheSniffing::~CacheSniffing() { }
void CacheSniffing::operation(LevelOneCache *l1cache) {
	printSniff(l1cache->bus->getBussSingalBuffer(), l1cache->bus->getBroadcastTag(), l1cache->bus->translator);
}

CacheProcessingSniffed::CacheProcessingSniffed() { 	this->StateName = "CacheProcessingSniffed"; };
CacheProcessingSniffed::~CacheProcessingSniffed() { }
void CacheProcessingSniffed::operation(LevelOneCache *l1cache) {
	printProcessingSniff(l1cache->bus->getBussSingalBuffer(), l1cache->bus->getBroadcastTag(), l1cache->bus->translator);
	// sniffing cache has the copy, set to shared and return it because the acting cache is trying to read it
	if (l1cache->bsRequestSignal == BusRd) {
		if (l1cache->searchTagStore(l1cache->prRequestedTag) == true) {
			// change current cacheline state to shared
			l1cache->storeItr->stateOperation(Remote, l1cache->prRequest, BusRd);
			l1cache->bus->setBusSignalBuffer(FlushOpt);
			l1cache->storeItr = l1cache->dataStore.begin() + l1cache->itrShift;
			l1cache->bus->setBusDataBuffer(*(l1cache->storeItr));
			delete l1cache->cacheState;
			l1cache->cacheState = new CacheDone;
		}
		else {
			delete l1cache->cacheState;
			l1cache->cacheState = new CacheDone;

			// otherwise indicate "I don't have it"
			l1cache->bus->setBusSignalBuffer(NoFlushOpt);
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

	if (l1cache->bsRequestSignal == FlushOpt) {
		if (l1cache->cacheState->StateName != "CacheDone") {
			l1cache->bus->busReset();
			// get cache line from the other cache via shared bus
			l1cache->getCacheLineFromBus(l1cache->prRequestedTag);
			//set back to original processing state
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

