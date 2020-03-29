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
					const int ARRAYS_LENGTH = 5;
					int a[ARRAYS_LENGTH] = { 1, 2, 3, 4, 5 };
					int b[ARRAYS_LENGTH] = { 5, 4, 3, 2, 1 };
					int* matchedValue;

					int firstMatchIndex = Compare(&a[0], &b[0], ARRAYS_LENGTH, &matchedValue);

					Assert::AreEqual(2, firstMatchIndex);
					Assert::AreEqual(3, *matchedValue);
				}

				TEST_METHOD(Test_Get_From_Const)
				{
					const int EXPECTED_VALUES[] = { 10, 20, 30, 40, 50 };
					const int arrayLength = Get_From_Const_Array_Length();
					int value;

					Assert::AreEqual(5, arrayLength);

					for (int i = 0; i < arrayLength; i++)
					{
						Assert::AreEqual(1, Get_From_Const(i, &value));
						Assert::AreEqual(EXPECTED_VALUES[i], value);
					}
				}

				TEST_METHOD(Test_Reverse)
				{
					const int LENGTH = 5;
					int source[LENGTH] = { 1, 2, 3, 4, 5 };
					int destination[LENGTH];

					Reverse(&source[0], &destination[0], LENGTH);

					for (int i = 0, r = LENGTH-1; i < LENGTH; i++, r--)
					{
						Assert::AreEqual(source[i], destination[r]);
					}
				}

				TEST_METHOD(Test_Sum)
				{
					int data[] = { 10, 20, 30, 40, 50, -150 };

					Assert::AreEqual(0, Sum(&data[0], (sizeof(data) / sizeof(int))));
				}

				TEST_METHOD(Test_Sum_Columns)
				{
					const int NUM_ROWS = 5;
					const int NUM_COLUMNS = 3;
					const int EXPECTED_ANSWERS[NUM_ROWS] = { 1, 2, 3, 4, 5 };

					int data[NUM_ROWS][NUM_COLUMNS] = { {1,1,-1}, {2,2,-2}, {3,3,-3}, {4,4,-4}, {5,5,-5} };
					int answers[NUM_ROWS];

					int success = Sum_Columns(&data[0][0], &answers[0], NUM_ROWS, NUM_COLUMNS);

					Assert::AreEqual(1, success);

					for (int i = 0; i < NUM_ROWS; i++)
					{
						Assert::AreEqual(EXPECTED_ANSWERS[i], answers[i]);
					}
				}
			};
		}
	}
}
