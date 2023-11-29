# Verilator double-problem of corrupted VCD and optimization issue

This repository shows two problems with Verilator:
- Corrupted VCD trace
- Optimization issue that causes wrong runtime values

Verilator version tested: `Verilator 5.019 devel rev v5.018-58-g7167d4bdc`

## Seing the result depending on the optimization

How to run (this may take some minutes, depending on your machine):
```
python3 test_optimizations.py
```

You will get the following result:

```
For -fno-acyc-simp: Output signature: 244.
For -fno-assemble: Output signature: 244.
For -fno-case: Output signature: 244.
For -fno-combine: Output signature: 244.
For -fno-const: Output signature: 244.
For -fno-const-bit-op-tree: Output signature: 1403003.
For -fno-dedup: Output signature: 244.
For -fno-dfg: Output signature: 244.
For -fno-dfg-peephole: Output signature: 244.
For -fno-dfg-peephole: Output signature: 244.
For -fno-dfg-pre-inline: Output signature: 244.
For -fno-dfg-post-inline: Output signature: 244.
For -fno-expand: Output signature: 1403003.
For -fno-gate: Output signature: 1403003.
For -fno-inline: Output signature: 244.
For -fno-life: Output signature: 244.
For -fno-life-post: Output signature: 244.
For -fno-localize: Output signature: 244.
For -fno-merge-cond: Output signature: 244.
For -fno-merge-cond-motion: Output signature: 244.
For -fno-merge-const-pool: Output signature: 244.
For -fno-reloop: Output signature: 244.
For -fno-reorder: Output signature: 244.
For -fno-split: Output signature: 244.
For -fno-subst: Output signature: 1403003.
For -fno-subst-const: Output signature: 1403003.
For -fno-table: Output signature: 244.
For -fno-acyc-simp -fno-assemble -fno-case -fno-combine -fno-const -fno-const-bit-op-tree -fno-dedup -fno-dfg -fno-dfg-peephole -fno-dfg-peephole -fno-dfg-pre-inline -fno-dfg-post-inline -fno-expand -fno-gate -fno-inline -fno-life -fno-life-post -fno-localize -fno-merge-cond -fno-merge-cond-motion -fno-merge-const-pool -fno-reloop -fno-reorder -fno-split -fno-subst -fno-subst-const -fno-table: Output signature: 1403003.
```

## Seing the VCD corruption


```
verilator --cc --debug --trace --exe --Wno-UNOPTFLAT --Wno-WIDTHTRUNC --Wno-CMPCONST -Wno-WIDTHEXPAND --build tb_base.cc top.sv -CFLAGS '-g' --Mdir obj_dir --trace --build-jobs 100
TRACEFILE=trace.vcd SIMLEN=10 obj_dir/Vtop
python3 test_trace.py
```

This will raise:
```
UnicodeDecodeError: 'utf-8' codec can't decode byte 0xf5 in position 60748: invalid start byte
```

Additionally, gtkwave will only show very few time steps, less than the 10 expected steps.
