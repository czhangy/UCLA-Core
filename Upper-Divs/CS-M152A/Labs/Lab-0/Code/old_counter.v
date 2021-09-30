`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:17:13 09/28/2021 
// Design Name: 
// Module Name:    old_counter 
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
module old_counter(clk, rst, a0, a1, a2, a3);

// Input and output declarations
input clk, rst;
output a0, a1, a2, a3;
reg a0, a1, a2, a3;

// Generate outputs for the gates
always @ (posedge clk or posedge rst)
begin
	if (rst)
	begin
		a0 <= 1'b0;
		a1 <= 1'b0;
		a2 <= 1'b0;
		a3 <= 1'b0;
	end
	else
	begin
		a0 <= ~a0;
		a1 <= (a0 ^ a1);
		a2 <= ((a0 & a1) ^ a2);
		a3 <= ((a0 & a1 & a2) ^ a3);
	end
		
end

endmodule

/*
a1 <= (a0 ^ a1);
a2 <= ((a0 & a1) ^ a2);
a3 <= ((a0 & a1 & a2) ^ a3);
*/