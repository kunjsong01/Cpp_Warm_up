/*
 * component_fsm.h
 */

#ifndef COMPONENT_FSM_H_
#define COMPONENT_FSM_H_

typedef enum {
	Idle=0,
	ReadWait,
	WriteWait,
	Succcess // indicate successful instruction retirement
} ProcessorState;

#endif /* COMPONENT_FSM_H_ */
