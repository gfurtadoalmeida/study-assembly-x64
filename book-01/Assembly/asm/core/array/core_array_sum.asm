.code

; int Core_Array_Sum_(int* arrayPointer, int arrayLength);
Core_Array_Sum_ proc frame

; Prolog
push rsi
.pushreg rsi
.endprolog

xor rax, rax ; Sum value
mov rsi, rcx ; Array pointer address, our source
mov ecx, edx ; Array length

@@:
add eax, dword ptr [rsi]
add rsi, type dword ; Address = address + sizeof(int)
loop @B             ; Loop ecx times

Return:

; Epilog
pop rsi

ret

Core_Array_Sum_ endp

end