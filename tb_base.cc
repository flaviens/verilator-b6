// Copyright 2023 Flavien Solt, ETH Zurich.
// Licensed under the General Public License, Version 3.0, see LICENSE for details.
// SPDX-License-Identifier: GPL-3.0-only

#include "Vtop.h"
#include "verilated.h"
#include "ticks.h"

#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <fstream>
#include <cassert>

#if VM_TRACE
#if VM_TRACE_FST
#include <verilated_fst_c.h>
#else
#include <verilated_vcd_c.h>
#endif // VM_TRACE_FST
#endif // VM_TRACE

// This is a generated header
#include "interface_sizes.h"

typedef Vtop Module;

#define PATH_TO_METADATA "tmp/metadata.log"

size_t curr_id_in_random_inputs_from_file = 0;
std::vector<uint32_t> random_inputs_from_file;

#if VM_TRACE
const int kTraceLevel = 6;
#if VM_TRACE_FST
  VerilatedFstC *trace_;
#else
  VerilatedVcdC *trace_;
#endif // VM_TRACE_FST
#endif // VM_TRACE

void read_random_inputs_from_file(int simlen) {
  // Make sure we call this function only once
  assert(random_inputs_from_file.size() == 0);

  std::ifstream in_file(PATH_TO_RANDOM_INPUTS_FILE);
  int expected_num_ints = FULL_RANDOM ? simlen * IN_DATA_WIDTH / 32 : simlen;
  uint64_t next_random_input = 0;
  while (in_file >> next_random_input && random_inputs_from_file.size() < expected_num_ints) {
      random_inputs_from_file.push_back(next_random_input);
  }
  assert(random_inputs_from_file.size() == expected_num_ints);
}

void randomize_inputs(Module *my_module) {
#if FULL_RANDOM == 1
  for (int i = 0; i < IN_DATA_WIDTH / 32; i++) {
    my_module->in_data[i] = random_inputs_from_file[curr_id_in_random_inputs_from_file++];
  }
#else
  int random_input = random_inputs_from_file[curr_id_in_random_inputs_from_file++];
  for (int i = 0; i < IN_DATA_WIDTH / 32; i++)
    my_module->in_data[i] = random_input + i;
#endif
}

/**
 * Runs the testbench.
 *
 * @param tb a pointer to a testbench instance
 * @param simlen the number of cycles to run
 */
