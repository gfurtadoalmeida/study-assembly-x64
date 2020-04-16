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

			bool Vector_Cross_Product(const Vector* a, const Vector* b, Vector* result, uint32_t length)
			{
				return AVX512_Packed_Vector_Cross_Product_(a, b, result, length);
			}
		}
	}
}