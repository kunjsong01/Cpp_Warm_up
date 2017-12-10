// class constructor and destructor experiment
// and a bit of interface (non abstract class) and out-of-line method definition
// pointer to object and keyword "new"

#include <iostream>
using namespace std;

void makeJumbo(); // let's see constructor to be called when object is outside scope

class Box {
	private:
		double length, width;
	public:
		Box(double _len, double _wid);
		~Box(); // destructor
		void setSize(double _len, double _wid);
		double getSize();
};

// out of line constructor definition
// only constructors can take initialisers
Box::Box(double _len, double _wid): length(_len), width(_wid) {
	// the traditional way
	//this->length = _len;
	//this->width = _wid;
}

// out of line destructor
Box::~Box() {
	// print out a message to show this object has been deleted before exiting program
	cout << "Deleting box with length " << this->length << " width: " << this->width << endl;
}

// a fancy way to set class members
void Box::setSize(double _len, double _wid) {
	this->length = _len;
	this->width = _wid;
}

double Box::getSize() {
	return this->length * this->width;
}

int main() {

	Box b(2.15, 2.0);

	makeJumbo();

	cout << "Initial box b size: " << b.getSize() << endl;
	cout << "Modifying box b size: l=3.35, w=3.0 " << endl;
	b.setSize(3.35, 3.0);
	cout << "New box b size: " << b.getSize() << endl;

	Box * c = new Box(0.5, 3);
	cout << "Box C created with size: " << c->getSize() << endl;
	delete c; // Type new, type delete

	return 0;
}

void makeJumbo() {
	Box m(100, 200);
	cout << "Jumbo box size: " << m.getSize() << endl;
}
