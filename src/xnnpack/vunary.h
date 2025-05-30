// Copyright 2019 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#include <stddef.h>
#include <stdint.h>

#include "src/xnnpack/common.h"
#include "src/xnnpack/math.h"
#include "src/xnnpack/microparams.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DECLARE_BF16_UKERNEL_FUNCTION(fn_name, params_type)                   \
  XNN_INTERNAL void fn_name(size_t n, const xnn_bfloat16* x, xnn_bfloat16* y, \
                            const params_type* params);

#define DECLARE_F16_UKERNEL_FUNCTION(fn_name, params_type)                  \
  XNN_INTERNAL void fn_name(size_t n, const xnn_float16* x, xnn_float16* y, \
                            const params_type* params);

#define DECLARE_F32_UKERNEL_FUNCTION(fn_name, params_type)      \
  XNN_INTERNAL void fn_name(size_t n, const float* x, float* y, \
                            const params_type* params);

#define XNN_UKERNEL(arch_flags, fn_name, batch_tile, vector_tile, datatype, \
                    params_type, init_params)                               \
  XNN_INTERNAL void fn_name(size_t n, const int8_t* x, int8_t* y,           \
                            const struct xnn_s8_minmax_params* params);
#include "src/s8-vclamp/s8-vclamp.h"
#undef XNN_UKERNEL

#define XNN_UKERNEL(arch_flags, fn_name, batch_tile, vector_tile, datatype, \
                    params_type, init_params)                               \
  XNN_INTERNAL void fn_name(size_t n, const uint8_t* x, uint8_t* y,         \
                            const struct xnn_u8_minmax_params* params);
#include "src/u8-vclamp/u8-vclamp.h"
#undef XNN_UKERNEL

#define XNN_UKERNEL(arch_flags, fn_name, batch_tile, vector_tile, datatype, \
                    params_type, init_params)                               \
  DECLARE_F16_UKERNEL_FUNCTION(fn_name, params_type);
#include "src/f16-vabs/f16-vabs.h"
#include "src/f16-vapproxgelu/f16-vapproxgelu.h"
#include "src/f16-vclamp/f16-vclamp.h"
#include "src/f16-vcos/f16-vcos.h"
#include "src/f16-velu/f16-velu.h"
#include "src/f16-vexp/f16-vexp.h"
#include "src/f16-vgelu/f16-vgelu.h"
#include "src/f16-vhswish/f16-vhswish.h"
#include "src/f16-vlrelu/f16-vlrelu.h"
#include "src/f16-vneg/f16-vneg.h"
#include "src/f16-vrnd/f16-vrndd.h"
#include "src/f16-vrnd/f16-vrndne.h"
#include "src/f16-vrnd/f16-vrndu.h"
#include "src/f16-vrnd/f16-vrndz.h"
#include "src/f16-vrsqrt/f16-vrsqrt.h"
#include "src/f16-vsigmoid/f16-vsigmoid.h"
#include "src/f16-vsin/f16-vsin.h"
#include "src/f16-vsqr/f16-vsqr.h"
#include "src/f16-vsqrt/f16-vsqrt.h"
#include "src/f16-vtanh/f16-vtanh.h"
#undef XNN_UKERNEL
#undef XNN_UKERNEL

#define XNN_UKERNEL(arch_flags, fn_name, batch_tile, vector_tile, datatype, \
                    params_type, init_params)                               \
  DECLARE_F32_UKERNEL_FUNCTION(fn_name, params_type);
#include "src/f32-vabs/f32-vabs.h"
#include "src/f32-vapproxgelu/f32-vapproxgelu.h"
#include "src/f32-vclamp/f32-vclamp.h"
#include "src/f32-vcos/f32-vcos.h"
#include "src/f32-velu/f32-velu.h"
#include "src/f32-vexp/f32-vexp.h"
#include "src/f32-vgelu/f32-vgelu.h"
#include "src/f32-vhswish/f32-vhswish.h"
#include "src/f32-vlog/f32-vlog.h"
#include "src/f32-vlrelu/f32-vlrelu.h"
#include "src/f32-vneg/f32-vneg.h"
#include "src/f32-vrelu/f32-vrelu.h"
#include "src/f32-vrnd/f32-vrndd.h"
#include "src/f32-vrnd/f32-vrndne.h"
#include "src/f32-vrnd/f32-vrndu.h"
#include "src/f32-vrnd/f32-vrndz.h"
#include "src/f32-vrsqrt/f32-vrsqrt.h"
#include "src/f32-vsigmoid/f32-vsigmoid.h"
#include "src/f32-vsin/f32-vsin.h"
#include "src/f32-vsqr/f32-vsqr.h"
#include "src/f32-vsqrt/f32-vsqrt.h"
#include "src/f32-vtanh/f32-vtanh.h"
#undef XNN_UKERNEL
#undef XNN_UKERNEL

#define XNN_UKERNEL(arch_flags, fn_name, batch_tile, vector_tile, datatype, \
                    params_type, init_params)                               \
  XNN_INTERNAL void fn_name(size_t n, const int8_t* input, int8_t* output,  \
                            const params_type* params);
#include "src/qs8-vlrelu/qs8-vlrelu.h"
#undef XNN_UKERNEL

#define XNN_UKERNEL(arch_flags, fn_name, batch_tile, vector_tile, datatype,  \
                    params_type, init_params)                                \
  XNN_INTERNAL void fn_name(size_t n, const uint8_t* input, uint8_t* output, \
                            const params_type* params);
#include "src/qu8-vlrelu/qu8-vlrelu.h"
#undef XNN_UKERNEL

#define DECLARE_XX_VUNARY_UKERNEL_FUNCTION(fn_name)           \
  XNN_INTERNAL void fn_name(size_t n, const void* x, void* y, \
                            const void* params);

DECLARE_XX_VUNARY_UKERNEL_FUNCTION(xnn_xx_copy_ukernel__scalar_memcpy)

#ifdef __cplusplus
}  // extern "C"
#endif
