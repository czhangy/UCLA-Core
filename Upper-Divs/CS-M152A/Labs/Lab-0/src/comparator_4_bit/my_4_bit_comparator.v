/*
 * Module: Parametrized comparator code
 * 
 * Filename: my_4_bit_comparator.v
 * Version: 1.0
 *
 * Author: Cejo Konuparamban Lonappan
 *
 * Description: A parametrized Verilod description for implementing an unsigned
 * comparator. The width has been chosen to for a 4-bit comparator. 
 */

`define WIDTH 4 

module my_4_bit_comparator (InA, InB, A_Great_B_OutY, A_Less_B_OutY, A_Equal_B_OutY);

input [`WIDTH-1:0] InA, InB;
output reg A_Great_B_OutY, A_Less_B_OutY, A_Equal_B_OutY;

always @(InA or InB)
	{A_Great_B_OutY, A_Less_B_OutY, A_Equal_B_OutY} = {(InA > InB), (InA < InB), (InA == InB)};

endmodule
