// clang-format off
// Auto-generated file. Do not edit!
//   Template: src/qs8-dwconv/unipass-scalar.c.in
//   Generator: tools/xngen
//
// Copyright 2021 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>

#include "src/xnnpack/common.h"
#include "src/xnnpack/dwconv.h"
#include "src/xnnpack/math.h"
#include "src/xnnpack/microparams.h"
#include "src/xnnpack/unaligned.h"

void xnn_qu8_dwconv_minmax_fp32_ukernel_25p1c__scalar_lrintf(
    size_t channels,
    size_t output_width,
    const uint8_t** input,
    const void* weights,
    uint8_t* output,
    intptr_t input_stride,
    size_t output_increment,
    size_t input_offset,
    size_t input_pixel_stride,
    const uint8_t* zero,
    const union xnn_qu8_conv_minmax_params* restrict params)
{
  assert(channels != 0);
  assert(output_width != 0);

  const float vscale = params->fp32_scalar.scale;
  const float voutput_min_less_zero_point = (int32_t) params->fp32_scalar.output_min - (int32_t) params->fp32_scalar.output_zero_point;
  const float voutput_max_less_zero_point = (int32_t) params->fp32_scalar.output_max - (int32_t) params->fp32_scalar.output_zero_point;
  const int32_t voutput_zero_point = params->fp32_scalar.output_zero_point;
  const int32_t vkernel_zero_point = params->fp32_scalar.kernel_zero_point;
  do {
    const uint8_t* i0 = input[0];
    assert(i0 != NULL);
    if XNN_UNPREDICTABLE(i0 != zero) {
      i0 = (const uint8_t*) ((uintptr_t) i0 + input_offset);
    }
    const uint8_t* i1 = input[1];
    assert(i1 != NULL);
    if XNN_UNPREDICTABLE(i1 != zero) {
      i1 = (const uint8_t*) ((uintptr_t) i1 + input_offset);
    }
    const uint8_t* i2 = input[2];
    assert(i2 != NULL);
    if XNN_UNPREDICTABLE(i2 != zero) {
      i2 = (const uint8_t*) ((uintptr_t) i2 + input_offset);
    }
    const uint8_t* i3 = input[3];
    assert(i3 != NULL);
    if XNN_UNPREDICTABLE(i3 != zero) {
      i3 = (const uint8_t*) ((uintptr_t) i3 + input_offset);
    }
    const uint8_t* i4 = input[4];
    assert(i4 != NULL);
    if XNN_UNPREDICTABLE(i4 != zero) {
      i4 = (const uint8_t*) ((uintptr_t) i4 + input_offset);
    }
    const uint8_t* i5 = input[5];
    assert(i5 != NULL);
    if XNN_UNPREDICTABLE(i5 != zero) {
      i5 = (const uint8_t*) ((uintptr_t) i5 + input_offset);
    }
    const uint8_t* i6 = input[6];
    assert(i6 != NULL);
    if XNN_UNPREDICTABLE(i6 != zero) {
      i6 = (const uint8_t*) ((uintptr_t) i6 + input_offset);
    }
    const uint8_t* i7 = input[7];
    assert(i7 != NULL);
    if XNN_UNPREDICTABLE(i7 != zero) {
      i7 = (const uint8_t*) ((uintptr_t) i7 + input_offset);
    }
    const uint8_t* i8 = input[8];
    assert(i8 != NULL);
    if XNN_UNPREDICTABLE(i8 != zero) {
      i8 = (const uint8_t*) ((uintptr_t) i8 + input_offset);
    }
    const uint8_t* i9 = input[9];
    assert(i9 != NULL);
    if XNN_UNPREDICTABLE(i9 != zero) {
      i9 = (const uint8_t*) ((uintptr_t) i9 + input_offset);
    }
    const uint8_t* i10 = input[10];
    assert(i10 != NULL);
    if XNN_UNPREDICTABLE(i10 != zero) {
      i10 = (const uint8_t*) ((uintptr_t) i10 + input_offset);
    }
    const uint8_t* i11 = input[11];
    assert(i11 != NULL);
    if XNN_UNPREDICTABLE(i11 != zero) {
      i11 = (const uint8_t*) ((uintptr_t) i11 + input_offset);
    }
    const uint8_t* i12 = input[12];
    assert(i12 != NULL);
    if XNN_UNPREDICTABLE(i12 != zero) {
      i12 = (const uint8_t*) ((uintptr_t) i12 + input_offset);
    }
    const uint8_t* i13 = input[13];
    assert(i13 != NULL);
    if XNN_UNPREDICTABLE(i13 != zero) {
      i13 = (const uint8_t*) ((uintptr_t) i13 + input_offset);
    }
    const uint8_t* i14 = input[14];
    assert(i14 != NULL);
    if XNN_UNPREDICTABLE(i14 != zero) {
      i14 = (const uint8_t*) ((uintptr_t) i14 + input_offset);
    }
    const uint8_t* i15 = input[15];
    assert(i15 != NULL);
    if XNN_UNPREDICTABLE(i15 != zero) {
      i15 = (const uint8_t*) ((uintptr_t) i15 + input_offset);
    }
    const uint8_t* i16 = input[16];
    assert(i16 != NULL);
    if XNN_UNPREDICTABLE(i16 != zero) {
      i16 = (const uint8_t*) ((uintptr_t) i16 + input_offset);
    }
    const uint8_t* i17 = input[17];
    assert(i17 != NULL);
    if XNN_UNPREDICTABLE(i17 != zero) {
      i17 = (const uint8_t*) ((uintptr_t) i17 + input_offset);
    }
    const uint8_t* i18 = input[18];
    assert(i18 != NULL);
    if XNN_UNPREDICTABLE(i18 != zero) {
      i18 = (const uint8_t*) ((uintptr_t) i18 + input_offset);
    }
    const uint8_t* i19 = input[19];
    assert(i19 != NULL);
    if XNN_UNPREDICTABLE(i19 != zero) {
      i19 = (const uint8_t*) ((uintptr_t) i19 + input_offset);
    }
    const uint8_t* i20 = input[20];
    assert(i20 != NULL);
    if XNN_UNPREDICTABLE(i20 != zero) {
      i20 = (const uint8_t*) ((uintptr_t) i20 + input_offset);
    }
    const uint8_t* i21 = input[21];
    assert(i21 != NULL);
    if XNN_UNPREDICTABLE(i21 != zero) {
      i21 = (const uint8_t*) ((uintptr_t) i21 + input_offset);
    }
    const uint8_t* i22 = input[22];
    assert(i22 != NULL);
    if XNN_UNPREDICTABLE(i22 != zero) {
      i22 = (const uint8_t*) ((uintptr_t) i22 + input_offset);
    }
    const uint8_t* i23 = input[23];
    assert(i23 != NULL);
    if XNN_UNPREDICTABLE(i23 != zero) {
      i23 = (const uint8_t*) ((uintptr_t) i23 + input_offset);
    }
    const uint8_t* i24 = input[24];
    assert(i24 != NULL);
    if XNN_UNPREDICTABLE(i24 != zero) {
      i24 = (const uint8_t*) ((uintptr_t) i24 + input_offset);
    }
    input = (const uint8_t**) ((uintptr_t) input + input_stride);

    size_t c = channels;
    const void* w = weights;
    do {
      int32_t vacc = unaligned_load_s32(w);

      const int32_t vi0 = (int32_t) (uint32_t) *i0++;
      const int32_t vk0 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[0] - vkernel_zero_point;
      vacc += vi0 * vk0;
      const int32_t vi1 = (int32_t) (uint32_t) *i1++;
      const int32_t vk1 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[1] - vkernel_zero_point;
      vacc += vi1 * vk1;
      const int32_t vi2 = (int32_t) (uint32_t) *i2++;
      const int32_t vk2 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[2] - vkernel_zero_point;
      vacc += vi2 * vk2;
      const int32_t vi3 = (int32_t) (uint32_t) *i3++;
      const int32_t vk3 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[3] - vkernel_zero_point;
      vacc += vi3 * vk3;
      const int32_t vi4 = (int32_t) (uint32_t) *i4++;
      const int32_t vk4 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[4] - vkernel_zero_point;
      vacc += vi4 * vk4;
      const int32_t vi5 = (int32_t) (uint32_t) *i5++;
      const int32_t vk5 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[5] - vkernel_zero_point;
      vacc += vi5 * vk5;
      const int32_t vi6 = (int32_t) (uint32_t) *i6++;
      const int32_t vk6 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[6] - vkernel_zero_point;
      vacc += vi6 * vk6;
      const int32_t vi7 = (int32_t) (uint32_t) *i7++;
      const int32_t vk7 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[7] - vkernel_zero_point;
      vacc += vi7 * vk7;
      const int32_t vi8 = (int32_t) (uint32_t) *i8++;
      const int32_t vk8 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[8] - vkernel_zero_point;
      vacc += vi8 * vk8;
      const int32_t vi9 = (int32_t) (uint32_t) *i9++;
      const int32_t vk9 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[9] - vkernel_zero_point;
      vacc += vi9 * vk9;
      const int32_t vi10 = (int32_t) (uint32_t) *i10++;
      const int32_t vk10 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[10] - vkernel_zero_point;
      vacc += vi10 * vk10;
      const int32_t vi11 = (int32_t) (uint32_t) *i11++;
      const int32_t vk11 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[11] - vkernel_zero_point;
      vacc += vi11 * vk11;
      const int32_t vi12 = (int32_t) (uint32_t) *i12++;
      const int32_t vk12 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[12] - vkernel_zero_point;
      vacc += vi12 * vk12;
      const int32_t vi13 = (int32_t) (uint32_t) *i13++;
      const int32_t vk13 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[13] - vkernel_zero_point;
      vacc += vi13 * vk13;
      const int32_t vi14 = (int32_t) (uint32_t) *i14++;
      const int32_t vk14 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[14] - vkernel_zero_point;
      vacc += vi14 * vk14;
      const int32_t vi15 = (int32_t) (uint32_t) *i15++;
      const int32_t vk15 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[15] - vkernel_zero_point;
      vacc += vi15 * vk15;
      const int32_t vi16 = (int32_t) (uint32_t) *i16++;
      const int32_t vk16 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[16] - vkernel_zero_point;
      vacc += vi16 * vk16;
      const int32_t vi17 = (int32_t) (uint32_t) *i17++;
      const int32_t vk17 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[17] - vkernel_zero_point;
      vacc += vi17 * vk17;
      const int32_t vi18 = (int32_t) (uint32_t) *i18++;
      const int32_t vk18 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[18] - vkernel_zero_point;
      vacc += vi18 * vk18;
      const int32_t vi19 = (int32_t) (uint32_t) *i19++;
      const int32_t vk19 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[19] - vkernel_zero_point;
      vacc += vi19 * vk19;
      const int32_t vi20 = (int32_t) (uint32_t) *i20++;
      const int32_t vk20 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[20] - vkernel_zero_point;
      vacc += vi20 * vk20;
      const int32_t vi21 = (int32_t) (uint32_t) *i21++;
      const int32_t vk21 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[21] - vkernel_zero_point;
      vacc += vi21 * vk21;
      const int32_t vi22 = (int32_t) (uint32_t) *i22++;
      const int32_t vk22 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[22] - vkernel_zero_point;
      vacc += vi22 * vk22;
      const int32_t vi23 = (int32_t) (uint32_t) *i23++;
      const int32_t vk23 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[23] - vkernel_zero_point;
      vacc += vi23 * vk23;
      const int32_t vi24 = (int32_t) (uint32_t) *i24++;
      const int32_t vk24 = (int32_t) (uint32_t) ((const uint8_t*) ((uintptr_t) w + sizeof(int32_t)))[24] - vkernel_zero_point;
      vacc += vi24 * vk24;

      w = (const void*) ((uintptr_t) w + sizeof(int32_t) + 25 * sizeof(uint8_t));

      float vfpacc = (float) vacc * vscale;

      vfpacc = math_max_f32(vfpacc, voutput_min_less_zero_point);
      vfpacc = math_min_f32(vfpacc, voutput_max_less_zero_point);
      const int32_t vrndacc = (int32_t) lrintf(vfpacc);
      int32_t vout = vrndacc + voutput_zero_point;

      *output++ = (uint8_t) vout;
    } while (--c != 0);

    input_offset += input_pixel_stride;
    output = (uint8_t*) ((uintptr_t) output + output_increment);
  } while (--output_width != 0);
}
