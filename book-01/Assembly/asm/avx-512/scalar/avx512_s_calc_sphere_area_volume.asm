include comparison_predicates.inc

.const
	; Necessary as AVX does not support immediate values.

	PI real8 3.14159265358979323846
	NUMBER_3 real8 3.0
	NUMBER_4 real8 4.0

.code

; bool AVX512_Scalar_Calc_Sphere_Area_Volume_(double radius, double* area, double* volume, double errorValue);
AVX512_Scalar_Calc_Sphere_Area_Volume_ proc

vxorpd xmm5, xmm5, xmm5	  ; 0.0
vmovsd xmm16, xmm16, xmm3 ; Erro value

; k1[0] = 1 if radius >= 0.0
; xmm0 = radius
vcmpsd k1, xmm0, xmm5, CMP_GE_OS

; Area = 4 * pi * radius^2
; Volume = (area * radius) / 3
;
; The multiplications and divisions below will
; only occur if k1[0] == 1, otherwise xmm1-5 will
; be lef unchanged.
vmulsd xmm1{k1}, xmm0, xmm0       ; r * r
vmulsd xmm2{k1}, xmm1, [NUMBER_4] ; 4 * r * r
vmulsd xmm3{k1}, xmm2, [PI]       ; Area = 4 * PI * r * r
vmulsd xmm4{k1}, xmm3, xmm0       ; 4 * PI * r * r * r
vdivsd xmm5{k1}, xmm4, [NUMBER_3] ; Volume = 4 * PI * r * r * r / 3

; Set surface area and volume to error_val if radius < 0.0 is true
knotw k2, k1                 ; k2[0] = ~k1[0]
vmovsd xmm3{k2}, xmm3, xmm16 ; xmm3 = errorValue if radius < 0.0
vmovsd xmm5{k2}, xmm5, xmm16 ; xmm5 = errorValue if radius < 0.0

; Save results
vmovsd real8 ptr [rdx], xmm3 ; Area
vmovsd real8 ptr [r8], xmm5  ; Volume
kmovw eax, k1                ; Return code

ret

AVX512_Scalar_Calc_Sphere_Area_Volume_ endp

end