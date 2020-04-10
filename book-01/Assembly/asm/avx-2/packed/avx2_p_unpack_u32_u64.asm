.code

; YmmValAB AVX2_Packed_Unpack_U32_U64_(const YmmVal & a, const YmmVal & b)
AVX2_Packed_Unpack_U32_U64_ proc

; rcx is used by Visual C++ compiler to insert the
; pointer to the memory allocated to the return value.

vmovdqa ymm0, ymmword ptr [rdx]
vmovdqa ymm1, ymmword ptr [r8]


;        255            127              0
;        ---------------------------------
; ymm0 = | H | G | F | E | D | C | B | A |
; ymm1 = | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
;
;        255                             0
;        ---------------------------------
; ymm2 = |   5F  |   4E  |   1B  |   0A  |
; ymm3 = |   7H  |   6G  |   3D  |   2C  |

vpunpckldq ymm2, ymm0, ymm1
vpunpckhdq ymm3, ymm0, ymm1

vmovdqa ymmword ptr [rcx], ymm2
vmovdqa ymmword ptr [rcx+type ymmword], ymm3

mov rax, rcx

vzeroupper
ret

AVX2_Packed_Unpack_U32_U64_ endp

end