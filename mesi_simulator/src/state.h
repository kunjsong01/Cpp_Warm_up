/*
 * state.h
 *
 *  Created on: 14 Dec 2017
 *      Author: kunson01
 */

#ifndef STATE_H_
#define STATE_H_

// processor request enum
typedef enum {
	PrRd = 0,
	PrWr
} ProcessorRequest;

// bus request enum
typedef enum {
	BusRd = 0,
	BusRdx,
	BusUpgr,
	Flush,
	FlushOpt
} BusRequest;

#endif /* STATE_H_ */
