.const

align 16

; Initial value for AVX_Packed_Find_Array_Byte_Min_
; xmmword = biggest number possible with 128 bits.
StartMinVal qword 0ffffffffffffffffh
			qword 0ffffffffffffffffh

.code

; bool AVX_Packed_Array_Max_Byte_(byte* input, int arrayLength, byte* result);
AVX_Packed_Array_Max_Byte_ proc frame

; Prolog
push rbx
.pushreg rbx
.endprolog

xor eax, eax

test rcx, 0fh ; Check if array address is 16 byte aligned
jnz	Done

test edx, edx
jz Done

cmp rdx, 16 ; Do one by one if we can't fill a xmm register
jb OneByOne

vpxor xmm0, xmm0, xmm0 ; Initial compare values = 0

@@:
vmovdqa xmm1, xmmword ptr [rcx]
vpmaxub xmm0, xmm0, xmm1

add rcx, type xmmword
sub rdx, 16
cmp rdx, 16
jae @B

; Now that we have only one register with the max values
; we need to compare it with itself.
; How:
;  1 - Fill a temp register with the high values (main
;      register right shifted half the items count).
;  2 - Compare
;  3 - Repeat until you have only 2 numbers left.

vpsrldq xmm1, xmm0, 8    ; xmm1[0:61] = xmm0[61:128]
vpmaxub xmm2, xmm1, xmm0

vpsrldq xmm1, xmm2, 4    ; xmm1[0:31] = xmm0[31:63]
vpmaxub xmm0, xmm1, xmm2

vpsrldq xmm1, xmm0, 2    ; xmm1[0:15] = xmm0[15:23]
vpmaxub xmm2, xmm1, xmm0

; Get the last two numbers = two 8 bit numbers.
vpextrw eax, xmm2, 0

; eax = 32 bits, we moved 16 bits to it
; al = lower half of the first 16 bits = number 1
; ah = higher half of the first 16 bits = number 2
cmp al, ah
jae OneByOne
mov al, ah

OneByOne:
test rdx, rdx
jz Done

mov bl, byte ptr [rcx]
cmp bl, al
cmova rax, rbx
add rcx, type byte ; Advance to the next item
dec rdx
jnz OneByOne

mov byte ptr [r8], bl
mov eax, 1

Done:

; Epilog
pop rbx

ret

AVX_Packed_Array_Max_Byte_ endp

; bool AVX_Packed_Array_Min_Byte_(float* input, int arrayLength, float* result)
AVX_Packed_Array_Min_Byte_ proc frame

push rbx
.pushreg rbx
.endprolog

xor eax, eax

test rcx, 0fh
jnz	Done

test edx, edx
jz Done

cmp rdx, 16
jb OneByOne

vmovdqa xmm0, xmmword ptr [StartMinVal]

@@:
vmovdqa xmm1, xmmword ptr [rcx]
vpmaxub xmm0, xmm0, xmm1

add rcx, type xmmword
sub rdx, 16
cmp rdx, 16
jae @B

vpsrldq xmm1, xmm0, 8
vpminub xmm2, xmm1, xmm0

vpsrldq xmm1, xmm2, 4
vpminub xmm0, xmm1, xmm2

vpsrldq xmm1, xmm0, 2
vpminub xmm2, xmm1, xmm0

vpextrw eax, xmm2, 0

cmp al, ah
jbe OneByOne
mov al, ah

OneByOne:
test rdx, rdx
jz Done

mov bl, byte ptr [rcx]
cmp bl, al
cmovb rax, rbx
add rcx, type byte
dec rdx
jnz OneByOne

mov byte ptr [r8], bl
mov eax, 1

Done:

pop rbx

ret

AVX_Packed_Array_Min_Byte_ endp

end