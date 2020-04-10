.code

; void AVX2_Packed_Convert_Short_Int_(YmmVal * values, YmmVal result[2])
AVX2_Packed_Convert_Short_Int_ proc

; Convert, sign extending, a int16_t into a int32_t.
; The maximum register size for source is 128 bits (xmm).
; As we're using 256 bits for source, we need two conversions.
;
; values = 16 uint16_t
; ymm0 = 8 uint32_t
; ymm1 = 8 uint32_t

vpmovsxwd ymm0, xmmword ptr [rcx]
vpmovsxwd ymm1, xmmword ptr [rcx+type xmmword]

vmovdqa ymmword ptr [rdx], ymm0
vmovdqa ymmword ptr [rdx+type ymmword], ymm1

vzeroupper
ret

AVX2_Packed_Convert_Short_Int_ endp

end