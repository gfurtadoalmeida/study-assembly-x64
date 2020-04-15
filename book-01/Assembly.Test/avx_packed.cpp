
#include "pch.h"
#include "CppUnitTest.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "../Assembly/asm-headers/avx.h"
#include "../Assembly/asm-headers/avx_packed.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Assembly::AVX;
using namespace Assembly::AVX::Packed;
using namespace Assembly::AVX::Types;

namespace Assembly {
	namespace Test {
		namespace AVX {
			TEST_CLASS(Packed)
			{
				// The use of "alignas(16)" or "alignas(32)" instruction on the 
				// tests below are necessary because they use aligned AVX instructions.
				// We could omit it if unaligned AVX instructions were used.
				// For performance, aligned instructions should be used.
				//
				// For any array, use a length bigger than and not 
				// divisible by 16 so we can test the batch and one-by-one
				// processing modes.
				//
				// Use of alignas:
				// - 128 bits = alignas(16)
				// - 256 bits = alignas(32)

			public:
				TEST_METHOD(Test_Array_Max_Byte)
				{
					const uint32_t LENGTH = 19;
					uint8_t result = 0;

					alignas(16) uint8_t values[LENGTH];

					for (uint8_t i = 0; i < LENGTH; i++)
					{
						values[i] = i;
					}

					Assert::IsTrue(Array_Max_Byte(values, LENGTH, &result));
					Assert::AreEqual(values[LENGTH - 1], result);
				}

				TEST_METHOD(Test_Array_Max_Float)
				{
					const uint32_t LENGTH = 19;
					float result = 0.0F;

					alignas(16) float values[LENGTH];

					for (uint32_t i = 0; i < LENGTH; i++)
					{
						values[i] = (float)i;
					}

					Assert::IsTrue(Array_Max_Float(values, LENGTH, &result));
					Assert::AreEqual(values[LENGTH - 1], result);
				}

				TEST_METHOD(Test_Array_Mean_Byte)
				{
					// This array need a length bigger than and not 
					// divisible by 32 so we can test the batch and one-by-one
					// processing modes.
					const uint32_t LENGTH = 34;

					alignas(16) uint8_t values[LENGTH]
					{
						12, 13, 15, 16, 24, 15, 22, 10, 9, 13, 13, 18, 16, 25, 23, 24,
						18, 214, 35, 52, 99, 53, 47, 33, 69, 81, 23, 0, 1, 12, 109, 32,
						44, 86
					};

					uint64_t sum;
					double mean;

					Assert::IsTrue(Array_Mean_Byte(values, LENGTH, &sum, &mean));
					Assert::AreEqual(1276ULL, sum);
					Assert::AreEqual(37.529411764705884, mean);
				}

				TEST_METHOD(Test_Array_Min_Byte)
				{
					const int LENGTH = 19;
					uint8_t result = 0;

					alignas(16) uint8_t values[LENGTH];

					for (uint8_t i = 0; i < LENGTH; i++)
					{
						values[i] = i + 1;
					}

					values[LENGTH - 1] = 0;

					Assert::IsTrue(Array_Min_Byte(values, LENGTH, &result));
					Assert::AreEqual(values[LENGTH - 1], result);
				}

				TEST_METHOD(Test_Array_Min_Float)
				{
					const uint32_t LENGTH = 19;
					float result = 0.0F;

					alignas(16) float values[LENGTH];

					for (uint32_t i = 0; i < LENGTH; i++)
					{
						values[i] = (float)i;
					}

					values[LENGTH - 1] = -1.0F;

					Assert::IsTrue(Array_Min_Float(values, LENGTH, &result));
					Assert::AreEqual(-1.0F, result);
				}

				TEST_METHOD(Test_Array_Sqtr_Float)
				{
					const uint32_t LENGTH = 19;

					alignas(16) float values[LENGTH];
					alignas(16) float results[LENGTH];

					for (uint32_t i = 0; i < LENGTH; i++)
					{
						values[i] = (float)i * (float)i;
					}

					Array_Sqtr_Float(values, LENGTH, results);

					for (uint32_t i = 0; i < LENGTH; i++)
					{
						Assert::AreEqual((float)i, results[i]);
					}
				}

				TEST_METHOD(Test_Compare_Equal_Double)
				{
					// 4 doubles (64 bits) in 128 bits (xmm register).
					const uint32_t LENGTH = 2;

					alignas(16) XmmVal a;
					alignas(16) XmmVal b;
					alignas(16) XmmVal results[LENGTH];

					a.Double[0] = 5.0;
					b.Double[0] = 5.0;

					a.Double[1] = 1.0;
					b.Double[1] = 2.0;

					Compare_Equal_Double(a, b, results);

					// Even though the results are stored in the double array,
					// they are in fact 2 long values (64 bits, same size as a double).
					// 0x0 = false
					// 0XF = true
					// As 0xF is NaN when double, we just check if it NaN, which means it's true.

					Assert::IsTrue(std::isnan(results->Double[0]));
					Assert::AreEqual(0.0, results->Double[1]);
				}

				TEST_METHOD(Test_Convert_Byte_To_Float_0_1_Range)
				{
					// This array needs a length bigger than and not 
					// divisible by 32 so we can test the batch and one-by-one
					// processing modes.
					const uint32_t LENGTH = 34;

					alignas(16) uint8_t values[LENGTH]
					{
						12, 13, 15, 16, 24, 15, 22, 10, 9, 13, 13, 18, 16, 25, 23, 24,
						18, 214, 35, 52, 99, 53, 47, 33, 69, 81, 23, 0, 1, 12, 109, 32,
						44, 86
					};
					alignas(16) float output[LENGTH];

					Assert::IsTrue(Convert_Byte_To_Float_0_1_Range(values, LENGTH, output));

					for (size_t i = 0; i < LENGTH; i++)
					{
						Assert::AreEqual(values[i], (uint8_t)ceilf(output[i] * 255.0F));
					}
				}

				TEST_METHOD(Test_Convert_Float_To_Byte_0_255_Range)
				{
					// This array needs a length bigger than and not 
					// divisible by 32 so we can test the batch and one-by-one
					// processing modes.
					const uint32_t LENGTH = 34;

					alignas(16) float values[LENGTH]
					{
						1.0F, 0.3F,  0.5F, 0.6F, 0.7F, 0.8F, 0.95F, 0.96F, 0.96F, 0.3F, 0.1F, 0.22F, 0.33F, 0.97F, 1.0F, 0.0F,
						0.8F, 0.24F, 0.65F, 0.0F, 0.0F, 0.3F, 0.23F, 0.52F, 0.69F, 0.81F, 0.22F, 0.0F, 1.0F, 0.20F, 0.52F, 0.22F,
						0.44F, 0.86F
					};
					alignas(16) uint8_t output[LENGTH];

					// Lets use the same rounding mode.
					Set_Rounding_Mode(RoundingMode::Truncate);

					bool converted = Convert_Float_To_Byte_0_255_Range(values, LENGTH, output);

					Set_Rounding_Mode(RoundingMode::Nearest);

					Assert::IsTrue(converted);

					for (size_t i = 0; i < LENGTH; i++)
					{
						Assert::AreEqual((uint8_t)truncf(values[i] * 255), output[i]);
					}
				}

				TEST_METHOD(Test_Convert_Number)
				{
					// 4 float (32 bits) in 128 bits (xmm register).
					const uint32_t LENGTH = 4;

					alignas(16) XmmVal src;
					alignas(16) XmmVal des;

					src.Float[0] = 2.7F;
					src.Float[1] = 5.32F;
					src.Float[2] = -15.1523F;
					src.Float[3] = -5.22F;

					RoundingMode originalMode = Get_Rounding_Mode();

					// Lets use the same rounding mode as C++.
					Set_Rounding_Mode(RoundingMode::Truncate);

					bool converted = Convert_Number(src, des, CvtOp::F32_I32);

					Set_Rounding_Mode(originalMode);

					Assert::IsTrue(converted);

					for (uint32_t i = 0; i < LENGTH; i++)
					{
						Assert::AreEqual((int32_t)src.Float[i], des.Int32[i]);
					}
				}

				TEST_METHOD(Test_Histogram_Gray_Image)
				{
					// This array needs a length bigger than and not 
					// divisible by 32 so we can test the batch and one-by-one
					// processing modes.
					const uint32_t LENGTH = 34;

					alignas(16) uint8_t values[LENGTH]
					{
						0, 0, 0, 0, 0, 0, 0, 0,
						63, 63, 63, 63, 63, 63, 63, 63,
						127, 127, 127, 127, 127, 127, 127, 127,
						255, 255, 255, 255, 255, 255, 255, 255,
						15, 31
					};
					alignas(16) uint32_t output[256];

					Assert::IsTrue(Histogram_Gray_Image(values, LENGTH, output));

					Assert::AreEqual(8U, output[0]);
					Assert::AreEqual(8U, output[63]);
					Assert::AreEqual(8U, output[127]);
					Assert::AreEqual(8U, output[255]);
					Assert::AreEqual(1U, output[15]);
					Assert::AreEqual(1U, output[31]);
				}

				TEST_METHOD(Test_Matrix_Multiplication_Float)
				{
					alignas(16) float matrixA[4][4]
					{
						{10.0F, 11.0F, 12.0F, 13.0F},
						{20.0F, 21.0F, 22.0F, 23.0F},
						{30.0F, 31.0F, 32.0F, 33.0F},
						{40.0F, 41.0F, 42.0F, 43.0F}
					};
					alignas(16) float matrixB[4][4]
					{
						{100.0F, 101.0F, 102.0F, 103.0F},
						{200.0F, 201.0F, 202.0F, 203.0F},
						{300.0F, 301.0F, 302.0F, 303.0F},
						{400.0F, 401.0F, 402.0F, 403.0F}
					};
					alignas(16) float results[4][4];

					Matrix_Multiplication_Float(*matrixA, *matrixB, *results);

					const float TRUTH[4][4]
					{
						{12000.0F, 12046.0F, 12092.0F, 12138.0F},
						{22000.0F, 22086.0F, 22172.0F, 22258.0F},
						{32000.0F, 32126.0F, 32252.0F, 32378.0F},
						{42000.0F, 42166.0F, 42332.0F, 42498.0F}
					};

					for (uint32_t row = 0; row < 4; row++)
					{
						for (uint32_t column = 0; column < 4; column++)
						{
							Assert::AreEqual(TRUTH[row][column], results[row][column]);
						}
					}
				}

				TEST_METHOD(Test_Matrix_Transpose_Float)
				{
					alignas(16) float matrix[4][4]
					{
						{2.0F,  7.0F,  8.0F,  3.0F},
						{11.0F, 14.0F, 16.0F, 10.0F},
						{24.0F, 21.0F, 27.0F, 29.0F},
						{31.0F, 34.0F, 38.0F, 33.0F}
					};
					alignas(16) float results[4][4];

					Matrix_Transpose_Float(*matrix, *results);

					for (uint32_t row = 0; row < 4; row++)
					{
						for (uint32_t column = 0; column < 4; column++)
						{
							Assert::AreEqual(matrix[row][column], results[column][row]);
						}
					}
				}

				TEST_METHOD(Test_Multiply_Int_A)
				{
					alignas(16) XmmVal a;
					alignas(16) XmmVal b;
					alignas(16) XmmVal results[2];

					a.Int32[0] = 2;
					b.Int32[0] = 2;

					a.Int32[1] = -2;
					b.Int32[1] = 2;

					a.Int32[2] = 4;
					b.Int32[2] = 4;

					a.Int32[3] = -4;
					b.Int32[3] = 4;

					Multiply_Int_A(a, b, results);

					Assert::AreEqual((int64_t)4, results[0].Int64[0]);
					Assert::AreEqual((int64_t)-4, results[0].Int64[1]);
					Assert::AreEqual((int64_t)16, results[1].Int64[0]);
					Assert::AreEqual((int64_t)-16, results[1].Int64[1]);
				}

				TEST_METHOD(Test_Multiply_Int_B)
				{
					alignas(16) XmmVal a;
					alignas(16) XmmVal b;
					alignas(16) XmmVal results;

					a.Int32[0] = 2;
					b.Int32[0] = 2;

					a.Int32[1] = -2;
					b.Int32[1] = 2;

					a.Int32[2] = 4;
					b.Int32[2] = 4;

					a.Int32[3] = -4;
					b.Int32[3] = 4;

					Multiply_Int_B(a, b, results);

					Assert::AreEqual((int32_t)4, results.Int32[0]);
					Assert::AreEqual((int32_t)-4, results.Int32[1]);
					Assert::AreEqual((int32_t)16, results.Int32[2]);
					Assert::AreEqual((int32_t)-16, results.Int32[3]);
				}

				TEST_METHOD(Test_Multiply_Short)
				{
					alignas(16) XmmVal a;
					alignas(16) XmmVal b;
					alignas(16) XmmVal results[2];

					a.Int16[0] = 2;
					b.Int16[0] = 2;

					a.Int16[1] = -2;
					b.Int16[1] = 2;

					a.Int16[2] = 4;
					b.Int16[2] = 4;

					a.Int16[3] = -4;
					b.Int16[3] = 4;

					a.Int16[4] = -5;
					b.Int16[4] = 5;

					Multiply_Short(a, b, results);

					Assert::AreEqual((int32_t)4, results[0].Int32[0]);
					Assert::AreEqual((int32_t)-4, results[0].Int32[1]);
					Assert::AreEqual((int32_t)16, results[0].Int32[2]);
					Assert::AreEqual((int32_t)-16, results[0].Int32[3]);
					Assert::AreEqual((int32_t)-25, results[1].Int32[0]);
				}

				TEST_METHOD(Test_Shift_Integer)
				{
					alignas(16) XmmVal src;
					alignas(16) XmmVal des;

					// Each HEX digit = 4 bits
					// Shifting by 4 means just moving a
					// digit left /right.
					// HEX are cool!

					src.UInt32[0] = 0x12345678;
					src.UInt32[1] = 0xFF00FF00;
					src.UInt32[2] = 0x03030303;
					src.UInt32[3] = 0x80800F0F;

					Assert::AreEqual(true, Shift_Integer(src, des, ShiftOp::U32_LOG_LEFT, 4));

					Assert::AreEqual((uint32_t)0x23456780, des.UInt32[0]);
					Assert::AreEqual((uint32_t)0xF00FF000, des.UInt32[1]);
					Assert::AreEqual((uint32_t)0x30303030, des.UInt32[2]);
					Assert::AreEqual((uint32_t)0x0800F0F0, des.UInt32[3]);
				}

				TEST_METHOD(Test_Sum_Float)
				{
					// 4 float (32 bits) in 128 bits (xmm register).
					const int LENGTH = 4;

					alignas(16) XmmVal a;
					alignas(16) XmmVal b;
					alignas(16) XmmVal results[LENGTH];

					for (short i = 0; i < LENGTH; i++)
					{
						a.Float[i] = i + 1.0F;
						b.Float[i] = i + 1.0F;
					}

					Sum_Float(a, b, results);

					for (short i = 0; i < LENGTH; i++)
					{
						Assert::AreEqual((i + 1) * 2.0F, results->Float[i]);
					}
				}

				TEST_METHOD(Test_Sum_Short)
				{
					alignas(16) XmmVal a;
					alignas(16) XmmVal b;
					alignas(16) XmmVal results[2];

					// We can fit 8 short numbers in it but I 
					// send only 4.
					a.Int16[0] = 10;
					b.Int16[0] = 100;

					a.Int16[1] = 200;
					b.Int16[1] = -200;

					a.Int16[2] = 30;
					b.Int16[2] = 32760;

					a.Int16[3] = -32766;
					b.Int16[3] = -400;

					Sum_Short(a, b, results);

					// Wraparound
					Assert::AreEqual((int16_t)110, results[0].Int16[0]);
					Assert::AreEqual((int16_t)0, results[0].Int16[1]);
					Assert::AreEqual((int16_t)-32746, results[0].Int16[2]);
					Assert::AreEqual((int16_t)32370, results[0].Int16[3]);

					// Saturated
					Assert::AreEqual((int16_t)110, results[1].Int16[0]);
					Assert::AreEqual((int16_t)0, results[1].Int16[1]);
					Assert::AreEqual((int16_t)32767, results[1].Int16[2]);
					Assert::AreEqual((int16_t)-32768, results[1].Int16[3]);
				}

				TEST_METHOD(Test_Y_Abs_Double)
				{
					// 4 double (64 bits) in 256 bits (ymm register).
					const int LENGTH = 4;

					alignas(32) YmmVal a;
					alignas(32) YmmVal results[LENGTH];

					for (short i = 0; i < LENGTH; i++)
					{
						a.Double[i] = -(i + 1);
					}

					Y_Abs_Double(a, results);

					for (short i = 0; i < LENGTH; i++)
					{
						Assert::AreEqual(i + 1.0, results->Double[i]);
					}
				}

				TEST_METHOD(Test_Y_Array_Cols_Mean_Double)
				{
					const int ROWS = 2;
					const int COLS = 8;

					alignas(32) double matrix[ROWS][COLS]
					{
						{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 },
						{ 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 }
					};
					alignas(32) double means[COLS];

					Y_Array_Cols_Mean_Double(&matrix[0][0], ROWS, COLS, means);

					Assert::AreEqual(1.5, means[0]);
					Assert::AreEqual(2.5, means[1]);
					Assert::AreEqual(3.5, means[2]);
					Assert::AreEqual(4.5, means[3]);
					Assert::AreEqual(5.5, means[4]);
					Assert::AreEqual(6.5, means[5]);
					Assert::AreEqual(7.5, means[6]);
					Assert::AreEqual(8.5, means[7]);
				}

				TEST_METHOD(Test_Y_Blend_Float)
				{
					alignas(32) YmmVal src1;
					alignas(32) YmmVal src2;
					alignas(32) YmmVal results;
					alignas(32) BlendSource blends[8]
					{
						  BlendSource::Source2,
						  BlendSource::Source2,
						  BlendSource::Source2,
						  BlendSource::Source2,
						  BlendSource::Source1,
						  BlendSource::Source1,
						  BlendSource::Source1,
						  BlendSource::Source1
					};

					src1.Float[0] = 100; src2.Float[0] = 10;
					src1.Float[1] = 200; src2.Float[1] = 20;
					src1.Float[2] = 300; src2.Float[2] = 30;
					src1.Float[3] = 400; src2.Float[3] = 40;
					src1.Float[4] = 500; src2.Float[4] = 50;
					src1.Float[5] = 600; src2.Float[5] = 60;
					src1.Float[6] = 700; src2.Float[6] = 70;
					src1.Float[7] = 800; src2.Float[7] = 80;

					Y_Blend_Float(&src1, &src2, &results, blends);

					for (size_t i = 0; i < 4; i++)
					{
						Assert::AreEqual(src2.Float[i], results.Float[i]);
					}

					for (size_t i = 4; i < 8; i++)
					{
						Assert::AreEqual(src1.Float[i], results.Float[i]);
					}
				}

				TEST_METHOD(Test_Y_Calc_Correlation_Coefficient)
				{
					const int LENGTH = 6;
					alignas(32) double x[LENGTH]{ 5.0, 10.0, 15.0, 20.0, 25.0, 30.0 };
					alignas(32) double y[LENGTH]{ 2.0, 4.0, 6.0, 8.0, 10.0, 12.0 };
					alignas(32) double sums[5];
					double rho;
					double epsilon = 1.0e-12;

					Assert::IsTrue(Y_Calc_Correlation_Coefficient(x, y, LENGTH, sums, epsilon, &rho));

					Assert::AreEqual(105.0, sums[0]);
					Assert::AreEqual(42.0, sums[1]);
					Assert::AreEqual(2275.0, sums[2]);
					Assert::AreEqual(364.0, sums[3]);
					Assert::AreEqual(910.0, sums[4]);
				}

				TEST_METHOD(Test_Y_Calc_Sphere_Area_Volume)
				{
					// 8 float (32 bits) in 256 bits (ymm register).
					const int LENGTH = 8;

					alignas(32) float radius[LENGTH]{ NAN, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F };
					alignas(32) float areas[LENGTH];
					alignas(32) float volumes[LENGTH];

					Y_Calc_Sphere_Area_Volume(radius, LENGTH, areas, volumes, NAN);

					// Skip the first item. It will be tested alone.
					for (size_t i = 1; i < LENGTH; i++)
					{
						float area = 4.0F * (float)M_PI * powf(radius[i], 2);
						float volume = (area * radius[i]) / 3;

						// Compare with 2 decimal digits only.
						Assert::AreEqual(trunc(area * 100), trunc(areas[i] * 100));
						Assert::AreEqual(trunc(volume * 100), trunc(volumes[i] * 100));
					}

					Assert::IsTrue(isnan(areas[0]));
					Assert::IsTrue(isnan(volumes[0]));
				}

				TEST_METHOD(Test_Y_Matrix_Multiplication_Double)
				{
					alignas(32) double matrixA[4][4]
					{
						{10.0, 11.0, 12.0, 13.0},
						{20.0, 21.0, 22.0, 23.0},
						{30.0, 31.0, 32.0, 33.0},
						{40.0, 41.0, 42.0, 43.0}
					};
					alignas(32) double matrixB[4][4]
					{
						{100.0, 101.0, 102.0, 103.0},
						{200.0, 201.0, 202.0, 203.0},
						{300.0, 301.0, 302.0, 303.0},
						{400.0, 401.0, 402.0, 403.0}
					};
					alignas(32) double results[4][4];

					Y_Matrix_Multiplication_Double(*matrixA, *matrixB, *results);

					const double TRUTH[4][4]
					{
						{12000.0, 12046.0, 12092.0, 12138.0},
						{22000.0, 22086.0, 22172.0, 22258.0},
						{32000.0, 32126.0, 32252.0, 32378.0},
						{42000.0, 42166.0, 42332.0, 42498.0}
					};

					for (uint32_t row = 0; row < 4; row++)
					{
						for (uint32_t column = 0; column < 4; column++)
						{
							Assert::AreEqual(TRUTH[row][column], results[row][column]);
						}
					}
				}

				TEST_METHOD(Test_Y_Matrix_Transpose_Double)
				{
					alignas(32) double matrix[4][4]
					{
						{2.0,  7.0,  8.0,  3.0},
						{11.0, 14.0, 16.0, 10.0},
						{24.0, 21.0, 27.0, 29.0},
						{31.0, 34.0, 38.0, 33.0}
					};
					alignas(32) double results[4][4];

					Y_Matrix_Transpose_Double(*matrix, *results);

					for (uint32_t row = 0; row < 4; row++)
					{
						for (uint32_t column = 0; column < 4; column++)
						{
							Assert::AreEqual(matrix[row][column], results[column][row]);
						}
					}
				}

				TEST_METHOD(Test_Y_Permute_Float)
				{
					alignas(32) YmmVal src;
					alignas(32) YmmVal indexes;
					alignas(32) YmmVal results;

					src.Float[0] = 100; indexes.Int32[0] = 7;
					src.Float[1] = 200; indexes.Int32[1] = 6;
					src.Float[2] = 300; indexes.Int32[2] = 5;
					src.Float[3] = 400; indexes.Int32[3] = 4;
					src.Float[4] = 500; indexes.Int32[4] = 3;
					src.Float[5] = 600; indexes.Int32[5] = 2;
					src.Float[6] = 700; indexes.Int32[6] = 1;
					src.Float[7] = 800; indexes.Int32[7] = 0;

					Y_Permute_Float(&src, &results, &indexes);

					for (size_t i = 0, r = 7; i < 8; i++, r--)
					{
						Assert::AreEqual(src.Float[i], results.Float[r]);
					}
				}

				TEST_METHOD(Test_Y_Sum_Float)
				{
					// 8 float (32 bits) in 256 bits (ymm register).
					const int LENGTH = 8;

					alignas(32) YmmVal a;
					alignas(32) YmmVal b;
					alignas(32) YmmVal results[LENGTH];

					for (short i = 0; i < LENGTH; i++)
					{
						a.Float[i] = i + 1.0F;
						b.Float[i] = i + 1.0F;
					}

					Y_Sum_Float(a, b, results);

					for (short i = 0; i < LENGTH; i++)
					{
						Assert::AreEqual((i + 1) * 2.0F, results->Float[i]);
					}
				}
			};
		}
	}
}