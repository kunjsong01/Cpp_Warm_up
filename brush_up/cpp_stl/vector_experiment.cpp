// vector experiment

#include <iostream>
#include <vector>
#include <algorithm> // lower_bound

using namespace std;

int main () {

	// create a vector
	vector<int> g1;

	for (int i=0; i<=5; ++i) {
		g1.push_back(i);
	}

	// create forward/backward iterator for that vector
	vector<int> :: iterator it;
	vector<int> :: reverse_iterator itr;

	// output using forward iterator
	cout << "Output of forward iterator: " << endl;
	for (it = g1.begin(); it != g1.end(); ++it) {
		cout << *it << '\t';
	}
	cout << "\n" << endl;

	// output using forward iterator
	cout << "Output of forward iterator: " << endl;
	for (itr = g1.rbegin(); itr != g1.rend(); ++itr) {
		cout << *itr << '\t';
	}
	cout << "\n" << endl;

	// experiment with more popular functions for vectors
	cout << "Size: " << g1.size() << endl;
	cout << "Capacity: " << g1.capacity() << endl;
	cout << "Max number of int a vector can hold: " << g1.max_size() << endl;

	// reference operator
	cout << "Returning 2nd element g1[2]: " << g1[2] << endl;
	cout << "Element returned by g1.at(3): " << g1.at(3) << endl;
	cout << "Element returned by front(): " << g1.front() << endl;
	cout << "Element returned by back(): " << g1.back() << endl;

	// test of assign 1
	// vector is basically re-initialized
	g1.assign(5, 10);
	// output using forward iterator
	cout << "Output of test assign 1: " << endl;
	for (it = g1.begin(); it != g1.end(); ++it) {
		cout << *it << '\t';
	}
	cout << "\n" << endl;

	// clear everythin
	g1.clear();
	cout << "Size after clear: " << g1.size() << endl;

	// convert array to vector
	int gfg[] = {0,1,0,0,1,1,0,1,0};
	vector<int> v(gfg, gfg+5); // convert part of array to vector
	cout << "Output of v: " << endl;
	//sort(v.begin(), v.end());
	for (it = v.begin(); it != v.end(); ++it) {
		cout << *it << '\t';
	}
	cout << "\n" << endl;

	// use lower_bound to get the first appearance of 1
	vector<int>::iterator lower;

	lower = lower_bound(v.begin(), v.end(), 1);
	cout << "Lower bound for 1 at position: " << (lower - v.begin()) << endl;
	return 0;
}
