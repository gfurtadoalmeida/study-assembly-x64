.code

; void AVX_Packed_Y_Sum_Float_(const YmmVal & a, const YmmVal & b, YmmVal results[])
AVX_Packed_Y_Sum_Float_ proc

xor rax, rax

vmovaps ymm0, ymmword ptr [rcx]
vmovaps ymm1, ymmword ptr [rdx]

; | 127 |  63 |  31 |  0  | 127 |  63 |  31 |  0  |
; -------------------------------------------------
; | [3] | [2] | [1] | [0] | [3] | [2] | [1] | [0] | ymm0
;    +     +     +     +     +     +     +     +
; | [3] | [2] | [1] | [0] | [3] | [2] | [1] | [0] | ymm1
;    =     =     =     =     =     =     =     =
; | [3] | [2] | [1] | [0] | [3] | [2] | [1] | [0] | ymm2

vaddps ymm2, ymm0, ymm1

vmovaps ymmword ptr [r8], ymm2

; Any code that uses 256 bits registers should
; call "vzeroupper" to clear the upper 128 bits 
; of all ymm registers.
; This will avoid false dependency in case other
; code uses xmm registers, as the false dependency
; would be with the upper 128 bits of the ymm register.
; Avoiding this dependency improves performance.
; Remember that xmm is just the lower 128 bits of ymm.

vzeroupper

ret

AVX_Packed_Y_Sum_Float_ endp

end