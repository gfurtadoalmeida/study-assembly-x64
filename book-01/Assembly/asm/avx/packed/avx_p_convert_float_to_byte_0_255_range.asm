include macros.inc
include comparison_predicates.inc

.const
	align 16

	FloatToUint8Min real4 0.0, 0.0, 0.0, 0.0
	FloatToUint8Max real4 1.0, 1.0, 1.0, 1.0
	FloatToUint8Scale real4 255.0, 255.0, 255.0, 255.0
	Uint8Min dword 0
	Uint8Max dword 255
.code

; bool AVX_Packed_Convert_Float_To_Byte_0_255_Range(const float* input, uint32_t arrayLength, uint8_t * output);

AVX_Packed_Convert_Float_To_Byte_0_255_Range proc frame

_CreateFrame F2U_, 0, 96
_SaveXmmRegs xmm6, xmm7, xmm12, xmm13, xmm14, xmm15
_EndProlog

xor eax, eax

test rdx, rdx ; Exit if arrayLenght == 0
jz InvalidArg

test rcx, 0fh ; Exit if not aligned
jnz InvalidArg

test r8, 0fh ; Exit if not aligned
jnz InvalidArg

; Initializations
mov r9, rdx
shr r9d, 2             ; arrayLength >> 2 = arrayLength % 4 = Number of blocks with 4 items
vpxor xmm1, xmm1, xmm1 ; Just zeros
vmovaps xmm13, xmmword ptr [FloatToUint8Scale]
vmovaps xmm14, xmmword ptr [FloatToUint8Min]
vmovaps xmm15, xmmword ptr [FloatToUint8Max]

test r9, r9 ; Do one by one number of blocks is zero
jz OneByOne

@@:
vmovaps xmm0, xmmword ptr [rcx] ; xmm0 have 4 floats

; Values < 0.0F = 0.0F
vcmpps xmm1, xmm0, xmm14, CMP_LT
vandnps xmm2, xmm1, xmm0

; Values > 1.0F = 1.0F
vcmpps xmm3, xmm2, xmm15, CMP_GT
vandps xmm4, xmm3, xmm15
vandnps xmm5, xmm3, xmm2
vorps xmm6, xmm5, xmm4

; Values = values * 255.0F
vmulps xmm7, xmm6, xmm13

; Convert 4 floats to 4 int32_t
vcvtps2dq xmm0, xmm7

; Convert 4 int32_t to 8 uint16_t
;        127                                                           0
; xmm1 = xmm0[3] xmm0[2] xmm0[1] xmm0[0] xmm0[3] xmm0[2] xmm0[1] xmm0[0]
; It's safe to do because the values will never go beyond 255
vpackusdw xmm1, xmm0, xmm0

; Convert 8 uint16_t to 16 uint8_t
;        127                                                              0
; xmm1 = xmm0[3] xmm0[2] xmm0[1] xmm0[0] ... xmm0[3] xmm0[2] xmm0[1] xmm0[0]
; It's safe to do because the values will never go beyond 255
vpackuswb xmm2, xmm1, xmm1

vpextrd eax, xmm2, 0 ; Get the 4 uint_8 converted number (32 bits)
mov dword ptr [r8], eax

add rcx, 16 ; Advance to the next 16 bytes (4 items * sizeof(float))
add r8, type dword
sub rdx, 4
sub r9d, 1
jnz @B

OneByOne:
test rdx, rdx
jz Done

; Get next number.
; Multiply it by uint8_t max value.
; Convert it to int32_t.
vmovss xmm1, real4 ptr [rcx]
vmulss xmm2, xmm1, real4 ptr [FloatToUint8Scale]
vcvtss2si eax, xmm2

; Value < 0 = 0
cmp eax, 0
cmovb eax, dword ptr [Uint8Min]

; Value > 255 = 255
cmp eax, 255
cmova eax, dword ptr [Uint8Max]

mov byte ptr [r8], al

add rcx, type real4 ; Advance to the next number
add r8, type byte
dec rdx
jnz OneByOne

Done:
mov rax, 1

InvalidArg:

_RestoreXmmRegs xmm6, xmm7, xmm8, xmm9, xmm10, xmm11, xmm12, xmm13, xmm14, xmm15
_DeleteFrame

ret

AVX_Packed_Convert_Float_To_Byte_0_255_Range endp

end