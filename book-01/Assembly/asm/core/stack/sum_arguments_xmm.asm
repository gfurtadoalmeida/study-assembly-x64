.code

; double Core_Stack_Sum_Arguments_Xmm_(double a, double b, double c, double d, double e, double f, double g, double h)
Core_Stack_Sum_Arguments_Xmm_ proc frame

; Prolog

; 4 xmm registers will be save on stack = 64 bytes
STACK_XMM_REGS_SIZE = 4*type xmmword

; 4 double parameters (e,f,g,h) passed in the stack
; Offset = rbp + SIZE_REGS_PUSHED + STACK_XMM_REGS_SIZE + old rbp + return value + rcx + rdx + r8 + r9
STACK_PARAMS_OFFSET = STACK_XMM_REGS_SIZE+6*type qword

push rbp
.pushreg rbp

; Allocate space to save 4 xmm registers.
; Return value is at: rsp + STACK_PARAMS_SIZE + STACK_XMM_REGS_SIZE 
sub rsp, STACK_XMM_REGS_SIZE 
.allocstack STACK_XMM_REGS_SIZE 

mov rbp, rsp
.setframe rbp, 0

; Save non-volatile xmm registers
movdqa xmmword ptr [rbp], xmm12
.savexmm128 xmm12, 0
movdqa xmmword ptr [rbp+16], xmm13
.savexmm128 xmm13, 16
movdqa xmmword ptr [rbp+32], xmm14
.savexmm128 xmm14, 32
movdqa xmmword ptr [rbp+48], xmm15
.savexmm128 xmm15, 48

.endprolog

; Move params from stack to registers
vmovsd xmm12, real8 ptr [rbp+STACK_PARAMS_OFFSET+24] ; xmm12 = e
vmovsd xmm13, real8 ptr [rbp+STACK_PARAMS_OFFSET+16] ; xmm13 = f
vmovsd xmm14, real8 ptr [rbp+STACK_PARAMS_OFFSET+8]  ; xmm14 = g
vmovsd xmm15, real8 ptr [rbp+STACK_PARAMS_OFFSET]    ; xmm15 = h

; Sum all values
vaddsd xmm0, xmm0, xmm1
vaddsd xmm0, xmm0, xmm2
vaddsd xmm0, xmm0, xmm3
vaddsd xmm0, xmm0, xmm12
vaddsd xmm0, xmm0, xmm13
vaddsd xmm0, xmm0, xmm14
vaddsd xmm0, xmm0, xmm15

; Epilog

; Restore xmm registers
vmovdqa xmm12, xmmword ptr [rbp] 
vmovdqa xmm13, xmmword ptr [rbp+16]
vmovdqa xmm14, xmmword ptr [rbp+32]
vmovdqa xmm15, xmmword ptr [rbp+48]

add rsp, STACK_XMM_REGS_SIZE
pop rbp

ret

Core_Stack_Sum_Arguments_Xmm_ endp

end
