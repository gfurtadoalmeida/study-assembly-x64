include macros.inc

.code

_Mat4x4TransposeF32 macro

; Input Matrix       Output Matrix
; --------------------------------------
;       127       0         127       0
;       -----------         -----------
; xmm0  a3 a2 a1 a0 | xmm4  d0 c0 b0 a0
; xmm1  b3 b2 b1 b0 | xmm5  d1 c1 b1 a1
; xmm2  c3 c2 c1 c0 | xmm6  d2 c2 b2 a2
; xmm3  d3 d2 d1 d0 | xmm7  d3 c3 b3 a3
;
;       0       127
;       -----------
; xmm4  a0 b0 c0 d0
; xmm5  a1 b1 c1 d1
; xmm6  a2 b2 c2 d2
; xmm7  a3 b3 c3 d3

; vunpcklps des, srcA, srcB
;
; des = srcB[1], srcA[1], srcB[0], srcA[0]

vunpcklps xmm6, xmm0, xmm1 ; xmm6 = b1 a1 b0 a0
vunpckhps xmm0, xmm0, xmm1 ; xmm0 = b3 a3 b2 a2
vunpcklps xmm7, xmm2, xmm3 ; xmm7 = d1 c1 d0 c0
vunpckhps xmm1, xmm2, xmm3 ; xmm1 = d3 c3 d2 c2

; vmovlhps des, srcA, srcB
;
; des = srcB[1], srcB[0], srcA[1], srcA[0]

vmovlhps xmm4, xmm6, xmm7 ; xmm4 = d0 c0 b0 a0
vmovhlps xmm5, xmm7, xmm6 ; xmm5 = d1 c1 b1 a1
vmovlhps xmm6, xmm0, xmm1 ; xmm6 = d2 c2 b2 a2
vmovhlps xmm7, xmm1, xmm0 ; xmm7 = d3 c3 b2 a3

endm

; void AVX_Packed_Matrix_Transpose_Float_(float* input, const float* result)
AVX_Packed_Matrix_Transpose_Float_ proc frame

_CreateFrame MT_, 0, xmmword*2 ; Space for xmm6 and xmm7
_SaveXmmRegs xmm6, xmm7
_EndProlog

vmovaps xmm0, xmmword ptr[rcx]    ; xmm0 = input[0:3]
vmovaps xmm1, xmmword ptr[rcx+16] ; xmm1 = input[4:7]
vmovaps xmm2, xmmword ptr[rcx+32] ; xmm2 = input[8:11]
vmovaps xmm3, xmmword ptr[rcx+48] ; xmm3 = input[12:15]

_Mat4x4TransposeF32

vmovaps xmmword ptr [rdx], xmm4    ; result[0:3] = xmm4
vmovaps xmmword ptr [rdx+16], xmm5 ; result[4:7] = xmm5
vmovaps xmmword ptr [rdx+32], xmm6 ; result[8:11] = xmm6
vmovaps xmmword ptr [rdx+48], xmm7 ; result[12:15] = xmm7

Done:
_RestoreXmmRegs xmm6, xmm7
_DeleteFrame

ret

AVX_Packed_Matrix_Transpose_Float_ endp

end