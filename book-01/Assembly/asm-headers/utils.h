#pragma once
#include <cstdint>

namespace Assembly {
	namespace Utils {

		__declspec(dllexport) int16_t ClampToShort(int32_t value);
		__declspec(dllexport) uint64_t Merge(uint32_t high, uint32_t low);
	}
}
