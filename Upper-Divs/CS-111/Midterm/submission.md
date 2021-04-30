# CS 111 Midterm



## Question 1

What is lower level than the operating system (or which does it abstract)?



------



### Answer

```
The hardware
```



## Question 2

What interface does a process use to interact with the kernel?



------



### Answer

```
System calls
```



## Question 3

What is something both monolithic kernels and microkernels need to do?



------



### Answer

```
Process scheduling
```



## Question 4

What is it called when the OS changes the current process to a new one?



------



### Answer

```
Context switching
```



## Question 5

Consider the following code snippet:



```c
int main() {
  while (true) {
    fork();
  }
}
```



Assume that execution begins at `main` and `fork` never fails. How many processes are there at the end of the third iteration of the loop?



------



### Answer

```
8
```



## Question 6

What system call creates a new process?

​	a. `wait`

​	b. `execve`

​	c. `open`

​	d. `fork`



------



### Answer

```
d. fork
```



## Question 7

What are signals NOT an example of?

​	a. virtualization

​	b. concurrency

​	c. interrupts

​	d. inter-process communication



------



### Answer

```
a. virtualization
```



## Question 8

Which is NOT a metric to evaluate scheduling algorithms?

​	a. throughput

​	b. frequency

​	c. fairness

​	d. waiting time



------



### Answer

```
b. frequency
```



## Question 9

What is the kind of scheduling called that has to be concerned with time constraints?



------



### Answer

```
Real-time scheduling
```



## Question 10

What do page tables map a virtual address to?



------



### Answer

```
A physical address
```



## Question 11

What hardware speeds up virtual address translation?



------



### Answer

```
The translation look-aside buffer (TLB)
```



## Question 12

What is NOT an example of a trap?

​	a. exception

​	b. interrupt

​	c. system call

​	d. blocking



------



### Answer

```
d. blocking
```



## Question 13

What is the optimal page replacement algorithm?

​	a. replace the page that won't be used the longest

​	b. replace a random page

​	c. replace the oldest page

​	d. replace the page least recently used



------



### Answer

```
a. replace the page that won't be used the longest
```



## Question 14

What CPU mode did your code execute in for Lab 0?



------



### Answer

```
Kernel mode
```



## Question 15

In Lab 0, what system call did you re-use to access internal kernel information?

​	a. `read`

​	b. `sbrk`

​	c. `wait`

​	d. `nice`



------



### Answer

```
a. read
```



## Question 16

What are the benefits and pitfalls of dynamic libraries compared to static libraries?



------



### Answer

```
Dynamic libraries allow the executable to reuse common libraries, allowing for the trimming of excess duplicate code.
They also don't require executables to be recompiled when libraries are updated, while static libraries do. The biggest
problem with dynamic libraries is that they reduce a program's reliability, as they're linked at runtime, and therefore
don't go through the process of static checking at compile-time. For instance, ABI changes have the potential to crash
executables if not carefully implemented.
```



## Question 17

Is a zombie orphan process possible? Explain.



------



### Answer

```
Zombie orphan processes are possible. Zombie processes are created when child processes finish execution before their
parent. Orphan processes are created when a parent exits without first addressing its children, resulting in the child
still running. In the case when a zombie process is waiting to be addressed by its parent, and the parent exits, that
zombie process is now a zombie orphan process, as it has finished executing, but it also hasn't been addressed by its
parent, which has now exited.
```



## Question 18

What is priority inversion with respect to scheduling, and how would you mitigate it?



------



### Answer

```
Priority inversion occurs when a process with a high priority has a dependence on a process with a low priority. Here,
the high priority process can't run, even when called upon, because the lower priority process has yet to be called on.
As a result, the higher priority process essentially has the same priority as the lower priority, since the lower
priority process needs to run for the higher priority process to run. This can be mitigated using priority inheritance,
which has priorities in a dependence chain inherit the highest priority in the chain. This can be chained across
multiple dependencies if necessary, and the processes reset to their original priorities when the dependencies have
been resolved.
```



## Question 19

A CPU supports 39 bit virtual addresses. It has a 1 KiB page size, and each PTE (page table entry) is 8 bytes. How many levels of page tables would you need if you used hierarchical page tables? Justify your answer.



------



### Answer

