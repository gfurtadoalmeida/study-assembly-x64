#pragma once
#include "types_avx.h"

using namespace Assembly::AVX::Types;

namespace Assembly {
	namespace AVX {

		__declspec(dllexport) RoundingMode Get_Rounding_Mode();
		__declspec(dllexport) void Set_Rounding_Mode(const RoundingMode roudingMode);
	}
}