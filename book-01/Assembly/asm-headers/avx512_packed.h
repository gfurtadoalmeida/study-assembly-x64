#pragma once

#include "types_avx.h"

namespace Assembly {
	namespace AVX512 {
		namespace Packed {

			__declspec(dllexport) void Math_Double(const ZmmVal* a, const ZmmVal* b, ZmmVal result[8]);
			__declspec(dllexport) void Math_Float(const ZmmVal* a, const ZmmVal* b, ZmmVal result[8]);
		}
	}
}