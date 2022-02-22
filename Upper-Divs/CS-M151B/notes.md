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
    - Usually always 32 shifts in general, counted in the control test
  - Booth's Algorithm
    - Look for sequences of `1`s in the multiplier
      - Each sequence can be reduced to a subtraction and an addition
    - LSB and the "bit to the right"
      - `00` => nothing
      - `01` => end of a sequence, add
      - `10` => beginning of a sequence, subtract
      - `11` => nothing



## Lecture 6: Datapath

- Introduction

  - 
    $$
    \text{ET}=\text{IC}\times\text{CPI}\times\text{CT}
    $$

  - Build the microprocessor with a subset of the MIPS ISA

    - R-format: `add`, `sub`, `slt`, `or`, `nor`, `and`
    - I-format: `lw`, `sw`, `beq`
    - Be able to expand this datapath
      - Add components to make the new instruction work
      - Avoid breaking the implementation of already-existing instructions

  - Single-cycle datapath

    - `CPI = 1`
    - `CT` dependent on longest latency instruction

- Datapath

  - High-Level Flow
    - Use the PC to access instruction memory and grab instruction
    - The instruction must be decoded by the instruction decoder, accessing registers and determining control
    - The instruction is executed, involving the ALU and branching
    - Data memory is accessed if necessary
      - Loads/stores
    - Write back occurs back to the register files
  - Major Blocks
    - PC
      - Clock-latched
    - Instruction Memory
      - Idealized
      - I/O
        - 32-bit input port:
          - Address
        - 32-bit output port
          - Instruction
      - We supply an address, it supplies an instruction
    - Register File
      - Clock-latched
      - I/O
        - 3 5-bit input ports:
          - Address A
          - Address B
          - Write Address
        - 32-bit input port:
          - Write Data
        - 2 5-bit output ports:
          - Data A
          - Data B
      - Data A/B is the data contained in the register specified by Address A/B
      - Write Data is the data to be written to the register specified by Write Address
    - ALU
      - I/O
        - 2 32-bit input ports
          - X
          - Y
        - 1 1-bit output port
          - Zero
        - 1 32-bit output port
          - Result
      - Handles arithmetic and logical operations for R-types
      - Handles the subtraction for the branching comparison
    - Data Memory
      - I/O
        - 2 32-bit input ports
          - Address
          - Write Data
        - 1 32-bit output port
          - Data
      - Address allows us to read from or write to that address in memory
        - Data is what is read from data memory
        - Write Data is what is written to data memory
  - Control
    - Components need to be controlled to affect what data moves between components
    - `RegWrite`
      - 2 registers will be read from unconditionally
      - Register writes need to be protected
        - Only write if `RegWrite = 1`
    - `Operation`
      - 4-bit
      - Control what operation is performed on the data coming into the ALU
    - `MemRead`
      - Indicates if we are reading from data memory at the address specified
      - We don't want every instruction to read from data memory for caching/page fault/protection fault reasons
    - `MemWrite`
      - Indicates if we are writing to data memory from the address specified
      - Mutually exclusive with `MemRead` for the single-cycle datapath
    - `ALUOp`
      - 2-bit
      - `00` => add
      - `01` => subtract
      - `10` -> `funct` field
    - `ALUSrc`
      - `0` => use Data B output as source of Y for ALU
      - `1` => use immediate as source of Y for ALU
    - `MemtoReg`
      - `0` => ALU output connected to Write Data of register file
      - `1` => Data memory Data port connected to Write Data of register file
    - `RegDst`
      - `0` => `rt` used as Write Address
      - `1` => `rd` used as Write Address
    - `Branch`
      - Indicates if the current instruction is a branching instruction
  - Flow
    - Instruction Breakdown
      - Top 6 bits (`[31 - 26]`) of the instruction from instruction memory are isolated to determine opcode
      - `[25 - 21]` to Address A of register file (`rs`)
      - `[20 - 16]` to Address B of register file (`rt`)
    - R-Type
      - Data A and Data B flow into X and Y in the ALU
      - `Operation` set based on the `funct` field of the instruction
      - Doesn't use data memory
        - Result of ALU connected to the Write Data port of the register file
        - Bits `[15 - 11]` of the instruction set to Write Address port of register file
      - Bits `[5 - 0]` enter the ALU control to specify what the ALU should do for an R-type
        - Used if `ALUOp = 10`
    - I-Type
      - Bits `[15 - 0]` should be used as the immediate
        - Needs to be sign-extended to a 32-bit value
        - Patch it into Y input of ALU with a MUX
      - Access data memory (`lw`)
        - Patch output to Write Data with a MUX
        - Use a MUX to specify `rt` as the destination register
      - Write to data memory (`sw`)
        - Reroute Data B of the register file to the Write Data port of data memory
        - Set `RegWrite = 0`
          - Doesn't matter what `RegDst` or `MemtoReg` are, as no writes are occurring in the register file anyways
      - Alter the PC (`beq`)
        - Shift the sign-extended immediate by `2`
        - Patch it into the `PC + 4` ALU with a MUX
          - Cannot hardwire with `Zero` output, as that would cause any arithmetic operation that resulted in `0` to branch randomly => guard with AND gate (`Zero & Branch`)
    - PC
      - Route PC output to an ALU with `+ 4` hardcoded to advance the PC



## Lecture 7: Datapath Extension

- `addi`
  - I-type
  - `R[RT] = R[RS] + SE(I)`
  - Datapath
    - No new datapath elements needed
  - Control
    - New unique opcode since this is an I-type
    - `RegDst = 0`
    - `ALUSrc = 1`
    - `MemtoReg = 0`
    - `RegWrite = 1`
    - `MemRead = 0`
    - `MemWrite = 0`
    - `Branch = 0`
    - `ALUOp = 00`
    - No new control needed
- `blt`
  - I-type
  - `if R[RS] < R[RT] PC = PC + 4 + SES(I)`
  - Datapath
    - Hardwire `11` to be `slt` on the ALU control
    - Use the `Zero` output of the ALU and invert it
    - Use an AND-gate to perform `Bltc & Zero`
    - Use an OR-gate to perform `(Branch & Zero) | (Bltc & Sign)`
  - Control
    - New unique opcode since this is an I-type
    - `RegDst = X`
    - `ALUSrc = 0`
    - `MemtoReg = X`
    - `RegWrite = 0`
    - `MemRead = 0`
    - `MemWrite = 0`
    - `Branch = 0`
    - `ALUOp = 11`
    - New control
      - `Bltc = 1`, `0` for all other instructions
- `jr`
  - R-type
  - `PC = R[RS]`
  - Datapath
    - New MUX choosing between the current PC input and the result of `R[RS]`
      - Controlled by `Jrc`
    - New MUX between `RegWrite` and register file
      - Hardwire a `0` so that `jr` doesn't write to register
  - Control
    - Opcode is `000000` since `jr` is an R-type
      - Unique `func` field for ALU control
    - `RegWrite = 0`
    - New control
      - `Jrc` coming out of the ALU control, only `1` on the `func` field representing `jr`
- `jal`
  - J-type
  - `PC = PC + 4[31:28] || Immed || 00`, `$31 = PC + 4`
  - Datapath
    - Take lower 26 bits of the instruction, shift it to the left by 2, and then append to the upper 4 bits of `PC + 4`
      - MUX this with `PC + 4`
    - Connect original `PC + 4` with a MUX to the Write Data port
    - Add a hardcoded `$31` to the Write Register port
  - Control
    - New unique opcode
    - `RegDst = 10`
      - Sign-extend all others
    - `ALUSrc = X`
    - `MemtoReg = X`
    - `RegWrite = 1`
    - `MemRead = 0`
    - `MemWrite = 0`
    - `Branch = 0`
    - `ALUOp = 00`
    - New control
      - `Jalc = 1`, `0` for all others
- `cmov`
  - R-type
  - `if (R[RT] != 0) R[RD] = R[RS]`
  - Datapath
    - Take Read Data 1 to MUX with the Write Data port
      - Controlled by `Cmovc`
    - MUX Read Data 1 input to ALU, with `1` hardwired to `0`
      - Controlled by `Cmovc`
    - MUX `RegWrite` with the `Zero` output from the ALU
      - Controlled by `Cmovc`
  - Control
    - Opcode is `000000` since `cmov` is an R-type
    - ALU control is add
    - New control
      - `Cmovc` coming out of the ALU control, only `1` on the `func` field representing `cmov`
- `saw`
  - I-type
  - `M[R[RS]] = R[RT] + SE(I)`
  - Datapath
    - MUX with Read Data 1 into the Address of data memory
      - Controlled by `Sawc`
    - MUX with ALU result into the Write Data of data memory
      - Controlled by `Sawc`
  - Control
    - `RegDst = X` 
    - `Branch = 0`
    - `MemRead = 0`
    - `MemtoReg = X`
    - `ALUOp = 00`
    - `MemWrite = 1`
    - `ALUSrc = 1`
    - `RegWrite = 0`
    - New control
      - `Sawc` coming out of control, `1` for `sawc`, `0` otherwise



