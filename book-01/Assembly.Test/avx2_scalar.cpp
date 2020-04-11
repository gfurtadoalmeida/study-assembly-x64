#include "pch.h"
#include "CppUnitTest.h"
#include "../Assembly/asm-headers/avx.h"
#include "../Assembly/asm-headers/avx2_scalar.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Assembly::AVX::Types;
using namespace Assembly::AVX2::Scalar;

namespace Assembly {
	namespace Test {
		namespace AVX2 {
			TEST_CLASS(Scalar)
			{
				TEST_METHOD(Test_And_Not)
				{
					uint32_t a = 100;
					uint32_t b = 50;

					Assert::AreEqual(~a & b, And_Not(a, b));
				}

				TEST_METHOD(Test_Count_Zero_Bits)
				{
					uint32_t value = 0b00000000000000000000010000000000;
					uint32_t leadingZeros = 0;
					uint32_t trailingZeros = 0;

					Count_Zero_Bits(value, &leadingZeros, &trailingZeros);

					Assert::AreEqual(21U, leadingZeros);
					Assert::AreEqual(10U, trailingZeros);
				}

				TEST_METHOD(Test_Extract_Bits)
				{
					uint32_t value = 0b00000000000000000101010101000000;

					Assert::AreEqual(0b0101010101U, Extract_Bits(value, 6, 10));
				}

				TEST_METHOD(Test_Flagless_Multiply_UInt)
				{
					uint64_t flags[2];

					Assert::AreEqual(8ULL, Flagless_Multiply_UInt(2, 4, flags));
					Assert::AreEqual(flags[0], flags[1]);
				}

				TEST_METHOD(Test_Flagless_Shift_UInt)
				{
					const uint32_t value = 0x800F0000U;
					uint32_t results[3];
					uint64_t flags[4];

					Flagless_Shift_UInt(value, 4, results, flags);

					Assert::AreEqual(0xF800F000U, results[0]);
					Assert::AreEqual(0x00F00000U, results[1]);
					Assert::AreEqual(0x0800F000U, results[2]);

					Assert::AreEqual(flags[0], flags[1]);
					Assert::AreEqual(flags[0], flags[2]);
					Assert::AreEqual(flags[0], flags[3]);
				}
			};
		}
	}
}