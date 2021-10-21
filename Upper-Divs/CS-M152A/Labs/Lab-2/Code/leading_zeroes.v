`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:54:28 10/20/2021 
// Design Name: 
// Module Name:    leading_zeroes 
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
module leading_zeroes(D, E, F, fifth_bit);

    // Inputs
    input [11:0] D;

    // Outputs
    output reg [2:0] E;
    output reg [3:0] F;
    output reg fifth_bit;

    // Loop variables
    integer i;
    integer j;
    reg flag;
	 
    always @* begin
        // Init variables
        i = 11;
        flag = 0;
        E = 8;
        while (i > 3) begin		
			// Set flag when a 1 is found => don't update E anymore
			if (D[i] == 1)
				flag = 1;
			// If flag is unset, update E
			if (flag == 0)
				// Get exponent using table + # of leading zeroes
				E = E - 1;
			// Iterate
			i = i - 1;
		end
		// Get significand by indexing
		i = E + 3;
		j = 3;
        // Build significand
		while (j >= 0) begin
			F[j] = D[i];
            // Iterate
			i = i - 1;
			j = j - 1;
		end
        // Extract fifth bit
		if (i >= 0)
			fifth_bit = D[i];
        // Exponent is 0, don't round
		else
			fifth_bit = 0;
    end
	 
endmodule