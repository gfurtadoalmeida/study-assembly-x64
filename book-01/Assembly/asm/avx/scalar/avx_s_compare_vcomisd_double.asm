.code

; int AVX_Scalar_Compare_VCOMISD_Double_(double a, double b)
AVX_Scalar_Compare_VCOMISD_Double_ proc

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

AVX_Scalar_Compare_VCOMISD_Double_ endp

end