```
You would need 5 levels of page tables. The number of levels of page tables is determined by the ceiling of virtual
address bits minus offset bits, divided by index bits. Virtual address bits is given to us as 39 bits. Offset bits
can be found from taking the log of the page size, 1KiB. 1KiB translates to 1024 bytes, or 2^10 bytes, so there are 10
offset bits. Finally, the number of index bits can be found by dividing the page size (2^10) by the PTE size (8 = 2^3),
and then taking the log of that. This gives us 7 index bits. Taken together, we have the ceiling of (39 - 10) / 7, or
29 / 7, which is 5.
```



## Question 20

Describe how your solution in Lab 1 works when a user runs `./pipe ls wc`. Assume that the process id (pid) of the parent is `100`, and `fork` creates children with pid `101` and `102`. Also assume that the `pipe` system call returns file descriptor `3` in index `0` (the read end) and file descriptor `4` in index `1` (the write end). You can ignore errors.



------



### Answer

```
The idea behind my Lab 1 implementation is that we first store the file descriptors of read and write ends of all
necessary pipes, and then we fork enough times to address each of the process arguments. This allows all processes
to run concurrently, as they set up pipes/file descriptors before calling execlp to become their assigned process.

For the specific call given, we will first create a single array of length 2 (determined by the fact that we need 1)
pipe. This array will have pipe called on it, storing file descriptors 3 and 4. Then, we will have the parent process
fork 2 times to account for each of the processes in the arguments. While it forks, it stores the pids of 101 and 102
for later use, and also assigns each child process a number that represents which process it's responsible for.
Afterwards, the processes will begin to assign file descriptors. Since the first process (ls) needs to read from stdin
and write to the write end of the pipe (4), we leave file descriptor 0 untouched, but use dup2 to replace stdout with
the write end of the pipe. This allows file descriptor 1 to direct to the write end of the pipe instead of stdout.
Now, ls will run, reading from stdin, and writing to the write end of the pipe. The second process (wc) needs to read
from the read end of the pipe (3) and write to stdout, we leave file descriptor 1 untouched, but use dup2 to replace
stdin with the read end of the pipe. This allows file descriptor 0 to direct to the read end of the pipe instead of
stdin.

Now that all the pipes are redirected properly, both child processes can use execlp to become ls and wc, reading and
writing to the proper locations. Finally, the parent process uses the saved pids to wait for each of the children and
prevent them from becoming orphans.
```



## Question 21

For the following schedule questions use the following processes:

| Process | Arrival Time | Burst Time |
| :-----: | :----------: | :--------: |
|    1    |      0       |     4      |
|    2    |      5       |     3      |
|    3    |      7       |     2      |
|    4    |      1       |     3      |
|    5    |      3       |     1      |

You'll be using these processes to create a schedule using round robin (with a quantum length of 2) and shortest remaining time first. Both algorithms use preemption. You'll need to create a schedule, then calculate the average waiting time and average response time for both algorithms.

For round robin (RR) scheduling with a quantum length of 2 time units please select which process is running during the specified time. If there are ties (e.g. one process is being re-queued while another one arrives) favor the arriving process.

​	a) What process is scheduled for round robin between time 0-1?

​	b) What process is scheduled for round robin between time 1-2?

​	c) What process is scheduled for round robin between time 2-3?

​	d) What process is scheduled for round robin between time 3-4?

​	e) What process is scheduled for round robin between time 4-5?

​	f) What process is scheduled for round robin between time 5-6?

​	g) What process is scheduled for round robin between time 6-7?

​	h) What process is scheduled for round robin between time 7-8?

​	i) What process is scheduled for round robin between time 8-9?

​	j) What process is scheduled for round robin between time 9-10?

​	k) What process is scheduled for round robin between time 10-11?

​	l) What process is scheduled for round robin between time 11-12?

​	m) What process is scheduled for round robin between time 12-13?



------



### Answer

```
a) 1
b) 1
c) 4
d) 4
e) 1
f) 1
g) 5
h) 4
i) 2
j) 2
k) 3
l) 3
m) 2
```



## Question 22

What is the average waiting time for the RR schedule you previously made? (Use one decimal place)



------



### Answer

```
3.2
```



## Question 23

What is the average response time for the RR schedule you previously made? (Use one decimal place)



------



### Answer

```
2.0
```



## Question 24

