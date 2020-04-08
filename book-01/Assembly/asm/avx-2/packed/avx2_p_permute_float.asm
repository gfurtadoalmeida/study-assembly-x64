.code

; void AVX2_Packed_Permute_Float_(YmmVal * src, YmmVal * des, YmmVal * indexes)
AVX2_Packed_Permute_Float_ proc

vmovaps ymm0, ymmword ptr [rcx] ; src
vmovdqa ymm1, ymmword ptr [r8]	; indexes

; Rearrange the items in src according to the indexes control.
; The register is divided in half and each half has a index value
; from 0-3 and can only permutate the items in its half side.

;  255               127                  0
;  ----------------------------------------
;  | 7    6    5    4    3    2    1    0 |
;  ----------------------------------------
;           B         =         A
;  ----------------------------------------
;  | 3    2    1    0 |  3    2    1    0 |
;  ----------------------------------------
;
; Items in A can only rearrange among them.
; Same for items in B.

vpermilps ymm2, ymm0, ymm1

vmovaps ymmword ptr [rdx], ymm2

vzeroupper

ret

AVX2_Packed_Permute_Float_ endp

end