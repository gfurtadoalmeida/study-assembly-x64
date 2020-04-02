.code

; bool AVX_Packed_Array_Max_Float_(float* input, int arrayLength, float* result);
AVX_Packed_Array_Max_Float_ proc

xor eax, eax

test rcx, 0fh ; Check if array address is 16 byte aligned
jnz	Done

test edx, edx
jz Done

mov eax, 1

vbroadcastss xmm0, real4 ptr [rcx] ; All 4 items of xmm0 = input[0]

cmp rdx, 4  ; At least 4 items are needed to use packed instructions
jb OneByOne

@@:
vmovaps xmm1, xmmword ptr [rcx] ; Get 4 items from input
vmaxps xmm0, xmm0, xmm1 ; Calculate max and store on xmm0
add rcx, type xmmword   ; Advance to the next 4 items (16 bytes)
sub rdx, 4
cmp rdx, 4
jae @B

OneByOne:
test rdx, rdx
jz Done

vmaxss xmm0, xmm0, real4 ptr [rcx] ; Find max between xmm0[0] and input[i]
add rcx, type real4 ; Advance to the next item (4 bytes)
dec rdx
jnz OneByOne

; vshufps control byte
;
;    00_00_00_00b
;    D  C  B  A
;
; Each two bits group (0-3) indicates which position
; of the source operand will go to a position on the 
; destination operand.
;
; Positions on destination operand:
; A = 0 [0:31]
; B = 1 [32:63]
; C = 2 [64:95]
; D = 3 [96:127]

;        128--------------------------0
; xmm2 = xmm0[0]_xmm0[0]_xmm0[3]_xmm0[2]
; xmm0 = xmm0[3]_xmm0[2]_xmm0[1]_xmm0[0]
; xmm1 = ignored_ignored_  max  _  max
vshufps xmm2, xmm0, xmm0, 00001110b
vmaxps xmm1, xmm2, xmm0

;        128--------------------------0
; xmm2 = xmm1[0]_xmm1[0]_xmm1[0]_xmm1[1]
; xmm1 = xmm1[3]_xmm1[2]_xmm1[1]_xmm0[0]
; xmm1 = ignored_ignored_ignored_  max
vshufps xmm2, xmm1, xmm1, 00000001b
vmaxps xmm1, xmm2, xmm1

vmovss real4 ptr [r8], xmm1 ; r8 = xmm1[0]

Done:

ret

AVX_Packed_Array_Max_Float_ endp

; bool AVX_Packed_Array_Min_Float_(float* input, int arrayLength, float* result)
AVX_Packed_Array_Min_Float_ proc

xor eax, eax

test rcx, 0fh
jnz	Done

test edx, edx
jz Done

mov eax, 1

vbroadcastss xmm0, real4 ptr [rcx]

cmp rdx, 4
jb OneByOne

@@:
vmovaps xmm1, xmmword ptr [rcx]
vminps xmm0, xmm0, xmm1
add rcx, type xmmword 
sub rdx, 4
cmp rdx, 4
jae @B

OneByOne:
test rdx, rdx
jz Done

vminss xmm0, xmm0, real4 ptr [rcx]
add rcx, type real4
dec rdx
jnz OneByOne

vshufps xmm2, xmm0, xmm0, 00001110b
vminps xmm1, xmm2, xmm0

vshufps xmm2, xmm1, xmm1, 00000001b
vminps xmm1, xmm2, xmm1

vmovss real4 ptr [r8], xmm1

Done:

ret

AVX_Packed_Array_Min_Float_ endp

end