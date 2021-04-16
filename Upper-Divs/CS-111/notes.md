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
      - Chain together multiple inheritences if needed
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