## Lecture 8: Pipelined Datapath

- 5 structurally independent stages:
  - `IF`: instruction fetch
    - PC and instruction memory

  - `ID`: instruction decode
    - Register file

  - `EX`: execution
    - ALU

  - `MEM`: memory access
    - Data memory

  - `WB`: write back
    - Register file

  - One instruction per stage of the pipeline
    - Achieved by buffering between each stage with latches
      - Banks of registers that hold data values between clock ticks
      - Operations in stage complete before the setup time of the latch, which can then store the values in that stage on the clock edge
      - Latches store data and control signals between stages
      - Forces each instruction to go through each stage of the pipeline whether that stage is useful for that instruction or not
        - "Regularity" of the pipeline

    - 4 latches:
      - `IF/ID`
      - `ID/EX`
      - `EX/MEM`
      - `MEM/WB`

    - Synchronization of clocks between latches allow us to separate instructions
    - Single-cycle implementation cycle time is bounded by the total latency of the critical path
      - Hope is to drop the clock time while keeping the CPI close to `1`
      - Ideally, each stage is perfectly balanced, but this isn't realistic
      - Pipelined cycle time is bounded by the slowest stage
        - Some drop in cycle time, but we don't know by how much

    - When each stage of the pipeline is filled, we are in the steady state
      - Way for us to gauge if we are utilizing the pipeline optimally
      - Cannot avoid the pipeline's start-up time
        - "Disappears" as more instructions are executed

- A structural hazard is when there isn't enough physical resources to satisfy the current needs of the instructions in the pipeline
  - Current design of the pipeline has non-overlapping functionality
  - No structural hazards exist in our datapath

- Data Hazards
  - Data from a prior instruction is needed for the current instruction
    - Forces us to leave the steady state, pulling CPI away from `1`

  - Software approach:
    - Inserting of independent instructions between two dependent instructions by the compiler
      - Without hardware support, we need 3 independent instructions or no-ops to resolve this

    - Assume the register file has a transparent latch
      - Write occurs in the first half of the clock cycle and read occurs in the second half of the clock cycle
      - Allows `WB` of one instruction and `ID` of a dependent instruction to occur in the same clock cycle

    - Requires the compiler to know information about the hardware
      - ISA changes now break code portability for the same ISA
      - Ruins separation between hardware and software

    - Instruction count would likely increase due to the injection of no-ops
      - Unlikely that enough independent instructions can be found in the program

  - Hardware approach:
    - Inject a bubble into the pipeline to stall
      - Effectively a no-op, but not an instruction fetched from memory
        - Doesn't take space in the instruction cache
        - Introduces the need for the hazard detection logic
          - May impact cycle time if this logic is the critical path

      - All control signals zeroed-out
      - Freezes the dependent instruction and all following instructions in their respective stages
        - Requires us to do two things:
          - Make sure the PC and `IF/ID` latch do not update
            - Write disable line into PC and `IF/ID`, controlled by the hazard detection logic

          - The `ID/EX` latch must create the bubble
            - MUX that controls if the control logic is passed into `ID/EX` or if all `0`s are

    - Hazard Detection
      - If `RegWrite` is high and the destination register from `ID/EX` is writing to one of the registers being read in `IF/ID`, there is a potential need to stall
        - Needs the `rs` and `rt` of `IF/ID`
        - Needs the destination register (`rd` or `rt`) and `RegWrite` of `ID/EX`
      - If `RegWrite` is high and the destination register from `EX/MEM` is a match, there is a potential need to stall
      - Resultant signal generates the bubble at `ID/EX` and stops the `IF/ID` latch and PC from updating

  - 3 types:
    - RAW (read after write)
      - True data dependence
      - `lw` then `add`

    - WAW (write after write)
      - False data dependence
      - `add` then `add`
      - Creates a hazard for out-of-order execution

    - WAR (write after read)
      - False data dependence
      - `add` then `lw`
      - Creates a hazard for out-of-order execution




## Lecture 9: Pipeline Forwarding and Branching

- Motivation

  - In certain situations, it can be noted that there might not be a need to stall, but we will with hazard detection
  - An instruction executing in the `EX` stage will have its result ready by the end of the cycle, so the following instruction could theoretically use that computed value without going through the register file
  - We could forward this value, removing the need to stall
    - Need to be able to forward to the `EX` stage from both the `EX/MEM` latch and the `MEM/WB` latch
    - Results in 3 possible candidates for the sources of the ALU in `EX`

- Forwarding

  - Loads must be handled differently, as the result of an `lw` instruction is known at the end of the `MEM` stage, not the `EX` stage

    - Known as the Load-Use Hazard

  - Forwarding Unit

    - Decides what to forward and when to forward

    - Note that the forwarding unit doesn't handle any data transfer, it is solely responsible for acting as a control unit

      - Forwarding of data handled by the datapath itself

    - 2 outputs: `ForwardA` and `ForwardB`

      - Control the MUXs that decide what is input to the ALU

    - Takes in 2 inputs from the `ID/EX` latch: `Rs` and `Rt`

      - Tells the forwarding unit what register specifiers the instruction currently in `EX` is waiting on

    - Takes in 2 inputs from the `EX/MEM` latch: `RegWrite` and `Rd`

      - Tells the forwarding unit if the instruction currently in `MEM` is writing back to the register file, and, if it is, which register it is writing back to

    - Takes in 2 inputs from the `MEM/WB` latch: `RegWrite` and `Rd`

      - Tells the forwarding unit if the instruction currently in `WB` is writing back to the register file, and, if it is, which register it is writing back to

    - `EX` hazard

      - ```pseudocode
        if (EX/MEM.RegWrite and (EX/MEM.RegisterRd != 0)
            and (EX/MEM.RegisterRd == ID/EX.RegisterRs))
            ForwardA = 10
            
        if (EX/MEM.RegWrite and (EX/MEM.RegisterRd != 0)
            and (EX/MEM.RegisterRd == ID/EX.RegisterRt))
            ForwardB = 10
        ```

      - Tests if the forwarding unit should be `10`

        - Passes the result of the ALU operation for the previous instruction into the ALU input(s) for the current instruction

      - Checks 3 things:

        - Checks if the previous instruction is writing to the register file at all
        - Checks if the destination register of the previous instruction overlaps with an input register of the current instruction
          - `rs` for `ForwardA`
          - `rt` for `ForwardB`

        - Checks if the destination register of the previous instruction is `$zero`
          - No reason to forward if this is the case

    - `MEM` hazard

      - ```pseudocode
        if (MEM/WB.RegWrite and (MEM/WB.RegisterRd != 0)
        	and not (EX/MEM.RegWrite and (EX/MEM.RegisterRd != 0)
        			 and (EX/MEM.RegisterRd = ID/EX.RegisterRs))
        	and (MEM/WB.RegisterRd == ID/EX.RegisterRs))
            ForwardA = 01
            
        if (MEM/WB.RegWrite and (MEM/WB.RegisterRd != 0)
        	and not (EX/MEM.RegWrite and (EX/MEM.RegisterRd != 0)
        			 and (EX/MEM.RegisterRd = ID/EX.RegisterRt))
        	and (MEM/WB.RegisterRd == ID/EX.RegisterRt))
            ForwardB = 01
        ```

      - Tests if the forwarding unit should be `01`

        - Passes the result of the ALU operation for the instruction in `WB` into the ALU input(s) for the current instruction

      - Checks 4 things:

        - Checks if the instruction in `WB` is writing to the register file at all

        - Checks if the destination register of the instruction in `WB` overlaps with an input register of the current instruction

        - Checks if the destination register of the instruction in `WB` is `$zero`

        - Checks that there doesn't also exist an `EX` hazard

          - `EX` hazards should take precedence

          - Example:

            - ```mips
              add	$t0, $s1, $s2
              sub	$t0, $t0, $s0
              or	$t1, $t0, $s3
              ```

            - The `or` instruction should be taking the result of the `sub`, not the `add`, as that was the most recent modification of `$t0`

    - Load-Use Hazard

      - Occurs when a `lw` is directly followed by a dependent instruction
        - The `lw`'s value isn't known until `MEM`, and therefore breaks the current forwarding logic
        - The dependent instruction needs to be stalled by 1 cycle in the `EX` stage
          - Zeroes out control bits
          - Don't update the PC or `IF/ID`

      - Add to the hazard detection unit
        - Look for this specific load-use case and bubble if it occurs
          - In the current instruction set, we can check `ID/EX.MemRead` to see if there is an `lw` in the `EX` stage
          - Check `ID/EX.RegisterRt` for the destination of the `lw`
            - Check against `IF/ID.RegisterRs` and `IF/ID.RegisterRt` to see if there's an overlap with the instruction in `ID`

          - If all of these things are true, we send a bubble into the `ID/EX` latch for 1 cycle to stall the instruction in `ID`

        - Once `lw` reaches the `WB` stage, we can now successfully forward the value fetched by `lw` from `MEM/WB` to `EX`

