[TOC]

**C++ Standard Library Notes**
===========================================  

Keywords, Operators & Syntax
-------
1. C++ Standard Library has a rich collections of classes and functions. Include the library header file in the
preprocessor directive **#include**.
* **using namespace std** saves lots of typing effort. It allows compiler to understand the keywords. 
2. **endl** inserts a new-line character and flushes the stream
3. Unary scope resolution operator **::** is used to access a global variable. E.g. **::number**, here *number* is a global variable, not the local variable number. But use different names to avoid confusion.
4. Just like C, C++ double is 8 bytes. Float is 4 bytes. 
5. ++a (**pre increment**, return new value) vs. a++ (**post increment**, return original value)   a=1, In b = a++, b takes 1.  In b = ++a, b takes 2.
6. C++ has standard library class template vector, **#include &lt;vector>**, it is a "super" array. E.g.
* **vector<int> myIntVec( 10)** // initialises an array of 10 integers
* **myIntVec.size()** // returns 10
7. >> extraction operator; << is insertion operator. They operate on iostreams, such as cin and cout.
8. = assignment operator can be used to assign one object to another, performed by member-wise assignment.
9. 

Template
-------
A mean of code generation, a compact way to deal with same operation using different data types (i.e. overloading) ... compile-time polymorphism

1. Function Template: See #5 in Function section. 
2. Class Template
* When using class template specialisation, syntax is like **class MyClass &lt;char>**
* Out-of-line function definition for class template can be used.
** Out-of-line function definition without template<...> prefix results in __compilation error__
3. Template Specialisation: 
* Define different implementation when different types of parameters passed to function constructor
4. Mix of class and function templates: bespoke implementations for both class attributes and methods - **BAD** practice, could have caused confusion, but interesting to investigate the behaviour ... (look into the experiment in **mix_class_func_templt**)

Functions
-------
1. Use **inline** function for small and frequently used functions to avoid function call overhead. Compiler will generate a copy of the function in place. 
* It may reduce execution time but increase the program size. 
2. Pass-By-Value: **int square (int x)**; Pass-By-Reference: **int square (int  &x)**
* Use PBR for large data size to avoid the function calling overhead.
3. Default argument: **int volume (int length = 1, int width);**
4. **Function Overloading** means multiple functions can co-exist using the same function name but they have different set(s) of variables. 
5.  **Function Template** is a more compact way to perform **function overloading**. Templates are means of code generation. 

OOP in C++
-------
1. Difference between encapsulation and  data abstraction:
* Encapsulation: binding data and related functions together
* Data Abstraction: Hiding the implementation details from usage. E.g. every time you call a method in an object like **Object.Method1()**
2. Abstract Class vs. Concrete Class:
* Abstract Class defines interfaces in C++, it cannot be instantiated. Interfaces describes the capability of a class but does not describe the implementation behind it.
* Concrete Class are ones that can be instantiated. 
3. More on Abstract class:
* It provides a base class from which some other classes can inherit. 
* At least one of the method is declared as **virtual method**, like **virtual double getArea() = 0;** 
* Subclasses need to implement all virtual methods. Otherwise __compilation error__
4.  Attributes and accessors:
* Accessing private attribute outside the class results in a __compilation error__
* private, public, protected 
5. Accessing attributes in an object:
* By **name**, use **dot (.)** operator
* By **reference**, use **dot (.)** operator
* By **pointer**, use **arrow (->)** operator
⋅⋅* Keyword "this" within a class appears to be a pointer, usage is **this->attribute**
6. A class instance created without "new" stays on the stack. Too many of these could result in stack overflow.
7. Keyword "new":
* Usage is like **Box *b = new Box(1, 1.5);**
* It allocates memory on the heap. It requires to be deleted explicitly, e.g. **delete b;**
* The Rule: **Type new, type delete**. Otherwise, (probably) memory leak.
* Look into experiment /study/stack_heap_destructor/heap_destructor_experiment.cpp
8. __const__ members and objects:
* Non-const method cannot be called by const object. 
* Const method can be called by any type of object. 
* Look into experiment /study/const_method_behaviour
9. Usage of "this" pointer:
* Access attributes or method within a class
* Return current object from member function, e.g. **return *this**
* Guard self-reference, e.g. if ( &otherObject != this)
10. **Composition** means a class has an object of another class as its member
* has-a relation, e.g. a car has-a engine, and this engine only belongs to that specific car
* Look into experiment /study/composition
11. **Function Overriding**: In Base Class, there is a function A. In the Derived Class, function A can be implemented 0

More on OOP
-------
1. **Friendship** in C++, **Friend** function and **Friend** class
> Friendship in C++ is __NOT__ transitive, i.e. the friend of a friend does not work unless explicitly specified.
> Friendship in C++ is __NOT__ mutual, i.e. the A is declared as friend within B, but B still cannot access A's private or protected members.

2. **Friend** class
> If A is declared as friend within B, A can access B's __private__ or __protected__ members.

3. **Friend** function implements the operations that are conducted between two different classes 
> Friend function of a class can access the __private__ and __protected__ members within that class, but it is __NOT__ a member of that class!
> Friend function takes a reference to object as the input

4. Inheritance and modes of inheritance: 
* **Private member(s)** will **never** be inherited from the superclass! 
* Accessor behaviours are summarised below: 
	|  -------    |  Subclass in _[public]_ mode | Subclass in _[private]_ mode  | Subclass in _[protected]_ mode |
	| ------------ |:-------------:|:-------------:|:-------------:|
	| private      | NOT inherited 	  | NOT inherited  | NOT inherited  |
	| public       | public      	  | private 	   | protected 		|
	| protected    | protected        | Private 	   | protected 		|

* single-level inheritance
* Multi-level inheritance (use the above table to "derive" the accessor relationships)
** Makes it interesting when inherit from a private subclass... 
* Multiple inheritance, e.g. **class cat: public class animal, public class mammal { ... }**
* Hierarchical Inheritance
* Hybrid Inheritance (any combinations of the above mentioned types...)

5. Mimic "super" in C++: https://stackoverflow.com/questions/180601/using-super-in-c
6. __Friends__ are inherited if there is no function overriding. 
* See experiment in /study/friend_and_inheritance/