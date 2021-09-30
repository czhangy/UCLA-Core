`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:07:13 09/30/2021 
// Design Name: 
// Module Name:    clock_divider 
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
module clock_divider(clk, rst, led);

// Input and output declarations
input clk;
input rst;
output led;

reg led;
reg [25:0] counter;

// Generate outputs for the led
always @ (posedge clk or posedge rst)
begin
	if (rst)
	begin
		led <= 1'b0;
		counter <= 0;
	end
	else
	begin
		counter <= counter + 1;
		// Count to 50,000,000 lol
		if (counter == 50000000)
		begin
			led <= ~led;
			counter <= 0;
		end
	end
end

endmodule
