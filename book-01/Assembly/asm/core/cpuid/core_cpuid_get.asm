; Must foollow the same structure as
; defined in "core_cpuid.h".
CpuidRegs struct
    RegEAX dword ?
    RegEBX dword ?
    RegECX dword ?
    RegEDX dword ?
CpuidRegs ends

.code
; uint32_t Core_CPUID_Get_(uint32_t eax, uint32_t ecx, CpuidRegs * result)
Core_CPUID_Get_ proc frame

; Prolog
push rbx
.pushreg rbx
.endprolog

; Yeah, bit confusing, just remember:
; ecx -> uint32_t eax
; edx -> uint32_t ecx
mov eax, ecx
mov ecx, edx

cpuid

mov dword ptr [r8+CpuidRegs.RegEAX], eax
mov dword ptr [r8+CpuidRegs.RegEBX], ebx
mov dword ptr [r8+CpuidRegs.RegECX], ecx
mov dword ptr [r8+CpuidRegs.RegEDX], edx

; Test for unsupported CPUID leaf
or eax, ebx
or ecx, edx
or eax, ecx

; Epilog
pop rbx

ret

Core_CPUID_Get_ endp

end