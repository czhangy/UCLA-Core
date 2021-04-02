# COM SCI 111 - Spring '21 - Eyolfson



[TOC]

## Lecture 1: Expectations and Overview

- An OS sits between applications and hardware
  - The primary role of an OS is to manage and coordinate resources
- Ubuntu and Android are considered different OSes
  - Both use a Linux kernel, but they run different applications
  - There isn't a clear line, especially with Linux
  - For desktop applications (using a GUI), you'd draw the line at the Display System
  - Linux uses Wayland, and Android uses SurfaceFlinger
- OSes allow running more than 1 application
  - Without an OS, a CPU start executing code at a fixed address
  - You could put your application here, but it would be the only one
  - You would have to handle specific hardware in your application
  - Instead, we start executing an OS at boot
- Our first abstraction is a process
  - Each process contains its own set of registers, including the program counter
  - When starting a process, it specifies where the CPU should start executing
  - The OS has to:
    - Keep track of registers for each process
    - Switch between different processes
    - Decide when to switch between processes
- We could put applications in different parts of memory
  - This isn't very flexible
- Virtualization fools something into thinking it has all resources in a system
- Virtual memory abstracts away physical memory
  - Each process believes it has access to all the memory
  - Different processes can have the same starting address
  - The OS has to:
    - Map VM access to PM
    - Keep track of memory usage (allocate and deallocate)
    - Handle out-of-memory scenarios
      - Swap file
      - Out-of-memory killer
- Virtualization is a powerful concept
  - Applies to both processes and VM
  - We can extend this to an entire machine
  - A single PM can run multiple OSes at once
- Concurrency is multiple things happening at the same time
  - We want multiple applications running at once
    - The application is binary, purely static
    - A process is the application while its running
  - We want applications to do multiple things at once
  - We don't want applications isolated
  - We want applications and libraries to communicate
    - Otherwise, the application is useless
- Concurrency is necessary for OSes
  - Running 1 application at a time isn't a good experience
  - Completely isolate applications aren't useful
    - The simplest applications still communicate with the terminal
  - The OS has to:
    - Allow multiple executions at once, safely
      - One application shouldn't be able to impact another, unless intended
    - Manage abstractions for different kinds of inter-process communication (IPC)
    - Provide permission checking and access control
- Finally, we need persistence for a basic OS
  - We want to be able to access data between boots
  - A file system specifies how to organize data on a storage medium
  - The OS has to:
    - Store and retrieve data
    - Ensure integrity of data
- File descriptors abstract both communication and persistence
  - A file descriptor is just a number identifier (per process) that you can:
    - Read bytes from
    - Write bytes to
  - The OS can direct the bytes to whatever it represents
  - You could imagine it representing a file, or one side of communication
- Security is another consideration
  - We want our computers to only do what we tell them to
  - The OS has to:
    - Encrypt sensitive data
    - Prevent bypassing access control
    - Only execute applications the user wants
- Most kernel code is device drivers
  - Device drivers implement the abstractions we'll learn to the physical hardware
  - It involves reading manufacturer specifications and finding bugs
  - Sometimes there's inconsistencies between documentation and reality
- There are 4 major concepts in this course:
  - Virtualization
  - Concurrency
  - Persistence
  - Security



## Lecture 2: Interfaces and Libraries

