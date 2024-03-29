#include "pch.h"

#if BUILD_AVX512 == 1

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
			public:
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

				TEST_METHOD(Test_Math_Long)
				{
					alignas(64) ZmmVal a;
					alignas(64) ZmmVal b;
					alignas(64) ZmmVal result[6];

					// We're going to do operations with the first 5 numbers.
					// The last two we're going to test if they're zeros; ignored by the mask.
					uint32_t opmask = 0x3f;

					a.Int64[0] = LLONG_MAX;	b.Int64[0] = 1; // Add, wraparound
					a.Int64[1] = LLONG_MIN;	b.Int64[1] = 1; // Subtraction, wraparound
					a.Int64[2] = -2048;		b.Int64[2] = 2; // Multiplication, signed, low 64 bits
					a.Int64[3] = -2048;     b.Int64[3] = 2; // Logical left shift
					a.Int64[4] = 8192;      b.Int64[4] = 5; // Arithmetic right shift
					a.Int64[5] = -4096;     b.Int64[5] = 7; // Abs
					a.Int64[6] = 16;        b.Int64[6] = 3;
					a.Int64[7] = 512;       b.Int64[7] = 6;

					Math_Long(&a, &b, result, opmask);

					Assert::AreEqual(LLONG_MIN, result[0].Int64[0]);
					Assert::AreEqual(LLONG_MAX, result[1].Int64[1]);
					Assert::AreEqual(a.Int64[2] * b.Int64[2], result[2].Int64[2]);
					Assert::AreEqual(a.Int64[3] << b.Int64[3], result[3].Int64[3]);
					Assert::AreEqual(a.Int64[4] >> b.Int64[4], result[4].Int64[4]);
					Assert::AreEqual(abs(a.Int64[5]), result[5].Int64[5]);
					Assert::AreEqual(0LL, result[0].Int64[6]);
					Assert::AreEqual(0LL, result[0].Int64[7]);
				}

				TEST_METHOD(Test_Math_Short)
				{
					alignas(64) ZmmVal a;
					alignas(64) ZmmVal b;
					alignas(64) ZmmVal result[6];

					for (int16_t i = 6; i < 32; i++)
					{
						a.Int16[i] = i + 2;
						b.Int16[i] = i + 3;
					}

					a.Int16[0] = SHRT_MAX; b.Int16[0] = 1;   // Add, wraparound
					a.Int16[1] = SHRT_MAX; b.Int16[1] = 100; // Add, saturation
					a.Int16[2] = SHRT_MIN; b.Int16[2] = 1;   // Subtraction, wraparound
					a.Int16[3] = SHRT_MIN; b.Int16[3] = 100; // Subtraction, saturation
					a.Int16[4] = -50;      b.Int16[4] = 500; // Minimum, signed
					a.Int16[5] = -60;      b.Int16[5] = 600; // Maximum, signed

					Math_Short(&a, &b, result);

					// I won't validate all items. If the items below are ok
					// then everything is ok.
					Assert::AreEqual((short)SHRT_MIN, result[0].Int16[0]);
					Assert::AreEqual((short)SHRT_MAX, result[1].Int16[1]);
					Assert::AreEqual((short)SHRT_MAX, result[2].Int16[2]);
					Assert::AreEqual((short)SHRT_MIN, result[3].Int16[3]);
					Assert::AreEqual(a.Int16[4], result[4].Int16[4]);
					Assert::AreEqual(b.Int16[5], result[5].Int16[5]);
				}

				TEST_METHOD(Test_Matrix_Vector_Multiplication_Float)
				{
					const uint32_t VECTORS_COUNT = 8;

					alignas(64) float matrix[4][4]
					{
					   10.0F, 11.0F, 12.0F, 13.0F,
					   20.0F, 21.0F, 22.0F, 23.0F,
					   30.0F, 31.0F, 32.0F, 33.0F,
					   40.0F, 41.0F, 42.0F, 43.0F
					};
					alignas(64) Vector4x1_F32 vectors[VECTORS_COUNT];
					alignas(64) Vector4x1_F32 results[VECTORS_COUNT];

					std::uniform_real_distribution<float> unif(1.0F, 10000.0F);
					std::default_random_engine re;

					for (uint32_t i = 0; i < VECTORS_COUNT; i++)
					{
						vectors[i].W = unif(re); results[i].W = 1.0F;
						vectors[i].X = unif(re); results[i].X = 1.0F;
						vectors[i].Y = unif(re); results[i].Y = 1.0F;
						vectors[i].Z = unif(re); results[i].Z = 1.0F;
					}

					Assert::IsTrue(Matrix_Vector_Multiplication_Float(matrix, vectors, VECTORS_COUNT, results));

					for (uint32_t i = 0; i < VECTORS_COUNT; i++)
					{
						Assert::AreEqual((matrix[0][0] * vectors[i].W + matrix[0][1] * vectors[i].X) + (matrix[0][2] * vectors[i].Y + matrix[0][3] * vectors[i].Z), results[i].W);
						Assert::AreEqual((matrix[1][0] * vectors[i].W + matrix[1][1] * vectors[i].X) + (matrix[1][2] * vectors[i].Y + matrix[1][3] * vectors[i].Z), results[i].X);
						Assert::AreEqual((matrix[2][0] * vectors[i].W + matrix[2][1] * vectors[i].X) + (matrix[2][2] * vectors[i].Y + matrix[2][3] * vectors[i].Z), results[i].Y);
						Assert::AreEqual((matrix[3][0] * vectors[i].W + matrix[3][1] * vectors[i].X) + (matrix[3][2] * vectors[i].Y + matrix[3][3] * vectors[i].Z), results[i].Z);
					}
				}

				TEST_METHOD(Test_Vector_Cross_Product)
				{
					const uint32_t LENGTH = 32;

					std::uniform_real_distribution<double> unif(1.0, 10000.0);
					std::default_random_engine re;

					// They are not aligned because would waste too much space.
					Vector a[LENGTH];
					Vector b[LENGTH];
					Vector result[LENGTH];

					for (size_t i = 0; i < LENGTH; i++)
					{
						a[i].X = unif(re);
						a[i].Y = unif(re);
						a[i].Z = unif(re);

						b[i].X = unif(re);
						b[i].Y = unif(re);
						b[i].Z = unif(re);
					}

					Assert::IsTrue(Vector_Cross_Product(a, b, result, LENGTH));

					for (size_t i = 0; i < LENGTH; i++)
					{
						Assert::AreEqual(a[i].Y * b[i].Z - a[i].Z * b[i].Y, result[i].X);
						Assert::AreEqual(a[i].Z * b[i].X - a[i].X * b[i].Z, result[i].Y);
						Assert::AreEqual(a[i].X * b[i].Y - a[i].Y * b[i].X, result[i].Z);
					}
				}
			};
		}
	}
}

#endif