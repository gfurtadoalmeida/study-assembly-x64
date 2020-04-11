.code

; void AVX2_Packed_Convert_HalfPrecision_Float_(uint16_t values[8], float result[8])
AVX2_Packed_Convert_HalfPrecision_Float_ proc

vcvtph2ps ymm0, xmmword ptr [rcx]
vmovups ymmword ptr [rdx], ymm0

vzeroupper
ret

AVX2_Packed_Convert_HalfPrecision_Float_ endp

end