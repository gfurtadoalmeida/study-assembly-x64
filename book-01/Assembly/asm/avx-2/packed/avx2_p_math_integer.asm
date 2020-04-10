.code

; void AVX2_Packed_Sum_Int_(const YmmVal & a, const YmmVal & b, YmmVal & result)
AVX2_Packed_Sum_Int_ proc

vmovdqa ymm0, ymmword ptr [rcx]
vmovdqa ymm1, ymmword ptr [rdx]

; It's NOT a saturated operation.
; result > Int16.MaxValue = Wraparound
; result < Int16.MinValue = Wraparound

vpaddd ymm2, ymm0, ymm1
vmovdqa ymmword ptr [r8], ymm2

vzeroupper
ret

AVX2_Packed_Sum_Int_ endp

; void AVX2_Packed_Sum_Short_(const YmmVal & a, const YmmVal & b, YmmVal & result)
AVX2_Packed_Sum_Short_ proc

vmovdqa ymm0, ymmword ptr [rcx]
vmovdqa ymm1, ymmword ptr [rdx]

; It's a saturated operation.
; result > Int16.MaxValue = Int16.MaxValue
; result < Int16.MinValue = Int16.MinValue
vpaddsw ymm2, ymm0, ymm1

vmovdqa ymmword ptr [r8], ymm2

vzeroupper
ret

AVX2_Packed_Sum_Short_ endp

end