#pragma once

namespace Assembly {
	namespace Core {
		namespace String {

			__declspec(dllexport) size_t Concat(const char* const* source, size_t sourceElements, const char* destination, size_t destinationLength);
			__declspec(dllexport) int Count_Char_Occurrence(const char* text, char value);
		}
	}
}