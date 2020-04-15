include comparison_predicates.inc

.code

; void AVX512_Packed_Compare_Double_(const ZmmVal * a, const ZmmVal * b, uint8_t result[8]);
AVX512_Packed_Compare_Double_ proc

vmovaps zmm0, zmmword ptr [rcx]
vmovaps zmm1, zmmword ptr [rdx]

vcmppd k1, zmm0, zmm1, CMP_EQ_OQ
kmovb byte ptr [r8], k1

vcmppd k1, zmm0, zmm1, CMP_NEQ_OQ
kmovb byte ptr [r8+1], k1 

vcmppd k1, zmm0, zmm1, CMP_LT_OS
kmovb byte ptr [r8+2], k1

vcmppd k1, zmm0, zmm1, CMP_LE_OS
kmovb byte ptr [r8+3], k1

vcmppd k1, zmm0, zmm1, CMP_GT_OS
kmovb byte ptr [r8+4], k1

vcmppd k1, zmm0, zmm1, CMP_GE_OS
kmovb byte ptr [r8+5], k1

vcmppd k1, zmm0, zmm1, CMP_ORD_S
kmovb byte ptr [r8+6], k1

vcmppd k1, zmm0, zmm1, CMP_UNORD_S
kmovb byte ptr [r8+7], k1

vzeroupper
ret


AVX512_Packed_Compare_Double_ endp

end