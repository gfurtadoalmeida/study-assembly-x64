#include "../asm-headers/__declarations.h"
#include "../asm-headers/avx512_packed.h"

namespace Assembly {
	namespace AVX512 {
		namespace Packed {

			void Compare_Double(const ZmmVal* a, const ZmmVal* b, uint8_t result[8])
			{
				AVX512_Packed_Compare_Double_(a, b, result);
			}

			void Compare_Float(const ZmmVal* a, const ZmmVal* b, uint16_t result[8])
			{
				AVX512_Packed_Compare_Float_(a, b, result);
			}

			void Math_Double(const ZmmVal* a, const ZmmVal* b, ZmmVal result[8])
			{
				AVX512_Packed_Math_Double_(a, b, result);
			}

			void Math_Float(const ZmmVal* a, const ZmmVal* b, ZmmVal result[8])
			{
				AVX512_Packed_Math_Float_(a, b, result);
			}
			
			void Math_Long(const ZmmVal* a, const ZmmVal* b, ZmmVal result[5], uint32_t operationMask)
			{
				AVX512_Packed_Math_Long_(a, b, result, operationMask);
			}

			void Math_Short(const ZmmVal* a, const ZmmVal* b, ZmmVal result[6])
			{
				AVX512_Packed_Math_Short_(a, b, result);
			}

			bool Matrix_Vector_Multiplication_Float(float matrix[4][4], Vector4x1_F32* vectors, uint32_t vectorCount, Vector4x1_F32* result)
			{
				return AVX512_Packed_Matrix_Vector_Multiplication_Float_(matrix, vectors, vectorCount, result);
			}

			bool Vector_Cross_Product(const Vector* a, const Vector* b, Vector* result, uint32_t length)
			{
				return AVX512_Packed_Vector_Cross_Product_(a, b, result, length);
			}
		}
	}
}