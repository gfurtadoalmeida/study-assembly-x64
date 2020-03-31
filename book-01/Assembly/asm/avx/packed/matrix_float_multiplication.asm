include macros.inc

.code

; void AVX_Packed_Matrix_Float_Multiplication_(const float* a, const float* b, float* result)
AVX_Packed_Matrix_Float_Multiplication_ proc frame

_CreateFrame MM_, 0, xmmword*2 ; Space for xmm6 and xmm7
_SaveXmmRegs xmm6, xmm7
_EndProlog

vmovaps xmm0, xmmword ptr [rdx]    ; xmm0 = b.row_0
vmovaps xmm1, xmmword ptr [rdx+16] ; xmm1 = b.row_1
vmovaps xmm2, xmmword ptr [rdx+32] ; xmm2 = b.row_2
vmovaps xmm3, xmmword ptr [rdx+48] ; xmm3 = b.row_3

xor r9, r9

;        127              95                 63                 31                 0
; xmm4 = a[row][0] * b[0][3] | a[row][0] * b[0][2] | a[row][0] * b[0][1] | a[row][0] * b[0][0] |
;                  +                     +                     +                     +
; xmm5 = a[row][1] * b[1][3] | a[row][1] * b[1][2] | a[row][1] * b[1][1] | a[row][1] * b[1][0] |
;                  +                     +                     +                     +
; xmm6 = a[row][2] * b[2][3] | a[row][2] * b[2][2] | a[row][2] * b[2][1] | a[row][2] * b[2][0] |
;                  +                     +                     +                     +
; xmm7 = a[row][3] * b[3][3] | a[row][3] * b[3][2] | a[row][3] * b[3][1] | a[row][3] * b[3][0] |
;                  =                     =                     =                     =
; res  =        [row][3]     |     res[row][2]     |     res[row][1]     |     res[row][0]     |

@@:
vbroadcastss xmm4, real4 ptr [rcx+r9]    ; xmm4 = a[row][0]
vbroadcastss xmm5, real4 ptr [rcx+r9+4]  ; xmm5 = a[row][1]
vbroadcastss xmm6, real4 ptr [rcx+r9+8]  ; xmm6 = a[row][2]
vbroadcastss xmm7, real4 ptr [rcx+r9+12] ; xmm7 = a[row][3]

vmulps xmm4, xmm4, xmm0 ; xmm4 = a.[row][0] * b.row_0
vmulps xmm5, xmm5, xmm1 ; xmm5 = a.[row][1] * b.row_1
vmulps xmm6, xmm6, xmm2 ; xmm6 = a.[row][2] * b.row_2
vmulps xmm7, xmm7, xmm3 ; xmm7 = a.[row][3] * b.row_3

vaddps xmm4, xmm4, xmm5
vaddps xmm6, xmm6, xmm7
vaddps xmm4, xmm4, xmm6

vmovaps xmmword ptr[r8+r9], xmm4
add r9, type xmmword ; Advance to the next row
cmp r9, 48
jle @B

_RestoreXmmRegs xmm6, xmm7
_DeleteFrame

ret

AVX_Packed_Matrix_Float_Multiplication_ endp

end