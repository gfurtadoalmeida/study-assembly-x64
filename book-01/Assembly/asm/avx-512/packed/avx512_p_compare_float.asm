include comparison_predicates.inc

.code

; void AVX512_Packed_Compare_Float_(const ZmmVal * a, const ZmmVal * b, uint16_t result[8]);
AVX512_Packed_Compare_Float_ proc

vmovaps zmm0, zmmword ptr [rcx]
vmovaps zmm1, zmmword ptr [rdx]

vcmpps k1, zmm0, zmm1, CMP_EQ_OQ
kmovw word ptr [r8], k1

vcmpps k1, zmm0, zmm1, CMP_NEQ_OQ
kmovw word ptr [r8+2], k1 

vcmpps k1, zmm0, zmm1, CMP_LT_OS
kmovw word ptr [r8+4], k1

vcmpps k1, zmm0, zmm1, CMP_LE_OS
kmovw word ptr [r8+6], k1

vcmpps k1, zmm0, zmm1, CMP_GT_OS
kmovw word ptr [r8+8], k1

vcmpps k1, zmm0, zmm1, CMP_GE_OS
kmovw word ptr [r8+10], k1

vcmpps k1, zmm0, zmm1, CMP_ORD_S
kmovw word ptr [r8+12], k1

vcmpps k1, zmm0, zmm1, CMP_UNORD_S
kmovw word ptr [r8+14], k1

vzeroupper
ret

AVX512_Packed_Compare_Float_ endp

end