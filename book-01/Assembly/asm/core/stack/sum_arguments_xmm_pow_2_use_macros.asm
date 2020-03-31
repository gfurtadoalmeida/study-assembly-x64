include macros.inc

.code

extern pow:proc

; double Core_Stack_Sum_Arguments_Xmm_Pow_2_Use_Macros_(double a, double b, double c, double d, double e, double f, double g, double h)
Core_Stack_Sum_Arguments_Xmm_Pow_2_Use_Macros_ proc frame

; Prolog
; Local variables: 2 double
_CreateFrame MyStack_, 32, 64, r12
_SaveXmmRegs xmm12, xmm13, xmm14, xmm15

.endprolog

; Move params from stack to registers
vmovsd xmm12, real8 ptr [rbp+MyStack_OffsetStackArgs+24] ; xmm12 = e
vmovsd xmm13, real8 ptr [rbp+MyStack_OffsetStackArgs+16] ; xmm13 = f
vmovsd xmm14, real8 ptr [rbp+MyStack_OffsetStackArgs+8]  ; xmm14 = g
vmovsd xmm15, real8 ptr [rbp+MyStack_OffsetStackArgs]    ; xmm15 = h

; Sum all values
vaddsd xmm0, xmm0, xmm1
vaddsd xmm0, xmm0, xmm2
vaddsd xmm0, xmm0, xmm3
vaddsd xmm0, xmm0, xmm12
vaddsd xmm0, xmm0, xmm13
vaddsd xmm0, xmm0, xmm14
vaddsd xmm0, xmm0, xmm15

; Save the xmm0/1 into the stack.
; Completely unnecessary as their values would
; not be used in the end.
; Was done to learn how to use the variable 
; local space created by the macro.
movd real8 ptr [rbp], xmm0
movd real8 ptr [rbp+type qword], xmm1

; As any function can modify rcx,rdx,r8,r9, the register
; r12 was used. Unecessary again but made to learn.
mov r12, 2
vcvtsi2sd xmm1, xmm1, r12 ; xmm1 = 2.0
sub rsp, type qword*4	  ; Allocate registers home (ecx,edx,r8,r9) for math::pow
call pow                  ; xmm0 = pow(xmm0, xmm1) = pow (sum, 2.0)

vaddsd xmm0, xmm0, real8 ptr [rbp]            ; xmm0 += sum
vaddsd xmm0, xmm0, real8 ptr [rbp+type real8] ; xmm0 += original xmm1

; Epilog
_RestoreXmmRegs xmm12, xmm13, xmm14, xmm15
_DeleteFrame r12

ret

Core_Stack_Sum_Arguments_Xmm_Pow_2_Use_Macros_ endp

end
