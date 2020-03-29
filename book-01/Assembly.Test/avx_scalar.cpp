
#include "pch.h"
#include "CppUnitTest.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "../Assembly/asm-headers/avx.h"
#include "../Assembly/asm-headers/avx_scalar.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Assembly::AVX;
using namespace Assembly::AVX::Scalar;
using namespace Assembly::AVX::Types;


namespace Assembly {
	namespace Test {
		namespace AVX {
			TEST_CLASS(Scalar)
			{
			public:
				TEST_METHOD(Test_Calc_Euclidian_Distance)
				{
					Assert::AreEqual(117.79643458101778, Calc_Euclidian_Distance(86.0, 84.0, 5.0, 32.0, 8.0, 77.0));
				}

				TEST_METHOD(Test_Calc_Mean_Stdev)
				{
					const double VALUES[] = { 10, 12, 23, 23, 16, 23, 21, 16 };
					const int LENGTH = sizeof(VALUES) / sizeof(double);
					double mean = 0.0;
					double stdev = 0.0;

					Assert::AreEqual(true, Calc_Mean_Stdev(&VALUES[0], LENGTH, &mean, &stdev));
					Assert::AreEqual(18.0, mean);
					Assert::AreEqual(4.8989794855663558, stdev);
				}

				TEST_METHOD(Test_Calc_Sphere_Area_Volume)
				{
					const double RADIOUS = 5.0;
					double area = -1;
					double volume = -1;

					Calc_Sphere_Area_Volume(RADIOUS, &area, &volume);

					Assert::AreEqual(314.15926535897933, area);
					Assert::AreEqual(523.59877559829886, volume);
				}

				TEST_METHOD(Test_Compare_Double_VCMPSD)
				{
					Assert::AreEqual(-1, Compare_Double_VCMPSD(10.0, 10.5));
					Assert::AreEqual(0, Compare_Double_VCMPSD(10.0, 10.0));
					Assert::AreEqual(1, Compare_Double_VCMPSD(10.5, 10.0));
				}

				TEST_METHOD(Test_Compare_Double_VCOMISD)
				{
					Assert::AreEqual(-1, Compare_Double_VCOMISD(10.0, 10.5));
					Assert::AreEqual(0, Compare_Double_VCOMISD(10.0, 10.0));
					Assert::AreEqual(1, Compare_Double_VCOMISD(10.5, 10.0));
				}

				TEST_METHOD(Test_Convert_Celsius_Fahrenheit)
				{
					Assert::AreEqual(98.6F, Convert_Celsius_Fahrenheit(37.0F));
				}

				TEST_METHOD(Test_Convert_Fahrenheit_Celsius)
				{
					Assert::AreEqual(37.0F, Convert_Fahrenheit_Celsius(98.6F));
				}

				TEST_METHOD(Test_Convert_Number)
				{
					Uval src1, src2, src3, src4, src5;
					Uval des1, des2, des3, des4, des5;

					src1.Float = (float)M_PI;
					src2.Float = (float)-M_E;
					src3.Double = M_SQRT2;
					src4.Double = M_SQRT1_2;
					src5.Double = 1.0 + DBL_EPSILON;

					RoundingMode originalMode = Get_Rounding_Mode();

					// Lets use the same rounding mode as
					// C++.
					Set_Rounding_Mode(RoundingMode::Truncate);

					Assert::AreEqual(true, Convert_Number(&src1, &des1, CvtOp::F32_I32));
					Assert::AreEqual(true, Convert_Number(&src2, &des2, CvtOp::F32_I64));
					Assert::AreEqual(true, Convert_Number(&src3, &des3, CvtOp::F64_I32));
					Assert::AreEqual(true, Convert_Number(&src4, &des4, CvtOp::F64_I64));
					Assert::AreEqual(true, Convert_Number(&src5, &des5, CvtOp::F64_F32));

					Set_Rounding_Mode(originalMode);

					Assert::AreEqual((int)src1.Float, des1.Int32);
					Assert::AreEqual((long long)src2.Float, des2.Int64);
					Assert::AreEqual((int)src3.Double, des3.Int32);
					Assert::AreEqual((long long)src4.Double, des4.Int64);
					Assert::AreEqual((float)src5.Double, des5.Float);
				}
			};
		}
	}
}