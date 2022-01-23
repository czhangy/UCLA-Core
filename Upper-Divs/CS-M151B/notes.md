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

    - 2GHz clock

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

        

## Lecture 2: ISA Basics

- CISC vs. RISC

  - Old computers had low memory capacity, slow cycle times
    - As memory capacity and CPU latency trended upwards, memory latency grew much slower (memory wall)
      - Transistors scaled (got smaller, leading to higher density), wires did not => results in much slower DRAM access
      - More problematic as we run into problems that require more and more data => motivates caching

    - Rudimentary compiler technology
    - Lack of sophisticated design tools to build complex systems
    - Computer complexity is low relative to today
    - All factors force us into an ISA implementation where there were a lot of types of complex instructions => CISC
      - Simple datapath allows for lack of conflict in this approach (no aggressive clock, etc.)
      - Reduces the size of the program, making efficient use of limited memory
      - Variable-length ISA to conserve even more memory based on complexity of instruction

  - Processor frequency increases, compiler technology improves => system becomes more and more complex to put together
    - Complex instructions begin to inhibit pipelining, driven by the memory wall
    - Memory is no longer an issue, multiple discrete instructions are no longer a concern => RISC
      - Better compilers also help to reorder instructions for better efficiency => unlocked by breaking complex instructions into simpler ones
      - "Reduced" refers to the number of instructions available to us to build the program, not the number of instructions being executed for a given program
      - Fixed-length ISA makes it easier to decode instructions at the cost of memory fragmentation (32 bits in MIPS)

- MIPS

  - 32 registers

    - Each register can hold 32 bits
    - Register files are implemented in hardware, on the CPU
    - To retrieve a particular value in the register, we provide a "register address"
      - This means we must specify which of the 32 registers we want => 5 bits for the register address

  - Operands

    - Register
      - One of the 32 32-bit values from the register file
      - Instruction knows the address of the register value, not the value in the register => level of indirection
      - Flexible, a single instruction can be reused for many different values
      - Can store data or other operands => up to the program to decide

    - Immediate
      - A constant that is specified as part of the instruction itself
      - Doesn't have to access memory or the register file
      - Faster in terms of latency
        - Instructions either read the value of the register address or the value of the immediate
        - Due to pipelining, this benefit doesn't materialize in practice

      - Note the balancing of space in the instruction and space in the register file

  - Formats

    - R-Type

      - Contains an opcode, 3 register specifiers, shift amount, and function determiner
        - The opcode for all R types is always the same 6-bit value
        - The function determiner specifies what operation the instruction encodes

      - Most R-type instructions work in the following format: `RF[RD] = RF[RS] FUNC RF[RT]`

    - I-Type

      - Contains an opcode, 2 register specifiers, and an immediate

      - This is a 32-bit operation

      - `ADDI`: `RF[RT] = RF[RS] + SE(I)`

      - `LW`/`SW`

        - Data movement operations
          - Responsible for moving between memory and register files
          - `LW` loads from memory into the register file
          - `SW` stores from register file into memory

        - `LW`: `RF[RT] <= M[RF[RS] + SE(I)]`
        - `SW`: `M[RF[RS] + SE(I)] <= RF[RT]`

      - `BEQ`/`BNE`

        - `BEQ`:

          - ```pseudocode
            if (RF[RS] == RF[RT])
            	PC = PC + 4 + SES(I)
            else
            	PC = PC + 4
            ```

          - Note that any `BEQ` will advance the `PC` by `4`

          - Since the `PC` is word-aligned, the last 2 bits of the `PC` are always `00`

            - The `I` is left-shifted by `2` prior to the sign extension and addition to ensure this

        - `BNE`

          - ```pseudocode
            if (RF[RS] != RF[RT])
            	PC = PC + 4 + SES(I)
            else
            	PC = PC + 4
            ```

        - Optimized for shorter jumps

        - Conditionals

    - J-Type

      - Contains an opcode and an immediate
      - When we do `PC + 4`, we take the top 4 bits of the result, append the 26-bit immediate in the J-type instruction, and then place `00` at the end for the new address
      - Optimized for longer jumps
      - Unconditional
      - `j`
      - `jal`
        - Stores the `PC + 4` into a register (the return address register) prior to jumping
          - Essentially storing the address of the instruction following the `JAL`
          - Setting up a call queue

        - We can then use an instruction like `jR` to return to the next instruction
          - Forces you to specify the register being used
            - Allows for use beyond simple returning

          - `PC = RF[RS]`
          - Goes away from the format that the instruction is used in, but still uses R-type instructions




## Lecture 3: ISA Design

- Register Spilling

  - May result in storing of the old value and loading of the new value, or just loading of the new value (if the old value is already stored/no longer needed)
  - This may affect execution time, as the increasing frequency of loads and stores may increase the CPI of the program
    - Tradeoffs that we must discuss conceptually
    - Won't get a definitive answer

- Larger Register File

  - Attempt to reduce spilling

  - Increase in hardware latency from increasing the size of the register file manifests in an increase in cycle time and/or an increase in CPI
    - Dependent on the design and how we implement tolerance for that latency
  - Should result in a reduction in spills on the software side (application dependent), resulting in a decrease in instruction count and/or CPI (less loads and stores)
    - Will necessitate a change in the ISA => more registers requires more register bits in instructions
      - Larger instructions
        - Leads to larger code, increasing CPI and possibly CT
      - Same-size instructions
        - Decrease the length of the opcode or `func` field, leading to an increase in instruction count (decrease in number of instructions available)
        - Decrease the length of `shamt` in the R-type and of the immediates in I- and J-type, increasing the instruction count

- Procedure Inlining

  - Reduces branching, which reduces the instruction count and increases CPI (if branching instructions are lower than average)
  - Increases the instruction footprint in memory, possibly increasing CPI



## Lecture 4: ALU I

- The ALU is the physical structure that handles the core arithmetic operations for instructions
  - Takes in a 4-bit ALU operation that specifies one of 6 instructions
  - Takes in 2 32-bit inputs: `a` and `b`
  - Outputs a 32-bit result
  - Outputs a 1-bit value that tells us if the result of the operation was `0`
  - Outputs a 1-bit value that tells us if overflow has occurred
  - Outputs a 1-bit carry out value
