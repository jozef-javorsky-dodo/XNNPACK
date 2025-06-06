// clang-format off
// Auto-generated file. Do not edit!
//   Template: src/qs8-f32-vcvt/rvv.c.in
//   Generator: tools/xngen
//
// Copyright 2024 Imagination Technologies, inc.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <riscv_vector.h>

#include "src/xnnpack/common.h"
#include "src/xnnpack/intrinsics-polyfill.h"
#include "src/xnnpack/vcvt.h"


void xnn_qu8_f32_vcvt_ukernel__rvv_u1v(
    size_t batch,
    const uint8_t* input,
    float* output,
    const struct xnn_qu8_f32_cvt_params* restrict params)
{
  assert(batch != 0);
  assert(batch % sizeof(int8_t) == 0);
  assert(input != NULL);
  assert(output != NULL);

  batch >>= XNN_LOG2_SIZEOF_INT8_T;

  const float scale = params->scalar.scale;
  const int32_t minus_zero_point = -params->scalar.zero_point;

  for (; batch > 0; ) {
    const int32_t n = __riscv_vsetvl_e8m1(batch); batch -= n;

    vuint8m1_t x_u8v = __riscv_vle8_v_u8m1(input, n); input += n;

    vint32m4_t wx_i32v = __riscv_vreinterpret_v_u32m4_i32m4(__riscv_vzext_vf4_u32m4(x_u8v, n));
    wx_i32v = __riscv_vadd_vx_i32m4(wx_i32v, minus_zero_point, n);
    vfloat32m4_t y_f32v = __riscv_vfcvt_f_x_v_f32m4(wx_i32v, n);
    y_f32v = __riscv_vfmul_vf_f32m4(y_f32v, scale, n);

    __riscv_vse32_v_f32m4(output, y_f32v, n); output += n;
  }
}
