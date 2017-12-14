// test composition update
#include <iostream>
using namespace std;


#include <vector>
class store {
	public:
		int value;
	public:
		store(int _value = 1): value(_value){
			cout << "Store constructor called: " << this->value << endl; // value assign will be called after this line
		}
		~store() {
			cout << "Store destructor called: " << this->value << endl;
		}

};

class multiStore {
	public:
		vector<store> v;
		store * sptr;

		store sd;
		multiStore(store _sd) {
			v.push_back(store(100)); // vector actually takes a copy and the original is destroyed
			v.push_back(store(200));
			sd = _sd; // pass-by-value, store destructor will be called for that copy
			//sptr = 0:
		}

		void modifyStore() {
			// replace a store and look at what happened
			v.pop_back(); // expecting store 200 to be destroyed

			v.push_back(store(400)); // store 400 destructor will be called here
		}

		void pointerTest () {
			store s(300); // will be destroyed when going out of the function
			sptr = &s;
			// testing destroy s inside function
			// delete sptr; gives error

			cout << "going out of function" << endl; // expecting s 300 to be destroyed
		}

		void updateComposition(store _s) {
			cout << "inside update" << endl;
			// store 400's copy will be destroyed
			sd = _s; // C++ does not call destructor of the original _s.
		}
};

int main() {

	// something else
	store s1(10);
	store s2(20);

	cout << "s1 and s2 value: " << s1.value << " "<< s2.value << endl;

	s2 = s1;
	cout << "s1 and s2 value: " << s1.value << " "<< s2.value << endl; // expect s2 calue to be changed, member-wise copy

	cout << endl;
	cout << endl;

	store s3(30);
	multiStore ms1(s3);
	cout << "Test modify ... " << endl;
	ms1.modifyStore();

	cout << "Test pointer ..." << endl;
	ms1.pointerTest();


	cout << endl;
	cout << "Update composition ..." << endl;
	cout << "Original store in multistore: " << ms1.sd.value << endl;
	store s4(40);
	ms1.updateComposition(s4); // here you are generating a copy that sits on the stack
	cout << "update sotre in multistore: " << ms1.sd.value << endl;


	cout << endl;

	return 0;
}
