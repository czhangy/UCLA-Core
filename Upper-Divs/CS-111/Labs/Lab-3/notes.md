# Hash Hash Hash



## Goal

**Write a C program that implements the hash table data structure, made safe to use concurrently using two separate locking strategies.**



## Requirements

- ```bash
  > ./hash-table-tester -t 8 -s 50000
  Generation: 130,340 usec
  Hash table base: 1,581,974 usec
  	- 0 missing
  Hash table v1: 359,149 usec
  	- 28 missing
  Hash table v2: 39
  ```

  - Add locking calls to `hash_table_v1_add_entry` and `hash_table_v2_add_entry`
  - Create a single mutex for `v1` and make the add entry function safe using the proper locking calls
  - Create as many mutexes as you like for `v2`, making it safe using the proper locking calls
  - You may add fields to any hash table struct: the hash table, `hash_table_entry`, or `list_entry`
    - Do not modify `contains` or `get_value`
  - Check for errors for any `pthread_mutex_*` functions you use
    - `exit` with the proper error code
    - Pass `valgrind` with no memory leaks

- Once complete, documentation should be written into `README.md`




## Deliverables

- Coding
  - [x] Implement `hash_table_v1_add_entry`
  - [x] Implement `hash_table_v2_add_entry`
  - [x] Perform error checking
  - [ ] Perform memory leak checking

- Documentation
  - [x] One sentence description of the program
  - [x] Explain how to build the program
  - [x] Show a test run of the program and the expected output
  - [x] Explain how to clean up all binary files generated
  - [x] Explain the `hash_table_v1_add_entry` implementation
  - [x] Explain the `hash_table_v2_add_entry` implementation

- Submission
  - [x] Use `git push` to push the final submission to the repository



## Relevant Links

- **[`slist` Man Pages](https://man7.org/linux/man-pages/man3/slist.3.html)**
- **[`pthread` Man Pages](https://man7.org/linux/man-pages/man7/pthreads.7.html)**