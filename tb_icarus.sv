`define DO_TRACE

`define SIMLEN 10

module testbench;

  bit [31:0] in_data_words [288 / 32];
  bit [31:0] out_data_words [160 / 32];

  int fd;
  int in_buf;

  bit [63:0] cumulated_output;

  // Instantiate the design under test (DUT)
  bit [288-1:0]  in_data;
  bit [160-1:0] out_data;

  top dut(in_data, out_data);

  always_comb begin
    for (int in_word_id = 0; in_word_id < 288 / 32; in_word_id++) begin : reset_generator
      in_data[32*in_word_id +: 32] = in_data_words[in_word_id];
    end
    for (int out_word_id = 0; out_word_id < 160 / 32; out_word_id++) begin : reset_generator
      out_data_words[out_word_id] = out_data[32*out_word_id +: 32];
    end
  end

  // Stimulus generation
  initial begin
    cumulated_output = 0;

    fd = $fopen("inputs.txt", "r");
    if (fd == 0) begin
      $display("Error: could not open file `random_inputs.txt`.");
      $finish;
    end

`ifdef DO_TRACE
    $dumpfile("icarus_dump.vcd");
    $dumpvars(0,dut);
`endif

    for (int step_id = 0; step_id < `SIMLEN; step_id++) begin
      $fscanf(fd, "%d", in_buf);
      in_data_words[0] = in_buf;
      for (int word_id = 1; word_id < 288 / 32; word_id++) begin
        in_data_words[word_id] = in_data_words[0] + word_id;
      end
      #1;

      // Cumulate the outputs
      for (int word_id = 0; word_id < 160 / 32; word_id++) begin
        cumulated_output += out_data_words[word_id];
      end
    end

    $display("Output signature: %d.", cumulated_output);
  end

endmodule
