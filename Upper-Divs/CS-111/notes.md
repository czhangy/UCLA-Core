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



## Lecture 2: Interfaces

- CPUs have "rings" to control instruction access

  - Each ring can access instruction in any of its outer rings

- The kernel of the OS runs in kernel mode

- System calls transition between user and kernel mode

- A monolithic kernel runs OS services in kernel mode

- A microkernel runs the minimum amount of services in kernel mode

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

- Kernel interfaces operate between CPU mode boundaries
  - The lessons from the lecture:
    - Code running in kernel code is part of your kernel
    - Different kernel architectures shift how much code runs in kernel mode
    - System calls is the interface between user and kernel mode
    - System calls is the interface between user and kernel mode
    - Everything involved to define a simple `Hello World` (in 178 bytes)
      - Difference between API and ABI
      - How to explore system calls



## Lecture 3:

- 



