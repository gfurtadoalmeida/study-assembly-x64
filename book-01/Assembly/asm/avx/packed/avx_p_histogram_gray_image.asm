include macros.inc

.code

; bool AVX_Packed_Histogram_Gray_Image_(const uint8_t * pixels, uint32_t numPixels, uint32_t * histogram)
AVX_Packed_Histogram_Gray_Image_ proc frame

; 1 KB of memory for histogram.
; 1 KB = 255 gray scales intensities * sizeof(uint32_t) + 4 bytes for padding
_CreateFrame BIH_, 1024, 0, rbx, rsi, rdi, r10, r11
_EndProlog

xor eax, eax

test rdx, rdx
jz InvalidArg

test rcx, 0fh
jnz InvalidArg

test r8, 0fh
jnz InvalidArg

; Initilize histogram and buffers with zeros:
;   r9  = pixels input
;   rsi = histogram output
;   rbp = stack allocated buffer
; Why 128 and not 255:
;   1. rep stosq will operate on 64 bits address size.
;   2. We'll generate 32 bits per pixel intensity (uint32_t).
;   3. It means that each 64 bits address can hold 2 pixel intensity results.
;   4. So we need only 128 iterations to zero the memory needed for 255 pixel intensitites (uint32_t).
; * It only works because we're compiling for x64. On x86 we'd need 255 iterations.
mov r9, rcx
mov rsi, r8
mov rdi, rsi
mov rcx, 128
rep stosq    ; Stores rax (0) at rdi(r8=histogram), rcx times.
mov rdi, rbp
mov rcx, 128
rep stosq    ; Stores rax (0) at rdi(rbp=allocated stack), rcx times.

mov rdi, rbp ; rdi = stack allocated buffer

; Saving registers values for later
mov r10, rdx

; arrayLength >> 4 = arrayLength % 16 = Number of blocks with 16 pixels
mov r11, rdx 
shr r11, 4
jz OneByOne

; Aligning the target of a jump instruction on a 16-byte boundary 
; is an optimization technique that often improves performance.
align 16

; Calculate histogram values:
;   1. Every pixel intensity (0-255) has a unique address initialized with zero.
;   2. Intensity address = output address + (pixel intensity * sizeof(uint32_t))
;   3. Add one to the address calculated.
;   4. vpextrb = extracts the byte at position 'P'.
;
; Why not just use the output address instead of doing half on stack and half
; main memory:
;   1. It's faster to access stack memory than main memory.
;
@@:
vmovdqa xmm0, xmmword ptr [r9] ; Contains 16 uint8_t pixels

; Process pixels 0-3
vpextrb rax, xmm0, 0
vpextrb rbx, xmm0, 1
vpextrb rcx, xmm0, 2
vpextrb rdx, xmm0, 3
add dword ptr [rsi+rax*type dword], 1
add dword ptr [rdi+rbx*type dword], 1
add dword ptr [rsi+rcx*type dword], 1
add dword ptr [rdi+rdx*type dword], 1

; Process pixels 4-7
vpextrb rax, xmm0, 4
vpextrb rbx, xmm0, 5
vpextrb rcx, xmm0, 6
vpextrb rdx, xmm0, 7
add dword ptr [rsi+rax*type dword], 1
add dword ptr [rdi+rbx*type dword], 1
add dword ptr [rsi+rcx*type dword], 1
add dword ptr [rdi+rdx*type dword], 1

; Process pixels 8-11
vpextrb rax, xmm0, 8
vpextrb rbx, xmm0, 9
vpextrb rcx, xmm0, 10
vpextrb rdx, xmm0, 11
add dword ptr [rsi+rax*type dword], 1
add dword ptr [rdi+rbx*type dword], 1
add dword ptr [rsi+rcx*type dword], 1
add dword ptr [rdi+rdx*type dword], 1

; Process pixels 12-15
vpextrb rax, xmm0, 12
vpextrb rbx, xmm0, 13
vpextrb rcx, xmm0, 14
vpextrb rdx, xmm0, 15
add dword ptr [rsi+rax*type dword], 1
add dword ptr [rdi+rbx*type dword], 1
add dword ptr [rsi+rcx*type dword], 1
add dword ptr [rdi+rdx*type dword], 1

add r9, 16  ; Get next 16 bytes or 16 pixels (uint8_t)
sub r10, 16 ; We've just processed 16 pixels
dec r11
jnz @B

; Merge the values into the histogram output:
;   rax = offset
;   rcx = counter = 64 iterations * 16 bytes per loop = 1024 bytes
xor rax, rax
mov ecx, 64

@@:
vmovdqa xmm0, xmmword ptr [rsi+rax]
vpaddd xmm0, xmm0, xmmword ptr [rdi+rax]

vmovdqa xmmword ptr [rsi+rax], xmm0

add rax, 16 ; We loaded 4 uint32_t (pixel intensity for a pixel) per xmm register = 16 bytes
dec ecx
jnz @B

xor rax, rax

OneByOne:
test r10, r10
jz Done

mov al, byte ptr [r9]
add dword ptr [rsi+rax*type dword], 1

inc r9
dec r10
jnz OneByOne

Done:

mov eax, 1

InvalidArg:

_DeleteFrame rbx, rsi, rdi, r10, r11

ret

AVX_Packed_Histogram_Gray_Image_ endp

end 