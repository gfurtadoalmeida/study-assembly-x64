#pragma once

#include "types_avx.h"

namespace Assembly {
	namespace AVX {
		namespace Packed {

			__declspec(dllexport) bool Array_Max_Byte(const uint8_t* input, uint32_t arrayLength, uint8_t* result);
			__declspec(dllexport) bool Array_Min_Byte(const uint8_t* input, uint32_t arrayLength, uint8_t* result);
			__declspec(dllexport) bool Array_Max_Float(const float* input, uint32_t arrayLength, float* result);
			__declspec(dllexport) bool Array_Min_Float(const float* input, uint32_t arrayLength, float* result);
			__declspec(dllexport) void Array_Sqtr_Float(float* input, uint32_t arrayLength, const float* result);
			__declspec(dllexport) void Compare_Equal_Double(const XmmVal& a, const XmmVal& b, XmmVal results[]);
			__declspec(dllexport) bool Convert_Number(const XmmVal& source, const XmmVal& destination, CvtOp operation);
			__declspec(dllexport) void Matrix_Multiplication_Float(const float* a, const float* b, float* result);
			__declspec(dllexport) void Matrix_Transpose_Float(float* input, const float* result);
			__declspec(dllexport) void Multiply_Int_A(const XmmVal& a, const XmmVal& b, XmmVal results[2]);
			__declspec(dllexport) void Multiply_Int_B(const XmmVal& a, const XmmVal& b, XmmVal& results);
			__declspec(dllexport) void Multiply_Short(const XmmVal& a, const XmmVal& b, XmmVal results[2]);
			__declspec(dllexport) bool Shift_Integer(const XmmVal& input, XmmVal& results, ShiftOp shift_op, uint32_t count);
			__declspec(dllexport) void Sum_Float(const XmmVal& a, const XmmVal& b, XmmVal results[]);
			__declspec(dllexport) void Sum_Short(const XmmVal& a, const XmmVal& b, XmmVal results[2]);
		}
	}
}