//============================================================================
// Name        : mesi_simulator.cpp
// Description : A MESI simulator implemented based on GoF state design pattern
//				for FSM.
//============================================================================

#include <iostream>
using namespace std;

#include "mesi_fsm.h"

int main() {

	cout << "Cache Coherence MESI simulator" << endl;

	// Create components
	LevelTwoCache l2_cache;
	Processor P1(Change_Initiator, &l2_cache);

	P1.readCacheLine(3);

	return 0;
}
