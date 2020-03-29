#include "pch.h"
#include "CppUnitTest.h"
#include "../Assembly/asm-headers/avx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Assembly::AVX;
using namespace Assembly::AVX::Types;

namespace Assembly {
	namespace Test {
		namespace AVX {
			TEST_CLASS(AVX)
			{
			public:
				TEST_METHOD(Test_Get_Rouding_Mode)
				{
					// The default rounding mode is "Nearest".
					Assert::AreEqual((unsigned int)RoundingMode::Nearest, (unsigned int)Get_Rounding_Mode());
				}

				TEST_METHOD(Test_Set_Rouding_Mode)
				{
					RoundingMode originalMode = Get_Rounding_Mode();

					Set_Rounding_Mode(RoundingMode::Up);

					RoundingMode changedMode = Get_Rounding_Mode();

					Set_Rounding_Mode(originalMode);

					Assert::AreNotEqual((unsigned int)originalMode, (unsigned int)changedMode);
					Assert::AreEqual((unsigned int)RoundingMode::Up, (unsigned int)changedMode);
				}
			};
		}
	}
}