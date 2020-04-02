.code

; int64_t Core_Stack_Sum_Arguments_(int8_t a, int16_t b, int32_t c, int64_t d, int8_t e, int16_t f, int32_t g, int64_t h);
Core_Stack_Sum_Arguments_ proc frame

; argument z	 <--- rsp+offset (higher address)
;    .             |
;    .             |
;    .             |
; argument b	   |
; argument a	   |
; r9  home         |
; r8  home         |
; rdx home         |
; rcx home         |
; return address   |
; saved old rbp  <--- rsp (grows to lower address)
; local var a      |
; local var b      |
;    .             |
;    .             |
;    .             |
; local var z    <--- rsp-offset (lower address)
;
; At the beginning of the function, rbp must be pushed to the stack
; and then rsp must be saved on rbp.

; Prolog

push rbp    ; Save caller's rbp
.pushreg rbp

sub rsp, 16 ; Allocate 16 bytes on the stack. It's 16 because the stack must be 16 bytes aligned
.allocstack 16

mov rbp, rsp
.setframe rbp, 0 ; rbp = rsp-16 = new base offset

RBP_RETURN_ADDRESS_OFFSET = 24 ; Offset from rbp to return address; 16 allocated + 8 for old rbp value
.endprolog

; Save argument registers to home area (optional).
; Area created but not filled by the caller.
mov qword ptr [rbp+RBP_RETURN_ADDRESS_OFFSET+8], rcx
mov qword ptr [rbp+RBP_RETURN_ADDRESS_OFFSET+16], rdx
mov qword ptr [rbp+RBP_RETURN_ADDRESS_OFFSET+24], r8
mov qword ptr [rbp+RBP_RETURN_ADDRESS_OFFSET+32], r9

; Sum the argument values a, b, c, d. Were passed using registers
movsx rcx, cl
movsx rdx, dx
movsxd r8, r8d
add rcx, rdx
add r8, r9
add r8, rcx
mov qword ptr [rbp], r8 ; Save the value on the allocated space on the stack

; Sum the argument values e, f, g, h; Were passed using the stack
movsx rcx, byte ptr [rbp+RBP_RETURN_ADDRESS_OFFSET+40]
movsx rdx, word ptr [rbp+RBP_RETURN_ADDRESS_OFFSET+48]
movsxd r8, dword ptr [rbp+RBP_RETURN_ADDRESS_OFFSET+56]
add rcx, rdx
add r8, qword ptr [rbp+RBP_RETURN_ADDRESS_OFFSET+64]
add r8, rcx

mov rax, qword ptr [rbp]
add rax, r8

; Epilog
add rsp, 16 ; Release allocated bytes
pop rbp

ret

Core_Stack_Sum_Arguments_ endp

end