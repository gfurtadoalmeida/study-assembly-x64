.code

; void AVX2_Packed_Gather_Double_I32_(const double* src, double* des, const int32_t * indexes, const int64_t * merge)
AVX2_Packed_Gather_Double_I32_ proc

vmovups ymm0, ymmword ptr [rdx] ; des
vmovdqu xmm1, xmmword ptr [r8]  ; indexes
vmovdqu ymm2, ymmword ptr [r9]  ; merge

; Shift the merge items to high-order bits.
; Each merge value must be one of the following values:
; - 0xF0000000 = high order bit set    = copy the item
; - 0x00000000 = high orderbit not set = leave unchanged
;
; As merge items are 1 or 0, in case of 1, if we shift it
; 63 times, we set the high order bit.
;
; 1 = 00000000000000000000000000000000_00000000000000000000000000000001
;                                    << 63
;     10000000000000000000000000000000_00000000000000000000000000000000
vpsllq ymm2, ymm2, 63 

; Source pointer is used just as an address.
; We do not iterate over it or do any direct action
; on its items.
;
; The gather instruction for 32 bits indexes 
; and double precision numbers can only operate
; with xmm registers.
;
; For each item on destination:
;   If merge for that item has the high order bit set:
;     Address of item to be copied = source pointer + (index * sizeof(double))
;     Copy the item from source to destination
;   Else
;     Leave destination item unchanged
vgatherdpd ymm0, [rcx+xmm1*type real8], ymm2

vmovupd ymmword ptr [rdx], ymm0

vmovupd ymm0, ymmword ptr [rdx+32]
vmovdqu xmm1, xmmword ptr [r8+16]
vmovdqu ymm2, ymmword ptr [r9+32]

vpsllq ymm2, ymm2, 63
vgatherdpd ymm0, [rcx+xmm1*type real8], ymm2
vmovupd ymmword ptr [rdx+32], ymm0

vzeroupper
ret

AVX2_Packed_Gather_Double_I32_ endp

; void AVX2_Packed_Gather_Double_I64_(const double* src, double* des, const int64_t * indexes, const int64_t * merge)
AVX2_Packed_Gather_Double_I64_ proc

vmovups ymm0, ymmword ptr [rdx]
vmovdqu ymm1, ymmword ptr [r8]
vmovdqu ymm2, ymmword ptr [r9]

vpsllq ymm2, ymm2, 63
vgatherqpd ymm0, [rcx+ymm1*type real8], ymm2
vmovupd ymmword ptr [rdx], ymm0

vmovupd ymm0, ymmword ptr [rdx+32]
vmovdqu ymm1, ymmword ptr [r8+32]
vmovdqu ymm2, ymmword ptr [r9+32]

vpsllq ymm2, ymm2, 63
vgatherqpd ymm0, [rcx+ymm1*type real8], ymm2
vmovupd ymmword ptr [rdx+32], ymm0

vzeroupper
ret

AVX2_Packed_Gather_Double_I64_ endp

; void AVX2_Packed_Gather_Float_I32_(const float* src, float* des, const int32_t * indexes, const int32_t * merge)
AVX2_Packed_Gather_Float_I32_ proc

vmovups ymm0, ymmword ptr [rdx]
vmovdqu ymm1, ymmword ptr [r8]
vmovdqu ymm2, ymmword ptr [r9]

vpslld ymm2, ymm2, 31

vgatherdps ymm0, [rcx+ymm1*type real4], ymm2

vmovups ymmword ptr [rdx], ymm0

vzeroupper
ret

AVX2_Packed_Gather_Float_I32_ endp

; void AVX2_Packed_Gather_Float_I64_(const float* src, float* des, const int64_t * indexes, const int32_t * merge)
AVX2_Packed_Gather_Float_I64_ proc

vmovups xmm0, xmmword ptr [rdx]
vmovdqu ymm1, ymmword ptr [r8]
vmovdqu xmm2, xmmword ptr [r9]

vpslld xmm2, xmm2, 31

; The gather instruction for 64 bits indexes 
; and single precision numbers can only operate
; with xmm registers.
vgatherqps xmm0, [rcx+ymm1*type real4], xmm2
vmovups xmmword ptr [rdx], xmm0

vmovups xmm3, xmmword ptr [rdx+16]
vmovdqu ymm1, ymmword ptr [r8+32]
vmovdqu xmm2, xmmword ptr [r9+16]

vpslld xmm2, xmm2,31
vgatherqps xmm3, [rcx+ymm1*type real4], xmm2
vmovups xmmword ptr [rdx+16], xmm3

vzeroupper
ret

AVX2_Packed_Gather_Float_I64_ endp

end