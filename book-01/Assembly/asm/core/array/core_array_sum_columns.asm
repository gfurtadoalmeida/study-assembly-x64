.code

; int Core_Array_Sum_Columns_(int* sourceMatrix, int* destinationArray, int numRows, int numColumns)
Core_Array_Sum_Columns_ proc frame

; Prolog
push rsi
.pushreg rsi
push rdi
.pushreg rdi
push rbx
.pushreg rbx
.endprolog

cmp r8d, 0
jle InvalidCount

cmp r9d, 0
jle InvalidCount

movsxd r8, r8d ; numRows sign-extended
movsxd r9, r9d ; numColumns sign-extended

mov rsi, rcx ; Source matrix
mov rdi, rdx ; Destination array

; Initialize destination array with zeros.
; Not necessary but it's fun to learn rep stosd
mov rbx, rdi ; Backing-up rdi as stosd modifies it
mov rcx, r8  ; Counter = numRows
xor eax, eax ; eax = fill value = 0
rep stosd    ; Fill RDI ecx times with eax

mov rdi, rbx ; rdi = backed up rdi
xor rcx, rcx ; i = 0

LoopRow:
xor rdx, rdx   ; j = 0
xor r10d, r10d ; temp

; Value = base + (((i * numColumns) + j) * sizeof(int))
LoopColumn:
mov rax, rcx ; rax = i
imul rax, r9 ; rax = rax * numColumns
add rax, rdx ; rax = rax + j
add r10d, dword ptr [rsi+rax*type dword] ; r10d = row/column value

inc rdx ; j++

cmp rdx, r9
jl LoopColumn

mov dword ptr [rdi+rcx*type dword], r10d

inc rcx ; i++

cmp rcx, r8
jl LoopRow

jmp Success

InvalidCount:
xor eax, eax ; Error

Success:
mov eax, 1   ; success

; epilog
pop rbx
pop rdi
pop rsi

ret

Core_Array_Sum_Columns_ endp

end