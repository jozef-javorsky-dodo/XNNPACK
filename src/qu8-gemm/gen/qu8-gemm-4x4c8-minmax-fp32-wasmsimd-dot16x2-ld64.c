// clang-format off
// Auto-generated file. Do not edit!
//   Template: src/qs8-gemm/MRx4c8-wasmsimd-dot16x2.c.in
//   Generator: tools/xngen
//
// Copyright 2021 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <wasm_simd128.h>

#include "src/xnnpack/gemm.h"
#include "src/xnnpack/math.h"


void xnn_qu8_gemm_minmax_fp32_ukernel_4x4c8__wasmsimd_dot16x2_ld64(
    size_t mr,
    size_t nc,
    size_t kc,
    const uint8_t* restrict a,
    size_t a_stride,
    const void* restrict w,
    uint8_t* restrict c,
    size_t cm_stride,
    size_t cn_stride,
    const union xnn_qu8_conv_minmax_params* restrict params) XNN_OOB_READS
{
  assert(mr != 0);
  assert(mr <= 4);
  assert(nc != 0);
  assert(kc != 0);
  assert(kc % sizeof(uint8_t) == 0);
  assert(a != NULL);
  assert(w != NULL);
  assert(c != NULL);

  kc = round_up_po2(kc, 8 * sizeof(uint8_t));
  const uint8_t* a0 = a;
  uint8_t* c0 = c;
  const uint8_t* a1 = (const uint8_t*) ((uintptr_t) a0 + a_stride);
  uint8_t* c1 = (uint8_t*) ((uintptr_t) c0 + cm_stride);
  if XNN_UNPREDICTABLE(mr < 2) {
    a1 = a0;
    c1 = c0;
  }
  const uint8_t* a2 = (const uint8_t*) ((uintptr_t) a1 + a_stride);
  uint8_t* c2 = (uint8_t*) ((uintptr_t) c1 + cm_stride);
  if XNN_UNPREDICTABLE(mr <= 2) {
    a2 = a1;
    c2 = c1;
  }
  const uint8_t* a3 = (const uint8_t*) ((uintptr_t) a2 + a_stride);
  uint8_t* c3 = (uint8_t*) ((uintptr_t) c2 + cm_stride);
  if XNN_UNPREDICTABLE(mr != 4) {
    a3 = a2;
    c3 = c2;
  }

  const v128_t vscale = wasm_v128_load32_splat(&params->fp32_scalar.scale);
  XNN_FORCE_REALIZATION(vscale);

  const v128_t vmagic_bias = wasm_f32x4_const_splat(12582912.0f);
  const int32_t output_min_less_zero_point = (int32_t) params->fp32_scalar.output_min - (int32_t) params->fp32_scalar.output_zero_point;
  const v128_t vmagic_min = wasm_i32x4_splat((int32_t) float_as_uint32(12582912.0f + output_min_less_zero_point));
  const v128_t vmagic_bias_less_output_zero_point = wasm_i32x4_splat(INT32_C(0x4B400000) - (int32_t) params->fp32_scalar.output_zero_point);
  const v128_t voutput_max = wasm_i8x16_splat(params->fp32_scalar.output_max);
  XNN_FORCE_REALIZATION(vmagic_bias);
  XNN_FORCE_REALIZATION(vmagic_min);
  XNN_FORCE_REALIZATION(vmagic_bias_less_output_zero_point);
  XNN_FORCE_REALIZATION(voutput_max);

  const v128_t vb_zero_point = wasm_i16x8_splat(params->fp32_scalar.kernel_zero_point);
  XNN_FORCE_REALIZATION(vb_zero_point);
  do {
    v128_t vacc0x0 = wasm_v128_load32_zero(w);
    v128_t vacc0x1 = wasm_v128_load32_zero((const int32_t*) w + 1);
    v128_t vacc0x2 = wasm_v128_load32_zero((const int32_t*) w + 2);
    v128_t vacc0x3 = wasm_v128_load32_zero((const int32_t*) w + 3);
    v128_t vacc1x0 = vacc0x0;
    v128_t vacc1x1 = vacc0x1;
    v128_t vacc1x2 = vacc0x2;
    v128_t vacc1x3 = vacc0x3;
    v128_t vacc2x0 = vacc0x0;
    v128_t vacc2x1 = vacc0x1;
    v128_t vacc2x2 = vacc0x2;
    v128_t vacc2x3 = vacc0x3;
    v128_t vacc3x0 = vacc0x0;
    v128_t vacc3x1 = vacc0x1;
    v128_t vacc3x2 = vacc0x2;
    v128_t vacc3x3 = vacc0x3;
    w = (const int32_t*) w + 4;

    size_t k = kc;

    while (k >= 8 * sizeof(uint8_t)) {
      const v128_t vxa0 = wasm_u16x8_load8x8(a0);
      a0 += 8;
      const v128_t vxa1 = wasm_u16x8_load8x8(a1);
      a1 += 8;
      const v128_t vxa2 = wasm_u16x8_load8x8(a2);
      a2 += 8;
      const v128_t vxa3 = wasm_u16x8_load8x8(a3);
      a3 += 8;

      const v128_t vxb0 = wasm_i16x8_sub(wasm_u16x8_load8x8(w), vb_zero_point);

      vacc0x0 = wasm_i32x4_add(vacc0x0, wasm_i32x4_dot_i16x8(vxa0, vxb0));
      vacc1x0 = wasm_i32x4_add(vacc1x0, wasm_i32x4_dot_i16x8(vxa1, vxb0));
      vacc2x0 = wasm_i32x4_add(vacc2x0, wasm_i32x4_dot_i16x8(vxa2, vxb0));
      vacc3x0 = wasm_i32x4_add(vacc3x0, wasm_i32x4_dot_i16x8(vxa3, vxb0));
      const v128_t vxb1 = wasm_i16x8_sub(wasm_u16x8_load8x8((const int8_t*) w + 8), vb_zero_point);

      vacc0x1 = wasm_i32x4_add(vacc0x1, wasm_i32x4_dot_i16x8(vxa0, vxb1));
      vacc1x1 = wasm_i32x4_add(vacc1x1, wasm_i32x4_dot_i16x8(vxa1, vxb1));
      vacc2x1 = wasm_i32x4_add(vacc2x1, wasm_i32x4_dot_i16x8(vxa2, vxb1));
      vacc3x1 = wasm_i32x4_add(vacc3x1, wasm_i32x4_dot_i16x8(vxa3, vxb1));
      const v128_t vxb2 = wasm_i16x8_sub(wasm_u16x8_load8x8((const int8_t*) w + 16), vb_zero_point);

      vacc0x2 = wasm_i32x4_add(vacc0x2, wasm_i32x4_dot_i16x8(vxa0, vxb2));
      vacc1x2 = wasm_i32x4_add(vacc1x2, wasm_i32x4_dot_i16x8(vxa1, vxb2));
      vacc2x2 = wasm_i32x4_add(vacc2x2, wasm_i32x4_dot_i16x8(vxa2, vxb2));
      vacc3x2 = wasm_i32x4_add(vacc3x2, wasm_i32x4_dot_i16x8(vxa3, vxb2));
      const v128_t vxb3 = wasm_i16x8_sub(wasm_u16x8_load8x8((const int8_t*) w + 24), vb_zero_point);

      vacc0x3 = wasm_i32x4_add(vacc0x3, wasm_i32x4_dot_i16x8(vxa0, vxb3));
      vacc1x3 = wasm_i32x4_add(vacc1x3, wasm_i32x4_dot_i16x8(vxa1, vxb3));
      vacc2x3 = wasm_i32x4_add(vacc2x3, wasm_i32x4_dot_i16x8(vxa2, vxb3));
      vacc3x3 = wasm_i32x4_add(vacc3x3, wasm_i32x4_dot_i16x8(vxa3, vxb3));

      w = (const uint8_t*) w + 32;
      k -= 8 * sizeof(uint8_t);
    };

    const v128_t vacc0x02 = wasm_i32x4_add(wasm_v32x4_shuffle(vacc0x0, vacc0x2, 0, 4, 1, 5), wasm_v32x4_shuffle(vacc0x0, vacc0x2, 2, 6, 3, 7));
    const v128_t vacc0x13 = wasm_i32x4_add(wasm_v32x4_shuffle(vacc0x1, vacc0x3, 0, 4, 1, 5), wasm_v32x4_shuffle(vacc0x1, vacc0x3, 2, 6, 3, 7));
    const v128_t vacc1x02 = wasm_i32x4_add(wasm_v32x4_shuffle(vacc1x0, vacc1x2, 0, 4, 1, 5), wasm_v32x4_shuffle(vacc1x0, vacc1x2, 2, 6, 3, 7));
    const v128_t vacc1x13 = wasm_i32x4_add(wasm_v32x4_shuffle(vacc1x1, vacc1x3, 0, 4, 1, 5), wasm_v32x4_shuffle(vacc1x1, vacc1x3, 2, 6, 3, 7));
    const v128_t vacc2x02 = wasm_i32x4_add(wasm_v32x4_shuffle(vacc2x0, vacc2x2, 0, 4, 1, 5), wasm_v32x4_shuffle(vacc2x0, vacc2x2, 2, 6, 3, 7));
    const v128_t vacc2x13 = wasm_i32x4_add(wasm_v32x4_shuffle(vacc2x1, vacc2x3, 0, 4, 1, 5), wasm_v32x4_shuffle(vacc2x1, vacc2x3, 2, 6, 3, 7));
    const v128_t vacc3x02 = wasm_i32x4_add(wasm_v32x4_shuffle(vacc3x0, vacc3x2, 0, 4, 1, 5), wasm_v32x4_shuffle(vacc3x0, vacc3x2, 2, 6, 3, 7));
    const v128_t vacc3x13 = wasm_i32x4_add(wasm_v32x4_shuffle(vacc3x1, vacc3x3, 0, 4, 1, 5), wasm_v32x4_shuffle(vacc3x1, vacc3x3, 2, 6, 3, 7));

    v128_t vacc0x0123 = wasm_i32x4_add(wasm_v32x4_shuffle(vacc0x02, vacc0x13, 0, 4, 1, 5), wasm_v32x4_shuffle(vacc0x02, vacc0x13, 2, 6, 3, 7));
    v128_t vacc1x0123 = wasm_i32x4_add(wasm_v32x4_shuffle(vacc1x02, vacc1x13, 0, 4, 1, 5), wasm_v32x4_shuffle(vacc1x02, vacc1x13, 2, 6, 3, 7));
    v128_t vacc2x0123 = wasm_i32x4_add(wasm_v32x4_shuffle(vacc2x02, vacc2x13, 0, 4, 1, 5), wasm_v32x4_shuffle(vacc2x02, vacc2x13, 2, 6, 3, 7));
    v128_t vacc3x0123 = wasm_i32x4_add(wasm_v32x4_shuffle(vacc3x02, vacc3x13, 0, 4, 1, 5), wasm_v32x4_shuffle(vacc3x02, vacc3x13, 2, 6, 3, 7));

    vacc0x0123 = wasm_f32x4_convert_i32x4(vacc0x0123);
    vacc1x0123 = wasm_f32x4_convert_i32x4(vacc1x0123);
    vacc2x0123 = wasm_f32x4_convert_i32x4(vacc2x0123);
    vacc3x0123 = wasm_f32x4_convert_i32x4(vacc3x0123);

    vacc0x0123 = wasm_f32x4_mul(vacc0x0123, vscale);
    vacc1x0123 = wasm_f32x4_mul(vacc1x0123, vscale);
    vacc2x0123 = wasm_f32x4_mul(vacc2x0123, vscale);
    vacc3x0123 = wasm_f32x4_mul(vacc3x0123, vscale);

    vacc0x0123 = wasm_f32x4_add(vacc0x0123, vmagic_bias);
    vacc1x0123 = wasm_f32x4_add(vacc1x0123, vmagic_bias);
    vacc2x0123 = wasm_f32x4_add(vacc2x0123, vmagic_bias);
    vacc3x0123 = wasm_f32x4_add(vacc3x0123, vmagic_bias);

    vacc0x0123 = wasm_i32x4_max(vacc0x0123, vmagic_min);
    vacc1x0123 = wasm_i32x4_max(vacc1x0123, vmagic_min);
    vacc2x0123 = wasm_i32x4_max(vacc2x0123, vmagic_min);
    vacc3x0123 = wasm_i32x4_max(vacc3x0123, vmagic_min);

    vacc0x0123 = wasm_i32x4_sub(vacc0x0123, vmagic_bias_less_output_zero_point);
    vacc1x0123 = wasm_i32x4_sub(vacc1x0123, vmagic_bias_less_output_zero_point);
    vacc2x0123 = wasm_i32x4_sub(vacc2x0123, vmagic_bias_less_output_zero_point);
    vacc3x0123 = wasm_i32x4_sub(vacc3x0123, vmagic_bias_less_output_zero_point);

    v128_t vacc01x0123 = wasm_i16x8_narrow_i32x4(vacc0x0123, vacc1x0123);
    v128_t vacc23x0123 = wasm_i16x8_narrow_i32x4(vacc2x0123, vacc3x0123);

    v128_t vacc = wasm_u8x16_narrow_i16x8(vacc01x0123, vacc23x0123);

    vacc = wasm_u8x16_min(vacc, voutput_max);

    if XNN_LIKELY(nc >= 4) {
      wasm_v128_store32_lane(c0, vacc, 0);
      wasm_v128_store32_lane(c1, vacc, 1);
      wasm_v128_store32_lane(c2, vacc, 2);
      wasm_v128_store32_lane(c3, vacc, 3);

      c0 = (uint8_t*) ((uintptr_t) c0 + cn_stride);
      c1 = (uint8_t*) ((uintptr_t) c1 + cn_stride);
      c2 = (uint8_t*) ((uintptr_t) c2 + cn_stride);
      c3 = (uint8_t*) ((uintptr_t) c3 + cn_stride);

      a0 = (const uint8_t*) ((uintptr_t) a0 - kc);
      a1 = (const uint8_t*) ((uintptr_t) a1 - kc);
      a2 = (const uint8_t*) ((uintptr_t) a2 - kc);
      a3 = (const uint8_t*) ((uintptr_t) a3 - kc);

      nc -= 4;
    } else {
      if (nc & 2) {
        wasm_v128_store16_lane(c0, vacc, 0);
        c0 += 2;
        wasm_v128_store16_lane(c1, vacc, 2);
        c1 += 2;
        wasm_v128_store16_lane(c2, vacc, 4);
        c2 += 2;
        wasm_v128_store16_lane(c3, vacc, 6);
        c3 += 2;

        vacc = wasm_u32x4_shr(vacc, 16);
      }
      if (nc & 1) {
        wasm_v128_store8_lane(c0, vacc, 0);
        wasm_v128_store8_lane(c1, vacc, 4);
        wasm_v128_store8_lane(c2, vacc, 8);
        wasm_v128_store8_lane(c3, vacc, 12);
      }

      nc = 0;
    }
    } while (nc != 0);
}
