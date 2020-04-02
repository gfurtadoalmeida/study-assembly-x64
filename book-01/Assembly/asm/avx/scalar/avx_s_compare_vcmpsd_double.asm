include comparison_predicates.inc

.code

; int AVX_Scalar_Compare_Double_VCMPSD_(double a, double b)
AVX_Scalar_Compare_Double_VCMPSD_ proc

xor r8, r8

vcmpsd xmm2, xmm0, xmm1, CMP_LT
vmovq rax, xmm2
and al, 1   ; Remove unecessary bits and set RFLAGS. If comparison fails ZF will be zero.
jnz Smaller

vcmpsd xmm2, xmm0, xmm1, CMP_EQ
vmovq rax, xmm2
and al, 1
jnz Done

vcmpsd xmm2, xmm0, xmm1, CMP_GT
vmovq rax, xmm2
and al, 1
jnz Bigger

Smaller:
dec r8 ; r8 = -1
jmp Done

Bigger:
inc r8 ; r8 = 1

Done:
mov eax, r8d
ret

AVX_Scalar_Compare_Double_VCMPSD_ endp

end