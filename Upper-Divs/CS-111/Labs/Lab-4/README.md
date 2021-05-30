# Hey! I'm Filing Here

This is a C program that implements a valid ext2 filesystem containing 2
directories, a regular file, and a symbolic link.

## Building

This program can be built using the Makefile in the root directory:

```
make
```

## Running

Show how to compile, mount, and example output of `ls -ain` your mounted
filesystem.

This code can be compiled using the ext2-create executable:

```
./ext2-create
```

Once ran, a file named `cs111-base.img` will be generated. We can then create
a directory to mount this file using:

```
mkdir mnt
```

With the directory created, we can now mount our filesystem using:

```
sudo mount -o loop cs111-base.img mnt
```

Once mounted, we can view the contents of our filesystem using:

```
ls -ain mnt/
```

If done correctly, the following should be output (with the fields of the `..`
directory entry and timestamps dependent on your machine):

```bash
total 7
     2 drwxr-xr-x 3    0    0 1024 May 30 13:39 .
146843 drwxr-xr-x 3 1000 1000 4096 May 30 13:41 ..
    13 lrw-r--r-- 1 1000 1000   11 May 30 13:39 hello -> hello-world
    12 -rw-r--r-- 1 1000 1000   12 May 30 13:39 hello-world
    11 drwxr-xr-x 2    0    0 1024 May 30 13:39 lost+found
```

## Cleaning up

The filesystem can be unmounted using:

```
sudo umount mnt
```

Afterwards, the directory can be safely removed using:

```
rmdir mnt
```

Finally, binary files can be cleaned out of the filesystem using:

```
make clean
```