- Basic idea of improving on the ripple carry adder is that we have a tradeoff between physical space and performance
  - Use extra logic to precompute carry outs so we don't have to wait for each carry out to propagate down the chain
    - `T` to propagate to the next ALU, `T` to perform the XOR with `a ^ b`
      - `2nT` for the `n`th `CarryOut`
    - 3 situations without `CarryIn`:
      - `G`/generate: `a & b`, we know `CarryOut` must be `1`
      - `P`/propagate: `a ^ b`, we know that `CarryOut` will be the same as `CarryIn`
      - `K`/kill: `a NOR b`, we know that no `CarryOut` exists
  -  All `G` and `P` signals can be computed in parallel, and be used to precompute `CarryIn`s of later adders
    - `C_1 = G_0 OR P_0 AND C_0`
    - `C_2 = G_1 OR P_1 AND G_0 OR C_0 AND P_0 AND P_1`
    - etc.
    - All `G` and `P` signals ready after `T`
    - All `CarryIn` ready at `3T`
    - All sums ready at `4T`



## Lecture 5: Hierarchal CLA and Multiplication

- Hierarchal CLA

  - Idea is to connect multiple CLA structures together with a higher-level CLA

  - Using the notion of generates and propagates at a higher granularity

    - $$
      G=G_0\cdot P_1\cdot P_2\cdot P_3+G_1\cdot P_2\cdot P_3+G_2\cdot P_3+G_3
      $$

    - $$
      P=P_0\cdot P_1\cdot P_2\cdot P_3
      $$

      - Note the lack of reliance on carry-in entirely

    - Expressions for individual carry-ins are exactly the same logical form as their smaller granularity counterparts

  - Controls the exponential fan-in of CLA

- Multiplication

  - Multiplier stored in `Product`'s lower 32 bits
    - `Product` right shifted every iteration
    - Usually always 32 shifts in general



