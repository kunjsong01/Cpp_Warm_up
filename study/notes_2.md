 **C++ Concept Study Notes**
===========================================  

Keywords, Operators & Semantics
-------
1. C++ Standard Library has a rich collections of classes and functions. Include the library header file in the
preprocessor directive **#include**.
* **using namespace std** saves lots of typing effort. It allows compiler to understand the keywords. 
2. **endl** inserts a new-line character and flushes the stream
3. Unary scope resolution operator **::** is used to access a global variable. E.g. **::number**, here *number* is a global variable, not the local variable number. But use different names to avoid confusion.
4. Just like C, C++ double is 8 bytes. Float is 4 bytes. 

Functions
-------
1. Use **inline** function for small and frequently used functions to avoid function call overhead. Compiler will generate a copy of the function in place. 
* It may reduce execution time but increase the program size. 
2. Pass-By-Value: **int square (int x)**; Pass-By-Reference: **int square (int  &x)**
* Use PBR for large data size to avoid the function calling overhead.
3. Default argument: **int volume (int length = 1, int width);**
4. **Function Overloading** means multiple functions can co-exist using the same function name but they have different set(s) of variables. 
5.  **Function Templates** is a more compact way to perform **function overloading**. Templates are means of code generation. 