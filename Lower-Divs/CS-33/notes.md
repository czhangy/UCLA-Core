# COM SCI 33 - Spring '20 - Reinman



[TOC]

## **Lecture 1: Bits and Bytes**

- Pre-processor -> compiler -> assembler -> linker
  - Text to binary through assembler
  - Assembler is machine specific
    - On a binary level, program is run for a particular machine architecture
- Hex - denoted by `0x` preceding hex number
- Left shift - shift bit vector left, fill with `0`s
- Right shift
  - Arithmetic - shift bit vector right, replicate most significant digit
  - Logical - shift bit vector right, fill with `0`s

## **Lecture 2: Integers**

- Encoding integers

  - Unsigned:
    - $$
    B2U(x) = \sum^w_{i=0}x_i\cdot2^i
    $$
  - Two's Complement:
    - $$
    -x_{w-1}\cdot 2^{w-1}+\sum^w_{i=0}x_i\cdot 2^i
    $$

      - Most significant bit indicates sign

  - | Binary | Unsigned | Two's Complement |
    | :----: | :------: | :--------------: |
    |  0000  |    0     |        0         |
    |  0001  |    1     |        1         |
    |  0010  |    2     |        2         |
    |  0011  |    3     |        3         |
    |  ...   |   ...    |       ...        |
    |  0111  |    7     |        7         |
    |  1000  |    8     |        -8        |
    |  ...   |   ...    |       ...        |
    |  1111  |    15    |        -1        |

  - Maxes/Mins

    - $$
      |{T_{min}}| = T_{max} + 1
      $$

      - Asymmetric range

    - $$
      U_{max} = 2 \times T_{max} + 1
      $$

    - `#include <limits.h>` for C programming

      - Constants: `ULONG_MAX`, `LONG_MAX`, `LONG_MIN`

  - Word size - size used for pointers (i.e. 64-bit machine encodes pointers as 64 bits)

  - Casting

    - Signed values implicitly cast to unsigned
      - `-1 > 0U` - unsigned is `U_max`
      - `2147483647U < -2147483647 - 1` - `011...111 < 11...110`
      - `(unsigned) - 1 > -2`
      - `2147483647 < 2147483648U` - `T_max < T_max + 1`
      - `2147483647 > (int) 2147483648U`

## **Lecture 3: Machine-Level Programming: Basics**

- CPU puts addresses into memory

  - Memory returns data/instructions

- Register is part of CPU

  - Faster than memory (SRAM vs. DRAM)
  - Compiler-visible like memory

- PC - program counter - tells us what instruction is being executed

- Registers and memory together hold the state of the program

- Memory is byte-addressable

- x86-64 has 16 integer registers

  - `%rax` has 64 bits
    - Contains `%eax` - lower 32 bits can reference individually
    - Can reference lower, but not upper
  - `%rsp` points to the current location in memory where the stack is
  - Memory is contiguous in each register file

- Moving Data

  - `movq` - copies from source -> destination
    - Operand can be 1 of 3 types:
      - Immediate - constant integer data
        - Ex) `$0x400`, `$-533`
      - Register - one of 16 integer registers
        - Ex) `%rax`, `%r13` -> location, not value
      - Memory - 8 bytes of memory at address given by register
        - Ex) `(%rax)` -> pointer for `movq` instruction (dereference)
    - Immediate -> Register: `movq $0x4, %rax` -> `temp = 0x4`
    - Immediate -> Memory: `movq $-147, (%rax)` -> `*p = -147`
    - Register -> Register: `movq %rax, %rdx` -> `temp2 = temp1`
    - Register -> Memory: `movq %rax, (%rdx)` -> `*p = temp`
    - Memory -> Register: `movq (%rax), %rdx` -> `temp = *p`
      - Memory denoted with parentheses

- Complete Memory Addressing Modes
  - $$
    D(Rb, Ri, S) = Mem[Reg(Rb) + S\times Reg(Ri) + D]
    $$

    - Ex) `8(%rax, %rdx, 2)` -> accesses `%rax + 2 * %rdx + 8` location in memory

