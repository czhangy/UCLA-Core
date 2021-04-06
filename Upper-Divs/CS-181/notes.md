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



## Lecture 2: Deterministic Finite Automata

- Problem refers to an infinite number of instances

- An alphabet is defined as any nonempty, finite set of objects (other than epsilon) called symbols

- A string/word is defined as a finite sequence of symbols from a given alphabet `Σ`

  - We generally refer to this as a string or word over an alphabet

  - The length of a word, `|w|` is the number of symbols in `w`

  - $$
    \Sigma^+\equiv\{\text{all nonempty words over}\  \Sigma\}
    $$

    - Infinite set of finite-length strings
      - The strings are indefinitely long

    - String of length 1 could also be a symbol in the alphabet

- Let `Σ` be an alphabet and `w` be a string over `Σ` of the form `rst`

  - `r`, `s`, and `t` are substrings of `w`
    - Any substring of `w` is called a proper substring of `w` as long as its not the entire word
  - `r` is a prefix of `w`
  - `t` is a suffix of `w`

- Define `#(a, w)` where:

  - $$
    a\in\Sigma\\
    w\in\Sigma^+
    $$

  - To be the number of occurrences of symbol `a` in string `w`

- Define a "run of `a` in `w`" as a substring of `w` such that it consists only of 1 symbol `a` and there are no other `a`'s adjacent to it

- Define `w^R` as a word `w` written in reverse order

- Given an alphabet `Σ`, we define a language over `Σ` to be any set of words over `Σ`

  - So, a language is any subset of `Σ^+`
    - `{}` is a language over any alphabet
    - A language is any member of `P(Σ^+)`
  - Languages can represent computational problems

- `ε` can be a proper substring of any string except `ε`

- Generalize concatenate:

  - $$
    \Sigma^+=\Sigma\cup\Sigma\cdot\Sigma\cup\Sigma\cdot\Sigma\cdot\Sigma\cup\cdot\cdot\cdot
    $$

    - Language concatenation:

      - $$
        S\cdot T\equiv\{s\cdot t|\ s\in S, t\in T\}
        $$

- Formal Definition of Deterministic Finite Automata

  - See Reading 2
  - If a DFA is missing some input option, then blocking occurs and the input is rejected

  

## Reading 1: Discrete Concepts