## Pre-Lecture 1: Introduction and Performance

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
    - Supercomputers
      - High-end scientific and engineering calculations
      - Highest capability but represent a small fraction of the overall computer market
    - Embedded computers
      - Hidden as components of systems
      - Stringent power/performance/cost constraints
      - Line between personal and embedded computers is blurry
    
  - The PostPC Era

    - As we move more towards mobile devices and away from the traditional desktop, we're seeing changes in market shares
    - Tablets and smartphones becoming much more popular than the conventional PC
    - As a programmer of a system, what types of machines take precedence?
      - Rise in mobile devices => more emphasis on power efficiency, less requirement for computing power
    - Personal Mobile Device (PMD)
      - Battery operated
      - Connects to the Internet
      - Hundreds of dollars
      - Smartphones, tablets, electronic glasses, etc.
    - Cloud computing
      - Warehouse Scale Computers (WSC)
        - Big data
        - Shared by a large community of users
      - Software as a Service (SaaS)
      - Portion of software run on a PMD and a portion run in the Cloud
      - Amazon and Google

  - What You Will Learn

    - How programs are translated into the machine lanagueg
      - And how the hardware executes them
    - The hardware/software interface
      - Design tradeoffs
    - What determines program performance
      - And how it can be improved
    - How hardware designers improve performance
    - What is parallel processing?

  - Understanding Performance

    - Algorithm
      - Determines number of operations executed
    - Programming language, compiler, architecture
      - Determine number of machine instructions executed per operation
    - Processor and memory system
      - Determine how fast instructions are executed
    - I/O system (including OS)
      - Determines how fast I/O operations are executed

  - Eight Great Ideas

    - Design for Moore's Law
      - Technology trends are giving processor designers a large toolchain to be used
      - Voltage doesn't scale well, how do we spend out budget of transistors effectively?
    - Use abstraction to simplify design
      - Designing for something without fully knowing how it works as a means of simplifying a problem
    - Make the common case fast
      - Something that is done frequently should be as optimized as possible
      - Putting innovation effort in areas where it will benefit the most
    - Performance via parallelism
      - Overlapping latencies to save time and improve efficiency
    - Performance via pipelining
      - Special case of parallelism that separates tasks into specialized stages
      - Assembly line
    - Performance via prediction
      - In cases where it is difficult to know what the process will do ahead of time, we guess to try and save time
      - Focus on branch prediction
    - Hierarchy of memories
      - Difficult to make a high-capacity memory with low latency
      - Instead of having a single type of memory, we have multiple types of memory that cooperate together
    - Dependability via redundancy

  - Below Your Program

    - Application software
      - Written in high-level language
    - System software
      - Compiler: translates HLL code to machine code
      - Operating System: service code
        - Handling I/O
        - Managing memory and storage
        - Scheduling tasks and sharing resources
    - Hardware
      - Processor, memory, I/O controllers

  - Levels of Program Code

    - High-level language
      - Level of abstraction closer to problem domain
      - Provides for productivity and portability
      - Sent to compiler/interpreter
    - Assembly language
      - Textual representation of instructions
      - Sent to assembler
    - Hardware representation
      - Binary digits (bits)
      - Encoded instructions and data

  - Components of a Computer

    - Same components for all kinds of computers
      - Desktop, server, embedded, etc.
    - I/O includes:
      - User-interface devices
        - Display, keyboard, mouse, etc.
      - Storage devices
        - Hard disk, CD/DVD, flash, etc.
      - Network adapaters
        - For communicating with other computers

  - Inside the Processor (CPU)

    - Datapath: performs operations on data
      - Can handle a wide array of instructions
    - Control: sequences datapath, memory, etc.
      - Implements individual instructions
    - Cache memory
      - Small, fast SRAM memory for immediate access to data
      - Close to the top of the memory hierarchy

  - Abstractions

    - Abstraction helps us deal with complexity
      - Hide lower-level detail
    - Instruction Set Architecture (ISA)
      - The hardware/software interface
      - The language that the compiler uses to speak to the processor
      - The implementation that the processor provides to the compiler
      - ISA guides what the architecture needs to be able to handle
      - Gives the architecture and software clear pictures of what they need from each other
    - Application Binary Interface (ABI)
      - The ISA + system software interface
    - Implementation
      - The details underlying and interface

  - Technology Trends

    - Electronics technology continues to evolve
      - Increase capacity and performance
      - Reduced cost
    - The gap between memory and processing speed is growing as DRAM gets larger and larger
      - The "memory wall"
      - Large amount of memory in DRAM constrained by a high latency to DRAM access
    - Pushing us towards accelerator-rich design

  - Semiconductor Technology

    - Silicon: semiconductor
    - Add materials to transform properties:
      - Conductors
      - Insulators
      - Switches

  - Manufacturing ICs

    - Yield: proportion of working dies per wafer

  - Integrated Circuit Cost

    - $$
      \text{Cost per die}=\frac{\text{Cost per wafer}}{\text{Dies per wafer}\times\text{Yield}}\\
      \text{Dies per wafer}\approx\frac{\text{Wafer area}}{\text{Die area}}\\
      \text{Yield}=\frac{1}{(1+(\text{Defects per area}\times\frac{\text{Die area}}{2}))^2}
      $$

    - Non-linear relation to area and defect rate

      - Wafer cost and area are fixed
      - Defect rate determined by manufacturing process
      - Die area determined by architecture and circuit design

  - Response Time and Throughput

    - Response time
      - How long it takes to do a task
    - Throughput
      - Total work done per unit time
        - e.g., tasks/transactions/etc. per hour
    - How are response time and throughput affected by:
      - Replacing the processor with a faster version?
      - Adding more processors?
    - We'll focus on response time for now

  - Relative Performance

    - Define `Performance = 1 / Execution Time`

    - "`X` is `n` times faster than `Y`"

      - $$
        \frac{\text{Performance}_X}{\text{Performance}_Y}=\frac{\text{Execution Time}_Y}{\text{Execution Time}_X}=n
        $$

    - Example: time taken to run a program

      - 10s on `A`, 15s on `B`
      - So `A` is 1.5 times faster than `B`

  - Measuring Execution Time

    - Elapsed time
      - Total response time, including all aspects
        - Processing, I/O, OS overhead, idle time
      - Determines system performance
    - CPU time
      - Time spent processing a given job
        - Discounts I/O time, other jobs' shares
      - Comprises user CPU time and system CPU time
      - Different programs are affected differently by CPU and system performance

  - CPU Clocking

    - Operation of digital hardware governed by a constant-rate clock
    - Clock period: duration of a clock cycle
    - Clock frequency (rate): cycles per second

  - CPU Time

    - $$
      \text{CPU Time}=\text{CPU Clock Cycles}\times\text{Clock Cycle Time}=\frac{\text{CPU Clock Cycles}}{\text{Clock Rate}}
      $$

    - Performance improved by

      - Reducing number of clock cycles
      - Increasing clock rate
      - Hardware designer must often trade off clock rate against cycle count

    - Example:

      - Computer `A`: 2GHz clock, 10s CPU time

      - Designing Computer `B`

        - Aim for 6s CPU time
        - Can do faster clock, but causes `1.2x` clock cycles

      - How fast must Computer `B`'s clock be?

        - $$
          \text{Clock Rate}_B=\frac{\text{Clock Cycles}_B}{\text{CPU Time}_B}=\frac{1.2\times\text{Clock Cycles}_A}{6\text{s}}\\
          \text{Clock Cycles}_A=\text{CPU Time}_A\times\text{Clock Rate}_A=10\text{s}\times 2\text{GHz}=20\times 10^9\\
          \text{Clock Rate}_B=\frac{1.2\times 20\times 10^9}{6\text{s}}=\frac{24\times 10^9}{6\text{s}}=\boxed{4\text{GHz}}
          $$

  - Instruction Count and CPI

    - $$
      \text{Clock Cycles}=\text{Instruction Count}\times\text{Cycles per Instruction}\\
      \text{CPU Time}=\text{Instruction Count}\times\text{CPI}\times\text{Clock Cycle Time}=\frac{\text{Instruction Count}\times\text{CPI}}{\text{Clock Rate}}
      $$

    - Instruction count for a program

      - Determined by program, ISA, and compiler
      - Dynamic count => the number of instructions actually being executed

    - Average cycles per instruction

      - Determined by CPU hardware and software
      - If different instructions have different CPI, the average CPI affected by instruction mix

    - Example:

      - Computer `A`: cycle time = 250ps, CPI = 2.0

      - Computer `B`: cycle time = 500ps, CPI = 1.2

      - Same ISA

      - Which is faster, and by how much?

        - $$
          \text{CPU Time}_A=\text{Instruction Count}\times\text{CPI}_A\times\text{Cycle Time}_A=\text{IC}\times2\times250\text{ps}\\
          =\boxed{\text{IC}\times 500\text{ps}}\\
          \text{CPU Time}_B=\text{Instruction Count}\times\text{CPI}_B\times\text{Cycle Time}_B=\text{IC}\times1.2\times500\text{ps}\\
          =\text{IC}\times 600\text{ps}\\
          \frac{\text{CPU Time}_B}{\text{CPU Time}_A}=\frac{\text{IC}\times 600\text{ps}}{\text{IC}\times 500\text{ps}}=\boxed{1.2}
          $$

    - CPI in More Detail

      - If different instruction classes take different numbers of cycles:

        - $$
          \text{Clock Cycles}=\sum^n_{i=1}(\text{CPI}_i\times\text{Instruction Count}_i)
          $$

        - Weighted average CPI:

          - $$
            \text{CPI}=\frac{\text{Clock Cycles}}{\text{Instruction Count}}=\sum^n_{i=1}(\text{CPI}\times\frac{\text{Instruction Count}_i}{\text{Instruction Count}})
            $$

      - Example:

        - Alternative compiled code sequences using instructions in classes `A`, `B`, and `C`

        - | Class            |  A   |  B   |  C   |
          | ---------------- | :--: | :--: | :--: |
          | CPI for class    |  1   |  2   |  3   |
          | IC in sequence 1 |  2   |  1   |  2   |
          | IC in sequence 2 |  4   |  1   |  1   |

        - Sequence 1: IC = 5

          - $$
            \text{Clock Cycles}=2\times 1+ 1\times 2+ 2\times 3=10\\
            \text{Avg. CPI}=\frac{10}{5}=\boxed{2.0}
            $$

        - Sequence 2: IC = 6

          - $$
            \text{Clock Cycles}=4\times 1+1\times 2+1\times 3=9\\
            \text{Avg. CPI}=\frac{9}{6}=\boxed{1.5}
            $$

  - Performance Summary

    - $$
      \text{CPU Time}=\frac{\text{Instructions}}{\text{Program}}\times\frac{\text{Clock Cycles}}{\text{Instruction}}\times\frac{\text{Seconds}}{\text{Clock Cycle}}\\
      \text{CPU Time}=\text{Instruction Count}\times\text{Cycles per Instruction}\times\text{Cycle Time}
      $$

    - Performance depends on:

      - Algorithm: affects IC and possibly CPI
      - Programming language: affects IC and CPI
      - Compiler: affects IC and CPI
      - ISA: affects IC, CPI, and CT

  - Power Trends

    - In CMOS IC technology

      - $$
        \text{Power}=\text{Capacitive Load}\times\text{Voltage}^2\times\text{Frequency}
        $$

      - Capacitive load influenced by what we integrate on the actual chip
        - Use transistors in a smart way
      - Voltage is the drop in the operable circuit
        - Looked at for dynamic tuning due to its significance

    - As we got performance improvements with increasing clock rate, we saw rises in power concerns

      - Shifts innovation towards multi-core rather than monolithic core
      - "Power wall"
      - Power drops as we optimize more for multi-core

  - Reducing Power

    - Suppose a new CPU has:

      - 85% of capacitive load of old CPU
      - 15% voltage and 15% frequency reduction

    - $$
      \frac{P_{\text{new}}}{P_{\text{old}}}=\frac{C_{\text{old}}\times 0.85\times(V_{\text{old}}\times 0.85)^2\times F_{\text{old}}\times 0.85}{C_{\text{old}}\times V_{\text{old}}^2\times F_{\text{old}}}=0.85^4=\boxed{0.52}
      $$

    - The power wall

      - We can't reduce voltage further
      - We can't remove more heat

    - How else can we improve performance?

  - Uniprocessor Performance

    - Recent improvements to processor performance have slowed down due to the constraints of power, ILP, and memory latency

  - Multiprocessors

    - Multi-core microprocessors
      - More than one processor per chip
    - Requires explicitly parallel programming
      - Compare with ILP
        - Hardware executes multiple instructions at once
        - Hidden from the programmer
      - Hard to do
        - Programming for performance
        - Load balancing
        - Optimizing communication and synchronization

  - SPEC CPU Benchmark

    - Programs used to measure performance

      - Supposedly typical of actual workload

    - Standard Performance Evaluation Corp (SPEC)

      - Develops benchmarks for CPU, I/O, Web, etc.

    - SPEC CPU2006

      - Elapsed time to execute a selection of programs
        - Negligible I/O, so focuses on CPU performance
      - Normalize relative to reference machine
      - Summarize as geometric mean of performance ratios
        - CINT2006 (integer) and CFP2006 (floating-point)

    - $$
      \sqrt[n]{\prod^n_{i=1}(\text{Execution Time Ratio}_i)}
      $$

  -  Pitfall: Amdahl's Law

    - Improving an aspect of a computer and expecting a proportional improvement in overall performance

    - $$
      T_{\text{improved}}=\frac{T_{\text{affected}}}{\text{Improvement Factor}}+T_{\text{unaffected}}
      $$

    - Example: multiply accounts for 80s / 100s

      - How much improvement in multiply performance to get 5x overall?

      - $$
        20=\frac{80}{n}+20
        $$

        - Can't be done!

    - Corollary: make the common case fast

  - Pitfall: MIPS as a Performance Metric

    - MIPS: Millions of Instructions Per Second

    - Doesn't account for:

      - Differences in ISAs between computers
      - Differences in complexity between instructions

    - $$
      \text{MIPS}=\frac{\text{IC}}{\text{ET}\times 10^6}=\frac{\text{IC}}{\frac{\text{IC}\times\text{CPI}}{\text{Clock Rate}}\times 10^6}=\frac{\text{Clock Rate}}{\text{CPI}\times 10^6}
      $$

    - CPI varies between programs on a given CPU

  - Concluding Remarks

    - Cost/performance is improving due to underlying technology development
    - Hierarchal layers of abstraction in both hardware and software
    - ISA => the hardware/software interface
    - Execution time: the best performance measure
    - Power is a limiting factor
      - Use parallelism to improve performance