- Branch Hazards

  - At a branch instruction, we must wait for the `beq` to resolve before we can guarantee that instructions coming into the pipeline are the correct instructions

  - Software methods:

    - Fill up space behind branch instructions with no-ops

      - Results in increase in instruction count
      - Forces the compiler to know when branches are resolved in a given pipeline, reducing portability

    - Branch delay slot

      - Basic idea is to place control-independent instructions into special slots after the branch instruction
      - Allows for a less significant increase in instruction count, as meaningful work can still be done while waiting for the branch instruction to resolve

      - Good for situations in which we have a tight control over the compiler and hardware, we have enough instructions to fill many slots/few slots to fill, and when the penalty for re-compiling code for different hardware is small

  - Hardware methods:

    - Not-Taken Prediction
      - Guess that the branch is not taken every time
      - Actual result determined when the branch instruction resolves
        - If correct, we can just continue fetching instructions on the path we guessed, avoiding any negative penalties
        - If incorrect, we must kill off instructions that shouldn't have executed and then redirect fetch to the instructions that should have been executed
          - We kill off instructions by flushing (turning the instructions into bubbles)
          - Flushing must occur before we modify any data we shouldn't have

    - Static Prediction
      - For a specific instruction, we give it a prediction based on the instruction itself

    - Dynamic Prediction
      - Use a hardware structure called the branch predictor, which uses the PC and other information to guess if a given instruction will be taken or not taken
      - An approach that learns as the program executes and branches are taken
      - Use a way to look up past behavior, helping with structures such as `while` and `for` which are heavily biased towards one side
        - 2-Bit Pattern History Table
          - Each entry of the PHT has 2 bits of storage, hashed by a part of the PC
          - MSB may tell us the prediction
          - Update the predictor based on observed behavior at the end of `EX`
          - Dictated by an FSM

        - Use in combination with a branch target buffer to cache previous locations that have been jumped to

- Bubbling to stall and incorrect branch predictions both contribute to an increasing CPI



## Lecture 10: Advanced Pipelining

- Performance Implications of Pipelining

  - Assume the 5-stage pipeline we've been using

  - $$
    \text{ET}=\text{IC}\times\text{CPI}\times\text{CT}
    $$

    - In a balanced pipeline, `CT` may be `1/5` of the original `CT`
      - Can be improved by more aggressive pipelining
    - In a perfect situation, `CPI` may be very close to `1`
      - Not achievable due to hazards
    - Ideally, pipelining may drop our `ET` to `1/5` of the original

- Aggressive Pipelining/Superpipelining

  - Basic idea is to continue breaking down the critical path, lessening the longest latency of a pipeline stage, allowing the `CT` to decrease further
  - Hazard penalties increase as the pipeline gets deeper
    - i.e., branch misprediction, load-use, etc.
    - Loose Loops Sink Chips

  - Is a given change worth it given the benefit, or does the added cost outweigh any benefits?

- Total CPI

  - $$
    \text{TCPI}=\text{BCPI}+\text{MCPI}
    $$

  - `BCPI` is based on the CPI that results from the pipeline/hazards

  - `MCPI` is based on the latency of memory accesses

- Multiple Issue/Superscalar

  - Basic idea is to increase the throughput of the pipeline, allowing for more instructions to be executed at a time, resulting in a decrease in CPI
  - Structural Aspects
    - Bring out 8 bytes (2 instructions) from instruction memory in `IF`
      - Control dependencies make this challenging
      - Requirement of finding independent instructions makes a challenging case of ILP
        - Dependent instructions running simultaneously will result in incorrect program behavior

    - Separate control logic for the instructions in `ID`
      - Add more ports to support more reading/writing in the register file
      - Sharing of the register file allows for easier data sharing than with TLP

    - Duplicate hardware in `EX`
    - Increase ports and simultaneous loads for the data memory in `MEM`
    - Add more ports to support multiple instructions writing back to the register file for `WB`
    - All changes increase the latency of the hardware, likely resulting in a `CT` impact

  - Static vs. Dynamic Tradeoffs
    - Compilation has an amortized, up-front cost
    - Compiler can see the entire program, while the hardware is bounded by the buffer for instruction memory
    - Compiler can't see real-time information, while the hardware can, making it more flexible
    - Compiler is forced to behave conservatively when it optimizes, leading to possibly incomplete optimization when compared to hardware approaches

  - Example Multiple Issue
    - Bundle ALU instructions with memory instructions
    - Heterogeneous specialization simplifies the hardware
      - Possibly prevents an increase in cycle time that results from an increase in complexity

    - Constrains what instructions can be bundled together 

  - Static Multiple Issue
    - VLIW (Very Long Instruction Word) method
      - The compiler bundles independent instructions together
      - May include `NOP`s bundled with instructions with large amounts of dependencies
      - Due to the compiler's reliance on knowledge of the hardware for this method, it can also be exploited to deal with hazards rather than stalling it in the hardware
        - Ex) scheduling to avoid a load-use hazard

    - Static scheduling can resolve dependencies within the compiler
      - Can also handle anti-dependencies using offsets
      - Can more aggressively optimize by adding ILP through techniques such as loop unrolling
        - Reduces the number of `NOP`s needed

    - Generates a single version per program, independent of the data

  - Dynamic Multiple Issue
    - Abstract View
      - We get instructions in program order (the order the compiler determined)
        - `IF`

      - We execute the instructions out of order
        - `EX`, `MEM`, `WB`

      - We then reorder the instructions back into program order in the commit phase
        - This allows for the illusion that, from the software/OS point of view, the program is executing instructions in the order given by the compiler
        - In reality, we want to be executing things in whatever order we want to speed things up

    - The complexity originates from the need to determine what instructions can be executed out of order, and how to bring those instructions back in order for the commit phase
    - Register Renaming
      - Logical registers, such as `$t0` and `$s1`, are registers that the compiler can see and allocate
        - The ones the ISA is aware of and are needed to handle commit

      - Physical registers may not have a 1-to-1 correspondence with logical registers, there should be more of them
        - They act as multiple versions of a single logical register

      - Converts a logical register specifier into a physical register specifier
        - Renaming allows for further division of dependent instructions by getting rid of false dependencies
        - Allocation done for registers being written to, while reading done for registers being read from
          - Reading done using the Register Alias Table (RAT), which maps from logical registers to physical tables

      - Done in the frontend of the hardware
        - Compiler is unaware of this process

    - Reorder Buffer (ROB)
      - Contains the original order of instructions that have been fetched, but not committed
      - Allocated and removed in order
        - Instructions that have completed before their predecessors are forced to wait

      - Updated out of order
      - Determines how many instructions we can consider as a whole for a commit

    - Scheduling Window
      - Contains the instructions that have been fetched, but not completed
      - Instructions placed in the scheduling window and ROB at the same time
      - Instructions are fetched, placed in the SW/ROB, sent into execution by the SW, then wait in the ROB until committed
      - Constrains how many instructions can be sent into execution

    - Out-of-order execution helps to overlap latencies as much as possible
      - Can adapt to the data of the program
      - In-order commits help verify execution and maintain precise exceptions




## Lecture 11: Superscalar Processors

- Superscalar
  - In-Order 1
    - `IF`
    - `ID`
    - Register renaming
      - Uses the RAT
      - Maps from logical registers to physical registers to remove false dependencies and make better use of ILP
      - Problem of aliasing of effective address of `lw` and `sw`
  - Out-of-Order
    - `EX`
    - `MEM`
    - `WB`
  - In-Order 2
    - Commit
  - Allocation
    - ROB (Reorder Buffer)
      - Allocates in order, completes out of order, commits in order
    - MOB (Memory Ordering Buffer)
      - Deal with `lw` and `sw` in particular
      - Tracks the effective addresses of `lw` and `sw` in program order
        - Once the address is known, we can check if there is a conflict
    - SB (Store Buffer)
      - Keeps the data for `sw` instructions that haven't yet been verified by the MOB
    - Reservation Station
      - Wakes up instructions that are eligible for execution by the functional units
        - Selection has to watch out for structural hazards
  - Idea of completing instructions before knowing before that they can be executed - speculative execution
