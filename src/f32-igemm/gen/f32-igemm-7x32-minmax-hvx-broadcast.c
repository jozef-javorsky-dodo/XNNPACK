// clang-format off
// Auto-generated file. Do not edit!
//   Template: src/f32-igemm/hvx-broadcast.c.in
//   Generator: tools/xngen
//
// Copyright 2024 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>
#include <hexagon_types.h>
#include <hexagon_protos.h>
#include <hvx_hexagon_protos.h>

#include "src/xnnpack/igemm.h"
#include "src/xnnpack/intrinsics-polyfill.h"

void xnn_f32_igemm_minmax_ukernel_7x32__hvx_broadcast(
    size_t mr,
    size_t nc,
    size_t kc,
    size_t ks,
    const float** restrict a,
    const float* restrict w,
    float* restrict c,
    size_t cm_stride,
    size_t cn_stride,
    size_t a_offset,
    const float* zero,
    const struct xnn_f32_minmax_params* restrict params)
{
  assert(mr != 0);
  assert(mr <= 7);
  assert(nc != 0);
  assert(kc != 0);
  assert(kc % sizeof(float) == 0);
  assert(ks != 0);
  assert(ks % (7 * sizeof(void*)) == 0);
  assert(a_offset % sizeof(float) == 0);
  assert(a != NULL);
  assert(w != NULL);
  assert(c != NULL);

  float* c0 = c;
  float* c1 = (float*) ((uintptr_t) c0 + cm_stride);
  if XNN_UNPREDICTABLE(mr < 2) {
    c1 = c0;
  }
  float* c2 = (float*) ((uintptr_t) c1 + cm_stride);
  if XNN_UNPREDICTABLE(mr <= 2) {
    c2 = c1;
  }
  float* c3 = (float*) ((uintptr_t) c2 + cm_stride);
  if XNN_UNPREDICTABLE(mr < 4) {
    c3 = c2;
  }
  float* c4 = (float*) ((uintptr_t) c3 + cm_stride);
  if XNN_UNPREDICTABLE(mr <= 4) {
    c4 = c3;
  }
  float* c5 = (float*) ((uintptr_t) c4 + cm_stride);
  if XNN_UNPREDICTABLE(mr < 6) {
    c5 = c4;
  }
  float* c6 = (float*) ((uintptr_t) c5 + cm_stride);
  if XNN_UNPREDICTABLE(mr <= 6) {
    c6 = c5;
  }

  do {
    HVX_Vector vacc0x0 = Q6_Vqf32_vadd_Vqf32Vsf(Q6_V_vzero(), *((HVX_Vector *)(w + 0)));
    HVX_Vector vacc1x0 = vacc0x0;
    HVX_Vector vacc2x0 = vacc0x0;
    HVX_Vector vacc3x0 = vacc0x0;
    HVX_Vector vacc4x0 = vacc0x0;
    HVX_Vector vacc5x0 = vacc0x0;
    HVX_Vector vacc6x0 = vacc0x0;
    w += 32;

    size_t p = ks;
    do {
      const float* restrict a0 = a[0];
      assert(a0 != NULL);
      if XNN_UNPREDICTABLE(a0 != zero) {
        a0 = (const float*) ((uintptr_t) a0 + a_offset);
      }
      const float* restrict a1 = a[1];
      assert(a1 != NULL);
      if XNN_UNPREDICTABLE(a1 != zero) {
        a1 = (const float*) ((uintptr_t) a1 + a_offset);
      }
      const float* restrict a2 = a[2];
      assert(a2 != NULL);
      if XNN_UNPREDICTABLE(a2 != zero) {
        a2 = (const float*) ((uintptr_t) a2 + a_offset);
      }
      const float* restrict a3 = a[3];
      assert(a3 != NULL);
      if XNN_UNPREDICTABLE(a3 != zero) {
        a3 = (const float*) ((uintptr_t) a3 + a_offset);
      }
      const float* restrict a4 = a[4];
      assert(a4 != NULL);
      if XNN_UNPREDICTABLE(a4 != zero) {
        a4 = (const float*) ((uintptr_t) a4 + a_offset);
      }
      const float* restrict a5 = a[5];
      assert(a5 != NULL);
      if XNN_UNPREDICTABLE(a5 != zero) {
        a5 = (const float*) ((uintptr_t) a5 + a_offset);
      }
      const float* restrict a6 = a[6];
      assert(a6 != NULL);
      if XNN_UNPREDICTABLE(a6 != zero) {
        a6 = (const float*) ((uintptr_t) a6 + a_offset);
      }
      a += 7;

      size_t k = kc;
      do {
        const HVX_Vector vb0 = *((HVX_Vector *)(w));
        w += 32;

        const HVX_Vector va0 =  Q6_V_vsplat_R(*(uint32_t *)a0);
        a0 += 1;
        const HVX_Vector va1 =  Q6_V_vsplat_R(*(uint32_t *)a1);
        a1 += 1;
        const HVX_Vector va2 =  Q6_V_vsplat_R(*(uint32_t *)a2);
        a2 += 1;
        const HVX_Vector va3 =  Q6_V_vsplat_R(*(uint32_t *)a3);
        a3 += 1;
        const HVX_Vector va4 =  Q6_V_vsplat_R(*(uint32_t *)a4);
        a4 += 1;
        const HVX_Vector va5 =  Q6_V_vsplat_R(*(uint32_t *)a5);
        a5 += 1;
        const HVX_Vector va6 =  Q6_V_vsplat_R(*(uint32_t *)a6);
        a6 += 1;

        vacc0x0 = Q6_Vqf32_vadd_Vqf32Vqf32(vacc0x0, Q6_Vqf32_vmpy_VsfVsf(va0, vb0));
        vacc1x0 = Q6_Vqf32_vadd_Vqf32Vqf32(vacc1x0, Q6_Vqf32_vmpy_VsfVsf(va1, vb0));
        vacc2x0 = Q6_Vqf32_vadd_Vqf32Vqf32(vacc2x0, Q6_Vqf32_vmpy_VsfVsf(va2, vb0));
        vacc3x0 = Q6_Vqf32_vadd_Vqf32Vqf32(vacc3x0, Q6_Vqf32_vmpy_VsfVsf(va3, vb0));
        vacc4x0 = Q6_Vqf32_vadd_Vqf32Vqf32(vacc4x0, Q6_Vqf32_vmpy_VsfVsf(va4, vb0));
        vacc5x0 = Q6_Vqf32_vadd_Vqf32Vqf32(vacc5x0, Q6_Vqf32_vmpy_VsfVsf(va5, vb0));
        vacc6x0 = Q6_Vqf32_vadd_Vqf32Vqf32(vacc6x0, Q6_Vqf32_vmpy_VsfVsf(va6, vb0));
        k -= sizeof(float);
      } while (k != 0);
      p -= 7 * sizeof(void*);
    } while (p != 0);

    vacc0x0 = Q6_Vsf_equals_Vqf32(vacc0x0);
    vacc1x0 = Q6_Vsf_equals_Vqf32(vacc1x0);
    vacc2x0 = Q6_Vsf_equals_Vqf32(vacc2x0);
    vacc3x0 = Q6_Vsf_equals_Vqf32(vacc3x0);
    vacc4x0 = Q6_Vsf_equals_Vqf32(vacc4x0);
    vacc5x0 = Q6_Vsf_equals_Vqf32(vacc5x0);
    vacc6x0 = Q6_Vsf_equals_Vqf32(vacc6x0);

    const HVX_Vector vmin = Q6_V_vsplat_R(params->scalar.min);
    vacc0x0 = Q6_Vsf_vmax_VsfVsf(vmin, vacc0x0);
    vacc1x0 = Q6_Vsf_vmax_VsfVsf(vmin, vacc1x0);
    vacc2x0 = Q6_Vsf_vmax_VsfVsf(vmin, vacc2x0);
    vacc3x0 = Q6_Vsf_vmax_VsfVsf(vmin, vacc3x0);
    vacc4x0 = Q6_Vsf_vmax_VsfVsf(vmin, vacc4x0);
    vacc5x0 = Q6_Vsf_vmax_VsfVsf(vmin, vacc5x0);
    vacc6x0 = Q6_Vsf_vmax_VsfVsf(vmin, vacc6x0);

    const HVX_Vector vmax = Q6_V_vsplat_R(params->scalar.max);
    vacc0x0 = Q6_Vsf_vmin_VsfVsf(vmax, vacc0x0);
    vacc1x0 = Q6_Vsf_vmin_VsfVsf(vmax, vacc1x0);
    vacc2x0 = Q6_Vsf_vmin_VsfVsf(vmax, vacc2x0);
    vacc3x0 = Q6_Vsf_vmin_VsfVsf(vmax, vacc3x0);
    vacc4x0 = Q6_Vsf_vmin_VsfVsf(vmax, vacc4x0);
    vacc5x0 = Q6_Vsf_vmin_VsfVsf(vmax, vacc5x0);
    vacc6x0 = Q6_Vsf_vmin_VsfVsf(vmax, vacc6x0);

    if XNN_LIKELY(nc >= 32) {
      *((HVX_UVector *)(c6)) = vacc6x0;
      c6 = (float*) ((uintptr_t) c6 + cn_stride);
      *((HVX_UVector *)(c5)) = vacc5x0;
      c5 = (float*) ((uintptr_t) c5 + cn_stride);
      *((HVX_UVector *)(c4)) = vacc4x0;
      c4 = (float*) ((uintptr_t) c4 + cn_stride);
      *((HVX_UVector *)(c3)) = vacc3x0;
      c3 = (float*) ((uintptr_t) c3 + cn_stride);
      *((HVX_UVector *)(c2)) = vacc2x0;
      c2 = (float*) ((uintptr_t) c2 + cn_stride);
      *((HVX_UVector *)(c1)) = vacc1x0;
      c1 = (float*) ((uintptr_t) c1 + cn_stride);
      *((HVX_UVector *)(c0)) = vacc0x0;
      c0 = (float*) ((uintptr_t) c0 + cn_stride);

      a = (const float**restrict) ((uintptr_t) a - ks);
      nc -= 32;
    } else {
      Q6_V_vstu_variable(c6, nc * sizeof(float), vacc6x0);
      Q6_V_vstu_variable(c5, nc * sizeof(float), vacc5x0);
      Q6_V_vstu_variable(c4, nc * sizeof(float), vacc4x0);
      Q6_V_vstu_variable(c3, nc * sizeof(float), vacc3x0);
      Q6_V_vstu_variable(c2, nc * sizeof(float), vacc2x0);
      Q6_V_vstu_variable(c1, nc * sizeof(float), vacc1x0);
      Q6_V_vstu_variable(c0, nc * sizeof(float), vacc0x0);

      nc = 0;
    }
  } while (nc != 0);
}
