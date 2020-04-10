#include <cstdint>
#include <algorithm>
#include "../asm-headers/utils.h"

namespace Assembly {
	namespace Utils {

		int16_t ClampToShort(int32_t value)
		{
			return (int16_t)std::clamp(value, SHRT_MIN, SHRT_MAX);
		}

		uint64_t Merge(uint32_t high, uint32_t low)
		{
			return ((uint64_t)high) << 32 | low;
		}
	}
}