- Interfaces

  - CPUs have "rings" to control instruction access

    - Hypervisor (Ring -1), Supervisor/Kernel (Ring 0), User (Ring 3)
    - Each ring can access instruction in any of its outer rings

  - The kernel of the OS runs in kernel mode

  - System calls (352 total) transition between user and kernel mode

    - Interfacing to hardware

  - A monolithic kernel runs OS services in kernel mode

  - A microkernel runs the minimum amount of services in kernel mode

    - Pros: security => crashing can avoid kernel crashes
    - Cons: slower => overhead from crossing boundary between user and kernel space

  - Other types of kernels

    - "Hybrid" kernels are between monolithic and microkernels
      - Emulation services to user mode (Windows)
      - Device drivers to user mode (macOS)
    - Nanokernels and picokernels
      - Move even more into user mode than traditional microkernels
    - There's many different lines you can draw with different trade-offs

  - Executing a 178 byte `Hello World` on Linux x86-64

    - ```assembly
      0x7F 0x45 0x4C 0x46 0x02 0x01 0x01 0x03 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x02 0x00 0x3E 0x00 0x01 0x00 0x00 0x00
      0x78 0x00 0x01 0x00 0x00 0x00 0x00 0x00 0x40 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00
      0x00 0x00 0x00 0x00 0x40 0x00 0x38 0x00 0x01 0x00 0x40 0x00 0x00 0x00 0x00 0x00 0x01 0x00 0x00 0x00 0x05 0x00 0x00 0x00
      0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x01 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x01 0x00 0x00 0x00 0x00 0x00
      0xB2 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0xB2 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x01 0x00 0x00 0x00 0x00 0x00 0x00
      0x48 0xC7 0xC0 0x01 0x00 0x00 0x00 0x48 0xC7 0xC7 0x01 0x00 0x00 0x00 0x48 0xC7 0xC6 0xA6 0x00 0x01 0x00 0x48 0xC7 0xC2
      0x0C 0x00 0x00 0x00 0x0F 0x05 0x48 0xC7 0xC0 0xE7 0x00 0x00 0x00 0x48 0xC7 0xC7 0x00 0x00 0x00 0x00 0x0F 0x05 0x48 0x65
      0x6C 0x6C 0x6F 0x20 0x77 0x6F 0x72 0x6C 0x64 0x0A
      ```

    - ELF is the binary format for Unix OSes

      - Executable and Linkable Format (ELF) is a file format
      - Always starts with the 4 bytes: `0x7f 0x45 0x4c 0x46`
        - Or with ASCII encoding: `0x7f 'E' 'L' 'F'`
      - Followed by a byte signifying 32 or 64-bit architectures, then a byte signifying little or big endian
      - Most file formats have different starting signatures (or magic numbers)

    - Use `readelf` to read ELF file headers

      - Command: `readelf <filename>`
      - Contains the following:
        - Information about the machine (e.g. the ISA)
        - The entry point of the program
        - Any program headers (required for executables)
        - Any section headers (required for libraries)
      - The header is 64 bytes, so we still have to account for 114 more

    - ELF program header

      - Tells the OS how to load the executable
        - Which type? Examples:
          - Load directly into memory
          - Use dynamic linking (libraries)
          - Interpret the program
        - Permission? Read/Write/Execute
        - Which VA to put it in?
          - Note that you'll rarely ever use PA's (for embedded)
      - For `Hello World` we load everything into memory
        - One program header is 56 bytes - 58 bytes left

    - `Hello World` needs 2 system calls

      - Command: `strace <filename>`
      - This shows all the system calls our program makes

    - Quick aside: API tells you what and ABI tells you how

      - Application Programming Interface (API) abstracts the details how to communicate
        - e.g. A function takes 2 integer arguments
      - Application Binary Interface (ABI) specifies how to layout data and how to concretely communicate
        - e.g. The same function using the C calling convention

    - System call API for `Hello World`

      - `strace` shows the API of system calls
      - The `write` system call's API is:
        - A file descriptor to write bytes to
        - An address to contiguous sequence of bytes
        - How many bytes to write from the sequence
      - The `exit_group` system call's API is:
        - An exit code for the program (`0`-`255`)

    - System call ABI for Linux x86-64

      - Enter the kernel with a `syscall` instruction, using registers for arguments
        - `rax` - system call number
        - `rdi` - 1st argument
        - `rsi` - 2nd argument
        - `rdx` - 3rd argument
        - `r10` - 4th argument
        - `r8` - 5th argument
        - `r9` - 6th argument
        - What are the limitations of this?
          - Limited number of arguments
          - Limited size of arguments
      - Note: other registers are not used, whether they're saved isn't important for us

    - Instructions for `Hello World`, using the Linux x86-64 ABI

      - Our disassembled instructions:

        - ```assembly
          mov rax,0x1
          mov rdi,0x1
          mov rsi,0x100a6
          mov rdx,0xc
          syscall
          mov rax,0xe7
          mov rdi,0x0
          syscall
          ```

    - Finishing up `Hello World`

      - The remaining 12 bytes is the “Hello world” string itself, ASCII encoded:
        - `0x48 0x65 0x6C 0x6C 0x6F 0x20 0x77 0x6F 0x72 0x6C 0x64 0x0A`
        - Low level ASCII tip: bit `5` is `0`/`1` for uppercase/lowercase (values differ by `32`)
      - This accounts for every single byte of our 178 byte program, let’s see what C does... 
      - Can you already spot a difference between strings in our example compared to C?

  - Source Code for `Hello World` in C

    - ```c
      #include <stdio.h>
      int main(int argc, char **argv) {
          printf("Hello world\n");
          return 0;
      }
      ```

    - What are other notable differences between this and our `Hello World`?

      - Lack of system calls
      - Access to command line arguments

    - The `return 0` doesn't end the program, programs must end with an `exit_group` system call

  - Kernel interfaces operate between CPU mode boundaries
    - The lessons from the lecture:
      - Code running in kernel code is part of your kernel
      - Different kernel architectures shift how much code runs in kernel mode
      - System calls is the interface between user and kernel mode
      - System calls is the interface between user and kernel mode
      - Everything involved to define a simple `Hello World` (in 178 bytes)
        - Difference between API and ABI
        - How to explore system calls

