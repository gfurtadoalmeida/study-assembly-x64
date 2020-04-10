.code

; void AVX2_Packed_Pack_I32_I16_(const YmmVal & a, const YmmVal & b, YmmVal * result)
AVX2_Packed_Pack_I32_I16_ proc

vmovdqa ymm0, ymmword ptr [rcx]
vmovdqa ymm1, ymmword ptr [rdx]

;        255            127              0
;        ---------------------------------
; ymm0 = | H | G | F | E | D | C | B | A |
; ymm1 = | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
;
;        255                                                             0
;        -----------------------------------------------------------------
; ymm2 = | 7 | 6 | 5 | 4 | H | G | F | E | 3 | 2 | 1 | 0 | D | C | B | A |
;
; This is not a saturated pack, which means any value bigger
; than Int16.MaxValue os smaller than Int16.MinValue will
; be clipped to Int16.MaxValue or Int16.MinValue.
vpackssdw ymm2, ymm0, ymm1

vmovdqa ymmword ptr [r8], ymm2

vzeroupper
ret

AVX2_Packed_Pack_I32_I16_ endp

end