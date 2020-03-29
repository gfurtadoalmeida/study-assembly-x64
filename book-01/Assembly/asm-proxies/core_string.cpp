#include "../asm-headers/__declarations.h"
#include "../asm-headers/core_string.h"

namespace Assembly {
	namespace Core {
		namespace String {

			size_t Concat(const char* const* source, size_t sourceElements, const char* destination, size_t destinationLength)
			{
				return Core_String_Concat_(source, sourceElements, destination, destinationLength);
			}

			int Count_Char_Occurrence(const char* text, char value)
			{
				return Core_String_Count_Char_Occurrence_(text, value);
			}
		}
	}
}