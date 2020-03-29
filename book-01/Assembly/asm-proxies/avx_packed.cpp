#include "../asm-headers/__declarations.h"
#include "../asm-headers/avx_packed.h"

namespace Assembly {
	namespace AVX {
		namespace Packed {

			void Compare_Doubles_Equal(const XmmVal& a, const XmmVal& b, XmmVal results[])
			{
				AVX_Packed_Compare_Doubles_Equal_(a, b, results);
			}

			bool Convert_Numbers(const XmmVal& source, const XmmVal& destination, CvtOp operation)
			{
				return AVX_Packed_Convert_Numbers_(source, destination, operation);
			}

			void Sum_Floats(const XmmVal& a, const XmmVal& b, XmmVal results[])
			{
				AVX_Packed_Sum_Floats_(a, b, results);
			}
		}
	}
}