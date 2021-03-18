## CS 97 Final



## Question 1

The Liddil test is meant to check if there is a hard or symbolic link between two existing files in the current directory. We can verify this by comparing the two hashed of the two lines of output. It exits with `0` to confirm that they are linked or are the same file. It exits with `1` to confirm they aren't linked or aren't the same file.



------



### Answer

```
A plausible simplification that wouldn’t work is checking if one file is the
backup of another by comparing the strings passed in, as these inherently become
two different separate files as shown by their distinct hashes. (Ex: notes.txt
and notes.txt~).

Another plausible simplification which wouldn’t work is that the Liddil test is
comparing the contents of the two files, since they can have the same content,
but not be naming the same file. This also applies for checking if files have
been modified at the same time, as two files can be modified at the same time
but be different regardless.
```



## Question 2

Write a shell command name `Liddil-test` that quietly succeeds if given two operands for which the Liddil test succeeds, quietly fails if given two operands for which the Liddil test succeeds, quietly fails if given two operands for which the Liddil test fails, and fails with a diagnostic otherwise. For example, on SEASnet, `Liddil-test/bin/sh/usr/bin/bash` should succeed, whereas `Liddil-test''/` should quietly fail because the empty string does not name a fail. When given two operands your command should not generate any output: it should merely succeed or fail, so that the user can write a shell command like:



```bash
if Liddil-test /bin/sh/usr/bin/bash
then echo ‘same file’
else echo ‘differing files’
fi
```



Without getting any stray messages. Your command should not take any options, and should treat all operands as file names even if they begin with `-`; for example, `Liddil-test -E.` should quietly fail unless you happen to have a symbolic link like `-E ->.`.



------



### Answer

```bash
#!/usr/bin/bash

a=$1 # Reading in first argument
b=$2 # Reading in second argument
ls -Liddil $a $b > tmp.txt 2>/dev/null # No output regardless of failed command
c=$(sed -n '1p' tmp.txt | cut -c 1-8) # First line of output
d=$(sed -n '2p' tmp.txt | cut -c 1-8) # Second line of output
rm tmp.txt # Removing created file
if [ $c -ne $d ] # Comparing hash values
then
	exit 1 fi
exit 0
```



## Question 3

Suppose some other program is modifying the file system at the same time that your `Liddil-test` program runs. How would this affect the validity of your program’s results? Briefly explain.



------



### Answer

```
If one is editing file A via a text editor like Emacs, the hard link between the
files can be lost, as a backup version A~ is created that B is now linked to
instead. This causes the test program to fail. However, this is fine if the two
files are symbolic linked, this would not affect the validity of the programs
results, as any modifications would occur for both operands A and B.
Furthermore, if file A is linked to file B (or vice versa), but file B is moved
outside of the current directory that the Liddil test is running in, the program
will not be able to find this file B and the test will fail.
```



## Question 4

In `.git/objects` Git splits the 40-character SHA-1 text checksum into two parts, of length 2 and 38 characters respectively. Why doesn’t Git instead split them into equal parts of 20 characters each? Wouldn’t that be fairer or more efficient in some way? Or, if 2 vs 38 is good, why wouldn’t 1 vs 39 (or 3 vs 37, etc.) be better? Briefly explain.



------



### Answer

```prolog
Git needs this split of checksums in the first place to prevent a single
directory from growing too large. Therefore, Git uses the first 2 characters to
index into a subdirectory. Git doesn’t split them into equal parts of 20
characters because that would result in an unreasonably large number of
subdirectories. Since Git must search through these subdirectories to locate
data, if there are too many subdirectories, the objects system essentially loses
its hash table qualities and finding data becomes a linear search.

We only use 2 characters as the index because the number of subdirectories
created by 1 character would likely be insufficient and certain filesystems
would have their file limit exceeded, as the subdirectories contents would be
flooded. We don’t need any more characters because this would flood the base
objects directory with too many subdirectories. This is unnecessary, as the
efficiency of using 2 characters is plenty efficient for the vast majority of
repositories. This could likely have been resolved through testing as Git was
designed.
```



## Question 5

Data backup systems use deduplication, compression, and encryption heavily. Compare and contrast their use of these three technologies to how Git uses them. Assume Git plumbing only; do not worry about porcelain or add-ons.



