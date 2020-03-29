.const
	; Necessary as AVX does not support immediate values.

	SCALE_F_TO_C real4 0.55555556 ; 5 / 9
	SCALE_C_TO_F real4 1.8        ; 9 / 5
	FLOAT_32 real4 32.0
.code

; float AVX_Scalar_Convert_Fahrenheit_Celsius_(float degree)
AVX_Scalar_Convert_Fahrenheit_Celsius_ proc

vmovss xmm1, real4 ptr [FLOAT_32]
vsubss xmm2, xmm0, xmm1 ; xmm2 = degree - 32

vmovss xmm1, real4 ptr [SCALE_F_TO_C]
vmulss xmm0, xmm2, xmm1 ; xmm0 = (degree - 32) * (5 / 9)

ret

AVX_Scalar_Convert_Fahrenheit_Celsius_ endp

; float AVX_Scalar_Convert_Celsius_Fahrenheit_(float degree)
AVX_Scalar_Convert_Celsius_Fahrenheit_ proc

vmulss xmm0, xmm0, real4 ptr [SCALE_C_TO_F] ; xmm0 = degree * (9 / 5)
vaddss xmm0, xmm0, real4 ptr [FLOAT_32] ; xmm0 = (degree * (9 / 5)) + 32

ret

AVX_Scalar_Convert_Celsius_Fahrenheit_ endp

end