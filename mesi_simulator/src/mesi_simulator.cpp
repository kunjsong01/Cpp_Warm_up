//============================================================================
// Name        : mesi_simulator.cpp
// Description : A MESI simulator implemented based on GoF state design pattern
//				for FSM.
//============================================================================

#include <iostream>
using namespace std;

#include "mesi_fsm.h"

using namespace std;

int main() {

	SimExecutor simulator;

	// Create components
	LevelTwoCache l2_cache;
	SharedBus bus;
	Processor P1(Idle, Initiator, &l2_cache);
	Processor P2(Idle, Follower, &l2_cache);

	/*
	 * processor local read
	 */
	cout << "@@ Processor Local Read: cache line already exists in processor's L1d cache" << endl;
	simulator.levelOneCacheInsertion(&P1, 3);
	P1.readCacheLine(3);
	cout << endl;

	/*
	 * processor remote read 1
	 */
	cout << "@@ Processor Local Read: cache line does not exist in the L1d cache of Processor 0, " \
			<< "and Processor 1 does not have the copy either" << endl;








	return 0;
}
