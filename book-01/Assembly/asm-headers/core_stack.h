#pragma once
#include <cstdint>

namespace Assembly {
	namespace Core {
		namespace Stack {

			__declspec(dllexport) int64_t Sum_Arguments(int8_t a, int16_t b, int32_t c, int64_t d, int8_t e, int16_t f, int32_t g, int64_t h);
			__declspec(dllexport) double Sum_Arguments_Xmm(double a, double b, double c, double d, double e, double f, double g, double h);
			__declspec(dllexport) double Sum_Arguments_Xmm_Pow_2_Use_Macros(double a, double b, double c, double d, double e, double f, double g, double h);
		}
	}
}