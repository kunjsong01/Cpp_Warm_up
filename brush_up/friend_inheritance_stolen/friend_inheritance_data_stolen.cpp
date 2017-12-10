// steal data inside a Derived friend class from the original class 

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
		string printFounder(Polygon p) {
			cout << "This is founder returned from friend class object: " << p.founder << endl;
			return p.founder;
		}
};

// this works fine
class FalseReporter: public FounderReporter {
	public:
		string printFounder2(Polygon p) {
			// The following line gives error!
            // If overriding, this derived "false friend" cannot access the data of its base's friend
			//cout << "This is founder returned from DERIVED friend class object: " << p.founder << endl;

			// However the following line will redirect the call to the printFounder function within base class
			string gotIt = FounderReporter::printFounder(p);
			return gotIt;
		}
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

	FalseReporter frDerived;
	string data = frDerived.printFounder2(p);
	cout << "This is data \"stolen\" by redirection: " << data << endl;

	return 0;
}
