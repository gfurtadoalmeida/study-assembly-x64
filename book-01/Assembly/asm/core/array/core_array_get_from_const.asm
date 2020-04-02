.const
	Array dword 10, 20, 30, 40, 50
	Core_Array_Get_From_Const_ArrayLength_ dword ($ - Array) / sizeof dword

	public Core_Array_Get_From_Const_ArrayLength_

.code

; int Core_Array_Get_From_Const_(int position, int* value)
Core_Array_Get_From_Const_ proc 

; Error if < 0
cmp ecx, 0
jl InvalidIndex

; Error if >= array size
cmp ecx, dword ptr [Core_Array_Get_From_Const_ArrayLength_]
jge InvalidIndex

mov r8, offset Array
mov r9d, dword ptr [r8+rcx*type dword] ; Address = array position + (i * sizeof(int))
mov dword ptr [rdx], r9d
mov eax, 1
ret

InvalidIndex:
xor eax, eax
ret

Core_Array_Get_From_Const_ endp

end