- CPI Calculation of More Complex Pipelines
  - `TCPI = BCPI + MCPI`
    - `BCPI`: comes from the pipeline
    - `MCPI`: comes from memory
  - `BCPI`
    - Assume it's baked into the pipeline
    - `BCPI = Peak CPI + Stalls per Instruction + Flushes per Instruction`
      - Stalls per instruction handles data hazards
      - Flushes per instruction handles control hazards
    - Example:
      - Assume:
        - Scalar processor
        - 5-stage pipeline
        - Forwarding for data hazards
        - Load-use hazards cost 1 cycles
        - 90% accurate dynamic branch prediction
        - Branches are resolved in `MEM`
        - 30% of instructions are `lw`s
          - 50% of these are immediately followed by a dependent
        - 20% of instructions are `beq`/`bne`
      - Peak CPI is `1`
      - For hazards, think `Frequency × Penalty`
      - Stalls per instruction is `(0.3)(0.5)(1)`
        - `(0.3)(0.5)` is the frequency
        - `(1)` is the penalty
      - Flushes per instruction is `(0.2)(0.1)(3)`
        - `(0.2)(0.1)` is the frequency
        - `(3)` is the penalty



## Lecture 12: Caching

- Model:
  - L1 cache holds `2^12` bytes and takes 1 cycle to access
  - L2 cache holds `2^20` bytes and takes 10 cycles to access
  - Memory holds `2^32` bytes and takes 200 cycles to access
  - 32B block size
- Caches
  - Moves data at a courser granularity than bytes to take advantage of locality
    - Views memory as blocks
    - Each block is discrete
    - Requested data will be somewhere within the fetched chunk
    - Starting memory address dependent on block size
      - Ex) 32B block size => `...00000`
  - Address requests data from cache, can result in a hit or miss
    - On a hit, the data block can then be fetched from the cache
    - Address contains an offset that can be used to see where the data is within the block
      - Offset size dependent on block size
      - Used to isolate a word
  - We need a way to check if a given address is present in the cache
    - Simplest method is direct mapping
      - Indexed by the middle bits of the address, right before the offset
        - Number of bits determined by cache size
        - Minimizes thrashing by allowing for data near each other to co-exist in the cache
        - Decoder maps the bits to the table entry
        - Low-level hash table
      - Rest of the address is the tag, which uniquely identifies an entry in the direct-mapped cache
        - Saved in the cache
        - Compare the upper bits of the address and the tag with a comparator
      - Cache also contains an additional bit call the valid bit that tells us if the data in the cache is valid
        - Check for tag equivalence and valid bit => if true, then we have the correct data
    - More complex method is associativity
      - How many blocks map to a particular cache index
      - Each block in an index is referred to as a way
      - We need as many comparators as ways
        - Need to compare each way to a particular memory request
      - `Total Data Size = # Indices × Associativity × Block Size`
  - We need a method to evict data from the cache
    - LRU => expensive on highly associative implementations
    - Random => models LRU closely
  - How do stores handle caches?
    - Write through
      - Write the next level when the current level is written to
    - Write back
      - Write the next level at eviction
      - Maintains a dirty bit that tracks if the next level needs to be written to
      - We don't have to pay the cost of accessing memory on every write, the cost is amortized
      - Delays the instruction that triggers the write back
    - What about on a store miss?
      - Write allocate treats the store just like a load
      - Write around skips the current level and writes directly to the next level
        - Attempts to avoid polluting the cache
        - Beneficial when there is low locality between loads and stores
  - There are multiple types of misses
    - A compulsory miss is one that we didn't have an opportunity to avoid
      - Cache itself doesn't matter
    - A conflict miss is one where the data was previously in the cache and there was space to keep it in the cache, but it was evicted
      - Compare with a fully associative cache, which eliminates conflict misses
    - A capacity miss is one where there isn't enough physical room in the cache, causing a miss



## Lecture 13:

- 



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



## Pre-Lecture 6: Datapath and Control

- Introduction
  - CPU performance factors
    - Instruction count
    - CPI and cycle time
  - We will examine 2 MIPS implementations
    - A single-cycle implementation
      - CPI will always be `1`, cycle time will be based on the instruction with the longest latency
    - A pipelined version
  - Simple subset, shows most aspects
    - Memory reference: `lw`, `sw`
    - Arithmetic/logical: `add`, `sub`, `and`, `or`, `slt`
    - Control transfer: `beq`, `j`
- Instruction Execution
  - PC => instruction memory, fetch instruction
  - Register numbers => register file, read registers
  - Depending on instruction class:
    - Use ALU to calculate
      - Arithmetic result
      - Memory address for load/store
      - Branch target address
    - Access data memory for load/store
    - PC <= target address or PC + 4
- CPU Overview
  - PC pointing to instruction memory
    - Specify what instruction to grab at what address
    - Instruction comes out of the instruction memory
      - Assume box spits out instruction based off of input address
  - Register file has two outputs into the ALU beside it (`rs`, `rt`)
    - The ALU also has another wire coming straight from the instruction memory that can be used for immediate arithmetic
  - ALU sends calculation to the data input port of the register file and to the address port of data memory for loads/stores
    - Data memory can either send data to the data input of the register file (load) or grab from the register file and place in the data port of data memory (store)
  - First adder has a hardwired value of `4`, which allows us to get the next instruction (increment PC)
  - Second adder is for effective address calculation, grabbing an immediate from instruction memory to calculate a new PC
  - Multiplexers
    - Can't just join wires together
      - Use multiplexers
    - Control
      - Sets up what happens along the datapath

- Logic Design Basics

  - Information encoded in binary
    - Low voltage = `0`, high voltage = `1`
    - One wire per bit
    - Multi-bit data encoded on multi-wire buses
  - Combinational element
    - Operate on data
    - Output is a function of input
  - State (sequential) elements
    - Store information
  - Combinational Elements
    - AND-gate
      - `Y = A & B`
    - Adder
      - `Y = A + B`
    - Multiplexer
      - `Y = S ? l1 : l0`
    - Arithmetic/Logic Unit
      - `Y = F(A, B)`
  - Sequential Elements
    - Register: stores data in a circuit
      - Uses a clock signal to determine when to update the stored value
      - Edge-triggered: update when `clk` changes from `0` to `1`
        - All processing needs to occur between clock ticks
      - Register with write control
        - Only updates on clock edge when write control input is `1`
        - Used when stored value is required later
  - Clocking Methodology
    - Combinational logic transforms data during clock cycles
      - Between clock edges
      - Input from state elements, output to state element
      - Longest delay determines clock period

- Building a Datapath

  - Datapath
    - Elements that process data and addresses in the CPU
      - Registers, ALUs, MUXs, memories, etc.
  - We will build a build a MIPS datapath incrementally
    - Refining the overview design
  - Instruction Fetch
    - 32-bit register PC
      - Provides the address for the instruction memory to fetch an instruction
      - Instruction comes out of instruction memory
      - Incremented by `4` with an ALU for the next instruction
      - Everything happens in a single cycle
  - R-Format Instructions
    - Read two register operands (`rs` and `rt`)
    - Register file
      - Read register 1 and 2 ports (5-bit)
        - Data at specified registers driven out of read data 1 and read data 2 ports, respectively
      - Write register port (5-bit)
      - Write data port is the value that will be written to the register specified by the write register port
      - `RegWrite` is control logic that tells the register file whether or not to write using write register/write data
    - ALU
      - 4-bit ALU operation from control logic
      - Perform arithmetic/logical operation
    - Write register result
  - Load/Store Instruction
    - Read register operands
    - Calculate address using 16-bit offset
      - Use ALU, but sign-extend offset
      - Sign extension unit transforms 16-bit immediate into 32-bit value
    - Data memory
      - Address port to specify where to read.write
      - Read data port pulls data out of memory
      - Write data port writes data into memory
      - `MemWrite` control line enables write data port
      - `MemRead` control line enables read data port
    - Load: read memory and update register
    - Store: write register value to memory
  - Branch Instructions
    - Read register operands
    - Compare operands
      - Use ALU, subtract, and check `Zero` output
    - Calculate target address
      - Sign-extend displacement
      - Shift left 2 places (word displacement)
      - Add to `PC + 4`
        - Already calculated by instruction fetch
    - Adder
      - Takes in `PC + 4` from instruction datapath and the sign extended immediate from the instruction that has been left-shifted by `2`
      - Outputs the branch target
    - ALU
      - Concerned with the `Zero` output for comparison
  - Composing the Elements
    - First-cut datapath does an instruction in one clock cycle
      - Each datapath element can only do one function at a time
      - Hence, we need separate instruction and data memories
    - Use MUXs where alternate data sources are used for different instructions

