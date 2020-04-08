#pragma once

#include "types_avx.h"

namespace Assembly {
	namespace AVX2 {
		namespace Packed {

			__declspec(dllexport) void Permute_Float(YmmVal* src, YmmVal* des, YmmVal* indexes);
		}
	}
}