// interactions between friendship and inheritance
// experiment with friend function, friend class and inheritance
// constructor is also inherited
// Derived parameterised constructor and its default constructor
// Multiple constructors in superclass for inheritance

#include <iostream>
#include <string>
using namespace std;

class  FounderReporter; // Class declaration. If removed, result in ambiguity in Polygon class

class Polygon {
	friend class FounderReporter;

	protected:
		string myTag;
		string founder;

	public:
		Polygon(string _Tag, string _founder="Euclides"): myTag(_Tag), founder(_founder) {
			cout << "Creating a polygon, using tag only" << endl;
		}

		friend void accessTag(Polygon &p);
};

// friend class that accesses the (protected) founder within polygon
class FounderReporter {
	public:
		void printFounder(Polygon p) {
			cout << "This is founder returned from friend class object: " << p.founder << endl;
		}
};

// Is friendship not inherited in this way?
class FalseReporter: public FounderReporter {
	public:
		void printFounder(Polygon p) {
			// The following line gives error!
			//cout << "This is founder returned from DERIVED friend class object: " << p.founder << endl;
		}
};

// friendship is not inherited??
class TrueReporter: public FounderReporter {

};

// friend function that accesses the (protected) tag within polygon
void accessTag(Polygon &p) {
	cout << "This is my PROTECTED tag: " << p.myTag << " returned from a friend function..." << endl;
}

// subclass of polygon
class Shape: public Polygon {
	protected:
		int numberOfSides;
	public:
		Shape(string _Tag, int n): Polygon(_Tag), numberOfSides(n) {
			// need to explicitly initialize the base class constructor which does not have a default constructor
			cout << "Creating a shape, using tag and int" << endl;
			cout << "shape has " << myTag << " tag." << endl;
			cout << "shape has " << numberOfSides << " sides." << endl;
		}
};

int main() {
	// friend function to a class
	Polygon p("Polygon_Tag");
	accessTag(p);

	Shape s("Shape_Tag", 5);
	accessTag(s); // s is also type of polygon, so no problem here...

	FounderReporter fr;
	fr.printFounder(p);
	fr.printFounder(s);

	// The following line gives error
	//FalseReporter frDerived;
	//frDerived.printFounder(p);

	// The following line works fine
	TrueReporter tr;
	tr.printFounder(p);
	tr.printFounder(s);

	return 0;
}