- Full Datapath

  - ALU Control

    - ALU used for:

      - Load/Store: `F = add`
      - Branch: `F = subtract`
      - R-type: `F` depends on `funct` field

    - | ALU Control | Function |
      | :---------: | :------: |
      |   `0000`    |   AND    |
      |   `0001`    |    OR    |
      |   `0010`    |   Add    |
      |   `0110`    | Subtract |
      |   `0111`    |   SLT    |
      |   `1100`    |   NOR    |

    - Assume 2-bit `ALUop` derived from opcode

      - Combinational logic derives ALU control

      - | opcode | `ALUop` |
        | ------ | ------- |
        | `lw`   | `00`    |
        | `sw`   | `00`    |
        | `beq`  | `01`    |
        | R-type | `10`    |

  - The Main Control Unit

    - Control signals derived from instruction
    - Breaking up instructions
      - 4 possible opcodes: R-type, load, store, branch
      - `rs` is present for all instructions

  - Controller

    - |            | R-format |   `lw`   |   `sw`   |  `beq`   |
      | :--------: | :------: | :------: | :------: | :------: |
      |   Opcode   | `000000` | `100011` | `101011` | `000100` |
      |  `RegDst`  |   `1`    |   `0`    |    X     |    X     |
      |  `ALUSrc`  |   `0`    |   `1`    |   `1`    |   `0`    |
      | `MemtoReg` |   `0`    |   `1`    |    X     |    X     |
      | `RegWrite` |   `1`    |   `1`    |   `0`    |   `0`    |
      | `MemRead`  |   `0`    |   `1`    |   `0`    |   `0`    |
      | `MemWrite` |   `0`    |   `0`    |   `1`    |   `0`    |
      |  `Branch`  |   `0`    |   `0`    |   `0`    |   `1`    |
      |  `ALUOp1`  |   `1`    |   `0`    |   `0`    |   `0`    |
      |  `ALUOp2`  |   `0`    |   `0`    |   `0`    |   `1`    |

  - Implementing Jumps

    - Jump uses word address
    - Update PC with concatenation of:
      - Top 4 bits of old PC
      - 26-bit jump address
      - `00`
    - Need an extra control signal decoded from opcode

- Up Next

  - Pipelined Implementation
  - Why isn't single cycle enough?
    - Control is relatively simple
    - CPI is `1`, but cycle time must be long enough for every instruction to complete
    - Branch instruction vs. load instruction
      - Loads require instruction fetch, register access, ALU, memory access, register access
      - Branches require instruction fetch, register access, ALU
    - And this is for a simplified processor!
      - No floating point ops, no multiply or divide



## Pre-Lecture 7: Single-Cycle Datapath Control

- Main Controller

  - | Signal Name | R-format | `lw` | `sw` | `beq` |
    | ----------- | :------: | :--: | :--: | :---: |
    | `op[5]`     |   `0`    | `1`  | `1`  |  `0`  |
    | `op[4]`     |   `0`    | `0`  | `0`  |  `0`  |
    | `op[3]`     |   `0`    | `0`  | `1`  |  `0`  |
    | `op[2]`     |   `0`    | `0`  | `0`  |  `1`  |
    | `op[1]`     |   `0`    | `1`  | `1`  |  `0`  |
    | `op[0]`     |   `0`    | `1`  | `1`  |  `0`  |
    | `RegDst`    |   `1`    | `0`  |  X   |   X   |
    | `ALUSrc`    |   `0`    | `1`  | `1`  |  `0`  |
    | `MemtoReg`  |   `0`    | `1`  |  X   |   X   |
    | `RegWrite`  |   `1`    | `1`  | `0`  |  `0`  |
    | `MemRead`   |   `0`    | `1`  | `0`  |  `0`  |
    | `MemWrite`  |   `0`    | `0`  | `1`  |  `0`  |
    | `Branch`    |   `0`    | `0`  | `0`  |  `1`  |
    | `ALUOp[1]`  |   `1`    | `0`  | `0`  |  `0`  |
    | `ALUOp[0]`  |   `0`    | `0`  | `0`  |  `1`  |

- ALU Controller

  - | Opcode | `ALUOp` | Instruction  | Function | ALU Action | ALUCtrl |
    | ------ | :-----: | ------------ | -------- | ---------- | ------- |
    | `lw`   |  `00`   | Load word    | XXXXXX   | Add        | `010`   |
    | `sw`   |  `00`   | Store word   | XXXXXX   | Add        | `010`   |
    | `beq`  |  `01`   | Branch equal | XXXXXX   | Sub        | `110`   |
    | R-type |  `10`   | Add          | `100000` | Add        | `010`   |
    | R-type |  `10`   | Subtract     | `100010` | Sub        | `110`   |
    | R-type |  `10`   | AND          | `100100` | AND        | `000`   |
    | R-type |  `10`   | OR           | `100101` | OR         | `001`   |
    | R-type |  `10`   | SLT          | `101010` | SLT        | `111`   |



## Pre-Lecture 8: Pipelined Datapath

- Performance Issues

  - Longest delay determines clock period
    - Critical path: load instruction
    - Instruction memory => register file => ALU => data memory => register file
  - Not feasible to vary period for different instructions
  - Violates design principle
    - Making the common case fast
  - We will improve performance by pipelining

- Pipelining Analogy

  - Pipelined laundry: overlapping execution
    - Parallelism improves performance

- MIPS Pipeline

  - Five stages, one step per stage:
    - `IF`: Instruction fetch from memory
    - `ID`: Instruction decode and register read
    - `EX`: Execute operation or calculate address
    - `MEM`: Access memory operand
    - `WB`: Write result back to register
  - Pipeline Performance
  - Pipeline Speedup
    - If all stages are balanced:
      - i.e., all take the same time
      - The time between pipelined instructions is equal to the time between non-pipelined instructions divided by the number of stages
    - If not balanced, speedup is less
    - Speedup due to increased throughput
      - Latency (time for each instruction) does not decrease
  - Pipelining and ISA Design
    - MIPS ISA designed for pipelining
      - All instructions are 32 bits
        - Easier to fetch and decode in one cycle
        - Compare to x86: 1- to 17-byte instructions
      - Few and regular instruction formats
        - Can decode and read registers in one step
      - Load/store addressing
        - Can calculate address in 3rd stage, access memory in 4th stage
      - Alignment of memory operands
        - Memory access takes only one cycle
  - Pipeline Principles
    - All instructions that share a pipeline must hav e the same stages in the same order
      - Therefore, `add` does nothing during the `MEM` stage
      - `sw` does nothing during the `WB` stage
    - All intermediate values must be latched each cycle
    - There is no functional block reuse
      - Ex) we need 2 adders and ALU (like in single-cycle)
  - Pipeline Registers
    - Need registers between stages to hold information produced in the previous cycle

- Pipeline Operation

  - Cycle-by-cycle flow of instructions through the pipelined datapath
    - "Single-clock-cycle" pipeline diagram
      - Shows pipeline usage in a single cycle
      - Highlight the resources used
    - Compare to a "multi-clock-cycle" diagram
      - Graph of operation over time
  - We'll look at "single-clock-cycle" diagrams for load and store

- Pipelined Control

  - Control signals derived from instruction
    - As in single-cycle implementation

- Hazards

  - Example:

    - Suppose initially, register `$i` holds the number `2i`

    - What happens when we see the following dynamic instruction sequence:

      - ```mips
        add $3, $10, $11
        ```

        - This should add `20 + 22`, putting the result `42` into `$3`

      - ```mips
        lw $8, 50($3)
        ```

        - This should load memory location `92` (`42 + 50`) into `$8`

      - ```mips
        sub $11, $8, $7
        ```

        - This should subtract `14` from that just-loaded value

  - Situations that prevent starting the next instruction in the next cycle

  - Structure Hazards

    - A required resource is busy
    - Conflict for use of a resource
    - In MIPS pipeline with single memory
      - Load/store requires data access
      - Instruction fetch would have to stall for that cycle
        - Would cause a pipeline "bubble"
    - Hence, pipelined datapaths require separate instruction/data memories
      - Or separate instruction/data caches

  - Data Hazards

    - Need to wait for previous instruction to complete its data read/write

    - An instruction depends on completion of data access by a previous instruction

      - ```mips
        add $s0, $t0, $t1
        sub $t2, $s0, $t3
        ```

    - Occurs when a result is needed in the pipeline before it is available

    - Dealing with Data Hazards

      - In software:
        - Insert independent instructions (or no-ops)
        - Reorder code to avoid use of load result in the next instruction
      - In hardware:
        - Insert bubbles (i.e., stall the pipeline)
          - To ensure proper pipeline execution in light of register dependencies, we must:
            - Detect the hazard
            - Stall the pipeline
              - Prevent the `IF `na d`ID` stages from making progress
                - The `ID` stage because we can't go on until the dependent instruction completes correctly
                - The `IF` stage because we do not want to lose any instructions
                - Don't write the `PC` (`PCWrite = 0`)
                - Don't rewrite the `IF`/`ID` register (`IF/IDWrite = 0`)
              - Insert "nops"
                - Set all control signals propagating to `EX`/`MEM`/`WB` to zero
        - Data forwarding

  - Control Hazards

    - Deciding on control action depends on previous instruction



