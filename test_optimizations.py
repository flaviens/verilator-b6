import subprocess
import multiprocessing as mp

optimization_exclusions = [
    '-fno-acyc-simp',
    '-fno-assemble',
    '-fno-case',
    '-fno-combine',
    '-fno-const',
    '-fno-const-bit-op-tree',
    '-fno-dedup',
    '-fno-dfg',
    '-fno-dfg-peephole',
    '-fno-dfg-peephole',
    '-fno-dfg-pre-inline',
    '-fno-dfg-post-inline',
    '-fno-expand',
    '-fno-gate',
    '-fno-inline',
    '-fno-life',
    '-fno-life-post',
    '-fno-localize',
    '-fno-merge-cond',
    '-fno-merge-cond-motion',
    '-fno-merge-const-pool',
    '-fno-reloop',
    '-fno-reorder',
    '-fno-split',
    '-fno-subst',
    '-fno-subst-const',
    '-fno-table',
]

# We also add a compound of all no-optimizations
optimization_exclusions.append(' '.join(optimization_exclusions))

# Now, we try with all the no-optimizations
def worker(no_optim_flag_id: str):
    print(f"Running {no_optim_flag_id}")
    obj_dir_name = f"obj_dir_{no_optim_flag_id}"
    no_optim_flag = optimization_exclusions[no_optim_flag_id]
    verilate_cmd_str = f"verilator --cc --debug {no_optim_flag} --exe --Wno-UNOPTFLAT --Wno-WIDTHTRUNC --Wno-CMPCONST -Wno-WIDTHEXPAND --build tb_base.cc top.sv -CFLAGS '-g' --Mdir {obj_dir_name} --trace --build-jobs 16"
    try:
        subprocess.run(verilate_cmd_str, shell=True, check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    except:
        print(f"Failed verilation with {no_optim_flag}")
        return None

    run_cmd_str = f"TRACEFILE=trace.vcd SIMLEN=10 {obj_dir_name}/Vtop"
    try:
        subprocess_result = subprocess.run(run_cmd_str, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    except:
        print(f"Failed run with {no_optim_flag}")
        return None
    ret_lines = subprocess_result.stdout.decode('utf-8').split('\n')
    print(f"Finished {no_optim_flag}: {ret_lines}")
    return ret_lines

with mp.Pool(mp.cpu_count()) as pool:
    results = pool.map(worker, range(len(optimization_exclusions)))

for result_id, result in enumerate(results):
    if result is None:
        print(f"Failed to run {optimization_exclusions[result_id]}")
    for line in result:
        if 'Output signature' in line:
            print(f"For {optimization_exclusions[result_id]}: {line}")
            break
