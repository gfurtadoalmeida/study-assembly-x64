.code

; void AVX2_Packed_Convert_Short_Long_(YmmVal * values, YmmVal result[4]);
AVX2_Packed_Convert_Short_Long_ proc

; Convert, sign extending, a int16_t into a int64_t.
; The maximum register size for source is 64 bits (xmm).
; As we're using 256 bits for source, we need four conversions.
;
; values = 16 uint16_t
; ymm0 = 4 uint64_t
; ymm1 = 4 uint64_t
; ymm2 = 4 uint64_t
; ymm3 = 4 uint64_t

vpmovsxwq ymm0, qword ptr [rcx]
vpmovsxwq ymm1, qword ptr [rcx+8]
vpmovsxwq ymm2, qword ptr [rcx+16]
vpmovsxwq ymm3, qword ptr [rcx+24]

vmovdqa ymmword ptr [rdx], ymm0
vmovdqa ymmword ptr [rdx+32], ymm1
vmovdqa ymmword ptr [rdx+64], ymm2
vmovdqa ymmword ptr [rdx+96], ymm3

vzeroupper
ret

AVX2_Packed_Convert_Short_Long_ endp

end