- Mathematical Notions and Terminology

  - Sets

    - A **set** is a group of objects represented as a unit

    - Sets can contain numbers, symbols, and other sets

    - Objects in a set are called **elements** or **members**

    - Can be described as:

      - $$
        S = \{7, 21, 5\}
        $$

    - We say that a set `A` is a **subset** of a set `B` if every member of `A` is also a member of `B`

      - `A` is a **proper subset** of `B` if `A` is a subset of `B` and `B` is not a subset of `A`

    - Order and repetition of elements don't matter

      - If the number of occurrences of members matter, the group is instead called a **multiset**
      - An **infinite set** consists of infinitely many elements
      - The **empty set** contains 0 members
      - A set containing 1 member is called the **singleton set**
      - A set with 2 members is called an **unordered pair**

    - Sets can be described with a rule rather than with discrete elements

    - The **union** of 2 sets is the set obtained by combining the elements of both sets

    - The **intersection** of 2 sets is the set of elements that are in both sets

    - The **complement** of a set is the set of all elements under consideration that are not in the set

  - Sequences and Tuples

    - A **sequence** of objects is a list of objects in some order

      - Can be described as:

        - $$
          \\(7, 21, 57)
          $$

      - Order and repetition matter in a sequence

      - Finite sequences are called **tuples**

        - A sequence with `k` elements is called a **`k`-tuple**
        - A 2-tuple is also called a **ordered pair**

      - Sets and sequences may appear as elements of other sets and sequences

        - The **power set** of `A` is the set of all subsets of `A`
        - The **Cartesian product** or **cross product** of 2 sets `A` and `B` is the set of all ordered pairs wherein the first element is a member of `A` and the second is a member of `B`
          - The Cartesian product of `k` sets is the set consisting of all `k`-tuples following the same guidelines

  - Functions and Relations

    - A **function** is an object that sets up an I/O relationship

      - The same input always produces the same output

      - Also called a **mapping**, where if `f(a) = b`, then `f` maps `a` to `b`

      - The set of possible inputs to a function is called its **domain**

      - The outputs of a function come from a set called the **range**

        - $$
          f: D\rightarrow R
          $$

          - `f` is a function with domain `D` and range `R`

        - A function may not use all of the elements of the specified range

        - A function that does use all the elements of the range is said to be **onto** the range

      - When the domain of a function `f` is `A_1 x ... x A_k` for some sets `A_1, ... , A_k`, the input to `f` is a `k`-tuple `(a_1, a_2, ... , a_k)` and `a_i` is an **argument** to `f`

        - A function with `k` arguments is called a **`k`-ary function**, where `k` is the **arity** of function
          - If `k` is 1, then `f` is a **unary function**
          - If `k` is 2, then `f` is a **binary function**
            - Common binary functions are written using **infix notation** rather than **prefix notation**

      - A **predicate** or **property** is a function whose range is `{TRUE, FALSE}`

        - A property whose domain is a set of `k`-tuples `A x ... x A` is called a **relation**, **`k`-ary relation**, or a  **`k`-ary relation on `A`**
          - Common case is a 2-ary relation, or **binary relation**
            - Usually use infix notation

    - Special type of binary relation that captures the notion of 2 objects being equal in some feature is called an **equivalence relation**

      - `R` is **reflexive** if for every `x`, `xRx`
      - `R` is **symmetric** if for every `x` and `y`, `xRy` implies `yRx`
      - `R` is **transitive** if for every `x`, `y`, and `z`, `xRy` and `yRz` implies `xRz`

  - Graphs

    - An **undirected graph**, or simply a **graph** is a set of points with lines connecting some of the points
      - The points are called **nodes** or **vertices**
      - The lines are called **edges**
        - The number of edges at a particular node is the **degree** of that node
        - No more than 1 edge is allowed between any 2 nodes
        - Edges can go from a node to itself, called a **self-loop**
      - If `V` is the set of nodes of a graph `G` and `E` is the set of edges, we say `G = (V, E)`
    - Graphs are used to represent data
      - For convenience, we label the nodes/edges of the graph, which makes the graph a **labeled graph**
    - `G` is a **subgraph** of `H` if the nodes of `G` are a subset of the nodes of `H` and the edges of `G` are the edges of `H` on the corresponding nodes
    - A **path** in a graph is a sequence of nodes connected by edges
      - A **simple path** is a path that doesn't repeat any nodes
      - A graph is **connected** if every 2 nodes have a path between them
      - A path is a **cycle** if it starts and ends in the same node
      - A **simple cycle** is one that contains at least 3 nodes and repeats only the first and last nodes
      - A graph is a **tree** if it's connected and has no simple cycles
        - Tree may contain a specially designated node called the **root**
        - Nodes of degree 1 in a tree, other than the root are called **leaves**
    - A **directed graph** has arrows instead of lines
      - Number of arrows pointing from a particular node is the **outdegree** of that node
      - The number of arrows pointing to a particular node is the **indegree**
      - A path in which all the arrows point in the same direction as its steps is called a **directed path**
        - A directed graph is **strongly connected** if a directed path connects every 2 nodes
      - Useful for depicting binary relations

  - Strings and Languages

    - An **alphabet** is any nonempty finite set
      - The members of the alphabet are **symbols** of the alphabet
    - A **string over an alphabet** is a finite sequence of symbols from that alphabet, usually written next to one another and not separated by commas
    - The **length** of a string `w` is the number of symbols `w` contains, written `|w|`
      - The string of length 0 is called the **empty string**, written `ε`
    - The **reverse** of `w`, written `w^R` is the string obtained by writing `w` in the opposite order
    - String `z` is a **substring** of `w` if `z` appears consecutively within `w`
    - Given string `x` of length `m` and string `y` of length `n`, the concatenation of `x` and `y`, `xy`, is the string obtained by appending `y` to the end of `x`
    - The **lexicographic order** of strings is the same as the familiar dictionary order
      - We occasionally use a modified lexicographic order called **shortlex order** or **string order** where shorter strings precede longer strings
    - String `x` is a **prefix** of string `y` if a string `z` exists where `xz = y`
      - `x` is a **proper prefix** of `y` if in addition `x != y`
    - A **language** is a set of strings
      - A language is **prefix-free** if no member is a proper prefix of another member

  - Boolean Logic

    - **Boolean logic** is a mathematical system built around the two values `TRUE` and `FALSE`
      - The values `TRUE` and `FALSE` are called the **Boolean values** and are often represented by the values 1 and 0
      - We can manipulate Boolean values with the **Boolean operations**
        - The simplest Boolean operation is the **negation** or **`NOT`** operation, designated with the symbol `¬`, which converts a Boolean value to the opposite value
        - We designate the **conjunction** or **`AND`** operation with the symbol `∧`
          - The conjunction of two Boolean values is `1` if both of those values are `1`
        - The **disjunction** or **`OR`** operation is designated with the symbol `∨`
          - The disjunction of 2 Boolean values is `1` if either of those values is `1`
        - The operations are used on **operands** 
        - The **exclusive or**, or **`XOR`**, operation is designated by the `⊕` symbol and is `1` if either but not both of its 2 operands is `1`
        - The **equality** operation, written with the symbol `↔`, is `1` if both of its operands have the same value
        - Finally, the **implication** operation is designated by the symbol `→` and is `0` if its first operand is `1` and its second operand is `0`; otherwise, `→` is `1`
      - The **distributive law** for `AND` and `OR`:
        - `P ∧ (Q ∨ R)` equals `(P ∧ Q) ∨ (P ∧ R)`
        - `P ∨ (Q ∧ R)` equals `(P ∨ Q) ∧ (P ∨ R)`

