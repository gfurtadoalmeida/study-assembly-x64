#include "../asm-headers/__declarations.h"
#include "../asm-headers/avx512_scalar.h"

namespace Assembly {
	namespace AVX512 {
		namespace Scalar {
			
			bool Calc_Conditional_Sum_Zero_Masking(double* a, double* b, double* result, uint32_t length, double valueToIgnore)
			{
				return AVX512_Scalar_Calc_Conditional_Sum_Zero_Masking_(a, b, result, length, valueToIgnore);
			}

			bool Calc_Sphere_Area_Volume(double radius, double* area, double* volume, double errorValue)
			{
				return AVX512_Scalar_Calc_Sphere_Area_Volume_(radius, area, volume, errorValue);
			}
		}
	}
}