- Address Computation Instruction
  - `leaq` -> doesn't dereference, doesn't go into memory
    - Setting up an address (finding a pointer)
    - `leaq (%rax), %rdx` vs. `movq (%rax), %rdx`
      - `leaq (%rax), %rdx)` = `movq %rax, %rdx`
    - `leaq (%rax, %rbx), %rdx` -> adds `%rax` and `%rbx` and writes it to `%rdx`
  - Useful for 2 address code (an address is an input and output)

## **Lecture 4: Machine-Level Programming: Control**

- Condition codes: 1-bit registers

  - `CF` - carry flag (unsigned)
  - `ZF` - zero flag
  - `SF` - sign flag (signed)
  - `OF` - overflow flag (signed)
    - Ex) Using `addq`: `t = a + b`
      - `CF` set if MSB carried out
      - `ZF` set if `t == 0`
      - `SF` set if `t < 0` (set if signed or unsigned)
      - `OF` set if 2s complement overflow (set if signed or unsigned, set with `CF`)
    - Not set by `leaq`

- `cmpq` instruction `(Src2, Src1) -> (Src1 - Src2)`

  - Performs subtraction without setting destination
    - Saves register space when performing comparisons
    - `CF` - carry out, `ZF` - `a == b`, `SF` - `(a - b) < 0`, `OF` - 2s complement overflow

- Jumping - jump to different parts of code depending on condition codes

  - Can be set explicitly (`cmpq`) or implicitly (arithmetic)
  - Modifies `%rip`, which points to current instruction (instruction pointer)
  - `jmp` - unconditional jump
  - Rest of instructions are conditional
    - Ex) `je`/`jne` - jumps if equal/zero or not equal/nonzero
    - Ex) `ja`/`jb` - unsigned
      - Check if `< 0` or `> 10` -> can use `ja` -> all negative values interpreted as `> 10`
  - Linker replaces labels with memory addresses for jumping

- Conditional move: using more registers, allows us to avoid control flow issues

  - Ex)

    - ```c++
      if (x < y)
          return x - y;
      else
          return y - x;
      ```

      - Writes both results into registers before evaluating condition
      - Decides which to return based on condition

  - Compiler stores alternatives that will be performed to be returned/selected later

  - `cmov` - conditional move instruction

  - Bad when expensive (hard evaluations), risky (dereferencing), side effects present (value modification)

- All loops can generally be modified to the same structure

  - Do while:

    - ```assembly
      .L2:
        movq %rdi, %rdx -> %rdi is x
        andl   $1, %edx -> %edx is either 0 or 1
        addq %rdx, %rax
        shrq     %rdi -> sets ZF when x = 0, x >>= 1
        jne       .L2
        rep; ret
      ```

  - Switch:

    - ```c++
      case 100:
        i++;
        j++;
        break;
      case 102:
        i += 2;
        j += 2;
        break;
      case 103: // fall through
        i++;
      case 104:
        j += 2;
        break;
      case 106:
        i += 2;
        j++;
        break;
      default:
        i = 0;
        j = 0;
      ```

      - Jump table  (values close together
        - One jump instruction sends the `%rip` to find the correct memory address
        - Cases merge back to the `break`

- Direct jump - `jbe` -> to a location

- Indirect jump - `jmpq *(ADDR)` -> used in the jump table

## **Lecture 5: Machine-Level Programming: Procedures**

- The stack grows down in addresses (`FFF` -> `000`)

  - `%rsp` points to the top of the stack (lowest address)
  - All programs have their own stack/heap -> virtual memory

- Ex)

  - ```assembly
    400500 <multstore>:
    ...
    400544: callq 400550<mult2>
    400549:   mov %rax, (%rbx)
    ...
    400550 <mult2>:
    400550:   mov %rdi, %rax
    ...
    400557: retq
    ```

  - `%rip` increments with the instruction addresses

    - Naturally goes to the next instruction
      - Changes with jumps, `callq`, etc.

  - `callq` leaves the original caller's memory address on the stack and changes `%rip` to the new instruction address

  - `retq` -> `pop` + `jmp` -> consumes data in the stack, changes `%rip` back to caller's address

    - Uses the `%rsp` to locate the caller's address

