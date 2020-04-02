.code

; void AVX_Packed_Multiply_Int_A_(const XmmVal & a, const XmmVal & b, XmmVal results[2])
AVX_Packed_Multiply_Int_A_ proc

vmovdqa xmm0, xmmword ptr [rcx]
vmovdqa xmm1, xmmword ptr [rdx] 

; Multiplies packed signed doubleword integers in the even-numbered 
; (zero-based reference) elements of the first source operand with 
; the packed signed doubleword integers in the corresponding elements 
; of the second source operand and stores packed signed quadword results 
; in the destination operand.
;
; Each result will occupy 2 * sizeof(int).
; It is needed so the result does not get truncated when a overflow occurrs.
;
; 4 int in -> 4 long out

vpmuldq xmm2, xmm0, xmm1 ; xmm2 = { a[2] * b[2] | a[0] * b[0] }

; Shift source operands right by 4 bytes
vpsrldq xmm0, xmm0, 4
vpsrldq xmm1, xmm1, 4
vpmuldq xmm3, xmm0, xmm1

vpextrq qword ptr [r8], xmm2, 0    ; result[0] = xmm2[0:63]
vpextrq qword ptr [r8+8], xmm3, 0  ; result[1] = xmm3[0:63]
vpextrq qword ptr [r8+16], xmm2, 1 ; result[2] = xmm2[63:127]
vpextrq qword ptr [r8+24], xmm3, 1 ; result[3] = xmm3[63:127]

ret

AVX_Packed_Multiply_Int_A_ endp

; void AVX_Packed_Multiply_Int_B_(const XmmVal & a, const XmmVal & b, XmmVal & results)
AVX_Packed_Multiply_Int_B_ proc

vmovdqa xmm0, xmmword ptr [rcx]

; From the 64 bit result will hold only the lower 32 bits.
; No overflow control.
;
; 4 int in -> 4 int out

vpmulld xmm1, xmm0, xmmword ptr [rdx]

vmovdqa xmmword ptr [r8], xmm1

ret

AVX_Packed_Multiply_Int_B_ endp

; void AVX_Packed_Multiply_Short_(const XmmVal & a, const XmmVal & b, XmmVal results[2])
AVX_Packed_Multiply_Short_ proc

vmovdqa xmm0, xmmword ptr [rcx]
vmovdqa xmm1, xmmword ptr [rdx]

; From the 32 bit result will hold only the lower 32 bits.
; No overflow control.
;
; xmm2 = low[3] low[2] low[1] low[0]

vpmullw xmm2, xmm0, xmm1

; From the 32 bit result will hold only the higher 32 bits.
; No overflow control.
;
; xmm3 = high[3] high[2] high[1] high[0]

vpmulhw xmm3, xmm0, xmm1

;        127            63             0
; xmm4 = high[1] low[1] | high[0] low[0]

vpunpcklwd xmm4, xmm2, xmm3 ; Merge low and high results 

;        127            63             0
; xmm5 = high[3] low[3] | high[2] low[2]
vpunpckhwd xmm5, xmm2, xmm3 ; into final signed dwords

; Everything above was done because AVX doesn't
; have a native instruction to mutiply shorts.

vmovdqa xmmword ptr [r8], xmm4
vmovdqa xmmword ptr [r8+16], xmm5

ret

AVX_Packed_Multiply_Short_ endp

end