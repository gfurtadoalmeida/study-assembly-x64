
; Must match the type defined at
; 'types_avx.h'.
PixelClipData struct 
	Source           qword ?
	Destination      qword ?
	NumPixels        qword ?
	NumClippedPixels qword ?
	ThresholdLow     byte ?
	ThresholdHigh    byte ?
PixelClipData ends

.code

; bool AVX2_Packed_Clip_Pixel_Gray_Image_(PixelClipData * pcd)
AVX2_Packed_Clip_Pixel_Gray_Image_ proc

xor rax, rax ; Success status
xor r8, r8   ; Cliped pixels count

mov rdx, [rcx+PixelClipData.NumPixels]
or rdx, rdx
jz Done

; We need at least 32 pixels and count
; must be multiple of 32.
test rdx, 1fh
jnz Done

mov r10, [rcx+PixelClipData.Source]
test r10, 1fh
jnz Done

mov r11, [rcx+PixelClipData.Destination]
test r11, 1fh
jnz Done

vpbroadcastb ymm4, [rcx+PixelClipData.ThresholdLow]
vpbroadcastb ymm5, [rcx+PixelClipData.ThresholdHigh]

; Clip pixels to threshold values
@@:
vmovdqa ymm0, ymmword ptr [r10] ; Orignal values
vpmaxub ymm1, ymm0, ymm4		; High values replaced with threshold high
vpminub ymm2, ymm1, ymm5		; Low values replaced with threshold low
vmovdqa ymmword ptr [r11], ymm2

; Count number of clipped pixels.
; vpcmpeqb compares for equality and set the destination
; operando to all 1's when equal (not clipped), otherwise 0's.
;
; A = | 00001010 | 00110010 | 01010000 |
; B = | 00001010 | 00101000 | 00011110 |
;                     ==
; D = | 11111111 | 00000000 | 00000000 |
;
; vpmovmskb copies the most significant bit of each element
; on a ymm register to a r64 register. In this case, each 1
; means a non-cliped pixel.
;
; D = | 11111111 | 00000000 | 00000000 |
; R = 000...100
;
; We then invert it so the 0's of the clipped pixels become 1's.
; not(R) = 011
;
; popcnt counts the number of 1's on a value.
; popcnt(R) = popcnt(011) = 2
;
; This example clipped 2 pixels.

vpcmpeqb ymm3, ymm2, ymm0
vpmovmskb eax, ymm3
not eax
popcnt eax, eax
add r8, rax

add r10, type ymmword ; Advance source
add r11, type ymmword ; Advance destination
sub rdx, type ymmword ; Decrement counter
jnz @B

mov eax, 1

Done:
mov [rcx+PixelClipData.NumClippedPixels], r8

vzeroupper
ret

AVX2_Packed_Clip_Pixel_Gray_Image_ endp

end