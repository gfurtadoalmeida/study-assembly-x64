.code

; int Core_Array_Compare_(int* a, int* b, int arraysLength, int* matchedValue)
Core_Array_Compare_ proc frame

; Prolog
push rsi
.pushreg rsi
push rdi
.pushreg rdi
.endprolog

mov rax, -1 ; Return code = error

test r8, r8
jle @F

mov rsi, rcx ; rsi = *a[0]
mov rdi, rdx ; rdi = *b[0]
mov rcx, r8  ; Counter = arrays length
mov rax, r8  ; rax = array length
repne cmpsd  ; Do rcx times while ZF = 0 {compare rsi with rdi, if equal set ZF = 1 else increment rsi and rdi} decrement rcx
jne @F       ; ZF will be 1 if cmpsd finds a match

sub rax, rcx ; rax = index of match + 1
dec rax      ; rax = index of match

lea r8, [rsi-type dword] ; Calculate the matched value address
mov qword ptr [r9], r8   ; Set the address in the matched value pointer address

@@:
; Epilog

pop rdi
pop rsi

ret

Core_Array_Compare_ endp

end