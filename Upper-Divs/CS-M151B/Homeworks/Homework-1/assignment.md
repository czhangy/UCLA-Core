# Homework 1

## Problem 1.2

​	The seven great ideas in computer architecture are similar to ideas from other fields. Match the seven ideas from computer architecture, “Use Abstraction to Simplify Design”, “Make the Common Case Fast”, “Performance via Parallelism”, “Performance via Pipelining”, “Performance via Prediction” “Hierarchy of Memories”, and “Dependability via Redundancy” to the following ideas from other fields:

​	a. Assembly lines in automobile manufacturing

​	b. Suspension bridge cables

​	c. Aircraft and marine navigation systems that incorporate wind information

​	d. Express elevators in buildings

​	e. Library reserve desk

​	f. Increasing the gate area on a CMOS transistor to decrease its switching time

​	g. Building self-driving cars whose control systems partially rely on existing sensor systems already installed into the base vehicle, such as lane departure systems and smart cruise control systems



## Problem 1.7

​	Consider two different implementations of the same instruction set architecture. The instructions can be divided into four classes according to their CPI (class A, B, C, and D). P1 with a clock rate of 2.5 GHz and CPIs of 1, 2, 3, and 3, and P2 with a clock rate of 3 GHz and CPIs of 2, 2, 2, and 2.

​	Given a program with a dynamic instruction count of 1.0E6 instructions divided into classes as follows: 10% class A, 20% class B, 50% class C, and 20% class D, which is faster: P1 or P2?

​	a. What is the global CPI for each implementation?

​	b. Find the clock cycles required in both cases.



## Problem 1.8

​	Compilers can have a profound impact on the performance of an application. Assume that for a program, compiler A results in a dynamic instruction count of 1.0E9 and has an execution time of 1.1 s, while compiler B results in a dynamic instruction count of 1.2E9 and an execution time of 1.5 s.

​	a. Find the average CPI for each program given that the processor has a clock cycle time of 1 ns.

​	b. Assume the compiled programs run on two different processors. If the execution times on the two processors are the same, how much faster is the clock of the processor running compiler A’s code versus the clock of the processor running compiler B’s code?

​	c. A new compiler is developed that uses only 6.0E8 instructions and has an average CPI of 1.1. What is the speedup of using this new compiler versus using compiler A or B on the original processor?