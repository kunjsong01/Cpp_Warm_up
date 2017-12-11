C++ STL Review
1. Container classes
1.1 vector
1.2 deque
1.3 list
1.4 Associative Container
1.4.1 Set
1.4.2 Map
1.5 String
1.6 Rope
1.7 Container Adaptators
1.7.1 stack
1.7.2 queue
1.7.2 priority_queue
1.8 bitset
2. Operations on Containers
2.1 Iterators
2.2 Algorithms
2.3 auto_ptr

**C++ STL Review**
===========================================  

STL provides advanced data structures and operations on them. Data structures instances are like list, map, vector, string ... etc. Operations are like iterators, algorithms ...etc.

# 1. Container classes
* Type of the container is specified by the template parameter, e.g. 
> vector&lt;int> V;
> vector&lt; vector&lt;int> > V2; // avoid confused by ">>" operator, multi-dimensional vectors  

* Some container classes has __begin()__ and __end()__ to return __forward order__ beginning and end iterators.
* Some container classes has __rbegin()__ and __rend()__ to return __backward order__ beginning and end iterators.

## 1.1 vector
* Vectors are dynamic arrays that can be resized. The memory is handled automatically by container.
* Vector elements can be accessed by __reference operator []__ just like arrays.
* The memory is also contiguous so that they can be accessed and traversed by iterators. 
* Syntax: 
> vector&lt;int> v(10); // vector of 10 ints
> vector&lt;int> v[10]; // vector of 10 empty vectors

* Popular functions: 
> v.size(); 
> v.empty();
> v.push_back(); // add element to the end of the vector
> v.pop_back();
> v.clear(); // erases all elements, NOT make them 0
> v.erase()
> v.resize() // memory will be allocated for additional elements

* Modifiers __assign()__ can be used to re-initialise the whole vector. Additionally, with iterators, it can be used to change part of the vector and resize.

• When vector is passed to function, a copy is created. Avoid doing this and use __pass-by-reference__
* Syntax:
> vector&lt;type> V(size, value);

## 1.2 deque
* Skip
## 1.3 list
## 1.4 Associative Container
### 1.4.1 Set
### 1.4.2 Map
## 1.5 String
## 1.6 Rope
* Skip
## 1.7 Container Adaptors
### 1.7.1 stack
### 1.7.2 queue
### 1.7.2 priority_queue
* Skip

## 1.8 bitset


# 2. Operations on Containers

## 2.1 Iterators
* Iterator is a general way to access data stored in a container. 
* Iterator can provide range checking
* __reverse()__ function
* To create an iterator object. append “__::iterator__”, “__::const_iterator__”, “__::reverse_iterator__” or “__::const_reverse_iterator__”  to container, e.g.:
> vector&lt;int>::iterator

* 

## 2.2 Algorithms
* find() and sort()
* some functions takes iterator parameters
* lower_bound() to find the first appearance of a thing

## 2.3 auto_ptr
* Class to manage memory pointers and avoid memory leaks


** __#include &lt;exception>__