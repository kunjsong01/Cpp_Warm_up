// pass by ref, pass by value

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
};

// class template specialisation
// i.e. customized for char type here
template <>
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
};

int main() {
	ValueStore <int> myint (10);
	ValueStore <char> mychar ('x');
	cout << myint.increase() << endl;
	cout << mychar.ToUpper() << endl;

	return 0;
}