- Definitions, Theorems, and Proofs

  - **Definitions** describe the objects and notions that we use
    - Precision is essential to any mathematical definition
  - After we have defined various objects and notions, we usually make **mathematical statements** about them
    - Typically, a statement expresses that some object has a certain property
    - No ambiguity about its meaning is allowed
  - A **proof** is a convincing logical argument that a statement is true
    - A mathematician demands proof beyond *any* doubt
  - A **theorem** is a mathematical statement proved true
    - A **lemma** is a statement that is only interesting because it assist in the proof of another, more interesting statement
    - A **corollary** of a theorem is a statement that can be proved true due to its relation to the theorem or its proof
  - Finding Proofs
    - One frequently occurring type of multipart statement has the form “`P` if and only if `Q`”
      - If `P` is true, then `Q` is true, written `P ⇒ Q` => the **forward direction** of the original statement
      - If `Q` is true, then `P` is true, written `P ⇐ Q` => the **reverse direction** of the original statement
    - An object that fails to have the property you're trying to prove is called a **counterexample**
    - A well-written proof is a sequence of statements, wherein each one follows by simple reasoning from previous statements in the sequence

- Types of Proof

  - Proof by Construction
    - **Proof by construction** is a proof technique where you demonstrate how to construct the object that you are trying to prove exists
  - Proof by Contradiction
    - **Proof by contradiction** is a proof technique where you begin by assuming the theorem is false and then showing that this assumption leads to a false consequence called a contradiction
  - Proof by Induction
    - **Proof by induction** is a method used to show that all elements in an infinite set have a specified property
    - Each proof by induction has 2 parts:
      - The **basis** proves that `P(1)` is true
      - The **induction step** proves that for each `i ≥ 1`, if `P(i)` is true, then so is `P(i + 1)`
        - In the induction step, the assumption that `P(i)` is true is called the **induction hypothesis**



## Reading 2: Finite Automata

- Finite automata are good models for computers with an extremely limited amount of memory

  - Automatic door example, elevators, household appliances, etc.

