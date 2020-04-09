#include "../asm-headers/__declarations.h"
#include "../asm-headers/avx2_packed.h"

namespace Assembly {
	namespace AVX2 {
		namespace Packed {

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

			void Permute_Float(YmmVal* src, YmmVal* des, YmmVal* indexes)
			{
				AVX2_Packed_Permute_Float_(src, des, indexes);
			}
		}
	}
}