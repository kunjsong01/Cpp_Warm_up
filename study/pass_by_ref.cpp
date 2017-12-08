// pass by ref, pass by value

#include <iostream>
using namespace std;

int squareByValue( int ); // prototype,value pass
void squareByReference( int & ); // prototype, reference pass

int main() {
	int x = 2;
	int z = 4;

	// examine the before/after values of a variable
	cout << "pass-by-value before: " << x << endl;
	cout << "pass-by-value result: " << squareByValue(x) << endl;
	cout << "pass-by-value after: " << x << endl;

	// examine the before/after values of a variable
	cout << "pass-by-ref before: " << z << endl;
	squareByReference(z);
	cout << "pass-by-ref after: " << z << endl;

}

int squareByValue( int number ){
	return number *= number;
}

void squareByReference( int &numRef ) {
	numRef *= numRef;
}

