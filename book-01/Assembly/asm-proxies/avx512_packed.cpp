#include "../asm-headers/__declarations.h"
#include "../asm-headers/avx512_packed.h"

namespace Assembly {
	namespace AVX512 {
		namespace Packed {

			void Math_Double(const ZmmVal* a, const ZmmVal* b, ZmmVal result[8])
			{
				AVX512_Packed_Math_Double_(a, b, result);
			}

			void Math_Float(const ZmmVal* a, const ZmmVal* b, ZmmVal result[8])
			{
				AVX512_Packed_Math_Float_(a, b, result);
			}
		}
	}
}