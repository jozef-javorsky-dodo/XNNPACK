// clang-format off
// Auto-generated file. Do not edit!
//   Template: src/f32-vlrelu/rvv.c.in
//   Generator: tools/xngen
//
// Copyright 2024 Imagination Technologies, Inc.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <riscv_vector.h>
#include "src/xnnpack/common.h"
#include "src/xnnpack/vunary.h"

void xnn_f32_vlrelu_ukernel__rvv_u1v(
    size_t batch,
    const float* input,
    float* output,
    const struct xnn_f32_lrelu_params* restrict params)
{
  assert(batch != 0);
  assert(batch % sizeof(float) == 0);
  assert(input != NULL);
  assert(output != NULL);

  const float slope = params->scalar.slope;
  batch >>= XNN_LOG2_SIZEOF_FLOAT;

  do {
    size_t n = __riscv_vsetvl_e32m1(batch); batch -= n;
    vfloat32m1_t in_f32v = __riscv_vle32_v_f32m1(input, n); input += n;
    vbool32_t mask_f32v = __riscv_vmflt_vf_f32m1_b32(in_f32v, 0.0f, n);
    vfloat32m1_t out_f32v = __riscv_vfmul_vf_f32m1_mu(mask_f32v, in_f32v, in_f32v, slope, n);
    __riscv_vse32_v_f32m1(output, out_f32v, n); output += n;
  } while (batch != 0);
}
