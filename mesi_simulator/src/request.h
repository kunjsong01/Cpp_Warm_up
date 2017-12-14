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
	Pr_Rd = 0,
	Pr_Wr
} ProcessorRequest;

// bus request enum
typedef enum {
	Bus_Rd = 0,
	Bus_Rdx,
	Bus_Upgr,
	Flush,
	Flush_Opt
} BusRequest;

#endif /* REQUEST_H_ */
