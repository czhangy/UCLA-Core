# A Kernel Seedling



## Goal

**Create a file `/proc/count` that shows the number of running processes by accessing the process table located in kernel mode.**



## Requirements

- ```bash
  make
  sudo insmod proc_count.ko
  cat /proc/count
  ```

  - The final command needs to output a single integer representing the number of running processes on the machine
  - Process:
    - Build your module with `make`
    - Insert your module into the kernel with `sudo insmod proc_count.ko`
    - Read any information messages printed in the kernel with `sudo dmesg -l info`
    - Remove your module from the kernel (so you can insert a new one) with `sudo rmmod proc_count`
    - Sanity check your module information with `modinfo proc_count.ko`
    - Clean your file system with `make clean`

- Once complete, documentation should be written into `README.md`

  - The `uname` command can be used to check for kernel version number



## Deliverables

- Coding
  - [x] Properly create and remove `/proc/count` when your module loads and unloads, respectively
  - [x] Make `/proc/count` return some string when you run `cat /proc/count`
  - [x] Make `/proc/count` return an integer with the number of running processes (or tasks) when you run `cat /proc/count`

- Documentation
  - [x] One sentence description of the module
  - [x] Explain how to build the module
  - [x] Explain how to run the module and what should be output
  - [x] Explain how to remove the module and clean up the code
  - [x] Report which kernel version the module was tested on

- Submission
  - [x] Use `git push` to push the final submission to the repository



## Relevant Links

- **[Symbol and Function Lookup](https://elixir.bootlin.com/linux/latest/source)**

