# Sequencer

## Goal

**Use an FPGA to demo and study a sequencer and complete exercises based on the demo.**

## Requirements

- Translate and demo the following commands in the UART console

  - ```
    PUSH R0 0x4
    PUSH R0 0x0
    PUSH R1 0x3
    MULT R0 R1 R2
    ADD R2 R0 R3
    SEND R0
    SEND R1
    SEND R2
    SEND R3
    ```

- Complete workshop 1

  - Read, understand, and answer questions about the code's clock divider
  - Read, understand, and answer questions about the code's button debouncing
  - Read, understand, and answer questions about the code's register file

- Complete workshop 2

  - Clean up the UART simulation output
  - Modify the testbench to make use of `seq.code` to load instructions
  - Design instructions that can print out the Fibonacci series on the UART

## Deliverables

- Demo
  - [ ] Translate and demo the UART console of the following commands
  - [ ] Complete and demo the contents of Workshop 2

- Submission
  - [ ] Read the implementation code and finish Workshop 1
  - [ ] Include results in the report

