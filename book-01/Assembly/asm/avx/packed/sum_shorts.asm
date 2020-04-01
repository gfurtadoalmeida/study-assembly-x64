.code

; void AVX_Packed_Sum_Shorts_(const XmmVal & a, const XmmVal & b, XmmVal results[2])
AVX_Packed_Sum_Shorts_ proc

vmovdqa xmm0, xmmword ptr [rcx]
vmovdqa xmm1, xmmword ptr [rdx]

vpaddw xmm2, xmm0, xmm1  ; Wraparound
vpaddsw xmm3, xmm0, xmm1 ; Saturated

vmovdqa xmmword ptr [r8], xmm2 ; Wraparound
vmovdqa xmmword ptr [r8+type xmmword], xmm3 ; Saturated

ret

AVX_Packed_Sum_Shorts_ endp

end