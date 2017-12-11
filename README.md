# Cpp_Warm_up

Mini roadmap for C++ review: 

1. C++ review: 

    * Review on C++ concepts, template, memory management, OOP behaviour (friend, inheritance, composition, constructor/destructor calling order .etc).
        ** See basic_review_notes.md

    * Review on STL, including container, pairs, iterators, vectors, set and map. Using iterator to loop through container.  
        ** See stl_review_notes.md

    There are some experiment programs in *brush_up* folder which could help one to understand some common behaviours, e.g.: 
        * Interactions between Friend/Derived Friend and Base/Derived Base. 
        * Mixed usage of class and function tempalte.
        * ...etc

2. The *remaining_question* folder has two experiment programs

    * 2a) A program to examine the behaviour of the following program

> There are two classes, A and B. Class A has a member which is a pointer pointing to Object B. This pointer is initialised in A's constructor. If A is destructed, what happened to B? 


    * 2b) A program implementing Round-Robin scheduling  

> The Round-Robin selection of the element in an array, where the array is dynamically changing in each selection round. Values of the array can be 0 or 1. Only the next 1 is selected.

3. Study basic usage of gdb watchpoint.  


