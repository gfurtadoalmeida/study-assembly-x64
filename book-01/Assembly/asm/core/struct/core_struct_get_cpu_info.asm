.code

ProcessorInfo struct
	Vendor byte 13 DUP(?) 
	ModelName byte 49 DUP(?)  ; Do not use "Name" as it is mistaken as an ignored directive ".NAME"
ProcessorInfo ends

; bool Core_Struct_Get_CPU_Info_(const ProcessorInfo* processorInfo)
Core_Struct_Get_CPU_Info_ proc frame

; Prolog

push rsi
.pushreg rsi
push rdi
.pushreg rdi
push rbx
.pushreg rbx
.endprolog

mov rsi, rcx ; Cpuid modifies ecx, this will be base address
mov rdi, rcx ; Increment address for address calculation

xor eax, eax ; Cpuid level 0 = vendor id name
cpuid

; EBX-EDX-ECX contains at most 12 ASCII characters
; representing the Vendor ID Name.
mov dword ptr [rdi+ProcessorInfo.Vendor], ebx
add rdi, type dword
mov dword ptr [rdi+ProcessorInfo.Vendor], edx
add rdi, type dword
mov dword ptr [rdi+ProcessorInfo.Vendor], ecx
add rdi, type dword
mov byte ptr [rdi+ProcessorInfo.Vendor], 0 ; null terminator

mov rdi, rsi       ; Restore base address on address calculation register
mov r8d, 80000002h ; Cpuid level 8000_0002h, 8000_0003h, and 8000_0004h = processor name

@@:
mov eax, r8d
cpuid

; Processor name order: eax, ebx, ecx, edx
mov dword ptr [rdi+ProcessorInfo.ModelName], eax
add rdi, type dword
mov dword ptr [rdi+ProcessorInfo.ModelName], ebx
add rdi, type dword
mov dword ptr [rdi+ProcessorInfo.ModelName], ecx
add rdi, type dword
mov dword ptr [rdi+ProcessorInfo.ModelName], edx
add rdi, type dword

inc r8d
cmp r8d, 80000004h
jle @B

mov byte ptr [rdi+ProcessorInfo.ModelName], 0 ; Null terminator

mov eax, 1 ; Success

; Epilog
pop rbx
pop rdi
pop rsi

ret

Core_Struct_Get_CPU_Info_ endp

end