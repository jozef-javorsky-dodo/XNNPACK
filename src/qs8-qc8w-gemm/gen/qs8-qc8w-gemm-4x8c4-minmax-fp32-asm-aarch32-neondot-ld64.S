// clang-format off
// Auto-generated file. Do not edit!
//   Template: src/qs8-gemm/4x8c4-aarch32-neondot-ld64.S.in
//   Generator: tools/xngen
//
// Copyright 2021 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.


#include "src/xnnpack/assembly.h"

.syntax unified

// void xnn_qs8_qc8w_gemm_minmax_fp32_ukernel_4x8c4__asm_aarch32_neondot_ld64(
//     size_t mr,                            r0
//     size_t nc,                            r1
//     size_t kc,                            r2 -> r5
//     const uint8_t* restrict a,             r3
//     size_t a_stride,           sp + 80 -> (r7)
//     const void* restrict w,     sp + 84 -> r9
//     uint8_t* restrict c,        sp + 88 -> r11
//     size_t cm_stride,          sp + 92 -> (r6)
//     size_t cn_stride,          sp + 96 -> r7
//     xnn_qs8_qc8w_conv_minmax_params params)  sp + 100 -> (r5)

// d8-d15, r4-r11,r14(lr) need to be preserved if used. r13(sp),r15(pc) are reserved.

// Register usage
// A0   r3  d0
// A1  r12  d1
// A2  r10  d2
// A3   r0  d3
// B    r9  q2 q3 q4 q5
// C0  r11 d16-d17  q8  d18-d19  q9
// C1   r4 d20-d21 q10  d22-d23 q11
// C2   r8 d24-d25 q12  d26-d27 q13
// C3   r6 d28-d29 q14  d30-d31 q15
// unused q7

// params structure is 4 bytes
//  struct {
//    int16_t output_zero_point;  d13[2]
//    int8_t output_min;          d13[6]
//    int8_t output_max;          d13[7]
//  } xnn_qs8_minmax_params.neonv8;

// iOS does not support 32 bit ARM with Neon DotProduct.
#ifndef __APPLE__

BEGIN_FUNCTION xnn_qs8_qc8w_gemm_minmax_fp32_ukernel_4x8c4__asm_aarch32_neondot_ld64
        # Push 80 bytes
        PUSH        {r4, r5, r6, r7, r8, r9, r10, r11}  // 32
        VPUSH       {d8-d13}                            // +48 = 80

        LDR         r7, [sp, 80]            // a_stride
        ADD         r2, r2, 3               // kc = (kc + 3) & ~3
        LDR         r11, [sp, 88]           // c
        LDR         r6, [sp, 92]            // cm_stride
        LDR         r9, [sp, 84]            // w
        BIC         r2, r2, 3
        LDR         r5, [sp, 100]           // params

        # Clamp A and C pointers
        CMP         r0, 2                   // if mr >= 2
        ADD         r12, r3, r7             //   a1 = a0 + a_stride
        ADD         r4, r11, r6             //   c1 = c0 + cm_stride
        MOVLO       r12, r3                 // a1
        MOVLO       r4, r11                 // c1
                                        // if mr > 2
        ADD         r10, r12, r7            //   a2 = a1 + a_stride
        ADD         r8, r4, r6              //   c2 = c1 + cm_stride
        MOVLS       r10, r12                // a2
        MOVLS       r8, r4                  // c2

        CMP         r0, 4                   // if mr >=4
        ADD         r0, r10, r7             //   a3 = a2 + a_stride
        ADD         r6, r8, r6              //   c3 = c2 + cm_stride
        MOVLO       r0, r10                 // a3
        MOVLO       r6, r8                  // c3

        # Load params values
        VLD1.32     {d13[]}, [r5]           // QC8 params
        LDR         r7, [sp, 96]            // cn_stride

        .p2align    3
0:
        # Load initial bias from w into accumulators
        VLDM        r9!, {d16-d19}          // Bias
        SUBS        r5, r2, 8               // k = kc - 8
        VMOV        q10, q8
        VMOV        q11, q9
        VMOV        q12, q8
        VMOV        q13, q9
        VMOV        q14, q8
        VMOV        q15, q9
        BLO         3f                      // less than 8 channels?

        # Main loop - 8 bytes of A.
        # 16 SDOT, 4 LD64 A, 4 LD128 B
        .p2align    3
1:
        VLD1.8      {d0},  [r3]!            // A0
        VLD1.8      {q2},  [r9]!            // B0
        VLD1.8      {d1}, [r12]!            // A1
        VLD1.8      {q3},  [r9]!            // B1
        VLD1.8      {d2}, [r10]!            // A2
        VLD1.8      {q4},  [r9]!            // B2
        VLD1.8      {d3},  [r0]!            // A3
        VLD1.8      {q5},  [r9]!            // B3
        SUBS        r5, r5, 8

        VSDOT.S8    q8, q2, d0[0]
        VSDOT.S8    q9, q3, d0[0]
        VSDOT.S8    q10, q2, d1[0]
        VSDOT.S8    q11, q3, d1[0]
        VSDOT.S8    q12, q2, d2[0]
        VSDOT.S8    q13, q3, d2[0]
        VSDOT.S8    q14, q2, d3[0]
        VSDOT.S8    q15, q3, d3[0]

        VSDOT.S8    q8, q4, d0[1]
        VSDOT.S8    q9, q5, d0[1]
        VSDOT.S8    q10, q4, d1[1]
        VSDOT.S8    q11, q5, d1[1]
        VSDOT.S8    q12, q4, d2[1]
        VSDOT.S8    q13, q5, d2[1]
        VSDOT.S8    q14, q4, d3[1]
        VSDOT.S8    q15, q5, d3[1]
        BHS         1b

        # Is there a remainder?- 4 bytes of A
        ADDS        r5, r5, 8
        BNE         3f

