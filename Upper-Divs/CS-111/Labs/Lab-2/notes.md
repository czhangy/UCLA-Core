# You Spin Me Round Robin



## Goal

**Write a C program that implements round robin scheduling for a given workload and quantum length.**



## Requirements

- ```bash
  > ./rr processes.txt 3
  Average waiting time: 7.00
  Average response time: 2.75
  ```

  - The only code that should be added is to the fields in `struct process` and between the comments in `main`
  - Calculate the total response time in `total_response_time`
  - Calculate the total waiting time in `total_waiting_time`
  - Integer overflow may be ignored

- Once complete, documentation should be written into `README.md`




## Deliverables

- Coding
  - [x] Implement round robin scheduling
  - [x] Return the average waiting time
  - [x] Return the average response time

- Documentation
  - [x] One sentence description of the program
  - [x] Explain how to build the program
  - [x] Show a test run of the program with an arbitrary quantum length, and the expected output
  - [x] Explain how to clean up all binary files generated

- Submission
  - [x] Use `git push` to push the final submission to the repository



## Relevant Links

- **[`tailq` Man Pages](https://man7.org/linux/man-pages/man3/tailq.3.html)**