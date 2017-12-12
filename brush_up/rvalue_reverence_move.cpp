/*
 * Dequeue experiment
 */

#include<iostream>
#include<set>
#include<string>

using namespace std;

string getString ();
void printReference (const string& str);
void printReference (string&& str);

int main()
{
	//const string&& name = getName(); // ok, taking const reference of rvalue is always ok
	string&& name = getString();

	// test rvalue reference
	string s = "Hello";

	printReference(  s ); // taking an lvalue reference
	printReference( getString() ); // taking a mutable rvalue reference

	return 0;
}

string getString (){

	return "Hello"; // this is just a rvalue
}

void printReference (const string& str) {
        cout << str;
}

void printReference (string&& str) {
        cout << str;
}
