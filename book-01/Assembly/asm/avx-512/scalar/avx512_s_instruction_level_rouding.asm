.code

; void AVX512_Scalar_Convert_Round_F32_U32_(float value, uint32_t result[4])
AVX512_Scalar_Convert_Round_F32_U32_ proc

vcvtss2usi eax, xmm0{rn-sae} ; Round to nearest
mov dword ptr [rdx], eax

vcvtss2usi eax, xmm0{rd-sae} ; Round down
mov dword ptr [rdx+4], eax

vcvtss2usi eax, xmm0{ru-sae} ; Round up
mov dword ptr [rdx+8], eax

vcvtss2usi eax, xmm0{rz-sae} ; Truncate
mov dword ptr [rdx+12], eax

ret

AVX512_Scalar_Convert_Round_F32_U32_ endp

; void AVX512_Scalar_Convert_Round_F64_F32_(double value, float result[4])
AVX512_Scalar_Convert_Round_F64_F32_ proc

vcvtsd2ss xmm2, xmm2, xmm0{rn-sae}
vmovss real4 ptr [rdx], xmm2

vcvtsd2ss xmm2, xmm2, xmm0{rd-sae}
vmovss real4 ptr [rdx+4], xmm2

vcvtsd2ss xmm2, xmm2, xmm0{ru-sae}
vmovss real4 ptr [rdx+8], xmm2

vcvtsd2ss xmm2, xmm2, xmm0{rz-sae}
vmovss real4 ptr [rdx+12], xmm2

ret

AVX512_Scalar_Convert_Round_F64_F32_ endp
; void AVX512_Scalar_Convert_Round_F64_U64_(double value, uint64_t result[4])
AVX512_Scalar_Convert_Round_F64_U64_ proc

vcvtsd2usi rax, xmm0{rn-sae}
mov qword ptr [rdx], rax

vcvtsd2usi rax, xmm0{rd-sae}
mov qword ptr [rdx+8], rax

vcvtsd2usi rax, xmm0{ru-sae}
mov qword ptr [rdx+16], rax

vcvtsd2usi rax, xmm0{rz-sae}
mov qword ptr [rdx+24], rax

ret

AVX512_Scalar_Convert_Round_F64_U64_ endp

end