# COM SCI M152A - Fall '21 - Sarrafzadeh

[TOC]

## Lecture 1: FGPA and Verilog Basics

- An FGPA is an integrated circuit designed to be configured by the consumer after manufacturing

- Field-Programmable Gate Arrays

  - Logic blocks
    - To implement combinational and sequential logic
  - Interconnect
    - Wires to connect inputs and outputs to logic blocks
  - I/O blocks
    - Special logic blocks at periphery of device for external connections

- FGPA Design Fundamentals

  - Step 1 - Design
    - Know what it is that you want to implement
    - Module-level diagrams and interactions between modules
    - Understand how your FGPA will interact with the physical world
    - Plan **everything** before writing a single line of code
  - Step 2 - Implementation
    - Translate your plan to source code
    - Express each module in HDL source code
    - Connect the modules in hierarchal order like building LEGO blocks
      - Should end up with a single top-level file
    - Use any text editor
  - Step 3 - Simulation
    - Simulation is the single most important debugging tool you will ever use in FGPA design
    - You will have access to real-time debugging tools (chipScope), but it's easier to find/fix bugs in simulation
  - Step 4 - Logic Synthesis
    - Once the bugs are out a logic synthesis tool analyzes the design and generates a netlist with common cells available to the FPGA target
    - The netlist should be functionally equivalent to the original source code
    - We will use ISE's XST to synthesize the project
  - Step 5 - Technology Mapping
    - The synthesized netlist is mapped to the device-specific libraries
    - The result is another netlist that's closer to the final target device
    - On ISE, this is performed by NGDBUILD
  - Step 6 - Cell Placement
    - The cells instantiated by final netlist are placed in the FGPA layout, i.e. each cell is assigned a location on the physical device
    - Can be a time-consuming process depending on the size of the design and complexity of timing and physical constraints
    - On ISE, this process is done by the program MAP
  - Step 7 - Route
    - Often referred to as "Place-and-Route" in combination with cell placement
    - In this process, the placement tool determines how to connect ("route") the cells in the device to match the netlist
    - Can be a time-consuming process depending on the size of the design and complexity of timing and physical constraints
    - Done by program PAR on ISE
  - Step 8 - Bitstream Generation
    - A placed and routed design can be used to produce a programming file to program the FPGA
    - The programming file is called a "bitstream"
      - It contains everything there is about how to configure the cells and connecting them
    - Done by program BITGEN on ISE
    - Now, you have a "compiled" FPGA design

- Tools of Trade

  - Text editor of choice
  - Simulator
    - ISE Webpack provides ISIM
    - Alternatively, use free Modelsim PE
  - Synthesis
    - ISE Webpack provides XST
    - Alternatively, use Synplify Pro (evaluation version)
  - Map, Place-and-Route
    - ISE Webpack

- Verilog

  - Overview

    - Resemblance to C: case sensitive, same style comments, operators, etc.
    - Two standards: Verilog-1995, Verilog-2001, both supported by ISE
    - Easy to write, and easy to make mistakes

  - Behavioral vs. Synthesizable code

    - Historically Verilog has always served two functions:
      - Describe your digital logic design in a high-level way instead of using schematics (synthesizable code)
      - Model elements that interact with your design (behavioral models/testbenches)
    - You should **always** have a clear conscience of whether you are writing behavioral or synthesizable code
    - Better yet, know what your synthesizable code translates to in **physical hardware**

  - Two types of variables:

    - Wire: hot store (combinational logic)
      - Models basic wire that holds transient values
      - Only wires can be used on the LHS of continuous assign statement
      - Input/output port signals default to wire
    - Register: store previous values (sequential logic)
      - Anything that stores a value
      - Can appear in both combinational and sequential circuits
      - Only regs can be used on the LHS of non-continuous assign statement

  - Bitwise operations:

    - `~a` - complement
    - `a & b` - and
    - `a | b` - or
    - `a ^ b` - exclusive or
    - `a ~^ b` - exclusive not

  - Logical operations:

    - `a && b` - and
    - `a || b` - or

  - Blocking vs. Non-blocking

    - `a <= 4` - "parallel" during runtime (non-blocking)
      - Still determinant behavior
      - Helps to think about what the values are before and after a given time
      - Assignments deferred until all right hand sides has been evaluated, closer to actual hardware register behavior
      - Good for sequential logic
    - `a = 4` - "sequential" during runtime (blocking)
      - Assignment immediate, happens first
      - Good for combinational logic

  - ```verilog
    module top(a, b, ci, s, co);
    	input a, b, ci;
      output s, co;
    	reg g, p, co;
    	assign s = a ^ b ^ ci;
    	always @* begin
    		g = a & b;
    		p = a | b;
        co = g | (p & ci);
    	end
    endmodule
    ```

  - Assignment

    - ```verilog
      wire a;
      reg b;
      ```

      - Can only store `0`s or `1`s

    - ```verilog
      reg[4:0] reg = 16;
      reg[4:0] reg = 'b10000;
      reg[4:0] reg = 'h10;
      ```

      - Must use a radix to store other values

  - Module Instantiation

    - ```verilog
      module half_adder(a, b, x, y);
      	input a, b;
      	output x, y;
      	assign x = a & b;
      	assign y = a ^ b;
      endmodule
      
      module full_adder(a, b, ci, s, co);
        input a, b, ci;
        output s, co;
        wire g, p, pc;
        half_adder h1(.a(a), .b(b), .x(g), .y(p));
        half_adder h2(.a(p), .b(ci), .x(pc), .y(s));
        assign co = pc | g;
      endmodule
      ```

  - Clock

    - ```verilog
      always #10
        clk = ~clk
      end
      ```



## Lecture 2: 

- 

