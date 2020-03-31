#include "../asm-headers/__declarations.h"
#include "../asm-headers/avx_packed.h"

namespace Assembly {
	namespace AVX {
		namespace Packed {

			void Array_Float_Sqrt(float* input, const float* output, int arrayLength)
			{
				AVX_Packed_Array_Float_Sqtr_(input, output, arrayLength);
			}

			void Compare_Doubles_Equal(const XmmVal& a, const XmmVal& b, XmmVal results[])
			{
				AVX_Packed_Compare_Doubles_Equal_(a, b, results);
			}

			bool Convert_Numbers(const XmmVal& source, const XmmVal& destination, CvtOp operation)
			{
				return AVX_Packed_Convert_Numbers_(source, destination, operation);
			}
	
			bool Find_Array_Float_Max(const float* input, int arrayLength, float* result)
			{
				return AVX_Packed_Find_Array_Float_Max_(input, arrayLength, result);
			}

			bool Find_Array_Float_Min(const float* input, int arrayLength, float* result)
			{
				return AVX_Packed_Find_Array_Float_Min_(input, arrayLength, result);
			}

			void Matrix_Float_Transpose(float* input, const float* result)
			{
				AVX_Packed_Matrix_Float_Transpose_(input, result);
			}

			void Sum_Floats(const XmmVal& a, const XmmVal& b, XmmVal results[])
			{
				AVX_Packed_Sum_Floats_(a, b, results);
			}
		}
	}
}