- Finite automata and their probabilistic counterpart **Markov chains** are useful tools when we are attempting to recognize patterns in data

  - Used in speech processing and in optical character recognition
  - Markov chains have been used to model and predict price changes in financial markets

- A **state diagram** is a visualization of the interaction between inputs, outputs, and states of a finite automaton

  - The **start state** is indicated by the arrow pointing at it from nowhere, and is the state where processing starts at
  - The **accept state** is the one with a double circle
  - The arrows going from one state to another are called **transitions**
  - The output is either **`accept`** or **`reject`**
    - Output is `accept` when the automaton is in an accept state and `reject` otherwise

- Formal Definition of a Finite Automaton

  - A finite automaton has several parts:

    - It has a set of states and rules for going from one state to another, depending on the input symbol
    - It has an input alphabet that indicates the allowed input symbols
    - It has a start state and a set of accept states

  - The formal definition says that a finite automaton is a list of those five objects: set of states, input alphabet, rules for moving, start state, and accept states

  - We use something called a **transition function**, frequently denoted `δ`, to define the rules for moving

    - Ex) the finite automaton has an arrow from a state `x` to a state `y` labeled with the input symbol `1`

      - $$
        \delta (x, 1)=y
        $$

  - Formal definition:

    - A **finite automaton** is a 5-tuple `(Q, Σ, δ, q_0, F)`, where:

      - `Q` is a finite set called the **states**
      - `Σ` is a finite set called the **alphabet**
      - `δ: Q × Σ → Q` is the **transition function**
        - Specifies exactly 1 transition arrow exits every state for each possible input symbol
      - `q_0 ∈ Q` is the **start state**
      - `F ⊆ Q` is the **set of accept states** or **final states**
        - The null set is valid for `F` => there could be no accept states

    - If `A` is the set of all strings that machine `M` accepts, we say that `A` is the **language of machine `M`** and write:

      - $$
        L(M) = A
        $$

      - We say that **`M` recognizes `A`** or that **`M` accepts `A`**

      - A machine may accept several strings, but it always recognizes only one language

- Formal Definition of Computation

  - Let `M = (Q,Σ,δ,q_0,F)` be a finite automaton and let `w = w_1w_2 ··· w_n` be a string where each `w_i` is a member of the alphabet `Σ`

    - `M` **accepts** `w` if a sequence of states `r_0,r_1, ... ,r_n` in `Q` exists with 3 conditions:

      - $$
        r_0=q_0
        $$

        - The machine starts in the start state

      - $$
        \delta(r_i, w_{i+1}) = r_{i+1},\ \text{for}\  i=0,...,n-1
        $$

        - The machine goes from state to state according to the transition function

      - $$
        r_n\in F
        $$

        - The machine accepts its input if it ends up in an accept state

    - `M` **recognizes language** `A` if:

      - $$
        A=\{w|\ M\ \text{accepts}\ w\}
        $$

      - A language is called a **regular language** if some finite automaton recognizes it

- Designing Finite Automata

  - "Reader as automata" method

- The Regular Operations

  - We define three operations on languages, called the **regular operations**, and use them to study properties of the regular languages:

    - **Union**:

      - $$
        A\cup B=\{x|\ x\in A\ \text{or}\ x\in B \}
        $$

        - Takes all the strings in both `A`and `B` and lumps them together in 1 language

    - **Concatenation**:

      - $$
        A \circ B =\{xy|\ x\in A\ \text{and}\ y\in B\}
        $$

        - Attaches a string from `A` in front of a string from `B` in all possible ways to get the strings in the new language

    - **Star**:

      - 
        $$
        A^*=\{x_1x_2...x_k|\ k\ge 0\ \text{and each}\ x_i\in A\}
        $$

        - Works by attaching any number of strings in `A` together to get a string in the new language
        - **Unary operation** rather than **binary operation**

  - Generally speaking, a collection of objects is **closed** under some operation if applying that operation to members of the collection returns an object still in the collection

    - The class of regular languages is closed under the union operation



## Reading 3: Nondeterminism

