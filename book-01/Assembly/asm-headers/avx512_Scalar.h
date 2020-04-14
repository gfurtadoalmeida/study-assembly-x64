#pragma once

#include "types_avx.h"

namespace Assembly {
	namespace AVX512 {
		namespace Scalar {

			__declspec(dllexport) bool Calc_Conditional_Sum_Zero_Masking(const double* a, const double* b, double* result, uint32_t length, double valueToIgnore);
			__declspec(dllexport) bool Calc_Sphere_Area_Volume(double radius, double* area, double* volume, double errorValue);
			__declspec(dllexport) void Convert_Round_F32_U32(float value, uint32_t result[4]);
			__declspec(dllexport) void Convert_Round_F64_F32(double value, float result[4]);
			__declspec(dllexport) void Convert_Round_F64_U64(double value, uint64_t result[4]);
		}
	}
}