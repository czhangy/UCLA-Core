# Introduction to Verilog and Xilinx ISE

## Goal

**Learn about the Verilog HDL and Xilinx ISE development environments by implementing and simulating a combinational multiplexer, 4-bit counter, and clock divider.**

## Requirements

- Combinational Multiplexer
  - Open the code found in the provided `src/combinational_gates` folder in Verilog
  - Simulate the `combinational_gates_muxed.v` code in the Xilinx ISE
  - Program the Nexys 3 FGPA using the `combinational_gates_muxed.v` and `combinational_gates_muxed.ucf` files
  - Experiment and understand the way the switches interact with the LED
- 4-Bit Counter
  - Implement a 4-bit counter using 4 separate registers in Verilog
  - Write a testbench `old_counter_TB.v` file to simulate the 4-bit counter
  - Simulate the `old_counter.v` code in the Xilinx ISE
  - Repeat the process with a 4-bit counter that uses a single register
- Clock Divider
  - Implement a clock divider, which takes the Nexys 3's 100 MHz clock and converts it to a 1Hz clock in Verilog
  - Write a testbench `clock_divider_TB.v` file to simulate the clock divider
  - Simulate the `clock_divider.v` code in the Xilinx ISE
  - Write a `clock_divider.ucf` file to program the FGPA
  - Program the Nexys 3 FGPA using the `clock_divider.v` and `clock_divider.ucf` files



## Deliverables

- Coding
  - [x] Program the FGPA using `combinational_gates_muxed.v` and `combinational_gates_muxed.ucf`
  - [x] Implement the old 4-bit counter using `old_counter.v` and `old_counter_TB.v`
  - [x] Implement the new 4-bit counter using `counter.v` and `counter_TB.v`
  - [x] Implement the clock divider using `clock_divider.v` and `clock_divider_TB.v`
  - [x] Program the FGPA using `clock_divider.v` and `clock_divider.ucf`
- Submission
  - [x] Simulate and demo the combinational gates multiplexer
  - [x] Simulate the old counter
  - [x] Simulate the new counter
  - [x] Simulate and demo the clock divider

