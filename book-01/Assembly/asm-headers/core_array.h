#pragma once

namespace Assembly {
	namespace Core {
		namespace Array {

			__declspec(dllexport) int32_t Compare(const int32_t* a, const int32_t* b, uint32_t arraysLength, int32_t** matchedValue);
			__declspec(dllexport) bool Get_From_Const(uint32_t position, uint32_t* value);
			__declspec(dllexport) uint32_t Get_From_Const_Array_Length();
			__declspec(dllexport) void Reverse(const int32_t* source, const int32_t* destination, uint32_t arrayLength);
			__declspec(dllexport) int32_t Sum(const int32_t* source, uint32_t arrayLength);
			__declspec(dllexport) bool Sum_Columns(const int32_t* sourceMatrix, const int32_t* destinationArray, uint32_t numRows, uint32_t numColumns);
		}
	}
}