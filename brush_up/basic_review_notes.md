C++ review

- [1. Storage Duration (Automatic, Static and Dynamic Memory)] (#heading)
- [2. Struct vs. Class] (#heading-1)
- [3. Type Casting] (#heading-2)
- [4. RTTI] (#heading-3)
- [5. Template] (#heading-4)
- [6. Binding] (#heading-5)
- [7. Virtual Destructor] (#heading-6)
- [8. Orders of constructor and destructor calling in Composition/ Inheritance] (#heading-7)
- [9. Exception Handling] (#heading-8)
- [10. Functions] (#heading-9)
- [11. OOP in C++] (#heading-10)
- [12. Friends and Inheritance] (#heading-11)
- [13. Operator Overloading] (#heading-12)
- [14. Move Semantics, RValue reference] (#heading-13)
- [15. Miscellaneous] (#heading-14)

**C++ Review**
===========================================  

<!-- toc -->

# 1. Storage Duration (Automatic, Static and Dynamic Memory)
C++03

* Automatic storage means the variable(s) will be destroyed at the end of enclosing braces.
* Static storage means the variable(s) will be destroyed when program finishes.
* Dynamic storage means the thing to which a pointer of automatic storage pointing will not be destroyed at the end of enclosing braces. Use **delete** to delete manually otherwise you leak the memory.
* **Good programming practice** : In order to avoid making **dangling pointer**, assign the pointer to NULL 
**p = NULL** after deleting the dynamic memory allocation on heap. 
* Is leaked memory freed when a process terminates? Yes, OS will free it. However, in some RTOS, it may not be freed. 

# 2. Struct vs. Class
* Just like class, struct can be inherited in C++. The only different is default accessibility (member-wise and inheritance wise). Struct by default is public. Class by default is private. 
* Structs also have constructor and destructor.

# 3. Type Casting
* Traditional type casting: **(type)value**, **type(value)**
* Using the traditional type casting with classes and pointers to classes may result in runtime error or unexpected result (though syntax is correct), since pointers can be converted into any other type, regardless of the type it's pointing to. 
* To control these classes and ptr casting, C++ has four types of type casting:
** dynamic_cast, static_cast, const_cast, reinterpret_cast.
> syntax: cast_mode&lt;new_type> (expression)

* **dynamic_cast** yields a valid complete object of the type requested. 
** Derived-to-Base works fine. Base-to-Derived does not work.
** Class pointer-type dynamic_cast: returns null to indicate unsuccessful
** Class reference-type dynamic_cast: throws bad_cast exception
* **static_cast** does not yield a valid complete object of the requested type. 
** Class pointer type conversion to __related classes__
** Derived-to-Base works fine. Base-to-Derived also works fine.
** Programmer should do safety check. Otherwise runtime error may occur.
* **reinterpret_cast**
** Class pointer type conversion to __non related classes__
** Does not guarantee anything. Does not make much sense. 
* **const_cast**
** to be used to convert constness of an object, e.g. passed non-const object into function that expects const object
* Summary table:

	|  -------    |  Related Class? | Ensure pointer type?  | Ensure complete content?  |
	| ------------ |:-------------:|:-------------:|:-------------:|
	| dynamic_cast        | Yes 	  | Yes  | Yes  |
	| static_cast             | Yes   | Yes  | No	|
	| reinterpret_cast    | No    | No   | No	|
	| const_cast             | N/A   For constness conversion only | N/A   For constness conversion only | N/A   For constness conversion only | N/A   For constness conversion only |

# 4. RTTI
* Run-Time Type Info for type conversion in the inheritance hierachy
* often used with typeid() operator. 
* Only available for classes that have at least one virtual function. Otherwise gives runtime error (though compilation works fine)
* Used by dynamic_cast
** dynamic_cast is converting a pointer pointing to an object to a pointer to an derived object in the inheritance hierachy.

# 5. Template
Fundamentally it is Compile time code generation...
The calling function actually uses different versions generated by the template.
A way to deal with same operation using different data types (i.e. overloading), grouping a number of related overloaded functions.

1. Syntax is like: **template &lt;typename T>**, **template &lt;class T>**,  **template &lt;typename T, typename T>**. Keywords class and typename are **equivalent**. 
2. Non-template function **template &lt;typename T, int N>**. When calling, you need ** Foo<int 3>(5)**
3. Function template & function template specialisation
4. Class template & class template specialisation
* When using class template specialisation, syntax is like **class MyClass &lt;char>**
* Out-of-line function definition for class template can be used.
** Out-of-line function definition without template<...> prefix results in __compilation error__
5. Template Specialisation: 
* Define different implementation when a specific type of parameters passed to function constructor
6. Mix of class and function templates: bespoke implementations for both class attributes and methods - **BAD** practice, could have caused confusion, but interesting to investigate the behaviour ... (see experiment in /brush_up/mix_class_func_templt)

# 6. Binding
Connecting function call to function body.

1. When using **Base class pointer** to reference **Derived class object**, Early Binding occurs. Function call will be connected to that function within Base class instead of the overrided function in the Derived class. 
2. Using keyword **virtual** in that function will resolve the problem. This is Late Binding (type of the object can be determined at run time). Note that this is not the pure virtual function.

# 7. Virtual Destructor
1. When using **Base class pointer** to reference **Derived class object**, destructor within the derived class will NOT be called when performing a delete operation. 
2. Again, this can be fixed by making base class destructor **virtual**. 
3. **Good programming practice** : To ensure against any surprise later, any time you have a virtual function in the base class, make destructor virtual. 

# 8. Orders of constructor and destructor calling in Composition/ Inheritance
* In inheritance, the order is Base Constr ---> Derived Constr ---> Derived Destr ---> Base Destr
** Yes, base constr/destr are not inherited but always get called. 
* In composition, assume Class has two members made from Member1 class and Member2 class. 
** The order is Member1 Constr ---> Member2 Constr ---> Member2 Destr ---> Member1 Constr (Think of it like a stack, FILO)

# 9. Exception Handling
* try, catch, throw
** throw allows functions to specify its exception.
** Handle any type of exception:   __catch (...) { // code to handle it here}__
* C++ provides  __exception class__ Standard Library to make objects to be throw as exception.
** include exception Standard Library and __inherit from exception__ to define new type of exceptions
** __#include &lt;exception>__
** Override the __virtual what() function__ to report what caused the exception
* Program terminates abnormally if exception is thrown but not caught anywhere.
* Exception specifier: deprecated. Restrict the type of exception a function can throw.
> virtual const char* what() const throw() { return "An Exception!";}

* Alternatively __runtime\_error class__: include stdexcept and inherit from runtime\_error to define new type of runtime\_error
**__#include &lt;stdexcept>__ has runtime\_error class which is derived from Standard Library class _exception_.


# 10. Functions
1. Use **inline** function for small and frequently used functions to avoid function call overhead. Compiler will generate a copy of the function in place. 
* It may reduce execution time but increase the program size. 
2. Pass-By-Value: **int square (int x)**; Pass-By-Reference: **int square (int  &x)**
* Use PBR for large data size to avoid the function calling overhead.
3. Default argument: **int volume (int length = 1, int width);**
4. **Function Overloading** means multiple functions can co-exist using the same function name but they have different set(s) of variables. 
5.  **Function Template** is a more compact way to perform **function overloading**. Templates are means of code generation. 

# 11. OOP in C++
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
* Usage is like **Box *b = new Box(1, 1.5);**, **int *p = new int;**. Pointers p and b are on the stack.
* It allocates memory on the heap. It requires to be deleted explicitly, e.g. **delete b;**
* The Rule: **Type new, type delete**. Otherwise, (probably) memory leak.
* Look into experiment /brush_up/stack_heap_destructor/heap_destructor_experiment.cpp
8. __const__ members and objects:
* Non-const method cannot be called by const object. 
* Const method can be called by any type of object. 
* Look into experiment /brush_up/const_method_behaviour
9. Usage of "__this__" pointer:
* Access attributes or method within a class
* Return current object from member function, e.g. **return *this**
* Guard self-reference, e.g. if ( &otherObject != this)
10. **Composition** means a class has an object of another class as its member
* has-a relation, e.g. a car has-a engine, and this engine only belongs to that specific car
* Look into experiment /brush_up/composition
11. **Function Overriding**: In Base Class, there is a function A. In the Derived Class, function A can be implemented 0
12. __Constructor__ can also be overloaded in similar ways as functions.

# 12. Friends and Inheritance
1. **Friendship** in C++, **Friend** function and **Friend** class
> Friendship in C++ is __NOT__ transitive, i.e. the friend of a friend does not work unless explicitly specified.
> Friendship in C++ is __NOT__ mutual, i.e. the A is declared as friend within B, but B still cannot access A's private or protected members.

2. **Friend** class
> If A is declared as friend within B, A can access B's __private__ or __protected__ members.

3. **Friend** functions implement the operations that are conducted between two different classes 
> Friend function of a class can access the __private__ and __protected__ members within that class, but it is __NOT__ a member of that class!
> Friend function takes a reference to object as input

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
6. __Friends__ are NOT inherited if there is no function overriding in the subclass. i.e. If A is friend of B, C is inherited from A. You cannot get B's data within class C. 
* See experiment in /brush_up/friend_and_inheritance/
7. Things that are __NOT INHERITED__ from base class, including:
* constructor and destructor
** The default constructor and destructor (i.e. not parameterised ones) are always called
* Friends
* operator overloading members
8. Derived class of a friend class can "steal" data from the befriended class. Certain conditions applies.
* see experiment in /brush_up/friend_inheritance_stolen/ 

# 13. Operator Overloading
* E.g "Complex operator + (Complex const &obj) ()". This is an operator function, "operator" keyword followed by operator itself.
* conversion operator can also be overloaded, e.g. **operator float() {}**
* Unary and binary operator are both 'overloadable'. But not all operators can be overloaded

# 14. Move Semantics, RValue reference
C++11

* Move: 
	1. to avoid memory allocation for temporary object when returning an object from a function
	2. used to move unique_ptr into container.
	3. Move relies on rvalue reference. 
* A bit more on terminology: 
** lvalue takes permanent memory. You can assign value to it. lvalue can take reference
** rvalue does not take reference. rvalues refer to temporary objects. (But in C++11, there is a "rvalue reference")
** string&& str, this is a mutable rvalue reference

# 15. Miscellaneous
1. Unary scope resolution operator **::** usage: 
* Access global variable that was defined in file scope
* Out-of-line member function definition
* Access base class member function (see experiment in /brush-up/friend_inheritance_steal/)
2. ++a (**pre increment**, return new value) vs. a++ (**post increment**, return original value)   a=1, In b = a++, b takes 1.  In b = ++a, b takes 2.
3. C++ has standard library class template vector, **#include &lt;vector>**, it is a "super" array. E.g.
* **vector<int> myIntVec( 10)** // initialises an array of 10 integers
* **myIntVec.size()** // returns 10
4. >> extraction operator; << is insertion operator. They operate on iostreams, such as cin and cout.
5. = assignment operator can be used to assign one object to another, performed by member-wise assignment.
6. Official class definition: Program can use class to abstract real world object. A group of related data and methods can be encapsulated in a class.
7. **Abstract class** is a class that has at least one pure virtual function and cannot be instantiated, e.g. **virtual void printID() = 0**. This type of class is intentionally designed to be used as base class. A concrete class is a class that can be used to make objects. 
8. **Polymorphism** example in C++: a function can have many forms, i.e. overriding in derived class. Furthermore, in order to avoid Early Binding, you need to make that function in the base class "**virtual**". 
9. Keyword **explicit**:
> If a class has a constructor that can be called using a single argument (Note that the constructor doesn't have to be a single-argument constructor), this constructor becomes a **conversion** constructor. The object being constructed will be converted to the type of that argument. This is implicit type conversion. 

* Avoid it using explicit Specifier. 
* Adding explicit specified to a constructor will also allow user to typecast other values to the type of that class.
10. Keyword **extern**: 
* Variable has "external linkage". It means define something in the file scope
* Usually used in header file to declare global variable. All files that include this header file will be able to use that variable. 
* **static int a; extern int a;** works fine. However, **extern int a; static int a;** does not work!
11. **const** at the end of function declaration, e.g. Class A has "void Foo() const {}", one cannot change class members inside Foo, unless prefix the aMember declaration with **mutable** keyword, "mutable int aMember;". I.e. "this" becomes const inside Foo().
12. Check types: **#inclde &lt;typeinfo>**, function **if (typeid(a) == typeid(b)) {...}**
* __typeid(a).name()__ returns details
13. keyword auto: automatic storage duration, type inference "auto d = 5.0;" then d is a double.
14. Predicate (used by some STL algorithms): 
	* unary predicate: function that return a bool and takes only __one__ input
	* binary predicate: function that return a bool and takes only __two__ inputs
15. Functor (used by some STL algorithms): 
	* https://www.youtube.com/watch?v=fD0Sykh3vPs
	* a struct that overloads the function call operator "__()__" 