## Pre-Lecture 2: ISA Basics

- Instruction Set

  - The repertoire of instructions of a computer
    - Method by which the software communicates with the hardware
  - Different computers have different instruction sets
    - But with many aspects in common
  - Early computers had very simple instruction sets
    - Simplified implementation
  - Many modern computers also have simple instruction sets

- Key ISA Decisions

  - Operations
    - How many?
    - Which ones?
    - Length?
      - How many bits does it take to represent individual instructions?
  - Operands
    - How many?
    - Location?
      - Memory? Registers? Immediates?
    - Types?
    - How to specify?
  - Instruction Format
    - Size?
    - How many formats?
    - Remember that instructions are stored in memory

- Main ISA Classes

  - CISC (Complex Instruction Set Computers)
    - Digital's VAX (1977) and Intel's x86 (1978)
      - x86 gets translated to micro-operations, resulting in more RISC-like behavior
    - Large # of instructions
    - Many specialized complex instructions
    - Makes the software's job relatively easy
    - More useful for times when memory was more constrained
  - RISC (Reduced Instruction Set Computers)
    - Almost all machines of 80s and 90s are RISC
      - MIPS, PowerPC, DEC Alpha, IA64
    - Relatively fewer instructions in the set
      - More instructions executed
    - Enable pipelining and parallelism
      - Easier to overlap and extract small tasks

- The MIPS Instruction Set

  - Used as the example throughout the book
  - Stanford MIPS commercialized by MIPS Technologies
  - Large share of embedded core market
    - Applications in consumer electronics, network/storage equipment, cameras, printers, etc.
  - Typical of many modern ISAs

- Arithmetic Operations

  - Add and subtract, three operands

    - Two sources and one destination

  - ```pseudocode
    add a, b, c		# a gets b + c
    ```

    - All arithmetic operations have this form

  - Design Principle 1: Simplicity favors regularity

    - Regularity makes implementation simpler
    - Simplicity enables higher performance at lower cost

  - Example:

    - C code:

      - ```c
        f = (g + h) - (i + j);
        ```

    - Compiled MIPS code:

      - ```mips
        add t0, g, h		# temp t0 = g + h
        add t1, i, j		# temp t1 = i + j
        sub f, t0, t1		# f = t0 - t1
        ```

- Register Operands

  - Arithmetic instructions use register operands

  - MIPS has a 32 x 32-bit register file

    - Use for frequently accessed data
    - Numbered `0` to `31`
    - 32-bit data called a "word"

  - Assembler names:

    - `$t0`, `$t1`, ..., `$t9` for temporary values
    - `$s0`, `$s1`, ..., `$s7` for saved variables

  - Design Principle 2: Smaller is faster

    - c.f. main memory: millions of locations
    - Access latency on wires is shorter => related to physical design

  - Examples:

    - C code:

      - ```c
        f = (g + h) - (i + j);
        ```

        - `f`, ..., `j` in `$s0`, ... `$s4` => done through other instructions that aren't displayed below

    - Compiled MIPS code:

      - ```mips
        add $t0, $s1, $s2
        add $t1, $s3, $s4
        sub $s0, $t0, $t1
        ```

        - `add` instructions are independent of one another => potential for parallelism

