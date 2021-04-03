# COM SCI 181 - Spring '21 - Campbell



[TOC]

## Lecture 1: Models of Computation

- Course lies at the intersection of multiple disciplines: 
  - Discrete mathematics
    - Associated with left hemispheric thinking
  - Continuous mathematics
  - Computer science
  - Linguistics
    - Associated with right hemispheric thinking
  - Creativity within constraints
  - Clarity of communication
- Computer/Computation is:
  - Input/Output
    - Interfaces
  - Storage state information
  - Processing/Programmable
  - Deterministic
  - Sequential
    - Bounded action - computers can only process a finite amount of information in a finite amount of time
    - Automatic/mechanical
    - Even applies to most parallel machines
  - What problem the computer is trying to solve
  - Turing complete
  - Given a particular type of computer, what class of problems can that type or model solve?
- Models of computation
  - DFA
    - Corresponds to finite state languages
    - Equivalent to a finite state machine
  - CFG - context-free grammar
    - Corresponds to context-free languages
    - Handles syntax of languages, but not semantics
  - TM - Turing machine
  - There are things that none of these models are capable of doing
  - As we go down the models:
    - There's increasing expressiveness/computational power
    - There's decreasing understandability/predictability
      - There are more and more things that are impossible to predict behaviorally
        - Mathematical, not knowledge-based
- DFA
  - Inputs => finite sequence of symbols chosen from a pre-defined alphabet
  - Output => binary
  - Simplest model for a computer:
    - Black box connected to a lightbulb
      - Lightbulb acts as the binary output
    - Finite input string printed on a tape
      - Read left-to-right, symbol-by-symbol
      - At each symbol, the machine has to declare what its output would be if that were the end of the input
      - On => input so far is accepted
      - Off => input so far is rejected
      - Only input that matters is when the end of the tape is reached
        - On => string was accepted
        - Off => string was rejected
    - Black box must have a program storage/state and sequential/deterministic behavior
      - Directed graph with labels on the edges of the graph
      - Labels correspond to the symbols of the alphabet
        - Alphabet => any non-empty, finite set of objects
      - Finite state machine
        - Contains a special state called the accepting state, which implements the output
        - Binary output => accept/reject => decider
        - Each node has exactly 1 outgoing edge per symbol of the alphabet => Determinism
- Notation
  - Given a string `w` over some alphabet: 
    - Define `w^R` ≡ `w` written in reverse order
      - `(0101)^R` = `1010`
    - Define a "run of symbol `x` in `w`"
      - `w = aabcabbb`
      - `x` ∈ the alphabet `{a, b, c}`
        - `w` contains 2 runs of `a`
        - `w` contains 2 runs of `b`
        - `w` contains 1 run of `c`



## Reading 1: Mathematic Notions, Terminology, and Proofs

- Mathematical Notions and Terminology

  - Sets

    - A **set** is a group of objects represented as a unit

    - Sets can contain numbers, symbols, and other sets

    - Objects in a set are called **elements** or **members**

    - Can be described as:

      - $$
        S = {7, 21, 57}
        $$

        

        

