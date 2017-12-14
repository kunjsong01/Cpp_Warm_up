/*
 * mesi_fsm.h
 *
 *  Created on: 13 Dec 2017
 *      Author: kunson01
 */

#ifndef MESI_FSM_H_
#define MESI_FSM_H_

#include "cache_line.h"
#include "state.h"

class State {
	public:
		// operations in this state
		virtual void operation(CacheLine *cl) {};
		// this will be used polymorphically, i.e. base class reference for derived class object
		// hence delete polymorphically
		virtual ~State() {};
};

/*
 * Classes for each MESI state
 */

class Modified: public State {
	public:
		void operation(CacheLine *cl);
		~Modified();
};

class Exclusive: public State {
	public:
		void operation(CacheLine *cl);
		~Exclusive();
};

class Shared: public State {
	public:
		void operation(CacheLine *cl);
		~Shared();
};

class Invalid: public State {
	public:
		void operation(CacheLine *cl);
		~Invalid();
};


#endif /* MESI_FSM_H_ */
