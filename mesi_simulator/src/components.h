/*
 * cache_line.h
 *	Modelling the L1d and L2 caches, as well as the cache line
 *
 *  Created on: 13 Dec 2017
 *      Author: kunson01
 */

#ifndef COMPONENTS_H_
#define COMPONENTS_H_

#include <vector>
#include <string>

#include "component_fsm.h"
#include "request.h"
#include "simulator.h"

using namespace std;

class State;
class LevelTwoCache;
class LevelOneCache;
class Processor;
class SimExecutor;

/*
 * Cache line class that models each cace line
 * Assumption:
 * 	1. This does not model the tag/index access methodology. The cache line is like:
 * 		State-Tag-Data. Access is purely based on Tag.
 */
class CacheLine {
	friend class LevelOneCache;
	friend class LevelTwoCache;
	friend class SimExecutor;

	private:
		State *currentState;
		int tag;
		int data;
	public:
		CacheLine( int _tag, int _data);
		void setState( State *state);
		void stateOperation(Request request, ProcessorRequest prRqst, BusRequest busRqst);
};

/*
 * Level one data cache: here we just model it to be a vector
 * which holds a bunch of cache line objects.
 * Maximum cache size is 5.
 * Assumption:
 * 	1. Cache retention policy is LRU, i.e. always pop_front in the vector
 * 	2. No tag store, the tag is inside the line itself.
 * 	3. This is a snoopy cache that performs bus sniffing.
 * 	   The snooper is just modelled as a function to get bus request and process it
 * 	4. For the sake of design simplicity, the tag store is modelled here. It just simply traverses all
 * 	   cache lines and compare the tag with the requested one.
 */
class LevelOneCache {

	// Processor (and bus?) can access it
	friend class Processor;
	friend class SimExecutor;

	private:
		vector<CacheLine> dataStore;
		vector<CacheLine>::iterator storeItr;
		int maxSize = 5;
		int itrShift = 0;
		// pointer to next level cache, i.e. the L2 cache
		LevelTwoCache *l2cache;

		void lruDelete();
		void addCacheLineOnMiss(int _tag, LevelTwoCache *l2cache);

		bool searchTagStore(int tag);
		void processPrRequest(Processor *processor, ProcessorRequest prReq, int tag, int value);
		void processBusRequest(BusRequest busReq);
		void putRequestOnBus(BusRequest busReq);

	public:
		LevelOneCache(LevelTwoCache *_l2cache);
		~LevelOneCache();
};

/*
 * Level two cache: here we just model it to be a vector
 * which holds a bunch of cache line objects.
 * Maximum cache size is 20.
 * Assumption:
 * 	1. In order to simplify the bus modelling, let's do a logical link
 * 	   between L1d and L2. If a cache miss occurs in L1d, let L1d quiry L2
 * 	   to get the requested cache line.
 */
class LevelTwoCache {

	// Note that this is just an "logical" link between L1 and L2 cache.
	// This is just to simply the bus model
	friend class LevelOneCache;
	private:
		vector<CacheLine> dataStore;
		vector<CacheLine>::iterator storeItr;
		int maxSize = 20;

		CacheLine returnCacheLine(int _tag);

	public:
		LevelTwoCache();
		~LevelTwoCache();
};

/*
 * Processor class that send PrWr and PrRd request to its cache.
 * To generate a PrWr request, the processor issues a command "store X value", where X
 * is the cache line tag and value the the new value to be written into that
 * cache line.
 * To generate a PrRd request, the processor issues a command "load X" to indicate its read
 * intention.
 *
 * For simulation purpose, a processor is set to be one of the two roles, "changeInitiator" or "changeFollower",
 * in each clock cycle.
 *
 * A "changeInitiator" is the processor that issues a read or write operation to its L1d cache which in turn puts a
 * new bus request on the bus.
 *
 * A "changeFollower" is the processor that sniffs the bus request a "changeInitiator" put on the bus. Its own L1d cache, a
 * snoopy cache, will update the cache lines accordingly.
 *
 * Assumption:
 * 	1. the processor is a single cycle machine, i.e. it completes a read or write operation in one cycle.
 */

class Processor {
	friend class LevelOneCache;
	friend class SimExecutor;

	private:
		LevelOneCache lOneCache;
		ProcessorRole role;
		ProcessorState state;

	public:
		Processor(ProcessorState _state, ProcessorRole _role, LevelTwoCache *l2cache);
		void readCacheLine(int tag);
		void writeCacheLine(ProcessorRequest prReq, int tag, int value);
		void printReadSuccess(string state, int tag, int data);
		int getState();
};

/*
 * shared bus class
 */
class SharedBus {
	friend class SimExecutor;
	friend class LevelOneCache;

	private:
		CacheLine *lineBuffer;
		BusRequest	cacheRequestBuffer;
	public:
		void setCacheLineBuffer (CacheLine *cl);
		void setCacheRequestBuffer(BusRequest busRqst);
};

/*
 * A simulator executor driver class that drives the simulation
 */
class SimExecutor {
	public:
		SimExecutor();
		void levelOneCacheInsertion(Processor *pr, int tag);
		void setBusSignal(SharedBus *bus, BusRequest busRqst);
};

#endif /* COMPONENTS_H_ */
