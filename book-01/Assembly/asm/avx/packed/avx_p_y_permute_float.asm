.code

; void AVX_Packed_Y_Permute_Float_(YmmVal * src, YmmVal * des, YmmVal * indexes)
AVX_Packed_Y_Permute_Float_ proc

vmovaps ymm0, ymmword ptr [rcx] ; src
vmovdqa ymm1, ymmword ptr [r8]	; indexes

; Rearrange the items in src according to the indexes control.
vpermps ymm2, ymm1, ymm0

vmovaps ymmword ptr [rdx], ymm2

vzeroupper

ret

AVX_Packed_Y_Permute_Float_ endp

end