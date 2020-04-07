include macros.inc

.code

; void AVX_Packed_Y_Matrix_Multiplication_Double_(const double* a, const double* b, double* result);
AVX_Packed_Y_Matrix_Multiplication_Double_ proc frame

_CreateFrame MM_, 0, xmmword*2 ; Space for xmm6 and xmm7
_SaveXmmRegs xmm6, xmm7
_EndProlog

vmovapd ymm0, ymmword ptr [rdx]    ; ymm0 = b.row_0
vmovapd ymm1, ymmword ptr [rdx+32] ; ymm1 = b.row_1
vmovapd ymm2, ymmword ptr [rdx+64] ; ymm2 = b.row_2
vmovapd ymm3, ymmword ptr [rdx+96] ; ymm3 = b.row_3

xor r9, r9

;        255                 127                   96                    63                    0
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
vbroadcastsd ymm4, real8 ptr [rcx+r9]    ; ymm4 = a[row][0]
vbroadcastsd ymm5, real8 ptr [rcx+r9+8]  ; ymm5 = a[row][1]
vbroadcastsd ymm6, real8 ptr [rcx+r9+16] ; ymm6 = a[row][2]
vbroadcastsd ymm7, real8 ptr [rcx+r9+24] ; ymm7 = a[row][3]

vmulpd ymm4, ymm4, ymm0 ; ymm4 = a.[row][0] * b.row_0
vmulpd ymm5, ymm5, ymm1 ; ymm5 = a.[row][1] * b.row_1
vmulpd ymm6, ymm6, ymm2 ; ymm6 = a.[row][2] * b.row_2
vmulpd ymm7, ymm7, ymm3 ; ymm7 = a.[row][3] * b.row_3

vaddpd ymm4, ymm4, ymm5
vaddpd ymm6, ymm6, ymm7
vaddpd ymm4, ymm4, ymm6

vmovapd ymmword ptr[r8+r9], ymm4
add r9, type ymmword ; Advance to the next row
cmp r9, 96
jle @B

_RestoreXmmRegs xmm6, xmm7
_DeleteFrame

vzeroupper

ret

AVX_Packed_Y_Matrix_Multiplication_Double_ endp

end