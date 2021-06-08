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



## Lecture 3: Libraries and Processes

- Libraries

  - Semantic Versioning Meets Developer's Expectations

    - Given a version number `MAJOR.MINOR.PATCH`, increment the:
      - `MAJOR` version when you make incompatible API/ABI changes
      - `MINOR` version when you add functionality in a backwards-compatible manner
      - `PATCH` version when you make backwards-compatible bug fixes

  - Dynamic Libraries Allow Easier Debugging

    - Control dynamic linking with environment variables

      - `LD_LIBRARY_PATH` and `LD_PRELOAD`

    - Consider the following example:

      - ```c
        #include <stdlib.h>
        #include <stdio.h>
        
        int main(int argc, char **argv) {
            int *x = malloc(sizeof(int));
            printf("x = %p\n", x);
            free(x);
            return 0;
        }
        ```

  - We Can Monitor All Allocations with Our Own Library

    - Normal runs of `alloc-example` outputs `x = 0x561116384260`
    - Create `alloc-wrapper.so` that outputs all `malloc` and `free` calls
    - Interesting, we did not make 2 `malloc` calls
      - `printf` allocates a buffer for itself

  - Detecting Memory Leaks

    - `valgrind` is another useful tool to detect memory leaks from `malloc` and `free`

      - Usage: `valgrind <executable>`

    - Here's a note from the `man` pages regarding what we saw:

      - > "The GNU C library (`libc.so`), which is used by all programs, may allocate memory for its own uses. Usually it doesn't bother to free that memory when the program ends - there would be no point, since the Linux kernel reclaims all process resources when a process exits anyway, so it would just slow things down"

      - This does not excuse you from not calling `free`

  - Standard File Descriptors for Unix

    - All command line executables use the following standard for file descriptors:
      - `0` - `stdin` (Standard input)
      - `1` - `stdout` (Standard output)
      - `2` - `stderr` (Standard error)
    - The terminal emulator's job is to:
      - Translate key presses to bytes and write to `stdin`
      - Display bytes read from `stdout` and `stderr`
      - May redirect file descriptors between processes

  - Checking Open File Descriptors on Linux

    - `/proc/<PID>/fd` is a directory containing all open file descriptors for a process
    - `ps x` shows a list of processes matching your user (lots of other flags available)
    - `lsof <file>` shows you what processes have the file open
      - For example, processes using C: `lsof /lib/libc.so.6`

  - Operating Systems Provide the Foundation for Libraries

    - We learned:
      - Dynamic libraries and a comparison to static libraries
        - How to manipulate the dynamic loader
      - Example of issues from ABI changes without API changes
        - If something escapes your library, that ABI must remain constant, or else it could break any program that depends on it
      - Standard file descriptor conventions for UNIX

- Processes

  - A Process is an Instance of a Running Program
  - A program (or application) is just a static definition, including
      - Instructions
      - Data
      - Memory allocations
      - Symbols it uses
    - When you start executing a program, it turns into a process
  - Process is Like a Combination of all the Virtual Resources

    - If we consider a "virtual CPU", the OS needs to track all registers
    - It also contains all other resources it can access (memory and I/O)
    - Every execution runs the same code (part of the program)
      - An execution is running some specific code (part of the process)
  - A Process is More Flexible

    - A process contains both the program and information specific to its execution
    - It allows multiple executions of the same program
    - It even allows a process to run multiple copies of itself
  - A Process Control Block (PCB) Contains All Execution Information

    - Specifically, in Linux, this is the `task_struct` we saw in Lab 0
    - It contains:
      - Process state
      - CPU registers
      - Scheduling information
      - Memory management information
      - I/O status information
      - Any other type of accounting information
  - Aside: Concurrency and Parallelism Aren't the Same

    - Concurrency: switching between two or more things (can you get interrupted)
      - Goal: make progress on multiple things
    - Parallelism: running two or more things at the same time (are they independent)
      - Goal: run as fast as possible
  - A Real Life Situation of Concurrency and Parallelism

    - You're sitting at a table for dinner, and you can:
      - Eat
      - Drink
      - Talk
      - Gesture
    - You're so hungry that if you start eating, you won't stop until you finish
    - Which tasks can and can't be done concurrently, and in parallel?
  - Choose Any Two Tasks in the Real Life Example
    - You can't eat and talk (or drink) at the same time, and you can't switch
      - Not parallel and not concurrent
    - You could eat and gesture at the same time, but you can't switch
      - Parallel and not concurrent
    - You can't drink and talk at the same time, and you could switch
      - Not parallel and concurrent
    - You can talk (or drink) and gesture at the same time, and you could switch
      - Parallel and concurrent
  - Uniprogramming is for Old Batch Processing Operating Systems
    - Uniprogramming: only one process running at a time
      - Two processes are not parallel and not concurrent, no matter what
    - Multiprogramming: allow multiple processes
      - Two processes can run in parallel or concurrently
    - Modern operating systems try to run everything in parallel and concurrently
  - Process State Diagram

    - => Created
    - Created => Waiting/Ready
    - Waiting/Ready => Running
    - Running => Waiting/Ready
    - Running => Terminated (Accept state)
    - Running => Blocked
    - Blocked => Waiting/Ready
  - The Scheduler Decides When to Switch
    - To create a process, the OS has to at least load it into memory
    - When it's waiting, the scheduler (coming later) decides when it's running
    - We're going to first focus on the mechanics of switching processes
  - The Core Scheduling Loop Changes Running Processes
    - 1. Pause the currently running process
      2. Save its state, so you can restore it later
      3. Get the next process to run from the scheduler
      4. Load the next process' state and let that run
  - We Can Let Processes Themselves, or the OS Pause
    - Cooperative multitasking: the processes use a system call to tell the OS to pause it
      - Processes use system calls to manage pausing
    - True multitasking: the OS retains control and pauses processes
    - For true multitasking, the OS can:
      - Give processes set time slices
      - Wake up periodically using interrupts to do scheduling
  - Swapping Processes is Called Context Switching
    - We've said that, at minimum, we'd have to save all of the current registers
      - We have to save all of the values, using the same CPU as we're trying to save
    - There's hardware support for saving state, however, you may not want to save everything
    - Context switching is pure overhead, we want it to be as fast as possible
    - Usually, there's a combination of hardware and software to save as little as possible
    - You can think of a process as a program + context
  - We Could Create Processes from Scratch
    - We load the program into memory and create the process control block
      - This is what Windows does
    - Could we decompose this into more flexible abstractions?
  - Instead of Creating a New Process, We Could Clone It
    - Pause the currently running process, and copy it's PCB into a new one
      - This will reuse all of the information from the process, including variables
    - Distinguish between the two processes with a parent and child relationship
      - They could both execute different parts of the program together
    - We could then allow either process to load a new program and setup a new PCB
  - On Unix, the Kernel Launches A Single User Process
    - After the kernel initializes, it creates a single process from a program
    - This process is called `init` and it looks for it in `/sbin/init`
      - Responsible for executing every other process on the machine
        - Will be the parent/ancestor of every process on the machine
      - Must always be active, if it exits, the kernel thinks you're shutting down
    - For Linux, `init` will probably be `systemd`, but there's other options
  - Aside: some OSes create an "idle" process that the scheduler can run
  - How You Can See Your Process Tree
    - Use `htop`
      - `sudo pacman -S htop` to install on the virtual machine
    - You can press `F5` to switch between tree and list view
  - You may have to update all your packages first:
    
    - `sudo pacman -Syu` (Reboot if your kernel updates)
  - The Parent Process is Responsible for Its Child
    - The OS sets the exit status when a process terminates (by calling `exit`)
      - It can't remove its PCB yet
    - The minimum acknowledgement the parent has to do is read the child's exit status
    - There's two situations:
      - The child exits first (zombie process)
      - The parent exits first (orphan process)
  - A Zombie Process Waits for Its Parent to Read Its Exit Status
    - The process is terminated, but it hasn't been acknowledged
    - A process may have an error in it, where it never reads the child's exit status
    - The OS can interrupt the parent process to tell it to acknowledge the child
      - This is a basic form of IPC called a signal
      - By default, processes may ignore this
    - The OS has to keep the zombie process at least until the parent exits if it doesn't acknowledge it
  - An Orphan Process Needs a New Parent
    - The child process lost its parent process
      - The child still needs a process to acknowledge its exit
    - The OS re-parents the child process to `init`
      - The `init` process is now responsible to acknowledge the child
  - The OS Creates and Runs Processes
    - The OS has to:
      - Load a program and create a process with context
        - Register values, instruction pointer, etc.
      - Maintain process control blocks, including state
      - Switch between running processes using a context switch
      - Unix kernels start an `init` process
        - Responsible for running all the processes on the rest of the machine
      - Unix processes have to maintain a parent and child relationship



## Lecture 4: Process API and Basic IPC

- Process API

  - Linux Terminology is Slightly Different

    - You can look at a process' state by reading `/proc/<pid>/state`
      - Replace `<pid>` with the process ID
    - `R`: Running and runnable [Running and waiting]
    - `S`: Interruptible sleep [Blocked]
      - Could be opened up to execute
    - `D`: Uninterruptible sleep [Blocked]
    - `T`: Stopped
    - `Z`: Zombie
    - The kernel lets you explicitly stop a process to prevent it from running
      - You or another process must explicitly continue it

  - On POSIX Systems, You Can Find Documentation Using `man`

    - We'll be using the following APIs:
      - `execve`
      - `fork`
      - `wait`
    - You can use `man <function>` to look up documentation, or `man <number> <function>`
      - `2`: System calls
      - `3`: Library calls

  - `execve` Loads Another Program, and Replaces process with a New One

    - `execve` has the following API:
      - `pathname`: full path of the program to load
      - `argv`: array of strings (array of characters), terminated by a null pointer
        - Represents arguments to the process
      - `envp`: same as `argv`
        - Represents the environment of the process
      - Returns an error on failure, does not return if successful

  - `execve-example.c` Turns the Process into `ls`

    - ```c
      int main(int argc, char *argv[]) {
          printf("I'm going to become another process\n");
          char *exec_argv[] = {"ls", NULL};
          char *exec_envp[] = {NULL};
          int exec_return = execve("/use/bin/ls", exec_argv, exec_envp);
          if (exec_return == -1) {
              exec_return = errno;
              perror("execve failed");
              return exec_return;
          }
          printf("If execve worked, this will never print\n");
          return 0;
      }
      ```

  - `fork` Creates a New Process, a Copy of the Current One

    - `fork` has the following API:
      - Returns the process IS of the newly created child process
        - `-1`: on failure
        - `0`: in the child process
        - `>0`: in the parent process
    - There are now 2 processes running
      - Note: they can access the same variables, but they're separate
        - OS does "copy on write" to maximize sharing

  - `fork-example.c` Has One Process Execute Each Branch

    - ```c
      int main(int argc, char *argv[]) {
          pid_t pid = fork();
          if (pid == -1) {
              int err = errno;
              perror("fork failed");
              return err;
          }
          if (pid == 0) {
              printf("Child return pid: %d\n", pid);
              printf("Child pid: $d\n", getpid());
              printf("Child parent pid: %d\n", getppid());
          }
          else {
              printf("Parent returned pid: %d\n", pid);
              printf("Parent pid: %d\n", getpid());
              printf("Parent parent pid: %d\n", getppid());
          }
          return 0;
      }
      ```

  - `orphan-example.c` The Parent Exits Before the Child, `init` Cleans Up

    - ```c
      int main(int argc, char *argv[]) {
          pid_t pid = fork();
          if (pid == -1) {
              int err = errno;
              perror("fork failed");
              return err;
          }
          if (pid == 0) {
              printf("Child parent pid: %d\m", getppid());
              sleep(2);
              printf("Child parent pid (after sleep): %d\n", getppid());
              // getppid will be init or a subreaper id
          }
          else {
              sleep(1);
          }
          return 0;
      }
      ```

  - `zombie-example.c` The Parent Monitors the Child to Check Its State

    - ```c
      pid_t pid = fork();
      // Error checking
      if (pid == 0) {
          sleep(2);
      }
      else {
          // Parent process
          int ret;
          sleep(1);
          printf("Child process state: ");
          ret = print_state(pid);
          if (ret < 0) { return errno; }
          sleep(2);
          printf("Child process state: ");
          ret = print_state(pid);
          if (ret < 0) { return errno; }
      }
      ```

  - You Need to Call `wait` on Child Processes

    - `wait` has the following API:
      - `status`: address to store the wait status of the process
      - Returns the process ID of child process
        - `-1`: on failure
        - `0`: for no blocking calls with no child changes
        - `>0`: the child with a change
      - The wait status contains a bunch of information, including the exit code
        - Use `man wait` to find all the macros to query wait status
          - You can use `waitpid` to wait on a specific child process
    - Acknowledges the child

  - `wait-example.c` Blocks Until the Child Process Exists, and Cleans Up

    - ```c
      int main(int argc, char *argv[]) {
          pid_t pid = fork();
          if (pid == -1) {
              return errno
          }
          else {
              printf("Calling wait\n");
              int wstatus;
              pid_t wait_pid = wait(&wstatus);
              if (WIFEXITED(wstatus)) {
                  printf("Wait reutrned for an exited process! pid: %d, status: %d\n",
                        wait_pid, WEXITSTATUS(wstatus));
              }
          }
          return 0;
      }
      ```
    
  - We Used System Calls to Create Processes

    - You should be comfortable with:
      - `execve`
      - `fork`
      - `wait`
    - This includes understanding processes and their relationships

