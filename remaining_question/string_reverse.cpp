/*
 * Reverse a string
 *
 * 1. A primitive method using pointer
 * 2. A STL method using C++ string and iterator
 *
 */

#include <iostream>
#include <stdint.h>
#include <string>

using namespace std;

void primitive_reverse(uint8_t *s);
string stl_reverse(uint8_t *s);

int main(void) {

	// test primitive_reverse
	uint8_t a[100] = "Hello, I'm string";
	primitive_reverse(a);
	cout << "Result reversed by primitive_reverse: " << endl;
	cout << a << endl;

	cout << endl;

	// test stl_reverse (now reverse the reversed string)
	uint8_t b[100] = "Hello, I'm string";
	string c = stl_reverse(b);

	cout << "Result reversed by stl_reverse: " << endl;
	cout << c << endl;

	return 0;
}

// STL method using string and iterator
string stl_reverse(uint8_t *s) {
	// get string size
	uint8_t i = 0;
	uint8_t size = 0;

	while (*(s+i) != '\0') {
		++size;
		++i;
	}

	cout << "String size is " << (int)size << endl;

	// convert to string
	string str = "";
	for (i=0; i < size; ++i) {
		str += *(s+i);
	}
	cout << "Result of string conversion: " << str << endl;

	// use reverse iterator to reverse the string
	string::reverse_iterator rit = str.rbegin();

	string r_string = "";
	for (; rit != str.rend(); rit++) {
		r_string += *rit;
	}

	return r_string;
}

// primitive method using pointer
void primitive_reverse(uint8_t *s) {

	// get string size
	uint8_t i = 0;
	uint8_t size = 0;

	while (*(s+i) != '\0') {
		++size;
		++i;
	}

	cout << "String size is " << (int)size << endl;

	// assign pointer to the beginning and end of the string, skip '\0'
	uint8_t *s_begin = s;
	uint8_t *s_end = s;

	// set end pointer
	for (i=0; i < (size - 1); ++i) {
		s_end++;
	}

	// tmp holder when swapping
	uint8_t tmp;
	for (i = 0; i < (size / 2); ++i) {
		tmp = *s_begin;

		*s_begin = *s_end;
		*s_end = tmp;

		// move pointers towards the middle
		s_begin++;
		s_end--;
	}
}
