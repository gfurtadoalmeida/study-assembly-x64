.code

; void AVX_Packed_Y_Blend_Float_(YmmVal * src1, YmmVal * src2, YmmVal * des, BlendSource blend[])
AVX_Packed_Y_Blend_Float_ proc

vmovaps ymm0, ymmword ptr [rcx] ; src1
vmovaps ymm1, ymmword ptr [rdx]	; src2
vmovdqa ymm2, ymmword ptr [r9]	; blends

; Merges src and src2 according to the blend controls.
vblendvps ymm3, ymm0, ymm1, ymm2

vmovaps ymmword ptr [r8], ymm3

vzeroupper

ret

AVX_Packed_Y_Blend_Float_ endp

end