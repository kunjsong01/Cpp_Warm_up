//============================================================================
// Name        : mesi_simulator.cpp
// Description : A MESI simulator implemented based on GoF state design pattern
//				for FSM.
//============================================================================

#include <iostream>
using namespace std;

#include "mesi_fsm.h"

int main() {
	cout << "Hello world" << endl; // prints

	Modified m;
	CacheLine cl(&m);
	cl.stateOperation();

	return 0;
}
