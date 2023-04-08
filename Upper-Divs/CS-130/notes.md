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

          



## Lecture 3:

- 