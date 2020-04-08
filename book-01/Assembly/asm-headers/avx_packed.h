#pragma once

#include "types_avx.h"

namespace Assembly {
	namespace AVX {
		namespace Packed {

			__declspec(dllexport) bool Array_Max_Byte(const uint8_t* input, uint32_t arrayLength, uint8_t* result);
			__declspec(dllexport) bool Array_Max_Float(const float* input, uint32_t arrayLength, float* result);
			__declspec(dllexport) bool Array_Mean_Byte(const uint8_t* input, uint32_t arrayLength, uint64_t* sum, double* mean);
			__declspec(dllexport) bool Array_Min_Byte(const uint8_t* input, uint32_t arrayLength, uint8_t* result);
			__declspec(dllexport) bool Array_Min_Float(const float* input, uint32_t arrayLength, float* result);
			__declspec(dllexport) void Array_Sqtr_Float(float* input, uint32_t arrayLength, const float* result);
			__declspec(dllexport) void Compare_Equal_Double(const XmmVal& a, const XmmVal& b, XmmVal results[]);
			__declspec(dllexport) bool Convert_Byte_To_Float_0_1_Range(const uint8_t* input, uint32_t arrayLength, float* output);
			__declspec(dllexport) bool Convert_Float_To_Byte_0_255_Range(const float* input, uint32_t arrayLength, uint8_t* output);
			__declspec(dllexport) bool Convert_Number(const XmmVal& source, const XmmVal& destination, CvtOp operation);
			__declspec(dllexport) bool Histogram_Gray_Image(const uint8_t* pixels, uint32_t numPixels, uint32_t* histogram);
			__declspec(dllexport) void Matrix_Multiplication_Float(const float* a, const float* b, float* result);
			__declspec(dllexport) void Matrix_Transpose_Float(float* input, const float* result);
			__declspec(dllexport) void Multiply_Int_A(const XmmVal& a, const XmmVal& b, XmmVal results[2]);
			__declspec(dllexport) void Multiply_Int_B(const XmmVal& a, const XmmVal& b, XmmVal& results);
			__declspec(dllexport) void Multiply_Short(const XmmVal& a, const XmmVal& b, XmmVal results[2]);
			__declspec(dllexport) bool Shift_Integer(const XmmVal& input, XmmVal& results, ShiftOp shift_op, uint32_t count);
			__declspec(dllexport) void Sum_Float(const XmmVal& a, const XmmVal& b, XmmVal results[]);
			__declspec(dllexport) void Sum_Short(const XmmVal& a, const XmmVal& b, XmmVal results[2]);
			__declspec(dllexport) void Y_Abs_Double(const YmmVal& input, YmmVal results[]);
			__declspec(dllexport) bool Y_Array_Cols_Mean_Double(const double* input, uint32_t numRows, uint32_t numCols, double* colMeans);
			__declspec(dllexport) void Y_Blend_Float(YmmVal * src1, YmmVal * src2, YmmVal * des, BlendSource blend[]);
			__declspec(dllexport) bool Y_Calc_Correlation_Coefficient(const double* x, const double* y, size_t arrayLength, double sums[5], double epsilon, double* rho);
			__declspec(dllexport) void Y_Calc_Sphere_Area_Volume(const float* radius, uint32_t arrayLength, float* areas, float* volumes, float qnanValue);
			__declspec(dllexport) void Y_Matrix_Multiplication_Double(const double* a, const double* b, double* result);
			__declspec(dllexport) void Y_Matrix_Transpose_Double(double* input, const double* result);
			__declspec(dllexport) void Y_Permute_Float(YmmVal * src, YmmVal * des, YmmVal * indexes);
			__declspec(dllexport) void Y_Sum_Float(const YmmVal& a, const YmmVal& b, YmmVal results[]);
		}
	}
}