// Copyright 2025 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include "src/xnnpack/assembly.h"

BEGIN_FUNCTION xnn_f32_gemm_minmax_ukernel_1x16__asm_aarch64_neonfma_ld32_2

      # Free up GP registers.
      sub sp, sp, 256
      stp x27, x28, [sp, 224]
      stp x25, x26, [sp, 192]
      stp x23, x24, [sp, 160]
      stp x21, x22, [sp, 128]
      stp x19, x20, [sp, 96]

      # Preserve callee saved q8-q15 registers.
      stp d8, d9, [sp, 64]
      stp d10, d11, [sp, 48]
      stp d12, d13, [sp, 32]
      stp d14, d15, [sp, 16]

      # Load params.
      ldr x13, [sp, 264]

      # Load min/max values.
      ld2r {v0.4s, v1.4s}, [x13]

.Louter_loop:
      # Initialize k counter.
      mov x20, x2

      # Initialize accumulators with the biases.
      ldp q11, q12, [x5, 0]
      ldp q13, q14, [x5, 32]
      add x5, x5, 64

.Linner_loop:
      ldr s2, [x3], 4
      ldp q7, q8, [x5], 32
      ldp q9, q10, [x5], 32
      fmla v11.4s, v7.4s, v2.s[0]
      fmla v12.4s, v8.4s, v2.s[0]
      fmla v13.4s, v9.4s, v2.s[0]
      fmla v14.4s, v10.4s, v2.s[0]
      subs x20, x20, 4
      bne .Linner_loop


.Linner_loop_end:
      # Min/max clamping.
      fmin v11.4s, v1.4s, v11.4s
      fmin v12.4s, v1.4s, v12.4s
      fmin v13.4s, v1.4s, v13.4s
      fmin v14.4s, v1.4s, v14.4s
      fmax v11.4s, v0.4s, v11.4s
      fmax v12.4s, v0.4s, v12.4s
      fmax v13.4s, v0.4s, v13.4s
      fmax v14.4s, v0.4s, v14.4s

      # Check whether full or partial store.
      cmp x1, 16
      b.lo .Ltail_8
      stp q11, q12, [x6], #32
      stp q13, q14, [x6], #32
      sub x3, x3, x2

      sub x1, x1, 16
      b.ne .Louter_loop
      b .Lreturn

.Ltail_8:
      tbz w1, 3, .Ltail_4
      stp q11, q12, [x6], #32
      mov v11.16b, v13.16b
      mov v12.16b, v14.16b


.Ltail_4:
      tbz w1, 2, .Ltail_2
      str q11, [x6], #16
      mov v11.16b, v12.16b


.Ltail_2:
      tbz w1, 1, .Ltail_1
      str d11, [x6], #8
      dup d11, v11.d[1]


.Ltail_1:
      tbz w1, 0, .Lreturn
      str s11, [x6], #0

.Lreturn:
      # Restore the callee saved GP registers.
      ldp x27, x28, [sp, 224]
      ldp x25, x26, [sp, 192]
      ldp x23, x24, [sp, 160]
      ldp x21, x22, [sp, 128]
      ldp x19, x20, [sp, 96]

      # Restore callee saved q8-q15 registers.
      ldp d8, d9, [sp, 64]
      ldp d10, d11, [sp, 48]
      ldp d12, d13, [sp, 32]
      ldp d14, d15, [sp, 16]
      add sp, sp, 256
      ret
END_FUNCTION xnn_f32_gemm_minmax_ukernel_1x16__asm_aarch64_neonfma_ld32_2