#include "pch.h"
#include "CppUnitTest.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "../Assembly/asm-headers/avx.h"
#include "../Assembly/asm-headers/avx512_packed.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Assembly::AVX::Types;
using namespace Assembly::AVX512::Packed;

namespace Assembly {
	namespace Test {
		namespace AVX512 {
			TEST_CLASS(Packed)
			{
				TEST_METHOD(Test_Math_Double)
				{
					alignas(64) ZmmVal a;
					alignas(64) ZmmVal b;
					alignas(64) ZmmVal result[8];

					for (size_t i = 0; i < 8; i++)
					{
						a.Double[i] = i + 2.0;
					}

					for (size_t i = 0; i < 8; i++)
					{
						b.Double[i] = i + 15.0;
					}

					Math_Double(&a, &b, result);

					for (size_t i = 0; i < 8; i++)
					{
						Assert::AreEqual(result[0].Double[i], a.Double[i] + b.Double[i]);
						Assert::AreEqual(result[1].Double[i], a.Double[i] - b.Double[i]);
						Assert::AreEqual(result[2].Double[i], a.Double[i] * b.Double[i]);
						Assert::AreEqual(result[3].Double[i], a.Double[i] / b.Double[i]);
						Assert::AreEqual(result[4].Double[i], abs(b.Double[i]));
						Assert::AreEqual(result[5].Double[i], sqrt(a.Double[i]));
						Assert::AreEqual(result[6].Double[i], a.Double[i]);
						Assert::AreEqual(result[7].Double[i], b.Double[i]);
					}
				}

				TEST_METHOD(Test_Math_Float)
				{
					alignas(64) ZmmVal a;
					alignas(64) ZmmVal b;
					alignas(64) ZmmVal result[16];

					for (size_t i = 0; i < 16; i++)
					{
						a.Float[i] = i + 2.0F;
					}

					for (size_t i = 0; i < 16; i++)
					{
						b.Float[i] = i + 35.0F;
					}

					Math_Float(&a, &b, result);

					for (size_t i = 0; i < 8; i++)
					{
						Assert::AreEqual(result[0].Float[i], a.Float[i] + b.Float[i]);
						Assert::AreEqual(result[1].Float[i], a.Float[i] - b.Float[i]);
						Assert::AreEqual(result[2].Float[i], a.Float[i] * b.Float[i]);
						Assert::AreEqual(result[3].Float[i], a.Float[i] / b.Float[i]);
						Assert::AreEqual(result[4].Float[i], abs(b.Float[i]));
						Assert::AreEqual(result[5].Float[i], sqrt(a.Float[i]));
						Assert::AreEqual(result[6].Float[i], a.Float[i]);
						Assert::AreEqual(result[7].Float[i], b.Float[i]);
					}
				}
			};
		}
	}
}