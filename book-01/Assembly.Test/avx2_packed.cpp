#define _USE_MATH_DEFINES
#include "pch.h"
#include "CppUnitTest.h"
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

				TEST_METHOD(Test_Gather_Double_I32)
				{
					double src[20];
					double des[8]{ -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0 };

					int32_t indexes[8]{ 1, 3, 5, 7, 9, 11, 13, 15 };
					int64_t merge[8]{ 1, 1, 0, 1, 1, 0, 1, 1 };

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
					double src[20];
					double des[8]{ -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0 };

					int64_t indexes[8]{ 1, 3, 5, 7, 9, 11, 13, 15 };
					int64_t merge[8]{ 1, 1, 0, 1, 1, 0, 1, 1 };

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
					float src[20];
					float des[8]{ -1.0F, -1.0F, -1.0F, -1.0F, -1.0F, -1.0F, -1.0F, -1.0F };

					int32_t indexes[8]{ 1, 3, 5, 7, 9, 11, 13, 15 };
					int32_t merge[8]{ 1, 1, 0, 1, 1, 0, 1, 1 };

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
					float src[20];
					float des[8]{ -1.0F, -1.0F, -1.0F, -1.0F, -1.0F, -1.0F, -1.0F, -1.0F };

					int64_t indexes[8]{ 1, 3, 5, 7, 9, 11, 13, 15 };
					int32_t merge[8]{ 1, 1, 0, 1, 1, 0, 1, 1 };

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

				TEST_METHOD(Test_Sum_Int)
				{
					alignas(32) YmmVal a;
					alignas(32) YmmVal b;
					alignas(32) YmmVal result;

					// To test wraparound.
					a.Int32[0] = INT_MAX; b.Int32[0] = 100;

					for (size_t i = 1; i < 8; i++)
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

					for (size_t i = 1; i < 16; i++)
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