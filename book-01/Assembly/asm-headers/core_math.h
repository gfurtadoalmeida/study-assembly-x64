#pragma once

namespace Assembly {
	namespace Core {
		namespace Math {

			__declspec(dllexport) int Div(int a, int b, int* quotient, int* remainder);
			__declspec(dllexport) int Max(int a, int b, int c);
			__declspec(dllexport) int Max_v2(int a, int b, int c);
			__declspec(dllexport) int Min(int a, int b, int c);
			__declspec(dllexport) int Min_v2(int a, int b, int c);
			__declspec(dllexport) int Sum(int a, int b);
		}
	}
}