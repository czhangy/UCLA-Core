# COM SCI 130 - Spring '23 - Burns

[TOC]

## Lecture 1: Introduction

Nothing to see here!



## Lecture 2: Testing

- Most Important Lessons

  - Use revision control
  - If you don't want it to break, it needs a test

- Testing

  - Why Test?

    - Software has real-world consequences

  - Good tests are automated, repeatable, meaningful, reliable, easy to run, fast, and checked into revision control

  - Types of Tests

    - Unit tests
    - Integration tests
    - Regression tests
    - etc.

  - A well tested system has:

    - Many tests
    - Different kinds of tests, providing overlapping coverage

  - Test-Driven Development?

    - When you know the desired result before you know how to implement it
    - Before fixing a bug, write a unit test that fails because of the bug
    - Useful:
      - Upon discovering a bug => a new test can protect against that bug in the future
      - Ex) API prototyping
        - Write unit tests that are examples of using your API
    - Problems:
      - Can be impractical in practice
      - Adds a lot of overhead/extra work
    -  Conclusion: use when appropriate

  - When can I stop?

    - Signs you need more tests:
      - "Low-level" or "mission-critical" code
      - Lots of people depending on it (customers, coworkers, etc.)
      - Failure is expensive
      - Failure will result in death
    - Software engineering is really about managing risk, which is meaningless without a proper cost-benefit analysis
      - Each application is going to need a different amount of testing depending on the cost of the app breaking vs. the amount of time spent on testing
    - Writing more tests isn't always the answer:
      - Prototypes and rapidly changing code => too much change in behavior, so tests aren't worth the time spent
      - One-off scripts, non-production code
      - Tests can be flaky => results are meaningless
      - Sometimes there is no substitute for manual testing
        - Ex) UIs, hardware
      - Tests are expensive to write and maintain
        - Costs time, money, and opportunity
      - "Should I write more tests?" vs. "What are the right kinds of tests for this situation?"
    - General guidelines for this course:
      - Code should have unit tests, at least for basic use cases and common errors
      - Pretty much all classes and source files should have a unit test
      - Binaries should have an integration tests

  - Case Study: Assignment 1

    - Config Parsing

      - We need a way to configure the webserver we will write

        - ```bash
          % vi config
          % ./webserver config
          ```

      - Why is this separate from my server?

        - Separation of concerns
          - Ex) OOP
        - Separating binary and config is an important robustness surface
          - Lets you roll back misconfigs easily
          - Allows for testing other parts of the system easily using testing configs that exercise them
          - Allows us to easily test multiple different code paths
        - But, this introduces a layer in the code that itself needs testing

      - Example file format:

        - ```config
          port 8080; // Statement
          path /echo EchoHandler {}
          path /static StaticFileHandler { // Group of statements
          	root "example_static_files"; // Made of tokens
          }
          ```

        - Grammar:

          - `<config> ::= <statement>*`
          - `<statement> ::= <token>+ ";" | <token>+ "{" <config> "}"`

    - What tests should we write for this parser?

      - Pass in a bad file handle
        - Ex) Closed file, invalid name, etc.
      - Pass in a config file that doesn't conform to the grammar
        - Ex) Missing semicolon/closing brace, etc.

  - What to test?

    - How to come up with test cases
      - The public API
        - Typical use cases first
      - Error handling
        - Almost all catastrophic system failures are the result of incorrect handling of non-fatal errors explicitly signaled in software
        - In 58% of the catastrophic failures, the underlying faults could easily have been detected through simple testing
      - Anything particularly complex

  - How to test?

    - Unit tests <= today
    - Integration tests <= later
    - End-to-end tests <= later

  - Unit Tests

    - Introduction

      - Tests of code (classes, files, modules) in isolation
      - Written in the same language as the code they test
      - High bang-for-your-buck
        - Fast to write + fast to execute
      - Some unexpected benefits:
        - Serve as documentation, and demonstrates the API
        - You can make changes (refactor) quickly and confidently
        - Faster in the long run
      - Should be independent of the implementation, focusing on the inputs and outputs

    - Finding good test cases

      - Boundary conditions
        - `int add(int a, int b)` => what if `a` or `b` are 0, 1, negative, really big, etc.
        - `double avg(vector<double> a)` => what if `a` is empty, 1 element, really big, etc.
      - Pre and post-conditions
        - What should be true before and after a function, loop, or conditional?
      - Be defensive
        - What happens if something that "can't happen" happens?
      - When in doubt...
        - Write your API docs on public methods

    - Things that are hard to unit test

      - Global variables
      - Long, complex methods
      - Objects with state
      - Tight coupling (interdependent classes)
      - Bad abstractions

    - How to unit test

      - ```c
        foo_test.cc
        	TEST(TestCaseName, TestName) {...} // A test
        	class FooTest : public ::testing::Test {...}; // A fixture
        	TEST_F(FooTest, Bar) { // A test using the fixture
                EXPECT_TRUE(...);
                ASSERT_TRUE(...)
            }
        ```

      - `foo_test.cc` layout:

        - Fixtures and helper code
        - Basic tests first
        - Then, other use cases, error handling, weird edge cases, bugs, etc.

      - Example:

        - ```c
          TEST(SavingsAccountTest, StartAndGetBalance) {
            const int kStartBalance = 50;
            SavingsAccount account(kStartBalance);
            EXPECT_EQ(account.GetBalance(), kStartBalance);
          }
          
          TEST(SavingsAccountTest, Deposit) {
            SavingsAccount account(0);
            const int kDepositAmount = 100;
            account.Deposit(kDepositAmount);
            EXPECT_EQ(account.GetBalance(), kDepositAmount);
          }
          
          TEST(SavingsAccountTest, Withdraw) {
            SavingsAccount account(500);
            account.Withdraw(50);
            EXPECT_EQ(account.GetBalance(), 450);
          }
          ```




