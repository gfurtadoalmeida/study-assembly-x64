#pragma once

#include "types_avx.h"

namespace Assembly {
	namespace AVX512 {
		namespace Scalar {

			__declspec(dllexport) bool Calc_Conditional_Sum_Zero_Masking(double* a, double* b, double* result, uint32_t length, double valueToIgnore);
			__declspec(dllexport) bool Calc_Sphere_Area_Volume(double radius, double* area, double* volume, double errorValue);
		}
	}
}