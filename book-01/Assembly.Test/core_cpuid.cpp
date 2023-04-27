#include "pch.h"
#include "CppUnitTest.h"
#include "../Assembly/asm-headers/core_cpuid.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Assembly::Core::CPUID;
using namespace std;

namespace Assembly {
	namespace Test {
		namespace Core {
			TEST_CLASS(CPUID)
			{
			public:
				TEST_METHOD(Test_Get)
				{
					CpuidInfo ci;

					ci.LoadInfo();

					const string processorBrand = ci.GetProcessorBrand();
					const string vendorId = ci.GetVendorId();

					Assert::IsTrue(processorBrand.length() > 0);
					Assert::IsTrue(vendorId.length() > 0);
					Assert::IsTrue(ci.Has(CpuidInfo::FeatureFlag::AVX));
					Assert::IsTrue(ci.Has(CpuidInfo::FeatureFlag::AVX2));
#if BUILD_AVX512 == 1
					Assert::IsTrue(ci.Has(CpuidInfo::FeatureFlag::AVX512BW));
					Assert::IsTrue(ci.Has(CpuidInfo::FeatureFlag::AVX512CD));
					Assert::IsTrue(ci.Has(CpuidInfo::FeatureFlag::AVX512F));
#endif
					Assert::IsTrue(ci.Has(CpuidInfo::FeatureFlag::BMI1));
					Assert::IsTrue(ci.Has(CpuidInfo::FeatureFlag::FMA));

					Logger::WriteMessage(processorBrand.c_str());
					Logger::WriteMessage(vendorId.c_str());
				}
			};
		}
	}
}