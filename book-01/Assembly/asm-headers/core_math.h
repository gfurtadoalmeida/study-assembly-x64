#pragma once

namespace Assembly {
	namespace Core {
		namespace Math {

			__declspec(dllexport) bool Div(int32_t a, int32_t b, int32_t * quotient, int32_t * remainder);
			__declspec(dllexport) int32_t Max(int32_t a, int32_t b, int32_t c);
			__declspec(dllexport) int32_t Max_v2(int32_t a, int32_t b, int32_t c);
			__declspec(dllexport) int32_t Min(int32_t a, int32_t b, int32_t c);
			__declspec(dllexport) int32_t Min_v2(int32_t a, int32_t b, int32_t c);
			__declspec(dllexport) int32_t Sum(int32_t a, int32_t b);
		}
	}
}