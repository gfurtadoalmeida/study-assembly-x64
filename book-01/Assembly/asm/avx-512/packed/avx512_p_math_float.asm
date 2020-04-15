ConstVals segment readonly align(64) 'const' 
	AbsMaskF32 dword 16 dup(7fffffffh)
ConstVals ends

.code

; void AVX512_Packed_Math_Float_(const ZmmVal * a, const ZmmVal * b, ZmmVal result[8])
AVX512_Packed_Math_Float_ proc

vmovaps zmm0, zmmword ptr [rcx]
vmovaps zmm1, zmmword ptr [rdx]

; Addition
vaddps zmm2, zmm0, zmm1
vmovaps zmmword ptr [r8+0], zmm2

; Subtraction
vsubps zmm2, zmm0, zmm1
vmovaps zmmword ptr [r8+64], zmm2

; Multiplication
vmulps zmm2, zmm0, zmm1
vmovaps zmmword ptr [r8+128], zmm2

; Division
vdivps zmm2, zmm0, zmm1
vmovaps zmmword ptr [r8+192], zmm2

; Absolute value (b)
vandps zmm2, zmm1, zmmword ptr [AbsMaskF32]
vmovaps zmmword ptr [r8+256], zmm2

; Square root (a)
vsqrtps zmm2, zmm0
vmovaps zmmword ptr [r8+320], zmm2

; Minimum
vminps zmm2, zmm0, zmm1
vmovaps zmmword ptr [r8+384], zmm2

; Maximum
vmaxps zmm2, zmm0, zmm1
vmovaps zmmword ptr [r8+448], zmm2

vzeroupper
ret

AVX512_Packed_Math_Float_ endp

end