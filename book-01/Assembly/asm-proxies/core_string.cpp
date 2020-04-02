#include "../asm-headers/__declarations.h"
#include "../asm-headers/core_string.h"

namespace Assembly {
	namespace Core {
		namespace String {

			uint32_t Concat(const char* const* source, uint32_t sourceElements, const char* destination, uint32_t destinationLength)
			{
				return Core_String_Concat_(source, sourceElements, destination, destinationLength);
			}

			uint32_t Count_Char_Occurrence(const char* text, char value)
			{
				return Core_String_Count_Char_Occurrence_(text, value);
			}
		}
	}
}