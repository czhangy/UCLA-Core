# COM SCI M51A - Winter '21 - Abari



[TOC]

## **Lecture 1: Introduction**

- Digital system - inputs and outputs are a finite number of discrete values
  - Ex) Calculator
  - Can be used for numerical and nonnumerical processing
  - Information processing can use a general-purpose system
  - Digital representation - binary signals
    - Easy for hardware implementation
    - Switches/transistors are open or closed
  - Digital systems are very robust to noise/insensitive to variations
  - Numerical digital systems can be made more accurate by increasing the number of digits we use
  - Advances of microelectronics
    - Possible to fabricate extremely complex systems, which are small, fast, and cheap
    - Digital systems built as integrated circuits composed of a large number of simple devices
  - Different implementations of systems which trade-off cost and performance
- Analog system - inputs and outputs are continuous
  - Ex) Earth
- Mixed systems - analog and digital
  - We live in an analog world (temperature, sound, etc. are continuous)
  - We like to build digital systems
  - Mismatch between our world and system preferences → convert from analog to digital for processing
    - Ex) Microphone and speaker
- High-level specification
  - Input set - set of values for the input
  - Output set - set of values for the output
  - Input-output function
    - Defined with a table, arithmetic expression, conditional expression, logical expression, composition of simpler functions, etc.
- Combinational and sequential systems
  - Classes of digital systems
  - Combinational - no memory, the output doesn’t depend on previous inputs
  - Sequential - has memory, the output depends on previous inputs
- Data Representation and Manipulation
  - How characters and numbers are represented in a typical computer
  - Characters - ASCII (7 bits)

## **Lecture 2: Data Representation**

- Switching function - relation between inputs and outputs
  - Typically presented in a truth table
  - Symbols 0 and 1 are SEs
  - A symbol representing a binary variable is an SE
- \+ represents or, . represents and, ‘ represents complement
- Boolean algebra properties
  - Commutativity - `ab = ba`, `a + b = b + a`
  - Distributivity - `a(b + c) = (ab) + (ac)`, `a + (bc) = (a + b)(a + c)`
  - Associativity - `a + (b + c) = (a + b) + c`, `a + b + c`, `(ab)c = a(bc) = abc`
  - Idempotency - `a + a = a`, `aa = a`
  - Complement - `a + a’ = 1`, `aa’ = 0`
  - Identity - `0 + a = a`, `1a = a`
  - Involution - `(a’)’ = a`
  - Absorption - `a + ab = a`, `a(a + b) = a`
  - Simplification - `a + a’b = a + b`, `a(a’ + b) = ab`
  - De Morgan’s Law - `(a + b)’ = a’b’`, `(ab)’ - a’ + b’`
- Logic gates

## **Lecture 3: Sum of Products and Minterms**

- Product terms - terms containing 0 or more ANDs
  - `x0`, `x2x1`, `x3x1x0’`
- Sum of products - using OR on product terms
- Minterm notation - `mj = xn...x0` where `xi = 1` and `xi’ = 0`
  - Minterm `x3x2’x1’x0` is `m9` because `1001 = 9`
  - Minterms only have value of `1` for corresponding `j` input
  - System with `n` inputs has `2n` minterms
  - Can be used to represent gate output
- Can transition from given truth table to sum of minterms
  - Find lines with output of `1`
  - Get all minterms from those lines
  - Expression is OR of all those terms
- Convert expression to sum of minterms
  - Convert to equivalent sum of products
  - Convert product terms to minterms
  - Eliminate repeated minterms
- Sum terms - terms containing 0 or more ORs
  - `x0`, `x2 + x0`, `x3 + x1 + x0’`
- Product of sums - using AND on sum terms
- Maxterm notation - `Mj = xn...x0` where `xi = 0` and `xi’ = 1`
  - Maxterm `x3 + x2’ + x1 + x0’` is `M5` because `0101 = 5`
- Can transition from given truth table to product of maxterms
- Find lines with output of `0`
- Get all maxterms from those lines
- Expression is AND of all those terms

## **Lecture 4: Transistors**

- CMOS - complementary metal oxide semiconductor
- Representation of binary variables
  - Representation of `0` and `1` electrical signals - voltages, currents, charges, etc.
  - Realization of circuits that operate on these signals to implement desired switching functions
  - Typical values for a 3.3V CMOS technology
    - `VHmax = 3.3V`, `VLmax = 0.8V`, `VHmin = 2.0V`, `VLmin = 0.0V`
- Structure and operation of transistors
  - 2 types: n-type and p-type (NMOS and PMOS)
    - Resistance between `A` and `B` very low → switch closed, resistance very high → switch open
      - Compare to some threshold voltage
    - Exactly opposite of each other
  - NMOS - high voltage gate = closed switch, low voltage gate = open switch
  - PMOS - high voltage gate = open switch, low voltage gate = closed switch
    - Have circle on symbol
- To analyze a CMOS circuit:
  - Make table with inputs, transistors, and outputs
  - For each row of table, check whether transistor resistance is high or low
  - For each row of table, check if output has clean path to power or ground
    - Neither (floating)/both - bad design

## **Lecture 5: Transmission Gates**

- Transmission gate
  - 3 state buffer
  - Low voltage on `C` → high-impedance state
    - `Z` regardless of other input
  - High voltage on `C` → input is same as other input
  - Need to combine PMOS and NMOS
    - NMOS is a good switch → NMOS connects to ground → `0`
    - PMOS is a good switch → PMOS connects to `VDD` → `1`
  - Can control module → output transition
  - Can be used to build multiplexer

