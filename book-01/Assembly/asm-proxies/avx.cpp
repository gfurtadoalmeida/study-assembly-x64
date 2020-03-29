#include "../asm-headers/__declarations.h"
#include "../asm-headers/avx.h"

namespace Assembly {
	namespace AVX {

		RoundingMode Get_Rounding_Mode()
		{
			return AVX_Get_Rounding_Mode_();
		}

		void Set_Rounding_Mode(const RoundingMode roundingMode)
		{
			AVX_Set_Rounding_Mode_(roundingMode);
		}
	}
}