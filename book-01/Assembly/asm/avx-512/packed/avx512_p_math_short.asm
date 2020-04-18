.code

; void AVX512_Packed_Math_Short_(const ZmmVal * a, const ZmmVal * b, ZmmVal result[6]);
AVX512_Packed_Math_Short_ proc

vmovdqu16 zmm0, zmmword ptr [rcx]
vmovdqu16 zmm1, zmmword ptr [rdx]

; Add (wraparound)
vpaddw zmm2, zmm0, zmm1
vmovdqa64 zmmword ptr [r8], zmm2

; Add with signed saturation			  
vpaddsw zmm2, zmm0, zmm1
vmovdqa64 zmmword ptr [r8+64], zmm2

; Subtraction (wraparound)
vpsubw zmm2, zmm0, zmm1
vmovdqa64 zmmword ptr [r8+128], zmm2

; Subtraction with signed saturation
vpsubsw zmm2, zmm0, zmm1               
vmovdqa64 zmmword ptr [r8+192], zmm2

; Signed minimums
vpminsw zmm2, zmm0, zmm1
vmovdqa64 zmmword ptr [r8+256], zmm2

; Signed maximums
vpmaxsw zmm2, zmm0, zmm1
vmovdqa64 zmmword ptr [r8+320], zmm2

vzeroupper
ret

AVX512_Packed_Math_Short_ endp

end