.code

; AVX_Packed_Array_Sqtr_Float_(float* input, int arrayLength, const float* output)
AVX_Packed_Array_Sqtr_Float_ proc

xor rax, rax ; Our counter for the loop

test rdx, rdx  ; Exit if array length is zero
jz Done

; If (rcx & 0f) == 0 then exit
; because the address is not 16 byte
; aligned.
test rcx, 0fh 
jnz Done

test r8, 0fh
jnz Done

; Calculate the square roots as a batch (packed instructions)
cmp rdx, 4
jb OneByOne ; We need >= 4 items to process as a batch, otherwise one by one.

@@:
vsqrtps xmm0, xmmword ptr [rcx+rax] ; Calculate 4 square roots
vmovaps xmmword ptr [r8+rax], xmm0  ; Save the 4 result to destination
add rax, type xmmword ; Advance to the next 4 items (16 bytes)
sub rdx, 4
cmp rdx, 4
jae @B

; Calculate the square roots for the last items (<=3 => scalar instructions)
OneByOne:
test rdx, rdx
jz Done

vsqrtss xmm0, xmm0, real4 ptr [rcx+rax] ; Calculate one square roots
vmovss real4 ptr [r8+rax], xmm0	        ; Save the single result to destination
add rax, type real4 ; Advance to the next item (4 bytes)
dec rdx
jnz OneByOne 

Done:

ret

AVX_Packed_Array_Sqtr_Float_ endp

end