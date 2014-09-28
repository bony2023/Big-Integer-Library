Big Integer Library
===============

This Library contains three files:

1.  BigInt.h
==========
Contains all the functions and overloaded operators of type BigInt. 

2. BigInt.cpp
===========
Driver program to test Big Integer. (Here) Computes Fibonacci(5000).

3. FFTM.h
=========
This uses The Fast Fourier Transform algorithm for Multiplication of two BigInt. 

Complexity of Functions
====================

1. Overloaded Comparison Operators
==============================
All the operators tales O(1) time and return a boolean value. 

2. Overloaded + operator
====================
Takes linear time O(n) where n is length of longer number. 

3. Overloaded - operator 
====================
Takes O(n) time. 

4. Overloaded * operator 
====================
Uses FFT. Takes O(nlog(n)) time to multiply. 

5. Overloaded / operator
====================
Takes O(n) time. 

6. Overloaded % operator
====================
Takes O(n) time. 

7. Function gcd() 
==============
Takes O(log(n)) time. 

8. Function pow() 
==============
Takes O(eNlog(N)) where e=exponent and N=length of Number

9. Function factorial() 
=================
Takes O(N*M), N=current length of Number, M=Number;

10. Function abs() 
===============
Takes O(1) time. 

11. Function min() 
===============
Takes O(1) time. 

12. Function max() 
===============
Takes O(1) time. 

13. Function swap() 
================
Takes O(1) time. 
