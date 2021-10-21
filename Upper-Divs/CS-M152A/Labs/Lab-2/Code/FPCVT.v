`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:44:23 10/20/2021 
// Design Name: 
// Module Name:    FPCVT
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
module FPCVT(D, S, E, F);

	// Inputs
	input [11:0] D;

	// Outputs
	output S;
	output [2:0] E;
	output [3:0] F;

	// Wires
	wire [11:0] signed_mag;
	wire fifth_bit;
	wire [2:0] exp;
	wire [3:0] sig;

	// Convert D from Two's Complement to Signed Magnitude
	to_signed_magnitude m1 (.D(D), .S(S), .signed_mag(signed_mag));

	// Count leading zeroes and extract leading bits
	leading_zeroes m2 (.D(signed_mag), .E(exp), .F(sig), .fifth_bit(fifth_bit));

	// Round
	handle_round m3 (.E_in(exp), .F_in(sig), .fifth_bit(fifth_bit), .E_out(E), .F_out(F));

endmodule