- Procedure Data Flow

  - 1st 6 arguments stored in registers
    - `%rdi`, `%rsi`, `%rdx`, `%rcx`, `%r8`, `%r9`
  - 7+ arguments placed on stack

- x86-64/Linux Stack Frame

  - Frame - data of some function call
    - Arguments (if 7+), return address -> callee frame
      - Callee frame: registers + variables, argument build (if caller of another function)

- Register Saving Conventions

  - Caller saved - temporary values saved in frame before call
  - Callee saved - temporary values saved in frame after call, before using
    - Restored by callee before returning to caller

- x86-64 Linux Register Usage

  - `%rax` -> return value
    - Caller saved, can be modified by procedure
  - `%rdi`, `%rsi`, `%rdx`, `%rcx`, `%r8`, `%r9` -> arguments
    - Caller saved, can be modified by procedure
  - `%r10`, `%r11`
    - Caller saved
  - `%rbx`, `%r12`, `%r13`, `%r14`
    - Callee saved
  - `%rbp`
    - Callee saved, may be used as a frame pointer
  - `%rsp`
    - Special form of callee save, stack pointer

## **Lecture 6: Machine-Level Programming: Data**

- Multidimensional arrays

  - Declaration: `T A[R][C]`
    - 2D array of type `T`
    - `R` rows, `C` columns
    - Type `T` element requires `K` bytes
  - Array size: `R * C * K` bytes
  - Arrangement: row-major ordering

- Multi-level array

  - Array with a first array that contains pointers to secondary arrays
  - More flexible, more complex
  - Can have varying lengths at each unit

- Machine-level translation

  - Fixed-size -> `C = 16, K = 4` -> `A + i * (16 * K) + j + K`

    - `i * (16 * K)` positions which nested array

    - `j * K` positions inside the nested array

    - `a` in `%rdi`, `i` in `%rsi`, `j` in `%rdx`

    - ```assembly
      salq $6, %rsi -> 64 * i
      addq %rsi, %rdi -> a + 64 * i
      movl (%rdi, %rdx, 4), %eax -> M[a + 64 * i + 4 * j]
      ret
      ```

  - Dynamic -> `C = n, K = 4` -> `A + i * (C * K) + j * K`

    - Must use multiplication rather than shifts

    - `n` in `%rdi`, `a` in `%rsi`, `i` in `%rdx`, `j` in `%rcx`

    - ```assembly
      imulq %rdx, %rdi -> n * i
      leaq (%rsi, %rdi, 4), %rax -> a + 4 * n * i
      movl (%rax, %rcx, 4), %rax -> a + 4 * n * i + 4 * j
      ret
      ```

- Structs

  - Must satisfy alignment requirement `K` = largest alignment of any element

    - Prevents overlapping of blocks/pages/etc.

  - ```c++
    struct S1 {
      char c;
      int i[2];
      double v;
    }
    ```

## **Lecture 7: Floating Points**

- Tiny FP example (8 bits)
  - The sign is the MSB
  - Next 4 bits are the exponent -> bias of 7 -> `2^n-1 - 1`
  - The last 3 bits are the `frac`
  - Normalized: `(-1)^s 1.frac * 2^E`
    - `E = exp - bias`
    - `exp != 000...0`, `exp != 111...1`
  - Denormalized: `exp = 000...0`
    - `E = 1 - bias`, `M = 0.frac`
  - Infinity: `exp = 111...1`, `frac = 0`
  - NaN: `exp = 111...1`, `frac != 0`
    - Instead of overflow, floating point arithmetic saturates