- Memory Operands

  - Main memory used for composite data

    - Arrays, structures, dynamic data, etc.

  - To apply arithmetic operations

    - Load values from memory into registers
    - Store result from register to memory

  - Memory is byte-addressed

    - Each address identifies an 8-bit byte
    - Word granularity for load instructions

  - Words are aligned in memory

    - Address must be a multiple of `4`

  - MIPS is Big Endian

    - MSB is at the least address of a word
    - c.f. Little Endian: LSB is at the least address of a word

  - Example 1:

    - C code:

      - ```c
        g = h + A[8]
        ```

        - `g` in `$s1`, `h` in `$s2`, base address of `A` in `$s3`

    - Compiled MIPS code:

      - Index `8` requires offset of `32`

        - 4 bytes per word

      - ```mips
        lw	$t0, 32($s3)		# load word
        add	$s1, $s2, $t0
        ```

        - `<offset>(<base register>)` 

  - Example 2:

    - C code:

      - ```c
        A[12] = h + A[8]
        ```

        - `h` in `$s2`, base address of `A` in `$s3`

    - Compiled MIPS code:

      - Index `8` requires offset of `32`

      - Index `12` requires offset of `48`

      - ```mips
        lw	$t0, 32($s3)		# load word
        add	$t0, $s2, $t0
        sw	$t0, 48($s3)		# store word
        ```

        - Load words grab from memory and write to a register
        - Store words grab from a register and write to memory

- Registers vs. Memory

  - Registers are faster to access than memory
  - Operating on memory data requires loads and stores
    - More instructions to be executed
    - c.f. CISC where instructions can directly access memory
  - Compiler must use registers for variables as much as possible
    - Only spill to memory for less frequently used variables
      - Can result in more loads and stores => makes optimization extremely important
    - Register optimization is important!

- Immediate Operands

  - Constant data specified in an instruction

  - ```mips
    addi $s3, $s3, 4
    ```

  - No subtract immediate instruction

    - Just use a negative constant:

      - ```mips
        addi $s2, $s1, -1
        ```

  - Design Principle 3: Make the common case fast

    - Small constants are common => helps reduce instruction count
    - Immediate operand avoids a load instruction

- The Constant Zero

  - MIPS register 0 (`$zero`) is the constant `0`

    - Cannot be overwritten

  - Useful for common operations

    - E.g., move between registers

      - ```mips
        add $t2, $t1, $zero
        ```

- Unsigned Binary Integers

  - Range:

    - $$
      [0, 2^n-1]
      $$

- 2s-Complement Signed Integers

  - Range:

    - $$
      [-2^{n-1},2^{n-1}-1]
      $$

  - Bit `31` is the sign bit

    - `1` for negative numbers
    - `0` for non-negative numbers

- Signed Negation

  - Complement and add `1`
    - Complement means `1 -> 0` and `0 -> 1`

- Sign Extension

  - Representing a number using more bits
    - Preserve the numeric value
  - In MIPS instruction set
    - `addi`: extend immediate value
    - `lb`, `lh`: extend loaded byte/half-word
    - `beq`, `bne`: extend the displacement
  - Replicate the sign bit to the left
    - c.f. unsigned values: extend with `0`s

- Representing Instructions

  - Instructions are encoded in binary
    - Called machine code
  - MIPS instructions
    - Encoded as 32-bit instruction words (fixed-length)
    - Small number of formats encoding operation code (opcode), register numbers, etc.
    - Regularity!
  - Register numbers
    - `$t0` - `$t7` are registers `8` - `15`
    - `$t8` - `$t9` are registers `24` - `25`
    - `$s0` - `$s7` are registers `16` - `23`

- MIPS R-format Instructions

  |  `op`  |  `rs`  |  `rt`  |  `rd`  | `shamt` | `funct` |
  | :----: | :----: | :----: | :----: | :-----: | :-----: |
  | 6 bits | 5 bits | 5 bits | 5 bits | 5 bits  | 6 bits  |

- Instruction fields:

  - `op`: operation code (opcode)
  - `rs`: first source register number
  - `rt`: second source register number
  - `rd`: destination register number
  - `shamt`: shift amount
  - `funct`: function code (extends opcode)

  - Example:

    - ```mips
      add $t0, $s1, $s2
      ```

      | special  |   $s1   |   $s2   |   $t0   |    0    |   add    |
      | :------: | :-----: | :-----: | :-----: | :-----: | :------: |
      | `000000` | `10001` | `10010` | `01000` | `00000` | `100000` |

- Hexadecimal

  - Base-16
    - Compact representation of bit-strings
    - 4 bits per hex digit

- MIPS I-Format Instructions

  |  `op`  |  `rs`  |  `rt`  | constant or address |
  | :----: | :----: | :----: | :-----------------: |
  | 6 bits | 5 bits | 5 bits |       16 bits       |

- Immediate arithmetic and load/store instructions

  - `rt`: destination or source register number

  - Constant:

    - $$
      [-2^{15},2^{15}-1]
      $$

  - Address: offset added to base address in `rs`

  - Design Principle 4: Good design demands good compromises
    - Different formats complicate decoding, but allow 32-bit instructions uniformly
    - Keep formats as similar as possible

- Stored Program Computers

  - Instructions represented in binary, just like data
  - Instructions and data stored in memory
  - Programs can operate on programs
    - e.g., compilers, linkers, etc.
  - Binary compatibility allows compiled programs to work on different computers
    - Standardized ISAs

- Logical Operations

  - Instructions for bitwise manipulation

    |  Operation  |  C   | Java  |     MIPS      |
    | :---------: | :--: | :---: | :-----------: |
    | Shift left  | `<<` | `<<`  |     `sll`     |
    | Shift right | `>>` | `>>>` |     `srl`     |
    | Bitwise AND | `&`  |  `&`  | `and`, `andi` |
    | Bitwise OR  | `|`  |  `|`  |  `or`, `ori`  |
    | Bitwise NOT | `~`  |  `~`  |     `nor`     |

  - Useful for extracting and inserting groups of bits in a word

