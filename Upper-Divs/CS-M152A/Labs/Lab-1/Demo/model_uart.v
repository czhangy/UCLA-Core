`timescale 1ns / 1ps

module model_uart(/*AUTOARG*/
   // Outputs
   TX,
   // Inputs
   RX
   );

   output TX;
   input  RX;

   parameter baud    = 115200;
   parameter bittime = 1000000000/baud;
   parameter name    = "UART0";
   
   reg [7:0] rxData;
   event     evBit;
   event     evByte;
   event     evTxBit;
   event     evTxByte;
   reg       TX;
   
   reg [1:0] counter;
   reg [23:0] bytes;

   initial
     begin
        TX = 1'b1;
		counter = 2'b0;
     end
   
   always @ (negedge RX)
     begin
		bytes[23:0] <= {bytes[15:0], rxData[7:0]};
        rxData[7:0] = 8'h0;
        #(0.5*bittime);
		
        repeat (8)
          begin
             #bittime ->evBit;
             //rxData[7:0] = {rxData[6:0],RX};
             rxData[7:0] = {RX,rxData[7:1]};
          end
        ->evByte;
		if (counter == 3) begin
			$display ("%d %s Received (%s%s%s%s)", $stime, name, bytes[23:16], bytes[15:8], bytes[7:0], rxData);
			bytes <= 24'b0;
		end
		
		counter <= counter + 1;
	 end

   task tskRxData;
      output [7:0] data;
      begin
         @(evByte);
         data = rxData;
      end
   endtask // for
      
   task tskTxData;
      input [7:0] data;
      reg [9:0]   tmp;
      integer     i;
      begin
         tmp = {1'b1, data[7:0], 1'b0};
         for (i=0;i<10;i=i+1)
           begin
              TX = tmp[i];
              #bittime;
              ->evTxBit;
           end
         ->evTxByte;
      end
   endtask // tskTxData
   
endmodule // model_uart
