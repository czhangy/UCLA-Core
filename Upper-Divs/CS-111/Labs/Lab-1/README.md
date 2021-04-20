# Pipe Up

In this lab, we have used low-level C code to implement the pipe (`|`) command, ignoring additional command line arguments, like flags

## Building

Build the program in the root directory using the Makefile:

```
make
```

## Running

Run the program using `./pipe`, followed by 1-8 programs, which will be treated as arguments:

```
./pipe
```

For example, the program may be used as follows:

```
./pipe ls cat wc
```

This call pipes `ls` into `cat` into `wc`, which should have the same output as corresponding call using the built-in pipe operator:

```
ls | cat | wc
```

## Cleaning up

Binary files can be cleaned out of the filesystem using:

```
make clean
```