- Basic IPC

  - IPC is Transferring Bytes Between Two or More Processes
    - Reading and writing files is a form of IPC
    - For a process, you can read the input and write the output
      - Think about Lab 0
    - The `read` and `write` system calls allow any bytes
  - A Simple Process Could Write Everything It Reads
    - See: `lecture-06/read-write/example.c`
    - We `read` from `stdin` and `write` to `stdout`
      - Does this remind you of any program you've seen before? => `cat`
    - If we run it in our terminal without arguments, it'll wait for input
      - Press `Ctrl + D` when you're done to send end-of-file (`EOF`)
  - `read` Just Reads Data from a File Descriptor
    - See: `man 2 read`
    - There's no `EOF` character, `read` just returns 0 bytes read
      - The kernel returns `0` on a closed file descriptor
    - We need to check for errors!
      - Save `errno` if you're using another function that may set it
  - `write` Just Writes Data to a File Descriptor
    - See: `man 2 write`
    - It returns the number of bytes written, you can't assume it's always successful
      - Save `errno` if you're using another function that may set it
    - Both ends of the `read` and `write` have a corresponding `write` and `read`
      - This makes two communication channels with command line programs



## Lecture 5: Basic IPC and Basic Scheduling

- Basic IPC
  
  - The Standard File Descriptors are Powerful
    
    - We could close `stdin` (freeing file descriptor `0`) and open a file instead
      - Linux uses the lowest available file descriptor for new ones
    - See: `lecture-06/open-example.c` and `man 2 open`
    - Without changing the core code, it now works with multiple input types
    - You could type or use a file
    
  - Your Shell will Let You Redirect Standard File Descriptors
    - Instead of running `./open-example open-example.c`, we could run: `./open-example < open-example.c`
    - Your shell will do the `open` for you and replace the `stdin`
      - We didn't actually have to write that
    - You could also redirect across multiple processes
      - `cat open-example.c | ./open-example`
    
  - Piping in Your Shell Connects Two Processes Together
    - In `./p1 | ./p2`, the shell connects `p1`'s `stdout` to `p2`'s `stdin`
    - The kernel has a `pipe` system call that returns two file descriptors
      - `fd_pair[0]` is for `read` and `fd_pair[1]` is for `write`
    - This forms a one-way communication channel
  
  - Your Shell Properly Handles All the File Descriptors
  
    - This includes changing file descriptors, and closing them properly
    - You can use `dup2` to move a file descriptor to a new one
      - If the new one is already open, it'll `close` it first
    - See: `man 2 dup2` and `man 2 close`
    - How do you give processes different file descriptors
      - `fork` copies all the file descriptors to the new process
  
  - Signals are a Form of IPC that Interrupts
  
    - You could also press `Ctrl + C` to stop `./open-example`
      - This interrupts your program's execution and exits early
    - Kernel sends a number to your program indicating the type of signal
      - Kernel default handlers either ignore the signal or terminate your process
    - `Ctrl + C` sends `SIGINT` (interrupt from keyboard)
    - If the default handler occurs, the exit code will be `128 + signal number`
  
  - You Can Set Your Own Signal Handlers with `signal`
  
    - See: `lecture-6/signal-example.c` and `man 2 signal`
    - You just declare a function that doesn't return a value, and has an `int` argument
      - The integer is the signal number
    - Some numbers are non-standard, here are a few from Linux x86-64:
      - `2`: `SIGINT` (interrupt from keyboard)
      - `9`: `SIGKILL` (terminate immediately)
      - `11`: `SIGSEGV` (memory access violation)
      - `15`: `SIGTERM` (terminate)
  
  - A Signal Pauses your Process and Runs the Signal Handler
  
    - Your process can be interrupted at any point in execution
      - Your process resumes after the signal handler finishes
    - This is an example of concurrency, your process switches execution
      - You have to be careful what you write here
    - Run `./signal-example` and press `Ctrl + C`
  
  - You Need to Account for Interrupted System Calls
  
    - You should see:
  
      - ```
        Ignoring signal 2
        read: Interrupted system call
        ```
  
    - We can rewrite it to retry interrupted system calls
  
      - See: `lecture-06/signal-example-2.c`
  
    - Now the program continues when we press `Ctrl + C`
  
  - You Can Send Signals to Processes with Their PID
  
    - You can use the command `kill`
      - It is also a system call, taking a `pid` and signal number
    - Find a processes' ID with `pidof`, e.g. `pidof ./signal-example-2`
    - After, use `kill <pid>`, which by default sends `SIGTERM`
    - Use `kill -9 <pid>` to tell the kernel to terminate the process
      - Process won't terminate if it's in uninterruptible sleep
      - Sends `SIGKILL`, which can't be ignored
  
  - Shared Memory Allows Two Processes to Access the Same Memory
  
    - See: `lecture-06/shared-memory-example.c` and `man 3 shm_open`
    - You use `shm_open`, which returns a file descriptor
    - You can think of it as a new location to read and write bytes to
      - This needs to be resized with `ftruncate`
    - Note: on some implementations, this just opens a file in `/dev/shm`
  
  - `mmap` Allows You to Memory Map the Contents of a File Descriptor
  
    - See: `man 3 mmap`
    - Instead of using `read` and `write` system calls, you just access memory
      - The OS is responsible for management
    - Instead of accessing the file sequentially, you can access any part of it
    - You can `mmap` regular files as well
  
  - We Explored Basic IPC in an OS
  
    - Some basic IPC includes:
      - `read` and `write` through file descriptors (could be a regular file)
      - Redirecting file descriptors for communication
      - Pipes (which you'll explore)
      - Signals
      - Shared Memory
  
- Basic Scheduling

  - There are Preemptible and Non-Preemptible resources
    - A preemptible resource can be taken away and used for something else, e.g. a CPU
    - The resource is shared through scheduling
    - A non-preemptible resource cannot be taken away without acknowledgement, e.g. disk space
    - The resource is shared through allocations and deallocations
      - Note: Parallel and distributed systems may allow you to allocate a CPU
  - A Dispatcher and Scheduler Work Together
    - A dispatcher is a low-level mechanism
      - Responsible for context switching
    - A scheduler is a high-level policy
      - Responsible for deciding which processes to run
  - The Scheduler Runs Whenever a Process Changes State
    - First let's consider non-preemptible processes
      - Once the process starts, it runs uintil completion
    - In this case, the scheduler will only make a decision when the process terminates
    - Preemptive allows the OS to run the scheduler at will
      - Check `uname -v`, your kernel should tell you it's preemptible
  - Metrics
    - Minimize waiting time and response time
      - Don't have a process waiting too long (or too long to start)
    - Maximize CPU utilization
      - Don't have the CPU idle
    - Maximize throughput
      - Complete as many processes as possible
    - Fairness
      - Try to give each process the same percentage of the CPU
  - First Come First Served (FCFS)
    - The most basic form of scheduling
    - The first process that arrives gets the CPU
    - Processes are stored in a FIFO queue in arrival order
  - A Gantt Chart Illustrates the Schedule
  - What Happens to Our Waiting Time with a Different Arrival Order?
  - Shortest Job First (SJF)
    - A slight tweak to FCFS, we always schedule the job with the shortest burst time first
    - We're still assuming no preemption
  - SJF Minimizes the Average Wait Time Over FCFS
  - SJF is Not Practical
    - It is provably optimal at minimizing average wait time (if no preemption)
    - You will not know the burst times of each process
      - You could use the past to predict future executions => may not always work
    - You may starve long jobs (they may never execute)
  - Shortest Remaining Time First (SRTF)
    - Changing SJF to run with preemption requires another tweak
    - We'll assume that our minimum execution time is one unit
    - Similar to SJF, this optimizes the average waiting time
  - SRTF Reduces the Average Wait Time Compared to SJF
  - Round-Robin (RR)
    - So far we haven't handled fairness (it's a trade off with other metrics)
    - The OS divides execution into time slices (or quanta)
      - An individual time slice is called a quantum
    - Maintain a FIFO queue of processes similar to FCFS
      - Preempt if still running at end of quantum and re-add to queue
    - What are practical considerations for determining quantum length?
      - Context switching can't be a significant amount of the quantum length
  - Metrics for RR (3 Unit Quantum Length)
    - Note: on ties (a new process arrives while one is preempted), favor the new one
  - RR Performance Depends on Quantum Length and Job Length
    - RR has low response, good interactivity
      - Fair allocation of CPU
      - Low average waiting time (when job lengths vary)
    - The performance depends on the quantum length
      - Too high and it becomes FCFS
      - Too low and there's too many context switches (overhead)
    - RR has poor average waiting time when jobs have similar lengths
  - Scheduling Involves Trade-Offs
    - We looked at few different algorithms:
      - First Come First Served (FCFS) is the most basic scheduling algorithm
      - Shortest Job First (SJF) is a tweak that reduces waiting time
      - Shortest Remaining Time First (SRTF) uses SJF ideas with preemptions
        - SRTF optimizes lowest waiting time (or turnaround time)
      - Round-robin (RR) optimizes fairness and response time



## Lecture 6: Advanced Scheduling and Scheduling Example