- Libraries

  - Applications may pass through multiple layers of libraries

    - Libraries are typically built on top of each other

  - C ABI, or Calling Convention for x86-64

    - System calls use registers, while C is stack-based
      - Arguments pushed on the stack from right-to-left order
      - `rax`, `rcx`, and `rdx` are caller saved
      - Remaining registers are callee saved
    - What advantages does this give us vs. system call ABI? Disadvantages?
      - Advantages: stack is more flexible in terms of number/size of arguments, less wasted register space
      - Disadvantages: slower access times

  - System Calls are Rare in C

    - Mostly, you'll be using functions from the C standard library instead
    - Most system calls have corresponding function calls in C, but may:
      - Set `errno`
      - Buffer reads and writes (reduce the number of system calls)
        - Reduces overhead from switching between user and kernel mode
      - Simplify interfaces (function combines 2 system calls)
      - Add new features

  - C `exit` has additional features

    - System call `exit` (or `exit_group`): the program stops at that point

    - C `exit`: there's a feature to register functions to call on program exit (`atexit`)

      - ```c
        #include <stdio.h>
        #include <stdlib.h>
        
        void fini(void) {
          puts("Do fini");
        }
        
        int main (int argc char** argv) {
          atexit(fini);
          puts("Do main");
          return 0;
        }
        ```

  - Normal compilation in C

    - `main.c` => (Compilation) => `main.o` => (Linkage) => `executable`
    - Note: object files (`.o`) are just ELF files with code for functions

  - Dynamic Libraries are for Reusable Code

    - The C standard library is a dynamic library (`.so`), like any other on the system
      - Basically a collection of `.o` files containing function definitions
    - Multiple applications can use the same library
      - `Application 1` => `libc.so` <= `Application 2`
        - The OS only loads `libc.so` in memory once and shares it
        - The same physical page corresponds to different virtual pages in processes

  - Useful Command Line Utilities for Dynamic Libraries

    - `ldd <executable>`
      - Shows which dynamic libraries an executable uses
    - `objdump -T <library>`
      - Shows the symbols (often just function names) that are in the library
    - You can also use `objdump -D` to disassemble the library

  - Static vs. Dynamic Libraries

    - Another option is to statically link your code
      - Basically copies the `.o` file directly into the executable
    - The drawbacks compared to dynamic linking
      - Statically linking prevents reusing libraries, commonly-used libraries have many duplicates
      - Any updates to a static library requires the executable to be recompiled
    - What are issues with dynamic libraries?
      - Runtime performance
      - Missing libraries
      - Less reliability

  - Dynamic Library Updates Can Break Executables with ABI Changes

    - An update to a dynamic library can easily cause an executable using it to crash
    - Consider the following in a dynamic library:
      - A `struct` with multiple fields corresponding to a specific data layout (C ABI)
    - An executable accesses the fields of the `struct` in the dynamic library
    - Now, if the dynamic library reorders the fields, the executable uses the old offsets and is now wrong
    - Note: this is ok if the dynamic library never exposes the fields of the `struct`

  - C Uses a Consistent ABI for `struct`s

    - `struct`s are laid out in memory with the fields matching the declaration order

      - C compilers ensure the ABI of `struct`s are consistent for an architecture

    - Consider the following structures:

      - Library `v1`:

        - ```c
          struct point {
            int y;
            int x;
          }
          ```

      - Library `v2`:

        - ```c
          struct point {
          	int x;
          	int y;
          }
          ```

      - For `v1`, the `x` field is offset by 4 bytes from the start of `point`'s base, but is offset by 0 bytes in `v2`

        - This difference will cause problems

  - Mismatched Versions of This Library Causes Unexpected Results

    - The definition of `struct point` in both libraries is different
      - Order of `x` and `y` change (and therefore their offsets)
    - Our code works correctly with either `v1` or `v2` of the library
      - With the stable ABI in `libpoint.h`
    - If the `struct point` was exposed, we get unexpected results with `v2`
      - This would be compiled into your program if the `struct` was visible



## Lecture 3:

- 



