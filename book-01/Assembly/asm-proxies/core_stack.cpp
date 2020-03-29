#include <cstdint>
#include "../asm-headers/__declarations.h"
#include "../asm-headers/core_stack.h"

namespace Assembly {
	namespace Core {
		namespace Stack {

			int64_t Sum_Arguments(int8_t a, int16_t b, int32_t c, int64_t d, int8_t e, int16_t f, int32_t g, int64_t h)
			{
				return Core_Stack_Sum_Arguments_(a, b, c, d, e, f, g, h);
			}

			double Sum_Arguments_Xmm(double a, double b, double c, double d, double e, double f, double g, double h)
			{
				return Core_Stack_Sum_Arguments_Xmm_(a, b, c, d, e, f, g, h);
			}

			double Sum_Arguments_Xmm_Pow_2_Use_Macros(double a, double b, double c, double d, double e, double f, double g, double h)
			{
				return Core_Stack_Sum_Arguments_Xmm_Pow_2_Use_Macros_(a, b, c, d, e, f, g, h);
			}
		}
	}
}