- Shift Operations

  - `shamt`: how many positions to shift
  - Shift left logical
    - Shift left and fill with `0` bits
    - `sll` by `i` bits multiplies by `2^i`
  - Shift right logical
    - Shift right and fill with `0` bits
    - `srl` by `i` bits divides by `2^i` (unsigned only)

- AND Operations

  - Useful to mask bits in a word
    - Select some bits, clear other to `0`

- OR Operations

  - Useful to include bits in a word
    - Set some bits to `1`, leave other unchanged

- NOT Operations

  - Useful to invert bits in a word

    - Change `0` to `1`, and `1` to `0`

  - MIPS has NOR 3-operand instruction

    - `a NOR b == NOT (a OR b)`

    - ```mips
      nor $t0, $t1, $zero
      ```

      

## Pre-Lecture 3: Branching and Jumping

- Conditional Operations

  - Branch to a labeled instruction if a condition is true

    - Otherwise, continue sequentially

  - ```mips
    beq rs, rt, L1
    ```

    - If `(rs == rt)`, branch to instruction labeled `L1`

  - ```mips
    bne rs, rt, L1
    ```

    - If `(rs != rt)`, branch to instruction labeled `L1`

  - ```mips
    j L1
    ```

    - Unconditional jump to instruction labeled `L1`

  - Compiling If-Statements

    - C code:

      - ```c
        if (i == j) f = g + h;
        else f = g - h
        ```

        - `f`, `g`, etc. in `$s0`, `$s1`, etc.

    - Compiled MIPS code:

      - ```mips
              bne $s3, $s4, Else
              add $s0, $s1, $s2
              j   Exit
              sub $s0, $s1, $s2
        Else: sub $s0, $s1, $s2
        Exit: ...
        ```

        - Assembler calculates the addresses

  - Compiling Loop Statements

    - C code:

      - ```c
        while (save[i] == k) i += 1;
        ```

        - `i` in `$s3`, `k` in `$s5`, address of `save` in `$s6`

    - Compiled MIPS code:

      - ```mips
        Loop: sll  $t1, $s3, 2
              add  $t1, $t1, $s6
              lw   $t0, 0($t1)
              bne  $t0, $s5, Exit
              addi $s3, $s3, 1
              j    Loop
        Exit: ...
        ```

- Basic Blocks

  - A basic block is a sequence of instructions with:
    - No embedded branches (except at end)
    - No branch targets (except at beginning)
  - A compiler identifies basic blocks for optimization
  - An advanced processor can accelerate execution of basic blocks

- More Conditional Operations

  - Set result to `1` if a condition is true

    - Otherwise, set to `0`

  - ```mips
    slt rd, rs, rt
    ```

    - `if (rs < rt) rd = 1; else rd = 0;`

  - ```mips
    slti rt, rs, constant
    ```

    - `if (rs < constant) rt = 1; rt = 0;`

  - Use in combination with `beq`, `bne`

    - ```mips
      slt $t0, $s1, $s2  # if ($s1 < $s2)
      bne $t0, $zero, L  # branch to L
      ```

- Branch Instruction Design

  - Why not `blt`, `bge`, etc.?
  - Hardware for `<`, `>=`, etc. would be slower than `=`, `!=`
    - Combining with branch involves more work per instruction, requiring a slower clock
    - All instructions penalized
  - `beq` and `bne` are the common case
  - This is a good design compromise

- Signed vs. Unsigned

  - Signed comparison: `slt`, `slti`
  - Unsigned comparison: `sltu`, `sltui`

- Procedure Calling

  - "Jumping and linking"
    - An unconditional jump that saves the current location to return back to
  - Steps required:
    - Place parameters in registers
    - Transfer control to procedure
    - Acquire storage for procedure
    - Perform procedure's operations
    - Place result in register for caller
    - Return to place of call

- Register Usage

  - `$a0` - `$a3`: arguments (registers 4 - 7)
  - `$v0`, `$v1`: result values (registers 2 and 3)
  - `$t0` - `$t9`: temporaries
    - Can be overwritten by callee
  - `$s0` - `$s7`: saved
    - Must be saved/restored by callee
  - `$gp`: global pointer for static data (register 28)
  - `$sp`: stack pointer (register 29)
  - `$fp`: frame pointer (register 30)
  - `$ra`: return address (register 31)

- Procedure Call Instructions

  - Procedure call: jump and link

    - ```mips
      jal ProcedureLabel
      ```

      - Changes program counter to `ProcedureLabel`

    - Address of following instruction (current address + `4`) put in `$ra`

      - `$ra` used implicitly

    - Jumps to target address

  - Procedure return: jump register

    - ```mips
      jr $ra
      ```

    - Copies `$ra` to program counter

      - Specified explicitly

    - Can also be used for computed jumps

  - Leaf Procedure Example

    - C code:

      - ```c
        int leaf_example (int g, h, i, j) {
          int f;
          f = (g + h) - (i + j);
          return f;
        }
        ```

        - Arguments `g`, ..., `j` in `$a0`, ... `$a3`
        - `f` in `$s0` (hence, need to save `$s0` on stack)
        - Result in `$v0`

    - MIPS code:

      - ```mips
        leaf_example:
        	addi $sp, $sp, -4
        	sw   $s0, 0($sp)     # Save $s0 on stack
        	add  $t0, $a0, $a1
        	add  $t1, $a2, $a3
        	sub  $s0, $t0, $t1   # Procedure body
        	add  $v0, $s0, $zero # Result
        	lw   $s0, 0($sp)
        	addi $sp, $sp, 4     # Restore $s0
        	jr   $ra             # Return
        ```

- Non-Leaf Procedures

  - Procedures that call other procedures

  - For nested call, caller needs to save on the stack

    - Its return address
    - Any arguments and temporaries needed after the call

  - Restore from the stack after the call

  - Example:

    - C code:

      - ```c
        int fact (int n) {
          if (n < 1) return f;
          else return n * fact(n - 1);
        }
        ```

        - Argument `n` in `$a0`
        - Result in `$v0`

    - MIPS code:

      - ```mips
        fact:
        	  addi $sp, $sp, -8   # Adjust stack for 2 items
        	  sw   $ra, 4($sp)    # Save return address
        	  sw   $a0, 0($sp)    # Save argument
        	  slti $t0, $a0, 1    # Test for n < 1
        	  beq  $t0, $zero, L1
        	  addi $v0, $zero, 1  # If so, result is 1
        	  addi $sp, $sp, 8    # Pop 2 items from stack
        	  jr   $ra            # And return
        L1: addi $a0, $a0, -1   # Else decrement n
        	  jal  fact           # Recursive call
        	  lw   $a0, 0($sp)    # Restore original n
        	  lw   $ra, 4($sp)    # And return address
        	  addi $sp, $sp, 8    # Pop 2 items from stack
        	  mul  $v0, $a0, $v0  # Multiply to get result
        	  jr   $ra            # And return
        ```

