# Cpp_Warm_up

C++ review: 

* Review on C++ concepts, template, memory management, OOP behaviour (friend, inheritance, composition, constructor/destructor calling order .etc).
** See basic_review_notes.md

* Review on STL, including container, iterator and vector. Using iterator to loop through container.  
** See stl_review_notes.md

There are some experiment programs in *brush_up* folder which could help one to understand some common behaviours: 
* Interactions between Friend/Derived Friend and Base/Derived Base. 
* Mixed usage of class and function tempalte.

The *remaining_question* folder has two experiment programs:

1. A program to examine the behaviour of the following program:

> There are two classes, A and B. Class A has a member which is a pointer pointing to Object B. This pointer is initialised in A's constructor. If A is destructed, what happened to B? 

2. A program implementing the Round-Robin selection of the element in an array, where the array is dynamically changing in each selection round. Values of the array can be 0 or 1. Only the next 1 is selected.
