#include <math.h>
#include "pch.h"
#include "CppUnitTest.h"
#include "../Assembly/asm-headers/core_stack.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Assembly::Core::Stack;

namespace Assembly {
	namespace Test {
		namespace Core {
			TEST_CLASS(Stack)
			{
			public:
				TEST_METHOD(Test_Sum_Arguments)
				{
					Assert::AreEqual(36LL, Sum_Arguments(1, 2, 3, 4, 5, 6, 7, 8));
				}

				TEST_METHOD(Test_Sum_Arguments_Xmm)
				{
					Assert::AreEqual(36.0, Sum_Arguments_Xmm(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0));
				}

				TEST_METHOD(Test_Sum_Arguments_Xmm_Pow_2_Use_Macros)
				{
					const double SECOND_ARGUMENT = 2.0;
					const double RESULT = pow(36.0, 2.0) + 36.0 + SECOND_ARGUMENT;

					Assert::AreEqual(RESULT, Sum_Arguments_Xmm_Pow_2_Use_Macros(1.0, SECOND_ARGUMENT, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0));
				}
			};
		}
	}
}