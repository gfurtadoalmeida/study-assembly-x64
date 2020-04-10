.code

; void AVX2_Packed_Convert_UByte_UInt_(YmmVal * values, YmmVal result[4])
AVX2_Packed_Convert_UByte_UInt_ proc

; Convert, zero extending, a uint8_t into a uint32_t.
; The maximum register size for source is 64 bits (qword).
; As we're using 256 bits for source, we need four conversions.
;
; values = 32 uint8_t
; ymm0 = 8 uint32_t
; ymm1 = 8 uint32_t
; ymm2 = 8 uint32_t
; ymm3 = 8 uint32_t

vpmovzxbd ymm0, qword ptr [rcx]
vpmovzxbd ymm1, qword ptr [rcx+8]
vpmovzxbd ymm2, qword ptr [rcx+16]
vpmovzxbd ymm3, qword ptr [rcx+24]

vmovdqa ymmword ptr [rdx], ymm0
vmovdqa ymmword ptr [rdx+32], ymm1
vmovdqa ymmword ptr [rdx+64], ymm2
vmovdqa ymmword ptr [rdx+96], ymm3

vzeroupper
ret

AVX2_Packed_Convert_UByte_UInt_ endp

end