.code

; bool AVX_Packed_Y_Array_Cols_Mean_Double_(const double* input, uint32_t numRows, uint32_t numCols, double* colMeans)
AVX_Packed_Y_Array_Cols_Mean_Double_ proc

xor eax, eax

test rcx, 1fh ; Exit if not aligned
jnz InvalidArg

test r9, 1fh ; Exit if not aligned
jnz InvalidArg

test rdx, rdx ; Exit if numRows == 0
jz InvalidArg

test r8, r8   ; Exit if numCols == 0
jz InvalidArg

vxorpd xmm0, xmm0, xmm0
vcvtsi2sd xmm2, xmm2, rdx ; Convert rdx for later use

; Initialize output with zeros
@@:
vmovsd real8 ptr[r9+rax*type real8], xmm0
inc rax
cmp rax, r8
jb @B

; Compute the sum of each column in row X
LoopRow:
mov r11, r9  ; r11 = output pointer
xor r10, r10 ; r10 = processed columns counter

; 4 or more columns remaining?
; Jump if NO (col_index + 4 > numCols)
LoopColumn:
mov rax, r10
add rax, 4
cmp rax, r8
ja @F

; Update output using next four columns (4 doubles = 256 bits = ymm register = 32 bytes)
vmovupd ymm0, ymmword ptr [rcx]
vaddpd ymm1, ymm0, ymmword ptr [r11]
vmovupd ymmword ptr [r11], ymm1
add r10, 4
add rcx, 32
add r11, 32
jmp NextColSet

; 2 or more columns remaining?
; Jump if NO (col_index + 2 > numCols)
@@:
sub rax, 2
cmp rax, r8
ja @F

; Update output using next two columns (2 doubles = 128 bits = xmm register = 16 bytes)
vmovupd xmm0, xmmword ptr [rcx]
vaddpd xmm1, xmm0, xmmword ptr [r11]
vmovupd xmmword ptr [r11], xmm1
add r10, 2
add rcx, 16
add r11, 16
jmp NextColSet

; Update output using the last column (1 doubles = 64 bits = xmm register = 16 bytes)
@@:
vmovsd xmm0, real8 ptr [rcx]
vaddsd xmm1, xmm0, real8 ptr [r11]
vmovsd real8 ptr [r11], xmm1
inc r10
add rcx, 8

; More columns in current row?
NextColSet:
cmp r10, r8
jb LoopColumn ; Jump if more columns
dec rdx       ; numRows -= 1
jnz LoopRow   ; Jump if more rows

; Compute the final colMeans
@@:
vmovsd xmm0, real8 ptr [r9]
vdivsd xmm1, xmm0, xmm2
vmovsd real8 ptr [r9], xmm1
add r9, 8
dec r8
jnz @B

vzeroupper

mov rax, 1

InvalidArg:

ret

AVX_Packed_Y_Array_Cols_Mean_Double_ endp

end