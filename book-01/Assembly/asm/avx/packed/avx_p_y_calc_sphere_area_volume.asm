include macros.inc
include comparison_predicates.inc

.const
	; Necessary as AVX does not support immediate values.

	PI real4 3.14159265358979323846
	NUMBER_3 real4 3.0
	NUMBER_4 real4 4.0

.code

; void AVX_Packed_Y_Calc_Sphere_Area_Volume_(const float* radius, uint32_t arrayLength, float* areaa, float* volumea, float qnanValue)
AVX_Packed_Y_Calc_Sphere_Area_Volume_ proc frame

_CreateFrame CC_, 0, 64, r10
_SaveXmmRegs xmm6, xmm7, xmm8, xmm9
_EndProlog

; Initialization
vbroadcastss ymm8, xmm0                 ; QNAN
vbroadcastss ymm0, real4 ptr [NUMBER_4] ; 4
vbroadcastss ymm1, real4 ptr [PI]       ; PI
vmulps ymm6, ymm0, ymm1                 ; 4*PI
vbroadcastss ymm7, real4 ptr [NUMBER_3] ; 3
vxorps ymm9, ymm9, ymm9                 ; 0

xor eax, eax ; Offset
mov r10, rdx
shr r10, 3   ; arrayLength % 3 = num of blocks with 8 radius
jz OneByOne

; Area = 4 * pi * radius^2
; Volume = (area * radius) / 3
@@:
vmovdqa ymm0, ymmword ptr [rcx+rax]
vmulps ymm2, ymm6, ymm0 ; (4 * PI) * radius
vmulps ymm3, ymm2, ymm0 ; [(4 * PI) * radius] * radius

; X < 0  = FFFFFFFFh
; X >= 0 = 00000000h
vcmpps ymm1, ymm0, ymm9, CMP_LT_OS ; Any result < 0.0F ?

vandps ymm4, ymm1, ymm8  ; area >= 0.0F = 0.0F | area < 0.0F = QNAN
vandnps ymm5, ymm1, ymm3 ; area >= 0.0F = area | area < 0.0F = 0.0F
vorps ymm5, ymm4, ymm5   ; area >= 0.0F = area | area < 0.0F = QNAN
vmovaps ymmword ptr[r8+rax], ymm5

vmulps ymm2, ymm3, ymm0  ; area * radius
vdivps ymm3, ymm2, ymm7  ; (area * radius) / 3
vandps ymm4, ymm1, ymm8  ; volume >= 0.0F = 0.0F   | volume < 0.0F = QNAN
vandnps ymm5, ymm1, ymm3 ; volume >= 0.0F = volume | volume < 0.0F = 0.0F
vorps ymm5, ymm4, ymm5	 ; volume >= 0.0F = volume | volume < 0.0F = QNAN
vmovaps ymmword ptr[r9+rax], ymm5

add rax, type ymmword
sub rdx, 8  ; 8 radius processed
dec r10
jnz @B

OneByOne:
test rdx, rdx
jz Done

vmovss xmm0, real4 ptr [r8 + rax]
vmulss xmm2, xmm6, xmm0
vmulss xmm3, xmm2, xmm0

vcmpss xmm1, xmm0, xmm9, CMP_LT_OS

vandps xmm4, xmm1, xmm8
vandnps xmm5, xmm1, xmm3
vorps xmm5, xmm4, xmm5
vmovss real4 ptr[r8+rax], xmm5

vmulss xmm2, xmm3, xmm0
vdivss xmm3, xmm2, xmm7
vandps xmm4, xmm1, xmm8
vandnps xmm5, xmm1, xmm3
vorps xmm5, xmm4, xmm5
vmovss real4 ptr[r9+rax], xmm5

add rax, 4
dec rdx

jnz OneByOne

Done:

vzeroupper

_RestoreXmmRegs xmm6, xmm7, xmm8, xmm9
_DeleteFrame r10

ret

AVX_Packed_Y_Calc_Sphere_Area_Volume_ endp

end