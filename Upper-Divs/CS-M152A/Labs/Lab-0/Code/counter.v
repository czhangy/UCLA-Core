`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:04:02 09/28/2021 
// Design Name: 
// Module Name:    counter 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module counter(clk, rst, a);

// Input and output declarations
input clk;
input rst;
output [3:0] a;

reg [3:0] a;

// Generate outputs for the gates
always @ (posedge clk or posedge rst)
begin
	if (rst)
		a <= 4'b0000;
	else
		a <= a + 1;
end

endmodule
