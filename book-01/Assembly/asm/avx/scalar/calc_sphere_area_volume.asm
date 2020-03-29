.const
	; Necessary as AVX does not support immediate values.

	PI real8 3.14159265358979323846
	NUMBER_3 real8 3.0
	NUMBER_4 real8 4.0

.code

; void AVX_Scalar_Calc_Sphere_Area_Volume_(double radius, double* area, double* volume)
AVX_Scalar_Calc_Sphere_Area_Volume_ proc

; Area = 4*pi*radius^2
vmulsd xmm1, xmm0, xmm0	                  ; xmm0 = radius^2
vmulsd xmm2, xmm1, real8 ptr [PI] ; xmm0 = (radius^2) * pi
vmulsd xmm3, xmm2, real8 ptr [NUMBER_4]   ; xmm0 = (radius^2) * pi * 4 = area

; Volume = (area * radius)/3
vmulsd xmm4, xmm3, xmm0	                ; xmmo = area * radius
vdivsd xmm5, xmm4, real8 ptr [NUMBER_3] ; xmmo = (area * radius) / 3 = volume

vmovsd real8 ptr [rdx], xmm3
vmovsd real8 ptr [r8], xmm5

ret

AVX_Scalar_Calc_Sphere_Area_Volume_ endp

end