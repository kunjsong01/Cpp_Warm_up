// pass by ref, pass by value

#include <iostream>
using namespace std;

#include "compare.h"

int main() {
	// test with int
	int int1, int2;
	cout << "Enter two integers: ";
	cin >> int1 >> int2;
	cout << "The bigger one is: " << compare(int1, int2) << endl;

	// test with int
	double d1, d2;
	cout << "Enter two doubles: ";
	cin >> d1 >> d2;
	cout << "The bigger one is: " << compare(d1, d2);
}
