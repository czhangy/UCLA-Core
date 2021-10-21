`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:54:39 10/20/2021 
// Design Name: 
// Module Name:    handle_round 
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
module handle_round(E_in, F_in, fifth_bit, E_out, F_out);

    // Inputs
    input [2:0] E_in;
    input [3:0] F_in;
    input fifth_bit;

    // Outputs
    output reg [2:0] E_out;
    output reg [3:0] F_out;
	 
	always @* begin
		// Set defaults
		E_out = E_in;
		F_out = F_in;
        // Round up
        if (fifth_bit == 1) begin
            // Significand doesn't overflow
            if (F_in != 4'b1111) begin
                E_out = E_in;
                F_out = F_in + 1;
            // Significand overflows, exponent doesn't
            end else if (E_in != 3'b111) begin
                E_out = E_in + 1;
                F_out = 4'b1000;
            end
        end
    end

endmodule