## Pre-Lecture 9: Forwarding, Branching, and Exceptions

- Forwarding (aka Bypassing)

  - Use result when it is computed

    - Don't wait for it to be stored in a register
    - Requires extra connections in the datapath

  - Data Hazards in ALU Instructions

    - Consider this sequence:

      - ```mips
        sub	$2, $1, $3
        and	$12, $2, $5
        or	$13, $6, $2
        add	$14, $2, $2
        sw	$15, 100($2)
        ```

    - We can resolve hazards with forwarding

      - How do we detect when to forward?

  - Detecting the Need to Forward

    - Pass register numbers along pipeline
      - e.g., `ID/EX.RegisterRs` = register number for `rs` sitting in `ID/EX` pipeline register
      - ALU operand register numbers in `EX` stage are given by `ID/EX.RegisterRs`, `ID/EX.RegisterRt`
    - Data hazards when:
      - `EX/MEM.RegisterRd = ID/EX.RegisterRs`
      - `EX/MEM.RegisterRd = ID/EX.RegisterRt`
        - Forward from `EX/MEM` pipeline register
      - `MEM/WB.RegisterRd = ID/EX.RegisterRs`
      - `MEM/WB.RegisterRd = ID/EX.RegisterRt`
        - Forward from `MEM/WB` pipeline register
    - But only if the forwarding instruction will write to a register
      - `EX/MEM.RegWrite`, `MEM/WB.RegWrite`
    - And only if `rd` for that instruction is not `$zero`

- Forwarding Conditions

  - `EX` hazard

    - ```pseudocode
      if (EX/MEM.RegWrite and (EX/MEM.RegisterRd != 0) 
          and (EX/MEM.RegisterRd == ID/EX.RegisterRs))
          ForwardA = 10
      ```

    - ```pseudocode
      if (EX/MEM.RegWrite and (EX/MEM.RegisterRd != 0) 
          and (EX/MEM.RegisterRd == ID/EX.RegisterRt))
          ForwardB = 10
      ```

  - `MEM` hazard

    - ```pseudocode
      if (MEM/WB.RegWrite and (MEM/WB.RegisterRd != 0) 
          and (MEM/WB.RegisterRd == ID/EX.RegisterRs))
          ForwardA = 01
      ```

    - ```pseudocode
      if (MEM/WB.RegWrite and (MEM/WB.RegisterRd != 0) 
          and (MEM/WB.RegisterRd == ID/EX.RegisterRt))
          ForwardB = 01
      ```

- Double Data Hazard

  - Consider the sequence:

    - ```mips
      add $1, $1, $2
      add $1, $1, $3
      add $1, $1, $4
      ```

  - Both hazards occur

    - Want to use the most recent

  - Revise `MEM` hazard condition

    - Only forward if `EX` hazard condition isn't true

- Load-Use Data Hazard

  - Can't always avoid stalls by forwarding

    - If value not computed when needed
    - Can't forward backward in time

  - Load-Use Hazard Detection

    - Check when current instruction is decoded in `ID` stage

    - ALU operand register numbers in `ID` stage are given by:

      - `IF/ID.RegisterRs`, `IF/ID.RegisterRt`

    - Load-use hazard when:

      - ```pseudocode
        ID/EX.MemRead and 
        	((ID/EX.RegisterRt = IF/ID.RegisterRs) or
        	 (ID/EX.RegisterRt = IF.ID.RegisterRt))
        ```

    - If detected, stall and insert bubble

- How to Stall the Pipeline

  - Force control values in `ID/EX` register to `0`
    - `EX`, `MEM`, and `WB` do `nop` (no-operation)
  - Prevent update of `PC` and `IF/ID` register
    - Current instruction is decoded again
    - Following instruction is fetched again
    - 1-cycle stall allows `MEM` to read data for `lw`
      - Can subsequently forward to `EX` stage

- Stalls and Performance

  - Stalls reduce performance, but are required to get correct results
  - Compiler can arrange code to avoid hazards and stalls
    - Requires knowledge of the pipeline structure

- Control Hazards

  - Branch determines flow of control
    - Fetching next instruction depends on branch outcome
    - Pipeline can't always fetch correct instruction
      - Still working on `ID` stage of branch
  - In MIPS pipeline
    - Need to compare registers and compute target early in the pipeline
    - Add hardware to do it in `ID` stage
  - Dealing With Branch Hazards
    - Hardware solutions:
      - Stall until you know which direction branch goes
        - Wait until the branch outcome is decided before fetching the next instruction
      - Guess which direction, start executing chosen path (but be prepared to undo any mistakes)
        - Static branch prediction: base guess on instruction type
        - Dynamic branch prediction: base guess on execution history
        - Longer pipelines can't readily determine branch outcome early
          - Stall penalty becomes unacceptable
        - Predict outcome of branch
          - Only stall if prediction is wrong
          - In MIPS pipeline:
            - Can predict branches not taken
            - Fetch instruction after branch, with no delay
        - More-Realistic Branch Prediction
          - Static branch prediction
            - Based on typical branch behavior
            - Ex) loop and if-statement branches
              - Predict backward branches taken
              - Predict forward branches not taken
          - Dynamic branch prediction
            - Hardware measures actual branch behavior
              - e.g., record recent history of each branch
            - Assume future behavior will continue the trend
              - When wrong, stall while re-fetching, and update history
      - Reduce the branch delay
        - Move hardware to determine outcome to `ID` stage
          - Target address adder
          - Register comparator

- Data Hazards for Branches

  - If a comparison register is a destination of second or third preceding ALU instruction
    - Can resolve using forwarding
  - If a comparison register is a destination of preceding ALU instruction or second preceding load instruction
    - Need 1 stall cycle
  - If a comparison register is a destination of immediately preceding load instruction
    - Need 2 stall cycles

- Dynamic Branch Prediction

  - In deeper and superscalar pipelines, branch penalty is more significant
  - Use dynamic prediction
    - Branch prediction buffer (aka branch history table)
    - Indexed by recent branch instruction addresses
    - Stores outcome (taken/not taken)
    - To execute a branch
      - Check table, expect the same outcome
      - Start fetching from fall-through or target
      - If wrong, flush pipeline and flip prediction
  - 1-Bit Predictor: Shortcoming
    - Inner loop branches mispredicted twice
      - Mispredict as taken on last iteration of inner loop
      - Then mispredict as not taken on first iteration of inner loop next time around
  - 2-Bit Predictor
    - Only change prediction on two successive mispredictions

- Calculating the Branch Target

  - Even with predictor, still need to calculate the target address
    - 1-cycle penalty for a taken branch
  - Branch target buffer
    - Cache of target addresses
    - Indexed by PC when instruction fetched
      - If hit and instruction is branch predicted taken, can fetch target immediately

- Exceptions and Interrupts

  - "Unexpected" events requiring change in flow of control
    - Different ISAs use the terms differently
  - Exception
    - Arises within the CPU
      - e.g., undefined opcode, overflow, syscall, etc.
  - Interrupt
    - From an external I/O controller
  - Dealing with them without sacrificing performance is hard

- Handling Exceptions

  - In MIPS, exceptions managed by a System Control Coprocessor (`CP0`)
  - Save PC of offending (or interrupted) instruction
    - In MIPS: Exception Program Counter (EPC)
  - Save indication of the problem
    - In MIPS: Cause register
    - We'll assume 1-bit
      - `0` for undefined opcode, `1` for overflow
  - Jump to handler at `8000 00180`

- An Alternate Mechanism

  - Vectored Interrupts

    - Handler address determined by the cause

    - Example:

      - ```pseudocode
        Undefined opcode:	 C000 0000
        Overflow:			 C000 0020
        ```

  - Instructions either:

    - Deal with the interrupt
    - Jump to real handler

- Handler Actions

  - Read cause and transfer to relevant handler
  - Determine action required
  - If restartable:
    - Take corrective action
    - Use EPC to return to program
  - Otherwise:
    - Terminate program
    - Report error using EPC, cause, etc.

- Exceptions in a Pipeline

  - Another form of control hazard

  - Consider overflow on add in `EX` stage

    - ```mips
      add $1, $2, $1
      ```

    - Prevent `$1` from being clobbered

    - Complete previous instructions

    - Flush `add` and subsequent instructions

    - Set Cause and EPC register values

    - Transfer control to handler

  - Similar to mispredicted branch

    - Use much of the same hardware

- Exception Properties

  - Restartable exceptions
    - Pipeline can flush the instruction
    - Handler executes, then returns to the instruction
      - Refetched and executed from scratch
  - PC saved in EPC register
    - Identifies causing instruction
    - Actually, `PC + 4` is saved
      - Handler must adjust

