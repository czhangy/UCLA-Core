# Pipe Up



## Goal

**Use low-level C code to model the behavior performed by the pipe (`|`) operator in shells.**



## Requirements

- ```bash
  make
  ./pipe ls cat wc
  ls | cat | wc
  make clean
  ```

  - The bottom two commands should have the same output, Bash program arguments do not need to be accounted for
  - The program should be able to handle 1-8+ programs
  - Process:
    - Build your module with `make`
    - Call `./pipe`, passing in executable names as parameters
    - Sanity check using the same call with the default `|` operator
  - All errors need to be handled properly
    - The program should exit with the proper `errno` of the failing call
    - The program can exit as soon as the error is encountered, without attempting error recovery
    - The program should exit with the `errno = EINVAL` if passed zero arguments
  - No orphan processes are allowed, `wait()` must be called properly
  
- Once complete, documentation should be written into `README.md`




## Deliverables

- Coding
  - [x] Execute a single program from the command line using `./pipe`
  - [x] Execute multiple programs from the command line using `./pipe` independently
  - [x] Set up the pipe between two processes
  - [x] Set up the pipe between multiple processes

- Documentation
  - [x] One sentence description of the program
  - [x] Explain how to build the program
  - [x] Show a test run of the program with at least two additional arguments, and the expected output
  - [x] Explain how to clean up all binary files generated

- Submission
  - [ ] Use `git push` to push the final submission to the repository



## Relevant Links

- **[Symbol and Function Lookup](https://elixir.bootlin.com/linux/latest/source)**