## Lecture 3: Code Reviews

- Main Idea
  - The majority of the code you write at a company is building on someone else's code => code should be accessible to future developers
  - Source code isn't valuable unless someone else can use it
- Code Reviews
  - Best proof of reusability is review
  - For code intended for reuse:
    - Give it to someone else and see if they appreciate it
    - They should be able to merge it into the stack and use it
  - Code review ensures that someone else values and understands the code
- Thinking Systems
  - 2 types of systems:
    - System 1: Intuitive, fast, but has higher error rates
    - System 2: Methodical, slow, low error rates, but is hard to engage
  - We often have system 2 blindspots while coding
  - The addition of a code reviewer helps to generate "system 2 code"
  - Rubber duck debugging
    - Explain the problem to a rubber duck:
      - Go through the problem step-by-step
      - Think about each step clearly
      - Realize what the problem is
    - This is **system 2** thinking!
- Research on Code Reviews
  - Code review catches *60-90%* of errors according to a study by Fagan in 1976
  - The first reviewer and first review matter the most according to a study by Cohen in 2006
    - Following reviewers have too much trust in the first reviewer
  - Defect rates in code are related to program size, and seemingly little else according to a study by El Imam in 2001
- Before Sending Code for Review
  - Write code that is easy to review
    - Even if the final state of the code works, any hacky solutions/assumptions should be reviewed to prevent unnecessary growth in complexity
  - Keep changes small and focused
  - Send a work in progress review out early
    - A completely finished product is not necessary to submit a review
    - Especially if you're unfamiliar with the task, early feedback may be helpful
  - Review your own work
    - Goal should be to submit a change and get no comments back
    - Saves time on small changes
  - Change Descriptions
    - More than just "what" the change is
    - "Why" was the change made?
    - "How" was the "why" addressed?
    - Any new testing?
    - Add additional context on the change with whatever tooling available to you
- During Code Review
  - Flag errors of execution
    - Unclear documentation, typos, style violations, bad/missing tests, bugs, etc.
  - Apply deliberative thinking to find errors
    - Is this algorithm correct?
    - Is this built to specifications?
    - Does this code need to exist?
    - Is this the most elegant solution?
  - Develop a shared understanding about the purpose of the code
    - Align team on "landmarks"
    - Small changes can lead to target drift
      - One small change may adjust the behavior of a feature, which can get exacerbated as people build on it
    - Each code review is an opportunity to course-correct
    - How will this code be used in the future?
  - Establish "N + 1" availability on understanding of the code
    - Teams are dybamic
    - Minibus number
      - The amount of people that could become unavailable and the team can still function
- Methods of Code Review
  - Projection code in a meeting
  - Pair programming
  - Pull requests
- Final Code Review Guidelines
  - Be thoughtful and careful with words
  - Avoid personal attacks
  - Reviews are not a competition
  - Don't be too easy



## Lecture 4: Build Systems Deployment

- Vocab

  - **Build**: Compiling your code
    - Source code => Executable binary
  - **Deploy**: Get your code running
    - Run an executable

- Process

  - In the beginning...
    - Run compiler from the command line directly
    - Inputs are a few `.cc` files
    - Output is a single executable
    - Need to know all the flags
  - One step up...
    - Write it down

- Lessons

  - Builds should have one simple step

    - ```bash
      ./build.sh
      ```

  - Builds should be repeatable

    - Different engineers, different times => same output

  - Build scripts go into revision control

- Bash

  - Bash scripts can be tricky to write
  - Bash scripts aren't very readable/maintainable

