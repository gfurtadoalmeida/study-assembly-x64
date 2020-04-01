
#include "pch.h"
#include "CppUnitTest.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "../Assembly/asm-headers/avx.h"
#include "../Assembly/asm-headers/avx_packed.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Assembly::AVX;
using namespace Assembly::AVX::Packed;
using namespace Assembly::AVX::Types;

namespace Assembly {
	namespace Test {
		namespace AVX {
			TEST_CLASS(Packed)
			{
				// The use of "alignas(16)" instruction on the tests below
				// are necessary because I used only aligned AVX instructions.
				// We could omit it if unaligned AVX instructions were used.
				// For performance, aligned instructions should be used.

			public:
				TEST_METHOD(Test_Array_Float_Sqrt)
				{
					// Use a length bigger than and not 
					// divisible by 16.
					// It will test the batch and one-by-one
					// processing modes.
					const int LENGTH = 19;

					alignas(16) float values[LENGTH];
					alignas(16) float results[LENGTH];

					for (size_t i = 0; i < LENGTH; i++)
					{
						values[i] = (float)i * (float)i;
					}

					Array_Float_Sqrt(values, results, LENGTH);

					for (size_t i = 0; i < LENGTH; i++)
					{
						Assert::AreEqual((float)i, results[i]);
					}
				}

				TEST_METHOD(Test_Compare_Doubles_Equal)
				{
					// 4 doubles (64 bits) in 128 bits (xmm register).
					const int LENGTH = 2;

					alignas(16) XmmVal a;
					alignas(16) XmmVal b;
					alignas(16) XmmVal results[LENGTH];

					a.Double[0] = 5.0;
					b.Double[0] = 5.0;

					a.Double[1] = 1.0;
					b.Double[1] = 2.0;

					Compare_Doubles_Equal(a, b, results);

					// Even though the results are stored in the double array,
					// they are in fact 2 long values (64 bits, same size as a double).
					// 0x0 = false
					// 0XF = true
					// As 0xF is NaN when double, we just check if it NaN, which means it's true.

					Assert::AreEqual(true, std::isnan(results->Double[0]));
					Assert::AreEqual(0.0, results->Double[1]);
				}

				TEST_METHOD(Test_Convert_Numbers)
				{
					// 4 float (32 bits) in 128 bits (xmm register).
					const int LENGTH = 4;

					alignas(16) XmmVal src;
					alignas(16) XmmVal des;

					src.Float[0] = 2.7F;
					src.Float[1] = 5.32F;
					src.Float[2] = -15.1523;
					src.Float[3] = -5.22F;

					RoundingMode originalMode = Get_Rounding_Mode();

					// Lets use the same rounding mode as
					// C++.
					Set_Rounding_Mode(RoundingMode::Truncate);

					bool converted = Convert_Numbers(src, des, CvtOp::F32_I32);

					Set_Rounding_Mode(originalMode);

					Assert::AreEqual(true, converted);

					for (size_t i = 0; i < LENGTH; i++)
					{
						Assert::AreEqual((int)src.Float[i], des.Int32[i]);
					}
				}

				TEST_METHOD(Test_Find_Array_Float_Max)
				{
					// Use a length bigger than and not 
					// divisible by 16.
					// It will test the batch and one-by-one
					// processing modes.
					const int LENGTH = 19;
					float result = 0.0F;

					alignas(16) float values[LENGTH];

					for (size_t i = 0; i < LENGTH; i++)
					{
						values[i] = (float)i;
					}

					Assert::AreEqual(true, Find_Array_Float_Max(values, LENGTH, &result));
					Assert::AreEqual((float)LENGTH - 1, result);
				}

				TEST_METHOD(Test_Find_Array_Float_Min)
				{
					// Use a length bigger than and not 
					// divisible by 16.
					// It will test the batch and one-by-one
					// processing modes.
					const int LENGTH = 19;
					float result = 0.0F;

					alignas(16) float values[LENGTH];

					for (size_t i = 0; i < LENGTH; i++)
					{
						values[i] = (float)i;
					}

					values[0] = -1.0F;

					Assert::AreEqual(true, Find_Array_Float_Min(values, LENGTH, &result));
					Assert::AreEqual(-1.0F, result);
				}

				TEST_METHOD(Test_Matrix_Float_Multiplication)
				{
					alignas(16) float matrixA[4][4]
					{
						{10.0F, 11.0F, 12.0F, 13.0F},
						{20.0F, 21.0F, 22.0F, 23.0F},
						{30.0F, 31.0F, 32.0F, 33.0F},
						{40.0F, 41.0F, 42.0F, 43.0F}
					};
					alignas(16) float matrixB[4][4]
					{
						{100.0F, 101.0F, 102.0F, 103.0F},
						{200.0F, 201.0F, 202.0F, 203.0F},
						{300.0F, 301.0F, 302.0F, 303.0F},
						{400.0F, 401.0F, 402.0F, 403.0F}
					};
					alignas(16) float results[4][4];

					Matrix_Float_Multiplication(*matrixA, *matrixB, *results);

					const float TRUTH[4][4]
					{
						{12000.0F, 12046.0F, 12092.0F, 12138.0F},
						{22000.0F, 22086.0F, 22172.0F, 22258.0F},
						{32000.0F, 32126.0F, 32252.0F, 32378.0F},
						{42000.0F, 42166.0F, 42332.0F, 42498.0F}
					};

					for (size_t row = 0; row < 4; row++)
					{
						for (size_t column = 0; column < 4; column++)
						{
							Assert::AreEqual(TRUTH[row][column], results[row][column]);
						}
					}
				}

				TEST_METHOD(Test_Matrix_Float_Transpose)
				{
					alignas(16) float matrix[4][4]
					{
						{2.0F,  7.0F,  8.0F,  3.0F},
						{11.0F, 14.0F, 16.0F, 10.0F},
						{24.0F, 21.0F, 27.0F, 29.0F},
						{31.0F, 34.0F, 38.0F, 33.0F}
					};
					alignas(16) float results[4][4];

					Matrix_Float_Transpose(*matrix, *results);

					for (size_t row = 0; row < 4; row++)
					{
						for (size_t column = 0; column < 4; column++)
						{
							Assert::AreEqual(matrix[row][column], results[column][row]);
						}
					}
				}

				TEST_METHOD(Test_Multiply_Ints_A)
				{
					alignas(16) XmmVal a;
					alignas(16) XmmVal b;
					alignas(16) XmmVal results[2];

					a.Int32[0] = 2;
					b.Int32[0] = 2;

					a.Int32[1] = -2;
					b.Int32[1] = 2;

					a.Int32[2] = 4;
					b.Int32[2] = 4;

					a.Int32[3] = -4;
					b.Int32[3] = 4;

					Multiply_Ints_A(a, b, results);

					Assert::AreEqual((int64_t)4, results[0].Int64[0]);
					Assert::AreEqual((int64_t)-4, results[0].Int64[1]);
					Assert::AreEqual((int64_t)16, results[1].Int64[0]);
					Assert::AreEqual((int64_t)-16, results[1].Int64[1]);
				}

				TEST_METHOD(Test_Multiply_Ints_B)
				{
					alignas(16) XmmVal a;
					alignas(16) XmmVal b;
					alignas(16) XmmVal results;

					a.Int32[0] = 2;
					b.Int32[0] = 2;

					a.Int32[1] = -2;
					b.Int32[1] = 2;

					a.Int32[2] = 4;
					b.Int32[2] = 4;

					a.Int32[3] = -4;
					b.Int32[3] = 4;

					Multiply_Ints_B(a, b, results);

					Assert::AreEqual((int32_t)4, results.Int32[0]);
					Assert::AreEqual((int32_t)-4, results.Int32[1]);
					Assert::AreEqual((int32_t)16, results.Int32[2]);
					Assert::AreEqual((int32_t)-16, results.Int32[3]);
				}

				TEST_METHOD(Test_Multiply_Shorts)
				{
					alignas(16) XmmVal a;
					alignas(16) XmmVal b;
					alignas(16) XmmVal results[2];

					a.Int16[0] = 2;
					b.Int16[0] = 2;

					a.Int16[1] = -2;
					b.Int16[1] = 2;

					a.Int16[2] = 4;
					b.Int16[2] = 4;

					a.Int16[3] = -4;
					b.Int16[3] = 4;

					a.Int16[4] = -5;
					b.Int16[4] = 5;

					Multiply_Shorts(a, b, results);

					Assert::AreEqual((int32_t)4, results[0].Int32[0]);
					Assert::AreEqual((int32_t)-4, results[0].Int32[1]);
					Assert::AreEqual((int32_t)16, results[0].Int32[2]);
					Assert::AreEqual((int32_t)-16, results[0].Int32[3]);
					Assert::AreEqual((int32_t)-25, results[1].Int32[0]);
				}

				TEST_METHOD(Test_Shift_Integers)
				{
					alignas(16) XmmVal src;
					alignas(16) XmmVal des;

					// Each HEX digit = 4 bits
					// Shifting by 4 means just moving a
					// digit left /right.
					// HEX are cool!

					src.UInt32[0] = 0x12345678;
					src.UInt32[1] = 0xFF00FF00;
					src.UInt32[2] = 0x03030303;
					src.UInt32[3] = 0x80800F0F;

					Assert::AreEqual(true, Shift_Integers(src, des, ShiftOp::U32_LOG_LEFT, 4));

					Assert::AreEqual((uint32_t)0x23456780, des.UInt32[0]);
					Assert::AreEqual((uint32_t)0xF00FF000, des.UInt32[1]);
					Assert::AreEqual((uint32_t)0x30303030, des.UInt32[2]);
					Assert::AreEqual((uint32_t)0x0800F0F0, des.UInt32[3]);
				}

				TEST_METHOD(Test_Sum_Floats)
				{
					// 4 float (32 bits) in 128 bits (xmm register).
					const int LENGTH = 4;

					alignas(16) XmmVal a;
					alignas(16) XmmVal b;
					alignas(16) XmmVal results[LENGTH];

					for (short i = 0; i < LENGTH; i++)
					{
						a.Float[i] = i + 1;
						b.Float[i] = i + 1;
					}

					Sum_Floats(a, b, results);

					for (short i = 0; i < LENGTH; i++)
					{
						Assert::AreEqual((i + 1) * 2.0F, results->Float[i]);
					}
				}

				TEST_METHOD(Test_Sum_Shorts)
				{
					alignas(16) XmmVal a;
					alignas(16) XmmVal b;
					alignas(16) XmmVal results[2];

					// We can fit 8 short numbers in it but I 
					// send only 4.
					a.Int16[0] = 10;
					b.Int16[0] = 100;

					a.Int16[1] = 200;
					b.Int16[1] = -200;

					a.Int16[2] = 30;
					b.Int16[2] = 32760;

					a.Int16[3] = -32766;
					b.Int16[3] = -400;

					Sum_Shorts(a, b, results);

					// Wraparound
					Assert::AreEqual((int16_t)110, results[0].Int16[0]);
					Assert::AreEqual((int16_t)0, results[0].Int16[1]);
					Assert::AreEqual((int16_t)-32746, results[0].Int16[2]);
					Assert::AreEqual((int16_t)32370, results[0].Int16[3]);

					// Saturated
					Assert::AreEqual((int16_t)110, results[1].Int16[0]);
					Assert::AreEqual((int16_t)0, results[1].Int16[1]);
					Assert::AreEqual((int16_t)32767, results[1].Int16[2]);
					Assert::AreEqual((int16_t)-32768, results[1].Int16[3]);
				}
			};
		}
	}
}