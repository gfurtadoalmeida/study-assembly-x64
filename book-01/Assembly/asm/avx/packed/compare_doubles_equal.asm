include <comparison_predicates.inc>

.code

; void AVX_Packed_Compare_Doubles_Equal_(const XmmVal & a, const XmmVal & b, XmmVal results[])
AVX_Packed_Compare_Doubles_Equal_ proc

vmovaps xmm0, xmmword ptr [rcx] ; xmm0 = a
vmovaps xmm1, xmmword ptr [rdx] ; xmm1 = b

; |    127    |     0     |
; --------------------------
; |    [1]    |    [0]    | xmm0
;      ==          ==
; |    [1]    |    [0]    | xmm1
;      ==          ==
; |    [1]    |    [0]    | xmm2
;
; The returned values are not double.
; They are Int64:
; 0x0 = false
; 0xF = true

vcmppd xmm2, xmm0, xmm1, CMP_EQ

vmovapd xmmword ptr [r8], xmm2

ret

AVX_Packed_Compare_Doubles_Equal_  endp

end