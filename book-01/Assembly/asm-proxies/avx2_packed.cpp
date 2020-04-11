#include "../asm-headers/__declarations.h"
#include "../asm-headers/avx2_packed.h"

namespace Assembly {
	namespace AVX2 {
		namespace Packed {

			bool Clip_Pixel_Gray_Image(PixelClipData* pcd)
			{
				return AVX2_Packed_Clip_Pixel_Gray_Image_(pcd);
			}

			void Convert_Float_HalfPrecision(float values[8], uint16_t result[8], RoundingMode roudingMode)
			{
				AVX2_Packed_Convert_Float_HalfPrecision_(values, result, roudingMode);
			}

			void Convert_HalfPrecision_Float(uint16_t values[8], float result[8])
			{
				AVX2_Packed_Convert_HalfPrecision_Float_(values, result);
			}

			void Convert_Short_Int(YmmVal* values, YmmVal result[2])
			{
				AVX2_Packed_Convert_Short_Int_(values, result);
			}
			
			void Convert_Short_Long(YmmVal* values, YmmVal result[4])
			{
				AVX2_Packed_Convert_Short_Long_(values, result);
			}

			void Convert_UByte_UInt(YmmVal* values, YmmVal result[4])
			{
				AVX2_Packed_Convert_UByte_UInt_(values, result);
			}

			void Convert_UByte_UShort(YmmVal* values, YmmVal result[2])
			{
				AVX2_Packed_Convert_UByte_UShort_(values, result);
			}

			void Gather_Double(const double* src, double* des, const int32_t* indexes, const int64_t* merge)
			{
				AVX2_Packed_Gather_Double_I32_(src, des, indexes, merge);
			}

			void Gather_Double(const double* src, double* des, const int64_t* indexes, const int64_t* merge)
			{
				AVX2_Packed_Gather_Double_I64_(src, des, indexes, merge);
			}

			void Gather_Float(const float* src, float* des, const int32_t* indexes, const int32_t* merge)
			{
				AVX2_Packed_Gather_Float_I32_(src, des, indexes, merge);
			}

			void Gather_Float(const float* src, float* des, const int64_t* indexes, const int32_t* merge)
			{
				AVX2_Packed_Gather_Float_I64_(src, des, indexes, merge);
			}

			void Pack_I32_I16(const YmmVal& a, const YmmVal& b, YmmVal* result)
			{
				AVX2_Packed_Pack_I32_I16_(a, b, result);
			}

			void Permute_Float(YmmVal* src, YmmVal* des, YmmVal* indexes)
			{
				AVX2_Packed_Permute_Float_(src, des, indexes);
			}

			void Sum_Int(const YmmVal& a, const YmmVal& b, YmmVal& result)
			{
				AVX2_Packed_Sum_Int_(a, b, result);
			}

			void Sum_Short(const YmmVal& a, const YmmVal& b, YmmVal& result)
			{
				AVX2_Packed_Sum_Short_(a, b, result);
			}

			YmmValAB Unpack_U32_U64(const YmmVal& a, const YmmVal& b)
			{
				return AVX2_Packed_Unpack_U32_U64_(a, b);
			}
		}
	}
}