- Local Data on the Stack

  - Local data allocated by callee
    - e.g., C automatic variables
  - Procedure frame (activation record)
    - Used by some compilers to manage stack storage

- Memory Layout

  - Text: program code
  - Static data: global variables
    - e.g., static variables in C, constant arrays and string
    - `$gp` initialized to address allowing ± offsets into this segments
  - Dynamic data: heap
    - e.g., `malloc` in C, `new` in Java
    - Grows toward higher addresses
  - Stack: automatic storage
    - Used by procedure calls to store frames
    - Grows toward lower addresses
  - Instructions themselves are in memory
    - The program counter points to this memory

- 32-Bit Constants

  - Most constants are small

    - 16-bit immediate is sufficient

  - For the occasional 32-bit constant

    - ```mips
      lui rt, constant
      ```

    - Copies 16-bit constant to left 16 bits of `rt`

    - Clears right 16 bits of `rt` to `0`

  - Example:

    - ```mips
      lui $s0, 61
      ori $s0, $s0, 2304
      ```

      - Building a larger 32-bit address

- Branch Addressing

  - Branch instructions specify opcode, two registers, target address, etc.

  - Most branch targets are near branch

    - Forward or backward

    - |  `op`  |  `rs`  |  `rt`  | constant or address |
      | :----: | :----: | :----: | :-----------------: |
      | 6 bits | 5 bits | 5 bits |       16 bits       |

  - PC-relative addressing

    - `Target address = PC + offset x 4`
    - Program counter already incremented by `4` by this time

- Jump Addressing

  - Jump (`j` and `jal`) targets could be anywhere in the text segment

    - Encode full address in instruction

      - |  `op`  | address |
        | :----: | :-----: |
        | 6 bits | 26 bits |

  - (Pseudo) Direct jump addressing

    - `Target address = PC_(31 ... 28) : (address x 4)`

- Target Addressing Example

  - Loop code from earlier example
    - Assume `Loop` at location `80000`

- Branching Far Away

  - If branch target is too far to encode with 16-bit offset, assembler rewrites the code

  - Example:

    - ```mips
          beq $s0, $s1, L1
                 ↓
          bne $s0, $s1, L2
          j L1
      L2: ...
      ```



## Pre-Lecture 4: ALU Basics

- Arithmetic for Computers
  - Operations on integers
    - Addition and subtraction
    - Multiplication and division
    - Dealing with overflow
  - Floating-point real numbers
    - Representation and operations
  - Integer Addition
    - Example: `7 + 6`
    - Overflow if result out of range
      - Adding positive and negative operands, no overflow
      - Adding 2 positive operands
        - Overflow if result sign is `1`
      - Adding 2 negative operands
        - Overflow if result sign is `0`
  - Integer Subtraction
    - Add negation of second operand
    - Example: `7 - 6 = 7 + (-6)`
    - Overflow if result out of range
      - Subtracting 2 positive or 2 negative operands, no overflow
      - Subtracting positive from negative operand
        - Overflow if result sign is `0`
      - Subtracting negative from positive operand
        - Overflow if result sign is `1`
  - Dealing with Overflow
    - Some languages (e.g., C) ignore overflow
      - Use MIPS `addui`, `subu` instructions
    - Other languages (e.g., Ada, Fortran) require raising an exception
      - Use MIPS `add`, `addi`, `sub` instructions
      - On overflow, invoke exception handler
        - Save program counter in exception program counter (EPC) register
        - Jump to predefined handler address
        - `mfc0` (move from coprocessor register) instruction can retrieve EPC value to return after corrective action

- ALU Design

  - Instruction Fetch => Instruction Decode => Operand Fetch => Execute (ALU) => Result Store => Next Instruction
  - Inputs: `a`, `b`, and ALU operation
  - Outputs: `Zero`, `CarryOut`, `Result`, `Overflow`
    - `Result` should have the same number of bits as `a` and `b`

- One-Bit ALU

  - Performs `AND`, `OR`,  and `ADD`

    - On 1-bit operands
    - Components:
      - AND gate
      - OR gate
      - 1-bit adder
      - Multiplexer
        - Chooses which operation is pushed to result
        - Every time we use the ALU, all three operations are performed, but only one is output

  - One-Bit Full Adder

    - Also known as a (3, 2) adder

    - Half adder

      - No `CarryIn`

    - | `a`  | `b`  | `CarryIn` | `CarryOut` | `Sum` |  Comments  |
      | :--: | :--: | :-------: | :--------: | :---: | :--------: |
      | `0`  | `0`  |    `0`    |    `0`     |  `0`  | `0+0+0=00` |
      | `0`  | `0`  |    `1`    |    `0`     |  `1`  | `0+0+1=01` |
      | `0`  | `1`  |    `0`    |    `0`     |  `1`  | `0+1+0=01` |
      | `0`  | `1`  |    `1`    |    `1`     |  `0`  | `0+1+1=10` |
      | `1`  | `0`  |    `0`    |    `0`     |  `1`  | `1+0+0=01` |
      | `1`  | `0`  |    `1`    |    `1`     |  `0`  | `1+0+1=10` |
      | `1`  | `1`  |    `0`    |    `1`     |  `0`  | `1+0+1=10` |
      | `1`  | `1`  |    `1`    |    `1`     |  `1`  | `1+1+1=11` |

    - `CarryOut` Logic Equation

      - ```pseudocode
        CarryOut = (!a & b & CarryIn) | (a & !b & CarryIn)
        								| (a & b & !CarryIn) | (a & b & CarryIn)
        								
        CarryOut = (b & CarryIn) | (a & CarryIn) | (a & b)
        ```

    - `Sum` Logic Equation

      - ```pseudocode
        Sum = (!a & !b & CarryIn) | (!a & b & !CarryIn)
        					| (a & !b & !CarryIn) | (a & b & CarryIn)
        ```

