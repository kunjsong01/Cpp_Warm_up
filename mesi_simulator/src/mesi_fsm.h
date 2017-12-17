/*
 * mesi_fsm.h
 *
 *  Created on: 13 Dec 2017
 *      Author: kunson01
 */

#ifndef MESI_FSM_H_
#define MESI_FSM_H_

#include <string>

#include "components.h"
#include "request.h"

class State {
	public:
		string StateName;
	public:
		// operations in this state
		virtual void localOperation(ProcessorRequest stimulus, CacheLine *cl) {};
		virtual void remoteOperation(BusRequest stimulus, CacheLine *cl) {};
		// this will be used polymorphically, i.e. base class reference for derived class object
		// hence  polymorphically
		virtual ~State() {};
};

/*
 * Classes for each MESI state
 */

class Modified: public State {
	public:
		void localOperation(ProcessorRequest stimulus, CacheLine *cl);
		void remoteOperation(BusRequest stimulus, CacheLine *cl);
		Modified();
		~Modified();
};

class Exclusive: public State {
	public:
		void localOperation(ProcessorRequest stimulus, CacheLine *cl);
		void remoteOperation(BusRequest stimulus, CacheLine *cl);
		Exclusive();
		~Exclusive();
};

class Shared: public State {
	public:
		void localOperation(ProcessorRequest stimulus, CacheLine *cl);
		void remoteOperation(BusRequest stimulus, CacheLine *cl);
		Shared();
		~Shared();
};

class Invalid: public State {
	public:
		void localOperation(ProcessorRequest stimulus, CacheLine *cl);
		void remoteOperation(BusRequest stimulus, CacheLine *cl);
		Invalid();
		~Invalid();
};


#endif /* MESI_FSM_H_ */
