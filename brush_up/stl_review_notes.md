C++ STL Review

- [1. Container classes] (#heading)
    * [1.1 vector ($)](#sub-heading)
    * [1.2 deque ($)](#sub-heading)
    * [1.3 list (1%)](#sub-heading)
    * [1.4 Associative Container](#sub-heading)
    	+ [1.4.1 Set ($)](#sub-sub-heading)
    	+ [1.4.2 Map ($)](#sub-sub-heading)
    * [1.5 String](#sub-heading)
    * [1.6 Rope (1%)](#sub-heading)
    * [1.7 Container Adaptators](#sub-heading)
        + [1.7.1 stack (1%)](#sub-sub-heading)
    	+ [1.7.2 queue (1%)](#sub-sub-heading)
    	+ [1.7.3 priority_queue (1%)](#sub-sub-heading)
    * [1.8 bitset (1%)](#sub-heading)
- [2. Operations on Containers] (#heading)
    * [2.1 Iterators](#sub-heading)
    * [2.2 Algorithms](#sub-heading)
    * [2.3 auto_ptr / unique_pointer (smart pointer)](#sub-heading)

**C++ STL Review**
===========================================  

STL provides advanced data structures and operations on them. Data structures instances are like list, map, vector, string ... etc. Operations are like iterators, algorithms ...etc.

<!-- toc -->

# 1. Container classes
* Type of the container is specified by the template parameter, e.g. 
> vector&lt;int> V;
> vector&lt; vector&lt;int> > V2; // avoid confused by ">>" operator, multi-dimensional vectors  

## 1.1 vector ($)
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

* see experiment in /brush_up/cpp_stl/vector_experiment.cpp

## 1.2 deque ($)


## 1.3 list (1%)
* List or vector? Depending on the cost and benefits ... 
| Data structure      | Insertion | random access | 
| ------------------- |:-------------|:-------------| 
| List       | Low cost | Slow |
| Vector     | High cost | Fast | 

* For both list and vector, do __NOT__ use size() to check if list is empty, since size() returns unsigned result. Use empty() to do it!
* Popular functions:
> pop_front(), pop_back(), sort(), reverse()
* List support bidirectional iterator (++ / --), but does __NOT__ support random access iterator (binary + / - operator). 
** Searching list requires O(n) time, because __random access iterator is not supported !__.

## 1.4 Associative Container
### 1.4.1 Set
### 1.4.2 Map ($)
## 1.5 String
* string class, *string a = \"This is a string\";*
* It does NOT terminate with "\0". But if this was returned by c_str(), it will include the string terminator.

## 1.6 Rope
* Skip

## 1.7 Container Adaptors
### 1.7.1 stack
### 1.7.2 queue
### 1.7.3 priority_queue
* Skip

## 1.8 bitset
* It optimises the memory such that each bit takes 1 bit only. (Think of it like a compressed array of 0s and 1s.)
* size must be known at compile time, a constant. Size cannot be changed at runtime
* Bit set starts indexing __backward__!
* Works with operator [] (just like array)
* Constructor takes string/array... etc
* default construct initiates all bits 0
* popular functions: set, reset, size, count, test

# 2. Operations on Containers

## 2.1 Iterators
* Iterator is a general way to access data stored in a container class. 
* Iterator can provide range checking
* Algorithms use iterators.
* Some container classes has __begin()__ and __end()__ to return __forward order__ beginning and end iterators. (iterator returned by end() actually points to the theoretical terminating point)
* Access the element by dereferencing the iterator with a *
* To request an iterator object, append “__::iterator__”, “__::const_iterator__”, “__::reverse_iterator__” or “__::const_reverse_iterator__”  to container, e.g.:
> vector&lt;int>::iterator

** const iterator does not allow you change the content it's pointing to.
** 

* Some container classes has __rbegin()__ and __rend()__ to return __backward order__ beginning and end iterators.
* The forward iterator can only moves one way, from first to last.
* Types of iterators:
	** Random access iterator: you can ++ or --, or do iterator arithmetic.
	** Summary: 
| Iterator      | Ability       | 
| ------------------- |:-------------| 
| Input iterator      | Read forward  | 
| Output iterator     | Write forward |  
| Forward iterator 	  | R/W forward   |
| Bidirectional iterator 	  | R/W forward/bakcward   | 
| Random Access iterator 	  | R/W with random access (i.e. itr arithmetic)   | 
* No bound checking! could result in segmentation fault.
* __reverse()__ function

## 2.2 Algorithms
* find() and sort()
* some functions takes iterator parameters
* lower_bound() to find the first appearance of a thing in a sorted vector

## 2.3 auto_ptr / unique_pointer (smart pointer)
* Deprecated. Now using smart pointer (unique_pointer)?
