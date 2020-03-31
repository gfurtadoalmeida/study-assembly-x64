#pragma once

#include "types_avx.h"

namespace Assembly {
	namespace AVX {
		namespace Packed {

			__declspec(dllexport) void Array_Float_Sqrt(float* input, const float* output, int arrayLength);
			__declspec(dllexport) void Compare_Doubles_Equal(const XmmVal& a, const XmmVal& b, XmmVal results[]);
			__declspec(dllexport) bool Convert_Numbers(const XmmVal& source, const XmmVal& destination, CvtOp operation);
			__declspec(dllexport) bool Find_Array_Float_Max(const float* input, int arrayLength, float* result);
			__declspec(dllexport) bool Find_Array_Float_Min(const float* input, int arrayLength, float* result);
			__declspec(dllexport) void Matrix_Float_Transpose(float* input, const float* result);
			__declspec(dllexport) void Sum_Floats(const XmmVal& a, const XmmVal& b, XmmVal results[]);
		}
	}
}