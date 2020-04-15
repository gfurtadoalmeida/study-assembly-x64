#include "pch.h"
#include "CppUnitTest.h"
#include <random>
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
				TEST_METHOD(Test_Compare_Double)
				{
					alignas(64) ZmmVal a;
					alignas(64) ZmmVal b;
					alignas(64) uint8_t result[8];

					std::uniform_real_distribution<double> unif(1.0, 10000.0);
					std::default_random_engine re;

					for (size_t i = 0; i < 8; i++)
					{
						a.Double[i] = unif(re);
					}

					for (size_t i = 0; i < 8; i++)
					{
						b.Double[i] = unif(re);
					}

					Compare_Double(&a, &b, result);

					const uint8_t MASK = 0x01;

					for (size_t i = 0; i < 8; i++)
					{
						Assert::AreEqual(a.Double[i] == b.Double[i], (bool)(((result[0] >> i) & MASK) << 8));
						Assert::AreEqual(a.Double[i] != b.Double[i], (bool)(((result[1] >> i) & MASK) << 8));
						Assert::AreEqual(a.Double[i] < b.Double[i], (bool)(((result[2] >> i) & MASK) << 8));
						Assert::AreEqual(a.Double[i] <= b.Double[i], (bool)(((result[3] >> i) & MASK) << 8));
						Assert::AreEqual(a.Double[i] > b.Double[i], (bool)(((result[4] >> i) & MASK) << 8));
						Assert::AreEqual(a.Double[i] >= b.Double[i], (bool)(((result[5] >> i) & MASK) << 8));
						Assert::AreEqual(!(isnan(a.Double[i]) || isnan(b.Double[i])), (bool)(((result[6] >> i) & MASK) << 8));
						Assert::AreEqual(isnan(a.Double[i]) || isnan(b.Double[i]), (bool)(((result[7] >> i) & MASK) << 8));
					}
				}

				TEST_METHOD(Test_Compare_Float)
				{
					alignas(64) ZmmVal a;
					alignas(64) ZmmVal b;
					alignas(64) uint16_t result[8];

					std::uniform_real_distribution<float> unif(1.0F, 10000.0F);
					std::default_random_engine re;

					for (size_t i = 0; i < 16; i++)
					{
						a.Float[i] = unif(re);
					}

					for (size_t i = 0; i < 16; i++)
					{
						b.Float[i] = unif(re);
					}

					Compare_Float(&a, &b, result);

					const uint16_t MASK = 0x0001;

					for (size_t i = 0; i < 16; i++)
					{
						Assert::AreEqual(a.Float[i] == b.Float[i], (bool)(((result[0] >> i) & MASK) << 16));
						Assert::AreEqual(a.Float[i] != b.Float[i], (bool)(((result[1] >> i) & MASK) << 16));
						Assert::AreEqual(a.Float[i] < b.Float[i], (bool)(((result[2] >> i) & MASK) << 16));
						Assert::AreEqual(a.Float[i] <= b.Float[i], (bool)(((result[3] >> i) & MASK) << 16));
						Assert::AreEqual(a.Float[i] > b.Float[i], (bool)(((result[4] >> i) & MASK) << 16));
						Assert::AreEqual(a.Float[i] >= b.Float[i], (bool)(((result[5] >> i) & MASK) << 16));
						Assert::AreEqual(!(isnan(a.Float[i]) || isnan(b.Float[i])), (bool)(((result[6] >> i) & MASK) << 16));
						Assert::AreEqual(isnan(a.Float[i]) || isnan(b.Float[i]), (bool)(((result[7] >> i) & MASK) << 16));
					}
				}

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
						Assert::AreEqual(a.Double[i] + b.Double[i], result[0].Double[i]);
						Assert::AreEqual(a.Double[i] - b.Double[i], result[1].Double[i]);
						Assert::AreEqual(a.Double[i] * b.Double[i], result[2].Double[i]);
						Assert::AreEqual(a.Double[i] / b.Double[i], result[3].Double[i]);
						Assert::AreEqual(abs(b.Double[i]), result[4].Double[i]);
						Assert::AreEqual(sqrt(a.Double[i]), result[5].Double[i]);
						Assert::AreEqual(a.Double[i], result[6].Double[i]);
						Assert::AreEqual(b.Double[i], result[7].Double[i]);
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
						Assert::AreEqual(a.Float[i] + b.Float[i], result[0].Float[i]);
						Assert::AreEqual(a.Float[i] - b.Float[i], result[1].Float[i]);
						Assert::AreEqual(a.Float[i] * b.Float[i], result[2].Float[i]);
						Assert::AreEqual(a.Float[i] / b.Float[i], result[3].Float[i]);
						Assert::AreEqual(abs(b.Float[i]), result[4].Float[i]);
						Assert::AreEqual(sqrt(a.Float[i]), result[5].Float[i]);
						Assert::AreEqual(a.Float[i], result[6].Float[i]);
						Assert::AreEqual(b.Float[i], result[7].Float[i]);
					}
				}
			};
		}
	}
}