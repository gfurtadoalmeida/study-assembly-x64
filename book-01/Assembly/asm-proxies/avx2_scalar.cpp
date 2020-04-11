#include "../asm-headers/__declarations.h"
#include "../asm-headers/avx2_scalar.h"

namespace Assembly {
	namespace AVX2 {
		namespace Scalar {

			uint32_t And_Not(uint32_t a, uint32_t b)
			{
				return AVX2_Scalar_And_Not_(a, b);
			}

			void Count_Zero_Bits(uint32_t value, uint32_t* leadingZeros, uint32_t* trailingZeros)
			{
				AVX2_Scalar_Count_Zero_Bits_(value, leadingZeros, trailingZeros);
			}

			uint32_t Extract_Bits(uint32_t value, uint8_t start, uint8_t length)
			{
				return AVX2_Scalar_Extract_Bits_(value, start, length);
			}

			uint64_t Flagless_Multiply_UInt(uint32_t a, uint32_t b, uint64_t flags[2])
			{
				return AVX2_Scalar_Flagless_Multiply_UInt_(a, b, flags);
			}

			void Flagless_Shift_UInt(uint32_t value, uint32_t count, uint32_t results[3], uint64_t flags[4])
			{
				AVX2_Scalar_Flagless_Shift_UInt_(value, count, results, flags);
			}
		}
	}
}