verilator --cc --debug --trace --exe --Wno-UNOPTFLAT --Wno-WIDTHTRUNC --Wno-CMPCONST -Wno-WIDTHEXPAND --build tb_base.cc top.sv -CFLAGS '-g' --Mdir obj_dir --trace --build-jobs 100
TRACEFILE=trace.vcd SIMLEN=10 obj_dir/Vtop

rm -rf icarus_obj_dir && mkdir -p icarus_obj_dir && iverilog -g2012 -o icarus_obj_dir/Vtop top.sv tb_icarus.sv
vvp -M . -mdpi_wallclock icarus_obj_dir/Vtop +vcd
