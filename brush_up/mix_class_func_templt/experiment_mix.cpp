// let's do a more interesting thing ...
// mix of class template and function template
// use different method to deal with different types of class attributes...

#include <iostream>
using namespace std;

// original class template
template <class T>
class ValueStore {
	private:
		T value;

	public:
		ValueStore(T _value) {
			// class constructor to populate array
			this->value = _value;
		}
		T increase() {
			// function to increase each value
			return ++this->value;
		}
		template <class X>
		X printDone ();
};

// out-of-line function definition printDone for numbers
// out of line function declaration
template <class T> // if removed, caused unambiguity when resolving ValueStore<T>
template <class X>
X ValueStore<T>::printDone() {
	cout << "Number Done!" << endl;
	return 100;
}

// class template specialisation
// i.e. customized for char type here
template <> // if removed, caused class redefinition!
class ValueStore <char> {
	private:
		char value;
	public:
		ValueStore(char _value) {
			this->value = _value;
		}
		char ToUpper () {
			if ((this->value >= 'a') && (this->value <= 'z')) {
				this->value += ('A' - 'a');
			}
			return this->value;
		}
		template <class X>
		X printDone();
};

// out-of-line function definition printDone for numbers
// class template does not work inherit anything from template
template <class X> // if removed, causes unambiguity
X ValueStore<char>::printDone() {
	cout << "char Done!" << endl;
	return 'Z';
}

int main() {
	ValueStore <int> myint (10);
	ValueStore <char> mychar ('x');
	cout << myint.increase() << endl;
	cout << mychar.ToUpper() << endl;

	int rtnInt = myint.printDone <int> ();
	char rtnChar = mychar.printDone <char> ();

	cout << "This is the value of returned int: " << rtnInt << endl;
	cout << "This is the value of return char: "  << rtnChar << endl;
	return 0;
}