- Building the Config Parser

  - Input source files are compiled into intermediate files (`.o`), which are linked into executables
  - These intermediate files can be reused if needed, allowing the compilation to only be run once

- Makefiles

  - Encodes the dependency graph of the build
  - Makefiles can get real complex, real fast
  - Difficult to:
    - Detect compilers
    - Detect and build with installed packages
  - Solution: generate Makefiles!

- GNU Build System

  - Autoconf + Automake

  - Notable files:

    - `Makefile.am`
    - `configure`
    - `Makefile.in`
    - `config.h`

  - Run:

    - ```bash
      ./configure
      make
      ```

  - Creates GNU-compatible Makefiles

- CMake

  - Single tool

  - Notable files:

    - `CMakeLists.txt`
    - `build/`
      - For out-of-source builds
    - A ton of generated files

  - Run:

    - ```bash
      cd build
      cmake ..
      make
      ```

  - Supports multiple output formats

- Build System Wishlist

  - A good build system has many desirable features, but unfortunately, some of them are contradictory

  - Correct

    - The build should be a faithful representation of the current state of your source code
    - What if a file has changed somewhere, but the build system didn't realize it?
      - Easy to happen in GNU Make
      - `make clean` to the rescue
      - GMake detects changes by timestamps
        - Hashing is slower, but more accurate
    - The build should be as close as possible to what you're going to release
    - Very hard to achieve!
      - Debug vs. optimized builds
      - Instrumented binaries (e.g., to find memory bugs, coverage)
      - Extra logging?

  - Hermetic

    - Different users, different environments => same result
      - Different OSes?
      - Diferent compilers?
        - Almost never check your compiler into version control
      - Different shell configs?
        - `.bashrc`, `umask`, etc.
    - Possible solutions:
      - Build in a VM
      - Build in a Docker container

  - Flexible

    - Change compilation and linking options
    - Support other languages
    - Support custom build rules

  - Easy to use

    - Build in one step
    - Easy to set up for your project
    - One obvious correct way to do things (Make fails here!)
      - Confusion arises when there is more than one way to achieve the same output

  - Automatable

    - Builds should happen automatically, and frequently
      - Nightly?
      - After every submit? (continuous build)
      - Whenever you save a file you're editing?

  - Fast

    - The more builds you want to do, the faster it needs to be

      - Tell GMake to run 4 build commands at a time (`-j4`)

        - ```bash
          make -j4
          ```

      - Build cluster

      - Cache intermediates => only build what has changed

  - Manages dependencies

    - Very important for "fast" and "scalable"
    - In GMake, you have to declare your dependancies:
      - `foo.cc`: `#include "bar.h"`
      - `Makefile`: `foo.o: foo.cc foo.h bar.o`
      - Now you have dependencies in two places
      - Implicit rules
        - Easier to maintain complex Makefiles
        - Don't always manage dependencies very well
    - Automatic management
      - Read my code, figure out the dependencies
      - Very language-dependent
      - Example: ekam
        - Works by exploration
          - `.h` file: might want to add current directory to `#include` path
          - `.cc` file: try compiling it; what goes wrong?; missing header?
          - `.o` file: does it contain `main()`?; try linking it into a binary
        - Experimental, C++ only
        - If it can't figure something out, it's hard to intervene
      - CMake does this for you!

  - Integrated

    - Build and test when you send a code review, display results to reviewer
    - Save test results to a database you can query
      - How many times was this test run in the past week?
    - Works with your packaging and release system
    - Can query dependencies
      - What targets depend on `X`?
      - How does `X` depend on `Y`?

  - Scalable

    - Supports large codebases
    - Supports many users

