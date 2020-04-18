#include "pch.h"
#include "CppUnitTest.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "../Assembly/asm-headers/utils.h"
#include "../Assembly/asm-headers/avx.h"
#include "../Assembly/asm-headers/avx2_packed.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Assembly::Utils;
using namespace Assembly::AVX::Types;
using namespace Assembly::AVX2::Packed;

namespace Assembly {
	namespace Test {
		namespace AVX2 {
			TEST_CLASS(Packed)
			{
			public:
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

				TEST_METHOD(Test_Clip_Pixel_Gray_Image)
				{
					alignas(32) uint8_t source[64];
					alignas(32) uint8_t destination[64];

					PixelClipData pcd;
					pcd.Source = source;
					pcd.Destination = destination;
					pcd.NumPixels = 64;
					pcd.NumClippedPixels = 0;
					pcd.ThresholdLow = 50;
					pcd.ThresholdHigh = 200;

					// 20 pixels lower than threshold low.
					for (uint8_t i = 0; i < 20; i++)
					{
						source[i] = 20;
					}

					// 30 pixels higher than threshold high.
					for (uint8_t i = 20; i < 50; i++)
					{
						source[i] = 255;
					}

					// 14 not-clipped pixels.
					for (uint8_t i = 50; i < 64; i++)
					{
						source[i] = i;
					}

					Assert::IsTrue(Clip_Pixel_Gray_Image(&pcd));
					Assert::AreEqual(50ULL, pcd.NumClippedPixels);
				}

				TEST_METHOD(Test_Convert_Float_HalfPrecision_And_Back)
				{
					// As C++ does not have native support for half-precision
					// numbers, I'll have to test the conversion to-and-from
					// together in this method.

					alignas(32) float values[8];
					values[0] = 4.15F;
					values[1] = 32.90F;
					values[2] = 56.32F;
					values[3] = -68.67F;
					values[4] = 420.55F;
					values[5] = 750.01F;
					values[6] = -62.12F;
					values[7] = 170.06F;

					alignas(32) uint16_t conversions[4][8];
					alignas(32) float results[4][8];

					Convert_Float_HalfPrecision(values, conversions[0], RoundingMode::Nearest);
					Convert_Float_HalfPrecision(values, conversions[1], RoundingMode::Up);
					Convert_Float_HalfPrecision(values, conversions[2], RoundingMode::Down);
					Convert_Float_HalfPrecision(values, conversions[3], RoundingMode::Truncate);

					Convert_HalfPrecision_Float(conversions[0], results[0]);
					Convert_HalfPrecision_Float(conversions[1], results[1]);
					Convert_HalfPrecision_Float(conversions[2], results[2]);
					Convert_HalfPrecision_Float(conversions[3], results[3]);

					// As there is loss of precision in the conversions, it is
					// impossible to just compare the original values with converted ones.
					for (size_t i = 0; i < 8; i++)
					{
						Assert::AreEqual(roundf(results[0][i]) * 10, roundf(values[i]) * 10);
						Assert::AreEqual(ceilf(results[1][i]) * 10, ceilf(values[i]) * 10);
						Assert::AreEqual(floorf(results[2][i]) * 10, floorf(values[i]) * 10);
						Assert::AreEqual(truncf(results[3][i]) * 10, truncf(values[i]) * 10);
					}
				}

				TEST_METHOD(Test_Convert_Short_Int)
				{
					alignas(32) YmmVal values;
					alignas(32) YmmVal result[2];

					for (uint16_t i = 0; i < 16; i++)
					{
						values.Int16[i] = i;
					}

					Convert_Short_Int(&values, result);

					for (size_t i = 0; i < 8; i++)
					{
						Assert::AreEqual((int32_t)values.Int16[i], result[0].Int32[i]);
						Assert::AreEqual((int32_t)values.Int16[i + 8], result[1].Int32[i]);
					}
				}

				TEST_METHOD(Test_Convert_Short_Long)
				{
					alignas(32) YmmVal values;
					alignas(32) YmmVal result[4];

					for (uint16_t i = 0; i < 16; i++)
					{
						values.Int16[i] = i;
					}

					Convert_Short_Long(&values, result);

					for (size_t i = 0; i < 4; i++)
					{
						Assert::AreEqual((int64_t)values.Int16[i], result[0].Int64[i]);
						Assert::AreEqual((int64_t)values.Int16[i + 4], result[1].Int64[i]);
						Assert::AreEqual((int64_t)values.Int16[i + 8], result[2].Int64[i]);
						Assert::AreEqual((int64_t)values.Int16[i + 12], result[3].Int64[i]);
					}
				}

				TEST_METHOD(Test_Convert_UByte_UInt)
				{
					alignas(32) YmmVal values;
					alignas(32) YmmVal result[4];

					for (uint8_t i = 0; i < 32; i++)
					{
						values.UByte[i] = i;
					}

					Convert_UByte_UInt(&values, result);

					for (size_t i = 0; i < 8; i++)
					{
						Assert::AreEqual((uint32_t)values.UByte[i], result[0].UInt32[i]);
						Assert::AreEqual((uint32_t)values.UByte[i + 8], result[1].UInt32[i]);
						Assert::AreEqual((uint32_t)values.UByte[i + 16], result[2].UInt32[i]);
						Assert::AreEqual((uint32_t)values.UByte[i + 24], result[3].UInt32[i]);
					}
				}

				TEST_METHOD(Test_Convert_UByte_UShort)
				{
					alignas(32) YmmVal values;
					alignas(32) YmmVal result[2];

					for (uint8_t i = 0; i < 32; i++)
					{
						values.UByte[i] = i;
					}

					Convert_UByte_UShort(&values, result);

					for (size_t i = 0; i < 16; i++)
					{
						// Had to invert the cast because the assert does not
						// works with uint16_t.
						Assert::AreEqual(values.UByte[i], (uint8_t)result[0].UInt16[i]);
						Assert::AreEqual(values.UByte[i + 16], (uint8_t)result[1].UInt16[i]);
					}
				}

				TEST_METHOD(Test_Gather_Double_I32)
				{
					alignas(32) double src[20];
					alignas(32) double des[8]{ -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0 };
					alignas(32) int32_t indexes[8]{ 1, 3, 5, 7, 9, 11, 13, 15 };
					alignas(32) int64_t merge[8]{ 1, 1, 0, 1, 1, 0, 1, 1 };

					for (size_t i = 0; i < 20; i++)
					{
						src[i] = i + 1.0;
					}

					Gather_Double(src, des, indexes, merge);

					for (size_t i = 0; i < 8; i++)
					{
						if (merge[i] == 0)
						{
							Assert::AreEqual(-1.0, des[i]);
						}
						else
						{
							Assert::AreEqual(src[indexes[i]], des[i]);
						}
					}
				}

				TEST_METHOD(Test_Gather_Double_I64)
				{
					alignas(32) double src[20];
					alignas(32) double des[8]{ -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0 };
					alignas(32) int64_t indexes[8]{ 1, 3, 5, 7, 9, 11, 13, 15 };
					alignas(32) int64_t merge[8]{ 1, 1, 0, 1, 1, 0, 1, 1 };

					for (size_t i = 0; i < 20; i++)
					{
						src[i] = i + 1.0;
					}

					Gather_Double(src, des, indexes, merge);

					for (size_t i = 0; i < 8; i++)
					{
						if (merge[i] == 0)
						{
							Assert::AreEqual(-1.0, des[i]);
						}
						else
						{
							Assert::AreEqual(src[indexes[i]], des[i]);
						}
					}
				}

				TEST_METHOD(Test_Gather_Float_I32)
				{
					alignas(32) float src[20];
					alignas(32) float des[8]{ -1.0F, -1.0F, -1.0F, -1.0F, -1.0F, -1.0F, -1.0F, -1.0F };
					alignas(32) int32_t indexes[8]{ 1, 3, 5, 7, 9, 11, 13, 15 };
					alignas(32) int32_t merge[8]{ 1, 1, 0, 1, 1, 0, 1, 1 };

					for (size_t i = 0; i < 20; i++)
					{
						src[i] = i + 1.0F;
					}

					Gather_Float(src, des, indexes, merge);

					for (size_t i = 0; i < 8; i++)
					{
						if (merge[i] == 0)
						{
							Assert::AreEqual(-1.0F, des[i]);
						}
						else
						{
							Assert::AreEqual(src[indexes[i]], des[i]);
						}
					}
				}

				TEST_METHOD(Test_Gather_Float_I64)
				{
					alignas(32) float src[20];
					alignas(32) float des[8]{ -1.0F, -1.0F, -1.0F, -1.0F, -1.0F, -1.0F, -1.0F, -1.0F };
					alignas(32) int64_t indexes[8]{ 1, 3, 5, 7, 9, 11, 13, 15 };
					alignas(32) int32_t merge[8]{ 1, 1, 0, 1, 1, 0, 1, 1 };

					for (size_t i = 0; i < 20; i++)
					{
						src[i] = i + 1.0F;
					}

					Gather_Float(src, des, indexes, merge);

					for (size_t i = 0; i < 8; i++)
					{
						if (merge[i] == 0)
						{
							Assert::AreEqual(-1.0F, des[i]);
						}
						else
						{
							Assert::AreEqual(src[indexes[i]], des[i]);
						}
					}
				}

				TEST_METHOD(Test_Pack_I32_I16)
				{
					alignas(32) YmmVal a;
					alignas(32) YmmVal b;
					alignas(32) YmmVal result;

					a.Int32[0] = 10;      b.Int32[0] = 32768;
					a.Int32[1] = -200000; b.Int32[1] = 6500;
					a.Int32[2] = 300000;  b.Int32[2] = 42000;
					a.Int32[3] = -4000;   b.Int32[3] = -68000;
					a.Int32[4] = 9000;    b.Int32[4] = 25000;
					a.Int32[5] = 80000;   b.Int32[5] = 500000;
					a.Int32[6] = 200;     b.Int32[6] = -7000;
					a.Int32[7] = -32769;  b.Int32[7] = 12500;

					Pack_I32_I16(a, b, &result);

					for (size_t i = 0; i < 4; i++)
					{
						Assert::AreEqual(ClampToShort(a.Int32[i]), result.Int16[i]);
						Assert::AreEqual(ClampToShort(b.Int32[i]), result.Int16[i + 4]);
						Assert::AreEqual(ClampToShort(a.Int32[i + 4]), result.Int16[i + 8]);
						Assert::AreEqual(ClampToShort(b.Int32[i + 4]), result.Int16[i + 12]);
					}
				}

				TEST_METHOD(Test_Permute_Float)
				{
					alignas(32) YmmVal src;
					alignas(32) YmmVal indexes;
					alignas(32) YmmVal results;

					src.Float[0] = 100; indexes.Int32[0] = 3;
					src.Float[1] = 200; indexes.Int32[1] = 2;
					src.Float[2] = 300; indexes.Int32[2] = 1;
					src.Float[3] = 400; indexes.Int32[3] = 0;
					src.Float[4] = 500; indexes.Int32[4] = 3;
					src.Float[5] = 600; indexes.Int32[5] = 2;
					src.Float[6] = 700; indexes.Int32[6] = 1;
					src.Float[7] = 800; indexes.Int32[7] = 0;

					Permute_Float(&src, &results, &indexes);

					for (size_t i = 0, r = 3; i < 4; i++, r--)
					{
						Assert::AreEqual(src.Float[i], results.Float[r]);
					}

					for (size_t i = 4, r = 7; i < 8; i++, r--)
					{
						Assert::AreEqual(src.Float[i], results.Float[r]);
					}
				}

				TEST_METHOD(Test_Sum_Int)
				{
					alignas(32) YmmVal a;
					alignas(32) YmmVal b;
					alignas(32) YmmVal result;

					// To test wraparound.
					a.Int32[0] = INT_MAX; b.Int32[0] = 100;

					for (uint32_t i = 1; i < 8; i++)
					{
						a.Int32[i] = i * 10;
						b.Int32[i] = a.Int32[i];
					}

					Sum_Int(a, b, result);

					Assert::AreEqual(INT_MIN + b.Int32[0] - 1, result.Int32[0]);

					for (size_t i = 1; i < 8; i++)
					{
						Assert::AreEqual(a.Int32[i] * 2, result.Int32[i]);
					}
				}

				TEST_METHOD(Test_Sum_Short)
				{
					alignas(32) YmmVal a;
					alignas(32) YmmVal b;
					alignas(32) YmmVal result;

					// To test saturation.
					a.Int16[0] = SHRT_MAX; b.Int16[0] = 100;

					for (uint16_t i = 1; i < 16; i++)
					{
						a.Int16[i] = i * 10;
						b.Int16[i] = a.Int16[i];
					}

					Sum_Short(a, b, result);

					Assert::AreEqual((short)SHRT_MAX, result.Int16[0]);

					for (size_t i = 1; i < 16; i++)
					{
						Assert::AreEqual((int16_t)(a.Int16[i] * 2), result.Int16[i]);
					}
				}
				
				TEST_METHOD(Test_Unpack_U32_U64)
				{
					alignas(32) YmmVal a;
					alignas(32) YmmVal b;

					a.UInt32[0] = 0x00000000; b.UInt32[0] = 0x88888888;
					a.UInt32[1] = 0x11111111; b.UInt32[1] = 0x99999999;
					a.UInt32[2] = 0x22222222; b.UInt32[2] = 0xaaaaaaaa;
					a.UInt32[3] = 0x33333333; b.UInt32[3] = 0xbbbbbbbb;
					a.UInt32[4] = 0x44444444; b.UInt32[4] = 0xcccccccc;
					a.UInt32[5] = 0x55555555; b.UInt32[5] = 0xdddddddd;
					a.UInt32[6] = 0x66666666; b.UInt32[6] = 0xeeeeeeee;
					a.UInt32[7] = 0x77777777; b.UInt32[7] = 0xffffffff;

					YmmValAB result = Unpack_U32_U64(a, b);

					Assert::AreEqual(Merge(b.UInt32[0], a.UInt32[0]), result.A.UInt64[0]);
					Assert::AreEqual(Merge(b.UInt32[1], a.UInt32[1]), result.A.UInt64[1]);
					Assert::AreEqual(Merge(b.UInt32[4], a.UInt32[4]), result.A.UInt64[2]);
					Assert::AreEqual(Merge(b.UInt32[5], a.UInt32[5]), result.A.UInt64[3]);

					Assert::AreEqual(Merge(b.UInt32[2], a.UInt32[2]), result.B.UInt64[0]);
					Assert::AreEqual(Merge(b.UInt32[3], a.UInt32[3]), result.B.UInt64[1]);
					Assert::AreEqual(Merge(b.UInt32[6], a.UInt32[6]), result.B.UInt64[2]);
					Assert::AreEqual(Merge(b.UInt32[7], a.UInt32[7]), result.B.UInt64[3]);
				}
			};
		}
	}
}