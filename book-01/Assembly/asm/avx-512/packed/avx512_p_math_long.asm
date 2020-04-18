.code

; void AVX512_Packed_Math_Long_(const ZmmVal * a, const ZmmVal * b, ZmmVal result[5], uint32_t operationMask);
AVX512_Packed_Math_Long_ proc

vmovdqu16 zmm0, zmmword ptr [rcx]
vmovdqu16 zmm1, zmmword ptr [rdx]

and r9d, 0ffh ; r9d = operationMask value
kmovb k1, r9d ; k1 = operationMask

; Add (wraparound)
vpaddq zmm2{k1}{z}, zmm0, zmm1
vmovdqa64 zmmword ptr [r8], zmm2

; Substraction (wraparound)
vpsubq zmm2{k1}{z}, zmm0, zmm1
vmovdqa64 zmmword ptr [r8+64], zmm2

; Multiplication, signed, low 64 bits
vpmullq zmm2{k1}{z}, zmm0, zmm1
vmovdqa64 zmmword ptr [r8+128], zmm2

; Logical left shift
vpsllvq zmm2{k1}{z}, zmm0, zmm1
vmovdqa64 zmmword ptr [r8+192], zmm2

; Arithmetic right shift
vpsravq zmm2{k1}{z}, zmm0, zmm1
vmovdqa64 zmmword ptr [r8+256], zmm2

; Abs
vpabsq zmm2{k1}{z}, zmm0
vmovdqa64 zmmword ptr [r8+320], zmm2

vzeroupper
ret

AVX512_Packed_Math_Long_ endp

end