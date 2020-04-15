ConstVals segment readonly align(64) 'const' 
	AbsMaskF64 qword 8 dup(7fffffffffffffffh) 
ConstVals ends

.code

; void AVX512_Packed_Math_Double_(const ZmmVal * a, const ZmmVal * b, ZmmVal result[8])
AVX512_Packed_Math_Double_ proc

vmovapd zmm0, zmmword ptr [rcx]
vmovapd zmm1, zmmword ptr [rdx]

; Addition
vaddpd zmm2, zmm0, zmm1
vmovapd zmmword ptr [r8+0], zmm2

; Subtraction
vsubpd zmm2, zmm0, zmm1
vmovapd zmmword ptr [r8+64], zmm2

; Multiplication
vmulpd zmm2, zmm0, zmm1
vmovapd zmmword ptr [r8+128], zmm2

; Division
vdivpd zmm2, zmm0, zmm1
vmovapd zmmword ptr [r8+192], zmm2

; Absolute value (b)
vandpd zmm2, zmm1, zmmword ptr [AbsMaskF64]
vmovapd zmmword ptr [r8+256], zmm2

; Square root (a)
vsqrtpd zmm2, zmm0
vmovapd zmmword ptr [r8+320], zmm2

; Minimum
vminpd zmm2, zmm0, zmm1
vmovapd zmmword ptr [r8+384], zmm2

; Maximum
vmaxpd zmm2, zmm0, zmm1
vmovapd zmmword ptr [r8+448], zmm2

vzeroupper
ret

AVX512_Packed_Math_Double_ endp

end