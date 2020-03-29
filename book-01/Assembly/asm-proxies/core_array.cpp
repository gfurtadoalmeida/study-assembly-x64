#include "../asm-headers/__declarations.h"
#include "../asm-headers/core_array.h"

namespace Assembly {
	namespace Core {
		namespace Array {

			int Compare(const int* a, const int* b, int arraysLength, int** matchedValues)
			{
				return Core_Array_Compare_(a, b, arraysLength, matchedValues);
			}

			int Get_From_Const(int position, int* value)
			{
				return Core_Array_Get_From_Const_(position, value);
			}

			int Get_From_Const_Array_Length()
			{
				return Core_Array_Get_From_Const_ArrayLength_;
			}
						
			void Reverse(const int* source, const int* destination, int arrayLength)
			{
				Core_Array_Reverse_(source, destination, arrayLength);
			}

			int Sum(const int* arrayPointer, int arrayLength)
			{
				return Core_Array_Sum_(arrayPointer, arrayLength);
			}

			int Sum_Columns(const int* sourceMatrix, const int* destinationArray, int numRows, int numColumns)
			{
				return Core_Array_Sum_Columns_(sourceMatrix, destinationArray, numRows, numColumns);
			}
		}
	}
}