- `x != (int) (float) x` -> `float` doesn't have enough precision
- `x == (int) (double) x`
- `f == (float) (double) f`
- `d != (double) (float) d`
- `f == -(-f)` -> float doesn't have the asymmetry of `int`
- `2/3 != 2/3.0`
- `d <  0.0 => ((d * 2) < 0.0)` -> no overflow concerns
- `d < f => -f > -d`
- `d * d >= 0.0` -> no overflow concerns
- `(d + f) - d != f` -> potential for not enough precision, `f` rounded away

## **Lecture 8: Optimization**

- The compiler has to be conservative
  - Branching can block optimization -> not sure if code is actually executed
  - Storing to memory can block optimization -> memory alteration
  - Functions can block memory
    - Inlining can help, but you lose access to interposition (updates with DLLs without recompiling)
    - Interposition leaves a gap in the code assembly
    - The compiler cannot assume the function doesn't modify memory
- Simple optimizations: code motion, strength reduction, subexpressions
- Memory conflicts: aliasing
  - No guarantee that 2 references to memory don't overlap -> cannot optimize
  - Introducing local variables -> tells compiler to not check for aliasing

- Architecture
  - Processor can execute instructions in different order than compiler, must affect architectural units in correct order
    - Improves performance, reordered at end by retirement unit
  - Hardware does a lot of operation
  - Multiple functional units -> instruction-level parallelism
    - Computations may not be done, but the pipeline has an open slot
    - Computation divided into stages, independent computations can be passed from stage to stage
    - Latency bound vs. throughput bound -> time vs. number of tasks
    - A straight-line chain of computation is not optimal
- SIMD - Single Instruction Multiple Data
  - Vector elements -> vector registers -> hold multiple values
- Branch prediction - attempt to predict on branching, penalty when wrong prediction
  - Must flush pipeline if wrong, high cycle cost
  - Predictable branches have lower overhead

## **Lecture 9: Memory Hierarchy**

- CPU sends an address out, receives data/instructions from memory
  - Transistors scale well, memory wall means memory access doesn't
    - CPU can only be as fast as its ability to access memory
    - Bound by memory
- SRAM - Static Random Access Memory -> registers, caches, etc.
  - Fast to access, hard to have high capacity
- DRAM - Dynamic Random Access Memory -> main memory
  - Slower to access, higher capacity
- I/O bus:
  - Non-volatile storage: disks, USB drive, etc.
    - CPU request to disk, disk stored in main memory (DMA), CPU notified by interrupt
- Costs: area, material, power, monetary, etc.
- Locality: programs tend to use data and instructions with addresses near those they have used recently
  - Temporal: recently referenced items are likely to be referenced again in the near future (loop with iterator)
  - Spatial: items with nearby addresses tend to be referenced close together (arrays and structs)
- General Cache Concepts
  - Cache - smaller, faster, more expensive memory catches a subset of blocks transferred from main memory
    - Brings reused data in to lower latency of common accesses
    - Blocks may contain larger granularity than necessary
      - Why padding is necessary, takes advantage of spatial locality
    - Decisions based on cache policy combined with memory stream (eviction)
- Prefetching - attempt to access data ahead of time
  - Further ahead of time -> lower latency, balance with pollution of storage

## **Lecture 10: Memory and Parallelism**

- Matrix Multiplication:

  - 1st method: `k` in innermost loop
    - Row order with `i` -> 0.25 misses/iteration
    - Column order with `j` -> 1 miss/iteration
  - 2nd method: `j` in innermost loop
    - Row order with `B` and `C` -> 0.25 misses/iteration
    - More operations, better locality
  - 3rd method: `i` in innermost loop
    - Worst, `A` and `C` miss every iteration

- Blocked Matrix Multiplication

  - Constrains matrix to work in smaller matrices
    - Multiple rows/columns per block
    - Constraining amount of data accessed -> can control how much data the cache deals with
    - Can be worse due to time complexity/branching

