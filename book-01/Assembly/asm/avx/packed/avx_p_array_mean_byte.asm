include macros.inc

.code

; bool AVX_Packed_Array_Mean_Byte_(const uint8_t* input, uint32_t arrayLength, uint64_t* sum, double* mean)
AVX_Packed_Array_Mean_Byte_ proc frame

_CreateFrame CM_, 0, 64, rbx, r10, r11, r12
_SaveXmmRegs xmm6, xmm7, xmm8, xmm9
_EndProlog

xor eax, eax

test rdx, rdx ; Exit if arrayLenght == 0
jz InvalidArg

test rcx, 0fh ; Exit if not aligned
jnz InvalidArg

; Initializations
vpxor xmm8, xmm8, xmm8 ; xmm8 = last sum temp register (4 int32_t)
vpxor xmm9, xmm9, xmm9 ; xmm9 = packed zeros for conversions
mov r12, rdx ; Save arrayLength to final calculation

cmp rdx, 32 ; Do one by one if we can't fill the two xmm registers needed
jb OneByOne

@@:
vmovdqa xmm0, xmmword ptr [rcx]
vmovdqa xmm1, xmmword ptr [rcx+16]

; This will convert uint8_t to uint16_t.
; Needed to avoid truncation.
vpunpcklbw xmm2, xmm0, xmm9
vpunpckhbw xmm3, xmm0, xmm9
vpunpcklbw xmm4, xmm1, xmm9
vpunpckhbw xmm5, xmm1, xmm9

; Sum everything.
vpaddw xmm0, xmm2, xmm3
vpaddw xmm1, xmm4, xmm5
vpaddw xmm6, xmm0, xmm1 ; xmm6 = 8 uint16_t

; As we're going to sum this result with the
; next result, we need to convert it to uint32_t
; because uint16_t + uint16_t may overflow.
vpunpcklwd xmm1, xmm6, xmm9
vpunpckhwd xmm0, xmm6, xmm9
vpaddd xmm8, xmm0, xmm1 ; xmm8 = 4 uint32_t

add rcx, 32 * type byte ; Advance to next 32 numbers
sub rdx, 32
cmp rdx, 32
jae @B

; Sum the 4 integers in the temp sum register.
vpextrd eax, xmm8, 0
vpextrd r10d, xmm8, 1
add rax, r10 ; Use rax as uint32_t + uint32_t may overflow
vpextrd r10d, xmm8, 2
vpextrd r11d, xmm8, 3
add r10, r11
add rax, r10

OneByOne:
test rdx, rdx
jz Done

mov bl, byte ptr [rcx]
add rax, rbx
add rcx, type byte ; Advance to the next number
dec rdx
jnz OneByOne

Done:

mov qword ptr [r8], rax ; Save the final sum

; Calculate mean.
vcvtsi2sd xmm0, xmm0, rax ; Convert rax to double
vcvtsi2sd xmm1, xmm1, r12 ; Convert saved arrayLength do double
vdivsd xmm2, xmm0, xmm1

vmovsd real8 ptr [r9], xmm2 ; Save mean value

mov rax, 1

InvalidArg:

_RestoreXmmRegs xmm6, xmm7, xmm8, xmm9
_DeleteFrame rbx, r10, r11, r12

ret

AVX_Packed_Array_Mean_Byte_ endp

end