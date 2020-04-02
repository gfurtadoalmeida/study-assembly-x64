.code

; double AVX_Scalar_Calc_Euclidian_Distance_(double x1, double y1, double z1, double x2, double y2, double z2)
AVX_Scalar_Calc_Euclidian_Distance_ proc

; Distance = squareRoot((x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2)

; load y2 and z2 from stack
;
; +48 = z2
; +40 = y2
; +32 = r9 home
; +24 = r8 home
; +16 = rdx home
;  +8 = ecx home
;   0 = return address
vmovsd xmm4, real8 ptr [rsp + 40] ; xmm4 = y2
vmovsd xmm5, real8 ptr [rsp + 48] ; xmm5 = z2

vsubsd xmm0, xmm3, xmm0 ; xmm0 = x2 - x1
vmulsd xmm0, xmm0, xmm0 ; xmm0 = (x2 - x1) * (x2 - x1)

vsubsd xmm1, xmm4, xmm1 ; xmm1 = y2 - y1
vmulsd xmm1, xmm1, xmm1 ; xmm1 = (y2 - y1) * (y2 - y1)

vsubsd xmm2, xmm5, xmm2 ; xmm2 = z2 - z1
vmulsd xmm2, xmm2, xmm2 ; xmm2 = (z2 - z1) * (z2 - z1)

; Calculate final distance
vaddsd xmm3, xmm0, xmm1
vaddsd xmm4, xmm2, xmm3  ; xmm4 = sum of squares
vsqrtsd xmm0, xmm0, xmm4 ; xmm0 = final distance value

ret

AVX_Scalar_Calc_Euclidian_Distance_ endp

end