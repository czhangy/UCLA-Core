# Hey! I'm Filing Here



## Goal

**Implement a valid 1MB `ext2` filesystem with 2 directories, 1 regular file, and 1 symbolic link.**



## Requirements

- ```bash
  > make
  > ./ext2-create
  > fsck.ext2 cs111-base.img
  > dumpe2fs cs111-base.img
  > mkdir mnt
  > sudo mount -o loop cs111-base.img mnt
  > ls -ain mnt/
  total 7
  	 2 drwxr-xr-x 3    0    0 1024 .
  	   drwxr-xr-x 3                ..
  	13 lrw-r--r-- 1 1000 1000   11 hello -> hello-world
  	12 -rw-r--r-- 1 1000 1000   12 hello-world
  	11 drwxr-xr-x 2    0    0 1024 lost+found
  > sudo umount mnt
  > rmdir mnt
  > make clean
  ```
  
  - All header files that are needed are already included in the skeleton code
  - Write the following functions in `lab-04/ext2-create.c`:
    - `write_superblock`
    - `write_block_group_descriptor_table`
    - `write_block_bitmap`
    - `write_inode_bitmap`
    - `write_inode_table`
    - `write_root_dir_block`
    - `write_hello_world_file_block`
  - Try not to hard-code as much as possible
  - We're creating a 1MB `ext2` filesystem with 1KB-sized blocks, and enough space for 128 inodes
    - We'll be creating 4 inodes: the root directory, the `lost+found` directory, a regular file called `hello-world` , and a symbolic link named `hello`, which points to `hello-world`
      - The inode for `lost+found` is provided, along with its directory block
      - The root directory and `lost+found` should be owned by UID `0` and GUI `0` (root)
        - The owner should have read, write, and execute permissions
        - The group and other should have read and execute permissions
      - The `hello-world` file and `hello` symlink should be owned by UID `1000` and GID `1000`
        - The owner should have read and write permissions
        - The group and other should have read permissions
        - `hello-world` should be 12B, containing `"Hello world"` followed by a newline
  - Check all wrapped system calls for errors, exiting with `errno`
    - Use the `errno_exit` macro
  - Zero initialize everything
    - This means assigning `{0}` to a `struct` in C
    - Remember that all blocks start from `0` and all inodes start from `1`
  
- Once complete, documentation should be written into `README.md`




## Deliverables

- Coding
  - [x] Fill in the fields in `write_superblock`
  - [x] Fill in the fields in `write_block_group_descriptor_table`
  - [x] Write `write_block_bitmap`
  - [x] Write `write_inode_bitmap`
  - [x] Fill in the fields in `write_inode_table`
  - [x] Write `write_root_dir_block`
  - [x] Write `write_hello_world_file_block`
  - [x] Perform error checking using `dumpe2fs cs111-base.img` and `fsck.ext2 cs111-base.img`
  
- Documentation
  - [x] One sentence description of the program
  - [x] Explain how to build the program
  - [x] Show how to compile and mount your filesystem, with an example output generated by `ls -ain`
  - [x] Explain how to unmount the filesystem and clean up the filesystem

- Submission
  - [ ] Use `git push` to push the final submission to the repository



## Relevant Links

- **[The Ext2 Filesystem](http://www.science.smith.edu/~nhowe/262/oldlabs/ext2.html)**
- **[The Second Extended Filesystem](http://www.nongnu.org/ext2-doc/ext2.html)**
