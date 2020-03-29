
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