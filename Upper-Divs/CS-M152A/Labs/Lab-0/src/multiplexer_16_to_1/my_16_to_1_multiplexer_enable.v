/*
 * Module: A 16:1 multiplexer with enable input
 * 
 * Filename: my_16_to_1_multiplexer_enable.v
 * Version: 1.0
 *
 * Author: Cejo Konuparamban Lonappan
 *
 * Description: RTL for implementing a 16 to 1 multiplexer with an enable
 * input. 
 */

module my_16_to_1_multiplexer_enable (MuxIn, SelectIn, EnableIn, OutY);

input [15:0] MuxIn; 
input [3:0] SelectIn; 
input EnableIn; 
output OutY;
reg OutY;

always @(MuxIn or SelectIn or EnableIn)
	if (!EnableIn)
		OutY = 1'b0;
	else
		OutY = MuxIn[SelectIn];
endmodule