- Multiple Exceptions

  - Pipelining overlaps multiple instructions
    - Could have multiple exceptions at once
  - Simple approach: deal with exception from earliest instruction
    - Flush subsequent instructions
    - "Precise" exceptions
  - In complex pipelines:
    - Multiple instructions issued per cycle
    - Out-of-order completion
    - Maintaining precise exceptions is difficult

- Imprecise Exceptions

  - Just stop pipeline and save state
    - Including exceptions cause(s)
  - Let the handler work out:
    - Which instruction(s) had exceptions
    - Which to complete or flush
      - May require "manual" completion
  - Simplifies hardware, but more complex handler software
  - Not feasible for complex multiple-issue out-of-order pipelines



## Pre-Lecture 10: Multiple Issue

- Instruction-Level Parallelism (ILP)

  - Pipelining: executing multiple instructions in parallel
  - To increase ILP:
    - Deeper pipeline
      - Less work per stage => shorter clock cycle

    - Multiple issue
      - Replicate pipeline stages => multiple pipelines
      - Start multiple instructions per clock cycle
      - `CPI < 1`, so use Instructions Per Cycle (IPC)
      - e.g., 4GHz 4-way multiple-issue
        - 16 BIPS, peak `CPI = 0.25`, peak `IPC = 4`

      - But dependencies reduce this in practice
      - Static multiple issue
        - Compiler groups instructions to be issued together
        - Packages them into "issue slots"
        - Compiler detects and avoids hazards

      - Dynamic multiple issue
        - CPU examines instruction stream and chooses instructions to issue each cycle
        - Compiler can help by reordering instructions
        - CPU resolves hazards using advanced techniques at runtime

- Speculation

  - "Guess" what to do with an instruction
    - Start operation as soon as possible
    - Check whether guess was right
      - If so, complete the operation
      - If not, roll back and do the right thing

    - Common to static and dynamic multiple issue
    - Examples:
      - Speculate on branch outcome
        - Roll back if path taken is different

      - Speculate on load
        - Roll back if location is updated

  - Compiler/Hardware Speculation
    - Compiler can reorder instructions
      - e.g., move load before branch
      - Can include "fix-up" instructions to recover from incorrect guess

    - Hardware can look ahead for instructions to execute
      - Buffer results until it determines they are actually needed
      - Flush buffers on incorrect speculation

  - Speculation and Exceptions
    - What if exception occurs on a speculatively executed instruction?
      - e.g., speculative load before null-pointer check
    - Static speculation
      - Can add ISA support for deferring exceptions
    - Dynamic speculation
      - Can buffer exceptions until instruction completion (which may not occur)

- Static Multiple Issue

  - Compiler groups instructions into "issue packets"
    - Group of instructions that can be issued on a single cycle
    - Determined by pipeline resources required

  - Think of an issue packet as a very long instruction
    - Specifies multiple concurrent operations
    - Very Long Instruction Word (VLIW)

  - Scheduling Static Multiple Issue
    - Compiler must resolve some/all hazards
      - Reorder instructions into issue packets
      - No dependencies within a packet
      - Possibly some dependencies between packets
        - Varies between ISAs; compiler must know

      - Pad with `nop` if necessary

- MIPS with Static Dual Issue

  - Two-issue packets
    - One ALU/branch instruction
    - One load/store instruction
    - 64-bit aligned
      - ALU/branch, then load/store
      - Pad an unused instruction with `nop`

  - Hazards in the Dual-Issue MIPS
    - More instructions executing in parallel
    - `EX` data hazard
      - Forwarding avoided stalls with single-issue
      - Now can't use ALU result in load/store in same packet
        - Split into two packets, effectively a stall
    - Load-use hazard
      - Still one cycle use latency, but now 2 instructions
    - More aggressive scheduling required

- Loop Unrolling

  - Replicate loop body to expose more parallelism
    - Reduces loop-control overhead

  - Use different registers per replication
    - Called "register renaming"
    - Avoid loop-carried "anti-dependencies"
      - Store followed by a load of the same register
      - aka "name dependence"
        - Reuse of a register name

- Dynamic Multiple Issue

  - "Superscalar" processors

  - CPU decides whether to issue 0, 1, 2, etc. each cycle

    - Avoiding structural and data hazards

  - Avoids the need for compiler scheduling

    - Though it may still help
    - Code semantics ensured by the CPU

  - Dynamic Pipeline Scheduling

    - Allow the CPU to execute instructions out of order to avoid stalls

      - But commit result to registers in order

    - Example:

      - ```mips
        lw		$t0, 20($s2)
        addu	$t1, $t0, $t2
        sub		$s4, $s4, $t3
        slti	$t5, $s4, 20
        ```

      - Can start `sub` while `addu` is waiting for `lw`

  - Register Renaming

    - Reservation stations and reorder buffer effectively provide register renaming
    - On instruction issue to reservation station

      - If operand is available in register file or reorder buffer:
      - Copied to reservation station
      - No longer required in the register; can be overwritten
      - If operand is not yet available:
        - It will be provided to the reservation station by a function unit
        - Register update may not be required

  - Speculation

    - Predict branch and continue issuing
      - Don't commit until branch outcome determined

    - Load speculation
      - Avoid load and cache miss delay
        - Predict the effective address
        - Predict loaded value
        - Load before completing outstanding stores
        - Bypass stored values to load unit

      - Don't commit load until speculation cleared

  - Why Do Dynamic Scheduling?

    - Why not just let the compiler schedule code?
    - Not all stalls are predictable
      - e.g., cache misses

    - Can't always schedule around branches
      - Branch outcome is dynamically determined

    - Different implementations of an ISA have different latencies and hazards

  - Does Multiple Issue Work?

    - Yes, but not as much as we'd like
    - Programs have real dependencies that limit ILP
    - Some dependencies are hard to eliminate
      - e.g., pointer aliasing
    - Some parallelism is hard to expose
      - Limited window size during instruction issue
    - Memory delays and limited bandwidth
      - Hard to keep pipelines full
    - Speculation can help if done well




## Pre-Lecture 11: Memory Hierarchy

- Memory Technology

  - Static RAM (SRAM)
    - 0.5ns - 2.5ns, $2000 - $5000 per GB

  - Dynamic RAM (DRAM)
    - 50ns - 70ns, $20 - $75 per GB

  - Magnetic disk
    - 5ms - 20ms, $0.20 - $2 per GB

  - Ideal memory
    - Access time of SRAM
    - Capacity and cost/GB of disk

- DRAM Technology

  - Data stores as a charge in a capacitor
    - Single transistor used to access the charge
    - Must periodically be refreshed
      - Read contents and write back
      - Performed on a DRAM "row"

- Flash Storage

  - Nonvolatile semiconductor storage
    - 100x - 1000x faster than disk
    - Smaller, lower power, more robust
    - Higher cost/GB (between disk and DRAM)

- Disk Storage

  - Nonvolatile, rotating magnetic storage

- Principle of Locality

  - Programs access a small proportion of their address space at any time
  - Temporal locality
    - Items accessed recently are likely to be accessed again soon
    - e.g., instructions in a loop, induction variables

  - Spatial locality
    - Items near those accessed recently are likely to be accessed soon
    - e.g., sequential instruction access, array data

  - Taking Advantage of Locality
    - Memory hierarchy
    - Store everything on disk
    - Copy recently accessed (and nearby) items from disk to smaller DRAM memory
      - Main memory

    - Copy more recently accessed (and nearby) items from DRAM to smaller SRAM memory
      - Cache memory attached to CPU

- Memory Hierarchy Levels

  - Block (aka line): unit of copying
    - May be multiple words

  - If accessed data is present in upper level:
    - Hit: access satisfied by upper level
      - Hit ratio: hits/accesses

  - If accessed data is absent:
    - Miss: block copied from lower level
      - Time taken: miss penalty
      - Miss ratio: misses/accesses
        - Equal to `1 - Hit Ratio`

    - Then accessed data supplied from upper level

