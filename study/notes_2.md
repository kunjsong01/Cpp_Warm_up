
**C++ Concept Study Notes**
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
7. 

Template
-------
A mean of code generation, a compact way to deal with same operation using different data types (i.e. overloading) ... 

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
4.  Attributes:
* Accessing private attribute outside the class results in a __compilation error__
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
7.
  