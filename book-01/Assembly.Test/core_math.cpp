#include "pch.h"
#include "CppUnitTest.h"
#include "../Assembly/asm-headers/core_math.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Assembly::Core::Math;

namespace Assembly {
	namespace Test {
		namespace Core {
			TEST_CLASS(Math)
			{
			public:
				TEST_METHOD(Test_Div)
				{
					int quotient;
					int remainder;

					Assert::AreEqual(1, Div(15, 5, &quotient, &remainder));
					Assert::AreEqual(3, quotient);
					Assert::AreEqual(0, remainder);
				}

				TEST_METHOD(Test_Max)
				{
					Assert::AreEqual(15, Max(10, 15, 5));
				}

				TEST_METHOD(Test_Max_v2)
				{
					Assert::AreEqual(15, Max_v2(10, 15, 5));
				}

				TEST_METHOD(Test_Min)
				{
					Assert::AreEqual(5, Min(10, 15, 5));
				}

				TEST_METHOD(Test_Min_v2)
				{
					Assert::AreEqual(5, Min_v2(10, 15, 5));
				}

				TEST_METHOD(Test_Sum)
				{
					Assert::AreEqual(5, Sum(2,3));
				}
			};
		}
	}
}