#include "../asm-headers/__declarations.h"
#include "../asm-headers/core_math.h"

namespace Assembly {
	namespace Core {
		namespace Math {

			bool Div(int32_t a, int32_t b, int32_t* quotient, int32_t* remainder)
			{
				return Core_Math_Div_(a, b, quotient, remainder);
			}

			int32_t Max(int32_t a, int32_t b, int32_t c)
			{
				return Core_Math_Max_(a, b, c);
			}

			int32_t Max_v2(int32_t a, int32_t b, int32_t c)
			{
				return Core_Math_Max_v2_(a, b, c);
			}
			
			int32_t Min(int32_t a, int32_t b, int32_t c)
			{
				return Core_Math_Min_(a, b, c);
			}

			int32_t Min_v2(int32_t a, int32_t b, int32_t c)
			{
				return Core_Math_Min_v2_(a, b, c);
			}

			int32_t Sum(int32_t a, int32_t b)
			{
				return Core_Math_Sum_(a, b);
			}
		}
	}
}