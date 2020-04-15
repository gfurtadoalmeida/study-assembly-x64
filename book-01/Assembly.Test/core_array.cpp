#include "pch.h"
#include "CppUnitTest.h"
#include "../Assembly/asm-headers/core_array.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Assembly::Core::Array;

namespace Assembly {
	namespace Test {
		namespace Core {
			TEST_CLASS(Array)
			{
			public:
				TEST_METHOD(Test_Compare)
				{
					const uint32_t ARRAYS_LENGTH = 5;
					int32_t a[ARRAYS_LENGTH] = { 1, 2, 3, 4, 5 };
					int32_t b[ARRAYS_LENGTH] = { 5, 4, 3, 2, 1 };
					int32_t* matchedValue;

					int32_t firstMatchIndex = Compare(&a[0], &b[0], ARRAYS_LENGTH, &matchedValue);

					Assert::AreNotEqual(-1, firstMatchIndex);
					Assert::AreEqual(2, firstMatchIndex);
					Assert::AreEqual(3, *matchedValue);
				}

				TEST_METHOD(Test_Get_From_Const)
				{
					const uint32_t EXPECTED_VALUES[] = { 10, 20, 30, 40, 50 };
					const uint32_t arrayLength = Get_From_Const_Array_Length();
					uint32_t value;

					Assert::AreEqual(5U, arrayLength);

					for (uint32_t i = 0; i < arrayLength; i++)
					{
						Assert::IsTrue(Get_From_Const(i, &value));
						Assert::AreEqual(EXPECTED_VALUES[i], value);
					}
				}

				TEST_METHOD(Test_Reverse)
				{
					const uint32_t LENGTH = 5;
					int32_t source[LENGTH] = { 1, 2, 3, 4, 5 };
					int32_t destination[LENGTH];

					Reverse(&source[0], &destination[0], LENGTH);

					for (int i = 0, r = LENGTH-1; i < LENGTH; i++, r--)
					{
						Assert::AreEqual(source[i], destination[r]);
					}
				}

				TEST_METHOD(Test_Sum)
				{
					int32_t data[] = { 10, 20, 30, 40, 50, -150 };

					Assert::AreEqual(0, Sum(&data[0], (sizeof(data) / sizeof(int32_t))));
				}

				TEST_METHOD(Test_Sum_Columns)
				{
					const uint32_t NUM_ROWS = 5;
					const uint32_t NUM_COLUMNS = 3;
					const int32_t EXPECTED_ANSWERS[NUM_ROWS] = { 1, 2, 3, 4, 5 };

					int32_t data[NUM_ROWS][NUM_COLUMNS] = { {1,1,-1}, {2,2,-2}, {3,3,-3}, {4,4,-4}, {5,5,-5} };
					int32_t answers[NUM_ROWS];

					Assert::IsTrue(Sum_Columns(&data[0][0], &answers[0], NUM_ROWS, NUM_COLUMNS));

					for (int i = 0; i < NUM_ROWS; i++)
					{
						Assert::AreEqual(EXPECTED_ANSWERS[i], answers[i]);
					}
				}
			};
		}
	}
}
