.code

; int Core_Math_Min_(int a, int b, int c)
Core_Math_Min_ proc

mov eax, ecx
cmp eax, edx

jle @F

mov eax, edx

@@: 
cmp eax, r8d

jle @F

mov eax, r8d

@@: 
ret

Core_Math_Min_ endp

; int Core_Math_Min_v2_(int a, int b, int c)
Core_Math_Min_v2_ proc

cmp ecx, edx
cmovg ecx, edx

cmp ecx, r8d
cmovg ecx, r8d

mov eax, ecx
ret

Core_Math_Min_v2_ endp

; int Core_Math_Max_(int a, int b, int c)
Core_Math_Max_ proc

mov eax, ecx
cmp eax, edx

jge @F

mov eax, edx

@@: 
cmp eax, r8d

jge @F

mov eax, r8d

@@: 
ret

Core_Math_Max_ endp

; int Core_Math_Max_v2_(int a, int b, int c)
Core_Math_Max_v2_ proc

cmp ecx, edx
cmovl ecx, edx

cmp ecx, r8d
cmovl ecx, r8d

mov eax, ecx
ret

Core_Math_Max_v2_ endp

end