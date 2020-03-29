.code

; void AVX_Packed_Sum_Floats_(const XmmVal & a, const XmmVal & b, XmmVal results[])
AVX_Packed_Sum_Floats_ proc

xor rax, rax

vmovaps xmm0, xmmword ptr [rcx] ; xmm0 = a
vmovaps xmm1, xmmword ptr [rdx] ; xmm1 = b

; | 127 |  63 |  31 |  0  |
; --------------------------
; | [3] | [2] | [1] | [0] | xmm0
;    +     +     +     +  
; | [3] | [2] | [1] | [0] | xmm1
;    =     =     =     =  
; | [3] | [2] | [1] | [0] | xmm2; 

vaddps xmm2, xmm0, xmm1 ; xmm2 = xmm0 + xmm1

vmovaps xmmword ptr [r8], xmm2

ret

AVX_Packed_Sum_Floats_ endp

end