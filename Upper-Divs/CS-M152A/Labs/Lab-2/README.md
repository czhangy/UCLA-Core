# Floating Point Conversion

## Goal

**Use the Xilinx ISE to design and test an 8-bit floating point converter.**

## Requirements

- Top module
  - Take an input `D[11:0]`, which is a linear encoding in two's complement representation
  - Output `S`, the sign bit, `E[2:0]`, the exponent, and `F[3:0]`, the significand
  - Use compression to convert between the inputted linear encoding and the outputted floating-point representation
  - Module 1
    - Take in the linearly encoded data and convert it to sign-magnitude
    - Extract the sign bit `S` for output
  - Module 2
    - Count the number of leading zeroes to determine the exponent
    - Extract the leading bits used to determine the significand and round
  - Module 3
    - Round the significand up if the 5th bit is `1`
    - Round the exponent up if the significand overflows
    - Ignore cases where both the exponent and significand overflow
- Testbench
  - Cover as many test cases as possible
    - Regular positive number case
    - Regular negative number case
    - All known positive rounding cases from the spec
    - Negative rounding cases
    - Positive rounding case, where the significand overflows
    - Negative rounding case, where the significand overflows
    - Maximum negative number (`1000000000`)
    - Maximum positive number (`011111111111`)
    - `-1` (`111111111111`)
    - Large positive number
    - Large negative number

## Deliverables

- Coding
  - [x] Module that converts two's-complement to signed magnitude, extracting the sign bit
  - [x] Module that counts leading zeroes and extracts leading bits
  - [x] Module that rounds properly
  - [x] Top module that connects modules together
  - [ ] Testbench that covers edge cases
- Demo
  - [ ] Demo the floating point converter using the testbench
- Submission
  - [ ] Submit a cleaned and zipped ISE project file
  - [ ] Submit a paper copy of the report
  - [ ] Submit an electronic copy of the report