- When a DFA machine is in a given state and reads the next input symbol, we know what the next state will be - **deterministic** computation

  - In a **nondeterministic** machine, several choices may exist for the next state at any point
  - Nondeterminism is a generalization of determinism => every deterministic finite automaton is automatically a nondeterministic finite automaton

- Differences:

  - Every state of a DFA has exactly 1 exiting transition arrow for each symbol in the alphabet
    - In an NFA, a state may have 0, 1, or many exiting arrows for each alphabet symbol
  - In a DFA, labels on the transition arrows are symbols from the alphabet
    - An NFA may have 0, 1, or many arrows from each state labeled with `ε`

- How does an NFA compute?

  - After reading a symbol, the NFA splits into multiple copies of itself and follows all possibilities in parallel
    - Each copy takes a single way to proceed and continues as before
    - For subsequent choices, the machine will split again
    - If the next input symbol doesn't appear on any of the arrows exiting the current state, that copy of the machine dies
  - If any one of the copies of the machine is in an accept state at the end of the input, the input string is accepted
  - If a state with a `ε` symbol on an exiting arrow is encountered, the machine will split and follow each of these arrows, while leaving a copy of the machine at the current state
  - Operates like a tree of possibilities, where the root of the tree is the start of the computation

- Every NFA can be converted into an equivalent DFA

- Formal Definition of a Nondeterministic Finite Automaton

  - In a DFA, the transition function takes a state and an input symbol and produces the next state

  - In an NFA, the transition function takes a state and an input symbol or the empty string and produces the set of possible next states

  - A **nondeterministic finite automaton** is a 5 tuple `(Q, Σ, δ, q_0, F)` where:

    - `Q` is a finite set of states

    - `Σ` is a finite alphabet

    - The transition function is:

      - $$
        \delta : Q\times \Sigma_\varepsilon\rightarrow\mathcal{P}(Q)
        $$

    - The start state is:

      - $$
        q_0\in Q
        $$

    - The set of accept states is:

      - $$
        F\subseteq Q
        $$

- Equivalence of NFAs and DFAs

  - Deterministic and nondeterministic finite automata recognize the same class of languages

  - 2 machines are **equivalent** if they recognize the same language

  - > Every nondeterministic finite automaton has an equivalent deterministic finite
    > automaton

    - Proof:

      - Let `N = (Q, Σ, δ, q_0, F)` be the NFA recognizing some language `A`, we construct a DFA `M = (Q', Σ', δ'', q_0', F')` recognizing `A`

      - $$
        Q'=\mathcal{P}(Q)
        $$

        - Every state of `M` is a set of states of `N` => `P(Q)` is the set of subsets of Q

      - For `R ∈ Q'` and `a ∈ Σ`, let:

        - $$
          \delta '(R, a) = \{q\in Q|\ q\in \delta(r, a) \ \text{for some}\ r\in R\}
          $$

          - If `R` is a state of `M`, it is also a set of states of `N`

          - When `M` reads a symbol `a` in state `R`, it shows where `a` takes each state in `R`

          - $$
            \delta '(R,a) =\bigcup_{r\in R}\delta(r,a)
            $$

      - $$
        q_0' =\{q_0\}
        $$

        - `M` starts in the state corresponding to the collection containing just the start state of `N`

      - $$
        F' =\{R\in Q'|\ R\ \text{contains an accept state of}\ N\}
        $$

        - The machine `M` accepts if one of the possible states that `N` could be in at this point is an accept state

      - For any state `R` of `M`, we define `E(R)` to be the collection of states that can be reached from members of `R` by going only along `ε` arrows, including the members of `R` themselves:

        - $$
          E(R)=\{q|\ q\ \text{can be reached from}\ R\ \text{by traveling along 0 or more}\ \varepsilon\ \text{arrows}\}
          $$

      - $$
        \delta'(R, a)=\{q\in Q|\ q\in E(\delta(r,a))\ \text{for some}\ r\in R\}
        $$

        - Modify the transition function of `M` to place additional "fingers" on all states that can be reached by going along `ε` arrows after every step

      - $$
        q'_0=E(\{q_0\})
        $$

        - Modify the start state of `M` to move the fingers initially to all possible states that can be reached from the start state of `N` along the `ε` arrows

  - > A language is regular if and only if some nondeterministic finite automaton recognizes it

