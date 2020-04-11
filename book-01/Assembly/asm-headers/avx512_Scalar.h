#pragma once

#include "types_avx.h"

namespace Assembly {
	namespace AVX512 {
		namespace Scalar {

			__declspec(dllexport) bool Calc_Sphere_Area_Volume(double radius, double* area, double* volume, double errorValue);
		}
	}
}