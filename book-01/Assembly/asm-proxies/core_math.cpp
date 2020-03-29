#include "../asm-headers/__declarations.h"
#include "../asm-headers/core_math.h"

namespace Assembly {
	namespace Core {
		namespace Math {

			int Div(int a, int b, int* quotient, int* remainder)
			{
				return Core_Math_Div_(a, b, quotient, remainder);
			}

			int Max(int a, int b, int c)
			{
				return Core_Math_Max_(a, b, c);
			}

			int Max_v2(int a, int b, int c)
			{
				return Core_Math_Max_v2_(a, b, c);
			}
			
			int Min(int a, int b, int c)
			{
				return Core_Math_Min_(a, b, c);
			}

			int Min_v2(int a, int b, int c)
			{
				return Core_Math_Min_v2_(a, b, c);
			}

			int Sum(int a, int b)
			{
				return Core_Math_Sum_(a, b);
			}
		}
	}
}