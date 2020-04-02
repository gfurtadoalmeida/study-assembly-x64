#include "../asm-headers/__declarations.h"
#include "../asm-headers/core_array.h"

namespace Assembly {
	namespace Core {
		namespace Array {

			int32_t Compare(const int32_t* a, const int32_t* b, uint32_t arraysLength, int32_t** matchedValue)
			{
				return Core_Array_Compare_(a, b, arraysLength, matchedValue);
			}

			bool Get_From_Const(uint32_t position, uint32_t* value)
			{
				return Core_Array_Get_From_Const_(position, value);
			}

			uint32_t Get_From_Const_Array_Length()
			{
				return Core_Array_Get_From_Const_ArrayLength_;
			}
						
			void Reverse(const int32_t* source, const int32_t* destination, uint32_t arrayLength)
			{
				Core_Array_Reverse_(source, destination, arrayLength);
			}

			int32_t Sum(const int32_t* arrayPointer, uint32_t arrayLength)
			{
				return Core_Array_Sum_(arrayPointer, arrayLength);
			}

			bool Sum_Columns(const int32_t* sourceMatrix, const int32_t* destinationArray, uint32_t numRows, uint32_t numColumns)
			{
				return Core_Array_Sum_Columns_(sourceMatrix, destinationArray, numRows, numColumns);
			}
		}
	}
}