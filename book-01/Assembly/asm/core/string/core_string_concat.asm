.code

; uint32_t Core_String_Concat_(const char* const* source, uint32_t sourceElements, char* destination, uint32_t destinationLength);
Core_String_Concat_ proc frame

; Prolog
push rsi
.pushreg rsi
push rdi
.pushreg rdi
push rbx
.pushreg rbx
.endprolog

test rdx, rdx ; Works like cmp rdx, 0 but with smaller byte code
jz InvalidLenght

test r9d, r9d
jz InvalidLenght

xor rax, rax ; Error code = 0

; rbx = destination
; rdx = destination length
; r8 = source
; r9 = source num elements
; r10 = destination index
; r11 = i
; rcx = string length
; rsi, rdi = pointers for scasb & movsb instructions
mov rbx, r8           ; rbx = destination
mov r8, rcx           ; r8 = source
mov r10, rdx
mov rdx, r9           ; rdx = destination length
mov r9, r10           ; r9 = source num elements
xor r10, r10          ; Destination index = 0
xor r11, r11          ; i = 0
mov byte ptr [rbx], 0 ; Destination[0] = '\0'

@@:
mov rax, r8			          ; rax = source
mov rdi, qword ptr [rax+r11*type qword] ; rdi = source[i], source is an array of pointers to the strings
mov rsi, rdi			      ; rsi = source[i]

; Compute source[i] length
xor rax, rax ; rax = 0 = null terminator
mov rcx, -1
repne scasb ; While ZF != 0 {if rcx != 0 compare rdi with rax, increment rdi and decrement rcx}. Repne uses ZF, scasb uses rcx
not rcx     ; One's complement negation = abs(-X)-1
dec rcx     ; Remove 1 because the null terminator is not part of the string

; Compute destination index + source[i] length and verifies if fits at destination
mov rax, r10 ; rax = destination index
add rax, rcx ; rax = destination index + source[i] length (without null terminator)
cmp rax, rdx
jge Done

; Copy source[i] to destination
mov rax, r10 ; rax = old destination index
add r10, rcx ; r10 = new destination index
inc rcx      ; rcx = source[i] length + 1 will copy the null terminator
lea rdi, [rbx+rax] ; rdi = address destination + old destination index (offset)
rep movsb    ; While rcx != 0 {while rcx != 0 copy rcx bytes from rsi to rdi, decrementing rcx at each byte copied}

; Increment the source index
inc r11
cmp r11, r9
jl @B

Done:
mov rax, r10 ; rax = destination index = max copied chars

InvalidLenght:

; Epilog
pop rbx
pop rdi
pop rsi

ret

Core_String_Concat_ endp

end