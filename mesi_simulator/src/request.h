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
	FlushOpt,
	NoFlushOpt,
	None
} BusRequest;

// request group
typedef enum {
	Local=0, // processor local request for a cache line
	Remote // bus request for a cache line
} Request;

// Cache hit/miss result
typedef enum {
	Miss=0,
	Hit
} HitMiss;

#endif /* REQUEST_H_ */
