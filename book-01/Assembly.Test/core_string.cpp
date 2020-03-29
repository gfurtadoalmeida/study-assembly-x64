#include "pch.h"
#include "CppUnitTest.h"
#include "../Assembly/asm-headers/core_string.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Assembly::Core::String;

namespace Assembly {
	namespace Test {
		namespace Core {
			TEST_CLASS(String)
			{
			public:
				TEST_METHOD(Test_Concat)
				{
					const int NUM_ELEMENTS = 4;
					const int DEST_LENGTH = 24;
					const char* SOURCE[NUM_ELEMENTS] = { "This ", "Must ","Be ", "Concatened" };
					char destination[DEST_LENGTH];

					Assert::AreEqual((size_t)DEST_LENGTH - 1, Concat(SOURCE, NUM_ELEMENTS, &destination[0], DEST_LENGTH));
					Assert::AreEqual("This Must Be Concatened", destination);
				}

				TEST_METHOD(Test_Count_Char_Occurrence)
				{
					char text[] = "Saxon Lamb of God Flotsam and Jetsam";

					int occurrences = Count_Char_Occurrence(&text[0], 'a');

					Assert::AreEqual(5, occurrences);
				}
			};
		}
	}
}