------



### Answer

```
Git uses deduplication to prevent unnecessary overhead from copying large files.
It does this by redirecting a pointer to a block in memory if it is requested
and it is already in memory. This results in a danger of corrupting larger
amounts of memory, as if the original block is corrupted, all the files that
rely on it may be corrupted as well. Overall deduplication can speed up the
copying process because it theoretically cuts down on the amount of information
that needs to be copied, but it can be quite dangerous if data gets corrupted.

Git uses compression in the form of gzip to compress its object files. Like
deduplication, compression helps reduce the size of the total filesystem,
however, it doesn’t run the same risk of corruption that deduplication does.
Gzip combines various compression techniques such as Huffman coding and the
dictionary coder. The combination of these two techniques help the compression
be as small as possible while still not being too expensive.

Unlike deduplication and compression, encryption is not used to save space in
the overall repository. Encryption is used to prevent attackers from gaining
undue control of the backups. This is especially useful in case the repository
contains private information. Encrypting backups is extremely important.
Especially when a repository is meant to be kept private and away from
attackers. Encrypting backups helps data stay more secure and helps keep
developers at ease knowing their work is unlikely to be corrupted or stolen.
```



## Question 6

Suppose you wanted to add checkpoint/restart capability to a working `randall` program running on SEASnet. The idea is that you run the program like this:

`randall 100000000000 > output`

and that if the system crashes while in the middle of a run, after it reboots you can continue where you left off by doing this:

`randall 100000000000 >> output`

Explain how to modify your `randall` implementation to support checkpoint/restart in this way by using functions like `fseek`, `ftell`, or `lseek`. Use explicit code snippets in your explanation where appropriate. Explain what trouble your modifications would have when doing checkpoint/restart if the modified `randall` outputs to a pipe to some other program, instead of outputting to regular file.



------



### Answer

```
The fseek function can be used to move the position indicator associated with
the stream (of file data in bytes) to the appropriate position. fseek takes in 3
arguments, the first being a pointer to the file being read, the second being
the “offset,” or the new position to which the stream has been read, and the
last being the origin of the stream (output file).
	- For the first parameter, we must pass in a pointer to the file that is being
	  written to, which would be the “output” file in this case.
	- Using the function, ftell, allows us to set the offset argument which is the
	  location of the new position indicator.
	- The constant SEEK_SET should be passed in as the third argument, for it
	  contains the file pointer to the beginning of the file.
There should be another function that returns the position where writing to the
output file starts.
```

```c
int startPosition(int numBytes) {
  char *pos;
	File *outputFile = fopen("output", "rb");
	fseek(outputFile, SEEK_END, SEEK_SET); // Moves the position indicator to the
  																			 // end of the output file
	long int position = ftell(outputFile); // Returns the byte position of where
  																			 // the position indicator is pointing
	if(outputFile == NULL) { // If no output file already exists, that means the
      										 // inputted number of bytes should be generated
		return numBytes;
	} else if(position != 0) { // If the current position of the position
    												 // indicator is not at the beginning, a fewer
    												 // number of bytes should be generated than
    												 // requested
			return (numBytes - position);
  }
}
```

```
No file would exist if we piped into another program, which means we wouldn’t be
able to read the number of bytes that have been streamed. Determining the
appropriate location for the position indicator can be difficult or impossible.
```



## Question 7

Compare and contrast the following approaches to detecting and/or preventing integer overflow errors in your C or C++ programs.



------



### Answer

