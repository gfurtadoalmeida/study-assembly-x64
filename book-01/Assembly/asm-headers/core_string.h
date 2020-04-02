#pragma once

namespace Assembly {
	namespace Core {
		namespace String {
			__declspec(dllexport) uint32_t Concat(const char* const* source, uint32_t sourceElementsCount, const char* destination, uint32_t destinationLength);
			__declspec(dllexport) uint32_t Count_Char_Occurrence(const char* text, char value);
		}
	}
}