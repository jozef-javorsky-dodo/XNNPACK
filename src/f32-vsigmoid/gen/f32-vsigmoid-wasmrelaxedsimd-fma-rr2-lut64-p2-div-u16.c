// clang-format off
// Auto-generated file. Do not edit!
//   Template: src/f32-vsigmoid/wasmsimd-rr2-lut64-p2-div.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <wasm_simd128.h>

#include "src/xnnpack/common.h"
#include "src/xnnpack/vunary.h"


extern XNN_INTERNAL const uint32_t xnn_table_exp2minus_k_over_64[64];

void xnn_f32_vsigmoid_ukernel__wasmrelaxedsimd_fma_rr2_lut64_p2_div_u16(
    size_t batch,
    const float* input,
    float* output,
    const struct xnn_f32_default_params* restrict params) XNN_OOB_READS
{
  assert(batch != 0);
  assert(batch % sizeof(float) == 0);
  assert(input != NULL);
  assert(output != NULL);

  const v128_t vmagic_bias = wasm_f32x4_const_splat(0x1.800000p17f);
  const v128_t vminus_log2e = wasm_f32x4_const_splat(-0x1.715476p0f);
  const v128_t vindex_mask = wasm_u32x4_const_splat(UINT32_C(0x3F));
  const v128_t vln2_hi = wasm_f32x4_const_splat(0x1.630000p-1f);
  const v128_t vln2_lo = wasm_f32x4_const_splat(-0x1.BD0106p-13f);
  const v128_t vc2 = wasm_f32x4_const_splat(0x1.FFFF0Ap-2f);
  const v128_t vone = wasm_f32x4_const_splat(1.0f);
  const v128_t vdenorm_cutoff = wasm_f32x4_const_splat(0x1.5D589Ep+6f);

  XNN_FORCE_REALIZATION(vmagic_bias);
  XNN_FORCE_REALIZATION(vminus_log2e);
  // XNN_FORCE_REALIZATION(vindex_mask);
  XNN_FORCE_REALIZATION(vln2_hi);
  XNN_FORCE_REALIZATION(vln2_lo);
  XNN_FORCE_REALIZATION(vc2);
  // XNN_FORCE_REALIZATION(vone);
  XNN_FORCE_REALIZATION(vdenorm_cutoff);

  for (; batch >= 16 * sizeof(float); batch -= 16 * sizeof(float)) {
    const v128_t vx0123 = wasm_v128_load(input);
    const v128_t vx4567 = wasm_v128_load(input + 4);
    const v128_t vx89AB = wasm_v128_load(input + 8);
    const v128_t vxCDEF = wasm_v128_load(input + 12);
    input += 16;

    const v128_t vz0123 = wasm_f32x4_abs(vx0123);
    const v128_t vz4567 = wasm_f32x4_abs(vx4567);
    const v128_t vz89AB = wasm_f32x4_abs(vx89AB);
    const v128_t vzCDEF = wasm_f32x4_abs(vxCDEF);

    v128_t vn0123 = wasm_f32x4_relaxed_madd(vz0123, vminus_log2e, vmagic_bias);
    v128_t vn4567 = wasm_f32x4_relaxed_madd(vz4567, vminus_log2e, vmagic_bias);
    v128_t vn89AB = wasm_f32x4_relaxed_madd(vz89AB, vminus_log2e, vmagic_bias);
    v128_t vnCDEF = wasm_f32x4_relaxed_madd(vzCDEF, vminus_log2e, vmagic_bias);

    const v128_t vidx0123 = wasm_i32x4_shl(wasm_v128_and(vn0123, vindex_mask), 2);
    const v128_t ve0123 = wasm_i32x4_shl(vn0123, 17);
    const v128_t vidx4567 = wasm_i32x4_shl(wasm_v128_and(vn4567, vindex_mask), 2);
    const v128_t ve4567 = wasm_i32x4_shl(vn4567, 17);
    const v128_t vidx89AB = wasm_i32x4_shl(wasm_v128_and(vn89AB, vindex_mask), 2);
    const v128_t ve89AB = wasm_i32x4_shl(vn89AB, 17);
    const v128_t vidxCDEF = wasm_i32x4_shl(wasm_v128_and(vnCDEF, vindex_mask), 2);
    const v128_t veCDEF = wasm_i32x4_shl(vnCDEF, 17);

    const uint32_t vidx0 = wasm_u32x4_extract_lane(vidx0123, 0);
    v128_t vl0123 = wasm_v128_load32_zero((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx0));
    const uint32_t vidx4 = wasm_u32x4_extract_lane(vidx4567, 0);
    v128_t vl4567 = wasm_v128_load32_zero((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx4));
    const uint32_t vidx8 = wasm_u32x4_extract_lane(vidx89AB, 0);
    v128_t vl89AB = wasm_v128_load32_zero((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx8));
    const uint32_t vidxC = wasm_u32x4_extract_lane(vidxCDEF, 0);
    v128_t vlCDEF = wasm_v128_load32_zero((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidxC));

    const uint32_t vidx1 = wasm_u32x4_extract_lane(vidx0123, 1);
    vl0123 = wasm_v128_load32_lane((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx1), vl0123, 1);
    const uint32_t vidx5 = wasm_u32x4_extract_lane(vidx4567, 1);
    vl4567 = wasm_v128_load32_lane((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx5), vl4567, 1);
    const uint32_t vidx9 = wasm_u32x4_extract_lane(vidx89AB, 1);
    vl89AB = wasm_v128_load32_lane((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx9), vl89AB, 1);
    const uint32_t vidxD = wasm_u32x4_extract_lane(vidxCDEF, 1);
    vlCDEF = wasm_v128_load32_lane((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidxD), vlCDEF, 1);
    const uint32_t vidx2 = wasm_u32x4_extract_lane(vidx0123, 2);
    vl0123 = wasm_v128_load32_lane((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx2), vl0123, 2);
    const uint32_t vidx6 = wasm_u32x4_extract_lane(vidx4567, 2);
    vl4567 = wasm_v128_load32_lane((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx6), vl4567, 2);
    const uint32_t vidxA = wasm_u32x4_extract_lane(vidx89AB, 2);
    vl89AB = wasm_v128_load32_lane((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidxA), vl89AB, 2);
    const uint32_t vidxE = wasm_u32x4_extract_lane(vidxCDEF, 2);
    vlCDEF = wasm_v128_load32_lane((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidxE), vlCDEF, 2);
    const uint32_t vidx3 = wasm_u32x4_extract_lane(vidx0123, 3);
    vl0123 = wasm_v128_load32_lane((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx3), vl0123, 3);
    const uint32_t vidx7 = wasm_u32x4_extract_lane(vidx4567, 3);
    vl4567 = wasm_v128_load32_lane((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx7), vl4567, 3);
    const uint32_t vidxB = wasm_u32x4_extract_lane(vidx89AB, 3);
    vl89AB = wasm_v128_load32_lane((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidxB), vl89AB, 3);
    const uint32_t vidxF = wasm_u32x4_extract_lane(vidxCDEF, 3);
    vlCDEF = wasm_v128_load32_lane((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidxF), vlCDEF, 3);

    const v128_t vs0123 = wasm_i32x4_add(vl0123, ve0123);
    const v128_t vs4567 = wasm_i32x4_add(vl4567, ve4567);
    const v128_t vs89AB = wasm_i32x4_add(vl89AB, ve89AB);
    const v128_t vsCDEF = wasm_i32x4_add(vlCDEF, veCDEF);

    vn0123 = wasm_f32x4_sub(vn0123, vmagic_bias);
    vn4567 = wasm_f32x4_sub(vn4567, vmagic_bias);
    vn89AB = wasm_f32x4_sub(vn89AB, vmagic_bias);
    vnCDEF = wasm_f32x4_sub(vnCDEF, vmagic_bias);

    v128_t vt0123 = wasm_f32x4_relaxed_madd(vn0123, vln2_hi, vz0123);
    v128_t vt4567 = wasm_f32x4_relaxed_madd(vn4567, vln2_hi, vz4567);
    v128_t vt89AB = wasm_f32x4_relaxed_madd(vn89AB, vln2_hi, vz89AB);
    v128_t vtCDEF = wasm_f32x4_relaxed_madd(vnCDEF, vln2_hi, vzCDEF);

    vt0123 = wasm_f32x4_relaxed_madd(vn0123, vln2_lo, vt0123);
    vt4567 = wasm_f32x4_relaxed_madd(vn4567, vln2_lo, vt4567);
    vt89AB = wasm_f32x4_relaxed_madd(vn89AB, vln2_lo, vt89AB);
    vtCDEF = wasm_f32x4_relaxed_madd(vnCDEF, vln2_lo, vtCDEF);

    v128_t vp0123 = wasm_f32x4_mul(vt0123, vc2);
    v128_t vp4567 = wasm_f32x4_mul(vt4567, vc2);
    v128_t vp89AB = wasm_f32x4_mul(vt89AB, vc2);
    v128_t vpCDEF = wasm_f32x4_mul(vtCDEF, vc2);

    vp0123 = wasm_f32x4_relaxed_nmadd(vp0123, vt0123, vt0123);
    vp4567 = wasm_f32x4_relaxed_nmadd(vp4567, vt4567, vt4567);
    vp89AB = wasm_f32x4_relaxed_nmadd(vp89AB, vt89AB, vt89AB);
    vpCDEF = wasm_f32x4_relaxed_nmadd(vpCDEF, vtCDEF, vtCDEF);

    const v128_t vy0123 = wasm_f32x4_relaxed_nmadd(vs0123, vp0123, vs0123);
    const v128_t vy4567 = wasm_f32x4_relaxed_nmadd(vs4567, vp4567, vs4567);
    const v128_t vy89AB = wasm_f32x4_relaxed_nmadd(vs89AB, vp89AB, vs89AB);
    const v128_t vyCDEF = wasm_f32x4_relaxed_nmadd(vsCDEF, vpCDEF, vsCDEF);

    const v128_t vd0123 = wasm_f32x4_add(vy0123, vone);
    const v128_t vd4567 = wasm_f32x4_add(vy4567, vone);
    const v128_t vd89AB = wasm_f32x4_add(vy89AB, vone);
    const v128_t vdCDEF = wasm_f32x4_add(vyCDEF, vone);

    v128_t vf0123 = wasm_f32x4_div(vy0123, vd0123);
    v128_t vf4567 = wasm_f32x4_div(vy4567, vd4567);
    v128_t vf89AB = wasm_f32x4_div(vy89AB, vd89AB);
    v128_t vfCDEF = wasm_f32x4_div(vyCDEF, vdCDEF);

    vf0123 = wasm_v128_andnot(vf0123, wasm_f32x4_gt(vz0123, vdenorm_cutoff));
    vf4567 = wasm_v128_andnot(vf4567, wasm_f32x4_gt(vz4567, vdenorm_cutoff));
    vf89AB = wasm_v128_andnot(vf89AB, wasm_f32x4_gt(vz89AB, vdenorm_cutoff));
    vfCDEF = wasm_v128_andnot(vfCDEF, wasm_f32x4_gt(vzCDEF, vdenorm_cutoff));

    const v128_t vcf0123 = wasm_f32x4_sub(vone, vf0123);
    const v128_t vcf4567 = wasm_f32x4_sub(vone, vf4567);
    const v128_t vcf89AB = wasm_f32x4_sub(vone, vf89AB);
    const v128_t vcfCDEF = wasm_f32x4_sub(vone, vfCDEF);

    vf0123 = wasm_i32x4_relaxed_laneselect(vf0123, vcf0123, wasm_i32x4_shr(vx0123, 31));
    vf4567 = wasm_i32x4_relaxed_laneselect(vf4567, vcf4567, wasm_i32x4_shr(vx4567, 31));
    vf89AB = wasm_i32x4_relaxed_laneselect(vf89AB, vcf89AB, wasm_i32x4_shr(vx89AB, 31));
    vfCDEF = wasm_i32x4_relaxed_laneselect(vfCDEF, vcfCDEF, wasm_i32x4_shr(vxCDEF, 31));

    wasm_v128_store(output, vf0123);
    wasm_v128_store(output + 4, vf4567);
    wasm_v128_store(output + 8, vf89AB);
    wasm_v128_store(output + 12, vfCDEF);
    output += 16;
  }
  for (; batch >= 4 * sizeof(float); batch -= 4 * sizeof(float)) {
    const v128_t vx = wasm_v128_load(input);
    input += 4;

    const v128_t vz = wasm_f32x4_abs(vx);

    v128_t vn = wasm_f32x4_relaxed_madd(vz, vminus_log2e, vmagic_bias);
    const v128_t ve = wasm_i32x4_shl(vn, 17);

    const v128_t vidx = wasm_i32x4_shl(wasm_v128_and(vn, vindex_mask), 2);

    const uint32_t vidx0 = wasm_u32x4_extract_lane(vidx, 0);
    v128_t vl = wasm_v128_load32_zero((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx0));

    const uint32_t vidx1 = wasm_u32x4_extract_lane(vidx, 1);
    vl = wasm_v128_load32_lane((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx1), vl, 1);

    const uint32_t vidx2 = wasm_u32x4_extract_lane(vidx, 2);
    vl = wasm_v128_load32_lane((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx2), vl, 2);

    const uint32_t vidx3 = wasm_u32x4_extract_lane(vidx, 3);
    vl = wasm_v128_load32_lane((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx3), vl, 3);

    const v128_t vs = wasm_i32x4_add(vl, ve);
    vn = wasm_f32x4_sub(vn, vmagic_bias);

    v128_t vt = wasm_f32x4_relaxed_madd(vn, vln2_hi, vz);
    vt = wasm_f32x4_relaxed_madd(vn, vln2_lo, vt);

    v128_t vp = wasm_f32x4_mul(vt, vc2);
    vp = wasm_f32x4_relaxed_nmadd(vp, vt, vt);

    const v128_t vy = wasm_f32x4_relaxed_nmadd(vs, vp, vs);
    const v128_t vd = wasm_f32x4_add(vy, vone);

    v128_t vf = wasm_f32x4_div(vy, vd);
    vf = wasm_v128_andnot(vf, wasm_f32x4_gt(vz, vdenorm_cutoff));
    const v128_t vcf = wasm_f32x4_sub(vone, vf);
    vf = wasm_i32x4_relaxed_laneselect(vf, vcf, wasm_i32x4_shr(vx, 31));

    wasm_v128_store(output, vf);
    output += 4;
  }
  if XNN_UNLIKELY(batch != 0) {
    const v128_t vx = wasm_v128_load(input);

    const v128_t vz = wasm_f32x4_abs(vx);

    v128_t vn = wasm_f32x4_relaxed_madd(vz, vminus_log2e, vmagic_bias);
    const v128_t ve = wasm_i32x4_shl(vn, 17);

    const v128_t vidx = wasm_i32x4_shl(wasm_v128_and(vn, vindex_mask), 2);

    const uint32_t vidx0 = wasm_u32x4_extract_lane(vidx, 0);
    v128_t vl = wasm_v128_load32_zero((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx0));

    const uint32_t vidx1 = wasm_u32x4_extract_lane(vidx, 1);
    vl = wasm_v128_load32_lane((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx1), vl, 1);

    const uint32_t vidx2 = wasm_u32x4_extract_lane(vidx, 2);
    vl = wasm_v128_load32_lane((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx2), vl, 2);

    const uint32_t vidx3 = wasm_u32x4_extract_lane(vidx, 3);
    vl = wasm_v128_load32_lane((const void*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx3), vl, 3);

    const v128_t vs = wasm_i32x4_add(vl, ve);
    vn = wasm_f32x4_sub(vn, vmagic_bias);

    v128_t vt = wasm_f32x4_relaxed_madd(vn, vln2_hi, vz);
    vt = wasm_f32x4_relaxed_madd(vn, vln2_lo, vt);

    v128_t vp = wasm_f32x4_mul(vt, vc2);
    vp = wasm_f32x4_relaxed_nmadd(vp, vt, vt);

    const v128_t vy = wasm_f32x4_relaxed_nmadd(vs, vp, vs);
    const v128_t vd = wasm_f32x4_add(vy, vone);

    v128_t vf = wasm_f32x4_div(vy, vd);
    vf = wasm_v128_andnot(vf, wasm_f32x4_gt(vz, vdenorm_cutoff));
    const v128_t vcf = wasm_f32x4_sub(vone, vf);
    vf = wasm_i32x4_relaxed_laneselect(vf, vcf, wasm_i32x4_shr(vx, 31));

    if (batch & (2 * sizeof(float))) {
      wasm_v128_store64_lane(output, vf, 0);
      vf = wasm_v64x2_shuffle(vf, vf, 1, 1);
      output += 2;
    }
    if (batch & (1 * sizeof(float))) {
      wasm_v128_store32_lane(output, vf, 0);
    }
  }
}
