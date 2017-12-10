// cconst / non-const object behaviour
// const / non-const method behaviour

#include <iostream>
#include <string>
using namespace std;

class Box {
	private:
		string boxName;
		int age;
	public:
		Box(string _name, int _age): boxName(_name), age(_age) {};
		string getName() {
			return boxName;
		}
		// this is a const method
		int getAge() const {
			return age;
		}
};

int main() {

	Box b("boxB", 2);
	cout << "First box name is: " << b.getName() << " of age " << b.getAge() << endl;

	const Box c("boxC", 3);
	// The following line gives error message "member function getNAme not viable...not marked const"
	// cout << "Second box name is: " << c.getName() << " of age " << c.getAge() << endl;
	cout << "Second box age is: " << c.getAge() << endl;

}
