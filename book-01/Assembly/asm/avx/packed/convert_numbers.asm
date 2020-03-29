.code

; bool AVX_Packed_Convert_Numbers_(const XmmVal & source, const XmmVal & destination, CvtOp operation)
AVX_Packed_Convert_Numbers_ proc

mov eax, 1 ; Success

; Make sure cvt_op is valid, then jump to target conversion code
cmp r8d, CvtOpJumpTableCount         ; Is r8d a valid jump table index ?
jae BadCvtOp                         ; r9d is invalid if >= jump table count

lea r9, qword ptr [CvtOpJumpTable]   ; Get jumpt table address relative to RIP
lea r9, qword ptr [r9+r8*type qword] ; Find correct jump address
jmp qword ptr [r9]                   ; Jump to specified conversion

; int32 <-> float/double

I32_F32:
vmovdqa xmm0, xmmword ptr [rcx]
vcvtdq2ps xmm1, xmm0
vmovaps xmmword ptr [rdx], xmm1
ret

F32_I32:
vmovaps xmm0, xmmword ptr [rcx]
vcvtps2dq xmm1, xmm0
vmovdqa xmmword ptr [rdx], xmm1
ret

I32_F64:
vmovdqa xmm0, xmmword ptr [rcx]
vcvtdq2pd xmm1, xmm0
vmovapd xmmword ptr [rdx], xmm1
ret

F64_I32:
vmovapd xmm0, xmmword ptr [rcx]
vcvtpd2dq xmm1, xmm0
vmovdqa xmmword ptr [rdx], xmm1
ret

; int64 <-> float/double
; AVX does not support this conversions.
; They were added only in AVX-512
I64_F32:
F32_I64:
I64_F64:
F64_I64:
jmp BadCvtOp

; float <-> double

F32_F64:
vmovaps xmm0, xmmword ptr [rcx]
vcvtps2pd xmm1, xmm0
vmovapd xmmword ptr [rdx], xmm1
ret

F64_F32:
vmovapd xmm0, xmmword ptr [rcx]
vcvtpd2ps xmm1, xmm0
vmovaps xmmword ptr [rdx], xmm1
ret

BadCvtOp:
xor eax, eax
ret

align 8
; Must have the same order as defined in the 
; "CvtOp" enum at "avx.h"
CvtOpJumpTable equ $ 
    qword I32_F32
    qword F32_I32
    qword I32_F64
    qword F64_I32
    qword I64_F32
    qword F32_I64
    qword I64_F64
    qword F64_I64
    qword F32_F64
    qword F64_F32
CvtOpJumpTableCount equ ($-CvtOpJumpTable)/size qword

AVX_Packed_Convert_Numbers_ endp

end