.code

; bool AVX_Packed_Shift_Integers_(const XmmVal & input, XmmVal & results, ShiftOp shift_op, unsigned int count);
AVX_Packed_Shift_Integers_ proc

mov r8d, r8d ; Just to zero extend
cmp r8, ShiftOpJumpTableCount
jae BadShiftOp

vmovdqa xmm0, xmmword ptr [rcx] ; xmm0 = input
vmovd xmm1, r9d ; xmm1 = shift count
mov eax, 1
mov r10, ShiftOpJumpTable
jmp qword ptr [r10+r8*type qword]

U16_LOG_LEFT:
vpsllw xmm2, xmm0, xmm1
vmovdqa xmmword ptr [rdx], xmm2
ret

U16_LOG_RIGHT:
vpsrlw xmm2, xmm0, xmm1
vmovdqa xmmword ptr [rdx], xmm2
ret

U16_ARITH_RIGHT:
vpsraw xmm2, xmm0, xmm1
vmovdqa xmmword ptr [rdx], xmm2
ret

U32_LOG_LEFT:
vpslld xmm2, xmm0, xmm1
vmovdqa xmmword ptr [rdx], xmm2
ret

U32_LOG_RIGHT:
vpsrld xmm2, xmm0, xmm1
vmovdqa xmmword ptr [rdx], xmm2
ret

U32_ARITH_RIGHT:
vpsrad xmm2, xmm0, xmm1
vmovdqa xmmword ptr [rdx], xmm2
ret

BadShiftOp:
xor rax, rax
vpxor xmm0, xmm0, xmm0
vmovdqa xmmword ptr [rdx], xmm0
ret

align 8
; Must have the same order as defined in the 
; "CvtOp" enum at "avx.h"
ShiftOpJumpTable equ $ 
    qword U16_LOG_LEFT
    qword U16_LOG_RIGHT
    qword U16_ARITH_RIGHT
    qword U32_LOG_LEFT
    qword U32_LOG_RIGHT
    qword U32_ARITH_RIGHT
ShiftOpJumpTableCount equ ($-ShiftOpJumpTable)/size qword

AVX_Packed_Shift_Integers_ endp

end