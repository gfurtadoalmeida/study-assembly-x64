include comparison_predicates.inc

.code

; bool AVX512_Scalar_Calc_Conditional_Sum_Zero_Masking_(double* a, double* b, double* result, uint32_t length, double valueToIgnore)
AVX512_Scalar_Calc_Conditional_Sum_Zero_Masking_ proc

xor eax, eax
test r9, r9
jz Done

@@:
vmovsd xmm1, real8 ptr [rcx+rax*type real8] ; xmm1 = a[i]
vmovsd xmm2, real8 ptr [rdx+rax*type real8] ; xmm2 = b[i]

; xmm0 = valueToIgnore
; k1[0] = 1 if a[i] != valueToIgnore
vcmpsd k1, xmm1, xmm0, CMP_NEQ

; xmm3 = (a[i] == valueToIgnore) ? 0.0 : sum(a[i], b[i])
vaddsd xmm3{k1}{z}, xmm1, xmm2

vmovsd real8 ptr [r8+rax*type real8], xmm3

inc rax
cmp rax, r9
jl @B

mov eax, 1

Done:
ret

AVX512_Scalar_Calc_Conditional_Sum_Zero_Masking_ endp

end