- Cache Miss Analysis

  - Assume a block contains 8 `double`s, `c << n`, 3 blocks into cache `3B^2 < C`

    - `B^2/8` misses for each block
    - $$
      \frac{2n}{B} \times \frac{B^2}{8} = n\frac{B}{4}
      $$

- MIMD

  - Multi-core -> simultaneous execution when data sharing is unnecessary
  - Cooperative multithreading -> separate execution, but sharing of same data

## **Lecture 11: Parallelism: Part 1**

- Ideally parallel latency = `latency / 4`

  - Sometimes less performance
    - Overhead -> communication between cores/OS interaction
    - ILP -> may not be much parallelism in task
    - Load balancing -> work can't be distributed evenly
  - Sometimes more performance
    - Memory-bound applications can get much better memory locality by distributing across more caches
  - Balance computation vs. communication

- Work sharing

  - `for`:

    - ```c++
      #pragma omp parallel
      // Other code
      #pragma omp for
      for (i = 0; i < 10000; i++) // parallelize
      ```

      - Static - tasks split, no further communication/load balancing
      - Dynamic - requests more work when done with work
        - Much more overhead due to communication
      - Guided - start off with large chunks of work distributed and size decreases logarithmically
      - Cannot have `break`s - OpenMP must know at runtime how many iterations the loop will take

  - `single`:

    - Communicates that a piece of code is only to be done by 1 thread

  - Critical sections - only 1 thread can access this at a time -> sequential

    - A lot of overhead in creating this region

  - `reduction`

    - Specifies associative operator and the variable
    - Private variable created in each thread, after running, the associative operator is used on the variables to combine

- Deadlock - mutually exclusive resources access, threads hold resources until they have what they want, resources cannot be taken away, cyclical

## **Lecture 12: Parallelism: Part 2**

- 2 types of parallelism
  - Data - implicit parallelism inside data itself
  - Task - specialization of task across cores
    - Executes different things on each task
- OpenMP Tasks - independent units of work
  - Composed of code, data, and internal control variables
  - Threads perform the work of each task
  - Runtime system decides execution -> may be deferred, or executed immediately
    - Guaranteed completion at barriers
      - `barrier` -> thread barrier
      - `taskwait` -> task barrier
- Scope - variables are default private in a task
  - `shared` -> makes variables shared between threads
  - `firstprivate` -> make sure variable is private/has the correct value
- OpenMP memory model
  - Supports a shared memory model -> threads share an address space
  - Defined by
    - Coherence - behavior when single address is accessed by multiple threads
    - Consistency - orderings of reads, writes, syncs with various addresses and multiple threads
      - Weak consistency -> can't reorder sync operations with read or write operations

## **Lecture 13: Exceptional Control Flow and Linking**

- Synchronous Exceptions
  - Traps
    - Intentional - part of the actual code
    - System calls, breakpoint traps, special instructions
    - Returns control to next instruction
  - Fault
    - Unintentional but possibly recoverable
    - Page faults, protection faults, floating-point exceptions
    - Either re-executes faulting instruction or aborts
  - Aborts
    - Unintentional and unrecoverable
    - illegal instruction, parity error, machine check
    - Aborts current program
- Page Faults
  - User writes to memory location, which is currently on disk
    - OS copies page from disk to memory
- Invalid Memory Reference - fault
  - Starts with page fault, OS detects invalid address, signals the process
    - Sends `SIGSEGV`, program exits with segmentation fault
- System Calls - trap
  - Each x86-64 system call has a unique ID
  - OS needs to intervene (read, write, open, etc.)
  - Sends exception with ID in `%eax`, performs the specified instruction, returns with status of exception
- Compilation
  - `cpp` - preprocessor -> `#define`, `#pragma` -> injects source code
  - Compiler - parses -> forms an intermediate representation of source code across different languages and optimizes code
  - Assembler - change into binary
    - Multiple object files, may have unresolved symbols, incomplete view of memory layout
  - Linker - resolves clause issues
