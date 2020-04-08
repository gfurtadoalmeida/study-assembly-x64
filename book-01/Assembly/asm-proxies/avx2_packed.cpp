#include "../asm-headers/__declarations.h"
#include "../asm-headers/avx2_packed.h"

namespace Assembly {
	namespace AVX2 {
		namespace Packed {

			void Permute_Float(YmmVal* src, YmmVal* des, YmmVal* indexes)
			{
				AVX2_Packed_Permute_Float_(src, des, indexes);
			}
		}
	}
}