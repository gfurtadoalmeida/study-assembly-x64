#include "../asm-headers/__declarations.h"
#include "../asm-headers/avx_packed.h"

namespace Assembly {
	namespace AVX {
		namespace Packed {

			bool Array_Max_Byte(const uint8_t* input, uint32_t arrayLength, uint8_t* result)
			{
				return AVX_Packed_Array_Max_Byte_(input, arrayLength, result);
			}

			bool Array_Max_Float(const float* input, uint32_t arrayLength, float* result)
			{
				return AVX_Packed_Array_Max_Float_(input, arrayLength, result);
			}

			bool Array_Mean_Byte(const uint8_t* input, uint32_t arrayLength, uint64_t* sum, double* mean)
			{
				return AVX_Packed_Array_Mean_Byte_(input, arrayLength, sum, mean);
			}

			bool Array_Min_Byte(const uint8_t* input, uint32_t arrayLength, uint8_t* result)
			{
				return AVX_Packed_Array_Min_Byte_(input, arrayLength, result);
			}

			bool Array_Min_Float(const float* input, uint32_t arrayLength, float* result)
			{
				return AVX_Packed_Array_Min_Float_(input, arrayLength, result);
			}

			void Array_Sqtr_Float(float* input, uint32_t arrayLength, const float* result)
			{
				AVX_Packed_Array_Sqtr_Float_(input, arrayLength, result);
			}

			void Compare_Equal_Double(const XmmVal& a, const XmmVal& b, XmmVal results[])
			{
				AVX_Packed_Compare_Equal_Double_(a, b, results);
			}

			bool Convert_Byte_To_Float_0_1_Range(const uint8_t* input, uint32_t arrayLength, float* output)
			{
				return AVX_Packed_Convert_Byte_To_Float_0_1_Range_(input, arrayLength, output);
			}

			bool Convert_Float_To_Byte_0_255_Range(const float* input, uint32_t arrayLength, uint8_t* output)
			{
				return AVX_Packed_Convert_Float_To_Byte_0_255_Range(input, arrayLength, output);
			}

			bool Convert_Number(const XmmVal& source, const XmmVal& destination, CvtOp operation)
			{
				return AVX_Packed_Convert_Number_(source, destination, operation);
			}

			bool Histogram_Gray_Image(const uint8_t* pixels, uint32_t numPixels, uint32_t* histogram)
			{
				return AVX_Packed_Histogram_Gray_Image_(pixels, numPixels, histogram);
			}

			void Matrix_Multiplication_Float(const float* a, const float* b, float* result)
			{
				AVX_Packed_Matrix_Multiplication_Float_(a, b, result);
			}

			void Matrix_Transpose_Float(float* input, const float* result)
			{
				AVX_Packed_Matrix_Transpose_Float_(input, result);
			}

			void Multiply_Int_A(const XmmVal& a, const XmmVal& b, XmmVal results[2])
			{
				AVX_Packed_Multiply_Int_A_(a, b, results);
			}

			void Multiply_Int_B(const XmmVal& a, const XmmVal& b, XmmVal& results)
			{
				AVX_Packed_Multiply_Int_B_(a, b, results);
			}

			void Multiply_Short(const XmmVal& a, const XmmVal& b, XmmVal results[2])
			{
				AVX_Packed_Multiply_Short_(a, b, results);
			}

			bool Shift_Integer(const XmmVal& input, XmmVal& results, ShiftOp shift_op, uint32_t count)
			{
				return AVX_Packed_Shift_Integer_(input, results, shift_op, count);
			}

			void Sum_Float(const XmmVal& a, const XmmVal& b, XmmVal results[])
			{
				AVX_Packed_Sum_Float_(a, b, results);
			}

			void Sum_Short(const XmmVal& a, const XmmVal& b, XmmVal results[2])
			{
				AVX_Packed_Sum_Short_(a, b, results);
			}

			void Y_Abs_Double(const YmmVal& input, YmmVal results[])
			{
				AVX_Packed_Y_Abs_Double_(input, results);
			}

			bool Y_Array_Cols_Mean_Double(const double* input, uint32_t numRows, uint32_t numCols, double* colMeans)
			{
				return AVX_Packed_Y_Array_Cols_Mean_Double_(input, numRows, numCols, colMeans);
			}

			bool Y_Calc_Correlation_Coefficient(const double* x, const double* y, size_t arrayLength, double sums[5], double epsilon, double* rho)
			{
				return AVX_Packed_Y_Calc_Correlation_Coefficient_(x, y, arrayLength, sums, epsilon, rho);
			}

			void Y_Calc_Sphere_Area_Volume(const float* radius, uint32_t arrayLength, float* areas, float* volumes, float qnanValue)
			{
				AVX_Packed_Y_Calc_Sphere_Area_Volume_(radius, arrayLength, areas, volumes, qnanValue);
			}

			void Y_Sum_Float(const YmmVal& a, const YmmVal& b, YmmVal results[])
			{
				AVX_Packed_Y_Sum_Float_(a, b, results);
			}
		}
	}
}