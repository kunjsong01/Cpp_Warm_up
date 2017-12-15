/*
 * logger.cpp
 *
 *  Created on: 14 Dec 2017
 *      Author: kunson01
 */

#include <string>
#include "logger.h"
#include <iostream>

using namespace std;

void printCacheOperation (string msg) {
	cout << "\t [Cache operation]: " << msg << endl;
}

void printFSMOperation (string msg) {
	cout << "\t\t [FSM operation]: " << msg << endl;
}