```
When running a program with these three methods (under GDB, with -Wall -Wextra,
and with -fsanitize=undefined) the programmer is attempting to detect integer
overflow errors at and after compilation. These three methods are used to detect
this type of error with varying levels of scrutiny, where GDB is the most
general-purpose and -fsanitize is the most tailored to detecting undefined
behaviour such as integer overflow. Using GDB to debug a program enables the
programmer to find the values of program variables at specific points during
execution of the program, meaning it can be used to find if and where integer
overflow occurs. However, this requires manually searching. With gcc, the -Wall
and -Wextra flags can be used to enable all and extra compiler warning messages.
The -Wall flag turns on several warning flags, one of which is the -Wstrict-
overflow=n flag, which warns about potential simplifications to reduce the
chance or eliminate the chance of overflow in arithmetic operations. However,
this check is not very thorough as it will not warn about all cases where the
code might overflow, only where the compiler implements some optimization and
the warning can give false positives if overflow never happens. -Wextra also
turns on the -Wtype-limits flag which warns if a comparison is always true or
false due to the limited range of the data type. gcc -fsanitize=undefined is
used to detect undefined behaviour at runtime. Furthermore, there is an even
more specific sub option -fsanitize=signed-integer-overflow, which specifically
searches for signed-integer-overflow. A programmer would have to choose the most
suitable of these three methods depending on the circumstances of their problem.

Lisp uses machine word integers by default and switches to bignums if an
operation would result in integer overflow. Switching to the bignums package
expands the size of the integer to be as large as the system’s memory, which
prevents overflow from happening if the program was in C/C++. Compared to C/C++,
there is decreased performance for arithmetic operations and unpredictable
memory use. Similarly, Python automatically casts integers to the longinteger
data type to prevent integer overflow. This is similar to Lisp because the size
of the integer becomes constrained to the size of the system’s memory and the
issues with performance and unpredictability arise too. Javascript handles
integer overflow differently from Lisp and Python in that Javascript will return
“infinity” or “-infinity” if the arithmetic or number overflows. This, however,
will not terminate the behavior like in C/C++ and the user will know if an
overflow has occurred if “infinity” was returned.
```



## Question 8

Consider the following potential criticisms of Node.js:

1. It doesn’t support multithreaded applications, which makes many apps hard to scale.

2. It’s tied closely to Google’s V8 JavaScript engine, and so is not portable to other platforms.

3. It’s too low level; if you want to build a real app you must write everything nearly from scratch, or pull in other peoples’ code like crazy.

4. JSX is too complicated and its learning curve is too steep, compared to other approaches.

Add one other reasonable criticism to this list.

For each of the five criticisms (the above four, plus your fifth):

- Argue that the criticism is a reasonable one, as best you can.
- Give a defense of Node.js against the criticism, as best you can.
- Explain how well the criticism applies to the project that you worked on for this course.



------



### Answer

