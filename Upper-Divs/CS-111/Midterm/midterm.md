# CS 111 Midterm



## Question 1

What is lower level than the operating system (or which does it abstract)?



## Question 2

What interface does a process use to interact with the kernel?



## Question 3

What is something both monolithic kernels and microkernels need to do?



## Question 4

What is it called when the OS changes the current process to a new one?



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



## Question 6

What system call creates a new process?

​	a. `wait`

​	b. `execve`

​	c. `open`

​	d. `fork`



## Question 7

What are signals NOT an example of?

​	a. virtualization

​	b. concurrency

​	c. interrupts

​	d. inter-process communication



## Question 8

Which is NOT a metric to evaluate scheduling algorithms?

​	a. throughput

​	b. frequency

​	c. fairness

​	d. waiting time



## Question 9

What is the kind of scheduling called that has to be concerned with time constraints?



## Question 10

What do page tables map a virtual address to?



## Question 11

What hardware speeds up virtual address translation?



## Question 12

What is NOT an example of a trap?

​	a. exception

​	b. interrupt

​	c. system call

​	d. blocking



## Question 13

What is the optimal page replacement algorithm?

​	a. replace the page that won't be used the longest

​	b. replace a random page

​	c. replace the oldest page

​	d. replace the page least recently used



## Question 14

What CPU mode did your code execute in for Lab 0?



## Question 15

In Lab 0, what system call did you re-use to access internal kernel information?

​	a. `read`

​	b. `sbrk`

​	c. `wait`

​	d. `nice`



## Question 16

What are the benefits and pitfalls of dynamic libraries compared to static libraries?



## Question 17

Is a zombie orphan process possible? Explain.



## Question 18

What is priority inversion with respect to scheduling, and how would you mitigate it?



## Question 19

A CPU supports 39 bit virtual addresses. It has a 1 KiB page size, and each PTE (page table entry) is 8 bytes. How many levels of page tables would you need if you used hierarchical page tables? Justify your answer.



## Question 20

Describe how your solution in Lab 1 works when a user runs `./pipe ls wc`. Assume that the process id (pid) of the parent is `100`, and `fork` creates children with pid `101` and `102`. Also assume that the `pipe` system call returns file descriptor `3` in index `0` (the read end) and file descriptor `4` in index `1` (the write end). You can ignore errors.



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



## Question 22

What is the average waiting time for the RR schedule you previously made? (Use one decimal place)



## Question 23

What is the average response time for the RR schedule you previously made? (Use one decimal place)



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



## Question 25

What is the average waiting time for the SRTF schedule you previously made? (Use one decimal place)



## Question 26

What is the average response time for the SRTF schedule you previously made? (Use one decimal place)



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



## Question 29

Instead of using the modified clock algorithm, use the optimal algorithm for the same page accesses. How many page faults are there for the optimal algorithm?

