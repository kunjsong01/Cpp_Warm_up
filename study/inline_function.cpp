// inline function in C++
// basic i/o stream operator, concatenation

#include <iostream>
using namespace std;

inline double cube( const double side ) {
	return side * side * side;
}

int main() {
	double sideValue;

	for (int i = 1; i <= 3; ++i) {
		cout << "\n Enter side length of the cube: ";
		cin >> sideValue;

		// endl: insert a new-line character and flushes the stream
		cout << "Volume of the cube with side " << sideValue << " is " << cube( sideValue ) << endl;
	}
}
