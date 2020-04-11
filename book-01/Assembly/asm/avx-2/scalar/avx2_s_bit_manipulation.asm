.code

; uint32_t AVX2_Scalar_And_Not_(uint32_t a, uint32_t b)
AVX2_Scalar_And_Not_ proc

; Inverts 'a' and performs a bitwise
; logical AND with 'b'.
;
; eax = ~a & b
andn eax, ecx, edx

ret

AVX2_Scalar_And_Not_ endp

; void AVX2_Scalar_Count_Zero_Bits_(uint32_t value, uint32_t * leadingZeros, uint32_t * trailingZeros)
AVX2_Scalar_Count_Zero_Bits_ proc

; Leading zeros: 00010 => 3
lzcnt eax, ecx
mov dword ptr [rdx], eax

; Trailing zeros: 01000 => 3
tzcnt eax, ecx
mov dword ptr [r8], eax

ret

AVX2_Scalar_Count_Zero_Bits_ endp

; uint32_t AVX2_Scalar_Extract_Bits_(uint32_t value, uint8_t start, uint8_t length)
AVX2_Scalar_Extract_Bits_ proc

mov al, r8b ; length
mov ah, al  ; ah = length
mov al, dl  ; al = start

; Using eax as control bits, extract N bits
; from ecx, starting at S and store at eax.
;
; eax[al] = start
; eax[ah] = length

bextr eax, ecx, eax

ret

AVX2_Scalar_Extract_Bits_ endp

end