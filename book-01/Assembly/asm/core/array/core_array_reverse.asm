.code

; void Core_Array_Reverse_(const int* source, const int* destination, int arrayLength)
Core_Array_Reverse_ proc frame

; Prolog
push rsi
.pushreg rsi
push rdi
.pushreg rdi
.endprolog

test r8d, r8d
jle InvalidLength

mov rsi, rcx ; Source
mov rdi, rdx ; Destination
mov ecx, r8d ; Array length
lea rsi, [rsi+rcx*type dword-type dword] ; rsi = rsi[length-1]

pushfq ; Save eflags registers on stack
std    ; Set direction flag (EFLAGS.DT) to 1 (decrement/down)

; Copy the source array to destination array in reverse order
@@:
lodsd                    ; eax = source address, rsi = rsi + sizeof(int)
mov dword ptr [rdi], eax ; Destination address value = eax
add rdi, type dword		 ; Destination address = destination address + sizeof(int)
dec rcx
jnz @B                   ; While rcx > 0

; Restore EFLAGS
popfq

InvalidLength:

; epilog
pop rdi
pop rsi

ret

Core_Array_Reverse_ endp

end