- Advanced Scheduling
  - We Could Add Priorities
    - We may favor some processes over others
      - Assign each process a priority
    - Run higher priority process first, round-robin processes of equal priority
      - Can be preemptive or non-preemptive
  - Priorities Can Be Assigned an Integer
    - We can pick a lower, or higher number, to mean high priority
      - In Linux, `-20` is the highest priority, `19` is the lowest
    - We may lead processes to starvation if there's a lot of higher priority processes
    - One solution is to have the OS dynamically change the priority
      - Older processes that haven't been executed in a long time increase priority
  - Priority Inversion is a New Issue
    - We can accidentally change the priority of a low priority process to a high one
      - This is caused by dependencies, e.g. a high priority depends a low priority
    - One solution is priority inheritance
      - Inherit the highest priority of the waiting processes
      - Chain together multiple inheritances if needed
      - Revert back to the original priority after dependency
  - A Foreground Process Can Receive User Input, Background Cannot
    - Unix background process when: process group ID differs from its terminal group ID
      - You do not need to know this specific definition
    - The idea is to separate processes that users interact with:
      - Foreground processes are interactive and need good response time
      - Background processes may not need good response time, just throughput
  - We Can Use Multiple Queues for Other Purposes
    - We could create different queues for foreground and background processes
      - Foreground uses RR
      - Background uses FCFS
    - Now we have to schedule between queues
      - RR between the queues
      - Use a priority for each queue
  - Scheduling Can Get Complicated
    - There's no right answer, only trade-offs
    - We haven't talked about multiprocessor scheduling yet
    - We'll assume symmetric multiprocessing (SMP)
      - All CPUs are connected to the same physical memory
      - The CPUs have their own private cache (at least the lowest levels)
  - One Approach is to Use the Same Scheduling for All CPUs
    - There's still only one scheduler
      - It just keeps adding processes while there's available CPUs
    - Advantages
      - Good CPU utilization
      - Fair to all processes
    - Disadvantages
      - Not scalable (everything blocks on global scheduler)
      - Poor cache locality
    - This was the approach in Linux 2.4
  - We Can Create Per-CPU Schedulers
    - When there's a new process, assign it to a CPU
      - One strategy is to assign it to the CPU with the lowest number of processes
    - Advantages
      - Easy to implement
      - Scalable (there's no blocking on a resource)
      - Good cache locality
    - Disadvantages
      - Load imbalance
        - Some CPUs may have less processes, or less intensive ones
  - We Can Compromise Between Global and Per-CPU
    - Keep a global scheduler that can rebalance per-CPU queues
      - If a CPU is idle, take a process from another CPU (work stealing)
    - You may want more control over which processes can switch
      - Some may be more sensitive to caches
    - Use processor affinity
      - The preference of a process to be scheduled on the same core
    - This is a simplified version of the `O(1)` scheduler in Linux 2.6
  - Another Strategy is "Gang" Scheduling
    - Multiple process may need to be scheduled simultaneously
    - The scheduler on each CPU cannot be completely independent
    - "Gang Scheduling" (Co-scheduling)
      - Allows you to run a set of processes simultaneously (acting as a unit)
    - This requires a global context-switch across all CPUs
  - Real-Time Scheduling is Yet Another Problem
    - Real-time means there are time constraints, either for a deadline or rate
      - e.g. audio, autopilot
    - A hard real-time system
      - Required to guarantee a task complete within a certain amount of time
    - A soft real-time system
      - Critical processes have a higher priority and the deadline is met in practice
    - Linux is an example of soft real-time
  - Linux Also Implements FCFS and RR Scheduling
    - You can search around in the source tree FCFS (`SCHED_FIFO`) and RR (`SCHED_RR`)
    - Use a multilevel queue scheduler for processes with the same priority
      - Also let the OS dynamically adjust the priority
    - Soft real-time processes always schedule the highest priority processes first
    - Normal processes adjust the priority based on aging
  - Real-Time Processes are Always Prioritized
    - The soft real-time scheduling policy will either be `SHCED_FIFO` or `SCHED_RR`
      - There are 100 static priority levels (`1`-`99`)
    - Normal scheduling policies apply to the other processes (`SHCED_NORMAL`)
      - By default the priority is `0`
      - Priority ranges from `[-20, 19]`
    - Processes can change their own priorities with system calls: `nice`, `sched_setscheduler`
  - Linux Scheduler Evolution
    - 2.4-2.6, a `O(N)` global queue
      - Simple, but poor performance with multiprocessors and many processes
    - 2.6-2.6.22, a per-CPU run queue, `O(1)` scheduler
      - Complex to get right, interactivity had issues
      - No guarantee of fairness
    - 2.6.23-Present, the completely fair scheduler (CFS)
      - Fair and allows for good interactivity
  - The `O(1)` Scheduler Has Issues with Modern Processes
    - Foreground and background processes are a good division
      - Easier with a terminal, less so with GUI processes
    - Now the kernel has to detect interactive processes with heuristics
      - Processes that sleep a lot may be more interactive
        - This is ad hoc, and could be unfair
    - How would we introduce fairness for different priority processes
      - Use different size time slices
      - The higher the priority, the larger the time slice
        - There are also situations where this ad hoc solution could be unfair
  - Ideal Fair Scheduling
    - Assume you have an infinitely small time slice
      - If you have `n` processes, each runs at `1/n` rate
    - CPU usage is divided equally among every process
  - Example IFS Scheduling
  - IFS is the Fairest but Impractical Policy
    - This policy is fair, every process gets an equal amount of CPU time
      - Boosts interactivity, has the ideal response time
    - However, this would perform way too many context switches
    - You have to constantly scan all processes, which is `O(N)`
  - Completely Fair Scheduler (CFS)
    - For each runnable process, assign it a "virtual runtime"
      - At each scheduling point where the process runs for time `t`, increase the virtual runtime by `t x weight` (based on priority)
    - The virtual runtime monotonically increases
      - Scheduler selects the process based on the lowest virtual runtime
        - Compute its dynamic time slice based on the IFS
    - Allow the process to run, when the time slice ends, repeat the process
  - CFS is Implemented with Red-Black Trees
    - A red-black tree is a self-balancing BST
      - Keyed by virtual runtime
        - `O(log N)` insert, delete, and update
        - `O(1)` find minimum
    - The implementation uses a red-black tree with a nanosecond granularity
      - Doesn't need to guess the interactivity of a process
    - CFS tends to favor I/O bound processes by default
      - Small CPU bursts translate to a low virtual runtime
        - It will get a larger time slice, in order to catch up to the ideal
  - Scheduling Gets Even More Complex
    - There are more solutions, and more issues:
      - Introducing priority also introduces priority inversion
      - Some processes need good interactivity, others not so much
      - Multiprocessors may require per-CPU queues
      - Real-time requires predictability
      - Completely Fair Scheduler (CFS) tries to model the ideal fairness
- Scheduling Example
  - We're Going to Develop `lecture-09/srtf.c`
    - Filling the basic fields of processes are done for you - `data` and `size`
    - There's a doubly linked list set up for you
      - `man TAILQ_INIT`
        - It's overkill for now, but you might need it later
    - Ask any questions about this, or anything that hasn't been clear up to this point
  - We Did Implementation Today
    - Implemented SRTF in C:
      - Reports the average waiting and response time
      - (Hopefully) handles edge cases
      - Matches the results in the lecture



## Lecture 7: Page Tables

- Virtualization Fools Something Into Thinking it has All Resources

- Virtual Memory Checklist

  - Multiple processes must be able to coexist
  - Processes are not aware they are sharing physical memory
  - Processes cannot access each other's data (unless allowed explicitly)
  - Performance close to using physical memory
  - Limit the amount of fragmentation (wasted memory)

- Memory Management Unit (MMU)

  - Maps virtual address to physical address
    - Also checks permissions
  - One technique is to divide memory up into fixed-size pages (typically 4096B)
    - A page in virtual memory is called a page
    - A page in physical memory is called a frame

- Segmentation or Segments are Coarse Grained

  - Divide the virtual address space into segments for: code, data, stack, heap
    - Note: this looks like an ELF file, large sections of memory with permissions
  - Each segment is a variable size and can be dynamically resized
    - This is an old legacy technique that's no longer used
  - Segments can be large and very costly to relocate
    - It also leads to fragmentation (gaps of unused memory)
  - No longer used in modern OSes

- Segmentation Details

  - Each segment contains a: base, limit, and permissions
    - You get a physical address by using: `segment selector: offset`
  - The MMU checks that you offset is within the limit (size)
    - If it is, it calculates `base + offset`, and does permission checks
      - Otherwise, it's a segmentation fault
  - For example, `0x1:0xFF` with segment `0x1` base = `0x2000`, limit = `0x1FF`
    - Translates to `0x20ff`
  - Note: Linux sets every base to `0` and limit to the maximum amount

- You Typically Do Not Use all 64 Virtual Address Bits

  - CPUs may have different levels of virtual addresses you can use
    - Implementation ideas are the same
  - We'll assume a 39-bit virtual address space used by RISC-V and other architectures
    - Allows for 512GB of addressable memory (called Sv39)
  - Implemented with a page table indexed by Virtual Page Number (VPN)
    - Looks up the Physical Page Number (PPN)

- The Page Table Translates Virtual to Physical Addresses

- The Kernel Handles Translating Virtual Addresses

  - Considering the following page table:

    - |  VPN  |  PPN  |
      | :---: | :---: |
      | `0x0` | `0x1` |
      | `0x1` | `0x4` |
      | `0x2` | `0x3` |
      | `0x3` | `0x7` |

  - We would get the following virtual => physical address translations:

    - ```
      0x0AB0 -> 0x1AB0
      0x1FA0 -> 0x4FA0
      0x2884 -> 0x3884
      0x32D0 -> 0x72D0
      ```

- Page Translation Example Problem

  - Assume you have a 8-bit virtual address, 10-bit physical address, and each page is 64 bytes

    - How many virtual pages are there?

      - $$
        \frac{2^8}{2^6}=4
        $$

    - How many physical pages are there?

      - $$
        \frac{2^{10}}{2^6}=16
        $$

    - How many entries are in the page table?

      - $$
        4
        $$

    - Given the page table is `[0x2, 0x5, 0x1, 0x8]`, what's the physical address of `0xF1`?

      - $$
        0x231
        $$

- The Page Table Entry (PTE) Also Stores Flags in the Lower Bits

  - The MMU, which uses the page table, checks these flags
    - We'll focus on the first 5 flags

- Each Process Gets Its Own Virtual Address Space

- Each Process Gets Its Own Page Table

  - When you `fork` a process, it will copy the page table from the parent
    - Turn off the write permission so the kernel can implement copy-on-write
  - The problem is there are `2^27` entries in the page table, each one is 8B
    - This means the page table would be 1GB
  - Note that RISC-V translates a 39-bit virtual to a 56-bit physical address
    - It has 10 bits to spare in the PTE and could expand
    - Page size is 4096B (size of offset field)

- You May Be Thinking That Seems Like A Lot of Work

  - In Lab 1, we're doing a `fork` followed by an `exec`, why do we need to copy the page tables?
  - We don't, there's a system call for that - `vfork`
  - `vfork` shares all memory with the patent
    - It's undefined behavior to modify anything
  - Only used in very performance sensitive programs

- Multi-Level Page Tables Save Space for Sparse Allocations

- For RISC-V, Each Level Occupies One Page

  - There are 512 (`2^9`) entries of 8 (`2^3`) bytes each, which is 4096B
  - The PTE for `L(N)` points to the page table for `L(N - 1)`
  - You follow these page tables until `L0` and that contains the PPN

- Consider just one additional level

  - Assume our process uses just one virtual address at `0x3FFFF008`
    - Or `0b111111111_111111111_000000001000`
  - We'll just consider a 30-bit virtual address with a page size of 4096B
    - We would need a 2MB page table if we only had one (`2^18 x 2^3`)
  - Instead, we have a 4KB `L1` page table (`2^9 x 2^3`) and a 4 KB `L0` page table
    - Total of 8KB instead of 2MB
  - Note: worst case if we used all virtual addresses, we could consume 2MB + 4KB

- Translating `3FFFF008` with two page tables

  - Consider the `L1` table with the entry:

    - | Index |  PPN  |
      | :---: | :---: |
      | `511` | `0x8` |

  - Consider the `L0` table located at `0x8000` with the entry:

    - | Index |   PPN    |
      | :---: | :------: |
      | `511` | `0xCAFE` |

  - The final translated physical address would be `0xCAFE008`

- Processes use a register like `satp` to set the root page table

- Page allocation uses a free list

  - Given physical pages, the OS maintains a free list (linked list)
  - The unused pages themselves contain the `next` pointer in the free list
    - Physical memory gets initialized at boot
  - To allocate a page, you remove it from the free list
    - To deallocate a page, you add it back to the free list

- Using the page tables for every memory access is slow

  - We need to follow pointers across multiple levels of page tables
  - We'll likely access the same page multiple times (close to the first access time)
  - A process may only need a few VPN => PPN mappings at a time
  - Our solution is another CS classic: caching

- A Translation Lookaside Buffer (TLB) caches virtual addresses

- Effective Access Time (EAT)

  - Assume a single page table (there's only one additional memory access in the page table)

    - $$
      \text{TLB Hit Time}=\text{TLB Search}+\text{Mem}\\\text{TLB Miss Time}=\text{TLB Search}+2\times\text{Mem}\\\text{EAT}=\alpha\times\text{TLB Hit Time}+(1-\alpha)\times\text{TLB Miss Time}
      $$

  - If `α = 0.8`, `TLB Search = 10ns`, and memory accesses take 100ns, calculate `EAT`

    - $$
      \text{EAT}=0.8\times 110\text{ns}+0.2\times 210\text{ns}\\\text{EAT}=130\text{ns}
      $$

- Context switches require handling the TLB

  - You can either flush the cache, or attach a process ID to the TLB
  - Most implementations just flush the TLB
    - RISC-V uses a `sfence.vma` instruction to flush the TLB
  - On x86, loading the base page table will also flush the TLB

- How many levels do I need?

  - Assume we have a 32-bit virtual address with a page size of 4096B and a PTE size of 4B

  - We want each page table to fit into a single page

    - Find the number of PTEs we could have in a page (`2^10`)
      - `log(#PTEs per page)` is the number of bits to index a page table

  - $$
    \text{#Levels}=\lceil\frac{\text{Virtual Bits}-\text{Offset Bits}}{\text{Index Bits}}\rceil
    $$

    - 
      $$
      \text{#Levels}=\lceil\frac{32-12}{10}\rceil=2
      $$

- TLB testing

  - Check out `lecture-10/test-tlb` (you may need to `git submodule update --init --recursive`)
  - `./test-tlb <size> <stride>` creates a `<size>` memory allocation and accesses it every `<stride>` bytes

- Use `sbrk` for userspace allocation

  - This call grows or shrinks your heap (the stack has a set limit)
  - For growing, it'll grab pages from the free list to fulfill the request
    - The kernel sets `PTE_V` (valid) and other permissions
  - In memory allocators, this is difficult to use, you'll rarely shrink the heap
    - It'll stay claimed by the process, and the kernel cannot free pages
  - Memory allocators use `mmap` to bring in large blocks of virtual memory

- The kernel initializes the process' address space (and stack)

- A trampoline is a fixed virtual address set by the kernel

  - It allows the process to access kernel data without using a system call
  - The guard page will generate an exception if access meaning stack overflow
  - A trap is anytime special handler code runs:
    - System call
    - Exception
    - Interrupt (e.g. timer)

- Page faults allow the OS to handle virtual memory

  - Page faults are a type of exception for virtual memory access
    - Generated if it cannot find a translation, or permission check fails
  - This allows the OS to handle it
    - We could lazily allocate pages, implement copy-on-write, or swap to disk

- Page tables translate virtual to physical addresses

  - The MMU is the hardware that uses page tables, which may:
    - Be a single large table (wasteful, even for 32-bit machines)
    - Be a multi-level to save space for sparse allocations
    - Use the kernel to allocate pages from a free list
    - Use  TLB to speed up memory accesses



## Lecture 8: Page Replacement

- As you go down the computer memory hierarchy, capacity increases, but speed decreases
- We want to hide the hierarchy from the user
  - Each level wants to pretend it has the speed of the layer above it and the capacity of the layer below it
  - The memory used by all the processes may exceed the amount of physical memory
    - Not all of them may be in use at the same time
  - Only keep referenced pages in memory, put others on disk
    - Swap pages back to memory when they're needed
- Page replacement algorithms
  - Optimal - replace the page that won't be used for the longest
  - Random - replace a random page
  - FIFO - replace the oldest page first
  - Least Recently Used (LRU) - replace the page that hasn't been used in the longest time
- Implementing LRU in hardware has to search all pages
  - You could implement it by keeping a counter for each page
  - For each page reference, save the system clock into the counter
  - For replacement, scan through the pages and find the one with the oldest clock
- Implementing LRU in software is too expensive
  - Create a doubly linked list of pages
  - For each page reference, move it to the front of the list
  - For replacement, remove from the back of the list
  - It requires six pointer updates for each page reference, and also creates a high contention bottleneck for multiple processors
- Implementing LRU in practice isn't going to work
  - We settle for approximate LRU
    - LRU is an approximation of the optimal case anyways
  - There's lots of different tweaks you can do to implement it more efficiently
  - We'll be looking at the clock algorithm, but there's also:
    - Least Frequently Used (LFU), 2Q, Adaptive Replacement Cache (ARC)
- Clock Algorithm
  - Data structures:
    - Keeps a circular list of pages in memory
    - Uses a reference bit for each page in memory
    - Has a "hand" (iterator) pointing to the last element examined
  - Algorithm, to insert a new page:
    - Check the hand's reference bit, if it's `0`, then place the page and advance hand
    - If the reference bit is `1`, set it to `0`, advance the hand, and repeat
- Swapping to disk is less important now
  - Memory is cheap, and has quite high capacity
    - Some systems may not even have swap
  - Larger page sizes allow for speedup
    - Trade more fragmentation for more TLB coverage
  - With 64 bits, we have a huge address space compared to memory capacity
    - Lots of room to use virtual addresses for other uses (`mmap`)
- Page replacement algorithms aim to reduce page faults
  - We saw the following:
    - Optimal (good for comparison, but not realistic)
    - Random (actually works surprisingly well, avoids the worst case)
    - FIFO (easy to implement, but Belady's anomaly)
    - LRU (gets close to optimal, but expensive to implement)
    - Clock (a decent approximation of LRU)



## Lecture 9: Threads

- Threads are like processes with shared memory

  - The same principle as a process, except by default, they share memory
    - They have their own registers, program counter, and stack
  - They have the same address space, so changes appear in each thread
  - You need to explicitly state if any memory is specific to a thread (TLS)

- One process can have multiple threads

  - By default, a process just executes code in its own address space
  - Threads allow multiple executions in the same address space
  - They're lighter weight and less expensive to create than processes
    - They share code, data, file descriptors, etc.

- Assuming one CPU, threads can express concurrency

  - A process can appear like it's executing in multiple locations at once

    - However, the OS is just context switching within a process

  - It may be easier to program concurrently

    - E.g. handle a web request in a new thread

  - ```c
    while (true) {
        struct request *req = get_request();
        create_thread(process_request, req);
    }
    ```

- Threads are lighter weight than processes

  - |                 Process                  |                Thread                 |
    | :--------------------------------------: | :-----------------------------------: |
    |        Independent code/data/heap        |         Shared code/data/heap         |
    |          Independent execution           | Must live within an executing process |
    |     Has its own stack and registers      |    Has its own stack and registers    |
    | Expensive creation and context switching | Cheap creation and context switching  |
    |    Completely removed from OS on exit    |  Stack removed from process on exit   |

  - When a process dies, all threads within it die as well

- We'll be using POSIX threads

  - For Windows, there's a Win32 thread, but we're going to use *UNIX threads
  - `#include <pthread.h>` - in your source file
  - `-pthread` - compile and link the `pthread` library
  - All the `pthread` functions have documentation in the `man` pages

- You create threads with `pthread_create`

  - ```c
    int pthread_create(pthread_t* thread,
                       const pthread_attr_t* attr,
                       void* (*start_routine)(void*),
                       void* arg);
    ```

    - `thread` - creates a handle to a thread at a pointer location
    - `attr` - thread attributes (`NULL` for defaults, more details later)
    - `start_routine` - function to start execution
    - `arg` - value to pass to `start_routine`
    - Returns `0` on success, error number otherwise (contents of *thread are undefined)

- Creating threads is a bit different than processes

  - ```c
    #include <pthread.h>
    #include <stdio.h>
    
    void* run(void*) {
        printf("In run\n");
        return NULL;
    }
    
    int main() {
        pthread_t thread;
        pthread_create(&thread, NULL, &run, NULL);
        printf("In main\n");
    }
    ```

  - What are some differences? Are we missing anything?

- The `wait` equivalent for threads - `join`

  - ```c
    int pthread_join(pthread_t thread,
                     void** retval)
    ```

    - `thread` - wait for this thread to terminate (`thread` must be joinable)
    - `retval` - stores exit status of `thread` (set by `pthread_exit`) to the location pointed by `*retval`
      - If cancelled, returns `PTHREAD_CANCELLED`
      - `NULL` is ignored
    - Returns `0` on success, error number otherwise

  - Only call this one time per thread

    - Multiple calls on the same thread leads to undefined behavior

- Previous example that waits properly

  - ```c
    #include <pthread.h>
    #include <stdio.h>
    
    void* run(void*) {
        printf("In run\n");
        return NULL;
    }
    
    int main() {
        pthread_t thread;
        pthread_create(&thread, NULL, &run, NULL);
        printf("In main\n");
        pthread_join(thread, NULL);
    }
    ```

  - Now we joined, the thread's resources are cleaned up

- Ending a thread early (think of `exit`)

  - ```c
    void pthread_exit(void *retval);
    ```

    - `retval` - return value passed to function that calls `pthread_join`

  - Note: `start_routine` returning is equivalent of calling `pthread_exit`

    - Think of the difference between returning from `main` and `exit`

  - `pthread_exit` is called implicitly when the `start_routine` of a thread returns

- Detached threads

  - Joinable threads (the default) wait for someone to call `pthread_join`, then they release their resources

  - Detached threads release their resources when they terminate

  - ```c
    int pthread_detach(pthread_t thread);
    ```

    - `thread` - marks the thread as detached
    - Returns `0` on success, error number otherwise

  - Calling `pthread_detach` on an already detached thread is undefined behavior

- Detached threads aren't joined

  - ```c
    #include <pthread.h>
    #include <stdio.h>
    
    void* run(void*) {
        printf("In run\n");
        return NULL;
    }
    
    int main() {
        pthread_t thread;
        pthread_create(&thread, NULL, &run, NULL);
        pthread_detach(thread);
        printf("In main\n");
    }
    ```

    - Code just prints `"In main"`, why?

- `pthread_exit` in `main` waits for all detached threads to finish

  - ```c
    #include <pthread.h>
    #include <stdio.h>
    
    void* run(void*) {
        printf("In run\n");
        return NULL;
    }
    
    int main() {
        pthread_t thread;
        pthread_create(&thread, NULL, &run, NULL);
        pthread_detach(thread);
        printf("In main\n");
        pthread_exit(NULL);
    }
    ```

    - Code now works as expected

- You can use attributes to get/set thread variables

  - ```c
    size_t stacksize;
    pthread_attr_t attributes;
    pthread_attr_init(&attributes);
    pthread_attr_getstacksize(&attributes, &stacksize);
    printf("Stack size = %i\n", stacksize);
    pthread_attr_destroy(&attributes)l
    ```

    - Running this should show a stack size of 8MiB (on most Linux systems)

  - You can also set a thread state to joinable

    - ```c
      pthread_attr_setdetachstate(&attributes,
                                  PTHREAD_CREATE_JOINABLE);
      ```

- Multithreading models

  - Where do we implement threads?
    - We can either do user or kernel threads
  - User threads are completely in user space
    - Kernel doesn't treat your threaded process any differently
  - Kernel threads are implemented in kernel space
    - Kernel manages everything for you, and can treat threads specially

- Thread support requires a thread table

  - Similar to the process table we saw previously
    - It could be in user space or kernel space depending
  - For user threads, there also needs to be a runtime system to determine scheduling
  - In both models, each process can contain multiple threads

- We could avoid system calls, or let a thread block everything

  - For pure user level threads (again, no kernel support):
    - Very fast to create and destroy, no system call, no context switches
    - One thread that blocks blocks the entire process (kernel can't distinguish)
  - For kernel level threads:
    - Slower, creation involves system calls
    - If one thread blocks, the kernel can schedule another one

- All threading libraries you use run in user mode

  - The thread library maps user threads to kernel threads
  - Many-to-one: threads completely implemented in user space, the kernel only sees one process
  - One-to-one: one user thread maps directly to one kernel thread, the kernel handles everything
  - Many-to-many: many user level threads map to many kernel level threads

- Many-to-one is pure user space implementation

  - It's fast (as outlined before) and portable
    - It doesn't depend on the system, it's just a library
  - Drawbacks are that one thread blocking causes all threads to block
    - Also we cannot execute threads in parallel
      - The kernel will only schedule a process to run

- One-to-one just uses the kernel thread implementation

  - There's just a thin wrapper around the system calls to make it easier to use
  - Exploits the full parallelism of your machine
    - The kernel can schedule multiple threads simultaneously
  - We do however need to use a slower system call interface, and we lose some control
  - Typically, this is the actual implementation used, we'll assume this for Linux

- Many-to-many is a hybrid approach

  - The idea is that there are more user level threads than kernel level threads
    - Cap the number of kernel level threads to the number we could run in parallel
  - We can get the most out of multiple CPUs while reducing the number of system calls
  - However, this leads to a complicated thread library
    - Depending on your mapping luck, you may block other threads

- Threads complicate the kernel

  - How should `fork` work with a process with multiple threads?
    - Copy all threads to the new process, in whatever state they're in?
      - How would this get out of hand?
  - Linux only copies the thread that called `fork` into a new process
    - If it hits `pthread_exit`, it'll always exit with status `0` (at least as far as I can tell)
  - There's `pthread_atfork` (not covered in this course) to control what happens

- Signals are sent to a process

  - Which thread should receive a signal? All of them?
  - Linux will just pick one random thread to handle the signal
    - Makes concurrency hard, any thread could be interrupted

- Instead of many-to-many, you can use a thread pool

  - The goal of many-to-many thread mapping is to avoid creation costs
  - A thread pool creates a certain number of threads and a queue of tasks (maybe as many threads as CPUs in the system)
  - As requests come in, wake them up and give them work to do
  - Reuse them, when there's no work, put them to sleep

- Our next complication

  - Let's create a program that spawns 8 threads
    - Each thread increments the same variable 10,000 times
  - What should the final value of the variable be?
    - The initial value of the variable is `0`
  - Run `examples/lecture-13/pthread-datarace`
    - Can you fix it?

- Both processes and (kernel) threads enable parallelization

  - We explored threads, and related them to something we already know (processes)
    - Threads are lighter weight, and share memory by default
    - Each process can have multiple (kernel) threads
    - Most implementations use one-to-one user-to-kernel thread mapping
    - The OS has to manage what happens during a fork or signal
    - We now have synchronization issues



## Lecture 10: Locks

- Data races can occur when sharing data

  - A data race is when two concurrent actions access the same variable and at least one of them is a write

- Atomic operations are indivisible

  - Any atomic instruction you may assume happens all at once
  - This means you cannot preempt it
  - However, between two atomic instructions, you may be preempted

- Three Address Code (TAC) is intermediate code used by compilers

  - TAC is mostly used for analysis and optimization by compilers
  - Statements represent one fundamental operation (assume each is atomic)
    - Useful to reason about data races and easier to read than assembly
  - Statements have the form `result := operand_1 operator operand_2`

- GIMPLE is the TAC used by GCC

  - To see the GIMPLE representation of your compilation, use:
    - `-fdump-tree-gimple` flag
  - To see all of the three address code generated by the compiler, use:
    - `-fdump-tree-all`
  - GIMPLE is easier to reason about your code at a low-level without assembly

- `lecture-13/pthread-datarace.c` data race

  - Instead of `count`, we'll look at `pcount` (the pointer to count, which is global)

  - The GIMPLE is the following:

    - ```
      D.1 = *pcount;
      D.2 = D.1 + 1;
      *pcount = D.2;
      ```

  - Assuming that two threads execute this once each and initially `*pcount = 0`, what are the possible values of `pcount`?

- To analyze data races, you have to assume all preemption possibilities

  - Let's call the read and write from thread 1 `R1` and `W1` (`R2` and `W2` from thread 2)

  - We'll assume no re-ordering of instructions: always read then write in a thread

  - All possible orderings:

    - | Order |      |      |      | `*pcount` |
      | :---: | :--: | :--: | :--: | :-------: |
      | `R1`  | `W1` | `R2` | `W2` |     2     |
      | `R1`  | `R2` | `W1` | `W2` |     1     |
      | `R1`  | `R2` | `W2` | `W1` |     1     |
      | `R2`  | `W2` | `R1` | `W1` |     2     |
      | `R2`  | `R1` | `W2` | `W1` |     1     |
      | `R2`  | `R1` | `W1` | `W2` |     1     |

- You can create mutexes statically or dynamically

  - ```c
    pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t m2;
    
    pthread_mutex_init(%m2, NULL);
    ...
    pthread_mutex_destory(&m1);
    pthread_mutex_destory(&m2);
    ```

  - If you want to include attributes, you need to use the dynamic version

- Everything within the lock and unlock is a critical section

  - ```c
    // code
    pthread_mutex_lock(&m1);
    // protected code
    pthread_mutex_unlock(&m1);
    // more code
    ```

  - Everything within the `lock` and `unlock` is protected

  - Be careful to avoid deadlocks if you are using multiple mutexes

  - Also a `pthread_mutex_trylock` if needed

- Adding a lock to prevent the data race

  - ```c
    // code
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    static int counter = 0;
    
    void* run(void* arg) {
        for (int i = 0; i < 100; ++i) {
            pthread_mutex_lock(&mutex);
            ++counter;
            pthread_mutext_unlock(&mutex);
        }
    }
    
    int main(int argc, char *argv[]) {
        // Create 8 threads
        // Join 8 threads
        pthread_mutex_destroy(&mutex);
        printf("counter = %i\n", counter);
    }
    ```

- A critical section needs to atomically execute multiple instructions

  - Safety (aka mutual exclusion)
    - There should only be a single thread in a critical section at once
  - Liveness (aka progress)
    - If multiple threads reach a critical section, one must proceed
    - The critical section can't depend on outside threads
      - You can mess up and deadlock (threads don't make progress)
    - Bounded waiting (aka starvation-free)
      - A waiting thread must eventually proceed

- Critical sections should also have minimal overhead

  - Efficient
    - You don't want to consume resources while waiting
  - Fair
    - You want each thread to wait approximately the same time
  - Simple
    - It should be easy to use, and hard to misuse

- Similar to libraries, you want layers of synchronization

  - Properly synchronized application => high-level synchronization primitives => hardware-provided low-level atomic operations

- You could use a lock to implement critical sections

  - Assuming a uniprocessor OS, you could implement locks as follows:

    - ```c
      void lock() {
          disable_interrupts();
      }
      
      void unlock() {
          enable_interrupts();
      }
      ```

  - This would disable concurrency (assuming it ignores signals and interrupts)

    - Not going to work on multiprocessors (and OS won't let you change hardware)

- Let's try to implement a lock in software

  - ```c
    void init(int *l) {
    	*l = 0;
    }
    
    void lock(int *l) {
        while (*l == 1);
        *l = 1;
    }
    
    void unlock(int *l) {
        *l = 0;
    }
    ```

  - What's the issue with this implementation?

    - It's not safe (both threads can be in the critical section)
    - It's not efficient (it wastes CPU cycles, busy wait)

- You can implement locks in software with minimal hardware

  - You hardware requirements just have to ensure:
    - Loads and stores are atomic
    - Instructions execute in order
  - There's 2 main algorithms you could use:
    - Peterson's algorithm and Lamport's bakery algorithm
  - The problem is that they don't scale well, and processors execute out-of-order

- Let's assume a magical atomic function - `compare_and_swap`

  - `compare_and_swap(int *p, int old, int new)` is atomic

    - It returns the original value pointed to
    - It only swaps if the original value equals `old` and changes it to `new`

  - Let's give it another shot:

    - ```c
      void init(int *l) {
          *l = 0;
      }
      
      void lock(int *l) {
          while (compare_and_swap(l, 0, 1));
          *l = 1;
      }
      
      void unlock(int *l) {
          *l = 0;
      }
      ```

- What we implement is essentially a spinlock

  - Compare and swap is a common atomic hardware instruction
  - On x86, this is the `cmpxchg` instruction (compare and exchange)
  - However, it still has this "busy wait" problem
  - Consider a uniprocessor system, if you can't get the lock, you should yield
    - Let the kernel schedule another process, that may free the lock
  - On a multiprocessor machine, it depends

- Let's add a yield

  - ```c
    void lock(int *l) {
        while (compare_and_swap(l, 0, 1)) {
            yield();
        }
        *l = 1;
    }
    ```

  - Now we have a thundering herd problem

    - Multiple threads may be waiting on the same lock

  - We have no control over who gets the lock next

    - We need to be able to reason about it (FIFO is ok)

- We can add a wait queue to the lock

  - ```c
    void lock(int *l) {
        if (compare_and_swap(l, 0, 1)) {
            // add myself to the wait queue
            yield();
        }
        *l = 1;
    }
    
    void unlock(int *l) {
        *l = 0;
        if (/* threads in wait queue */) {
            // wake up one thread
        }
    }
    ```

  - There are 2 issues with this:

    - Lost wakeup
    - The wrong thread gets the lock

- Lost wakeup example

  - ```c
    void lock(int *l) {
        if (compare_and_swap(l, 0, 1)) {
            // add myself to the wait queue
            yield();
        }
        *l = 1
    }
    
    void unlock(int *l) {
        *l = 0;
        if (/* threads in wait queue */) {
            // wake up one thread
        }
    }
    ```

    - Assume we have thread 1 (`T1`) and thread 2 (`T2`), thread 2 holds the lock
      - `T1` runs line 2 and fails, swap to `T2` that runs lines 11-13, `T1` runs lines 3-4
        - `T1` will never get woken up

- Wrong thread getting the lock example

  - ```c
    void lock(int *l) {
        if (compare_and_swap(l, 0, 1)) {
            // add myself to the wait queue
            yield();
        }
        *l = 1
    }
    
    void unlock(int *l) {
        *l = 0;
        if (/* threads in wait queue */) {
            // wake up one thread
        }
    }
    ```

    - Assume we have `T1`, `T2`, and `T3`. `T2` holds the lock, `T3` is in queue
      - `T2` runs line 10, swap to `T1` which runs line 2 and succeeds
        - `T1` just stole the lock from `T3`

- To fix these problems, we can use two variables (one to guard)

  - ```c
    typedef struct {
        int lock;
        int guard;
        queue_t *q;
    } mutex_t;
    
    void lock(mutex_t *m) {
        while (compare_and_swap(m->guard, 0, 1));
        if (m->lock == 0) {
            m->lock = 1; // acquire mutex
            m->guard = 0;
        } else {
            enqueue(m->q, self);
            m->guard = 0;
            yield();
        }
    }
    
    void unlock(mutex_t *m) {
        while (compare_and_swap(m->guard, 0, 1));
        if (queue_empty(m->q)) {
            // release lock, no one needs it
            m->lock = 0;
        } else {
            // direct transfer mutex to next thread
            wakeup(dequeue(m->q));
        }
        m->guard = 0;
    }
    ```

- Remember what causes a data race

  - A data race is when two concurrent actions access the same variable and at least one of them is a write
  - We could have as many readers as we want
    - We don't need a mutex as long as nothing writes at the same time
  - We need different lock modes for reading and writing

- Read-write locks

  - With mutexes/spinlocks, you have to lock the data, even for a read since you don't know if a write could happen
  - Reads can happen in parallel as long as there's no write
  - Multiple threads can hold a read lock (`pthread_relock_rdlock`), but only one thread may hold a write lock (`pthread_rwlock_wrlock`) and will wait until the current readers are done

- We can use a guard to keep track of readers

  - ```c
    typedef struct {
        int nreader;
        lock_t lock;
        lock_t guard;
        queue_t *q;
    } rwlock_t;
    
    void write_lock(rwlock_t *l) {
        lock(&l->lock)
    }
    
    void write_unlock(rwlock_t *l) {
        unlock(&l->lock);
    }
    
    void read_lock(rwlock_t *m) {
        lock(&l->guard);
        ++nreader;
        if (nreader == 1) { // first reader
            lock(&l->lock);
        }
        unlock(&l->guard);
    }
    
    void read_unlock(rwlock_t *m) {
        lock(&l->guard);
        --nreader;
        if (nreader == 0) { // last reader
        	unlock(&l->lock);
        }
        unlock(&l->guard);
    }
    ```

- We want critical sections to protect against data races

  - We should know what data races are, and how to prevent them
    - Mutex or spinlocks are the most straightforward locks
    - We need hardware support to implement locks
    - We need some kernel support for wake up notifications
    - If we know we have a lot of readers, we should use a read-write lock



## Lecture 11: Locking

- Locks ensure mutual exclusion

  - Only one thread at a time can be between the `lock` and `unlock` calls
  - It does not help you ensure ordering between threads
  - Assume you had a circular buffer you want to use in a producer/consumer scenario
    - e.g. `ls | wc`

- Semaphores are used for signaling

  - Semaphores have a `value` that's shared between threads/processes

  - ```c
    #include <semaphore.h>
    int sem_init(sem_t *sem, int pshared, unsigned int value)
    ```

  - There may be up to `value` number of things with the semaphore simultaneously

  - It has two fundamental operations `wait` and `post`

    - `wait` decrements the value atomically
    - `post` increments the value atomically

  - If `wait` will not return until the value is greater than `0`

- Semaphore API is similar to `pthread` locks

  - ```c
    #include <semaphore.h>
    
    int sem_init(sem_t *sem, int pshared, unsigned int value)
    int sem_destroy(set_t *sem)
    int sem_post(set_t *sem)
    int sem_wait(sem_t *sem)
    int sem_trywait(sem_t *sem)
    ```

  - All functions return `0` on success

  - The `pshared` argument is a boolean, you can set it to `1` for IPC

    - For IPC, the semaphore needs to be in shared memory

- How could we make this print `"Thread 1"` then `"Thread 2"`

  - ```c
    #include <pthread.h>
    #include <stdio.h>
    #include <semaphore.h>
    #include <stdlib.h>
    
    void* p1(void* arg) { printf("Thread 1\n"); return NULL; }
    void* p2(void* arg) { printf("Thread 2\n"); return NULL; }
    
    int main(int argc, char *argv[]) {
        pthread_t thread[2];
        pthread_create(&thread[0], NULL, p1, NULL);
        pthread_create(&thread[1], NULL, p2, NULL);
        pthread_join(thread[0], NULL);
        pthread_join(thread[1], NULL);
        return EXIT_SUCCESS;
    }
    ```

- This code prints `"Thread 1"`, then `"Thread 2"`

  - ```c
    static sem_t sem;
    
    void* p1(void* arg) {
        printf("Thread 1\n");
        sem_post(&sem);
    }
    
    void* p2(void* arg) {
        sem_wait(&sem);
        printf("Thread 2\n");
    }
    
    int main(int argc, char *argv[]) {
        sem_init(&sem, 0, 0);
        /* rest as before */
    }
    ```

- No matter which thread executes first, we get the same order

  - The `value` is initially `0`
  - Assume `"Thread 2"` executes first
    - It executes `sem_wait`, which is `0`, and doesn't continue
  - `"Thread 1"` doesn't have to wait, it prints first before it increments the `value`
  - `"Thread 2"` can execute its print statement
  - What happens if we initialized the `value` to `1`

- Using a semaphore as a mutex, note the `value`

  - ```c
    ...
    static sem_t sem;
    static int counter = 0;
    
    void* run(void* arg) {
        for (int i = 0; i < 100; i++) {
            sem_wait(&sem);
            ++counter;
            sem_post(&sem);
        }
    }
    
    int main(int argc, char *argv[]) {
        sem_init(&sem, 0, 1);
        // Create 8 threads
        // Join 8 threads
        printf("counter = %i\n", counter);
    }
    ```

- Can we come up with a solution for a producer/consumer problem?

  - Assume you have a circular buffer
  - The producer should write to the buffer
    - As long as the buffer is not full
  - The consumer should read to the buffer
    - As long as the buffer is not empty

- We could create two semaphores, what `value`s should we use?

  - ```c
    sem_t full;
    sem_t empty;
    
    sem_init(&full, 0, /* ??? */);
    sem_init(&empty, 0, /* ??? */);
    
    void producer() {
        // produce data
        sem_wait(empty);
        // fill a slot
        sem_post(full);
    }
    
    void consumer() {
        sem_wait(full);
        // empty a slot
        sem_post(empty);
        // consume data
    }
    ```

- The previous `value`s depend on the buffer size

  - `full` should always be initialized to `0`
  - `empty` should be initialized to the size of the buffer `N`
  - Do we need any extra locking?
    - No, if there's a single producer and consumer
    - Yes, otherwise

- Monitors are built into some languages

  - With OOP, developers wanted something easier to use
  - Could mark a method as monitored, and let the compiler handle locking
    - An object can only have one thread active in its monitored methods
  - It's basically one mutex per object, created for you
    - The compiler inserts calls to lock and unlock

- Java's `synchronized` keyword is an example of a monitor

  - ```java
    public class Account {
        int balance;
        public synchronized void deposit(int amount) { balance += amount; }
        public synchronized void withdraw(int amount) { balance -= amount; }
    }
    ```

    - The compiler transforms to:

      - ```java
        public void deposit(int amount) {
            lock(this.monitor);
            balance += amount;
            unlock(this.monitor);
        }
        
        public void withdraw(int amount) {
            lock(this.monitor);
            balance -= amount;
            unlock(this.monitor);
        }
        ```

- Condition variables behave like semaphores

  - You can create your own custom queue of threads

  - ```c
    #include <pthread.h>
    
    int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr+t *attr);
    int pthread_cond_destroy(pthread_cond_t *cond);
    int pthread_cond_signal(pthread_cond_t *cond);
    int pthread_cond_broadcast(pthread_cond_t *cond);
    int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
    int pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex,
                               const struct timespec *abstime);
    ```

  - The `wait` functions add this thread to the queue

    - `signal` wakes up one thread, `broadcast` wakes up all threads

- Condition variables must be paired with a mutex

  - Any calls to `wait`, `signal`, and `broadcast` must already hold the mutex
  - Why? `wait` needs to add itself to the queue safely (without data races)
    - It needs the mutex as an argument to unlock it before going to sleep
  - One mutex can also protect multiple condition variables
  - We'll only consider calls to `wait` and `signal`

- We can use condition variables for our producer/consumer

  - ```c
    pthread_mutex_t mutex;
    int nfilled;
    pthread_cond has_filled;
    pthread_cond has_empty;
    
    void producer() {
        // produce data
        pthread_mutex_lock(&mutex);
        if (nfilled == N) {
            pthread_cond_wait(&has_empty, &mutex);
        }
        // fill a slot
        ++nfilled;
        pthread_cond_signal(&has_filled);
        pthread_mutex_unlock(&mutex);
    }
    
    void consumer() {
        pthread_mutex_lock(&mutex);
        if (nfilled == 0) {
            pthread_cont_wait(&has_filled, &mutex);
        }
        // empty a slot
        --nfilled;
        pthread_cond_signal(&has_empty);
        pthread_mutex_unlock(&mutex);
        // consume data
    }
    ```

- Condition variables serve a similar purpose as semaphores

  - You can think of semaphores as a special case of condition variables
    - They'll go to sleep when the value is `0`, when it's greater than `0`, they wake up
  - You can implement one using the other, however, it can get messy
  - For complex conditions, condition variables offer much better clarity

- Locking granularity is the extent of your locks

  - You need locks to prevent data races
  - Lock large sections of your program, or divide the locks and use smaller sections
    - Lab 3
  - Things to consider about locks
    - Overhead
    - Contention
    - Deadlocks

- Locking overheads

  - Memory allocated
  - Initialization and destruction time
  - Time to acquire and release locks
  - The more locks you have, the greater each cost is going to be

- You do not want deadlocks

  - The more locks you have, the more you have to worry about deadlocks
  - Conditions for deadlocking
    - Mutual exclusion (of course for simple locks)
    - Hold and wait (you have a lock and try to acquire another)
    - No preemption (we can't take simple locks away)
    - Circular wait (waiting for a lock held by another process)

- A simple deadlock example

  - Consider two processes trying to get two locks:

    - Thread 1:

      - ```
        Get Lock 1
        Get Lock 2
        Release Lock 2
        Release Lock 1
        ```

    - Thread 2:

      - ```
        Get Lock 2
        Get Lock 1
        Release Lock 1
        Release Lock 2
        ```

    - Thread 1 gets Lock 1, then Thread 2 gets Lock 2, now they both wait for each other => deadlock

- You can ensure order to prevent deadlocks

  - ```c
    void f1() {
    	locktype_lock(&l1);
    	locktype_lock(&l2);
    	// protected code
    	locktype_unlock(&l2);
    	locktype_unlock(&l1);
    }
    ```

  - This code will not deadlock, you can only get `l2` if you have `l1`

- You could also prevent a deadlock by using `trylock`

  - Remember, for `pthread`, there's `trylock` that returns `0` if it gets the lock

  - ```c
    void f2() {
        locktype_lock(&l1);
        while (locktype_trylock(&l2) != 0) {
            locktype_unlock(&l1);
            // wait
            locktype_lock(&l1);
        }
        // protected code
        locktype_unlock(&l2);
        locktype_unlock(&l1);
    }
    ```

  - This code will not deadlock, it will give up `l1` if it can't get `l2`

- We explored more advanced locking

  - Before we did mutual exclusion, now we can ensure order
    - Semaphores are an atomic value that can be used for signaling
    - Condition variables are clearer for complex condition signaling
    - Locking granularity matters, you'll find out in Lab 3
    - You must prevent deadlocks



## Lecture 12: Memory Allocation

- Static allocation is the simplest strategy
  - Create a fixed size allocation in your program
    - e.g. `char buffer[4096]`
  - When the program loads, the kernel sets aside that memory for you
  - That memory exists as long as your process does, no need to free
- Dynamic allocation is often required
  - You may only conditionally require memory
    - Static allocations are sometimes wasteful
  - You may not know the size of the allocation
    - Static allocations need to account for the maximum size
  - Where do you allocate memory?
    - You can either allocate on the stack or on the heap
- Stack allocation is mostly done for you in C
  - Think of normal variables
    - e.g. `int x`
  - The compiler internally inserts `alloca` calls
    - e.g. `int *px = (int*) alloca(4);`
  - Whenever the function that called alloca` returns, it frees all the memory
    - This just restores the previous stack pointer
  - This won't work if you try to use the memory after returning
- You've used dynamic allocation before
  - These are the `malloc` family of functions
  - The most flexible way to use memory, but is also the most difficult to get right
  - You have to properly handle you memory lifetimes, and `free` exactly once
  - Also there's a new concern - fragmentation
- Fragmentation is a unique issue for dynamic allocation
  - You allocate memory in different sized contiguous blocks
    - Compaction is not possible and every allocation decision is permanent
  - A fragment is a small contiguous block of memory that cannot handle an allocation
    - You can think of it as a "hole" in memory, wasting space
  - There are three requirements for fragmentation:
    - Different allocation lifetimes
    - Different allocation sizes
    - Inability to relocate previous allocations
- There's internal and external fragmentation
  - External fragmentation occurs when you allocate different sized blocks
    - There's no room for an allocation between the blocks
  - Internal fragmentation occurs when you allocate fixed size blocks
    - There's wasted space within a block
- We want to minimize fragmentation
  - Fragmentation is just wasted space, which we should prevent
  - We want to reduce the number of "holes" between blocks of memory
    - If we have holes, we'd like to keep them as large as possible
  - Our goal is to keep allocating memory without wasting space
- Allocator implementations usually use a free list
  - They keep track of free blocks of memory by chaining them together
    - Implemented with a linked list
  - We need to be able to handle a request of any size
  - For allocation, we choose a block large enough for the request
    - Remove it from the free list
  - For deallocation, we add the block back to the free list
    - If it's adjacent to another free block, we can merge them
- There are three general heap allocation strategies
  - Best fit: choose the smallest block that can satisfy the request
    - Needs to search through the whole list (unless there's an exact match)
  - Worst fit: choose largest block (most leftover space)
    - Also has to search through the list
  - First fit: choose first block that can satisfy request
- Best fit and worst fit are most slow
  - Best fit: tends to leave very large holes and very small holes
    - Small holes may be useless
  - Worst fit: simulation says it's the worst in terms of storage utilization
  - First fit: tends to leave "average" sized holes
- The buddy allocator restricts the problem
  - Typically allocation requests are of size `2^n`
  - Restrict allocations to be powers of `2` to enable a more efficient implementation
    - Split blocks into `2` until you can handle the request
  - We want to be able to do fast searching and merging
- You can implement the buddy allocator using multiple lists
  - We restrict the requests to be `2^k`, `0 <= k <= N` (round up if needed)
  - Our implementation would use `N + 1` free lists of blocks for each size
  - For a request of size `2^k`, we search the free list until we find a big enough block
    - Search `k`, `k + 1`, `k + 2`, ... until we find one
      - Recursively divide the block if needed until it's the correct size
        - Insert "buddy" blocks into free lists
  - For deallocations, we coalesce the buddy blocks back together
    - Recursively coalesce the blocks if needed
- Buddy allocators are used in Linux
  - Advantages
    - Fast and simple compared to general dynamic memory allocation
    - Avoids external fragmentation by keeping free physical pages contiguous
  - Disadvantages
    - There's always internal fragmentation
      - We always round up the allocation size if it's not a power of `2`
- Slab allocators take advantage of fixed size allocations
  - Allocate objects of same size from a dedicated pool
    - All structures of the same type are the same size
  - Every object type has its own pool with blocks of the correct size
    - This prevents internal fragmentation
- Slab is a cache of "slots"
  - Each allocation size has a corresponding slab of slots (one slot holds one allocation)
  - Instead of a linked list, we can use a bitmap (there's a mapping between bit and slot)
    - For allocations we set the bit and return the slot
    - For deallocations, we just clear the bit
  - The slab can be implemented on top of the buddy allocator
- Each slab can be allocated using the buddy allocator
  - We can reduce internal fragmentation if slabs are located adjacently
- The kernel has to implement its own memory allocations
  - The concepts are the same for user space memory allocation (the kernel just gives them more contiguous virtual memory pages)
    - There's static and dynamic allocations
    - For dynamic allocations, fragmentation is a big concern
    - Dynamic allocation returns blocks of memory
      - Fragmentation between blocks is external
      - Fragmentation within a block is internal
    - There's three general allocation strategies for different sized allocations
      - Best fit
      - Worst fit
      - First fit
    - Buddy allocator is a real world restricted implementation
    - Slab allocator takes advantage of fixed size objects to reduce fragmentation



## Lecture 13: Disks

- Access speed depends on locality
  - Sectors on same track can be read continuously
  - Switching tracks needs repositioning of the arm
    - Repositioning the are is expensive
- You physically address a HDD using Cylinder-Head-Sector (CHS)
  - Data has the following coordinates (multi-dimensional polar coordinates):
    - Platter: which revolving platter (addressed as head) [`z`-axis]
    - Track: which track lane on platter (historically cylinder) [`||r||`]
    - Sector: which sector on track [`theta`]
  - The historical CHS has an approximate 8GB limit of addressable space
    - `(512 bytes/sector) x (63 sectors/track) x (255 heads (tracks/cylinder)) x (1024 cylinders)
  - LBA (Logical Block Addressing) uses one number to address any block and is not limited to 8GB
- Shingled Magnet Recording (SMR)
  - The write head only writes in the center of a track and has unused padding
  - You can't write to this padding without destroying neighboring tracks
  - SMR however, allows you to write over the padding, if you do it sequentially
  - Drive performance may suffer, but it's easier to increase capacity
- HDDs have latencies dependent on the distance travelled
  - Rotational delay: physically rotate the disk to get to the correct sector
    - Typically 4-8ms (average delay is half of a full rotation)
  - Seek time: moving the disk arm to get to the correct track
    - Typically 0.5-2ms
  - Transfer time: how long it takes to read bytes from the disk
    - Typically the maximum transfer speed is 125MB/s
- Calculating transfer rate
  - The total time, `T`, is equal to rotational delay + seek time + transfer time
  - The transfer rate, `R`, is equal to size of the transfer / `T`
  - What is the transfer rate of:
    - Large sequential accesses?
    - Small random accesses?
- We should use HDDs sequentially whenever possible
- Logical mapping could place all sectors next to each other
  - You may want to offset the sectors in different tracks so the head has time to settle
    - Track skew allows the disk to be efficient with minimal head movement
- You may want more flexibility than the default mapping
  - Pros
    - Simple to program
    - Default mapping reduces seek time for sequential access
  - Cons
    - Filesystem can't inspect or try to optimize the mapping
    - Trying to reverse the mapping is difficult
      - Number of sectors per track changes
      - Disk silently remaps bad sectors
- A cache can significantly speed up disk transfers
  - Disks have some internal memory (WD Red - 64MB) for caching
  - Implement a read-ahead "track buffer"
    - Read the entire contents of the track into memory during the rotational delay
  - Write caching with volatile memory
    - Write back: claim data is written to disk
      - Fast, but there's data loss if there's a power failure
      - Write through: acknowledge after data is physically written
- We can schedule disk accesses
  - We want to minimize the time the disk moves without reading or writing data
  - FCFS: schedule requests in the order received
    - Fair, but it has a high seek and rotation cost
  - SSTF: shortest seek time first
    - Handle the nearest cylinder/sector next
      - Pro: reduces arm movement (seek time)
      - Con: unfair, can starve some requests
- Elevator (aka SCAN or C-SCAN) sweeps across the disk
  - If a request comes in for a track already serviced this sweep, queue it for the next
- Elevator (or SSTF) ignores rotation
  - Shortest positioning time first (SPTF) is often the best strategy
    - The OS and disk need to work together to implement this
- Solid State Drives (SSD) are more modern
  - Use transistors (like RAM) to store data rather than magnetic disks
  - Pros:
    - No moving parts or physical limitations
    - Higher throughput and good random access
    - More energy efficient
    - Better space density
  - Cons:
    - More expensive
    - Lower endurance (number of writes)
    - More complicated to write drivers for
- An SSD contains pages
- SSDs using NAND Flash are much faster than HHDs
  - Pages are typically 4KB
  - Reading a page: 10 microseconds
  - Writing a page: 100 microseconds
  - Erasing a block: 1ms
- NAND Flash programming uses pages and blocks
  - You can only read complete pages and write to freshly erased pages
  - Erasing is done per block (a block has 128 or 256 pages)
    - An entire block needs to be erased before writing
  - Writing is slow (may need to create a new block)
- The OS can help speed up SSDs
  - SSDs need to garbage collect blocks
    - Move any pages that are still alive to a new block (may be overhead)
  - The disk controller doesn't know what blocks are still alive
    - SSD may think the disk is full, when a file could be deleted (not erased)
  - The OS can use the TRIM command to inform the SSD a block is unused
    - The SSD can freely erase the block without moving overhead
- So far we've been talking about single devices
  - Sometimes called Single Large Expensive Disk (SLED)
    - Just one large disk for data
      - Single point of failure
  - There's also Redundant Array of Independent Disks (RAID)
    - Data distributed on multiple disks
      - Use redundancy to prevent data loss
      - Use redundancy to increase throughput
- RAID 0 is called a striped volume
  - Data stripes (128KB and 256KB) are distributed over disls
- RAID 0 is for performance only
  - The data is stripped across all disks in the array (you can have more than 2)
  - Pro: faster parallel access, roughly `N` times speed
  - Con: any disk failure results in a data loss (more points of failure)
- RAID 1 mirrors all data across all disks
- RAID 1 is simple, but wasteful
  - Every disk in the array has a mirrored copy of all the data
  - Pros:
    - Good reliability, as long as one disk remains, no data loss
    - Good read perfromance
  - Cons:
    - High cost for redundancy (we can do better)
    - Write performance is the same as a single disk
- RAID 4 introduces parity
  - Data stripes distributed over disks with a dedicated parity disk (p = parity)
  - Parity stores xor of copies 1-3, any one copy can be reconstructed

- RAID 4 can use the parity drive to recover
  - With parity, we can use `1 - 1/N` of the available space
    - Requires at least 3 drives
  - Pros:
    - We can `(N - 1)` times performance (removing parity disk)
    - We can replace a failed disk and rebuild
  - Con: Write performance can suffer, every write must write to parity disk
- RAID 5 distributes parity across all disks
  - Data stripes distributed over disks and each disk takes turns with parity blocks
- RAID 5 is an improved RAID 4
  - It has all the sam pros as RAID 4
  - Write performance is improved, no longer a bottleneck on a single parity drive
- RAID 6 adds another parity block per stripe
- RAID 6 can recover from 2 simultaneous drive failures
  - Due to the extra parity, we can use `1 - 2/N` of the available space
    - Requires at least 4 drives
  - Write performance is slightly less than RAID 5, due to another parity calculation
- Disks enable persistence
  - We explored two kinds of disks: SSDs and HDDs
    - Magnetic disks have poor random access (need to be scheduled)
    - Shortest Positioning Time First (SPTF) is the best scheduling for throughput
    - SSDs are more like RAM, except accessed in pages and blocks
    - SSDs also need to work with the OS for best performance (TRIM)
    - Use RAID to tolerate failures and improve performance using multiple disks



## Lecture 14: Filesystems

- POSIX filesystem

  - Special symbols:
    - `.` - current directory
    - `..` - parent directory
    - `~` - user's home directory (`$HOME`)
  - Relative paths are calculated from current working directory (`$PWD`)

- You can access files sequentially or randomly

  - Sequential access
    - Each read advances the position inside the file
    - Writes are appended and the position set to the end afterwards
  - Random access
    - Records can be read/written to the file in any order
    - A specific position is required for each operation

- POSIX filesystem

  - ```c
    int open(const char *pathname, int flags, mode_t mode);
    // flags can specify which operations: O_RDWR, O_WRONLY, O_RDWR
    // also: O_APPEND moves the position to the end of the file initially
    
    off_t lseek(int fd, off_t offset, int whence);
    // lseek changes the position to the offset
    // whence can be one of: SEEK_SET, SEEK_CUR, SEEK_END
    //	set makes the offset absolute, cur and end are both relative
    ```

- Accessing directory API

  - ```c
    DIR *opendir(char *path); // open directory
    struct dirent *readdir(DIR *dir); // get next item
    int closedir(DIR *dir); // close directory
    
    void print_directory_contents(char *path) {
      DIR *dir = opendir(path);
      struct dirent *item;
      while (item = readdir(dir)) {
        printf("- %s\n", item->d_name);
      }
      closedir(path);
    }
    ```

- File tables are stored in the Process Control Block (PCB)

- Each process contains a file table in its PCB

  - A file descriptor is an index in the table
  - Each item points to a system-wide global open file table
  - The GOF table holds information about the seek position and flags
    - It also points to a VNode (supports read/write/etc.)
  - A VNode (virtual node) holds information about the file
    - VNodes can represent regular files, pipes, network sockets, etc.

- Remember what happens in a fork

  - PCB is copied on fork
  - Specifically for us, the local open file table gets inherited
  - Both PCBs point to the same GOF table entry

- Both processes point to the same GOF entry

- There are some gotchas for this sharing

  - Current position in the file is shared between both processes
  - Seek in one process leads to seek in all other processes using the same GOF entry
  - Opening the same file in both processes after forking creates multiple GOF entries

- How many LOF and GOF entries exist? What is the relationship?

  - ```c
    open("todo.txt", O_RDONLY);
    fork();
    open("b.txt", O_RDONLY);
    ```

    - Assume there are no previously opened files (not even the standard ones)

  - There are 2 LOF entries each, and 3 GOF entries

- How do we store files? Contiguous allocation?

- Contiguous allocation is fast, if there are no modifications

  - Space efficient: only start block and # of blocks need to be stored

  - Fast random access:

    - $$
      \text{Block}=\left\lfloor\frac{\text{Offset}}{\text{Block Size}}\right\rfloor
      $$

  - Files cannot grow easily

    - Internal fragmentation (may not fill a block)
    - External fragmentation when files are deleted or truncated

- What about storing like a free list of pages? Linked allocation

- Linked allocation has slow random access

  - Space efficient: only start block needs to be stored
    - Blocks need to store a pointer to the next block (block is slightly smaller)
  - Files can grow/shrink
    - No external fragmentation
    - Internal fragmentation
  - How can we increase random access speed? We need to walk each block
    - Each block may be located far away (it will never be cached)

- File allocation table moves the list to a separate table

- File Allocation Table (FAT) is similar to linked allocation

  - Files can grow/shrink
    - No external fragmentation
    - internal fragmentation
  - Fast random access: FAT can be held in memory/cache
    - FAT size is linear to disk size: can become very large
  - How can we further increase random access speed?

- Indexed allocation maps each block directly

- For indexed allocation, each file needs an index block

  - Files can still grow/shrink
    - No external fragmentation
    - Internal fragmentation
  - Fast random access
  - File size limited by the maximum size of the index block (fit in one block)

- Indexed allocation problem

  - Assume this scenario:
    - An index block stores pointers to data blocks only (no meta information)
    - A disk block is 8KB in size
    - A pointer to a block is 4B
  - What is the maximum size of a file managed by this index block?

- Indexed allocation solution

  - $$
    \text{# of pointers}=\left(\frac{8\text{KB}}{4\text{B}}\right)\left(\frac{2^{13}\text{B}}{2^2\text{B}}\right)=2^{11}
    $$

  - $$
    \text{# of addressable blocks}=\text{# of pointers}
    $$

  - $$
    \text{Total of bytes}=2^{11}\times 2^{13}=2^{24}=16\text{MB}
    $$

- An inode describes a file system object (files and directories)

- Linux inodes aim to be efficient for small files, and support large ones

  - UNIX inodes hold metadata and pointers to blocks
  - Smaller files only use direct pointers
  - Larger files have additional index nodes with pointers to additional blocks
  - Very small files can have its contents directly inside the inode

- inode problem

  - Assume this scenario:
    - An index block stores 12 direct pointers, one single, double, and triple indirect pointer each
    - A disk block is 8KB in size
    - A pointer to a block is 4B
    - Indirect blocks consist of direct pointers only
  - What is the maximum size of a file managed by this index block?

- inode solution

  - $$
    \text{# of pointers per indirect table}=\frac{2^{13}}{2^2}=2^{11}
    $$

  - $$
    \text{# addressable blocks}=12+2^{11}+(2^{11})^2+(2^{11})^3\approx (2^{11})^3=2^{33}
    $$

  - $$
    \text{Total of bytes}=2^{33}\times 2^{13}=2^{46}=64\text{TB}
    $$

- Hard links are pointers to inodes

  - A directory entry (aka filename) is called a hard link
  - A hard link points to one inode

- Multiple hard links can point to the same inode

  - Deleting a file only removes a hard link (the file can be hard linked somewhere else)
  - POSIX has the `unlink` call rather than a delete call

- Soft links are paths to another file

  - When resolving the file, the filesystem is redirected somewhere else, so:
    - Soft link targets do not need to exist
    - Soft link targets can be deleted without notice of the soft link
    - Unresolvable soft links lead to an exception

- Filesystem example problem

  - ```bash
    touch todo.txt
    ln todo.txt b.txt
    ln -s todo.txt c.txt
    mv todo.txt d.txt
    rm b.txt
    ```

- In UNIX, everything is file

  - Directories are files of type "directory"
  - Additional types are "regular file", "block device" (HDDs, SSDs), "pipe", "socket", etc.
  - Directory inodes do not store pointers to data blocks but rather filenames and pointers to inodes

- What data is stored in an inode

  - Filename => no, names are stored in directories
  - Containing directory name => no, file can be in multiple directories
  - File size => yes
  - File type => yes
  - \# of soft links to file => no, they are unknown
  - Location of soft links => no, they are unknown
  - \# of hard links to file => yes, to know when to erase the file, check `stat`
  - Location of hard links => no, they are unknown to the node
  - Access rights => yes
  - Timestamps => yes
  - File contents => sometimes
  - Ordered list of data blocks => yes, by definition

- Filesystem caches speed up writing to disks

  - Writing data to the disk is slow, we can use a cache to speed it up
  - File blocks are cached in main memory in the filesystem cache
    - Reference blocks are likely to be reference again (temporal locality)
    - Logically near blocks are likely to be referenced (spatial locality)
  - A kernel thread (or daemon) writes changes periodically to disk
  - `flush` and `sync` system calls trigger a permanent write

- Journaling filesystem

  - Deleting a file on a UNIX filesystem involves three steps:
    - Removing its directory entry
    - Releasing the inode to the pool of free inodes
    - Returning all disk blocks to the pool of free disk blocks
  - Crashes could occur between any steps, leading to a storage leak
  - The journal contains operations in progress, so if a crash occurs we can recover

- Filesystems enable persistence

  - They describe how files are stored on disks:
    - API-wise, you can open files and change the position to read/write at
    - Each process has a local open file and there's a global open file table
    - There's multiple allocation strategies: contiguous, linked, FAT, indexed
    - Linux uses a hybrid inode approach
    - Everything is file on UNIX, names in a directory can be hard or soft links



## Lecture 15: Sockets

- Sockets are another form of IPC

  - We've seen pipes, shared memory, and signals
  - These forms of IPC assume that the processes are on the same physical machine
  - Sockets enable IPC between physical machines, typically over the network

- Servers follow four steps to use sockets

  - These are all system calls, and have the usual C wrappers:
    - `socket` - create the socket
    - `bind` - attach the socket to some location (a file, IP:port, etc.)
    - `listen` - indicate you're accepting connections, and set the queue limit
    - `accept` - return the next incoming connection for you to handle

- Clients follow two steps to use sockets

  - Clients have a much easier time, they use one socket per connection
    - `socket` - create the socket
    - `connect` - connect to some location, the socket can now send/receive data

- The `socket` system call sets the protocol and type of socket

  - ```c
    int socket(int domain, int type, int protocol);
    ```

  - `domain` is the general protocol, further specified with `protocol` (mostly unused)

    - `AF_UNIX` is for local communication (on the same physical machine)
    - `AF_INET` is for IPv4 protocol using your network interface
    - `AF_INET6` is for IPv6 protocol using your network interface

  - `type` is (usually) one of two options: stream or datagram sockets

- Stream sockets use TCP

  - All data sent by a client appears in the same order on the server
  - Forms a persistent connection between client and server
  - Reliable, but may be slow

- Datagram sockets use UDP

  - Sends messages between the client and server
  - No persistent connection between client and server
  - Fast, but messages may be reordered or dropped

- The `bind` system call sets a socket to an address

  - ```c
    int bind(int socket, const struct sockaddr *address,
             socklen_t address_len);
    ```

  - `socket` is the file descriptor returned from the `socket` system call

  - There's different `sockaddr` structures for different protocols

    - `struct sockaddr_un` for local communication (just a path)
    - `struct sockadd_in` for IPv4, a IPv4 address (e.g. `8.8.8.8`)
    - `struct sockaddr_in6` for IPv6, a IPv6 address (e.g. `2001:4860:4860::8888`)

- The `listen` system call blocks until there's a connection

  - ```c
    int accept(int socket, struct sockaddr *restrict address,
               socklen_t *restrict address_len);
    ```

  - `socket` is still the file descriptor returned from the `socket` system call

  - `address` and `address_len` are locations to write the connecting address

    - Acts as an optional return value, set both to `NULL` to ignore

- The `connect` system call allows a client to connect to an address

  - ```c
    int connect(int sockfd, const struct sockaddr *addr,
                socklen_t addrlen);
    ```

  - `sockfd` is the file descriptor returned by the `socket` system call

    - The client would need to be using the same protocol and type as the server

  - `addr` and `addrlen` is the address to connect to, exactly like `bind`

  - If this call succeeds, then `sockfd` may be used as a normal file descriptor

- Our example server sends `"Hello there!"` to every client and disconnects

  - Please see `examples/lecture-20` in your `cs111` repository
    - Relevant source files: `client.c` and `server.c`
  - We use a local socket just for demonstration, but you could use IPv4 or IPv6
    - We use `example.sock` in the current directory as out socket address
  - Our server uses signals to clean up and terminate from our infinite `accept` loop

- Instead of `read`/`write`, there's also `send`/`recv` system calls

  - These system calls are basically the same thing, except they have `flag`s
  - Some examples are:
    - `MSG_OOB` - send/receive out-of-band data
    - `MSG_PEEK` - look at data without reading
    - `MSG_DONTROUTE` - send data without routing packets
  - Except for maybe `MSG_PEEK`, you don't need to know these
  - `sento`/`recvfrom` take an additional address
    - The kernel ignores the address for stream sockets (there's a connection)

- Sockets form a basis for distributed systems

  - You can use a remote procedure call (RPC) to run a function on another machine
    - Corresponds to sending a request, and receiving a reply
  - RPC can be done asynchronously, your process sends a request and doesn't block
    - You can continue working in other threads to keep the process running
  - You can also have distributed file systems, the data can reside on another server
    - NFS is a protocol designed to appear as a file system, but uses a network

- Sockets are IPC across physical machines

  - We can now create servers and clients, but there's much more to learn
    - There's networking and distributed systems courses
  - However, today we learned the basics:
    - Sockets require an address (e.g. local and IPv4/IPv6)
    - There are two types of sockets: stream and datagram
    - Servers need to bind to an address, listen, and accept connections
    - Clients need to connect to an address



## Lecture 16: Virtual Machines

- Virtual machines abstract an entire machine
  - Goal: run multiple OSes on a single machine
    - Each OS believes they're the only one running
  - We used it for our labs to make sure we all had the same environment
    - It was a full Linux install with all the software you needed
- The host has direct control over the hardware
  - The hypervisor or virtual machine manager (VMM) controls virtual machines
    - Creation, management, isolation (which hardware is it able to access)
  - There are two kinds of hypervisors: type 1 and type 2
    - Type 1: bare metal hypervisor, it runs directly on the host's hardware
      - Requires special hardware support
    - Type 2: hosted hypervisor, it simulates a hypervisor and runs as an application
      - Slower, but does not require any special hardware
  - A guest sees its own virtual copy of the host
- Virtual machines are not emulation
  - Emulation is typically used to translate one ISA to another
    - e.g. x86-64 to ARM/RISC-V
  - Our guest OS executes instructions directly using the same ISA
    - Otherwise, translating instructions is typically slow
  - It's ok for some uses, such as an NES emulator
  - A VM could use emulation to run a VM for a different ISA
    - Performance would suffer greatly
- VMs enable pause and play
  - Much like our kernel can pause a process, a hypervisor can pause an OS
  - The hypervisor needs to context switch between VMs
    - It'll save the current state and restore it later
  - We could also move it around, exactly like a process
- VMs provide protection through isolation
  - The guests are isolated from each other and the host
  - The hypervisor and set limits on: CPU time, memory, network bandwidth, etc.
    - A compromised guest only has access to its own virtualized hardware
  - You can easily roll back the infected VM, or remove it
- VMs also help consolidation
  - In data centers, there's many servers running, often not making use of all resources
    - Servers with different purposes could be sharing the same hardware
  - Instead of having lightly used physical systems, make them VMs
    - Run as many on a single machine as possible
- A Virtual CPU (VCPU) is the key abstraction
  - For processes, part of the process control block (PCB) acted as a virtual CPU
    - It doesn't virtualize all parts of the CPU, just enough for user-mode processes
  - The VCPU is a data structure that stores the state of the CPU
    - The hypervisor saves this when the guest isn't running
  - When the VM resumes, like the PCB, it loads the data and resumes
- The guest still uses user and kernel modes
  - There are no changes to the guest OSes
    - A Linux kernel still uses privileged instructions
  - Recall on x86-64, user mode is ring 3, kernel mode is ring 0
    - A hardware hypervisor (type 1) is ring -1, letting it control the guest
  - For type 2 hypervisors, the host has to create a virtual kernel and user mode
- One strategy is to trap-and-emulate
  - For type 2 hypervisors, the guest runs on the host in user mode
    - Any privileged instructions generate a trap (wrong mode)
  - The hypervisor should explicitly handle this error
    - Emulate (or simulate) the operation for the guest and resume it
  - This will slow down the otherwise native execution
- Trap-and-emulate doesn't always work
  - Some CPUs are not clear between privileged and non-privileged instructions
    - This includes x86-64, VMs didn't exist in the 1970s
  - One example is the `popf` instruction, it loads the flags register from the stack
    - It behaves differently for both kernel and user mode
  - It doesn't generate a trap, so you can't trap-and-emulate
    - These special instructions need another approach
- Special instructions need binary translation
  - If the guest VCPU is in user mode, we can run instructions natively
    - In kernel mode, the hypervisor inspects every instruction before execution
  - Special instructions need to be translated to instructions with the same effect
    - Regular instructions can run natively
  - The kernel uses a CPU instruction to switch from user to kernel mode
    - The hypervisor can handle that using normal trap-and-emulate
  - Overall performance for type 2 hypervisors suffer, but they're adequate

- One more hardware rescue
  - In 2005, Intel introduced virtualization as VT-x and in 2006, AMD did as AMD-V
    - Intel's codename Vanderpool, published as Virtual Machine Extensions (VMX)
    - AMD's codename Pacifica, published as Secure Virtual Machine (SVM)
  - This added the concept of ring -1, or hypervisor mode
  - The host kernel claims the hypervisor, and is the only one able to access it
    - It can set the isolation for the guests and what hardware to virtualize
- Virtualized scheduling
  - if there is only one CPU on the physical machine, the guest will not know
    - The host could still present multiple VCPUs to the guest
  - We now need to map the VCPUs to physical CPUs, or schedule them like processes
    - Like a normal kernel, there will also be hypervisor threads
- One approach is CPU assignment
  - If there are more physical cores on the host than all VCPUs, we can map 1:1
    - The host can continue using the spare physical cores
  - If we have to share, things get more complicated (called overcommitting)
    - At equal numbers, we can still map 1:1, the hypervisor threads don't run often
  - We have to use a scheduling algorithm, like we used for processes
- CPU overcommitment causes additional problems
  - The guest OS runs too unpredictably for soft real-time tasks
    - It may be context switched out when the user process says not to
  - For example, consider a real-time round robin time slice of 10ms
    - The guest will not have a consistent slice of 10ms, it may be much higher
  - This may make processes miss deadlines they wouldn't have running on the host
    - In this case, virtualization has different observable behavior
- Virtualized memory management gets a lot more complex
  - Recall: VM allows each process to think it has the entire address space
  - Now the guest kernel thinks it's managing the entire physical address space
    - We have to virtualize that too
  - The problem gets even worse if memory is overcommitted as well
- Nested page tables enable VM for guest kernels
  - The guest thinks it controls physical memory, and does page table management
  - The hypervisor maintains a nested page table that retranslates for the guest
    - It translates the guest's page table to the real physical page table
  - For overcommitted memory, the hypervisor can provide double-paging
    - The hypervisor does its own page replacement algorithm
      - However, the guest may know its memory access patterns better
- Guests could share pages if they're duplicates
  - Similar to copy-on-write pages, we can get memory saves by sharing pages
    - This time, instead of sharing between processes, share between guests
  - The hypervisor can do duplicate detection by hashing the contents of pages
    - If two hashes are the same, check they're the same byte-for-byte
  - If they're the same, we can share them until one of the guests try to write
    - Then we again do copy-on-write as before
- The hypervisor provides virtualized I/O devices
  - The hypervisor can multiplex one device to multiple VMs
    - The hypervisor could also emulate devices that don't physically exist
  - The hypervisor could also map one physical device to a virtual device on VM
    - The VM has exclusive access to the device, but hypervisor still translates
  - There is a hardware solution to remove the hypervisor during runtime - IOMMU
    - The hypervisor maps the devices VM exclusively to the guest
      - The VM now actually has exclusive control over the device
        - This allows complex GPUs to work at native speeds in VMs
- VMs boot from a virtualized disk
  - You create a disk image that has all the contents of a physical disk
    - It contains partitions and each partition has a filesystem
  - Usually, it's one big file (but some formats allow you to split it up)
    - The guest kernel sees it has a normal disk, that it has full control of
  - The disk image is all you need for the VM, makes it easy to move
    - The `ova` file you downloaded is basically a disk image and guest settings
- VMs enable live migration
  - You can migrate a VM from one physical machine to another
  - Users using the guest can't tell that the guest moved physical machines
    - Usually, it's a long process: you have to tell the users
  - This is how cloud providers try to balance the load
    - They move VMs off of overloaded machines
- Live migration in eight easy steps
  - The source hypervisor connects to the destination hypervisor
  - The destination creates a configuration for a new guest
  - The source sends all read-only memory pages to the destination
  - The source sends all read-write pages (marking them as clean)
  - Any pages that were modified during the previous step (if any) are sent and marked as clean
  - If there were few pages that were dirty in the previous two steps, the source freezes the guest, sends the final state and any final dirty pages
  - The destination acknowledges receipt and begins execution of the guest
  - The source terminates the guest
- VMs could be used to isolate an application
  - Assume your application uses a dynamic library (back to lecture 3)
    - An ABI change would cause your application to no longer work
      - Even more subtle, the library's behavior could change
  - You may want to freeze your dependencies to deploy it in production
    - Create a VM for it with all the libraries it needs
- Containers, like Docker, aim to be faster
  - The hypervisor sets limits on: CPU time, memory, network bandwidth, etc.
    - What if the kernel supported this directly, without virtualization?
  - Linux control groups (`cgroups`) support hypervisor-like limits for processes
    - Isolate a process to a namespace
  - You can set other resources a namespace can access (mount points, IPC, etc.)
  - Containers are lighter-weight than full VMs, they use a normal kernel
- VMs virtualize a physical machine
  - They allow multiple OSes to share the same hardware
    - VMs provide isolation, the hypervisor allocates resources
    - Type 2 hypervisors are slower due to trap-and-emulate and binary translation
    - Type 1 hypervisors are supported by hardware, IOMMU speeds up devices
    - Hypervisors may overcommit resources and need to physically move VM
    - Containers aim to have the benefits of VMs, without the overhead



## Lecture 17: Course Recap

- There are 4 major concepts in this course
  - You'll learn how the following applies to OSes
    - Virtualization
    - Concurrency
    - Persistence
    - Security (out of scope, somewhat touched on in VMs)
- Kernel interfaces operate between CPU mode boundaries
  - The lessons from the lecture:
    - Code running in kernel mode is part of your kernel
    - Different kernel architectures shift how much code runs in kernel mode
    - System calls are the interface between user and kernel mode
    - Everything involved to define a simple `"Hello world"` (in 178 bytes)
      - Difference between API and ABI
      - How to explore system calls
- Operating systems provide the foundation for libraries
  - We learned:
    - Dynamic libraries and a comparison to static libraries
      - How to manipulate a dynamic loader
    - Example of issues from ABI changes without API changes
    - Standard file descriptor conventions for UNIX
- The OS creates and runs processes
  - The OS has to:
    - Load a program and create a process with context
    - Maintain process control blocks, including state
    - Switch between running processes using a context switch
    - UNIX kernels start and `init` process
    - UNIX processes have to maintain a parent and child relationship
- We used system calls to create processes
  - You should be comfortable with:
    - `execve`
    - `fork`
    - `wait`
  - This includes understanding processes and their relationships
- We explored basic IPC in an OS
  - Some basic IPC includes:
    - `read` and `write` through file descriptors (could be a regular file)
    - Redirecting file descriptors for communication
    - Pipes (which you'll explore)
    - Signals
    - Shared Memory
- Scheduling involves some trade-offs
  - We looked at a few different algorithms
    - First Come First Served (FCFS) is the most basic scheduling algorithm
    - Shortest Job First (SJF) is a tweak that reduces waiting time
    - Shortest Remaining Time First (SRTF) uses SJF ideas with preemptions
    - SRTF optimizes lowest waiting time (or turnaround time)
    - Round-robin (RR) optimizes fairness and response time
- Scheduling gets even more complex
  - There are more solutions and more issues:
    - Introducing priority also introduces priority inversion
    - Some processes need good interactivity, others not so much
    - Multiprocessors may require per-CPU queues
    - Real-time requires predictability
    - Completely Fair Scheduler (CFS) tries to model the ideal fairness
- Page tables translate virtual to physical addresses
  - The MMU is the hardware that uses page tables, which may:
    - Be a single large table (wasteful, even for 32-bit machines)
    - Be a multi-level to save space for sparse allocations
    - Use the kernel to allocate pages from a free list
    - Use a TLB to speed up memory accesses
- Page replacement algorithms aim to reduce page faults
  - We saw the following:
    - Optimal (good for comparison, but not realistic)
    - Random (actually works surprisingly well, avoids the worst case)
    - FIFO (easy to implement, but Belady's anomaly)
    - LRU (gets close to optimal but expensive to implement)
    - Clock (a decent approximation of LRU)
- Both processes and (kernel) threads enable parallelization
  - We explored threads and related them to something we already know (processes)
    - Threads are lighter weight, and share memory by default
    - Each process can have multiple (kernel) threads
    - Most implementations use one-to-one user-to-kernel thread mapping
    - The OS has to manage what happens during a fork, or signals
    - We now have synchronization issues
- We want critical sections to protect against data races
  - We should know what data races are, and how to prevent them:
    - Mutex or spinlocks are the most straightforward locks
    - We need hardware support to implement locks
    - We need some kernel support for wake up notifications
    - If we know we have a lot of readers, we should use a read-write lock
- We explored more advanced locking
  - Before we did mutual exclusion, now we can ensure order
    - Semaphores are an atomic value that can be used for signaling
    - Condition variables are clearer for complex condition signaling
    - Locking granularity matters, you found out in Lab 3
    - You must prevent deadlocks
- The kernel has to implement it's own memory allocations
  - The concepts are the same for user space memory allocation (the kernel just gives them more contiguous virtual memory pages):
    - There's static and dynamic allocations
    - For dynamic allocations, fragmentation is a big concern
    - Dynamic allocation returns blocks of memory
      - Fragmentation between blocks is external
      - Fragmentation within a block is internal
    - There's three general allocation strategies for different sized allocations
      - Best fit
      - Worst fit
      - First fit
    - Buddy allocator is a real world restricted implementation
    - Slab allocator takes advantage of fixed size objects to reduce fragmentation
- Disks enable persistence
  - We explored two kinds of disks: SSDs and HDDs
    - Magnetic disks have poor random access (need to be scheduled)
    - Shortest Positioning Time First (SPTF) is the best scheduling for throughput
    - SSDs are more like RAM, except accessed in pages and blocks
    - SSDs also need to work with the OS for best performance (TRIM)
    - Use RAID to tolerate failures and improve performance using multiple disks
- Filesystem enable persistence
  - They describe how files are stored on disks
    - API-wise you can open files, and change the position to read/write at
    - Each process has a local open file and there's a global open file table
    - There's multiple allocation strategies: contiguous, linked, FAT, indexed
    - Linux uses a hybrid inode approach
    - Everything is file on UNIX, names in a directory can be hard or soft links
- Sockets are IPC across physical machines
  - We can now create servers and clients, but there's much more to learn
    - There's networking and distributed systems courses
  - However, we learned the basics:
    - Sockets require an address (e.g. local and IPv4/IPv6)
    - There are two types of sockets: stream and datagram
    - Servers need to bind to an address, listen, and accept connections
    - Clients need to connect to an address
- Virtual machines virtualize a physical machine
  - They allow multiple OSes to share the same hardware
    - Virtual machines provide isolation, the hypervisor allocates resources
    - Type 2 hypervisors are slower due to trap-and-emulate and binary translation
    - Type 1 hypervisors are supported by hardware, IOMMU speeds up devices
    - Hypervisors may overcommit resources and need to physically move VM
    - Containers aim to have the benefits of VM, without the overhead