- Cache Memory

  - Cache memory: the level of the memory hierarchy closest to the CPU

  - Given accesses `X_1, ... , X_n-1, X_n`:

    - How do we know if the data is present?
    - Where do we look?

  - Direct Mapped Cache

    - Location determined by address
    - Direct mapped: only one choice
      - `Block address % # blocks in cache`
      - `# blocks in cache` is a power of 2
      - Use low-order address bits

  - Tags and Valid Bits

    - How do we know which particular block is stored in a cache location?
      - Store block address as well as the data
      - Actually, only need the high-order bits
      - Called the tag

    - What if there is no data in a location?
      - Valid bit: `1` means data is present, `0` means data is not present
      - Initially `0`

  - Block Size Considerations

    - Larger blocks should reduce miss rate due to spatial locality
    - But in a fixed-size cache:

      - Larger blocks => fewer blocks
        - More competition => increased miss rate

      - Larger blocks => pollution

    - Larger miss penalty
      - Can override benefit of reduced miss rate
      - Early restart and critical-word-first can help

  - Cache Misses

    - On cache hit, CPU proceeds normally
    - On cache miss:
      - Stall the CPU pipeline
      - Fetch block from next level of hierarchy
      - Instruction cache miss:
        - Restart instruction fetch

      - Data cache miss:
        - Complete data access

  - Write-Through

    - On data-write hit, could just update the block in cache
      - But then cache and memory would be inconsistent

    - Write-through: also update memory
    - But makes writes take longer
      - e.g., assume base CPI is `1`, 10% of instructions are stores, write to memory takes 100 cycles
        - Effective CPI = `1 + 0.1 × 100 = 11`

    - Solution: write buffer
      - Holds data waiting to be written to memory
      - CPU continues immediately
        - Only stalls on writes if write buffer is already full

  - Write-Back

    - Alternative: on data-write hit, just update the block in cache
      - Keep track of whether each block is dirty

    - When a dirty block is replaced
      - Write it back to memory
      - Can use a write buffer to allow replacing block to be read first

  - Write Allocation

    - What should happen on a write miss?
    - Alternatives for write-through:
      - Allocate on miss: fetch the blcok
      - Write around: don't fetch the blcok
        - Since programs often write a whole block before reading it (e.g., initialization)

    - For write-back:
      - Usually fetch the block

  - Measuring Cache Performance

    - Components of CPU time

      - Program execution cycles
        - Includes cache hit time

      - Memory stall cycles
        - Mainly from cache misses

    - With simplifying assumptions:

      - $$
        \text{Memory stall cycles}=\frac{\text{Memory accesses}}{\text{Program}}\times\text{Miss rate}\times{\text{Miss penalty}}\\
        =\frac{\text{Instructions}}{\text{Program}}\times\frac{\text{Misses}}{\text{Instruction}}\times\text{Miss penalty}
        $$

    - Example:

      - Given:
        - I-cache miss rate = 2%
        - D-cache miss rate = 4%
        - Miss penalty = 100 cycles
        - Base CPI (ideal cache) = 2
        - Load and stores are 36% of instructions

      - Miss cycles per instruction:
        - I-cache: `0.02 × 100 = 2`
        - D-cache: `0.36 × 0.04 × 100 = 1.44`

      - `Actual CPI = 2 + 2 + 1.44 = 5.44`
        - Ideal CPU is `5.44 / 2 = 2.72` times faster

  - Average Access Time

    - Hit time is also important for performance

    - Average memory access time (AMAT)

      - $$
        \text{AMAT}=\text{Hit time}\times\text{Miss rate}\times\text{Miss penalty}
        $$

    - Example:

      - Given:
        - CPU is 1ns clock
        - Hit time = 1 cycle
        - Miss penalty = 20 cycles
        - I-cache miss rate = 5%

      - `AMAT = 1 + 0.05 × 20 = 2ns`
        - 2 cycles per instruction

  - Performance Summary

    - When CPU performance increases, miss penalty becomes more significant
    - Decreasing base CPI results in a greater proportion of time spent on memory stalls
    - Increasing clock rate results in memory stalls accounting for more CPU cycles
    - Can't neglect cache behavior when evaluating system performance

  - Associative Caches

    - Fully associative
      - Allow a given block to go in any cache entry
      - Requires all entries to be searched at once
      - Comparator per entry (expensive)

    - `n`-way set associative
      - Each set contains `n` entries
      - Block number determines which set
        - `Block number % # of sets in cache`

      - Search all entries in a given set at once
      - `n` comparators (less expensive)

    - How Much Associativity?
      - Increased associativity decreases miss rate, but with diminishing returns

  - Replacement Policy

    - Direct mapped: no choice
    - Set associative
      - Prefer non-valid entry, if there is one
      - Otherwise, choose among entries in the set

    - Least-recently used (LRU)
      - Choose the one unused for the longest time
        - Simple for 2-way, manageable for 4-way, too hard beyond that

    - Random
      - Gives approximately the same performance as LRU for high associativity

  - Multilevel Caches

    - Primary cache attached to CPU
      - Small, but fast

    - Level-2 cache services misses from primary cache
      - Larger, slower, but still faster than main memory

    - Main memory services L-2 cache misses
    - Some high-end systems include L-3 cache
    - Example:
      - Given:
        - CPU base CPI = 1
        - Clock rate = 4GHz
        - Miss rate per instruction = 2%
        - Main memory access time = 100ns

      - With just primary cache:
        - `Miss penalty = 100ns / 0.25ns = 400 cycles`
        - `Effective CPI = 1 + 0.02 × 400 = 9`

      - Now add an L-2 cache:
        - Access time = 5ns
        - Miss rate = 10%

      - Primary miss with L-2 hit:
        - `Penalty = 5ns / 0.25ns = 20 cycles`

      - Primary miss with L-2 miss:
        - `Extra penalty = 400 cycles`

      - `CPI = 1 + 0.02 × (20 + 0.10 × 400) = 2.2`
      - Performance ration: `9 / 2.2 = 4.1`

    - Multilevel Cache Considerations
      - Primary cache
        - Focus on minimal hit time

      - L-2 cache
        - Focus on low miss rate to avoid main memory access
        - Hit time has less overall impact

      - Results:
        - L-1 cache usually smaller than a single cache
        - L-1 block size smaller than L-2 block size

  - Interactions with Advanced CPUs

    - Out-of-order CPUs can execute instructions during cache miss
      - Pending store stays in load/store unit
      - Dependent instructions wait in reservation stations
        - Independent instructions continue

    - Effect of miss depends on program data flow
      - Much harder to analyze
      - Use system simulation

  - Interactions with Software

    - Misses depend on memory access patterns
      - Algorithm behavior
      - Compiler optimization for memory access

- The Memory Hierarchy

  - Common principles apply at all levels of the memory hierarchy

    - Based on notions of caching

  - At each level in the hierarchy:

    - Block placement
    - Finding a block
    - Replacement on a miss
    - Write policy

  - Block Placement

    - Determined by associativity
      - Direct mapped (1-way associative)
        - One choice for placement

      - `n`-way set associative
        - `n` choices within a set

      - Fully associative
        - Any location

    - Higher associativity reduces miss rate
      - Increases complexity, cost, and access time

  - Finding a Block

    - | Associativity           | Location Method                               | Tag Comparisons |
      | ----------------------- | --------------------------------------------- | --------------- |
      | Direct Mapped           | Index                                         | 1               |
      | `n`-way Set Associative | Set index, then search entries within the set | `n`             |
      | Fully Associative       | Search all entries                            | # of entries    |
      | Fully Associative       | Full lookup table                             | 0               |

    - Hardware caches

      - Reduce comparisons to reduce cost

    - Virtual memory

      - Full table lookup makes full associativity feasible
      - Benefit in reduced miss rate

  - Replacement on a Miss

    - Choice of entry to replace on a miss
      - Least recently used (LRU)
        - Complex and costly hardware for high associativity

      - Random
        - Close to LRU, easier to implement

    - Virtual memory
      - LRU approximation with hardware support

  - Write Policy

    - Write-through
      - Update both upper and lower levels
      - Simplifies replacement, but may require write buffer

    - Write-back
      - Update upper level only
      - Update lower level when block is replaced
      - Need to keep more state

    - Virtual memory
      - Only write-back is feasible, given disk write latency

  - Sources of Misses

    - Compulsory misses (aka cold start misses)
      - First access to a block

    - Capacity misses
      - Due to finite cache size
      - A replaced block is later accessed again

    - Conflict misses (aka collision misses)
      - In a non-fully associative cache
      - Due to competition for entries in a set
      - Would not occur in a fully associative cache of the same total size

  - Cache Design Trade-offs

    - | Design Change          | Effect on Miss Rate        | Negative Performance Effect                                  |
      | ---------------------- | -------------------------- | ------------------------------------------------------------ |
      | Increase cache size    | Decrease capacity misses   | May increase access time                                     |
      | Increase associativity | Decrease conflict misses   | May increase access time                                     |
      | Increase block size    | Decrease compulsory misses | Increases miss penalty; for very large block size, may increase miss rate due to pollution |

- Concluding Remarks

  - Fast memories are small, large memories are slow
    - We really want fast, large memories
    - Caching gives this illusion

  - Principle of locality
    - Programs use a small part of their memory space frequently

  - Memory hierarchy
    - L1 cache <=> L2 cache <=> ... <=> DRAM memory <=> disk

  - Memory system design is critical for multiprocessors




## Pre-Lecture 12:

- 

