/*
 * Round Robin scheduling:
 *	Selecting the next non-zero element in an array of 0s and 1s which are
 *	randomly generated in each round.
 *	If array contains all 0s, return the last time selected.
 *
 *	This is the primitive version using pointers.
 */

#include <iostream>
#include <stdint.h>
#include <random>

using namespace std;

#define N 5
#define ROUND 15 

void printArray(uint8_t a[], uint8_t length);
void randomArray(uint8_t *a, uint8_t length);
uint8_t sched(uint8_t *a, uint8_t length, uint8_t r);

int main(void) {

	uint8_t i;
	// initialise array to be used for round robin scheduling
	uint8_t baseArray[N] = {};
	for (i = 0; i < N; ++i) {
		baseArray[i] = 1;
	}
	cout << "Initial array: " << endl;
	printArray(baseArray, N);

	i = 0;
	while (i <= ROUND) {
		cout << "=== Round: " << (int)i << "==="<< endl;

		// randomly update the array
		randomArray(baseArray, N);
		printArray(baseArray, N);

		// Round-Robin scheduling the first non-zero element
		uint8_t index = sched(baseArray, N, i);

		cout << "Selected index: " << (int)index << endl;
		cout << "Selected value: " << (int)baseArray[index] << endl;

		++i;
	}

	cout << "END" << endl;
	return 0;
}

// function to print the array
void printArray(uint8_t a[], uint8_t length) {
	for (int i = 0; i < length; ++i) {
		cout << (int)(a[i]) << " ";
	}
	cout << endl;
}

// function to randomly update values in that base array
void randomArray(uint8_t *a, uint8_t length) {

	// update the array randomly
	for (int i = 0; i < length; ++i) {
		// not pseudo random, but it works fine in this case ...
		uint8_t r = ((uint8_t)rand() % 100);
		if (r % 2 == 0) {
			*a = 1;
		}
		else {
			*a = 0;
		}
		a++;
	}
}

// Round-Robin scheduling
uint8_t sched(uint8_t *a, uint8_t length, uint8_t r) {

	static uint8_t *selected = a;

	// check all zero
	uint8_t sum = 0;
	for (uint8_t i = 0; i < length; ++i) {
		sum += *(a + i);
	}

	if (sum != 0) {
		// initial selection attempt
		if (r != 0) {
			selected++;
			if (r >= length) {
				selected = a + ((selected - a) % length);
			}
		}

		// check value and update selection.
		// Only select the index that can be dereferenced to value 1
		while(*(selected) != 1) {
			selected++;
			// reset pointer to the beginning if it exceeds bound
			if ((selected - a) > (length - 1)) selected = a;
		}
	}

	return (selected - a);
}

