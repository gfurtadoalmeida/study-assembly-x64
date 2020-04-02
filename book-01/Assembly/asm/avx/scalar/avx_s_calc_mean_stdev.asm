.code

; void AVX_Scalar_Calc_Mean_Stdev_(const double* values, int arrayLength, double* mean, double* stdev)
AVX_Scalar_Calc_Mean_Stdev_ proc

cmp rdx, 2
jl InvalidLength

xor eax, eax            ; i = 0
vxorpd xmm0, xmm0, xmm0 ; xmm0 = sum = 0

; Process values for mean calculation
@@:
vaddsd xmm0, xmm0, real8 ptr [rcx+rax*type real8] ; sum += x[i]
inc eax
cmp eax, edx
jl @B

; Calculate mean
vcvtsi2sd xmm1, xmm1, rdx ; Convert arrayLength to double
vdivsd xmm3, xmm0, xmm1   ; xmm3 = mean(sum / arrayLength)
vmovsd real8 ptr [r8], xmm3

xor eax, eax            ; i = 0
vxorpd xmm0, xmm0, xmm0 ; xmm0 = sum = 0

; Process values for stdevcalculation
@@:
vmovsd xmm1, real8 ptr [rcx+rax*type real8]
vsubsd xmm2, xmm1, xmm3 ; xmm2 = x[i] - mean
vmulsd xmm2, xmm2, xmm2 ; xmm2 = (x[i] - mean)^2
vaddsd xmm0, xmm0, xmm2 ; sum2 += (x[i] - mean)^2
inc eax
cmp eax, edx
jl @B

; Calculate stdev
dec rcx
vcvtsi2sd xmm1, xmm1, rdx   ; Convert (arrayLength - 1) to double
vdivsd xmm0, xmm0, xmm1     ; xmm0 = sum2 / (n - 1)
vsqrtsd xmm0, xmm0, xmm0    ; xmm0 = stdev
vmovsd real8 ptr [r9], xmm0

mov eax, 1

InvalidLength:

ret

AVX_Scalar_Calc_Mean_Stdev_ endp

end