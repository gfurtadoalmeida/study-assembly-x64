.code

; bool AVX_Scalar_Convert_Number_(Uval * source, Uval * destination, CvtOp operation)
AVX_Scalar_Convert_Number_ proc

mov eax, 1 ; Success

; Make sure cvt_op is valid, then jump to target conversion code
cmp r8d, CvtOpJumpTableCount         ; Is r8d a valid jump table index ?
jae BadCvtOp                         ; r9d is invalid if >= jump table count

lea r9, qword ptr [CvtOpJumpTable]   ; Get jumpt table address relative to RIP
lea r9, qword ptr [r9+r8*type qword] ; Find correct jump address
jmp qword ptr [r9]                   ; Jump to specified conversion

; int32 <-> float/double

I32_F32:
mov r9d, dword ptr [rcx]
vcvtsi2ss xmm0, xmm0, r9d
vmovss real4 ptr [rdx], xmm0
ret

F32_I32:
vmovss xmm0, real4 ptr [rcx]
vcvtss2si r9d, xmm0
mov real4 ptr [rdx], r9d
ret

I32_F64:
mov r9d, dword ptr [rcx]
vcvtsi2sd xmm0, xmm0, r9d
vmovsd real8 ptr [rdx], xmm0
ret

F64_I32:
vmovsd xmm0, real8 ptr [rcx]
vcvtsd2si r9, xmm0
mov dword ptr [rdx], r9d
ret

; int64 <-> float/double

I64_F32:
mov r9, qword ptr [rcx]
vcvtsi2ss xmm0, xmm0, r9
vmovss real4 ptr [rdx], xmm0
ret

F32_I64:
vmovss xmm0, real4 ptr [rcx]
vcvtss2si r9, xmm0
mov qword ptr [rdx], r9
ret

I64_F64:
mov r9, qword ptr [rcx]
vcvtsi2sd xmm0, xmm0, r9
vmovsd real8 ptr [rdx], xmm0
ret

F64_I64:
vmovsd xmm0, real8 ptr [rcx]
vcvtsd2si r9, xmm0
mov qword ptr [rdx], r9
ret

; float <-> double

F32_F64:
vmovss xmm0, real4 ptr [rcx]
vcvtss2sd xmm1, xmm1, xmm0
vmovsd real8 ptr [rdx], xmm1
ret

F64_F32:
vmovsd xmm0, real8 ptr [rcx]
vcvtsd2ss xmm1, xmm1, xmm0
vmovss real4 ptr [rdx], xmm1
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

AVX_Scalar_Convert_Number_ endp

end