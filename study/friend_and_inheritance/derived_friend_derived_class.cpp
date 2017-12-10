// more interactions between friendship and inheritance

#include <iostream>
using namespace std;

class MyClass
{
	// Declare a friend class
	friend class SecondClass;

	public:
		MyClass() : Secret(0){}
		void printMember()
		{
			cout << Secret << endl;
		}
	//private:
	protected:
		int Secret;
};

class DerivedClass: public MyClass {

};

class SecondClass
{
	public:
		void change( MyClass& yourclass, int x )
		{
			yourclass.Secret = x;
		}
};

class ThirdClass: public SecondClass {


};

int main()
{
	MyClass my_class;
	SecondClass sec_class;
	my_class.printMember();
	sec_class.change( my_class, 5 );
	my_class.printMember();

	// test of third class accessibility
	ThirdClass thd_class;
	thd_class.change( my_class, 10);
	my_class.printMember();

	// derived friend class on derived class?
	DerivedClass dr_class;
	thd_class.change(dr_class, 30);
	dr_class.printMember();

	return 0;
}
