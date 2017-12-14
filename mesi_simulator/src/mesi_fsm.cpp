/*
 * mesi_fsm.cpp
 *
 *  Created on: 13 Dec 2017
 *      Author: kunson01
 */

#include <iostream>

#include "mesi_fsm.h"

using namespace std;

// Protocol implementation of Modified
Modified::~Modified() { }

void Modified::operation(CacheLine *cl) {
	cout << "End line" << endl;
}

// Protocol implementation of Exclusive
Exclusive::~Exclusive() { }

void Exclusive::operation(CacheLine *cl) {

}

// Protocol implementation of Shared
Shared::~Shared() { }

void Shared::operation(CacheLine *cl) {

}

// Protocol implementation of Invalid
Invalid::~Invalid() { }

void Invalid::operation(CacheLine *cl) {

}

