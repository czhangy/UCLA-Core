/*
 * Module: Testbench for 16:1 multiplexer with enable input
 * 
 * Filename: my_16_to_1_multiplexer_enable_TB.v
 * Version: 1.0
 *
 * Author: Cejo Konuparamban Lonappan
 *
 * Description: The testbench RTL code for verifying the functionality of a 
 * 16 to 1 multiplexer with an enable input. 
 */

`timescale 1ns / 1ps

module my_16_to_1_multiplexer_enable_tb; // No inputs for a testbench!

// Inputs in the module to be tested will be port mapped to register variables
reg [15:0] MuxIn_T;
reg [3:0] SelectIn_T;
reg EnableIn_T;

// Outputs in the module to be tested will be port mapped to wire variables
wire OutY_T;

// If using for loop in testbench code to generate the test cases, declare an
// integer variable
integer i;

// Instantiation of the design module to be verified by the testbench
// Use named portmapping to map inputs to regsiter variables and outputs to
// wires
my_16_to_1_multiplexer_enable UUT (.MuxIn(MuxIn_T),
				   .SelectIn(SelectIn_T),
				   .EnableIn(EnableIn_T),
				   .OutY(OutY_T));

// Used for saving Value Change Dump (.vcd) file that records the waveforms of
// the simulation. Not needed while using Xilinx ISIM simulator.
initial
begin
	$dumpfile("16_to_1_multiplexer.vcd");
	$dumpvars(2, my_16_to_1_multiplexer_enable_tb.UUT);
end

// Uses a for loop to generate all the test cases.
initial 
	for (i = 21'h1FFFFF; i >= 0; i = i - 1)
	begin
		{EnableIn_T, MuxIn_T, SelectIn_T} = i;
		#5 ;
	end

// Code to terminate simulation after all the test cases have been covered.
initial 
	#(2097152*5) $finish; // After 10485760 timeunits, terminate simulation.

endmodule
