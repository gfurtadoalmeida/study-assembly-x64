
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
				//
				// For any array, use a length bigger than and not 
				// divisible by 16 so we can test the batch and one-by-one
				// processing modes.

			public:
				TEST_METHOD(Test_Array_Max_Byte)
				{
					const uint32_t LENGTH = 19;
					uint8_t result = 0;

					alignas(16) uint8_t values[LENGTH];

					for (uint8_t i = 0; i < LENGTH; i++)
					{
						values[i] = i;
					}

					Assert::IsTrue(Array_Max_Byte(values, LENGTH, &result));
					Assert::AreEqual(values[LENGTH - 1], result);
				}

				TEST_METHOD(Test_Array_Max_Float)
				{
					const uint32_t LENGTH = 19;
					float result = 0.0F;

					alignas(16) float values[LENGTH];

					for (uint32_t i = 0; i < LENGTH; i++)
					{
						values[i] = (float)i;
					}

					Assert::IsTrue(Array_Max_Float(values, LENGTH, &result));
					Assert::AreEqual(values[LENGTH - 1], result);
				}

				TEST_METHOD(Test_Array_Mean_Byte)
				{
					// This array need a length bigger than and not 
					// divisible by 32 so we can test the batch and one-by-one
					// processing modes.
					const uint32_t LENGTH = 34;

					alignas(16) uint8_t values[LENGTH]
					{  
						12, 13, 15, 16, 24, 15, 22, 10, 9, 13, 13, 18, 16, 25, 23, 24, 
						18, 214, 35, 52, 99, 53, 47, 33, 69, 81, 23, 0, 1, 12, 109, 32, 
						44, 86
					};

					uint64_t sum;
					double mean;

					Assert::IsTrue(Array_Mean_Byte(values, LENGTH, &sum, &mean));
					Assert::AreEqual(1276ULL, sum);
					Assert::AreEqual(37.529411764705884, mean);
				}

				TEST_METHOD(Test_Array_Min_Byte)
				{
					const int LENGTH = 19;
					uint8_t result = 0;

					alignas(16) uint8_t values[LENGTH];

					for (uint8_t i = 0; i < LENGTH; i++)
					{
						values[i] = i + 1;
					}

					values[LENGTH - 1] = 0;

					Assert::IsTrue(Array_Min_Byte(values, LENGTH, &result));
					Assert::AreEqual(values[LENGTH - 1], result);
				}

				TEST_METHOD(Test_Array_Min_Float)
				{
					const uint32_t LENGTH = 19;
					float result = 0.0F;

					alignas(16) float values[LENGTH];

					for (uint32_t i = 0; i < LENGTH; i++)
					{
						values[i] = (float)i;
					}

					values[LENGTH - 1] = -1.0F;

					Assert::IsTrue(Array_Min_Float(values, LENGTH, &result));
					Assert::AreEqual(-1.0F, result);
				}

				TEST_METHOD(Test_Array_Sqtr_Float)
				{
					const uint32_t LENGTH = 19;

					alignas(16) float values[LENGTH];
					alignas(16) float results[LENGTH];

					for (uint32_t i = 0; i < LENGTH; i++)
					{
						values[i] = (float)i * (float)i;
					}

					Array_Sqtr_Float(values, LENGTH, results);

					for (uint32_t i = 0; i < LENGTH; i++)
					{
						Assert::AreEqual((float)i, results[i]);
					}
				}

				TEST_METHOD(Test_Compare_Equal_Double)
				{
					// 4 doubles (64 bits) in 128 bits (xmm register).
					const uint32_t LENGTH = 2;

					alignas(16) XmmVal a;
					alignas(16) XmmVal b;
					alignas(16) XmmVal results[LENGTH];

					a.Double[0] = 5.0;
					b.Double[0] = 5.0;

					a.Double[1] = 1.0;
					b.Double[1] = 2.0;

					Compare_Equal_Double(a, b, results);

					// Even though the results are stored in the double array,
					// they are in fact 2 long values (64 bits, same size as a double).
					// 0x0 = false
					// 0XF = true
					// As 0xF is NaN when double, we just check if it NaN, which means it's true.

					Assert::IsTrue(std::isnan(results->Double[0]));
					Assert::AreEqual(0.0, results->Double[1]);
				}

				TEST_METHOD(Test_Convert_Number)
				{
					// 4 float (32 bits) in 128 bits (xmm register).
					const uint32_t LENGTH = 4;

					alignas(16) XmmVal src;
					alignas(16) XmmVal des;

					src.Float[0] = 2.7F;
					src.Float[1] = 5.32F;
					src.Float[2] = -15.1523F;
					src.Float[3] = -5.22F;

					RoundingMode originalMode = Get_Rounding_Mode();

					// Lets use the same rounding mode as C++.
					Set_Rounding_Mode(RoundingMode::Truncate);

					bool converted = Convert_Number(src, des, CvtOp::F32_I32);

					Set_Rounding_Mode(originalMode);

					Assert::IsTrue(converted);

					for (uint32_t i = 0; i < LENGTH; i++)
					{
						Assert::AreEqual((int32_t)src.Float[i], des.Int32[i]);
					}
				}

				TEST_METHOD(Test_Matrix_Multiplication_Float)
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

					Matrix_Multiplication_Float(*matrixA, *matrixB, *results);

					const float TRUTH[4][4]
					{
						{12000.0F, 12046.0F, 12092.0F, 12138.0F},
						{22000.0F, 22086.0F, 22172.0F, 22258.0F},
						{32000.0F, 32126.0F, 32252.0F, 32378.0F},
						{42000.0F, 42166.0F, 42332.0F, 42498.0F}
					};

					for (uint32_t row = 0; row < 4; row++)
					{
						for (uint32_t column = 0; column < 4; column++)
						{
							Assert::AreEqual(TRUTH[row][column], results[row][column]);
						}
					}
				}

				TEST_METHOD(Test_Matrix_Transpose_Float)
				{
					alignas(16) float matrix[4][4]
					{
						{2.0F,  7.0F,  8.0F,  3.0F},
						{11.0F, 14.0F, 16.0F, 10.0F},
						{24.0F, 21.0F, 27.0F, 29.0F},
						{31.0F, 34.0F, 38.0F, 33.0F}
					};
					alignas(16) float results[4][4];

					Matrix_Transpose_Float(*matrix, *results);

					for (uint32_t row = 0; row < 4; row++)
					{
						for (uint32_t column = 0; column < 4; column++)
						{
							Assert::AreEqual(matrix[row][column], results[column][row]);
						}
					}
				}

				TEST_METHOD(Test_Multiply_Int_A)
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

					Multiply_Int_A(a, b, results);

					Assert::AreEqual((int64_t)4, results[0].Int64[0]);
					Assert::AreEqual((int64_t)-4, results[0].Int64[1]);
					Assert::AreEqual((int64_t)16, results[1].Int64[0]);
					Assert::AreEqual((int64_t)-16, results[1].Int64[1]);
				}

				TEST_METHOD(Test_Multiply_Int_B)
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

					Multiply_Int_B(a, b, results);

					Assert::AreEqual((int32_t)4, results.Int32[0]);
					Assert::AreEqual((int32_t)-4, results.Int32[1]);
					Assert::AreEqual((int32_t)16, results.Int32[2]);
					Assert::AreEqual((int32_t)-16, results.Int32[3]);
				}

				TEST_METHOD(Test_Multiply_Short)
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

					Multiply_Short(a, b, results);

					Assert::AreEqual((int32_t)4, results[0].Int32[0]);
					Assert::AreEqual((int32_t)-4, results[0].Int32[1]);
					Assert::AreEqual((int32_t)16, results[0].Int32[2]);
					Assert::AreEqual((int32_t)-16, results[0].Int32[3]);
					Assert::AreEqual((int32_t)-25, results[1].Int32[0]);
				}

				TEST_METHOD(Test_Shift_Integer)
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

					Assert::AreEqual(true, Shift_Integer(src, des, ShiftOp::U32_LOG_LEFT, 4));

					Assert::AreEqual((uint32_t)0x23456780, des.UInt32[0]);
					Assert::AreEqual((uint32_t)0xF00FF000, des.UInt32[1]);
					Assert::AreEqual((uint32_t)0x30303030, des.UInt32[2]);
					Assert::AreEqual((uint32_t)0x0800F0F0, des.UInt32[3]);
				}

				TEST_METHOD(Test_Sum_Float)
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

					Sum_Float(a, b, results);

					for (short i = 0; i < LENGTH; i++)
					{
						Assert::AreEqual((i + 1) * 2.0F, results->Float[i]);
					}
				}

				TEST_METHOD(Test_Sum_Short)
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

					Sum_Short(a, b, results);

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