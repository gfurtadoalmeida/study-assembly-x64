include macros.inc

.code

_Mat4x4TransposeF64 macro

; Input Matrix       Output Matrix
; --------------------------------------
;       255       0         255       0
;       -----------         -----------
; ymm0  a3 a2 a1 a0 | ymm0  d0 c0 b0 a0
; ymm1  b3 b2 b1 b0 | ymm1  d1 c1 b1 a1
; ymm2  c3 c2 c1 c0 | ymm2  d2 c2 b2 a2
; ymm3  d3 d2 d1 d0 | ymm3  d3 c3 b3 a3
;
;       0       255
;       -----------
; ymm0  a0 b0 c0 d0
; ymm1  a1 b1 c1 d1
; ymm2  a2 b2 c2 d2
; ymm3  a3 b3 c3 d3

; vunpcklps des, srcA, srcB
;
; des = srcB[1], srcA[1], srcB[0], srcA[0]

vunpcklpd ymm4, ymm0, ymm1 ; ymm4 = b1 a1 b0 a0
vunpckhpd ymm5, ymm0, ymm1 ; ymm5 = b3 a3 b2 a2
vunpcklpd ymm6, ymm2, ymm3 ; ymm6 = d1 c1 d0 c0
vunpckhpd ymm7, ymm2, ymm3 ; ymm7 = d3 c3 d2 c2

; vperm2f128 des, srcA, srcB, control
;
; control = 7    3    0
;           -----------
;     B ==> 0000 | 0000 <== A
; 
; A: des[0:127]
;    00 = srcA[0:127]
;    01 = srcA[128:255]
;    10 = srcB[0:127]
;    11 = srcB[128:255]
;    1xxx = zeros
;
; B: des[128:255]
;    00 = srcA[0:127]
;    01 = srcA[128:255]
;    10 = srcB[0:127]
;    11 = srcB[128:255]
;    1xxx = zeros

vperm2f128 ymm0, ymm4, ymm6, 00100000b ; ymm0 = d0 c0 b0 a0
vperm2f128 ymm1, ymm5, ymm7, 00100000b ; ymm1 = d1 c1 b1 a1
vperm2f128 ymm2, ymm4, ymm6, 00110001b ; ymm2 = d2 c2 b2 a2
vperm2f128 ymm3, ymm5, ymm7, 00110001b ; ymm3 = d3 c3 b2 a3

endm

; void AVX_Packed_Y_Matrix_Transpose_Double_(double* input, const double* result)
AVX_Packed_Y_Matrix_Transpose_Double_ proc frame

_CreateFrame MT_, 0, xmmword*2 ; Space for xmm6 and xmm7
_SaveXmmRegs xmm6, xmm7
_EndProlog

vmovapd ymm0, ymmword ptr[rcx]    ; ymm0 = input[0:3]
vmovapd ymm1, ymmword ptr[rcx+32] ; ymm1 = input[4:7]
vmovapd ymm2, ymmword ptr[rcx+64] ; ymm2 = input[8:11]
vmovapd ymm3, ymmword ptr[rcx+96] ; ymm3 = input[12:15]

_Mat4x4TransposeF64

vmovapd ymmword ptr [rdx], ymm0    ; result[0:3] = ymm0
vmovapd ymmword ptr [rdx+32], ymm1 ; result[4:7] = ymm1
vmovapd ymmword ptr [rdx+64], ymm2 ; result[8:11] = ymm2
vmovapd ymmword ptr [rdx+96], ymm3 ; result[12:15] = ymm3

_RestoreXmmRegs xmm6, xmm7
_DeleteFrame

vzeroupper

ret

AVX_Packed_Y_Matrix_Transpose_Double_ endp

end