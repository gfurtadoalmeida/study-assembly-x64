#pragma once

#include "types_avx.h"

namespace Assembly {
	namespace AVX2 {
		namespace Scalar {

			__declspec(dllexport) uint32_t And_Not(uint32_t a, uint32_t b);
			__declspec(dllexport) void Count_Zero_Bits(uint32_t value, uint32_t* leadingZeros, uint32_t* trailingZeros);
			__declspec(dllexport) uint32_t Extract_Bits(uint32_t value, uint8_t start, uint8_t length);
			__declspec(dllexport) uint64_t Flagless_Multiply_UInt(uint32_t a, uint32_t b, uint64_t flags[2]);
			__declspec(dllexport) void Flagless_Shift_UInt(uint32_t value, uint32_t count, uint32_t results[3], uint64_t flags[4]);
		}
	}
}