For shortest remaining time first (SRTF) scheduling please select which process is running during the specified time. For ties (e.g. two processes have the same remaining time) favor the process that newly arrives. This will ensure your minimize average response time while not changing average waiting time.

​	a) What process is scheduled for SRTF between time 0-1?

​	b) What process is scheduled for SRTF between time 1-2?

​	c) What process is scheduled for SRTF between time 2-3?

​	d) What process is scheduled for SRTF between time 3-4?

​	e) What process is scheduled for SRTF between time 4-5?

​	f) What process is scheduled for SRTF between time 5-6?

​	g) What process is scheduled for SRTF between time 6-7?

​	h) What process is scheduled for SRTF between time 7-8?

​	i) What process is scheduled for SRTF between time 8-9?

​	j) What process is scheduled for SRTF between time 9-10?

​	k) What process is scheduled for SRTF between time 10-11?

​	l) What process is scheduled for SRTF between time 11-12?

​	m) What process is scheduled for SRTF between time 12-13?



------



### Answer

```
a) 1
b) 4
c) 4
d) 5
e) 4
f) 2
g) 2
h) 2
i) 3
j) 3
k) 1
l) 1
m) 1
```



## Question 25

What is the average waiting time for the SRTF schedule you previously made? (Use one decimal place)


------



### Answer

```
2.2
```



## Question 26

What is the average response time for the SRTF schedule you previously made? (Use one decimal place)



------



### Answer

```
0.2
```



## Question 27

Assume the following accesses to physical page numbers:
$$
1, 2, 3, 4, 5, 2, 3, 1, 4, 2
$$
or in table format:

| Access | Physical Page |
| :----: | :-----------: |
|   1    |       1       |
|   2    |       2       |
|   3    |       3       |
|   4    |       4       |
|   5    |       5       |
|   6    |       2       |
|   7    |       3       |
|   8    |       1       |
|   9    |       4       |
|   10   |       2       |

Assume that all pages are initially on disk. For each access you'll have to answer which page gets evicted, and which page gets brought in. You have 4 physical pages in memory.

Unless otherwise stated, you'll be using the clock algorithm to replace pages. However, instead of doing nothing with the reference bit on a page hit, you'll set the reference bit to 1. This will allow the clock algorithm to approximate LRU.

For the modified clock algorithm, for each access, please state which page gets evicted (removed from physical memory) as part of the access.

​	a) For the modified clock algorithm on access 1, which page gets evicted?

​	b) For the modified clock algorithm on access 2, which page gets evicted?

​	c) For the modified clock algorithm on access 3, which page gets evicted?

​	d) For the modified clock algorithm on access 4, which page gets evicted?

​	e) For the modified clock algorithm on access 5, which page gets evicted?

​	f) For the modified clock algorithm on access 6, which page gets evicted?

​	g) For the modified clock algorithm on access 7, which page gets evicted?

​	h) For the modified clock algorithm on access 8, which page gets evicted?

​	i) For the modified clock algorithm on access 9, which page gets evicted?

​	j) For the modified clock algorithm on access 10, which page gets evicted?



------



### Answer

```
a) None
b) None
c) None
d) None
e) 1
f) None
g) None
h) 4
i) 5
j) None
```



## Question 28

For the modified clock algorithm, for each access, please state which page gets swapped in (adds the page to physical memory) as part of the access.

​	a) For the modified clock algorithm on access 1, which page gets swapped in?

​	b) For the modified clock algorithm on access 2, which page gets swapped in?

​	c) For the modified clock algorithm on access 3, which page gets swapped in?

​	d) For the modified clock algorithm on access 4, which page gets swapped in?

​	e) For the modified clock algorithm on access 5, which page gets swapped in?

​	f) For the modified clock algorithm on access 6, which page gets swapped in?

​	g) For the modified clock algorithm on access 7, which page gets swapped in?

​	h) For the modified clock algorithm on access 8, which page gets swapped in?

​	i) For the modified clock algorithm on access 9, which page gets swapped in?

​	j) For the modified clock algorithm on access 10, which page gets swapped in?



------



### Answer

```
a) 1
b) 2
c) 3
d) 4
e) 5
f) None
g) None
h) 1
i) 4
j) None
```



## Question 29

Instead of using the modified clock algorithm, use the optimal algorithm for the same page accesses. How many page faults are there for the optimal algorithm?



------



### Answer

```
6
```

