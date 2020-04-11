.code

; void AVX2_Packed_Convert_Float_HalfPrecision_(float values[8], uint16_t result[8], RoundingMode roudingMode)
AVX2_Packed_Convert_Float_HalfPrecision_ proc

vmovups ymm0, ymmword ptr [rcx]

; Nearest
cmp r8d, 0
jne @F
vcvtps2ph xmm1, ymm0, 0
jmp SaveResult

; Up
@@:
cmp r8d, 1
jne @F
vcvtps2ph xmm1, ymm0, 1
jmp SaveResult

; Down
@@:
cmp r8d, 2
jne @F
vcvtps2ph xmm1, ymm0, 2
jmp SaveResult

; Truncate
@@:
cmp r8d, 3
jne @F
vcvtps2ph xmm1, ymm0, 3
jmp SaveResult

; Use MXCSR.RC
@@:
vcvtps2ph xmm1, ymm0, 4

SaveResult:
vmovdqu xmmword ptr [rdx], xmm1

vzeroupper
ret

AVX2_Packed_Convert_Float_HalfPrecision_ endp

end