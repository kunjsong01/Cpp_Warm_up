/*
 * Dequeue experiment
 */

#include <iostream>
#include <stdint.h>
#include <deque>

using namespace std;

void printDeque(deque<uint8_t> & dq);
void changeDeque(deque<uint8_t> & dq);

int main(void) {

	// deque<double> deq1(5);
	// deque<double> deq2(5, 2.0);

	// calling the deque array constructor
	uint8_t array[8] = {9, 67, 10, 3, 99, 78, 6, 677};
	deque<uint8_t> deq3(array, array + 8);

	printDeque(deq3);
	changeDeque(deq3);

	cout << "After changing.." << endl;
	printDeque(deq3);
	return 0;
}

void printDeque(deque<uint8_t> & dq) {
	deque<uint8_t>::const_iterator it = dq.begin();
	//deque<uint8_t>::iterator it = dq.begin();
	for (; it != dq.end(); ++it ) {
		// test of const vector, the following gives an error
		// *it = 1;
		cout << (int)(*it) << " ";
	}
	cout << endl;
}

void changeDeque(deque<uint8_t> & dq) {
	deque<uint8_t>::reverse_iterator rit = dq.rbegin();

	for (; rit != dq.rend(); ++rit) {
		*rit = 'a';
	}
}

