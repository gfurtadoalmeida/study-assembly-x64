#pragma once

#include "types_avx.h"

namespace Assembly {
	namespace AVX2 {
		namespace Packed {

			__declspec(dllexport) void Convert_Short_Int(YmmVal* values, YmmVal result[2]);
			__declspec(dllexport) void Convert_Short_Long(YmmVal* values, YmmVal result[4]);
			__declspec(dllexport) void Convert_UByte_UInt(YmmVal* values, YmmVal result[4]);
			__declspec(dllexport) void Convert_UByte_UShort(YmmVal* values, YmmVal result[2]);
			__declspec(dllexport) void Gather_Double(const double* src, double* des, const int32_t* indexes, const int64_t* merge);
			__declspec(dllexport) void Gather_Double(const double* src, double* des, const int64_t* indexes, const int64_t* merge);
			__declspec(dllexport) void Gather_Float(const float* src, float* des, const int32_t* indexes, const int32_t* merge);
			__declspec(dllexport) void Gather_Float(const float* src, float* des, const int64_t* indexes, const int32_t* merge);
			__declspec(dllexport) void Pack_I32_I16(const YmmVal& a, const YmmVal& b, YmmVal* result);
			__declspec(dllexport) void Permute_Float(YmmVal* src, YmmVal* des, YmmVal* indexes);
			__declspec(dllexport) void Sum_Int(const YmmVal& a, const YmmVal& b, YmmVal& result);
			__declspec(dllexport) void Sum_Short(const YmmVal& a, const YmmVal& b, YmmVal& result);
			__declspec(dllexport) YmmValAB Unpack_U32_U64(const YmmVal& a, const YmmVal& b);
		}
	}
}