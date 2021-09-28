/*
 * Module: Testbench for 4-bit comparator logic
 * 
 * Filename: my_4_bit_comparator_TB.v
 * Version: 1.0
 *
 * Author: Cejo Konuparamban Lonappan
 *
 * Description: The testbench code for the functional verification of a 4-bit
 * comparator. 
 */

`timescale 1ns / 1ps

module my_4_bit_comparator_tb; // No inputs for a testbench!

reg [3:0] InA_T, InB_T; // Inputs in the module to be tested will be port mapped to register variables
wire A_Great_B_OutY_T, A_Less_B_OutY_T, A_Equal_B_OutY_T; // Outputs in the module to be tested will be port mapped to wire variables

// Instantiation of the design module to be verified by the testbench
// Use named portmapping to map inputs to regsiter variables and outputs to
// wires
my_4_bit_comparator UUT (.InA(InA_T), 
			 .InB(InB_T), 
			 .A_Great_B_OutY(A_Great_B_OutY_T), 
			 .A_Less_B_OutY(A_Less_B_OutY_T), 
			 .A_Equal_B_OutY(A_Equal_B_OutY_T));

// Used for saving Value Change Dump (.vcd) file that records the waveforms of
// the simulation. Not needed while using Xilinx ISIM simulator. 
initial
begin
        $dumpfile("four_bit_comparator.vcd");
        $dumpvars(2, my_4_bit_comparator_tb.UUT);
end

// IMPORTANT: Initialize all inputs. Otherwise the default value of register
// will be don't care (x). 
initial
begin
	InA_T = 4'h0;
	InB_T = 4'h0;
	// Produce console output to verify the design
	$monitor("Input A: %d; Input B:%d; A_Great_B = %b; A_Less_B = %b; A_Equal_B = %b", InA_T, InB_T, A_Great_B_OutY_T, A_Less_B_OutY_T, A_Equal_B_OutY_T);
end

// Uses forever loop to generate all the test cases after the initialization. 
always
	forever #5 InA_T[0] = ~InA_T[0];

always
        forever #10 InA_T[1] = ~InA_T[1];

always
        forever #20 InA_T[2] = ~InA_T[2];

always
        forever #40 InA_T[3] = ~InA_T[3];

always
        forever #80 InB_T[0] = ~InB_T[0];

always
        forever #160 InB_T[1] = ~InB_T[1];

always
        forever #320 InB_T[2] = ~InB_T[2];

always
        forever #640 InB_T[3] = ~InB_T[3];

// Code to terminate simulation after all the test cases have been covered. 
initial
	#1280 $finish; // After 1280 timeunits, terminate simulation. 

endmodule
