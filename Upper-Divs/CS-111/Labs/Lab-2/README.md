# You Spin Me Round Robin

In this lab, we have used low-level C code and `TAILQ` from `sys/queue.h` to implement round robin scheduling for given workloads and quantum lengths, and then used that implementation to examine average waiting and response times.

## Building

Build the program in the root directory using the Makefile:

```
make
```

## Running

Run the program using `./rr`, followed by `processes.txt`, which contains the process IDs, arrival times, and burst times for a predefined number of processes, followed by the desired quantum length `n`:

```
./rr processes.txt n
```

For example, this program may be used as follows:

```
./rr processes.txt 10
```

With `processes.txt` containing:

```
4
1, 0, 7
2, 2, 4
3, 4, 1
4, 5, 4
```

This would be expected to output:

```
Average waiting time: 4.75
Average response time: 4.75
```

## Cleaning up

Binary files can be cleaned out of the root directory using:

```
make clean
```
