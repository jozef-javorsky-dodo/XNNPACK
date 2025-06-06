// clang-format off
// Auto-generated file. Do not edit!
//   Template: src/qs8-gemm/MRx16c4-wasmdot.c.in
//   Generator: tools/xngen
//
// Copyright 2024 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <wasm_simd128.h>

#include "src/xnnpack/gemm.h"
#include "src/xnnpack/math.h"

void xnn_qs8_qc8w_gemm_minmax_fp32_ukernel_3x16c4__wasmusdot(
    size_t mr,
    size_t nc,
    size_t kc,
    const int8_t* restrict a,
    size_t a_stride,
    const void* restrict w,
    int8_t* restrict c,
    size_t cm_stride,
    size_t cn_stride,
    const union xnn_qs8_qc8w_conv_minmax_params* restrict params) XNN_OOB_READS
{
  assert(mr != 0);
  assert(mr <= 3);
  assert(nc != 0);
  assert(kc != 0);
  assert(kc % sizeof(int8_t) == 0);
  assert(a != NULL);
  assert(w != NULL);
  assert(c != NULL);

  kc = round_up_po2(kc, 4 * sizeof(int8_t));
  const int8_t* a0 = a;
  int8_t* c0 = c;
  const int8_t* a1 = (const int8_t*) ((uintptr_t) a0 + a_stride);
  int8_t* c1 = (int8_t*) ((uintptr_t) c0 + cm_stride);
  if XNN_UNPREDICTABLE(mr < 2) {
    a1 = a0;
    c1 = c0;
  }
  const int8_t* a2 = (const int8_t*) ((uintptr_t) a1 + a_stride);
  int8_t* c2 = (int8_t*) ((uintptr_t) c1 + cm_stride);
  if XNN_UNPREDICTABLE(mr <= 2) {
    a2 = a1;
    c2 = c1;
  }


  const v128_t vmagic_bias = wasm_f32x4_const_splat(12582912.0f);
  const int32_t output_min_less_zero_point = (int32_t) params->fp32_scalar.output_min - (int32_t) params->fp32_scalar.output_zero_point;
  const v128_t vmagic_min = wasm_i32x4_splat((int32_t) float_as_uint32(12582912.0f + output_min_less_zero_point));
  const v128_t vmagic_bias_less_output_zero_point = wasm_i32x4_splat(INT32_C(0x4B400000) - (int32_t) params->fp32_scalar.output_zero_point);
  const v128_t voutput_max = wasm_i8x16_splat(params->fp32_scalar.output_max);
  //XNN_FORCE_REALIZATION(vmagic_bias);
  //XNN_FORCE_REALIZATION(vmagic_min);
  //XNN_FORCE_REALIZATION(vmagic_bias_less_output_zero_point);
  //XNN_FORCE_REALIZATION(voutput_max);

  const v128_t vsign_mask = wasm_u8x16_const_splat(UINT8_C(0x80));
  XNN_FORCE_REALIZATION(vsign_mask);

  do {
    v128_t vacc0x0123 = wasm_v128_load(w);
    v128_t vacc0x4567 = wasm_v128_load((const int32_t*) w + 4);
    v128_t vacc0x89AB = wasm_v128_load((const int32_t*) w + 8);
    v128_t vacc0xCDEF = wasm_v128_load((const int32_t*) w + 12);
    v128_t vacc1x0123= vacc0x0123;
    v128_t vacc1x4567= vacc0x4567;
    v128_t vacc1x89AB= vacc0x89AB;
    v128_t vacc1xCDEF= vacc0xCDEF;
    v128_t vacc2x0123= vacc0x0123;
    v128_t vacc2x4567= vacc0x4567;
    v128_t vacc2x89AB= vacc0x89AB;
    v128_t vacc2xCDEF= vacc0xCDEF;
    w = (const int32_t*) w + 16;

    size_t k = kc;

    while (k != 0) {
      v128_t va0x0123 = wasm_v128_load32_splat(a0);
      a0 += 4;
      v128_t va1x0123 = wasm_v128_load32_splat(a1);
      a1 += 4;
      v128_t va2x0123 = wasm_v128_load32_splat(a2);
      a2 += 4;

      va0x0123 = wasm_v128_xor(va0x0123, vsign_mask);
      va1x0123 = wasm_v128_xor(va1x0123, vsign_mask);
      va2x0123 = wasm_v128_xor(va2x0123, vsign_mask);

      const v128_t vb0123 = wasm_v128_load((const int8_t*) w);
      const v128_t vb4567 = wasm_v128_load((const int8_t*) w + 16);
      const v128_t vb89AB = wasm_v128_load((const int8_t*) w + 32);
      const v128_t vbCDEF = wasm_v128_load((const int8_t*) w + 48);

      vacc0x0123 = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(vb0123, va0x0123, vacc0x0123);
      vacc0x4567 = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(vb4567, va0x0123, vacc0x4567);
      vacc0x89AB = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(vb89AB, va0x0123, vacc0x89AB);
      vacc0xCDEF = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(vbCDEF, va0x0123, vacc0xCDEF);
      vacc1x0123 = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(vb0123, va1x0123, vacc1x0123);
      vacc1x4567 = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(vb4567, va1x0123, vacc1x4567);
      vacc1x89AB = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(vb89AB, va1x0123, vacc1x89AB);
      vacc1xCDEF = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(vbCDEF, va1x0123, vacc1xCDEF);
      vacc2x0123 = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(vb0123, va2x0123, vacc2x0123);
      vacc2x4567 = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(vb4567, va2x0123, vacc2x4567);
      vacc2x89AB = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(vb89AB, va2x0123, vacc2x89AB);
      vacc2xCDEF = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(vbCDEF, va2x0123, vacc2xCDEF);

      w = (const int8_t*) w + 64;
      k -= 4 * sizeof(int8_t);
    }

    vacc0x0123 = wasm_f32x4_convert_i32x4(vacc0x0123);
    vacc0x4567 = wasm_f32x4_convert_i32x4(vacc0x4567);
    vacc0x89AB = wasm_f32x4_convert_i32x4(vacc0x89AB);
    vacc0xCDEF = wasm_f32x4_convert_i32x4(vacc0xCDEF);
    vacc1x0123 = wasm_f32x4_convert_i32x4(vacc1x0123);
    vacc1x4567 = wasm_f32x4_convert_i32x4(vacc1x4567);
    vacc1x89AB = wasm_f32x4_convert_i32x4(vacc1x89AB);
    vacc1xCDEF = wasm_f32x4_convert_i32x4(vacc1xCDEF);
    vacc2x0123 = wasm_f32x4_convert_i32x4(vacc2x0123);
    vacc2x4567 = wasm_f32x4_convert_i32x4(vacc2x4567);
    vacc2x89AB = wasm_f32x4_convert_i32x4(vacc2x89AB);
    vacc2xCDEF = wasm_f32x4_convert_i32x4(vacc2xCDEF);

    const v128_t vscale0123 = wasm_v128_load(w);
    w = (const float*) w + 4;
    const v128_t vscale4567 = wasm_v128_load(w);
    w = (const float*) w + 4;
    const v128_t vscale89AB = wasm_v128_load(w);
    w = (const float*) w + 4;
    const v128_t vscaleCDEF = wasm_v128_load(w);
    w = (const float*) w + 4;
    vacc0x0123 = wasm_f32x4_mul(vacc0x0123, vscale0123);
    vacc0x4567 = wasm_f32x4_mul(vacc0x4567, vscale4567);
    vacc0x89AB = wasm_f32x4_mul(vacc0x89AB, vscale89AB);
    vacc0xCDEF = wasm_f32x4_mul(vacc0xCDEF, vscaleCDEF);
    vacc1x0123 = wasm_f32x4_mul(vacc1x0123, vscale0123);
    vacc1x4567 = wasm_f32x4_mul(vacc1x4567, vscale4567);
    vacc1x89AB = wasm_f32x4_mul(vacc1x89AB, vscale89AB);
    vacc1xCDEF = wasm_f32x4_mul(vacc1xCDEF, vscaleCDEF);
    vacc2x0123 = wasm_f32x4_mul(vacc2x0123, vscale0123);
    vacc2x4567 = wasm_f32x4_mul(vacc2x4567, vscale4567);
    vacc2x89AB = wasm_f32x4_mul(vacc2x89AB, vscale89AB);
    vacc2xCDEF = wasm_f32x4_mul(vacc2xCDEF, vscaleCDEF);

    vacc0x0123 = wasm_f32x4_add(vacc0x0123, vmagic_bias);
    vacc0x4567 = wasm_f32x4_add(vacc0x4567, vmagic_bias);
    vacc0x89AB = wasm_f32x4_add(vacc0x89AB, vmagic_bias);
    vacc0xCDEF = wasm_f32x4_add(vacc0xCDEF, vmagic_bias);
    vacc1x0123 = wasm_f32x4_add(vacc1x0123, vmagic_bias);
    vacc1x4567 = wasm_f32x4_add(vacc1x4567, vmagic_bias);
    vacc1x89AB = wasm_f32x4_add(vacc1x89AB, vmagic_bias);
    vacc1xCDEF = wasm_f32x4_add(vacc1xCDEF, vmagic_bias);
    vacc2x0123 = wasm_f32x4_add(vacc2x0123, vmagic_bias);
    vacc2x4567 = wasm_f32x4_add(vacc2x4567, vmagic_bias);
    vacc2x89AB = wasm_f32x4_add(vacc2x89AB, vmagic_bias);
    vacc2xCDEF = wasm_f32x4_add(vacc2xCDEF, vmagic_bias);

    vacc0x0123 = wasm_i32x4_max(vacc0x0123, vmagic_min);
    vacc0x4567 = wasm_i32x4_max(vacc0x4567, vmagic_min);
    vacc0x89AB = wasm_i32x4_max(vacc0x89AB, vmagic_min);
    vacc0xCDEF = wasm_i32x4_max(vacc0xCDEF, vmagic_min);
    vacc1x0123 = wasm_i32x4_max(vacc1x0123, vmagic_min);
    vacc1x4567 = wasm_i32x4_max(vacc1x4567, vmagic_min);
    vacc1x89AB = wasm_i32x4_max(vacc1x89AB, vmagic_min);
    vacc1xCDEF = wasm_i32x4_max(vacc1xCDEF, vmagic_min);
    vacc2x0123 = wasm_i32x4_max(vacc2x0123, vmagic_min);
    vacc2x4567 = wasm_i32x4_max(vacc2x4567, vmagic_min);
    vacc2x89AB = wasm_i32x4_max(vacc2x89AB, vmagic_min);
    vacc2xCDEF = wasm_i32x4_max(vacc2xCDEF, vmagic_min);

    vacc0x0123 = wasm_i32x4_sub(vacc0x0123, vmagic_bias_less_output_zero_point);
    vacc0x4567 = wasm_i32x4_sub(vacc0x4567, vmagic_bias_less_output_zero_point);
    vacc0x89AB = wasm_i32x4_sub(vacc0x89AB, vmagic_bias_less_output_zero_point);
    vacc0xCDEF = wasm_i32x4_sub(vacc0xCDEF, vmagic_bias_less_output_zero_point);
    vacc1x0123 = wasm_i32x4_sub(vacc1x0123, vmagic_bias_less_output_zero_point);
    vacc1x4567 = wasm_i32x4_sub(vacc1x4567, vmagic_bias_less_output_zero_point);
    vacc1x89AB = wasm_i32x4_sub(vacc1x89AB, vmagic_bias_less_output_zero_point);
    vacc1xCDEF = wasm_i32x4_sub(vacc1xCDEF, vmagic_bias_less_output_zero_point);
    vacc2x0123 = wasm_i32x4_sub(vacc2x0123, vmagic_bias_less_output_zero_point);
    vacc2x4567 = wasm_i32x4_sub(vacc2x4567, vmagic_bias_less_output_zero_point);
    vacc2x89AB = wasm_i32x4_sub(vacc2x89AB, vmagic_bias_less_output_zero_point);
    vacc2xCDEF = wasm_i32x4_sub(vacc2xCDEF, vmagic_bias_less_output_zero_point);

    v128_t vacc0x01234567 = wasm_i16x8_narrow_i32x4(vacc0x0123, vacc0x4567);
    v128_t vacc0x89ABCDEF = wasm_i16x8_narrow_i32x4(vacc0x89AB, vacc0xCDEF);
    v128_t vacc1x01234567 = wasm_i16x8_narrow_i32x4(vacc1x0123, vacc1x4567);
    v128_t vacc1x89ABCDEF = wasm_i16x8_narrow_i32x4(vacc1x89AB, vacc1xCDEF);
    v128_t vacc2x01234567 = wasm_i16x8_narrow_i32x4(vacc2x0123, vacc2x4567);
    v128_t vacc2x89ABCDEF = wasm_i16x8_narrow_i32x4(vacc2x89AB, vacc2xCDEF);

    vacc0x01234567 = wasm_i8x16_narrow_i16x8(vacc0x01234567, vacc0x01234567);
    vacc0x89ABCDEF = wasm_i8x16_narrow_i16x8(vacc0x89ABCDEF, vacc0x89ABCDEF);
    vacc1x01234567 = wasm_i8x16_narrow_i16x8(vacc1x01234567, vacc1x01234567);
    vacc1x89ABCDEF = wasm_i8x16_narrow_i16x8(vacc1x89ABCDEF, vacc1x89ABCDEF);
    vacc2x01234567 = wasm_i8x16_narrow_i16x8(vacc2x01234567, vacc2x01234567);
    vacc2x89ABCDEF = wasm_i8x16_narrow_i16x8(vacc2x89ABCDEF, vacc2x89ABCDEF);

    vacc0x01234567 = wasm_i8x16_min(vacc0x01234567, voutput_max);
    vacc0x89ABCDEF = wasm_i8x16_min(vacc0x89ABCDEF, voutput_max);
    vacc1x01234567 = wasm_i8x16_min(vacc1x01234567, voutput_max);
    vacc1x89ABCDEF = wasm_i8x16_min(vacc1x89ABCDEF, voutput_max);
    vacc2x01234567 = wasm_i8x16_min(vacc2x01234567, voutput_max);
    vacc2x89ABCDEF = wasm_i8x16_min(vacc2x89ABCDEF, voutput_max);

    if XNN_LIKELY(nc >= 16) {
      wasm_v128_store64_lane(c0, vacc0x01234567, 0);
      wasm_v128_store64_lane(c0 + 8, vacc0x89ABCDEF, 0);
      wasm_v128_store64_lane(c1, vacc1x01234567, 0);
      wasm_v128_store64_lane(c1 + 8, vacc1x89ABCDEF, 0);
      wasm_v128_store64_lane(c2, vacc2x01234567, 0);
      wasm_v128_store64_lane(c2 + 8, vacc2x89ABCDEF, 0);

      c0 = (int8_t*) ((uintptr_t) c0 + cn_stride);
      c1 = (int8_t*) ((uintptr_t) c1 + cn_stride);
      c2 = (int8_t*) ((uintptr_t) c2 + cn_stride);

      a0 = (const int8_t*) ((uintptr_t) a0 - kc);
      a1 = (const int8_t*) ((uintptr_t) a1 - kc);
      a2 = (const int8_t*) ((uintptr_t) a2 - kc);

      nc -= 16;
    } else {
      if (nc & 8) {
        wasm_v128_store64_lane(c0, vacc0x01234567, 0);
        c0 += 8;
        wasm_v128_store64_lane(c1, vacc1x01234567, 0);
        c1 += 8;
        wasm_v128_store64_lane(c2, vacc2x01234567, 0);
        c2 += 8;

        vacc0x01234567 = vacc0x89ABCDEF;
        vacc1x01234567 = vacc1x89ABCDEF;
        vacc2x01234567 = vacc2x89ABCDEF;
      }
      if (nc & 4) {
        wasm_v128_store32_lane(c0, vacc0x01234567, 0);
        c0 += 4;
        wasm_v128_store32_lane(c1, vacc1x01234567, 0);
        c1 += 4;
        wasm_v128_store32_lane(c2, vacc2x01234567, 0);
        c2 += 4;

        vacc0x01234567 = wasm_u64x2_shr(vacc0x01234567, 32);
        vacc1x01234567 = wasm_u64x2_shr(vacc1x01234567, 32);
        vacc2x01234567 = wasm_u64x2_shr(vacc2x01234567, 32);
      }
      if (nc & 2) {
        wasm_v128_store16_lane(c0, vacc0x01234567, 0);
        c0 += 2;
        wasm_v128_store16_lane(c1, vacc1x01234567, 0);
        c1 += 2;
        wasm_v128_store16_lane(c2, vacc2x01234567, 0);
        c2 += 2;

        vacc0x01234567 = wasm_u32x4_shr(vacc0x01234567, 16);
        vacc1x01234567 = wasm_u32x4_shr(vacc1x01234567, 16);
        vacc2x01234567 = wasm_u32x4_shr(vacc2x01234567, 16);
      }
      if (nc & 1) {
        wasm_v128_store8_lane(c0, vacc0x01234567, 0);
        wasm_v128_store8_lane(c1, vacc1x01234567, 0);
        wasm_v128_store8_lane(c2, vacc2x01234567, 0);
      }

      nc = 0;
    }
  } while (nc != 0);
}