- Closure Under the Regular Operations

  - > The class of regular languages is closed under the union operation

    - Proof:

      - Let `N_1 = (Q_1, Σ, δ_1, q_1, F_1)` recognize `A_1` and `N_2 = (Q_2, Σ, δ_2, q_2, F_2)` recognize `A_2`, construct `N = (Q, Σ, δ, q, F)` to recognize `A_1 ∪ A_2`

      - $$
        Q=\{q_0\}\cup Q_1\cup Q_2
        $$

        - The states of `N` are all the states of `N_1` and `N_2`, with the addition of a new start state `q_0`

      - The state `q_0` is the start state of `N`

      - The set of accept states:

        - $$
          F=F_1\cup F_2
          $$

          - The accept states of `N` are all the accept states of `N_1` and `N_2` => `N` accepts if either `N_1` or `N_2` accept

      - Define `δ` so that for any `q ∈ Q'` and any `a ∈ Σ_ε`:

        - $$
          \delta(q,a)=\begin{cases}\delta_1(q,a)&q\in Q_1\\\delta_2(q,a)&q\in Q_2\\\{q_1,q_2\}&q=q_0\ \text{and}\ a=\varepsilon\\\emptyset&q=q_0\ \text{and}\ a\ne\varepsilon\end{cases}
          $$

  - > The class of regular languages is closed under the concatenation operation

    - Proof:

      - Let `N_1 = (Q_1, Σ, δ_1, q_1, F_1)` recognize `A_1` and `N_2 = (Q_2, Σ, δ_2, q_2, F_2)` recognize `A_2`, construct `N = (Q, Σ, δ, q, F)` tp recognize `A_1 ◦ A_2`

      - $$
        Q=Q_1\cup Q_2
        $$

        - The states of `N` are all the states of `N_1` and `N_2`

      - The state `q_1` is the same as the start state of `N_1`

      - The accept states `F_2` are the same as the accept states of `N_2`

      - Define `δ` so that for any `q ∈ Q'` and any `a ∈ Σ_ε`:

        - $$
          \delta(q,a)=\begin{cases}\delta_1(q,a)&q\in Q_1\ \text{and}\ q\notin F_1\\\delta_2(q,a)&q\in F_1\ \text{and}\ a\ne\varepsilon\\\delta_1(q,a)\cup\{q_2\}&q\in F_1\ \text{and}\ a=\varepsilon\\\delta_2(q,a)&q\in Q_2\end{cases}
          $$

  - > The class of regular languages is closed under the star operation

    - Proof:

      - Let `N_1 = (Q_1, Σ, δ_1, q_1, F_1)` recognize `A_1`, construct `N = (Q, Σ, δ, q, F)` tp recognize `A_1*`

      - $$
        Q=\{q_0\}\cup Q_1
        $$

        - The states of `N` are the states of `N_1` plus a new start state

      - The state `q_0` is the new start state

      - $$
        F=\{q_0\}\cup F_1
        $$

        - The accept states are the old accept states plus the new start state

      - Define `δ` so that for any `q ∈ Q'` and any `a ∈ Σ_ε`:

        - $$
          \delta(q,a)=\begin{cases}\delta_1(q,a)&q\in Q_1\ \text{and}\ q\notin F_1\\\delta_1(q,a)&q\in F_1\ \text{and}\ a\ne\varepsilon\\\delta_1(q,a)\cup\{q_1\}&q\in F_1\ \text{and}\ a=\varepsilon\\\{q_1\}&q=q_0\ \text{and}\ a=\varepsilon\\\emptyset&q=q_0\ \text{and}\ a\ne\varepsilon\end{cases}
          $$



## Reading 4: Regular Expressions

- 



































