/*
 * processor_cache_fsm.h
 *
 *  Created on: 16 Dec 2017
 *      Author: kunson01
 */

#ifndef COMPONENT_FSM_H_
#define COMPONENT_FSM_H_

// processor request enum
typedef enum {
	Idle=0,
	ReadWait,
	WriteWait,
	Success
} ProcessorState;

#endif /* COMPONENT_FSM_H_ */
