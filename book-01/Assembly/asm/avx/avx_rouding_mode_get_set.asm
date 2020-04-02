.code

; MXCSR flag bits
; 0	 =	  Invalid operation
; 1	 =	  Denormal
; 2	 =	  Division-by-zero
; 3	 =	  Overflow
; 4	 =	  Underflow
; 5	 =	  Precision
; 6	 =	  Denormals are zero
; 7	 =	  Invalid operation mask
; 8	 =	  Denormal operation mask
; 9  =	  Divide-by-zero mask
; 10 =	  Overflow mask
; 11 =	  Underflow mask
; 12 =	  Precision mask
; 13-14 = Rouding control
; 15 =    Flush to zero
; 16-31 = Reserved

; RoundingMode AVX_Get_Rounding_Mode_()
AVX_Get_Rounding_Mode_ proc

vstmxcsr dword ptr [rsp+type qword] ; Store mxcsr flags on top of the return value;
mov eax, dword ptr [rsp+type qword]
shr eax, 13 ; eax = MXCSR[13:31]
and eax, 3  ; eax = eax [0:2]

ret

AVX_Get_Rounding_Mode_ endp

; void AVX_Set_Rounding_Mode_(const RoundingMode roundingMode)
AVX_Set_Rounding_Mode_ proc

and ecx, 3  ; Remove unecessary bits
shl ecx, 13 ; Move the bits to their correct position regarding mxcsr

vstmxcsr dword ptr [rsp+type qword] ; Save current mcxsr
mov eax, dword ptr [rsp+type qword]
and eax, 9fffh ; 1001 1111 1111 1111 = will clear bits bits 13:14
or eax, ecx    ; Merge the bits into the right place

mov dword ptr [rsp+type qword], eax
vldmxcsr dword ptr [rsp+type qword]

ret

AVX_Set_Rounding_Mode_ endp

end