.code

; void AVX2_Packed_Convert_UByte_UShort_(YmmVal * values, YmmVal result[2])
AVX2_Packed_Convert_UByte_UShort_ proc

; Convert, zero extending, a uint8_t into a uint16_t.
; The maximum register size for source is 128 bits (xmm).
; As we're using 256 bits for source, we need two conversions.
;
; values = 32 uint8_t
; ymm0 = 16 uint16_t
; ymm1 = 16 uint16_t

vpmovzxbw ymm0, xmmword ptr [rcx]
vpmovzxbw ymm1, xmmword ptr [rcx+type xmmword]

vmovdqa ymmword ptr [rdx], ymm0
vmovdqa ymmword ptr [rdx+type ymmword], ymm1

vzeroupper
ret

AVX2_Packed_Convert_UByte_UShort_ endp

end