#include "pch.h"
#include "CppUnitTest.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "../Assembly/asm-headers/avx.h"
#include "../Assembly/asm-headers/avx2_packed.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Assembly::AVX::Types;
using namespace Assembly::AVX2::Packed;

namespace Assembly {
	namespace Test {
		namespace AVX2 {
			TEST_CLASS(Packed)
			{
				// The use of "alignas(16)" or "alignas(32)" instruction on the 
				// tests below are necessary because they use aligned AVX instructions.
				// We could omit it if unaligned AVX instructions were used.
				// For performance, aligned instructions should be used.
				//
				// For any array, use a length bigger than and not 
				// divisible by 16 so we can test the batch and one-by-one
				// processing modes.
				//
				// Use of alignas:
				// - 128 bits = alignas(16)
				// - 256 bits = alignas(32)

				TEST_METHOD(Test_Permute_Float)
				{
					alignas(32) YmmVal src;
					alignas(32) YmmVal indexes;
					alignas(32) YmmVal results;

					src.Float[0] = 100; indexes.Int32[0] = 3;
					src.Float[1] = 200; indexes.Int32[1] = 2;
					src.Float[2] = 300; indexes.Int32[2] = 1;
					src.Float[3] = 400; indexes.Int32[3] = 0;
					src.Float[4] = 500; indexes.Int32[4] = 3;
					src.Float[5] = 600; indexes.Int32[5] = 2;
					src.Float[6] = 700; indexes.Int32[6] = 1;
					src.Float[7] = 800; indexes.Int32[7] = 0;

					Permute_Float(&src, &results, &indexes);

					for (size_t i = 0, r = 3; i < 4; i++, r--)
					{
						Assert::AreEqual(src.Float[i], results.Float[r]);
					}

					for (size_t i = 4, r = 7; i < 8; i++, r--)
					{
						Assert::AreEqual(src.Float[i], results.Float[r]);
					}
				}
			};
		}
	}
}