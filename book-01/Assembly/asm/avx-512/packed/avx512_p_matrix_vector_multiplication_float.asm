ConstVals segment readonly align(64) 'const'
	; Indices for matrix permutations
	MatPerm0 dword 0, 4, 8, 12, 0, 4, 8, 12, 0, 4, 8, 12, 0, 4, 8, 12
	MatPerm1 dword 1, 5, 9, 13, 1, 5, 9, 13, 1, 5, 9, 13, 1, 5, 9, 13
	MatPerm2 dword 2, 6, 10, 14, 2, 6, 10, 14, 2, 6, 10, 14, 2, 6, 10, 14
	MatPerm3 dword 3, 7, 11, 15, 3, 7, 11, 15, 3, 7, 11, 15, 3, 7, 11, 15
	
	; Indices for vector permutations
	VecPerm0 dword 0, 0, 0, 0, 4, 4, 4, 4, 8, 8, 8, 8, 12, 12, 12, 12
	VecPerm1 dword 1, 1, 1, 1, 5, 5, 5, 5, 9, 9, 9, 9, 13, 13, 13, 13
	VecPerm2 dword 2, 2, 2, 2, 6, 6, 6, 6, 10, 10, 10, 10, 14, 14, 14, 14
	VecPerm3 dword 3, 3, 3, 3, 7, 7, 7, 7, 11, 11, 11, 11, 15, 15, 15, 15
ConstVals ends

.code

; bool AVX512_Packed_Matrix_Vector_Multiplication_Float_(float matrix[4][4], Vector4x1_F32 * vectors, uint32_t vectorCount, Vector4x1_F32 * result)
AVX512_Packed_Matrix_Vector_Multiplication_Float_ proc

xor eax, eax

test r8, r8
jz Done ; Exit if vectorsCount is zero

test r8, 3
jnz Done ; Exit if vectorsCount % 4 != 0

test rcx, 3fh
jnz Done ; Exit if matrix is not 64 byte aligned

test rdx, 3fh
jnz Done ; Exit if vector is not 64 byte aligned

test r9, 3fh
jnz Done ; Exit if result is not 64 byte aligned

; Load permutation indices for matrix columns and vector elements
vmovdqa32 zmm16, zmmword ptr [MatPerm0] ; matrix column 0 indices
vmovdqa32 zmm17, zmmword ptr [MatPerm1] ; matrix column 1 indices
vmovdqa32 zmm18, zmmword ptr [MatPerm2] ; matrix column 2 indices
vmovdqa32 zmm19, zmmword ptr [MatPerm3] ; matrix column 3 indices

vmovdqa32 zmm24, zmmword ptr [VecPerm0] ; W component indices
vmovdqa32 zmm25, zmmword ptr [VecPerm1] ; X component indices
vmovdqa32 zmm26, zmmword ptr [VecPerm2] ; Y component indices
vmovdqa32 zmm27, zmmword ptr [VecPerm3] ; Z component indices

; Load source matrix and duplicate columns
vmovaps zmm0, zmmword ptr [rcx] ; zmm0 = matrix

vpermps zmm20, zmm16, zmm0 ; zmm20 = matrix column 0 (4x)
vpermps zmm21, zmm17, zmm0 ; zmm21 = matrix column 1 (4x)
vpermps zmm22, zmm18, zmm0 ; zmm22 = matrix column 2 (4x)
vpermps zmm23, zmm19, zmm0 ; zmm23 = matrix column 3 (4x)

; Load the next 4 vectors
align 16
@@:
vmovaps zmm4, zmmword ptr [rdx+rax] ; zmm4 = vector (4 vectors)

; Permute the vector elements for subsequent calculations
vpermps zmm0, zmm24, zmm4 ; zmm0 = vector W components
vpermps zmm1, zmm25, zmm4 ; zmm1 = vector X components
vpermps zmm2, zmm26, zmm4 ; zmm2 = vector Y components
vpermps zmm3, zmm27, zmm4 ; zmm3 = vector Z components

; Perform matrix-vector multiplications (4 vectors)
vmulps zmm28, zmm20, zmm0
vmulps zmm29, zmm21, zmm1
vmulps zmm30, zmm22, zmm2
vmulps zmm31, zmm23, zmm3
vaddps zmm4, zmm28, zmm29
vaddps zmm5, zmm30, zmm31
vaddps zmm4, zmm4, zmm5 ; zmm4 = result (4 vectors)

vmovaps zmmword ptr [r9+rax], zmm4 ; Save result

add rax, type zmmword
sub r8, 4
jnz @B

mov eax, 1

Done:
vzeroupper
ret

AVX512_Packed_Matrix_Vector_Multiplication_Float_ endp

end