.code

; int AVX_Scalar_Compare_Double_VCOMISD_(double a, double b)
AVX_Scalar_Compare_Double_VCOMISD_ proc

xor eax, eax

vcomisd xmm0, xmm1

jb Smaller
ja Bigger
ret ; If equal will stop here

Smaller:
dec rax
ret

Bigger:
inc rax
ret

AVX_Scalar_Compare_Double_VCOMISD_ endp

end