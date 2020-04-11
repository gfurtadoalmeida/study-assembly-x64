.code

; uint64_t AVX2_Scalar_Flagless_Multiply_UInt_(uint32_t a, uint32_t b, uint64_t flags[2])
AVX2_Scalar_Flagless_Multiply_UInt_ proc

; Save original flags
pushfq
pop rax
mov qword ptr [r8], rax

; Multiply the source operand (rcx) with rdx.
; Stores the low half of the result in the second operand and
; the high half of the result in the first operand.
; r10d = result[0:31]
; r11d = result[32:63]
mulx r11d, r10d, ecx

; Save flags after multiplication
pushfq
pop rax
mov qword ptr [r8+type qword], rax

; Build the result
mov eax, r10d
shl r11, 32
or rax, r11

ret

AVX2_Scalar_Flagless_Multiply_UInt_ endp

; void AVX2_Scalar_Flagless_Shift_UInt_(uint32_t value, uint32_t count, uint32_t results[3], uint64_t flags[4])
AVX2_Scalar_Flagless_Shift_UInt_ proc

; Save original flags
pushfq
pop rax
mov qword ptr [r9], rax

; Shifts:
; - Arithmetic right
; - Logical left
; - Logical right
;
; For each shift, the flags after the operation
; is saved.

sarx eax, ecx, edx
mov dword ptr [r8], eax
pushfq
pop rax
mov qword ptr [r9+8], rax

shlx eax, ecx, edx
mov dword ptr [r8+4], eax
pushfq
pop rax
mov qword ptr [r9+16], rax

shrx eax, ecx, edx
mov dword ptr [r8+8], eax
pushfq
pop rax
mov qword ptr [r9+24], rax

ret

AVX2_Scalar_Flagless_Shift_UInt_ endp

end