## **Lecture 6: Timing Analysis**

- Find delays between changing input → changing output
  - `TpLH` → time from low to high
  - `TpHL` → time from high to low
  - `Fan` → number of inputs
  - `L` → number of output channels
- Propagation delay of a system is worst path through system
  - FPGA vs. ASIC
  - FPGA - flexible
- ASIC - higher-performance
- Wafer → die (integrated chipset)
- 2-level network
  - And-or network → sum of products
  - Or-and network → product of sums
- Minimal 2 level network
  - Inputs are complemented and uncomplemented
  - Fan-in unlimited
  - Single output networks
  - Minimum number of gates and inputs

## **Lecture 7: Two-Level Systems**

- 2 types: OR-AND and AND-OR
- k-Maps:
  - 2-D array of cells
  - `n` variables → `2n` cells
  - Represents switching functions/expressions
  - Graphical aid in simplifying expressions
- Any 2 neighboring cells have a 1-variable difference

## **Lecture 8: Sequential Systems**

- Output is a function of the input over a given period of time
- In addition to input and output, we define a state for our system at time `t`
  - Ex) `s(t) ∈ {EVEN, ODD}`
  - Represent with transition and output functions
  - Output depends on input + state
- State diagrams
  - Represent state using circle
  - Separate input and output with ‘/’
  - Transition shown by arrow
- Mealy and Moore machines
  - Mealy machine - output is a function of state and input
    - `s(t + 1) = H(s(t), x(t))`
  - Moore machine - output is a function of state only
    - `s(t + 1) = H(s(t))`
    - Can simplify state diagram by writing `S/z` in circles
- Reduction of the State Set
  - States are distinguishable if they don’t have exactly the same outputs
  - States are equivalent if they have exactly the same outputs
  - States are 2-equivalent if a string of 2 inputs result in the same outputs

## **Lecture 9: Flip-Flops**

- Sequential System Implementation
  - Combinational network takes in present input, gives output
  - State register takes in present state and outputs next state
- SR Latch with NOR gates
  - 2 NOR gates
  - Both inputs `0` → value stays the same
  - `0 1` → reset state
  - `1 0` → Set state
  - `1 1` → undefined
  - Advantages:
    - Can remember value
    - Natural reset and set signals
  - Disadvantages:
    - `SR = 11` input has to be avoided
    - No notion of a clock or change at discrete points yet
- The D Latch
  - Similar to SR Latch, added gates at the inputs
  - `0 X` → no change in state
  - `1 0` → `Q = 0` → reset
  - `1 1` → `Q = 1` → set
  - Clock is `0` → no change
  - Clock is `1` → copy input to output
- The D Flip Flop
  - We want state to be affected only at discrete points in time; a master-slave design achieves this
  - D Latches in series → one is a master and one is a slave
  - Second D Latch works in inverse of first
  - Flip flop updates value on the falling edge of the clock
    - Put another inverter → updates on rising edge
  - `QE` depends on `QI`, which depends on `D`
    - `QE` depends on `D` at the falling edges
  - Stores 1 bit per flip-flop
- Flip-Flop: Master-Slave
  - Inverter on diagram means it’s sensitive to the falling edge
  - `Q(t + 1) = D(t)`
- In reality, there’s propagation delay where the flip flop gets updated
- Timing parameters of a binary cell
  - Set-up time - the amount of time the input is stable before a sample
  - Hold time - the amount of time the input is stable after a sample
- Network set-up time: `tsu(net) = d1x + tsu(cell)`
- Network hold time: `th(net) = th(cell)`
- Network propagation delay: `tp(net) = tp(cell) + d2`

## **Lecture 10: Design of Canonical Networks**

- Design
  - Translate states and inputs to binary
  - Use K-maps to find expressions for states/output
  - Use the expressions to create a gate level design
    - Number of flip-flops = number of bits needed to represent state
- SR Flip-Flop
  - 2 inputs: `S` and `R` → `S(t)R(t)`
  - `PS = 0` → `S(t) = 0` returns to current state, `10` goes to state `1`
  - `PS = 1` → `R(t) = 0` returns to current state, `01` goes to state `0`
  - `11` is undefined for both states
  - `Q(t + 1) = Q(t)R’(t) + S(t)`, restriction: `R(t) · S(t) = 0`
  - 2 other inputs: preset and clear → independent of `CLK`
    - Preset → set `Q(t)` to `1`
    - Clear → set `Q(t)` to `0`
- JK Flip-Flop
  - Same as SR Flip-Flop
  - Added `11` input → inverts `Q(t)`
  - `Q(t + 1) = Q(t)K’(t) + Q’(t)J(t)`
- T (Toggle) Flip-Flop
  - 1 input: `T`
  - `T(t) = 0` → `Q(t + 1) = Q(t)`
  - `T(t) = 1` → `Q(t + 1) = Q’(t)`
  - `Q(t + 1) = Q(t) ^ T(t)`
  - Has PR and CLR inputs
- Design is opposite of analysis

## **Lecture 11: Decoders**

- Decoder has `n` inputs, `2^n` outputs
  - Can be used for main memory
  - Essentially translates binary to minterms
- Coincident Decoder
  - 2 decoders connected by AND gates
  - `n` total inputs --> creates `2^n` outputs from smaller decoders
- Tree Decoder
  - 1 decoder's output connected to enable ports
  - Inputs shared between decoders
- Encoder has `2^n` inputs, `n` outputs
  - Only one of the input bits can be `1`
  - Translates from minterm to binary
  - Priority Binary Encoder
    - Ignores bits past the leading `1`
