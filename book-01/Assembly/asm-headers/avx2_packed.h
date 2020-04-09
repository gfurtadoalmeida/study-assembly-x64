#pragma once

#include "types_avx.h"

namespace Assembly {
	namespace AVX2 {
		namespace Packed {

			__declspec(dllexport) void Gather_Double(const double* src, double* des, const int32_t* indexes, const int64_t* merge);
			__declspec(dllexport) void Gather_Double(const double* src, double* des, const int64_t* indexes, const int64_t* merge);
			__declspec(dllexport) void Gather_Float(const float* src, float* des, const int32_t* indexes, const int32_t* merge);
			__declspec(dllexport) void Gather_Float(const float* src, float* des, const int64_t* indexes, const int32_t* merge);
			__declspec(dllexport) void Permute_Float(YmmVal* src, YmmVal* des, YmmVal* indexes);
		}
	}
}