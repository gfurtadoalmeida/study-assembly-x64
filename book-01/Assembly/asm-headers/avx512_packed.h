#pragma once

#include "types_avx.h"

namespace Assembly {
	namespace AVX512 {
		namespace Packed {

			__declspec(dllexport) void Compare_Double(const ZmmVal* a, const ZmmVal* b, uint8_t result[8]);
			__declspec(dllexport) void Compare_Float(const ZmmVal* a, const ZmmVal* b, uint16_t result[8]);
			__declspec(dllexport) void Math_Double(const ZmmVal* a, const ZmmVal* b, ZmmVal result[8]);
			__declspec(dllexport) void Math_Float(const ZmmVal* a, const ZmmVal* b, ZmmVal result[8]);
			__declspec(dllexport) bool Matrix_Vector_Multiplication_Float(float matrix[4][4], Vector4x1_F32* vectors, uint32_t vectorCount, Vector4x1_F32* result);
			__declspec(dllexport) bool Vector_Cross_Product(const Vector* a, const Vector* b, Vector* result, uint32_t length);
		}
	}
}