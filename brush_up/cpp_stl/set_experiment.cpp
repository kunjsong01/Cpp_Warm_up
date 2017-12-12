/*
 * Dequeue experiment
 */

#include<iostream>
#include<set>
#include<string>

using namespace std;

int main()
{
	set<string> setOfNumbers;

	// Lets insert four elements
	setOfNumbers.insert("first");
	setOfNumbers.insert("second");
	setOfNumbers.insert("third");
	setOfNumbers.insert("first");

	// Only 3 elements will be inserted
	cout<<"Set Size = "<<setOfNumbers.size()<<endl;

	// Iterate through all the elements in a set and display the value.
	for (set<string>::iterator it=setOfNumbers.begin(); it!=setOfNumbers.end(); ++it)
	    cout << ' ' << *it;
	cout<<"\n";
	return 0;
}