std::pair<long, uint64_t> run_test(Module *my_module, int simlen, const std::string trace_filename) {
  
  srand(time(NULL)); // set random seed to current time
  uint64_t cumulated_output = 0;
  auto start = std::chrono::steady_clock::now();

#if VM_TRACE
#if VM_TRACE_FST
    trace_ = new VerilatedFstC;
#else
    trace_ = new VerilatedVcdC;
#endif // VM_TRACE_FST
    my_module->trace(trace_, kTraceLevel);
    trace_->open(trace_filename.c_str());
    size_t tick_count_ = 0;
    trace_->dump(tick_count_++);
#endif // VM_TRACE

  for (int tick_id = 0; tick_id < simlen; tick_id++) {
    randomize_inputs(my_module);
    my_module->eval();
#if VM_TRACE
      trace_->dump(tick_count_++);
#endif // VM_TRACE

    for (int i = 0; i < OUT_DATA_WIDTH / 32; i++) {
      cumulated_output += my_module->out_data[i];
    }

    // std::cout << "signal000_" << std::hex << my_module->signal000_ << std::endl;
    // std::cout << "signal001_" << std::hex << my_module->signal001_ << std::endl;
    // std::cout << "signal002_" << std::hex << my_module->signal002_ << std::endl;
    // std::cout << "signal003_" << std::hex << my_module->signal003_ << std::endl;
    // std::cout << "signal004_" << std::hex << my_module->signal004_ << std::endl;
    // std::cout << "signal005_" << std::hex << my_module->signal005_ << std::endl;
    // std::cout << "signal006_" << std::hex << my_module->signal006_ << std::endl;
    // std::cout << "signal007_" << std::hex << my_module->signal007_ << std::endl;
    // std::cout << "signal008_" << std::hex << my_module->signal008_ << std::endl;
    // std::cout << "signal009_" << std::hex << my_module->signal009_ << std::endl;
    // std::cout << "signal010_" << std::hex << my_module->signal010_ << std::endl;
    // std::cout << "signal011_" << std::hex << my_module->signal011_ << std::endl;
    // std::cout << "signal012_" << std::hex << my_module->signal012_ << std::endl;
    // std::cout << "signal013_" << std::hex << my_module->signal013_ << std::endl;
    // std::cout << "signal014_" << std::hex << my_module->signal014_ << std::endl;
    // std::cout << "signal015_" << std::hex << my_module->signal015_ << std::endl;
    // std::cout << "signal016_" << std::hex << my_module->signal016_ << std::endl;
    // std::cout << "signal017_" << std::hex << my_module->signal017_ << std::endl;
    // std::cout << "signal018_" << std::hex << my_module->signal018_ << std::endl;
    // std::cout << "signal019_" << std::hex << my_module->signal019_ << std::endl;
    // std::cout << "signal020_" << std::hex << my_module->signal020_ << std::endl;
    // std::cout << "signal021_" << std::hex << my_module->signal021_ << std::endl;
    // std::cout << "signal022_" << std::hex << my_module->signal022_ << std::endl;
    // std::cout << "signal023_" << std::hex << my_module->signal023_ << std::endl;
    // std::cout << "signal024_" << std::hex << my_module->signal024_ << std::endl;
    // std::cout << "signal025_" << std::hex << my_module->signal025_ << std::endl;
    // std::cout << "signal026_" << std::hex << my_module->signal026_ << std::endl;
    // std::cout << "signal027_" << std::hex << my_module->signal027_ << std::endl;
    // std::cout << "signal028_" << std::hex << my_module->signal028_ << std::endl;
    // std::cout << "signal029_" << std::hex << my_module->signal029_ << std::endl;
    // std::cout << "signal030_" << std::hex << my_module->signal030_ << std::endl;
    // std::cout << "signal031_" << std::hex << my_module->signal031_ << std::endl;
    // std::cout << "signal032_" << std::hex << my_module->signal032_ << std::endl;
    // std::cout << "signal033_" << std::hex << my_module->signal033_ << std::endl;
    // std::cout << "signal034_" << std::hex << my_module->signal034_ << std::endl;
    // std::cout << "signal035_" << std::hex << my_module->signal035_ << std::endl;
    // std::cout << "signal036_" << std::hex << my_module->signal036_ << std::endl;
    // std::cout << "signal037_" << std::hex << my_module->signal037_ << std::endl;
    // std::cout << "signal038_" << std::hex << my_module->signal038_ << std::endl;
    // std::cout << "signal039_" << std::hex << my_module->signal039_ << std::endl;
    // std::cout << "signal040_" << std::hex << my_module->signal040_ << std::endl;
    // std::cout << "signal041_" << std::hex << my_module->signal041_ << std::endl;
    // std::cout << "signal042_" << std::hex << my_module->signal042_ << std::endl;
    // std::cout << "signal043_" << std::hex << my_module->signal043_ << std::endl;
    // std::cout << "signal044_" << std::hex << my_module->signal044_ << std::endl;
    // std::cout << "signal045_" << std::hex << my_module->signal045_ << std::endl;
    // std::cout << "signal046_" << std::hex << my_module->signal046_ << std::endl;
    // std::cout << "signal047_" << std::hex << my_module->signal047_ << std::endl;
    // std::cout << "signal048_" << std::hex << my_module->signal048_ << std::endl;
    // std::cout << "signal049_" << std::hex << my_module->signal049_ << std::endl;
    // std::cout << "signal050_" << std::hex << my_module->signal050_ << std::endl;
    // std::cout << "signal051_" << std::hex << my_module->signal051_ << std::endl;
    // std::cout << "signal052_" << std::hex << my_module->signal052_ << std::endl;
    // std::cout << "signal053_" << std::hex << my_module->signal053_ << std::endl;
    // std::cout << "signal054_" << std::hex << my_module->signal054_ << std::endl;
    // std::cout << "signal055_" << std::hex << my_module->signal055_ << std::endl;
    // std::cout << "signal056_" << std::hex << my_module->signal056_ << std::endl;
    // std::cout << "signal057_" << std::hex << my_module->signal057_ << std::endl;
    // std::cout << "signal058_" << std::hex << my_module->signal058_ << std::endl;
    // std::cout << "signal059_" << std::hex << my_module->signal059_ << std::endl;
    // std::cout << "signal060_" << std::hex << my_module->signal060_ << std::endl;
    // std::cout << "signal061_" << std::hex << my_module->signal061_ << std::endl;
    // std::cout << "signal062_" << std::hex << my_module->signal062_ << std::endl;
    // std::cout << "signal063_" << std::hex << my_module->signal063_ << std::endl;
    // std::cout << "signal064_" << std::hex << my_module->signal064_ << std::endl;
    // std::cout << "signal065_" << std::hex << my_module->signal065_ << std::endl;
    // std::cout << "signal066_" << std::hex << my_module->signal066_ << std::endl;
    // std::cout << "signal067_" << std::hex << my_module->signal067_ << std::endl;
    // std::cout << "signal068_" << std::hex << my_module->signal068_ << std::endl;
    // std::cout << "signal069_" << std::hex << my_module->signal069_ << std::endl;
    // std::cout << "signal070_" << std::hex << my_module->signal070_ << std::endl;
    // std::cout << "signal071_" << std::hex << my_module->signal071_ << std::endl;
    // std::cout << "signal111_" << std::hex << my_module->signal111_ << std::endl;
    // std::cout << "signal124_" << std::hex << my_module->signal124_ << std::endl;
    // std::cout << "signal129_" << std::hex << my_module->signal129_ << std::endl;
    // std::cout << "signal115_" << std::hex << my_module->signal115_ << std::endl;
    // std::cout << "signal116_" << std::hex << my_module->signal116_ << std::endl;
    // std::cout << "signal109_" << std::hex << my_module->signal109_ << std::endl;
    // std::cout << "signal075_" << std::hex << my_module->signal075_ << std::endl;
    // std::cout << "signal076_" << std::hex << my_module->signal076_ << std::endl;
    // std::cout << "signal077_" << std::hex << my_module->signal077_ << std::endl;
    // std::cout << "signal122_" << std::hex << my_module->signal122_ << std::endl;
    // std::cout << "signal123_" << std::hex << my_module->signal123_ << std::endl;
    // std::cout << "signal091_" << std::hex << my_module->signal091_ << std::endl;
    // std::cout << "signal112_" << std::hex << my_module->signal112_ << std::endl;
    // std::cout << "signal132_" << std::hex << my_module->signal132_ << std::endl;
    // std::cout << "signal146_" << std::hex << my_module->signal146_ << std::endl;
    // std::cout << "signal166_" << std::hex << my_module->signal166_ << std::endl;
    // std::cout << "signal176_" << std::hex << my_module->signal176_ << std::endl;
    // std::cout << "signal113_" << std::hex << my_module->signal113_ << std::endl;
    // std::cout << "signal114_" << std::hex << my_module->signal114_ << std::endl;
    // std::cout << "signal121_" << std::hex << my_module->signal121_ << std::endl;
    // std::cout << "signal095_" << std::hex << my_module->signal095_ << std::endl;
    // std::cout << "signal096_" << std::hex << my_module->signal096_ << std::endl;
    // std::cout << "signal097_" << std::hex << my_module->signal097_ << std::endl;
    // std::cout << "signal080_" << std::hex << my_module->signal080_ << std::endl;
    // std::cout << "signal081_" << std::hex << my_module->signal081_ << std::endl;
    // std::cout << "signal082_" << std::hex << my_module->signal082_ << std::endl;
    // std::cout << "signal088_" << std::hex << my_module->signal088_ << std::endl;
    // std::cout << "signal145_" << std::hex << my_module->signal145_ << std::endl;
    // std::cout << "signal089_" << std::hex << my_module->signal089_ << std::endl;
    // std::cout << "signal090_" << std::hex << my_module->signal090_ << std::endl;

    // for (int i = 0; i < 72/32  + 1; i++)
    //   std::cout << "signal083_ " << i << " " << std::hex << my_module->signal083_[i] << std::endl;
    // for (int i = 0; i < 72/32  + 1; i++)
    //   std::cout << "signal084_ " << i << " " << std::hex << my_module->signal084_[i] << std::endl;
    // for (int i = 0; i < 77/32  + 1; i++)
    //   std::cout << "signal139_ " << i << " " << std::hex << my_module->signal139_[i] << std::endl;
    // for (int i = 0; i < 78/32  + 1; i++)
    //   std::cout << "signal156_ " << i << " " << std::hex << my_module->signal156_[i] << std::endl;
    // for (int i = 0; i < 81/32  + 1; i++)
    //   std::cout << "signal098_ " << i << " " << std::hex << my_module->signal098_[i] << std::endl;
    // for (int i = 0; i < 81/32  + 1; i++)
    //   std::cout << "signal099_ " << i << " " << std::hex << my_module->signal099_[i] << std::endl;
    // for (int i = 0; i < 82/32  + 1; i++)
    //   std::cout << "signal171_ " << i << " " << std::hex << my_module->signal171_[i] << std::endl;
    // for (int i = 0; i < 83/32  + 1; i++)
    //   std::cout << "signal148_ " << i << " " << std::hex << my_module->signal148_[i] << std::endl;
    // for (int i = 0; i < 86/32  + 1; i++)
    //   std::cout << "signal173_ " << i << " " << std::hex << my_module->signal173_[i] << std::endl;
    // for (int i = 0; i < 88/32  + 1; i++)
    //   std::cout << "signal110_ " << i << " " << std::hex << my_module->signal110_[i] << std::endl;
    // for (int i = 0; i < 109/32 + 1; i++)
    //   std::cout << "signal125_ " << i << " " << std::hex << my_module->signal125_[i] << std::endl;
    // for (int i = 0; i < 109/32 + 1; i++)
    //   std::cout << "signal126_ " << i << " " << std::hex << my_module->signal126_[i] << std::endl;
    // for (int i = 0; i < 124/32 + 1; i++)
    //   std::cout << "signal159_ " << i << " " << std::hex << my_module->signal159_[i] << std::endl;
    // for (int i = 0; i < 130/32 + 1; i++)
    //   std::cout << "signal137_ " << i << " " << std::hex << my_module->signal137_[i] << std::endl;
    // for (int i = 0; i < 142/32 + 1; i++)
    //   std::cout << "signal158_ " << i << " " << std::hex << my_module->signal158_[i] << std::endl;
    // for (int i = 0; i < 144/32 + 1; i++)
    //   std::cout << "signal138_ " << i << " " << std::hex << my_module->signal138_[i] << std::endl;
    // for (int i = 0; i < 144/32 + 1; i++)
    //   std::cout << "signal182_ " << i << " " << std::hex << my_module->signal182_[i] << std::endl;
    // for (int i = 0; i < 146/32 + 1; i++)
    //   std::cout << "signal180_ " << i << " " << std::hex << my_module->signal180_[i] << std::endl;
    // for (int i = 0; i < 152/32 + 1; i++)
    //   std::cout << "signal174_ " << i << " " << std::hex << my_module->signal174_[i] << std::endl;
    // for (int i = 0; i < 157/32 + 1; i++)
    //   std::cout << "signal181_ " << i << " " << std::hex << my_module->signal181_[i] << std::endl;
    // for (int i = 0; i < 171/32 + 1; i++)
    //   std::cout << "signal168_ " << i << " " << std::hex << my_module->signal168_[i] << std::endl;
    // for (int i = 0; i < 174/32 + 1; i++)
    //   std::cout << "signal107_ " << i << " " << std::hex << my_module->signal107_[i] << std::endl;
    // for (int i = 0; i < 174/32 + 1; i++)
    //   std::cout << "signal108_ " << i << " " << std::hex << my_module->signal108_[i] << std::endl;
    // for (int i = 0; i < 176/32 + 1; i++)
    //   std::cout << "signal133_ " << i << " " << std::hex << my_module->signal133_[i] << std::endl;
    // for (int i = 0; i < 180/32 + 1; i++)
    //   std::cout << "signal154_ " << i << " " << std::hex << my_module->signal154_[i] << std::endl;
    // for (int i = 0; i < 187/32 + 1; i++)
    //   std::cout << "signal150_ " << i << " " << std::hex << my_module->signal150_[i] << std::endl;
    // for (int i = 0; i < 193/32 + 1; i++)
    //   std::cout << "signal134_ " << i << " " << std::hex << my_module->signal134_[i] << std::endl;
    // for (int i = 0; i < 200/32 + 1; i++)
    //   std::cout << "signal100_ " << i << " " << std::hex << my_module->signal100_[i] << std::endl;
    // for (int i = 0; i < 200/32 + 1; i++)
    //   std::cout << "signal101_ " << i << " " << std::hex << my_module->signal101_[i] << std::endl;
    // for (int i = 0; i < 200/32 + 1; i++)
    //   std::cout << "signal102_ " << i << " " << std::hex << my_module->signal102_[i] << std::endl;
    // for (int i = 0; i < 201/32 + 1; i++)
    //   std::cout << "signal169_ " << i << " " << std::hex << my_module->signal169_[i] << std::endl;
    // for (int i = 0; i < 205/32 + 1; i++)
    //   std::cout << "signal117_ " << i << " " << std::hex << my_module->signal117_[i] << std::endl;
    // for (int i = 0; i < 205/32 + 1; i++)
    //   std::cout << "signal118_ " << i << " " << std::hex << my_module->signal118_[i] << std::endl;
    // for (int i = 0; i < 206/32 + 1; i++)
    //   std::cout << "signal183_ " << i << " " << std::hex << my_module->signal183_[i] << std::endl;
    // for (int i = 0; i < 214/32 + 1; i++)
    //   std::cout << "signal179_ " << i << " " << std::hex << my_module->signal179_[i] << std::endl;
    // for (int i = 0; i < 218/32 + 1; i++)
    //   std::cout << "signal184_ " << i << " " << std::hex << my_module->signal184_[i] << std::endl;
    // for (int i = 0; i < 219/32 + 1; i++)
    //   std::cout << "signal105_ " << i << " " << std::hex << my_module->signal105_[i] << std::endl;
    // for (int i = 0; i < 219/32 + 1; i++)
    //   std::cout << "signal106_ " << i << " " << std::hex << my_module->signal106_[i] << std::endl;
    // for (int i = 0; i < 223/32 + 1; i++)
    //   std::cout << "signal119_ " << i << " " << std::hex << my_module->signal119_[i] << std::endl;
    // for (int i = 0; i < 223/32 + 1; i++)
    //   std::cout << "signal120_ " << i << " " << std::hex << my_module->signal120_[i] << std::endl;
    // for (int i = 0; i < 223/32 + 1; i++)
    //   std::cout << "signal135_ " << i << " " << std::hex << my_module->signal135_[i] << std::endl;
    // for (int i = 0; i < 223/32 + 1; i++)
    //   std::cout << "signal136_ " << i << " " << std::hex << my_module->signal136_[i] << std::endl;
    // for (int i = 0; i < 224/32 + 1; i++)
    //   std::cout << "signal162_ " << i << " " << std::hex << my_module->signal162_[i] << std::endl;
    // for (int i = 0; i < 224/32 + 1; i++)
    //   std::cout << "signal163_ " << i << " " << std::hex << my_module->signal163_[i] << std::endl;
    // for (int i = 0; i < 225/32 + 1; i++)
    //   std::cout << "signal144_ " << i << " " << std::hex << my_module->signal144_[i] << std::endl;
    // for (int i = 0; i < 229/32 + 1; i++)
    //   std::cout << "signal130_ " << i << " " << std::hex << my_module->signal130_[i] << std::endl;
    // for (int i = 0; i < 229/32 + 1; i++)
    //   std::cout << "signal131_ " << i << " " << std::hex << my_module->signal131_[i] << std::endl;
    // for (int i = 0; i < 235/32 + 1; i++)
    //   std::cout << "signal178_ " << i << " " << std::hex << my_module->signal178_[i] << std::endl;
    // for (int i = 0; i < 238/32 + 1; i++)
    //   std::cout << "signal078_ " << i << " " << std::hex << my_module->signal078_[i] << std::endl;
    // for (int i = 0; i < 238/32 + 1; i++)
    //   std::cout << "signal079_ " << i << " " << std::hex << my_module->signal079_[i] << std::endl;
    // for (int i = 0; i < 240/32 + 1; i++)
    //   std::cout << "signal157_ " << i << " " << std::hex << my_module->signal157_[i] << std::endl;
    // for (int i = 0; i < 247/32 + 1; i++)
    //   std::cout << "signal172_ " << i << " " << std::hex << my_module->signal172_[i] << std::endl;
    // for (int i = 0; i < 247/32 + 1; i++)
    //   std::cout << "signal175_ " << i << " " << std::hex << my_module->signal175_[i] << std::endl;
    // for (int i = 0; i < 259/32 + 1; i++)
    //   std::cout << "signal092_ " << i << " " << std::hex << my_module->signal092_[i] << std::endl;
    // for (int i = 0; i < 259/32 + 1; i++)
    //   std::cout << "signal093_ " << i << " " << std::hex << my_module->signal093_[i] << std::endl;
    // for (int i = 0; i < 259/32 + 1; i++)
    //   std::cout << "signal094_ " << i << " " << std::hex << my_module->signal094_[i] << std::endl;
    // for (int i = 0; i < 259/32 + 1; i++)
    //   std::cout << "signal140_ " << i << " " << std::hex << my_module->signal140_[i] << std::endl;
    // for (int i = 0; i < 262/32 + 1; i++)
    //   std::cout << "signal164_ " << i << " " << std::hex << my_module->signal164_[i] << std::endl;
    // for (int i = 0; i < 262/32 + 1; i++)
    //   std::cout << "signal165_ " << i << " " << std::hex << my_module->signal165_[i] << std::endl;
    // for (int i = 0; i < 271/32 + 1; i++)
    //   std::cout << "signal149_ " << i << " " << std::hex << my_module->signal149_[i] << std::endl;
    // for (int i = 0; i < 271/32 + 1; i++)
    //   std::cout << "signal155_ " << i << " " << std::hex << my_module->signal155_[i] << std::endl;
    // for (int i = 0; i < 273/32 + 1; i++)
    //   std::cout << "signal160_ " << i << " " << std::hex << my_module->signal160_[i] << std::endl;
    // for (int i = 0; i < 273/32 + 1; i++)
    //   std::cout << "signal161_ " << i << " " << std::hex << my_module->signal161_[i] << std::endl;
    // for (int i = 0; i < 274/32 + 1; i++)
    //   std::cout << "signal167_ " << i << " " << std::hex << my_module->signal167_[i] << std::endl;
    // for (int i = 0; i < 275/32 + 1; i++)
    //   std::cout << "signal143_ " << i << " " << std::hex << my_module->signal143_[i] << std::endl;
    // for (int i = 0; i < 281/32 + 1; i++)
    //   std::cout << "signal072_ " << i << " " << std::hex << my_module->signal072_[i] << std::endl;
    // for (int i = 0; i < 281/32 + 1; i++)
    //   std::cout << "signal073_ " << i << " " << std::hex << my_module->signal073_[i] << std::endl;
    // for (int i = 0; i < 281/32 + 1; i++)
    //   std::cout << "signal074_ " << i << " " << std::hex << my_module->signal074_[i] << std::endl;
    // for (int i = 0; i < 282/32 + 1; i++)
    //   std::cout << "signal151_ " << i << " " << std::hex << my_module->signal151_[i] << std::endl;
    // for (int i = 0; i < 282/32 + 1; i++)
    //   std::cout << "signal152_ " << i << " " << std::hex << my_module->signal152_[i] << std::endl;
    // for (int i = 0; i < 282/32 + 1; i++)
    //   std::cout << "signal153_ " << i << " " << std::hex << my_module->signal153_[i] << std::endl;
    // for (int i = 0; i < 289/32 + 1; i++)
    //   std::cout << "signal147_ " << i << " " << std::hex << my_module->signal147_[i] << std::endl;
    // for (int i = 0; i < 289/32 + 1; i++)
    //   std::cout << "signal170_ " << i << " " << std::hex << my_module->signal170_[i] << std::endl;
    // for (int i = 0; i < 291/32 + 1; i++)
    //   std::cout << "signal185_ " << i << " " << std::hex << my_module->signal185_[i] << std::endl;
    // // for (int i = 0; i < 291/32 + 1; i++)
    // //   std::cout << "signal186_ " << i << " " << std::hex << my_module->signal186_[i] << std::endl;
    // for (int i = 0; i < 295/32 + 1; i++)
    //   std::cout << "signal177_ " << i << " " << std::hex << my_module->signal177_[i] << std::endl;
    // for (int i = 0; i < 296/32 + 1; i++)
    //   std::cout << "signal103_ " << i << " " << std::hex << my_module->signal103_[i] << std::endl;
    // for (int i = 0; i < 296/32 + 1; i++)
    //   std::cout << "signal104_ " << i << " " << std::hex << my_module->signal104_[i] << std::endl;
    // for (int i = 0; i < 298/32 + 1; i++)
    //   std::cout << "signal127_ " << i << " " << std::hex << my_module->signal127_[i] << std::endl;
    // for (int i = 0; i < 298/32 + 1; i++)
    //   std::cout << "signal128_ " << i << " " << std::hex << my_module->signal128_[i] << std::endl;
    // for (int i = 0; i < 299/32 + 1; i++)
    //   std::cout << "signal085_ " << i << " " << std::hex << my_module->signal085_[i] << std::endl;
    // for (int i = 0; i < 299/32 + 1; i++)
    //   std::cout << "signal086_ " << i << " " << std::hex << my_module->signal086_[i] << std::endl;
    // for (int i = 0; i < 299/32 + 1; i++)
    //   std::cout << "signal087_ " << i << " " << std::hex << my_module->signal087_[i] << std::endl;
    // for (int i = 0; i < 299/32 + 1; i++)
    //   std::cout << "signal141_ " << i << " " << std::hex << my_module->signal141_[i] << std::endl;
    // for (int i = 0; i < 299/32 + 1; i++)
    //   std::cout << "signal142_ " << i << " " << std::hex << my_module->signal142_[i] << std::endl;
  }

#if VM_TRACE
      trace_->flush();
#endif // VM_TRACE

  auto stop = std::chrono::steady_clock::now();
  long ret = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
  return std::make_pair(ret, cumulated_output);
}

int main(int argc, char **argv, char **env) {

  Verilated::commandArgs(argc, argv);
  Verilated::traceEverOn(VM_TRACE);

  ////////
  // Get the env vars early to avoid Verilator segfaults.
  ////////

  std::cout << "Starting getting env variables." << std::endl;
  int simlen = get_sim_length_cycles(0);
  read_random_inputs_from_file(simlen);
  std::string vcd_filepath = cl_get_tracefile();

  ////////
  // Instantiate the module.
  ////////

  Module *my_module = new Module;

  ////////
  // Run the experiment.
  ////////

  std::pair<long, uint64_t> duration_and_output = run_test(my_module, simlen, vcd_filepath);
  long duration = duration_and_output.first;
  uint64_t cumulated_output = duration_and_output.second;

  std::cout << "Testbench complete!" << std::endl;
  std::cout << "Output signature: " << std::dec << cumulated_output << "." << std::endl;
  std::cout << "Elapsed time: " << std::dec << duration << "." << std::endl;

  delete my_module;
  exit(0);
}
