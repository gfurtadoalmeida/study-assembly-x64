include	macros.inc

.code

; bool AVX_Packed_Y_Calc_Correlation_Coefficient_(const double* x, const double* y, size_t arrayLength, double sums[5], double epsilon, double* rho);
AVX_Packed_Y_Calc_Correlation_Coefficient_ proc frame
_CreateFrame CC_, 0,32
_SaveXmmRegs xmm6, xmm7
_EndProlog

or r8, r8
jz InvalidArg

test rcx, 1fh
jnz InvalidArg

test rdx, 1fh
jnz InvalidArg

; Initialize sum variables to zero
vxorpd ymm3, ymm3, ymm3
vxorpd ymm4, ymm4, ymm4
vxorpd ymm5, ymm5, ymm5
vxorpd ymm6, ymm6, ymm6
vxorpd ymm7, ymm7, ymm7
mov r10, r8 ; Save arrayLength

; Jump if arrayLength >= 1 && arrayLength <= 3
cmp r8, 4
jb LP2

; Calculate intermediate packed sum variables
LP1:
vmovapd ymm0, ymmword ptr [rcx]
vmovapd ymm1, ymmword ptr [rdx]

vaddpd ymm3, ymm3, ymm0 ; Update packed sum_x
vaddpd ymm4, ymm4, ymm1 ; Update packed sum_y

vmulpd ymm2, ymm0, ymm1 ; ymm2 = packed xy values
vaddpd ymm7, ymm7, ymm2 ; Update packed sum_xy

vmulpd ymm0, ymm0, ymm0 ; ymm0 = packed xx values
vmulpd ymm1, ymm1, ymm1 ; ymm1 = packed yy values

vaddpd ymm5, ymm5, ymm0 ; Update packed sum_xx
vaddpd ymm6, ymm6, ymm1 ; Update packed sum_yy

add rcx, 32
add rdx, 32
sub r8, 4
cmp r8, 4
jae LP1

or r8, r8
jz FinalSum

; Update sum variables with final x & y values
LP2:
vmovsd xmm0, real8 ptr [rcx] ; xmm0[63:0] = x[i], ymm0[255:64] = 0
vmovsd xmm1, real8 ptr [rdx] ; xmm1[63:0] = y[i], ymm1[255:64] = 0

vaddpd ymm3, ymm3, ymm0 ; Update packed sum_x
vaddpd ymm4, ymm4, ymm1 ; Update packed sum_y

vmulpd ymm2, ymm0, ymm1 ; ymm2 = packed xy values
vaddpd ymm7, ymm7, ymm2 ; Update packed sum_xy

vmulpd ymm0, ymm0, ymm0 ; ymm0 = packed xx values
vmulpd ymm1, ymm1, ymm1 ; ymm1 = packed yy values
vaddpd ymm5, ymm5, ymm0 ; Update packed sum_xx
vaddpd ymm6, ymm6, ymm1 ; Update packed sum_yy

add rcx, 8
add rdx, 8
sub r8, 1
jnz LP2

; Calculate final sum variables
FinalSum:
vextractf128 xmm0, ymm3, 1
vaddpd xmm1, xmm0, xmm3
vhaddpd xmm3, xmm1, xmm1 ; xmm3[63:0] = sum_x

vextractf128 xmm0, ymm4, 1
vaddpd xmm1, xmm0, xmm4
vhaddpd xmm4, xmm1, xmm1 ; xmm4[63:0] = sum_y

vextractf128 xmm0, ymm5, 1
vaddpd xmm1, xmm0, xmm5
vhaddpd xmm5, xmm1, xmm1 ; xmm5[63:0] = sum_xx

vextractf128 xmm0, ymm6, 1
vaddpd xmm1, xmm0, xmm6
vhaddpd xmm6, xmm1, xmm1 ; xmm6[63:0] = sum_yy

vextractf128 xmm0, ymm7, 1
vaddpd xmm1, xmm0, xmm7
vhaddpd xmm7, xmm1, xmm1 ; xmm7[63:0] = sum_xy

; Save final sum variables
vmovsd real8 ptr [r9], xmm3    ; Save sum_x
vmovsd real8 ptr [r9+8], xmm4  ; Save sum_y
vmovsd real8 ptr [r9+16], xmm5 ; Save sum_xx
vmovsd real8 ptr [r9+24], xmm6 ; Save sum_yy
vmovsd real8 ptr [r9+32], xmm7 ; Save sum_xy

; Calculate rho numerator
; rho_num = n * sum_xy - sum_x * sum_y

vcvtsi2sd xmm2, xmm2, r10 ; xmm2 = arrayLength
vmulsd xmm0, xmm2, xmm7   ; xmm0 = arrayLength * sum_xy
vmulsd xmm1, xmm3, xmm4   ; xmm1 = sum_x * sum_y
vsubsd xmm7, xmm0, xmm1   ; xmm7 = rho_num

; Calculate rho denominator
; t1 = sqrt(n * sum_xx - sum_x * sum_x)
; t2 = sqrt(n * sum_yy - sum_y * sum_y)
; rho_den = t1 * t2

vmulsd xmm0, xmm2, xmm5  ; xmm0 = arrayLength * sum_xx
vmulsd xmm3, xmm3, xmm3  ; xmm3 = sum_x * sum_x
vsubsd xmm3, xmm0, xmm3  ; xmm3 = arrayLength * sum_xx - sum_x * sum_x
vsqrtsd xmm3, xmm3, xmm3 ; xmm3 = t1

vmulsd xmm0, xmm2, xmm6  ; xmm0 = arrayLength * sum_yy
vmulsd xmm4, xmm4, xmm4  ; xmm4 = sum_y * sum_y
vsubsd xmm4, xmm0, xmm4  ; xmm4 = arrayLength * sum_yy - sum_y * sum_y
vsqrtsd xmm4, xmm4, xmm4 ; xmm4 = t2

vmulsd xmm0, xmm3, xmm4  ; xmm0 = rho_den

; Calculate and save final rho
xor eax, eax
vcomisd xmm0, real8 ptr [rbp+CC_OffsetStackArgs] ; rho_den < epsilon?
setae al  ; Success code
jb BadRho ; Jump if rho_den < epsilon
vdivsd xmm1, xmm7, xmm0 ; xmm1 = rho

SaveRho:
mov rdx, [rbp+CC_OffsetStackArgs+type real8] ; rdx = ptr to rho
vmovsd real8 ptr [rdx], xmm1 ; Save rho

Done:
vzeroupper
_RestoreXmmRegs xmm6, xmm7
_DeleteFrame
ret

BadRho:
vxorpd xmm1, xmm1, xmm1 ; rho = 0
jmp SaveRho

InvalidArg:
xor eax, eax
jmp Done

AVX_Packed_Y_Calc_Correlation_Coefficient_ endp

end