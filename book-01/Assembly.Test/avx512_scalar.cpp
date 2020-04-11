#include "pch.h"
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
			};
		}
	}
}