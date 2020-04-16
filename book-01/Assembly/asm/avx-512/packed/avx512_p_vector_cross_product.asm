; Indices for gather and scatter instructions.
;
; Vector array representation in memory:
; XYZ|XYZ|XYZ|XYZ
; V0  V1  V2  V3
;
; So, to access the vector V3 we need to access
; the locations 6, 7, 8.
; Using the gather indexes below, V3 would be:
; Index V3.X = idxGatherX[2] = 6
; Index V3.Y = idxGatherY[2] = 7
; Index V3.Z = idxGatherZ[2] = 8
;
; GS_X[i]GS_Y[i]GS_Z[i] = one vector
;
; Indexes of the first 8 vectors.
; The code uses the firsts 8 indexes and
; then calculate the next ones.
ConstVals segment readonly align(64) 'const'
	GS_X qword 0, 3, 6, 9, 12, 15, 18, 21 
	GS_Y qword 1, 4, 7, 10, 13, 16, 19, 22 
	GS_Z qword 2, 5, 8, 11, 14, 17, 20, 23 
ConstVals ends 

.code

; bool AVX512_Packed_Vector_Cross_Product_(const Vector * a, const Vector * b, Vector * result, uint32_t length)
AVX512_Packed_Vector_Cross_Product_ proc

xor eax, eax

test r9, r9  ; Stop if length == 0
jz Done

test r9, 07h ; Stop if length % 8 != 0
jnz Done

vmovdqa64 zmm29, zmmword ptr [GS_X] ; zmm29 = X component indices
vmovdqa64 zmm30, zmmword ptr [GS_Y] ; zmm30 = Y component indices
vmovdqa64 zmm31, zmmword ptr [GS_Z] ; zmm31 = Z component indices

align 16
@@:
; Set the first 8 bits to one, this way vgatherqpd will get 8 numbers.
; Not necessary and shown just to learn.
kxnorb k1, k1, k1
vgatherqpd zmm0{k1}, [rcx+zmm29*type real8] ; zmm0 = A.X values

kxnorb k2, k2, k2
vgatherqpd zmm1{k2}, [rcx+zmm30*type real8] ; zmm1 = A.Y values

kxnorb k3, k3, k3
vgatherqpd zmm2{k3}, [rcx+zmm31*type real8] ; zmm2 = A.Z values

kxnorb k4, k4, k4
vgatherqpd zmm3{k4}, [rdx+zmm29*type real8] ; zmm3 = B.X values

kxnorb k5, k5, k5
vgatherqpd zmm4{k5}, [rdx+zmm30*type real8] ; zmm4 = B.Y values

kxnorb k6, k6, k6
vgatherqpd zmm5{k6}, [rdx+zmm31*type real8] ; zmm5 = B.Z values

; Calculate 8 vector cross products
vmulpd zmm16, zmm1, zmm5
vmulpd zmm17, zmm2, zmm4
vsubpd zmm18, zmm16, zmm17 ; c.X = a.Y * b.Z - a.Z * b.Y

vmulpd zmm19, zmm2, zmm3
vmulpd zmm20, zmm0, zmm5
vsubpd zmm21, zmm19, zmm20 ; c.Y = a.Z * b.X - a.X * b.Z

vmulpd zmm22, zmm0, zmm4
vmulpd zmm23, zmm1, zmm3
vsubpd zmm24, zmm22, zmm23 ; c.Z = a.X * b.Y - a.Y * b.X

; Save calculated cross products
kxnorb k4, k4, k4
vscatterqpd [r8+zmm29*type real8]{k4}, zmm18 ; save C.X components

kxnorb k5, k5, k5
vscatterqpd [r8+zmm30*type real8]{k5}, zmm21 ; save C.Y components

kxnorb k6, k6, k6
vscatterqpd [r8+zmm31*type real8]{k6}, zmm24 ; save C.Z components 

; Update pointers and counters
add rcx, 192 ; a += 8 vectors * 3 numbers [x,y,z] * 8 bytes/number
add rdx, 192 ; b += 8 vectors * 3 numbers [x,y,z] * 8 bytes/number
add r8, 192  ; c += 8 vectors * 3 numbers [x,y,z] * 8 bytes/number
add rax, 8
cmp rax, r9
jb @B

mov eax, 1

Done:
vzeroupper
ret

AVX512_Packed_Vector_Cross_Product_ endp

end