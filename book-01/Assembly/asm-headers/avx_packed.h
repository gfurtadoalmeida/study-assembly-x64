#pragma once

#include "types_avx.h"

namespace Assembly {
	namespace AVX {
		namespace Packed {

			__declspec(dllexport) void Compare_Doubles_Equal(const XmmVal& a, const XmmVal& b, XmmVal results[]);
			__declspec(dllexport) bool Convert_Numbers(const XmmVal& source, const XmmVal& destination, CvtOp operation);
			__declspec(dllexport) void Sum_Floats(const XmmVal& a, const XmmVal& b, XmmVal results[]);
		}
	}
}