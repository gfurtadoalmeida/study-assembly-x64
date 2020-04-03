include macros.inc

.const
	align 16

	Uint8ToFloat real4 255.0, 255.0, 255.0, 255.0

.code

; bool AVX_Packed_Convert_Byte_To_Float_0_1_Range_(const uint8_t * input, uint32_t arrayLength, float* output);
AVX_Packed_Convert_Byte_To_Float_0_1_Range_ proc frame 

_CreateFrame U2F_, 0, 160
_SaveXmmRegs xmm6, xmm7, xmm8, xmm9, xmm10, xmm11, xmm12, xmm13, xmm14, xmm15
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
shr r9d, 5 ; arrayLength >> 5 = arrayLength % 32 = Number of blocks with 32 items
vmovaps xmm6, xmmword ptr [Uint8ToFloat] ; uint8_t max values for normalization
vpxor xmm7, xmm7, xmm7                   ; Just zeros

test r9, r9 ; Do one by one number of blocks is zero
jz OneByOne

@@:
; xmm0 + xmm1 32 uint8_t
vmovdqa xmm0, xmmword ptr [rcx]
vmovdqa xmm1, xmmword ptr [rcx+type xmmword]

; Convert xmm0 to uint16_t
vpunpcklbw xmm2, xmm0, xmm7
vpunpckhbw xmm3, xmm0, xmm7
vpunpcklwd xmm8, xmm2, xmm7
vpunpckhwd xmm9, xmm2, xmm7
vpunpcklwd xmm10, xmm3, xmm7
vpunpckhwd xmm11, xmm3, xmm7

; Convert xmm1 to uint16_t
vpunpcklbw xmm2, xmm1, xmm7
vpunpckhbw xmm3, xmm1, xmm7
vpunpcklwd xmm12, xmm2, xmm7
vpunpckhwd xmm13, xmm2, xmm7
vpunpcklwd xmm14, xmm3, xmm7
vpunpckhwd xmm15, xmm3, xmm7

; Convert to uint16_t to float
vcvtdq2ps xmm8, xmm8
vcvtdq2ps xmm9, xmm9
vcvtdq2ps xmm10, xmm10
vcvtdq2ps xmm11, xmm11
vcvtdq2ps xmm12, xmm12
vcvtdq2ps xmm13, xmm13
vcvtdq2ps xmm14, xmm14
vcvtdq2ps xmm15, xmm15

; At this moment we have a raw conversion:
;     uint8_t 255 => float 255.0F
; What we need is a value between 0 and 1:
;     uint8_t 0 => float 0.0F
;     uint8_t 255 => float 1.0F
; We do that dividing the raw value by the max value
; for uint8_t.

; Each vmovaps will move the 8 floats (16 bytes) in each
; xmm register to destination.
; 8 copies * 16 bytes = 128 bytes copied.

vdivps xmm0, xmm8, xmm6
vmovaps xmmword ptr [r8], xmm0
vdivps xmm1, xmm9, xmm6
vmovaps xmmword ptr [r8+16], xmm1
vdivps xmm2, xmm10, xmm6
vmovaps xmmword ptr [r8+32], xmm2
vdivps xmm3, xmm11, xmm6
vmovaps xmmword ptr [r8+48], xmm3
vdivps xmm0, xmm12, xmm6
vmovaps xmmword ptr [r8+64], xmm0
vdivps xmm1, xmm13, xmm6
vmovaps xmmword ptr [r8+80], xmm1
vdivps xmm2, xmm14, xmm6
vmovaps xmmword ptr [r8+96], xmm2
vdivps xmm3, xmm15, xmm6
vmovaps xmmword ptr [r8+112], xmm3

add rcx, 32 ; Advance to the next 32 bytes (32 items * sizeof(uint8_t))
add r8, 128 ; We've just copied 128 bytes do output, so now we advance.
sub rdx, 32
sub r9d, 1
jnz @B

OneByOne:
test rdx, rdx
jz Done

mov al, byte ptr [rcx]
vcvtsi2ss xmm0, xmm0, eax
vdivss xmm1, xmm0, xmm6
vmovss real4 ptr [r8], xmm1

add rcx, type byte ; Advance to the next number
add r8, type real4
dec rdx
jnz OneByOne

Done:
mov rax, 1

InvalidArg:

_RestoreXmmRegs xmm6, xmm7, xmm8, xmm9, xmm10, xmm11, xmm12, xmm13, xmm14, xmm15
_DeleteFrame

ret

AVX_Packed_Convert_Byte_To_Float_0_1_Range_ endp

end