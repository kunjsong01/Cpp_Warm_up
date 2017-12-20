//============================================================================
// Name        : mesi_simulator.cpp
// Description : A MESI simulator implemented based on GoF state design pattern
//				for FSM.
//============================================================================

#include <iostream>
using namespace std;

#include "component_fsm.h"
#include "mesi_fsm.h"

using namespace std;

void resetSystem (Processor &P0, Processor &P1, SimExecutor &simulator, SharedBus *bus);
void runSimulation(Processor &P0, Processor &P1, SimExecutor &simulator, SharedBus *bus);
void verify (Processor &P0, Processor &P1, SimExecutor &simulator, LevelTwoCache &l2_cache, int tag);

int main() {

	SimExecutor simulator;

	// Create components
	LevelTwoCache l2_cache;
	SharedBus bus;
	Processor P0(Idle, Initiator, &l2_cache, &bus);
	Processor P1(Idle, Follower, &l2_cache, &bus);

	/*
	 * P0 local read, cache hit
	 */
	cout << "{Processor Local Read}: P0 reads in a cache line that already exists in its L1d cache" << endl;
	simulator.levelOneCacheInsertion(&P0, 1); // test case prep
	P0.readCacheLine(1); // initiate test case
	runSimulation(P0, P1, simulator, &bus);
	verify(P0, P1, simulator, l2_cache, 1);
	printBoundary();

	resetSystem(P0, P1, simulator, &bus);

	/*
	 * P0 local read, cache miss, P1 does not have the copy
	 */
	cout << "{Processor Local Read}: P0 reads in a cache line that doesn't exist in its L1d cache, " \
			<< "and P1 does not have the copy either" << endl;
	P0.readCacheLine(2);
	runSimulation(P0, P1, simulator, &bus);
	verify(P0, P1, simulator, l2_cache, 2);
	printBoundary();

	resetSystem(P0, P1, simulator, &bus);

	/*
	 * P0 remote read, cache miss, P1 does not have the copy
	 */

	return 0;
}

void runSimulation(Processor &P0, Processor &P1, SimExecutor &simulator, SharedBus *bus) {

	int clockCycle = 1;
	int timeout = 10;

	while (P0.getState() != Succcess) {

		// stop the simulation if it takes too long
		if (clockCycle == timeout) {
			// TO-DO: throw exception saying "Maximum cycle number reached. Expecting Read/Write to finish within 100 cycles"
			cout << "ERROR !!! Maximum cycle number reached. Expecting Read/Write to finish within 100 cycles" << endl;
			break;
		}
		cout << "@@ Cycle " << clockCycle << " :" << endl;

		// print out bus state for debugging
		simulator.printBusBroadcast(bus);

		// alternate P1/P2 snoopy cache state
		if ( clockCycle % 2 != 0) {

			// Odd cycle P0 cache acts, P1 sniffs
			cout << "  - Acting Processor: " << P0.getRole() << endl;
			simulator.setCacheAct(&P0);
			simulator.printBusBroadcast(bus);
			cout << "  - Sniffing Processor: " << P1.getRole() << endl;
			simulator.setCacheSniff(&P1);
		}
		else {
			// Even cycle P0 cache sniffs, P1 acts
			cout << "  - Acting Processor: " << P1.getRole() << endl;
			simulator.setCacheAct(&P1);
			simulator.printBusBroadcast(bus);
			cout << "  - Sniffing Processor: " << P0.getRole() << endl;
			simulator.setCacheSniff(&P0);
		}

		// increase clock cycle
		clockCycle++;
		cout << endl;
	}

	cout << "Successful instruction retirement. " << endl;
	cout << "Total cycle consumption: " << (clockCycle-1) << endl;
	cout << endl;
}

void resetSystem (Processor &P0, Processor &P1, SimExecutor &simulator, SharedBus *bus) {
	// reset components
	simulator.resetSharedBus(bus);
	simulator.resetProcessor(&P0);
	simulator.resetProcessor(&P1);
}

void verify (Processor &P0, Processor &P1, SimExecutor &simulator, LevelTwoCache &l2_cache, int tag) {
	// verification of the copies of the target cache line
	cout << "Verifying the copies of cache line with tag (" << tag << ") ..." << endl;

	cout << "Tag " << tag << " in L1 cache of Processor " << P0.getRole() << " :" << endl;
	simulator.verifyCaches<LevelOneCache>(P0.getL1Cache(), tag);

	cout << "Tag " << tag << " in L1 cache of Processor " << P1.getRole() << " :" << endl;
	simulator.verifyCaches<LevelOneCache>(P1.getL1Cache(), tag);

	simulator.verifyCaches<LevelTwoCache>(&l2_cache, tag);

	// TO-DO: could have done another function to compare the states of each target cache line,
	// to confirm they are "coherent"
}
