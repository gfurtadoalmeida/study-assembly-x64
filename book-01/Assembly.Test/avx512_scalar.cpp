#include "pch.h"

#if BUILD_AVX512 == 1

#include "CppUnitTest.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "../Assembly/asm-headers/avx.h"
#include "../Assembly/asm-headers/avx512_scalar.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Assembly::AVX::Types;
using namespace Assembly::AVX512::Scalar;

namespace Assembly {
	namespace Test {
		namespace AVX512 {
			TEST_CLASS(Scalar)
			{
			public:
				TEST_METHOD(Test_Calc_Conditional_Sum_Zero_Masking)
				{
					const uint32_t LENGTH = 6;

					alignas(64) double a[LENGTH] = { 10.0, 20.0, 30.0, 40.0, 30.0, 60.0 };
					alignas(64) double b[LENGTH] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
					alignas(64) double result[LENGTH];

					Assert::IsTrue(Calc_Conditional_Sum_Zero_Masking(a, b, result, LENGTH, 30.0));
					Assert::AreEqual(11.0, result[0]);
					Assert::AreEqual(22.0, result[1]);
					Assert::AreEqual(0.0, result[2]);
					Assert::AreEqual(44.0, result[3]);
					Assert::AreEqual(0.0, result[4]);
					Assert::AreEqual(66.0, result[5]);
				}

				TEST_METHOD(Test_Calc_Sphere_Area_Volume)
				{
					double radius = 2.0;
					double area = 0.0;
					double volume = 0.0;

					double areaCompare = 4.0 * M_PI * pow(radius, 2);
					double volumeCompare = (areaCompare * radius) / 3;

					Assert::IsTrue(Calc_Sphere_Area_Volume(radius, &area, &volume, HUGE_VAL));
					Assert::AreEqual(trunc(areaCompare * 100), trunc(area * 100));
					Assert::AreEqual(trunc(volumeCompare * 100), trunc(volume * 100));

					Assert::IsFalse(Calc_Sphere_Area_Volume(-1.0, &area, &volume, HUGE_VAL));
					Assert::AreEqual(HUGE_VAL, area);
					Assert::AreEqual(HUGE_VAL, volume);
				}

				TEST_METHOD(Test_Convert_Round_F32_U32)
				{
					uint32_t result[4];

					Convert_Round_F32_U32(3.14159F, result);

					Assert::AreEqual(3U, result[0]);
					Assert::AreEqual(3U, result[1]);
					Assert::AreEqual(4U, result[2]);
					Assert::AreEqual(3U, result[3]);
				}

				TEST_METHOD(Test_Convert_Round_F64_F32)
				{
					float result[4];

					Convert_Round_F64_F32(3.1415927, result);

					Assert::AreEqual(3.1415927F, result[0]);
					Assert::AreEqual(3.1415925F, result[1]);
					Assert::AreEqual(3.1415927F, result[2]);
					Assert::AreEqual(3.1415925F, result[3]);
				}

				TEST_METHOD(Test_Convert_Round_F64_U64)
				{
					uint64_t result[4];

					Convert_Round_F64_U64(1.41421, result);

					Assert::AreEqual(1ULL, result[0]);
					Assert::AreEqual(1ULL, result[1]);
					Assert::AreEqual(2ULL, result[2]);
					Assert::AreEqual(1ULL, result[3]);
				}
			};
		}
	}
}

#endif