- Creating a library
  - Put all functions in a single source file - space/time inefficient
  - Put each function in a separate source file - burdensome on programmer
    - Related object files into a single archive file, linker searches through `.a` for symbols

## **Lecture 14: Virtual Memory**

- Program accesses memory with an address, the memory returns data to the program
  - This model cannot handle simultaneous, independently compiled programs
    - Wastes memory, must account for all possible combinations
  - Virtual memory: program sends virtual address to the Memory Management Unit, which sends the physical address to memory
    - Applications have own view of memory, translated into single set of main memory
    - Excess memory not in DRAM, in disk instead -> exploit locality
- Page Table - takes VA, translates into PA -> dynamic by necessity
  - Resides in physical memory - may not fit in memory as a whole
    - Communication between VM and MM done in pages
    - Relatively high access cost -> common swaps = thrashing
  - A page table register per process
    - Can protect from duplicate addresses across processes or allow sharing
  - Page table start denoted by page table base register (PTBR)
  - Each entry has a valid bit that tells if the entry is in physical memory
    - Accessing an entry with an invalid bit results in a page fault -> evicts old page from memory and replaces with requested page
      - Behavior is non-deterministic
  - Dirty page - page in memory doesn't match page on disk -> consistency
  - Breakdown of address
    - Page offset - index within page -> unchanged between VA and PA
    - Page number - specifies which page in VM is translated into MM
- TLB - Translation Lookaside Buffer
  - Hardware structure acts as a cache for the page table
  - Takes you to physical address directly

- Multi-level Page Tables
  - Level 1 - each PTE points to a page table
    - Allows for only part of page table in DRAM
    - More loads -> less sever if good locality
- Balancing page size, spatial locality, and performance

## **Lecture 15: MIPS**

- CISC vs. RISC
  - CISC motivated by capacity of memory limitations
    - Complex instructions -> memory addressing mode
    - Memory access or register address -> all in 1 instruction = compact
    - Small number of registers
    - Variable length instructions
    - Difficult to decode/pipeline/implement
  - Compilers becoming more powerful, complexity rising -> move to RISC
    - Simpler instructions, fixed length
      - Wastes space, simplifies decoding
  - Boundaries blurred to allow both architectures to coexist
- MIPS
  - Fixed length - 32 bits
    - R type - register specifiers (`Rs`, `Rt`, `Rd`) -> 5 bit, ALU-oriented
      - 32 registers
      - `dest`, `src`
    - I type - load word and store word -> data transfer
      - load = memory -> register, store = register -> memory
      - `LW $t0, 4($s0)` -> `R[$t0] ,- M[R[$s0] + 4]`
        - Base (register) + displacement (immediate)
    - J type - jump (`j`) and jump and link (`jnl`)
      - `j` changes the PC
      - `jnl` is like a `callq` -> `$RA` set to PC + 4, PC to new PC
        - Nested calls -> `$RA` saved on the stack

## **Lecture 16: MIPS**

- Pseudoinstructions
  - Translated into other machine instructions
  - `move` -> `move $t, $s` -> `addiu $t, $s, 0`
  - `clear` -> `clear $t` -> `addu $t, $zero, $zero`
  - Load 16-bit immediate -> `li $t, C` -> `addiu $t, $zero, C_lo`
  - Load 32-bit immediate -> `li $t, C` -> `lui $t, C_hi; ori $t, $t, C_lo`
  - Load label address -> `la $t, A` -> `lui $t, A_hi; ori $t, $t, A_lo`
    - Instructions have 6 bits for op-code, 5 for each register -> only 16 to hold immediate -> must separate `C_hi` and `C_lo`
- System calls - traps are recoverable and intentional
  - Application trying to perform I/O that requires communication with OS -> `syscall`
  - Passes a code as a parameter to identify the specific `syscall` -> `$V0`
    - Switch statement-esque
- `$a0` and `$a1` hold parameters