```
1. This is a reasonable criticism because multithreading is seen in the vast
majority of development software and frameworks in modern times. Multithreading
greatly improves performance of code and makes sure that a machine is making the
most of its hardware. The fact that Node.js does not have multithreading means
that instead more hardware (essentially more machines) are needed to scale apps
properly, which can be quite costly for developers. However, the fact that
Node.js is single-threaded is not entirely bad. It means that there is no
possibility for race conditions, which are notoriously difficult to debug. It
also means that developers do not need to worry about learning and using locks,
priority inversions, and all the other tools that come with multithreading. In
regards to our project, since our server is single threaded, it must handle each
incoming request for classes one at a time. This can bog down the server if many
users are making requests at the same time but since our server operations
mainly require constant time lookups in our JSON file of classes, this is less
of an issue especially on a small application such as ours.

2. This is a reasonable criticism because not everyone likes to use Google on
their computers. By tying Node.js so closely to Google, it can force developers
who dislike Google to have to use a browser they dislike simply because they
have to use Node.js for a project. This is a bit unfair because hundreds of
thousands of people around the world may prefer to use other search engines and
will have to be forced to conform to using Google because the developers of
Node.js did not keep them in mind. For instance, in China, Google is blocked
unless using a VPN to pretend like you are in a different country. It is a bit
unfair to exclude so many people from the developer community. However, this is
not entirely a bad thing. While it is true that many people dislike Google, the
overwhelming majority of people around the world do use Google. So the fact that
Node.js is tied to one of the most widely used applications in the world really
makes it accessible to a lot of people. This criticism was not really a problem
for my group’s project because we all use Google and have been using it our
entire lives. We didn’t run into any issues where group members were unfamiliar
with Google or did not want to use it.

3. This is a reasonable criticism because it really is a pain to work with low-
level programming languages and frameworks. Because Node.js is a low-level
framework, it is very difficult for many developers to get used to — it requires
a lot of time to learn the intricacies of using it because it isn’t very similar
to many other frameworks or languages that many developers would commonly use.
The fact that Node.js is low-level means that developers can not rely on slow,
high-level abstractions to perform the work for them. Developers must
painstakingly handle everything at the low-level themselves, which can be
frustrating and tedious. However, Node.js being low-level is not an entirely bad
thing. Node.js is perfect for performing evented asynchronous non-blocking I/O
because of its low-level nature. This is because it can effectively handle a
large amount of simultaneous connections with high throughput. This is good when
a developer wants to create an application that needs a lot of connections with
many clients. For our project, this criticism does apply to some extent since
our backend code needed packages for sending requests to the server (Axios) and
reading a file (Async-file). Building these packages’ functionalities would be time-consuming to implement ourselves, importing other people’s packages helped
to speed up development time. However, importing packages rely that the person
who created them ensures the package is stable and robust. It is placing a lot
of trust into the developer of the package, which many people may hesitate to
do.

4. This is a reasonable criticism because JSX is a bit awkward to use,
especially if someone doesn’t have extensive experience with HTML and JavaScript
beforehand. The fact that JSX is so heavily reliant on these two other languages
makes it a lot more difficult to learn as it requires a lot of prior knowledge
before even being able to scratch the surface of what JSX can be used for. There
are other technologies such as t7 that can accomplish similar functions as JSX
but are much easier to learn. JSX is not very intuitive, which makes it one of
the most daunting obstacles that impede new web developers. However, for someone
who has prior knowledge of JavaScript and HTML, JSX is amazing. There isn’t very
much that has to be learned in this case as JSX just piggybacks off of these two
languages. This makes JSX extremely easy to pick up, so seasoned developers can
get into frontend development very quickly and easily. I think this criticism
definitely did apply to my group's project. I was one of the frontend developers
for our group, and I was definitely very confused by JSX for the first two
weeks. It took a lot of tutorials and YouTube demonstrations for me to even get
an idea of what was going on with JSX because I had very little experience with
JavaScript. I agree that the learning curve for JSX is indeed really steep
compared to a lot of other approaches out there.

5. This is a reasonable criticism because having a framework that relies heavily
on callbacks can lead to what is known as “callback hell”. A callback is a
function that runs after each task in the queue is finished. When a program
requires a lot of callbacks, it can have multiple problems. It leads to ugly,
almost unreadable code that is impossible to interpret. This can make debugging
extremely difficult and frustrating as the code is difficult to trace.
Accidentally creating a callback hell within a program is a huge problem as it
leads to unclear code. However, having Node.js be reliant on callbacks is not
entirely terrible. Callbacks are excellent when it comes to handle asynchronous
behavior, which is one of the main things that Node.js excels at doing.
Callbacks are really great because Node.js is single-threaded, so the callbacks
help the tasks get finished as efficiently as possible with a single-threaded
environment. In our group’s project, we didn’t really run into callback hell but
we very well could have if we were not careful. We took many steps to make sure
that we avoided confusing callbacks in our project by giving functions
meaningful names and not nesting to many callbacks inside of each other. This
made the callbacks a lot easier to trace and debug when needed. Callback hell is
a problem that can be avoided with careful programming that aims to keep the
program simple and readable.
```



## Question 9

The `man` page for `git merge` has the following words of wisdom:

> Running git merge with non-trivial uncommitted changes is discouraged: while possible, it may leave you in a state that is hard to back out of in the case of a conflict.

Write a shell script that illustrates this advice. Your shell script should set up a Git repository and working files from scratch (no fair cloning from any other source), and run `git merge` with nontrivial uncommitted changes. Explain the resulting state, and why this sort of state is hard to back out of in the more-typical case where you don’t have a complete shell script that you can replay.



------



### Answer

```bash
#!/bin/sh

git init
touch ex0.txt
git checkout -b newbranch # Create a new branch
touch ex1.txt
touch ex2.txt # Creating 2 .txt files in newbranch
git add . # Add these new files to the staging area
echo “I like dogs” >> ex1.txt # Adding a change to an existing file
git checkout master # Move back into the master branch
git merge newbranch master # Merge newbranch (which has uncommitted changes)
													 # with master
```

