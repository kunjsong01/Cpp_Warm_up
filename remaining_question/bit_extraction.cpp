/*
 * Extract i-th bit from a byte:
 *
 * 1. A primitive method using mask
 * 2. A STL method using bitset
 *
 * Assumption:
 * - We are dealing with unsigned numbers. Bits exceeding the MSB are 0s.
 */


#include <iostream>
#include <stdint.h>
#include <bitset>

using namespace std;

void primitive_extraction(uint8_t &n, uint8_t &i);
void stl_extraction(uint8_t &n, uint8_t &i);

int main(void) {

	uint8_t number = 16;
	uint8_t position = 5;

	// test of primitive method
	cout << "Result returned by primitive method: " << endl;
	primitive_extraction(number, position);
	cout << endl;

	// test of STL method using C++ bitset data structure
	cout << "Result returned by STL method: " << endl;
	stl_extraction(number, position);
	cout << endl;

	return 0;
}

// primitive method
void primitive_extraction(uint8_t &n, uint8_t &i) {
	uint8_t mask = 1 << i;

	// test result
	uint8_t result = ((n & mask) != 0)? 1 : 0;

	cout << "Bit at position " << (int)i \
			<< " is " << (int)result << endl;
}

// A C++ STL method
void stl_extraction(uint8_t &n, uint8_t &i) {

	// convert it to bit
	bitset<8> b(n);
	cout << "This is the bitset: " << b << endl;

	// test result
	bool isOne = b.test((size_t) i);
	cout << "Bit at position " << (int)i \
			<< " is " << (int)isOne << endl;
}
