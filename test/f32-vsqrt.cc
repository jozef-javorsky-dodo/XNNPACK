// clang-format off
// Copyright 2019 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.
//
// Auto-generated file. Do not edit!
//   Microkernel: f32-vsqrt
//   Generator: tools/generate-vunary-test.py


#include <array>
#include <cmath>
#include <cstdint>
#include <cstddef>
#include <limits>

#include <gtest/gtest.h>
#include "include/xnnpack.h"
#include "src/xnnpack/common.h"
#include "src/xnnpack/isa-checks.h"
#include "src/xnnpack/microparams-init.h"
#include "src/xnnpack/microparams.h"
#include "src/xnnpack/vunary.h"
#include "test/next_prime.h"
#include "test/unary-ops.h"
#include "test/vunary-microkernel-tester.h"

using TestInfo = SquareRoot;

#define XNN_QUANTIZED(T) xnnpack::quantized<T>
#define XNN_UKERNEL(arch_flags, ukernel, batch_tile, vector_tile, datatype, params_type, init_params)       \
  TEST(ukernel, batch_eq) { TestBatchEq<TestInfo, datatype, datatype>(arch_flags, batch_tile, ukernel, init_params); }  \
  TEST(ukernel, batch_div) { TestBatchDiv<TestInfo, datatype, datatype>(arch_flags, batch_tile, ukernel, init_params); }\
  TEST(ukernel, batch_lt) { TestBatchLT<TestInfo, datatype, datatype>(arch_flags, batch_tile, ukernel, init_params); }  \
  TEST(ukernel, batch_gt) { TestBatchGT<TestInfo, datatype, datatype>(arch_flags, batch_tile, ukernel, init_params); }  \
  TEST(ukernel, inplace) { TestInPlace<TestInfo, datatype, datatype>(arch_flags, batch_tile, ukernel, init_params); }   \
TEST(ukernel, special_values) {                                                                                         \
  TEST_REQUIRES_ARCH_FLAGS(arch_flags);                                                                                 \
  VUnaryMicrokernelTester().Test<TestInfo, datatype, datatype>(ukernel, init_params,                                    \
    /*inputs=*/{0.0f, -0.0f, 1.0f, -1.0f},                                                                              \
    /*outputs=*/{0.0f, -0.0f, 1.0f, NAN},                                                                               \
    /*tolerance_ulp=*/1);                                                                                               \
}
#include "src/f32-vsqrt/f32-vsqrt.h"
#undef XNN_UKERNEL
#undef XNN_QUANTIZED