- 32-Bit ALU

  - Ripple carry ALU

    - Carry from each 1-bit ALU to the next
      - Each handles 1 bit of the result
    - Start at the 0th ALU and end at the 31st ALU

  - Subtraction

    - Expand our 1-bit ALU to include an inverter
      - 2's complement: take inverse of every bit and add `1`
        - Add input `Binvert` to multiplex between the original signal and the inverted signal, then add `1` by setting `CarryIn` to `1`

  - Overflow

    - For `N`-bit ALU

      - ```pseudocode
        Overflow = CarryIn[N - 1] ^ CarryOut[N - 1]
        ```

    - On the MSB (`N - 1`) ALU

  - Zero Detection

    - Conditional branches

    - One big NOR gate

      - Add an `Ainvert` signal to achieve a NOR effect

    - ```pseudocode
      Zero = (Result_N-1 + Result_N-2 + ... Result_1 + Result_0)
      ```

    - Any non-zero result will cause zero detection output to be `0`

  - Set-On-Less-Than (`SLT`)

    - `SLT` produces a `1` if `rs < rt` and `0` otherwise
      - All but least significant bit will be `0`
      - How do we set the least significant bit?
      - Can we use subtraction?
        - `rs - rt < 0`
      - Set the least significant bit to the sign-bit of `rs - rt`
    - New input: `LESS`
      - All set to `0` except the LSB's
    - New output: `SET`
      - Set by the adder in the MSB's ALU
    - Implementation
      - `SET` of MSB is connected to `LESS` of LSB

- Final ALU

  - You should feel comfortable identifying what signals accomplish:
    - `add`
    - `sub`
    - `and`
    - `or`
    - `nor`
    - `slt`

- Can We Make a Faster Adder?

  - Worst-case delay for `N`-bit ripple carry adder

    - `2N` gate delays
      - 2 gates per `CarryOut`
      - `N` `CarryOut`s

  - We will explore the carry lookahead adder

    - Generate - bit `i` creates new `Carry`

      - ```pseudocode
        g_i = A_i & B_i
        ```

- Carry Look Ahead

  - Idea is to avoid propagating the `CarryOut` of one adder into the `CarryIn` of the next by generating the `CarryIn` ahead of time
    - Trades area for performance
    - If `A == B`, we know what the `CarryOut` is
    - Add 2 new signals to adders: `G` and `P`
      - `G`: `A & B` => guaranteed carry, "generate"
      - `P`: `A ^ B` => carry if `CarryIn`, "propagate"
      - All done in parallel, `G` and `P` are only dependent on `A` and `B`
  - Partial Carry Lookahead Adder
    - Connect several `N`-bit lookahead adders together
      - Ripple carry
    - 4 8-bit carry lookahead adders can form a 32-bit partial carry lookahead adder
  - Hierarchal CLA

- Carry Select Adder

  - 2 1-bit adders, one with `1` as `CarryIn` and the other with `0` as `CarryIn`
    - Multiplex these with `CarryIn`, if the delay of the multiplexer is less than the delay of chaining, we see benefit to this tradeoff



## Pre-Lecture 5: Multiplication and Floating Point

- Multiplication

  - Start with long-multiplication approach

  - Multiplication Hardware

    - Multiplies using a series of adds and shifts
    - Shifts the multiplier right every iteration
    - Shifts the multiplicand left every iteration (64-bit)
      - Forces ALU to be 32 bits
    - Product develops in the product register, with 64 bits of significance
    - Process:
      - Test `Multiplier[0]`
        - If `1`, add multiplicand to product and place in `Product`
        - Shift `Multiplicand` left 1 bit
        - Shift `Multiplier` right 1 bit
        - Check if it's the 32nd iteration
          - Loop back to step 1 if not

  - Optimized Multiplier

    - Shift `Product` right instead of `Multiplicand`
      - Allows us to use 32-bit ALUs and multiplicand register, saving latency
      - Add to the upper bits of product and shift right
      - Load multiplier into the lower bits of `Product`
        - Right shift strips bits out
        - Upper bits written depending on the control test
    - Perform steps in parallel: add/shift
    - One cycle per partial-product addition
      - That's ok, if frequency of multiplications is low

  - Faster Multiplier

    - Uses multiple adders
      - Cost/performance tradeoff
    - Can be pipelined
      - Several multiplications performed in parallel

  - MIPS Multiplication

    - Two 32-bit registers for product

      - `HI`: most-significant 32 bits
      - `LO`: least-significant 32 bits

    - Instructions

      - ```mips
        mult rs, rt
        multu rs, rt
        ```

        - 64-bit product in `HI`/`LO`

      - ```mips
        mfhi rd
        mflo rd
        ```

        - Move from `HI`/`LO` to `rd`
        - Can test `HI` value to see if product overflows 32 bits

      - ```mips
        mul rd, rs, rt
        ```

        - Least-significant 32 bits of product into `rd`

  - Signed Multiplication?

    - Make both positive
      - Remember whether to complement product when done
    - Apply definition of 2's complement
      - Need to sign-extend partial products and subtract at the end
    - Booth's Algorithm
      - Elegant way to multiply signed number using same hardware as before and saving cycles
      - Replace a string of `1`s in multiplier with an initial subtract when we first see a `1`, and then later add for the bit after the last `1`
      - Current bit vs. bit to the right

- IEEE Floating-Point Format

  - `S | Exponent | Fraction`

    - `Exponent` is 8 bits in a single and 11 bits in a double
    - `Fraction` is 23 bits in a single and 52 bits in a double
    - `S`: sign bit (`0` => non-negative, `1` => negative)
    - Normalize significand: `1.0 <= |significand| < 2.0`
      - Always has a leading pre-binary-point `1` bit, so no need to represent it explicitly (hidden bit)
      - Significand is `Fraction` with the `1.` restored
    - `Exponent`: excess representation: actual exponent + `Bias`
      - Ensures exponent is unsigned
      - Single: `Bias = 127`; Double: `Bias = 1203`

  - Floating-Point Addition

    - Consider a 4-digit decimal example:

      - $$
        9.999\times10^1+1.610\times10^{-1}
        $$

      - Align decimal points

        - Shift number with smaller exponent

        - $$
          9.999\times10^1+0.016\times10^1
          $$

      - Add significands

        - $$
          9.999\times10^1+0.016\times10^1=10.015\times10^1
          $$

      - Normalize result and check for over/underflow

        - $$
          1.0015\times10^2
          $$

      - Round and renormalize if necessary

        - $$
          1.002\times10^2
          $$

    - FP Adder Hardware

      - Small ALU to check difference of exponents
      - Large ALU to add shifted fractional fields
      - etc.
      - Large amount of hardware needed for this to work
        - Typically multi-cycled operations



## Pre-Lecture 6:

- 

