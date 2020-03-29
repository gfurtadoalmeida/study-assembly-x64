#pragma once

namespace Assembly {
	namespace Core {
		namespace Array {

			__declspec(dllexport) int Compare(const int* a, const int* b, int arraysLength, int** matchedValue);
			__declspec(dllexport) int Get_From_Const(int position, int* value);
			__declspec(dllexport) int Get_From_Const_Array_Length();
			__declspec(dllexport) void Reverse(const int* source, const int* destination, int arrayLength);
			__declspec(dllexport) int Sum(const int* arrayPointer, int arrayLength);
			__declspec(dllexport) int Sum_Columns(const int* sourceMatrix, const int* destinationArray, int numRows, int numColumns);
		}
	}
}