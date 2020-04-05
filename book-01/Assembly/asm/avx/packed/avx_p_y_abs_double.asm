.const
	; We can't use "align 32" because MASM does not support it.
	; "dup" create N copies of the value in the parantheses.
	; AbsMask = array with 4 items with value of 7fffffffffffffffh.
	AbsMask qword 4 dup(7fffffffffffffffh)

.code

; void AVX_Packed_Y_Abs_Double_(const YmmVal & input, YmmVal results[])
AVX_Packed_Y_Abs_Double_ proc

xor rax, rax

vmovaps ymm0, ymmword ptr [rcx]

; Will clear the sign bit, the most significant one.
vandps ymm1, ymm0, ymmword ptr [AbsMask]

vmovaps ymmword ptr [rdx], ymm1

vzeroupper

ret

AVX_Packed_Y_Abs_Double_ endp

end