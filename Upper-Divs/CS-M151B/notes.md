# COM SCI M151B - Winter '22 - Reinman

[TOC]

## Lecture 1: Introduction and Performance

- Motivation

  - Microprocessors are built for performance
    - Also considers battery life, size, power dissipated, etc.
    - Transistor count has increased exponentially, how do we use them to maximize efficiency of parts?
    - Single-threaded performance scaled consistently with the number of transistors for a time, but now, the gap between them is increasing
      - Mainly a power issue
      - Stabilized due to shift towards multi-core computing as the primary means of delivering better performance
    - Frequency scaled with performance and transistor count as well, before falling off
      - Synchronous processors use a clock to manage computations
      - Mainly a power issue => overheating of the chip due to the chip not being able to dissipate the power output (thermal bottleneck)
    - The number of logical cores begins increasing to offset the thermal bottleneck
      - Breaking up of processing elements to cooperate in simpler chunks in order to resolve power dissipation limits
    - Improvements being made through multithreading
      - These operations scale well because of the leveraging of the multiple cores
      - Dependent on the application => some are inherently serial, some have large potential for parallelism

- Introduction

  - Layers of Computation
    - We first have a software layer
      - Written in whatever programming language
      - High-level algorithms
      - Compiler, OS, etc.
    - The ISA receives instructions from the software layer to perform
      - Instructions, registers, memory model, condition codes, etc.
      - Basically the interface for how the software communicates with the physical machine
    - The instructions are passed to the hardware
      - Handled by the microarchitecture
        - Influenced by the software side: efficiency of language/compiler/OS, parallelism, etc.
          - Performance and design
        - Influenced by physical design constraints: resistance of wires, etc.
      - Implemented physically
  - Course Breakdown
    - Performance
      - Breaking down of pieces of the microarchitecture
    - ISA
      - What types of instructions do we need, and what trade-offs do they entail?
    - ALU
    - Datapath + Control
    - Pipelining
    - Memory
      - Caching, VM, etc.
    - Multi-Core

- Performance

  - `Execution Time = Instruction Count × Cycles Per Instruction × Cycle Time`

    - There is an application `A` running on processor `X`
      - Particular application running on a particular processor
      - The application is comprised of instructions
        - There is a static count (number of instructions)
        - There is also a dynamic count (accounts for control flow, actual number of executions)
          - Instruction count refers to the dynamic count
        - Dependent on the application and the particular ISA
      - We must translate the processor's notion of time (cycles) into our notion of time (seconds)
        - Dependent on the processor
          - Designed with a particular ISA in mind
        - Clock cycles are used to stabilize data being passed through logic circuits
        - More stages vs. faster clock trade-off
        - Captured by cycle time
      - More complex processors may have a slower clock time, but can process instructions in less clock cycles
        - Links the number of instructions and the cycle time
        - Note that this value is a weighted average value
          - Instructions can have fixed or variable cycle times
          - Simplify the problem by assuming cycle times are fixed
        - Frequency of instructions, latency of instructions, etc.
    - Instruction count
      - Influenced by the programming language, high-level algorithm, compiler, ISA, etc.
      - Smaller instruction count doesn't equate to faster execution time
      - Higher instruction count may have power benefits
    - Cycle time
      - Influenced by the ISA and the hardware implementation
    - Cycles per instruction
      - Influenced by weighting of instructions in the application, cycle time, strength reduction, implemented hardware, 

  - Example:

    - 10 billion instructions

    - 2 GHz clock

    - Instruction set:

      - | Instruction | # of Cycles | Frequency |
        | :---------: | :---------: | :-------: |
        |      R      |  4 cycles   |    40%    |
        |    LW/SW    |  6 cycles   |    30%    |
        |   BEQ/BNE   |  3 cycles   |    30%    |

    - $$
      \text{ET}=\text{IC}\times\text{CPI}\times\text{CT}\\
      \text{ET}=(10\times 10^9)\times(0.4\times 4\times0.3\times 6\times 0.3\times 3)\times(0.5\times 10^{-9})
      $$

    - Imagine a frequent case of `LW` followed by `BEQ`, resulting in benefits to introducing the instruction `LB`, which combines the two instructions => how can we analyze this?

      - We need the frequency of such a use case (i.e., 50% of all `BEQ`s could make use of this new instruction)

      - We need the number of cycles the new instruction takes (i.e., `LB` takes 7 cycles)

      - We need the possible increase in clock time (i.e., +10% to clock time)

        - Assumption that this doesn't change the number of cycles for instructions
        - Does this change actually improve the situation or not?

      - $$
        \text{ET}=\text{IC}\times\text{CPI}\times\text{CT}\\
        \text{ET}=(8.5\times 10^9)\times(\frac{40}{85}\times 5\times\frac{15}{85}\times 6\times\frac{15}{85}\times 3\times\frac{15}{85}\times 7)\times(1.1\times 0.5\times 10^{-9})
        $$

        

## Lecture 2:

- 



## Video 1: Introduction and Performance

- Computer Abstractions and Technology
  - The Computer Revolution	
    - Progress in computer technology
      - Underpinned by Moore's Law (every new generation of technology comes with a doubling of transistor density => more capacity for computing)
    - Makes novel applications feasible
      - Computers in automobiles
      - Cell phones
      - Human genome project
      - World Wide Web (especially in relation to SaaS)
      - Search engines
    - Computers are pervasive
  - Classes of Computers
    - Personal computers
      - General purpose, variety of software
      - Subject to cost/performance tradeoff
    - Server computers
      - Network-based
      - High capacity, performance, reliability
      - Range from small servers to building-sized

