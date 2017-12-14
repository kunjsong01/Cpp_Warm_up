/*
 * Compotision, multiple ownership
 * Experiment:
 * 	Class A and Class B both has object class C object as a member.
 * 	Shared ownership of an signle instance of C?
 */

#include<iostream>

#include "class_c.h"

using namespace std;

//class C;

class A {
	private:
		C myNumber;
	public:
		void printMyC() {
			cout << myNumber.store << endl;
		}

		void modifyMyC() {
			myNumber.store *= 5;
		}

		A(C _n): myNumber(_n) { // this is actually pass-by-value! a copy of C!

		}
};

class B {
	private:
		C myNumber;
	public:
		void printMyC() {
			cout << myNumber.store << endl;
		}

		void modifyMyC() {
			myNumber.store += 2;
		}

		B(C _n): myNumber(_n) {

		}
};

int main()
{
	C myC(10);

	A anA(myC);
	B anB(myC);

	cout << "Original C value is : " << endl;
	myC.getStore();

	cout << "A modify and print" << endl;
	anA.modifyMyC();
	cout << "A's C value is: " << endl;
	anA.printMyC();
	cout << "Shared C value is: " << endl;
	myC.getStore();

	cout << "B modify and print" << endl;
	anB.modifyMyC();
	cout << "B's C value is: " << endl;
	anB.printMyC();
	cout << "Shared C value is: " << endl;
	myC.getStore();

	return 0;
}

