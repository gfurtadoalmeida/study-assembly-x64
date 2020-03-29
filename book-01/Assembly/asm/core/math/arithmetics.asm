.code

; int Core_Math_Sum_(int a, int b)
Core_Math_Sum_ proc

add ecx, edx
mov eax, ecx
ret

Core_Math_Sum_ endp

; int Core_Math_Div_(int a, int b, int* quotient, int* remainder)
Core_Math_Div_ proc

; Error if < 0
cmp edx, 0
je InvalidDivisor

mov r10d, edx ; Backup the divisor value
mov eax, ecx

; Convert an int stored in eax to long, where:
; eax: contains least significant bits (32 bits)
; edx: contains most significant bits (32 bits) {that's the reason for the backup above}
cdq 

; Divides eax by the operand and place:
; quotient: eax
; remainder: edx
idiv r10d

mov dword ptr [r8], eax
mov dword ptr [r9], edx
mov eax, 1

ret

InvalidDivisor:
xor eax, eax
ret

Core_Math_Div_ endp

end