- Scalability

  - Build scalability the typical way
    - Constrain the change rate of your dependencies
      - Separate repositories
      - Long-lived release branches
    - Example:
      - Your project depends on a library built by another team
      - Other team builds, tests, releases the library to you once a quarter
      - Side effect: when you get a new release of the library, you spend a week fixing things that have broken
  - Multi-repo vs. mono-repo
    - Multi-repo
      - Separate repositories
      - Release branches
      - Library built/released quarterly
      - Some manual testing possible
      - Spend a week fixing things after release
      - Builds are fast because you only build your code
    - Mono-repo
      - One repository
      - Development on `HEAD`
      - You always have the latest version
      - Test must be automated
      - Fix things as soon as they are broken
      - Have to build the whole codebase to test your code
  - Google's problem
    - We want:
      - Fast builds for engineers
      - Build and test every commit
      - Have to build the whole source tree
    - You can't ever build from scratch
    - You can't `make clean`
    - Reasons to `make clean`:
      - Untracked dependencies
      - Builds aren't reproducible
  - Google's solution
    - Each commit changes only a small part of the source tree
      - The rest of the object files shouldn't need to be recompiled
    - If our builds are always correct, we can cache the results
    - Achieving correctness if really hard!
  - Cloud storage
    - Engineers work on a small part of the code
      - CitC stores and snapshots your changes in the cloud
      - FUSE filesystem makes it transparent (looks like local files you've checked out)
    - Send diffs to the cloud to compile
    - Fetch back binaries (don't care about intermediate object files)
    - Reuse other people's builds
    - Process:
      - Computer sends diffs to build workers
      - SrcFS talks to build workers
      - Build workers and ObjFS talk to each other
      - ObjFS sends the binary to the computer

- Deployment

  - What is deployment?

    - Process that takes you from dev to prod
    - Production:
      - Server: running in the cloud
      - Application: running on users' phones, computers, etc.

  - History

    - To run a web server, you used to have to:
      - Buy hardware
      - Find a place to put your hardware
      - Get a network connection
      - Install and configure an OS
      - Install and configure your software
    - 1997 - 2000: datacenters
    - 2000s: hosting providers, virtualization (computer rental)

  - Where are we now?

    - Recent past:
      - "Here's a VM image, please run 200 instances for me"
        - Configure OS and install software once, then use the image to start
        - No more manual labor
      - Get billed per machine
        - 200 instances will be paid for, regardless of traffic, wasting resources
    - Current:
      - "Here's my web server image, please run enough instances for me"
        - Start with a few, spin up more when usage rises, kill machines when usage falls
      - Get billed for CPU/RAM/storage
        - Much more efficient in sharing/using resources

  - Observations

    - Deployment requires packaging, isolation, and resource management
    - VMs provide these, but at high overhead, is there a better way?

  - An aside on virtualization

    - Widely-used term in CS, but hard to define

    - Easiest to define as the antonym of "actual"

      - Virtual memory vs. actual memory
      - Virtual machine vs. actual machine

    - Predates computers

    - Examples:

      - Virtual functions: specify an interface without an implementation

      - Memory virtualization: present a large address space independent of RAM

      - Storage virtualization: make many disks on many computers appear as one

      - JVM: consistent data, memory, computation model on different architectures

      - Machine virtualization

        - | Technology              | CPU       | Hardware  | OS        | Overhead |
          | ----------------------- | --------- | --------- | --------- | -------- |
          | Emulation               | Different | Different | Different | Higher   |
          | OS-level virtualization | Same      | Different | Different |          |
          | Paravirtualization      | Same      | Different | Different |          |
          | Hypervisor              | Same      | Same      | Different |          |
          | Containerization        | Same      | Same      | Same      | Lower    |

  - Containerization

    - A restricted view of the underlying OS
      - See group of related processes
      - Manage and limit resource usage
      - Separate or restricted filesystem
      - Restrict system calls
    - Linux kernel magic

  - Docker

    - Utilities and glue for Linux containerization
    - A way to build filesystems in layers
    - Defines a package format
      - Basically, a filesystem and a config
    - A package repository
    - Uses the Moby Linux VM to provide Linux utility to Mac/Windows

  - Docker Concepts

    - Image

      - Snapshot of OS, defined by commands, stacked in layers
      - Created by `docker build`
      - Defined by `Dockerfile`
      - Base is another image
        - e.g., `ubuntu:latest`
      - Can be tagged with versions
        - e.g., `latest`
      - Analogous to a binary executable

    - Container

      - Running instance of an image
      - Created by `docker run`
      - Analogous to a running process

    - Volume

      - Virtual disk image

      - Created by:

        - ```bash
          docker run -v/--mount
          docker volume
          ```

      - Persists across restarts

      - Shareable between containers

    - Bind mount

      - Mount the host filesystem in container

      - Created by:

        - ```bash
          docker run -v/--mount
          ```

      - Share data between host and container

      - Volume that lives in host filesystem

    - Port

      - Expose ports inside container to:
        - Host: `127.0.0.1`
        - Internet: `0.0.0.0`
      - Define in:
        - Image (`Dockerfile`)
          - For documentation
        - Container (`docker run`)
          - For implementation

    - Container registries

      - Storage for built container images

      - Local storage:

        - ```bash
          docker image ls
          ```

      - Remote storage:

        - `docker push`
        - `docker pull`
        - And other tools

      - Implicit pull when docker build needs a base image

  - Google Cloud Build

    - Define series of build steps in `cloudbuild.yaml`

    - Start a build with some directory/files as the source

      - ```bash
        gcloud builds submit
        ```

    - Build is performed in the cloud

    - Build is performed hermetically

      - No context from previous builds

    - Output:

      - Build logs
        - Console
        - Web UI
      - Build artifacts
        - Container images
        - Compiled outputs



## Lecture 5:

- 

