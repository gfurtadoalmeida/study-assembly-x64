
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
			};
		}
	}
}