/*
 * request.h
 *
 *  Created on: 14 Dec 2017
 *      Author: kunson01
 */

#ifndef REQUEST_H_
#define REQUEST_H_

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

#endif /* REQUEST_H_ */
