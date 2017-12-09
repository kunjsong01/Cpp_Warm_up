/*
 * compare.h
 *
 *  Created on: 8 Dec 2017
 *      Author: kunson01
 */

// prevent multiple inclusions of this header file
#ifndef COMPARE_H_
#define COMPARE_H_

template <class T>
T compare (T a, T b) {
	return (a>b? a: b);
}

#endif /* COMPARE_H_ */