2:
        # QC8 FP32 quantization
        VLD1.8      {q0-q1},  [r9]!

        VCVT.F32.S32    q8,  q8
        VCVT.F32.S32    q9,  q9
        VCVT.F32.S32    q10, q10
        VCVT.F32.S32    q11, q11
        VCVT.F32.S32    q12, q12
        VCVT.F32.S32    q13, q13
        VCVT.F32.S32    q14, q14
        VCVT.F32.S32    q15, q15

        VMUL.F32    q8,  q8, q0             // multiplier
        VMUL.F32    q9,  q9, q1
        VMUL.F32    q10, q10, q0
        VMUL.F32    q11, q11, q1
        VMUL.F32    q12, q12, q0
        VMUL.F32    q13, q13, q1
        VMUL.F32    q14, q14, q0
        VMUL.F32    q15, q15, q1

        VCVTN.S32.F32   q8,  q8
        VCVTN.S32.F32   q9,  q9
        VCVTN.S32.F32   q10, q10
        VCVTN.S32.F32   q11, q11
        VCVTN.S32.F32   q12, q12
        VCVTN.S32.F32   q13, q13
        VCVTN.S32.F32   q14, q14
        VCVTN.S32.F32   q15, q15

        VDUP.16     q0, d13[2]              // output_zero_point

        VQMOVN.S32  d16, q8
        VQMOVN.S32  d17, q9
        VQMOVN.S32  d18, q10
        VQMOVN.S32  d19, q11
        VQMOVN.S32  d20, q12
        VQMOVN.S32  d21, q13
        VQMOVN.S32  d22, q14
        VQMOVN.S32  d23, q15

        VQADD.S16   q8,  q8, q0
        VQADD.S16   q9,  q9, q0
        VQADD.S16   q10, q10, q0
        VQADD.S16   q11, q11, q0

        VDUP.8      q12, d13[6]             // output_min

        VQMOVN.S16  d0,  q8
        VQMOVN.S16  d1,  q9
        VQMOVN.S16  d2, q10
        VQMOVN.S16  d3, q11

        VDUP.8      q13, d13[7]             // output_max

        VMAX.S8     q0, q0, q12
        VMAX.S8     q1, q1, q12

        SUBS        r1, r1, 8

        VMIN.S8     q0, q0, q13
        VMIN.S8     q1, q1, q13

        # Store full 4 x 8
        BLO         4f
        VST1.8      {d0}, [r11], r7
        SUB         r3, r3, r2
        VST1.8      {d1}, [r4], r7
        SUB         r12, r12, r2
        VST1.8      {d2}, [r8], r7
        SUB         r10, r10, r2
        VST1.8      {d3}, [r6], r7
        SUB         r0, r0, r2
        BHI         0b

        VPOP        {d8-d13}
        POP         {r4, r5, r6, r7, r8, r9, r10, r11}
        BX          lr

        # Remainder- 4 bytes of A
        .p2align    3
3:
        VLD1.32     {d0[0]},  [r3]!         // A0
        VLD1.32     {q2},  [r9]!            // B0
        VLD1.32     {d1[0]}, [r12]!         // A1
        VLD1.32     {q3},  [r9]!            // B1
        VLD1.32     {d2[0]}, [r10]!         // A2
        VLD1.32     {d3[0]},  [r0]!         // A3

        VSDOT.S8    q8, q2, d0[0]
        VSDOT.S8    q9, q3, d0[0]
        VSDOT.S8    q10, q2, d1[0]
        VSDOT.S8    q11, q3, d1[0]
        VSDOT.S8    q12, q2, d2[0]
        VSDOT.S8    q13, q3, d2[0]
        VSDOT.S8    q14, q2, d3[0]
        VSDOT.S8    q15, q3, d3[0]
        B           2b

        # Store odd width
        .p2align    3
4:
        TST         r1, 4
        BEQ         5f
        VST1.32     {d0[0]}, [r11]!
        VST1.32     {d1[0]}, [r4]!
        VST1.32     {d2[0]}, [r8]!
        VST1.32     {d3[0]}, [r6]!
        VEXT.8      q0, q0, q0, 4
        VEXT.8      q1, q1, q1, 4
5:
        TST         r1, 2
        BEQ         6f
        VST1.16     {d0[0]}, [r11]!
        VST1.16     {d1[0]}, [r4]!
        VST1.16     {d2[0]}, [r8]!
        VST1.16     {d3[0]}, [r6]!
        VEXT.8      q0, q0, q0, 2
        VEXT.8      q1, q1, q1, 2

6:
        TST         r1, 1
        BEQ         7f
        VST1.8      {d0[0]}, [r11]
        VST1.8      {d1[0]}, [r4]
        VST1.8      {d2[0]}, [r8]
        VST1.8      {d3[0]}, [r6]

7:
        VPOP        {d8-d13}
        POP         {r4, r5, r6, r7, r8, r9, r10, r11}
        BX          lr

END_FUNCTION xnn_qs8_qc8w_gemm_minmax_fp32_ukernel_4x8c4__asm_aarch32_neondot_ld64
#endif  // __APPLE__

#ifdef __ELF__
.section ".note.GNU-stack","",%progbits
#endif