```
The automatic nature of git merge makes it challenging to keep track of any non-
trivial changes. Since the merge occurs in a single action, the user doesn’t
have the ability to traceback the changes that git merge decided to make. The
shell script gives us this ability, as we know exactly what data we’re merging,
but without this exact knowledge, the changes become extremely difficult to
follow. The main problem with merging uncommitted changes is that it can lead to
dangerous merge conflict that ends up deleting the changes that were meant to be
applied to the git repository. For instance, there could be unsaved work (there
is unsaved work in newbranch, in the above script). Once ex1.txt and ex2.txt get
added to the staging area and a merge occurs, it is highly likely that ex1.txt
and ex2.txt would either get corrupted or lost. This is because there is no way
to recover what has never been committed or stashed at some point in time.
Obviously this state is difficult to back out of because now the new additions
that were supposed to be merged are gone. All the work that was lost would have
to be redone by the developer from scratch. The script is a pretty harmless
example of this phenomenon because the only data that is lost are some .txt
files, but this can be a nightmare if the uncommitted changes consisted of work
that took hours, days, or weeks to create.
```



## Question 10

The man page for `git rebase` does not have words of wisdom that are like those mentioned in the previous (`git merge`) question. Should it? Briefly explain.



------



### Answer

```
git rebase is the second Git utility that is used for integrating changes from
one branch to another. It works similarly to git merge, but has a slightly
different function. Git merge is unique in that it has a forward moving change
record. Merges are relatively safe in most scenarios as git does give sufficient
warnings about merge commits and the like when merging two branches together.
However, rebasing can be a bit more dangerous to use. The command git rebase X
essentially computes all the changes from the common ancestor of the two
branches and applies them to the current branch. As one may presume, this can be
quite dangerous because there is always the possibility that a rebase will
overwrite some history that should not have been overwritten. This can be
extremely problematic especially when working on a group project as these shared
branches may have history overwritten. This can interfere with other group
members’ works on accident and cause a lot of pain to try and figure out what
was modified by the rebase command. The man page for git rebase really should
include a warning for the potential consequences that may occur when using the
command as it is not as widely known as git merge — people may have a hard time
understanding what the command actually does and use it incorrectly. The warning
would make people think twice about using the command in case it causes some
unwanted side effects.
```



## Question 11

Suppose we want to reimplement Emacs using Node.js and React, instead of the existing Emacs code base that uses C as its core. We want existing Emacs scripts and keystrokes to work unchanged, so that current users can continue to get their work done. Does this idea make sense? Briefly explain why or why not. Either way, give the biggest obstacles you see to making it work.



------



### Answer

```
Developing a new version of Emacs using Node.js and React would be inefficient
compared to the current implementation. C is low level, which makes Emacs more
programmable, and you can get better performance out of it. Rewriting the Emacs
code base to be in JavaScript would result in a bigger, slower program.
Additionally, Emacs’ portable nature allows for great flexibility. Being
precompiled and able to run without having to do any installs is extremely
useful. The version built with Node.js and React would restrict the users and
take away much of the freedom. If this alternate version of Emacs were deployed
on the web, users would only have access to the version that the authors decide
to host rather than being able to use the version of their choice. One of the
biggest obstacles of rewriting the code base in React and Node.js is the amount
of work that has gone into developing the existing code base currently written
in C. Finding developers willing to rewrite the entire code base would be
incredibly difficult, not to mention tedious. Historically, rewriting the code
base of programs has killed programs, resulting in a totally different program.
So by migrating Emacs to React, you risk ending up with a completely different
program that might have poorer performance than the original Emacs.
```



## Question 12

Assuming you could pull off the idea of reimplementing Emacs in Node.js and React, how does it compare to the existing practice of using Emacs as a development environment for Node.js and React applications? Would there be significant advantages to the proposed implementation compared to the current one? Briefly explain.



------



### Answer

```
In order to start developing in React using Emacs, one must go through a
significant amount of setup. Currently, to develop in React, you need to set up
the package for js-mode, or web-mode to be able to develop smoothly using
JavaScript. However, if Emacs was reimplemented in Node.js and React, this could
no longer be an issue as tools like js-mode and web-mode could be implemented as
a native feature. Overall, it would make the setup process and configuration for
developers who are new to Emacs because they could just install Emacs with all
the proper settings and use it right away. There aren’t really any huge
advantages to developing Emacs in Node.js and React though, which is probably
why no one has bothered to create it.
```


