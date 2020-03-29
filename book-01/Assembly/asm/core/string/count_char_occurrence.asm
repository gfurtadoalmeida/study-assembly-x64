.code

; int Core_String_Count_Char_Occurrence_(char* text, char value)
Core_String_Count_Char_Occurrence_ proc frame

; Prolog
push rsi
.pushreg rsi
.endprolog

mov rsi, rcx
mov cl, dl   ; Char to compare
xor edx, edx ; Occurrence counter
xor r8d, r8d ; Used in the calculation

@@:
lodsb     ; al = char at rsi, rsi = rsi + sizeof(byte)
or al, al ; If al = 0 (null terminator) the instruction 'or' will set the zero flag
jz @F
cmp al, cl
sete r8b  ; If zero flag is true (al = cl), r8d will be 1 else 0
add edx, r8d
jmp @B

@@:
mov rax, rdx

; Epilog
pop rsi

ret

Core_String_Count_Char_Occurrence_ endp

end