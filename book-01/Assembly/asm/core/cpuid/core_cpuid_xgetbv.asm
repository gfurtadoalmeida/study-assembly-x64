.code

; uint32_t Core_CPUID_Xgetbv_(uint32_t * eax, uint32_t ecx, uint32_t * edx)
Core_CPUID_Xgetbv_ proc

mov r9, rcx  ; r9 = uint32_t eax
mov rcx, rdx ; rcx = uint32_t ecx

xgetbv

mov dword ptr [r9], eax ; Save low word result -> uint32_t eax
mov dword ptr [r8], edx ; Save high word result -> uint32_t edx

ret

Core_CPUID_Xgetbv_ endp

end